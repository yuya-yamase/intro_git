/****************************************************************************/
/*  Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file    L3R_Scheduler.h
 * @brief   スケジューラー
 * @details 
 * @note    なし
 * @date    v1.00   2018/05/23  T.Yamamura(FSI)     新規作成
 *          v1.10   2018/07/12  A.Yasui(FSI)        【L7R】L3Rからの構成の独立対応
 *          v1.11   2018/07/19  K.Ito(FSI)          帯域制限追加対応
 *          v1.20   2018/09/19  Y.Katayama(FSI)     Router_MainTask()のコール追加
 *          V2.00   2018/11/21  Y.Katayama(FSI)     中継改善(オブジェクト不変）
 *          V2.01   2019/02/05  Y.Katayama(FSI)     課題1099574対応(オブジェクト不変)
 *          V2.02   2019/03/24  K.Ito(FSI)          [IntegNo.1106749]
 *                                                  [570B-Phase9] 拡張車両向けコンフィグ対応
 ****************************************************************************/

#ifndef L3R_SCHEDULER_H
#define L3R_SCHEDULER_H

/*--------------------------------------------------------------------------*/
/*      ファイルインクルード(コンフィグ)                                    */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_BandLimit.h"
#include "L3R_CanMessage.h"
#include "L3R_canmbq_main.h"
#include "L3R_Common.h"
#include "L3R_DiagQueRouter.h"
#include "L3R_DynamicQueRouter.h"
#include "L3R_FrmInfo.h"
#include "L3R_GateManager.h"
#include "L3R_GwIdRouter.h"
#include "L3R_Fail.h"

#include "L3R_canmbq_tx.h"

/*--------------------------------------------------------------------------*/
/*      マクロ定義(コンフィグ)                                              */
/*--------------------------------------------------------------------------*/

/*************************************************************************//**
 * @fn          L3R_System_ResetInitialze()
 * @brief       リセット初期化処理
 * @details     リセット初期化処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_ResetInitialze()                                         \
do {                                                                        \
    CANMBQ_ClrSendLockFlg();                                                \
    L3R_GateM_Init();                                                       \
    CanMessage_Init();                                                      \
    GwIdRouter_Init(&gwIdRouter);                                           \
    DiagQueRouter_Init(&diagQueRouter);                                     \
    DynamicQueRouter_Init(&dynamicQueRouter);                               \
    CANMBQ_ClrSndQueAll();                                                  \
    L3R_FrmInfo_Initialize();                                               \
    L3R_Fail_Init();                                                        \
    TxChannel_ClrTxCnt();                                                   \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_WakeUpInitialze()
 * @brief       ウェイクアップ初期化処理
 * @details     ウェイクアップ初期化処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_WakeUpInitialze()                                        \
do {                                                                        \
    CANMBQ_ClrSendLockFlg();                                                \
    L3R_GateM_Init();                                                       \
    CanMessage_WakeUpInit();                                                \
    GwIdRouter_Init(&gwIdRouter);                                           \
    DiagQueRouter_Init(&diagQueRouter);                                     \
    DynamicQueRouter_Init(&dynamicQueRouter);                               \
    CANMBQ_ClrSndQueAll();                                                  \
    L3R_FrmInfo_Initialize();                                               \
    L3R_Fail_Init();                                                        \
    TxChannel_ClrTxCnt();                                                   \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_SleepInitialze()
 * @brief       スリープ前初期化処理
 * @details     スリープ前初期化処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_SleepInitialze()                                         \
do {                                                                        \
    /* nothing */                                                           \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_DriverTask()
 * @brief       ドライバタスク処理(1ms)
 * @details     ドライバタスク処理(1ms)を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_DriverTask()                                             \
do {                                                                        \
    QueRouter_DriverTask(&dynamicQueRouter);                                \
    CANMBQ_DriverTask();                                                    \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_MainInDrvTask()
 * @brief       メインタスク入力ドライバ(5ms)
 * @details     メインタスク入力ドライバ(5ms)を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_MainInDrvTask()                                          \
do {                                                                        \
    L3R_Fail_MainTask();                                                    \
    CanMessage_MainInDrvTask();                                             \
    BandLimit_MainTask();                                                   \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_MainInMedTask()
 * @brief       メインタスク入力調停(5ms)
 * @details     メインタスク入力調停(5ms)を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_MainInMedTask()                                          \
do {                                                                        \
    L3R_FrmInfo_SwitchFlag();                                               \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_MainAppTask()
 * @brief       メインタスクアプリケーション(5ms)
 * @details     メインタスクアプリケーション(5ms)を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_MainAppTask()                                            \
do {                                                                        \
    CANMBQ_Omed_Er();                                                       \
    L3R_GateM_MainTask();                                                   \
    QueRouter_MainTask(&diagQueRouter);                                     \
    QueRouter_MainTask(&dynamicQueRouter);                                  \
    CanMessage_Task();                                                      \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_MainOutMedTask()
 * @brief       メインタスク出力調停(5ms)
 * @details     メインタスク出力調停(5ms)を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_MainOutMedTask()                                         \
do {                                                                        \
    CanMessage_ModeSet();                                                   \
} while(0)

/*************************************************************************//**
 * @fn          L3R_System_EntryPostRunHook()
 * @brief       PostRunEntryHook処理
 * @details     PostRunEntryHook処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
#define L3R_System_EntryPostRunHook()                                       \
do {                                                                        \
    BandLimit_ExitMainTask();                                               \
} while(0)

#endif  /* L3R_SCHEDULER_H */
