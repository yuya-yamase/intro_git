/* Dcm_Dsl_Ctrl_ComSrv_c(v5-10-0)                                           */
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
#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"

#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"

#include <Dcm/Dcm_Dsd_SendMng.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_COMSRV_RXBUFSIZE ((uint32)2UL)
#define DCM_DSL_ID_SID10_REQUEST ((uint8)0x10U)
#define DCM_DSL_ID_SID11_REQUEST ((uint8)0x11U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Received data information structure for each PduID */
typedef struct {
    AB_83_DcmPduInfoType                    stRxPduInfo;               /* Receive Buffer and Receive Message Length */
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  ptRxPduAddr;               /* Receive Buffer start address */
    AB_83_DcmPduLengthType                  RxSduLengthRmd;            /* Remain Receive Buffer Length              */
} Dcm_Dsl_RxDataType;

typedef struct {
    AB_83_DcmPduInfoType                    stRxPduInfo;               /* Receive Buffer and Receive Message Length */
    AB_83_DcmPduLengthType                  RxSduLengthRmd;            /* Remain Receive Buffer Length              */
} Dcm_Dsl_KALDataType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ComSrv_Clear
(
    const uint16 u2PduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopTimers
( void );

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeleteAfterRebootEvent
( void );

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduIdMapIndexBySourceAddr
(
    const uint16 u2TesterSourceAddr
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DataIndFunctional
(
    const uint16 u2RxPduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartS3Timer
(
    const uint16 u2RxPduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartS3TimerCore
(
    const uint16 u2RxPduMapIndex,
    const boolean bParallelCheck
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopS3Timer
(
    const uint16 u2RxPduMapIndex
);

#if( DCM_AUTHENTICATION_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartAuthCtrl
(
    const uint16 u2PduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthCtrl
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetS3Server
( void );

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetResUseId
(
    const uint16 u2PduMapIndex,
    const boolean bUseResource
);

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId
(
    const uint16 u2PduMapIndex,
    const boolean bUseResource
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ClearSaveRoePreExeState
(
    const uint16 u2RxPduMapIndex
);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseServiceToRespondToResUseId
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeemedReceiveEventResource
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseRxResource
(
    const uint16 u2PduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseKALResource
(
    const uint16 u2PduMapIndex
);

static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CallInactiveAllCh
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/* DSL State */
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1DslState[DCM_DSL_CLIENT_NUM];

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1SaveRoePreExeState;
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bInteractiveClient;

/* For Rx */
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsl_u2ResUseId[DCM_DSL_CLIENT_NUM];

/* PduMapIndex for Tx/Dsp  */
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsl_u2PduMapIndex;

/* PduMapIndex for Rx */
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsl_u2RxPduMapIndex;

/* PduMapIndex for ServiceToRespondTo */
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsl_u2StrPduMapIndex;

static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsl_bFirstServiceToRespondTo;

/* Received data information structure for each PduID */
static VAR(Dcm_Dsl_RxDataType, DCM_VAR_NO_INIT) Dcm_Dsl_stRxData[DCM_DSL_PDUID_NUM];

/* Received data information structure for each FUNCADDR */
static VAR(Dcm_Dsl_KALDataType, DCM_VAR_NO_INIT) Dcm_Dsl_stKALData[DCM_DSL_FUNCADDRINFO_NUM];

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsl_u1RxBuf4DeemedReception[DCM_DSL_COMSRV_RXBUFSIZE];
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

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
/* Function Name | Dcm_Dsl_Ctrl_ComSrv_Init                                 */
/* Description   | This function initializes Dsl_Ctrl_ComSrv.               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ComSrv_Init
( void )
{
    uint16 u2_Cnt;
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_PduIdNumMax;
    uint16 u2_ClientNumMax;

    u2_PduIdNumMax  = Dcm_Dsl_u2PduIdNum;
    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;

    Dcm_Dsl_bInteractiveClient   = (boolean)FALSE;
    Dcm_Dsl_u2PduMapIndex        = (uint16)0U;
    Dcm_Dsl_u2RxPduMapIndex      = (uint16)0U;
    Dcm_Dsl_u2StrPduMapIndex     = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_bFirstServiceToRespondTo = (boolean)FALSE;

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
    Dcm_Dsl_u1SaveRoePreExeState = DCM_DSL_ST_IDLE;
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

    for( u2_Cnt = (uint16)0U; u2_Cnt < u2_ClientNumMax; u2_Cnt++ )
    {
        Dcm_Dsl_u1DslState[u2_Cnt]  = DCM_DSL_ST_IDLE;
        Dcm_Dsl_u2ResUseId[u2_Cnt]  = DCM_DSL_INVALID_U2_DATA;
    }

    for( u2_PduIDNum_Cnt = (uint16)0U; u2_PduIDNum_Cnt < u2_PduIdNumMax; u2_PduIDNum_Cnt++ )
    {
        Dcm_Dsl_Ctrl_ReleaseRxResource(u2_PduIDNum_Cnt);
        Dcm_Dsl_Ctrl_ReleaseKALResource(u2_PduIDNum_Cnt);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ComSrv_Clear                                */
/* Description   | This function initializes Dsl_Ctrl_ComSrv.               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ComSrv_Clear
(
    const uint16 u2PduMapIndex
)
{
    boolean  b_ServiceToRespondTo;

    Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)FALSE);
    Dcm_Dsl_Ctrl_ReleaseRxResource(u2PduMapIndex);

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
        Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId(u2PduMapIndex, (boolean)FALSE);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
        Dcm_Dsl_Ctrl_ReleaseServiceToRespondToResUseId(u2PduMapIndex);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */
    }

    return;
}

/**********                Timer Handlers                          **********/
/****************************************************************************/
/* Function Name | Dcm_Dsl_S3TOCbk                                          */
/* Description   | Perform a process in the S3Server timeout.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : DCM_M_TMRID_S3TIMER                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_S3TOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    uint16  u2_PduMapIndex;
    uint8   u1_DslState;
    boolean bActiveResponse;
    boolean b_ServiceToRespondTo;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState == DCM_DSL_ST_IDLE )
    {
        Dcm_Dsl_Ctrl_SetDefSes(u2_PduMapIndex);
    }
    else
    {
        bActiveResponse      = Dcm_Dsl_Ctrl_IsActiveResponse();
        b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2_PduMapIndex);
        if( b_ServiceToRespondTo == (boolean)TRUE )
        {
            bActiveResponse = (boolean)TRUE;
        }

        if( bActiveResponse == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_SetDefSes(u2_PduMapIndex);
        }
        else
        {
            Dcm_Dsl_Ctrl_Abort();
        }
    }

    return ;
}

/**********                Event Handlers                          **********/
/****************************************************************************/
/* Function Name | Dcm_Dsl_SetDefSesCbk                                     */
/* Description   | Set default session.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_SETDEFSES               */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_SetDefSesCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
#if( DCM_AUTHENTICATION_USE == STD_ON )
    uint16 u2_ActivePduMapIndex;
    uint16 u2_ClientIndex;
    uint16 u2_ClientIndexMax;
    uint16 u2_InteractiveClientIndex;
    uint16 u2_PduIdMapIndex;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

    DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION, (boolean)FALSE);

    /* Return value ignoring */
    (void)Dcm_Dsl_SessionMng_SwitchModeSesCtrl(RTE_MODE_DcmSesCtrl_DEFAULT_SESSION);

#if( DCM_AUTHENTICATION_USE == STD_ON )
    u2_ClientIndexMax = Dcm_Dsl_u2ClientNum;
    u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    u2_InteractiveClientIndex = Dcm_Dsl_PduIdMapTable[u2_ActivePduMapIndex].u2ClientIndex;

    for( u2_ClientIndex = (uint16)0U ; u2_ClientIndex < u2_ClientIndexMax ; u2_ClientIndex++ )
    {
        if( u2_ClientIndex != u2_InteractiveClientIndex )
        {
            u2_PduIdMapIndex = Dcm_Dsl_ConnectionIdMapTable[u2_ClientIndex];
            Dcm_Dsl_Ctrl_StartAuthCtrl(u2_PduIdMapIndex);
        }
    }
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_ReceiveCbk                                       */
/* Description   | This function is called from DcmMain and notifies Dsd.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_RECEIVE                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_ReceiveCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint16 u2_PduMapIndex;
    uint8  u1_DslState;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
    {
        Dcm_Dsl_Ctrl_SetPduMapIndex(u2_PduMapIndex);
        Dcm_Dsl_Ctrl_DataIndFunctional(u2_PduMapIndex);
    }
    else
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();
        Dcm_Dsl_Ctrl_SetDslState(u2_PduMapIndex, DCM_DSL_ST_IDLE);
        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_StartS3Timer(u2_PduMapIndex);

#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StartAuthCtrl(u2_PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();
        Dcm_Dsl_Ctrl_ComSrv_Clear(u2_PduMapIndex);
        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();
    }

    return;
}

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_ComMActiveDiagnosticCbk                          */
/* Description   | Via a connector function,                                */
/*               |   call ComM_DCM_ActiveDiagnostic function.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_COMM_ACTIVE             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_ComMActiveDiagnosticCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    uint16              u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    Dcm_Dsl_CmHdl_CallActive(u2_PduMapIndex, DCM_DSL_REQ_ACTIVE, (boolean)TRUE);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SetupProgConditions                              */
/* Description   | This function sets program conditions                    */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptProgConditions : Pointer of ProgConditions Data   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_SetupProgConditions
(
    P2CONST( Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA ) ptProgConditions
)
{
    uint16          u2_PduMapIndex;
    uint8           u1_SID;
    Dcm_SesCtrlType u1_InitSession;
    Dcm_SesCtrlType u1_ChgNotifProhibNonDefSession;
    boolean         b_StartInNonDefaultSession;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduIdMapIndexBySourceAddr(ptProgConditions->TesterAddress);
    u1_SID = ptProgConditions->Sid;

    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        if( u1_SID == DCM_DSL_ID_SID10_REQUEST )
        {
            /* Typecasting for comparising session values */
            u1_InitSession = (Dcm_SesCtrlType)ptProgConditions->SubFncId;

            b_StartInNonDefaultSession = (boolean)FALSE;
            u1_ChgNotifProhibNonDefSession = Dcm_M_u1InitRpgSession;

            if( u1_InitSession == DCM_DEFAULT_SESSION )
            {
                Dcm_Dsl_SessionMng_SetInitialSession(u1_InitSession);
            }
            else if( u1_InitSession == u1_ChgNotifProhibNonDefSession )
            {
                Dcm_Dsl_SessionMng_SetInitialSession(u1_InitSession);
                b_StartInNonDefaultSession = (boolean)TRUE;
            }
            else
            {
                Dcm_Dsl_Ctrl_SetSesCtrlType(u1_InitSession, (boolean)FALSE);
                b_StartInNonDefaultSession = (boolean)TRUE;
            }

            if( ptProgConditions->ResponseRequired == (boolean)TRUE )
            {
                Dcm_Dsl_Ctrl_RespReqAfterEcuReset(u2_PduMapIndex, u1_SID, ptProgConditions->SubFncId);
            }
            else
            {
                if( b_StartInNonDefaultSession == (boolean)TRUE )
                {
                    /* Send DCM_M_EVTID_DSL_COMM_ACTIVE event. Return value ignoring */
                    (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_COMM_ACTIVE);

                    Dcm_Dsl_bInteractiveClient = (boolean)TRUE;
                    Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2_PduMapIndex);
                    Dcm_Dsl_Ctrl_SetPduMapIndex(u2_PduMapIndex);
                    Dcm_Dsl_Ctrl_StartS3TimerCore(u2_PduMapIndex, (boolean)FALSE);
                }
            }
        }
        else if( u1_SID == DCM_DSL_ID_SID11_REQUEST )
        {
            if( ptProgConditions->ResponseRequired == (boolean)TRUE )
            {
                Dcm_Dsl_Ctrl_RespReqAfterEcuReset(u2_PduMapIndex, ptProgConditions->Sid, ptProgConditions->SubFncId);
            }
        }
        else
        {
            /* no process */
        }
    }

    return ;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StartOfReception                            */
/* Description   | This function performs processing at the time of         */
/*               | receiving start notification.                            */
/* Preconditions | Arbitration type 1: Calling only from interacting or     */
/*               | high priority clients.                                   */
/*               | Arbitration type 2: no restrictions                      */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] bKeepAliveMsg : KAL(TRUE) or Not KAL(FALSE)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartOfReception
(
    const uint16 u2PduMapIndex,
    const boolean bKeepAliveMsg
)
{
    uint8  u1_DslState;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState == DCM_DSL_ST_IDLE )
    {
        Dcm_Dsl_Ctrl_StopS3Timer(u2PduMapIndex);

#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StopAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

        if( bKeepAliveMsg == (boolean)FALSE )
        {
            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_RECEIVING);

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RedoOfReception                             */
/* Description   | This function prepares to overwrite the received message */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1PrevReqKind : Previous Request kind               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RedoOfReception
(
    const uint16 u2PduMapIndex,
    const uint8 u1PrevReqKind
)
{

    if( u1PrevReqKind == DCM_DSL_RX_REQ_NORMAL )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_NotifyPseudoKALasNoKAL                      */
/* Description   | This function performs processing when the request is    */
/*               | considered pseudoKAL but not KAL.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_NotifyPseudoKALasNoKAL
(
    const uint16 u2PduMapIndex
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_RECEIVING);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_Accept                                      */
/* Description   | This function accepts a request and processes            */
/*               | the request.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Accept
(
    const uint16 u2PduMapIndex
)
{
    boolean b_ChangeClient;
    boolean b_InteractiveClient;
    uint8   u1_DslState;

    b_ChangeClient   = (boolean)FALSE;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState != DCM_DSL_ST_RECEIVING )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_SETDEFSES, (boolean)TRUE);

        Dcm_Dsl_Ctrl_StartS3Timer(u2PduMapIndex);
#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StartAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */        

        Dcm_Dsl_Ctrl_ReleaseRxResource(u2PduMapIndex);
        Dcm_Dsl_Ctrl_ReleaseKALResource(u2PduMapIndex);
    }
    else
    {
        Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_S3TIMER);
#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StopAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
        Dcm_Dsl_CmHdl_CallActive(u2PduMapIndex, DCM_DSL_REQ_ACTIVE, (boolean)TRUE);

        if( Dcm_Dsl_bInteractiveClient == (boolean)FALSE )
        {
            Dcm_Dsl_bInteractiveClient = (boolean)TRUE;
            b_ChangeClient             = (boolean)TRUE;
        }
        else
        {
            b_InteractiveClient = Dcm_Dsl_Ctrl_IsRecvInteractiveClient(u2PduMapIndex);
            if( b_InteractiveClient == (boolean)FALSE )
            {
                b_ChangeClient = (boolean)TRUE;
            }
        }

        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2PduMapIndex);
        Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)TRUE);
        Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_WT_SVCOMP);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);

        Dcm_Dsl_Ctrl_SetResPendOccur((boolean)FALSE);

        if( b_ChangeClient == (boolean)TRUE )
        {
            Dcm_Dsl_Ctrl_NotifyServiceStart((boolean)FALSE, DCM_DSL_DEFAULTSESSION);
        }
        else
        {
            Dcm_Dsl_Ctrl_NotifyServiceStart((boolean)FALSE, DCM_DSL_CURRENTSESSION);
        }

        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_RECEIVE, (boolean)FALSE);
        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_RECEIVE);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ProcKeepAliveReq                            */
/* Description   | This function requests Keep-Alive Logic.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ProcKeepAliveReq
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_Ctrl_StartS3Timer(u2PduMapIndex);
#if( DCM_AUTHENTICATION_USE == STD_ON )
    Dcm_Dsl_Ctrl_StartAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    Dcm_Dsl_Ctrl_ReleaseKALResource(u2PduMapIndex);
    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_BusyTransmit                                */
/* Description   | This function handles busy response requests.            */
/*               |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1ErrorCode   : Error Code(NRC)                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_BusyTransmit
(
    const uint16                       u2PduMapIndex,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    AB_83_DcmPduInfoType  st_RxBuf;
    uint8                 u1_SID;
    uint8                 u1_DslState;
    boolean               b_NoBusyResponse;

    st_RxBuf.SduDataPtr = NULL_PTR;
    st_RxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;

    Dcm_Dsl_Ctrl_GetRxBuf(u2PduMapIndex, &st_RxBuf);
    u1_SID = Dcm_Dsd_GetDirectSID(st_RxBuf.SduDataPtr);

    b_NoBusyResponse = Dcm_Dsl_Ctrl_IsSuppressNegMsg(u2PduMapIndex, u1_SID, u1ErrorCode);
    if( b_NoBusyResponse == (boolean)FALSE )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( u1_DslState == DCM_DSL_ST_RECEIVING )
        {
            Dcm_Dsl_CmHdl_CallActive(u2PduMapIndex, DCM_DSL_REQ_ACTIVE, (boolean)FALSE);

            Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);

            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_SENDING);
            Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)TRUE);

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();

            /* Register for a busy response event. Ignore request if event registered. */
            Dcm_Dsl_Ctrl_BusyRespReq(u2PduMapIndex, u1_SID, u1ErrorCode);
        }
    }
    else
    {
#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StartAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
        Dcm_Dsl_Ctrl_ReleaseRxResource(u2PduMapIndex);
    }

    return ;
}


#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DeemedReceiveProc                           */
/* Description   | This function performs deemed reception processing.      */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptProgConditions : Pointer of ProgConditions Data   */
/*               |                                                          */
/*               | [in] u1Sid            : SID                              */
/*               | [in] u1SubFncId       : SubFunction                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeemedReceiveProc
(
    const uint16 u2PduMapIndex,
    const uint8  u1Sid,
    const uint8  u1SubFncId
)
{
    P2VAR( Dcm_Dsl_RxDataType, AUTOMATIC, DCM_APPL_DATA ) ptRxData;

    ptRxData                         = &Dcm_Dsl_stRxData[u2PduMapIndex];
    ptRxData->stRxPduInfo.SduDataPtr = &Dcm_Dsl_u1RxBuf4DeemedReception[0];
    ptRxData->stRxPduInfo.SduLength  = (AB_83_DcmPduLengthType)0U;
    ptRxData->ptRxPduAddr            = ptRxData->stRxPduInfo.SduDataPtr;

    /* Set SID/SubFunction in a reception buffer. To refer to SID at the time of P4 time-out outbreak from DSD */
    ptRxData->stRxPduInfo.SduDataPtr[DCM_DSL_IDX_REQUEST_SID] = u1Sid;
    ptRxData->stRxPduInfo.SduDataPtr[DCM_DSL_IDX_REQUEST_SFC] = u1SubFncId;

    /* Send DCM_M_EVTID_DSL_COMM_ACTIVE event. Return value ignoring */
    (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_COMM_ACTIVE);

    /* Set RxPduMapIndex. Change the state like the data reception from PduR */
    Dcm_Dsl_bInteractiveClient = (boolean)TRUE;
    Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2PduMapIndex);
    Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)TRUE);
    Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_SENDING);
    Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);

    return ;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */


#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DeemedReceiveEvent                          */
/* Description   | This function performs deemed reception processing.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptRxBuf       : ServiceRespondTo store rx buffer    */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeemedReceiveEvent
(
    const uint16          u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxBuf
)
{
    AB_83_DcmPduInfoType       st_TxBuf;
    Dcm_Dsd_DataIndicationType st_DataInd;

    st_TxBuf.SduDataPtr = NULL_PTR;
    st_TxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;

    Dcm_Dsl_Ctrl_SetDeemedReceiveEventResource(u2PduMapIndex);

    Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);

    Dcm_Dsl_Ctrl_NotifyServiceToResponseStart();

    Dcm_Dsl_Ctrl_GetDataIndParam(u2PduMapIndex, &st_DataInd.u1ReqType, &st_DataInd.u2PduId);

    Dcm_Dsl_Ctrl_GetRoeTxBuf(u2PduMapIndex, &st_TxBuf);
    Dcm_Dsd_DataIndicationFunctionality(&st_DataInd, ptRxBuf, &st_TxBuf);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ActiveDeemedReceiveProc                     */
/* Description   | This function performs deemed reception processing.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ActiveDeemedReceiveProc
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_Ctrl_SetDeemedReceiveEventResource(u2PduMapIndex);
    Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_SENDING);
    Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);

    return;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_RxErrNotification                           */
/* Description   | This function performs processing at the time of         */
/*               | receiving error notification.                            */
/* Preconditions | Arbitration type 1: Calling only from interacting or     */
/*               | high priority clients.                                   */
/*               | u2PduMapIndex transitions from receiving to idle.        */
/*               | Arbitration type 2: u2PduMapIndex transitions from       */
/*               | receiving to idle.                                       */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_RxErrNotification
(
    const uint16 u2PduMapIndex
)
{
    uint8   u1_DslState;
    boolean b_ParallelProcess;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( ( u1_DslState == DCM_DSL_ST_IDLE )
     || ( u1_DslState == DCM_DSL_ST_RECEIVING ) )
    {
        b_ParallelProcess = Dcm_Dsl_RxAbt_IsReceivingClient(u2PduMapIndex);
        if( b_ParallelProcess == (boolean)FALSE )
        {
            /* lock */
            SchM_Enter_Dcm_Dsl_Ctrl();

            Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
            Dcm_Dsl_Ctrl_ClearSaveRoePreExeState(u2PduMapIndex);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

            /* unlock */
            SchM_Exit_Dcm_Dsl_Ctrl();

            Dcm_Dsl_Ctrl_StartS3TimerCore(u2PduMapIndex, (boolean)FALSE);
        }
#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StartAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
        Dcm_Dsl_Ctrl_ReleaseRxResource(u2PduMapIndex);
    }
    Dcm_Dsl_Ctrl_ReleaseKALResource(u2PduMapIndex);

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_Confirmation                                */
/* Description   | Do Procesing after Dcm_TpTxConfirmation.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Confirmation
(
    const uint16 u2PduMapIndex
)
{
    boolean  b_ServiceToRespondTo;
    boolean  b_ActiveClient;
    boolean  b_ActiveSession;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);
    Dcm_Dsl_Ctrl_TxSrv_Clear(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        /* no process */
    }
    else
    {
        Dcm_Dsl_Ctrl_StartS3Timer(u2PduMapIndex);

#if( DCM_AUTHENTICATION_USE == STD_ON )
        Dcm_Dsl_Ctrl_StartAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

        b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession();
        if( b_ActiveSession == (boolean)FALSE )
        {
            Dcm_Dsl_Ctrl_CallInactiveAllCh();
        }
        else
        {
            b_ActiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
            Dcm_Dsl_CmHdl_CallActive(u2PduMapIndex, DCM_DSL_REQ_INACTIVE, b_ActiveClient);
        }
    }

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_ComSrv_Clear(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_TxErrNotification                           */
/* Description   | This function performs recovery processing after         */
/*               | an error occurs.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_TxErrNotification
(
    const uint16 u2PduMapIndex
)
{
    uint8 u1_DslState;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        Dcm_Dsl_TxAbt_Activate(u2PduMapIndex);
    }

    /*
     * Since resources(Dcm_Dsl_u2ResUseId) have been released by Confirmation,
     * resources will not be released by this notification
     */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_CancelService                               */
/* Description   | Call the function(Dcm_Dsd_CancelService)                 */
/*               | to cancel service.                                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CancelService
( void )
{
    Dcm_Dsd_CancelService();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_CancelConfirmation                          */
/* Description   | Call the function (Dcm_Dsl_Ctrl_TxSrv_Clear)             */
/*               | to clear datamanagemer unit data.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : Cancel PduMapIndex Value            */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CancelConfirmation
(
    const uint16 u2PduMapIndex
)
{
    boolean  b_InteractiveClient;
    uint8    u1_DslState;

    b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
    if( b_InteractiveClient == (boolean)TRUE )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
        if( u1_DslState == DCM_DSL_ST_SENDING )
        {
            Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);
        }
        Dcm_Dsl_Ctrl_TxSrv_Clear(u2PduMapIndex);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();
    }
    else
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        Dcm_Dsl_Ctrl_SetDslState(u2PduMapIndex, DCM_DSL_ST_IDLE);
        Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)FALSE);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();
    }
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ChgInteractiveClient                        */
/* Description   | This function switches clients during a conversation.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ChgInteractiveClient
( void )
{
    boolean b_ServiceToRespondTo;
    uint8   u1_DslState;
    uint16  u2_PduMapIndex;

    if( Dcm_Dsl_bInteractiveClient == (boolean)FALSE )
    {
        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_SETDEFSES);
    }
    else
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
        u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
         || ( u1_DslState == DCM_DSL_ST_SENDING ) )
        {
            u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx();
            Dcm_Dsl_TxAbt_CancelReq(u2_PduMapIndex);

            b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2_PduMapIndex);
            if( b_ServiceToRespondTo == (boolean)TRUE )
            {
#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
                Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId(u2_PduMapIndex, (boolean)FALSE);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
                Dcm_Dsl_Ctrl_ReleaseServiceToRespondToResUseId(u2_PduMapIndex);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */
            }
        }

        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        if( u1_DslState != DCM_DSL_ST_RECEIVING )
        {
            Dcm_Dsl_Ctrl_SetDslState(u2_PduMapIndex, DCM_DSL_ST_IDLE);
            Dcm_Dsl_Ctrl_ReleaseRxResource(u2_PduMapIndex);
        }
        Dcm_Dsl_Ctrl_SetResUseId(u2_PduMapIndex, (boolean)FALSE);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
        Dcm_Dsl_Ctrl_DeleteAfterRebootEvent();
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_SETDEFSES, (boolean)FALSE);

        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_SETDEFSES);

        Dcm_Dsl_CmHdl_CallActive(u2_PduMapIndex, DCM_DSL_REQ_INACTIVE, (boolean)FALSE);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsDirectKeepAliveMsg                        */
/* Description   | This function checks reception Message is Keep-Alive     */
/*               | Message or not                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/*               | [in] ptRxInfo     : DCM reception buffer                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Keep-Alive Message                   */
/*               |        FALSE      : not Keep-Alive Message               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsDirectKeepAliveMsg
(
    const uint16 u2RxPduMapIndex,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_CONST ) ptRxInfo
)
{
    uint16            u2_RowIndex;
    uint16            u2_ConnectionIndex;
    uint16            u2_ProtocolRxIndex;
    uint8             u1_Addrtype;
    boolean           b_Result;

    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);

    u1_Addrtype = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
    b_Result    = Dcm_Dsd_isKeepAliveMsg(u1_Addrtype, ptRxInfo);

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsFirstCommunication                        */
/* Description   | This function returns whether it is the first            */
/*               | communication                                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : first communication                  */
/*               |        FALSE      : After the second time                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsFirstCommunication
( void )
{
    boolean b_Result;

    b_Result = (boolean)FALSE;

    if( Dcm_Dsl_bInteractiveClient == (boolean)FALSE )
    {
        b_Result = (boolean)TRUE;
    }
    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsInteractiveClient                         */
/* Description   | This function determines whether the specified           */
/*               | PduMapIndex is a client in conversation                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Interacting client                   */
/*               |        FALSE      : not Interacting client               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsInteractiveClient
(
    const uint16 u2PduMapIndex
)
{
    uint16   u2_PduMapIndex;
    uint16   u2_ActiveGroup;
    uint16   u2_ReqGroup;
    boolean  b_Result;

    b_Result = (boolean)FALSE;

    if( Dcm_Dsl_bInteractiveClient != (boolean)FALSE )
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();
        u2_ActiveGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2_PduMapIndex);
        u2_ReqGroup    = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduMapIndex);

        if( u2_ReqGroup == u2_ActiveGroup )
        {
            b_Result = (boolean)TRUE;
        }
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsRecvInteractiveClient                     */
/* Description   | This function determines whether the specified           */
/*               | RxPduMapIndex is a client in conversation                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Interacting client                   */
/*               |        FALSE      : not Interacting client               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsRecvInteractiveClient
(
    const uint16 u2RxPduMapIndex
)
{
    uint16   u2_RxPduMapIndex;
    uint16   u2_ActiveGroup;
    uint16   u2_ReqGroup;
    boolean  b_Result;

    b_Result = (boolean)FALSE;

    if( Dcm_Dsl_bInteractiveClient != (boolean)FALSE )
    {
        u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
        u2_ActiveGroup   = Dcm_Dsl_Ctrl_GetConnectionGroup(u2_RxPduMapIndex);
        u2_ReqGroup      = Dcm_Dsl_Ctrl_GetConnectionGroup(u2RxPduMapIndex);

        if( u2_ReqGroup == u2_ActiveGroup )
        {
            b_Result = (boolean)TRUE;
        }
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsServiceToRespondTo                        */
/* Description   | This function checks if the specified PduMapindex is     */
/*               | ServiceToRespondTo                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : ServiceToRespondTo                   */
/*               |        FALSE      : not ServiceToRespondTo               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsServiceToRespondTo
(
    const uint16 u2PduMapIndex
)
{
    boolean  b_Result;

    b_Result = (boolean)FALSE;

    if( u2PduMapIndex == Dcm_Dsl_u2StrPduMapIndex )
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsBusyServiceToRespondTo                    */
/* Description   | This function checks if the ServiceToRespondTo is busy.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Processing                           */
/*               |        FALSE      : Not in process                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsBusyServiceToRespondTo
(
    const uint16 u2RxPduMapIndex
)
{
    boolean b_Result;
    boolean b_InteractiveClient;

    b_Result = (boolean)FALSE;

    if( Dcm_Dsl_u2StrPduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        b_Result = (boolean)TRUE;

        b_InteractiveClient = Dcm_Dsl_Ctrl_IsRecvInteractiveClient(u2RxPduMapIndex);
        if( b_InteractiveClient == (boolean)FALSE )
        {
            if( Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].u2ClientIndex !=
                Dcm_Dsl_PduIdMapTable[Dcm_Dsl_u2StrPduMapIndex].u2ClientIndex )
            {
                b_Result = (boolean)FALSE;
            }
        }
    }

    return b_Result;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsActiveDiag                                */
/* Description   | This function determines whether DIAG is being processed.*/
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Processing                           */
/*               |        FALSE      : Not in process                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveDiag
( void )
{
    boolean         b_Result;
    uint8           u1_DslState;
    uint16          u2_PduMapIndex;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( u1_DslState != DCM_DSL_ST_IDLE )
    {
        b_Result = (boolean)TRUE;
    }
    else
    {
        b_Result = Dcm_Dsl_RxAbt_IsReceivingDiag();
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsBusyInteractiveClient                     */
/* Description   | This function determines whether the interactive client  */
/*               | is processing.                                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Processing                           */
/*               |        FALSE      : Not in process                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsBusyInteractiveClient
( void )
{
    uint16  u2_PduMapIndex;
    uint8   u1_DslState;
    boolean b_Result;

    b_Result    = (boolean)FALSE;
    u1_DslState = DCM_DSL_ST_IDLE;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    if( Dcm_Dsl_bInteractiveClient != (boolean)FALSE )
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
        u1_DslState    = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    if( ( u1_DslState == DCM_DSL_ST_IDLE )
     || ( u1_DslState == DCM_DSL_ST_RECEIVING ) )
    {
        /* no process */
    }
    else
    {
        /* DCM_DSL_ST_RECEIVING is not included because User (Rx) does not use it for judgment */
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsActiveClient                              */
/* Description   | This function determines whether the interactive client  */
/*               | is processing.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Processing                           */
/*               |        FALSE      : Not in process                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveClient
(
    const uint16 u2PduMapIndex
)
{
    boolean b_Result;
    uint8   u1_DslState;

    b_Result = (boolean)FALSE;

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( ( u1_DslState == DCM_DSL_ST_RECEIVING )
     || ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        b_Result = (boolean)TRUE;
    }
    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsResourceInUse                             */
/* Description   | This function determines whether resources are being     */
/*               | used.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : In use                               */
/*               |        FALSE      : unused                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsResourceInUse
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_ResUseId;
    boolean b_Result;
    uint8   u1_DslState;

    b_Result = (boolean)FALSE;

    u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
    if( ( u1_DslState == DCM_DSL_ST_RECEIVING )
     || ( u1_DslState == DCM_DSL_ST_WT_SVCOMP )
     || ( u1_DslState == DCM_DSL_ST_SENDING ) )
    {
        u2_ResUseId = Dcm_Dsl_Ctrl_GetResUseId(u2PduMapIndex);
        if( u2_ResUseId == u2PduMapIndex )
        {
            b_Result = (boolean)TRUE;
        }
    }

    return b_Result;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsActiveSession                             */
/* Description   | This function determines whether the session is a        */
/*               | non-default session.                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : non-default session                  */
/*               |        FALSE      : default session                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsActiveSession
( void )
{
    boolean         b_Result;
    Dcm_SesCtrlType u1_Session;

    /* The return value is always successful */
    (void)Dcm_Dsl_SessionMng_GetSesCtrlType(&u1_Session);

    if( u1_Session != DCM_DEFAULT_SESSION )
    {
        b_Result = (boolean)TRUE;
    }
    else
    {
        b_Result = (boolean)FALSE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DataIndFunctional                           */
/* Description   | Call the Dsd-Function                                    */
/*               | (Dcm_Dsd_DataIndicationFunctionality)                    */
/*               | to notify Dsd of the first service request.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DataIndFunctional
(
    const uint16 u2RxPduMapIndex
)
{
    AB_83_DcmPduInfoType       st_RxBuf;
    AB_83_DcmPduInfoType       st_TxBuf;
    Dcm_Dsd_DataIndicationType st_DataInd;
    uint16                     u2_RowIndex;
    uint16                     u2_ConnectionIndex;
    uint16                     u2_ProtocolRxIndex;

    st_RxBuf.SduDataPtr = NULL_PTR;
    st_RxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
    st_TxBuf.SduDataPtr = NULL_PTR;
    st_TxBuf.SduLength  = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_Ctrl_ConvPMIdxToPrtclRxIdx(u2RxPduMapIndex, &u2_RowIndex, &u2_ConnectionIndex, &u2_ProtocolRxIndex);
    st_DataInd.u1ReqType = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;
    st_DataInd.u2PduId   = Dcm_Dsl_PduIdMapTable[u2RxPduMapIndex].RxPduId;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_GetRxBuf(u2RxPduMapIndex, &st_RxBuf);

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_GetTxBuf(&st_TxBuf);

    Dcm_Dsd_DataIndicationFunctionality(&st_DataInd, &st_RxBuf, &st_TxBuf);

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetS3Server                                 */
/* Description   | Get a S3Server Value.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       0U~65535U : S3Server Value                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetS3Server
( void )
{
    uint16 u2_RowIndex;
    uint16 u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();
    u2_RowIndex    = Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].u2RowIndex;

    return Dcm_Dsl_stRow[u2_RowIndex].u2S3ServerTimeout;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StartS3Timer                                */
/* Description   | Check the restart of the S3 timer.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartS3Timer
(
    const uint16 u2RxPduMapIndex
)
{
    Dcm_Dsl_Ctrl_StartS3TimerCore(u2RxPduMapIndex, (boolean)TRUE);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StartS3TimerCore                            */
/* Description   | Check the restart of the S3 timer.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/*               | [in] bParallelCheck  : TRUE  Check parallel processing.  */
/*               |                        FALSE No Check                    */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartS3TimerCore
(
    const uint16 u2RxPduMapIndex,
    const boolean bParallelCheck
)
{
    uint16  u2_S3Server;
    uint8   u1_DslState;
    boolean b_ParallelProcess;
    boolean b_SesCtrlPermission;
    boolean b_StartTimer;

    b_StartTimer = (boolean)FALSE;

    b_SesCtrlPermission = Dcm_Dsl_Ctrl_IsSesCtrlPermission(u2RxPduMapIndex);
    if( b_SesCtrlPermission == (boolean)TRUE )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Ctrl();

        /* u2RxPduMapIndex = InteractiveClient */
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2RxPduMapIndex);

        /* unlock */
        SchM_Exit_Dcm_Dsl_Ctrl();

        if( u1_DslState == DCM_DSL_ST_IDLE )
        {
            if( bParallelCheck == (boolean)TRUE )
            {
                b_ParallelProcess = Dcm_Dsl_RxAbt_IsReceivingClient(u2RxPduMapIndex);
                if( b_ParallelProcess == (boolean)FALSE )
                {
                    b_StartTimer = (boolean)TRUE;
                }
            }
            else
            {
                b_StartTimer = (boolean)TRUE;
            }
        }
    }

    if( b_StartTimer == (boolean)TRUE )
    {
        u2_S3Server = Dcm_Dsl_Ctrl_GetS3Server();
        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_S3TIMER, (uint32)u2_S3Server);
    }

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopS3Timer                                 */
/* Description   | This function stops the S3 timer.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopS3Timer
(
    const uint16 u2RxPduMapIndex
)
{
    boolean b_SesCtrlPermission;

    b_SesCtrlPermission = Dcm_Dsl_Ctrl_IsSesCtrlPermission(u2RxPduMapIndex);
    if( b_SesCtrlPermission == (boolean)TRUE )
    {
        Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_S3TIMER);
    }

    return;
}

#if( DCM_AUTHENTICATION_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StartAuthCtrl                               */
/* Description   | Control the start of the authentication timer for        */
/*               | the connection to which the specified Pdu belongs.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartAuthCtrl
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_ConnectionId;
    uint8   u1_DslState;
    boolean b_ActiveSession;
    boolean b_Authenticated;
    boolean b_AuthTimeOut;    
    boolean b_InteractiveClient;
    boolean b_ParallelProcess;
    boolean b_StartTimer;    
    boolean b_TimerRunning;

    b_StartTimer = (boolean)FALSE;
    b_AuthTimeOut = Dcm_Dsl_bAuthTimeOut;

    if( b_AuthTimeOut == (boolean)TRUE)
    {
        u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
        b_Authenticated = Dcm_Dsl_Ctrl_isClientAuthenticated(u2_ConnectionId);
        if( b_Authenticated == (boolean)TRUE )
        {
            b_TimerRunning = Dcm_Dsl_Ctrl_isAuthTimerRunning(u2_ConnectionId);
            if( b_TimerRunning == (boolean)FALSE )
            {
                /* lock */
                SchM_Enter_Dcm_Dsl_Ctrl();
                u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2PduMapIndex);
                /* unlock */
                SchM_Exit_Dcm_Dsl_Ctrl();
                if( u1_DslState == DCM_DSL_ST_IDLE )
                {
                    b_ParallelProcess = Dcm_Dsl_RxAbt_IsReceivingClient(u2PduMapIndex);
                    if( b_ParallelProcess == (boolean)FALSE )
                    {
                        b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
                        if( b_InteractiveClient == (boolean)TRUE )
                        {
                            b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession(); 
                            if( b_ActiveSession == (boolean)FALSE )
                            {
                                b_StartTimer = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            b_StartTimer = (boolean)TRUE;
                        }
                    }
                }
            }
        }
    }

    if( b_StartTimer == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_StartAuthTimer(u2_ConnectionId);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopAuthCtrl                                */
/* Description   | Control the stop of the authentication timer for         */
/*               | the connection to which the specified Pdu belongs        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthCtrl
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_ConnectionId;
    boolean b_AuthTimeOut;

    b_AuthTimeOut = Dcm_Dsl_bAuthTimeOut;

    if( b_AuthTimeOut == (boolean)TRUE)
    {
        u2_ConnectionId  = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
        Dcm_Dsl_Ctrl_StopAuthTimer(u2_ConnectionId);
    }

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetDefSes                                   */
/* Description   | Change for a default session.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDefSes
(
    const uint16 u2PduMapIndex
)
{
#if( DCM_AUTHENTICATION_USE == STD_ON )
    uint16  u2_ConnectionId;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_S3TIMER);

    DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION, (boolean)FALSE);
#if( DCM_AUTHENTICATION_USE == STD_ON )
    u2_ConnectionId = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2ClientIndex;
    Dcm_Dsl_Ctrl_SetDeauthenticate(u2_ConnectionId);
    Dcm_Dsl_Ctrl_StopAuthCtrl(u2PduMapIndex);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    Dcm_Dsl_Ctrl_CallInactiveAllCh();

    /* Return value ignoring */
    (void)Dcm_Dsl_SessionMng_SwitchModeSesCtrl(RTE_MODE_DcmSesCtrl_DEFAULT_SESSION);

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPduMapIndex                              */
/* Description   | Get a Dcm_Dsl_u2PduMapIndex Value.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       0U~65534U : Dcm_Dsl_u2PduMapIndex Value            */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduMapIndex
( void )
{
    uint16 u2_PduMapIndex;

    if( Dcm_Dsl_u2StrPduMapIndex == DCM_DSL_INVALID_U2_DATA )
    {
        u2_PduMapIndex = Dcm_Dsl_u2PduMapIndex;
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_u2StrPduMapIndex;
    }
    return u2_PduMapIndex;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduMapIndex
( void )
{
    return Dcm_Dsl_u2PduMapIndex;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetPduMapIndex                              */
/* Description   | Set a Dcm_Dsl_u2PduMapIndex Value.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetPduMapIndex
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_u2PduMapIndex = u2PduMapIndex;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRxPduMapIndex                            */
/* Description   | Get a Dcm_Dsl_u2RxPduMapIndex Value.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       0U~65534U : Dcm_Dsl_u2RxPduMapIndex Value          */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxPduMapIndex
( void )
{
    uint16 u2_RxPduMapIndex;

    if( Dcm_Dsl_u2StrPduMapIndex == DCM_DSL_INVALID_U2_DATA )
    {
        u2_RxPduMapIndex = Dcm_Dsl_u2RxPduMapIndex;
    }
    else
    {
        u2_RxPduMapIndex = Dcm_Dsl_u2StrPduMapIndex;
    }

    return u2_RxPduMapIndex;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxPduMapIndex
( void )
{
    return Dcm_Dsl_u2RxPduMapIndex;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetRxPduMapIndex                            */
/* Description   | Set a Dcm_Dsl_u2RxPduMapIndex Value.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetRxPduMapIndex
(
    const uint16 u2RxPduMapIndex
)
{
    Dcm_Dsl_u2RxPduMapIndex = u2RxPduMapIndex;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPduMapIndex4Tx                           */
/* Description   | Get a Dcm_Dsl_u2PduMapIndex Value.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       0U~65534U : Dcm_Dsl_u2PduMapIndex Value            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduMapIndex4Tx
( void )
{
    uint16 u2_PduMapIndex;

    if( Dcm_Dsl_u2StrPduMapIndex == DCM_DSL_INVALID_U2_DATA )
    {
        u2_PduMapIndex = Dcm_Dsl_u2PduMapIndex;
    }
    else
    {
        u2_PduMapIndex = Dcm_Dsl_u2StrPduMapIndex;
    }
    return u2_PduMapIndex;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx                         */
/* Description   | Get a Dcm_Dsl_u2RxPduMapIndex Value.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint16                                                   */
/*               |       0U~65534U : Dcm_Dsl_u2RxPduMapIndex Value          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxPduMapIndex4Tx
( void )
{
    uint16 u2_RxPduMapIndex;

    if( Dcm_Dsl_u2StrPduMapIndex == DCM_DSL_INVALID_U2_DATA )
    {
        u2_RxPduMapIndex = Dcm_Dsl_u2RxPduMapIndex;
    }
    else
    {
        u2_RxPduMapIndex = Dcm_Dsl_u2StrPduMapIndex;
    }

    return u2_RxPduMapIndex;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRxResource                               */
/* Description   | This function acquires the receiving resource assigned   */
/*               | to the specified ID.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex    : PduMapIndex Value                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   E_NOT_OK              : Failure                        */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_EXTBUF_ENABLE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxResource
(
    const uint16 u2PduMapIndex
)
{
    P2VAR( Dcm_Dsl_RxDataType, AUTOMATIC, DCM_APPL_DATA ) pt_RxData;
    AB_83_DcmPduInfoType   st_RxInfo;
    AB_83_DcmPduLengthType u4_RxBufSize;
    uint16                 u2_funcAddrMapIndex;
    Std_ReturnType         u1_RetVal;
    Std_ReturnType         u1_Result;
    boolean                b_ResourceInUse;

    u1_Result     = (Std_ReturnType)E_OK;
    u1_RetVal     = (Std_ReturnType)E_OK;
    u4_RxBufSize  = (AB_83_DcmPduLengthType)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].u4RxBufSize;
    pt_RxData     = &Dcm_Dsl_stRxData[u2PduMapIndex];

    /* Overwrite check */
    if( pt_RxData->stRxPduInfo.SduDataPtr == NULL_PTR )
    {
        if( Dcm_Dsl_stRxBufferTable[u2PduMapIndex].bUseExternalBuf == (boolean)TRUE )
        {
            st_RxInfo.SduDataPtr = NULL_PTR;
            st_RxInfo.SduLength  = u4_RxBufSize;

            u1_RetVal = Dcm_GetExternalBuffer(&st_RxInfo);
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                pt_RxData->stRxPduInfo.SduDataPtr = st_RxInfo.SduDataPtr;
                pt_RxData->ptRxPduAddr            = st_RxInfo.SduDataPtr;
            }
            else
            {
                u1_Result = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            pt_RxData->stRxPduInfo.SduDataPtr = (uint8 *)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].ptRxBuf;
            pt_RxData->ptRxPduAddr            = (uint8 *)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].ptRxBuf;
        }
    }
    else
    {
        /* Overwrite if allocated */
        pt_RxData->stRxPduInfo.SduDataPtr = pt_RxData->ptRxPduAddr;
    }

    if( u1_Result == (Std_ReturnType)E_OK )
    {
        b_ResourceInUse = Dcm_Dsl_Ctrl_IsResourceInUse(u2PduMapIndex);
        if( b_ResourceInUse == (boolean)FALSE )
        {
            pt_RxData->stRxPduInfo.SduLength  = (AB_83_DcmPduLengthType)0U;
            pt_RxData->RxSduLengthRmd         = u4_RxBufSize;
        }

        /* Overwrite if allocated */
        u2_funcAddrMapIndex = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2FuncAddrMapIndex;
        if( u2_funcAddrMapIndex != DCM_DSL_INVALID_U2_DATA )
        {
            Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduDataPtr    = (uint8 *)Dcm_Dsl_stKALBufferTable[u2_funcAddrMapIndex].ptRxBuf;
            Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduLength     = (AB_83_DcmPduLengthType)0U;
            Dcm_Dsl_stKALData[u2_funcAddrMapIndex].RxSduLengthRmd            = (AB_83_DcmPduLengthType)Dcm_Dsl_stKALBufferTable[u2_funcAddrMapIndex].u4RxBufSize;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_DSL_EXTBUF_ENABLE == STD_ON */
#if( DCM_DSL_EXTBUF_ENABLE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxResource
(
    const uint16 u2PduMapIndex
)
{
    P2VAR( Dcm_Dsl_RxDataType, AUTOMATIC, DCM_APPL_DATA ) pt_RxData;
    uint16                                                u2_funcAddrMapIndex;
    boolean                                               b_ResourceInUse;

    /* Overwrite if allocated */
    pt_RxData                         = &Dcm_Dsl_stRxData[u2PduMapIndex];
    pt_RxData->stRxPduInfo.SduDataPtr = (uint8 *)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].ptRxBuf;
    pt_RxData->ptRxPduAddr            = (uint8 *)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].ptRxBuf;

    b_ResourceInUse = Dcm_Dsl_Ctrl_IsResourceInUse(u2PduMapIndex);
    if( b_ResourceInUse == (boolean)FALSE )
    {
        pt_RxData->stRxPduInfo.SduLength  = (AB_83_DcmPduLengthType)0U;
        pt_RxData->RxSduLengthRmd         = (AB_83_DcmPduLengthType)Dcm_Dsl_stRxBufferTable[u2PduMapIndex].u4RxBufSize;
    }

    u2_funcAddrMapIndex = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2FuncAddrMapIndex;
    if( u2_funcAddrMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduDataPtr    = (uint8 *)Dcm_Dsl_stKALBufferTable[u2_funcAddrMapIndex].ptRxBuf;
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduLength     = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].RxSduLengthRmd            = (AB_83_DcmPduLengthType)Dcm_Dsl_stKALBufferTable[u2_funcAddrMapIndex].u4RxBufSize;
    }

    return (Std_ReturnType)E_OK;
}
#endif /* DCM_DSL_EXTBUF_ENABLE == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetKALResource                              */
/* Description   | This function gets the KAL resource with the specified   */
/*               | ID.                                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex    : PduMapIndex Value                */
/*               | [out] ptRxInfo        : RxBuffer Address/RxMsg Length    */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxInfo
)
{
    uint16 u2_funcAddrMapIndex;

    u2_funcAddrMapIndex = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2FuncAddrMapIndex;
    if( u2_funcAddrMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        if( ptRxInfo != NULL_PTR )
        {
            ptRxInfo->SduDataPtr = (uint8 *)Dcm_Dsl_stKALBufferTable[u2_funcAddrMapIndex].ptRxBuf;
            ptRxInfo->SduLength  = Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduLength;
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReleaseRxResource                           */
/* Description   | This function releases receiving resources.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseRxResource
(
    const uint16 u2PduMapIndex
)
{
    Dcm_Dsl_stRxData[u2PduMapIndex].stRxPduInfo.SduDataPtr    = NULL_PTR;
    Dcm_Dsl_stRxData[u2PduMapIndex].stRxPduInfo.SduLength     = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_stRxData[u2PduMapIndex].ptRxPduAddr               = NULL_PTR;
    Dcm_Dsl_stRxData[u2PduMapIndex].RxSduLengthRmd            = (AB_83_DcmPduLengthType)0U;
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReleaseKALResource                          */
/* Description   | This function releases the KAL resources.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseKALResource
(
    const uint16 u2PduMapIndex
)
{
    uint16 u2_funcAddrMapIndex;

    u2_funcAddrMapIndex = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2FuncAddrMapIndex;
    if( u2_funcAddrMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduDataPtr    = NULL_PTR;
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo.SduLength     = (AB_83_DcmPduLengthType)0U;
        Dcm_Dsl_stKALData[u2_funcAddrMapIndex].RxSduLengthRmd            = (AB_83_DcmPduLengthType)0U;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetRxBuf                                    */
/* Description   | Get a RxMsg Buffer Address/RxMsg Length.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptRxBuf      : RxBuffer Address/RxMsg Length       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetRxBuf
(
    const uint16 u2PduMapIndex,
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxBuf
)
{
    P2VAR( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) pt_RxInfo;

    pt_RxInfo             = &Dcm_Dsl_stRxData[u2PduMapIndex].stRxPduInfo;

    ptRxBuf->SduDataPtr   = Dcm_Dsl_stRxData[u2PduMapIndex].ptRxPduAddr;
    ptRxBuf->SduLength    = pt_RxInfo->SduLength;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetCurRxResource                            */
/* Description   | This function gets the current value of the receiving    */
/*               | resource.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptRxResInfo  : RxBuffer Address/RxMsg Length       */
/*               |                      RxBuffer Remaining Size             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetCurRxResource
(
    const uint16 u2PduMapIndex,
    P2VAR( Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxResInfo
)
{
    if( ptRxResInfo != NULL_PTR )
    {
        ptRxResInfo->ptRxPduInfo      = &Dcm_Dsl_stRxData[u2PduMapIndex].stRxPduInfo;
        ptRxResInfo->ptRxSduLengthRmd = &Dcm_Dsl_stRxData[u2PduMapIndex].RxSduLengthRmd;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetCurKALResource                           */
/* Description   | This function gets the current KAL resource.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [out] ptRxResInfo  : RxBuffer Address/RxMsg Length       */
/*               |                      RxBuffer Remaining Size             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_GetCurKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR( Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxResInfo
)
{
    uint16 u2_funcAddrMapIndex;

    u2_funcAddrMapIndex = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2FuncAddrMapIndex;
    if( u2_funcAddrMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        if( ptRxResInfo != NULL_PTR )
        {
            ptRxResInfo->ptRxPduInfo      = &Dcm_Dsl_stKALData[u2_funcAddrMapIndex].stRxPduInfo;
            ptRxResInfo->ptRxSduLengthRmd = &Dcm_Dsl_stKALData[u2_funcAddrMapIndex].RxSduLengthRmd;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetDslState                                 */
/* Description   | Get a Dsl state.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | uint8                                                    */
/*               |        DSL State : DCM_DSL_ST_IDLE                       */
/*               |                  : DCM_DSL_ST_RECEIVING                  */
/*               |                  : DCM_DSL_ST_WT_SVCOMP                  */
/*               |                  : DCM_DSL_ST_SENDING                    */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsl_Ctrl_GetDslState
(
    const uint16 u2PduMapIndex
)
{
    uint16   u2_ReqGroup;

    u2_ReqGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduMapIndex);

    /* Get Dsl State */
    return Dcm_Dsl_u1DslState[u2_ReqGroup];
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetDslState                                 */
/* Description   | Set a Dsl state.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] u1State : DCM_DSL_ST_IDLE                           */
/*               |              : DCM_DSL_ST_RECEIVING                      */
/*               |              : DCM_DSL_ST_WT_SVCOMP                      */
/*               |              : DCM_DSL_ST_SENDING                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDslState
(
    const uint16 u2PduMapIndex,
    const uint8  u1State
)
{
    uint16   u2_ReqGroup;

    u2_ReqGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduMapIndex);

    /* Set Dsl State */
    Dcm_Dsl_u1DslState[u2_ReqGroup] = u1State;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetResUseId                                 */
/* Description   | This function gets the resource use Pdu.                 */
/* Preconditions | u2PduMapIndex is a valid value.                          */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | uint16                                                   */
/*               |      0x0000~0xFFFFU : PduMapIndex Value                  */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetResUseId
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_ReqGroup;

    u2_ReqGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduMapIndex);
    return Dcm_Dsl_u2ResUseId[u2_ReqGroup];
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetResUseId                                 */
/* Description   | This function sets the resource use Pdu.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] bUseResource  : TRUE(use)                           */
/*               |                    : FALSE(unuse)                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetResUseId
(
    const uint16 u2PduMapIndex,
    const boolean bUseResource
)
{
    uint16   u2_ReqGroup;

    u2_ReqGroup = Dcm_Dsl_Ctrl_GetConnectionGroup(u2PduMapIndex);

    if( bUseResource == (boolean)TRUE )
    {
        Dcm_Dsl_u2ResUseId[u2_ReqGroup] = u2PduMapIndex;
    }
    else
    {
        Dcm_Dsl_u2ResUseId[u2_ReqGroup] = DCM_DSL_INVALID_U2_DATA;
    }

    return ;
}

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId               */
/* Description   | This function sets the resource use Pdu for ServiceTo.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] bUseResource  : TRUE(use)                           */
/*               |                    : FALSE(unuse)                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId
(
    const uint16 u2PduMapIndex,
    const boolean bUseResource
)
{
    uint16   u2_ActivePduMapIndex;

    u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    if( bUseResource == (boolean)TRUE )
    {
        /* Block interactive client resources */
        Dcm_Dsl_Ctrl_SetResUseId(u2_ActivePduMapIndex, (boolean)TRUE);
        if( u2PduMapIndex != u2_ActivePduMapIndex )
        {
            Dcm_Dsl_u1SaveRoePreExeState = Dcm_Dsl_Ctrl_GetDslState(u2_ActivePduMapIndex);
            Dcm_Dsl_Ctrl_SetDslState(u2_ActivePduMapIndex, DCM_DSL_ST_WT_SVCOMP);
        }
        Dcm_Dsl_u2StrPduMapIndex = u2PduMapIndex;
    }
    else
    {
        if( Dcm_Dsl_bFirstServiceToRespondTo == (boolean)TRUE )
        {
            Dcm_Dsl_bFirstServiceToRespondTo = (boolean)FALSE;
            Dcm_Dsl_bInteractiveClient       = (boolean)FALSE;
            Dcm_Dsl_u2PduMapIndex            = (uint16)0U;
            Dcm_Dsl_u2RxPduMapIndex          = (uint16)0U;
        }

        /* Interactive client resource release */
        Dcm_Dsl_Ctrl_SetResUseId(u2_ActivePduMapIndex, (boolean)FALSE);

        if( Dcm_Dsl_u1SaveRoePreExeState == DCM_DSL_ST_RECEIVING )
        {
            Dcm_Dsl_Ctrl_SetDslState(u2_ActivePduMapIndex, DCM_DSL_ST_RECEIVING);
        }
        else
        {
            Dcm_Dsl_Ctrl_SetDslState(u2_ActivePduMapIndex, DCM_DSL_ST_IDLE);
        }

        Dcm_Dsl_u2StrPduMapIndex = DCM_DSL_INVALID_U2_DATA;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ClearSaveRoePreExeState                     */
/* Description   | This function clears saved information for ROE           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduMapIndex : PduMapIndex Value                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ClearSaveRoePreExeState
(
    const uint16 u2RxPduMapIndex
)
{
    uint16   u2_RxPduMapIndex;

    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
    if( u2_RxPduMapIndex == u2RxPduMapIndex )
    {
        Dcm_Dsl_u1SaveRoePreExeState = DCM_DSL_ST_IDLE;
    }

    return ;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */

#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReleaseServiceToRespondToResUseId           */
/* Description   | This function sets the resource use Pdu for ServiceTo.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReleaseServiceToRespondToResUseId
(
    const uint16 u2PduMapIndex
)
{
    uint16   u2_ActivePduMapIndex;

    u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    if( Dcm_Dsl_bFirstServiceToRespondTo == (boolean)TRUE )
    {
        Dcm_Dsl_bFirstServiceToRespondTo = (boolean)FALSE;
        Dcm_Dsl_bInteractiveClient       = (boolean)FALSE;
        Dcm_Dsl_u2PduMapIndex            = (uint16)0U;
        Dcm_Dsl_u2RxPduMapIndex          = (uint16)0U;
    }

    Dcm_Dsl_Ctrl_SetResUseId(u2_ActivePduMapIndex, (boolean)FALSE);
    Dcm_Dsl_u2StrPduMapIndex = DCM_DSL_INVALID_U2_DATA;

    return;
}
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */

#if( DCM_DSL_ROE_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetDeemedReceiveEventResource               */
/* Description   | This function sets the resource use Pdu for ServiceTo.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeemedReceiveEventResource
(
    const uint16 u2PduMapIndex
)
{
    if( Dcm_Dsl_bInteractiveClient == (boolean)FALSE )
    {
        /* Change the state like the data reception from PduR */
        Dcm_Dsl_bInteractiveClient = (boolean)TRUE;
        Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2PduMapIndex);
        Dcm_Dsl_Ctrl_SetPduMapIndex(u2PduMapIndex);
        Dcm_Dsl_bFirstServiceToRespondTo = (boolean)TRUE;
    }

    Dcm_Dsl_Ctrl_SetResUseId(u2PduMapIndex, (boolean)TRUE);

#if( DCM_DSL_ARBT_TYPE1 == STD_ON )
    Dcm_Dsl_Ctrl_SetServiceToRespondToResUseId(u2PduMapIndex, (boolean)TRUE);
#endif /* DCM_DSL_ARBT_TYPE1 == STD_ON */
#if( DCM_DSL_ARBT_TYPE1 == STD_OFF )
    Dcm_Dsl_u2StrPduMapIndex = u2PduMapIndex;
#endif /* DCM_DSL_ARBT_TYPE1 == STD_OFF */

    return ;
}
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_Abort                                       */
/* Description   | This function aborts Dsl Subcomponent processing.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Abort
( void )
{
    uint16  u2_PduMapIndex;

    u2_PduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();

    Dcm_Dsd_CancelService();

    Dcm_Dsl_Ctrl_StopTimers();

    /* Return value ignoring */
    (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_CANCELRECEIVE, (boolean)FALSE);

    Dcm_Dsl_Ctrl_SetSesCtrlType(DCM_DEFAULT_SESSION, (boolean)FALSE);
#if( DCM_AUTHENTICATION_USE == STD_ON )
    Dcm_Dsl_Ctrl_SetDeauthenticateAll();
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    Dcm_Dsl_Ctrl_Confirmation(u2_PduMapIndex);

    /* Return value ignoring */
    (void)Dcm_Dsd_DataConfirmationFunctionality(DCM_RES_NEG_NOT_OK, (boolean)FALSE);

    Dcm_Dsl_CmHdl_CallInactiveAllCh();

    /* Dcm_Dsl_RxAbt_Init() need not call */
    /* Dcm_Dsl_CmHdl_Init() should not call, because u1ComModeState is NoCoM */

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    Dcm_Dsl_Ctrl_Init();
    Dcm_Dsl_TxAbt_Abort();
    Dcm_Dsl_RxMsg_Init();

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopTimers                                  */
/* Description   | This function stops various timers                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopTimers
( void )
{
#if( DCM_AUTHENTICATION_USE == STD_ON )
    boolean b_AuthTimeOut;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

    Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_RXFSTIMER);
    Dcm_Dsl_Ctrl_StopTxTimers();
    
#if( DCM_AUTHENTICATION_USE == STD_ON )
    b_AuthTimeOut = Dcm_Dsl_bAuthTimeOut;
    if( b_AuthTimeOut == (boolean)TRUE )
    {
        Dcm_Dsl_Ctrl_StopAuthAllTimers();
    }
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_CallInactiveAllCh                           */
/* Description   | This function makes the channel of the idle client       */
/*               | inactive.                                                */
/* Preconditions | InteractiveClient state is idle                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_CallInactiveAllCh
( void )
{
    uint16  u2_Cnt;
    uint16  u2_ClientNumMax;
    uint16  u2_InteractiveClient;
    uint16  u2_PduMapIndex;
    uint16  u2_ActivePduMapIndex;
    boolean b_ActiveClient;

    u2_ClientNumMax      = Dcm_Dsl_u2ClientNum;
    u2_ActivePduMapIndex = Dcm_Dsl_Ctrl_GetPduMapIndex();
    u2_InteractiveClient = Dcm_Dsl_PduIdMapTable[u2_ActivePduMapIndex].u2ClientIndex;

    for( u2_Cnt = (uint16)0U; u2_Cnt < u2_ClientNumMax; u2_Cnt++ )
    {
        if( Dcm_Dsl_u1DslState[u2_Cnt] == DCM_DSL_ST_IDLE )
        {
            if( u2_InteractiveClient == u2_Cnt )
            {
                b_ActiveClient = (boolean)TRUE;
            }
            else
            {
                b_ActiveClient= (boolean)FALSE;
            }
            u2_PduMapIndex = Dcm_Dsl_ConnectionIdMapTable[u2_Cnt];
            Dcm_Dsl_CmHdl_CallActive(u2_PduMapIndex, DCM_DSL_REQ_INACTIVE, b_ActiveClient);
        }
    }

    return;
}

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_DeleteAfterRebootEvent                      */
/* Description   | This function deletes the event related to the response  */
/*               | after ECU reset.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_DeleteAfterRebootEvent
( void )
{
    /* Return value ignoring */
    (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_COMM_ACTIVE, (boolean)TRUE);
    /* Return value ignoring */
    (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_RESPREQ_AFRST, (boolean)TRUE);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_GetPduIdMapIndexBySourceAddr                */
/* Description   | Look for a Index of PduIdMap from Source Addrress        */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2TesterSourceAddr : Source Addrress of Tester     */
/* Return Value  | uint16                                                   */
/*               |      Index of PduIdMap                                   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( uint16, DCM_CODE ) Dcm_Dsl_Ctrl_GetPduIdMapIndexBySourceAddr
(
    const uint16 u2TesterSourceAddr
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_RowType, AUTOMATIC, DCM_APPL_CONST ) pt_Row;
    uint16          u2_RowIndex;
    uint16          u2_ConnectionIndex;
    uint16          u2_ProtocolRxIndex;
    uint16          u2_ProtocolRxTesterSourceAddr;
    uint16          u2_PduIdNumMax;
    uint16          u2_PduMapIndex;
    uint16          u2_Result;
    uint8           u1_AddrType;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;
    pt_Row         = &Dcm_Dsl_stRow[0];
    u2_Result      = DCM_DSL_INVALID_U2_DATA;

    for( u2_PduMapIndex = (uint16)0U; u2_PduMapIndex < u2_PduIdNumMax; u2_PduMapIndex++ )
    {
        Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
        u2_ProtocolRxTesterSourceAddr = pt_Row[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].u2ProtocolRxTesterSourceAddr;

        if( u2_ProtocolRxTesterSourceAddr == u2TesterSourceAddr )
        {
            u2_ProtocolRxIndex  = Dcm_Dsl_PduIdMapTable[u2_PduMapIndex].u2ProtocolRxIndex;
            u1_AddrType         = pt_Row[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolRx[u2_ProtocolRxIndex].u1AddrType;

            if( u1_AddrType == DCM_DSL_ADDINFO_PHYS )
            {
                u2_Result = u2_PduMapIndex;
                break;
            }
        }
    }

    return u2_Result;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-6-2         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-08-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
