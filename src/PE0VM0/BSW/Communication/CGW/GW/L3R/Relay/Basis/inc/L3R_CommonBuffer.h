/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file	L3R_CommonBuffer.h
 * @brief	
 * @details	
 * @note	なし
 * @date	v1.00	2018/01/20	T.Totsuka(FSI)		新規作成
 * 			v1.01	2018/05/11	A.Yasui(FSI)		中継のCHとPRTCL_BITの命名規則明確化レベルアップ
 * 			v2.00	2018/05/16	T.Yamamura(FSI)		可変化対応
 * 													・GW_RTR_config.h→CHM_LogicCh.h変更
 * 			v2.01	2018/05/22	A.Yasui(FSI)		コーディング規約対応(オブジェクト不変の修正2)
 * 			v2.02	2018/05/30	A.Yasui(FSI)		コーディング規約対応(inline関数化対応)
 * 			v2.03	2018/07/25	T.Yamamura(FSI)		処理負荷改善対応
 * 													・Bit位置取得方法を変更
 * 			v3.00	2018/08/24	K.Ito(FSI)			クラス型統一
 * 			v3.01	2018/10/25	T.Yamamura(FSI) 	コードレベルアップ対応(オブジェクト不変)
 *			v4.00	2018/11/21	Y.Katayama(FSI)		中継改善(オブジェクト不変）
 *			v4.01	2019/10/09	T.Yamamura(FSI)		[570B-Phase10][IntegNo.1124328]処理負荷削減対応
 * 													・CommonBuffer_SendFinNotify()削除
 *			v5.00	2020/12/07	T.Yamamura(FSI)		[Post19CY] 29Bit対応 
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#ifndef	L3R_COMMONBUFFER_H
#define	L3R_COMMONBUFFER_H


/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_Common.h"
#include "L3R_config.h"
#include "L3R_LIB.h"

#include "CHM_LogicCh.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
typedef const struct commonBufferTag CommonBuffer;
typedef const struct commBufferFuncListTag CommonBufferFuncList;
typedef struct commonBufferFieldsTag CommonBufferFields;
typedef void(*const InitBufferFunc)(CommonBuffer *self);
typedef uint8(*const GetGWDataFunc)(CommonBuffer *self, uint8 ch, uint8 *pDlc, uint32 *pCanid32, uint8 **ppData);

struct commBufferFuncListTag {
	InitBufferFunc Init;
	GetGWDataFunc GetGWData;
};
/* 共有ダイアグバッファヘッダ要素 */
struct commonBufferFieldsTag {
	uint32 rcvTime;						/* 受信時間(ms) */
	uint8 length;						/* データ長 */
	uint8 fd;							/* FD受信：0:CAN、1:FD */
	uint32 canId;						/* CAN-ID(uint32) */
	uint16 sndPrtclBit;					/* 送信ステータス */
	uint16 sndPrtclReqBit;				/* 送信要求 */
	uint16 searchId;					/* CAN-ID探索位置 */
};
/* GWバッファ(ROM) */
struct commonBufferTag{
	CommonBufferFuncList *funcList;
	uint8 *Data;						/* データのアドレス */
	uint8 frameClass;					/* フレーム種別 */
	uint8 maxDataSize;					/* プロトコル上の最大データ長 */
	CommonBufferFields *pFields;		/* フィールドへのポインタ */
	uint16 defSndPrtclBit;					/* デフォルト送信プロトコル情報 */
	uint8 dlc;							/* DLC */
	uint16 transCycle;					/* 送信周期 */
};


/*--------------------------------------------------------------------------*/
/*		関数マクロ															*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void CommonBuffer_SetSndStatusCh(CommonBuffer *const self, uint8 ch)
 * @brief		送信ステータスセット処理
 * @details		GW-IDの送信Ch毎の送信ステータスをセットする
 * @param[in]	self	自身へのポインタ
 * @param[in]	ch		送信Ch
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_SetSndStatusCh(CommonBuffer *const self, uint8 ch) __attribute__((always_inline,unused));
static inline void CommonBuffer_SetSndStatusCh(CommonBuffer *const self, uint8 ch)
{
	(self)->pFields->sndPrtclBit |= (((uint16)L3R_ON) << ch);
}

/**
 * @fn			void CommonBuffer_SetSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
 * @brief		送信ステータスセット処理
 * @details		GW-IDの送信Ch毎の送信ステータスをセットする
 * @param[in]	self			自身へのポインタ
 * @param[in]	targetPrtclBit	送信Chビット情報
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_SetSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit) __attribute__((always_inline,unused));
static inline void CommonBuffer_SetSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
{
	(self)->pFields->sndPrtclBit |= (targetPrtclBit);
}

/**
 * @fn			void CommonBuffer_ClrSndStatusCh(CommonBuffer *const self, uint8 ch)
 * @brief		送信ステータスクリア処理
 * @details		GW-IDの送信Ch毎の送信ステータスをクリアする
 * @param[in]	self	自身へのポインタ
 * @param[in]	ch		送信Ch
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_ClrSndStatusCh(CommonBuffer *const self, uint8 ch) __attribute__((always_inline,unused));
static inline void CommonBuffer_ClrSndStatusCh(CommonBuffer *const self, uint8 ch)
{
	(self)->pFields->sndPrtclBit = (uint16)(((uint32)((self)->pFields->sndPrtclBit)) & ~(((uint32)L3R_ON) << (uint32)ch));
}

/**
 * @fn			void CommonBuffer_ClrSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
 * @brief		送信ステータスクリア処理
 * @details		GW-IDの送信Ch毎の送信ステータスをクリアする
 * @param[in]	self			自身へのポインタ
 * @param[in]	targetPrtclBit	送信Chビット情報
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_ClrSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit) __attribute__((always_inline,unused));
static inline void CommonBuffer_ClrSndStatusPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
{
	(self)->pFields->sndPrtclBit &= ~(targetPrtclBit);
}

/**
 * @fn			void CommonBuffer_SetSndReqCh(CommonBuffer *const self, uint8 ch)
 * @brief		送信要求セット処理
 * @details		GW-IDの送信Ch毎の送信要求をセットする
 * @param[in]	self	自身へのポインタ
 * @param[in]	ch		送信Ch
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_SetSndReqCh(CommonBuffer *const self, uint8 ch) __attribute__((always_inline,unused));
static inline void CommonBuffer_SetSndReqCh(CommonBuffer *const self, uint8 ch)
{
	(self)->pFields->sndPrtclReqBit |= (((uint16)L3R_ON) << ch);
}

/**
 * @fn			void CommonBuffer_SetSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
 * @brief		送信要求セット処理
 * @details		GW-IDの送信Ch毎の送信要求をセットする
 * @param[in]	self			自身へのポインタ
 * @param[in]	targetPrtclBit	送信Chビット情報
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_SetSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit) __attribute__((always_inline,unused));
static inline void CommonBuffer_SetSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
{
	(self)->pFields->sndPrtclReqBit |= (targetPrtclBit);
}

/**
 * @fn			void CommonBuffer_ClrSndReqCh(CommonBuffer *const self, uint8 ch)
 * @brief		送信要求クリア処理
 * @details		GW-IDの送信Ch毎の送信要求をクリアする
 * @param[in]	self	自身へのポインタ
 * @param[in]	ch		送信Ch
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_ClrSndReqCh(CommonBuffer *const self, uint8 ch) __attribute__((always_inline,unused));
static inline void CommonBuffer_ClrSndReqCh(CommonBuffer *const self, uint8 ch)
{
	(self)->pFields->sndPrtclReqBit = (uint16)(((uint32)((self)->pFields->sndPrtclReqBit)) & ~(((uint32)L3R_ON) << (uint32)ch));
}

/**
 * @fn			void CommonBuffer_ClrSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
 * @brief		送信要求クリア処理
 * @details		GW-IDの送信Ch毎の送信要求をクリアする
 * @param[in]	self			自身へのポインタ
 * @param[in]	targetPrtclBit	送信Chビット情報
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_ClrSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit) __attribute__((always_inline,unused));
static inline void CommonBuffer_ClrSndReqPrtcl(CommonBuffer *const self, uint16 targetPrtclBit)
{
	(self)->pFields->sndPrtclReqBit &= ~(targetPrtclBit);
}

/**
 * @fn			void CommonBuffer_ClrSndReqAll(CommonBuffer *const self)
 * @brief		送信要求クリア処理
 * @details		GW-IDの全送信要求をクリアする
 * @param[in]	self			自身へのポインタ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void CommonBuffer_ClrSndReqAll(CommonBuffer *const self) __attribute__((always_inline,unused));
static inline void CommonBuffer_ClrSndReqAll(CommonBuffer *const self)
{
	(self)->pFields->sndPrtclReqBit = L3R_LOG_BIT_NULL;
}

/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
extern void CommonBuffer_Init(CommonBuffer *self);
extern uint8 CommonBuffer_GetCanData(CommonBuffer *self, uint8 ch, uint8* pDlc, uint32* pCanid32, uint8** ppData);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		２重インクルード防止												*/
/*--------------------------------------------------------------------------*/
#endif	/* L3R_COMMONBUFFER_H */
