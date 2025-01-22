/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_ReprogCanMessage.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・タイプ宣言定義をGW_RTR_config.hへ移動
 * 													・L3R_DiagCanMessage.hのインクルード削除  
 * 			v2.01	2018/05/23	T.Yamamura(FSI)		可変化対応
 * 													・タイプ宣言定義をGW_RTR_config.hから移動
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_REPROGCANMESSAGE_H
#define	L3R_REPROGCANMESSAGE_H


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
extern CanMessageFuncList ReprogCanMessage_funcList[];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
#define	Create_ReprogCanMessage(name, canid, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) \
	Create_DiagCanMessageElements(name, (ch0), (ch1), (ch2), (ch3), (ch4), (ch5), (ch6), (ch7), (ch8), (ch9), (ch10), (ch11), (ch12), (ch13), (ch14), (ch15));	\
	L3R_PRAGMA_SECTION_CONST_START																	\
	static CanMessage (name) = {New_DiagCanMessage(name, (canid), &ReprogCanMessage_funcList[0])}	\
	L3R_PRAGMA_SECTION_CONST_STOP

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
/**
 * @fn			ReprogCanMessage_Init()
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define ReprogCanMessage_Init() CanMessage_Init()


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern uint16 ReprogCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_REPROGCANMESSAGE_H */
