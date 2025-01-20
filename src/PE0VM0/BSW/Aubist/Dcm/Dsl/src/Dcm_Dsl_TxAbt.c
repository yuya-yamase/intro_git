/* Dcm_Dsl_TxAbt_c(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_TxAbt/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"

#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_TxMsg.h"

#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

#include <Dcm.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_NEG_RESPONSE_SIZE   ((uint8)3U)          /* Negative acknowledge sending buffer size              */

#define DCM_DSL_BUFID_TXBUF         ((uint8)0x00U)       /* PduR sending buffer ID                                */
#define DCM_DSL_BUFID_TXNORESP      ((uint8)0x01U)       /* Designation buffer ID of the no response              */
#define DCM_DSL_BUFID_TXNRCPENDING  ((uint8)0x02U)       /* Buffer ID for exclusive use of the NRC 0x78 sending   */
#define DCM_DSL_COMMON_BUFID_NUM    ((uint8)0x03U)       /* Number of common buffers                              */

#define DCM_DSL_BUFID_TXNRC         ((uint8)0x10U)       /* Negative acknowledge sending buffer ID                */

#define DCM_DSL_RETRY_DUMMY_CNT     ((uint16)10U)        /* Dummy number of retransmissions for interactive client */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Management structure of the sending queue */
typedef struct Dcm_Dsl_tagTxMsgNodeType {
    struct Dcm_Dsl_tagTxMsgNodeType *ptNext;                                /* The next element of the queue */
    AB_83_DcmPduInfoType            stTxPduInfo;                            /* Transmit data                 */
    Dcm_Dsl_ResponseSettingType     u1ResponseKind;                         /* Response kind                 */
} Dcm_Dsl_TxMsgNodeType;

/* Outbound message structure */
typedef struct {
    P2VAR(Dcm_Dsl_TxMsgNodeType, TYPEDEF, DCM_APPL_DATA) ptHead;            /* First address of the queue    */
    P2VAR(Dcm_Dsl_TxMsgNodeType, TYPEDEF, DCM_APPL_DATA) ptTail;            /* End address of the queue      */
} Dcm_Dsl_QueueType;

typedef struct {
    Dcm_Dsl_QueueType    stTxq;                                             /* Sending queue                         */
    Dcm_TxPduInfoType    stTxBuf;                                           /* Sending buffer information            */
    uint16               u2RetryCnt;                                        /* Number of retries allowed             */
} Dcm_Dsl_TxClientType;

typedef struct {
    uint8 u1TxNrc[DCM_DSL_NEG_RESPONSE_SIZE];                               /* Negative acknowledge sending buffer */
} Dcm_Dsl_TxClientBufType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetTxState
(
    const uint16 u2PduMapIndex
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxState
(
    const uint16 u2PduMapIndex,
    const uint8  u1TxState
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Clear
(
    const uint16 u2PduMapIndex
);

static FUNC_P2VAR(Dcm_Dsl_TxClientType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxClient
(
    const uint16 u2PduMapIndex
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxPduInfo
(
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) ptTxClient
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxNRCData
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptSduData,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

static FUNC_P2VAR(AB_83_DcmPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_CreRcrrpMsg
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);

static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxBufById
(
    const uint16 u2PduMapIndex,
    const uint8 u1BufId
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_Rcrrp_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_BusyResTransmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_P4TO_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfConfirmation
(
    const uint16 u2PduMapIndex
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_HandlRcrrpConfirmation
(
    const uint16 u2PduMapIndex,
    const Std_ReturnType u1Result
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmation
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmationNoSesUpdate
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify
(
    const uint16 u2PduMapIndex
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandleLastNonAffirmation
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
);

static FUNC(Dcm_ConfirmationStatusType, DCM_CODE) Dcm_Dsl_TxAbt_GetConfStatus
(
    const uint16         u2PduMapIndex,
    const Std_ReturnType u1Result
);

static FUNC(Dcm_ConfirmationStatusType, DCM_CODE) Dcm_Dsl_TxAbt_CnvConfStatus
(
    const Dcm_Dsl_ResponseSettingType u1ResponseKind,
    const Std_ReturnType u1Result
);

static FUNC_P2VAR(Dcm_TxPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxReservMsg
(
    const uint16                                                 u2PduMapIndex,
    P2VAR(Dcm_Dsl_ResponseSettingType, AUTOMATIC, DCM_APPL_DATA) ptResponseKind
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_RepLastMsg
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptTxq,
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) ptLastMsg
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_DelLatestMsg
(
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) ptTxClient
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Initq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue,
    const uint16                                       u2ClientIndex
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Enq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue,
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) ptNode
);

static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_Deq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue
);

static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetPeekq
(
    P2CONST(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue
);

static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_SetP4TOMsg
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_SetNoticeMsg4P4TO
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetRoePrioCompResult
(
    const uint16 u2ReqPduMapIndex,
    const uint16 u2ActivePduMapIndex
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/* Response sending buffer plant area */
static VAR(Dcm_Dsl_TxClientType, DCM_VAR_NO_INIT) Dcm_Dsl_TxClient[DCM_DSL_CLIENT_NUM];

/* Sending queue header information */
static VAR(Dcm_Dsl_TxMsgNodeType, DCM_VAR_NO_INIT) Dcm_Dsl_stTxMsgHead[DCM_DSL_COMMON_BUFID_NUM];

static VAR(Dcm_Dsl_TxMsgNodeType, DCM_VAR_NO_INIT) Dcm_Dsl_stTxMsgQueueHead[DCM_DSL_CLIENT_NUM];
static VAR(Dcm_Dsl_TxMsgNodeType, DCM_VAR_NO_INIT) Dcm_Dsl_stNegMsgHead[DCM_DSL_CLIENT_NUM];

/* Negative acknowledge sending buffer */
static VAR(Dcm_Dsl_TxClientBufType, DCM_VAR_NO_INIT) Dcm_Dsl_stTxClientBuf[DCM_DSL_CLIENT_NUM];

/* NRC 0x78 sending buffer */
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1NrcPending[DCM_DSL_NEG_RESPONSE_SIZE];

/* Tx State */
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1TxState[DCM_DSL_CLIENT_NUM];

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Init                                       */
/* Description   | This function initializes Dsl_TxAbt.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Init
(void)
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;

    u2_ClientNumMax         = Dcm_Dsl_u2ClientNum;
    Dcm_Dsl_u1NrcPending[0] = (uint8)0U;

    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        Dcm_Dsl_u1TxState[u2_ClientCnt]                = DCM_DSL_TXST_IDLE;
        Dcm_Dsl_stTxClientBuf[u2_ClientCnt].u1TxNrc[0] = (uint8)0U;

        Dcm_Dsl_TxClient[u2_ClientCnt].stTxBuf.SduStartAddr = NULL_PTR;
        Dcm_Dsl_TxClient[u2_ClientCnt].stTxBuf.SduPos       = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_TxClient[u2_ClientCnt].stTxBuf.SduLength    = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_TxClient[u2_ClientCnt].u2RetryCnt           = (uint16)0U;

        Dcm_Dsl_TxAbt_Initq(&Dcm_Dsl_TxClient[u2_ClientCnt].stTxq, u2_ClientCnt);

        Dcm_Dsl_stNegMsgHead[u2_ClientCnt].stTxPduInfo.SduDataPtr = &Dcm_Dsl_stTxClientBuf[u2_ClientCnt].u1TxNrc[0];
        Dcm_Dsl_stNegMsgHead[u2_ClientCnt].stTxPduInfo.SduLength  = DCM_DSL_NEG_RESPONSE_SIZE;
        Dcm_Dsl_stNegMsgHead[u2_ClientCnt].u1ResponseKind         = DCM_DSL_SET_NEGATIVE_RESPONSE;
    }

    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].stTxPduInfo.SduDataPtr        = Dcm_Dsl_TxClient[0].stTxBuf.SduStartAddr;
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].stTxPduInfo.SduLength         = Dcm_Dsl_TxClient[0].stTxBuf.SduLength;
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].u1ResponseKind                = DCM_DSL_SET_POSITIVE_RESPONSE;

    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].stTxPduInfo.SduDataPtr = &Dcm_Dsl_u1NrcPending[0];
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].stTxPduInfo.SduLength  = DCM_DSL_NEG_RESPONSE_SIZE;
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].u1ResponseKind         = DCM_DSL_SET_PENDING_RESPONSE;

    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].stTxPduInfo.SduDataPtr     = NULL_PTR;
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].stTxPduInfo.SduLength      = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].u1ResponseKind             = DCM_DSL_SET_NO_RESPONSE_NEG;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Activate                                   */
/* Description   | This function activates Dsl_TxAbt.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Activate
(
    const uint16 u2PduMapIndex
)
{
    uint8 u1_TxState;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

    if( u1_TxState == DCM_DSL_TXST_IDLE )
    {
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Deactivate                                 */
/* Description   | This function deactivates Dsl_TxAbt.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Deactivate
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, DCM_RES_POS_OK);

    Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_FailSafeTO                                 */
/* Description   | This function performs a process in TxFailsafe time out. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_FailSafeTO
(
    const uint16 u2PduMapIndex
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
    uint8                      u1_TxState;
    boolean                    b_IsTxState;
    boolean                    b_Clear;
    boolean                    b_InteractiveClient;
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;

    u1_TxState     = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    pt_TxClient    = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    b_Clear        = (boolean)FALSE;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_StopTxTimers();
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)FALSE);

        if( ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST_P4 )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 ) )
        {
            Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);

            if( ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
             || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 ) )
            {
                Dcm_Dsl_TxAbt_DelLatestMsg(pt_TxClient);
            }
            u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);

            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);

            if( ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST )
             || ( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
             || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
             || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 ) )
            {
                Dcm_Dsl_TxMsg_CancelTransmit(u2PduMapIndex);
            }
            b_Clear = (boolean)TRUE;
        }
        else if( ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
              || ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
              || ( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP )
              || ( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
              || ( u1_TxState == DCM_DSL_TXST_WT_CL_TX )
              || ( u1_TxState == DCM_DSL_TXST_WT_CL_TXERR )
              || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP ) )
        {
            Dcm_Dsl_Ctrl_CancelService();

            b_IsTxState = Dcm_Dsl_TxAbt_IsTxState(u2PduMapIndex);
            if( b_IsTxState == (boolean)TRUE )
            {
                Dcm_Dsl_TxMsg_CancelTransmit(u2PduMapIndex);
            }
            else
            {
                if( u1_TxState  == DCM_DSL_TXST_WT_CL_TX )
                {
                    Dcm_Dsl_TxMsg_CancelTransmit(u2PduMapIndex);
                }
            }
            Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
            b_Clear = (boolean)TRUE;
        }
        else if( ( u1_TxState == DCM_DSL_TXST_IDLE )
             || ( u1_TxState == DCM_DSL_TXST_WT_COMP_LAST ) )
        {
            /* no process */
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }
    else
    {
        if( ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST ) )
        {
            Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);

            if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST )
            {
                Dcm_Dsl_TxMsg_CancelTransmit(u2PduMapIndex);
            }
        }
        b_Clear = (boolean)TRUE;
    }

    if( b_Clear == (boolean)TRUE )
    {
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Deactivate(u2PduMapIndex); /* Change State DCM_DSL_TXST_IDLE */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_TransmitReq                                */
/* Description   | This function for the sending call back a latch          */
/*               | (final response).                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   DCM_E_PENDING         : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TransmitReq
(
    const uint16 u2PduMapIndex
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA)  pt_Info;
#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    AB_83_DcmPduInfoType        st_NoticeInfo;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */
    uint8                       u1_TxState;
    boolean                     b_InteractiveClient;
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_Result;
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;

    u1_Result           = (Std_ReturnType)E_OK;
    u1_ResponseKind     = (Dcm_Dsl_ResponseSettingType)0U;
    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);

    pt_Info = Dcm_Dsl_TxAbt_GetTxReservMsg(u2PduMapIndex, &u1_ResponseKind);
    if( pt_Info != NULL_PTR )
    {
        u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
        if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

            if( b_InteractiveClient == (boolean)TRUE )
            {
                u1_RetVal = Dcm_Dsl_TxAbt_Transmit(u2PduMapIndex, pt_Info, u1_ResponseKind);
            }
            else
            {
                pt_TxClient             = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
                pt_TxClient->u2RetryCnt = Dcm_Dsl_u2TxRetryCountValue;

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
                st_NoticeInfo.SduDataPtr = pt_Info->SduStartAddr;
                st_NoticeInfo.SduLength  = pt_Info->SduLength;
                Dcm_Dsl_Ctrl_ProvideDiagComData(u2PduMapIndex, &st_NoticeInfo, DCM_DSL_SET_NEGATIVE_RESPONSE);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

                u1_RetVal = Dcm_Dsl_TxAbt_BusyResTransmit(u2PduMapIndex, pt_Info);
            }

            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                /* no process */
            }
            else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_DISABLE )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
                u1_Result = (Std_ReturnType)DCM_E_PENDING;
            }
            else
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
        else if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST_P4 )
        {
            Dcm_Dsl_Ctrl_NotifyTxStart();
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

            u1_RetVal = Dcm_Dsl_TxAbt_P4TO_Transmit(u2PduMapIndex, pt_Info);
            if( u1_RetVal != (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
        else
        {
            if( b_InteractiveClient == (boolean)FALSE )
            {
                Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_TxRetryReq                                 */
/* Description   | This function performs a retry of the sending            */
/*               | until P2ServerMax progress.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   DCM_E_PENDING         : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TxRetryReq
(
    const uint16 u2PduMapIndex
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA)  pt_Info;
    uint8                       u1_TxState;
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_Result;
    boolean                     b_RetryOver;
    boolean                     b_InteractiveClient;

    u1_Result    = (Std_ReturnType)E_OK;
    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    u1_TxState   = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    b_RetryOver  = (boolean)FALSE;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        b_RetryOver             = Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed();
        pt_TxClient->u2RetryCnt = DCM_DSL_RETRY_DUMMY_CNT;
    }
    else
    {
        if( pt_TxClient->u2RetryCnt == (uint16)0U )
        {
            b_RetryOver = (boolean)TRUE;
        }
    }

    if( b_RetryOver == (boolean)FALSE )
    {
        pt_TxClient->u2RetryCnt = pt_TxClient->u2RetryCnt - (uint16)1U;
        if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
        {
            u1_ResponseKind = DCM_DSL_SET_NONE_RESPONSE;
            pt_Info = Dcm_Dsl_TxAbt_GetTxReservMsg(u2PduMapIndex, &u1_ResponseKind);
            if( pt_Info != NULL_PTR )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

                if( b_InteractiveClient == (boolean)TRUE )
                {
                    u1_RetVal = Dcm_Dsl_TxAbt_Transmit(u2PduMapIndex, pt_Info, u1_ResponseKind);
                }
                else
                {
                    u1_RetVal = Dcm_Dsl_TxAbt_BusyResTransmit(u2PduMapIndex, pt_Info);
                }

                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    /* no process */
                }
                else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_DISABLE )
                {
                    Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
                    u1_Result = (Std_ReturnType)DCM_E_PENDING;
                }
                else /* E_NOT_OK */
                {
                    Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
                }
            }
        }
        else
        {
            if( b_InteractiveClient == (boolean)FALSE )
            {
                Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
    }
    else
    {
        if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
        {
            if( b_InteractiveClient == (boolean)TRUE )
            {
                Dcm_Dsl_Ctrl_StopTxTimers();

                u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);
                Dcm_Dsl_TxAbt_NonAffirmationNoSesUpdate(u2PduMapIndex, u1_ConfirmationStatus);
            }
            else
            {
                Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
            }
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
        else if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST_P4 )
        {
            Dcm_Dsl_Ctrl_NotifyTxStart();
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

            u1_RetVal = Dcm_Dsl_TxAbt_P4TO_Transmit(u2PduMapIndex, &pt_TxClient->stTxBuf);
            if( u1_RetVal != (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
        else
        {
            if( b_InteractiveClient == (boolean)FALSE )
            {
                Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
            }
        }
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_WriteNRCData                               */
/* Description   | This function makes a negative acknowledge message.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : Service ID                          */
/*               |                                                          */
/*               | [in] u1ErrorCode   : Error code(NRC)                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_WriteNRCData
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    uint16  u2_ClientIndex;
    u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);
    Dcm_Dsl_TxAbt_SetTxNRCData(&Dcm_Dsl_stTxClientBuf[u2_ClientIndex].u1TxNrc[0], u1SID, u1ErrorCode);
    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_P2TO                                       */
/* Description   | This function performs a process in P2Server time out    */
/*               | and the P2*Server time out.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : SID                                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_P2TO
(
    const uint16 u2PduMapIndex,
    const uint8  u1SID
)
{
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    Dcm_TxPduInfoType           st_Info;
    uint8                       u1_TxState;
    Std_ReturnType              u1_RetVal;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

    if( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        pt_Msg = Dcm_Dsl_TxAbt_CreRcrrpMsg(u2PduMapIndex, u1SID);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP);

        st_Info.SduStartAddr = pt_Msg->SduDataPtr;
        st_Info.SduPos       = (AB_83_DcmPduLengthType)0U;
        st_Info.SduLength    = pt_Msg->SduLength;

        u1_RetVal = Dcm_Dsl_TxAbt_Rcrrp_Transmit(u2PduMapIndex, &st_Info);
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_SEND_ERR )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP_P2MINTO);
        }
        else /* E_NOT_OK */
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }
    /* Valid state   = DCM_DSL_TXST_WT_TX_LAST, DCM_DSL_TXST_WT_TX_LAST_P4 -> no process */
    /* Invalid state = Other                                               -> Disregard */

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_P2MinTO                                    */
/* Description   | This function performs a process in P2*ServerMin         */
/*               | time out.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_P2MinTO
(
    const uint16 u2PduMapIndex
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
    uint8             u1_TxState;
    Std_ReturnType    u1_RetVal;

    pt_TxClient = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    u1_TxState  = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

    if( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
    {
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP);
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP )
    {
        Dcm_Dsl_Ctrl_NotifyRcrrpTxStart();
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP);

        u1_RetVal = Dcm_Dsl_TxAbt_Rcrrp_Transmit(u2PduMapIndex, &pt_TxClient->stTxBuf);
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_SEND_ERR )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP_P2MINTO);
        }
        else /* E_NOT_OK */
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }
    else
    {
        /* no process */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_P4TO                                       */
/* Description   | This function performs a process in the P4Server timeout.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : SID                                 */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_P4TO
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_RcrrpMsg;
#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_NoticeMsg;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */
    Dcm_TxPduInfoType          st_Info;
    uint8                      u1_TxState;
    Std_ReturnType             u1_RetVal;
    Std_ReturnType             u1_Result;

    u1_Result    = (Std_ReturnType)E_OK;
    pt_Msg       = Dcm_Dsl_TxAbt_SetP4TOMsg(u2PduMapIndex, u1SID);
    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    u1_TxState   = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    pt_NoticeMsg = Dcm_Dsl_TxAbt_SetNoticeMsg4P4TO(u2PduMapIndex, u1SID);
    Dcm_Dsl_Ctrl_ProvideDiagComData(u2PduMapIndex, &pt_NoticeMsg->stTxPduInfo, DCM_DSL_SET_NEGATIVE_RESPONSE);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

    if( ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
     || ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
     || ( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP ) )
    {
        /* DCM_M_TMRID_P2MINTIMER, DCM_M_TMRID_P2TIMER stop */
        Dcm_Dsl_Ctrl_NotifyTxStart();

        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        if( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP )
        {
            /* Replace RCRRP with a designation message */
            Dcm_Dsl_TxAbt_RepLastMsg(&pt_TxClient->stTxq, pt_Msg);
        }
        else
        {
            Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
        }
        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

        st_Info.SduStartAddr = pt_Msg->stTxPduInfo.SduDataPtr;
        st_Info.SduPos       = (AB_83_DcmPduLengthType)0U;
        st_Info.SduLength    = pt_Msg->stTxPduInfo.SduLength;

        u1_RetVal = Dcm_Dsl_TxAbt_P4TO_Transmit(u2PduMapIndex, &st_Info);
        if( u1_RetVal != (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);

        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        /* Replace final response with a designation message  */
        Dcm_Dsl_TxAbt_RepLastMsg(&pt_TxClient->stTxq, pt_Msg);
        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST_P4);
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP )
    {
        Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);

        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4);
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);

        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        /* Replace final response with a designation message  */
        /* Get RCRRP msg */
        pt_RcrrpMsg = Dcm_Dsl_TxAbt_Deq(&pt_TxClient->stTxq);

        /* Get final response and leave msg */
        (void)Dcm_Dsl_TxAbt_Deq(&pt_TxClient->stTxq);

        Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_RcrrpMsg);
        Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4);
    }
    else if( ( u1_TxState == DCM_DSL_TXST_WT_CL_TXERR )
        ||   ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST_P4 )
        ||   ( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
        ||   ( u1_TxState == DCM_DSL_TXST_WT_CL_TX )
        ||   ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 )
        ||   ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST ) )
    {
        /* no process */
        /* State sticking can not occur in subsequent processing */
    }
    else /* DCM_DSL_TXST_IDLE, DCM_DSL_TXST_WT_COMP_LAST, Other */
    {
        u1_Result = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_TransmitFunctionality                      */
/* Description   | This function orders sending of the response message to  */
/*               | Dsl.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex  : PduMapIndex Value                  */
/*               |                                                          */
/*               | [in] ptInfo         : PduR sending buffer address        */
/*               |                                                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/*               |   DCM_E_PENDING         : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TransmitFunctionality
(
    const uint16 u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_NoticeMsg;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */
    uint8                      u1_TxState;
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;
    Std_ReturnType             u1_RetVal;
    Std_ReturnType             u1_Result;
#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    boolean                    b_ServiceToRespondTo;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

    u1_Result   = (Std_ReturnType)E_OK;
    pt_TxClient = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);

    if( u1ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE )
    {
        pt_Msg                         = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXBUF);
        pt_Msg->stTxPduInfo.SduDataPtr = ptInfo->SduDataPtr;
        pt_Msg->stTxPduInfo.SduLength  = ptInfo->SduLength;
    }
    else if( u1ResponseKind == DCM_DSL_SET_NEGATIVE_RESPONSE )
    {
        pt_Msg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);
    }
    else
    {
        pt_Msg                 = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNORESP);
        pt_Msg->u1ResponseKind = u1ResponseKind;
    }

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    if( u1_TxState != DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
    {
        b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
        if( b_ServiceToRespondTo == (boolean)FALSE )
        {
            if( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_POS )
            {
                pt_NoticeMsg                         = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXBUF);
                pt_NoticeMsg->stTxPduInfo.SduDataPtr = ptInfo->SduDataPtr;
                pt_NoticeMsg->stTxPduInfo.SduLength  = ptInfo->SduLength;
            }
            else if( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_NEG )
            {
                pt_NoticeMsg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);
            }
            else
            {
                pt_NoticeMsg = pt_Msg;
            }
            Dcm_Dsl_Ctrl_ProvideDiagComData(u2PduMapIndex, &pt_NoticeMsg->stTxPduInfo, u1ResponseKind);
        }
    }
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

    if( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
    {
        if( u1ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE )
        {
            /* lock */
            SchM_Enter_Dcm_Dsl_TxPduInfo();

            pt_TxClient->stTxBuf.SduLength += pt_Msg->stTxPduInfo.SduLength; /* no wrap around */

            /* unlock */
            SchM_Exit_Dcm_Dsl_TxPduInfo();

            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);
        }
        else
        {
            u1_Result = (Std_ReturnType)E_NOT_OK;
        }
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP_ABT);

    }
    else if( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);

        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1ResponseKind, (Std_ReturnType)E_NOT_OK);
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);

        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);

        /* u2_CancelPduMapIndex =(equal) u2PduMapIndex */
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_CL_TX )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);

        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1ResponseKind, (Std_ReturnType)E_NOT_OK);
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);

        /* u2_CancelPduMapIndex =(equal) u2PduMapIndex */
        Dcm_Dsl_TxAbt_CancelTransmit(u2PduMapIndex); /* Change State DCM_DSL_TXST_IDLE */
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_CL_TXERR )
    {
        Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg(u2PduMapIndex);

        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);

        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1ResponseKind, (Std_ReturnType)E_NOT_OK);
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);

        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Deactivate(u2PduMapIndex);       /* Change State DCM_DSL_TXST_IDLE */
    }
    else if( ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
          || ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
          || ( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP ) )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        if( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP )
        {
            /* Replace final response with a designation message  */
            Dcm_Dsl_TxAbt_RepLastMsg(&pt_TxClient->stTxq, pt_Msg);
        }
        else
        {
            Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
        }

        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

        u1_RetVal = Dcm_Dsl_TxAbt_Transmit(u2PduMapIndex, &pt_TxClient->stTxBuf, u1ResponseKind);
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_DISABLE )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
            u1_Result = (Std_ReturnType)DCM_E_PENDING;
        }
        else
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }
    /* DCM_DSL_TXST_IDLE, DCM_DSL_TXST_WT_TX_LAST, DCM_DSL_TXST_WT_TX_LAST_P4,
     * DCM_DSL_TXST_WT_TX_COMP_RP_ABT, DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4,
     * DCM_DSL_TXST_WT_TX_COMP_LAST, DCM_DSL_TXST_WT_COMP_LAST, other...
     */
    else
    {
        u1_Result = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Result;
}


#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetRespReqMsg                              */
/* Description   | This function stores the response message in the         */
/*               | transmission buffer.                                     */
/* Preconditions | Call only from Dcm_Dsl_RespReqAfterEcuReset()            */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo        : PduR sending buffer address         */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetRespReqMsg
(
    const uint16 u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;

    pt_TxClient                    = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    pt_Msg                         = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXBUF);
    pt_Msg->stTxPduInfo.SduDataPtr = ptInfo->SduDataPtr;
    pt_Msg->stTxPduInfo.SduLength  = ptInfo->SduLength;

    Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
    Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

    Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_RespReqAfterEcuReset                       */
/* Description   | This function sends response message                     */
/* Preconditions | Call only from Dcm_Dsl_RespReqAfterEcuResetCbk()         */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   DCM_E_PENDING         : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_RespReqAfterEcuReset
(
    const uint16 u2PduMapIndex
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    AB_83_DcmPduInfoType        st_NoticeInfo;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */
    Std_ReturnType              u1_Result;
    uint8                       u1_TxState;

    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    u1_TxState   = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    u1_Result    = (Std_ReturnType)E_OK;

    if( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
    {
        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);

        /* u2_CancelPduMapIndex =(equal) u2PduMapIndex */
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
    }
    else
    {
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_LAST);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
        st_NoticeInfo.SduDataPtr = pt_TxClient->stTxBuf.SduStartAddr;
        st_NoticeInfo.SduLength  = pt_TxClient->stTxBuf.SduLength;
        Dcm_Dsl_Ctrl_ProvideDiagComData(u2PduMapIndex, &st_NoticeInfo, DCM_DSL_SET_POSITIVE_RESPONSE);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

        u1_Result = Dcm_Dsl_TxMsg_PosResTransmit(u2PduMapIndex, &pt_TxClient->stTxBuf);
        if( u1_Result != (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
            u1_Result = (Std_ReturnType)DCM_E_PENDING;
        }
    }

    return u1_Result;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetBusyRespReq                             */
/* Description   | This function makes a negative response asynchronous     */
/*               | send request.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : Service ID                          */
/*               |                                                          */
/*               | [in] u1ErrorCode   : Error code(NRC)                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_SetBusyRespReq
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    uint8                                                  u1_TxState;
    Std_ReturnType                                         u1_Result;

    u1_Result = (Std_ReturnType)E_OK;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
    {
        pt_TxClient = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
        pt_Msg      = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);

        Dcm_Dsl_TxAbt_WriteNRCData(u2PduMapIndex, u1SID, u1ErrorCode);
        Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
    }
    else
    {
        u1_Result = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SendForcePendingResponse                   */
/* Description   | This function requires ForceRCRRP.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : Service ID                          */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SendForcePendingResponse
(
    const uint16 u2PduMapIndex,
    const uint8  u1SID
)
{
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    Dcm_TxPduInfoType           st_Info;
    uint8           u1_TxState;
    Std_ReturnType  u1_RetVal;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

    if( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
    {
        Dcm_Dsl_Ctrl_NotifyRcrrpTxStart();

        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        pt_Msg = Dcm_Dsl_TxAbt_CreRcrrpMsg(u2PduMapIndex, u1SID);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_COMP_RP);

        st_Info.SduStartAddr = pt_Msg->SduDataPtr;
        st_Info.SduPos       = (AB_83_DcmPduLengthType)0U;
        st_Info.SduLength    = pt_Msg->SduLength;

        u1_RetVal = Dcm_Dsl_TxAbt_Rcrrp_Transmit(u2PduMapIndex, &st_Info);
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TX_E_SEND_ERR )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP_P2MINTO);
        }
        else /* E_NOT_OK */
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        (void)Dcm_Dsl_TxAbt_CreRcrrpMsg(u2PduMapIndex, u1SID);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_RCRRP);
    }
    else /* DCM_DSL_TXST_WT_TX_COMP_RP, other */
    {
        /* no process */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CancelReq                                  */
/* Description   | This function requires a cancel process.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelReq
(
    const uint16 u2PduMapIndex
)
{
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;
    uint8                      u1_TxState;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);

    if( ( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
     || ( u1_TxState == DCM_DSL_TXST_WT_CL_TX )
     || ( u1_TxState == DCM_DSL_TXST_WT_CL_TXERR )
     || ( u1_TxState == DCM_DSL_TXST_WT_COMP_LAST ) )
    {
        /* no process */
    }
    else
    {
        Dcm_Dsl_Ctrl_StopTxTimers();
        Dcm_Dsl_TxMsg_StopTimer();

        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);
        Dcm_Dsl_Ctrl_NotifyTxCancel(u2PduMapIndex, u1_ConfirmationStatus);

        if( ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
         || ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_RCRRP )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_LAST_P4 ) )
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_CL_SV_COMP);
        }
        else
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_CL_TX);
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CancelTransmit                             */
/* Description   | This function cancels the transmission process           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : Cancel PduMapIndex Value            */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelTransmit
(
    const uint16 u2PduMapIndex
)
{
    boolean                    b_DisableCancelService;
    uint8                      u1_TxState;
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;

    Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);
    b_DisableCancelService = Dcm_Dsl_Ctrl_IsAcceptedFinalResp(u2PduMapIndex);

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( u1_TxState == DCM_DSL_TXST_WT_CL_TXERR )
    {
        Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Deactivate(u2PduMapIndex);        /* Change State DCM_DSL_TXST_IDLE */
        Dcm_Dsl_Ctrl_TxErrNotification(u2PduMapIndex);  /* Change to DCM_DSL_TXST_WT_SV_COMP state if new request is accepted */
    }
    else if( ( u1_TxState == DCM_DSL_TXST_WT_CL_SV_COMP )
         ||  ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP )
         ||  ( u1_TxState == DCM_DSL_TXST_WT_SV_COMP_P2MINTO )
         ||  ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP ) )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);

        if( b_DisableCancelService == (boolean)TRUE )
        {
            u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);
            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);
        }
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
    }
    else if( u1_TxState == DCM_DSL_TXST_WT_CL_TX )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);

        if( b_DisableCancelService == (boolean)TRUE )
        {
            u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);
            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);
        }

        Dcm_Dsl_TxMsg_CancelTransmit(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
    }
    else
    {
        /* no process */
    }

    return ;
}

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CancelRespReq                              */
/* Description   | This function cancels response request after reset       */
/* Preconditions | Call only from Dcm_Dsl_RespReqAfterEcuResetCbk()         */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelRespReq
(
    const uint16 u2PduMapIndex
)
{
    /* DCM_M_TMRID_P4TIMER stop */
    Dcm_Dsl_Ctrl_StopTxTimers();
    Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
    Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
    return ;
}

#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CancelPagedBuffer                          */
/* Description   | This function performs a process in PagedBuffer time out.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelPagedBuffer
(
    const uint16 u2PduMapIndex
)
{
    uint8                      u1_TxState;
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( ( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
      ||( u1_TxState == DCM_DSL_TXST_WT_CL_TX ) )
    {
        /* DCM_M_TMRID_PAGEDBUFFERTIMER stop */
        Dcm_Dsl_Ctrl_StopTxTimers();
        Dcm_Dsl_TxMsg_StopTimer();

        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)FALSE);

        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, (Std_ReturnType)E_NOT_OK);

        if( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
        {
            Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
        }
        else
        {
            Dcm_Dsl_Ctrl_CancelConfirmation(u2PduMapIndex);
        }

        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1_ConfirmationStatus, (boolean)FALSE);

        /* CancelTransmit prohibited */
        Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
        Dcm_Dsl_TxAbt_Deactivate(u2PduMapIndex); /* Change State DCM_DSL_TXST_IDLE */
    }
    else if( ( u1_TxState == DCM_DSL_TXST_IDLE )
          || ( u1_TxState == DCM_DSL_TXST_WT_COMP_LAST ) )
    {
        /* no process */
    }
    else
    {
        Dcm_Dsl_TxMsg_Abort();
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage                     */
/* Description   | This function requires UpdatePage in upper layer         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_E_NOT_OK : Data has been copied to the transmit  */
/*               |  BUFREQ_E_BUSY   : Request could not be fulfilled        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage
(
    const uint16 u2PduMapIndex
)
{
    BufReq_ReturnType  u1_Result;
    uint8              u1_TxState;
    boolean            b_InteractiveClient;
    boolean            b_UpdateReqResult;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    u1_Result  = BUFREQ_E_BUSY;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST )
        {
            b_UpdateReqResult = Dcm_Dsl_Ctrl_ReqUpdatePage();
            if( b_UpdateReqResult == (boolean)TRUE )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_PAGE_UPDATE);
            }
            else
            {
                u1_Result = BUFREQ_E_NOT_OK;
            }
        }
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandlTopHalfLastConfirmation               */
/* Description   | This function performs sending completion notice         */
/*               | handling of final response (top half).                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1Result : Result of the transmission of the I-PDU. */
/*               |                                                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfLastConfirmation
(
    const uint16         u2PduMapIndex,
    const Std_ReturnType u1Result,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;
    boolean                    b_InteractiveClient;
    boolean                    b_ServiceToRespondTo;

    u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1ResponseKind, u1Result);
    Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, u1_ConfirmationStatus);

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        /* DCM_M_TMRID_PAGEDBUFFERTIMER stop */
        Dcm_Dsl_Ctrl_StopTxTimers();

        if( u1Result == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)TRUE);
        }
        else
        {
            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)TRUE);
        }

        Dcm_Dsl_TxAbt_HandlTopHalfConfirmation(u2PduMapIndex);
        Dcm_Dsl_Ctrl_NotifyTxEnd();
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_COMP_LAST);
    }
    else
    {
        b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);

        Dcm_Dsl_TxAbt_HandlTopHalfConfirmation(u2PduMapIndex);

        if( b_ServiceToRespondTo == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_NotifyTxEnd();
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_COMP_LAST);
        }
        else
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_IDLE);
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandlTopHalfRcrrpConfirmation              */
/* Description   | This function performs sending completion notice         */
/*               | handling of RCRRP (top half).                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1Result : Result of the transmission of the I-PDU. */
/*               |                                                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfRcrrpConfirmation
(
    const uint16         u2PduMapIndex,
    const Std_ReturnType u1Result,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    uint8                       u1_TxState;
    Std_ReturnType              u1_Retval;
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;

    u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1ResponseKind, u1Result);
    Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, u1_ConfirmationStatus);

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP )
    {
        Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_SV_COMP_P2MINTO);

        u1_Retval = Dcm_Dsl_TxAbt_HandlRcrrpConfirmation(u2PduMapIndex, u1Result);
        if( u1_Retval == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_Ctrl_RcrrpConfirmation(u2PduMapIndex);
        }
        else /* TxErrHdl:DCM_TXERR_SESCHG_DEFAULT or DCM_TXERR_DISCON */
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_CL_TXERR);
        }
    }
    else /* DCM_DSL_TXST_WT_TX_COMP_RP_ABT, DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 */
    {
        u1_Retval = Dcm_Dsl_TxAbt_HandlRcrrpConfirmation(u2PduMapIndex, u1Result);
        if( u1_Retval == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_Ctrl_RcrrpConfirmation(u2PduMapIndex);

            if( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST);
            }
            else
            {
                Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_TX_LAST_P4);
            }
        }
        else /* TxErrHdl:DCM_TXERR_SESCHG_DEFAULT or DCM_TXERR_DISCON */
        {
            Dcm_Dsl_TxAbt_SetTxState(u2PduMapIndex, DCM_DSL_TXST_WT_COMP_LAST);
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_IsTxState                                  */
/* Description   | It is determined whether this function is status during  */
/*               | the response.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Under response                              */
/*               |      FALSE : no response                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_IsTxState
(
    const uint16 u2PduMapIndex
)
{
    uint8   u1_TxState;
    boolean b_Result;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    b_Result   = (boolean)FALSE;

    if( ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP )
     || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
     || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 )
     || ( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
     || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST ) )
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_IsActive                                   */
/* Description   | It is determined whether this function is status during  */
/*               | the response.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Active                                      */
/*               |      FALSE : Inactive                                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_IsActive
(
    const uint16 u2PduMapIndex
)
{
    uint8   u1_TxState;
    boolean b_Result;

    b_Result   = (boolean)FALSE;

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( u1_TxState != DCM_DSL_TXST_IDLE )
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CanStartRoe                                */
/* Description   | This function checks whether the ROE start condition     */
/*               | is satisfied.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex       : PduMapIndex Value             */
/*               | [in] u2ActivePduMapIndex : PduMapIndex Value             */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |       TRUE : can                                         */
/*               |      FALSE : can not                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_CanStartRoe
(
    const uint16 u2ReqPduMapIndex,
    const uint16 u2ActivePduMapIndex
)
{
    uint8           u1_ActivePriorityCompResult;
    boolean         b_Result;
    boolean         b_Active;

    b_Result   = (boolean)FALSE;

    if( u2ReqPduMapIndex == u2ActivePduMapIndex )
    {
        b_Result = (boolean)TRUE;
    }
    else
    {
        u1_ActivePriorityCompResult = Dcm_Dsl_TxAbt_GetRoePrioCompResult(u2ReqPduMapIndex, u2ActivePduMapIndex);
        if( u1_ActivePriorityCompResult == DCM_DSL_PRIORITY_HIGH )
        {
            b_Result = (boolean)TRUE;
        }
        else
        {
            b_Active = Dcm_Dsl_Ctrl_IsActiveSession();
            if( b_Active == (boolean)FALSE )
            {
                b_Result = (boolean)TRUE;
            }
        }
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetRoePrioCompResult                       */
/* Description   | This function compares request id and active id client   */
/*               | priority.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ReqPduIdMapIndex:                                 */
/*               |             Management number of request PduId           */
/*               | [in] u2ActivePduIdMapIndex:                              */
/*               |             Management number of active PduId            */
/* Return Value  | uint8                                                    */
/*               |     DCM_DSL_PRIORITY_HIGH : Request id has high priority */
/*               |     DCM_DSL_PRIORITY_EQUAL: Request id has Same priority */
/*               |     DCM_DSL_PRIORITY_LOW  : Request id has low priority  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetRoePrioCompResult
(
    const uint16 u2ReqPduMapIndex,
    const uint16 u2ActivePduMapIndex
)
{
    uint8 u1_RetVal;
    uint8 u1_ReqClientPriority;
    uint8 u1_ActiveClientPriority;

    u1_ReqClientPriority    = Dcm_Dsl_Ctrl_GetConnectionPriority(u2ReqPduMapIndex);
    u1_ActiveClientPriority = Dcm_Dsl_Ctrl_GetConnectionPriority(u2ActivePduMapIndex);

    if( u1_ReqClientPriority < u1_ActiveClientPriority )
    {
        u1_RetVal = DCM_DSL_PRIORITY_HIGH;
    }
    else if( u1_ReqClientPriority == u1_ActiveClientPriority )
    {
        u1_RetVal = DCM_DSL_PRIORITY_EQUAL;
    }
    else /* u1_ReqClientPriority > u1_ActiveClientPriority */
    {
        u1_RetVal = DCM_DSL_PRIORITY_LOW;
    }

    return u1_RetVal;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetTxBuf                                   */
/* Description   | This function acquires the address of the sending buffer */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | Dcm_TxPduInfoType *                                      */
/*               |   DataPointer : There is an outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(Dcm_TxPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxBuf
(
    const uint16 u2PduMapIndex
)
{
    uint16 u2_ClientIndex;
    u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);

    return &Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetLastTransmittedMsg                      */
/* Description   | This function acquires the information of the latest     */
/*               | message which has been sent.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex   : PduMapIndex Val                   */
/*               |                                                          */
/*               | [out] ptResponseKind : Response kind                     */
/*               |                                                          */
/* Return Value  | AB_83_DcmPduInfoType *                                   */
/*               |   DataPointer : There is an outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(AB_83_DcmPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetLastTransmittedMsg
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_ResponseSettingType, AUTOMATIC, DCM_APPL_DATA) ptResponseKind
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    P2VAR(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)  pt_Result;

    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    pt_Result    = NULL_PTR;

    pt_Msg = Dcm_Dsl_TxAbt_Deq(&pt_TxClient->stTxq);
    if( pt_Msg != NULL_PTR )
    {
        *ptResponseKind = pt_Msg->u1ResponseKind;
        pt_Result       = &pt_Msg->stTxPduInfo;
        Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);
    }
    else
    {
        *ptResponseKind = DCM_DSL_SET_NONE_RESPONSE;
    }

    return pt_Result;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetResponseDataLength                      */
/* Description   | This function gets Response Data Length.                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | AB_83_DcmPduLengthType                                   */
/*               |   0x000000U-0xFFFFFFFFU : Response Data Length           */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC(AB_83_DcmPduLengthType, DCM_CODE) Dcm_Dsl_TxAbt_GetResponseDataLength
(void)
{
    return Dcm_Dsl_Ctrl_GetResponseDataLength();
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_NotifyTxStart                              */
/* Description   | This function stops sending time register by a lump      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NotifyTxStart
(void)
{
    Dcm_Dsl_Ctrl_NotifyTxStart();
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetSrcPduMapIndex                          */
/* Description   | This function gets the source address.                   */
/* Preconditions | u2PduMapIndex is a valid value.                          */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | uint16                                                   */
/*               |      0x0000~0xFFFFU : PduMapIndex Value                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint16, DCM_CODE) Dcm_Dsl_TxAbt_GetSrcPduMapIndex
(
    const uint16 u2PduMapIndex
)
{
    return Dcm_Dsl_Ctrl_GetResUseId(u2PduMapIndex);
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetNumOfConcurrentTx                       */
/* Description   | Get the number of concurrent transmissions(top half).    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               |      0x00~0xFFU : number of concurrent transmissions     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetNumOfConcurrentTx
(void)
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;
    uint8  u1_Retval;
    uint8  u1_TxState;

    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;
    u1_Retval       = (uint8)0U;

    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        u1_TxState = Dcm_Dsl_u1TxState[u2_ClientCnt];
        if( ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4 )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_PAGE_UPDATE )
         || ( u1_TxState == DCM_DSL_TXST_WT_TX_COMP_LAST ) )
        {
            u1_Retval = u1_Retval + (uint8)1U;
        }
    }

    return u1_Retval;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Abort                                      */
/* Description   | This function aborts Dsl Subcomponent processing.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Abort
(void)
{
    Dcm_Dsl_TxAbt_Init();
    Dcm_Dsl_TxMsg_Abort();
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetTxState                                 */
/* Description   | This function gets a Tx state.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |      Tx State  : DCM_DSL_TXST_IDLE                       */
/*               |                : DCM_DSL_TXST_WT_SV_COMP                 */
/*               |                : DCM_DSL_TXST_WT_SV_COMP_P2MINTO         */
/*               |                : DCM_DSL_TXST_WT_TX_RCRRP                */
/*               |                : DCM_DSL_TXST_WT_TX_LAST                 */
/*               |                : DCM_DSL_TXST_WT_TX_LAST_P4              */
/*               |                : DCM_DSL_TXST_WT_CL_SV_COMP              */
/*               |                : DCM_DSL_TXST_WT_CL_TX                   */
/*               |                : DCM_DSL_TXST_WT_CL_TXERR                */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP              */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP_ABT          */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4       */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_LAST            */
/*               |                : DCM_DSL_TXST_WT_TX_PAGE_UPDATE          */
/*               |                : DCM_DSL_TXST_WT_COMP_LAST               */
/* Notes         |  -                                                       */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetTxState
(
    const uint16 u2PduMapIndex
)
{
    uint8 u1_Result;

    /* lock */
    SchM_Enter_Dcm_Dsl_TxPduInfo();

    /* Get Tx State */
    u1_Result = Dcm_Dsl_u1TxState[Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex];

    /* unlock */
    SchM_Exit_Dcm_Dsl_TxPduInfo();

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetTxState                                 */
/* Description   | This function sets a Tx state.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TxState : DCM_DSL_TXST_IDLE                       */
/*               |                : DCM_DSL_TXST_WT_SV_COMP                 */
/*               |                : DCM_DSL_TXST_WT_SV_COMP_P2MINTO         */
/*               |                : DCM_DSL_TXST_WT_TX_RCRRP                */
/*               |                : DCM_DSL_TXST_WT_TX_LAST                 */
/*               |                : DCM_DSL_TXST_WT_TX_LAST_P4              */
/*               |                : DCM_DSL_TXST_WT_CL_SV_COMP              */
/*               |                : DCM_DSL_TXST_WT_CL_TX                   */
/*               |                : DCM_DSL_TXST_WT_CL_TXERR                */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP              */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP_ABT          */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4       */
/*               |                : DCM_DSL_TXST_WT_TX_COMP_LAST            */
/*               |                : DCM_DSL_TXST_WT_TX_PAGE_UPDATE          */
/*               |                : DCM_DSL_TXST_WT_COMP_LAST               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxState
(
    const uint16 u2PduMapIndex,
    const uint8  u1TxState
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_TxPduInfo();

    /* Set Tx State */
    Dcm_Dsl_u1TxState[Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex] = u1TxState;

    /* unlock */
    SchM_Exit_Dcm_Dsl_TxPduInfo();

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Clear                                      */
/* Description   | This function initializes TxClient.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Clear
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_ClientIndex;
    boolean b_InteractiveClient;

    u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);

    Dcm_Dsl_stTxClientBuf[u2_ClientIndex].u1TxNrc[0] = (uint8)0U;

    Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf.SduStartAddr = NULL_PTR;
    Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf.SduPos       = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf.SduLength    = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_TxClient[u2_ClientIndex].u2RetryCnt           = (uint16)0U;

    Dcm_Dsl_TxAbt_Initq(&Dcm_Dsl_TxClient[u2_ClientIndex].stTxq, u2_ClientIndex);

    Dcm_Dsl_stNegMsgHead[u2_ClientIndex].stTxPduInfo.SduDataPtr = &Dcm_Dsl_stTxClientBuf[u2_ClientIndex].u1TxNrc[0];
    Dcm_Dsl_stNegMsgHead[u2_ClientIndex].stTxPduInfo.SduLength  = DCM_DSL_NEG_RESPONSE_SIZE;
    Dcm_Dsl_stNegMsgHead[u2_ClientIndex].u1ResponseKind         = DCM_DSL_SET_NEGATIVE_RESPONSE;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        Dcm_Dsl_u1NrcPending[0] = (uint8)0U;

        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].stTxPduInfo.SduDataPtr        = Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf.SduStartAddr;
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].stTxPduInfo.SduLength         = Dcm_Dsl_TxClient[u2_ClientIndex].stTxBuf.SduLength;
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXBUF].u1ResponseKind                = DCM_DSL_SET_POSITIVE_RESPONSE;

        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].stTxPduInfo.SduDataPtr = &Dcm_Dsl_u1NrcPending[0];
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].stTxPduInfo.SduLength  = DCM_DSL_NEG_RESPONSE_SIZE;
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNRCPENDING].u1ResponseKind         = DCM_DSL_SET_PENDING_RESPONSE;

        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].stTxPduInfo.SduDataPtr     = NULL_PTR;
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].stTxPduInfo.SduLength      = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_stTxMsgHead[DCM_DSL_BUFID_TXNORESP].u1ResponseKind             = DCM_DSL_SET_NO_RESPONSE_NEG;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetTxClient                                */
/* Description   | This function acquires the address of the response       */
/*               | sending buffer.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | Dcm_Dsl_TxClientType *                                   */
/*               |   DataPointer : Address of the response sending buffer   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxClientType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxClient
(
    const uint16 u2PduMapIndex
)
{
    uint16   u2_ClientIndex;
    u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);
    return &Dcm_Dsl_TxClient[u2_ClientIndex];
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetTxPduInfo                               */
/* Description   | This function sets information of the designated sending */
/*               | buffer to the response sending buffer area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptTxClient : Response sending buffer address    */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxPduInfo
(
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) ptTxClient
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;

    pt_Msg = Dcm_Dsl_TxAbt_GetPeekq(&ptTxClient->stTxq);
    if( pt_Msg != NULL_PTR )
    {
        ptTxClient->stTxBuf.SduStartAddr = pt_Msg->stTxPduInfo.SduDataPtr;
        ptTxClient->stTxBuf.SduPos       = (AB_83_DcmPduLengthType)0U;
        ptTxClient->stTxBuf.SduLength    = pt_Msg->stTxPduInfo.SduLength;
    }
    else
    {
        ptTxClient->stTxBuf.SduStartAddr = NULL_PTR;
        ptTxClient->stTxBuf.SduPos       = (AB_83_DcmPduLengthType)0U;
        ptTxClient->stTxBuf.SduLength    = (AB_83_DcmPduLengthType)0U;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetTxNRCData                               */
/* Description   | This function makes a negative acknowledge message.      */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptSduData   : Address of the sending buffer        */
/*               |                                                          */
/*               | [in] u1SID        : Service ID                           */
/*               |                                                          */
/*               | [in] u1ErrorCode  : Error code(NRC)                      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetTxNRCData
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptSduData,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    ptSduData[0]                   = DCM_DSL_SID_TX_NRC;
    ptSduData[DCM_DSL_NEG_SID]     = u1SID;
    ptSduData[DCM_DSL_ERROR_INDEX] = u1ErrorCode;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CreRcrrpMsg                                */
/* Description   | This function creates an RCRRP message and stores it     */
/*               | in the transmission buffer.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : SID                                 */
/*               |                                                          */
/* Return Value  | AB_83_DcmPduInfoType *                                   */
/*               |   DataPointer : There is an outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(AB_83_DcmPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_CreRcrrpMsg
(
    const uint16 u2PduMapIndex,
    const uint8  u1SID
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;

    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    pt_Msg       = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRCPENDING);

    Dcm_Dsl_TxAbt_SetTxNRCData(&Dcm_Dsl_u1NrcPending[0], u1SID,
                             DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_Dsl_TxAbt_Enq(&pt_TxClient->stTxq, pt_Msg);
    Dcm_Dsl_TxAbt_SetTxPduInfo(pt_TxClient);

    return &pt_Msg->stTxPduInfo;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetTxBufById                               */
/* Description   | This function acquires the address of the buffer         */
/*               | with designation sending buffer ID.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1BufId       : Sending buffer ID                   */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_TxMsgNodeType *                                  */
/*               |   DataPointer : Address of the response sending buffer   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxBufById
(
    const uint16 u2PduMapIndex,
    const uint8  u1BufId
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_RetVal;
    uint16                 u2_ClientIndex;

    if( u1BufId == DCM_DSL_BUFID_TXNRC )
    {
        u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);
        pt_RetVal      = &Dcm_Dsl_stNegMsgHead[u2_ClientIndex];
    }
    else
    {
        pt_RetVal = &Dcm_Dsl_stTxMsgHead[u1BufId];
    }
    return pt_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Transmit                                   */
/* Description   | This function sends response message                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo    : Length and pointer to the buffer of     */
/*               |                  the I-PDU.                              */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/*               |   DCM_DSL_TX_E_DISABLE  : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_Transmit
(
    const uint16                                         u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType                    u1ResponseKind
)
{
    Std_ReturnType              u1_Result;
    Std_ReturnType              u1_Retval;
    Std_ReturnType              u1_TxResult;
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;
    boolean                     b_TxConf;
    boolean                     b_P2ServerMaxElapsed;

    b_TxConf       = (boolean)FALSE;
    u1_TxResult    = (Std_ReturnType)E_NOT_OK;
    u1_Retval      = (Std_ReturnType)E_OK;

    u1_Result = Dcm_Dsl_TxMsg_Transmit(u2PduMapIndex, ptInfo, u1ResponseKind);
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        /* no process */
    }
    else if( u1_Result == DCM_DSL_TX_E_DISABLE )
    {
        b_P2ServerMaxElapsed = Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed();
        if( b_P2ServerMaxElapsed == (boolean)TRUE )
        {
            b_TxConf = (boolean)TRUE;
            Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
            Dcm_Dsl_Ctrl_StopTxTimers();
        }
        else
        {
            u1_Retval = (Std_ReturnType)DCM_DSL_TX_E_DISABLE;
        }
    }
    else /* DCM_DSL_TX_E_SEND_ERR, DCM_DSL_TX_E_NORESP, (Not DCM_DSL_TX_E_SUPPRES) */
    {
        b_TxConf = (boolean)TRUE;

        if( u1_Result == DCM_DSL_TX_E_NORESP )
        {
            u1_TxResult = (Std_ReturnType)E_OK;

            if( ( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_POS )
             || ( u1ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE ) )
            {
                Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)TRUE);
                Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg(u2PduMapIndex);
            }
            else
            {
                Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
            }
        }
        else if( u1_Result == DCM_DSL_TX_E_SEND_ERR )
        {
            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)FALSE);
        }
        else
        {
            Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        }
    }

    if( b_TxConf == (boolean)TRUE )
    {
        u1_ConfirmationStatus = Dcm_Dsl_TxAbt_GetConfStatus(u2PduMapIndex, u1_TxResult);
        Dcm_Dsl_TxAbt_NonAffirmation(u2PduMapIndex, u1_ConfirmationStatus);
        u1_Retval = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Retval;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Rcrrp_Transmit                             */
/* Description   | This function sends RCRRP.                               */
/*               | RCRRP : requestCorrectlyReceivedResponsePending          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo    : Length and pointer to the buffer of     */
/*               |                  the RCRRP.                              */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/*               |   DCM_DSL_TX_E_SEND_ERR : Transmission Error             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_Rcrrp_Transmit
(
    const uint16                                         u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    Std_ReturnType              u1_Result;
    Std_ReturnType              u1_RetVal;
    uint8                       u1_TxErrHdl;
    boolean                     b_TxConf;
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;

    u1_RetVal             = (Std_ReturnType)E_OK;
    b_TxConf              = (boolean)FALSE;
    u1_ConfirmationStatus = DCM_RES_NEG_NOT_OK;
    pt_TxClient           = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);

    u1_Result = Dcm_Dsl_TxMsg_Transmit(u2PduMapIndex, ptInfo, DCM_DSL_SET_PENDING_RESPONSE);
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        Dcm_Dsl_Ctrl_SetResPendOccur((boolean)TRUE);
    }
    else if( u1_Result == DCM_DSL_TX_E_DISABLE )
    {
        /* Does not retransmit in NRC78 transmission */
        Dcm_Dsl_TxAbt_DelLatestMsg(pt_TxClient);
        b_TxConf = (boolean)TRUE;
    }
    else if( u1_Result == DCM_DSL_TX_E_SUPPRES )
    {
        Dcm_Dsl_TxAbt_DelLatestMsg(pt_TxClient);
        b_TxConf              = (boolean)TRUE;
        u1_ConfirmationStatus = DCM_RES_NEG_OK;
    }
    else /* DCM_DSL_TX_E_SEND_ERR, (Not DCM_DSL_TX_E_NORESP) */
    {
        Dcm_Dsl_TxAbt_DelLatestMsg(pt_TxClient);

        u1_TxErrHdl = Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)FALSE);
        if( ( u1_TxErrHdl == DCM_TXERR_SESCHG_DEFAULT )
         || ( u1_TxErrHdl == DCM_TXERR_DISCON ) )
        {
            /* DCM_M_TMRID_P4TIMER stop */
            Dcm_Dsl_Ctrl_StopTxTimers();
            Dcm_Dsl_Ctrl_CancelService();
            Dcm_Dsl_TxAbt_HandlTopHalfConfirmation(u2PduMapIndex);
            u1_RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            b_TxConf = (boolean)TRUE;
        }
    }

    if( b_TxConf == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_RcrrpErrNotification(u1_ConfirmationStatus);
        u1_RetVal = (Std_ReturnType)DCM_DSL_TX_E_SEND_ERR;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_BusyResTransmit                            */
/* Description   | This function sends response message                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo    : Length and pointer to the buffer of     */
/*               |                  the I-PDU.                              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/*               |   DCM_DSL_TX_E_DISABLE  : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_BusyResTransmit
(
    const uint16                                         u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) pt_TxClient;
    Std_ReturnType              u1_Result;
    Std_ReturnType              u1_RetVal;
    boolean                     b_TxConf;

    u1_RetVal    = (Std_ReturnType)E_OK;
    b_TxConf     = (boolean)FALSE;
    pt_TxClient  = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);

    u1_Result = Dcm_Dsl_TxMsg_NegResTransmit(u2PduMapIndex, ptInfo);
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        /* no process */
    }
    else if( u1_Result == DCM_DSL_TX_E_DISABLE )
    {
        if( pt_TxClient->u2RetryCnt == (uint16)0U )
        {
            b_TxConf = (boolean)TRUE;
        }
        else
        {
            u1_RetVal = (Std_ReturnType)DCM_DSL_TX_E_DISABLE;
        }
    }
    else /* DCM_DSL_TX_E_SUPPRES, DCM_DSL_TX_E_SEND_ERR, (Not DCM_DSL_TX_E_NORESP) */
    {
        b_TxConf = (boolean)TRUE;
    }

    if( b_TxConf == (boolean)TRUE )
    {
        Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify(u2PduMapIndex);
        u1_RetVal = (Std_ReturnType)E_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_P4TO_Transmit                              */
/* Description   | This function sends generalReject.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo    : Length and pointer to the buffer of     */
/*               |                  the I-PDU.                              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_P4TO_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    Std_ReturnType  u1_Retval;
    Std_ReturnType  u1_Result;
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;

    u1_Retval       = (Std_ReturnType)E_OK;
    u1_ResponseKind = DCM_DSL_SET_NONE_RESPONSE;

    /* Return value ignoring */
    (void)Dcm_Dsl_TxAbt_GetTxReservMsg(u2PduMapIndex, &u1_ResponseKind);
    /* Convert the acquired response kind */
    if( u1_ResponseKind == DCM_DSL_SET_NEGATIVE_RESPONSE )
    {
        /* Send a negative response for P4Timeout */
        u1_Result = Dcm_Dsl_TxMsg_Transmit(u2PduMapIndex, ptInfo, DCM_DSL_SET_P4TO_NEG_RESPONSE);
    }
    else
    {
        /* Suppress to send of negative response */
        u1_Result = Dcm_Dsl_TxMsg_Transmit(u2PduMapIndex, ptInfo, DCM_DSL_SET_NO_RESPONSE_NEG);
    }

    if( u1_Result == (Std_ReturnType)E_OK )
    {
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)TRUE);
    }
    else if( u1_Result == DCM_DSL_TX_E_SUPPRES )
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_TxAbt_NonAffirmation(u2PduMapIndex, DCM_RES_NEG_OK);
        u1_Retval = (Std_ReturnType)E_NOT_OK;
    }
    else /* DCM_DSL_TX_E_SEND_ERR, DCM_DSL_TX_E_DISABLE, DCM_DSL_TX_E_NORESP */
    {
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_TxAbt_NonAffirmation(u2PduMapIndex, DCM_RES_NEG_NOT_OK);
        u1_Retval = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Retval;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandlTopHalfConfirmation                   */
/* Description   | This function performs a sending completion notice       */
/*               | (top half) of the final response.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfConfirmation
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
    Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandlRcrrpConfirmation                     */
/* Description   | This function performs sending completion notice         */
/*               | handling of RCRRP (top half)                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1Result  : Result of the transmission of the       */
/*               |                  I-PDU.                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : failure                            */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_HandlRcrrpConfirmation
(
    const uint16 u2PduMapIndex,
    const Std_ReturnType u1Result
)
{
    uint8          u1_TxErrHdl;
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    if( u1Result != (Std_ReturnType)E_OK )
    {
        u1_TxErrHdl = Dcm_Dsl_Ctrl_ReqTxErrHandling(u2PduMapIndex, (boolean)TRUE);
        if( ( u1_TxErrHdl == DCM_TXERR_SESCHG_DEFAULT )
         || ( u1_TxErrHdl == DCM_TXERR_DISCON ) )
        {
            Dcm_Dsl_Ctrl_StopTxTimers();
            Dcm_Dsl_Ctrl_RcrrpErrHandling(u2PduMapIndex);
            Dcm_Dsl_TxAbt_HandlTopHalfConfirmation(u2PduMapIndex);
            u1_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_NonAffirmation                             */
/* Description   | This function notifies transmission completion excluding */
/*               | ForceRCRRP.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1ConfirmationStatus : indicates the response       */
/*               |   transmission process has finished successfully or not. */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmation
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    Dcm_Dsl_TxAbt_HandleLastNonAffirmation(u2PduMapIndex, u1ConfirmationStatus);
    Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
    Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, DCM_RES_POS_OK);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_NonAffirmationNoSesUpdate                  */
/* Description   | This function notifies transmission completion           */
/*               | (No Session Update) excluding ForceRCRRP.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1ConfirmationStatus : indicates the response       */
/*               |   transmission process has finished successfully or not. */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmationNoSesUpdate
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
    Dcm_Dsl_TxAbt_NonAffirmation(u2PduMapIndex, u1ConfirmationStatus);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify                */
/* Description   | This function notifies transmission completion excluding */
/*               | ForceRCRRP.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NonAffirmationWithoutNotify
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
    Dcm_Dsl_TxAbt_Clear(u2PduMapIndex);
    Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, DCM_RES_POS_OK);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_HandleLastNonAffirmation                   */
/* Description   | This function notifies transmission completion excluding */
/*               | ForceRCRRP.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1ConfirmationStatus : indicates the response       */
/*               |   transmission process has finished successfully or not. */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandleLastNonAffirmation
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    boolean  b_DisableCancelService;
    uint8    u1_TxState;

    b_DisableCancelService = Dcm_Dsl_Ctrl_IsAcceptedFinalResp(u2PduMapIndex);

    u1_TxState = Dcm_Dsl_TxAbt_GetTxState(u2PduMapIndex);
    if( ( u1_TxState == DCM_DSL_TXST_IDLE )
     || ( u1_TxState == DCM_DSL_TXST_WT_COMP_LAST ) )
    {
        /* Service is not running, so do not cancel(specify TRUE). */
        b_DisableCancelService = (boolean)TRUE;
    }

    if( b_DisableCancelService == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1ConfirmationStatus, (boolean)FALSE);
    }
    else
    {
        Dcm_Dsl_Ctrl_CancelService();
        Dcm_Dsl_Ctrl_Confirmation(u2PduMapIndex);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetConfStatus                              */
/* Description   | This function gets ConfirmationStatus of response.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1Result : Result of the transmission of the I-PDU. */
/*               |                                                          */
/* Return Value  | Dcm_ConfirmationStatusType                               */
/*               |    DCM_RES_POS_OK     : Successful acknowledgment        */
/*               |    DCM_RES_POS_NOT_OK : Positive acknowledgment failure  */
/*               |    DCM_RES_NEG_OK     : Negative response success        */
/*               |    DCM_RES_NEG_NOT_OK : Negative response failure        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Dcm_ConfirmationStatusType, DCM_CODE) Dcm_Dsl_TxAbt_GetConfStatus
(
    const uint16         u2PduMapIndex,
    const Std_ReturnType u1Result
)
{
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;

    pt_TxClient = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);

    pt_Msg = Dcm_Dsl_TxAbt_GetPeekq(&pt_TxClient->stTxq);
    if( pt_Msg != NULL_PTR )
    {
        u1_ResponseKind = pt_Msg->u1ResponseKind;
    }
    else
    {
        u1_ResponseKind = DCM_DSL_SET_NONE_RESPONSE;
    }
    u1_ConfirmationStatus = Dcm_Dsl_TxAbt_CnvConfStatus(u1_ResponseKind, u1Result);

    return u1_ConfirmationStatus;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_CnvConfStatus                              */
/* Description   | This function gets ConfirmationStatus of response.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/*               | [in] u1Result : Result of the transmission of the I-PDU. */
/*               |                                                          */
/* Return Value  | Dcm_ConfirmationStatusType                               */
/*               |    DCM_RES_POS_OK     : Successful acknowledgment        */
/*               |    DCM_RES_POS_NOT_OK : Positive acknowledgment failure  */
/*               |    DCM_RES_NEG_OK     : Negative response success        */
/*               |    DCM_RES_NEG_NOT_OK : Negative response failure        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Dcm_ConfirmationStatusType, DCM_CODE) Dcm_Dsl_TxAbt_CnvConfStatus
(
    const Dcm_Dsl_ResponseSettingType u1ResponseKind,
    const Std_ReturnType u1Result
)
{
    Dcm_ConfirmationStatusType u1_ConfirmationStatus;

    if( u1ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE )
    {
        if( u1Result == (Std_ReturnType)E_OK )
        {
            u1_ConfirmationStatus = DCM_RES_POS_OK;
        }
        else
        {
            u1_ConfirmationStatus = DCM_RES_POS_NOT_OK;
        }
    }
    else if( u1ResponseKind == DCM_DSL_SET_NEGATIVE_RESPONSE )
    {
        if( u1Result == (Std_ReturnType)E_OK )
        {
            u1_ConfirmationStatus = DCM_RES_NEG_OK;
        }
        else
        {
            u1_ConfirmationStatus = DCM_RES_NEG_NOT_OK;
        }
    }
    else if( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_POS )
    {
        u1_ConfirmationStatus = DCM_RES_POS_OK;
    }
    else
    {
        u1_ConfirmationStatus = DCM_RES_NEG_OK;
    }

    return u1_ConfirmationStatus;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetP4TOMsg                                 */
/* Description   | This function prepares a response message for P4 timeout */
/*               | occurrence.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : Service ID                          */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_TxMsgNodeType *                                  */
/*               |   DataPointer : Address of the response sending buffer   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_SetP4TOMsg
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    uint16  u2_ClientIndex;
    boolean b_SuppressResponse;

    b_SuppressResponse = Dcm_Dsl_Ctrl_IsSuppressNegMsg(u2PduMapIndex, u1SID, DCM_E_GENERALREJECT);
    if( b_SuppressResponse == (boolean)TRUE )
    {
        pt_Msg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNORESP);
    }
    else
    {
        pt_Msg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);
        u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);
        Dcm_Dsl_TxAbt_SetTxNRCData(&Dcm_Dsl_stTxClientBuf[u2_ClientIndex].u1TxNrc[0], u1SID, DCM_E_GENERALREJECT);
    }

    return pt_Msg;
}

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_SetNoticeMsg4P4TO                          */
/* Description   | This function prepares a response message for P4 timeout */
/*               | occurrence.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1SID         : Service ID                          */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_TxMsgNodeType *                                  */
/*               |   DataPointer : Address of the response sending buffer   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_SetNoticeMsg4P4TO
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    uint16  u2_ClientIndex;
    boolean b_SuppressResponse;

    b_SuppressResponse = Dcm_Dsl_Ctrl_IsSuppressNegMsg(u2PduMapIndex, u1SID, DCM_E_GENERALREJECT);
    if( b_SuppressResponse == (boolean)TRUE )
    {
        pt_Msg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);
        u2_ClientIndex = Dcm_Dsl_Ctrl_ConvPMIdxToClientIdx(u2PduMapIndex);
        Dcm_Dsl_TxAbt_SetTxNRCData(&Dcm_Dsl_stTxClientBuf[u2_ClientIndex].u1TxNrc[0], u1SID, DCM_E_GENERALREJECT);
    }
    else
    {
        pt_Msg = Dcm_Dsl_TxAbt_GetTxBufById(u2PduMapIndex, DCM_DSL_BUFID_TXNRC);
    }

    return pt_Msg;
}
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetTxReservMsg                             */
/* Description   | This function acquires the message information of the    */
/*               | sending appointment.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex   : PduMapIndex Value                 */
/*               |                                                          */
/*               | [out] ptResponseKind : Response kind                     */
/*               |                                                          */
/* Return Value  | Dcm_TxPduInfoType *                                      */
/*               |   DataPointer : There is an outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_TxPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxReservMsg
(
    const uint16                                                 u2PduMapIndex,
    P2VAR(Dcm_Dsl_ResponseSettingType, AUTOMATIC, DCM_APPL_DATA) ptResponseKind
)
{
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA)  pt_TxClient;
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Msg;
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA)     pt_Result;

    pt_TxClient = Dcm_Dsl_TxAbt_GetTxClient(u2PduMapIndex);
    pt_Result     = NULL_PTR;

    pt_Msg = Dcm_Dsl_TxAbt_GetPeekq(&pt_TxClient->stTxq);
    if( pt_Msg != NULL_PTR )
    {
        pt_TxClient->stTxBuf.SduStartAddr = pt_Msg->stTxPduInfo.SduDataPtr;
        pt_TxClient->stTxBuf.SduPos       = (AB_83_DcmPduLengthType)0U;
        pt_TxClient->stTxBuf.SduLength    = pt_Msg->stTxPduInfo.SduLength;
        *ptResponseKind                   = pt_Msg->u1ResponseKind;
        pt_Result                         = &pt_TxClient->stTxBuf;
    }
    else
    {
        *ptResponseKind = DCM_DSL_SET_NONE_RESPONSE;
    }

    return pt_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_RepLastMsg                                 */
/* Description   | This function replaces first message with a designation  */
/*               | message.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptTxq         : Sending queue                       */
/*               |                                                          */
/*               | [in] ptLastMsg     : Outbound last message               */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_RepLastMsg
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptTxq,
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) ptLastMsg
)
{
    /* Get First msg and leave msg */
    (void)Dcm_Dsl_TxAbt_Deq(ptTxq);

    Dcm_Dsl_TxAbt_Enq(ptTxq, ptLastMsg);

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_DelLatestMsg                               */
/* Description   | This function deletes the latest outbound message        */
/*               | information                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptTxClient         : TxClient Sending queue         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_DelLatestMsg
(
    P2VAR(Dcm_Dsl_TxClientType, AUTOMATIC, DCM_APPL_DATA) ptTxClient
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_TxPduInfo();

    /* Return value ignoring */
    (void)Dcm_Dsl_TxAbt_Deq(&ptTxClient->stTxq);
    Dcm_Dsl_TxAbt_SetTxPduInfo(ptTxClient);

    /* unlock */
    SchM_Exit_Dcm_Dsl_TxPduInfo();

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Initq                                      */
/* Description   | This function initializes sending queue.                 */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptQueue      :  Sending queue                      */
/*               |                                                          */
/*               | [in] u2ClientIndex :  client index                       */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Initq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue,
    const uint16                                       u2ClientIndex
)
{
    ptQueue->ptTail                         = &Dcm_Dsl_stTxMsgQueueHead[u2ClientIndex];
    ptQueue->ptHead                         = ptQueue->ptTail;
    ptQueue->ptHead->ptNext                 = NULL_PTR;
    ptQueue->ptHead->u1ResponseKind         = (Dcm_Dsl_ResponseSettingType)0U;
    ptQueue->ptHead->stTxPduInfo.SduDataPtr = NULL_PTR;
    ptQueue->ptHead->stTxPduInfo.SduLength  = (AB_83_DcmPduLengthType)0U;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Enq                                        */
/* Description   | This function adds a message to sending queue.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptQueue     : Sending queue                         */
/*               |                                                          */
/*               | [in/out] ptNode  : Outbound message                      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Enq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue,
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) ptNode
)
{
    ptQueue->ptTail->ptNext = ptNode;
    ptQueue->ptTail         = ptQueue->ptTail->ptNext;
    ptQueue->ptTail->ptNext = NULL_PTR;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_Deq                                        */
/* Description   | This function picks up a message from sending queue.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptQueue :        Sending queue                      */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_TxMsgNodeType *                                  */
/*               |   DataPointer : There is an outbound message             */
/*               |   NULL_PTR    : There is no outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_Deq
(
    P2VAR(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Result;

    pt_Result = NULL_PTR;

    if( ( ptQueue != NULL_PTR )
     && ( ptQueue->ptHead != NULL_PTR )
     && ( ptQueue->ptHead->ptNext != NULL_PTR ) )
    {
        pt_Result               = ptQueue->ptHead->ptNext;
        ptQueue->ptHead->ptNext = pt_Result->ptNext;

        if( ptQueue->ptHead->ptNext == NULL_PTR )
        {
            ptQueue->ptTail = ptQueue->ptHead;
        }
    }

    return pt_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxAbt_GetPeekq                                   */
/* Description   | This function refers to a head message of the sending    */
/*               | queue.                                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptQueue :        Sending queue                      */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_TxMsgNodeType *                                  */
/*               |   DataPointer : There is an outbound message             */
/*               |   NULL_PTR    : There is no outbound message             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2VAR(Dcm_Dsl_TxMsgNodeType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetPeekq
(
    P2CONST(Dcm_Dsl_QueueType, AUTOMATIC, DCM_APPL_DATA) ptQueue
)
{
    P2VAR(Dcm_Dsl_TxMsgNodeType, AUTOMATIC, DCM_APPL_DATA) pt_Result;

    pt_Result = NULL_PTR;

    if( ( ptQueue != NULL_PTR )
     && ( ptQueue->ptHead != NULL_PTR )
     && ( ptQueue->ptHead->ptNext != NULL_PTR ) )
    {
        pt_Result = ptQueue->ptHead->ptNext;
    }

    return pt_Result;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
