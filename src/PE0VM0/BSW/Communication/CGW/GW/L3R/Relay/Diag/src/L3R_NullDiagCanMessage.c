/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_NullDiagCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * @date	v1.10	2018/02/16	T.Yamamura(FSI)		CANIDフィルタ対応
 *													関数CanMessage_ABusErrorHandler引数追加
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・GW_RTR_config.h→CHM_LogicCh.h変更
 * 													・RTR_A_CH→CHM_LOG_CH_A変更
 * 			v2.01	2018/07/20	K.Ito(FSI)			A-Busフィルタ削除対応
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_NullDiagCanMessage.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList NullDiagCanMessage_funcList[] = { { NullDiagCanMessage_GetGwId, NullCanMessage_RelayData } };
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
 * @fn			uint16 NullDiagCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
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
uint16 NullDiagCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	return (NULL_GWID);
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
