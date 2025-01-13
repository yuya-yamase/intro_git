/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_IdRouter.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・IdRouter_SendReq()の引数名称を変更
 * 			v2.01	2018/05/30	A.Yasui(FSI)		コーディング規約対応(inline関数化対応)
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v5.00	2018/12/25	T.Yamamura(FSI)		新アーキテクチャSBR仕様適合対応
 * 													制御データ中継モード対応
 *			v6.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_IDROUTER_H
#define	L3R_IDROUTER_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_CommonBuffer.h"
#include "L3R_config.h"

#include "L3R_Router.h"

#include "L3R_Section.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
#define	Create_IdRouterElements(name)										\
	/* Create_RouterElements(name) */
#define	New_IdRouter(name, className, size)									\
	New_Router(name, className, (size), NULL_PTR)
#define	Create_IdRouter(name, className, size)								\
	/* Create_IdRouterElements(name); */									\
	L3R_PRAGMA_SECTION_CONST_START											\
	Router (name) = {New_IdRouter(name, className, (size))}					\
	L3R_PRAGMA_SECTION_CONST_STOP


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
/**
 * @fn			IdRouter_Init(self)
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param[in]	self	自身へのポインタ
 * @return		なし
 * @attention	割り込み禁止で呼び出される
 * @note		なし
 */
#define IdRouter_Init(self) Router_Init(self)


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern CommonBuffer *IdRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 searchId, uint8 fd);
extern void IdRouter_SendReq(CommonBuffer *pCommonBuffer);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern void ( *const L3R_SendReqIdFuncTbl[CHM_LOG_ALL_CH_NUM])(uint8 ch, CommonBuffer *const pCommonBuffer);
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_IDROUTER_H */
