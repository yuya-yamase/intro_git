/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Definition of Library User's Header for Automotive
 * File     : cri_atom_at_def.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_at_def.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_AT_DEF_H
#define CRI_INCL_CRI_ATOM_AT_DEF_H

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(1)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(24000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(24000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif
#endif	/* CRI_INCL_CRI_ATOM_AT_DEF_H */

/* --- end of file --- */
