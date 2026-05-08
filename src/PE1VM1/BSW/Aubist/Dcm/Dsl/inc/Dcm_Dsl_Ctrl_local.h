/* Dcm_Dsl_Ctrl_local_h(v5-10-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name | Dcm/Dsl_Ctrl_local/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_CTRL_LOCAL_H
#define DCM_DSL_CTRL_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Main_Common.h>
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_COMTYPE_TRANSMIT        ((uint8)0x00U)
#define DCM_DSL_COMTYPE_RECEIVE         ((uint8)0x01U)

#define DCM_DSL_SESCHG_KIND_NONE        ((uint8)0x00U)
#define DCM_DSL_SESCHG_KIND_DM_OFF      ((uint8)0x01U)
#define DCM_DSL_SESCHG_KIND_DM_ON       ((uint8)0x02U)

#define DCM_DSL_SESCHG_KIND_EXTERNAL    ((uint8)0x01U)
#define DCM_DSL_SESCHG_KIND_INTERNAL    ((uint8)0x02U)

#define DCM_DSL_ST_IDLE                 ((uint8)0x00U)
#define DCM_DSL_ST_RECEIVING            ((uint8)0x01U)
#define DCM_DSL_ST_WT_SVCOMP            ((uint8)0x02U)
#define DCM_DSL_ST_SENDING              ((uint8)0x03U)

#define DCM_DSL_DEFAULTSESSION          ((uint8)0x00U)
#define DCM_DSL_CURRENTSESSION          ((uint8)0x01U)

#define DCM_DSL_INVALID_U2_DATA         ((uint16)0xFFFFU)

#define DCM_DSL_PRIORITY_LOW            (uint8)0x00U       /* Request id has high priority */
#define DCM_DSL_PRIORITY_EQUAL          (uint8)0x01U       /* Request id has Same priority */
#define DCM_DSL_PRIORITY_HIGH           (uint8)0x02U       /* Request id has low priority */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Received data information structure for each PduID */
typedef struct {
    P2VAR( AB_83_DcmPduInfoType, TYPEDEF, DCM_APPL_DATA )   ptRxPduInfo;        /* Receive Buffer and Receive Message Length */
    P2VAR( AB_83_DcmPduLengthType, TYPEDEF, DCM_APPL_DATA ) ptRxSduLengthRmd;   /* Remain Receive Buffer Length              */
} Dcm_Dsl_RxResInfoType;

typedef struct
{
    P2VAR( uint8, TYPEDEF, DCM_APPL_DATA ) SduStartAddr;   /* SDU start address */
    AB_83_DcmPduLengthType                 SduPos;         /* SDU operation position */
    AB_83_DcmPduLengthType                 SduLength;      /* length of the SDU in bytes */
} Dcm_TxPduInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartOfReception
(
    const uint16 u2PduMapIndex,
    const boolean bKeepAliveMsg
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RedoOfReception
(
    const uint16 u2PduMapIndex,
    const uint8 u1PrevReqKind
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyPseudoKALasNoKAL
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Accept
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ProcKeepAliveReq
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_BusyTransmit
(
    const uint16                       u2PduMapIndex,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RespReqAfterEcuReset
(
    const uint16 u2PduMapIndex,
    const uint8  u1SID,
    const uint8  u1SubFncId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeemedReceiveProc
(
    const uint16 u2PduMapIndex,
    const uint8  u1Sid,
    const uint8  u1SubFncId
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeemedReceiveEvent
(
    const uint16          u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxBuf
);
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ActiveDeemedReceiveProc
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RxErrNotification
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Confirmation
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpConfirmation
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpErrHandling
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpErrNotification
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyServiceStart
(
    const boolean bP2kind,
    const uint8 u1SesInfo
);

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyServiceToResponseStart
( void );
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxStart
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyRcrrpTxStart
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxErrNotification
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyResult
(
    const uint16 u2PduMapIndex,
    const boolean bResult
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxEnd
( void );

FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_ReqTxErrHandling
(
    const uint16 u2PduMapIndex,
    const boolean bDelayUpdate
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxCancel
(
    const uint16 u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CancelService
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CancelConfirmation
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsFirstCommunication
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ChgInteractiveClient
( void );

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsDirectKeepAliveMsg
(
    const uint16 u2RxPduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_CONST) ptRxInfo
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsInteractiveClient
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsRecvInteractiveClient
(
    const uint16 u2RxPduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsServiceToRespondTo
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsBusyServiceToRespondTo
(
    const uint16 u2RxPduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveDiag
( void );

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsBusyInteractiveClient
( void );

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveClient
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsResourceInUse
(
    const uint16 u2PduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetResUseId
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveSession
( void );

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_DataConfFunctional
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus,
    const boolean bIsSendForcedPending
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDefSes
(
    const uint16 u2PduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduMapIndex
( void );


FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetPduMapIndex
(
    const uint16 u2PduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxPduMapIndex
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetRxPduMapIndex
(
    const uint16 u2RxPduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduMapIndex4Tx
( void );

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxBuf
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxBuf
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxResource
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxInfo
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetCurRxResource
(
    const uint16 u2PduMapIndex,
    P2VAR( Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxResInfo
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetCurKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR( Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxResInfo
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
);

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetRoeTxBuf
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetDslState
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDslState
(
    const uint16 u2PduMapIndex,
    const uint8  u1State
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed
( void );


FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetResPendOccur
(
    const boolean bDetectRcrrp
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Abort
( void );


FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetSesCtrlType
(
    Dcm_SesCtrlType SesCtrlType,
    const boolean bDelayUpdate
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetSesConf
(
    const boolean bUpdateEnable
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReqSesCtrlChgNotification
( void );

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_ReqUpdatePage
( void );

FUNC( AB_83_DcmPduLengthType, DCM_CODE ) Dcm_Dsl_Ctrl_GetResponseDataLength
( void );
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_BusyRespReq
(
    const uint16                       u2PduMapIndex,
    const uint8                        u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsSuppressNegMsg
(
    const uint16                       u2PduMapIndex,
    const uint8                        u1SID,
    const Dcm_NegativeResponseCodeType u1Nrc
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsAcceptedFinalResp
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetLatestConfData
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsSesCtrlPermission
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx
(
    const uint16 u2RxPduMapIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRowIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptProtocolRxIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx
(
    const uint16 u2RxPduMapIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRowIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptConnectionIndex
);

FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetComMChannel
(
    const uint16 u2RxPduMapIndex
);

FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetConnectionPriority
(
    const uint16 u2RxPduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetConnectionGroup
(
    const uint16 u2RxPduMapIndex
);

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx
(
    const uint16 u2PduMapIndex
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsNoResPduID
(
    const uint16 u2PduMapIndex
);

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetDataIndParam
(
    const uint16 u2PduMapIndex,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )     ptReqType,
    P2VAR( PduIdType, AUTOMATIC, DCM_APPL_DATA ) ptPduId
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId
(
    const uint16 u2ConnectionId
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsFunctionalAddressingMsg
(
    const uint16 u2PduMapIndex
);

FUNC( AB_83_DcmPduLengthType, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxBufSize
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Init
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Clear
(
    const uint16 u2PduMapIndex
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Refresh
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ComSrv_Init
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopTxTimers
( void );

#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_isClientAuthenticated
(
    const uint16 u2ConnectionId
);

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_isAuthTimerRunning
(
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartAuthTimer
(
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthTimer
(
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthAllTimers
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeauthenticate
(
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeauthenticateAll
( void );

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetAuthConf
(
    const uint16 u2ConnectionId,
    const boolean bUpdateEnable
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReqAuthStateChangeNotification
(
    const uint16 u2ConnectionId
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_IfConfirmation
(
    const uint16         u2IfPduMapIndex,
    const Std_ReturnType u1Result
);

FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_IfTimeout
(void);

FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetNumOfConcurrentTxIf
( void );

#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveResponse
( void );

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ProvideDiagComData
(
    const uint16 u2PduMapIndex,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptInfo,
    const uint8 u1ResponseKind
);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSL_CTRL_LOCAL_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2022-08-30                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-08-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
