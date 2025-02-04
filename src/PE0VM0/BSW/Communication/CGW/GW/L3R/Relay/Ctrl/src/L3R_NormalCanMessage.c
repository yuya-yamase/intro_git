/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_NormalCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・マクロ定義RTR_TCON_USE_MSGIDをGW_RTR_config.hへ移動(名称変更)
 * 			v2.01	2018/05/10	K.Ito(FSI)			[1052827]	課題対応
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v5.00	2018/12/25	T.Yamamura(FSI)		新アーキテクチャSBR仕様適合対応
 * 													制御データ中継モード対応
 *			v6.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_Common.h"
#include "L3R_config.h"
#include "L3R_GwIdRouter.h"

#include "L3R_NormalCanMessage.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList NormalCanMessage_funcList[] = { { NormalCanMessage_GetGwId, NormalCanMessage_RelayData } };
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
 * @fn			uint16 NormalCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
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
uint16 NormalCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint16 gwId = self->GwId[rxCh];

	if(gwId == NULL_GWID) {
		/* 対象チャンネルが、ルーティングマップに登録されていない場合は、動的ルーティングで対応 */
		gwId = DynamicCanMessage_GetGwId(self, rxCh, dlc, Data, searchId);
	}

	return (gwId);
}

/*************************************************************************//**
 * @fn			void NormalCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
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
/* 通常のGW対象制御フレームの場合 */
void NormalCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
{
	if(gwId != DYNAMIC_GWID) {
		/* 戻り値（データを保存するCommonBufferへのポインタ）を処理する必要がない */
		(void)IdRouter_RelayData(&gwIdRouter, (self->canid), dlc, Data, gwId, rxCh, searchId, fd);
	}else{
		/* 対象チャンネルが、ルーティングマップに登録されていない場合は、動的ルーティングで対応 */
		DynamicCanMessage_RelayData(self, fd, dlc, Data, gwId, rxCh, searchId);
	}

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
