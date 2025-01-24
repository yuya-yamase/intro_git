/****************************************************************************/
/*  Copyright 2013-2014  DENSO Corporation. All rights reserved.            */
/****************************************************************************/
/*【ファイル名】	L3R_canmbq_common.h										*/
/*【モジュール名】	CAN MBOXキュー制御										*/
/*【機能】			CAN MBOXキュー制御 共通のヘッダファイル					*/
/*                                                                          */
/****************************************************************************/
/*	変更履歴
 *	@version	1.0.0	2013.05.09	@author	K.Hirakata(NCOS)
 *		MPC 5604C対応 MBOXキュー制御として新規作成
 *	@version	1.0.1	2013.11.12	@author	K.Hirakata(NCOS)
 *		MISRA2004対応(識別子に関するルール適合)
 *	@version	1.0.2	2017.03.03	@author	Y.Katayama(FSI)
 *		19PF対応 CH数の追加対応(8CH対応) 
 *	@version	2.0.0	2018.05.23	@author	T.Yamamura(FSI)
 *		可変化対応 インクルード記載変更
 *	@version	3.0.0	2018.11.21	@author	Y.Katayama(FSI)
 *		中継改善(オブジェクト不変)
*/
#ifndef L3R_CANMBQ_COMMON_H
#define L3R_CANMBQ_COMMON_H

#include "L3R_canmbq_cfg.h"
#include "L3R_canmbq_inter.h"



#if !defined(CANMBQ_ENDIAN)
#error [DECSTER Configuration Error!!! (Endian)]
#elif ((CANMBQ_ENDIAN != CANMBQ_LITTLEENDIAN) && (CANMBQ_ENDIAN != CANMBQ_BIGENDIAN))
#error [DECSTER Configuration Error!!! (Endian)]
#endif

#if !defined(CANMBQ_BITORDER)
#error [DECSTER Configuration Error!!! (Bit Order)]
#elif ((CANMBQ_BITORDER != CANMBQ_LSBFIRST) && (CANMBQ_BITORDER != CANMBQ_MSBFIRST))
#error [DECSTER Configuration Error!!! (Bit Order)]
#endif

#if ((CANMBQ_CHMAX < 1) || (CANMBQ_CHMAX > 16))
#error [DECSTER Configuration Error!!! (CAN ch)]
#endif

#ifndef CANMBQ_CH0
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH0)]
#endif
#if (CANMBQ_CHMAX >= 2)
#ifndef CANMBQ_CH1
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH1)]
#endif
#endif
#if (CANMBQ_CHMAX >= 3)
#ifndef CANMBQ_CH2
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH2)]
#endif
#endif
#if (CANMBQ_CHMAX >= 4)
#ifndef CANMBQ_CH3
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH3)]
#endif
#endif
#if (CANMBQ_CHMAX >= 5)
#ifndef CANMBQ_CH4
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH4)]
#endif
#endif
#if (CANMBQ_CHMAX >= 6)
#ifndef CANMBQ_CH5
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH5)]
#endif
#endif
#if (CANMBQ_CHMAX >= 7)
#ifndef CANMBQ_CH6
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH6)]
#endif
#endif
#if (CANMBQ_CHMAX >= 8)
#ifndef CANMBQ_CH7
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH7)]
#endif
#endif
#if (CANMBQ_CHMAX >= 9)
#ifndef CANMBQ_CH8
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH8)]
#endif
#endif
#if (CANMBQ_CHMAX >= 10)
#ifndef CANMBQ_CH9
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH9)]
#endif
#endif
#if (CANMBQ_CHMAX >= 11)
#ifndef CANMBQ_CH10
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH10)]
#endif
#endif
#if (CANMBQ_CHMAX >= 12)
#ifndef CANMBQ_CH11
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH11)]
#endif
#endif
#if (CANMBQ_CHMAX >= 13)
#ifndef CANMBQ_CH12
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH12)]
#endif
#endif
#if (CANMBQ_CHMAX >= 14)
#ifndef CANMBQ_CH13
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH13)]
#endif
#endif
#if (CANMBQ_CHMAX >= 15)
#ifndef CANMBQ_CH14
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH14)]
#endif
#endif
#if (CANMBQ_CHMAX == 16)
#ifndef CANMBQ_CH15
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH15)]
#endif
#endif

#ifdef CANMBQ_CH0
#if (CANMBQ_CH0 != 0)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH0)]
#endif
#endif
#ifdef CANMBQ_CH1
#if (CANMBQ_CH1 != 1)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH1)]
#endif
#endif
#ifdef CANMBQ_CH2
#if (CANMBQ_CH2 != 2)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH2)]
#endif
#endif
#ifdef CANMBQ_CH3
#if (CANMBQ_CH3 != 3)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH3)]
#endif
#endif
#ifdef CANMBQ_CH4
#if (CANMBQ_CH4 != 4)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH4)]
#endif
#endif
#ifdef CANMBQ_CH5
#if (CANMBQ_CH5 != 5)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH5)]
#endif
#endif
#ifdef CANMBQ_CH6
#if (CANMBQ_CH6 != 6)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH6)]
#endif
#endif
#ifdef CANMBQ_CH7
#if (CANMBQ_CH7 != 7)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH7)]
#endif
#endif
#ifdef CANMBQ_CH8
#if (CANMBQ_CH8 != 8)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH8)]
#endif
#endif
#ifdef CANMBQ_CH9
#if (CANMBQ_CH9 != 9)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH9)]
#endif
#endif
#ifdef CANMBQ_CH10
#if (CANMBQ_CH10 != 10)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH10)]
#endif
#endif
#ifdef CANMBQ_CH11
#if (CANMBQ_CH11 != 11)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH11)]
#endif
#endif
#ifdef CANMBQ_CH12
#if (CANMBQ_CH12 != 12)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH12)]
#endif
#endif
#ifdef CANMBQ_CH13
#if (CANMBQ_CH13 != 13)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH13)]
#endif
#endif
#ifdef CANMBQ_CH14
#if (CANMBQ_CH14 != 14)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH14)]
#endif
#endif
#ifdef CANMBQ_CH15
#if (CANMBQ_CH15 != 15)
#error [DECSTER Configuration Error!!! (DECSTAR conf. ERROR! CANMBQ_CH15)]
#endif
#endif

#if ((CANMBQ_QUENUM < 4) || (CANMBQ_QUENUM > 15))
#error [DECSTER Configuration Error!!! (CANMBQ_QUENUM)]
#endif

#endif /* L3R_CANMBQ_COMMON_H */
