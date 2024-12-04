/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_MemmapProtect_Env.h
 * [Module]			System
 * [Function]		System Enviroment
 * [Notes]			None
 ****************************************************************************/
#ifndef SS_MEMMAPPROTECT_ENV_H
#define SS_MEMMAPPROTECT_ENV_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <SS_Memmap_Cfg.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Sections
 *--------------------------------------------------------------------------*/
#pragma ghs section text = ".ss_code_p"

#if (SS_MEMMAP_ACCESS_SDA == STD_ON)
#pragma ghs section rosdata = ".ss_const_p"
#elif (SS_MEMMAP_ACCESS_SDA == STD_OFF)
#pragma ghs section rodata = ".ss_const_p"
#else
#error invalid SS_MEMMAP_ACCESS_SDA
#endif

#if (SS_MEMMAP_ACCESS_SDA == STD_ON)
#pragma ghs section sbss = ".ss_nvar_sw_p"
#elif (SS_MEMMAP_ACCESS_SDA == STD_OFF)
#pragma ghs section bss = ".ss_nvar_sw_p"
#else
#error invalid SS_MEMMAP_ACCESS_SDA
#endif

#endif /* SS_MEMMAPPROTECT_ENV_H */
