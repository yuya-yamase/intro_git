/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	Cid_Search.c
 * @brief	CANID探索
 * @details	
 * @note	なし
 * @date	v1.00	2022/09/22	T.Matsushita(FSI)		新規作成
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "Cid_Data.h"
#include "Cid_Notify_Cfg.h"
#include "Cid_Search.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
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
#define GW_CID_START_SEC_CODE
#include "GW_Cid_Memmap.h"

/*************************************************************************//**
 * @fn			void Cid_Search_ReceiveCanData(uint8 rxCh, const CanMsgType* ptMsg)
 * @brief		CAN受信完了通知処理
 * @details		CAN受信したメッセージを通知します
 * @param[in]	uint8 rxCh			受信CH
 * @param[in]	const CanMsgType* ptMsg		受信データポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Cid_Search_ReceiveCanData(uint8 rxCh, const CanMsgType* ptMsg)
{
	uint32 canId = (ptMsg->u4Id & CID_TCOV_MSK_CANCOM); /* CANFD,拡張ビットを落とす */
	uint16	search_min = 0x0U;
	uint16	search_max;
	uint16	searchId;
	uint16	retIndex = CID_NO_SEARCH;
	CanidDataArraySet *pCidDataArrayNow;
	
	/* 拡張ID判定 */
	if (canId > CID_NOMALCANID_MAX) {
		/* 拡張ID探索用に設定 */
		pCidDataArrayNow = Cid_Data_CanId_Ex_UserTable;
		search_max = CID_SEARCHEX_MAX -1U;
	}else {
		/* 標準ID探索用に設定 */
		pCidDataArrayNow = Cid_Data_CanId_UserTable;
		search_max = CID_SEARCH_MAX -1U;
	}
	
	/* CANIDを探索 */
	while (search_min <= search_max) {
		searchId = ((search_max + search_min) >> 1U);
		if (canId == pCidDataArrayNow[searchId].canid_s) {
			retIndex = searchId;
			break;
		} else if (canId < pCidDataArrayNow[searchId].canid_s) {
			if ((uint32)searchId == (uint32)0) {
				break;
			}
			search_max = searchId - 1U;
		} else {
			search_min = searchId + 1U;
		}
	}

	
	Cid_Notify_SearchResult(rxCh, ptMsg->u4Id, ptMsg->u1Length, ptMsg->ptData, retIndex, pCidDataArrayNow);
	
	return;
}

/*************************************************************************/ /**
 * @fn			uint16 Cid_Search_GetIndexNo(uint32 canId, const uint32 *pCanIdTableNow, uint16 canIdSearchMax)
 * @brief		CANID探索処理
 * @details		テーブルよりCANIDを探索しIndex番号を返す
 * @param[in]	uint32 canId								探索CANID
 * @param[in]	uint32 *pCanIdTableNow						探索するテーブル
 * @param[in]	uint16 canIdSearchMax						探索テーブル数
 * @return		retIndex									Indexb番号
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint16 Cid_Search_GetIndexNo(uint32 canId, const uint32 *pCanIdTableNow, uint16 canIdSearchMax)
{
	uint32 recCanId;
	uint16 searchMin = 0x0U;
	uint16 searchMax = canIdSearchMax;
	uint16 searchId;
	uint16 retIndex = CID_NO_SEARCH;

	recCanId = (canId & CID_TCOV_MSK_CANCOM); /* CANFD,拡張ビットを落とす */
	
	/* MAX値の調整 */
	if (searchMax != 0U){
		searchMax = searchMax - 1U;
	
		/* CANIDを探索 */
		while (searchMin <= searchMax) {
			searchId = ((searchMax + searchMin) >> 1U);
			if (recCanId == pCanIdTableNow[searchId]) {
				retIndex = searchId;
				break;
			} else if (recCanId < pCanIdTableNow[searchId]) {
				if ((uint32)searchId == (uint32)0) {
					break;
				}
				searchMax = searchId - 1U;
			} else {
				searchMin = searchId + 1U;
			}
		}
	}
	return (retIndex);
}

#define GW_CID_STOP_SEC_CODE
#include "GW_Cid_Memmap.h"
