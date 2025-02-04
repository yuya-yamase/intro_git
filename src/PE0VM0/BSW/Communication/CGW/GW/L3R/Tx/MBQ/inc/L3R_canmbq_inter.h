/****************************************************************************/
/*  Copyright 2013-2014 DENSO Corporation. All rights reserved.             */
/****************************************************************************/
/*【ファイル名】    L3R_canmbq_inter.h                                      */
/*【モジュール名】  CAN MBOXキュー制御                                      */
/*【機能】          CAN MBOXキュー制御のカスタマイズ要素(共通内部向け)      */
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.11.13	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(識別子に関するルール適合)
 *		SPF R1.3.1 CS(zf3)対応
 *		XSS_MPC560x V1.0.0alpha対応
 *	@version	1.0.1	2013.12.20	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(空マクロの呼出し)
 *		MBQ初期化契機追加(バススリープ/ウェイクアップ時)
 *	@version	1.0.2	2014.03.03	@author	K.Hirakata(NCOS)
 *		送信要求クリアAPI対応
 *	@version	1.0.3	2017.3.3	@author	Y.Katayama(FSI)
 *		19PFに対応しインクルードファイルの変更 
 *	@version	2.0.0	2018.05.23	@author	T.Yamamura(FSI)
 *		可変化対応 ソースファイルをconfから移動
 *	@version	3.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#ifndef L3R_CANMBQ_INTER_H
#define L3R_CANMBQ_INTER_H


/*---------------------------------------------------------------------------*/
/* ここはユーザが自環境に合わせるために各種システムの設定をする。            */
/*---------------------------------------------------------------------------*/
#include	"Std_Types.h"
#include	"Os.h"

#include	"CS_Can.h"
#include	"CS_Can_Cfg.h"

#include	"L3R.h"
#include	"L3R_Fail.h"
/*---------------------------------------------------------------------------*/

#define CANMBQ_LITTLEENDIAN  (1U)
#define CANMBQ_BIGENDIAN     (2U)
#define CANMBQ_ENDIAN        (CANMBQ_BIGENDIAN)


#define CANMBQ_LSBFIRST      (1U)
#define CANMBQ_MSBFIRST      (2U)
#define CANMBQ_BITORDER      (CANMBQ_MSBFIRST)


#define CANMBQ_BASETIME_MS     (5U)
#define CANMBQ_DRVBASETIME_MS  (1U)


#define CANMBQ_TLOCK		(400U/CANMBQ_BASETIME_MS)


#define CANMBQ_pushDI_AREA1()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA1()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA2()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA2()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA3()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA3()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA4()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA4()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA5()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA5()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA6()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA6()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA7()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA7()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA8()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA8()	ResumeAllInterrupts()
#define CANMBQ_pushDI_AREA9()	SuspendAllInterrupts()
#define CANMBQ_popEI_AREA9()	ResumeAllInterrupts()


#define CANMBQ_CANCELSEARCH		(5U)


#endif /* L3R_CANMBQ_INTER_H */
