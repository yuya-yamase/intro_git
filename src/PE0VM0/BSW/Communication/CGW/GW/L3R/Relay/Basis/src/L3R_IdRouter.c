/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_IdRouter.c
 * @brief	ID毎ルータ制御
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
 * 			v3.01	2018/09/14	T.Yamamura(FSI)		GwIdRouter_QuickWakeup()のコンパイルSW付与
 * 			v3.02	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
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

#include "L3R_AutoTCanConvertRule.h"
#include "L3R_CommonBuffer.h"
#include "L3R_Common.h"
#include "L3R_config.h"
#include "L3R_Fail.h"
#include "L3R_LIB.h"
#include "L3R_Timer.h"

#include "L3R_IdRouter.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


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
 * @fn			CommonBuffer *IdRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId uint8 fd)
 * @brief		中継処理（ID毎ルータタイプ）
 * @details		GW管理データをID毎バッファで管理します
 * @param[in]	self	自身へのポインタ
 * @param[in]	canId	CAN ID
 * @param[in]	dlc		データ長
 * @param[in]	Data	データへのポインタ
 * @param[in]	gwId	GwID
 * @param[in]	rxCh	受信CH
 * @param[in]	searchId	探索位置
 * @return		データを保存するCommonBufferへのポインタ
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
CommonBuffer *IdRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId, uint8 fd)
{
	CommonBuffer *pCommonBuffer = self->pBuffer[gwId];
	CommonBufferFields *pBufferFields;

		
	/*----------------------------------------------------------------------*/
	/* データ上書き時の処理													*/
	/*----------------------------------------------------------------------*/
	self->OverWrite(self, &pCommonBuffer);

	pBufferFields = pCommonBuffer->pFields;

	L3R_DI();
	
	/* ↓データコピー～送信要求の設定までは、割禁にしないと途中で送信完了割り込みが入ると、同じフレームを2度送ることになる */
	/*----------------------------------------------------------------------*/
	/* ID毎バッファへのデータコピー                                         */
	/*----------------------------------------------------------------------*/
	pBufferFields->rcvTime	= L3R_Timer_Frt();
	pBufferFields->canId	= canId;
	pBufferFields->length	= dlc;
	pBufferFields->searchId	= searchId;
	L3R_LIB_memcpy(pCommonBuffer->Data, Data, pCommonBuffer->maxDataSize);
	
	/*----------------------------------------------------------------------*/
	/* 送信要求の設定														*/
	/*----------------------------------------------------------------------*/
	pBufferFields->sndPrtclReqBit	|= self->GetSendProtocol(pCommonBuffer, 0U, rxCh);
	/* ↑データコピー～送信要求の設定までは割禁。途中で送信完了割り込みが入ると、同じフレームを2度送ることになるため */
	pCommonBuffer->pFields->fd = fd;

	/*----------------------------------------------------------*/
	/* 中継先ディスパッチ                                       */
	/*----------------------------------------------------------*/

	IdRouter_SendReq(pCommonBuffer);

	L3R_EI();

	return (pCommonBuffer);
}


/*************************************************************************//**
 * @fn			void IdRouter_SendReq(CommonBuffer *pCommonBuffer)
 * @brief		送信要求処理
 * @details		CH数分送信要求する
 * @param[in]	pCommonBuffer		送信するCommonBufferへのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void IdRouter_SendReq(CommonBuffer *pCommonBuffer) 
{
	uint16 sndPrtclReqBit = pCommonBuffer->pFields->sndPrtclReqBit;
	
	if(sndPrtclReqBit != L3R_LOG_BIT_NULL){
		uint32 ch;							/* CH						*/

		for (ch = 0; ch < CHM_LOG_ALL_CH_NUM; ch++) {
			/*------------------------------------------------------*/
			/* CH数分送信要求を実施                                 */
			/*------------------------------------------------------*/
			if ((sndPrtclReqBit & (((uint16)L3R_ON) << ch)) != 0U) {
				L3R_SendReqIdFuncTbl[ch]((uint8) ch, pCommonBuffer);
			}
		}
		CommonBuffer_ClrSndReqAll(pCommonBuffer);
	}

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
