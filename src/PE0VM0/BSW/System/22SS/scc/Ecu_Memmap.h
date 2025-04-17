/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_Memmap.h
 * [Module]			Memmap
 * [Function]		Sample memmap for SS callout
 * [Notes]			None
 ****************************************************************************/
#ifndef ECU_MEMMAP_H
#define ECU_MEMMAP_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#if ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__)))
#else
#include <Std_Types.h>
#include <SS.h>

#include <Ecu_Internal.h>
#endif /* ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__))) */

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define ECU_SAMPLE_SECTION_TEXT   ".ecu_code"
#define ECU_SAMPLE_SECTION_RODATA ".ecu_const"
#define ECU_SAMPLE_SECTION_BSS    ".ecu_nvar_sw"

/*----------------------------------------------------------------------------
 *		Sections
 *--------------------------------------------------------------------------*/
/* for assembly language */
#if ((defined(__ghs__)) && (defined(__LANGUAGE_ASM__)))

/* no definition */

/* for C language */
#else

#pragma ghs section text   = ECU_SAMPLE_SECTION_TEXT
#pragma ghs section rodata = ECU_SAMPLE_SECTION_RODATA
#pragma ghs section bss    = ECU_SAMPLE_SECTION_BSS

extern uint32 __ghsbegin_data[];
extern uint32 __ghsbegin_romdata[];
extern uint32 DATA_SIZE[];

extern uint32 __ghsbegin_ecu_nvar_top[];
extern uint32 __ghsbegin_ecu_nvar_bottom[];
extern uint32 ECU_NVAR_SIZE[];

extern uint32 __ghsbegin_MEM_SEC_STA_RAM_LOC_APPL[];
extern uint32 __ghsbegin_MEM_SEC_END_RAM_LOC_APPL[];
extern uint32 LOC_RAM_SIZE[];

extern uint32 __ghsbegin_cdd_ram_top[];
extern uint32 __ghsbegin_cdd_ram_bottom[];
extern uint32 CDD_RAM_SIZE[];

extern uint32 __ghsbegin_MEM_SEC_ADDR_STA_BSS_MS[];
extern uint32 __ghsbegin_MEM_SEC_ADDR_END_BSS_MS[];
extern uint32 NVMC_RAM_SIZE[];

extern uint32 __ghsbegin_bsw_e_nvar_top[];
extern uint32 __ghsbegin_bsw_e_nvar_bottom[];
extern uint32 BSW_E_NVAR_SIZE[];

extern uint32 __ghsbegin_bsw_n_nvar_top[];
extern uint32 __ghsbegin_bsw_n_nvar_bottom[];
extern uint32 BSW_N_NVAR_SIZE[];

extern uint32 __ghsbegin_bsw_e_rvar_top[];
extern uint32 __ghsbegin_bsw_e_rvar_bottom[];
extern uint32 BSW_E_RVAR_SIZE[];

extern uint32 __ghsbegin_bsw_e_rvar_withval_top[];
extern uint32 __ghsbegin_bsw_e_rvar_ival_top[];
extern uint32 BSW_E_RVAR_WITHVAL_SIZE[];

extern uint32 __ghsbegin_bsw_n_rvar_top[];
extern uint32 __ghsbegin_bsw_n_rvar_bottom[];
extern uint32 BSW_N_RVAR_SIZE[];

extern uint32 __ghsbegin_bsw_n_rvar_withval_top[];
extern uint32 __ghsbegin_bsw_n_rvar_ival_top[];
extern uint32 BSW_N_RVAR_WITHVAL_SIZE[];

extern uint32 __ghsbegin_bsw_n_nvar_withval_top[];
extern uint32 __ghsbegin_bsw_n_nvar_ival_top[];
extern uint32 BSW_N_NVAR_WITHVAL_SIZE[];

extern uint32 __ghsbegin_bsw_e_nvar_withval_top[];
extern uint32 __ghsbegin_bsw_e_nvar_ival_top[];
extern uint32 BSW_E_NVAR_WITHVAL_SIZE[];

extern uint32 __ghsbegin_ecu_n_bvar_top[];
extern uint32 __ghsbegin_bsw_ecu_n_bvar_bottom[];
extern uint32 ECU_N_BVAR_SIZE[];

extern uint32 __ghsbegin_iohw_ram_top[];
extern uint32 __ghsbegin_iohw_ram_bottom[];
extern uint32 IOHW_RAM_SIZE[];

extern uint32 __ghsbegin_MEM_SEC_STA_BACK_BSW[];
extern uint32 __ghsbegin_MEM_SEC_END_BACK_BSW[];
extern uint32 BSS_BACK_BSW_SIZE[];

extern uint32 __ghsbegin_MEM_SEC_STA_BACK_APPL[];
extern uint32 __ghsbegin_MEM_SEC_END_BACK_APPL[];
extern uint32 BSS_BACK_SIZE[];

#if (SS_USE_LWH == SS_LWH_EXIST)
extern uint32 __ghsbegin_ecu_n_nvarLR_top[];
extern uint32 __ghsbegin_ecu_n_nvarLR_bottom[];
extern uint32 ECU_N_NVAR_LR_SIZE[];

extern uint32 __ghsbegin_app_n_nvarLR_withval[];
extern uint32 __ghsbegin_app_n_nvarLR_ival[];
extern uint32 APP_N_NVARLR_WITHVAL_SIZE[];
#endif

#if (SS_USE_LWH == SS_LWH_NONE)
extern uint32 __ghsbegin_ecu_n_nvarLR0_top[];
extern uint32 __ghsbegin_ecu_n_nvarLR0_bottom[];
extern uint32 ECU_N_NVAR_LR0_SIZE[];

#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 __ghsbegin_ecu_n_nvarLR1_top[];
extern uint32 __ghsbegin_ecu_n_nvarLR1_bottom[];
extern uint32 ECU_N_NVAR_LR1_SIZE[];
#endif // SS_USE_CORE_COUNT >= 2u

#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 __ghsbegin_ecu_n_nvarLR2_top[];
extern uint32 __ghsbegin_ecu_n_nvarLR2_bottom[];
extern uint32 ECU_N_NVAR_LR2_SIZE[];
#endif // SS_USE_CORE_COUNT >= 3u

#if (SS_USE_CORE_COUNT >= 4u)
extern uint32 __ghsbegin_ecu_n_nvarLR3_top[];
extern uint32 __ghsbegin_ecu_n_nvarLR3_bottom[];
extern uint32 ECU_N_NVAR_LR3_SIZE[];
#endif // SS_USE_CORE_COUNT >= 4u

extern uint32 __ghsbegin_app_n_nvarLR0_withval[];
extern uint32 __ghsbegin_app_n_nvarLR0_ival[];
extern uint32 APP_N_NVARLR0_WITHVAL_SIZE[];

#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 __ghsbegin_app_n_nvarLR1_withval[];
extern uint32 __ghsbegin_app_n_nvarLR1_ival[];
extern uint32 APP_N_NVARLR1_WITHVAL_SIZE[];
#endif // SS_USE_CORE_COUNT >= 2u

#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 __ghsbegin_app_n_nvarLR2_withval[];
extern uint32 __ghsbegin_app_n_nvarLR2_ival[];
extern uint32 APP_N_NVARLR2_WITHVAL_SIZE[];
#endif // SS_USE_CORE_COUNT >= 3u

#if (SS_USE_CORE_COUNT >= 4u)
extern uint32 __ghsbegin_app_n_nvarLR3_withval[];
extern uint32 __ghsbegin_app_n_nvarLR3_ival[];
extern uint32 APP_N_NVARLR3_WITHVAL_SIZE[];
#endif // SS_USE_CORE_COUNT >= 4u
#endif // SS_USE_LWH == SS_LWH_NONE

#if (ECU_TARGETDEVICE == ECU_U2A16)
extern uint32 __ghsbegin_ecu_n_nvarCR0_top[];
extern uint32 __ghsbegin_ecu_n_nvarCR0_bottom[];
extern uint32 ECU_N_NVAR_CR0_SIZE[];

extern uint32 __ghsbegin_ecu_n_nvarCR1_top[];
extern uint32 __ghsbegin_ecu_n_nvarCR1_bottom[];
extern uint32 ECU_N_NVAR_CR1_SIZE[];

extern uint32 __ghsbegin_app_n_nvarCR0_withval[];
extern uint32 __ghsbegin_app_n_nvarCR0_ival[];
extern uint32 APP_N_NVARCR0_WITHVAL_SIZE[];

extern uint32 __ghsbegin_app_n_nvarCR1_withval[];
extern uint32 __ghsbegin_app_n_nvarCR1_ival[];
extern uint32 APP_N_NVARCR1_WITHVAL_SIZE[];
#endif

#if (SS_USE_LWH == SS_LWH_NONE)
extern uint32 __ghsbegin_mcu_evar_withival[];
extern uint32 __ghsbegin_mcu_evar_ival[];
extern uint32 MCU_EVAR_WITHIVAL_SIZE[];
#endif

#if (SS_USE_UP == STD_ON)
extern uint32 __ghsbegin_os_stack_top[];
extern uint32 __ghsbegin_os_stack_bottom[];
extern uint32 __ghsbegin_os_var_top[];
extern uint32 __ghsbegin_os_var_bottom[];
extern uint32 OS_STACK_SIZE[];

#if (SS_USE_CORE_COUNT >= 2u)
extern uint32 __ghsbegin_os_stack1_top[];
extern uint32 __ghsbegin_os_stack1_bottom[];
extern uint32 OS_STACK1_SIZE[];
#endif // SS_USE_CORE_COUNT >= 2u

#if (SS_USE_CORE_COUNT >= 3u)
extern uint32 __ghsbegin_os_stack2_top[];
extern uint32 __ghsbegin_os_stack2_bottom[];
extern uint32 OS_STACK2_SIZE[];
#endif // SS_USE_CORE_COUNT >= 3u

#if (SS_USE_CORE_COUNT >= 4u)
extern uint32 __ghsbegin_os_stack3_top[];
extern uint32 __ghsbegin_os_stack3_bottom[];
extern uint32 OS_STACK3_SIZE[];
#endif // SS_USE_CORE_COUNT >= 4u
#else  // SS_USE_UP == STD_ON
extern uint32 __ghsbegin_ecu_nvar_lram_top[];
extern uint32 __ghsbegin_ecu_nvar_lram_bottom[];
extern uint32 ECU_NVAR_LRAM_SIZE[];

extern uint32 __ghsbegin_data_lram[];
extern uint32 __ghsbegin_romdata_lram[];
extern uint32 DATA_LRAM_SIZE[];

extern uint32 __ghsbegin_ecu_nvar_global_top[];
extern uint32 ECU_NVAR_GLOBAL_SIZE[];

extern uint32 __ghsbegin_data_vcc[];
extern uint32 __ghsbegin_romdata_vcc[];
extern uint32 DATA_VCC_SIZE[];
#endif // SS_USE_UP == STD_ON

#endif
#endif /* ECU_MEMMAP_H */
