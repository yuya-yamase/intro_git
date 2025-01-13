/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_QueRouter_cfg.c
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
 * @note            templates/L3R_QueRouter_cfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_config.h"
#include "L3R_Router.h"

#include "L3R_QueRouter.h"


/* QueRouter用 関数テーブル */
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
void ( * const L3R_SendReqQueFuncTbl[CHM_LOG_ALL_CH_NUM])(uint8 ch, CommonBuffer *const pCommonBuffer) = {
	&Router_SendGWIdOverWrite,
	&Router_SendGWIdOverWrite,
	&Router_SendGWIdOverWrite,
	&Router_SendGWIdOverWrite
};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
