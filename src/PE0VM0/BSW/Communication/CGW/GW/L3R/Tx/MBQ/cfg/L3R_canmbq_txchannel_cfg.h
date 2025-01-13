/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_txchannel_cfg.h											*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			Header file for driver transmission process				*/
/*                                                                          */
/****************************************************************************/
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
 * @note            templates/L3R_canmbq_txchannel_cfgH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/
#ifndef L3R_CANMBQ_TXCHANNEL_CFG_H
#define L3R_CANMBQ_TXCHANNEL_CFG_H

/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "Can.h"
#include "CHM_LogicCh.h"
#include "CHM_PhysicalCh.h"

#include "L3R_canmbq_auto_drvcfg_0.h"
#include "L3R_canmbq_auto_drvcfg_1.h"
#include "L3R_canmbq_auto_drvcfg_2.h"
#include "L3R_canmbq_auto_drvcfg_3.h"
#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_main.h"
#include "L3R_canmbq_tx.h"
#include "L3R_CommonBuffer.h"
#include "L3R_Section.h"

/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
#define	Create_TxChannelElements(name, ch, chName)		\
	L3R_PRAGMA_SECTION_NBVA_ZI_START								\
	static SendQueFields name##SendQueFields0;						\
	static SendQueFields name##SendQueFields1;						\
	static SendQueFields name##SendQueFields2;						\
	static SendQueFields name##SendQueFields3;						\
	static CommonBuffer *SndQue0_##ch[CANMBQ_QUE0_TXQUESIZE_##ch];	\
	static CommonBuffer *SndQue1_##ch[CANMBQ_QUE1_TXQUESIZE_##ch];	\
	static CommonBuffer *SndQue2_##ch[CANMBQ_QUE2_TXQUESIZE_##ch];	\
	static CommonBuffer *SndQue3_##ch[CANMBQ_QUE3_TXQUESIZE_##ch];	\
	L3R_PRAGMA_SECTION_NBVA_ZI_STOP									\
	L3R_PRAGMA_SECTION_CONST_START									\
	static SendQue name##SendQue[CANMBQ_QUENUM] = {					\
		{CANMBQ_QUE0_TXQUESIZE_##ch, CANMBQ_QUE0_TXRETRY_##ch, &(MBQ_SendPriority2MboxId_Tbl[CHM_PHY_IPID_##chName][0]), &(name##SendQueFields0), SndQue0_##ch},\
		{CANMBQ_QUE1_TXQUESIZE_##ch, CANMBQ_QUE1_TXRETRY_##ch, &(MBQ_SendPriority2MboxId_Tbl[CHM_PHY_IPID_##chName][1]), &(name##SendQueFields1), SndQue1_##ch},\
		{CANMBQ_QUE2_TXQUESIZE_##ch, CANMBQ_QUE2_TXRETRY_##ch, &(MBQ_SendPriority2MboxId_Tbl[CHM_PHY_IPID_##chName][2]), &(name##SendQueFields2), SndQue2_##ch},\
		{CANMBQ_QUE3_TXQUESIZE_##ch, CANMBQ_QUE3_TXRETRY_##ch, &(MBQ_SendPriority2MboxId_Tbl[CHM_PHY_IPID_##chName][3]), &(name##SendQueFields3), SndQue3_##ch}\
	};																\
	L3R_PRAGMA_SECTION_CONST_STOP
#define	New_TxChannel(name, chName, CanIpTxReq, sendReq, drvTaskTx)	\
	CHM_LOG_CH_##chName,											\
	CHM_PHY_CONTROLLERID_##chName,									\
	name##SendQue,													\
	(CanIpTxReq),													\
	(sendReq),														\
	(drvTaskTx)
#define	Create_TxChannel(name, ch, chName, CanIpTxReq, sendReq, drvTaskTx)	\
	Create_TxChannelElements(name, ch, chName)					\
	L3R_PRAGMA_SECTION_CONST_START								\
	static TxChannel (name) = {New_TxChannel(name, chName, (CanIpTxReq), sendReq, drvTaskTx)}	\
	L3R_PRAGMA_SECTION_CONST_STOP

#endif	/* L3R_CANMBQ_TXCHANNEL_CFG_H */
