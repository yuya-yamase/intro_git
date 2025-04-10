/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		CHM_ChCnvtr.c
 * @brief		チャネル論物変換
 * @attention	チャネル構成変更時には必ず、本情報および使用箇所に必要な修正を実施すること
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		チャンネル定義ファイル：
 * @note            チャネル設定.xlsx
 * @note		テンプレートファイル：
 * @note            templates/CHM_ChCnvtrC.tmpl
 * @note	ツールバージョン
 * @note		4.4.0
 ****************************************************************************/
#include "CHM_ChCnvtr.h"
#include "CS_Can.h"
#include "CS_Can_Cfg.h"

#define GW_CHM_START_SEC_CONST
#include "GW_CHM_Memmap.h"

/*---- 論理 ⇒ 論理 -----------------------------------------*/

/* ローカル論論変換(CANドライバ抽象化ID⇒エッジ制御ID。エッジ制御IDに論理CHを使用) */
const uint8 CHM_ChCnvtr_ControllerId_To_Log[CHM_CONTROLLER_NUM] = {
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_LOG_CH_G2M2_FD_BUS,
	CHM_CH_INVALID,
	CHM_LOG_CH_G2M1_FD_BUS,
	CHM_CH_INVALID,
	CHM_LOG_CH_G5M_FD_BUS,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID
};

/*---- 論理 ⇒ 物理 -----------------------------------------*/

/**
 * @brief	"CANIP0コントローラ番号"を"論理CH番号"に変換するテーブル
 * @note	CAN受信通知、送信完了割込で使用
 */
const uint8 CHM_ChCnvtr_PhyIp0_To_Log[CHM_PHY_IP0_CONTROLLER_NUM] = {
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_LOG_CH_G2M2_FD_BUS,
	CHM_CH_INVALID,
	CHM_LOG_CH_G2M1_FD_BUS,
	CHM_CH_INVALID,
	CHM_LOG_CH_G5M_FD_BUS
};

/**
 * @brief	"CANIP1コントローラ番号"を"論理CH番号"に変換するテーブル
 * @note	CAN受信通知、送信完了割込で使用
 */
const uint8 CHM_ChCnvtr_PhyIp1_To_Log[CHM_PHY_IP1_CONTROLLER_NUM] = {
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID,
	CHM_CH_INVALID
};

/**
 * @brief	"VCANコントローラ番号"を"論理CH番号"に変換するテーブル
 */
const uint8 CHM_ChCnvtr_VCan_To_Log[CHM_VCAN_CONTROLLER_NUM] = {
	CHM_LOG_CH_VCAN_BUS
};

/**
 * @brief	"ETHコントローラ番号"を"論理CH番号"に変換するテーブル
 */
const uint8 CHM_ChCnvtr_Eth_To_Log[CHM_ETH_CONTROLLER_NUM] = {
	CHM_CH_INVALID
};

/*---- 物理 ⇒ 論理 -----------------------------------------*/

/**
 * @brief	"論理CH"を"CANIP番号"と"IP別コントローラ番号"に変換するテーブル
 * @note	CAN送信要求で使用
 */
const CHM_PHY_RESOURCE_INFO CHM_ChConv_Log_To_Phy[CHM_LOG_CAN_CH_NUM] = {
	{ CHM_PHY_IPID_G2M2_FD_BUS,	CHM_PHY_CONTROLLERID_G2M2_FD_BUS	},
	{ CHM_PHY_IPID_G2M1_FD_BUS,	CHM_PHY_CONTROLLERID_G2M1_FD_BUS	},
	{ CHM_PHY_IPID_G5M_FD_BUS,	CHM_PHY_CONTROLLERID_G5M_FD_BUS	},
	{ CHM_PHY_IPID_VCAN_BUS,	CHM_PHY_CONTROLLERID_VCAN_BUS	}
};

/**
 * @brief	"論理CH番号"から"ネットワーク種別"を取得するテーブル
 * @note	フィルタ対象判定で使用
 */
const uint8 CHM_ChCnvtr_Log_To_NwType[CHM_LOG_CAN_CH_NUM] = {
	CHM_NWTYPE_CTRL,
	CHM_NWTYPE_CTRL,
	CHM_NWTYPE_CTRL,
	CHM_NWTYPE_NONE
};

#if ((CHM_LOG_CH_G2M1_FD_BUS != ComMConf_ComMChannel_CANFD_G2M_1_BUS) || \
     (CHM_LOG_CH_G2M2_FD_BUS != ComMConf_ComMChannel_CANFD_G2M_2_BUS) || \
     (CHM_LOG_CH_G5M_FD_BUS  != ComMConf_ComMChannel_CANFD_G5M_BUS  ) || \
     (CHM_LOG_CH_VCAN_BUS    != ComMConf_ComMChannel_VCAN_VCC_1_BUS ))
#error "CHM_LogicCh.h : CHM_LOG_CH_XXX shall be equal to ComMConf_ComMChannel_XXX."
#endif

#define GW_CHM_STOP_SEC_CONST
#include "GW_CHM_Memmap.h"
