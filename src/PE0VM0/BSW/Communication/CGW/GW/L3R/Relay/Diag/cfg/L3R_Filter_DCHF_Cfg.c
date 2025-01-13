/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Filter_DCHF_Cfg.c
 * @brief		
 * @details		
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		制御フレームルーティングマップ：
 * @note            Ctrl_RTM.xlsx
 * @note		ダイアグ/リプログフレームルーティングマップ：
 * @note            Diag_RTM.xlsx
 * @note		チャンネル定義ファイル：
 * @note            channelDef.yml
 * @note		チャンネル定義ファイル(L3R)：
 * @note            channelDef_L3R.yml
 * @note		例外フレーム定義ファイル：
 * @note            exceptionalMessages.yml
 * @note		テンプレートファイル：
 * @note            templates/L3R_Filter_DCHF_CfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

/*#include "DCHF_Mng.h"*/
#include "L3R_FilterCanMessage_Cfg.h"

#include "L3R_Filter_DCHF_Cfg.h"
/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			uint8 FilterCanMessage_CheckDchfReq(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		Dchf要求フィルタ
 * @details		Dchf要求フィルタを行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		受信データ長
 * @param[in]	Data	受信データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		フィルタ判定結果
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint8 FilterCanMessage_CheckDchfReq(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint8 Ret = L3R_RTN_FILTER_PHB;	/* 戻り値に中継禁止を設定 */

	if ( (self->GwId[rxCh]) != NULL_GWID) {

#ifdef DCHF_MNG_H
		/* DCHF状態遷移のため受信Chを要求として通知 */
		DCHF_Mng_UpdateStateByChannel(rxCh, DCHF_MNG_RX_TYPE_REQ);
		
		/* 受信Chが有効であるか判定 */
		if(DCHF_Mng_JudgeValidBus(rxCh) == DCHF_MNG_RTN_RELAY_PMT){
			Ret = L3R_RTN_FILTER_PMT;	/* 戻り値に中継許可を設定 */
		}
#else
		Ret = L3R_RTN_FILTER_PMT;	/* 戻り値に中継許可を設定 */
#endif /* #ifdef DCHF_MNG_H */
	}

	return (Ret);
}

/*************************************************************************//**
 * @fn			uint8 FilterCanMessage_CheckDchfRes(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		Dchf応答フィルタ
 * @details		Dchf応答フィルタを行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		受信データ長
 * @param[in]	Data	受信データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		フィルタ判定結果
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint8 FilterCanMessage_CheckDchfRes(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint8 Ret = L3R_RTN_FILTER_PMT;	/* 戻り値に中継許可を設定 */

#ifdef DCHF_MNG_H
	if ( (self->GwId[rxCh]) != NULL_GWID) {
		/* DCHF状態遷移判定のため受信Chを応答として通知 */
		DCHF_Mng_UpdateStateByChannel(rxCh, DCHF_MNG_RX_TYPE_RES);
	}
#endif

	return (Ret);
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
