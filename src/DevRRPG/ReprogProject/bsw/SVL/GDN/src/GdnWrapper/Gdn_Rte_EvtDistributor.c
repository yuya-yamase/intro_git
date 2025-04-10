/* Gdn_Rte_EvtDistributor_c_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | Event Distributor                                            */
/* Notes       | NonOS用ラッパー                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2015/01/21   DN野田   新規作成                                  */
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2019/12/03   AUBASS   Update                                    */
/*  00_0003   2022/06/07   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include "Gdn_Std_Lib.h"
#include "Gdn_Rte_EvtDistributor.h"
#include "Gdn_LocalNotification.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/
/* Event Queue情報 */
typedef struct {
    gdn_uint32*     QueuePtr;   /* Queueポインタ */
    gdn_uint16      QueueSize;  /* Queueサイズ */
} Gdn_EventQueueAttr;

/*----------------------------------------------------------------------------*/
/* External Variables                                                         */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/* Event Queue使用状態 */
static Gdn_EventQueue Gdn_EventQueueInfo;

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
static Gdn_Std_ReturnType  Gdn_SendAsyncEvent( gdn_uint32 EventId, const gdn_uint32* Param, gdn_uint32 ParamNum);
static void Gdn_ReceiveAsyncEvent( gdn_uint16 DequeueNum, gdn_uint32 Buff[] );

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/* Event Queue */
static gdn_uint32 Gdn_EventQueueTimeOut[ GDN_CFG_EVNET_QUEUE_MAX_TIMEOUT ];

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/* Event Queue情報 */
static GdnConst Gdn_EventQueueAttr gdn_EventQueueAttrTable = {
    &Gdn_EventQueueTimeOut[0], GDN_CFG_EVNET_QUEUE_MAX_TIMEOUT
};

static GdnConst Gdn_Rte_EventAttr Gdn_Dcm_Dcp_EvtInfo[] = {
    /* サービス実行要求 */
    {
        GDN_DCM_DCP_EVENTID_SERVICE_PROCESSING,
    #if (REPROG_CFG_ETH_USE == STD_ON)
        GDN_RTE_TASK_ASYNC_TIMEOUT,
    #else
        GDN_RTE_TASK_SYNC,
    #endif
        &Gdn_Dcm_Dcp_ServiceProcessingFuncTask
    },
    /* サービス応答要求 */
    {
        GDN_DCM_DCP_EVENTID_SERVICE_DONE,
    #if ( (REPROG_CFG_ETH_USE == STD_ON) || (REPROG_CFG_CXPI_USE == STD_ON) )
        GDN_RTE_TASK_ASYNC_TIMEOUT,
    #else
        GDN_RTE_TASK_SYNC,
    #endif
        &Gdn_Dcm_Dcp_ProcessingDoneFuncTask
    },
    /* セッション遷移通知 */
    {
        GDN_DCM_DCP_EVENTID_SESSION_TRANSITION,
        GDN_RTE_TASK_SYNC,
        &Gdn_Dcm_Dcp_SessionTransitionFuncTask
    },
    #if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    /* サブマイコンゲートウェイ実行要求 */
    {
        GDN_DCM_DCP_EVENTID_SUB_SERVICE_GW,
        GDN_RTE_TASK_SYNC,
        &Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask
    }
    #endif  /* REPROG_CFG_SUBMICON_USE_MAIN == STD_ON */
};

static GdnConst gdn_uint8 Gdn_Dcm_Dcp_EvtInfo_Num = (sizeof(Gdn_Dcm_Dcp_EvtInfo) / sizeof(Gdn_Dcm_Dcp_EvtInfo[0]));


#define GDN_WRAPPER_STOP_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_WRAPPER_START_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_Rte_SendEvent                                          */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CODE_SLOW) Gdn_Rte_SendEvent
(
    VAR(gdn_uint32, AUTOMATIC) EventId,
    VAR(gdn_uint32, AUTOMATIC) ParamNum,
    P2CONST(gdn_uint32, AUTOMATIC, GDN_APPL_CONST) Param
)
{
    gdn_uint32          i;
    gdn_uint32          EvtNum;
    Gdn_Std_ReturnType  Result;

    Result = GDN_E_NOT_OK;
    EvtNum = Gdn_Dcm_Dcp_EvtInfo_Num;

    for( i = 0UL; i < EvtNum; i++ ) {
        if ( Gdn_Dcm_Dcp_EvtInfo[i].EventId == EventId ) {
            if ( Gdn_Dcm_Dcp_EvtInfo[i].SyncAsync == GDN_RTE_TASK_SYNC ) {
                Gdn_Dcm_Dcp_EvtInfo[i].Event(Param);
                Result = GDN_E_OK;
            } else {
                Result = Gdn_SendAsyncEvent(EventId, Param, ParamNum);
            }
            break;
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | Gdn_Rte_DequeueEvent_TimeOut                               */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_Rte_DequeueEvent_TimeOut
(
    VAR(gdn_uint16, AUTOMATIC) DequeueNum
)
{
    gdn_uint32  Buff[ GDN_TASK_PARAM_MAX_TIMEOUT ];
    gdn_uint8   i;

    for ( i = 0U; i < (gdn_uint8)GDN_TASK_PARAM_MAX_TIMEOUT; i++ ) {
        Buff[i] = 0UL;
    }

    Gdn_ReceiveAsyncEvent( DequeueNum, &Buff[0] );
}

/******************************************************************************/
/* Function Name | Gdn_EvtDistributor_Init                                    */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_EvtDistributor_Init (void)
{
    Gdn_EventQueueInfo.WriteIndex = (gdn_uint16)0U;
    Gdn_EventQueueInfo.ReadIndex = (gdn_uint16)0U;
    Gdn_EventQueueInfo.Count = (gdn_uint16)0U;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_SendAsyncEvent                                         */
/******************************************************************************/
static Gdn_Std_ReturnType  Gdn_SendAsyncEvent( gdn_uint32 EventId, const gdn_uint32* Param, gdn_uint32 ParamNum)
{
    gdn_uint32*         QueuePtr;
    gdn_uint32          i;
    gdn_uint16          QueueSize;
    gdn_uint16          Count;
    gdn_uint16          TotalNum;
    gdn_uint16          WriteIndex;
    Gdn_Std_ReturnType  Result;

    QueueSize = gdn_EventQueueAttrTable.QueueSize;
    Result    = GDN_E_NOT_OK;

    Gdn_DI();

    Count = Gdn_EventQueueInfo.Count;
    TotalNum = (gdn_uint16)1U + (gdn_uint16)1U + (gdn_uint16)ParamNum;

    if ( ( Count + TotalNum ) <= QueueSize ) {    /* Over Flow Check */
        Result   = GDN_E_OK;

        /* イベントをQueueへ登録 */
        QueuePtr = gdn_EventQueueAttrTable.QueuePtr;
        WriteIndex = Gdn_EventQueueInfo.WriteIndex;

        /* イベントID登録 */
        QueuePtr[WriteIndex] = EventId;
        WriteIndex++;       /* no wrap around */
        if ( WriteIndex >= QueueSize ) {
            WriteIndex = (gdn_uint16)0U;
        }

        /* パラメータ数登録 */
        QueuePtr[WriteIndex] = ParamNum;
        WriteIndex++;       /* no wrap around */
        if ( WriteIndex >= QueueSize ) {
            WriteIndex = (gdn_uint16)0U;
        }

        /* パラメータ登録 */
        for ( i = 0UL; i < ParamNum; i++ ) {
            QueuePtr[WriteIndex] = Param[i];
            WriteIndex++;   /* no wrap around */
            if ( WriteIndex >= QueueSize ) {
                WriteIndex = (gdn_uint16)0U;
            }
        }

        Gdn_EventQueueInfo.Count += TotalNum;   /* no wrap around */
        Gdn_EventQueueInfo.WriteIndex = WriteIndex;
    }

    Gdn_EI();

    return Result;
}

/******************************************************************************/
/* Function Name | Gdn_ReceiveAsyncEvent                                      */
/******************************************************************************/
static void Gdn_ReceiveAsyncEvent( gdn_uint16 DequeueNum, gdn_uint32 Buff[] )
{
    const gdn_uint32*   QueuePtr;
    gdn_uint32          RteEventId;
    gdn_uint32          ParamNum;
    gdn_uint32          EvtNum;
    gdn_uint32          i;
    gdn_uint16          QueueSize;
    gdn_uint16          Count;
    gdn_uint16          TotalNum;
    gdn_uint16          ReadIndex;
    gdn_uint16          LoopNum;

    QueuePtr = gdn_EventQueueAttrTable.QueuePtr;
    QueueSize = gdn_EventQueueAttrTable.QueueSize;
    LoopNum = 0U;

    Count = Gdn_EventQueueInfo.Count;
    EvtNum = Gdn_Dcm_Dcp_EvtInfo_Num;

    while ( ( Count > (gdn_uint16)0U ) && ( ( DequeueNum == (gdn_uint16)0U ) || ( LoopNum < DequeueNum ) ) ) {
        ReadIndex = Gdn_EventQueueInfo.ReadIndex;

        /* イベントID取得 */
        RteEventId = QueuePtr[ReadIndex];
        ReadIndex++;        /* no wrap around */
        if ( ReadIndex >= QueueSize ) {
            ReadIndex = (gdn_uint16)0U;
        }

        /* パラメータ数取得 */
        ParamNum = QueuePtr[ReadIndex];
        ReadIndex++;        /* no wrap around */
        if ( ReadIndex >= QueueSize ) {
            ReadIndex = (gdn_uint16)0U;
        }

        /* パラメータ取得 */
        for ( i = 0UL; i < ParamNum; i++ ) {
            Buff[i] = QueuePtr[ReadIndex];
            ReadIndex++;    /* no wrap around */
            if ( ReadIndex >= QueueSize ) {
                ReadIndex = (gdn_uint16)0U;
            }
        }
        TotalNum = (gdn_uint16)1U + (gdn_uint16)1U + (gdn_uint16)ParamNum;
        Count -= TotalNum;  /* no wrap around */

        Gdn_DI();

        Gdn_EventQueueInfo.Count -= TotalNum;   /* no wrap around */
        Gdn_EventQueueInfo.ReadIndex = ReadIndex;

        Gdn_EI();

        /* 非同期イベント発行 */
        for( i = 0UL; i < EvtNum; i++ ) {
            if ( Gdn_Dcm_Dcp_EvtInfo[i].EventId == RteEventId ) {
                if ( Gdn_Dcm_Dcp_EvtInfo[i].SyncAsync == GDN_RTE_TASK_ASYNC_TIMEOUT ) {
                    Gdn_Dcm_Dcp_EvtInfo[i].Event(Buff);
                }
                break;
            }
        }
        LoopNum++;

    }
}

#define GDN_WRAPPER_STOP_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/**** End of File *************************************************************/
