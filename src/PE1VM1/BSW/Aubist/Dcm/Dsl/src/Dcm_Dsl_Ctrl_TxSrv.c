/* Dcm_Dsl_Ctrl_TxSrv_c(v5-8-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Ctrl/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"

#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_TxIf.h"

#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"

#include <Dcm/Dcm_Dsd_SendMng.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_ROE_INTERMEDIATE_RESP_BUFSIZE ((uint8)0x10U)

/* Cs If Status */
#define DCM_DSL_TXIFST_IDLE                   ((uint8)0x01U)   /* Idle          */
#define DCM_DSL_TXIFST_SENDING                ((uint8)0x03U)   /* Sending       */
#define DCM_DSL_TXIFST_SENDCMP                ((uint8)0x10U)   /* Send Complete */
#define DCM_DSL_TXIFST_SENDERR                ((uint8)0x11U)   /* Send Error    */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure to store P2Server */
typedef struct {
    uint16 u2P2StarServer;                                                  /* P2*Server Value               */
    uint16 u2P2StarServerMin;                                               /* P2*ServerMin Value            */
    uint8  u1NumRespPend;                                                   /* Number of negative responses with response code 0x78 */
} Dcm_Dsl_P2ServerStoredType;

/* Type of Sending completion notice data */
typedef struct {
    uint16                      u2PduMapIndexOfSent;                        /* PduMapIndex of Confirmation    */
    Dcm_ConfirmationStatusType  u1ConfirmationStatus;                       /* ConfirmationStatus of response */
    boolean                     bSendForcedPending;                         /* FORCE_RCRRP sending flag       */
} Dcm_Dsl_ConfirmationType;

/* Structure to TxId Queue */
typedef struct {
    uint16 u2Queue[DCM_DSL_CLIENT_NUM];
    volatile uint16 u2ReadPos;
    volatile uint16 u2WritePos;
} Dcm_Dsl_TxIdQueueType;

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/* struct Dcm_Dsl_TxIfType */
typedef struct {
    uint8                 u1TxIfStatus;                       /* Cs If Status                                 */
    uint16                u2RetryCnt;                         /* Number of retries allowed                    */
    AB_83_DcmPduInfoType  stTxBuf;                            /* Sending buffer information                   */
} Dcm_Dsl_TxIfType;

/* struct Dcm_Dsl_TxIfMngType */
typedef struct {
    uint8                                  u1PeriodicIndex;   /* Periodic Connection index                 */
    P2VAR( Dcm_Dsl_TxIfType, TYPEDEF, DCM_APPL_DATA ) ptIf;   /* Start address of Dcm_Dsl_TxIfType array   */
} Dcm_Dsl_TxIfMngType;
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_GetAnalyzeReqMsgDirectly
( void );

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetAnalyzeReqMsgDirectly
(
    const boolean bAnalyze
);

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetNextTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptNextTxBuf,
    P2VAR( Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptCurTxBuf
);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_EnQueueTxID
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue,
    const uint16 u2PduMapIndex
);

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_DeQueueTxID
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue
);

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2Server
(
    const boolean bP2kind,
    const uint8 u1SesInfo
);

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2ServerMin
( void );

#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC( uint32, DCM_CODE ) Dcm_Dsl_Ctrl_GetP4Server
( void );
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetForceRcrrp
(
    const boolean bForceRcrrp
);

static FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsForceRcrrp
( void );

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed
(
    const boolean bP2ServerMaxElapsed
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpCompNotification
( void );

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CompleteWriting
( void );
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxRetryReq
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue,
    const uint16 u2PduMapIndex,
    const uint8 u1_EventId
);

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetDsdConfData
(
    P2VAR( Dcm_ConfirmationStatusType, AUTOMATIC, DCM_APPL_DATA ) ptConfirmationStatus,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptSendForcedPending
);

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxIdOfWaitingEvent
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventId
);

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_IfInit
( void );
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_RoeInit
( void );

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_RoeClear
( void );

static FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_Ctrl_JudgeStartOfRoe
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_PeriodicTxRetryReq
(
    const uint16 u2PduMapIndex,
    const uint8  u1PeriodicIndex
);

static FUNC_P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) Dcm_Dsl_Ctrl_GetPeriodicRef
(
    const uint16 u2PduMapIndex
);

#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/* NRC 0x78 sending detection flag */
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bDetectRcrrp;

/* PduR sending buffer */
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1TxBuf[DCM_DSL_TXBUF_MAXSIZE];

/* Flag to parse request message directly */
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bAnalyzeReqMsgDirectly;

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1NotifySwcMsgNum;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

/* Reserv TxId Queue */
static VAR( Dcm_Dsl_TxIdQueueType, DCM_VAR_NO_INIT ) Dcm_Dsl_stReservTxID;
/* Cancel TxId Queue */
static VAR( Dcm_Dsl_TxIdQueueType, DCM_VAR_NO_INIT ) Dcm_Dsl_stCancelTxID;

/* P2ServerMax elapsed flag */
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bP2ServerMaxElapsed;

/* FORCE_RCRRP sending flag */
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bForceRcrrp;

/* Latest ConfirmationStatus of response */
static VAR( Dcm_Dsl_ConfirmationType, DCM_VAR_NO_INIT ) Dcm_Dsl_stLatestConfirmationStatus;

/* P2Server related data */
static VAR( Dcm_Dsl_P2ServerStoredType, DCM_VAR_NO_INIT ) Dcm_Dsl_stP2StoredData;

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )

/* Periodic transmission management data */
static VAR( Dcm_Dsl_TxIfMngType, DCM_VAR_NO_INIT ) Dcm_Dsl_stTxIf[DCM_DSL_CLIENT_NUM];

static VAR( Dcm_Dsl_TxIfType, DCM_VAR_NO_INIT ) Dcm_Dsl_stTxIfArray[DCM_DSL_IFPDUID_NUM];

/* Periodic TxId Queue */
static VAR( Dcm_Dsl_TxIdQueueType, DCM_VAR_NO_INIT ) Dcm_Dsl_stPeriodicTxID;

#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#if( DCM_DSL_ROE_ENABLE == STD_ON )

static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bRoeInterRespBufferUsed;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1RoeInterRespBuf[DCM_DSL_ROE_INTERMEDIATE_RESP_BUFSIZE];

#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

static CONST(AB_83_ConstV uint16, DCM_CONST) Dcm_Dsl_u2TxIdQueueMax = DCM_DSL_CLIENT_NUM;

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_Init                                  */
/* Description   | This function initializes Dsl_Ctrl_TxSrv.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Init
( void )
{
    Dcm_Dsl_u1TxBuf[0]             = (uint8)0U;
    Dcm_Dsl_bDetectRcrrp           = (boolean)FALSE;
    Dcm_Dsl_bAnalyzeReqMsgDirectly = (boolean)FALSE;
    Dcm_Dsl_bP2ServerMaxElapsed    = (boolean)FALSE;
    Dcm_Dsl_bForceRcrrp            = (boolean)FALSE;

    Dcm_Dsl_stReservTxID.u2Queue[0] = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_stReservTxID.u2ReadPos  = (uint16)0U;
    Dcm_Dsl_stReservTxID.u2WritePos = (uint16)0U;

    Dcm_Dsl_stCancelTxID.u2Queue[0] = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_stCancelTxID.u2ReadPos  = (uint16)0U;
    Dcm_Dsl_stCancelTxID.u2WritePos = (uint16)0U;

    Dcm_Dsl_stLatestConfirmationStatus.u2PduMapIndexOfSent  = (uint16)0U;
    Dcm_Dsl_stLatestConfirmationStatus.u1ConfirmationStatus = DCM_RES_POS_OK;
    Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending   = (boolean)FALSE;

    Dcm_Dsl_stP2StoredData.u2P2StarServer    = (uint16)0U;
    Dcm_Dsl_stP2StoredData.u2P2StarServerMin = (uint16)0U;
#if( DCM_DSL_ROE_ENABLE == STD_ON )
    Dcm_Dsl_Ctrl_TxSrv_RoeInit();
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */
#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
    Dcm_Dsl_Ctrl_TxSrv_IfInit();
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    Dcm_Dsl_u1NotifySwcMsgNum = (uint8)0U;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_IfInit                                */
/* Description   | This function initializes Dsl_Ctrl_TxSrv.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_IfInit
( void )
{
    uint16 u2_IfMapIndex;
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;
    uint16 u2_PeriodicNumMax;

    u2_ClientNumMax   = Dcm_Dsl_u2ClientNum;
    u2_PeriodicNumMax = Dcm_Dsl_u2IfPduIdNum;

    Dcm_Dsl_stPeriodicTxID.u2Queue[0] = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_stPeriodicTxID.u2ReadPos  = (uint16)0U;
    Dcm_Dsl_stPeriodicTxID.u2WritePos = (uint16)0U;

    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        Dcm_Dsl_stTxIf[u2_ClientCnt].u1PeriodicIndex = 0U;
        Dcm_Dsl_stTxIf[u2_ClientCnt].ptIf            = NULL_PTR;
    }

    for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_PeriodicNumMax; u2_IfMapIndex++ )
    {
        Dcm_Dsl_stTxIfArray[u2_IfMapIndex].u1TxIfStatus       = DCM_DSL_TXIFST_IDLE;
        Dcm_Dsl_stTxIfArray[u2_IfMapIndex].stTxBuf.SduDataPtr = NULL_PTR;
        Dcm_Dsl_stTxIfArray[u2_IfMapIndex].stTxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_stTxIfArray[u2_IfMapIndex].u2RetryCnt         = (uint16)0U;
    }

    return;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_RoeInit                               */
/* Description   | This function initializes Dsl_Ctrl_TxSrv.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_RoeInit
( void )
{
    Dcm_Dsl_Ctrl_TxSrv_RoeClear();
    return;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_Clear                                 */
/* Description   | This function initializes Dsl_Ctrl_TxSrv.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Clear
(
    const uint16 u2PduMapIndex
)
{
    boolean b_InteractiveClient;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        Dcm_Dsl_u1TxBuf[0]                   = (uint8)0U;
        Dcm_Dsl_bDetectRcrrp                 = (boolean)FALSE;
        Dcm_Dsl_bForceRcrrp                  = (boolean)FALSE;
        Dcm_Dsl_bP2ServerMaxElapsed          = (boolean)FALSE;

#if( DCM_DSL_ROE_ENABLE == STD_ON )
        Dcm_Dsl_Ctrl_TxSrv_RoeClear();
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_RoeClear                              */
/* Description   | This function initializes Dsl_Ctrl_TxSrv.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_RoeClear
( void )
{
    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_u1RoeInterRespBuf[0]    = (uint8)0U;
    Dcm_Dsl_bRoeInterRespBufferUsed = (boolean)FALSE;

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxSrv_Refresh                               */
/* Description   | This function refresh unit data of Dcm_Dsl_TxSrv.        */
/* Preconditions | The user must exclude this access data.                  */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxSrv_Refresh
( void )
{
    P2VAR( volatile uint16, AUTOMATIC, DCM_APPL_DATA ) pt_TxIDReadPos;
    P2VAR( volatile uint16, AUTOMATIC, DCM_APPL_DATA ) pt_TxIDWritePos;
    uint16 u2_TxIDReadPos;
    uint16 u2_TxIDWritePos;

    pt_TxIDReadPos    = &Dcm_Dsl_stReservTxID.u2ReadPos;
    u2_TxIDReadPos    = *pt_TxIDReadPos;
    *pt_TxIDReadPos   = u2_TxIDReadPos;

    pt_TxIDWritePos   = &Dcm_Dsl_stReservTxID.u2WritePos;
    u2_TxIDWritePos   = *pt_TxIDWritePos;
    *pt_TxIDWritePos  = u2_TxIDWritePos;

    pt_TxIDReadPos    = &Dcm_Dsl_stCancelTxID.u2ReadPos;
    u2_TxIDReadPos    = *pt_TxIDReadPos;
    *pt_TxIDReadPos   = u2_TxIDReadPos;

    pt_TxIDWritePos   = &Dcm_Dsl_stCancelTxID.u2WritePos;
    u2_TxIDWritePos   = *pt_TxIDWritePos;
    *pt_TxIDWritePos  = u2_TxIDWritePos;

    return ;
}

/**********                Timer Handlers                          **********/
/****************************************************************************/
/* Function Name | Dcm_Dsl_P2TOCbk                                          */
/* Description   | Perform a process in the P2Server time out and           */
/*               | the P2*Server time out.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_P2TIMER                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_P2TOCbk
(
    const uint8 u1TimerId
)
{
    uint8              u1_DslState;
    uint8              u1_SID;
    uint16             u2_RxPduMapIndex;
    boolean            b_Transmit;

    b_Transmit       = (boolean)FALSE;
    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();
    u1_DslState      = Dcm_Dsl_Ctrl_GetDslState(u2_RxPduMapIndex);

    if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        if( Dcm_Dsl_stDiagResp[0].bP4Server == (boolean)TRUE )
        {
            if( Dcm_Dsl_stP2StoredData.u1NumRespPend >= Dcm_Dsl_stDiagResp[0].u1RespMaxNumRespPend )
            {
                Dcm_Dsl_P4TOCbk(u1TimerId);
            }
            else
            {
                b_Transmit = (boolean)TRUE;
            }
        }
        else
        {
            b_Transmit = (boolean)TRUE;
        }
    }
    else
    {
        Dcm_Dsl_Ctrl_Abort();
    }

    if( b_Transmit == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed((boolean)TRUE);
        u1_SID = Dcm_Dsd_GetSID();
        Dcm_Dsl_TxAbt_P2TO(u2_RxPduMapIndex, u1_SID);
    }

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_P2MinTOCbk                                       */
/* Description   | Perform a process in the P2*ServerMin time out.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_P2MINTIMER                  */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_P2MinTOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    uint8  u1_DslState;
    uint16 u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
    {
        Dcm_Dsl_TxAbt_P2MinTO(u2_PduMapIndex);
    }

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_P4TOCbk                                          */
/* Description   | Perform a process in the P4Server timeout.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_P4TIMER/DCM_M_TMRID_P2TIMER */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_P4TOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    AB_83_DcmPduInfoType  st_RxBuf;
    uint16                u2_RxPduMapIndex;
    uint8                 u1_DslState;
    uint8                 u1_SID;
    Std_ReturnType        u1_RetVal;
    boolean               b_AnalyzeReqMsgDirectly;

    st_RxBuf.SduDataPtr = NULL_PTR;
    st_RxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
    u2_RxPduMapIndex    = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_RxPduMapIndex);
    if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_SetDslState(u2_RxPduMapIndex, DCM_DSL_ST_SENDING);
        b_AnalyzeReqMsgDirectly = Dcm_Dsl_Ctrl_GetAnalyzeReqMsgDirectly();

        if( b_AnalyzeReqMsgDirectly == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_GetRxBuf(u2_RxPduMapIndex, &st_RxBuf);
            u1_SID = Dcm_Dsd_GetDirectSID(st_RxBuf.SduDataPtr);
            Dcm_Dsl_Ctrl_SetAnalyzeReqMsgDirectly((boolean)FALSE);
        }
        else
        {
            u1_SID = Dcm_Dsd_GetSID();
        }

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
        Dcm_Dsl_u1NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum + (uint8)1U;
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
        {
            Dcm_Dsd_CancelService();
        }

        /* To Cancel the Response Request After EcuReset */
        Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed((boolean)TRUE);

        /* For Force RCRRP of DCM_DSL_TXST_WT_SV_COMP_P2MINTO, Return value ignoring */
        (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY, (boolean)TRUE);

        u1_RetVal = Dcm_Dsl_TxAbt_P4TO(u2_RxPduMapIndex, u1_SID);
        if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }
    else
    {
        Dcm_Dsl_Ctrl_Abort();
    }

    return;

}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_PagedBufferTOCbk                                 */
/* Description   | This function performs a process in PagedBuffer time out.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_PAGEDBUFFERTIMER            */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_PagedBufferTOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    uint8                     u1_DslState;
    uint16                    u2_PduMapIndex;
    Dcm_Main_EvtDistr_RetType u1_EvtResult;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        u1_EvtResult = Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CANCELTXSERVICE, (boolean)TRUE);
        if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
        {
            /* Return value ignoring */
            (void)Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stCancelTxID);
        }

        Dcm_Dsd_CancelPagedBufferProcessing();
        Dcm_Dsl_TxAbt_CancelPagedBuffer(u2_PduMapIndex);
    }
    else if( ( u1_DslState == DCM_DSL_ST_IDLE )
          || ( u1_DslState == DCM_DSL_ST_RECEIVING )
          || ( u1_DslState == DCM_DSL_ST_WT_SVCOMP ) )
    {
        /* No process */
    }
    else
    {
        Dcm_Dsl_Ctrl_Abort();
    }
    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_RoeRetryTOCbk                                    */
/* Description   | Perform a process in the RetryTimer(P2Server) time out   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId :  DCM_M_TMRID_ROERETRY_TIMER             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_RoeRetryTOCbk
(
    const uint8 u1TimerId
)
{
    uint8              u1_DslState;
    uint16             u2_RxPduMapIndex;

    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();
    u1_DslState      = Dcm_Dsl_Ctrl_GetDslState(u2_RxPduMapIndex);

    if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed((boolean)TRUE);
    }

    return;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/**********                Event Handlers                          **********/

/****************************************************************************/
/* Function Name | Dcm_Dsl_CancelTxCancelServiceCbk                         */
/* Description   | Call function(Dcm_Dsd_CancelService)                     */
/*               | and function(Dcm_Dsl_TxAbt_CancelTransmit)               */
/*               | to cancel service and cancel transmission.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_CANCELTXSERVICE         */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_CancelTxCancelServiceCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint8    u1_DslState;
    uint16   u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stCancelTxID);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
        if( u1_DslState != DCM_DSL_ST_SENDING )
        {
            Dcm_Dsd_CancelService();
        }

        Dcm_Dsl_TxAbt_CancelTransmit(u2_PduMapIndex);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_DataConfFunctionalityCbk                         */
/* Description   | Notice to Dsd after Dcm_TpTxConfirmation.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_CONF_FUNCTIONALITY      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_DataConfFunctionalityCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint16  u2_PduMapIndex;
    uint8   u1_ConfirmationStatus;
    uint8   u1_DslState;
    boolean b_IsSendForcePending;

    u1_ConfirmationStatus = (uint8)0U;
    b_IsSendForcePending  = (boolean)FALSE;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetDsdConfData(&u1_ConfirmationStatus, &b_IsSendForcePending);

    if( b_IsSendForcePending != (boolean)TRUE )
    {
        Dcm_Dsl_TxAbt_Deactivate(u2_PduMapIndex);

        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

        if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
        {
            Dcm_Dsl_TxAbt_Activate(u2_PduMapIndex);
        }
    }

    Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg(u2_PduMapIndex);

    /* Return value ignoring */
    (void)Dcm_Dsd_DataConfirmationFunctionality(u1_ConfirmationStatus, b_IsSendForcePending);

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TransmitCbk                                      */
/* Description   | This function for the sending call back a latch          */
/*               | (final response).                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_TRANSMIT                */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_TransmitCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint16          u2_PduMapIndex;
    uint8           u1_DslState;
    Std_ReturnType  u1_RetVal;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stReservTxID);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
        if( u1_DslState == DCM_DSL_ST_SENDING )
        {
            u1_RetVal = Dcm_Dsl_TxAbt_TransmitReq(u2_PduMapIndex);
            if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stReservTxID, u2_PduMapIndex, DCM_M_EVTID_DSL_TXRETRY);
            }
        }
        else if( ( u1_DslState == DCM_DSL_ST_IDLE )
              || ( u1_DslState == DCM_DSL_ST_RECEIVING )
              || ( u1_DslState == DCM_DSL_ST_WT_SVCOMP ) )
        {
            /* No process */
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxRetryCbk                                       */
/* Description   | This function performs a retry of the sending            */
/*               | until P2ServerMax progress.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_TXRETRY                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_TxRetryCbk
(
    const uint8 u1EventId
)
{
    uint16          u2_PduMapIndex;
    uint8           u1_DslState;
    Std_ReturnType  u1_RetVal;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stReservTxID);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
        if( u1_DslState == DCM_DSL_ST_SENDING )
        {
            u1_RetVal = Dcm_Dsl_TxAbt_TxRetryReq(u2_PduMapIndex);
            if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stReservTxID, u2_PduMapIndex, u1EventId);
            }
        }
        else if( ( u1_DslState == DCM_DSL_ST_IDLE )
              || ( u1_DslState == DCM_DSL_ST_RECEIVING )
              || ( u1_DslState == DCM_DSL_ST_WT_SVCOMP ) )
        {
            /* No process */
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }

    return ;
}

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_PeriodicTxRetryCbk                               */
/* Description   | This function performs a retry of the sending            */
/*               | until P2ServerMax progress.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_TXIFRETRY               */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_PeriodicTxRetryCbk
(
    const uint8 u1EventId
)
{
    uint16          u2_IfPduMapIndex;
    uint16          u2_PduMapIndex;
    uint16          u2_ClientIndex;
    uint8           u1_TxIfStatus;
    Std_ReturnType  u1_RetVal;
    uint8           u1_PeriodicIndex;

    u2_IfPduMapIndex = Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stPeriodicTxID);
    if( u2_IfPduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u2_PduMapIndex     = Dcm_Dsl_IpduIdMapTable[u2_IfPduMapIndex].u2PduMapIndex;
        u1_PeriodicIndex   = Dcm_Dsl_IpduIdMapTable[u2_IfPduMapIndex].u1TxIfIndex;
        u2_ClientIndex     = Dcm_Dsl_IpduIdMapTable[u2_IfPduMapIndex].u2ClientIndex;

        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        u1_TxIfStatus = Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf[u1_PeriodicIndex].u1TxIfStatus;

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( u1_TxIfStatus == DCM_DSL_TXIFST_SENDING )
        {
            u1_RetVal = Dcm_Dsl_Ctrl_PeriodicTxRetryReq(u2_PduMapIndex, u1_PeriodicIndex);
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                /* no process */
            }
            else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stPeriodicTxID, u2_IfPduMapIndex, DCM_M_EVTID_DSL_TXIFRETRY);
            }
            else
            {
                /* lock */
                SchM_Enter_Dcm_Dsl_Ctrl();
                Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf[u1_PeriodicIndex].u1TxIfStatus = DCM_DSL_TXIFST_SENDERR;
                /* unlock */
                SchM_Exit_Dcm_Dsl_Ctrl();
            }
        }
        else if( ( u1_TxIfStatus == DCM_DSL_TXIFST_IDLE )
              || ( u1_TxIfStatus == DCM_DSL_TXIFST_SENDCMP )
              || ( u1_TxIfStatus == DCM_DSL_TXIFST_SENDERR ) )
        {
            /* No process */
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }
    return ;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_RespReqAfterEcuResetCbk                          */
/* Description   | Perform condition establishment wait of the transmission */
/*               | of signals.                                              */
/*               | In addition, transmit a reply signal at the time of      */
/*               | condition establishment.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_RESPREQ_AFRST           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_RespReqAfterEcuResetCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint16                     u2_PduMapIndex;
    uint8                      u1_DslState;
    Std_ReturnType             u1_Result;
    Dcm_Main_EvtDistr_RetType  u1_EvtResult;
    boolean                    b_P2StarElapsed;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        b_P2StarElapsed = Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed();
        /* Check P2*Server TimeOut                                          */
        if( b_P2StarElapsed == (boolean)TRUE )
        {
            /* Release Resource                                             */
            Dcm_Dsl_TxAbt_CancelRespReq(u2_PduMapIndex);
        }
        else
        {
            u1_EvtResult = Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CANCELTXSERVICE, (boolean)TRUE);
            if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
            {
                /* Return value ignoring */
                (void)Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stCancelTxID);
            }

            /* Transmit a reply                                             */
            u1_Result = Dcm_Dsl_TxAbt_RespReqAfterEcuReset(u2_PduMapIndex);
            if( u1_Result == (Std_ReturnType)E_OK )
            {
                /* Transmission is complete */
            }
            else
            {
                /* Send Event DCM_M_EVTID_DSL_RESPREQ_AFRST. Return value ignoring */
                (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_RESPREQ_AFRST);
            }
        }
    }

    return;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */



#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_UpdatePageCbk                                    */
/* Description   | Notify Dsd of UpdatePage                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_PAGEDBUFFER             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_UpdatePageCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    P2VAR( Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA ) pt_CurTxBuf;
    AB_83_DcmPduInfoType        st_TxBuf;
    uint16                      u2_PduMapIndex;
    Std_ReturnType              u1_RetVal;
    uint8                       u1_DslState;
    Dcm_Main_EvtDistr_RetType   u1_EvtResult;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        st_TxBuf.SduDataPtr = NULL_PTR;
        st_TxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
        pt_CurTxBuf         = Dcm_Dsl_TxAbt_GetTxBuf(u2_PduMapIndex);

        Dcm_Dsl_Ctrl_GetNextTxBuf(&st_TxBuf, pt_CurTxBuf);

        u1_RetVal = Dcm_Dsd_UpdatePage((Dcm_MsgType)st_TxBuf.SduDataPtr, (Dcm_MsgLenType)st_TxBuf.SduLength);
        if( ( u1_RetVal == (Std_ReturnType)E_OK )
         || ( u1_RetVal == (Std_ReturnType)DCM_E_PENDING ) )
        {
            /* No process */
        }
        else
        {
            u1_EvtResult = Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CANCELTXSERVICE, (boolean)TRUE);
            if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
            {
                /* Return value ignoring */
                (void)Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stCancelTxID);
            }

            Dcm_Dsl_TxAbt_CancelPagedBuffer(u2_PduMapIndex);
        }
    }
    /* else case: Wait for PagedBuffer Timeout */

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RcrrpConfirmation                           */
/* Description   | This function notifies completion of RCRRP transmission. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpConfirmation
(
    const uint16 u2PduMapIndex
)
{
    boolean                     b_SendForcedPending;
    uint8                       u1_DslState;
    Dcm_Main_EvtDistr_RetType   u1_EvtResult;

    Dcm_Dsl_Ctrl_RcrrpCompNotification();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
    {
        b_SendForcedPending = Dcm_Dsl_Ctrl_IsForceRcrrp();
        if( b_SendForcedPending == (boolean)TRUE )
        {
            u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY);
            if( u1_EvtResult != DCM_MAIN_EVTDISTR_E_OK )
            {
                Dcm_Dsl_TxAbt_Abort();
            }
        }
        Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending = b_SendForcedPending;
    }
    else if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_TRANSMIT);
        if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
        {
            Dcm_Dsl_Ctrl_EnQueueTxID(&Dcm_Dsl_stReservTxID, u2PduMapIndex);
        }
        else
        {
            Dcm_Dsl_TxAbt_Abort();
        }
    }
    else
    {
        /* no process */
    }

    Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RcrrpErrHandling                            */
/* Description   | This function performs RCRRP error handling.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpErrHandling
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Main_EvtDistr_RetType u1_EvtResult;
    uint8                     u1_DslState;

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
    {
        Dcm_Dsl_Ctrl_EnQueueTxID(&Dcm_Dsl_stCancelTxID, u2PduMapIndex);
        u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_CANCELTXSERVICE);
        if( u1_EvtResult != DCM_MAIN_EVTDISTR_E_OK )
        {
            Dcm_Dsl_TxAbt_Abort();
        }
    }
    else if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY);
        if( u1_EvtResult != DCM_MAIN_EVTDISTR_E_OK )
        {
            Dcm_Dsl_TxAbt_Abort();
        }
    }
    else
    {
        /* no process */
    }

    Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RcrrpErrNotification                        */
/* Description   | This function notifies the start failure of RCRRP        */
/*               | transmission.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1ConfirmationStatus  : Confirmation Status         */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpErrNotification
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    boolean b_ForceRcrrp;

    Dcm_Dsl_Ctrl_RcrrpCompNotification();

    b_ForceRcrrp = Dcm_Dsl_Ctrl_IsForceRcrrp();
    if( b_ForceRcrrp == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);
        /* Return value ignoring */
        (void)Dcm_Dsl_Ctrl_DataConfFunctional(u1ConfirmationStatus, b_ForceRcrrp);
    }
    else
    {
        Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RcrrpCompNotification                       */
/* Description   | This function notifies completion of RCRRP transmission. */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RcrrpCompNotification
( void )
{
    uint16 u2_P2StarServer;
    uint16 u2_P2ServerMin;

    u2_P2ServerMin  = Dcm_Dsl_Ctrl_GetP2ServerMin();
    u2_P2StarServer = Dcm_Dsl_Ctrl_GetP2Server((boolean)TRUE, DCM_DSL_CURRENTSESSION);

    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_P2MINTIMER, (uint32)u2_P2ServerMin);
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_P2TIMER, (uint32)u2_P2StarServer);

    if( Dcm_Dsl_stP2StoredData.u1NumRespPend < Dcm_Dsl_stDiagResp[0].u1RespMaxNumRespPend )
    {
        Dcm_Dsl_stP2StoredData.u1NumRespPend++;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyServiceStart                          */
/* Description   | This function notifies the start of the service.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] bP2kind : P2Server kind   TRUE  P2*Server           */
/*               |                                FALSE P2Server            */
/*               | [in] u1SesInfo : Set Sesiion Information                 */
/*               |                                DCM_DSL_DEFAULTSESSION    */
/*               |                                DCM_DSL_CURRENTSESSION    */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyServiceStart
(
    const boolean bP2kind,
    const uint8 u1SesInfo
)
{
    uint32   u4_P2ServerMax;
    uint32   u4_ExtResTimer;
    uint16   u2_RxPduMapIndex;
    uint16   u2_RowIndex;
    uint16   u2_ConnectionIndex;
    uint16   u2_ProtocolRxIndex;
    uint8    u1_AddrType;
    boolean  b_ExtSuppressRspMsg;

    u4_P2ServerMax = Dcm_Dsl_Ctrl_GetP2Server(bP2kind, u1SesInfo);
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_P2TIMER, u4_P2ServerMax);

    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2_RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
    b_ExtSuppressRspMsg = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].bExtSuppressRspMsg;
    if( b_ExtSuppressRspMsg == (boolean)TRUE )
    {
        u1_AddrType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
        if( u1_AddrType == DCM_DSL_ADDINFO_FUNC )
        {
            u4_ExtResTimer = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u4ExtResTimeout;
            if( u4_ExtResTimer == (uint32)0U )
            {
                u4_ExtResTimer = (uint32)1U;
            }
            Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_P4TIMER, u4_ExtResTimer);
        }
    }

    return ;
}

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyServiceToResponseStart                */
/* Description   | This function notifies the start of the service.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyServiceToResponseStart
( void )
{
    uint32  u4_P4ServerMax;
    uint32  u4_P2ServerMax;

    u4_P2ServerMax = Dcm_Dsl_Ctrl_GetP2Server((boolean)FALSE, DCM_DSL_CURRENTSESSION);
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_ROERETRY_TIMER, u4_P2ServerMax);

    u4_P4ServerMax = Dcm_Dsl_Ctrl_GetP4Server();
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_P4TIMER, u4_P4ServerMax);

    return ;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyTxStart                               */
/* Description   | This function notifies the start of transmission of      */
/*               | the final response.                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxStart
( void )
{
    Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);
    Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);

    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2MINTIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P4TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_ROERETRY_TIMER);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyRcrrpTxStart                          */
/* Description   | This function notifies the start of RCRRP transmission.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyRcrrpTxStart
( void )
{
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2TIMER);
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyResult                                */
/* Description   | This function notifies the transmission result.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] bResult       : Request result                      */
/*               |                TRUE  : Success                           */
/*               |                FALSE : Failure                           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyResult
(
    const uint16 u2PduMapIndex,
    const boolean bResult
)
{
#if( DCM_AUTHENTICATION_USE == STD_ON )
    uint16  u2_ConnectionId;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    boolean b_ServiceToRespondTo;

    Dcm_Dsl_Ctrl_SetSesConf(bResult);

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)FALSE )
    {
#if( DCM_AUTHENTICATION_USE == STD_ON )
        u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
        Dcm_Dsl_Ctrl_SetAuthConf(u2_ConnectionId, bResult);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg                    */
/* Description   | This function notifies the user of the status change.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyCompletionOfStsChg
(
    const uint16 u2PduMapIndex
)
{
#if( DCM_AUTHENTICATION_USE == STD_ON )
    uint16  u2_ConnectionId;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    boolean b_ServiceToRespondTo;

    Dcm_Dsl_Ctrl_ReqSesCtrlChgNotification();

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)FALSE )
    {
#if( DCM_AUTHENTICATION_USE == STD_ON )
        u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
        Dcm_Dsl_Ctrl_ReqAuthStateChangeNotification(u2_ConnectionId);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyTxEnd                                 */
/* Description   | This function notifies the end of transmission of        */
/*               | the final response.                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxEnd
( void )
{
    Dcm_Main_EvtDistr_RetType  u1_EvtResult;

    u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY);
    if( u1_EvtResult != DCM_MAIN_EVTDISTR_E_OK )
    {
        Dcm_Dsl_TxAbt_Abort();
    }
    return ;
}

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ProvideDiagComData                          */
/* Description   | This function notifies DSD of Diag ComData.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] ptInfo        : Length and pointer to the buffer of */
/*               |                      the I-PDU.                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ProvideDiagComData
(
    const uint16 u2PduMapIndex,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptInfo,
    const uint8 u1ResponseKind
)
{
    Dcm_MsgContextType   st_MsgContext;
    AB_83_DcmPduInfoType st_RxBuf;
    uint16               u2_RowIndex;
    uint16               u2_ConnectionIndex;
    uint16               u2_ProtocolRxIndex;
    uint8                u1_NotifySwcMsgNum;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum;

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_NotifySwcMsgNum > (uint8)0U )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_u1NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum - (uint8)1U;

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_GetRxBuf(u2PduMapIndex, &st_RxBuf);
        if( st_RxBuf.SduDataPtr != NULL_PTR )
        {
            Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);

            st_MsgContext.resMaxDataLen      = (Dcm_MsgLenType)ptInfo->SduLength;
            st_MsgContext.dcmRxPduId         = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].RxPduId;
            st_MsgContext.msgAddInfo.reqType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;

            if( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_POS )
            {
                st_MsgContext.msgAddInfo.suppressPosResponse = STD_ON;
            }
            else
            {
                st_MsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
            }

            st_MsgContext.idContext  = st_RxBuf.SduDataPtr[DCM_DSL_POS_SID];
            st_MsgContext.reqData    = &st_RxBuf.SduDataPtr[0];
            st_MsgContext.reqDataLen = (Dcm_MsgLenType)st_RxBuf.SduLength;
            st_MsgContext.resData    = &ptInfo->SduDataPtr[0];
            st_MsgContext.resDataLen = (Dcm_MsgLenType)ptInfo->SduLength;

            Dcm_Dsd_ProvideDiagComData(&st_MsgContext, u1ResponseKind);
        }
    }

    return ;
}
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IfConfirmation                              */
/* Description   | The lower layer communication interface module confirms  */
/*               | the transmission of an I-PDU.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2IfPduMapIndex : I-PduMapIndex Value               */
/*               |                                                          */
/*               | [in] u1Result : E_OK     The PDU was transmitted.        */
/*               |                 E_NOT_OK Transmission of the PDU failed. */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_IfConfirmation
(
    const uint16         u2IfPduMapIndex,
    const Std_ReturnType u1Result
)
{
    uint8   u1_TxIfStatus;
    uint8   u1_PeriodicIndex;
    uint16  u2_ClientIndex;

    u1_PeriodicIndex   = Dcm_Dsl_IpduIdMapTable[u2IfPduMapIndex].u1TxIfIndex;
    u2_ClientIndex     = Dcm_Dsl_IpduIdMapTable[u2IfPduMapIndex].u2ClientIndex;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_TxIfStatus = Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf[u1_PeriodicIndex].u1TxIfStatus;

    if( u1_TxIfStatus == DCM_DSL_TXIFST_SENDING )
    {
        if( u1Result == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf[u1_PeriodicIndex].u1TxIfStatus = DCM_DSL_TXIFST_SENDCMP;
        }
        else
        {
            Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf[u1_PeriodicIndex].u1TxIfStatus = DCM_DSL_TXIFST_SENDERR;
        }
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IfTimeout                                   */
/* Description   | The lower layer communication interface module confirms  */
/*               | the transmission of an I-PDU.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_IfTimeout
(void)
{

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_stTxIf[0].ptIf[0].u1TxIfStatus = DCM_DSL_TXIFST_SENDERR;

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return ;
}
#endif /* DCM_DSL_PERIODICTX_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyTxCancel                              */
/* Description   | This function notifies the cancellation of transmission  */
/*               | processing.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1ConfirmationStatus : Confirmation Status          */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyTxCancel
(
    const uint16 u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    Dcm_Main_EvtDistr_RetType  u1_EvtResult;
    uint8                      u1_DslState;
    uint8                      u1_EventId;

    Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)FALSE);
    Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        u1_EventId = DCM_M_EVTID_DSL_CONF_FUNCTIONALITY;
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
        Dcm_Dsl_Ctrl_SetLatestConfData(u2PduMapIndex, u1ConfirmationStatus);
    }
    else
    {
        u1_EventId = DCM_M_EVTID_DSL_CANCELTXSERVICE;
        Dcm_Dsl_Ctrl_EnQueueTxID(&Dcm_Dsl_stCancelTxID, u2PduMapIndex);

        if( Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending == (boolean)TRUE )
        {
            /* For Force RCRRP of DCM_DSL_TXST_WT_SV_COMP_P2MINTO, Return value ignoring */
            (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY, (boolean)TRUE);
        }
    }

    u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(u1_EventId);
    if( u1_EvtResult != DCM_MAIN_EVTDISTR_E_OK )
    {
        Dcm_Dsl_TxAbt_Abort();
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReqErrHandling                              */
/* Description   | This function requests transmission error handling.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] bDelayUpdate  :                                     */
/*               |                TRUE  : Confirmation Reception timing     */
/*               |                FALSE : Immediate                         */
/* Return Value  | uint8                                                    */
/*               |   DCM_TXERR_SESCHG_DEFAULT : Default Session Transition  */
/*               |   DCM_TXERR_DISCON         : Disconnect                  */
/*               |   DCM_TXERR_END            : Other                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_ReqTxErrHandling
(
    const uint16 u2PduMapIndex,
    const boolean bDelayUpdate
)
{
    uint8   u1_TxErrHdl;
    uint16  u2_RowNum;
    uint16  u2_ConnectionIndex;
#if( DCM_AUTHENTICATION_USE == STD_ON )
    uint16  u2_ConnectionId;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST) pt_ProtocolTx;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowNum, &u2_ConnectionIndex);
    u1_TxErrHdl        = DCM_TXERR_END;
    pt_ProtocolTx      = Dcm_Dsl_stRow[u2_RowNum].ptConnection[u2_ConnectionIndex].ptMainConnection->ptProtocolTx;

    if( pt_ProtocolTx != NULL_PTR )
    {
        u1_TxErrHdl = pt_ProtocolTx->u1TxErrorHandling;
    }

    if( u1_TxErrHdl == DCM_TXERR_SESCHG_DEFAULT )
    {
        Dcm_Dsl_Ctrl_SetSesCtrlType(DCM_DEFAULT_SESSION, bDelayUpdate);
        Dcm_Dsl_Ctrl_SetSesConf((boolean)TRUE);

#if( DCM_AUTHENTICATION_USE == STD_ON )
        u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
        Dcm_Dsl_Ctrl_SetAuthConf(u2_ConnectionId, (boolean)FALSE);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    }
    else
    {
        Dcm_Dsl_Ctrl_NotifyResult(u2PduMapIndex, (boolean)FALSE);
    }
    return u1_TxErrHdl;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReqUpdatePage                               */
/* Description   | This function notifies the start of UpdatePage.          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : success                                   */
/*               |        FALSE : failure                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_ReqUpdatePage
( void )
{
    uint32                    u4_PagedBufferTimeoutVal;
    Dcm_Main_EvtDistr_RetType u1_EvtResult;
    boolean                   b_Result;

    b_Result = (boolean)TRUE;

    u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_PAGEDBUFFER);
    if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
    {
        u4_PagedBufferTimeoutVal = Dcm_M_TmrSrv_u2PagedBufferTimeout;
        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_PAGEDBUFFERTIMER, u4_PagedBufferTimeoutVal);
    }
    else
    {
        b_Result = (boolean)FALSE;
    }
    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_CompleteWriting                             */
/* Description   | This function notifies the end of UpdatePage.            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CompleteWriting
( void )
{
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_PAGEDBUFFERTIMER);
    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopTxTimers                                */
/* Description   | This function stops sending time register by a lump      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopTxTimers
( void )
{
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2MINTIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P4TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_ROERETRY_TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_PAGEDBUFFERTIMER);
    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopTxTimers
( void )
{
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2MINTIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P2TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_P4TIMER);
    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_ROERETRY_TIMER);
    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetTxBuf                                    */
/* Description   | Get a TxMsg Buffer Address/TxMsg Buffer MAX Length.      */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptTxBuf : TxMsg Buffer Address/TxMsg Length        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_SubConnectionType, AUTOMATIC, DCM_APPL_CONST ) pt_RoeConnection;
    uint16  u2_PduMapIndex;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;
    boolean b_ServiceToRespondTo;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2_PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        pt_RoeConnection    = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptRoeConnectionRef;
        ptTxBuf->SduDataPtr = &pt_RoeConnection->ptTxBuf[0];
    }
    else
    {
        ptTxBuf->SduDataPtr = &Dcm_Dsl_u1TxBuf[0];
    }
    ptTxBuf->SduLength  = (AB_83_DcmPduLengthType)Dcm_Dsl_stRow[u2_RowIndex].u2ProtocolMaximumResponseSize;

    return;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#if( DCM_DSL_ROE_ENABLE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
)
{
    uint16  u2_PduMapIndex;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    ptTxBuf->SduDataPtr = &Dcm_Dsl_u1TxBuf[0];
    ptTxBuf->SduLength  = (AB_83_DcmPduLengthType)Dcm_Dsl_stRow[u2_RowIndex].u2ProtocolMaximumResponseSize;

    return;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_OFF */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST ) pt_ProtocolTx;
    uint16  u2_PduMapIndex;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;
    boolean b_ServiceToRespondTo;

    u2_PduMapIndex       = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2_PduMapIndex);

    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_GetRoeTxBuf(u2_PduMapIndex, ptTxBuf);
    }
    else
    {
        Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
        pt_ProtocolTx = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
        ptTxBuf->SduDataPtr = &Dcm_Dsl_u1TxBuf[0];

        if( pt_ProtocolTx != NULL_PTR )
        {
            ptTxBuf->SduLength  = (AB_83_DcmPduLengthType)pt_ProtocolTx->u4TxBufSize;
        }
        else
        {
            ptTxBuf->SduLength = (AB_83_DcmPduLengthType)0U;
        }
    }

    return;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
#if( DCM_DSL_ROE_ENABLE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST ) pt_ProtocolTx;
    uint16  u2_PduMapIndex;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    pt_ProtocolTx       = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
    ptTxBuf->SduDataPtr = &Dcm_Dsl_u1TxBuf[0];

    if( pt_ProtocolTx != NULL_PTR )
    {
        ptTxBuf->SduLength  = (AB_83_DcmPduLengthType)pt_ProtocolTx->u4TxBufSize;
    }
    else
    {
        ptTxBuf->SduLength = (AB_83_DcmPduLengthType)0U;
    }

    return;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_OFF */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPeriodicTxBuf                            */
/* Description   | This function gets a buffer for periodic response.       */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/*               | [out] ptResMaxDataLen : Response Max Length              */
/* Return Value  | uint8 *                                                  */
/*               |   DataPointer : Response Buffer Address                  */
/*               |   NULL_PTR    : failure                                  */
/* Notes         | Call after Dcm_Dsl_PeriodicSendStart call                */
/****************************************************************************/
#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
FUNC_P2VAR( uint8, DCM_APPL_DATA, DCM_CODE ) Dcm_Dsl_GetPeriodicTxBuf
(
    const uint16                                      u2ConnectionId,
    P2VAR( Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA ) ptResMaxDataLen
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) pt_PeriodicRef;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                                            pt_Result;
    P2VAR( Dcm_Dsl_TxIfType, AUTOMATIC, DCM_APPL_DATA )                                 pt_TxIfArray;
    uint16  u2_PduMapIndex;
    uint8   u1_PeriodicIndex;
    uint8   u1_TxIfStatus;

    pt_Result = NULL_PTR;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        pt_PeriodicRef = Dcm_Dsl_Ctrl_GetPeriodicRef(u2_PduMapIndex);
        if( pt_PeriodicRef != NULL_PTR )
        {
            u1_PeriodicIndex = Dcm_Dsl_stTxIf[u2ConnectionId].u1PeriodicIndex;
            pt_TxIfArray     = &Dcm_Dsl_stTxIf[u2ConnectionId].ptIf[u1_PeriodicIndex];

            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            u1_TxIfStatus = pt_TxIfArray->u1TxIfStatus;

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();

            if( u1_TxIfStatus == DCM_DSL_TXIFST_IDLE )
            {
                pt_Result = &pt_PeriodicRef->ptPeriodicConnection[u1_PeriodicIndex].ptTxBuf[0];
                if( ptResMaxDataLen != NULL_PTR )
                {
                    *ptResMaxDataLen = pt_PeriodicRef->ptPeriodicConnection[u1_PeriodicIndex].u4TxBufSize;
                }
            }
        }
    }

    return pt_Result;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetSizeOfPeriodicBuffer                          */
/* Description   | This function gets a bufferSize for periodic response.   */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/* Return Value  | Dcm_MsgLenType                                           */
/*               |   0x000008U-0xFFFFFFFFU : Success. Response Data  Length */
/*               |   0x000000U             : Failure.                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dcm_MsgLenType, DCM_CODE ) Dcm_Dsl_GetSizeOfPeriodicBuffer
(
    const uint16 u2ConnectionId
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) pt_PeriodicRef;
    Dcm_MsgLenType u4_BufSize;
    uint16         u2_PduMapIndex;
    uint16         u2_IfMapIndex;
    uint16         u2_IfPduIdNum;
    uint8          u1_PeriodicIndex;

    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;
    u4_BufSize    = (Dcm_MsgLenType)0U;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
        {
            if( Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u2PduMapIndex == u2_PduMapIndex )
            {
                pt_PeriodicRef = Dcm_Dsl_Ctrl_GetPeriodicRef(u2_PduMapIndex);
                if( pt_PeriodicRef != NULL_PTR )
                {
                    u1_PeriodicIndex = Dcm_Dsl_stTxIf[u2ConnectionId].u1PeriodicIndex;
                    u4_BufSize       = pt_PeriodicRef->ptPeriodicConnection[u1_PeriodicIndex].u4TxBufSize;
                }
                break;
            }
        }
    }

    return u4_BufSize;

}

#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRoeTxBuf                                 */
/* Description   | Get a RoeTxMsg Buffer Address/TxMsg Buffer MAX Length.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptTxBuf : TxMsg Buffer Address/TxMsg Length        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetRoeTxBuf
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxBuf
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_SubConnectionType, AUTOMATIC, DCM_APPL_CONST ) pt_RoeConnection;
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    pt_RoeConnection     = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptRoeConnectionRef;
    ptTxBuf->SduDataPtr  = &pt_RoeConnection->ptTxBuf[0];
    ptTxBuf->SduLength   = (AB_83_DcmPduLengthType)pt_RoeConnection->u4TxBufSize;

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetRoeIntermediateRespBuf                        */
/* Description   | Get a RoeTxMsg Buffer Address/TxMsg Buffer MAX Length.   */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/*               | [out] ptResMaxDataLen : Response Max Length              */
/* Return Value  | uint8 *                                                  */
/*               |   DataPointer : Response Buffer Address                  */
/*               |   NULL_PTR    : failure                                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR( uint8, DCM_APPL_DATA, DCM_CODE ) Dcm_Dsl_GetRoeIntermediateRespBuf
(
    const uint16                                      u2ConnectionId,
    P2VAR( Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA ) ptResMaxDataLen
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_Result;
    uint16  u2_PduMapIndex;
    uint8   u1_DslState;
    boolean b_RoeInterRespBufferUsed;

    pt_Result = NULL_PTR;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        b_RoeInterRespBufferUsed = Dcm_Dsl_bRoeInterRespBufferUsed;

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( b_RoeInterRespBufferUsed == (boolean)FALSE )
        {
            u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
            if( u1_DslState == DCM_DSL_ST_IDLE )
            {
                if( ptResMaxDataLen != NULL_PTR )
                {
                    *ptResMaxDataLen = DCM_DSL_ROE_INTERMEDIATE_RESP_BUFSIZE;
                }
                pt_Result = &Dcm_Dsl_u1RoeInterRespBuf[0];
            }
        }
    }

    return pt_Result;
}

#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetResPendOccur                             */
/* Description   | Set a Dcm_Dsl_bDetectRcrrp Value.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] bDetectRcrrp : Dcm_Dsl_bDetectRcrrp Value           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetResPendOccur
(
    const boolean bDetectRcrrp
)
{
    Dcm_Dsl_bDetectRcrrp = bDetectRcrrp;

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_IsResponsePendingOccured                         */
/* Description   | This function acquires information on whether NRC0x78    */
/*               | has been transmitted at least once.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Transmitted NRC0x78 more than once        */
/*               |        FALSE : No transmission of NRC0x78                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_IsResponsePendingOccured
( void )
{
    boolean b_RetVal;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    b_RetVal = Dcm_Dsl_bDetectRcrrp;

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed                       */
/* Description   | Set a P2ServerMaxElapsed Flag.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] bP2ServerMaxElapsed : P2Server timeout occurred     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed
(
    const boolean bP2ServerMaxElapsed
)
{
    Dcm_Dsl_bP2ServerMaxElapsed = bP2ServerMaxElapsed;
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed                       */
/* Description   | Get a S3Timer Flag.                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |       TRUE : P2Server timeout occurred                   */
/*               |      FALSE : P2Server timeout has not occurred           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2ServerMaxElapsed
( void )
{
    return Dcm_Dsl_bP2ServerMaxElapsed;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_WriteNRCData                                     */
/* Description   | Call the function(Dcm_Dsl_TxAbt_WriteNRCData) to         */
/*               | write NRC data.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID       : Service ID                            */
/*               |                                                          */
/*               | [in] u1ErrorCode : Error code(NRC)                       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_WriteNRCData
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    uint16  u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();

    Dcm_Dsl_TxAbt_WriteNRCData(u2_PduMapIndex, u1SID, u1ErrorCode);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TransmitFunctionality                            */
/* Description   | Call the function(Dcm_Dsl_TxAbt_TransmitFunctionality)   */
/*               | to request transmission of the response message.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext   : Transmit and receive management    */
/*               |                       address.                           */
/*               | [in] u1ResponseKind : Response kind                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_TransmitFunctionality
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    boolean                   b_Transmit;
    uint8                     u1_DslState;
    uint8                     u1_DummyEventId;
    Std_ReturnType            u1_RetVal;
    uint16                    u2_PduMapIndex;
    AB_83_DcmPduInfoType      st_TxBuf;

    st_TxBuf.SduDataPtr = NULL_PTR;
    st_TxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
    b_Transmit          = (boolean)FALSE;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetTxIdOfWaitingEvent(&u1_DummyEventId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        b_Transmit = (boolean)TRUE;
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
        u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

        if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
         || ( u1_DslState == DCM_DSL_ST_SENDING ) )
        {
            b_Transmit = (boolean)TRUE;
        }
    }

    if( b_Transmit == (boolean)TRUE )
    {
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
        Dcm_Dsl_Ctrl_CompleteWriting();
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
        Dcm_Dsl_Ctrl_SetDslState(u2_PduMapIndex, DCM_DSL_ST_SENDING);

        Dcm_Dsl_Ctrl_GetTxBuf(&st_TxBuf);
        st_TxBuf.SduLength = (AB_83_DcmPduLengthType)ptMsgContext->resDataLen;

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();
        Dcm_Dsl_u1NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum + (uint8)1U;
        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

        u1_RetVal = Dcm_Dsl_TxAbt_TransmitFunctionality(u2_PduMapIndex, &st_TxBuf, u1ResponseKind);
        if(u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
        {
            Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stReservTxID, u2_PduMapIndex, DCM_M_EVTID_DSL_TXRETRY);
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }

    return ;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SendForcePendingResponse                         */
/* Description   | Call the function(Dcm_Dsl_TxAbt_SendForcePendingResponse)*/
/*               | to request the transmission of ForceRCRRP.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID : not use                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_SendForcePendingResponse
(
    const uint8 u1SID
)
{
    boolean b_Transmit;
    uint8   u1_DslState;
    uint8   u1_WaitEventId;
    uint16  u2_PduMapIndex;

    u1_WaitEventId = DCM_M_EVTDISTR_ID_NUM;
    b_Transmit     = (boolean)FALSE;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetTxIdOfWaitingEvent(&u1_WaitEventId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        /* Prioritize pending events and ignore user requests */
        if( u1_WaitEventId == DCM_M_EVTID_DSL_CANCELTXSERVICE )
        {
            Dcm_Dsd_CancelService();
            Dcm_Dsl_TxAbt_CancelTransmit(u2_PduMapIndex);
        }
        else
        {
            Dcm_Dsl_DataConfFunctionalityCbk(u1_WaitEventId);
        }
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
        u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
        if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
        {
            if( Dcm_Dsl_stDiagResp[0].bP4Server == (boolean)TRUE )
            {
                if( Dcm_Dsl_stP2StoredData.u1NumRespPend >= Dcm_Dsl_stDiagResp[0].u1RespMaxNumRespPend )
                {
                    /* Perform fail-safe processing */
                    Dcm_Dsl_P4TOCbk(DCM_M_TMRID_P2TIMER);
                }
                else
                {
                    b_Transmit = (boolean)TRUE;
                }
            }
            else
            {
                b_Transmit = (boolean)TRUE;
            }
        }

        if( b_Transmit == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_SetForceRcrrp((boolean)TRUE);
            Dcm_Dsl_Ctrl_SetP2ServerMaxElapsed((boolean)TRUE);
            Dcm_Dsl_TxAbt_SendForcePendingResponse(u2_PduMapIndex, u1SID);
        }
    }

    return;
}

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_PeriodicSendStart                                */
/* Description   | This function notifies the start of periodic             */
/*               | transmission.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_PeriodicSendStart
(
    const uint16 u2ConnectionId
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) pt_PeriodicRef;
    P2VAR( Dcm_Dsl_TxIfType, AUTOMATIC, DCM_APPL_DATA ) pt_TxIfArray;
    uint16 u2_IfMapIndex;
    uint16 u2_ClientIndex;
    uint16 u2_PduMapIndex;
    uint16 u2_IfPduIdNum;
    uint8  u1_ifcnt;
    boolean b_find;
    boolean b_sending;

    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;

    if( u2ConnectionId == DCM_DSL_ALL_TARGETS )
    {
        b_sending = Dcm_Dsl_Ctrl_IsActiveResponse();
        if( b_sending == (boolean)FALSE )
        {
            for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
            {
                if( Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u1TxIfIndex == (uint8)0U )
                {
                    u2_ClientIndex                                 = Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u2ClientIndex;
                    Dcm_Dsl_stTxIf[u2_ClientIndex].u1PeriodicIndex = 0U;
                    Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf            = &Dcm_Dsl_stTxIfArray[u2_IfMapIndex];
                }

                /* lock */
                SchM_Enter_Dcm_Dsl_Ctrl();

                pt_TxIfArray                     = &Dcm_Dsl_stTxIfArray[u2_IfMapIndex];
                pt_TxIfArray->u1TxIfStatus       = DCM_DSL_TXIFST_IDLE;
                pt_TxIfArray->stTxBuf.SduDataPtr = NULL_PTR;
                pt_TxIfArray->stTxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
                pt_TxIfArray->u2RetryCnt         = (uint16)0U;

                /* unlock */
                SchM_Exit_Dcm_Dsl_Ctrl();
            }
        }
    }
    else
    {
        b_find         = (boolean)FALSE;
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);

        /* Get IfMapindex */
        for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
        {
            if( Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u2PduMapIndex == u2_PduMapIndex )
            {
                b_find = (boolean)TRUE;
                break;
            }
        }

        if( b_find == (boolean)TRUE )
        {
            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            u2_ClientIndex                                 = Dcm_Dsl_IpduIdMapTable[u2_IfMapIndex].u2ClientIndex;
            Dcm_Dsl_stTxIf[u2_ClientIndex].u1PeriodicIndex = 0U;
            Dcm_Dsl_stTxIf[u2_ClientIndex].ptIf            = &Dcm_Dsl_stTxIfArray[u2_IfMapIndex];

            pt_PeriodicRef = Dcm_Dsl_Ctrl_GetPeriodicRef(u2_PduMapIndex);
            if( pt_PeriodicRef != NULL_PTR )
            {
                for( u1_ifcnt = (uint8)0U; u1_ifcnt < pt_PeriodicRef->u1PeriodicConnectionNum; u1_ifcnt++ )
                {
                    pt_TxIfArray = &Dcm_Dsl_stTxIfArray[u2_IfMapIndex + u1_ifcnt];
                    if( pt_TxIfArray->u1TxIfStatus == DCM_DSL_TXIFST_SENDING )
                    {
                        break;
                    }
                    else
                    {
                        pt_TxIfArray->u1TxIfStatus       = DCM_DSL_TXIFST_IDLE;
                        pt_TxIfArray->stTxBuf.SduDataPtr = NULL_PTR;
                        pt_TxIfArray->stTxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
                        pt_TxIfArray->u2RetryCnt         = (uint16)0U;
                    }
                }
            }

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_PeriodicSendReq                                  */
/* Description   | This function requests transmission (single) in          */
/*               | the periodic transmission service.                       */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptMsgContext : Transmit and receive management      */
/*               |                     address.                             */
/*               | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/* Return Value  | Dcm_StatusType                                           */
/*               |      E_OK                   : Success                    */
/*               |      DCM_E_PERIODICID_NOT_ACCEPTED : Busy                */
/*               |                                     (Retry recommended)  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_PeriodicSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) pt_PeriodicRef;
    P2VAR( Dcm_Dsl_TxIfType, AUTOMATIC, DCM_APPL_DATA ) pt_TxIfArray;
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )            pt_PeriodicIndex;
    uint16                    u2_PduMapIndex;
    uint16                    u2_IfPduMapIndex;
    uint8                     u1_TxIfStatus;
    Std_ReturnType            u1_RetVal;
    Dcm_StatusType            u1_Result;

    u1_Result = DCM_E_PERIODICID_NOT_ACCEPTED;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        pt_PeriodicRef = Dcm_Dsl_Ctrl_GetPeriodicRef(u2_PduMapIndex);
        if( pt_PeriodicRef != NULL_PTR )
        {
            pt_PeriodicIndex = &Dcm_Dsl_stTxIf[u2ConnectionId].u1PeriodicIndex;
            pt_TxIfArray     = &Dcm_Dsl_stTxIf[u2ConnectionId].ptIf[*pt_PeriodicIndex];

            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            u1_TxIfStatus = pt_TxIfArray->u1TxIfStatus;

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();

            if( u1_TxIfStatus == DCM_DSL_TXIFST_IDLE )
            {
                u1_Result = (Dcm_StatusType)E_OK;

                /* lock */
                SchM_Enter_Dcm_Dsl_Ctrl();

                pt_TxIfArray->u1TxIfStatus       = DCM_DSL_TXIFST_SENDING;
                pt_TxIfArray->stTxBuf.SduDataPtr = ptMsgContext->resData;
                pt_TxIfArray->stTxBuf.SduLength  = (AB_83_DcmPduLengthType)ptMsgContext->resDataLen;
                pt_TxIfArray->u2RetryCnt         = Dcm_Dsl_u2TxRetryCountValue;

                /* unlock */
                SchM_Exit_Dcm_Dsl_Ctrl();

                u1_RetVal = Dcm_Dsl_TxIf_PeriodicTransmit(u2_PduMapIndex, *pt_PeriodicIndex, &pt_TxIfArray->stTxBuf);
                if( u1_RetVal != (Std_ReturnType)DCM_DSL_TXIF_E_DISABLE )
                {
                    /* lock */
                    SchM_Enter_Dcm_Dsl_Ctrl();

                    *pt_PeriodicIndex = *pt_PeriodicIndex + (uint8)1U; /* no wrap around */
                    if( *pt_PeriodicIndex >= pt_PeriodicRef->u1PeriodicConnectionNum )
                    {
                        *pt_PeriodicIndex = (uint8)0U;
                    }

                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        /* no process */
                    }
                    else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TXIF_E_SEND_ERR )
                    {
                        pt_TxIfArray->u1TxIfStatus = DCM_DSL_TXIFST_SENDERR;
                    }
                    else /* DCM_DSL_TXIF_E_SUPPRES */
                    {
                        pt_TxIfArray->u1TxIfStatus = DCM_DSL_TXIFST_SENDCMP;
                    }

                    /* unlock */
                    SchM_Exit_Dcm_Dsl_Ctrl();
                }
                else
                {
                    u2_IfPduMapIndex = Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].u2IfMapIndex + *pt_PeriodicIndex;
                    Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stPeriodicTxID, u2_IfPduMapIndex, DCM_M_EVTID_DSL_TXIFRETRY);
                }
            }
        }
    }

    return u1_Result;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_GetPeriodicSendResult                            */
/* Description   | This function gets the UUDT transmission result          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  |  DCM_DSL_PERIODICTX_COMPLETE : Transmission comlete      */
/*               |  DCM_DSL_PERIODICTX_ERROR    : Transmission failure      */
/*               |  DCM_DSL_PERIODICTX_SENDING  : There is a job being sent.*/
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_GetPeriodicSendResult
(
    const uint16 u2ConnectionId
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) pt_PeriodicRef;
    P2VAR( Dcm_Dsl_TxIfType, AUTOMATIC, DCM_APPL_DATA ) pt_TxIfArray;
    uint16         u2_IfCnt;
    uint16         u2_PduMapIndex;
    uint16         u2_IfMapIndex;
    uint16         u2_IfPduIdNum;
    Std_ReturnType u1_Retval;

    u1_Retval     = DCM_DSL_PERIODICTX_COMPLETE;
    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;

    if( u2ConnectionId == DCM_DSL_ALL_TARGETS )
    {
        for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
        {
            pt_TxIfArray = &Dcm_Dsl_stTxIfArray[u2_IfMapIndex];
            if( pt_TxIfArray->u1TxIfStatus == DCM_DSL_TXIFST_SENDERR )
            {
                u1_Retval = DCM_DSL_PERIODICTX_ERROR;
                break;
            }
            else if( pt_TxIfArray->u1TxIfStatus == DCM_DSL_TXIFST_SENDING )
            {
                u1_Retval = DCM_DSL_PERIODICTX_SENDING;
            }
            /* DCM_DSL_TXIFST_IDLE or DCM_DSL_TXIFST_SENDCMP */
            else
            {
                /* no process */
            }
        }
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
        if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
        {
            pt_PeriodicRef = Dcm_Dsl_Ctrl_GetPeriodicRef(u2_PduMapIndex);
            if( pt_PeriodicRef != NULL_PTR )
            {
                for( u2_IfCnt = (uint16)0U; u2_IfCnt < pt_PeriodicRef->u1PeriodicConnectionNum; u2_IfCnt++ )
                {
                    pt_TxIfArray = &Dcm_Dsl_stTxIf[u2ConnectionId].ptIf[u2_IfCnt];
                    if( pt_TxIfArray->u1TxIfStatus == DCM_DSL_TXIFST_SENDERR )
                    {
                        u1_Retval = DCM_DSL_PERIODICTX_ERROR;
                        break;
                    }
                    else if( pt_TxIfArray->u1TxIfStatus == DCM_DSL_TXIFST_SENDING )
                    {
                        u1_Retval = DCM_DSL_PERIODICTX_SENDING;
                    }
                    /* DCM_DSL_TXIFST_IDLE or DCM_DSL_TXIFST_SENDCMP */
                    else
                    {
                        /* no process */
                    }
                }
            }
            else
            {
                /* Since RAM is garbled, periodic transmission is stopped. */
                u1_Retval = DCM_DSL_PERIODICTX_ERROR;
            }
        }
        else
        {
            u1_Retval = DCM_DSL_PERIODICTX_ERROR;
        }
    }
    return u1_Retval;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetNumOfConcurrentTxIf                      */
/* Description   | Get the number of concurrent transmissions(top half).    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               |      0x00~0xFFU : number of concurrent transmissions     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetNumOfConcurrentTxIf
( void )
{
    uint8  u1_Retval;
    uint8  u1_TxIfStatus;
    uint16 u2_IfMapIndex;
    uint16 u2_IfPduIdNum;

    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;
    u1_Retval     = (uint8)0U;

    for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
    {
        u1_TxIfStatus = Dcm_Dsl_stTxIfArray[u2_IfMapIndex].u1TxIfStatus;
        if( u1_TxIfStatus == DCM_DSL_TXIFST_SENDING )
        {
            u1_Retval = u1_Retval + (uint8)1U; /* no wrap around */
        }
    }

    return u1_Retval;
}
#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsActiveResponse                            */
/* Description   | This function shows periodic sending status              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sending periodic transmission             */
/*               |        FALSE : Other                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveResponse
( void )
{
    uint16 u2_IfPduIdNum;
    uint16 u2_IfMapIndex;
    boolean b_Result;

    u2_IfPduIdNum = Dcm_Dsl_u2IfPduIdNum;
    b_Result      = (boolean)FALSE;

    for( u2_IfMapIndex = (uint16)0U; u2_IfMapIndex < u2_IfPduIdNum; u2_IfMapIndex++ )
    {
        if( Dcm_Dsl_stTxIfArray[u2_IfMapIndex].u1TxIfStatus == DCM_DSL_TXIFST_SENDING )
        {
            b_Result = (boolean)TRUE;
            break;
        }
    }

    return b_Result;
}
#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */
#if( DCM_DSL_PERIODICTX_ENABLE == STD_OFF )
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveResponse
( void )
{
    boolean b_Result;

    b_Result = (boolean)FALSE;

    return b_Result;
}
#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_OFF  */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | DslInternal_ResponseOnOneEvent                           */
/* Description   | Accept a demand to transmit an positive response         */
/*               | after Ecu reset.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptMsg : Pointer to response data                    */
/*               |                                                          */
/*               | [in] u4MsgLen : Response Data Length                     */
/*               |                                                          */
/*               | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/* Return Value  | Dcm_StatusType                                           */
/*               |      DCM_E_OK               : Success                    */
/*               |      DCM_E_ROE_NOT_ACCEPTED : Busy(should retry)         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dcm_StatusType, DCM_CODE ) DslInternal_ResponseOnOneEvent
(
    const Dcm_MsgType     ptMsg,
    const Dcm_MsgLenType  u4MsgLen,
    const uint16          u2ConnectionId
)
{
    AB_83_DcmPduInfoType  st_RxBuf;
    uint16                u2_PduMapIndex;
    Dcm_StatusType        u1_RetVal;
    Dcm_StatusType        u1_RoeStartJdgResult;

    u1_RetVal = DCM_E_ROE_NOT_ACCEPTED;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_RoeStartJdgResult = Dcm_Dsl_Ctrl_JudgeStartOfRoe(u2_PduMapIndex);
        if( u1_RoeStartJdgResult == (Dcm_StatusType)E_OK )
        {
            st_RxBuf.SduDataPtr = ptMsg;
            st_RxBuf.SduLength  = (AB_83_DcmPduLengthType)u4MsgLen;

            Dcm_Dsl_Ctrl_SetDslState(u2_PduMapIndex, DCM_DSL_ST_WT_SVCOMP);

            Dcm_Dsl_Ctrl_DeemedReceiveEvent(u2_PduMapIndex, &st_RxBuf);
            u1_RetVal = DCM_E_OK;
        }
        else if( u1_RoeStartJdgResult == (Dcm_StatusType)E_NOT_OK )
        {
            /* Request discard */
            u1_RetVal = DCM_E_OK;
        }
        else
        {
            /* no Process */
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_RoeSendReq                                       */
/* Description   | This function sends the ROE intermediate response and    */
/*               | final response.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptMsgContext : Transmit and receive management      */
/*               |                     address.                             */
/*               | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                                                          */
/* Return Value  | Dcm_StatusType                                           */
/*               |      DCM_E_OK               : Success                    */
/*               |      DCM_E_ROE_NOT_ACCEPTED : Busy(should retry)         */
/* Notes         | Important: The user should reserve the area for          */
/*               |            transmitted data.                             */
/****************************************************************************/
FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_RoeSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    AB_83_DcmPduInfoType  st_TxBuf;
    uint32                u4_P2ServerMax;
    uint16                u2_PduMapIndex;
    Std_ReturnType        u1_RetVal;
    Dcm_StatusType        u1_Result;
    Dcm_StatusType        u1_RoeStartJdgResult;

    u1_Result = (Dcm_StatusType)DCM_E_ROE_NOT_ACCEPTED;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexByConnectionId(u2ConnectionId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        u1_RoeStartJdgResult = Dcm_Dsl_Ctrl_JudgeStartOfRoe(u2_PduMapIndex);
        if( u1_RoeStartJdgResult == (Dcm_StatusType)E_OK )
        {
            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            Dcm_Dsl_bRoeInterRespBufferUsed = (boolean)TRUE;

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();

            /* Change State DCM_DSL_ST_SENDING */
            Dcm_Dsl_Ctrl_ActiveDeemedReceiveProc(u2_PduMapIndex);

            st_TxBuf.SduDataPtr = &Dcm_Dsl_u1RoeInterRespBuf[0];
            st_TxBuf.SduLength  = (AB_83_DcmPduLengthType)ptMsgContext->resDataLen;

            u4_P2ServerMax = Dcm_Dsl_Ctrl_GetP2Server((boolean)FALSE, DCM_DSL_CURRENTSESSION);
            Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_ROERETRY_TIMER, u4_P2ServerMax);

            u1_RetVal = Dcm_Dsl_TxAbt_TransmitFunctionality(u2_PduMapIndex, &st_TxBuf, u1ResponseKind);
            if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsl_Ctrl_TxRetryReq(&Dcm_Dsl_stReservTxID, u2_PduMapIndex, DCM_M_EVTID_DSL_TXRETRY);
            }

            u1_Result = DCM_E_OK;
        }
        else if( u1_RoeStartJdgResult == (Dcm_StatusType)E_NOT_OK )
        {
            /* Request discard */
            u1_Result = DCM_E_OK;
        }
        else
        {
            /* no Process */
        }
    }

    return u1_Result;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RespReqAfterEcuReset                        */
/* Description   | Accept a demand to transmit an positive response         */
/*               | after Ecu reset.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [In] u1SID         : SID                                 */
/*               | [In] u1SubFncId    : SubFunction                         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RespReqAfterEcuReset
(
    const uint16 u2PduMapIndex,
    const uint8  u1SID,
    const uint8  u1SubFncId
)
{
    AB_83_DcmPduInfoType  st_TxBuf;

    /* Change State DCM_DSL_ST_SENDING */
    Dcm_Dsl_Ctrl_DeemedReceiveProc(u2PduMapIndex, u1SID, u1SubFncId);

    /* Get P2*Server. Acquire a P2*Server value by the second function call. Return value ignoring */
    (void)Dcm_Dsl_Ctrl_GetP2Server((boolean)FALSE, DCM_DSL_CURRENTSESSION);
    Dcm_Dsl_Ctrl_NotifyServiceStart((boolean)TRUE, DCM_DSL_CURRENTSESSION);

    Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);
    Dcm_Dsl_Ctrl_SetAnalyzeReqMsgDirectly((boolean)TRUE);

    /* Get Tx Buffer. Set request SID and Sub-Function */
    Dcm_Dsl_Ctrl_SetPduMapIndex(u2PduMapIndex);
    Dcm_Dsl_Ctrl_GetTxBuf(&st_TxBuf);

    st_TxBuf.SduDataPtr[DCM_DSL_IDX_RESPONSE_SID] = u1SID;
    st_TxBuf.SduDataPtr[DCM_DSL_IDX_RESPONSE_SFC] = u1SubFncId;

    Dcm_Dsl_CreRspMsgAfterEcuReset(&st_TxBuf);
    Dcm_Dsl_TxAbt_SetRespReqMsg(u2PduMapIndex, &st_TxBuf);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();
    Dcm_Dsl_u1NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum + (uint8)1U;
    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

    /* Send DCM_M_EVTID_DSL_RESPREQ_AFRST event. Return value ignoring */
    (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_RESPREQ_AFRST);

    return ;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_BusyRespReq                                 */
/* Description   | This function makes a negative response asynchronous     */
/*               | send request.                                            */
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
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_BusyRespReq
(
    const uint16                       u2PduMapIndex,
    const uint8                        u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    Dcm_Main_EvtDistr_RetType u1_EvtResult;
    Std_ReturnType            u1_RetVal;

    u1_RetVal = Dcm_Dsl_TxAbt_SetBusyRespReq(u2PduMapIndex, u1SID, u1ErrorCode);
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_TRANSMIT);
        if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
        {
            Dcm_Dsl_Ctrl_EnQueueTxID(&Dcm_Dsl_stReservTxID, u2PduMapIndex);

#if( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();
            Dcm_Dsl_u1NotifySwcMsgNum = Dcm_Dsl_u1NotifySwcMsgNum + (uint8)1U;
            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */

        }
        else
        {
            Dcm_Dsl_TxAbt_Abort();
        }
    }
    else
    {
        Dcm_Dsl_TxAbt_Abort();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxRetryReq                                  */
/* Description   | This function notifies the start of transmission of      */
/*               | the final response.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptQueue   : TxId Queue                          */
/*               | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1_EventId    : Event Id                            */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxRetryReq
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue,
    const uint16 u2PduMapIndex,
    const uint8 u1_EventId
)
{
    Dcm_Main_EvtDistr_RetType u1_EvtResult;

    u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(u1_EventId);
    if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
    {
        Dcm_Dsl_Ctrl_EnQueueTxID(ptQueue, u2PduMapIndex);
    }
    else
    {
        Dcm_Dsl_Ctrl_Abort();
    }
    return ;
}

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_PeriodicTxRetryReq                          */
/* Description   | This function performs a retry of the sending            */
/*               | until P2ServerMax progress.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex   : PduMapIndex Value                 */
/* Parameters    | [in] u1PeriodicIndex : periodic connection index         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Processing normal              */
/*               |   E_NOT_OK              : failure                        */
/*               |   DCM_E_PENDING         : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_PeriodicTxRetryReq
(
    const uint16 u2PduMapIndex,
    const uint8  u1PeriodicIndex
)
{
    P2VAR( Dcm_Dsl_TxIfType, AUTOMATIC, DCM_APPL_DATA ) pt_TxIf;
    uint8                       u1_TxIfStatus;
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_Result;

    u1_Result         = (Std_ReturnType)E_OK;
    pt_TxIf           = &Dcm_Dsl_stTxIf[Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex].ptIf[u1PeriodicIndex];
    u1_TxIfStatus     = pt_TxIf->u1TxIfStatus;

    if( pt_TxIf->u2RetryCnt > (uint16)0U )
    {
        pt_TxIf->u2RetryCnt--;
        if( u1_TxIfStatus == DCM_DSL_TXIFST_SENDING )
        {
            u1_RetVal = Dcm_Dsl_TxIf_PeriodicTransmit(u2PduMapIndex, u1PeriodicIndex, &pt_TxIf->stTxBuf);
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                /* no process */
            }
            else if( u1_RetVal == (Std_ReturnType)DCM_DSL_TXIF_E_DISABLE )
            {
                u1_Result = (Std_ReturnType)DCM_E_PENDING;
            }
            else /* Transmission error only */
            {
                u1_Result = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            u1_Result = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        u1_Result = (Std_ReturnType)E_NOT_OK;
    }

    return u1_Result;
}
#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DataConfFunctional                          */
/* Description   | Notice to Dsd of Tx Confirmation.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1ConfirmationStatus  : Confirmation Status         */
/*               | [in] bIsSendForcedPending  :                             */
/*               |        TRUE  : Transmitted FCRRP                         */
/*               |        FALSE : No transmission of FCRRP                  */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_DataConfFunctional
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus,
    const boolean bIsSendForcedPending
)
{
    uint8 u1_RetVal;

    u1_RetVal = Dcm_Dsd_DataConfirmationFunctionality(u1ConfirmationStatus, bIsSendForcedPending);

    return u1_RetVal;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetResponseDataLength                       */
/* Description   | This function gets Response Data Length.                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | AB_83_DcmPduLengthType                                   */
/*               |   0x000000U-0xFFFFFFFFU : Response Data  Length          */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( AB_83_DcmPduLengthType, DCM_CODE ) Dcm_Dsl_Ctrl_GetResponseDataLength
( void )
{
    return (AB_83_DcmPduLengthType)Dcm_Dsd_GetResponseDataLength();
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsSuppressNegMsg                            */
/* Description   | This function determines whether the message suppresses  */
/*               | the response.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1SID         : Service ID                          */
/*               | [in] u1Nrc         : Negative Response Code              */
/* Return Value  | boolean                                                  */
/*               |     TRUE:  Suppress negative response message            */
/*               |    FALSE:  Other                                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsSuppressNegMsg
(
    const uint16                       u2PduMapIndex,
    const uint8                        u1SID,
    const Dcm_NegativeResponseCodeType u1Nrc
)
{
    uint16  u2_ConnectionId;
    boolean b_RetVal;

    u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
    b_RetVal        = Dcm_Dsd_IsSuppressNegMsg(u1SID, u1Nrc, u2_ConnectionId);

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsAcceptedFinalResp                         */
/* Description   | This function shows acceptance existence of              */
/*               | the final response.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : acceptance                                */
/*               |        FALSE : Non-acceptance                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsAcceptedFinalResp
(
    const uint16 u2PduMapIndex
)
{
    boolean b_Result;
    uint8   u1_DslState;

    b_Result = (boolean)FALSE;

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( u1_DslState == DCM_DSL_ST_SENDING )
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetForceRcrrp                               */
/* Description   | This function sets ForceRCRRP flag.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] bForceRcrrp : TRUE  : transmitted                   */
/*               |                    FALSE : non-sending                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetForceRcrrp
(
    const boolean bForceRcrrp
)
{
    Dcm_Dsl_bForceRcrrp = bForceRcrrp;
    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsForceRcrrp                                */
/* Description   | This function shows sending existence of ForceRCRRP.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sent NRC0x78 more than once               */
/*               |        FALSE : No transmission of NRC0x78                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsForceRcrrp
( void )
{
    return Dcm_Dsl_bForceRcrrp;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetDsdConfData                              */
/* Description   | This function acquires ConfirmationStatus to carry       */
/*               | to Dsd.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptConfirmationStatus : ConfirmationStatus          */
/*               |                                                          */
/*               | [out] ptSendForcedPending : FORCE_RCRRP sending existence*/
/*               |                                                          */
/* Return Value  | uint16                                                   */
/*               |      Index of PduIdMap                                   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetDsdConfData
(
    P2VAR( Dcm_ConfirmationStatusType, AUTOMATIC, DCM_APPL_DATA ) ptConfirmationStatus,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptSendForcedPending
)
{
    *ptConfirmationStatus = Dcm_Dsl_stLatestConfirmationStatus.u1ConfirmationStatus;
    *ptSendForcedPending  = Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending;

    return Dcm_Dsl_stLatestConfirmationStatus.u2PduMapIndexOfSent;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetLatestConfData                           */
/* Description   | This function sets latest sending result                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] u1ConfirmationStatus : Confirmation Status          */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetLatestConfData
(
    const uint16                     u2PduMapIndex,
    const Dcm_ConfirmationStatusType u1ConfirmationStatus
)
{
    boolean b_InteractiveClient;
    boolean b_ServiceToRespondTo;

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        Dcm_Dsl_stLatestConfirmationStatus.u2PduMapIndexOfSent  = u2PduMapIndex;
        Dcm_Dsl_stLatestConfirmationStatus.u1ConfirmationStatus = u1ConfirmationStatus;
        Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending   = (boolean)FALSE;
    }
    else
    {
        b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
        if( b_InteractiveClient == (boolean)TRUE )
        {
            Dcm_Dsl_stLatestConfirmationStatus.u2PduMapIndexOfSent  = u2PduMapIndex;
            Dcm_Dsl_stLatestConfirmationStatus.u1ConfirmationStatus = u1ConfirmationStatus;
            Dcm_Dsl_stLatestConfirmationStatus.bSendForcedPending   = (boolean)FALSE;
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_EnQueueTxID                                 */
/* Description   | Enqueue a PduMapIndex(for TxID).                         */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptQueue     : TxId Queue                        */
/*               |                                                          */
/*               | [in] u2PduMapIndex   : PduMapIndex Value                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_EnQueueTxID
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue,
    const uint16 u2PduMapIndex
)
{
    uint16 u2_TxIdQueueMax;

    u2_TxIdQueueMax = Dcm_Dsl_u2TxIdQueueMax;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    if( ptQueue->u2WritePos < u2_TxIdQueueMax )
    {
        ptQueue->u2Queue[ptQueue->u2WritePos] = u2PduMapIndex;
        ptQueue->u2WritePos = ptQueue->u2WritePos + (uint16)1U; /* no wrap around */
    }

    if( ptQueue->u2WritePos >= u2_TxIdQueueMax )
    {
        ptQueue->u2WritePos = (uint16)0U;
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DeQueueTxID                                 */
/* Description   | Dequeue a PduMapIndex(for TxID).                         */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptQueue     : TxId Queue                        */
/* Return Value  | uint16                                                   */
/*               |       0U~0xFFFEU              : PduMapIndex Value        */
/*               |       DCM_DSL_INVALID_U2_DATA : Invalid value            */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_DeQueueTxID
(
    P2VAR( Dcm_Dsl_TxIdQueueType, AUTOMATIC, DCM_APPL_DATA ) ptQueue
)
{
    P2VAR( volatile uint16, AUTOMATIC, DCM_APPL_DATA ) pt_ReadPos;
    uint16 u2_PduMapIndex;
    uint16 u2_TxIdQueueMax;
    uint16 u2_WritePos;

    u2_TxIdQueueMax = Dcm_Dsl_u2TxIdQueueMax;
    u2_WritePos     = ptQueue->u2WritePos;
    pt_ReadPos      = &ptQueue->u2ReadPos;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u2_PduMapIndex = ptQueue->u2Queue[*pt_ReadPos];
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        *pt_ReadPos = *pt_ReadPos + (uint16)1U; /* no wrap around */

        if( *pt_ReadPos >= u2_TxIdQueueMax )
        {
            *pt_ReadPos = (uint16)0U;
        }

        if( *pt_ReadPos == u2_WritePos )
        {
            *pt_ReadPos         = (uint16)0U;
            ptQueue->u2WritePos = (uint16)0U;
            ptQueue->u2Queue[0] = DCM_DSL_INVALID_U2_DATA;
        }
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return u2_PduMapIndex;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetAnalyzeReqMsgDirectly                    */
/* Description   | Gets whether to parse request message directly.          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Directly analyze request messages           */
/*               |      FALSE : Do not parse request messages directly      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_GetAnalyzeReqMsgDirectly
( void )
{
    return Dcm_Dsl_bAnalyzeReqMsgDirectly;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetAnalyzeReqMsgDirectly                    */
/* Description   | Set whether to analyze request message directly.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] bAnalyze   :                                        */
/*               |           parse request message directly                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetAnalyzeReqMsgDirectly
(
    const boolean bAnalyze
)
{
    Dcm_Dsl_bAnalyzeReqMsgDirectly = bAnalyze;

    return;

}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetNextTxBuf                                */
/* Description   | Get a TxMsg Paged-Buffer Address/Max Length.             */
/* Preconditions | none                                                     */
/* Parameters    | [out]    ptNextTxBuf : Next Tx Buffer                    */
/* Parameters    | [in/out] ptCurTxBuf  : Current TxBuffer                  */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetNextTxBuf
(
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptNextTxBuf,
    P2VAR( Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptCurTxBuf
)
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_SduDataPtr;
    AB_83_DcmPduLengthType uv_CopyLength;

    pt_SduDataPtr = &ptCurTxBuf->SduStartAddr[ptCurTxBuf->SduPos];

    /* Get Max Length for Paged-Buffer */
    Dcm_Dsl_Ctrl_GetTxBuf(ptNextTxBuf);

    for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptCurTxBuf->SduLength; uv_CopyLength++ )
    {
        ptNextTxBuf->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
    }
    ptCurTxBuf->SduPos      = (AB_83_DcmPduLengthType)0U;
    ptNextTxBuf->SduDataPtr = &ptNextTxBuf->SduDataPtr[uv_CopyLength];

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetTxIdOfWaitingEvent                       */
/* Description   | This function gets the TxID of the wait event.           */
/* Preconditions | none                                                     */
/* Parameters    | [Out] ptEventId : Event Id                               */
/* Return Value  | uint16                                                   */
/*               |       0U~0xFFFEU  : PduMapIndex of Waiting event         */
/*               |       DCM_DSL_INVALID_U2_DATA : No Waiting event         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetTxIdOfWaitingEvent
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventId
)
{
    boolean                   b_DummySendForcePending;
    uint8                     u1_DummyConfirmationStatus;
    Dcm_Main_EvtDistr_RetType u1_EvtResult;
    uint16                    u2_PduMapIndex;

    u2_PduMapIndex = DCM_DSL_INVALID_U2_DATA;
    *ptEventId     = DCM_M_EVTDISTR_ID_NUM;

    u1_EvtResult = Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CANCELTXSERVICE, (boolean)TRUE);
    if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
    {
        /* Change to a sending ID waiting for cancellation */
        u2_PduMapIndex = Dcm_Dsl_Ctrl_DeQueueTxID(&Dcm_Dsl_stCancelTxID);
        *ptEventId = DCM_M_EVTID_DSL_CANCELTXSERVICE;
    }
    else
    {
        /* Completion notification when cancellation instruction comes during transmission,
         * or RCRRP transmission completion notification
         */
        u1_EvtResult = Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CONF_FUNCTIONALITY, (boolean)TRUE);
        if( u1_EvtResult == DCM_MAIN_EVTDISTR_E_OK )
        {
            u2_PduMapIndex = Dcm_Dsl_Ctrl_GetDsdConfData(&u1_DummyConfirmationStatus, &b_DummySendForcePending);
            *ptEventId = DCM_M_EVTID_DSL_CONF_FUNCTIONALITY;
        }
    }

    return u2_PduMapIndex;
}

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetP4Server                                 */
/* Description   | Get a P4Server Value.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint32                                                   */
/*               |       1U~4294967295U : P4Server Value                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint32, DCM_CODE ) Dcm_Dsl_Ctrl_GetP4Server
( void )
{
    uint16   u2_RxPduMapIndex;
    uint16   u2_RowIndex;
    uint16   u2_ConnectionIndex;
    uint16   u2_ProtocolRxIndex;
    boolean  b_ExtSuppressRspMsg;
    uint8    u1_AddrType;
    uint32   u4_P4Server;

    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();

    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2_RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
    b_ExtSuppressRspMsg = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].bExtSuppressRspMsg;

    if( b_ExtSuppressRspMsg == (boolean)TRUE )
    {
        u1_AddrType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;

        if( u1_AddrType == DCM_DSL_ADDINFO_FUNC )
        {
            u4_P4Server = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u4ExtResTimeout;
        }
        else
        {
            u4_P4Server = Dcm_Dsl_stRow[u2_RowIndex].u4DiagFailSafeTimeout;
        }
    }
    else
    {
        u4_P4Server = Dcm_Dsl_stRow[u2_RowIndex].u4DiagFailSafeTimeout;
    }

    if( u4_P4Server == (uint32)0U )
    {
        u4_P4Server = (uint32)1U;
    }

    return u4_P4Server;

}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetP2Server                                 */
/* Description   | Get a P2Server/P2*Server Value.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] bP2kind : P2Server kind   TRUE  P2*Server           */
/*               |                                FALSE P2Server            */
/*               | [in] u1SesInfo : Set Sesiion Information                 */
/*               |                                DCM_DSL_DEFAULTSESSION    */
/*               |                                DCM_DSL_CURRENTSESSION    */
/*               |                                                          */
/* Return Value  | uint16                                                   */
/*               |       1U~65535U : P2Server/P2*Server Value               */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2Server
(
    const boolean bP2kind,
    const uint8 u1SesInfo
)
{
    Dcm_ProtocolType u1_ProtocolType;
    Dcm_SesCtrlType u1_Session;
    uint16 u2_P2Server;
    uint16 u2_Result;
    uint16 u2_RowIndex;
    uint16 u2_RxPduMapIndex;

    if( bP2kind == (boolean)TRUE )
    {
        u2_Result = Dcm_Dsl_stP2StoredData.u2P2StarServer;
    }
    else
    {
        u1_Session = DCM_DEFAULT_SESSION;
        if( u1SesInfo == DCM_DSL_CURRENTSESSION )
        {
            /* Return value ignoring */
            (void)Dcm_GetSesCtrlType(&u1_Session);
        }

        u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();
        u2_RowIndex = Dcm_Dsl_PduIdMapTable[u2_RxPduMapIndex].u2RowIndex;
        u1_ProtocolType = Dcm_Dsl_stRow[u2_RowIndex].u1ID;

        u2_P2Server = (uint16)0;
        Dcm_Dsl_stP2StoredData.u2P2StarServer = (uint16)0;
        Dcm_Dsl_stP2StoredData.u2P2StarServerMin = (uint16)0;

        Dcm_Dsl_GetP2ServerValue( u1_Session,
                                  u1_ProtocolType,
                                  &u2_P2Server,
                                  &Dcm_Dsl_stP2StoredData.u2P2StarServer,
                                  &Dcm_Dsl_stP2StoredData.u2P2StarServerMin );

        if( u2_P2Server > Dcm_Dsl_stRow[u2_RowIndex].u2P2ServerAdjust )
        {
            u2_P2Server = u2_P2Server - Dcm_Dsl_stRow[u2_RowIndex].u2P2ServerAdjust;
        }
        else
        {
            u2_P2Server = (uint16)1U;
        }

        if( Dcm_Dsl_stP2StoredData.u2P2StarServer > Dcm_Dsl_stRow[u2_RowIndex].u2P2StarServerAdjust )
        {
            Dcm_Dsl_stP2StoredData.u2P2StarServer = Dcm_Dsl_stP2StoredData.u2P2StarServer -
                                                    Dcm_Dsl_stRow[u2_RowIndex].u2P2StarServerAdjust;
        }
        else
        {
            Dcm_Dsl_stP2StoredData.u2P2StarServer = (uint16)1U;
        }

        Dcm_Dsl_stP2StoredData.u1NumRespPend = (uint8)0U;
        u2_Result                            = u2_P2Server;
    }

    return u2_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetP2ServerMin                              */
/* Description   | Get a P2*ServerMin Value.                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       1U~65535U : P2*ServerMin Value                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetP2ServerMin
( void )
{
    return Dcm_Dsl_stP2StoredData.u2P2StarServerMin;
}

#if( DCM_DSL_PERIODICTX_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPeriodicRef                              */
/* Description   | This function gets PeriodicConnectionRef.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | Dcm_Dsl_PeriodicTransmissionType                         */
/*               |   ptPeriodicConnectionRef : exist                        */
/*               |   NULL_PTR                : not exist                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC_P2CONST( AB_83_ConstV Dcm_Dsl_PeriodicTransmissionType, AUTOMATIC, DCM_APPL_CONST ) Dcm_Dsl_Ctrl_GetPeriodicRef
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptPeriodicConnectionRef;
}
#endif /*  DCM_DSL_PERIODICTX_ENABLE == STD_ON  */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_JudgeStartOfRoe                             */
/* Description   | This function checks if ROE can be started.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | Dcm_StatusType                                           */
/*               |      E_OK                   : Success                    */
/*               |      E_NOT_OK               : Failure                    */
/*               |      DCM_E_ROE_NOT_ACCEPTED : Busy(should retry)         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsl_Ctrl_JudgeStartOfRoe
(
    const uint16 u2PduMapIndex
)
{
    uint16         u2_ActivePduMapIndex;
    uint16         u2_ActiveRxPduMapIndex;
    uint8          u1_DslState;
    uint8          u1_ReqState;
    Dcm_StatusType u1_Result;
    boolean        b_Active;
    boolean        b_CanRoe;

    u1_Result = DCM_E_ROE_NOT_ACCEPTED;
    b_Active  = (boolean)TRUE;

    u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    b_CanRoe = Dcm_Dsl_TxAbt_CanStartRoe(u2PduMapIndex, u2_ActivePduMapIndex);
    if( b_CanRoe == (boolean)TRUE )
    {
        u2_ActiveRxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_ActiveRxPduMapIndex);
        if( u1_DslState == DCM_DSL_ST_IDLE )
        {
            if( u2_ActivePduMapIndex != u2PduMapIndex )
            {
                u1_ReqState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
                if( u1_ReqState == DCM_DSL_ST_IDLE )
                {
                    b_Active = Dcm_Dsl_TxAbt_IsActive(u2_ActivePduMapIndex);
                    if( b_Active == (boolean)FALSE )
                    {
                        b_Active = Dcm_Dsl_TxAbt_IsActive(u2PduMapIndex);
                    }
                }
            }
            else
            {
                b_Active = Dcm_Dsl_TxAbt_IsActive(u2PduMapIndex);
            }
        }
        else if( u1_DslState == DCM_DSL_ST_RECEIVING )
        {
            if( u2_ActivePduMapIndex != u2PduMapIndex )
            {
                u1_ReqState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
                if( u1_ReqState == DCM_DSL_ST_IDLE )
                {
                    b_Active = Dcm_Dsl_TxAbt_IsActive(u2_ActivePduMapIndex);
                    if( b_Active == (boolean)FALSE )
                    {
                        b_Active = Dcm_Dsl_TxAbt_IsActive(u2PduMapIndex);
                    }
                }
            }
        }
        else
        {
            /* no process */
        }

        if( b_Active == (boolean)FALSE )
        {
            u1_Result = E_OK;
        }
    }
    else
    {
        u1_Result = E_NOT_OK;
    }
    return u1_Result;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-5-0         :2023-07-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-6-2         :2024-06-24                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
