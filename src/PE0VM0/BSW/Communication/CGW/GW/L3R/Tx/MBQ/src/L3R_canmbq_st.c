/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_st.c											*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			Driver status process									*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2018.01.20	@author	T.Totsuka(FSI)
 *		新規作成
 *	@version	1.0.1	2018.10.25	@author	T.Yamamura(FSI)
 *		コードレベルアップ対応(オブジェクト不変)
 *	@version	2.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#include "Std_Types.h"

#include "L3R_canmbq_common.h"
#include "L3R_canmbq_st.h"


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void CANMBQ_SndLock(uint8 ch)
 * @brief		送信ロック検出通知
 * @details		MBQで検出した送信ロックを通知する
 * @param[in]	ch	送信ロック検出CH番号
 * @return		なし
 * @attention	なし
 * @note		なし
 */
void CANMBQ_SndLock(uint8 ch)
{
	/* MBOXキュー制御での送信ロック検出時はフラグを立てておき、			*/
	/* SPF CSが提供するフック(spf_cmng_UJudgeFail)からフラグを参照して	*/
	/*  "上位層通信障害検出"を通知する。	*/
	CANMBQ_SetSendLockFlg(ch);
	
	/* 送信ロックを検出したことを上位層へ通知する */
	L3R_Fail_SendLockNotify(ch);

	return;
}

/**
 * @fn			uint8 CANMBQ_GetMode(uint8 ch)
 * @brief		通信状態取得
 * @details		指定CHの通信状態を取得する
 * @param[in]	ch	CH番号
 * @return		通信状態取得結果
 * @retval		CANMBQ_NOCOMM	通信不可状態
 * @retval		CANMBQ_COMM		通信可能状態
 * @attention	なし
 * @note		なし
 */
uint8 CANMBQ_GetMode(uint8 ch)
{
	ComM_StateType ComM_Status;
	uint8 ret = CANMBQ_NOCOMM;
	
	(void)ComM_GetState(CHM_ChCnvtr_Log_To_AubCh[ch], &ComM_Status);
	if ((ComM_Status == COMM_FULL_COM_NETWORK_REQUESTED) || 
		(ComM_Status == COMM_FULL_COM_READY_SLEEP) ||
		(ComM_Status == COMM_SILENT_COM )) {
		ret = CANMBQ_COMM;
	}
	
	return ret;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
