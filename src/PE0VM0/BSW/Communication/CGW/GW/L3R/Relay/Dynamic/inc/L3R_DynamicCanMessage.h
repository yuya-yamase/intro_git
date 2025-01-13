/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_DynamicCanMessage.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v3.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_DYNAMICCANMESSAGE_H
#define	L3R_DYNAMICCANMESSAGE_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "L3R_CommonBuffer.h"

#include "L3R_CanMessage.h"

#include "L3R_Section.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern CanMessageFuncList DynamicCanMessage_funcList[];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

#define	Create_DynamicCanMessageElements(name)								\
	Create_CanMessageBackUpElements(name);									\
	L3R_PRAGMA_SECTION_NBVA_ZI_START        								\
	static CommonBuffer *(name##CommonBuffer)           					\
	L3R_PRAGMA_SECTION_NBVA_ZI_STOP
#define	New_DynamicCanMessage(name, canid, canMessageFuncList, GwId)		\
	New_CanMessage(name, (canid), (canMessageFuncList), name##CommonBuffer, (GwId))
	
#define	Create_DynamicCanMessage(name, canid)								\
	Create_DynamicCanMessageElements(name);									\
	L3R_PRAGMA_SECTION_CONST_START											\
	static CanMessage (name) = {New_DynamicCanMessage(name, (canid), &DynamicCanMessage_funcList[0], &CanMessage_aGwId[0])}	\
	L3R_PRAGMA_SECTION_CONST_STOP

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
/**
 * @fn			DynamicCanMessage_Init()
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define DynamicCanMessage_Init() CanMessage_Init()


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern uint16 DynamicCanMessage_GetGwId(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 searchId);
extern void DynamicCanMessage_RelayData(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_DYNAMICCANMESSAGE_H */
