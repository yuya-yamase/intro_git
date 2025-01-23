/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_config.h
 * @brief		L3R機能 コンフィグ
 * @attention	
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		制御フレームルーティングマップ：
 * @note            Ctrl_RTM.xlsx
 * @note		ダイアグ/リプログフレームルーティングマップ：
 * @note            Diag_RTM.xlsx
 * @note		チャンネル定義ファイル：
 * @note            channelDef.yml
 * @note		チャンネル定義ファイル(L3R)：
 * @note            channelDef_L3R.yml
 * @note		例外フレーム定義ファイル：
 * @note            exceptionalMessages.yml
 * @note		テンプレートファイル：
 * @note            templates/L3R_configH.tmpl
 * @note	ツールバージョン
 * @note		3.6.0
 ****************************************************************************/
#ifndef L3R_CONFIG_H
#define L3R_CONFIG_H

#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_Common.h"


/*----共通定義--------------------------------------------------------------*/
#define L3R_DISABLE  (0U)
#define L3R_ENABLE   (1U)


/*----BroadCast定義--------------------------------------------------------------*/
#define L3R_USE_BROADCAST		L3R_DISABLE


/*----論理CH番号(ChMaster)--------------------------------------------------------*/
#define L3R_LOG_BIT_NULL		(0U)

#define L3R_LOG_CH_G2M2_FD_BUS		(CHM_LOG_CH_G2M2_FD_BUS)
#define L3R_LOG_CH_G2M1_FD_BUS		(CHM_LOG_CH_G2M1_FD_BUS)
#define L3R_LOG_CH_G5M_FD_BUS		(CHM_LOG_CH_G5M_FD_BUS)
#define L3R_LOG_CH_VCAN_BUS			(CHM_LOG_CH_VCAN_BUS)
                   
/*	論理CHビット情報定義(ChMaster) */
#define L3R_LOG_BIT_G2M1_FD_BUS		(((uint16) 0x1U) << CHM_LOG_CH_G2M2_FD_BUS)
#define L3R_LOG_BIT_G5M_FD_BUS		(((uint16) 0x1U) << CHM_LOG_CH_G2M1_FD_BUS)
#define L3R_LOG_BIT_VCAN_CH0_CEN	(((uint16) 0x1U) << CHM_LOG_CH_G5M_FD_BUS)
#define L3R_LOG_BIT_VCAN_CH1_MET	(((uint16) 0x1U) << CHM_LOG_CH_VCAN_BUS)


/*----CHリスト-----------------------------------------------------------*/
#define CH_ARRY(ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15)			{(ch0), (ch1), (ch2), (ch3), (ch4), (ch5), (ch6), (ch7), (ch8), (ch9), (ch10), (ch11), (ch12), (ch13), (ch14), (ch15)}


/*----BusSpec情報--------------------------------------------------------*/

#define L3R_GATESPEC_MAX		(2U)	/**< バス仕様数*/
#define L3R_GATESPEC_NM			(0x00U)	/**< NM仕様index*/
#define L3R_GATESPEC_IG			(0x01U)	/**< IG仕様index*/

/*----FailTimer用マクロ--------------------------------------------------------*/
#define L3R_GM_FT_LSB			5U                          	/**< タイマーLSB */
#define L3R_GM_FT_SENDLOCK		(10U/L3R_GM_FT_LSB)				/**< 送信ロック復帰タイマー */
#define L3R_GM_FT_BUSOFF		(35U/L3R_GM_FT_LSB)			/**< バスオフ復帰タイマー */
#define L3R_GM_FT_MAX 			L3R_GM_FT_BUSOFF				/**< タイマー最長定数 */


/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern const uint8 L3R_GateSpecTbl[CHM_LOG_CAN_CH_NUM];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#endif	/* L3R_CONFIG_H */
