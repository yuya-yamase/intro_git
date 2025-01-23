/****************************************************************************/
/*  Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file    L3R_CanMessage.c
 * @brief   受信したCAN情報の前処理
 * @details 
 * @note    なし
 * @date    v1.00   2018/01/20  T.Totsuka(FSI)      新規作成
 *          v1.01   2018/05/11  A.Yasui(FSI)        中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 *          v1.02   2018/05/12  A.Yasui(FSI)        デファインの二重定義を解消(CAN FD情報)
 *          v2.00   2018/05/15  T.Yamamura(FSI)     可変化対応
 *                                                  ・CAN300関連関数の関数マクロ化(GW_RTR_config.h)
 *                                                  ・CH名称CHM_LOG_BIT_DIAG→RTR_LOG_BIT_DIAGへ変更
 *                                                  ・L3R_Ids_FltErrFrmInfo.hのインクルード削除
 *          v2.01   2018/05/21  A.Yssui(FSI)        動的ルーティング先設定中はスリープNG(RUN要求)を発行
 *          v2.02   2018/05/23  T.Yamamura(FSI)     可変化対応
 *                                                  ・CAN300関連関数の関数マクロ化廃止
 *          v2.03   2018/06/07  T.Yamamura(FSI)     QAC対応
 *                                                  ・currentPosのキャスト追加
 *          v2.03   2018/06/11  T.Yamamura(FSI)     QAC対応
 *                                                  ・CanMessage_ActivateCAN300()のインライン化
 *          v2.04   2018/06/19  K.Ito(FSI)          帯域制限追加対応
 *          v2.05   2018/07/13  K.Ito(FSI)          帯域制限RoB対応
 *          v2.06   2018/07/31  K.Ito(FSI)          QAC対応
 *          v2.07   2018/08/06  K.Ito(FSI)          DLC9以上対応
 *          v2.08   2018/08/29  T.Yamamura(FSI)     CanMessage_EnterNormalModeの名称変更、static化
 *          v3.00   2018/08/24  K.Ito(FSI)          クラス型統一
 *          v3.01   2018/10/25  T.Yamamura(FSI)     コードレベルアップ対応(オブジェクト不変)
 *          v4.00   2018/11/21  Y.Katayama(FSI)     中継改善(オブジェクト不変）
 *          v4.01   2019/02/05  Y.Katayama(FSI)     課題1099574対応(オブジェクト不変)
 *          v4.10   2019/03/14  Y.Katayama(FSI)     欠陥1104558対応
 *                                                  ・ウェイクアップ時の制御フレームモニタ動的送信先クリア処理の削除
 *          v4.11   2019/03/20  Y.Katayama(FSI)     課題1105170対応
 *          v4.12   2019/03/24  K.Ito(FSI)          [IntegNo.1099809]
 *                                                  [570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 *          v4.13   2019/05/17  K.Ito(FSI)          [IntegNo.1111499]
 *                                                  [570B-Phase9] CAN300復帰処理削除
 *          v5.00   2020/12/07  T.Yamamura(FSI)     [Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*      ファイルインクルード                                                */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"
/* #include "EVT.h" */

#include "L3R_AutoCanMessage.h"

#if L3R_USE_BROADCAST == L3R_ENABLE
#include "L3R_BroadCastCanMessage.h"
#endif

#include "L3R_Common.h"
#include "L3R_config.h"

#include "L3R_FilterCanMessage_Cfg.h"
#include "L3R_CanMessage.h"
#include "L3R_CanMessageExt.h"

/*--------------------------------------------------------------------------*/
/*      マクロ定義                                                          */
/*--------------------------------------------------------------------------*/
#define REQUEST_NULL_COUNTER            (0x0FU)
#define REQUEST_INITIAL_VALUE           {NULL_PTR, NULL_PTR, 0, 0, 0, 0, REQUEST_NULL_COUNTER, 0}

#define L3R_MODEREQ_OFF                 (0U)
#define L3R_MODEREQ_ON                  (1U)


/*--------------------------------------------------------------------------*/
/*      タイプ宣言                                                          */
/*--------------------------------------------------------------------------*/
typedef struct setIdRequestTag {
    CallBackFunc CallBack;
    const uint32 *CanId;
    uint16 length;
    uint16 sndPrtclBit;
    uint16 index;
    uint16 startPos;
    uint8 counter;
    uint8 setFlg;
} SetIdRequest;


/*--------------------------------------------------------------------------*/
/*      外部公開変数                                                        */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*      ファイル内変数                                                      */
/*--------------------------------------------------------------------------*/
/* #define GW_L3R_START_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* static CanMessageArraySet *pCanMessageArrayNow = &pCanMessageArray[0]; */

/* #if L3R_USE_BROADCAST == L3R_ENABLE */
/* static CanMessageArraySet *pCanMessageBroadCastArrayNow = &pCanMessageBroadCastArray[0]; */
/* #endif */

/* static uint8 CanMessage_ReprogModeReq = L3R_MODEREQ_OFF; */
/* #define GW_L3R_STOP_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* #define GW_L3R_START_SEC_VAR_SAVED_ZONE */
/* #include "GW_L3R_Memmap.h" */
/* uint16 CanMessage_monitorMask = DEFAULT_MASK; */
/* uint16 CanMessage_requestState = DEFAULT_MASK; */
/* static uint8 CanMessage_ThatchamModeReq = L3R_MODEREQ_OFF; */
/* #define GW_L3R_STOP_SEC_VAR_SAVED_ZONE */
/* #include "GW_L3R_Memmap.h" */
/* #define GW_L3R_START_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* uint16 CanMessage_sndPrtclBit = 0; */
/* #define GW_L3R_STOP_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
static const SetIdRequest setIdRequestInitial = REQUEST_INITIAL_VALUE;
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
/* #define GW_L3R_START_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* static SetIdRequest setIdRequestMonitor = REQUEST_INITIAL_VALUE; */
/* #define GW_L3R_STOP_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* #define GW_L3R_START_SEC_VAR_NO_INIT */
/* #include "GW_L3R_Memmap.h" */
/* uint8 CanMessage_CancelEvtState; */
/* #define GW_L3R_STOP_SEC_VAR_NO_INIT */
/* #include "GW_L3R_Memmap.h" */

/* #define GW_L3R_START_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* const uint8 *pFilterCanMessageArrayNow = &FilterCanMessageNormalArray[0];	/\* フィルタタイプテーブルポインタ *\/ */
/* #define GW_L3R_STOP_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
const uint16 CanMessage_aGwId[CHM_LOG_ALL_CH_NUM] = {0};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

static CanMessageArraySet *    pCanMessageArrayNow;

#if L3R_USE_BROADCAST == L3R_ENABLE
static CanMessageArraySet *    pCanMessageBroadCastArrayNow;
#endif
static uint8                   CanMessage_ReprogModeReq;
uint16                         CanMessage_sndPrtclBit;
static SetIdRequest            setIdRequestMonitor;
uint8                          CanMessage_CancelEvtState;
const uint8 *                  pFilterCanMessageArrayNow;

#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"

uint16                         CanMessage_monitorMask;
uint16                         CanMessage_requestState;
static uint8                   CanMessage_ThatchamModeReq;

#define GW_L3R_STOP_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*      プロトタイプ宣言                                                    */
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
static void CanMessage_ProtocolTask(SetIdRequest *pSetIdRequest);
static void   CanMessage_SetProtocolAllSub(SetIdRequest *pSetIdRequest, uint16 startPos, uint16 endPos);
static uint32 CanMessage_SetProtocol(uint16 sndPrtclBit, uint32 startPos, uint16 searchId);


/*************************************************************************//**
 * @fn          void CanMessage_Init(void)
 * @brief       リセット時初期化
 * @details     リセット時初期化処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_Init(void)
{
    uint32 canId;
    CanMessageArraySet *pCanMessageArrayNow4Loop = &pCanMessageArray[0];

    pCanMessageArrayNow          = &pCanMessageArray[0];

#if L3R_USE_BROADCAST == L3R_ENABLE
    pCanMessageBroadCastArrayNow = &pCanMessageBroadCastArray[0];
#endif
    CanMessage_ReprogModeReq     = L3R_MODEREQ_OFF;
    CanMessage_sndPrtclBit       = 0;
 /* setIdRequestMonitor          = setIdRequestInitial; */
    CanMessage_CancelEvtState    = L3R_CLR;
    pFilterCanMessageArrayNow    = &FilterCanMessageNormalArray[0];

    CanMessage_monitorMask       = DEFAULT_MASK;
    CanMessage_requestState      = DEFAULT_MASK;
    CanMessage_ThatchamModeReq   = L3R_MODEREQ_OFF;

    CanMessage_InActivateMonitor();
    for(canId = 0; canId < L3R_SEARCH_MAX; canId++){
        *(pCanMessageArrayNow4Loop[canId].pClass->pSndPrtclBit) = 0;
    }
    setIdRequestMonitor = setIdRequestInitial;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_WakeUpInit(void)
 * @brief       ウェイクアップ時初期化
 * @details     ウェイクアップ時初期化処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_WakeUpInit(void)
{
 /* pCanMessageArrayNow          = &pCanMessageArray[0]; */             /* initialized at CanMessage_ModeSet() */

#if L3R_USE_BROADCAST == L3R_ENABLE
    pCanMessageBroadCastArrayNow = &pCanMessageBroadCastArray[0];
#endif
    CanMessage_ReprogModeReq     = L3R_MODEREQ_OFF;
    CanMessage_sndPrtclBit       = 0;
 /* setIdRequestMonitor          = setIdRequestInitial; */
    CanMessage_CancelEvtState    = L3R_CLR;
 /* pFilterCanMessageArrayNow    = &FilterCanMessageNormalArray[0]; */  /* initialized at CanMessage_ModeSet() */

 /* CanMessage_monitorMask       = DEFAULT_MASK; */
 /* CanMessage_requestState      = DEFAULT_MASK; */
 /* CanMessage_ThatchamModeReq   = L3R_MODEREQ_OFF; */

    CanMessage_ModeSet();
    CanMessage_InActivateMonitor();

    setIdRequestMonitor = setIdRequestInitial;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_MainInDrvTask(void)
 * @brief       5msタスク入力ドライバ処理
 * @details     5msタスク入力ドライバ処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_MainInDrvTask(void)
{
#ifdef EVT_H
    L3R_DI();

    if((CanMessage_CancelEvtState & EVT_BIT_CTRLFRM_MTR_SUSPEND) == EVT_BIT_CTRLFRM_MTR_SUSPEND) {
        EVT_SendInMed(EVT_IM_L3R_CTRLFRM_MTR_SUSPEND);
        EVT_SendApp(EVT_AP_L3R_CTRLFRM_MTR_SUSPEND);
        EVT_SendOutMed(EVT_OM_L3R_CTRLFRM_MTR_SUSPEND);
    }

    CanMessage_CancelEvtState = L3R_CLR;

    L3R_EI();

    return;
#else
    CanMessage_CancelEvtState = L3R_CLR;
#endif
}

/*************************************************************************//**
 * @fn          void CanMessage_Task(void)
 * @brief       5msタスク(アプリ)処理
 * @details     5msタスク(アプリ)処理を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_Task(void)
{
    CanMessage_ProtocolTask(&setIdRequestMonitor);

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_Receive(uint8 rxCh, uint32 canid32, uint8 dlc, uint8* Data, uint16 searchId)
 * @brief       CANデータ受信処理
 * @details     受信したCAN情報を処理します
 * @param[in]   uint8 rxCh          受信CH
 * @param[in]   uint32 canid32      受信データのCANID(フラグ付き）
 * @param[in]   uint8 dlc           受信データ長
 * @param[in]   uint8* Data         受信データへのポインタ
 * @param[in]   uint16 searchId     受信データのCANID探索位置
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_Receive(uint8 rxCh, uint32 canid32, uint8 dlc, uint8* Data, uint16 searchId)
{
    uint16 gwId;
    uint8   fd;
    CanMessage *pCanMessage;

    fd = (uint8) ((canid32 & L3R_TCOV_CANFD_BIT) >> L3R_TCOV_CANFD_SHIFT_NO);
    if ((fd == L3R_FDF_ON) || (dlc <= L3R_CAN_DATAMAX)) {

#if L3R_USE_BROADCAST == L3R_ENABLE
        uint32 canId = (canid32 & L3R_TCOV_MSK_CANCOM); /* CANFD,拡張ビットを落とす */

        /* ダイアグ/リプログフレーム処理 */
        if (( canId >= 0x001 && canId <= 0x009)
        ||  ( canId >= 0x700 && canId <= 0x7FF)
        ||  ( canId >= 0x1F000000 && canId <= 0x1FFFFFFF)
        ||  ( canId >= 0x18DA0000 && canId <= 0x18DAFFFF)
        ||  ( canId >= 0x18DB0000 && canId <= 0x18DBFFFF)) {
            pCanMessage = pCanMessageBroadCastArrayNow[0].pClass;
            gwId = pCanMessage->funcList->GetGwId(pCanMessage, rxCh, dlc, Data);
            BroadCastCanMessage_RelayData(pCanMessage, fd, dlc, Data, gwId, rxCh, 0, canId);

            return;
        }
#endif

        /* CanMessage設定 */
        pCanMessage = pCanMessageArrayNow[searchId].pClass;

        /* 探索判定 */
        if ( pCanMessage == L3R_NULL) {
            gwId = NULL_GWID;
        }else {
            gwId = pCanMessage->funcList->GetGwId(pCanMessage, rxCh, dlc, Data, searchId);
        }

        switch(gwId)
        {
        case NULL_GWID:                     /* 中継対象外 */
            CanMessage_UnKnownErrorHandler();
            break;
        case FILTERERR_GWID:                /* CAN/DLC/SIDエラー */
            break;
        default:                            /* 通常中継/動的中継 */
            pCanMessage->funcList->RelayData(pCanMessage, fd, dlc, Data, gwId, rxCh, searchId);
            break;
        }
    }

    return;
}

/*************************************************************************//**
 * @fn          static void CanMessage_ModeSet(void)
 * @brief       各種モード設定
 * @details     各種モード設定を行う
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_ModeSet(void)
{
    /* pCanMessageArrayNowは上位タスクによる参照が行われているが、本更新処理では割禁未設定              */
    /* pCanMessageArrayNowへのアクセスは1命令なため、不完全な状態の値が参照側でロードされることはない   */
    /* そのため現状は問題ないが、今後処理の追加/変更等を実施する場合は、割禁の追加を検討すること        */
    L3R_DI();   /* 割り込み禁止 */

    if (CanMessage_ThatchamModeReq == L3R_MODEREQ_ON) {
        pCanMessageArrayNow = pCanMessageThatchamArray; /* サッチャムモード */
        pFilterCanMessageArrayNow = &FilterCanMessageThatchamArray[0];  /* サッチャムモード フィルタタイプテーブルポインタ設定 */
    } else if (CanMessage_ReprogModeReq == L3R_MODEREQ_ON) {
        pCanMessageArrayNow = pCanMessageReprogArray;       /* リプログGWモード */
        pFilterCanMessageArrayNow = &FilterCanMessageReprogArray[0];    /* リプログGWモード フィルタタイプテーブルポインタ設定 */
    } else {
        pCanMessageArrayNow = pCanMessageArray;         /* 通常モード */
        pFilterCanMessageArrayNow = &FilterCanMessageNormalArray[0];    /* 通常モード フィルタタイプテーブルポインタ設定 */
    }

    L3R_EI();   /* 割り込み許可 */
}

/*************************************************************************//**
 * @fn          void CanMessage_EnterReprogMode(void)
 * @brief       リプログGWモードに入る
 * @details     リプログGWモードに入る
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_EnterReprogMode(void)
{
    CanMessage_ReprogModeReq = L3R_MODEREQ_ON;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_ExitReprogMode(void)
 * @brief       リプログGWモード終了
 * @details     リプログGWモードを終了する
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_ExitReprogMode(void)
{
    CanMessage_ReprogModeReq = L3R_MODEREQ_OFF;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_EnterThatchamMode(void)
 * @brief       サッチャムモードに入る
 * @details     サッチャムモードに入る
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_EnterThatchamMode(void)
{
    CanMessage_ThatchamModeReq = L3R_MODEREQ_ON;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_ExitThatchamMode(void)
 * @brief       サッチャムモード終了
 * @details     サッチャムモードを終了する
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_ExitThatchamMode(void)
{
    CanMessage_ThatchamModeReq = L3R_MODEREQ_OFF;

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_ActivateMonitor(void)
 * @brief       動的ルーティング有効化(制御フレームモニタ)
 * @details     外部からの要求による動的ルーティングの有効化(制御フレームモニタ)
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_ActivateMonitor(void)
{
    uint8 bandLimitCheck;

    L3R_DI();

    bandLimitCheck = BandLimit_JudgeLimit();

    CanMessage_requestState = (uint16)((uint32)CanMessage_requestState | ((uint32)DEFAULT_MASK | CHM_LOG_BIT_USE_DIAG));

    /* 帯域制限中でない場合のみ要求受付 */
    if (L3R_E_OK == bandLimitCheck) {
        CanMessage_monitorMask = (uint16)((uint32)CanMessage_monitorMask | ((uint32)DEFAULT_MASK | CHM_LOG_BIT_USE_DIAG));
    } else {
        /* 制御フレームモニタのキャンセルイベントがあったことを記憶 */
        CanMessage_CancelEvtState |= EVT_BIT_CTRLFRM_MTR_SUSPEND;
    }

    L3R_EI();

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_InActivateMonitor(void)
 * @brief       動的ルーティング無効化(制御フレームモニタ)
 * @details     外部からの要求による動的ルーティングの無効化(制御フレームモニタ)
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_InActivateMonitor(void)
{
    L3R_DI();

    CanMessage_requestState = (uint16)((uint32)CanMessage_requestState & ~CHM_LOG_BIT_USE_DIAG);
    CanMessage_monitorMask = (uint16)((uint32)CanMessage_monitorMask & ~CHM_LOG_BIT_USE_DIAG);

    L3R_EI();

    return;
}

/*************************************************************************//**
 * @fn          void CanMessage_InActivateMonitorByRTR(void)
 * @brief       動的ルーティング無効化(制御フレームモニタ)
 * @details     内部要因による動的ルーティングの無効化(制御フレームモニタ)
 * @param       なし
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
void CanMessage_InActivateMonitorByRTR(void)
{
    if((CHM_LOG_BIT_USE_DIAG & (uint32)CanMessage_monitorMask) == CHM_LOG_BIT_USE_DIAG){
        CanMessage_monitorMask = (uint16)((uint32)CanMessage_monitorMask & ~CHM_LOG_BIT_USE_DIAG);
        /* 制御フレームモニタのキャンセルイベントがあったことを記憶 */
        CanMessage_CancelEvtState |= EVT_BIT_CTRLFRM_MTR_SUSPEND;
    }

    return;
}

/*************************************************************************//**
 * @fn          Std_ReturnType CanMessage_SetProtocolAll(const uint32 CanId[], uint16 length, uint16 sndPrtclBit, uint16 startPos, uint16 endPos, CallBackFunc func)
 * @brief       送信先の設定
 * @details     送信先の設定を行う
 * @param[in]   CanId[]         CANID
 * @param[in]   length          設定数
 * @param[in]   sndPrtclBit     送信先
 * @param[in]   startPos        設定範囲の最初
 * @param[in]   endPos          設定範囲の最後
 * @param[in]   func            コールバック関数
 * @return      送信先設定結果
 * @retval      E_OK        設定成功
 * @retval      E_NOT_OK    設定失敗
 * @attention   前提条件：  CanId[]内のIDはソートされている
 *                          lengthはCanId[]の要素数を超えていない
 *                          startPosは0x100より小さい
 * @note        なし
 ****************************************************************************/
Std_ReturnType CanMessage_SetProtocolAll(const uint32 CanId[], uint16 length, uint16 sndPrtclBit, uint16 startPos, uint16 endPos, CallBackFunc func)
{
    Std_ReturnType result = E_NOT_OK;

    if(sndPrtclBit != CHM_LOG_BIT_NON){
        if((uint32)sndPrtclBit == CHM_LOG_BIT_USE_DIAG){
        /* 制御フレームモニタ */
        setIdRequestMonitor.CallBack = func;
        setIdRequestMonitor.CanId = CanId;
        setIdRequestMonitor.length = length;
        setIdRequestMonitor.sndPrtclBit = sndPrtclBit;
        setIdRequestMonitor.index = 0;
        setIdRequestMonitor.startPos = startPos;
        setIdRequestMonitor.counter = 0;
        setIdRequestMonitor.setFlg = 0;
        result = E_OK;
    }else{
            /* 処理なし */
        }
    }

    return (result);
}

/*************************************************************************//**
 * @fn          static void CanMessage_SetProtocolAllSub(SetIdRequest *pSetIdRequest, uint16 startPos, uint16 endPos)
 * @brief       送信先の設定
 * @details     送信先の設定を行う
 * @param[in]   pSetIdRequest   要求へのポインタ
 * @param[in]   startPos        設定範囲の最初
 * @param[in]   endPos          設定範囲の最後
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
static void CanMessage_SetProtocolAllSub(SetIdRequest *pSetIdRequest, uint16 startPos, uint16 endPos)
{
    const uint32 *CanId = pSetIdRequest->CanId;
    uint16 length = pSetIdRequest->length;
    uint16 sndPrtclBit = pSetIdRequest->sndPrtclBit;
    uint32 requestedIndex = pSetIdRequest->index;
    uint32 currentPos = startPos;
    uint32 currentNullId;

    for (; requestedIndex < length; requestedIndex++) {
        const uint32 requestedId = CanId[requestedIndex];
        const uint32 startId     = pCanMessageArrayNow[startPos].canid_s;
        const uint32 lastId      = pCanMessageArrayNow[endPos].canid_s;
        if ((requestedId >= L3R_DIAGFRM_STARTID && requestedId <= L3R_DIAGFRM_ENDID) || (requestedId >= L3R_EXD_DIAGFRM_STARTID && requestedId <= L3R_EXD_DIAGFRM_ENDID)) {
            /* 処理なし */
        } else if ((startId <= requestedId) && (requestedId <= lastId)) {

            uint16 search_min = startPos;
            uint16 search_max = endPos;
            uint16  searchId;

            /* CANIDを探索 */
            while (search_min <= search_max) {
                searchId = ((search_max + search_min) >> 1U);

                /* CANID一致時に対象のCANIDに送信先をセット */
                if (requestedId == pCanMessageArrayNow[searchId].canid_s) {
                    currentPos = CanMessage_SetProtocol(sndPrtclBit, (uint16)currentPos, searchId);
                    break;
                } else if (requestedId < pCanMessageArrayNow[searchId].canid_s) {
                    search_max = searchId - 1U;
                } else {
                    search_min = searchId + 1U;
                    }
            }
        } else if (lastId < requestedId) {
            break;
        }else{
            /* 処理継続 */
        }
    }

    for (currentNullId = currentPos; currentNullId <= endPos; currentNullId++) {
        CanMessage_RemoveSendProtocol(currentNullId, sndPrtclBit);          /* 送信先クリア */
    }

    pSetIdRequest->index = (uint16) requestedIndex;
    pSetIdRequest->counter++;

    return;
}

/*************************************************************************//**
 * @fn          static uint32 CanMessage_SetProtocol(uint16 sndPrtclBit, uint32 startPos, uint16 searchId)
 * @brief       送信先の設定
 * @details     送信先の設定を行う
 * @param[in]   sndPrtclBit     設定する送信先
 * @param[in]   startPos        未処理の最初の位置
 * @param[in]   requestedId     要求されたID
 * @return      未処理の最初の位置
 * @attention   なし
 * @note        なし
 ****************************************************************************/
static uint32 CanMessage_SetProtocol(uint16 sndPrtclBit, uint32 startPos, uint16 searchId)
{
    uint32 currentPos = startPos;
    uint32 currentNullPos;

    for(currentNullPos = currentPos ; currentNullPos < searchId; currentNullPos++)
    {
        CanMessage_RemoveSendProtocol(currentNullPos, sndPrtclBit); /* 送信先クリア */
    }
    /* CanMessage_AddSendProtocol()内で更新されるRAMは上位タスクによる参照が行われているが、本更新処理では割禁未設定    */
    /* RAMへのアクセスは1命令なため、不完全な状態の値が参照側でロードされることはない                                   */
    /* そのため現状は問題ないが、今後処理の追加/変更等を実施する場合は、割禁の追加を検討すること                        */
    CanMessage_AddSendProtocol(searchId, sndPrtclBit);          /* 送信先設定 */
    if(currentPos <= ((uint32) searchId)){
        /* 未処理の最初の位置を計算 */
        currentPos = (uint32) searchId + 1U;
    }

    return (currentPos);
}

/*************************************************************************//**
 * @fn          static void CanMessage_ProtocolTask(SetIdRequest *pSetIdRequest)
 * @brief       送信先設定要求
 * @details     送信先設定要求の処理を行う
 * @param[in]   pSetIdRequest   要求へのポインタ
 * @return      なし
 * @attention   なし
 * @note        なし
 ****************************************************************************/
static void CanMessage_ProtocolTask(SetIdRequest *pSetIdRequest)
{
    uint16 startPos = (pSetIdRequest->counter) * 0x100U;
    uint16 endPos = startPos + 0xFFU;

    if ((uint32)pSetIdRequest->setFlg == (uint32)0) {
        if (endPos >= L3R_SEARCH_MAX) {
            endPos = L3R_SEARCH_MAX - 1U;
            CanMessage_SetProtocolAllSub(pSetIdRequest, startPos, endPos);
            pSetIdRequest->setFlg = 1;
        } else {
            CanMessage_SetProtocolAllSub(pSetIdRequest, startPos, endPos);
        }
    } else {
        if(pSetIdRequest->CallBack != NULL_PTR){
            pSetIdRequest->CallBack(E_OK);
            pSetIdRequest->CallBack = NULL_PTR;
        }
    }

    return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
