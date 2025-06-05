/* EthSwt_SWIC_STM.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_STM_Cfg.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_STM_CFG_H
#define ETHSWT_SWIC_STM_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Init.h>
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_SWIC_Port.h>
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
typedef void (*EthSwt_HiPorcFunc)(void);
typedef struct {
    EthSwt_HiPorcFunc           uninitFunc;
    EthSwt_HiPorcFunc           initFunc;
    EthSwt_HiPorcFunc           portInitCompletedFunc;
    EthSwt_HiPorcFunc           setRelayOnFunc;
    EthSwt_HiPorcFunc           activeFunc;
    EthSwt_HiPorcFunc           setRelayOffFunc;
} EthSwt_HiProcFuncList;
const EthSwt_HiProcFuncList G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED       , SET_RELAY_ON              , ACTIVE                        , SET_RELAY_OFF      */
    {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                  , EthSwt_SWIC_Link_TimerUpdate  , NULL_PTR              }   /* リンク状態取得 */
};
#define D_ETHSWT_SWIC_HIPROC_FUNC_NUM       (sizeof(G_ETHSWT_SWIC_HIPROC_FUNC_TABLE) / sizeof(G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[0]))


typedef Std_ReturnType (*EthSwt_registerAccessFunc)(uint32 * const);
typedef struct {
    EthSwt_registerAccessFunc   uinitFunc;
    EthSwt_registerAccessFunc   initFunc;
    EthSwt_registerAccessFunc   portInitCompletedFunc;
    EthSwt_registerAccessFunc   setRelayOnFunc;
    EthSwt_registerAccessFunc   activeFunc;
    EthSwt_registerAccessFunc   setRelayOffFunc;
} EthSwt_backgroundFuncList;
const EthSwt_backgroundFuncList G_ETHSWT_SWIC_BACK_FUNC_TABLE[] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED       , SET_RELAY_ON                          , ACTIVE                    , SET_RELAY_OFF      */
    {   NULL_PTR                , EthSwt_SWIC_Init_Setting  , NULL_PTR                  , NULL_PTR                              , NULL_PTR                  , NULL_PTR                  }   /* 初期レジスタ設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , EthSwt_SWIC_Port_RelayOn              , NULL_PTR                  , NULL_PTR                  }   /* 中継開始設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , NULL_PTR                  , EthSwt_SWIC_Port_RelayOff }   /* 中継停止設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Link_Action   , NULL_PTR                  }   /* リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Link_FastGet  , NULL_PTR                  }   /* 高速リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Port_Action   , NULL_PTR                  }   /* ポートモード制御 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , EthSwt_SWIC_Port_ResetSwitchPortMode  , NULL_PTR                  , NULL_PTR                  }   /* [注意：中継開始よりも後に入れる]リセット時のポート復帰 */
};
#define D_ETHSWT_SWIC_BACK_FUNC_NUM         (sizeof(G_ETHSWT_SWIC_BACK_FUNC_TABLE) / sizeof(G_ETHSWT_SWIC_BACK_FUNC_TABLE[0]))
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_STM_CFG_H */
/* -------------------------------------------------------------------------- */
