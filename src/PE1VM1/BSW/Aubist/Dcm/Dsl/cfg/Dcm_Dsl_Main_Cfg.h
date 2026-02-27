/* Dcm_Dsl_Main_Cfg_h(v5-9-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_Main_cfg/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_MAIN_CFG_H
#define DCM_DSL_MAIN_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Dsl_Main_Callout.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_ROW_NUM                     ((uint16)0x01U)  /* Number of Dcm_Dsl_RowType */
#define DCM_DSL_R0_CONNECTION_NUM           ((uint16)0x05U)  /* Number of Dcm_Dsl_ConnectionType */
#define DCM_DSL_R0_SESSION_NUM              ((uint8)0x00U)   /* Number of sessions to activate the S3Server */
#define DCM_DSL_R0_C1_PROTOCOLRX_NUM        ((uint8)0x02U)   /* Number of Dcm_Dsl_ProtocolRxType */
#define DCM_DSL_R0_C2_PROTOCOLRX_NUM        ((uint8)0x01U)   /* Number of Dcm_Dsl_ProtocolRxType */
#define DCM_DSL_R0_C3_PROTOCOLRX_NUM        ((uint8)0x02U)   /* Number of Dcm_Dsl_ProtocolRxType */
#define DCM_DSL_R0_C4_PROTOCOLRX_NUM        ((uint8)0x01U)   /* Number of Dcm_Dsl_ProtocolRxType */
#define DCM_DSL_PDUID_NUM                   ((uint16)0x06U)  /* Number of Dcm_Dsl_PduIdMapTableType */
#define DCM_DSL_CLIENT_NUM                  ((uint16)0x04U)  /* Number of Client */
#define DCM_DSL_IFPDUID_NUM                 ((uint16)0x00U)  /* Number of Periodic Connection */
#define DCM_DSL_ROEID_NUM                   ((uint16)0x00U)  /* Number of ROE Connection */
#define DCM_DSL_INDSESCHG_NUM               ((uint8)3U)      /* Number of notification destinations at session change */
#define DCM_DSL_INDSECLEVELCHG_NUM          ((uint8)0U)      /* Number of notification destinations at security Level change */
#define DCM_DSL_INDAUTHSTSCHG_NUM           ((uint8)0U)      /* Number of notification destinations at authentication state change */
#define DCM_DSL_FUNCADDR_NUM                ((uint16)2U)     /* Number of DCM_DSL_ADDINFO_FUNC */
#define DCM_DSL_FUNCADDRINFO_NUM            ((uint16)2U)     /* Number of DCM_DSL_ADDINFO_FUNC Management Information */

#define DCM_DSL_BUF_SIZE_0                  ((uint32)4095UL) /* Transmit buffer size */
#define DCM_DSL_BUF_SIZE_1                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_2                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_3                  ((uint32)4095UL) /* Transmit buffer size */
#define DCM_DSL_BUF_SIZE_4                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_5                  ((uint32)4095UL) /* Transmit buffer size */
#define DCM_DSL_BUF_SIZE_6                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_7                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_8                  ((uint32)4095UL) /* Transmit buffer size */
#define DCM_DSL_BUF_SIZE_9                  ((uint32)4095UL) /* Receive buffer size */
#define DCM_DSL_BUF_SIZE_10                 ((uint32)4095UL) 
#define DCM_DSL_TXBUF_MAXSIZE               ((uint32)4095UL) /* Transmit buffer max size */
#define DCM_DSL_TXIFBUF_MAXSIZE             ((uint32)1UL)    /* Periodic buffer size */
#define DCM_DSL_ROEBUF_SIZE                 ((uint32)4095UL) /* ROE buffer size */
#define DCM_TXERR_SESCHG_DEFAULT            ((uint8)0x00U)   /* Default Session Transition */
#define DCM_TXERR_DISCON                    ((uint8)0x01U)   /* Disconnect */
#define DCM_TXERR_END                       ((uint8)0xFFU)   /* No Default Session Transition */
#define DCM_DSL_CANCELIDQUEUE_MAX           ((uint16)5U)     /* Cancel ID queue max size */
#define DCM_DSL_OBD_PROTOCOL                ((uint8)0x00U)   /* OBD Protocol Group */
#define DCM_DSL_UDS_PROTOCOL                ((uint8)0x01U)   /* UDS Protocol Group */
#define DCM_DSL_KEEPALIVE_LEN               ((uint8)0x02U)   /* Length of Keep-Alive message */

#define DCM_DSL_ROE_ENABLE                  (STD_ON)         /* ROE enable */
#define DCM_DSL_ROE_EXTENDED_ENABLE         (STD_OFF)        /* ROE Destination extension Enable */
#define DCM_DSL_PERIODICTX_ENABLE           (STD_OFF)        /* PeriodicTx enable */
#define DCM_DSL_EXTBUF_ENABLE               (STD_OFF)        /* ExternalBuffer enable */
#define DCM_DSL_ARBT_TYPE1                  (STD_OFF)        /* Multiple client arbitration type#1 */
#define DCM_DSL_ARBT_TYPE2                  (STD_ON)         /* Multiple client arbitration type#2 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/******************/
/* Normal Config  */
/******************/


/* Dcm_Dsl_RxBufferType container */
typedef struct{
    const uint32    u4RxBufSize;
    CONSTP2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptRxBuf;
    const boolean   bUseExternalBuf;
}Dcm_Dsl_RxBufferType;

/* Dcm_Dsl_KALBufferType container */
typedef struct{
    const uint32    u4RxBufSize;
    CONSTP2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptRxBuf;
}Dcm_Dsl_KALBufferType;

/* Dcm_Dsl_ProtocolTxType container */
typedef struct{
    const uint32     u4TxBufSize;
    const PduIdType  TxConfirmationPduId;
    const PduIdType  TxPdu;
    const uint8      u1TxErrorHandling;
}Dcm_Dsl_ProtocolTxType;

/* Dcm_Dsl_ProtocolRxType container */
typedef struct{
    const uint32    u4ExtResTimeout;
    const PduIdType PduId;
    const PduIdType RxPdu;
    const uint8     u1AddrType;
    const boolean   bExtSuppressRspMsg;
}Dcm_Dsl_ProtocolRxType;

/* Dcm_Dsl_SubConnectionType container */
typedef struct{
    const uint32 u4TxBufSize;
    CONSTP2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptTxBuf;
    const uint16 TxConfirmationPduId;
    const PduIdType TxPdu;
}Dcm_Dsl_SubConnectionType;

/* Dcm_Dsl_PeriodicTransmissionType container */
typedef struct{
    const uint8 u1PeriodicConnectionNum;
    P2CONST(AB_83_ConstV Dcm_Dsl_SubConnectionType, TYPEDEF, DCM_APPL_CONST) ptPeriodicConnection;
}Dcm_Dsl_PeriodicTransmissionType;

/* Dcm_Dsl_MainConnectionType container */
typedef struct{
    const uint16 u2ConnectionId;
    const uint16 u2ConnectionGroup;
    const uint16 u2ProtocolRxTesterSourceAddr;
    const uint8  u1ProtocolComMChannel;
    const uint8  u1ConnectionPriority;
    const boolean bExtPduLength;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, TYPEDEF, DCM_APPL_CONST) ptProtocolRx;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, TYPEDEF, DCM_APPL_CONST) ptProtocolTx;
    P2CONST(AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, TYPEDEF, DCM_APPL_CONST) ptPeriodicConnectionRef;
    P2CONST(AB_83_ConstV Dcm_Dsl_SubConnectionType, TYPEDEF, DCM_APPL_CONST) ptRoeConnectionRef;
}Dcm_Dsl_MainConnectionType;

/* Dcm_Dsl_ConnectionType container */
typedef struct{
    P2CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, TYPEDEF, DCM_APPL_CONST) ptMainConnection;
    P2CONST(AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, TYPEDEF, DCM_APPL_CONST) ptPeriodicTransmission;
    P2CONST(AB_83_ConstV Dcm_Dsl_SubConnectionType, TYPEDEF, DCM_APPL_CONST) ptResponseOnEvent;
}Dcm_Dsl_ConnectionType;

/* Dcm_Dsl_RowType container */
typedef struct{
    P2CONST(AB_83_ConstV Dcm_Dsl_ConnectionType, TYPEDEF, DCM_APPL_CONST) ptConnection;
    P2CONST(AB_83_ConstV uint8, TYPEDEF, DCM_APPL_CONST) ptSessionRef;
    const uint32   u4DiagFailSafeTimeout;
    const uint16   u2S3ServerTimeout;
    const uint16   u2P2ServerAdjust;
    const uint16   u2P2StarServerAdjust;
    const uint8    u1ID;
    const uint8    u1SessionNum;
    const boolean  bCommunicationCancelUsed;
}Dcm_Dsl_RowType;

/* Dcm_Dsl_CbkDCMRequestServiceType container */
typedef struct{
    const boolean bClientChangeNotifUsed;
}Dcm_Dsl_CbkDCMRequestServiceType;

/* Dcm_Dsl_GeneralType container */
typedef struct{
    const uint32 u4FailSafeTimeout;
}Dcm_Dsl_GeneralType;

/* Dcm_Dsl_DiagRespType container */
typedef struct{
    const  boolean bP4Server;
    const  boolean bDiagRespOnSecondDeclinedRequest;
    const  uint8   u1RespMaxNumRespPend;
}Dcm_Dsl_DiagRespType;

/************************/
/* Mapping Table Config */
/************************/
/* Dcm_Dsl_PduIdMapTableType container */
typedef struct{
    const uint16 u2RowIndex;
    const uint16 u2ConnectionIndex;
    const uint16 u2ProtocolRxIndex;
    const uint16 u2ClientIndex;
    const uint16 u2IfMapIndex;
    const uint16 u2FuncAddrMapIndex;
    const PduIdType    RxPduId;
    const uint8  u1ProtocolGroup;
}Dcm_Dsl_PduIdMapTableType;

/* Dcm_Dsl_IpduIdMapTableType container */
typedef struct{
    const PduIdType  TxConfirmationPduId;
    const uint16     u2PduMapIndex;
    const uint16     u2ClientIndex;
    const uint8      u1TxIfIndex;
}Dcm_Dsl_IpduIdMapTableType;

/* Dcm_Dsl_RoeMapTableType */
typedef struct{
    const PduIdType  TxConfirmationPduId;
    const uint16     u2PduMapIndex;
}Dcm_Dsl_RoeMapTableType;


/************************/
/* Internal Config      */
/************************/
/* Dcm_Dsl_IndSesCtrlChgTableType */
typedef P2FUNC( void, DCM_CODE, Dcm_Dsl_IndSesCtrlChgTableType )
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);

/* Dcm_Dsl_IndSecLevelChgTableType */
typedef P2FUNC( void, DCM_CODE, Dcm_Dsl_IndSecLevelChgTableType )
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
);

/* Dcm_Dsl_IndAuthStateChgTableType */
typedef P2FUNC( void, DCM_CODE, Dcm_Dsl_IndAuthStateChgTableType )
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId
);

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_IndicateSesCtrlChange
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_IndicateSecLevelChange
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
);

FUNC(void, DCM_CODE) Dcm_Dsl_GetP2ServerValue
(
    const Dcm_SesCtrlType u1SesCtrlType,
    const Dcm_ProtocolType u1ProtocolType,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2Server,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2StarServerMax,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2StarServerMin
);

FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetNoComMode
(
    uint8 NetworkId
);

FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetSilentComMode
(
    uint8 NetworkId
);

FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetFullComMode
(
    uint8 NetworkId
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST(AB_83_ConstV Dcm_Dsl_PduIdMapTableType, DCM_CONFIG_DATA) Dcm_Dsl_PduIdMapTable[DCM_DSL_PDUID_NUM];
extern CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_ConnectionIdMapTable[DCM_DSL_CLIENT_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stProtocolTx[1];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stProtocolTx[1];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stProtocolTx[1];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C4_stProtocolTx[1];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stProtocolRx[DCM_DSL_R0_C1_PROTOCOLRX_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stProtocolRx[DCM_DSL_R0_C2_PROTOCOLRX_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stProtocolRx[DCM_DSL_R0_C3_PROTOCOLRX_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C4_stProtocolRx[DCM_DSL_R0_C4_PROTOCOLRX_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stMainConnection[1];
extern CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stMainConnection[1];
extern CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stMainConnection[1];
extern CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C4_stMainConnection[1];
extern CONST(AB_83_ConstV Dcm_Dsl_ConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_stConnection[DCM_DSL_R0_CONNECTION_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_SubConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C0_stResponseOnEvent[1];
extern CONST(AB_83_ConstV Dcm_Dsl_GeneralType, DCM_CONFIG_DATA) Dcm_Dsl_stGeneral[1];
extern CONST(AB_83_ConstV Dcm_Dsl_DiagRespType, DCM_CONFIG_DATA) Dcm_Dsl_stDiagResp[1]; 
extern CONST(AB_83_ConstV Dcm_Dsl_RowType, DCM_CONFIG_DATA) Dcm_Dsl_stRow[DCM_DSL_ROW_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_RxBufferType, DCM_CONFIG_DATA) Dcm_Dsl_stRxBufferTable[DCM_DSL_PDUID_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_KALBufferType, DCM_CONFIG_DATA) Dcm_Dsl_stKALBufferTable[DCM_DSL_FUNCADDR_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_CbkDCMRequestServiceType, DCM_CONFIG_DATA) Dcm_Dsl_stCbkDCMRequestService[1];
extern CONST(AB_83_ConstV Dcm_Dsl_IndSesCtrlChgTableType, DCM_CONFIG_DATA) Dcm_Dsl_IndSesCtrlChgTable[DCM_DSL_INDSESCHG_NUM];
extern CONST(AB_83_ConstV Dcm_Dsl_IndSecLevelChgTableType, DCM_CONFIG_DATA) Dcm_Dsl_IndSecLevelChgTable[1];

extern CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2RowNum;            /* DCM_DSL_ROW_NUM */
extern CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsl_u1IndSesChgNum;       /* DCM_DSL_INDSESCHG_NUM */
extern CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsl_u1IndSecLvChgNum;     /* DCM_DSL_INDSECLEVELCHG_NUM */
extern CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2ClientNum;         /* DCM_DSL_CLIENT_NUM */
extern CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2PduIdNum;          /* DCM_DSL_PDUID_NUM */
extern CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2TxRetryCountValue; /* Retransmission counter value */
extern CONST(AB_83_ConstV boolean, DCM_CONFIG_DATA) Dcm_Dsl_bSecLockOnlyDefSes;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSL_MAIN_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
