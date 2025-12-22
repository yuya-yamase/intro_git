/* Dem_MM_BlockRead_c(v5-7-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM_BlockRead/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Mm_MM.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../cfg/Dem_MM_Cfg.h"
#include "Dem_MM_local.h"


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_CheckSingleBlockStatus
( void );
static FUNC( void, DEM_CODE ) Dem_MM_CheckReadComplete
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex
);

static FUNC( void, DEM_CODE ) Dem_MM_SetAllBlockReadFailure
( void );
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetMultiBlockStatus
( void );

static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentWaitReadAll
( void );

static FUNC( void, DEM_CODE ) Dem_MM_RAMInit
(
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) BlockRecordKind,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DataPtr,
    VAR( Dem_u16_BlockSizeType, AUTOMATIC ) Length
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( boolean, DEM_VAR_NO_INIT ) Dem_MM_MultiBlockJobEnd;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_MM_ReadFailBlockExist;
static VAR( Dem_u16_NvBlockIndexType, DEM_VAR_NO_INIT ) Dem_MM_NumberOfCheckedBlocks;

/* Timeout Counter */
static VAR( Dem_u32_MMTimeOutCountType, DEM_VAR_NO_INIT ) Dem_MM_ReadAllTimeOutCnt;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_MM_InitBlockReadStatus                               */
/* Description   | Initializes manage data for BlockRead.                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_InitBlockReadStatus
( void )
{
    Dem_MM_MultiBlockJobEnd               = (boolean)FALSE;
    Dem_MM_ReadFailBlockExist             = (boolean)FALSE;
    Dem_MM_NumberOfCheckedBlocks        = (Dem_u16_NvBlockIndexType)0U;

    Dem_MM_ReadAllTimeOutCnt = DEM_MM_TIMEOUTCNT_INITIAL_VALUE;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_MM_CheckNvBlockStatus                                */
/* Description   | Checks all Nv block status to use Dem.                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Non-volatilization reading complete. */
/*               |        DEM_IRT_PENDING : Non-volatilization reading pen- */
/*               |        ding.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_CheckNvBlockStatus
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultMultiBlockStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultSingleBlockCheck;
    VAR( boolean, AUTOMATIC ) waitReadAll;

    /* Variable initialization */
    retVal = DEM_IRT_OK;

    /* Confirmation of the completion of ReadAll */
    if( Dem_MM_MultiBlockJobEnd == (boolean)TRUE )
    {
        /* Set ReadAll state to complete */
        resultMultiBlockStatus = DEM_IRT_OK;
    }
    else
    {
        /* Get ReadAll status */
        resultMultiBlockStatus = Dem_MM_GetMultiBlockStatus();
    }

    /* ReadAll is completed */
    if( resultMultiBlockStatus != DEM_IRT_PENDING )
    {
        Dem_MM_MultiBlockJobEnd = (boolean)TRUE;

        /* Block processing status acquisition */
        resultSingleBlockCheck = Dem_MM_CheckSingleBlockStatus();

        /* If the processing is not completed */
        if( resultSingleBlockCheck == DEM_IRT_PENDING )
        {
            retVal = DEM_IRT_PENDING;
        }
        else
        {
            /*----------------------------------*/
            /*  all block checked.              */
            /*----------------------------------*/

            /* If there is a failing Block */
            if( Dem_MM_ReadFailBlockExist == (boolean)TRUE )
            {
                /* Error notification -Failed block- */
                Dem_NotifyErrorStatus( DEM_BLOCKID_MULTIBLOCK, DEM_ERROR_NVM_READALL_READ_FAILED );
            }
        }
    }
    else
    {
        /* If the ReadAll is incomplete */
        /* Timeout judgment */
        waitReadAll = Dem_MM_JudgmentWaitReadAll();

        /* In case of continuous monitoring */
        if( waitReadAll == (boolean)TRUE )
        {
            retVal = DEM_IRT_PENDING;
        }
        else
        {
            /* All block failure setting */
            Dem_MM_SetAllBlockReadFailure();

            /* Error notification -TimeOut- */
            Dem_NotifyErrorStatus( DEM_BLOCKID_MULTIBLOCK, DEM_ERROR_NVM_READALL_TIMEOUT );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_CheckSingleBlockStatus                            */
/* Description   | Status confirmation handling of non-volatilization bloc- */
/*               | kProcessing for checking the status of nonvolatile bloc- */
/*               | ks                                                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Non-volatilization reading complete. */
/*               |        DEM_IRT_PENDING : Non-volatilization reading pen- */
/*               |        ding.                                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_CheckSingleBlockStatus
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) listIndex;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) checkBlockCounter;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) mmNvMBlockCheckNum;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) nvmUseNvblockNum;


    /* Variable initialization */
    retVal = DEM_IRT_OK;
    checkBlockCounter = (Dem_u16_NvBlockIndexType)0U;
    mmNvMBlockCheckNum = Dem_MMNvMBlockCheckNum;
    nvmUseNvblockNum = Dem_NvMUseNvblockNum;

    /* Block status check loop processing */
    for( listIndex = Dem_MM_NumberOfCheckedBlocks; listIndex < nvmUseNvblockNum; listIndex++ )  /* [GUD:for]listIndex */
    {
        /* Block state confirmation processing */
        Dem_MM_CheckReadComplete( listIndex );                                                  /* [GUD]listIndex */

       /* Increment check block number count */
        checkBlockCounter = checkBlockCounter + (Dem_u16_NvBlockIndexType)1U;

        /* Confirmation of completion */
        if( checkBlockCounter > mmNvMBlockCheckNum )
        {
            /* If the set block number has been reached */
            /* Pending flag setting */

            /*  stored checked block count. */
            Dem_MM_NumberOfCheckedBlocks    =   listIndex + (Dem_u16_NvBlockIndexType)1U;

            retVal = DEM_IRT_PENDING;

            break;
        }

    } /* Check NvBlock Status process */

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_MM_CheckReadComplete                                 */
/* Description   | Read completion confirmation processing                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] ListIndex :                                         */
/*               |        List Index                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_CheckReadComplete
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex
)
{
    /* Auto variable definition */
    VAR( Dem_NvM_RequestResultType, AUTOMATIC ) getStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retValGetErrorStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) judgmentStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetNvBlockInfo;
    VAR( Dem_NvBlockType, AUTOMATIC ) nvBlockInfo;
    VAR( boolean, AUTOMATIC ) readBlockStatus;


    /* Variable initialization */
    getStatus = DEM_NVM_REQ_OK;
    nvBlockInfo.DemNvRamBlockId        = DEM_MM_INDEX_INITIAL_VALUE;
    nvBlockInfo.DemNvBlockLength       = (Dem_u16_BlockSizeType)0U;
    nvBlockInfo.DemRamBlockDataAddress = NULL_PTR;
    nvBlockInfo.BlockRecordKind        = (Dem_u16_MMBlockRecKindIndexType)0U;

    /*  error block.        */
    readBlockStatus =   (boolean)FALSE;

    /* Block status acquisition request */
    resultGetNvBlockInfo = Dem_MM_GetNvBlockInfo( ListIndex, &nvBlockInfo);
    if( resultGetNvBlockInfo == DEM_IRT_OK )
    {
        retValGetErrorStatus = Dem_NvM_If_GetReadBlockStatus( nvBlockInfo.DemNvRamBlockId, &getStatus );

        /* When block status acquisition is successful */
        if( retValGetErrorStatus == (Std_ReturnType)E_OK )
        {
            /* Internal classification of acquisition block status */
            judgmentStatus = Dem_MM_JudgmentErrorStatus( getStatus );

            if ( judgmentStatus == DEM_IRT_OK )
            {
                /*  success block.      */
                readBlockStatus =   (boolean)TRUE;
            }
        }

        /*----------------------------------------------------------------------*/
        /*  Dem_NvM_If_GetReadBlockStatus returns not E_OK.                     */
        /*  Dem_NvM_If_GetReadBlockStatus's output parameter is not DEM_IRT_OK. */
        if ( readBlockStatus == (boolean)FALSE )
        {
            /* ReadFailureFlag */
            Dem_MM_ReadFailBlockExist = (boolean)TRUE;

            /* Corresponding permanent RAM area clear request */
            Dem_MM_RAMInit( nvBlockInfo.BlockRecordKind, (P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ))nvBlockInfo.DemRamBlockDataAddress, nvBlockInfo.DemNvBlockLength );

            /* ClrInfoBlock Read Failure */
            if( ListIndex == Dem_RecordInfo_NvBlockTable[Dem_MMNvMRecKindClrInfo].DemBlockIndexFirst )  /* [GUD:CFG]Dem_MMNvMRecKindClrInfo */
            {
                Dem_ClrInfoMng_NvMReadError();
            }
        }
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_SetAllBlockReadFailure                            */
/* Description   | Nonvolatile all block read failure process.              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_SetAllBlockReadFailure
( void )
{
    /* Auto variable definition */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) recStartPtr;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKind;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindNum;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )    blockIndexNumInKind;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )    blockIndexCnt;
    VAR( Dem_u16_BlockSizeType, AUTOMATIC )       blockSize;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )    recPtrOffset;

    /* Variable initialization */
    recKindNum    = Dem_MMNvMRecKindNum;

    /* Failure handling setting processing of all block(EventRecordList) */
    for( recKind = (Dem_u16_MMBlockRecKindIndexType)0U; recKind < recKindNum; recKind++ )   /* [GUD:for]recKind */
    {
        blockIndexNumInKind = (Dem_u16_NvBlockIndexType)Dem_RecordInfo_NvBlockTable[recKind].DemBlockTotalNum;                          /* [GUD]recKind */
        blockSize           = Dem_RecordInfo_NvBlockTable[recKind].DemBlockSize;                                                        /* [GUD]recKind */
        recStartPtr         = (P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ))Dem_RecordInfo_NvBlockTable[recKind].DemRamDataFirstPtr;   /* [GUD]recKind */

        for( blockIndexCnt = 0U; blockIndexCnt < blockIndexNumInKind; blockIndexCnt++ )     /* [GUD:for]blockIndexCnt */
        {
            recPtrOffset = (Dem_u16_NvBlockIndexType)( blockIndexCnt * blockSize );         /* [GUD:logic]recPtrOffset */

            /* Permanent RAM area clear request */
            /* Do not access outside the recStartPtr[recPtrOffset] because it is consistent with Aubist-Configurator */
            Dem_MM_RAMInit( recKind, &recStartPtr[recPtrOffset], blockSize );               /* [GUD]recPtrOffset *//* [ARYCHK] blockSize*blockIndexNumInKind / 1 / recPtrOffset */
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_MM_GetMultiBlockStatus                               */
/* Description   | Get status of multi block requests                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_PENDING : pending                         */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetMultiBlockStatus
( void )
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_NvM_RequestResultType, AUTOMATIC ) getStatus;
    VAR( Std_ReturnType, AUTOMATIC ) retValGetErrorStatus;

    /* Variable initialization */
    getStatus = DEM_NVM_REQ_OK;

    /* ReadAll processing status acquisition */
    retValGetErrorStatus = Dem_NvM_If_GetReadAllStatus( &getStatus );

    /* If the state acquisition succeeds */
    if( retValGetErrorStatus == (Std_ReturnType)E_OK )
    {
        /* Classify to internal status */
        retVal = Dem_MM_JudgmentErrorStatus( getStatus );
    }
    else
    {
        retVal = DEM_IRT_PENDING;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_JudgmentWaitReadAll                               */
/* Description   | Timeout determination processing of ReadAll processing   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : The specified time has not elapsed.        */
/*               |        FALSE : The specified time has passed.            */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MM_JudgmentWaitReadAll
( void )
{
    /* Auto variable definition */
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u32_MMTimeOutCountType, AUTOMATIC ) readAllTimeoutCnt;

    readAllTimeoutCnt = Dem_MMReadAllTimeoutCnt;

    /* Counter increment */
    Dem_MM_ReadAllTimeOutCnt = Dem_MM_ReadAllTimeOutCnt + (Dem_u32_MMTimeOutCountType)1U;   /*  no wrap around      */

    /* Timeout limit upper check */
    if( Dem_MM_ReadAllTimeOutCnt >= readAllTimeoutCnt )
    {
        /* Specified time has passed. */
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Specified time has not elapsed. */
        retVal = (boolean)TRUE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_MM_RAMInit                                           */
/* Description   | Initializes select RAM.                                  */
/* Preconditions | Usable only Dem_MM unit.                                 */
/* Parameters    | [in] BlockRecordKind :                                   */
/*               |        BlockRecordKind                                   */
/*               | [in] DataPtr :                                           */
/*               |        data address                                      */
/*               | [in] Length :                                            */
/*               |        data length                                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC          :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]IUMPR        :   NotifySavedZone                 */
/* UpdateRecord  | [UpdRec]AltIUMPR     :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MM_RAMInit
(
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) BlockRecordKind,  /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DataPtr,
    VAR( Dem_u16_BlockSizeType, AUTOMATIC ) Length
)
{
    /* Variable declaration */
    VAR( Dem_u16_BlockSizeType, AUTOMATIC  ) cnt;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DemRamDataPtr;

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindPFC;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindPFCMisfire;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindIUMPR;
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindAltIUMPR;
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )    */

    /* Data type cast processing */
    DemRamDataPtr = (P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE )) DataPtr;

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    recKindPFC      =   Dem_MMNvMRecKindPFC;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    recKindPFCMisfire   =   Dem_MMNvMRecKindPFCMisfire;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    recKindIUMPR    =   Dem_MMNvMRecKindIUMPR;
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    recKindAltIUMPR =   Dem_MMNvMRecKindAltIUMPR;
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )    */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if ( BlockRecordKind == recKindPFC )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        /* Clear data of designated area */
        for( cnt = (Dem_u16_BlockSizeType)0U; cnt < Length; cnt++ )     /* [GUD:for]cnt */
        {
            /* Clear processing */
            DemRamDataPtr[cnt]  = DEM_NVBLOCK_FACTORY_VALUE;            /* [GUD]cnt *//*[UpdRec]PFC *//* [ARYCHK] Length / 1 / cnt */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
    else
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    if ( BlockRecordKind == recKindPFCMisfire )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        /* Clear data of designated area */
        for( cnt = (Dem_u16_BlockSizeType)0U; cnt < Length; cnt++ )     /* [GUD:for]cnt */
        {
            /* Clear processing */
            DemRamDataPtr[cnt]  = DEM_NVBLOCK_FACTORY_VALUE;            /* [GUD]cnt *//*[UpdRec]PFCMisfire *//* [ARYCHK] Length / 1 / cnt */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
    else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( BlockRecordKind == recKindIUMPR )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_IUMPR update - start.         */
        Dem_NotifySavedZoneIUMPRUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        /* Clear data of designated area */
        for( cnt = (Dem_u16_BlockSizeType)0U; cnt < Length; cnt++ )     /* [GUD:for]cnt */
        {
            /* Clear processing */
            DemRamDataPtr[cnt]  = DEM_NVBLOCK_FACTORY_VALUE;            /* [GUD]cnt *//*[UpdRec]IUMPR *//* [ARYCHK] Length / 1 / cnt */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_IUMPR update - end.           */
        Dem_NotifySavedZoneIUMPRUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
    else
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )  /*  [FuncSw]    */
    if ( BlockRecordKind == recKindAltIUMPR )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_IUMPR update - start.         */
        Dem_NotifySavedZoneIUMPRUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        /* Clear data of designated area */
        for( cnt = (Dem_u16_BlockSizeType)0U; cnt < Length; cnt++ )     /* [GUD:for]cnt */
        {
            /* Clear processing */
            DemRamDataPtr[cnt]  = DEM_NVBLOCK_FACTORY_VALUE;            /* [GUD]cnt *//*[UpdRec]AltIUMPR *//* [ARYCHK] Length / 1 / cnt */
        }

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_IUMPR update - end.           */
        Dem_NotifySavedZoneIUMPRUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
    else
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )    */
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /* Clear data of designated area */
        for( cnt = (Dem_u16_BlockSizeType)0U; cnt < Length; cnt++ )     /* [GUD:for]cnt */
        {
            /* Clear processing */
            DemRamDataPtr[cnt]  = DEM_NVBLOCK_FACTORY_VALUE;            /* [GUD]cnt *//* [ARYCHK] Length / 1 / cnt */
        }

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
