/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Boot_cfg.inc
 * [Module]			Boot
 * [Function]		Boot
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_BOOT_CFG_INC
#define SS_BOOT_CFG_INC

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/













#include <Ecu_Internal.h>

/*----------------------------------------------------------------------------
 *		Imports
 *--------------------------------------------------------------------------*/
	.import _Ecu_Int_destroyRamEcc
	.import _Ecu_Int_enableEcc
	.import _Ecu_Int_initPeri
	.import _Ecu_Int_init

/*----------------------------------------------------------------------------
 *		Macros
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_preInitCallout(void)
 * [Function]	Pre-Init Callout
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/

.macro _SS_Boot_destroyRamEcc
#if (ECU_USE_RAMECCDESTROY == ECU_USE)
    jarl _Ecu_Int_destroyRamEcc, lp
#endif
.endm

.macro _SS_Boot_enableEcc
    /* TPpr_mov__u4g_SS_TEST_orgStackBackup_r25_Ecu_ISeq_ResetBoot */
    /* TPpr_st_w_sp_0_r25_Ecu_ISeq_ResetBoot */
    /* TPpr_mov__test_stack_end_sp_Ecu_ISeq_ResetBoot */
    
    /* TPpr_mov__u4g_SS_TEST_orgStackBackup_r25_Ecu_ISeq_ResetBoot */
    /* TPpr_ld_w_0_r25_sp_Ecu_ISeq_ResetBoot */
    /* TPpr_pushsp_lp-lp_Ecu_ISeq_ResetBoot */
    /* TPpr_jarl_TPsp_Ecu_ISeq_ResetBoot_GetResetFactor_lp_Ecu_ISeq_ResetBoot */
    /* TPpr_popsp_lp-lp_Ecu_ISeq_ResetBoot */
#if (SS_USE_LWH == SS_LWH_NONE)
    jarl _Ecu_Int_enableEcc, lp
#endif
.endm

.macro _SS_Boot_initIntPeri
#if (SS_USE_LWH == SS_LWH_NONE)
    jarl _Ecu_Int_initPeri, lp
#endif
.endm

.macro _SS_Boot_initIntPE0
    jarl _Ecu_Int_init, lp
.endm

#if (SS_USE_CORE_COUNT >= 2u)
.macro _SS_Boot_initIntPE1
    jarl _Ecu_Int_init, lp
.endm

#endif
#if (SS_USE_CORE_COUNT >= 3u)
.macro _SS_Boot_initIntPE2
    jarl _Ecu_Int_init, lp
.endm

#endif
#if (SS_USE_CORE_COUNT >= 4u)
.macro _SS_Boot_initIntPE3
    jarl _Ecu_Int_init, lp
.endm

#endif


#endif /* SS_BOOT_CFG_INC */
