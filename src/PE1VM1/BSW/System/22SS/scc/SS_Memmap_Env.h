/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Memmap_Env.h
 * [Module]			System
 * [Function]		System Enviroment
 * [Notes]			None
 ****************************************************************************/
#ifndef SS_MEMMAP_ENV_H
#define SS_MEMMAP_ENV_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Memmap_Cfg.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Sections
 *--------------------------------------------------------------------------*/
#pragma ghs section text = ".ss_code"

#if (SS_MEMMAP_ACCESS_SDA == STD_ON)
#pragma ghs section rosdata = ".ss_const"
#elif (SS_MEMMAP_ACCESS_SDA == STD_OFF)
#pragma ghs section rodata = ".ss_const"
#else
#error invalid SS_MEMMAP_ACCESS_SDA
#endif

#if (SS_MEMMAP_ACCESS_SDA == STD_ON)
#pragma ghs section sbss = ".ss_nvar_sw"
#elif (SS_MEMMAP_ACCESS_SDA == STD_OFF)
#pragma ghs section bss = ".ss_nvar_sw"
#else
#error invalid SS_MEMMAP_ACCESS_SDA
#endif

/* for PE common */
extern uint32 __ghsbegin_ss_nvar_e_top[];
extern uint32 __ghsbegin_ss_nvar_e_bottom[];
extern uint32 SS_NVAR_E_SIZE[];
extern uint32 __ghsbegin_ss_rvar_e_top[];
extern uint32 __ghsbegin_ss_rvar_e_bottom[];
extern uint32 SS_RVAR_E_SIZE[];

/* for STACK of every PE */
extern uint32 __ghsbegin_ss_stack[];
extern uint32 __ghsend_ss_stack[];

#define SS_ptSTACKADDR_0 (__ghsbegin_ss_stack)

#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 __ghsbegin_ss_stack1[];
extern uint32 __ghsend_ss_stack1[];

#define SS_ptSTACKADDR_1 (__ghsbegin_ss_stack1)

#endif
#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 __ghsbegin_ss_stack2[];
extern uint32 __ghsend_ss_stack2[];

#define SS_ptSTACKADDR_2 (__ghsbegin_ss_stack2)

#endif
#if (SS_USE_CORE_COUNT >= 4u)
extern uint32 __ghsbegin_ss_stack3[];
extern uint32 __ghsend_ss_stack3[];

#define SS_ptSTACKADDR_3 (__ghsbegin_ss_stack3)
#endif

/* for STACK_BOUNDARYCHECK of every PE */
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)

extern uint32 __ghsbegin_ss_stack_top[];
extern uint32 __ghsbegin_ss_stack_bottom[];
extern uint32 __ghssize_ss_stack_top[];
extern uint32 __ghssize_ss_stack_bottom[];

#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 __ghsbegin_ss_stack1_top[];
extern uint32 __ghsbegin_ss_stack1_bottom[];
extern uint32 __ghssize_ss_stack1_top[];
extern uint32 __ghssize_ss_stack1_bottom[];
#endif
#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 __ghsbegin_ss_stack2_top[];
extern uint32 __ghsbegin_ss_stack2_bottom[];
extern uint32 __ghssize_ss_stack2_top[];
extern uint32 __ghssize_ss_stack2_bottom[];
#endif
#if (SS_USE_CORE_COUNT >= 4u)
extern uint32 __ghsbegin_ss_stack3_top[];
extern uint32 __ghsbegin_ss_stack3_bottom[];
extern uint32 __ghssize_ss_stack3_top[];
extern uint32 __ghssize_ss_stack3_bottom[];
#endif

#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

#endif /* SS_MEMMAP_ENV_H */
