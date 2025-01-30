/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Middleware Library
 * Module   : CRI Common Header for RH850D1
 * File     : cri_xpts_rh850d1.h
 * Date     : 2017-06-06
 * Version  : 1.00
 *
 ****************************************************************************/

#if !defined(CRI_INCL_CRI_XPTS_RH850D1_H)
#define CRI_INCL_CRI_XPTS_RH850D1_H

/*****************************************************************************
 * 基本データ型宣言
 *****************************************************************************/

#if !defined(CRI_TYPEDEF_CriUint8)
#define CRI_TYPEDEF_CriUint8
typedef unsigned char			CriUint8;		/* 符号なし１バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriSint8)
#define CRI_TYPEDEF_CriSint8
typedef signed char				CriSint8;		/* 符号つき１バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriUint16)
#define CRI_TYPEDEF_CriUint16
typedef unsigned short			CriUint16;		/* 符号なし２バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriSint16)
#define CRI_TYPEDEF_CriSint16
typedef signed short			CriSint16;		/* 符号つき２バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriUint32)
#define CRI_TYPEDEF_CriUint32
typedef unsigned long			CriUint32;		/* 符号なし４バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriSint32)
#define CRI_TYPEDEF_CriSint32
typedef signed long				CriSint32;		/* 符号つき４バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriUint64)
#define CRI_TYPEDEF_CriUint64
typedef unsigned long long		CriUint64;		/* 符号なし８バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriSint64)
#define CRI_TYPEDEF_CriSint64
typedef signed long long		CriSint64;		/* 符号つき８バイト整数 */
#endif

#if !defined(CRI_TYPEDEF_CriUint128)
#define CRI_TYPEDEF_CriUint128
typedef struct {								/* 符号なし16バイト整数 */
	CriUint64			h;						/* 上位64ビット */
	CriUint64			l;						/* 下位64ビット */
} CriUint128;
#endif

#if !defined(CRI_TYPEDEF_CriSint128)
#define CRI_TYPEDEF_CriSint128
typedef struct {								/* 符号つき16バイト整数 */
	CriSint64	h;								/* 上位64ビット */
	CriUint64	l;								/* 下位64ビット */
} CriSint128;
#endif

#if !defined(CRI_TYPEDEF_CriFloat16)
#define CRI_TYPEDEF_CriFloat16
typedef signed short			CriFloat16;		/* ２バイト実数 */
#endif

#if !defined(CRI_TYPEDEF_CriFloat32)
#define CRI_TYPEDEF_CriFloat32
typedef float					CriFloat32;		/* ４バイト実数 */
#endif

#if !defined(CRI_TYPEDEF_CriFloat64)
#define CRI_TYPEDEF_CriFloat64
typedef double					CriFloat64;		/* ８バイト実数 */
#endif

#if !defined(CRI_TYPEDEF_CriFixed32)
#define CRI_TYPEDEF_CriFixed32
typedef signed int				CriFixed32;		/* 固定小数点32ビット */
#endif

#if !defined(CRI_TYPEDEF_CriBool)
#define CRI_TYPEDEF_CriBool
typedef CriSint32				CriBool;		/* 論理型（論理定数を値にとる） */
#endif

#if !defined(CRI_TYPEDEF_CriChar8)
#define CRI_TYPEDEF_CriChar8
typedef char					CriChar8;		/* 文字型 */
#endif

/*****************************************************************************
 * ポインタを格納可能な整数型
 *****************************************************************************/
#if !defined(CRI_TYPEDEF_CriSintPtr)
#define CRI_TYPEDEF_CriSintPtr
typedef signed long			CriSintPtr; /* 4 bytes pointer */
#endif

#if !defined(CRI_TYPEDEF_CriUintPtr)
#define CRI_TYPEDEF_CriUintPtr
typedef unsigned long		CriUintPtr; /* 4 bytes pointer */
#endif

/*****************************************************************************
 * 呼び出し規約
 *****************************************************************************/

#if !defined(CRIAPI)
#define CRIAPI
#endif

#endif	/* CRI_INCL_CRI_XPTS_RH850D1_H */

/* end of file */
