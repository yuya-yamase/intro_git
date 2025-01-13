/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Router_cfg.c
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
 * @note            templates/L3R_Router_cfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#if (CHM_LOG_ETH_CH_NUM != 0)
#include "CEConv.h"
#endif

#include "L3R_Router.h"


/* CAN-Eth中継用 コンテナID変換テーブル */
#if (CHM_LOG_ETH_CH_NUM != 0)
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
const uint8 L3R_Log_To_ContainerTable[CHM_LOG_ALL_CH_NUM] = {
	CECONV_CONTAINER_INVALID,
	CECONV_CONTAINER_INVALID,
	CECONV_CONTAINER_INVALID,
	CECONV_CONTAINER_INVALID
};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
#endif
