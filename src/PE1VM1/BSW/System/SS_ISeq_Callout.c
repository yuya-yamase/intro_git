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
#include "wdg_drv.h"

/* Memory               */
#include "rim_ctl.h"

/* System               */
#include "scheduler.h"

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <Ecu_Memmap.h>

#include <Ecu_Internal.h>
#include <Ecu_CtgOs.h>
#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>
#include <Ecu_Intg_Callout.h>

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
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_preOsInitCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
    
    (void)SS_Memory_set(__ghsbegin_os_stack_top, 0UL, (uintptr_t)OS_STACK_SIZE);
    (void)SS_Memory_set(__ghsbegin_bsw_e_nvar_top, 0UL, (uintptr_t)BSW_E_NVAR_SIZE);
    (void)SS_Memory_set(__ghsbegin_bsw_e_rvar_top, 0UL, (uintptr_t)BSW_E_RVAR_SIZE);

    (void)SS_Memory_copy(__ghsbegin_bsw_e_nvar_withval_top, __ghsbegin_bsw_e_nvar_ival_top, (uintptr_t)BSW_E_NVAR_WITHVAL_SIZE);

    if (u4_BootSource == SS_PM_BOOT_SUP)
    {
        (void)SS_Memory_set(__ghsbegin_bsw_e_rvar_top, 0UL, (uintptr_t)BSW_E_RVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_e_rvar_withval_top, __ghsbegin_bsw_e_rvar_ival_top, (uintptr_t)BSW_E_RVAR_WITHVAL_SIZE);
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
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
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
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
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
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postClockUpCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
    Ecu_Intg_BootCauseType u4BootCause;

//    vd_g_Wdg_Init();
    u4BootCause = Ecu_IntgHAL_getBootCause();
    if(u4BootCause == ECU_INTG_u4BTCAUSE_PON){
        (void)SS_Memory_set(__ghsbegin_MEM_SEC_STA_BACK_BSW, 0UL, (uintptr_t)BSS_BACK_BSW_SIZE);
    }

    /* RAM initialize for ECU and BSW */
    (void)SS_Memory_set(__ghsbegin_ecu_nvar_top, 0UL, (uintptr_t)ECU_NVAR_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_nvar_p_top, 0UL, (uintptr_t)ECU_NVAR_P_SIZE);

    (void)SS_Memory_set(__ghsbegin_MEM_SEC_STA_RAM_LOC_APPL, 0UL, (uintptr_t)LOC_RAM_SIZE);

    (void)SS_Memory_copy(__ghsbegin_data, __ghsbegin_romdata, (uintptr_t)DATA_SIZE);

    (void)SS_Memory_set(__ghsbegin_bsw_n_nvar_top, 0UL, (uintptr_t)BSW_N_NVAR_SIZE);
    (void)SS_Memory_set(__ghsbegin_bsw_n_rvar_top, 0UL, (uintptr_t)BSW_N_RVAR_SIZE);

    (void)SS_Memory_copy(__ghsbegin_bsw_n_nvar_withval_top, __ghsbegin_bsw_n_nvar_ival_top, (uintptr_t)BSW_N_NVAR_WITHVAL_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR_withval, __ghsbegin_app_n_nvarLR_ival, (uintptr_t)APP_N_NVARLR_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR_top, 0UL, (uintptr_t)ECU_N_NVAR_LR_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR0_withval, __ghsbegin_app_n_nvarCR0_ival, (uintptr_t)APP_N_NVARCR0_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR0_top, 0UL, (uintptr_t)ECU_N_NVAR_CR0_SIZE);

    (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR1_withval, __ghsbegin_app_n_nvarCR1_ival, (uintptr_t)APP_N_NVARCR1_WITHVAL_SIZE);
    (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR1_top, 0UL, (uintptr_t)ECU_N_NVAR_CR1_SIZE);

    if (u4_BootSource == SS_PM_BOOT_SUP)
    {
        (void)SS_Memory_set(__ghsbegin_bsw_n_rvar_top, 0UL, (uintptr_t)BSW_N_RVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_n_rvar_withval_top, __ghsbegin_bsw_n_rvar_ival_top, (uintptr_t)BSW_N_RVAR_WITHVAL_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_bvar_top, 0UL, (uintptr_t)ECU_N_BVAR_SIZE);
    }

    vd_g_Gpt_OstInit();    /* call in each VM that use OSTM */
    
    vd_g_SchdlrInit();

    /* 仮：Rim起動時処理                                            */
    /* ※Bon/Wkup判定条件は仮                                       */
    /*     BRAMが正常か否かで切り分ける(起動時に必ずどちらかを実施) */
    /* 下記IFでRAMチェックした結果で、Bon/Wkupを切り分けるべき。    */
    /* (他の部品もその基準でBon/Wkupを切り分けているものがあるはず) */
    /* ※組み込み未実施                                             */
    /*     u1_g_Rim_WkupRAMCheck                                    */
    /*     u1_g_Rim_TmrWkupRAMCheck                                 */
    if((u4BootCause == ECU_INTG_u4BTCAUSE_PON  ) ||
       (u4BootCause == ECU_INTG_u4BTCAUSE_RESET)){
        vd_g_Rim_BonInit();
    }
    else{
        vd_g_Rim_WkupInit();
    }


#ifdef ECU_SAMPLE_ON
    Ecu_App_postClockUp(u4_BootSource);
#endif
    u4BootCause = Ecu_IntgHAL_getBootCause();
    Ecu_Intg_initCdd(u4BootCause);

    Ecu_Intg_checkAndImmShutdown();
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource)
 * [Function]	Post-StartOS Callout
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_postStartOs(u4_BootSource);
#endif

    Ecu_Intg_initApp();

    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postRteStartCallout(SS_BootType u4_BootSource)
 * [Function]	Post-RteStart Callout
 * [Arguments]	SS_BootType u4_BootSource：ブート要因
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
 * [Arguments]	SS_ShutdownReqSrcType u4_ReqSrc：Shutdown request source type
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
    if(u4_ReqSrc == SS_PM_u4REQSRC_INIT){
        /* 仮：Rim起動後処理                                            */
        /* BRAMが正常であることを確認するためのKeyWordを設定している    */
        /* 他部品のBRAM初期化後に実施すること                           */
        vd_g_Rim_PostInit();
    }

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
    vd_g_Rim_DeInit();

    Ecu_CtgOs_stop(ECU_CTGOS_TMRES_OWNVM);
    (void)ClearPendingInterrupt((ISRType)OS_SYSTEM_COUNTER_ISR0);
    /* VMスリープ投入 */
    (void)ehvm_vmm_exit(EHVM_EXIT_FACTOR_NO_AWAKE, EHVM_VM_ACTION_SLEEP);

    /* ^^ User Hook end   ^^ */

    return;
}
#endif /* (SS_USE_SHUTDOWN == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_preArbitrationCallout(void)
 * [Function]	システム状態調停直前のタイミングを提供する
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
