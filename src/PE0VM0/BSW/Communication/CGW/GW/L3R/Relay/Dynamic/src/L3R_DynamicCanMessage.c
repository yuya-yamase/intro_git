/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DynamicCanMessage.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * @date	v1.10	2018/02/16	T.Yamamura(FSI)		CANIDフィルタ対応
 *													関数CanMessage_DiagBusErrorHandler引数追加
 * 			v1.11	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 *													・CH名称CHM_LOG_BIT_DIAG→RTR_LOG_BIT_DIAGへ変更
 * 													・GW_RTR_config.hのインクルード追加
 * 			v2.01	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・DynamicCanMessage_RelayData内に割込み禁止処理追加
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v4.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 * 			v4.02	2019/07/23	N.Shiraishi(FSI)	[IntegNo.1118454]
 *													[570B-Phase9] 【L3R】NMフレームを中継できない 対応
 * 			v4.03	2019/10/08	T.Yamamura(FSI)		[IntegNo.1124545]
 *													[570B-Phase10] CAN300収集対象外フレームの条件変更
 *			v5.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "L3R_CommonBuffer.h"

#include "CHM_LogicCh.h"
#include "L3R_DynamicQueRouter.h"

#include "L3R_DynamicCanMessage.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CanMessageFuncList DynamicCanMessage_funcList[] = { { DynamicCanMessage_GetGwId, DynamicCanMessage_RelayData } };
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
 * @fn			uint16 DynamicCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
 * @brief		GwIdの取得
 * @details		GwIdの取得を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	rxCh	受信CH
 * @param[in]	dlc		受信データ長
 * @param[in]	Data	受信データへのポインタ
 * @param[in]	searchId	探索位置
 * @return		GWID
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint16 DynamicCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId)
{
	uint16 gwId = DYNAMIC_GWID;
	uint16 *pSndPrtclBit = self->pSndPrtclBit;

	if(rxCh == CHM_LOG_CH_USE_DIAG){
		CanMessage_DiagBusErrorHandler(rxCh, self->canid);
		gwId = FILTERERR_GWID;
	}else{
		if (*pSndPrtclBit == 0U){
			gwId = NULL_GWID;
		}else{
			/* 動的ルーティング */
			CanMessage_UnKnownErrorHandler();
		}
	}

	return (gwId);
}

/*************************************************************************//**
 * @fn			void DynamicCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
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
void DynamicCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId)
{
	
	CommonBuffer **ppCommonBuffer;
	CommonBuffer *pCommonBuffer;
	uint32 canId;
	
	L3R_DI();
	ppCommonBuffer = self->ppCommonBuffer;
	pCommonBuffer = *ppCommonBuffer;
	canId = self->canid;
	if ((pCommonBuffer == NULL_PTR)
		|| (pCommonBuffer->pFields->canId != self->canid)
		|| ((pCommonBuffer->pFields->sndPrtclBit == 0U) && (pCommonBuffer->pFields->sndPrtclReqBit == 0U))
		) {
		/* 新規送信 */
		*ppCommonBuffer = QueRouter_RelayData(&dynamicQueRouter, canId, dlc, Data, gwId, searchId, fd);
	}else{
		*ppCommonBuffer = QueRouter_RelayDataByBuffer(&dynamicQueRouter, pCommonBuffer, canId, dlc, Data, gwId, searchId);
		QueRouter_SendReq(*ppCommonBuffer);
	}
	(*ppCommonBuffer)->pFields->fd = fd;
	L3R_EI();

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
