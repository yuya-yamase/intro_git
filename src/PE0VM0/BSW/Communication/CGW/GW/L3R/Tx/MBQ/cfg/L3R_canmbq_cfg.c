/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_canmbq_cfg.c
 * @brief		CAN MBOXキュー制御
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
 * @note            templates/L3R_canmbq_cfgC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_canmbq_main.h"
#include "L3R_canmbq_tx.h"
#include "L3R_canmbq_txchannel_cfg.h"

#include "L3R_canmbq_cfg.h"

/* 送信優先度からCANドライバMBOX番号を特定するテーブル */
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
const uint8 MBQ_SendPriority2MboxId_Tbl[CANMBQ_TXREQ_CANIP_NUM][CANMBQ_QUENUM] = {
	/* 高優先, 中優先, 低優先, 7xx(ダイアグ) */
	{ 0, 1, 2, 3 }, /* CANIP0 (ストレート接続) */
	{ 0, 1, 2, 3 }, /* CANIP1 (ストレート接続) */
	{ 2, 3, 4, 5 }  /* CANIP2 (ストレート接続) */
};

/* CANドライバMBOX番号から送信優先度を特定するテーブル(CANIP0) */
const uint8 MBQ_MboxId2SendPriority_Tbl_IP0[CANMBQ_MBOX_IDX_MAX_IP0] = {
	0, 1, 2, 3
};

/* CANドライバMBOX番号から送信優先度を特定するテーブル(CANIP1) */
const uint8 MBQ_MboxId2SendPriority_Tbl_IP1[CANMBQ_MBOX_IDX_MAX_IP1] = {
	0, 1, 2, 3
};

/* CANドライバMBOX番号から送信優先度を特定するテーブル(VCAN) */
const uint8 MBQ_MboxId2SendPriority_Tbl_VCAN[CANMBQ_MBOX_IDX_MAX_VCAN] = {
	2, 3, 4, 5
};

/* フレーム種別からから送信優先度(QueId)を設定するテーブル */
const uint8 MBQ_QueIdTbl[CANMBQ_QUE_NUM][CANMBQ_CHMAX] = { 
	{ 0,0,0,0 },		/* フレーム種別：0 */
	{ 1,1,1,1 },		/* フレーム種別：1 */
	{ 2,2,2,2 },		/* フレーム種別：2 */
	{ CANMBQ_QUEID_DIAG, CANMBQ_QUEID_DIAG, CANMBQ_QUEID_DIAG, CANMBQ_QUEID_DIAG },		/* フレーム種別：3 */
	{ CANMBQ_QUEID_DYNAMC, CANMBQ_QUEID_DYNAMC, CANMBQ_QUEID_DYNAMC, CANMBQ_QUEID_DYNAMC },		/* フレーム種別：4 */
	{ 0, 0, 0, 0 }					/* フレーム種別：5 */
 };
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

/* 外部変数定義(TxChannel) */
Create_TxChannel(txChannel0, 0, G2M2_FD_BUS, Can_TxReq, TxChannel_SendReqCan, TxChannel_DrvTask_Tx_Can);
Create_TxChannel(txChannel1, 1, G2M1_FD_BUS, Can_TxReq, TxChannel_SendReqCan, TxChannel_DrvTask_Tx_Can);
Create_TxChannel(txChannel2, 2, G5M_FD_BUS, Can_TxReq, TxChannel_SendReqCan, TxChannel_DrvTask_Tx_Can);
Create_TxChannel(txChannel3, 3, VCAN_BUS, VCan_TxReq, TxChannel_SendReqVCan, TxChannel_DrvTask_Tx_VCan);

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
TxChannel *const txChannelArray[CANMBQ_CHMAX] = {
	&txChannel0,
	&txChannel1,
	&txChannel2,
	&txChannel3
};
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
