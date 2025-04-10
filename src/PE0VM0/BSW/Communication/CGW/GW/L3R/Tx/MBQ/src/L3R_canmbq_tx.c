/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_tx.c											*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			Driver transmission process								*/
/*【備考】																	*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2018.05.22	@author	A.Yasui(FSI)
 *		コーディング規約対応(オブジェクト不変の修正2)
 *	@version	2.0.0	2018.05.23	@author	T.Yamamura(FSI)
 *		可変化対応 L3R_GwBuffer_cfg.hのインクルード追加
 *	@version	2.0.1	2018.05.30	@author	K.Ito(FSI)
 *		帯域制限削除対応
 *	@version	2.0.2	2018.06.19	@author	K.Ito(FSI)
 *		帯域制限追加対応
 *	@version	2.0.3	2018.07.25	@author	T.Yamamura(FSI)
 *		処理負荷改善対応 TxChannel_WriteSendQue内の割込み禁止処理削除
 *	@version	2.0.4	2018.09.19	@author	Y.Katayama(FSI)
 *		送信ロック・バスオフクリア時の割禁区間変更
 *	@version	2.0.5	2018.10.25	@author	T.Yamamura(FSI)
 *		コードレベルアップ対応(オブジェクト不変)
 *	@version	2.0.6	2018.10.26	@author	T.Yamamura(FSI)
 *		割込み禁止コメント修正
 *	@version	3.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
 *	@version	3.0.1	2019.10.09	@author	T.Yamamura(FSI)
 *		[570B-Phase10][IntegNo.1124328]処理負荷削減対応 CommonBuffer_SendFinNotify()削除
*/
#include "CS_Can.h"
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_BandLimit.h"
#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_common.h"
#include "L3R_canmbq_st.h"
#include "L3R_GwBuffer_cfg.h"

#include "L3R_canmbq_tx.h"

#include "L3R_Fail.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define CANMBQ_HIT						(0U)
#define CANMBQ_NOHIT_CONT				(1U)
#define CANMBQ_NOHIT_BREK				(2U)

#define CANMBQ_SENDREQ_BIT_REQOK		(0x00U)
#define CANMBQ_SENDREQ_BIT_REQNG		(0x01U)
#define CANMBQ_SENDREQ_BIT_WAIT			(0x02U)
#define CANMBQ_SENDREQ_BIT_OVERDELAY	(0x04U)
#define CANMBQ_SENDREQ_BIT_TXLIMIT		(0x08U)

/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
static uint8 TxChannel_GetCanData(const uint8 logicCh, SendQue* const pSendQue, CanMsgType* const pCanMsg);
static uint8 TxChannel_SendReq(TxChannel* const self, CanMsgType* const pCanMsg, SendQue* const pSendQue);
static void TxChannel_ClrBuff(TxChannel *self, SendQue *pSendQue, SendQueFields *pSendQueFields);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/
/* #define GW_L3R_START_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */
/* static uint8 CANMBQ_txCount[CANMBQ_CHMAX] = {0}; */
/* #define GW_L3R_STOP_SEC_VAR */
/* #include "GW_L3R_Memmap.h" */

#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static uint8 CANMBQ_txCount[CANMBQ_CHMAX];
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void TxChannel_ClrBuff(TxChannel *self, SendQue *pSendQue, SendQueFields *pSendQueFields)
 * @brief		MBQバッファ情報クリア
 * @details		特定CHの特定キューのバッファ情報をクリアする
 * @param[in]	self			自身へのポインタ
 * @param[in]	pSendQue		特定キューへのポインタ
 * @param[in]	pSendQueFields	特定キュー制御情報へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static void TxChannel_ClrBuff(TxChannel *self, SendQue *pSendQue, SendQueFields *pSendQueFields)
{
	uint32 readPoint;
	uint32 count;
	uint16 size;
	uint8 logicCh;
	CommonBuffer **pCommonBufferArray;
	CommonBuffer *pCommonBuffer;
	
	L3R_DI();
	
	size = pSendQue->size;
	logicCh = self->logicCh;
	pCommonBufferArray = pSendQue->ppCommonBuffer;
	
	readPoint = pSendQueFields->readPoint;
	count = pSendQueFields->count;
	
	L3R_EI();
	
	while (count > 0U) {
		L3R_DI();
		
		pCommonBuffer = pCommonBufferArray[readPoint];
		CommonBuffer_ClrSndStatusCh(pCommonBuffer, logicCh);
		
		readPoint++;
		if (readPoint >= size) {
			readPoint = 0;
		}
		count--;
		
		L3R_EI();
	}

	return;
}

/**
 * @fn			void TxChannel_ClrSndQueAll(TxChannel *self)
 * @brief		特定CHの全キュークリア
 * @details		特定CHの全キューをクリアする
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_ClrSndQueAll(TxChannel *self)
{
	uint32 queIndex;
	SendQue *pSendQue = self->pSendQue;
	SendQueFields *pSendQueFields;
	
	CANMBQ_pushDI_AREA1();
	
	for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
		pSendQueFields = pSendQue->pFields;
		
		pSendQueFields->readPoint = 0;
		pSendQueFields->writePoint = 0;
		pSendQueFields->count = 0;
		pSendQueFields->sendingFlg = CANMBQ_CLR;
		pSendQueFields->lockTimer = 0;
		
		pSendQue++;
	}
	
	CANMBQ_popEI_AREA1();

	return;
}

/**
 * @fn			void TxChannel_ClrSndQueAllWithBuffer(TxChannel *self)
 * @brief		特定CHの全キュークリア(バッファ情報を含む)
 * @details		特定CHの全キュー(バッファ情報を含む)をクリアする
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_ClrSndQueAllWithBuffer(TxChannel *self)
{
	uint32 queIndex;
	SendQue *pSendQue = self->pSendQue;
	SendQueFields *pSendQueFields;
	
	for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
		pSendQueFields = pSendQue->pFields;

		TxChannel_ClrBuff(self, pSendQue, pSendQueFields);
		
		L3R_DI();
		
		pSendQueFields->readPoint = 0;
		pSendQueFields->writePoint = 0;
		pSendQueFields->count = 0;
		pSendQueFields->sendingFlg = CANMBQ_CLR;
		pSendQueFields->lockTimer = 0;
		
		L3R_EI();
		
		pSendQue++;
	}
	
	return;
}

/**
 * @fn			void TxChannel_ClrSndQue(TxChannel *self, uint8 queId)
 * @brief		特定CHの特定キュークリア
 * @details		特定CHの特定キューをクリアする
 * @param[in]	self	自身へのポインタ
 * @param[in]	queId	キュー番号
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_ClrSndQue(TxChannel *self, uint8 queId)
{
	SendQueFields *pSendQueFields = self->pSendQue[queId].pFields;
	
	CANMBQ_pushDI_AREA2();

	pSendQueFields->readPoint = 0;
	pSendQueFields->writePoint = 0;
	pSendQueFields->count = 0;
	
	CANMBQ_popEI_AREA2();
	
	return;
}

/**
 * @fn			uint8 TxChannel_WriteSendQue(TxChannel *self, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell)
 * @brief		MBQへの書き込み
 * @details		MBQへの書き込みを行う
 * @param[in]	self			自身へのポインタ
 * @param[in]	pCommonBuffer	書き込み対象となるCommonBufferへのポインタ
 * @param[out]	ppBufferToDell	削除対象CommonBufferの格納先
 * @return		書き込み結果
 * @retval		CANMBQ_INVALID	書き込み対象なし(書き込み失敗)
 * @retval		CANMBQ_OK		書き込み成功
 * @retval		CANMBQ_FULL_OK	MBQバッファフル(書き込み成功)
 * @attention	割り込み禁止で呼び出される
 * @note		なし
 */
uint8 TxChannel_WriteSendQue(TxChannel *self, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell)
{
	uint8 ret;
	
	if (pCommonBuffer == NULL_PTR) {
		ret = CANMBQ_INVALID;
	} else {
		uint8 queId = MBQ_QueIdTbl[pCommonBuffer->frameClass][self->logicCh];
		SendQue *pSendQue = &(self->pSendQue[queId]);
		SendQueFields *pSendQueFields = pSendQue->pFields;
		const uint16 size = pSendQue->size;
		uint16 writePoint;

		/* ドライバ状態はチェックせずに空きがあればキューイングする */
		
		if (pSendQueFields->count < size) {
			ret = CANMBQ_OK;
		} else {
			uint16 readPoint = pSendQueFields->readPoint;

			/* MBQバッファフル 最古フレーム破棄  */
			if (ppBufferToDell != NULL_PTR) {
				*ppBufferToDell = pSendQue->ppCommonBuffer[readPoint];
			}

			readPoint++;
			if (readPoint < size) {
				pSendQueFields->readPoint = readPoint;
			} else {
				pSendQueFields->readPoint = 0;
			}
			pSendQueFields->count--;
			
			ret = CANMBQ_FULL_OK;
		}
		/* MBQバッファ書き込み処理 */
		writePoint = pSendQueFields->writePoint;
		pSendQue->ppCommonBuffer[writePoint] = pCommonBuffer;

		writePoint++;
		if (writePoint < size) {
			pSendQueFields->writePoint = writePoint;
		} else {
			pSendQueFields->writePoint = 0;
		}
		pSendQueFields->count++;

	}

	return ret;
}

/**
 * @fn			uint8 TxChannel_GetCanData(const uint8 logicCh, SendQue* const pSendQue, CanMsgType* const pCanMsg)
 * @brief		CANデータ取得
 * @details		CANデータを取得する
 * @param[in]		logicCh		論理CH番号
 * @param[in,out]	pSendQue	特定キューへのポインタ
 * @param[out]		pCanMsg		受信データ
 * @return		CANデータ取得結果
 * @retval		CANMBQ_HIT			取得成功
 * @retval		CANMBQ_NOHIT_BREK	取得失敗(要求待ち)
 * @retval		CANMBQ_NOHIT_CONT	取得失敗(過剰遅延)
 * @attention	なし
 * @note		なし
 */
static uint8 TxChannel_GetCanData(const uint8 logicCh, SendQue* const pSendQue, CanMsgType* const pCanMsg)
{
	uint8 searchFlg = CANMBQ_NOHIT_BREK;
	uint8 reqResult = L3R_REQ_WAIT;
	SendQueFields* const pSendQueFields = pSendQue->pFields;
	uint16 readPoint = pSendQueFields->readPoint;
	CommonBuffer* const pCommonBuffer = pSendQue->ppCommonBuffer[readPoint];

	if (pCommonBuffer != NULL_PTR) {
		reqResult = CommonBuffer_GetCanData(pCommonBuffer, logicCh,
			&pCanMsg->u1Length, &pCanMsg->u4Id, &pCanMsg->ptData);
		
		if (reqResult == L3R_REQ_OK) {
			/* CANデータの取得に成功 */
			searchFlg = CANMBQ_HIT;
		} else if (reqResult == L3R_REQ_WAIT) {
			/* 取得失敗(要求待ち) */
			searchFlg = CANMBQ_NOHIT_BREK;
		} else {
			uint16 FailCh;
			/* フェール発生チャンネル情報を取得 */
			FailCh = L3R_Fail_GetFailChBit(logicCh);
			
			/* フェール復帰中のチャンネルでない場合 */
			if (FailCh == L3R_LOG_BIT_NULL) {
				/* 取得失敗(過剰遅延)もしくは未定義値なら、フレームを破棄する。*/
				searchFlg = CANMBQ_NOHIT_CONT;
				
				pSendQue->ppCommonBuffer[readPoint] = NULL_PTR;
				
				readPoint++;
				if (readPoint < pSendQue->size) {
					pSendQueFields->readPoint = readPoint;
				} else {
					pSendQueFields->readPoint = 0U;
				}
				pSendQueFields->count--;
			}
		}
	}
	
	return searchFlg;
}

/**
 * @fn			uint8 TxChannel_SendReq(TxChannel* const self, CanMsgType* const pCanMsg, SendQue* const pSendQue)
 * @brief		CANデータ送信要求
 * @details		CANデータ送信要求を行う
 * @param[in]		self		自身へのポインタ
 * @param[in]		pCanMsg		受信データ
 * @param[in,out]	pSendQue	特定キューへのポインタ
 * @return		送信要求結果
 * @retval		CAN_PROC_OK		送信OK
 * @retval		CAN_PROC_NG		送信待ち
 * @retval		CAN_PROC_BUSY	送信NG
 * @attention	なし
 * @note		なし
 */
static uint8 TxChannel_SendReq(TxChannel* const self, CanMsgType* const pCanMsg, SendQue* const pSendQue)
{
	SendQueFields* const pSendQueFields = pSendQue->pFields;

	/* CANドライバに送信要求(コントローラ番号、CANIP番号は静的に決まるためコンフィグ値を参照) */
	const uint8 txResult = self->CanIpTxReq(self->controllerId, *(pSendQue->pMboxId), pCanMsg);

	if (txResult == CAN_PROC_OK) {
		const uint16 size = pSendQue->size;
		uint16 readPoint = pSendQueFields->readPoint;
		CommonBuffer* const pCommonBuffer = pSendQue->ppCommonBuffer[readPoint];

		/* GWドメインにCAN Driverへの送信成功を通知する */
		CommonBuffer_ClrSndStatusCh(pCommonBuffer, self->logicCh);

		/* バス送信完了は上位に通知しないので、送信データの保持は実施しない */

		pSendQue->ppCommonBuffer[readPoint] = NULL_PTR;

		readPoint++;
		if (readPoint < size) {
			pSendQueFields->readPoint = readPoint;
		} else {
			pSendQueFields->readPoint = 0U;
		}
		pSendQueFields->count--;

		/* 送信フラグをセット */
		pSendQueFields->sendingFlg = CANMBQ_SET;
		/* 送信ロックタイマを起動 */
		pSendQueFields->lockTimer = CANMBQ_TLOCK;

	} else if (txResult == CAN_PROC_NG) {
		;
		/* 指定コントローラの状態がSTARTEDでない場合はH/W通信を停止しており */
		/* 送信ロックタイマを起動しない。                                   */
	} else if (txResult == CAN_PROC_BUSY) {

		/* 送信中フラグを用いて送信完了後に送信要求すること、かつ           */
		/* H/Wレベルの送信キャンセルは未使用のため、異常時にしか発生しない。*/
		/* このためフェールセーフとして、送信ロックタイマを起動する(        */
		/* 既に起動していればそのままカウント継続)。                        */
		if (pSendQueFields->lockTimer == 0U) {
			pSendQueFields->lockTimer = CANMBQ_TLOCK;
		}
	} else {
		;
		/* Can_TxReqの戻り値が変更された場合は、戻り値に対する */
		/* 処理内容が妥当かどうかの見直しが必要。              */
	}

	return txResult;
}

/**
 * @fn			uint8 TxChannel_SendReqCan(TxChannel* const self, SendQue* const pSendQue)
 * @brief		MBQからの送信要求(物理CAN用)
 * @details		MBQからの送信要求を行う
 * @param[in]		self		自身へのポインタ
 * @param[in,out]	pSendQue	特定キューへのポインタ
 * @return		送信要求結果
 * @retval		CANMBQ_SENDREQ_BIT_REQOK	送信要求異常なし(固定値)
 * @attention	なし
 * @note		なし
 */
uint8 TxChannel_SendReqCan(TxChannel* const self, SendQue* const pSendQue)
{
	SendQueFields* const pSendQueFields = pSendQue->pFields;
	uint16 retryCounter = 0U;
	
	/* CANデータ取得結果が成功または取得失敗(要求待ち)の場合はループを終了 */
	/* 取得失敗(過剰遅延)の場合はリトライ数上限までCANデータ取得を繰り返す */
	while ((pSendQueFields->count > 0U) && (retryCounter <= pSendQue->retryCount)) {
		CanMsgType canMsg;
		/* CANデータ取得 */
		const uint8 result = TxChannel_GetCanData(self->logicCh, pSendQue, &canMsg);
		if (result == CANMBQ_HIT) {
			/* 取得成功の場合は送信要求 */
			(void)TxChannel_SendReq(self, &canMsg, pSendQue);
			break;
		} else if (result == CANMBQ_NOHIT_BREK) {
			/* 取得失敗(要求待ち)の場合はループを抜ける */
			break;
		} else {
			/* 取得失敗(過剰遅延)もしくは未定義値の場合はリトライカウンタを加算 */
			retryCounter++;
		}
	}
	/*  戻り値(送信要求結果)を送信要求異常なしに設定 */
	return CANMBQ_SENDREQ_BIT_REQOK;
}


/**
 * @fn			uint8 TxChannel_SendReqVCan(TxChannel* const self, SendQue* const pSendQue)
 * @brief		MBQからの送信要求(仮想CAN用)
 * @details		MBQからの送信要求を連続で行う
 * @param[in]		self		自身へのポインタ
 * @param[in,out]	pSendQue	特定キューへのポインタ
 * @return		送信要求結果
 * @retval		CANMBQ_SENDREQ_BIT_REQOK		送信要求異常なし
 * @retval		CANMBQ_SENDREQ_BIT_REQNG		送信要求失敗
 * @retval		CANMBQ_SENDREQ_BIT_WAIT			データ取得失敗(送信要求待ち)
 * @retval		CANMBQ_SENDREQ_BIT_OVERDELAY	データ取得失敗(過剰遅延)
 * @retval		CANMBQ_SENDREQ_BIT_TXLIMIT		送信回数超過/送信データ無
 * @attention	なし
 * @note		なし
 */
uint8 TxChannel_SendReqVCan(TxChannel* const self, SendQue* const pSendQue)
{
	SendQueFields* const pSendQueFields = pSendQue->pFields;
	uint8 ret;
	
	/*  戻り値(送信要求結果)を送信要求異常なしに設定 */
	ret = CANMBQ_SENDREQ_BIT_REQOK;
	/* 「送信キュー格納フレーム数が存在する」かつ「送信回数制限カウンタが仮想CAN 送信要求制限回数未満」の間は連続送信を行う */
	if ((pSendQueFields->count > 0U) && (CANMBQ_txCount[self->logicCh] < CANMBQ_VCAN_TX_LIMIT)) {
		CanMsgType canMsg;
		/* CANデータ取得 */
		const uint8 getResult = TxChannel_GetCanData(self->logicCh, pSendQue, &canMsg);
		if (getResult == CANMBQ_HIT) {
			/* 取得成功の場合は送信要求 */
			const uint8 reqResult = TxChannel_SendReq(self, &canMsg, pSendQue);
			/* 仮想CANでは送信完了を実施しないため送信フラグはクリアする */
			pSendQueFields->sendingFlg = CANMBQ_CLR;
			if (reqResult != CAN_PROC_OK) {
				/* 戻り値(送信要求結果)を送信要求失敗に設定 */
				ret = CANMBQ_SENDREQ_BIT_REQNG;
			} else {
				/* CANデータ送信関数の結果が成功の場合 */
				/* 仮想CANでは送信完了を実施しないため送信結果OKの場合は送信ロックタイマをクリア */
				pSendQueFields->lockTimer  = 0U;
				/* 送信回数制限カウンタを加算 */
				CANMBQ_txCount[self->logicCh]++;
			}
		} else if (getResult == CANMBQ_NOHIT_BREK) {
			/* 戻り値(送信要求結果)をデータ取得失敗(送信要求待ち)に設定 */
			ret = CANMBQ_SENDREQ_BIT_WAIT;
		} else {
			/* 取得失敗(過剰遅延)もしくは未定義値の場合は送信回数制限カウンタを加算 */
			CANMBQ_txCount[self->logicCh]++;
			/* 戻り値(送信要求結果)をデータ取得失敗(過剰遅延)に設定 */
			ret = CANMBQ_SENDREQ_BIT_OVERDELAY;
		}
	} else {
		/* 「送信キュー格納フレーム数が存在しない」もしくは「送信回数制限カウンタが仮想CAN 送信要求制限回数以上」の場合 */
		/* 戻り値(送信要求結果)を送信回数超過/送信データ無に設定 */
		ret = CANMBQ_SENDREQ_BIT_TXLIMIT;
	}
	return ret;
}

/**
 * @fn			void TxChannel_ClrTxCnt(void)
 * @brief		送信回数制限クリア
 * @details		送信回数制限のクリアを行う
 * @param[in]	なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_ClrTxCnt(void)
{
	uint8 clrCh;
	
	for (clrCh = 0; clrCh < CANMBQ_CHMAX; clrCh++){
		CANMBQ_txCount[clrCh] = 0;
	}
	
	return;
}

/**
 * @fn			void TxChannel_TxFin(TxChannel *self, uint8 queId)
 * @brief		送信完了通知
 * @details		送信完了通知時処理を行う
 * @param[in]	self	自身へのポインタ
 * @param[in]	queId	キュー番号
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_TxFin(TxChannel *self, uint8 queId)
{	
	uint8 bandLimitCheck = BandLimit_JudgeLimit();
	
	SendQue *pSendQue = &(self->pSendQue[queId]);
	SendQueFields *pSendQueFields = pSendQue->pFields;
	
	pSendQueFields->sendingFlg = CANMBQ_CLR;
	pSendQueFields->lockTimer = 0;
	
	if (L3R_E_OK == bandLimitCheck) {
		if (pSendQueFields->count != 0U) {
			/* 物理CANチャンネル時は現状固定値応答の為戻り値の判断は不要 */
			/* VCANチャンネル時は送信完了ではコールされない為戻り値の判断は不要 */
			(void)self->SendReq(self, pSendQue);
		}
		
		/* 送信完了フックは未使用 */
		/* CANMBQ_SENDFIN_HOOK_0((uint8)CANMBQ_CH, que); */
	}
	
	return;
}

/**
 * @fn			void TxChannel_Omed_SndLock(TxChannel *self)
 * @brief		送信ロック検出判定
 * @details		送信ロック検出の判定を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_Omed_SndLock(TxChannel *self)
{
	uint32 queIndex;
	uint8 chMode;
	uint8 lockTimer;
	SendQue *pSendQue = self->pSendQue;
	SendQueFields *pSendQueFields;
	
	chMode = CANMBQ_GetMode(self->logicCh);
	/* 通信可能状態の場合は中継機能の送信ロック発生を確認する */
	if (chMode == CANMBQ_COMM) {
		uint8 lockFlg = CANMBQ_CLR;
		/* 指定チャンネルの優先度毎のMBQの送信ロックをチェックする */
		for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
			uint16 writePoint;
			const uint16 size = pSendQue->size;
			pSendQueFields = pSendQue->pFields;

			CANMBQ_pushDI_AREA4();

			/* 送信ロックタイマーを減算し0に到達したら送信ロック発生フラグを設定 */
			lockTimer = pSendQueFields->lockTimer;
			if (lockTimer != 0U) {
				lockTimer--;
				pSendQueFields->lockTimer = lockTimer;
				if (lockTimer == 0U) {
					lockFlg = CANMBQ_SET;
				}
			/* MBOX送信中で送信ロックタイマーが0の場合タイマーに初期値設定 */
			} else {
				if (pSendQueFields->sendingFlg != CANMBQ_CLR) {
					pSendQueFields->lockTimer = CANMBQ_TLOCK;
				}
			}
			
			CANMBQ_popEI_AREA4();
			
			CANMBQ_pushDI_AREA5();
			
			/* ライトポインタ異常をチェックし異常時は送信ロック発生とする */
			writePoint = pSendQueFields->readPoint;
			writePoint = writePoint + pSendQueFields->count;
			if (writePoint < size) {
				if(pSendQueFields->writePoint != writePoint){
					lockFlg = CANMBQ_SET;
				}
			} else {
				if(pSendQueFields->writePoint != (uint16)(writePoint - size)){
					lockFlg = CANMBQ_SET;
				}
			}

			CANMBQ_popEI_AREA5();

			pSendQue++;
		}
		/* 中継機能の送信ロック発生時はCSに送信ロック発生を通知し復帰処理を行う */
		if (lockFlg == CANMBQ_SET) {
			CANMBQ_SndLock(self->logicCh);
		}
	/* 通信停止状態時はMBOXの送信中状態をクリアしロックタイマーを0クリアする */
	} else {
		for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
			pSendQueFields = pSendQue->pFields;

			CANMBQ_pushDI_AREA7();

			pSendQueFields->sendingFlg = CANMBQ_CLR;
			pSendQueFields->lockTimer = 0;

			CANMBQ_popEI_AREA7();

			pSendQue++;
		}
	}
	return;
}

/**
 * @fn			void TxChannel_DrvTask_Tx_Can(TxChannel *self)
* @brief		1msタスク処理(物理CAN用)
 * @details		MBQの1msタスク処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_DrvTask_Tx_Can(TxChannel *self)
{
	uint32 queIndex;
	SendQue *pSendQue = self->pSendQue;
	SendQueFields *pSendQueFields;
	
	for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
		pSendQueFields = pSendQue->pFields;

		CANMBQ_pushDI_AREA6();

		if ((pSendQueFields->count != 0U)
			&& (pSendQueFields->sendingFlg != CANMBQ_SET)) {
			/* 物理CANチャンネル時は現状固定値応答の為戻り値の判断は不要 */
			(void)self->SendReq(self, pSendQue);
		}

		CANMBQ_popEI_AREA6();
		
		pSendQue++;
	}

	return;
}

/**
 * @fn			void TxChannel_DrvTask_Tx_VCan(TxChannel *self)
* @brief		1msタスク処理(仮想CAN用)
 * @details		MBQの1msタスク処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void TxChannel_DrvTask_Tx_VCan(TxChannel *self)
{
	uint32 queIndex;
	SendQue *pSendQue = self->pSendQue;
	SendQueFields *pSendQueFields;
	uint8 txCount;
	uint8 txLimitCount;
	uint8 ret;
	
	/* チャンネルのMBQ分繰り返す */
	for (queIndex = 0; queIndex < CANMBQ_QUENUM; queIndex++) {
		pSendQueFields = pSendQue->pFields;
		/* 送信キューにフレームが存在する場合 */
		if (pSendQueFields->count != 0U) {
			/* 送信制限カウンタを元に残りの送信回数を算出する */
			txLimitCount = CANMBQ_VCAN_TX_LIMIT - CANMBQ_txCount[self->logicCh];
			/* 残りの送信回数分ループする */
			for (txCount = 0; txCount < txLimitCount; txCount++) {
				/* 1フレーム毎に割込禁止にして送信要求を実施する */
				CANMBQ_pushDI_AREA6();
				ret = self->SendReq(self, pSendQue);
				CANMBQ_popEI_AREA6();
				
				/* 戻り値(送信要求結果)が送信失敗、データ取得失敗(送信要求待ち)、送信回数超過/送信データ無のいずれか場合 */
				if ((ret & (CANMBQ_SENDREQ_BIT_REQNG | CANMBQ_SENDREQ_BIT_WAIT | CANMBQ_SENDREQ_BIT_TXLIMIT)) != 0U) {
					break;
				}
			}
		}
		/* 次のMBQにポインタを進める */
		pSendQue++;
	}

	return;
}

/**
 * @fn			uint8 TxChannel_SendReq_Tx(TxChannel *self, CommonBuffer* pCommonBuffer)
 * @brief		送信MBOXへ要求する
 * @details		送信MBOXへ要求する
 * @param[in]	self			自身へのポインタ
 * @param[in]	pCommonBuffer	バッファのポインタ
 * @return		CANMBQ_OK
 * @attention	なし
 * @note		なし
 */
void TxChannel_SendReq_Tx(TxChannel *self, CommonBuffer* pCommonBuffer)
{
	uint8 queId = MBQ_QueIdTbl[pCommonBuffer->frameClass][self->logicCh];
	SendQue* pSendQue = &(self->pSendQue[queId]);
	SendQueFields* pSendQueFields = pSendQue->pFields;
	
	if (pSendQueFields->sendingFlg != CANMBQ_SET) {
		/* 物理CANチャンネル時は現状固定値応答の為戻り値の判断は不要 */
		/* VCANチャンネル時は受信処理時は連続送信しない為判断は不要(1ms周期処理でも送信を実施) */
		(void)self->SendReq(self, pSendQue);
	} else {
		;
	}
	
	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
