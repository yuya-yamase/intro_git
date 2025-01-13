/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	    CHM_ChCnvtr.h
 * @brief	    チャネル論物変換
 * @attention	チャネル構成変更時には必ず、本情報および使用箇所に必要な修正を実施すること
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		チャンネル定義ファイル：
 * @note            チャネル設定.xlsx
 * @note		テンプレートファイル：
 * @note            templates/CHM_ChCnvtrH.tmpl
 * @note	ツールバージョン
 * @note		4.4.0
 ****************************************************************************/
#ifndef CHM_CHCNVTR_H
#define CHM_CHCNVTR_H

#include "CHM_PhysicalCh.h"
#include "CHM_LogicCh.h"

/*----外部変数宣言・変数名置換マクロ-----------------------------------------*/
#define CHM_CH_INVALID		(0xFFU)

/* 論理チャネル(文字列結合用マクロ) */
#define CHM_LOG_CH_0		(0U)
#define CHM_LOG_CH_1		(1U)
#define CHM_LOG_CH_2		(2U)
#define CHM_LOG_CH_3		(3U)

/* 物論変換 */
/* CAN用 */
#define CHM_PHY2LOG_CH_0	CHM_LOG_CH_0
#define CHM_PHY2LOG_CH_1	CHM_LOG_CH_1
#define CHM_PHY2LOG_CH_2	CHM_LOG_CH_2
#define CHM_PHY2LOG_CH_3	CHM_LOG_CH_3


/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_CHM_START_SEC_CONST
#include "GW_CHM_Memmap.h"

extern const uint8 CHM_ChCnvtr_ControllerId_To_Log[CHM_CONTROLLER_NUM];
extern const uint8 CHM_ChCnvtr_PhyIp0_To_Log[CHM_PHY_IP0_CONTROLLER_NUM];
extern const uint8 CHM_ChCnvtr_PhyIp1_To_Log[CHM_PHY_IP1_CONTROLLER_NUM];
extern const uint8 CHM_ChCnvtr_VCan_To_Log[CHM_VCAN_CONTROLLER_NUM];
extern const uint8 CHM_ChCnvtr_Eth_To_Log[CHM_ETH_CONTROLLER_NUM];
extern const CHM_PHY_RESOURCE_INFO CHM_ChConv_Log_To_Phy[CHM_LOG_CAN_CH_NUM];
extern const uint8 CHM_ChCnvtr_Log_To_NwType[CHM_LOG_CAN_CH_NUM];

#define GW_CHM_STOP_SEC_CONST
#include "GW_CHM_Memmap.h"

#endif /* CHM_CHCNVTR_H */
