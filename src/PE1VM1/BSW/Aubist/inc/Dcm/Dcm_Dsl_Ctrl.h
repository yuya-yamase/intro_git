/* Dcm_Dsl_Ctrl_h(v5-9-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_Ctrl/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_CTRL_H
#define DCM_DSL_CTRL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Main_Common.h>
#include "../../Dcm/Dsl/cfg/Dcm_Dsl_Main_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_SET_POSITIVE_RESPONSE  ((uint8)0x00U)    /* Acknowledgement designation       */
#define DCM_DSL_SET_NEGATIVE_RESPONSE  ((uint8)0x01U)    /* Negative acknowledge designation  */
#define DCM_DSL_SET_NO_RESPONSE_POS    ((uint8)0x02U)    /* Positive non-response designation */
#define DCM_DSL_SET_NO_RESPONSE_NEG    ((uint8)0x03U)    /* No answer designation             */

#define DCM_DSL_ADDINFO_PHYS           ((uint8)0x00U)
#define DCM_DSL_ADDINFO_FUNC           ((uint8)0x01U)

#define DCM_DSL_PERIODICTX_COMPLETE    ((uint8)0x00U)    /* Transmission comlete       */
#define DCM_DSL_PERIODICTX_ERROR       ((uint8)0x01U)    /* Transmission failure       */
#define DCM_DSL_PERIODICTX_SENDING     ((uint8)0x02U)    /* There is a job being sent. */

#define DCM_DSL_ALL_TARGETS             ((uint16)0xFFFFU) /* Rrequire processing for all connection */

#define DCM_AUTHENTICATION_INTERNAL_USE  (STD_OFF)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 Dcm_Dsl_ResponseSettingType;      /* Response classification  */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Init
( void );

/* Because it is a function used only by SID10 */
#if( DCM_SUPPORT_SID10 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_SwitchModeSesCtrl
(
    const uint8 u1Mode
);
#endif /* DCM_SUPPORT_SID10 == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_TransmitCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_ReceiveCbk
(
    const uint8 u1EventId
);
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_UpdatePageCbk
(
    const uint8 u1EventId
);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/* Because it is a function used only by SID28 */
#if( DCM_SUPPORT_SID28 == STD_ON )
FUNC( uint16, DCM_CODE ) Dcm_Dsl_GetPduMapIndex
( void );
#endif /* DCM_SUPPORT_SID28 == STD_ON */

FUNC( boolean, DCM_CODE ) Dcm_Dsl_IsResponsePendingOccured
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_P2TOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_P2MinTOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_P4TOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_S3TOCbk
(
    const uint8 u1TimerId
);
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_PagedBufferTOCbk
(
    const uint8 u1TimerId
);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_RoeRetryTOCbk
(
    const uint8 u1TimerId
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

#if( DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_ResetToDefaultSessionCbk
(
    const uint8 u1EventId
);
#endif /* DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_SendForcePendingResponse
(
    const uint8 u1SID
);

FUNC( void, DCM_CODE ) Dcm_Dsl_TransmitFunctionality
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( Dcm_StatusType, DCM_CODE ) DslInternal_ResponseOnOneEvent
(
    const Dcm_MsgType     ptMsg,
    const Dcm_MsgLenType  u4MsgLen,
    const uint16          u2ConnectionId
);

FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_RoeSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

FUNC_P2VAR( uint8, DCM_APPL_DATA, DCM_CODE ) Dcm_Dsl_GetRoeIntermediateRespBuf
(
    const uint16                                      u2ConnectionId,
    P2VAR( Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA ) ptResMaxDataLen
);

#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_WriteNRCData
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_GetSleepPermission
( void );

FUNC( boolean, DCM_CODE ) Dcm_Dsl_GetBusSleepPermission
( void );

FUNC( void, DCM_CODE ) DslInternal_SetSecurityLevel
(
    Dcm_SecLevelType SecurityLevel
);

FUNC( void, DCM_CODE ) DslInternal_SetSesCtrlType
(
    Dcm_SesCtrlType SesCtrlType,
    const boolean bDelayUpdate
);

#if( DCM_AUTHENTICATION_USE == STD_ON )
#if( DCM_AUTHENTICATION_INTERNAL_USE == STD_ON )
FUNC( uint8, DCM_CODE ) Dcm_Dsl_GetAuthState
(
    const uint16 u2ConnectionId
);
#endif /* DCM_AUTHENTICATION_INTERNAL_USE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_SetAuthState
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#if( DCM_NVM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_SetAuthenticate
(
    const uint16 u2ConnectionId
);
#endif /* DCM_NVM_AUTHENTICATION_USE == STD_ON */

#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_AuthTOCbk
(
    const uint8 u1TimerId
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_DataConfFunctionalityCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_SetDefSesCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_CancelReceiveCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_CancelTxCancelServiceCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_RxFailSafeTOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_TxFailSafeTOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_TxRetryCbk
(
    const uint8 u1EventId
);

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxIfTOCbk
(
    const uint8 u1TimerId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_PeriodicTxRetryCbk
(
    const uint8 u1EventId
);

FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_PeriodicSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_PeriodicSendStart
(
    const uint16 u2ConnectionId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_GetPeriodicSendResult
(
    const uint16 u2ConnectionId
);

FUNC_P2VAR( uint8, DCM_APPL_DATA, DCM_CODE ) Dcm_Dsl_GetPeriodicTxBuf
(
    const uint16                                      u2ConnectionId,
    P2VAR( Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA ) ptResMaxDataLen
);

FUNC( Dcm_MsgLenType, DCM_CODE ) Dcm_Dsl_GetSizeOfPeriodicBuffer
(
    const uint16 u2ConnectionId
);

#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_IdleRefresh
( void );

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_SetupProgConditions
(
    P2CONST( Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA ) ptProgConditions
);

FUNC( void, DCM_CODE ) Dcm_Dsl_RespReqAfterEcuResetCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsl_ComMActiveDiagnosticCbk
(
    const uint8 u1EventId
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */


FUNC( void, DCM_CODE ) Dcm_Dsl_SetComActive
(
    const uint16 u2ConnectionId,
    const boolean bActive
);

#if( DCM_ULDL_SERVICE_USE == STD_ON )
FUNC( Dcm_MsgLenType, DCM_CODE ) Dcm_Dsl_GetRxBufSize
(
    const PduIdType u2RxPduId
);

#endif /* DCM_ULDL_SERVICE_USE == STD_ON */

FUNC( uint8, DCM_CODE ) Dcm_Dsl_GetActiveProtocolGroup
(
    const uint16 u2ConnectionId
);

#if ( DCM_SUPPORT_SID10 == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_GetActiveProtocol
(
    P2VAR( Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA ) ptActiveProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptTesterSourceAddress
);
#endif /* DCM_SUPPORT_SID10 == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSL_CTRL_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
