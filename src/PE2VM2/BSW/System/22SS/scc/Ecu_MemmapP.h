/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_MemmapP.h
 * [Module]			Memmap
 * [Function]		Sample memmap for SS callout
 * [Notes]			None
 ****************************************************************************/
#ifndef ECU_MEMMAPP_H
#define ECU_MEMMAPP_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#if ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__)))
#else
#include <Std_Types.h>
#endif /* ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__))) */

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define ECU_SAMPLE_PROTECTED_SECTION_TEXT   ".ecu_code_p"
#define ECU_SAMPLE_PROTECTED_SECTION_RODATA ".ecu_const_p"
#define ECU_SAMPLE_PROTECTED_SECTION_BSS    ".ecu_nvar_sw_p"

/*----------------------------------------------------------------------------
 *		Sections
 *--------------------------------------------------------------------------*/
/* for assembly language */
#if ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__)))

/* no definition */

/* for C language */
#else

#pragma ghs section text   = ECU_SAMPLE_PROTECTED_SECTION_TEXT
#pragma ghs section rodata = ECU_SAMPLE_PROTECTED_SECTION_RODATA
#pragma ghs section bss    = ECU_SAMPLE_PROTECTED_SECTION_BSS

extern uint32 __ghsbegin_ecu_nvar_p_top[];
extern uint32 __ghsbegin_ecu_nvar_p_bottom[];
extern uint32 ECU_NVAR_P_SIZE[];

#endif

#endif /* ECU_MEMMAPP_H */
