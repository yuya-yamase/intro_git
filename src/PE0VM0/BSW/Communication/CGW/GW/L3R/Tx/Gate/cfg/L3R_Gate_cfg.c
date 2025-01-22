/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Gate_cfg.c
 * @brief	
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
 * @note            templates/L3R_Gate_cfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_config.h"


/* Gateの仕様をバス毎に設定する(論理CH順) */
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
const uint8 L3R_GateSpecTbl[CHM_LOG_CAN_CH_NUM] = {
	L3R_GATESPEC_NM,
	L3R_GATESPEC_NM,
	L3R_GATESPEC_NM,
	L3R_GATESPEC_NM
};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
