/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DynamicBuffer.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/10	A.Yasui(FSI)		制御フレームモニタで過剰遅延が起きた場合に、
 * 													該当IDの制御フレームモニタが止まる不具合対応
 * 			v1.02	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v1.03	2018/05/12	A.Yasui(FSI)		デファインの二重定義を解消(CAN FD情報)
 * 			v1.04	2018/05/30	A.Yasui(FSI)		コーディング規約対応(inline関数化対応)
 * 			v1.05	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・DynamicBuffer_GetGwData内の割込み禁止処理削除
 * 													・Bit位置取得方法を変更
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v2.01	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 * 			v2.02   2018/10/26	T.Yamamura(FSI)		割込み禁止コメント修正
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_CanMessageExt.h"
#include "L3R_Common.h"
#include "L3R_GateManager.h"
#include "L3R_LIB.h"
#include "L3R_Timer.h"
#include "L3R_CommonBuffer.h"

#include "L3R_DynamicBuffer.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define L3R_DYNAMIC_TIMEOUT	(1000U * L3R_FRT_1_MS)	/* 過剰遅延検出時間 */


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
 * @fn			uint8 DynamicBuffer_GetGwData(CommonBuffer *self, uint8 ch, uint8 *pDlc, uint32 *pCanid32, uint8 **ppData)
 * @brief		動的フレーム取得
 * @details		動的フレームのデータを引き渡す
 * @param[in]	self		自身へのポインタ
 * @param[in]	ch			Ch番号
 * @param[out]	pDlc		DLC格納先
 * @param[out]	pCanid32	CANID格納先
 * @param[out]	ppData		データ格納先
 * @return		データ取得結果
 * @retval		L3R_REQ_OK	データ取得成功
 * @retval		L3R_REQ_NG	データ取得失敗
 * @attention	割り込み禁止で呼び出される
 * @note		なし
 ****************************************************************************/
uint8 DynamicBuffer_GetGwData(CommonBuffer *self, uint8 ch, uint8 *pDlc, uint32 *pCanid32, uint8 **ppData)
{
	uint8 Ret = L3R_REQ_NG;	/* 戻り値               */
	
	CommonBufferFields *pDynamicBufferFields;
	uint16 sndPrtclBit = (((uint16)L3R_ON) << ch);

	pDynamicBufferFields = self->pFields;

	if ((pDynamicBufferFields->sndPrtclBit & sndPrtclBit) != 0U) {
		uint32 rcvTime = pDynamicBufferFields->rcvTime;
		uint32 sndTime = L3R_Timer_Frt();

		if (L3R_DYNAMIC_TIMEOUT > (sndTime - rcvTime)) {
			/*--------------------------------------------------------------*/
			/* 過剰遅延未検出→正常完了                                     */
			/*--------------------------------------------------------------*/
			uint32 canId32 = (uint32) pDynamicBufferFields->canId;
		
			/* 送信先Frame切り替え(標準/拡張) */
			if (pDynamicBufferFields->canId > L3R_NOMALCANID_MAX) {
				/* 拡張 Frame */
				canId32 = canId32 | (((uint32)L3R_ON) << L3R_TCOV_EXD_SHIFT_NO);
			} 
		
			*pDlc     = pDynamicBufferFields->length;
			*pCanid32 = canId32 | (((uint32) pDynamicBufferFields->fd) << L3R_TCOV_CANFD_SHIFT_NO);
			*ppData   = self->Data;

		Ret = L3R_REQ_OK;
		} else {
			/*------------------------------------------------------------------*/
			/* 中継破棄検出時、中継ステータスの更新                             */
			/*------------------------------------------------------------------*/
			DynamicBuffer_ClrSndStatusPrtcl(self, sndPrtclBit);
		}
	}

	return (Ret);
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
