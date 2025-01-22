/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_canmbq_auto_drvcfg_2.h
 * @brief		CAN MBOXキュー制御 
 * @details		CAN MBOXキュー制御 Ch2のカスタマイズ要素
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
 * @note            templates/L3R_canmbq_auto_drvcfgH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

#ifndef L3R_CANMBQ_AUTO_DRVCFG_2_H
#define L3R_CANMBQ_AUTO_DRVCFG_2_H


/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/

#define CANMBQ_SENDFIN_HOOK_2(ch, MsgBuffer)

#define CANMBQ_QUE0_TXQUESIZE_2	(2U)
#define CANMBQ_QUE1_TXQUESIZE_2	(2U)
#define CANMBQ_QUE2_TXQUESIZE_2	(64U)
#define CANMBQ_QUE3_TXQUESIZE_2	(512U)
#define CANMBQ_QUE4_TXQUESIZE_2	(0U)
#define CANMBQ_QUE5_TXQUESIZE_2	(0U)
#define CANMBQ_QUE6_TXQUESIZE_2	(0U)
#define CANMBQ_QUE7_TXQUESIZE_2	(0U)

#define CANMBQ_QUE0_TXRETRY_2	(1U)
#define CANMBQ_QUE1_TXRETRY_2	(1U)
#define CANMBQ_QUE2_TXRETRY_2	(1U)
#define CANMBQ_QUE3_TXRETRY_2	(1U)
#define CANMBQ_QUE4_TXRETRY_2	(0U)
#define CANMBQ_QUE5_TXRETRY_2	(0U)
#define CANMBQ_QUE6_TXRETRY_2	(0U)
#define CANMBQ_QUE7_TXRETRY_2	(0U)

#endif /* L3R_CANMBQ_AUTO_DRVCFG_2_H */
