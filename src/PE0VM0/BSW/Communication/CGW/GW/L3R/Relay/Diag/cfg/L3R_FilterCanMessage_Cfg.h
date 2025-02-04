/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	    L3R_FilterCanMessage_Cfg.h
 * @brief	    
 * @details	    
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
 * @note            templates/L3R_FilterCanMessage_CfgH.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_FILTERCANMESSAGE_CFG_H
#define	L3R_FILTERCANMESSAGE_CFG_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"
#include "L3R_CanMessage.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
enum {
	L3R_FILTER_TYPE_A =  (0U), 	/* フィルタTypeA */
	L3R_FILTER_TYPE_B,		 	/* フィルタTypeB */
	L3R_FILTER_TYPE_C,		 	/* フィルタTypeC */
	L3R_FILTER_TYPE_MAX,		/* フィルタTypeMAX */
	L3R_FILTER_TYPE_NONE = (0xFF)	/* フィルタTypeNONE */
};

#define L3R_DLCFILTER_CHECKVAL		(8U)	/* DLCフィルタチェック値 */
#define L3R_FILTERFUNC_MAX			(3U)	/* フィルタファンクション最大数 */

/* DLCフィルタ対象チャンネル指定 */
#define L3R_DLCFILTER_CH_BIT	(CHM_NWTYPE_DLC | CHM_NWTYPE_DCM | CHM_NWTYPE_AS)
/* SIDフィルタ対象チャンネル指定 */
#define L3R_SIDFILTER_CH_BIT	(CHM_NWTYPE_DLC | CHM_NWTYPE_DCM | CHM_NWTYPE_AS)

/* フィルタ判定結果 */
#define L3R_RTN_FILTER_PHB			(0U)	/* 中継禁止 */
#define L3R_RTN_FILTER_PMT			(1U)	/* 中継許可 */

typedef uint8 (*const FilterFunc)(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId);

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern 	const uint8 FilterCanMessageNormalArray[L3R_SEARCH_MAX];
extern	const uint8 FilterCanMessageReprogArray[L3R_SEARCH_MAX]; 
extern	const uint8 FilterCanMessageThatchamArray[L3R_SEARCH_MAX];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern	FilterFunc * const FilterType_FuncListTable[L3R_FILTER_TYPE_MAX]; 
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern	const uint8 FilterType_FuncListTable_Num[L3R_FILTER_TYPE_MAX];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_FILTERCANMESSAGE_CFG_H */
