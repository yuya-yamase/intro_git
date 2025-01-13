/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_tx.h											*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			Header file for driver transmission process				*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.05.10	@author	K.Hirakata(NCOS)
 *		MPC 5604C対応 MBOXキュー制御として新規作成
 *	@version	1.0.1	2013.11.11	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(識別子に関するルール適合)
 *	@version	1.0.2	2013.12.20	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(ルール17.4)
 *	@version	1.0.3	2017.03.03	@author	Y.Katayama(FSI)
 *		19PF向けの型定義に変更
 *		CH数の追加対応(8CH対応)
 *	@version	1.0.4	2018.05.22	@author	A.Yasui(FSI)
 *		コーディング規約対応(オブジェクト不変の修正2)
 *	@version	1.0.5	2018.05.30	@author	K.Ito(FSI)
 *		帯域制限削除対応
 *	@version	2.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#ifndef L3R_CANMBQ_TX_H
#define L3R_CANMBQ_TX_H

#include "Can.h"
#include "Std_Types.h"

#include "L3R_CommonBuffer.h"

/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
typedef const struct txChannelTag TxChannel;
typedef const struct sendQueTag SendQue;
typedef uint8 (*const CanIpTxReqFunc)(uint8 controllerid, uint8 mboxid, CanMsgType *rp);
typedef uint8 (*const CanMbpSendReq)(TxChannel* const self, SendQue* const pSendQue);
typedef void (*const CanDrvTaskTx)(TxChannel* self);

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
void TxChannel_ClrSndQueAll(TxChannel *self);
void TxChannel_ClrSndQueAllWithBuffer(TxChannel *self);
void TxChannel_ClrSndQue(TxChannel *self, uint8 queId);

uint8 TxChannel_SendReqCan(TxChannel* const self, SendQue* const pSendQue);
uint8 TxChannel_SendReqVCan(TxChannel* const self, SendQue* const pSendQue);

void TxChannel_ClrTxCnt(void);
void TxChannel_TxFin(TxChannel *self, uint8 queId);
uint8 TxChannel_WriteSendQue(TxChannel *self, CommonBuffer *pCommonBuffer, CommonBuffer** ppBufferToDell);
void TxChannel_SendReq_Tx(TxChannel *self, CommonBuffer* pCommonBuffer);

void TxChannel_Omed_SndLock(TxChannel *self);
void TxChannel_DrvTask_Tx_Can(TxChannel *self);
void TxChannel_DrvTask_Tx_VCan(TxChannel *self);

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/
typedef struct sendQueFieldsTag {
	volatile uint16 readPoint;
	volatile uint16 writePoint;
	volatile uint16 count;
	volatile uint8 sendingFlg;
	volatile uint8 lockTimer;
} SendQueFields;

struct sendQueTag {
	uint16 size;
	uint16 retryCount;
	const uint8 *pMboxId;
	SendQueFields *pFields;
	CommonBuffer **ppCommonBuffer;
} ;

struct txChannelTag
{
	uint8 logicCh;
	uint8 controllerId;
	SendQue *pSendQue;
	CanIpTxReqFunc CanIpTxReq;
	CanMbpSendReq  SendReq;
	CanDrvTaskTx drvTaskTx;
};

#endif	/* L3R_CANMBQ_TX_H */
