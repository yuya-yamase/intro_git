/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_FilterCanMessage.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2023/06/07	T.Matsushita(FSI)		新規作成
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_FILTERCANMESSAGE_H
#define	L3R_FILTERCANMESSAGE_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_DiagCanMessage.h"

#include "L3R_Section.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern CanMessageFuncList FilterCanMessage_funcList[];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
#define	Create_FilterCanMessage(name, canid, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) \
	Create_DiagCanMessageElements(name, (ch0), (ch1), (ch2), (ch3), (ch4), (ch5), (ch6), (ch7), (ch8), (ch9), (ch10), (ch11), (ch12), (ch13), (ch14), (ch15));	\
	L3R_PRAGMA_SECTION_CONST_START																\
	static CanMessage (name) = {New_DiagCanMessage(name, (canid), &FilterCanMessage_funcList[0])}	\
	L3R_PRAGMA_SECTION_CONST_STOP

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
/**
 * @fn			FilterCanMessage_Init()
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define FilterCanMessage_Init() CanMessage_Init()


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern void FilterCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId);
extern uint16 FilterCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_FILTERCANMESSAGE_H */
