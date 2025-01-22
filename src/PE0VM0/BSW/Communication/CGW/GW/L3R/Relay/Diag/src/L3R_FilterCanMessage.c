/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_FilterCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2023/06/07	T.Matsushita(FSI)		新規作成
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_DiagQueRouter.h"
#include "L3R_FilterCanMessage.h"
#include "L3R_FilterCanMessage_Cfg.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList FilterCanMessage_funcList[] = { { FilterCanMessage_GetGwId, FilterCanMessage_RelayData } };
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			uint16 FilterCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		GwIdの取得
 * @details		GwIdの取得を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		受信データ長
 * @param[in]	Data	受信データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		GwID
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint16 FilterCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint8 count;				/* フィルタカウンタ */
	FilterFunc *pFilterType_FuncListTable; /* フィルタタイプ ファンクションリストテーブル ポインタ */
	uint8 filterType;			/* フィルタタイプ */
	uint8 funcCount_cfg;		/* フィルタファンクションのカウンタコンフィグ値 */
	
	uint16 gwId = self->GwId[rxCh];	 /* GwIdの取得 */
	
	filterType = pFilterCanMessageArrayNow[searchId];	/* 探索位置からフィルタタイプを取得 */
	
	pFilterType_FuncListTable = FilterType_FuncListTable[filterType];	/* フィルタタイプからファンクションリストテーブルのポインタ取得 */
	funcCount_cfg = FilterType_FuncListTable_Num[filterType];	/* フィルタファンクションのカウンタコンフィグ値を取得 */

	for (count = 0; count < funcCount_cfg; count++)	/* フィルタファンクション数のカウンタコンフィグ値分のフィルタ実行 */
	{
		/* フィルタファンクションからフィルタ判定結果を取得し判定 */
		if(pFilterType_FuncListTable[count](self, rxCh, dlc, Data, searchId) == L3R_RTN_FILTER_PHB){
			gwId = FILTERERR_GWID;	/* フィルタエラー */
			break;
		}
	}
	
	return (gwId);
}

/*************************************************************************//**
 * @fn			void FilterCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
 * @brief		中継処理
 * @details		中継処理を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	fd		FD受信フラグ
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	gwId	GWID
 * @param[in]	rxCh	受信CH
 * @param[in]	searchId	探索位置
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void FilterCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
{
	(void) QueRouter_RelayData(&diagQueRouter, self->canid, dlc, Data, gwId, searchId, fd);

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
