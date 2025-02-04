/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_BroadCastCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * @date	v1.10	2018/02/16	T.Yamamura(FSI)		CANIDフィルタ対応
 *													関数CanMessage_ABusErrorHandler引数追加
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・RTR_A_CH→CHM_LOG_CH_A変更
 * 			v2.01	2018/07/20	K.Ito(FSI)			A-Busフィルタ削除対応
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v4.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_DiagQueRouter.h"
#include "L3R_config.h"

#include "L3R_BroadCastCanMessage.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList BroadCastCanMessage_funcList[] = { { BroadCastCanMessage_GetGwId, L3R_NULL } };
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
 * @fn			uint16 BroadCastCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
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
uint16 BroadCastCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	return (self->GwId[rxCh]);
}

/*************************************************************************//**
 * @fn			void BroadCastCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 exd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId, uint32 canId)
 * @brief		中継処理
 * @details		中継処理を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	fd		FD受信フラグ
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	gwId	GWID
 * @param[in]	rxCh	受信CH
 * @param[in]	searchId	探索位置
 * @param[in]	canId	受信したCANID
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void BroadCastCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId, uint32 canId)
{
 	(void) QueRouter_RelayData(&diagQueRouter, canId, dlc, Data, gwId, searchId, fd);

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
