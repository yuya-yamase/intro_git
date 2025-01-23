/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_GateManager.h
 * @brief		中継先ゲート管理
 * @details		送信許可or禁止or保留を制御する
 * @note	
 * @date		v1.00   2016/04/01  H.Tanaka    新規作成(リファクタリング) 
 * @date		v1.01   2017/03/03  Y.Katayama  19PF向け型定義対応 
 * @date		v1.02   2018/07/25  T.Yamamura  処理負荷改善対応
 * @date										・u1g_GW_RTR_GateM_GetGateStatus関数のインライン化
 * @date		v2.00	2018/11/21	Y.Katayama	中継改善(オブジェクト不変)
 ****************************************************************************/

#ifndef	L3R_GATEMANAGER_H
#define	L3R_GATEMANAGER_H

#include "Std_Types.h"
#include "CHM_LogicCh.h"

/*----外部変数宣言・変数名置換マクロ-----------------------------------------*/

#define L3R_GM_SEND_WAIT		(0x01U)
#define L3R_GM_SEND_OK			(0x02U)
#define L3R_GM_SEND_NG			(0x04U)

#define L3R_GM_NS_STANDBY		(0x01U)
#define L3R_GM_NS_START			(0x02U)
#define L3R_GM_NS_STOP			(0x04U)	

#define L3R_GM_FAIL_SENDLOCK	(0x01U) 	/* 送信ロック */
#define L3R_GM_FAIL_BUSOFF		(0x02U) 	/* バスオフ */

/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
extern uint8 GateStatus[CHM_LOG_CAN_CH_NUM];
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern void L3R_GateM_Init(void);
extern void L3R_GateM_MainTask(void);
extern void L3R_GateM_NmWakeup(uint8 LogicCh);
extern void L3R_GateM_QuickWakeup(void);
extern void L3R_GateM_IgOn(void);
extern void L3R_GateM_Fail(uint8 Factor, uint8 LogicCh);

/*----関数マクロ------------------------------------------------------------*/
/**
 * @fn			uint8 L3R_GateM_GetGateStatus(uint8 LogicCh)
 * @brief		通信(ゲート)状態取得
 * @details		指定CHの通信(ゲート)状態を取得する
 * @param[in]	LogicCh		CH番号
 * @return		通信(ゲート)状態
 * @retval		L3R_GM_SEND_WAIT	送信保留
 * @retval		L3R_GM_SEND_OK		送信許可
 * @retval		L3R_GM_SEND_NG		送信禁止
 * @attention	なし
 * @note		なし
 */
static inline uint8 L3R_GateM_GetGateStatus(uint8 LogicCh) __attribute__((always_inline,unused));
static inline uint8 L3R_GateM_GetGateStatus(uint8 LogicCh)
{
	return GateStatus[LogicCh];
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#endif	/* L3R_GATEMANAGER_H */
