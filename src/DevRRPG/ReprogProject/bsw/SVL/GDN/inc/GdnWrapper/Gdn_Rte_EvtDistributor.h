/* Gdn_Rte_EvtDistributor_h_00_0003 */
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
/*  00_0003   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_RTE_EVT_DISTRIBUTOR_H
#define GDN_RTE_EVT_DISTRIBUTOR_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include "Gdn_Rte_EvtDistributor_Cfg.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_RTE_TASK_ASYNC_TIMEOUT       (0UL)
#define GDN_RTE_TASK_SYNC                (0x7FUL)   /* 同期イベント */

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/
typedef P2FUNC(void, GDN_CALLOUT_CODE, Gdn_Rte_EventFuncType)
(
    CONST(gdn_uint32, AUTOMATIC) t_Parameter[]
);

/* イベント構造体 */
typedef struct {
    gdn_uint32              EventId;    /* EventId        */
    gdn_uint32              SyncAsync;  /* 同期非同期情報 */
    Gdn_Rte_EventFuncType   Event;      /* 受信関数       */
} Gdn_Rte_EventAttr;

/* Event Queue使用状態 */
typedef struct {
    gdn_uint16  WriteIndex;             /* 書き込みindex */
    gdn_uint16  ReadIndex;              /* 読み込みindex */
    gdn_uint16  Count;                  /* 使用中Queue数 */
} Gdn_EventQueue;

/*----------------------------------------------------------------------------*/
/* External Variables                                                         */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CODE_SLOW) Gdn_Rte_SendEvent
(
    VAR(gdn_uint32, AUTOMATIC) EventId,
    VAR(gdn_uint32, AUTOMATIC) ParamNum,
    P2CONST(gdn_uint32, AUTOMATIC, GDN_APPL_CONST) Param
);
FUNC(void, GDN_CODE_SLOW) Gdn_Rte_DequeueEvent_TimeOut
(
    VAR(gdn_uint16, AUTOMATIC) DequeueNum
);
FUNC(void, GDN_CODE_SLOW) Gdn_EvtDistributor_Init (void);

#endif /* GDN_RTE_EVT_DISTRIBUTOR_H */
/**** End of File *************************************************************/
