/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_main.c										*/
/*【モジュール名】	MBOXキュー制御 											*/
/*【機能】			CAN MBOXキュー制御 処理									*/
/*																			*/
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.05.09	@author	K.Hirakata(NCOS)
 *		MPC 5604C対応 MBOXキュー制御として新規作成
 *	@version	1.0.1	2013.06.13	@author	K.Hirakata(NCOS)
 *		送信キャンセル関数(ダミー)を追加
 *	@version	1.0.2	2013.11.12	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(識別子に関するルール適合)
 *	@version	1.0.3	2013.12.20	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(ルール16.9)
 *		MBQ初期化契機追加(バススリープ/ウェイクアップ時)
 *	@version	1.0.4	2014.02.25	@author	K.Hirakata(NCOS)
 *		送信要求クリアAPI対応
 *	@version	1.0.5	2014.08.08	@author	K.Yokooka (FSI)
 *		課題No.17816対応 送信要求関数に引数 DelIndexNum追加
 *	@version	1.0.6	2017.03.03	@author	Y.Katayama(FSI)
 *		19PF向けの型定義に変更
 *		CH数の追加対応(8CH対応)
 *	@version	1.0.7	2018.05.16	@author	A.Yasui(FSI)
 *		ダイアグバスに送信するフレームの送信順番が入れ替わる対応
 *	@version	2.0.0	2018.05.16	@author	T.Yamamura(FSI)
 *		可変化対応 TxChannel定義のcanmbq_auto_cfg.cへ移動
 *	@version	2.0.1	2018.05.22	@author	A.Yasui(FSI)
 *		コーディング規約対応(オブジェクト不変の修正2)
 *	@version	2.0.2	2018.05.30	@author	K.Ito(FSI)
 *		帯域制限削除対応
 *	@version	2.0.3	2018.06.19	@author	K.Ito(FSI)
 *		帯域制限追加対応
 *	@version	2.0.4	2018.10.25	@author	T.Yamamura(FSI)
 *		コードレベルアップ対応(オブジェクト不変)
 *	@version	3.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#include "L3R_BandLimit.h"
#include "L3R_canmbq_common.h"
#include "L3R_canmbq_tx.h"
#include "L3R_CommonBuffer.h"

#include "L3R_canmbq_main.h"


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static uint8 CanmbqSendLockErr[CANMBQ_CHMAX];
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void CANMBQ_Omed_Er(void)
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_Omed_Er(void)
{
	uint32 ch;
	
	CANMBQ_ClrSendLockFlg();
	
	for (ch = 0; ch < CANMBQ_CHMAX; ch++)
	{
		TxChannel_Omed_SndLock(txChannelArray[ch]);
	}

	return;
}

/**
 * @fn			void CANMBQ_DriverTask(void)
 * @brief		1msタスク処理
 * @details		1msタスク処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_DriverTask(void)
{
	uint8 bandLimitCheck;
	
	L3R_DI();
	
	bandLimitCheck = BandLimit_JudgeLimit();
	
	TxChannel_ClrTxCnt();
	
	L3R_EI();
	
	if (L3R_E_OK == bandLimitCheck) {
		uint32 ch;
		TxChannel *const *ppTxChannel = txChannelArray;

		for (ch = 0; ch < CANMBQ_CHMAX ; ch++)
		{		
			(*ppTxChannel)->drvTaskTx(*ppTxChannel);
			ppTxChannel++;
		}
	}
	
	return;
}

/**
 * @fn			void CANMBQ_ClrSendLockFlg(void)
 * @brief		送信ロックフラグクリア
 * @details		送信ロックフラグをクリアする
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_ClrSendLockFlg(void)
{
	uint32 ch;
	
	for (ch = 0; ch < CANMBQ_CHMAX; ch++) {
		CanmbqSendLockErr[ch] = CANMBQ_CLR;
	}
	
	return;
}

/**
 * @fn			void CANMBQ_SetSendLockFlg(uint8 ch)
 * @brief		送信ロックフラグセット
 * @details		送信ロックフラグをセットする
 * @param[in]	ch	CH番号
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_SetSendLockFlg(uint8 ch)
{
	CanmbqSendLockErr[ch] = CANMBQ_SET;
	return;
}

/**
 * @fn			uint8 CANMBQ_GetSendLockFlg(uint8 ch)
 * @brief		送信ロックフラグ取得
 * @details		送信ロックフラグを取得する
 * @param[in]	ch	CH番号
 * @return		送信ロックフラグ
 * @retval		CANMBQ_SET	フラグセット
 * @retval		CANMBQ_CLR	フラグクリア
 * @attention	なし
 * @note		なし
 */
uint8 CANMBQ_GetSendLockFlg(uint8 ch)
{
	uint8 ret;
	
	ret = CanmbqSendLockErr[ch];
	
	return ret;
}

/**
 * @fn			uint8 CANMBQ_Sendreq_GWmsg(uint8 ch, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell)
 * @brief		MBQへの送信要求
 * @details		MBQへの送信要求を行う
 * @param[in]	ch				CH番号
 * @param[in]	pCommonBuffer	書き込み対象となるCommonBufferへのポインタ
 * @param[in]	ppBufferToDell	削除対象CommonBufferの格納先
 * @return		書き込み結果
 * @retval		CANMBQ_INVALID	書き込み対象なし(書き込み失敗)
 * @retval		CANMBQ_OK		書き込み成功
 * @retval		CANMBQ_FULL_OK	MBQバッファフル(書き込み成功)
 * @attention	割り込み禁止で呼び出される
 * @note		なし
 */
uint8 CANMBQ_Sendreq_GWmsg(uint8 ch, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell)
{	
	TxChannel *pTxChannel = txChannelArray[ch];
	uint8 ret = TxChannel_WriteSendQue(pTxChannel, pCommonBuffer, ppBufferToDell);
	
	return ret;
}

/**
 * @fn			void CANMBQ_ClrSndQueAll(void)
 * @brief		MBQクリア
 * @details		MBQの全CHの全キューをクリアする
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_ClrSndQueAll(void)
{
	uint32 ch;
	
	for (ch = 0; ch < CANMBQ_CHMAX; ch++) {
		TxChannel *pTxChannel = txChannelArray[ch];
		TxChannel_ClrSndQueAll(pTxChannel);
	}
	
	return;
}

/**
 * @fn			uint8 CANMBQ_ClrSndQueAllWithBuffer(uint8 ch)
 * @brief		特定CHの全キュークリア(バッファ情報を含む)
 * @details		特定CHの全キュー(バッファ情報を含む)をクリアする
 * @param[in]	ch				CH番号
 * @return		クリア結果
 * @retval		CANMBQ_INVALID	クリア対象なし
 * @retval		CANMBQ_OK		クリア成功
 * @attention	なし
 * @note		なし
 */
uint8 CANMBQ_ClrSndQueAllWithBuffer(uint8 ch)
{
	uint8 ret = CANMBQ_OK;
	
	if (ch >= CANMBQ_CHMAX) {
		ret = CANMBQ_INVALID;
	} else {
		TxChannel *pTxChannel = txChannelArray[ch];
		TxChannel_ClrSndQueAllWithBuffer(pTxChannel);
	}
	
	return ret;
}

/**
 * @fn			uint8 CANMBQ_ClrSndQue(uint8 queId)
 * @brief		全CHの特定キュークリア
 * @details		全CHの特定キューをクリアする
 * @param[in]	queId			キュー番号
 * @return		クリア結果
 * @retval		CANMBQ_INVALID	クリア対象なし
 * @retval		CANMBQ_OK		クリア成功
 * @attention	なし
 * @note		なし
 */
uint8 CANMBQ_ClrSndQue(uint8 queId)
{
	uint8 ret = CANMBQ_OK;	

	if (queId >= CANMBQ_QUENUM) {
		ret = CANMBQ_INVALID;
	} else  {
		uint32 ch;

		for (ch = 0; ch < CANMBQ_CHMAX; ch++) {
			/*----------------------------------------------------------*/
			/* CH数分キャンセルを実施                                   */
			/*----------------------------------------------------------*/
			TxChannel *pTxChannel = txChannelArray[ch];
			TxChannel_ClrSndQue(pTxChannel, queId);
		}
	}
	
	return ret;
}

/**
 * @fn			void CANMBQ_SendcancelAll(CommonBuffer *pCommonBuffer)
 * @brief		全MBQ送信要求キャンセル
 * @details		全MBQの送信要求をキャンセルする
 * @param[in]	pCommonBuffer	キャンセル対象となるCommonBufferへのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_SendcancelAll(CommonBuffer *pCommonBuffer)
{
	uint32 ch;
	
	for (ch = 0; ch < CANMBQ_CHMAX; ch++)
	{
		TxChannel *pTxChannel = txChannelArray[ch];
		uint8 que = MBQ_QueIdTbl[pCommonBuffer->frameClass][ch];
		SendQue *pSendQue = &(pTxChannel->pSendQue[que]);
		SendQueFields *pSendQueFields = pSendQue->pFields;
		const uint16 size = pSendQue->size;	
		uint16 FailCh;

		/* フェール発生チャンネル情報を取得 */
		FailCh = L3R_Fail_GetFailChBit((uint8)ch);

		/* フェール復帰中のチャンネルでない場合 */
		if (FailCh == L3R_LOG_BIT_NULL) {
			CANMBQ_pushDI_AREA9();
	
			if(pSendQueFields->count > 0U) {
				uint16 readPoint = pSendQueFields->readPoint;

				if (pSendQue->ppCommonBuffer[readPoint] == pCommonBuffer){
					pSendQue->ppCommonBuffer[readPoint] = NULL_PTR;

					readPoint++;
					if (readPoint < size) {
						pSendQueFields->readPoint = readPoint;
					} else {
						pSendQueFields->readPoint = 0;
					}
					pSendQueFields->count--;
				}
			}
		
			CANMBQ_popEI_AREA9();
		}
	}
	
	return;
}

/**
 * @fn			uint8 CANMBQ_SendReq_Tx(uint8 ch, CommonBuffer* pCommonBuffer)
 * @brief		送信MBOXへ要求する
 * @details		送信MBOXへ要求する
 * @param[in]	ch	チャンネル
 * @param[in]	pCommonBuffer	バッファのポインタ
 * @return		CANMBQ_OK
 * @attention	なし
 * @note		なし
 */
void CANMBQ_SendReq_Tx(uint8 ch, CommonBuffer* pCommonBuffer)
{
	uint8 bandLimitCheck;
	
	bandLimitCheck = BandLimit_JudgeLimit();
	
	if (L3R_E_OK == bandLimitCheck) {
		TxChannel* pTxChannel = txChannelArray[ch];
		TxChannel_SendReq_Tx(pTxChannel, pCommonBuffer);
	}
	
	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
