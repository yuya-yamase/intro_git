/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_QueRouter.h
 * @brief	受信FIFO制御
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/30	A.Yasui(FSI)		コーディング規約対応(inline関数化対応)
 * 			v1.02	2018.05.30	K.Ito(FSI)			帯域制限削除対応
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_QUEROUTER_H
#define	L3R_QUEROUTER_H


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
#define	Create_QueRouterElements(name)											\
	/* Create_RouterElements(name); */											\
	L3R_PRAGMA_SECTION_NBVA_ZI_START											\
	static RouterFields name##Fields;											\
	L3R_PRAGMA_SECTION_NBVA_ZI_STOP
#define	New_QueRouter(name, className, size, pFields)							\
	New_Router(name, className, (size), (pFields))
#define	Create_QueRouter(name, className, size)									\
	Create_QueRouterElements(name)												\
	L3R_PRAGMA_SECTION_CONST_START												\
	Router (name) = {New_QueRouter(name, className, (size), &(name##Fields))}	\
	L3R_PRAGMA_SECTION_CONST_STOP

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern void QueRouter_Init(Router *self);
extern CommonBuffer *QueRouter_RelayData(Router *self, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId, uint8 fd);
extern CommonBuffer *QueRouter_SendData(Router *self, CommonBuffer *pCommonBuffer);
extern CommonBuffer *QueRouter_RelayDataByBuffer(Router *self, CommonBuffer *pCommonBuffer, uint32 canId, uint8 dlc, const uint8* Data, uint16 gwId, uint16 searchId);
extern void QueRouter_SendReq(CommonBuffer *pCommonBuffer);
extern void QueRouter_DriverTask(Router *self);
extern void QueRouter_MainTask(Router *self);
extern void QueRouter_ClearCh(Router *self, uint8 ch);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern void ( *const L3R_SendReqQueFuncTbl[CHM_LOG_ALL_CH_NUM])(uint8 ch, CommonBuffer *const pCommonBuffer);
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_QUEROUTER_H */
