/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_Router.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・Router_SendGWIdOverWrite()共通化(引数、処理変更）
 * 													・Router_SendGWId()マクロ→関数化(L3R_Router.cへ移動）
 * 			v2.01	2018/05/22	A.Yasui(FSI)		コーディング規約対応(オブジェクト不変の修正2)
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/09/19	Y.Katayama(FSI)		フェール発生CH情報セット・クリア関数マクロ追加
 *													Router_MainTask()のプロトタイプ宣言追加
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 * 			v5.00	2018/12/25	T.Yamamura(FSI)		新アーキテクチャSBR仕様適合対応
 * 													制御データ中継モード対応
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_ROUTER_H
#define	L3R_ROUTER_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_CommonBuffer.h"
#include "L3R_Fail.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
typedef const struct routerTag Router;
typedef struct routerFieldsTag RouterFields;
typedef uint8(*const QuickWakeupFunc)(CommonBuffer *pCommBuffer, uint8 first);
typedef void(*const OverWriteFunc)(Router *self, CommonBuffer **ppCommBuffer);
typedef void(*const ClearChFunc)(Router *self, uint8 ch);
typedef void(*const SendReqFunc)(CommonBuffer *pCommonBuffer);
typedef uint16(*const GetSendProtocolFunc)(CommonBuffer *pCommonBuffer, uint16 gwId, uint8 rxCh);
typedef void(*const CancelSendQueFunc)(void);

/* Router型 */
struct routerFieldsTag {
	uint16 writePointer;	/* Writeポインタ    */
	uint16 readPointer;		/* Readポインタ     */
	uint16 enquePointer;	/* Enqueポインタ    */
	uint16 readCount;		/* Readデータ件数   */
	uint16 enqueCount;		/* Enqueデータ件数  */
};

struct routerTag {
	QuickWakeupFunc QuickWakeup;
	OverWriteFunc OverWrite;
	GetSendProtocolFunc GetSendProtocol;
	CancelSendQueFunc CancelSendQue;
	CommonBuffer *const *pBuffer;
	uint16 size;
	RouterFields *pFields;
};

#define Create_RouterElements(name)
#define	New_Router(name, className, size, pFields)							\
	className##_QuickWakeup,												\
	className##_OverWrite,													\
	className##_GetSendProtocol,											\
	className##_CancelSendQue,												\
	name##Buffer,															\
	(size),																	\
	(pFields)


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
extern void Router_Init(Router *self);
extern void Router_SendGWIdOverWrite(uint8 ch, CommonBuffer *const pCommonBuffer);
extern void Router_SendGWIdOverWrite_Tx(uint8 ch, CommonBuffer *const pCommonBuffer);
extern void Router_SendGWId(uint8 ch, CommonBuffer *const pCommonBuffer);
extern void Router_SendGWId_Tx(uint8 ch, CommonBuffer *const pCommonBuffer);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#if (CHM_LOG_ETH_CH_NUM != 0)
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern void Router_CEConvAdapter_SendReq(uint8 ch, CommonBuffer *pCommonBuffer);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern const uint8 L3R_Log_To_ContainerTable[CHM_LOG_ALL_CH_NUM];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"
#endif

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_ROUTER_H */
