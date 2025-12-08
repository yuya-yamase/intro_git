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
#include <EthSwt_SWIC_SQI.h>
#include <EthSwt_SWIC_IntErr.h>
#include <EthSwt_SWIC_Time.h>
#include <EthSwt_SWIC_STM.h>
#include <EthSwt_SWIC_RstDtct.h>
#include <EthSwt_SWIC_MIB.h>
#include <EthSwt_SWIC_Qci.h>
#include <EthSwt_SWIC_RegAccess.h>
/* -------------------------------------------------------------------------- */
typedef void (*EthSwt_InitFunc)(void);
const EthSwt_InitFunc G_ETHSWT_SWIC_STM_INITLIST[] = 
{
    EthSwt_SWIC_Spi_Init
,	EthSwt_SWIC_Port_Init
,   EthSwt_SWIC_Time_Init
,	EthSwt_SWIC_IntErr_Init
,	EthSwt_SWIC_RstDtct_Init
,	EthSwt_SWIC_Link_Init
,	EthSwt_SWIC_SQI_Init
,   EthSwt_SWIC_MIB_Init
,   EthSwt_SWIC_Qci_Init
,   EthSwt_SWIC_RegAccess_Init
};
#define D_ETHSWT_SWIC_STM_INITFUNC_NUM     (sizeof(G_ETHSWT_SWIC_STM_INITLIST) / sizeof(G_ETHSWT_SWIC_STM_INITLIST[0]))


typedef void (*EthSwt_HiPorcFunc)(void);
const EthSwt_HiPorcFunc G_ETHSWT_SWIC_STM_HIPROCTABLE[][D_ETHSWT_SWIC_ST_NUM] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED               , SET_RELAY_ON                      , ACTIVE                            , SET_RELAY_OFF         */
    {   EthSwt_SWIC_Time_HiProc , EthSwt_SWIC_Time_HiProc   , EthSwt_SWIC_Time_HiProc           , EthSwt_SWIC_Time_HiProc           , EthSwt_SWIC_Time_HiProc           , EthSwt_SWIC_Time_HiProc           }   /* タイマ更新 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_IntErr_TimerUpdate    , EthSwt_SWIC_IntErr_TimerUpdate    , EthSwt_SWIC_IntErr_TimerUpdate    , EthSwt_SWIC_IntErr_TimerUpdate    }   /* 内部エラー検出 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_RstDtct_TimerUpdate   , EthSwt_SWIC_RstDtct_TimerUpdate   , EthSwt_SWIC_RstDtct_TimerUpdate   , EthSwt_SWIC_RstDtct_TimerUpdate   }   /* リセット検出 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                          , EthSwt_SWIC_Link_TimerUpdate      , NULL_PTR                          }   /* リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                          , EthSwt_SWIC_SQI_TimerUpdate       , NULL_PTR                          }   /* SQI値取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                          , EthSwt_SWIC_MIB_TimerUpdate       , NULL_PTR                          }   /* MIB取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                          , EthSwt_SWIC_Qci_TimerUpdate       , NULL_PTR                          }   /* Qci取得 */
};
#define D_ETHSWT_SWIC_STM_HIPROCFUNC_NUM   (sizeof(G_ETHSWT_SWIC_STM_HIPROCTABLE) / sizeof(G_ETHSWT_SWIC_STM_HIPROCTABLE[0]))


typedef Std_ReturnType (*EthSwt_registerAccessFunc)(uint32 * const);
const EthSwt_registerAccessFunc G_ETHSWT_SWIC_STM_BACKFUNCTABLE[][D_ETHSWT_SWIC_ST_NUM] =
{   /*  UNINT                   , INIT                      , PORT_INIT_COMPLETED               , SET_RELAY_ON                          , ACTIVE                            , SET_RELAY_OFF      */
    {   NULL_PTR                , EthSwt_SWIC_Init_Setting  , NULL_PTR                          , NULL_PTR                              , NULL_PTR                          , NULL_PTR                          }   /* 初期レジスタ設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , EthSwt_SWIC_Port_RelayOn              , NULL_PTR                          , NULL_PTR                          }   /* 中継開始設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                              , NULL_PTR                          , EthSwt_SWIC_Port_RelayOff         }   /* 中継停止設定 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                              , EthSwt_SWIC_Port_Action           , NULL_PTR                          }   /* ポートモード制御 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_IntErr_Action         , EthSwt_SWIC_IntErr_Action             , EthSwt_SWIC_IntErr_Action         , EthSwt_SWIC_IntErr_Action         }   /* 内部エラー検出 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_RstDtct_Action        , EthSwt_SWIC_RstDtct_Action            , EthSwt_SWIC_RstDtct_Action        , EthSwt_SWIC_RstDtct_Action        }   /* リセット検出 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                              , EthSwt_SWIC_Link_Action           , NULL_PTR                          }   /* リンク状態取得 */
,   {   NULL_PTR                , NULL_PTR                  , NULL_PTR                          , NULL_PTR                              , EthSwt_SWIC_SQI_Action            , NULL_PTR                          }   /* SQI値取得 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_MIB_ReadDiscard       , NULL_PTR                              , EthSwt_SWIC_MIB_Action            , NULL_PTR                          }   /* MIB取得 */
,   {   NULL_PTR                , NULL_PTR                  , EthSwt_SWIC_Qci_ReadDiscard       , NULL_PTR                              , EthSwt_SWIC_Qci_Action            , NULL_PTR                          }   /* Qci取得 */
};
#define D_ETHSWT_SWIC_STM_BACKFUNC_NUM         (sizeof(G_ETHSWT_SWIC_STM_BACKFUNCTABLE) / sizeof(G_ETHSWT_SWIC_STM_BACKFUNCTABLE[0]))


typedef void (*EthSwt_ClearFunc)(void);
const EthSwt_ClearFunc G_ETHSWT_SWIC_STM_STOPCLEAR[] = 
{
    EthSwt_SWIC_Link_Clear
,	EthSwt_SWIC_SQI_Clear
,   EthSwt_SWIC_MIB_Clear
,   EthSwt_SWIC_Qci_Clear
,   EthSwt_SWIC_RegAccess_Clear
};
#define G_ETHSWT_SWIC_STM_STOPCLEAR_NUM         (sizeof(G_ETHSWT_SWIC_STM_STOPCLEAR) / sizeof(G_ETHSWT_SWIC_STM_STOPCLEAR[0]))

const EthSwt_ClearFunc G_ETHSWT_SWIC_STM_RESETCLEAR[] = 
{
    EthSwt_SWIC_IntErr_Clear
,	EthSwt_SWIC_RstDtct_Clear
,   EthSwt_SWIC_Link_Clear
,	EthSwt_SWIC_SQI_Clear
,   EthSwt_SWIC_MIB_Clear
,   EthSwt_SWIC_Qci_Clear
,   EthSwt_SWIC_RegAccess_Clear
};
#define D_ETHSWT_SWIC_STM_RESETCLEAR_NUM        (sizeof(G_ETHSWT_SWIC_STM_RESETCLEAR) / sizeof(G_ETHSWT_SWIC_STM_RESETCLEAR[0]))

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_STM_CFG_H */
/* -------------------------------------------------------------------------- */
