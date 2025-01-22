/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_st.h											*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			Header file for driver status process					*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.05.09	@author	K.Hirakata(NCOS)
 *		MPC 5604C対応 MBOXキュー制御として新規作成
 *	@version	1.0.1	2013.11.11	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(識別子に関するルール適合)
 *	@version	1.0.2	2017.03.03	@author	Y.Katayama(FSI)
 *		19PF向けの型定義に変更
 *		CH数の追加対応(8CH対応)
 *	@version	1.0.3	2018.10.25	@author	T.Yamamura(FSI)
 *		コードレベルアップ対応(オブジェクト不変)
 *	@version	2.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#ifndef L3R_CANMBQ_ST_H
#define L3R_CANMBQ_ST_H


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
void CANMBQ_SndLock(uint8 ch);
uint8 CANMBQ_GetMode(uint8 ch);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


#define CANMBQ_COMM			(1U)
#define CANMBQ_NOCOMM		(0U)


#endif	/* L3R_CANMBQ_ST_H */
