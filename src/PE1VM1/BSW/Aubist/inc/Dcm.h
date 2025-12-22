/* Dcm_h(v5-6-0)                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_H
#define DCM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <Rte_Dcm_Type.h>
#include <Dcm/Dcm_Cfg.h>
#include <Dcm/Dcm_FuncSwitch.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_INITMODE_INIT                   (0x00U)      /* Init(Boot) */
#define DCM_INITMODE_WAKEUP                 (0x01U)      /* WakeUp     */

/* Dcm_StatusType */
#define DCM_E_OK                            (0x00U)     /* This value is representing a successful operation. */
#define DCM_E_ROE_NOT_ACCEPTED              (0x06U)     /* ResponseOnOneEvent request is not accepted by DCM. */
#define DCM_E_PERIODICID_NOT_ACCEPTED       (0x07U)     /* Periodic transmission request is not accepted by DCM. */

/* Dcm_CommunicationModeType */
#define DCM_ENABLE_RX_TX_NORM               (0x00U)
#define DCM_ENABLE_RX_DISABLE_TX_NORM       (0x01U)
#define DCM_DISABLE_RX_ENABLE_TX_NORM       (0x02U)
#define DCM_DISABLE_RX_TX_NORMAL            (0x03U)
#define DCM_ENABLE_RX_TX_NM                 (0x04U)
#define DCM_ENABLE_RX_DISABLE_TX_NM         (0x05U)
#define DCM_DISABLE_RX_ENABLE_TX_NM         (0x06U)
#define DCM_DISABLE_RX_TX_NM                (0x07U)
#define DCM_ENABLE_RX_TX_NORM_NM            (0x08U)
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM    (0x09U)
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM    (0x0AU)
#define DCM_DISABLE_RX_TX_NORM_NM           (0x0BU)

/* Dcm_ReturnReadMemoryType */
#define DCM_READ_OK                         ((uint8)0x00U)
#define DCM_READ_PENDING                    ((uint8)0x01U)
#define DCM_READ_FAILED                     ((uint8)0x02U)
#define DCM_READ_FORCE_RCRRP                ((uint8)0x03U)

/* Dcm_EcuStartModeType */
#define DCM_COLD_START                      ((uint8)0x00U)
#define DCM_WARM_START                      ((uint8)0x01U)

/* Dcm_ExtendedOpStatusType */
#define DCM_POS_RESPONSE_SENT               ((uint8)0x04U)   /* Indicates that a positive response has been sent successfully */
#define DCM_POS_RESPONSE_FAILED             ((uint8)0x05U)   /* Indicates that a positive response has not been sent successfully */
#define DCM_NEG_RESPONSE_SENT               ((uint8)0x06U)   /* Indicates that a negative response has been sent successfully */
#define DCM_NEG_RESPONSE_FAILED             ((uint8)0x07U)   /* Indicates that a negative response has not been sent successfully */


/* Std_ReturnType */
#define E_PROTOCOL_NOT_ALLOWED              (0x05U)
#define E_REQUEST_NOT_ACCEPTED              (0x08U)

/* Dcm_OpStatusType */
#define DCM_E_PENDING                       (0x0AU)     /* Request is not yet finished. Further call required to finish. */
#define DCM_E_COMPARE_KEY_FAILED            (0x0BU)     /* Key did not match */
#define DCM_E_FORCE_RCRRP                   (0x0CU)     /* Application request the transmission of a response Response Pending */
#define DCM_E_UPDATE_PAGE                   (0x0DU)     /* Application request update of the paged-buffer */
#define DCM_E_SEQERROR                      (0x0EU)     /* Incorrect processing order */

/* DcmVersionInfo */
#define DCM_VENDOR_ID                       ((uint16)0x0053U)   /* Vendor ID            */
#define DCM_MODULE_ID                       ((uint16)0x0035U)   /* Dcm MoludeID         */
#define DCM_AR_RELEASE_MAJOR_VERSION        ((uint8)(0x04u))
#define DCM_AR_RELEASE_MINOR_VERSION        ((uint8)(0x05u))
#define DCM_AR_RELEASE_REVISION_VERSION     ((uint8)(0x00u))

/* Authentication status */
#define DCM_DEAUTHENTICATED                 ((uint8)0x00U)
#define DCM_AUTHENTICATED                   ((uint8)0x01U)

/* DcmResponseOnEvent status */
#define DCM_EVENT_STARTED                   ((uint8)0x00U)
#define DCM_EVENT_STOPPED                   ((uint8)0x01U)
#define DCM_EVENT_CLEARED                   ((uint8)0x02U)

/* Dcm_ReturnWriteMemoryType */
#define DCM_WRITE_OK                        ((Dcm_ReturnWriteMemoryType)0x00U)
#define DCM_WRITE_PENDING                   ((Dcm_ReturnWriteMemoryType)0x01U)
#define DCM_WRITE_FAILED                    ((Dcm_ReturnWriteMemoryType)0x02U)
#define DCM_WRITE_FORCE_RCRRP               ((Dcm_ReturnWriteMemoryType)0x03U)

/* Transfer status */
#define DCM_TFR_NONE                        ((uint8)0x00U)
#define DCM_TFR_DL_START                    ((uint8)0x11U)
#define DCM_TFR_DL_PROCEED                  ((uint8)0x22U)
#define DCM_TFR_DL_FIN                      ((uint8)0x44U)
#define DCM_TFR_UL_START                    ((uint8)0x12U)
#define DCM_TFR_UL_PROCEED                  ((uint8)0x24U)
#define DCM_TFR_UL_FIN                      ((uint8)0x48U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8                   Dcm_StatusType;
typedef uint8                   Dcm_CommunicationModeType;
typedef uint8                   Dcm_ReturnReadMemoryType;
typedef uint8                   Dcm_EcuStartModeType;
typedef uint8                   Dcm_MsgItemType;
typedef Dcm_MsgItemType *       Dcm_MsgType;
typedef uint32                  Dcm_MsgLenType;
typedef uint8                   Dcm_IdContextType;
typedef uint8                   Dcm_ExtendedOpStatusType;
typedef uint8                   Dcm_ReturnWriteMemoryType;

typedef uint32                  AB_83_DcmPduLengthType;

typedef struct
{
    uint8 InitMode;                           /* ConfigParameter */
} Dcm_ConfigType;

typedef struct
{
    uint16  ConnectionId;
    uint16  TesterAddress;
    uint8   Sid;
    uint8   SubFncId;
    boolean ResponseRequired;
    boolean ApplUpdated;
    boolean ReprogramingRequest;
} Dcm_ProgConditionsType;

typedef struct
{
    uint8 reqType;                            /* bit type */
    uint8 suppressPosResponse;                /* bit type */
} Dcm_MsgAddInfoType;

typedef struct
{
    Dcm_MsgType         resData;
    Dcm_MsgLenType      resDataLen;
    Dcm_MsgType         reqData;
    Dcm_MsgLenType      reqDataLen;
    Dcm_MsgAddInfoType  msgAddInfo;
    Dcm_MsgLenType      resMaxDataLen;
    Dcm_IdContextType   idContext;
    PduIdType           dcmRxPduId;
} Dcm_MsgContextType;

/* AB_83_DcmPduInfoType  */
typedef struct
{
    P2VAR( uint8, TYPEDEF, DCM_APPL_DATA ) SduDataPtr;     /* uint8-pointer to the SDU of the PDU */
    AB_83_DcmPduLengthType                 SduLength;      /* length of the SDU in bytes */
} AB_83_DcmPduInfoType;

/* AB_83_DcmRetryInfoType  */
typedef struct {
    TpDataStateType           TpDataState;    /* The enum type to be used to store the state of Tp buffer */
    AB_83_DcmPduLengthType    TxTpDataCnt;    /* length of the SDU in bytes */
} AB_83_DcmRetryInfoType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Init
(
    P2CONST( Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST ) ConfigPtr
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetVin
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);

#define DCM_STOP_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if( DCM_VERSION_INFO_API == STD_ON )
FUNC( void, DCM_CODE ) Dcm_GetVersionInfo
(
    P2VAR( Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA ) versionInfo
);
#endif /* DCM_VERSION_INFO_API == STD_ON */

FUNC( boolean, DCM_CODE ) Dcm_GetSleepPermission
( void );

FUNC( boolean, DCM_CODE ) Dcm_GetBusSleepPermission
(
    const boolean bRecptionPeriodEnable
);

FUNC( void, DCM_CODE ) Dcm_PreWriteAll
( void );

/*------*/
/* DSL  */
/*------*/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetSecurityLevel           /* MISRA DEVIATION */
(
    P2VAR( Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA ) SecLevel
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetSesCtrlType             /* MISRA DEVIATION */
(
    P2VAR( Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA ) SesCtrlType
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_ResetToDefaultSession      /* MISRA DEVIATION */
( void );

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetActiveProtocol
(
    P2VAR( Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA ) ActiveProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ConnectionId,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) TesterSourceAddress
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetActiveDiagnostic        /* MISRA DEVIATION */
(
    boolean active
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRxPduID
(
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptRxPduId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetActiveClient
(
    const uint16 u2ConnectionId
);

/* Callback notifications */
FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_StartOfReception
(
    PduIdType id,
    P2CONST( PduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    PduLengthType TpSduLength,
    P2VAR( PduLengthType, AUTOMATIC, DCM_APPL_DATA ) bufferSizePtr
);

FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_CopyRxData
(
    PduIdType id,
    P2CONST( PduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    P2VAR( PduLengthType, AUTOMATIC, DCM_APPL_DATA ) bufferSizePtr
);

FUNC( void, DCM_CODE ) Dcm_TpRxIndication
(
    PduIdType id,
    Std_ReturnType result
);

FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_CopyTxData
(
    PduIdType id,
    P2CONST( PduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    P2CONST( RetryInfoType, AUTOMATIC, DCM_APPL_DATA ) retry,
    P2VAR( PduLengthType, AUTOMATIC, DCM_APPL_DATA ) availableDataPtr
);

FUNC( void, DCM_CODE ) Dcm_TpTxConfirmation
(
    PduIdType id,
    Std_ReturnType result
);

FUNC( void, DCM_CODE ) Dcm_TxConfirmation
(
    PduIdType TxPduId,
    Std_ReturnType result
);

FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_StartOfReception32
(
    PduIdType id,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    AB_83_DcmPduLengthType TpSduLength,
    P2VAR( AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA ) bufferSizePtr
);

FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_CopyRxData32
(
    PduIdType id,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    P2VAR( AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA ) bufferSizePtr
);

FUNC( BufReq_ReturnType, DCM_CODE ) Dcm_CopyTxData32
(
    PduIdType id,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) info,
    P2CONST( AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA ) retry,
    P2VAR( AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA ) availableDataPtr
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetNoComMode
(
    const uint8 u1NetworkId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetSilentComMode
(
    const uint8 u1NetworkId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetFullComMode
(
    const uint8 u1NetworkId
);

/*------*/
/* DSD  */
/*------*/
FUNC( void, DCM_CODE ) Dcm_ExternalSetNegResponse
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext,
    Dcm_NegativeResponseCodeType  ErrorCode
);

FUNC( void, DCM_CODE ) Dcm_ExternalProcessingDone
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);

FUNC(void, DCM_CODE) Dcm_SendNegativeNoResponse
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);

/*------*/
/* DSP  */
/*------*/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_TriggerOnEvent
(
    uint8 RoeEventId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetActiveResponse
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA ) ptActive
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetActiveResponse
(
    Dcm_ActiveStateType u1TargetService,
    boolean             bActive
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetTransferStatus
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferStatus
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_InitTransferStatus
( void );

FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetRoeEventStatus
(
    uint8 u1RoeEventId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMode,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptSetupSubFunc
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
