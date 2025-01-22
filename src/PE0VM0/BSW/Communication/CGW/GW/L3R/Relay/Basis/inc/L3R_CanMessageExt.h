/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_CanMessageExt.h
 * @brief	CanMessage制御
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/05/15	T.Yamamura(FSI)		可変化対応
 * 													・CH名称CHM_LOG_BIT_DIAG→RTR_LOG_BIT_DIAGへ変更
 * 			v2.03	2018/06/11	T.Yamamura(FSI)		QAC対応
 *													・CanMessage_ActivateCAN300()のインライン化
 * 			v2.04	2018/06/19	K.Ito(FSI)			帯域制限追加対応
 * 			v2.05	2018/07/31	K.Ito(FSI)			QAC対応
 * 			v2.06	2018/08/06	K.Ito(FSI)			DLC9以上対応
 * 			v2.07	2018/08/29	T.Yamamura(FSI)		CanMessage_EnterNormalModeの置換マクロ削除
 * 			v2.08	2018/10/25	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 * 			v2.09	2018/10/26	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *													・定数マクロ化
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/
#ifndef	L3R_CANMESSAGEEXT_H
#define	L3R_CANMESSAGEEXT_H

#include "L3R_config.h"
#include "L3R_CanMessage.h"

/*----プロトタイプ宣言------------------------------------------------------*/
#define L3R_CM_Receive(rxCh, canId32, dlc, Data, searchId) CanMessage_Receive(rxCh, canId32, dlc, Data, searchId)
#define L3R_CM_EnterReprogMode() CanMessage_EnterReprogMode()
#define L3R_CM_ExitReprogMode() CanMessage_ExitReprogMode()
#define L3R_CM_EnterThatchamMode() CanMessage_EnterThatchamMode()
#define L3R_CM_ExitThatchamMode() CanMessage_ExitThatchamMode()
#define L3R_CM_ActivateMonitor() CanMessage_ActivateMonitor()
#define L3R_CM_InActivateMonitor() CanMessage_InActivateMonitor()

/*----型宣言----------------------------------------------------------------*/

/*----マクロ定義------------------------------------------------------------*/
#define L3R_FDF_OFF							(0x0U)
#define L3R_FDF_ON							(0x1U)
#define L3R_EXDF_OFF						(0x0U)
#define L3R_EXDF_ON							(0x1U)
#define L3R_NOMALCANID_MAX					(0x7FFU)

/*----関数マクロ------------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"

/**
 * @fn			Std_ReturnType L3R_CM_SetMonitorAll(const uint32 CanId[], uint16 length, CallBackFunc func)
 * @brief		送信先の設定
 * @details		送信先の設定を行う
 * @param[in]	CanId[]		CANID
 * @param[in]	length		設定数
 * @param[in]	func		コールバック関数
 * @return		送信先設定結果
 * @retval		E_OK		設定成功
 * @retval		E_NOT_OK	設定失敗
 * @attention	前提条件：	CanId[]内のIDはソートされている
 *							lengthはCanId[]の要素数を超えていない
 * @note		なし
 */
static inline Std_ReturnType L3R_CM_SetMonitorAll(const uint32 CanId[], uint16 length, CallBackFunc func) __attribute__((always_inline,unused));
static inline Std_ReturnType L3R_CM_SetMonitorAll(const uint32 CanId[], uint16 length, CallBackFunc func)
{
	return CanMessage_SetProtocolAll(CanId, length, CHM_LOG_BIT_USE_DIAG, L3R_CTRLFRM_STARTID, L3R_CTRLFRM_ENDID, func);
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#endif	/* L3R_CANMESSAGEEXT_H */
