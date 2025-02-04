/* NvM_Evt.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/EVT/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_EVT_H
#define     NVM_EVT_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_E_EVT_PARAM_BLOCK_ID          ( 0x0AU )
#define NVM_E_EVT_PARAM_BLOCK_TYPE        ( 0x0BU )
#define NVM_E_EVT_PARAM_BLOCK_DATA_IDX    ( 0x0CU )
#define NVM_E_EVT_PARAM_ADDRESS           ( 0x0DU )
#define NVM_E_EVT_PARAM_DATA              ( 0x0EU )
#define NVM_E_EVT_PARAM_POINTER           ( 0x0FU )
#define NVM_E_EVT_NOT_INITIALIZED         ( 0x14U )
#define NVM_E_EVT_BLOCK_PENDING           ( 0x15U )
#define NVM_E_EVT_BLOCK_CONFIG            ( 0x18U )
#define NVM_E_EVT_BLOCK_LOCKED            ( 0x19U )

#define NVM_EVT_ERR_EVENT_HARDWARE                  ( 0x00U )
#define NVM_EVT_ERR_EVENT_INTEGRITY_FAILED          ( 0x01U )
#define NVM_EVT_ERR_EVENT_LOSS_OF_REDUNDANCY        ( 0x02U )
#define NVM_EVT_ERR_EVENT_REQ_FAILED                ( 0x03U )
#define NVM_EVT_ERR_EVENT_VERIFY_FAILED             ( 0x04U )
#define NVM_EVT_ERR_EVENT_WRONG_BLOCK_ID            ( 0x05U )

#define NVM_EVT_DETAIL_ERR_JOB_TIMEOUT                  ( 0x00U )
#define NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG            ( 0x01U )
#define NVM_EVT_DETAIL_ERR_WRT_TO_PROT_SKIP             ( 0x02U )
#define NVM_EVT_DETAIL_ERR_WRT_FRM_INVALID_RAM_SKIP     ( 0x03U )
#define NVM_EVT_DETAIL_ERR_WRT_FRM_UNCHANGE_RAM_SKIP    ( 0x04U )
#define NVM_EVT_DETAIL_ERR_READ_TO_VALID_RAM_SKIP       ( 0x05U )
#define NVM_EVT_DETAIL_ERR_CANCEL_USER_REQ              ( 0x06U )
#define NVM_EVT_DETAIL_ERR_CANCEL_WRT_ALL               ( 0x07U )
#define NVM_EVT_DETAIL_ERR_CANCEL_PREEMPT               ( 0x08U )
#define NVM_EVT_DETAIL_ERR_RESTORE                      ( 0x09U )
#define NVM_EVT_DETAIL_ERR_NODATA                       ( 0x0AU )
#define NVM_EVT_DETAIL_ERR_LOSS_OF_REDUNDANCY           ( 0x0BU )

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Evt_Init( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_ReportDevelopmentError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ServiceId,
    uint8 ErrorId
);

FUNC( void, NVM_CODE )
NvM_Evt_JobResultChange(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType JobResult
);

FUNC( void, NVM_CODE )
NvM_Evt_JobStart(
    NvM_BlockIdType BlockId,
    uint32 JobId
);

FUNC( void, NVM_CODE )
NvM_Evt_JobEnd(
    NvM_BlockIdType BlockId,
    uint32 JobId
);

FUNC( void, NVM_CODE )
NvM_Evt_SglBlkProcStart(
    NvM_BlockIdType BlockId,
    uint32 JobId
);

FUNC( void, NVM_CODE )
NvM_Evt_SglBlkProcEnd(
    NvM_BlockIdType BlockId,
    uint32 JobId
);

FUNC( void, NVM_CODE )
NvM_Evt_ReadStart(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
);

FUNC( void, NVM_CODE )
NvM_Evt_ReadEndInSuccess(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_ReadEndInFailure(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_WriteStart(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
);

FUNC( void, NVM_CODE )
NvM_Evt_WriteEndInSuccess(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_WriteEndInFailure(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_RestoreStart(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
);

FUNC( void, NVM_CODE )
NvM_Evt_RestoreEndInSuccess(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_RestoreEndInFailure(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Evt_InspectionErrorEventStart(
    uint8 ErrEvent
);

FUNC( void, NVM_CODE )
NvM_Evt_DetectionErrorEvent(
    uint8 ErrEvent
);

FUNC( void, NVM_CODE )
NvM_Evt_DetectionDetailError(
    uint8 DetailError
);

FUNC( void, NVM_CODE )
NvM_Evt_FatalFailedNotification( void );

FUNC( boolean, NVM_CODE )
NvM_Evt_IsFatalFailed( void );

FUNC( void, NVM_CODE )
NvM_Evt_SetFatalFailed( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_WriteRamBlockToNvm(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Evt_ReadRamBlockFromNvm(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_EVT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/12/12                                              */
/*  1-2-0          :2019/08/26                                              */
/*  2-0-0          :2021/06/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
