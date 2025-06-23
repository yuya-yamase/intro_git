/* Dcm_Dsl_Main_cfg_c(v5-5-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Main_Cfg/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/cfg/Dcm_Dsl_Main_Cfg.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Dsp_SID10.h>
#include <Dcm/Dcm_Dsp_SID28.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_0[DCM_DSL_BUF_SIZE_1]; /* RxBuffer */
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_1[DCM_DSL_BUF_SIZE_2]; /* RxBuffer */
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_2[DCM_DSL_BUF_SIZE_4]; /* RxBuffer */
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_3[DCM_DSL_BUF_SIZE_6]; /* RxBuffer */
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_4[DCM_DSL_BUF_SIZE_7]; /* RxBuffer */
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1RxBuf_PduID_5[DCM_DSL_BUF_SIZE_9]; /* RxBuffer */

static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1KALBuf_0[DCM_DSL_KEEPALIVE_LEN];
static  VAR(uint8, DCM_VAR_NO_INIT)   Dcm_Dsl_u1KALBuf_1[DCM_DSL_KEEPALIVE_LEN];


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

CONST(AB_83_ConstV Dcm_Dsl_RxBufferType, DCM_CONFIG_DATA) Dcm_Dsl_stRxBufferTable[DCM_DSL_PDUID_NUM] = 
{
    {
        DCM_DSL_BUF_SIZE_1,  &Dcm_Dsl_u1RxBuf_PduID_0[0], (boolean)FALSE
    },
    {
        DCM_DSL_BUF_SIZE_2,  &Dcm_Dsl_u1RxBuf_PduID_1[0], (boolean)FALSE
    },
    {
        DCM_DSL_BUF_SIZE_4,  &Dcm_Dsl_u1RxBuf_PduID_2[0], (boolean)FALSE
    },
    {
        DCM_DSL_BUF_SIZE_6,  &Dcm_Dsl_u1RxBuf_PduID_3[0], (boolean)FALSE
    },
    {
        DCM_DSL_BUF_SIZE_7,  &Dcm_Dsl_u1RxBuf_PduID_4[0], (boolean)FALSE
    },
    {
        DCM_DSL_BUF_SIZE_9,  &Dcm_Dsl_u1RxBuf_PduID_5[0], (boolean)FALSE
    }
};

/* Mapping table based on PduId */
CONST(AB_83_ConstV Dcm_Dsl_PduIdMapTableType, DCM_CONFIG_DATA) Dcm_Dsl_PduIdMapTable[DCM_DSL_PDUID_NUM]=
{
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)0U,    /* u2ConnectionIndex */
        (uint16)0U,    /* u2ProtocolRxIndex */
        (uint16)0U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)0xFFFFU,    /* u2FuncAddrMapIndex */
        (PduIdType)0x0004U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    },
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)0U,    /* u2ConnectionIndex */
        (uint16)1U,    /* u2ProtocolRxIndex */
        (uint16)0U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)0U,     /* u2FuncAddrMapIndex */
        (PduIdType)0x0005U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    },
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)1U,    /* u2ConnectionIndex */
        (uint16)0U,    /* u2ProtocolRxIndex */
        (uint16)1U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)0xFFFFU,    /* u2FuncAddrMapIndex */
        (PduIdType)0x0006U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    },
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)2U,    /* u2ConnectionIndex */
        (uint16)0U,    /* u2ProtocolRxIndex */
        (uint16)2U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)0xFFFFU,    /* u2FuncAddrMapIndex */
        (PduIdType)0x0007U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    },
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)2U,    /* u2ConnectionIndex */
        (uint16)1U,    /* u2ProtocolRxIndex */
        (uint16)2U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)1U,     /* u2FuncAddrMapIndex */
        (PduIdType)0x0008U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    },
    {
        (uint16)0U,    /* u2RowIndex */
        (uint16)3U,    /* u2ConnectionIndex */
        (uint16)0U,    /* u2ProtocolRxIndex */
        (uint16)3U,    /* u2ClientIndex */
        (uint16)0xFFFFU,    /* u2IfMapIndex */
        (uint16)0xFFFFU,    /* u2FuncAddrMapIndex */
        (PduIdType)0x0009U,     /* RxPduId */
        DCM_DSL_UDS_PROTOCOL    /* u1ProtocolGroup */
    }
};




/* ProtocolTx */
CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C0_stProtocolTx[1] =
{
    {
        DCM_DSL_BUF_SIZE_0,    /* u4TxBufSize */
        (PduIdType)0x00U,    /* TxConfirmationPduId */
        (PduIdType)0x0000U,    /* TxPdu */
        DCM_TXERR_DISCON    /* u1TxErrorHandling */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stProtocolTx[1] =
{
    {
        DCM_DSL_BUF_SIZE_3,    /* u4TxBufSize */
        (PduIdType)0x01U,    /* TxConfirmationPduId */
        (PduIdType)0x0001U,    /* TxPdu */
        DCM_TXERR_DISCON    /* u1TxErrorHandling */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stProtocolTx[1] =
{
    {
        DCM_DSL_BUF_SIZE_5,    /* u4TxBufSize */
        (PduIdType)0x02U,    /* TxConfirmationPduId */
        (PduIdType)0x0002U,    /* TxPdu */
        DCM_TXERR_DISCON    /* u1TxErrorHandling */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stProtocolTx[1] =
{
    {
        DCM_DSL_BUF_SIZE_8,    /* u4TxBufSize */
        (PduIdType)0x03U,    /* TxConfirmationPduId */
        (PduIdType)0x0003U,    /* TxPdu */
        DCM_TXERR_DISCON    /* u1TxErrorHandling */
    }
};

/* ProtocolRx */
CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C0_stProtocolRx[DCM_DSL_R0_C0_PROTOCOLRX_NUM]=
{
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x004U,     /* PduId */
        (PduIdType)0x0004U,    /* RxPdu */
        DCM_DSL_ADDINFO_PHYS,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    },
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x005U,     /* PduId */
        (PduIdType)0x0005U,    /* RxPdu */
        DCM_DSL_ADDINFO_FUNC,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stProtocolRx[DCM_DSL_R0_C1_PROTOCOLRX_NUM]=
{
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x006U,     /* PduId */
        (PduIdType)0x0006U,    /* RxPdu */
        DCM_DSL_ADDINFO_PHYS,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stProtocolRx[DCM_DSL_R0_C2_PROTOCOLRX_NUM]=
{
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x007U,     /* PduId */
        (PduIdType)0x0007U,    /* RxPdu */
        DCM_DSL_ADDINFO_PHYS,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    },
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x008U,     /* PduId */
        (PduIdType)0x0008U,    /* RxPdu */
        DCM_DSL_ADDINFO_FUNC,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_ProtocolRxType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stProtocolRx[DCM_DSL_R0_C3_PROTOCOLRX_NUM]=
{
    {
        (uint32)0UL,    /* u4ExtResTimeout */
        (PduIdType)0x009U,     /* PduId */
        (PduIdType)0x0009U,    /* RxPdu */
        DCM_DSL_ADDINFO_PHYS,    /* u1AddrType */
        (boolean)FALSE    /* bExtSuppressRspMsg */
    }
};

/* MainConnection */
CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C0_stMainConnection[1] =
{
    {
        (uint16)0x00U,   /* u2ConnectionId */
        (uint16)0x00U,   /* u2ConnectionGroup */
        (uint16)0U,    /* u2ProtocolRxTesterSourceAddr */
        (uint8)0x00U,    /* u1ProtocolComMChannel */
        (uint8)2U,    /* u1ConnectionPriority */
        (boolean)FALSE,    /* bExtPduLength */
        &Dcm_Dsl_R0_C0_stProtocolRx[0],    /* ptProtocolRx */
        &Dcm_Dsl_R0_C0_stProtocolTx[0],    /* ptProtocolTx */
        NULL_PTR,    /* ptPeriodicConnectionRef */
        NULL_PTR    /* ptRoeConnectionRef */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C1_stMainConnection[1] =
{
    {
        (uint16)0x01U,   /* u2ConnectionId */
        (uint16)0x01U,   /* u2ConnectionGroup */
        (uint16)0U,    /* u2ProtocolRxTesterSourceAddr */
        (uint8)0x00U,    /* u1ProtocolComMChannel */
        (uint8)3U,    /* u1ConnectionPriority */
        (boolean)FALSE,    /* bExtPduLength */
        &Dcm_Dsl_R0_C1_stProtocolRx[0],    /* ptProtocolRx */
        &Dcm_Dsl_R0_C1_stProtocolTx[0],    /* ptProtocolTx */
        NULL_PTR,    /* ptPeriodicConnectionRef */
        NULL_PTR    /* ptRoeConnectionRef */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C2_stMainConnection[1] =
{
    {
        (uint16)0x02U,   /* u2ConnectionId */
        (uint16)0x00U,   /* u2ConnectionGroup */
        (uint16)0U,    /* u2ProtocolRxTesterSourceAddr */
        (uint8)0x00U,    /* u1ProtocolComMChannel */
        (uint8)2U,    /* u1ConnectionPriority */
        (boolean)FALSE,    /* bExtPduLength */
        &Dcm_Dsl_R0_C2_stProtocolRx[0],    /* ptProtocolRx */
        &Dcm_Dsl_R0_C2_stProtocolTx[0],    /* ptProtocolTx */
        NULL_PTR,    /* ptPeriodicConnectionRef */
        NULL_PTR    /* ptRoeConnectionRef */
    }
};
CONST(AB_83_ConstV Dcm_Dsl_MainConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_C3_stMainConnection[1] =
{
    {
        (uint16)0x03U,   /* u2ConnectionId */
        (uint16)0x01U,   /* u2ConnectionGroup */
        (uint16)0U,    /* u2ProtocolRxTesterSourceAddr */
        (uint8)0x00U,    /* u1ProtocolComMChannel */
        (uint8)3U,    /* u1ConnectionPriority */
        (boolean)FALSE,    /* bExtPduLength */
        &Dcm_Dsl_R0_C3_stProtocolRx[0],    /* ptProtocolRx */
        &Dcm_Dsl_R0_C3_stProtocolTx[0],    /* ptProtocolTx */
        NULL_PTR,    /* ptPeriodicConnectionRef */
        NULL_PTR    /* ptRoeConnectionRef */
    }
};




/* Connection */
CONST(AB_83_ConstV Dcm_Dsl_ConnectionType, DCM_CONFIG_DATA) Dcm_Dsl_R0_stConnection[DCM_DSL_R0_CONNECTION_NUM] =
{

    {
        &Dcm_Dsl_R0_C0_stMainConnection[0],    /* ptMainConnection */
        NULL_PTR,                              /* ptPeriodicTransmission */
        NULL_PTR                               /* ptResponseOnEvent */
    },

    {
        &Dcm_Dsl_R0_C1_stMainConnection[0],    /* ptMainConnection */
        NULL_PTR,                              /* ptPeriodicTransmission */
        NULL_PTR                               /* ptResponseOnEvent */
    },

    {
        &Dcm_Dsl_R0_C2_stMainConnection[0],    /* ptMainConnection */
        NULL_PTR,                              /* ptPeriodicTransmission */
        NULL_PTR                               /* ptResponseOnEvent */
    },

    {
        &Dcm_Dsl_R0_C3_stMainConnection[0],    /* ptMainConnection */
        NULL_PTR,                              /* ptPeriodicTransmission */
        NULL_PTR                               /* ptResponseOnEvent */
    }
};

/* Row */
CONST(AB_83_ConstV Dcm_Dsl_RowType, DCM_CONFIG_DATA) Dcm_Dsl_stRow[DCM_DSL_ROW_NUM]=
{
    {
        &Dcm_Dsl_R0_stConnection[0],    /* ptConnection */
        NULL_PTR,    /* ptSessionRef */
        (uint32)1000000UL,    /* u4DiagFailSafeTimeout */
        (uint16)5000U,    /* u2S3ServerTimeout */
        (uint16)10U,    /* u2P2ServerAdjust */
        (uint16)10U,    /* u2P2StarServerAdjust */
        (uint8)DCM_UDS_ON_CAN,    /* u1ID */
        DCM_DSL_R0_SESSION_NUM,   /* u1SessionNum */
        (boolean)TRUE     /* bCommunicationCancelUsed */
    }
};

/* CbkDCMRequestService */
CONST(AB_83_ConstV Dcm_Dsl_CbkDCMRequestServiceType, DCM_CONFIG_DATA) Dcm_Dsl_stCbkDCMRequestService[1] =
{
    {
        (boolean)FALSE    /* bClientChangeNotifUsed */
    }
};

/* DiagResp */
CONST(AB_83_ConstV Dcm_Dsl_DiagRespType, DCM_CONFIG_DATA) Dcm_Dsl_stDiagResp[1] =
{
    {
        (boolean)TRUE,     /* bP4Server */
        (boolean)FALSE,    /* bDiagRespOnSecondDeclinedRequest */
        (uint8)0x24U        /* u1RespMaxNumRespPend */
    }
};

/* General */
CONST (AB_83_ConstV Dcm_Dsl_GeneralType, DCM_CONFIG_DATA) Dcm_Dsl_stGeneral[1] =
{
    {
        (uint32)181000UL    /* u4FailSafeTimeout */
    }
};

/************************/
/* Internal Config      */
/************************/
/* Session Change Notification */
CONST(AB_83_ConstV Dcm_Dsl_IndSesCtrlChgTableType, DCM_CONFIG_DATA) Dcm_Dsl_IndSesCtrlChgTable[DCM_DSL_INDSESCHG_NUM] =
{
    &Dcm_Dsp_SID28_ResetComCtrl
};

CONST(AB_83_ConstV Dcm_Dsl_IndSecLevelChgTableType, DCM_CONFIG_DATA) Dcm_Dsl_IndSecLevelChgTable[1] =
{
    NULL_PTR
};


CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_ConnectionIdMapTable[DCM_DSL_CLIENT_NUM] =
{
    (uint16)0U,
    (uint16)2U,
    (uint16)3U,
    (uint16)5U
};

CONST(AB_83_ConstV Dcm_Dsl_KALBufferType, DCM_CONFIG_DATA) Dcm_Dsl_stKALBufferTable[DCM_DSL_FUNCADDR_NUM] =
{
    {
        DCM_DSL_KEEPALIVE_LEN,  &Dcm_Dsl_u1KALBuf_0[0]
    },
    {
        DCM_DSL_KEEPALIVE_LEN,  &Dcm_Dsl_u1KALBuf_1[0]
    }
};


CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2RowNum            = DCM_DSL_ROW_NUM;             /* DCM_DSL_ROW_NUM */
CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsl_u1IndSesChgNum       = DCM_DSL_INDSESCHG_NUM;       /* DCM_DSL_INDSESCHG_NUM */
CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsl_u1IndSecLvChgNum     = DCM_DSL_INDSECLEVELCHG_NUM;  /* DCM_DSL_INDSECLEVELCHG_NUM */
CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2ClientNum         = DCM_DSL_CLIENT_NUM;          /* DCM_DSL_CLIENT_NUM */
CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2PduIdNum          = DCM_DSL_PDUID_NUM;           /* DCM_DSL_PDUID_NUM */
CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2TxRetryCountValue = (uint16)8U;                  /* Default session P2Server value / task time */
CONST(AB_83_ConstV boolean, DCM_CONFIG_DATA) Dcm_Dsl_bSecLockOnlyDefSes = (boolean)FALSE;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsl_IndicateSesCtrlChange                            */
/* Description   | Notify SW-C change of the session                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SesCtrlTypeOld : old session control type value   */
/*               | [in] u1SesCtrlTypeNew : new session control type value   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : success                                       */
/*               | E_NOT_OK : failure                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_IndicateSesCtrlChange
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_IndicateSesCtrlChange(u1SesCtrlTypeOld, u1SesCtrlTypeNew);
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_IndicateSecLevelChange                           */
/* Description   | Notify SW-C change of the security                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SecLevelOld : old security level value            */
/*               | [in] u1SecLevelNew : new security level value            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : success                                       */
/*               | E_NOT_OK : failure                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_IndicateSecLevelChange
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_IndicateSecLevelChange(u1SecLevelOld, u1SecLevelNew);
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetP2ServerValue                                 */
/* Description   | Get P2Server/P2StarServerMax/P2StarServerMin value       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  u1Level : session control type value               */
/*               | [out] ptP2Server : P2Server value                        */
/*               | [out] ptP2StarServerMax : P2StarServerMax value          */
/*               | [out] ptP2StarServerMin : P2StarServerMin value          */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_GetP2ServerValue
(
    const Dcm_SesCtrlType u1Level,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2Server,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2StarServerMax,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptP2StarServerMin
)
{
    uint8 u1_SessionRow;
    uint8 u1_SessionRowMax;

    u1_SessionRowMax = Dcm_P_u1SessionRow_N;

    for( u1_SessionRow = (uint8)0U; u1_SessionRow < u1_SessionRowMax; u1_SessionRow++ )
    {
        if( Dcm_P_SID10_stSessionRow_Tbl[u1_SessionRow].u1Level == u1Level )
        {
            *ptP2Server = Dcm_P_SID10_stSessionRow_Tbl[u1_SessionRow].u2P2ServerMax;
            *ptP2StarServerMax = Dcm_P_SID10_stSessionRow_Tbl[u1_SessionRow].u2P2StarServerMax;
            *ptP2StarServerMin = Dcm_P_SID10_stSessionRow_Tbl[u1_SessionRow].u2P2StarServerTimeoutMin;
            break;
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | SchM_Call_Dcm_IocM_SetNoComMode                          */
/* Description   | Call the function(Dcm_SetNoComMode)                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  NetworkId : Identifier of the network concerned by */
/*               |                   the mode change                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : success                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetNoComMode
(
    uint8 NetworkId
)
{
    return Dcm_SetNoComMode(NetworkId);
}

/****************************************************************************/
/* Function Name | SchM_Call_Dcm_IocM_SetSilentComMode                      */
/* Description   | Call the function(Dcm_SetSilentComMode)                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]  NetworkId : Identifier of the network concerned by */
/*               |                   the mode change                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : success                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetSilentComMode
(
    uint8 NetworkId
)
{
    return Dcm_SetSilentComMode(NetworkId);
}

/****************************************************************************/
/* Function Name | SchM_Call_Dcm_IocM_SetFullComMode                        */
/* Description   | Call the function(Dcm_SetFullComMode)                    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  NetworkId : Identifier of the network concerned by */
/*               |                   the mode change                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : success                                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) SchM_Call_Dcm_IocM_SetFullComMode
(
    uint8 NetworkId
)
{
    return Dcm_SetFullComMode(NetworkId);
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
