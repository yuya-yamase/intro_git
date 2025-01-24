/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		CommonBuffer.c
 * @brief		受信データを保存する
 * @date
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v1.02	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・CommonBuffer_SendFinNotify内の割込み禁止処理削除
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v2.01	2018/10/25	T.Yamamura(FSI) 	コードレベルアップ対応(オブジェクト不変)
 * 			v2.02   2018/10/26	T.Yamamura(FSI)		割込み禁止コメント修正
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v3.01	2019/10/09	T.Yamamura(FSI)		[570B-Phase10][IntegNo.1124328]処理負荷削減対応
 * 													・CommonBuffer_SendFinNotify()削除
 * @attention
 * @note
 ****************************************************************************/
#include "Std_Types.h"

#include "L3R_config.h"
#include "L3R_GateManager.h"
#include "L3R_LIB.h"

#include "L3R_CommonBuffer.h"

/*----マクロ定義------------------------------------------------------------*/

/*----プロトタイプ宣言------------------------------------------------------*/

/*----外部変数宣言----------------------------------------------------------*/


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			void CommonBuffer_Init(CommonBuffer *self)
 * @brief		初期化
 * @details		初期化処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void CommonBuffer_Init(CommonBuffer *self)
{
	CommonBufferFields *pBufferFields = self->pFields;
	
	L3R_DI();
	pBufferFields->rcvTime  = 0U;
	pBufferFields->length   = 0U;
	pBufferFields->canId    = 0U;
	pBufferFields->sndPrtclBit = L3R_LOG_BIT_NULL;
	pBufferFields->sndPrtclReqBit = L3R_LOG_BIT_NULL;
	pBufferFields->searchId    = 0U;
	L3R_LIB_memset(self->Data, 0U, self->maxDataSize);
	L3R_EI();
}

/*************************************************************************//**
 * @fn			uint8 CommonBuffer_GetCanData(CommonBuffer *self, uint8 ch, uint8* pDlc, uint32* pCanid32, uint8** ppData)
 * @brief		CANデータ取得要求
 * @details		CANデータの取得要求を行う
 * @param[in]	self		自身へのポインタ
 * @param[in]	ch			送信先CH
 * @param[out]	pDlc		受信サイズへのポインタ
 * @param[out]	pCanid32	受信CAN IDへのポインタ
 * @param[out]	ppData		受信データへのポインタ
 * @return		処置結果
 * @retval		L3R_REQ_OK		送信OK
 * @retval		L3R_REQ_WAIT	送信待ち
 * @retval		L3R_REQ_NG		送信NG
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint8 CommonBuffer_GetCanData(CommonBuffer *self, uint8 ch, uint8* pDlc, uint32* pCanid32, uint8** ppData)
{
	uint8 Ret = L3R_REQ_NG;

	if (self != NULL_PTR)
	{
		/*送信先Chのステータスを取得し、送信要求を処理*/
		uint8 GateStatusTmp = L3R_GateM_GetGateStatus(ch);
		switch (GateStatusTmp)
		{
		case L3R_GM_SEND_OK:
			Ret = self->funcList->GetGWData(self, ch, pDlc, pCanid32, ppData);/*過剰遅延ならばL3R_REQ_NGが戻り値*/
			break;
		case L3R_GM_SEND_NG:
			CommonBuffer_ClrSndStatusCh(self, ch);
			Ret = L3R_REQ_NG;
			break;
		case L3R_GM_SEND_WAIT:
			Ret = L3R_REQ_WAIT;
			break;
		default:/*RAM化け対策*/
			Ret = L3R_REQ_WAIT;
			break;
		}
	}

	return Ret;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
