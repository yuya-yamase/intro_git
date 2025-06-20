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
#include <EthSwt_SWIC_Spi.h>
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_SWIC_Port.h>
#include <EthSwt_SWIC_Time.h>
#include <EthSwt_SWIC_STM.h>
/* -------------------------------------------------------------------------- */
typedef void (*EthSwt_InitFunc)(void);
const EthSwt_InitFunc G_ETHSWT_SWIC_INIT_FUNC_LIST[] = 
{
    EthSwt_SWIC_Spi_Init
,	EthSwt_SWIC_Link_Init
,	EthSwt_SWIC_Port_Init
,   EthSwt_SWIC_Time_Init
};
#define D_ETHSWT_SWIC_INIT_FUNC_NUM     (sizeof(G_ETHSWT_SWIC_INIT_FUNC_LIST) / sizeof(G_ETHSWT_SWIC_INIT_FUNC_LIST[0]))


typedef void (*EthSwt_HiPorcFunc)(void);
const EthSwt_HiPorcFunc G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[][D_ETHSWT_SWIC_ST_NUM] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED       , SET_RELAY_ON              , ACTIVE                        , SET_RELAY_OFF             */
    {   EthSwt_SWIC_Time_HiProc , EthSwt_SWIC_Time_HiProc   , EthSwt_SWIC_Time_HiProc   , EthSwt_SWIC_Time_HiProc   , EthSwt_SWIC_Time_HiProc       , EthSwt_SWIC_Time_HiProc   }   /* タイマ更新 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                  , EthSwt_SWIC_Link_TimerUpdate  , NULL_PTR                  }   /* リンク状態取得 */
};
#define D_ETHSWT_SWIC_HIPROC_FUNC_NUM   (sizeof(G_ETHSWT_SWIC_HIPROC_FUNC_TABLE) / sizeof(G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[0]))


typedef Std_ReturnType (*EthSwt_registerAccessFunc)(uint32 * const);
const EthSwt_registerAccessFunc G_ETHSWT_SWIC_BACK_FUNC_TABLE[][D_ETHSWT_SWIC_ST_NUM] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED       , SET_RELAY_ON                          , ACTIVE                    , SET_RELAY_OFF      */
    {   NULL_PTR                , EthSwt_SWIC_Init_Setting  , NULL_PTR                  , NULL_PTR                              , NULL_PTR                  , NULL_PTR                  }   /* 初期レジスタ設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , EthSwt_SWIC_Port_RelayOn              , NULL_PTR                  , NULL_PTR                  }   /* 中継開始設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , NULL_PTR                  , EthSwt_SWIC_Port_RelayOff }   /* 中継停止設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Link_Action   , NULL_PTR                  }   /* リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Link_FastGet  , NULL_PTR                  }   /* 高速リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                  , NULL_PTR                              , EthSwt_SWIC_Port_Action   , NULL_PTR                  }   /* ポートモード制御 */
};
#define D_ETHSWT_SWIC_BACK_FUNC_NUM         (sizeof(G_ETHSWT_SWIC_BACK_FUNC_TABLE) / sizeof(G_ETHSWT_SWIC_BACK_FUNC_TABLE[0]))


typedef void (*EthSwt_ClearFunc)(void);
const EthSwt_ClearFunc G_ETHSWT_SWIC_CLEAR_FULC_LIST[] = 
{
    EthSwt_SWIC_Link_Init
};
#define D_ETHSWT_SWIC_CLEAR_FUNC_NUM    (sizeof(G_ETHSWT_SWIC_CLEAR_FULC_LIST) / sizeof(G_ETHSWT_SWIC_CLEAR_FULC_LIST[0]))

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_STM_CFG_H */
/* -------------------------------------------------------------------------- */
