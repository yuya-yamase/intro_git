/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	    L3R_AutoTCanConvertRule.h
 * @brief	    変換ルール
 * @details	    機能概略説明
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
 * @note            templates_SZK/L3R_AutoTCanConvertRuleH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_AUTOTCANCONVERTRULE_H
#define	L3R_AUTOTCANCONVERTRULE_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "L3R_canmbq_auto_drvcfg_0.h"
#include "L3R_canmbq_auto_drvcfg_1.h"
#include "L3R_canmbq_auto_drvcfg_2.h"
#include "L3R_canmbq_auto_drvcfg_3.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
/* CANプロトコル定義 */
#define L3R_TCAN_IDSTART		(1U)
#define L3R_TCAN_IDNUM			(487U)

#define L3R_TDIAG_IDSTART		(488U)
#define L3R_TDIAG_IDNUM			(0U)

/* 送信フレーム数 */
#define L3R_TCAN_CH0_PRIORITY_0_TXNUM		(0U)
#if (CANMBQ_QUE0_TXQUESIZE_0 < L3R_TCAN_CH0_PRIORITY_0_TXNUM)
#error [QUE0_TXQUESIZE_0 Configuration Error!!]
#endif
#define L3R_TCAN_CH0_PRIORITY_1_TXNUM		(0U)
#if (CANMBQ_QUE1_TXQUESIZE_0 < L3R_TCAN_CH0_PRIORITY_1_TXNUM)
#error [QUE1_TXQUESIZE_0 Configuration Error!!]
#endif
#define L3R_TCAN_CH0_PRIORITY_2_TXNUM		(0U)
#if (CANMBQ_QUE2_TXQUESIZE_0 < L3R_TCAN_CH0_PRIORITY_2_TXNUM)
#error [QUE2_TXQUESIZE_0 Configuration Error!!]
#endif
#define L3R_TCAN_CH0_PRIORITY_3_TXNUM		(0U)
#if (CANMBQ_QUE3_TXQUESIZE_0 < L3R_TCAN_CH0_PRIORITY_3_TXNUM)
#error [QUE3_TXQUESIZE_0 Configuration Error!!]
#endif
#define L3R_TCAN_CH1_PRIORITY_0_TXNUM		(0U)
#if (CANMBQ_QUE0_TXQUESIZE_1 < L3R_TCAN_CH1_PRIORITY_0_TXNUM)
#error [QUE0_TXQUESIZE_1 Configuration Error!!]
#endif
#define L3R_TCAN_CH1_PRIORITY_1_TXNUM		(0U)
#if (CANMBQ_QUE1_TXQUESIZE_1 < L3R_TCAN_CH1_PRIORITY_1_TXNUM)
#error [QUE1_TXQUESIZE_1 Configuration Error!!]
#endif
#define L3R_TCAN_CH1_PRIORITY_2_TXNUM		(79U)
#if (CANMBQ_QUE2_TXQUESIZE_1 < L3R_TCAN_CH1_PRIORITY_2_TXNUM)
#error [QUE2_TXQUESIZE_1 Configuration Error!!]
#endif
#define L3R_TCAN_CH1_PRIORITY_3_TXNUM		(0U)
#if (CANMBQ_QUE3_TXQUESIZE_1 < L3R_TCAN_CH1_PRIORITY_3_TXNUM)
#error [QUE3_TXQUESIZE_1 Configuration Error!!]
#endif
#define L3R_TCAN_CH2_PRIORITY_0_TXNUM		(0U)
#if (CANMBQ_QUE0_TXQUESIZE_2 < L3R_TCAN_CH2_PRIORITY_0_TXNUM)
#error [QUE0_TXQUESIZE_2 Configuration Error!!]
#endif
#define L3R_TCAN_CH2_PRIORITY_1_TXNUM		(0U)
#if (CANMBQ_QUE1_TXQUESIZE_2 < L3R_TCAN_CH2_PRIORITY_1_TXNUM)
#error [QUE1_TXQUESIZE_2 Configuration Error!!]
#endif
#define L3R_TCAN_CH2_PRIORITY_2_TXNUM		(53U)
#if (CANMBQ_QUE2_TXQUESIZE_2 < L3R_TCAN_CH2_PRIORITY_2_TXNUM)
#error [QUE2_TXQUESIZE_2 Configuration Error!!]
#endif
#define L3R_TCAN_CH2_PRIORITY_3_TXNUM		(0U)
#if (CANMBQ_QUE3_TXQUESIZE_2 < L3R_TCAN_CH2_PRIORITY_3_TXNUM)
#error [QUE3_TXQUESIZE_2 Configuration Error!!]
#endif
#define L3R_TCAN_CH3_PRIORITY_0_TXNUM		(7U)
#if (CANMBQ_QUE0_TXQUESIZE_3 < L3R_TCAN_CH3_PRIORITY_0_TXNUM)
#error [QUE0_TXQUESIZE_3 Configuration Error!!]
#endif
#define L3R_TCAN_CH3_PRIORITY_1_TXNUM		(17U)
#if (CANMBQ_QUE1_TXQUESIZE_3 < L3R_TCAN_CH3_PRIORITY_1_TXNUM)
#error [QUE1_TXQUESIZE_3 Configuration Error!!]
#endif
#define L3R_TCAN_CH3_PRIORITY_2_TXNUM		(331U)
#if (CANMBQ_QUE2_TXQUESIZE_3 < L3R_TCAN_CH3_PRIORITY_2_TXNUM)
#error [QUE2_TXQUESIZE_3 Configuration Error!!]
#endif
#define L3R_TCAN_CH3_PRIORITY_3_TXNUM		(0U)
#if (CANMBQ_QUE3_TXQUESIZE_3 < L3R_TCAN_CH3_PRIORITY_3_TXNUM)
#error [QUE3_TXQUESIZE_3 Configuration Error!!]
#endif

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_AUTOTCANCONVERTRULE_H */
