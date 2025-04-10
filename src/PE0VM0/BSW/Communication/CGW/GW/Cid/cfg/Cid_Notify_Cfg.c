/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		Cid_Notify_Cfg.c
 * @brief		受信情報通知
 * @details
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成（Cid）
 * @note        CNIDS-IDテーブル：
 * @note            CNIDS-ID_Table.yml
 * @note        L3R-IDテーブル：
 * @note            L3R-ID_Table.yml
 * @note		テンプレートファイル：
 * @note            templates/Notify_CfgC.tmpl
 * @note	ツールバージョン
 * @note		1.8.0
 ****************************************************************************/
/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_CanMessageExt.h"

#include "Cid_Data.h"
#include "Cid_Notify_Cfg.h"
/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		公開関数定義														*/
/*--------------------------------------------------------------------------*/
#define GW_CID_START_SEC_CODE
#include "GW_Cid_Memmap.h"

/*************************************************************************//**
 * @fn		void Cid_Notify_SearchResult(uint8 rxCh, uint32 canId, uint8 dlc, uint8 *Data, uint16 searchId, CanidDataArraySet *pCidDataArrayNotify)
 * @brief		CAN受信情報通知
 * @details		CAN受信情報を通知します
 * @param[in]	uint8 rxCh								受信Ch
 * @param[in]	uint32 canId							受信canId（フラグ付き）
 * @param[in]	uint8 dlc								受信データ長
 * @param[in]	uint8 *Data								受信データポインタ
 * @param[in]	uint16 searchId							ID探索位置(インデックス)
 * @param[in]	CanidDataArraySet *pCidDataArrayNotify	探索するテーブル	
 * @return		なし
 * @attention 	なし
 * @note		CNIDS搭載がない場合は通知関数なし
 ****************************************************************************/
void Cid_Notify_SearchResult(uint8 rxCh, uint32 canId, uint8 dlc, uint8 *Data, uint16 searchId, CanidDataArraySet *pCidDataArrayNotify)
{
	uint16  canmsgIndex;
	
	
	/*L3Rの処理*/
	if (searchId != CID_NO_SEARCH) { 
		/* 中継情報収集 */
		canmsgIndex = pCidDataArrayNotify[searchId].canmsgIndex;
	} else {	
		canmsgIndex = 0x0U;
	}	
	/* L3Rへ受信情報通知 */
	L3R_CM_Receive(rxCh, canId, dlc, Data, canmsgIndex);
	
	return;
}

#define GW_CID_STOP_SEC_CODE
#include "GW_Cid_Memmap.h"

