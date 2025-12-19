/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ISeq_Callout.c
 * [Module]			Initialize
 * [Function]		Initialize at change state
 * [Revision]		1.30
 * [Notes]			Customize file
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>
#include <ehvm.h>

/* MCAL */
#include "gpt_drv_ost.h"
#include "gpt_drv_j32.h"
#include "gpt_drv_d16.h"
#include "Spi.h"
#include "Dma.h"
#include "Adc.h"
#include "icu_drv_wk.h"
#include "wdg_drv.h"
#include "Port.h"

/* Iohw */
#include "iohw_adc.h"
#include "iohw_diflt.h"

/* Communication         */
#include "oxcan.h"

/* Diagnosis             */
#include "oxdocan.h"

/* Memory               */
#include "rim_ctl.h"
/* #include "nvmc_mgr.h" */

/* aubist */
#include <bswa_com.h>

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <Ecu_Memmap.h>

#include <Ecu_Internal.h>
#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>
#include <22SS_Callout.h>
#include <Ecu_Arb.h>

#ifdef ECU_SAMPLE_ON
#include <Ecu_App.h>
#endif

/* ^^ include end ^^ */
#include <SS_ISeq_Callout.h>
/* vv extern start vv */
/* ^^ extern end ^^ */

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableE_env.h>
/* ^^ include end ^^ */

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_preOsInitCallout(SS_BootType u4_BootSource)
 * [Function]	Pre-OsInit Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_preOsInitCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
    
    (void)SS_Memory_set(__ghsbegin_os_stack_top, 0UL, (uint32)OS_STACK_SIZE);
    (void)SS_Memory_set(__ghsbegin_bsw_e_nvar_top, 0UL, (uint32)BSW_E_NVAR_SIZE);
    (void)SS_Memory_copy(__ghsbegin_bsw_e_nvar_withval_top, __ghsbegin_bsw_e_nvar_ival_top, (uint32)BSW_E_NVAR_WITHVAL_SIZE);

    if (u4_BootSource == SS_PM_BOOT_SUP)
    {
        (void)SS_Memory_set(__ghsbegin_bsw_e_rvar_top, 0UL, (uint32)BSW_E_RVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_e_rvar_withval_top, __ghsbegin_bsw_e_rvar_ival_top, (uint32)BSW_E_RVAR_WITHVAL_SIZE);
    }

#ifdef ECU_SAMPLE_ON
    Ecu_App_init();
    Ecu_App_preOsInit(u4_BootSource);
#endif

    Ecu_Intg_init();
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postOsInitCallout(SS_BootType u4_BootSource)
 * [Function]	Post-OsInit Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postOsInitCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_postOsInit(u4_BootSource);
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_preClockUpCallout(SS_BootType u4_BootSource)
 * [Function]	Pre-ClockUp Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_preClockUpCallout(SS_BootType u4_BootSource)
{

    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_preClockUp(u4_BootSource);
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postClockUpCallout(SS_BootType u4_BootSource)
 * [Function]	Post-ClockUp Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postClockUpCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
    Ecu_Intg_BootCauseType u4BootCause;
    U1                     u1_t_bram_retained;

    vd_g_Wdg_Init();
    u4BootCause        = Ecu_IntgHAL_getBootCause();

    if(u4BootCause == ECU_INTG_u4BTCAUSE_PON){
        (void)SS_Memory_set(__ghsbegin_MEM_SEC_STA_BACK_BSW, 0UL, (uint32)BSS_BACK_BSW_SIZE);
    }

    /* RAM initialize for ECU and BSW */
    (void)SS_Memory_set(__ghsbegin_ecu_nvar_top, 0UL, (uint32)ECU_NVAR_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_nvar_p_top, 0UL, (uint32)ECU_NVAR_P_SIZE);

    (void)SS_Memory_set(__ghsbegin_MEM_SEC_STA_RAM_LOC_APPL, 0UL, (uint32)LOC_RAM_SIZE);

    (void)SS_Memory_copy(__ghsbegin_data, __ghsbegin_romdata, (uint32)DATA_SIZE);

    (void)SS_Memory_set(__ghsbegin_bsw_n_nvar_top, 0UL, (uint32)BSW_N_NVAR_SIZE);
    (void)SS_Memory_copy(__ghsbegin_bsw_n_nvar_withval_top, __ghsbegin_bsw_n_nvar_ival_top, (uint32)BSW_N_NVAR_WITHVAL_SIZE);

    (void)SS_Memory_set(__ghsbegin_bsw_sec_nvar_top, 0UL, (uint32)BSW_SEC_NVAR_SIZE);
    (void)SS_Memory_copy(__ghsbegin_bsw_sec_nvar_withval_top, __ghsbegin_bsw_sec_nvar_ival_top, (uint32)BSW_SEC_NVAR_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_bsw_sec_hsm_nvar_top, 0UL, (uint32)BSW_SEC_HSM_NVAR_SIZE);
    (void)SS_Memory_copy(__ghsbegin_bsw_sec_hsm_nvar_withval_top, __ghsbegin_bsw_sec_hsm_nvar_ival_top, (uint32)BSW_SEC_HSM_NVAR_WITHVAL_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR_withval, __ghsbegin_app_n_nvarLR_ival, (uint32)APP_N_NVARLR_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR_top, 0UL, (uint32)ECU_N_NVAR_LR_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR0_withval, __ghsbegin_app_n_nvarCR0_ival, (uint32)APP_N_NVARCR0_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR0_top, 0UL, (uint32)ECU_N_NVAR_CR0_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR1_withval, __ghsbegin_app_n_nvarCR1_ival, (uint32)APP_N_NVARCR1_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR1_top, 0UL, (uint32)ECU_N_NVAR_CR1_SIZE);

    (void)SS_Memory_set(__ghsbegin_iohw_ram_top, 0UL, (uint32)IOHW_RAM_SIZE);

    (void)SS_Memory_set(__ghsbegin_cdd_ram_top, 0UL, (uint32)CDD_RAM_SIZE);

    if (u4_BootSource == SS_PM_BOOT_SUP)
    {
        /* If MCU reset factor is not DRESF0 (DeepSTOP Reset Flag), u4_BootSource will be "SS_PM_BOOT_SUP" */
        (void)SS_Memory_set(__ghsbegin_bsw_n_rvar_top, 0UL, (uint32)BSW_N_RVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_n_rvar_withval_top, __ghsbegin_bsw_n_rvar_ival_top, (uint32)BSW_N_RVAR_WITHVAL_SIZE);
    }

/*  Spi_PrePortInit(); */           /* call in Host side */

/*  if((u4BootCause == ECU_INTG_u4BTCAUSE_PON  ) || */           /* call in Host side */
/*     (u4BootCause == ECU_INTG_u4BTCAUSE_RESET)){  */
/*       vd_g_IcuWkInit((U1)ICU_WK_CFG_MCU_STA_BY_RST); */
/*   }else{ */
/*       vd_g_IcuWkInit((U1)ICU_WK_CFG_MCU_STA_BY_WK); */
/*  } */

/*    vd_g_Gpt_FrtInit(); */    /* call in Host side */
    vd_g_Gpt_OstInit();         /* call in each VM that use OSTM */
    vd_g_Gpt_J32Init();
    vd_g_Gpt_D16Init();
/*    Spi_Init1(); */           /* call in Host side */
/*    Dma_Init(); */           /* call in Host side */

    Adc_Init(NULL_PTR);
    vd_g_IoHwAdcInit();
    vd_g_IoHwDifltInit();
    
    u1_t_bram_retained = (U1)FALSE;
    if(u4BootCause != ECU_INTG_u4BTCAUSE_PON){
        u1_t_bram_retained = u1_g_Rim_WkupRAMCheck();
    }

    if((u4BootCause        == ECU_INTG_u4BTCAUSE_PON) ||
       (u1_t_bram_retained != (U1)TRUE              )){
        vd_g_22SSCallout_StaBonInit();
        (void)SS_Memory_set(__ghsbegin_ecu_n_bvar_top, 0UL, (uint32)ECU_N_BVAR_SIZE);   /* Merged Ecu_Intg_initApp process with RIM keyword RAM destruction check */
    }
    else if(u4BootCause == ECU_INTG_u4BTCAUSE_RESET){
        vd_g_22SSCallout_StaRstInit();
    }
    else{
        vd_g_22SSCallout_StaWkupInit();
    }

    Ecu_Intg_checkAndImmShutdown();

    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource)
 * [Function]	Post-StartOS Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
    Ecu_Arb_wkUpFctrInit(); /* Wfd縺ｧ鄂ｮ縺肴鋤縺井ｺ亥ｮ� */
#ifdef ECU_SAMPLE_ON
    Ecu_App_postStartOs(u4_BootSource);
#endif

    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postRteStartCallout(SS_BootType u4_BootSource)
 * [Function]	Post-RteStart Callout
 * [Arguments]	SS_BootType u4_BootSource����壹ヶ繝ｼ繝郁ｦ∝屏
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postRteStartCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_postRteStart(u4_BootSource);
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_sleepCallout(void)
 * [Function]	Callout of initialize at sleep
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void SS_Pm_sleepCallout(void)
{
    
    
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */
    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_reSleepCallout(void)
 * [Function]	Callout of initialize at resleep
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void SS_Pm_reSleepCallout(void)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_reSleep();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_DisableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc)
 * [Function]	Callout for disabling C1ISR
 * [Arguments]	SS_ShutdownReqSrcType u4_ReqSrc����售hutdown request source type
 * [Return]		None
 * [Notes]		Use only for disabling C1ISR
 *--------------------------------------------------------------------------*/
void SS_Pm_DisableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc)
{
    /* vv User Hook start vv */
#if (SS_USE_CORE_COUNT >= 2u)
    SuspendOSInterrupts();
#else
    
    SuspendAllInterrupts();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_EnableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc)
 * [Function]	Callout for enabling C1ISR
 * [Arguments]	timing
 * [Return]		None
 * [Notes]		Use only for enabling C1ISR
 *--------------------------------------------------------------------------*/
void SS_Pm_EnableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc)
{
    /* vv User Hook start vv */
#if (SS_USE_CORE_COUNT >= 2u)
    ResumeOSInterrupts();
#else
    ResumeAllInterrupts();
    
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_wakeupCheckCallout(void)
 * [Function]	Hook to notify users of Wakeup check
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void SS_Pm_wakeupCheckCallout(void)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_wakeupCheck();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_shutdownCallout(void)
 * [Function]	Hook to notify users when SS shutdown
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SHUTDOWN == STD_ON)
void SS_Pm_shutdownCallout(void)
{
    /* vv User Hook start vv */
    vd_g_22SSCallout_PrepShtdwn();

    /* TPcsw_SS_Pm_shutdownCallout_if0 */
    vd_g_oXDoCANShutdown();
    vd_g_oXCANShtdwn();
    /* vd_g_Nvmc_DeInit(); */
    vd_g_Rim_DeInit();

    Adc_StopGroupConversion(ADC_GR_0);
	
#ifdef ADC_GR_1
    Adc_StopGroupConversion(ADC_GR_1);
#endif

#ifdef ADC_GR_2
    Adc_StopGroupConversion(ADC_GR_2);
#endif

    Adc_DeInit();
    Dma_DeInit();
    Spi_DeInit();
    vd_g_Gpt_D16DeInit();
    vd_g_Gpt_J32DeInit();
    vd_g_Gpt_OstDeInit();

    Port_Init( &cstPort_Config[1] );
    vd_g_IcuWkInit((U1)ICU_WK_CFG_PREP_MCU_TO_LPM);

    (void)ClearPendingInterrupt((ISRType)eMCOS_ISR_INTOSTM5TINT);

    /* 繝槭う繧ｳ繝ｳDeepStop謚募���� */
    (void)ehvm_vmm_exit(EHVM_EXIT_FACTOR_NO_AWAKE, EHVM_VM_ACTION_SLEEP);

    /* TPcsw_SS_Pm_shutdownCallout_endif */

    /* ^^ User Hook end   ^^ */

    return;
}
#endif /* (SS_USE_SHUTDOWN == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_preArbitrationCallout(void)
 * [Function]	繧ｷ繧ｹ繝����Β迥ｶ諷玖ｪｿ蛛懃峩蜑阪����繧ｿ繧､繝溘Φ繧ｰ繧呈署萓帙☆繧�
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_MODE == STD_OFF)
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Pm_preArbitrationCallout(void)
{
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)) */
#endif /* (SS_USE_MODE == STD_OFF) */
