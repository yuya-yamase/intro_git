/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_CanMessage.h
 * @brief	CanMessage制御
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * @date	v1.10	2018/02/16	T.Yamamura(FSI)		CANIDフィルタ対応
 *													関数L3R_Ids_SetDiagBusErrInfコール追加
 * 			v1.11	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v1.12	2018/05/22	A.Yasui(FSI)		コーディング規約対応(オブジェクト不変の修正2)
 * 			v1.13	2018/06/11	T.Yamamura(FSI)		QAC対応 DEFAULT_MASKの定義移動
 * 			v1.14	2018/06/19	K.Ito(FSI)			帯域制限追加対応
 * 			v1.15	2018/07/20	K.Ito(FSI)			A-Busフィルタ削除対応
 * 			v1.16	2018/07/31	K.Ito(FSI)			QAC対応
 * 			v1.17	2018/08/06	K.Ito(FSI)			DLC9以上対応
 * 			v1.18	2018/08/29	Y.Katayama(FSI)		課題1054895対応
 * 			v1.19	2018/08/29	T.Yamamura(FSI)		CanMessage_EnterNormalModeの外部公開廃止
 * 			v2.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v2.01	2018/10/26	T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 *													・定数マクロ化
 *			v3.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v3.01	2019/03/24	K.Ito(FSI)			[IntegNo.1099809]
 *													[570B-Phase9] 課題 制御データ中継モード対応によるTMC対応
 *			v3.02	2019/05/17	K.Ito(FSI)			[IntegNo.1111499]
 *													[570B-Phase9] CAN300復帰処理削除
 *			v4.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_CANMESSAGE_H
#define	L3R_CANMESSAGE_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "CHM_LogicCh.h"

#include "L3R_BandLimit.h"
#include "L3R_CommonBuffer.h"

#include "L3R_Section.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define NULL_GWID						(0U)
#define FILTERERR_GWID					(0xFFFEU)
#define DYNAMIC_GWID					(0xFFFFU)

#define DEFAULT_MASK					(0x0000U)

#define L3R_CTRLFRM_STARTID				(0x010U)
#define L3R_CTRLFRM_ENDID				(0x6FFU)
#define L3R_DIAGFRM_STARTID				(0x700U)
#define L3R_DIAGFRM_ENDID				(0x7FFU)
#define L3R_EXD_DIAGFRM_STARTID			(0x18DA0000U)
#define L3R_EXD_DIAGFRM_ENDID			(0x18DBFFFFU)

#define EVT_BIT_CTRLFRM_MTR_SUSPEND					((L3R_ON) << 2U)


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
typedef const struct canMessageTag CanMessage;
typedef const struct canMessageFuncListTag CanMessageFuncList;
typedef uint16 (*const GetGwIdFunc)(CanMessage *self, uint8 rxCh, uint8 dlc, const uint8* Data, uint16 search);
typedef void (*const RelayDataFunc)(CanMessage *self, uint8 fd, uint8 dlc, const uint8* Data, uint16 gwId, uint8 rxCh, uint16 search);
typedef void (*CallBackFunc)(Std_ReturnType result);
typedef const struct CanMessageArraySetTag CanMessageArraySet;

struct CanMessageArraySetTag {
	uint32 canid_s;
	CanMessage *pClass;
};
struct canMessageFuncListTag {
	GetGwIdFunc GetGwId;
	RelayDataFunc RelayData;
};
struct canMessageTag {
	CanMessageFuncList *funcList;
	uint32 canid;
	uint16 *pSndPrtclBit;
	CommonBuffer **ppCommonBuffer;
	const uint16 *GwId;
};
#define	Create_CanMessageElements(name) 									\
	L3R_PRAGMA_SECTION_NBVA_ZI_START										\
	static uint16 name##SndPrtclBit  										\
	L3R_PRAGMA_SECTION_NBVA_ZI_STOP
#define	Create_CanMessageBackUpElements(name) 								\
	L3R_PRAGMA_SECTION_BUVA_ZI_START     									\
	static uint16 name##SndPrtclBit		    								\
	L3R_PRAGMA_SECTION_BUVA_ZI_STOP
#define	New_CanMessage(name, canid, canMessageFuncList, pBuffer, GwId)		\
	(canMessageFuncList),													\
	(canid),																\
	&(name##SndPrtclBit),													\
	&(pBuffer),																\
	(GwId)
#define	New_CanMessageFixed(name, canid, canMessageFuncList, GwId)			\
	(canMessageFuncList),													\
	(canid),																\
	&CanMessage_sndPrtclBit,												\
	NULL_PTR,																\
	(GwId)
#define	New_CanMessageNull(name, canid, canMessageFuncList)					\
	(canMessageFuncList),													\
	(canid),																\
	&CanMessage_sndPrtclBit,												\
	NULL_PTR,																\
	&CanMessage_aGwId[0]


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"
extern uint16 CanMessage_monitorMask;
#define GW_L3R_STOP_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
extern uint16 CanMessage_sndPrtclBit;
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
#define GW_L3R_START_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"
extern uint16 CanMessage_requestState;
#define GW_L3R_STOP_SEC_BUVA_ZI
#include "GW_L3R_Memmap.h"
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
extern uint8 CanMessage_CancelEvtState;
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
extern const uint8 *pFilterCanMessageArrayNow;
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern const uint16 CanMessage_aGwId[CHM_LOG_ALL_CH_NUM];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void CanMessage_SidErrorHandler(void)
 * @brief		SIDフィルタエラー通知
 * @details		SIDフィルタエラー情報を通知する
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CanMessage_SidErrorHandler(void) __attribute__((always_inline,unused));
static inline void CanMessage_SidErrorHandler(void)
{
}

/**
 * @fn			void CanMessage_DlcErrorHandler(void)
 * @brief		DLCフィルタエラー通知
 * @details		DLCフィルタエラー情報を通知する
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CanMessage_DlcErrorHandler(void) __attribute__((always_inline,unused));
static inline void CanMessage_DlcErrorHandler(void)
{
}

/**
 * @fn			void CanMessage_DiagBusErrorHandler(uint8 RxCh, uint32 canid)
 * @brief		ダイアグバス受信エラー通知
 * @details		ダイアグバス受信エラー情報を通知する
 * @param[in]	RxCh	受信CH番号
 * @param[in]	canid	CANID
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CanMessage_DiagBusErrorHandler(uint8 RxCh, uint32 canid) __attribute__((always_inline,unused));
static inline void CanMessage_DiagBusErrorHandler(uint8 RxCh, uint32 canid)
{
}

/**
 * @fn			void CanMessage_UnKnownErrorHandler(void)
 * @brief		未定義CANIDエラー通知
 * @details		未定義CANIDエラー情報を通知する
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CanMessage_UnKnownErrorHandler(void) __attribute__((always_inline,unused));
static inline void CanMessage_UnKnownErrorHandler(void)
{
}
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#include "L3R_AutoCanMessage.h"							/* 以下の関数マクロのため、この位置でのインクルードが必要 */

/**
 * @fn			CanMessage_SetSendProtocol(canId, sndPrtclBit)
 * @brief		送信先の設定
 * @details		送信先の設定を行う
 * @param[in]	canId			CANID
 * @param[in]	sndPrtclBit		送信先
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define CanMessage_SetSendProtocol(searchId, sndPrtclBit)							\
do{																			\
	*(pCanMessageArray[searchId].pClass->pSndPrtclBit) = (sndPrtclBit);	/* どのモードでも、通常モードのCanMessageArrayに設定 */ \
} while(0)

/**
 * @fn			CanMessage_AddSendProtocol(canId, sndPrtclBit)
 * @brief		送信先の追加
 * @details		送信先の追加を行う
 * @param[in]	canId			CANID
 * @param[in]	sndPrtclBit		送信先
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define CanMessage_AddSendProtocol(searchId, sndPrtclBit)							\
do{																			\
	*(pCanMessageArray[searchId].pClass->pSndPrtclBit) |= (sndPrtclBit);	/* どのモードでも、通常モードのCanMessageArrayに設定 */ \
} while(0)

/**
 * @fn			CanMessage_RemoveSendProtocol(canId, sndPrtclBit)
 * @brief		送信先の削除
 * @details		送信先の削除を行う
 * @param[in]	canId			CANID
 * @param[in]	sndPrtclBit		送信先
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define CanMessage_RemoveSendProtocol(searchId, sndPrtclBit)						\
do{																			\
	*(pCanMessageArray[searchId].pClass->pSndPrtclBit) &= ~(sndPrtclBit);	/* どのモードでも、通常モードのCanMessageArrayに設定 */ \
} while(0)

/**
 * @fn			CanMessage_GetSendProtocol(canId)
 * @brief		送信先の取得
 * @details		送信先の取得を行う
 * @param[in]	canId			CANID
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define CanMessage_GetSendProtocol(searchId)									\
	(*(pCanMessageArray[searchId].pClass->pSndPrtclBit) & CanMessage_monitorMask)	/* どのモードでも、通常モードのCanMessageArrayから取得 */


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"

extern void CanMessage_Init(void);
extern void CanMessage_WakeUpInit(void);
extern void CanMessage_MainInDrvTask(void);
extern void CanMessage_Task(void);
extern void CanMessage_Receive(uint8 rxCh, uint32 canid32, uint8 dlc, uint8* Data, uint16 searchId);
extern void CanMessage_ModeSet(void);
extern void CanMessage_EnterReprogMode(void);
extern void CanMessage_ExitReprogMode(void);
extern void CanMessage_EnterThatchamMode(void);
extern void CanMessage_ExitThatchamMode(void);
extern void CanMessage_ActivateMonitor(void);
extern void CanMessage_InActivateMonitor(void);
extern void CanMessage_InActivateMonitorByRTR(void);
extern Std_ReturnType CanMessage_SetProtocolAll(const uint32 CanId[], uint16 length, uint16 sndPrtclBit, uint16 startPos, uint16 endPos, CallBackFunc func);

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_CANMESSAGE_H */
