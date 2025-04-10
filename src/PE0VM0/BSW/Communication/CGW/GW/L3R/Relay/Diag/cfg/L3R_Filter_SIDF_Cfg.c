/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Filter_SIDF_Cfg.c
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
 * @note            templates/L3R_Filter_SIDF_CfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_ChCnvtr.h"
/*#include "SIDF_Common.h"*/
/*#include "SIDF_FilterCtrl.h"*/
#include "L3R_FilterCanMessage_Cfg.h"

#include "L3R_Filter_SIDF_Cfg.h"
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
 * @fn			uint8 FilterCanMessage_CheckSidf(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		Sidフィルタ
 * @details		Sidフィルタを行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		受信データ長
 * @param[in]	Data	受信データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		フィルタ判定結果
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint8 FilterCanMessage_CheckSidf(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint8 Ret = L3R_RTN_FILTER_PMT;	/* 戻り値に中継許可を設定 */

#ifdef SIDF_FILTERCTRL_H
	if ((L3R_SIDFILTER_CH_BIT & CHM_ChCnvtr_Log_To_NwType[rxCh]) != 0U) {	/* SIDフィルタ対象チャンネル判定 */
		if (SIDF_FilterCtrl_IsRlyPrmt(self->canid, rxCh, dlc, Data, searchId) == SIDF_RTN_FILTER_PHB){	/* SIDフィルタ判定 */
			CanMessage_SidErrorHandler();
			Ret = L3R_RTN_FILTER_PHB;	/* 戻り値に中継禁止を設定 */
		}
	}
#endif /* #ifdef	SIDF_FILTERCTRL_H */

	return (Ret);
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
