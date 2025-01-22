/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_main.h										*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			CAN MBOXキュー制御 処理									*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.05.09	@author	K.Hirakata(NCOS)
 *		MPC 5604C対応 MBOXキュー制御として新規作成
 *	@version	1.0.1	2013.06.13	@author	K.Hirakata(NCOS)
 *		送信キャンセル関数のプロトタイプ宣言を追加
 *	@version	1.0.2	2013.12.20	@author	K.Hirakata(NCOS)
 *		MBQ初期化契機追加(バススリープ/ウェイクアップ時)
 *	@version	1.0.3	2014.08.08	@author	K.Yokooka (FSI)
 *		課題No.17816対応 送信要求関数に引数 DelIndexNum追加
 *      戻り値 CANMBQ_FULL→CANMBQ_FULL_OKにラベル変更
 *	@version	1.0.4	2017.03.03	@author	Y.Katayama(FSI)
 *		19PF向けの型定義に変更
 *	@version	2.0.0	2018.05.16	@author	T.Yamamura(FSI)
 *		可変化対応 canmbq_auto_cfg.hのインクルード変更
 *	@version	2.0.1	2018.05.22	@author	A.Yasui(FSI)
 *		コーディング規約対応(オブジェクト不変の修正2)
 *	@version	2.0.2	2018.05.30	@author	K.Ito(FSI)
 *		帯域制限削除対応
 *	@version	2.0.3	2018.10.25	@author	T.Yamamura(FSI)
 *		コードレベルアップ対応(オブジェクト不変)
 *	@version	3.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#ifndef L3R_CANMBQ_MAIN_H
#define L3R_CANMBQ_MAIN_H

#include "L3R_CommonBuffer.h"

#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_tx.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define CANMBQ_SET						(1U)
#define CANMBQ_CLR						(0U)

#define CANMBQ_OK						(1U)
#define CANMBQ_NG						(0U)
#define CANMBQ_FULL_OK					(2U)
#define CANMBQ_INVALID					(0xffU)


/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"
extern TxChannel *const txChannelArray[CANMBQ_CHMAX];
#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
void CANMBQ_Omed_Er(void);
void CANMBQ_DriverTask(void);

void CANMBQ_ClrSendLockFlg(void);
void CANMBQ_SetSendLockFlg(uint8 ch);
uint8 CANMBQ_GetSendLockFlg(uint8 ch);

uint8 CANMBQ_Sendreq_GWmsg(uint8 ch, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell);

void CANMBQ_ClrSndQueAll(void);
uint8 CANMBQ_ClrSndQueAllWithBuffer(uint8 ch);
uint8 CANMBQ_ClrSndQue(uint8 queId);
void CANMBQ_SendcancelAll(CommonBuffer *pCommonBuffer);
void CANMBQ_SendReq_Tx(uint8 ch, CommonBuffer* pCommonBuffer);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#endif	/* L3R_CANMBQ_MAIN_H */
