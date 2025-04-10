/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_canmbq_auto_drvcfg_9.h
 * @brief		CAN MBOXキュー制御 
 * @details		CAN MBOXキュー制御 Ch9のカスタマイズ要素
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
 * @note		3.6.0
 ****************************************************************************/

#ifndef L3R_CANMBQ_AUTO_DRVCFG_9_H
#define L3R_CANMBQ_AUTO_DRVCFG_9_H


/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/

#define CANMBQ_SENDFIN_HOOK_9(ch, MsgBuffer)

#define CANMBQ_QUE0_TXQUESIZE_9	(2U)
#define CANMBQ_QUE1_TXQUESIZE_9	(2U)
#define CANMBQ_QUE2_TXQUESIZE_9	(16U)
#define CANMBQ_QUE3_TXQUESIZE_9	(512U)
#define CANMBQ_QUE4_TXQUESIZE_9	(0U)
#define CANMBQ_QUE5_TXQUESIZE_9	(0U)
#define CANMBQ_QUE6_TXQUESIZE_9	(0U)
#define CANMBQ_QUE7_TXQUESIZE_9	(0U)

#define CANMBQ_QUE0_TXRETRY_9	(1U)
#define CANMBQ_QUE1_TXRETRY_9	(1U)
#define CANMBQ_QUE2_TXRETRY_9	(1U)
#define CANMBQ_QUE3_TXRETRY_9	(1U)
#define CANMBQ_QUE4_TXRETRY_9	(0U)
#define CANMBQ_QUE5_TXRETRY_9	(0U)
#define CANMBQ_QUE6_TXRETRY_9	(0U)
#define CANMBQ_QUE7_TXRETRY_9	(0U)

#endif /* L3R_CANMBQ_AUTO_DRVCFG_9_H */
