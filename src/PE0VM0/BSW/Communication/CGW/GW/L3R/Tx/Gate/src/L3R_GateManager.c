/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_GateManager.c
 * @brief		中継先ゲート管理
 * @details		送信許可or禁止or保留を制御する
 * @note	
 * @date		v1.00   2016/04/01  H.Tanaka    新規作成(リファクタリング) 
 * @date		v1.01   2017/03/03  Y.Katayama  19PF向け型定義対応 
 * @date		v1.02   2017/08/10  T.Yamamura  課題：997231対応 (欠陥：985063)
 * @date										・IGバス時の状態遷移対応 
 * @date										・CSバス状態をSYNC経由から直接取得するように変更 
 * @date		v1.03   2018/02/07  T.Totsuka    バスオフ復帰時間の変更(1150ms→50ms)
 * @date		v1.04   2018/03/03  T.Totsuka    バスオフ復帰時間の再変更(50ms→1150ms)
 * @date		v2.00   2018/05/16  T.Yamamura  可変化対応
 * @date										・CH数定数RTR_CANCH_MAX→CHM_LOG_CH_NUM変更
 * @date										・MSK定数RTR_BUS_LOGIC_NM_MSK→RTR_LOG_NM_MSKへ変更
 * @date										・GW_RTR_Common.h→CHM_LogicCh.h変更
 * @date		v2.01   2018/05/23  T.Yamamura  可変化対応
 * @date										・FailTimer用マクロをGW_RTR_config.hへ移動
 * @date		v2.02   2018/05/24  K.Ito        2段バッファ削除対応
 * @date		v2.03   2018/07/25  T.Yamamura  処理負荷改善対応
 * @date										・vdg_GW_RTR_GateM_QuickWakeup内の割込み禁止処理削除
 * @date										・u1g_GW_RTR_GateM_GetGateStatus関数のインライン化
 * @date		v2.04   2018/10/25  T.Yamamura  コードレベルアップ対応(オブジェクト不変)
 * @date		v2.05   2018/10/26  T.Yamamura  割込み禁止コメント修正
 * @date		v3.00	2018/11/21	Y.Katayama	中継改善(オブジェクト不変)
 ****************************************************************************/
#include "CHM_LogicCh.h"

#include "L3R_config.h"
#include "L3R_Fail.h"
#include "L3R_Gate_Nm.h"
#include "L3R_Gate_Ig.h"
#include "L3R_GwIdRouter.h"

#include "L3R_GateManager.h"

/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
static void L3R_GateM_SetGateStatus(uint8 LogicCh);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/*----ファイル内変数宣言----------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static uint8 NetworkStatus[CHM_LOG_CAN_CH_NUM];
static uint8 FailStatus[CHM_LOG_CAN_CH_NUM];
static uint16 FailTimer[CHM_LOG_CAN_CH_NUM];
uint8 GateStatus[CHM_LOG_CAN_CH_NUM];
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

/*----置換マクロ------------------------------------------------------------*/

/* NetworkStatus更新用マクロ */
#define L3R_GM_EVENT_POS_MSK		(0x01U)			/**< SYNC経由で取得するバス状態のビット位置 */

/* FailStatus用マクロ */
#define L3R_GM_FS_NORMAL		(0x01U)
#define L3R_GM_FS_FAIL			(0x02U)

/* NetworkStatus用マクロ */
#define L3R_CHINFO_ON			(0x01U)
#define L3R_CLR					(0U)

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
/* NetworkStatus用 関数テーブル(全CH一括設定されるイベントのみ用意) */
/* Init */
static uint8 (* const L3R_GateM_FuncTbl_Init[L3R_GATESPEC_MAX])(void) = {
	&L3R_NGate_Nm_Init,
	&L3R_NGate_Ig_Init,
};
/* Start */
static uint8 (* const L3R_GateM_FuncTbl_Start[L3R_GATESPEC_MAX])(uint8 NetSts) = {
	&L3R_NGate_Nm_Start,
	&L3R_NGate_Ig_Start,
};
/* Stop */
static uint8 (* const L3R_GateM_FuncTbl_Stop[L3R_GATESPEC_MAX])(uint8 NetSts) = {
	&L3R_NGate_Nm_Stop,
	&L3R_NGate_Ig_Stop,
};
/* Standby */
static uint8 (* const L3R_GateM_FuncTbl_Standby[L3R_GATESPEC_MAX])(uint8 NetSts) = {
	&L3R_NGate_Nm_Standby,
	&L3R_NGate_Ig_Standby,
};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			void L3R_GateM_Init(void)
 * @brief		初期化
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		リセット初期化orウェイクアップ初期化で呼び出される
 ****************************************************************************/
void L3R_GateM_Init(void)
{
	uint8 LogicCh;
	
	for(LogicCh = 0U; LogicCh < CHM_LOG_CAN_CH_NUM; LogicCh++) {
		NetworkStatus[LogicCh] = L3R_GateM_FuncTbl_Init[L3R_GateSpecTbl[LogicCh]]();
		
		FailStatus[LogicCh]	= L3R_GM_FS_NORMAL;
		FailTimer[LogicCh]	= L3R_CLR;
		
		L3R_GateM_SetGateStatus(LogicCh);
	}
	
	return ;
}


/*************************************************************************//**
 * @fn			void L3R_GateM_MainTask(void)
 * @brief		定期更新
 * @details		定期更新処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_GateM_MainTask(void)
{
	uint8 NetSts, FailSts;
	uint16 FailTmr;
	uint16 StartEventInfo = L3R_CLR;
	uint16 StopEventInfo = L3R_CLR;
	uint16 StandbyEventInfo = L3R_CLR;
	uint8 Status;
	uint8 LogicCh;
	
	/* CH毎にCSバス状態を取得する */
	for(LogicCh = 0U; LogicCh < CHM_LOG_CAN_CH_NUM; LogicCh++) {
		
		/* CSバス状態を取得 */
		Status = (BswM_CS_GetTRXStatus(LogicCh));
		
		/* CSバス状態情報生成 */
		switch(Status) {
			case BSWM_CS_TRXST_TRX_ENABLE:								/* 通信開始(通常動作)状態を検出 */
				/* StartEventInfo更新 */
				StartEventInfo = (uint16)((uint32)StartEventInfo | ((uint32)L3R_CHINFO_ON << (uint32)LogicCh));
				break;
			case BSWM_CS_TRXST_TRX_DISABLE:								/* 通信停止(スリープ可能)状態を検出 */
				/* StopEventInfo更新 */
				StopEventInfo = (uint16)((uint32)StopEventInfo | ((uint32)L3R_CHINFO_ON << (uint32)LogicCh));
				break;
			case BSWM_CS_TRXST_RX_ENABLE:								/* 受信可能(送信不可)状態を検出 */
				/* StandbyEventInfo更新 */
				StandbyEventInfo = (uint16)((uint32)StandbyEventInfo | ((uint32)L3R_CHINFO_ON << (uint32)LogicCh));
				break;
			default:
				/* do nothing */
				break;
		}
	}
		
	/* Gate定期更新(他イベントによるGate更新を防ぐため、割込禁止) */
	L3R_DI();
	
	for(LogicCh = 0U; LogicCh < CHM_LOG_CAN_CH_NUM; LogicCh++) {
		/* ローカル変数に代入 */
		NetSts = NetworkStatus[LogicCh];
		FailSts = FailStatus[LogicCh];	
		FailTmr = FailTimer[LogicCh];
		
		/* NetworkStatus更新 */
		if ( (StartEventInfo & L3R_GM_EVENT_POS_MSK) == L3R_TRUE) {			/* 通信開始(通常動作)状態を検出 */
			NetSts = L3R_GateM_FuncTbl_Start[L3R_GateSpecTbl[LogicCh]](NetSts);	
		} else if ( (StopEventInfo & L3R_GM_EVENT_POS_MSK) == L3R_TRUE) {	/* 通信停止(スリープ可能)状態を検出 */
			NetSts = L3R_GateM_FuncTbl_Stop[L3R_GateSpecTbl[LogicCh]](NetSts);
		} else if ( (StandbyEventInfo & L3R_GM_EVENT_POS_MSK) == L3R_TRUE) {	/* 受信可能(送信不可)状態を検出 */
			/* バス仕様判定 */
			if (L3R_GateSpecTbl[LogicCh] == L3R_GATESPEC_NM) {			/* NMバス時 */
				NetSts = L3R_GateM_FuncTbl_Stop[L3R_GateSpecTbl[LogicCh]](NetSts);
			} else if (L3R_GateSpecTbl[LogicCh] == L3R_GATESPEC_IG) {		/* IGバス時 */
				NetSts = L3R_GateM_FuncTbl_Standby[L3R_GateSpecTbl[LogicCh]](NetSts);
			} else {																			/* RAM異常時 */
				/* do nothing */
			}
		} else {																						/* RAM異常時 */
			/* do nothing */
		}
						
		/* FailStatus,FailTimer更新 */
		if (FailTmr == L3R_CLR) {
			FailSts = L3R_GM_FS_NORMAL;
		} else if (FailTmr <= L3R_GM_FT_MAX) {
			FailTmr--;
		} else {
			FailTmr =  (uint16)L3R_GM_FT_MAX;		/* FailTimer異常値のため、安全側に倒す（中継禁止最長時間を設定） */
		} 
		
		/* ファイル内変数に代入 */
		NetworkStatus[LogicCh] = NetSts;
		FailStatus[LogicCh] = FailSts;
		FailTimer[LogicCh]	= FailTmr;
		
		/* GateStatus更新 */
		L3R_GateM_SetGateStatus(LogicCh);
		
		/* ビット位置を次Chに合わせる */
		StartEventInfo  = StartEventInfo >> 1U;
		StopEventInfo = StopEventInfo >> 1U;
		StandbyEventInfo = StandbyEventInfo >> 1U;
	}
	
	L3R_EI();
		
	return;
}


/*************************************************************************//**
 * @fn			void L3R_GateM_NmWakeup(uint8 LogicCh)
 * @brief		「CNMバスウェイクアップ」イベント発生時にNetworkStatusを更新する
 * @details		「CNMバスウェイクアップ」イベント発生時にNetworkStatusを更新する
 * @param[in]	LogicCh		CH番号
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_GateM_NmWakeup(uint8 LogicCh)
{
	L3R_DI();
	
	/* NetworkStatus更新*/
	NetworkStatus[LogicCh] = L3R_NGate_Nm_Standby(NetworkStatus[LogicCh]);
	/* GateStatus更新 */
	L3R_GateM_SetGateStatus(LogicCh);
	
	L3R_EI();

	return;
}


/*************************************************************************//**
 * @fn			void L3R_GateM_QuickWakeup(void)
 * @brief		「特定イベントorダイアグフレーム受信orスキップアライブ」イベント発生時にスリープNGを発行し、NetworkStatusを更新する
 * @details		「特定イベントorダイアグフレーム受信orスキップアライブ」イベント発生時にスリープNGを発行し、NetworkStatusを更新する
 * @param		なし
 * @return		なし
 * @attention	割り込み禁止で呼び出される
 * @note		全NMチャネルを処理する
 ****************************************************************************/
void L3R_GateM_QuickWakeup(void)
{
	uint8 LogicCh;
	
	for(LogicCh = 0U; LogicCh < CHM_LOG_CAN_CH_NUM; LogicCh++) {
		/* NetworkStatus更新 */
		if(L3R_GateSpecTbl[LogicCh] == L3R_GATESPEC_NM) {
			NetworkStatus[LogicCh] = L3R_NGate_Nm_Standby(NetworkStatus[LogicCh]);
		}
		/* GateStatus更新 */
		L3R_GateM_SetGateStatus(LogicCh);
	}
	
	return;
}


/*************************************************************************//**
 * @fn			void L3R_GateM_IgOn(void)
 * @brief		「IGオン」イベント発生時にNetworkStatusを更新する
 * @details		「IGオン」イベント発生時にNetworkStatusを更新する
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		全IGチャネルを処理する
 ****************************************************************************/
void L3R_GateM_IgOn(void)
{
	uint8 LogicCh;
	
	L3R_DI();
	
	for(LogicCh = 0U; LogicCh < CHM_LOG_CAN_CH_NUM; LogicCh++) {
		/* NetworkStatus更新 */	
		if(L3R_GateSpecTbl[LogicCh] == L3R_GATESPEC_IG) {
			NetworkStatus[LogicCh] = L3R_NGate_Ig_Standby(NetworkStatus[LogicCh]);
		}
		/* GateStatus更新 */
		L3R_GateM_SetGateStatus(LogicCh);
	}

	L3R_EI();
	
	return;
}


/*************************************************************************//**
 * @fn			void L3R_GateM_Fail(uint8 Factor, uint8 LogicCh)
 * @brief		「送信ロックorバスオフ」イベント発生時にFailStatusとFailTimerを更新する
 * @details		「送信ロックorバスオフ」イベント発生時にFailStatusとFailTimerを更新する
 * @param[in]	Factor		イベント要因
 * @param[in]	LogicCh		CH番号
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_GateM_Fail(uint8 Factor, uint8 LogicCh)
{
	uint16 FailTmr;
	uint8 FailSts;
	
	L3R_DI();
	
	FailTmr = FailTimer[LogicCh];
	FailSts = FailStatus[LogicCh];
	
	/* フェール要因特定 */
	switch(Factor){
		case L3R_GM_FAIL_SENDLOCK:	/* 送信ロック検出 */
			FailTmr  = (uint16)L3R_GM_FT_SENDLOCK;
			FailSts = L3R_GM_FS_FAIL;
			break;
		case L3R_GM_FAIL_BUSOFF:	/* バスオフ検出 */
			FailTmr  = (uint16)L3R_GM_FT_BUSOFF;
			FailSts = L3R_GM_FS_FAIL;
			break;
		default:
			/* do nothing */
			break;
	}
	
	/* FailTimer更新(フェール連続発生時を考慮し、大きいタイマー値を設定) */
	if(FailTimer[LogicCh]  < FailTmr) {
		FailTimer[LogicCh]  = FailTmr;
	}	
	/* FailStatus更新 */
	FailStatus[LogicCh] = FailSts;	
	/* GateStatus更新 */
	L3R_GateM_SetGateStatus(LogicCh);
	
	L3R_EI();
		
	return;
}


/*************************************************************************//**
 * @fn			static void L3R_GateM_SetGateStatus(uint8 LogicCh)
 * @brief		GateStatus(中継許可/禁止/保留)の設定
 * @details		GateStatus(中継許可/禁止/保留)の設定を行う
 * @param[in]	LogicCh		CH番号
 * @return		なし
 * @attention	割込禁止処理が必要な場合は呼び出し元で実施すること
 * @note		なし
 ****************************************************************************/
static void L3R_GateM_SetGateStatus(uint8 LogicCh)
{	
	switch(NetworkStatus[LogicCh]){
		case L3R_GM_NS_START:
			{
				if(FailStatus[LogicCh] == L3R_GM_FS_NORMAL){
					GateStatus[LogicCh] = L3R_GM_SEND_OK;
				}
				else if(FailStatus[LogicCh] == L3R_GM_FS_FAIL){
					GateStatus[LogicCh] = L3R_GM_SEND_WAIT;
				}
				else {	/* FailStatus異常値のため、安全側に倒す（中継禁止し、タイマーも最長時間設定） */
					GateStatus[LogicCh] = L3R_GM_SEND_NG;
					FailStatus[LogicCh] = L3R_GM_FS_FAIL;
					FailTimer[LogicCh]  = (uint16)L3R_GM_FT_MAX;
				} 
			}
			break;
		case L3R_GM_NS_STANDBY:
			{
				GateStatus[LogicCh] = L3R_GM_SEND_WAIT;
			}
			break;
		case L3R_GM_NS_STOP:
			{
				GateStatus[LogicCh] = L3R_GM_SEND_NG;
			}
			break;
		default:	/* NetworkStatus異常値のため、安全側に倒す（中継禁止） */
			{
				GateStatus[LogicCh] = L3R_GM_SEND_NG;
							
				if(L3R_GateSpecTbl[LogicCh] == L3R_GATESPEC_NM) {
					NetworkStatus[LogicCh] = L3R_NGate_Nm_Defect();
				} else if(L3R_GateSpecTbl[LogicCh]  == L3R_GATESPEC_IG) {
					NetworkStatus[LogicCh] = L3R_NGate_Ig_Defect();
				} else {
					/* do nothing */
				}
			}
			break;	
	}
	
	return ;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
