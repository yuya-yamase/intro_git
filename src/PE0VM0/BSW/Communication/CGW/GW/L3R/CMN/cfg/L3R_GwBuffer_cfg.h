/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_GwBuffer_cfg.h
 * @brief		MBQのバッファリング コンフィグ
 * @details		
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
 * @note            templates/L3R_GwBuffer_cfgH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#ifndef L3R_GWBUFFER_CFG_H
#define L3R_GWBUFFER_CFG_H

#include "Std_Types.h"

#include "L3R_Common.h"

/*----フレーム種別定義--------------------------------------------------------------*/
#define L3R_FRAMECLASS_NON				(0U)	/* フレーム種別 なし */
#define L3R_FRAMECLASS_CTRL_0			(0U)	/* フレーム種別 0:制御 */
#define L3R_FRAMECLASS_CTRL_1			(1U)	/* フレーム種別 1:制御 */
#define L3R_FRAMECLASS_CTRL_2			(2U)	/* フレーム種別 2:制御 */
#define L3R_FRAMECLASS_DIAG				(3U)	/* フレーム種別 3:ダイアグ */
#define L3R_FRAMECLASS_DYNAMC			(4U)	/* フレーム種別 4:動的 */
#define L3R_FRAMECLASS_ETH				(5U)	/* フレーム種別 5:Ethernet */

#endif	/* L3R_GWBUFFER_CFG_H */
