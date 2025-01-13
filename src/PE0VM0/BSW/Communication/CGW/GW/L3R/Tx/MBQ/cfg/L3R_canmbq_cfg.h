/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	    L3R_canmbq_cfg.h
 * @brief	    CAN MBOXキュー制御 
 * @attention	CAN MBOXキュー制御のカスタマイズ要素(システム外部向け)
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
 * @note            templates/L3R_canmbq_cfgH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#ifndef L3R_CANMBQ_CFG_H
#define L3R_CANMBQ_CFG_H


/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_ChCnvtr.h"
#include "CHM_LogicCh.h"

/*---------------------------------------------------------------------------*/

/* 論理CH数(使用するMBQ数) */
#define CANMBQ_CHMAX       CHM_LOG_CAN_CH_NUM	/* MBQはL3Rドメインだが、L3R仮想CANを想定し、L3RではなくChMasterのチャネル数を直接引き込む */

#define CANMBQ_CH0         (0U)
#define CANMBQ_CH1         (1U)
#define CANMBQ_CH2         (2U)
#define CANMBQ_CH3         (3U)

#define CANMBQ_QUE0         (0U)
#define CANMBQ_QUE1         (1U)
#define CANMBQ_QUE2         (2U)
#define CANMBQ_QUE3         (3U)

/* フレーム種別のパターン数 */
#define CANMBQ_QUE_NUM		(6U)

/* ID毎バッファ使用時のダイアグバス送信用のQueId設定 */
#define CANMBQ_QUEID_CTRL_0		(CANMBQ_QUE0)		/* ID毎バッファからの動的ルーティング用MBQのQueID */
#define CANMBQ_QUEID_CTRL_1		(CANMBQ_QUE0)		/* ID毎バッファからの動的ルーティング用MBQのQueID */
#define CANMBQ_QUEID_CTRL_2		(CANMBQ_QUE0)		/* ID毎バッファからの動的ルーティング用MBQのQueID */

/* 共有バッファ使用時のQueId設定 */
#define CANMBQ_QUEID_DIAG		(CANMBQ_QUE3)		/* ダイアグGWフレーム用MBQのQueID */

/* 動的バッファ使用時のQueId設定 */
#define CANMBQ_QUEID_DYNAMC		(CANMBQ_QUE1)		/* 動的ルーティング用MBQのQueID */

/* 送信キュー数は、Ch毎ではなく全Ch共通の設定のみ可能 */
#define CANMBQ_QUENUM	(4U)

/* CANIP数 */
#define CANMBQ_TXREQ_CANIP_NUM		CHM_PHY_IP_NUM

/* CANドライバのMBOXインデックス最大値 */
#define CANMBQ_MBOX_IDX_MAX_IP0		(4U)		/* CANIP0 */
#define CANMBQ_MBOX_IDX_MAX_IP1		(4U)		/* CANIP1 */
#define CANMBQ_MBOX_IDX_MAX_VCAN	(4U)		/* VCAN   */

/* 仮想CAN ユーザ送信用MBOX 開始番号 */
#define CANMBQ_VMBOX_UTXOFFSET	(2U)

/* 仮想CAN 送信要求制限回数 */
#define CANMBQ_VCAN_TX_LIMIT	(20U)

/*---プロトタイプ宣言------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern const uint8 MBQ_SendPriority2MboxId_Tbl[CANMBQ_TXREQ_CANIP_NUM][CANMBQ_QUENUM];
extern const uint8 MBQ_MboxId2SendPriority_Tbl_IP0[CANMBQ_MBOX_IDX_MAX_IP0];
extern const uint8 MBQ_MboxId2SendPriority_Tbl_IP1[CANMBQ_MBOX_IDX_MAX_IP1];
extern const uint8 MBQ_MboxId2SendPriority_Tbl_VCAN[CANMBQ_MBOX_IDX_MAX_VCAN];
extern const uint8 MBQ_QueIdTbl[CANMBQ_QUE_NUM][CANMBQ_CHMAX];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#endif /* L3R_CANMBQ_CFG_H */
