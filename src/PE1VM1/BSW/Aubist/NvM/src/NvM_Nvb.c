/* NvM_Nvb.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/NVB/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include <NvM_Cbk.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Nvb_Internal.h"
#include "../inc/NvM_Nvb_Cust.h"
#include <MemIf.h>
#include <Mscd_Common.h>
#include "../inc/NvM_Lib.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Job.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( NvM_Nvb_MainStatusType,                             NVM_VAR_NO_INIT )               NvM_Nvb_MainStatus;
VAR( NvM_Nvb_SubStatusType,                              NVM_VAR_NO_INIT )               NvM_Nvb_SubStatus;
VAR( NvM_RequestResultType,                              NVM_VAR_NO_INIT )               NvM_Nvb_OperationResult;
VAR( NvM_Nvb_OperationInformationType,                   NVM_VAR_NO_INIT )               NvM_Nvb_ExecuteOperationInfo;

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
VAR( MemIf_JobResultType,                                NVM_VAR_NO_INIT )               NvM_Nvb_MainResult;
VAR( uint8,                                              NVM_VAR_NO_INIT )               NvM_Nvb_MainDataBuffer[NVM_MAX_REDUNDANT_BLOCK_LENGTH];
VAR( uint8,                                              NVM_VAR_NO_INIT )               NvM_Nvb_SubDataBuffer[NVM_MAX_REDUNDANT_BLOCK_LENGTH];
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )     NvM_Nvb_ConvertOperationIdPair[NVM_NVB_OPERATION_NUM] = 
{
    { (uint32)NVM_NVB_OPERATION_READ,       NVM_NVB_OPERATIONID_SER_READ        },
    { (uint32)NVM_NVB_OPERATION_WRITE,      NVM_NVB_OPERATIONID_SER_WRITE       }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )     NvM_Nvb_ConvertOperationIdTable = 
{
    NVM_NVB_OPERATION_NUM,
    NvM_Nvb_ConvertOperationIdPair
};

/* SubStatus Number Convert Table */
CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )     NvM_Nvb_SubStatusBitToSeqNumPair[NVM_NVB_SUB_COMMON_NUM] =
{
    { NVM_RND_NUM_UINT32_01, (uint32)NVM_NVB_SUB_COMMON_SEQ_00 },
    { NVM_RND_NUM_UINT32_02, (uint32)NVM_NVB_SUB_COMMON_SEQ_01 },
    { NVM_RND_NUM_UINT32_03, (uint32)NVM_NVB_SUB_COMMON_SEQ_02 },
    { NVM_RND_NUM_UINT32_04, (uint32)NVM_NVB_SUB_COMMON_SEQ_03 },
    { NVM_RND_NUM_UINT32_05, (uint32)NVM_NVB_SUB_COMMON_SEQ_04 },
    { NVM_RND_NUM_UINT32_06, (uint32)NVM_NVB_SUB_COMMON_SEQ_05 },
    { NVM_RND_NUM_UINT32_07, (uint32)NVM_NVB_SUB_COMMON_SEQ_06 }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )     NvM_Nvb_SubStatusBitToSeqNumTbl =
{
    NVM_NVB_SUB_COMMON_NUM,
    NvM_Nvb_SubStatusBitToSeqNumPair
};

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
CONST( AB_83_ConstV NvM_Nvb_MemIfRsltToRprNeedTblType,   NVM_CONST ) NvM_Nvb_MemIfRsltToRprNeedTbl[NVM_NVB_MEMIF_RESULT_PAIR_NUM] = 
{
    { MEMIF_JOB_OK,             MEMIF_JOB_OK,                 NVM_NVB_RPR_NEED_UNNEED         },
    { MEMIF_JOB_OK,             MEMIF_BLOCK_INCONSISTENT,     NVM_NVB_RPR_NEED_NEED_SUB       },
    { MEMIF_JOB_OK,             MEMIF_JOB_FAILED,             NVM_NVB_RPR_NEED_UNKNOWN        },
    { MEMIF_BLOCK_INCONSISTENT, MEMIF_JOB_OK,                 NVM_NVB_RPR_NEED_NEED_MAIN      },
    { MEMIF_BLOCK_INCONSISTENT, MEMIF_BLOCK_INCONSISTENT,     NVM_NVB_RPR_NEED_NODATA         },
    { MEMIF_BLOCK_INCONSISTENT, MEMIF_JOB_FAILED,             NVM_NVB_RPR_NEED_UNKNOWN        }
    /* If result of read from main NvBlock equals MEMIF_JOB_FAILE, repair need decide to UNKNOWN. */
    /* Therefore, excluded in this table. */
};
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

/*========================*/
/* Function pointer table */
/*========================*/

/* ----- Read operation execution function pointer table. ----- */
CONST( AB_83_ConstV NvM_Nvb_ActFuncType,   NVM_CONST ) NvM_Nvb_RdOpeExecFuncPtrTbl[] =
{
    &NvM_Nvb_ActRdNtvRsp,
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    &NvM_Nvb_ActRdRdtRprRdMainRsp,
    &NvM_Nvb_ActRdRdtRprRdSubRsp,
    &NvM_Nvb_ActRdRdtRprWtMainRsp,
    &NvM_Nvb_ActRdRdtRprWtSubRsp,
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
};
CONST( AB_83_ConstV uint16, NVM_CONST ) NvM_Nvb_RdOpeExecFuncPtrTblSize = sizeof( NvM_Nvb_RdOpeExecFuncPtrTbl ) / sizeof( NvM_Nvb_RdOpeExecFuncPtrTbl[0] );

/* ----- Write operation execution function pointer table. ----- */
CONST( AB_83_ConstV NvM_Nvb_ActFuncType,   NVM_CONST ) NvM_Nvb_WtOpeExecFuncPtrTbl[] =
{
    &NvM_Nvb_ActWtNtvRsp,
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    &NvM_Nvb_ActWtRdtRprRdMainRsp,
    &NvM_Nvb_ActWtRdtRprRdSubRsp,
    &NvM_Nvb_ActWtRdtRprWtMainRsp,
    &NvM_Nvb_ActWtRdtRprWtSubRsp,
    &NvM_Nvb_ActWtRdtWtMainRsp,
    &NvM_Nvb_ActWtRdtWtSubRsp,
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
};
CONST( AB_83_ConstV uint16, NVM_CONST ) NvM_Nvb_WtOpeExecFuncPtrTblSize = sizeof( NvM_Nvb_WtOpeExecFuncPtrTbl ) / sizeof( NvM_Nvb_WtOpeExecFuncPtrTbl[0] );

/* ----- Operation action table. ----- */

CONST( AB_83_ConstV NvM_Nvb_OperationActTblType,   NVM_CONST ) NvM_Nvb_OperationActTbl[NVM_NVB_OPERATION_NUM] =
{
    {
        /* Read Operation. */
        &NvM_Nvb_ActStartRd,
        &NvM_Nvb_RdOpeExecFuncPtrTblSize,
        NvM_Nvb_RdOpeExecFuncPtrTbl,
        &NvM_Nvb_ActCancel,
    },
    {
        /* Write Operation. */
        &NvM_Nvb_ActStartWt,
        &NvM_Nvb_WtOpeExecFuncPtrTblSize,
        NvM_Nvb_WtOpeExecFuncPtrTbl,
        &NvM_Nvb_ActCancel,
    }
};

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Nvb_Init                                             */
/* Description   | Service to initialize the NVB unit.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE ) NvM_Nvb_Init( void )
{
    NvM_Nvb_MainStatus = NVM_NVB_IDLING;
    NvM_Nvb_SubStatus = NVM_NVB_SUB_INVALID;
    NvM_Nvb_OperationResult = NVM_REQ_OK;
    NvM_Nvb_ExecuteOperationInfo.OperationId = NVM_NVB_OPERATION_NONE;
    NvM_Nvb_ExecuteOperationInfo.BlockId = NVM_BLOCKID_INVALID;
    NvM_Nvb_ExecuteOperationInfo.DstPtr = NULL_PTR;
    NvM_Nvb_ExecuteOperationInfo.SrcPtr = NULL_PTR;
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    NvM_Nvb_MainResult = MEMIF_JOB_OK;
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_RequestOperation                                 */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | OperationInfo :                                          */
/*               |            A structure which have operation information. */
/* Return Value  | Requirement receipting result.                           */
/*               | E_OK      : The requirement has receipted.               */
/*               | E_NOT_OK  : The requirement has not receipted.           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestOperation(
    P2CONST( NvM_Nvb_OperationInformationType, AUTOMATIC, TYPEDEF ) OperationInfo
){
    Std_ReturnType RequestResult = E_NOT_OK;

    if( NvM_Nvb_OperationResult != (NvM_RequestResultType)NVM_REQ_PENDING )
    {
        NvM_Nvb_StoreReqInfo( OperationInfo );
        RequestResult = E_OK;
        NvM_Nvb_OperationResult = NVM_REQ_PENDING;
        NvM_Nvb_MainStatus = NVM_NVB_IDLING;
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
        NvM_Nvb_MainResult = MEMIF_JOB_OK;
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
    }
    else
    {
        /* Nvb has already received operation request. */
    }

    return RequestResult;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_MainFunction                                     */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_MainFunction(
    uint8 CallMode
){
    NvM_Nvb_OperationIdType ReqOperationId;
    uint32 SerialOperationId;
    Std_ReturnType ChkResult;

    ReqOperationId = NvM_Nvb_ExecuteOperationInfo.OperationId;

    /* Check operation requirement status. */
    if( NvM_Nvb_OperationResult == (NvM_RequestResultType)NVM_REQ_PENDING )    /* No operation is required to execute. */
    {
        /* OperationId is not serial value. For using OperationId as function pointer array index, The Id need to be converted serial value. */
        SerialOperationId = NvM_Lib_ConvertValue( (uint32)ReqOperationId, NVM_NVB_OPERATIONID_SER_INVALID, &NvM_Nvb_ConvertOperationIdTable );

        ChkResult = E_NOT_OK;
        if( SerialOperationId < (uint8)NVM_NVB_OPERATION_NUM )    /* A operation is required to execute. */
        {
            ChkResult = NvM_Nvb_ChkExecBlockId();
        }
        
        if( ChkResult == (Std_ReturnType)E_OK )
        {
            NvM_Nvb_StateChangeAct( CallMode, SerialOperationId );
        }
        else
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_DestructiveCancelDrivingOperation                */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE ) NvM_Nvb_DestructiveCancelOperation( void )
{

    MemIf_Cancel( NVM_NVB_DUMMY_DEVICE_ID );

    if( NvM_Nvb_OperationResult == (NvM_RequestResultType)NVM_REQ_PENDING )
    {
        NvM_Nvb_MainStatus = NVM_NVB_RUNNING_CANCEL_WAITING;
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_GetOperationResult                               */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_RequestResultType, NVM_CODE ) NvM_Nvb_GetOperationResult( void )
{
    return NvM_Nvb_OperationResult;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_GetStatus                                        */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_StatusType, NVM_CODE ) NvM_Nvb_GetStatus( void )
{
    NvM_Nvb_StatusType NvbStatus;

    if( NvM_Nvb_OperationResult != (NvM_RequestResultType)NVM_REQ_PENDING )
    {
        NvbStatus = NVM_NVB_IDLE;
    }
    else
    {
        NvbStatus = NVM_NVB_BUSY;
    }

    return NvbStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SetMode                                          */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NvM_CODE ) NvM_Nvb_SetMode( NvM_Nvb_ModeType Mode )
{
#if ( NVM_DRV_MODE_SWITCH == STD_ON )
    MemIf_ModeType  SetMode;

    if( Mode == NVM_NVB_MODE_FAST )
    {
        SetMode = MEMIF_MODE_FAST;
    }
    else
    {
        SetMode = MEMIF_MODE_SLOW;
    }

    MemIf_SetMode( SetMode );
#endif
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Nvb_StoreReqInfo                                     */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_StoreReqInfo(
    P2CONST( NvM_Nvb_OperationInformationType, AUTOMATIC, TYPEDEF ) OperationInfo
){

    NvM_Nvb_ExecuteOperationInfo.OperationId = OperationInfo->OperationId;
    NvM_Nvb_ExecuteOperationInfo.BlockId = OperationInfo->BlockId;
    NvM_Nvb_ExecuteOperationInfo.DstPtr = OperationInfo->DstPtr;
    NvM_Nvb_ExecuteOperationInfo.SrcPtr = OperationInfo->SrcPtr;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_StateChangeAct                                   */
/* Description   | Service to execute state change action.                  */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/*               | SerialOperationId : Serialized OperationId.              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_StateChangeAct(
    uint8 CallMode,
    uint32 SerialOperationId
){

    NvM_Nvb_MainStatusType MainStatusCurrent = NvM_Nvb_MainStatus;
    NvM_Nvb_MainStatusType MainStatusNew = MainStatusCurrent;
    uint16 OperationExecFuncNum;
    uint32 SeqSubStatus;

    if( MainStatusCurrent == (NvM_Nvb_MainStatusType)NVM_NVB_IDLING )
    {
        MainStatusNew = NvM_Nvb_OperationActTbl[SerialOperationId].NvM_Nvb_OperationStartFuncPtr();
    }
    else if( MainStatusCurrent == (NvM_Nvb_MainStatusType)NVM_NVB_RUNNING_ACTIVE )
    {
        SeqSubStatus = NvM_Lib_ConvertValue( NvM_Nvb_SubStatus, NVM_NVB_SUB_INVALID_SEQ, &NvM_Nvb_SubStatusBitToSeqNumTbl );
        OperationExecFuncNum = *( NvM_Nvb_OperationActTbl[SerialOperationId].OperationExecFuncNumPtr );
        if( OperationExecFuncNum > SeqSubStatus )
        {
            MainStatusNew = NvM_Nvb_OperationActTbl[SerialOperationId].OperationExecFuncPtrTblAddr[SeqSubStatus]();
        }
    }
    else
    {
        ; /* None */
    }

    NvM_Nvb_CustExecMainFunction( CallMode );

    MainStatusNew = NvM_Nvb_StateChangeActForWait( SerialOperationId,
                                                       MainStatusNew );

    if( ( MainStatusCurrent != (NvM_Nvb_MainStatusType)NVM_NVB_IDLING )
     && ( MainStatusNew == (NvM_Nvb_MainStatusType)NVM_NVB_IDLING ) )
    {
        NvM_Nvb_ExecuteOperationInfo.OperationId = NVM_NVB_OPERATION_NONE;
    }

    NvM_Nvb_MainStatus = MainStatusNew;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_StateChangeActForWait                            */
/* Description   | Service to execute state change action for waiting.      */
/* Preconditions | None                                                     */
/* Parameters    | SerialOperationId : Serialized OperationId.              */
/*               | MainStatusCurrent : NVB unit's current main status.      */
/* Return Value  | Next main status                                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_StateChangeActForWait(
    uint32 SerialOperationId,
    NvM_Nvb_MainStatusType MainStatusCurrent
){
    MemIf_JobResultType MhaJobResult;
    NvM_Nvb_MainStatusType MainStatusNew = MainStatusCurrent;
    uint16 OperationExecFuncNum;
    uint32 SeqSubStatus;

    MhaJobResult = NvM_Nvb_GetMhaProcessingResult( NvM_Nvb_ExecuteOperationInfo.BlockId );

    if( MEMIF_JOB_PENDING != MhaJobResult )
    {
        if( MainStatusCurrent ==  (NvM_Nvb_MainStatusType)NVM_NVB_RUNNING_NORMAL_WAITING ) 
        {
            SeqSubStatus = NvM_Lib_ConvertValue( NvM_Nvb_SubStatus, NVM_NVB_SUB_INVALID_SEQ, &NvM_Nvb_SubStatusBitToSeqNumTbl );
            OperationExecFuncNum = *( NvM_Nvb_OperationActTbl[SerialOperationId].OperationExecFuncNumPtr );
            if( OperationExecFuncNum > SeqSubStatus )
            {
                MainStatusNew = NvM_Nvb_OperationActTbl[SerialOperationId].OperationExecFuncPtrTblAddr[SeqSubStatus]();
            }
        }
        else if( MainStatusCurrent == (NvM_Nvb_MainStatusType)NVM_NVB_RUNNING_CANCEL_WAITING )
        {
            MainStatusNew = NvM_Nvb_OperationActTbl[SerialOperationId].NvM_Nvb_CancelFuncPtr();
        }
        else
        {
            /* No process */
        }
    }

    return MainStatusNew;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActCancel                                        */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE ) NvM_Nvb_ActCancel( void )
{
    NvM_Nvb_MainStatusType MainStatus;

    MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_CANCELED );

    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ChkExecBlockId                                   */
/* Description   | The function for checking BlockId being executed.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : BlockId being executed is valid range.       */
/*               |  E_NOT_OK : BlockId being executed is invalid.           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_ChkExecBlockId( void )
{
    Std_ReturnType  Rtn;
    Std_ReturnType  GetJobExecBlockIdResult;
    NvM_BlockIdType JobExecBlockId              = NVM_BLOCKID_INVALID;

    Rtn = E_NOT_OK;
    GetJobExecBlockIdResult = NvM_Job_GetExecBlockId( &JobExecBlockId );
    if( GetJobExecBlockIdResult == (Std_ReturnType)E_OK )
    {
        if( JobExecBlockId == NvM_Nvb_ExecuteOperationInfo.BlockId )
        {
            Rtn = E_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_GetMhaProcessingResult                           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_JobResultType, NVM_CODE )
NvM_Nvb_GetMhaProcessingResult(
    NvM_BlockIdType BlockId
){
    MemIf_JobResultType MemIfResult;

    MemIfResult = MemIf_GetJobResult( NVM_NVB_DUMMY_DEVICE_ID );

    return MemIfResult;
}

/****************************************************************************/
/* Function Name | NvM_JobEndNotification                                   */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_POLLING_MODE == STD_OFF )
FUNC( void, NVM_CODE ) NvM_JobEndNotification( void )
{
    return;
}
#endif /* NVM_POLLING_MODE == STD_OFF */

/****************************************************************************/
/* Function Name | NvM_JobErrorNotification                                 */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_POLLING_MODE == STD_OFF )
FUNC( void, NVM_CODE ) NvM_JobErrorNotification( void )
{
    return;
}
#endif /* NVM_POLLING_MODE == STD_OFF */

/****************************************************************************/
/* Function Name | NvM_Nvb_RequestReadBlock                                 */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestReadBlock(
    NvM_BlockIdType BlockId,
    uint8 DataIndex,
    uint16 BlockOffset,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr,
    uint16 Length
){
    Std_ReturnType ReqResult;
    uint16 BlockNumber;

    BlockNumber = NvM_Nvb_MakeBlockNumber( BlockId, DataIndex );

    NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_REQ_FAILED );
    ReqResult = MemIf_Read( NVM_NVB_DUMMY_DEVICE_ID, BlockNumber, BlockOffset, DataBufferPtr, Length );

    if( ReqResult == (Std_ReturnType)E_OK )
    {
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
    }
    else
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }

    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_RequestWriteBlock                                */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestWriteBlock(
    NvM_BlockIdType BlockId,
    uint8 DataIndex,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr
){
    Std_ReturnType ReqResult;
    uint16 BlockNumber;

    BlockNumber = NvM_Nvb_MakeBlockNumber( BlockId, DataIndex );

    NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_REQ_FAILED );
    ReqResult = MemIf_Write( NVM_NVB_DUMMY_DEVICE_ID, BlockNumber, DataBufferPtr );

    if( ReqResult == (Std_ReturnType)E_OK )
    {
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
    }
    else
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }
    
    return ReqResult;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_MakeBlockNumber                                  */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint16, NVM_CODE )
NvM_Nvb_MakeBlockNumber(
    NvM_BlockIdType BlockId,
    uint8 DataIndex
){
    uint16 BlockNumber;

    BlockNumber = (uint16)( NvMBlockDescriptors[BlockId].NvMNvBlockBaseNumber << NvMDatasetSelectionBits ) + DataIndex;

    return BlockNumber;
}

/*-------------------------------------*/
/* Read operation's action function.   */
/*-------------------------------------*/

/****************************************************************************/
/* Function Name | NvM_Nvb_ActStartRd                                       */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActStartRd( void )
{
    Std_ReturnType ReqReadBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    NvM_BlockManagementTypeType BlockManagementType;
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;
    ExecBlockId = ExecOperationInfo->BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    BlockManagementType = NvMBlockDescriptors[ExecBlockId].NvMBlockManagementType;
    if( BlockManagementType == (NvM_BlockManagementTypeType)NVM_BLOCK_NATIVE )
    {
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
        ReqReadBlockResult = NvM_Nvb_RequestReadBlock( ExecBlockId, NVM_NVB_DATA_INDEX_NATIVE, NVM_NVB_OFFSET_NONE, ExecOperationInfo->DstPtr, NvBlockLength );
        if( ReqReadBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_RD_NTV_RSP;
        }
        else
        {
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    }
    else /* BlockManagementType == NVM_BLOCK_REDUNDANT */
    {
        ReqReadBlockResult = NvM_Nvb_RequestReadBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_MAIN, NVM_NVB_OFFSET_NONE, ExecOperationInfo->DstPtr, NvBlockLength );
        if( ReqReadBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_RD_RDT_RPR_RD_MAIN_RSP;
        }
        else
        {
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
    }
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActRdNtvRsp                                      */
/* Description   | Action function in sub status RD_NTV_RSP                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdNtvRsp( void )
{
    MemIf_JobResultType MhaJobResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;

    MainStatus = NvM_Nvb_MainStatus;

    MhaJobResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfReadJob( ExecBlockId, MhaJobResult );
    
    if( MEMIF_JOB_OK == MhaJobResult )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    }
    else if( MEMIF_JOB_FAILED == MhaJobResult )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else if( MEMIF_BLOCK_INCONSISTENT == MhaJobResult )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_NODATA );

        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_INTEGRITY_FAILED );
    }
    else if( MEMIF_BLOCK_INVALID == MhaJobResult )
    {
        /* It is within range but is not returned, so there is no process */
    }
    else
    {
        /* MEMIF_JOB_PENDING and MEMIF_JOB_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }

    return MainStatus;
}

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Nvb_ActRdRdtRprRdMainRsp                             */
/* Description   | Action function in sub status RD_RDT_RPR_RD_MAIN_RSP     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprRdMainRsp( void )
{
    MemIf_JobResultType RprRdMainResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;

    RprRdMainResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfReadJob( ExecBlockId, RprRdMainResult );
    
    if( RprRdMainResult == MEMIF_JOB_FAILED )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else
    {
        NvM_Nvb_MainResult = RprRdMainResult;
        
        MainStatus = NvM_Nvb_SubActRdRprReadSubStart();
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActRdRdtRprRdSubRsp                              */
/* Description   | Action function in sub status RD_RDT_RPR_RD_SUB_RSP      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprRdSubRsp( void )
{
    uint8 RprNeed;
    MemIf_JobResultType RprRdSubResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;
    ExecBlockId = ExecOperationInfo->BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;

    RprRdSubResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfReadJob( ExecBlockId, RprRdSubResult );
    if( RprRdSubResult != MEMIF_JOB_FAILED )
    {
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    RprNeed = NvM_Nvb_JudgeRepairNeed( NvM_Nvb_MainResult, RprRdSubResult, ExecOperationInfo->DstPtr, NvM_Nvb_SubDataBuffer, NvBlockLength );
    if( RprNeed == (uint8)NVM_NVB_RPR_NEED_UNNEED )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    }
    else if( ( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_MAIN )
          || ( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_SUB ) )
    {
        MainStatus = NvM_Nvb_SubActRdExecRepairStart( RprNeed );
    }
    else if( RprNeed == (uint8)NVM_NVB_RPR_NEED_NODATA )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_NODATA );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_INTEGRITY_FAILED );
    }
    else if( RprNeed == (uint8)NVM_NVB_RPR_NEED_UNKNOWN )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else /* RprNeed == NVM_NVB_RPR_NEED_INVALID */
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActRdRdtRprWtMainRsp                             */
/* Description   | Action function in sub status RD_RDT_RPR_WT_MAIN_RSP     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprWtMainRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    MemIf_JobResultType RprWtMainResult;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    
    RprWtMainResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, RprWtMainResult );
    if( RprWtMainResult != MEMIF_JOB_OK )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActRdRdtRprWtSubRsp                              */
/* Description   | Action function in sub status RD_RDT_RPR_WT_SUB_RSP      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprWtSubRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    MemIf_JobResultType RprWtSubResult;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    
    RprWtSubResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, RprWtSubResult );
    if( RprWtSubResult != MEMIF_JOB_OK )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActRdRprReadSubStart                          */
/* Description   | Function to start read for repair in read operation.     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActRdRprReadSubStart( void )
{
    Std_ReturnType ReqReadBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;

    ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;

    ReqReadBlockResult = NvM_Nvb_RequestReadBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_SUB, NVM_NVB_OFFSET_NONE, NvM_Nvb_SubDataBuffer, NvBlockLength );
    if( ReqReadBlockResult == (Std_ReturnType)E_OK )
    {
        MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
        NvM_Nvb_SubStatus = NVM_NVB_SUB_RD_RDT_RPR_RD_SUB_RSP;
    }
    else
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }

    return MainStatus;
}


/****************************************************************************/
/* Function Name | NvM_Nvb_SubActRdExecRepairStart                          */
/* Description   | Function to start repair in read operation.              */
/* Preconditions | None                                                     */
/* Parameters    | RprNeed : Judge result that repair need.                 */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActRdExecRepairStart(
    uint8 RprNeed
){
    Std_ReturnType ReqWriteBlockResult;
    Std_ReturnType ChkRprPermissionRslt;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ReadDstPtr;
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) SubDataBufferPtr;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;
    ExecBlockId = ExecOperationInfo->BlockId;
    ReadDstPtr = ExecOperationInfo->DstPtr;
    SubDataBufferPtr = NvM_Nvb_SubDataBuffer;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;
    
    ChkRprPermissionRslt = Mscd_Cnfm_CheckRestoreHook();
    if( ChkRprPermissionRslt == (Std_ReturnType)E_OK )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_RESTORE );

        if( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_MAIN )
        {
            NvM_Lib_MemcpyBitInvert( ReadDstPtr, SubDataBufferPtr, (uint32)NvBlockLength );
            
            ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_MAIN, ReadDstPtr );

            if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
            {
                MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
                NvM_Nvb_SubStatus = NVM_NVB_SUB_RD_RDT_RPR_WT_MAIN_RSP;
            }
            else
            {
                NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
                NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
                MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
            }
        }
        else    /* RprNeed == NVM_NVB_RPR_NEED_NEED_SUB */
        {
            NvM_Lib_MemcpyBitInvert( SubDataBufferPtr, ReadDstPtr, (uint32)NvBlockLength );
            
            ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_SUB, SubDataBufferPtr );

            if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
            {
                MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
                NvM_Nvb_SubStatus = NVM_NVB_SUB_RD_RDT_RPR_WT_SUB_RSP;
            }
            else
            {
                NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
                NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
                MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
            }
        }
    }
    else
    {
        if( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_MAIN )
        {
            NvM_Lib_MemcpyBitInvert( ReadDstPtr, SubDataBufferPtr, (uint32)NvBlockLength );
        }
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    }

    return MainStatus;
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


/*-------------------------------------*/
/* Write operation's action function.  */
/*-------------------------------------*/

/****************************************************************************/
/* Function Name | NvM_Nvb_ActStartWt                                       */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActStartWt( void )
{
    Std_ReturnType ReqWriteBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    Std_ReturnType ReqReadBlockResult;
    uint16 NvBlockLength;
    NvM_BlockManagementTypeType BlockManagementType;
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;
    ExecBlockId = ExecOperationInfo->BlockId;

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    BlockManagementType = NvMBlockDescriptors[ExecBlockId].NvMBlockManagementType;
    if( BlockManagementType == (NvM_BlockManagementTypeType)NVM_BLOCK_NATIVE )
    {
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
        ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_NATIVE, ExecOperationInfo->SrcPtr );
        if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_NTV_RSP;
        }
        else
        {
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
    }
    else /* BlockManagementType == NVM_BLOCK_REDUNDANT */
    {
        NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;
        
        ReqReadBlockResult = NvM_Nvb_RequestReadBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_MAIN, NVM_NVB_OFFSET_NONE, NvM_Nvb_MainDataBuffer, NvBlockLength );
        if( ReqReadBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_RPR_RD_MAIN_RSP;
        }
        else
        {
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
    }
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtNtvRsp                                      */
/* Description   | Action function in sub status WT_NTV_RSP                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtNtvRsp( void )
{
    MemIf_JobResultType MhaJobResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;

    MainStatus = NvM_Nvb_MainStatus;

    MhaJobResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, MhaJobResult );
    
    if( MEMIF_JOB_OK == MhaJobResult )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    }
    else if( MEMIF_JOB_FAILED == MhaJobResult )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else
    {
        /* MEMIF_JOB_PENDING and MEMIF_JOB_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }

    return MainStatus;
}

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtRprRdMainRsp                             */
/* Description   | Action function in sub status WT_RDT_RPR_RD_MAIN_RSP     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprRdMainRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    MemIf_JobResultType RprRdMainResult;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    
    RprRdMainResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfReadJob( ExecBlockId, RprRdMainResult );
    
    if( RprRdMainResult == MEMIF_JOB_FAILED )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else
    {
        NvM_Nvb_MainResult = RprRdMainResult;
        
        MainStatus = NvM_Nvb_SubActWtRprReadSubStart();
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtRprRdSubRsp                              */
/* Description   | Action function in sub status WT_RDT_RPR_RD_SUB_RSP      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprRdSubRsp( void )
{
    uint8 RprNeed;
    MemIf_JobResultType RprRdSubResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;

    ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;
    
    RprRdSubResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfReadJob( ExecBlockId, RprRdSubResult );
    if( RprRdSubResult != MEMIF_JOB_FAILED )
    {
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    RprNeed = NvM_Nvb_JudgeRepairNeed( NvM_Nvb_MainResult, RprRdSubResult, NvM_Nvb_MainDataBuffer, NvM_Nvb_SubDataBuffer, NvBlockLength );
    if( ( RprNeed == (uint8)NVM_NVB_RPR_NEED_UNNEED )
     || ( RprNeed == (uint8)NVM_NVB_RPR_NEED_NODATA ) )
    {
        MainStatus = NvM_Nvb_SubActWtWriteProcessStart( RprNeed );
    }
    else if( ( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_MAIN )
          || ( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_SUB ) )
    {
        MainStatus = NvM_Nvb_SubActWtExecRepairStart( RprNeed );
    }
    else if( RprNeed == (uint8)NVM_NVB_RPR_NEED_UNKNOWN )
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    else /* RprNeed == NVM_NVB_RPR_NEED_INVALID */
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtRprWtMainRsp                             */
/* Description   | Action function in sub status WT_RDT_RPR_WT_MAIN_RSP     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprWtMainRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    
    MainStatus = NvM_Nvb_SubActWtRprWriteEnd();
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtRprWtSubRsp                              */
/* Description   | Action function in sub status WT_RDT_RPR_WT_SUB_RSP      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprWtSubRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    
    MainStatus = NvM_Nvb_SubActWtRprWriteEnd();
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtWtMainRsp                                */
/* Description   | Action function in sub status WT_RDT_WT_MAIN_RSP         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtWtMainRsp( void )
{
    Std_ReturnType ReqWriteBlockResult;
    MemIf_JobResultType WtMainResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) SubDataBufferPtr;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;
    ExecBlockId = ExecOperationInfo->BlockId;
    
    WtMainResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, WtMainResult );
    
    if( WtMainResult == MEMIF_JOB_OK )
    {
        NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;
        SubDataBufferPtr = NvM_Nvb_SubDataBuffer;
        
        NvM_Lib_MemcpyBitInvert( SubDataBufferPtr, ExecOperationInfo->SrcPtr, (uint32)NvBlockLength );

        ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_SUB, SubDataBufferPtr );
        if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_WT_SUB_RSP;
        }
        else
        {
            NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
            NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
        }
    }
    else
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ActWtRdtWtSubRsp                                 */
/* Description   | Action function in sub status WT_RDT_WT_SUB_RSP          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtWtSubRsp( void )
{
    NvM_Nvb_MainStatusType MainStatus;
    MemIf_JobResultType WtSubResult;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    
    WtSubResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, WtSubResult );
    if( WtSubResult != MEMIF_JOB_OK )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
    }
    /* If write process to main NvBlock was success, result of write operation decide to REQ_OK. */
    /* Therefore, to check result of write proccess to sub NvBlock is not necessary. */
    MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_OK );
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActWtRprReadSubStart                          */
/* Description   | Function to start read for repair in write operation.    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtRprReadSubStart( void )
{
    Std_ReturnType ReqReadBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;

    ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;

    ReqReadBlockResult = NvM_Nvb_RequestReadBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_SUB, NVM_NVB_OFFSET_NONE, NvM_Nvb_SubDataBuffer, NvBlockLength );
    if( ReqReadBlockResult == (Std_ReturnType)E_OK )
    {
        MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
        NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_RPR_RD_SUB_RSP;
    }
    else
    {
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }

    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActWtExecRepairStart                          */
/* Description   | Function to start repair in write operation.             */
/* Preconditions | None                                                     */
/* Parameters    | RprNeed : Judge result that repair need.                 */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtExecRepairStart(
    uint8 RprNeed
){
    Std_ReturnType ReqWriteBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId;
    uint16 NvBlockLength;
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) MainDataBufferPtr;
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) SubDataBufferPtr;

    ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    NvBlockLength = NvMBlockDescriptors[ExecBlockId].NvMNvBlockLength;
    MainDataBufferPtr = NvM_Nvb_MainDataBuffer;
    SubDataBufferPtr = NvM_Nvb_SubDataBuffer;

    NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_RESTORE );

    if( RprNeed == (uint8)NVM_NVB_RPR_NEED_NEED_MAIN )
    {
        NvM_Lib_MemcpyBitInvert( MainDataBufferPtr, SubDataBufferPtr, (uint32)NvBlockLength );
        
        ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_MAIN, MainDataBufferPtr );
        if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_RPR_WT_MAIN_RSP;
        }
        else
        {
            NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
            NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
    }
    else    /* RprNeed == NVM_NVB_RPR_NEED_NEED_SUB */
    {
        NvM_Lib_MemcpyBitInvert( SubDataBufferPtr, MainDataBufferPtr, (uint32)NvBlockLength );
        
        ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecBlockId, NVM_NVB_DATA_INDEX_REDUNDANT_SUB, SubDataBufferPtr );
        if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
        {
            MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
            NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_RPR_WT_SUB_RSP;
        }
        else
        {
            NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
            NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
            MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
        }
    }

    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActWtRprWriteEnd                              */
/* Description   | Function to process when finished write of repair.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtRprWriteEnd( void )
{
    MemIf_JobResultType RprWtSubResult;
    NvM_Nvb_MainStatusType MainStatus;
    NvM_BlockIdType ExecBlockId = NvM_Nvb_ExecuteOperationInfo.BlockId;
    
    RprWtSubResult = NvM_Nvb_GetMhaProcessingResult( ExecBlockId );
    NvM_Nvb_EvtFinishedMemIfWriteJob( ExecBlockId, RprWtSubResult );
    
    if( RprWtSubResult == MEMIF_JOB_OK )
    {
        MainStatus = NvM_Nvb_SubActWtWriteProcessStart( NVM_NVB_RPR_NEED_UNNEED );
    }
    else
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }
    
    return MainStatus;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActWtWriteProcessStart                        */
/* Description   | Function to start write process.                         */
/* Preconditions | None                                                     */
/* Parameters    | RprNeed : Judge result that repair need.                 */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtWriteProcessStart( 
    uint8 RprNeed
){
    Std_ReturnType ReqWriteBlockResult;
    NvM_Nvb_MainStatusType MainStatus;
    P2VAR( NvM_Nvb_OperationInformationType, AUTOMATIC, NVM_VAR_NO_INIT ) ExecOperationInfo;

    ExecOperationInfo = &NvM_Nvb_ExecuteOperationInfo;

    ReqWriteBlockResult = NvM_Nvb_RequestWriteBlock( ExecOperationInfo->BlockId, NVM_NVB_DATA_INDEX_REDUNDANT_MAIN, ExecOperationInfo->SrcPtr );
    if( ReqWriteBlockResult == (Std_ReturnType)E_OK )
    {
        MainStatus = NVM_NVB_RUNNING_NORMAL_WAITING;
        NvM_Nvb_SubStatus = NVM_NVB_SUB_WT_RDT_WT_MAIN_RSP;
    }
    else
    {
        if( RprNeed == (uint8)NVM_NVB_RPR_NEED_NODATA )
        {
            NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY );
            NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        }
        MainStatus = NvM_Nvb_SubActOperationEnd( NVM_REQ_NOT_OK );
    }

    return MainStatus;
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


/*-------------------------------------*/
/* Common action function.             */
/*-------------------------------------*/

/****************************************************************************/
/* Function Name | NvM_Nvb_SubActOperationEnd                               */
/* Description   | Funcion to finish operation.                             */
/* Preconditions | None                                                     */
/* Parameters    | OperationResult : Result of operation.                   */
/* Return Value  | NvM_Nvb_MainStatusType : Next status                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActOperationEnd(
    NvM_RequestResultType OperationResult
){
    NvM_Nvb_MainStatusType MainStatus;

    NvM_Nvb_OperationResult = OperationResult;
    MainStatus = NVM_NVB_IDLING;
    NvM_Nvb_SubStatus = NVM_NVB_SUB_INVALID;

    return MainStatus;
}

/*-------------------------------------*/
/* Internal miscellaneous function.    */
/*-------------------------------------*/

/****************************************************************************/
/* Function Name | NvM_Nvb_ChkProductErrMemIfRead                           */
/* Description   | Check production error in MemIf read job.                */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : Check target Block ID.                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_ChkProductErrMemIfRead(
    NvM_BlockIdType BlockId
){
    MemIf_ExtProductionErrorType PrductErrBit;
    uint16 BlkNumber = NVM_NVB_MEMIF_BLOCK_NUMBER_INVALID;
    uint8 JobKind = NVM_NVB_MEMIF_JOB_INVALID;
    uint8 Lvl = NVM_NVB_MEMIF_LEVEL_INVALID;

    PrductErrBit = MemIf_ExtGetProductionError( NVM_NVB_DUMMY_DEVICE_ID, &BlkNumber, &JobKind, &Lvl );
    
    if( ( PrductErrBit & MEMIF_E_EXT_REQ_FAILED ) == (MemIf_ExtProductionErrorType)MEMIF_E_EXT_REQ_FAILED )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }
    if( ( PrductErrBit & MEMIF_E_EXT_WRONG_BLOCK_ID ) == (MemIf_ExtProductionErrorType)MEMIF_E_EXT_WRONG_BLOCK_ID )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID );
    }
    if( Lvl == (uint8)MEMIF_EXT_LEVEL_02 )
    {
        NvM_Evt_InspectionErrorEventStart( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );

        if( ( PrductErrBit & MEMIF_E_EXT_LOSS_OF_REDUNDANCY ) == (MemIf_ExtProductionErrorType)MEMIF_E_EXT_LOSS_OF_REDUNDANCY )
        {
            NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY );
        }
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_ChkProductErrMemIfWrite                          */
/* Description   | Check production error in MemIf write job.               */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : Check target Block ID.                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_ChkProductErrMemIfWrite(
    NvM_BlockIdType BlockId
){
    MemIf_ExtProductionErrorType PrductErrBit;
    uint16 BlkNumber = NVM_NVB_MEMIF_BLOCK_NUMBER_INVALID;
    uint8 JobKind = NVM_NVB_MEMIF_JOB_INVALID;
    uint8 Lvl = NVM_NVB_MEMIF_LEVEL_INVALID;

    PrductErrBit = MemIf_ExtGetProductionError( NVM_NVB_DUMMY_DEVICE_ID, &BlkNumber, &JobKind, &Lvl );
    
    if( ( PrductErrBit & MEMIF_E_EXT_REQ_FAILED ) == (MemIf_ExtProductionErrorType)MEMIF_E_EXT_REQ_FAILED )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }
    if( ( PrductErrBit & MEMIF_E_EXT_VERIFY_FAILED ) == (MemIf_ExtProductionErrorType)MEMIF_E_EXT_VERIFY_FAILED )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_VERIFY_FAILED );
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_EvtFinishedMemIfReadJob                          */
/* Description   | Event when finished MemIf read job.                      */
/* Preconditions | None                                                     */
/* Parameters    | BlockId        : Executed Block ID.                      */
/*               | MemIfJobResult : Result of read job.                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_EvtFinishedMemIfReadJob(
    NvM_BlockIdType BlockId,
    MemIf_JobResultType MemIfJobResult
){
    NvM_Nvb_ChkProductErrMemIfRead( BlockId );
    
    if( MemIfJobResult == (MemIf_JobResultType)MEMIF_JOB_FAILED )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }
    else if( MemIfJobResult == (MemIf_JobResultType)MEMIF_BLOCK_INCONSISTENT )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_INTEGRITY_FAILED );
    }
    else
    {
        /* Do Nothing */
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Nvb_EvtFinishedMemIfWriteJob                         */
/* Description   | Event when finished MemIf write job.                     */
/* Preconditions | None                                                     */
/* Parameters    | BlockId        : Executed Block ID.                      */
/*               | MemIfJobResult : Result of write job.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_EvtFinishedMemIfWriteJob(
    NvM_BlockIdType BlockId,
    MemIf_JobResultType MemIfJobResult
){
    NvM_Nvb_ChkProductErrMemIfWrite( BlockId );
    
    if( MemIfJobResult == (MemIf_JobResultType)MEMIF_JOB_FAILED )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_HARDWARE );
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
    }
    
    return;
}

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Nvb_JudgeRepairNeed                                  */
/* Description   | Function to Judge repair need.                           */
/* Preconditions | None                                                     */
/* Parameters    | MainResult        : Result of read main data.            */
/*               | SubResult         : Result of read sub data.             */
/*               | DataBufferMainPtr : Read main data.                      */
/*               | DataBufferSubPtr  : Read sub data.                       */
/*               | DataLength        : Data length.                         */
/* Return Value  | uint8 : Repair need.                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Nvb_JudgeRepairNeed(
    MemIf_JobResultType                  MainResult,
    MemIf_JobResultType                  SubResult,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferMainPtr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferSubPtr,
    uint16                               DataLength
){
    uint8 Index;
    uint8 RprNeed;
    P2CONST( AB_83_ConstV NvM_Nvb_MemIfRsltToRprNeedTblType, AUTOMATIC, NVM_CONST ) RprNeedTbl;
    sint32 CmpResult;
    
    RprNeed = NVM_NVB_RPR_NEED_INVALID;
    for( Index = 0U; Index < (uint8)NVM_NVB_MEMIF_RESULT_PAIR_NUM; Index++ )
    {
        RprNeedTbl = &NvM_Nvb_MemIfRsltToRprNeedTbl[Index];
        if( ( RprNeedTbl->MemIfMainResult == MainResult )
         && ( RprNeedTbl->MemIfSubResult == SubResult ) )
        {
            RprNeed = RprNeedTbl->RepairNeed;
            break;
        }
    }
    
    if( RprNeed == (uint8)NVM_NVB_RPR_NEED_UNNEED )
    {
        CmpResult = NvM_Lib_MemcmpBitInvert( DataBufferMainPtr, DataBufferSubPtr, (uint32)DataLength );
        if( CmpResult != (sint32)NVM_LIB_DATA1_EQUAL_DATA2 )
        {
            RprNeed = NVM_NVB_RPR_NEED_NEED_SUB;
        }
    }
    
    return RprNeed;
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/14                                              */
/*  1-2-0          :2019/11/01                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
