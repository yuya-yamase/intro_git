/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_NullCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * @date	v1.10	2018/02/16	T.Yamamura(FSI)		CANIDフィルタ対応
 *													関数CanMessage_DiagBusErrorHandler引数追加
 * @date	v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * @date	v2.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 * @date	v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * @date	v3.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 * @date	v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_config.h"

#include "L3R_NullCanMessage.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList NullCanMessage_funcList[] = { { NullCanMessage_GetGwId, NullCanMessage_RelayData } };
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
 * @fn			uint16 NullCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		GwIdの取得
 * @details		GwIdの取得を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		GwId
 * @retval		NULL_GWID		中継対象外時のGwId
 * @retval		FILTERERR_GWID	CAN/DLC/SIDエラー検出時のGwId
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint16 NullCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint16 gwId = NULL_GWID;

	if(rxCh == CHM_LOG_CH_USE_DIAG){
		CanMessage_DiagBusErrorHandler(rxCh, self->canid);
		gwId = FILTERERR_GWID;
	}

	return (gwId);
}

/*************************************************************************//**
 * @fn			void NullCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
 * @brief		中継処理
 * @details		中継処理を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	fd		FD受信フラグ
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	gwId	GwId
 * @param[in]	rxCh	受信CH
 * @param[in]	searchId	探索位置
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void NullCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
{
	/* 処理なし */
	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
