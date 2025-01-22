/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DynamicQueRouter.c
 * @brief	動的Queルーター
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v1.02	2018/05/22	A.Yasui(FSI)		コーディング規約対応(オブジェクト不変の修正2)
 * 			v2.00	2018/05/23	T.Yamamura(FSI)		可変化対応
 * 													・L3R_GwBuffer_cfg.hのインクルード追加
 * 			v2.01	2018.05.30	K.Ito(FSI)			帯域制限削除対応
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/09/19	Y.Katayama(FSI)		フェール発生CHの送信要求破棄の処理追加
 * 			v3.02	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v4.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 *			v5.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_Common.h"

#include "L3R_CanMessage.h"

#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_main.h"

#include "L3R_Fail.h"

#include "L3R_DynamicQueRouter.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
static uint8 DynamicQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first);
static void DynamicQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer);
static uint16 DynamicQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh);
static void DynamicQueRouter_CancelSendQue(void);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CommonBufferFuncList DynamicQueRouter_funcList[] = { { CommonBuffer_Init, DynamicBuffer_GetGwData } };
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

Create_DynamicQueRouter(dynamicQueRouter, DYNAMIC_QUE_FRMNUM);


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			static uint8 DynamicQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first)
 * @brief		Gateオープン
 * @details		Gateオープン処理を行う
 * @param[in]	pCommBuffer	対象バッファへのポインタ
 * @param[in]	first		Gateオープン初回判定用
 * @return		Gateオープン結果
 * @retval		L3R_TRUE	Gateオープン成功
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static uint8 DynamicQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first)
{
	uint8 Req = L3R_TRUE;			/* 処理不要　2017/11/15 */

	return (Req);
}

/*************************************************************************//**
 * @fn			static void DynamicQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer)
 * @brief		データ上書き時の処理
 * @details		データ上書き時の処理を行う
 * @param[in]	self			自身へのポインタ
 * @param[in]	ppCommBuffer	対象バッファへのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static void DynamicQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer)
{
	RouterFields *pQueRouterFields = self->pFields;
	const uint16 size = self->size;
	
	/*----------------------------------------------------------------------*/
	/* データ上書き時の処理													*/
	/*----------------------------------------------------------------------*/
	if (pQueRouterFields->readCount >= size) {
		/* 上書きされるデータの送信バッファからの削除 */
		CANMBQ_SendcancelAll(*ppCommBuffer);
	}

	return;
}

/*************************************************************************//**
 * @fn			static uint16 DynamicQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh)
 * @brief		送信先プロトコルを返す
 * @details		既定の送信先に、動的送信先を考慮して決定
 * @param[in]	pCommonBuffer	対象バッファへのポインタ
 * @param[in]	gwId			GWID
 * @param[in]	rxCh			受信CH
 * @return		送信先プロトコル
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static uint16 DynamicQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh)
{
	CommonBufferFields *pBufferFields = pCommonBuffer->pFields;
	uint16 searchId = pBufferFields->searchId;
	uint16 sndPrtclBit = CanMessage_GetSendProtocol(searchId);
	uint16 FailChBit;
	
	/* 送信中でない中継先のみを、送信先とする */
	sndPrtclBit = (sndPrtclBit & pBufferFields->sndPrtclBit) ^ sndPrtclBit;
	
	/* フェール発生CHへの送信要求を破棄する */
	FailChBit = L3R_Fail_GetFailChBitAll();
	sndPrtclBit &= ~(FailChBit);
	
	return (sndPrtclBit);
}

/*************************************************************************//**
 * @fn			static void DynamicQueRouter_CancelSendQue(void)
 * @brief		送信キュー内の要求をすべて削除する
 * @details		送信キュー内の要求をすべて削除する
 * @param		なし
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static void DynamicQueRouter_CancelSendQue(void)
{
	(void)CANMBQ_ClrSndQue(CANMBQ_QUEID_DYNAMC);

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
