/* Dem_MM_BlockWrite_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM_BlockWrite/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#include "../../../inc/Dem_Mm_MM.h"
#include "../../../inc/Dem_Mm_MemSync.h"
#include "../../../cfg/Dem_MM_Cfg.h"
#include "Dem_MM_local.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Status of Block */
#define DEM_MM_BLK_STS_01_INITIAL             DEM_MM_BLK_STS_INITIAL_VALUE
#define DEM_MM_BLK_STS_02_WRITE_REQ           ((Dem_u08_MMBlockStatusType)0x11U)
#define DEM_MM_BLK_STS_03_WRITE_CONFIRM       ((Dem_u08_MMBlockStatusType)0x22U)
#define DEM_MM_BLK_STS_04_PROCESS_COMPLETE    ((Dem_u08_MMBlockStatusType)0x33U)

/* Block Status Change Trigger */
typedef uint8       Dem_u08_MMBlockWriteMtxTrgrType;

#define DEM_MM_BLK_TRG_01_WRITE_REQ_OK              ((Dem_u08_MMBlockWriteMtxTrgrType)0x00U)
#define DEM_MM_BLK_TRG_02_WRITE_REQ_NG              ((Dem_u08_MMBlockWriteMtxTrgrType)0x11U)
#define DEM_MM_BLK_TRG_03_WRITE_OK                  ((Dem_u08_MMBlockWriteMtxTrgrType)0x22U)
#define DEM_MM_BLK_TRG_04_WRITE_NG                  ((Dem_u08_MMBlockWriteMtxTrgrType)0x33U)
#define DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM    ((Dem_u08_MMBlockWriteMtxTrgrType)0x44U)
#define DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT     ((Dem_u08_MMBlockWriteMtxTrgrType)0x55U)
#define DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT ((Dem_u08_MMBlockWriteMtxTrgrType)0x66U)
#define DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT     ((Dem_u08_MMBlockWriteMtxTrgrType)0x77U)
#define DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE     ((Dem_u08_MMBlockWriteMtxTrgrType)0x88U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    P2VAR( void, TYPEDEF, DEM_VAR_NO_INIT ) MirrorPtr;
} Dem_MMWriteBlockInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessWriteReq
( void );
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessConfirmComplete
( void );

static FUNC( void, DEM_CODE ) Dem_MM_NotifyWriteComplete
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);

static FUNC( void, DEM_CODE ) Dem_MM_BlockStatusTransition
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
);
static FUNC( void, DEM_CODE ) Dem_MM_BS01_Init
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
);
static FUNC( void, DEM_CODE ) Dem_MM_BS02_WriteReq
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
);
static FUNC( void, DEM_CODE ) Dem_MM_BS03_WriteConfirm
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
);
static FUNC( void, DEM_CODE ) Dem_MM_BS04_ProcessComplete
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
);

/* Switching function group */
static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentRetryWriteReq
( void );
static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentWaitSingleBlockProcess
( void );

static FUNC( void, DEM_CODE ) Dem_MM_ClearRetryWriteReqCnt
( void );
static FUNC( void, DEM_CODE ) Dem_MM_ClearSingleBlockTimeOutCnt
( void );


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_NvBlockIndexType, DEM_VAR_NO_INIT ) Dem_MM_WriteBlockListIndex;

/* Mirror data information */
static VAR( Dem_MMWriteBlockInfoType, DEM_VAR_NO_INIT ) Dem_MM_SyncNvBlockInfo;

/* Request Retry counter */
static VAR( Dem_u08_MMRetryCountType, DEM_VAR_NO_INIT ) Dem_MM_RetryWriteReqCnt;

/* Timeout Counter */
static VAR( Dem_u32_MMTimeOutCountType, DEM_VAR_NO_INIT ) Dem_MM_SingleBlockTimeOutCnt;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_MM_InitBlockWriteStatus                              */
/* Description   | Initializes manage data for BlockWrite.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_InitBlockWriteStatus
( void )
{
    Dem_MM_WriteBlockListIndex            = DEM_MM_INDEX_INITIAL_VALUE;

    /* Initialization of mirror area information */
    Dem_MM_SyncNvBlockInfo.MirrorPtr        = NULL_PTR;

    Dem_MM_ClearRetryWriteReqCnt();
    Dem_MM_ClearSingleBlockTimeOutCnt();

    Dem_MM_InitNvBlockStatusOfList();

    return ;
}

/****************************************************************************/
/* Function Name | Dem_MM_ProcessIdle                                       */
/* Description   | processing the IDLE status of the Dem_MM unit            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |  DEM_MM_WRITEEXEC_IDLE       :   not write.              */
/*               |  DEM_MM_WRITEEXEC_PROCESSING :   write process execute.  */
/*               |  DEM_MM_WRITEEXEC_COMPLETE   :   complete write process. */
/*               |                              :   (cannot write starting.)*/
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessIdle
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetNvWriteBlockData;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) writeBlockListIndex;
    VAR( Dem_DataMirrorInfoType, AUTOMATIC ) syncNvBlockInfo;

    retExecWrite   =   DEM_MM_WRITEEXEC_IDLE;
    /* Variable initialization */
    syncNvBlockInfo.MirrorPtr        = NULL_PTR;
    syncNvBlockInfo.RecordIndex      = DEM_RECORDINDEX_INVALID;
    syncNvBlockInfo.BlockRecordKind  = DEM_MMBLKRECKINDINDEX_INVALID;
    syncNvBlockInfo.RecordDataOffset = (Dem_u16_RecordDataSizeType)0x0000U;
    syncNvBlockInfo.MirrorLength     = (Dem_u16_RecordDataSizeType)0x0000U;

    /* Request for acquisition of nonvolatile write block information */
    resultGetNvWriteBlockData = Dem_DmSnc_GetNvMWriteData( &syncNvBlockInfo );

    /* When there is a writing target */
    if( resultGetNvWriteBlockData ==  DEM_IRT_OK )
    {
        /* Store target data Info */
        Dem_MM_SyncNvBlockInfo.MirrorPtr = syncNvBlockInfo.MirrorPtr;

        /* Clear monitoring information */
        writeBlockListIndex =  DEM_MM_INDEX_INITIAL_VALUE;
        Dem_MM_WriteBlockListIndex = DEM_MM_INDEX_INITIAL_VALUE;
        Dem_MM_ClearRetryWriteReqCnt();
        Dem_MM_ClearSingleBlockTimeOutCnt();

        /* Target block Id setting processing */
        Dem_MM_GetNvBlockIndex( syncNvBlockInfo.RecordIndex, syncNvBlockInfo.RecordDataOffset, syncNvBlockInfo.BlockRecordKind, &writeBlockListIndex );

        /* Store target list Index */
        Dem_MM_WriteBlockListIndex = writeBlockListIndex;

        /* Update UnitStatus */
        retExecWrite   =   DEM_MM_WRITEEXEC_PROCESSING; /*  processing  */
    }
    else
    {
        /* No update data */
        /* No process */
    }

    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_ProcessRequest                                    */
/* Description   | processing the REQUEST status of the Dem_MM unit         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |      DEM_MM_WRITEEXEC_EXEC   :   write process execute.  */
/*               |      DEM_MM_WRITEEXEC_COMPLETE:  complete write process. */
/*               |         TRUE     :   write complete                      */
/*               |         FALSE    :   writing process                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessRequest
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;
    VAR( Dem_u08_MMBlockStatusType, AUTOMATIC ) nvBlockStatus;

    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )   nvmUseNvblockNum;

    retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;  /*  complete        */

    /* Variable initialization */
    nvmUseNvblockNum = Dem_NvMUseNvblockNum;

    if ( Dem_MM_WriteBlockListIndex < nvmUseNvblockNum )
    {
        /* Nonvolatile block-based management state acquisition request */
        nvBlockStatus = Dem_MM_GetNvBlockStatusOfList( Dem_MM_WriteBlockListIndex );

        /* If the acquisition of the block list information is successful */
        switch( nvBlockStatus )
        {
            case DEM_MM_BLK_STS_01_INITIAL:
                /* Nonvolatile write request processing */
                retExecWrite   =   Dem_MM_ProcessWriteReq();
                break;
            case DEM_MM_BLK_STS_02_WRITE_REQ:
                /* Nonvolatile write request processing */
                retExecWrite   =   Dem_MM_ProcessWriteReq();
                break;
            case DEM_MM_BLK_STS_03_WRITE_CONFIRM:
                /* Writing processing state check processing */
                retExecWrite   =   Dem_MM_ProcessConfirmComplete();
                break;
            case DEM_MM_BLK_STS_04_PROCESS_COMPLETE:
                /* No process */
                break;
            default:
                /* No process */
                break;
        }
    }

    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_ProcessWriteReq                                   */
/* Description   | Processing in the state of write request                 */
/* Preconditions | Only when the Dem_MM unit status is in the write reques- */
/*               | t in progress state                                      */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |  DEM_MM_WRITEEXEC_PROCESSING :   write process execute.  */
/*               |  DEM_MM_WRITEEXEC_COMPLETE   :   complete write process. */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessWriteReq
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;

    VAR( Std_ReturnType, AUTOMATIC ) retValWriteBlock;
    VAR( boolean, AUTOMATIC ) resultJudgmentRetry;
    VAR( Dem_NvBlockType, AUTOMATIC ) nvBlockInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetNvBlockInfo;

    retExecWrite   =   DEM_MM_WRITEEXEC_PROCESSING;  /*  processing      */

    /* Nonvolatile block write request */
    resultGetNvBlockInfo = Dem_MM_GetNvBlockInfo( Dem_MM_WriteBlockListIndex, &nvBlockInfo);
    if( resultGetNvBlockInfo == DEM_IRT_OK )
    {
        retValWriteBlock = Dem_NvM_If_WriteSingleBlock( nvBlockInfo.DemNvRamBlockId, Dem_MM_SyncNvBlockInfo.MirrorPtr );

        /* If the nonvolatile write request is successful */
        if( retValWriteBlock == (Std_ReturnType)E_OK )
        {
            Dem_MM_ClearRetryWriteReqCnt();

            /* Block status update */
            Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_01_WRITE_REQ_OK );
        }
        else
        {
            /* Retry determination of write request */
            resultJudgmentRetry = Dem_MM_JudgmentRetryWriteReq();

            /* In case of retry permission */
            if( resultJudgmentRetry == (boolean)TRUE )
            {
                /* Block status update */
                Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_02_WRITE_REQ_NG );
            }
            else
            {
                /* Block status update */
                Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT );

                /* Write processing completion notification -Failure- */
                Dem_MM_NotifyWriteComplete( DEM_IRT_NG );

                retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */
            }
        }
    }
    else
    {
        retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */
    }
    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_ProcessConfirmComplete                            */
/* Description   | Processing in the request processing completion confirm- */
/*               | ing state                                                */
/* Preconditions | Only when the Dem_MM unit status is in the request proc- */
/*               | essing completion confirming state                       */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |  DEM_MM_WRITEEXEC_PROCESSING :   write process execute.  */
/*               |  DEM_MM_WRITEEXEC_COMPLETE   :   complete write process. */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessConfirmComplete
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;

    VAR( Dem_NvM_RequestResultType, AUTOMATIC ) nvResultStatus;
    VAR( Std_ReturnType, AUTOMATIC ) resultGetErrorStatus;
    VAR( Std_ReturnType, AUTOMATIC ) resultCancelJob;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) judgmentStatus;
    VAR( boolean, AUTOMATIC ) resultWaitProcess;
    VAR( boolean, AUTOMATIC ) timeOutJdgProcess;
    VAR( boolean, AUTOMATIC ) cancelProcess;
    VAR( Dem_NvBlockType, AUTOMATIC ) nvBlockInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetNvBlockInfo;

    retExecWrite   =   DEM_MM_WRITEEXEC_PROCESSING;  /*  processing      */

    /* Variable initialization */
    nvResultStatus       = DEM_NVM_REQ_OK;
    timeOutJdgProcess    = (boolean)FALSE;
    cancelProcess        = (boolean)FALSE;

    /* Nv block status acquisition request */
    resultGetNvBlockInfo = Dem_MM_GetNvBlockInfo( Dem_MM_WriteBlockListIndex, &nvBlockInfo );
    if( resultGetNvBlockInfo == DEM_IRT_OK )
    {
        resultGetErrorStatus = Dem_NvM_If_GetWriteBlockStatus( nvBlockInfo.DemNvRamBlockId, &nvResultStatus );

        if( resultGetErrorStatus == (Std_ReturnType)E_OK )
        {
            /* Internal classification of acquisition block state */
            judgmentStatus = Dem_MM_JudgmentErrorStatus( nvResultStatus );

            switch( judgmentStatus )
            {
                case DEM_IRT_PENDING:
                    /* Timeout determination processing flag setting */
                    timeOutJdgProcess = (boolean)TRUE;

                    /* Block status update */
                    Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM );

                    break;

                case DEM_IRT_OK:
                    /* Block status update */
                    Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_03_WRITE_OK );

                    /* Write Success notification processing */
                    Dem_MM_NotifyWriteComplete( DEM_IRT_OK );

                    retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */
                    break;

                default:        /*   DEM_IRT_NG:        */
                    /* Block status update */
                    Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex,DEM_MM_BLK_TRG_04_WRITE_NG );

                    /* Write processing completion notification -Failure- */
                    Dem_MM_NotifyWriteComplete( DEM_IRT_NG );

                    retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */

                    break;
            }
        }
        else
        {
            /* Cancel process execution flag setting */
            cancelProcess = (boolean)TRUE;

            /* Block status update */
            Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT );

        }
        /* Time-out judgement execuation */
        if( timeOutJdgProcess == (boolean)TRUE )
        {
            resultWaitProcess = Dem_MM_JudgmentWaitSingleBlockProcess();

            /* When time-out occurs */
            if( resultWaitProcess != (boolean)TRUE )
            {
                /* Error notification -TimeOut- */
                Dem_NotifyErrorStatus( nvBlockInfo.DemNvRamBlockId, DEM_ERROR_NVM_WRITE_TIMEOUT );

                /* Set cancel processing flag to ON */
                cancelProcess = (boolean)TRUE;

                /* Block status update */
                Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT );
            }
            else
            {
                /* No process. Within specified time. */
            }
        }

        /* Cancel processing judgement */
        if( cancelProcess == (boolean)TRUE )
        {
            resultCancelJob = Dem_NvM_If_CancelWriteJob( nvBlockInfo.DemNvRamBlockId );

            if( resultCancelJob != (Std_ReturnType)E_OK)
            {
                /* Error notification -CancelFailed- */
                Dem_NotifyErrorStatus( nvBlockInfo.DemNvRamBlockId, DEM_ERROR_NVM_CANCEL_FAILED );
            }
            else
            {
                /* No process */
            }

            /* Write processing completion notification -Failure- */
            Dem_MM_NotifyWriteComplete( DEM_IRT_NG );

            retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */
        }
    }
    else
    {
        retExecWrite   =   DEM_MM_WRITEEXEC_COMPLETE;   /*  complete    */
    }
    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_NotifyWriteComplete                               */
/* Description   | Non-volatile write Complete notification processing      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Result:                                             */
/*               |        Write process result                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_NotifyWriteComplete
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    /* Write processing completion notification -success- */
    Dem_DmSnc_CompleteWrite( Result );

    /* Initialize the retry counter */
    Dem_MM_ClearRetryWriteReqCnt();

    /* Reset timer monitoring */
    Dem_MM_ClearSingleBlockTimeOutCnt();

    /* Block status update */
    Dem_MM_BlockStatusTransition( Dem_MM_WriteBlockListIndex, DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_BlockStatusTransition                             */
/* Description   | Changes status for Block.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/*               | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_BlockStatusTransition
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
)
{
    /* Auto variable definition */
    VAR( Dem_u08_MMBlockStatusType, AUTOMATIC ) nvBlockStatus;

    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )   nvmUseNvblockNum;

    /* Variable initialization */
    nvmUseNvblockNum = Dem_NvMUseNvblockNum;

    if ( ListIndex < nvmUseNvblockNum )
    {
        /* Nonvolatile block-based management state acquisition request */
        nvBlockStatus = Dem_MM_GetNvBlockStatusOfList( Dem_MM_WriteBlockListIndex );

        switch( nvBlockStatus )
        {
            case DEM_MM_BLK_STS_01_INITIAL:
                Dem_MM_BS01_Init( ListIndex, Trigger );
                break;
            case DEM_MM_BLK_STS_02_WRITE_REQ:
                Dem_MM_BS02_WriteReq( ListIndex, Trigger );
                break;
            case DEM_MM_BLK_STS_03_WRITE_CONFIRM:
                Dem_MM_BS03_WriteConfirm( ListIndex, Trigger );
                break;
            case DEM_MM_BLK_STS_04_PROCESS_COMPLETE:
                Dem_MM_BS04_ProcessComplete( ListIndex, Trigger );
                break;
            default:
                /* No process */
                break;
        }
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MM_BS01_Init                                         */
/* Description   | Block state transition processing at state S1            */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/*               | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_BS01_Init
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
)
{

    switch( Trigger )
    {
        case DEM_MM_BLK_TRG_01_WRITE_REQ_OK:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_03_WRITE_CONFIRM );
            break;
        case DEM_MM_BLK_TRG_02_WRITE_REQ_NG:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_02_WRITE_REQ );
            break;
        case DEM_MM_BLK_TRG_03_WRITE_OK:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
        case DEM_MM_BLK_TRG_04_WRITE_NG:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
        case DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
            break;
        case DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;
        case DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT:
            /* No process. Same as DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE */
        case DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT:
            /* No process. Same as DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE */
        case DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE:
            /* No process */
            break;
        default:
            /* No process */
            break;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MM_BS02_WriteReq                                     */
/* Description   | Block state transition processing at state S2            */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/*               | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_BS02_WriteReq
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
)
{

    switch( Trigger )
    {
        case DEM_MM_BLK_TRG_01_WRITE_REQ_OK:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_03_WRITE_CONFIRM );
            break;
        case DEM_MM_BLK_TRG_02_WRITE_REQ_NG:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
        case DEM_MM_BLK_TRG_03_WRITE_OK:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
        case DEM_MM_BLK_TRG_04_WRITE_NG:
            /* No process. Same as DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM */
        case DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM:
            /* No process */
            break;
        case DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;
        case DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT:
            /* No process. Same as DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE */
        case DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT:
            /* No process. Same as DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE */
        case DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE:
            /* No process */
            break;
        default:
            /* No process */
            break;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MM_BS03_WriteConfirm                                 */
/* Description   | Block state transition processing at state S3            */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/*               | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_BS03_WriteConfirm
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
)
{

    switch( Trigger )
    {
        case DEM_MM_BLK_TRG_01_WRITE_REQ_OK:
            /* No process. Same as DEM_MM_BLK_TRG_02_WRITE_REQ_NG */
        case DEM_MM_BLK_TRG_02_WRITE_REQ_NG:
            /* No process */
            break;
        case DEM_MM_BLK_TRG_03_WRITE_OK:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;
        case DEM_MM_BLK_TRG_04_WRITE_NG:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;
        case DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM:
            /* No process. Same as DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT */
        case DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT:
            /* No process */
            break;
        case DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;
        case DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_04_PROCESS_COMPLETE );
            break;

        case DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE:
            /* No process */
            break;
        default:
            /* No process */
            break;
    }

   return;
}


/****************************************************************************/
/* Function Name | Dem_MM_BS04_ProcessComplete                              */
/* Description   | Block state transition processing at state S4            */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/*               | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_BS04_ProcessComplete
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockWriteMtxTrgrType, AUTOMATIC ) Trigger
)
{

    switch( Trigger )
    {
        case DEM_MM_BLK_TRG_01_WRITE_REQ_OK:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_02_WRITE_REQ_NG:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_03_WRITE_OK:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_04_WRITE_NG:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_05_WRITE_RESULT_UNCONFIRM:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_06_WRITE_REQ_RETRY_LIMIT:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_07_WRITE_CONFIRM_RETRY_LIMIT:
            /* No process. Same as DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT */
        case DEM_MM_BLK_TRG_08_WRITE_PROCESS_TIMEOUT:
            /* No process */
            break;
        case DEM_MM_BLK_TRG_09_WRITE_NOTIFY_COMPLETE:
            Dem_MM_SetNvBlockStatusOfList( ListIndex, DEM_MM_BLK_STS_01_INITIAL );
            break;
        default:
            /* No process */
            break;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_MM_JudgmentRetryWriteReq                             */
/* Description   | Retry determination processing of nonvolatile write req- */
/*               | uest                                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Retry is possible.                         */
/*               |        FALSE : Retry is impossible.                      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentRetryWriteReq
( void )
{
    /* Auto variable definition */
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_MMRetryCountType, AUTOMATIC ) reqAccessNVMMaxCnt;

    reqAccessNVMMaxCnt = Dem_MMReqAccessNvMMaxCnt;

    /* Retry limit upper check */
    if( Dem_MM_RetryWriteReqCnt >= reqAccessNVMMaxCnt )
    {
        /* Retry is impossible. */
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Increment of retry count */
        Dem_MM_RetryWriteReqCnt = Dem_MM_RetryWriteReqCnt + (Dem_u08_MMRetryCountType)1U;
        /* Retry is possible. */
        retVal = (boolean)TRUE;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_JudgmentWaitSingleBlockProcess                    */
/* Description   | Timeout determination processing of single block proces- */
/*               | sing                                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE :  Retry is possible.                        */
/*               |        FALSE : Retry is impossible.                      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentWaitSingleBlockProcess
( void )
{
    /* Auto variable definition */
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u32_MMTimeOutCountType, AUTOMATIC ) singleBlockTimeoutCnt;

    singleBlockTimeoutCnt = Dem_MMSingleBlockTimeoutCnt;

    /* Count up */
    Dem_MM_SingleBlockTimeOutCnt = Dem_MM_SingleBlockTimeOutCnt + (Dem_u32_MMTimeOutCountType)1U;       /*  no wrap around      */

    /* Timeout limit upper check */
    if( Dem_MM_SingleBlockTimeOutCnt >= singleBlockTimeoutCnt )
    {
        /* Retry is impossible. */
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Retry is possible. */
        retVal = (boolean)TRUE;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_ClearRetryWriteReqCnt                             */
/* Description   | Clear write request retry counter.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_ClearRetryWriteReqCnt
( void )
{
    Dem_MM_RetryWriteReqCnt = DEM_MM_RETRYCNT_INITIAL_VALUE;
    return;
}


/****************************************************************************/
/* Function Name | Dem_MM_ClearSingleBlockTimeOutCnt                        */
/* Description   | Clear single block process timeout count.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_ClearSingleBlockTimeOutCnt
( void )
{
    Dem_MM_SingleBlockTimeOutCnt = DEM_MM_TIMEOUTCNT_INITIAL_VALUE;
    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
