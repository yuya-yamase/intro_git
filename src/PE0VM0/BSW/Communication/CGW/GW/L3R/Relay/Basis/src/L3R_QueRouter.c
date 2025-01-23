/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_QueRouter.c
 * @brief	受信FIFO制御
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・送信要求処理の処理共通化（CAN300含む）
 * 													・GW_RTR_config.hのインクルード追加
 * 													・L3R_CAN300Adapter.hのインクルード削除
 *          v2.01	2018/05/21	A.Yasui(FSI)		JIRA GW19C-2480対応
 *					CAN300 100フレームを超えた場合、CAN-ETH中継が全くされない
 * 			v2.02	2018.05.30	K.Ito(FSI)			帯域制限削除対応
 * 			v2.03	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・Bit位置取得方法を変更
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 * 			v3.02   2018/10/26	T.Yamamura(FSI)		割込み禁止コメント修正
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v5.00	2018/12/25	T.Yamamura(FSI)		新アーキテクチャSBR仕様適合対応
 * 													制御データ中継モード対応
 *			v6.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_Common.h"
#include "L3R_CommonBuffer.h"
#include "L3R_config.h"
#include "L3R_Fail.h"
#include "L3R_LIB.h"
#include "L3R_Timer.h"

#include "L3R_QueRouter.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define QUE_DISPATCH_LMT	(25U)	/* 中継先ディスパッチ制限数 */

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
 * @fn			void QueRouter_Init(Router *self)
 * @brief		受信FIFO初期化処理
 * @details		受信FIFO制御領域とポインタの初期化を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void QueRouter_Init(Router *self)
{
	RouterFields *pQueRouterFields = self->pFields;

	Router_Init(self);

	pQueRouterFields->writePointer	= 0;
	pQueRouterFields->enquePointer	= 0;
	pQueRouterFields->readPointer	= 0;
	pQueRouterFields->enqueCount	= 0;
	pQueRouterFields->readCount		= 0;

	return;
}

/*************************************************************************//**
 * @fn			CommonBuffer *QueRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId uint8 fd)
 * @brief		中継処理（キュールータタイプ）
 * @details		受信データを共有バッファにコピーする
 * @param[in]	self	自身へのポインタ
 * @param[in]	canId	CAN ID
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	gwId	GwId
 * @param[in]	searchId	探索位置
 * @return		データを保存するCommonBufferへのポインタ
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
CommonBuffer *QueRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId, uint8 fd)
{
	RouterFields *pQueRouterFields = self->pFields;
	CommonBuffer *pCommonBuffer = self->pBuffer[pQueRouterFields->writePointer];
	CommonBufferFields *pBufferFields = pCommonBuffer->pFields;
	const uint16 size = self->size;
	
	/*----------------------------------------------------------------------*/
	/* データ上書き時の処理													*/
	/*----------------------------------------------------------------------*/
	self->OverWrite(self, &pCommonBuffer);

	L3R_DI();
	
	/*----------------------------------------------------------------------*/
	/* Writeポインタ更新処理                                                */
	/*----------------------------------------------------------------------*/
	pQueRouterFields->writePointer++;
	if (pQueRouterFields->writePointer >= size) {
		pQueRouterFields->writePointer = 0;
	}
	
	/*----------------------------------------------------------------------*/
	/* Readポインタ更新処理                                                 */
	/*----------------------------------------------------------------------*/
	pQueRouterFields->readCount++;
	if (pQueRouterFields->readCount > size) {
		pQueRouterFields->readPointer = pQueRouterFields->writePointer;
		pQueRouterFields->readCount = size;
	}

	/*----------------------------------------------------------------------*/
	/* Enqueポインタ更新処理                                                */
	/*----------------------------------------------------------------------*/
	pQueRouterFields->enqueCount++;
	if (pQueRouterFields->enqueCount > size) {
		pQueRouterFields->enquePointer = pQueRouterFields->writePointer;
		pQueRouterFields->enqueCount = size;
	}
	
	pBufferFields->sndPrtclBit = L3R_LOG_BIT_NULL;
	pBufferFields->sndPrtclReqBit = L3R_LOG_BIT_NULL;
	pBufferFields->fd	  = fd;
	pCommonBuffer = QueRouter_RelayDataByBuffer(self, pCommonBuffer, canId, dlc, Data, gwId, searchId);
	/* 戻り値（データを保存するCommonBufferへのポインタ）を処理する必要がない */
	(void)QueRouter_SendData(self, pCommonBuffer);

	L3R_EI();

	return (pCommonBuffer);
}

/*************************************************************************//**
 * @fn			CommonBuffer *QueRouter_SendData(Router *self, CommonBuffer *pCommonBuffer)
 * @brief		データ送信処理
 * @details		共有バッファのデータを送信する
 * @param[in]	self	自身へのポインタ
 * @param[in]	pCommonBuffer	データを保存するCommonBufferへのポインタ
 * @return		データを保存するCommonBufferへのポインタ
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
CommonBuffer *QueRouter_SendData(Router *self, CommonBuffer *pCommonBuffer)
{
	unsigned int enqueCnt;				/* ループ件数					*/
	uint16 size = self->size;
	RouterFields *pQueRouterFields = self->pFields;

	/*----------------------------------------------------------------------*/
	/* 中継先ディスパッチ処理                                               */
	/*----------------------------------------------------------------------*/
	enqueCnt = pQueRouterFields->enqueCount;

	if (enqueCnt > 0U) {
		uint16 enquePtr;				/* Enqueポインタ				*/
		uint8 Req;					/* Gateオープン要求済みのフラグ	*/
		unsigned int counter;			/* ループ件数					*/
		CommonBuffer *pCommonBuffer_Que;
		CommonBuffer *const *pCommonBufferArray = self->pBuffer;

		/*------------------------------------------------------------------*/
		/* 送信登録要求の残件がある場合のみ実施                             */
		/*------------------------------------------------------------------*/
		Req      = L3R_FALSE;

			/*--------------------------------------------------------------*/
			/* 帯域制限                                                     */
			/*--------------------------------------------------------------*/

		for (counter = 0; counter < enqueCnt; counter++) {
			/*--------------------------------------------------------------*/
			/* 上限まで繰り返し                                             */
			/*--------------------------------------------------------------*/

			/* 割り込み禁止設定区間短縮の為、Eポインタ取得・更新、*/
			/* Eカウンタ更新のみ処理する						  */
			enquePtr = pQueRouterFields->enquePointer;

			/*----------------------------------------------------------*/
			/* QP更新処理                                               */
			/*----------------------------------------------------------*/
			pQueRouterFields->enquePointer++;
			if (pQueRouterFields->enquePointer >= size) {
				pQueRouterFields->enquePointer = 0;
			}

			pQueRouterFields->enqueCount--;


			pCommonBuffer_Que = pCommonBufferArray[enquePtr];

			/*----------------------------------------------------------*/
			/* 中継先ディスパッチ                                       */
			/*----------------------------------------------------------*/
			Req = self->QuickWakeup(pCommonBuffer_Que, Req);
			QueRouter_SendReq(pCommonBuffer_Que);
		}
	}

	return (pCommonBuffer);
}

/*************************************************************************//**
 * @fn			CommonBuffer *QueRouter_RelayDataByBuffer(Router *self, CommonBuffer *pCommonBuffer, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId)
 * @brief		中継処理（データセット）
 * @details		中継処理（データセット）を行う
 * @param[in]	self			自身へのポインタ
 * @param[in]	pCommonBuffer	中継するデータを保存するCommonBuffer
 * @param[in]	canId			CAN ID
 * @param[in]	dlc				データ長
 * @param[in]	Data			データへのポインタ
 * @param[in]	gwId			GwId
 * @param[in]	searchId		探索位置
 * @return		データを保存するCommonBufferへのポインタ
 * @attention	割り込み禁止で呼び出される
 * @note		なし
 ****************************************************************************/
CommonBuffer *QueRouter_RelayDataByBuffer(Router *self, CommonBuffer *pCommonBuffer, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId)
{
	CommonBufferFields *pBufferFields = pCommonBuffer->pFields;
	
	/*----------------------------------------------------------------------*/
	/* 共有バッファへのデータコピー                                         */
	/*----------------------------------------------------------------------*/
	pBufferFields->rcvTime	= L3R_Timer_Frt();
	pBufferFields->canId	= canId;
	pBufferFields->length	= dlc;
	pBufferFields->searchId	= searchId;
	L3R_LIB_memcpy(pCommonBuffer->Data, Data, pCommonBuffer->maxDataSize);
	
	/*----------------------------------------------------------------------*/
	/* 送信要求の設定														*/
	/*----------------------------------------------------------------------*/
	pBufferFields->sndPrtclReqBit	|= self->GetSendProtocol(pCommonBuffer, gwId, 0U);
	
	return (pCommonBuffer);
}

/*************************************************************************//**
 * @fn			void QueRouter_SendReq(CommonBuffer *pCommonBuffer)
 * @brief		送信要求処理
 * @details		CH数分送信要求する
 * @param[in]	pCommonBuffer	送信対象へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void QueRouter_SendReq(CommonBuffer *pCommonBuffer)
{
	uint16 sndPrtclReqBit = pCommonBuffer->pFields->sndPrtclReqBit;
	
	if(sndPrtclReqBit != L3R_LOG_BIT_NULL){
		uint32 ch;							/* CH						*/

		for (ch = 0; ch < CHM_LOG_ALL_CH_NUM; ch++) {
			/*------------------------------------------------------*/
			/* CH数分送信要求を実施                                 */
			/*------------------------------------------------------*/
			if ((sndPrtclReqBit & (((uint16)L3R_ON) << ch)) != 0U) {
				L3R_DI();
				L3R_SendReqQueFuncTbl[ch]((uint8) ch, pCommonBuffer);
				L3R_EI();
			}
		}
		CommonBuffer_ClrSndReqAll(pCommonBuffer);
	}
	return;
}

/*************************************************************************//**
 * @fn			void QueRouter_DriverTask(Router *self)
 * @brief		1msタスク処理
 * @details		1msタスク処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void QueRouter_DriverTask(Router *self)
{
	unsigned int enqueCnt;				/* ループ件数					*/
	uint16 size = self->size;
	RouterFields *pQueRouterFields = self->pFields;

	/*----------------------------------------------------------------------*/
	/* 中継先ディスパッチ処理                                               */
	/*----------------------------------------------------------------------*/
	enqueCnt = pQueRouterFields->enqueCount;

	if (enqueCnt > 0U) {
		uint16 enquePtr;				/* Enqueポインタ				*/
		uint8 Req;					/* Gateオープン要求済みのフラグ	*/
		unsigned int counter;			/* ループ件数					*/
		CommonBuffer *pCommonBuffer;
		CommonBuffer *const *pCommonBufferArray = self->pBuffer;

		/*------------------------------------------------------------------*/
		/* 送信登録要求の残件がある場合のみ実施                             */
		/*------------------------------------------------------------------*/
		Req      = L3R_FALSE;

			/*--------------------------------------------------------------*/
			/* 帯域制限                                                     */
			/*--------------------------------------------------------------*/

		for (counter = 0; counter < enqueCnt; counter++) {
			/*--------------------------------------------------------------*/
			/* 上限まで繰り返し                                             */
			/*--------------------------------------------------------------*/
			L3R_DI();

			/* 割り込み禁止設定区間短縮の為、Eポインタ取得・更新、*/
			/* Eカウンタ更新のみ処理する						  */
			enquePtr = pQueRouterFields->enquePointer;

			/*----------------------------------------------------------*/
			/* QP更新処理                                               */
			/*----------------------------------------------------------*/
			pQueRouterFields->enquePointer++;
			if (pQueRouterFields->enquePointer >= size) {
				pQueRouterFields->enquePointer = 0;
			}

			pQueRouterFields->enqueCount--;

			L3R_EI();

			pCommonBuffer = pCommonBufferArray[enquePtr];

			/*----------------------------------------------------------*/
			/* 中継先ディスパッチ                                       */
			/*----------------------------------------------------------*/
			Req = self->QuickWakeup(pCommonBuffer, Req);
			QueRouter_SendReq(pCommonBuffer);
		}
	}

	return;
}

/*************************************************************************//**
 * @fn			void QueRouter_MainTask(Router *self)
 * @brief		5msタスク処理
 * @details		5msタスク処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void QueRouter_MainTask(Router *self)
{
	uint16 RdPtrVal;				/* Readポインタ差分計算結果		*/
	uint16 EqPtrVal;				/* Enqueポインタ差分計算結果	*/
	uint8 ChkPtr;					/* ポインタ整合チェック結果		*/
	uint8 Status;					/* 中継ステータス				*/
	uint16 size = self->size;
	RouterFields *pQueRouterFields = self->pFields;

	L3R_DI();
	/* 割り込み禁止設定区間短縮の為、割り込み禁止区間を分割し、*/
	/* ポインタ不整合チェックのみ処理する					   */

	/*----------------------------------------------------------------------*/
	/* ポインタの整合チェック                                               */
	/*----------------------------------------------------------------------*/
	RdPtrVal = pQueRouterFields->readPointer  + pQueRouterFields->readCount;
	EqPtrVal = pQueRouterFields->enquePointer + pQueRouterFields->enqueCount;

	if (RdPtrVal >= size) {
		/*------------------------------------------------------------------*/
		/* バッファサイズを超える場合は折り返す                             */
		/*------------------------------------------------------------------*/
		RdPtrVal = RdPtrVal - size;
	}

	if (EqPtrVal >= size) {
		/*------------------------------------------------------------------*/
		/* バッファサイズを超える場合は折り返す                             */
		/*------------------------------------------------------------------*/
		EqPtrVal = EqPtrVal - size;
	}

	if ((RdPtrVal != pQueRouterFields->writePointer)
	 || (EqPtrVal != pQueRouterFields->writePointer)) {
		/*------------------------------------------------------------------*/
		/* 差分とデータ件数の不一致により、受信バッファを初期化             */
		/*------------------------------------------------------------------*/
		ChkPtr = L3R_E_NOT_OK;
	} else {
		ChkPtr = L3R_E_OK;
	}

	L3R_EI();

	if (ChkPtr == L3R_E_OK) {
		uint16 Idx;					/* Readポインタ更新位置			*/
		uint32 counter;			/* Readポインタ更新カウンタ		*/
		uint32 countMax;			/* Readポインタ更新最大件数		*/
		CommonBuffer *const *pCommonBufferArray = self->pBuffer;

		/*----------------------------------------------------------------------*/
		/* Readポインタ調整処理                                                 */
		/*----------------------------------------------------------------------*/
		countMax = pQueRouterFields->readCount;
		Status = L3R_CLR;

		if (countMax > QUE_DISPATCH_LMT) {
			/*------------------------------------------------------------------*/
			/* 上限は中継先ディスパッチ制限件数まで                             */
			/*------------------------------------------------------------------*/
			countMax = QUE_DISPATCH_LMT;
		}

		for (counter = 0; counter < countMax; counter++) {
			/*------------------------------------------------------------------*/
			/* 1度の呼び出しで処理する件数分実施                                */
			/*------------------------------------------------------------------*/

			L3R_DI();
			/* 割り込み禁止設定区間短縮の為、割り込み禁止区間を分割し、*/
			/* Rポインタ取得・更新、Rカウンタ更新のみを処理する		   */

			Idx = pQueRouterFields->readPointer;

			if ((pCommonBufferArray[Idx]->pFields->sndPrtclBit == L3R_CLR)
				&& (pCommonBufferArray[Idx]->pFields->sndPrtclReqBit == L3R_CLR)){
				/*--------------------------------------------------------------*/
				/* 中継ステータスがクリアされていれば操作位置を進める           */
				/*--------------------------------------------------------------*/
				Idx++;

				if (Idx >= size) {
					Idx = 0;
				}
				pQueRouterFields->readPointer = Idx;
				pQueRouterFields->readCount--;
			} else {
				/*--------------------------------------------------------------*/
				/* 中継ステータスが立っていればその位置で中断                   */
				/*--------------------------------------------------------------*/
				Status = L3R_SET;
			}

			L3R_EI();

			if(Status == L3R_SET){
				/*--------------------------------------------------------------*/
				/* 割り込み禁止解除の制約により、中継ステータス再判定           */
				/* タイミングで、ループ処理を中断する                           */
				/*--------------------------------------------------------------*/
				break;
			}
		}
	} else {
		L3R_DI();

		/* 割り込み禁止設定区間短縮の為、割り込み禁止区間を分割し、		*/
		/* ポインタ不整合時は、GWバッファ制御変数、MBQバッファ制御変数  */
		/* クリア処理のみをする											*/

		pQueRouterFields->writePointer = 0;
		pQueRouterFields->enquePointer = 0;
		pQueRouterFields->readPointer  = 0;
		pQueRouterFields->enqueCount = 0;
		pQueRouterFields->readCount  = 0;

		self->CancelSendQue();

		L3R_EI();
	}

	return;
}

/*************************************************************************//**
 * @fn			void QueRouter_ClearCh(Router *self, uint8 ch)
 * @brief		存在するCh要素クリア
 * @details		特定Ch要求クリア（存在する要素のみ）
 * @param[in]	self	自身へのポインタ
 * @param[in]	ch		対象CH
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void QueRouter_ClearCh(Router *self, uint8 ch)
{
	uint32 id;					/* バッファインデックス */
	uint16 sndPrtclBit;					/* 送信プロトコル       */
	CommonBuffer *const *pCommonBufferArray = self->pBuffer;
	RouterFields *pQueRouterFields = self->pFields;
	uint32 readPointer = pQueRouterFields->readPointer;
	uint32 writePointer = pQueRouterFields->writePointer;

	sndPrtclBit = (((uint16)L3R_ON) << ch);

	if(readPointer <= writePointer) {
		for (id = readPointer; id < writePointer; id++) {
			L3R_DI();
			CommonBuffer_ClrSndStatusPrtcl(pCommonBufferArray[id], sndPrtclBit);
			L3R_EI();
		}
	} else {
		uint32 size = self->size;

		for (id = 0; id < writePointer; id++) {
			L3R_DI();
			CommonBuffer_ClrSndStatusPrtcl(pCommonBufferArray[id], sndPrtclBit);
			L3R_EI();
		}
		for (id = readPointer; id < size; id++) {
			L3R_DI();
			CommonBuffer_ClrSndStatusPrtcl(pCommonBufferArray[id], sndPrtclBit);
			L3R_EI();
		}
	}

	return ;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
