/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DiagQueRouter.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v1.02	2018/05/17	A.Yasui(FSI)		ダイアグフレームのGateオープンが二周期ごと発生する対応
 * 			v2.00	2018/05/15	T.Yamamura(FSI)		GW_RTR_DiagFilterCtrl.hのインクルード削除
 * 			v2.01	2018/05/23	T.Yamamura(FSI)		可変化対応
 * 													・L3R_GwBuffer_cfg.hのインクルード追加
 * 			v2.02	2018.05.30	K.Ito(FSI)			帯域制限削除対応
 * 			v2.03	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・DiagQueRouter_QuickWakeup内に割込み禁止処理追加
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/09/19	Y.Katayama(FSI)		フェール発生CHの送信要求破棄の処理追加
 * 			v3.02	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v5.00	2018/12/25	T.Yamamura(FSI)		新アーキテクチャSBR仕様適合対応
 * 													制御データ中継モード対応
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_Common.h"

#include "L3R_AutoDiagBuf.h"
#include "L3R_AutoTCanRelayRule.h"

#include "L3R_GateManager.h"
#include "L3R_CanMessage.h"
#include "L3R_FrmInfo.h"

#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_main.h"

#include "L3R_Fail.h"

#include "L3R_DiagQueRouter.h"


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
static uint8 DiagQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first);
static void DiagQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer);
static uint16 DiagQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh);
static void DiagQueRouter_CancelSendQue(void);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
CommonBufferFuncList DiagQueRouter_funcList[] = { { CommonBuffer_Init, DiagBuffer_GetGwData } };
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

Create_DiagQueRouter(diagQueRouter, L3R_DIAG_FRMNUM);



#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			static uint8 DiagQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first)
 * @brief		Gateオープン
 * @details		Gateオープン処理を行う
 * @param[in]	pCommBuffer	対象バッファへのポインタ
 * @param[in]	first		Gateオープン初回判定用
 * @return		Gateオープン結果
 * @retval		L3R_TRUE	Gateオープン成功
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static uint8 DiagQueRouter_QuickWakeup(CommonBuffer *pCommBuffer, uint8 first)
{
	uint8 Req = first;

	if (first != L3R_TRUE){
		/*------------------------------------------------------*/
		/* ダイアグフレームは初回のみGateオープンを実施         */
		/*------------------------------------------------------*/
		L3R_DI();
		L3R_GateM_QuickWakeup();
		L3R_EI();
		Req = L3R_TRUE;
	}
	L3R_FrmInfo_SndDiagRlyFrm(pCommBuffer->pFields->canId);	/* ダイアグGW通知情報記憶 */

	return (Req);
}

/*************************************************************************//**
 * @fn			static void DiagQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer)
 * @brief		データ上書き時の処理
 * @details		データ上書き時の処理を行う
 * @param[in]	self			自身へのポインタ
 * @param[in]	ppCommBuffer	対象バッファへのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static void DiagQueRouter_OverWrite(Router *self, CommonBuffer **ppCommBuffer)
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
 * @fn			static uint16 DiagQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh)
 * @brief		送信先プロトコルを返す
 * @details		既定の送信先に、動的送信先を考慮して決定
 * @param[in]	pCommonBuffer	対象バッファへのポインタ
 * @param[in]	gwId			GWID
 * @param[in]	rxCh			受信CH
 * @return		送信先プロトコル
 * @attention 	SIDフィルタもここで対応
 * @note		なし
 ****************************************************************************/
static uint16 DiagQueRouter_GetSendProtocol(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh)
{
#if (L3R_TDIAG_IDNUM > 0U)
	CommonBufferFields *pBufferFields = pCommonBuffer->pFields;
	uint16 FailChBit;

	/* L3R_TDIAG_IDSTARTのオフセットを配慮する必要がある */
	uint16 sndPrtclBit = L3R_TDiagSndPrtclBit[gwId - L3R_TDIAG_IDSTART];
	
	/* フェール発生CHへの送信要求を破棄する */
	FailChBit = L3R_Fail_GetFailChBitAll();
	sndPrtclBit &= ~(FailChBit);

	if (pBufferFields->fd == L3R_ON) {
		sndPrtclBit &= L3R_CAN_PRTCL_BIT_DIAG;
	}
	
	return (sndPrtclBit);
#else
    return ((uint16)0x0000U);
#endif /* #if (L3R_TDIAG_IDNUM > 0U) */
}

/*************************************************************************//**
 * @fn			static void GwIdRouter_CancelSendQue(void)
 * @brief		送信キュー内の要求をすべて削除する
 * @details		送信キュー内の要求をすべて削除する
 * @param		なし
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
static void DiagQueRouter_CancelSendQue(void)
{
	(void)CANMBQ_ClrSndQue(CANMBQ_QUEID_DIAG);

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
