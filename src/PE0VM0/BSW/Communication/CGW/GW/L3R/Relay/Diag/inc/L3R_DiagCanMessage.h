/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DiagCanMessage.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・タイプ宣言定義をGW_RTR_config.hへ移動
 * 			v2.01	2018/05/23	T.Yamamura(FSI)		可変化対応
 * 													・タイプ宣言定義をGW_RTR_config.hから移動
 *													・CH数切り分け追加
 * 			v2.02   2018/05/25  T.Totsuka(FSI) 		可変化対応
 *													・CH数切り分け定義修正
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v3.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 *			v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_DIAGCANMESSAGE_H
#define	L3R_DIAGCANMESSAGE_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_CanMessage.h"
#include "L3R_config.h"

#include "L3R_Section.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern CanMessageFuncList DiagCanMessage_funcList[];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
#define	Create_DiagCanMessageElements(name, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15)	\
	/*	Create_CanMessageElements(name) */									\
	L3R_PRAGMA_SECTION_CONST_START											\
	static const uint16 name##_aGwId[CHM_LOG_ALL_CH_NUM] = CH_ARRY((ch0), (ch1), (ch2), (ch3), (ch4), (ch5), (ch6), (ch7), (ch8), (ch9), (ch10), (ch11), (ch12), (ch13), (ch14), (ch15))	\
	L3R_PRAGMA_SECTION_CONST_STOP
#define	New_DiagCanMessage(name, canid, canMessageFuncList)					\
	New_CanMessageFixed(name, (canid), (canMessageFuncList), &name##_aGwId[0])

#define	Create_DiagCanMessage(name, canid, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) \
	Create_DiagCanMessageElements(name, (ch0), (ch1), (ch2), (ch3), (ch4), (ch5), (ch6), (ch7), (ch8), (ch9), (ch10), (ch11), (ch12), (ch13), (ch14), (ch15));	\
	L3R_PRAGMA_SECTION_CONST_START											\
	static CanMessage (name) = {New_DiagCanMessage(name, (canid), &DiagCanMessage_funcList[0])}	\
	L3R_PRAGMA_SECTION_CONST_STOP

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
/**
 * @fn			DiagCanMessage_Init()
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define DiagCanMessage_Init() CanMessage_Init()


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern uint16 DiagCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId);
extern void DiagCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_DIAGCANMESSAGE_H */
