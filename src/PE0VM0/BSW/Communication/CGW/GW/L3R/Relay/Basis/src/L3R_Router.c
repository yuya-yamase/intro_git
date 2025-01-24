/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_Router.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・Router_SendGWIdOverWrite()共通化(引数、処理変更）
 * 													・Router_SendGWId()マクロ→関数化(L3R_Router.hから移動）
 * 													・L3R_CAN300Adapter.hインクルード削除
 * 			v2.01	2018/06/07	T.Yamamura(FSI)		QAC対応
 * 													・u1g_GW_RTR_TConvertor_SendGWId()戻り値の無効化
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/09/19	Y.Katayama(FSI)		フェール発生CH情報初期化追加
 *													5msタスク定期処理関数追加
 * 			v3.02	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "CHM_LogicCh.h"

#if (CHM_LOG_ETH_CH_NUM != 0)
#include "CEConv.h"
#endif

#include "L3R_AutoTCanConvertRule.h"
#include "L3R_canmbq_main.h"
#include "L3R_Common.h"
#include "L3R_CommonBuffer.h"
#include "L3R_LIB.h"
#include "L3R_Timer.h"

#include "L3R_Router.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/

/* MBQ 送信要求結果 */
#define L3R_FULL_OK						(CANMBQ_FULL_OK)

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			void Router_Init(Router *self)
 * @brief		リセット初期化処理
 * @details		リセット時初期化処理を管理する(割り込み禁止でコール)
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Router_Init(Router *self)
{
	CommonBuffer *pBuffer;
	uint32 id;
	uint32 size = self->size;
	
	/* ID毎バッファ初期化 */
	for(id = 0; id < size; id++){
		pBuffer	= self->pBuffer[id];
		pBuffer->funcList->Init(pBuffer);
	}
	
	return ;
}

/*************************************************************************//**
 * @fn			void Router_SendGWIdOverWrite(uint8 ch, CommonBuffer *const pCommonBuffer)
 * @brief		MBQ格納要求（送信バッファフル時は、上書き対象のバッファの送信ステータスをクリアする）
 * @details		MBoxQue制御へ送信要求する
 * @param[in]	ch				送信先
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Router_SendGWIdOverWrite(uint8 ch, CommonBuffer *const pCommonBuffer)
{
	uint8 sendReq;								/* 送信要求結果		*/
	CommonBuffer *pBufferToDell = NULL_PTR;		/* 削除対象バッファ	*/

	sendReq = CANMBQ_Sendreq_GWmsg(ch, pCommonBuffer, &pBufferToDell);
	if ((sendReq == L3R_FULL_OK) 
		&& (pBufferToDell != NULL_PTR)){
		CommonBuffer_ClrSndStatusCh(pBufferToDell, ch);
	}
	CommonBuffer_SetSndStatusCh(pCommonBuffer, ch);

	return;
}

/*************************************************************************//**
 * @fn			void Router_SendGWIdOverWrite_Tx(uint8 ch, CommonBuffer *const pCommonBuffer)
 * @brief		MBQ送信要求（送信バッファフル時は、上書き対象のバッファの送信ステータスをクリアする）
 * @details		MBoxQue制御へ送信要求する
 * @param[in]	ch				送信先
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Router_SendGWIdOverWrite_Tx(uint8 ch, CommonBuffer *const pCommonBuffer)
{
	uint8 sendReq;								/* 送信要求結果		*/
	CommonBuffer *pBufferToDell = NULL_PTR;		/* 削除対象バッファ	*/

	sendReq = CANMBQ_Sendreq_GWmsg(ch, pCommonBuffer, &pBufferToDell);
	if ((sendReq == L3R_FULL_OK) 
		&& (pBufferToDell != NULL_PTR)){
		CommonBuffer_ClrSndStatusCh(pBufferToDell, ch);
	}
	CommonBuffer_SetSndStatusCh(pCommonBuffer, ch);
	
	/* 1ms定周期を待たずに送信要求する */
	CANMBQ_SendReq_Tx(ch, pCommonBuffer);
	
	return;
}

/*************************************************************************//**
 * @fn			void Router_SendGWId(uint8 ch, CommonBuffer *const pCommonBuffer)
 * @brief		MBQ格納要求
 * @details		MBoxQue制御へ送信要求する
 * @param[in]	ch				送信先
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Router_SendGWId(uint8 ch, CommonBuffer *const pCommonBuffer)
{
	(void)CANMBQ_Sendreq_GWmsg(ch, pCommonBuffer, L3R_NULL);
	CommonBuffer_SetSndStatusCh(pCommonBuffer, ch);

	return;
}

/*************************************************************************//**
 * @fn			void Router_SendGWId_Tx(uint8 ch, CommonBuffer *const pCommonBuffer)
 * @brief		MBQ送信要求
 * @details		MBoxQue制御へ送信要求する
 * @param[in]	ch				送信先
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void Router_SendGWId_Tx(uint8 ch, CommonBuffer *const pCommonBuffer)
{
	(void)CANMBQ_Sendreq_GWmsg(ch, pCommonBuffer, L3R_NULL);
	CommonBuffer_SetSndStatusCh(pCommonBuffer, ch);
	
	/* 1ms定周期を待たずに送信要求する */
	CANMBQ_SendReq_Tx(ch, pCommonBuffer);
	
	return;
}

/*************************************************************************/ /**
 * @fn			void Router_CEConvAdapter_SendReq(uint8 ch, CommonBuffer *pCommonBuffer)
 * @brief		送信要求の受付
 * @details		1ms定期処理で呼び出される
 * @param[in]	ch				送信先
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
#if (CHM_LOG_ETH_CH_NUM != 0)
void Router_CEConvAdapter_SendReq(uint8 ch, CommonBuffer *pCommonBuffer)
{
	uint8 containerId;
	CEConvCanMsgType currentMsg;

	currentMsg.CanId  = pCommonBuffer->pFields->canId;
	currentMsg.Length = pCommonBuffer->pFields->length;
	currentMsg.pData  = pCommonBuffer->Data;
	
	containerId = L3R_Log_To_ContainerTable[ch];
	
	if (containerId != CECONV_CONTAINER_INVALID) {
		CEConv_CanTxReq(&currentMsg, containerId);
	}
	CommonBuffer_ClrSndStatusCh(pCommonBuffer, ch);

	return;
}
#endif

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
