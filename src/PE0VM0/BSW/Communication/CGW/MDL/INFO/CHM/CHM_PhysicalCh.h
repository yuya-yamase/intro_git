/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		CHM_PhysicalCh.h
 * @brief		物理チャネル情報
 * @details		MCAL層が使用する物理チャネル情報を提供する
 * @attention	チャネル構成変更時には必ず、本情報および使用箇所に必要な修正を実施すること
 * @attention	マイコン、CANドライバ設定との整合性を確保すること
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		チャンネル定義ファイル：
 * @note            チャネル設定.xlsx
 * @note		テンプレートファイル：
 * @note            templates/CHM_PhysicalChH.tmpl
 * @note	ツールバージョン
 * @note		4.4.0
 ****************************************************************************/
#ifndef CHM_PHYSICALCH_H
#define CHM_PHYSICALCH_H

#include "Std_Types.h"
#include "VCan.h"


/*----外部変数宣言・変数名置換マクロ-----------------------------------------*/

typedef struct chm_phy_resource_info{
	uint8 ipid;
	uint8 controllerid;
} CHM_PHY_RESOURCE_INFO;	/* 物理リソース情報 */

/* マイコン CANコントローラID数 */
#define CHM_CONTROLLER_NUM		(16U)

/* 搭載IP情報 */
#define CHM_PHY_IP_NUM			(3U)
#define CHM_PHY_IP0ID			(0U)
#define CHM_PHY_IP1ID			(1U)
#define CHM_PHY_IP2ID			(2U)

/* 各IP搭載CANコントローラ数 */
#define CHM_PHY_IP0_CONTROLLER_NUM	(8U)
#define CHM_PHY_IP1_CONTROLLER_NUM	(8U)

/* VCANコントローラ数 */
#define CHM_VCAN_CONTROLLER_NUM	(1U)

/* ETHコントローラ数 */
#define CHM_ETH_CONTROLLER_NUM	(1U)

/* チャネル別IP番号 */
#define CHM_PHY_IPID_G2M2_FD_BUS		(CHM_PHY_IP0ID)
#define CHM_PHY_IPID_G2M1_FD_BUS		(CHM_PHY_IP0ID)
#define CHM_PHY_IPID_G5M_FD_BUS		(CHM_PHY_IP0ID)
#define CHM_PHY_IPID_VCAN_BUS		(CHM_PHY_IP0ID)

/* チャネル別コントローラ番号 */
#define CHM_PHY_CONTROLLERID_G2M2_FD_BUS	(3U)
#define CHM_PHY_CONTROLLERID_G2M1_FD_BUS	(5U)
#define CHM_PHY_CONTROLLERID_G5M_FD_BUS	(7U)
#define CHM_PHY_CONTROLLERID_VCAN_BUS	((0x0U) | (VCAN_VIRTUAL_CH))


#endif /* CHM_PHYSICALCH_H */ 
