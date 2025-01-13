/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		CHM_LogicCh.h
 * @brief		論理チャネル情報
 * @details		上位層のアプリケーションが使用する論理チャネル情報を提供する
 * @attention	チャネル構成変更時には必ず、本情報および使用箇所に必要な修正を実施すること
 * @attention	CSコンフィグとの整合性を確保すること
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		チャンネル定義ファイル：
 * @note            チャネル設定.xlsx
 * @note		テンプレートファイル：
 * @note            templates/CHM_LogicChH.tmpl
 * @note	ツールバージョン
 * @note		4.4.0
 ****************************************************************************/
#ifndef CHM_LOGICCH_H
#define CHM_LOGICCH_H

/*----外部変数宣言・変数名置換マクロ-----------------------------------------*/

/* 論理チャネル数 */
#define CHM_LOG_CAN_CH_NUM			(4U)
#define CHM_LOG_ETH_CH_NUM			(0U)
#define CHM_LOG_ALL_CH_NUM			(CHM_LOG_CAN_CH_NUM + CHM_LOG_ETH_CH_NUM)

/* 論理チャネル番号 */
#define CHM_LOG_CH_G2M2_FD_BUS			(0U)
#define CHM_LOG_CH_G2M1_FD_BUS			(1U)
#define CHM_LOG_CH_G5M_FD_BUS			(2U)
#define CHM_LOG_CH_VCAN_BUS			(3U)
#define CHM_LOG_CH_NON			(0xFFU)

/* ダイアグバス設定（論理チャネル） */
#define CHM_LOG_CH_USE_DIAG		(CHM_LOG_CH_NON)

/* 論理チャネルBIT情報 (Ch番号0 を0x1 とした定義) */
#define CHM_LOG_BIT_G2M2_FD_BUS		((uint32)(0x1U) << (uint32)(CHM_LOG_CH_G2M2_FD_BUS))
#define CHM_LOG_BIT_G2M1_FD_BUS		((uint32)(0x1U) << (uint32)(CHM_LOG_CH_G2M1_FD_BUS))
#define CHM_LOG_BIT_G5M_FD_BUS		((uint32)(0x1U) << (uint32)(CHM_LOG_CH_G5M_FD_BUS))
#define CHM_LOG_BIT_VCAN_BUS		((uint32)(0x1U) << (uint32)(CHM_LOG_CH_VCAN_BUS))
#define CHM_LOG_BIT_NON			(0x0U)

/* ダイアグバス設定（チャネルBIT情報） */
#define CHM_LOG_BIT_USE_DIAG		(CHM_LOG_BIT_NON)

/* 仮想CANバス設定（チャネルBIT情報） */
#define CHM_LOG_BIT_VCAN		(CHM_LOG_BIT_VCAN_BUS)

/* ネットワーク種別 */
#define CHM_NWTYPE_NONE			(0x0000U)
#define CHM_NWTYPE_CTRL			(0x0001U)
#define CHM_NWTYPE_AS			(0x0002U)
#define CHM_NWTYPE_OTA			(0x0004U)
#define CHM_NWTYPE_DLC			(0x0008U)
#define CHM_NWTYPE_DCM			(0x0010U)

#endif /* CHM_LOGICCH_H */
