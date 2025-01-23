/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_BandLimit.c
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/06/19	K.Ito(FSI)		新規作成
 * 			v1.01	2018/08/06	K.Ito(FSI)		帯域制限 定数変更対応
 * 			v1.02	2018/10/25	T.Yamamura(FSI)	コードレベルアップ対応(オブジェクト不変)
 *			v2.00	2018/11/21	Y.Katayama(FSI)	中継改善(オブジェクト不変)
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_Common.h"
#include "L3R_CanMessage.h"
#include "L3R_Timer.h"

#include "L3R_BandLimit.h"



/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define MAINTASK_TIMEOUT	(25U * L3R_FRT_1_MS)
                                       /**< 5msタスク遅延許容値(ms * LSB:μs) */

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static uint32 BandLimit_ReferenceTime;
static uint8 BandLimit_RunStateFlg;
#define GW_L3R_STOP_SEC_NBVA_ZI
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
 * @fn			void BandLimit_MainTask(void)
 * @brief		5msタスク処理
 * @details		5msタスク処理を行う
 * @param		なし
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void BandLimit_MainTask(void)
{
	L3R_DI();
	
	/* フリーランタイマの値を取得して基準時間を更新 */
	BandLimit_ReferenceTime = L3R_Timer_Frt();

#ifdef GSS_H
	/* 通常作動中の場合のみフラグをONに更新 */
	if (GSS_IsRun() == TRUE) {
		BandLimit_RunStateFlg = L3R_ON;
	} else {
		BandLimit_RunStateFlg = L3R_OFF;
	}
#else
    BandLimit_RunStateFlg = L3R_OFF;
#endif

	L3R_EI();

	return;
}

/*************************************************************************//**
 * @fn			void BandLimit_ExitMainTask(void)
 * @brief		Run状態終了時の処理
 * @details		Run状態終了時処理を行う
 * @param		なし
 * @return		なし
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
void BandLimit_ExitMainTask(void)
{
	L3R_DI();
	
	BandLimit_RunStateFlg = L3R_OFF;
	
	L3R_EI();
	
	return;
}

/*************************************************************************//**
 * @fn			uint8 BandLimit_JudgeLimit(void)
 * @brief		5msタスク上限超過判定
 * @details		5msタスク上限超過判定を行う
 * @param		なし
 * @return		判定結果
 * @retval		L3R_E_OK		5ms上限以下
 * @retval		L3R_E_NOT_OK	5ms上限超過
 * @attention 	なし
 * @note		なし
 ****************************************************************************/
uint8 BandLimit_JudgeLimit(void)
{
	uint32 elapsedTime;
	uint8 Ret = L3R_E_OK;

	/* 基準時間からの経過時間を計算 */
	elapsedTime = L3R_Timer_Frt() - BandLimit_ReferenceTime;

	if(MAINTASK_TIMEOUT < elapsedTime) {

		/* 信頼性フラグON時のみ帯域制限を行う */
		if (L3R_ON == BandLimit_RunStateFlg) {
			Ret = L3R_E_NOT_OK;

			/* 動的モニタの停止要求 */
			CanMessage_InActivateMonitorByRTR();
		}
	}
	
	return(Ret);
}


#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
