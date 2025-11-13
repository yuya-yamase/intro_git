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

/* MCAL */
#include "gpt_drv_frt.h"
#include "Port.h"
#include "typort.h"
#include "Spi.h"
#include "Dma.h"
#include "icu_drv_wk.h"
#include "ErrH.h"

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <Ecu_Memmap.h>

#include <SS_ISeq_Callout.h>
#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>
#include <22SS_Callout.h>

#include <Ecu_Int.h>
#ifdef ECU_SAMPLE_ON
#include <Ecu_Internal.h>
#endif /* ECU_SAMPLE_ON */
/* ^^ include end ^^ */
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
    

    SS_CoreIdType u4_CoreId;

    u4_CoreId = SS_CpuCore_getCoreID();
    if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
    {
        (void)SS_Memory_set(__ghsbegin_bsw_e_nvar_top, 0UL, (uint32)BSW_E_NVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_e_nvar_withval_top, __ghsbegin_bsw_e_nvar_ival_top, (uintptr_t)BSW_E_NVAR_WITHVAL_SIZE);

        if (u4_BootSource == SS_PM_BOOT_SUP)
        {
            (void)SS_Memory_set(__ghsbegin_bsw_e_rvar_top, 0UL, (uintptr_t)BSW_E_RVAR_SIZE);
            (void)SS_Memory_copy(__ghsbegin_bsw_e_rvar_withval_top, __ghsbegin_bsw_e_rvar_ival_top, (uintptr_t)BSW_E_RVAR_WITHVAL_SIZE);
        }
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
    }
#endif
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
    }
#endif
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
    }
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
    // Port_Init(&cstPort_Config[0]);
    Ecu_Intg_BootCauseType u4BootCause;
    SS_CoreIdType u4_CoreId;

    u4BootCause = Ecu_IntgHAL_getBootCause();
    u4_CoreId = SS_CpuCore_getCoreID();

    (void)SS_Memory_set(__ghsbegin_ecu_nvar_lram_top, 0UL, (uint32)ECU_NVAR_LRAM_SIZE);
    (void)SS_Memory_copy(__ghsbegin_data_lram, __ghsbegin_romdata_lram, (uint32)DATA_LRAM_SIZE);

    if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
    {
        vd_g_Gpt_FrtInit();     /* The GptFrt/LSTC timer is a global resource accessible to all PEs, so it should start immediatly post clock-up */

        (void)SS_Memory_set(__ghsbegin_ecu_nvar_top, 0UL, (uint32)ECU_NVAR_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_nvar_global_top, 0UL, (uint32)ECU_NVAR_GLOBAL_SIZE);
        (void)SS_Memory_copy(__ghsbegin_data, __ghsbegin_romdata, (uint32)DATA_SIZE);
        (void)SS_Memory_copy(__ghsbegin_data_vcc, __ghsbegin_romdata_vcc, (uint32)DATA_VCC_SIZE);

        (void)SS_Memory_set(__ghsbegin_bsw_n_nvar_top, 0UL, (uintptr_t)BSW_N_NVAR_SIZE);
        (void)SS_Memory_copy(__ghsbegin_bsw_n_nvar_withval_top, __ghsbegin_bsw_n_nvar_ival_top, (uintptr_t)BSW_N_NVAR_WITHVAL_SIZE);

        if (u4_BootSource == SS_PM_BOOT_SUP)
        {
            (void)SS_Memory_set(__ghsbegin_bsw_n_rvar_top, 0UL, (uintptr_t)BSW_N_RVAR_SIZE);
            (void)SS_Memory_copy(__ghsbegin_bsw_n_rvar_withval_top, __ghsbegin_bsw_n_rvar_ival_top, (uintptr_t)BSW_N_RVAR_WITHVAL_SIZE);
        }

        (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR0_withval, __ghsbegin_app_n_nvarLR0_ival, (uintptr_t)APP_N_NVARLR0_WITHVAL_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR0_top, 0UL, (uintptr_t)ECU_N_NVAR_LR0_SIZE);

        (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR0_withval, __ghsbegin_app_n_nvarCR0_ival, (uintptr_t)APP_N_NVARCR0_WITHVAL_SIZE);
        (void)SS_Memory_copy(__ghsbegin_app_n_nvarCR1_withval, __ghsbegin_app_n_nvarCR1_ival, (uintptr_t)APP_N_NVARCR1_WITHVAL_SIZE);

        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR0_top, 0UL, (uintptr_t)ECU_N_NVAR_CR0_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarCR1_top, 0UL, (uintptr_t)ECU_N_NVAR_CR1_SIZE);

        (void)SS_Memory_set(__ghsbegin_cluster2_share_ramtop, 0UL, (uintptr_t)BSW_SHARE_DATA_SIZE);

        Spi_PrePortInit();
        vd_g_tyPortPreInit();
        Port_Init( &cstPort_Config[0] );
        if (u4_BootSource == SS_PM_BOOT_SUP)
        {
            vd_g_tyPortInit((U1)TYPORT_CFG_STA_BY_RST);
        }
        else
        {
            vd_g_tyPortInit((U1)TYPORT_CFG_STA_BY_WK);
        }

        if((u4BootCause == ECU_INTG_u4BTCAUSE_PON  ) ||
           (u4BootCause == ECU_INTG_u4BTCAUSE_RESET)){
            vd_g_IcuWkInit((U1)ICU_WK_CFG_MCU_STA_BY_RST);
        }else{
            vd_g_IcuWkInit((U1)ICU_WK_CFG_MCU_STA_BY_WK);
        }

        vd_g_22SSCallout_BattLowInit();

        Spi_Init1();

        Dma_Init();

        ErrH_Init_1();
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
        (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR1_withval, __ghsbegin_app_n_nvarLR1_ival, (uintptr_t)APP_N_NVARLR1_WITHVAL_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR1_top, 0UL, (uintptr_t)ECU_N_NVAR_LR1_SIZE);
    }
#endif
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
        (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR2_withval, __ghsbegin_app_n_nvarLR2_ival, (uintptr_t)APP_N_NVARLR2_WITHVAL_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR2_top, 0UL, (uintptr_t)ECU_N_NVAR_LR2_SIZE);
    }
#endif
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
        (void)SS_Memory_copy(__ghsbegin_app_n_nvarLR3_withval, __ghsbegin_app_n_nvarLR3_ival, (uintptr_t)APP_N_NVARLR3_WITHVAL_SIZE);
        (void)SS_Memory_set(__ghsbegin_ecu_n_nvarLR3_top, 0UL, (uintptr_t)ECU_N_NVAR_LR3_SIZE);
    }
#endif

    

    Ecu_Intg_initApp();

//    Ecu_Intg_checkAndImmShutdown();
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
#if (SS_USE_UP == STD_ON)
void SS_Pm_postStartOSCallout(SS_BootType u4_BootSource)
{

    /* vv User Hook start vv */
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
    Ecu_IntgHAL_clearRAMV();
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

    Ecu_Intg_sleep(ECU_INTG_u41stSLEEP);
    /* ^^ User Hook end   ^^ */
    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */
#endif /* (SS_USE_UP == STD_ON) */

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
    Ecu_Intg_sleep(ECU_INTG_u4RESLEEP);
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
#if (SS_USE_UP == STD_ON)
void SS_Pm_DisableInterruptsCallout(SS_ShutdownReqSrcType u4_ReqSrc)
{
    /* vv User Hook start vv */
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
    /* ^^ User Hook end   ^^ */
    return;
}
#endif /* (SS_USE_UP == STD_ON) */

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
    SS_CpuCore_entryMasterSection();
    {
#ifdef ECU_SAMPLE_ON
        SS_Pm_requestWakeup(); /* 毎回起きてくる */
        SS_SleepTm_stop();     /* 目覚ましタイマを停止 */
#endif
    }
    SS_CpuCore_exitMasterSection();

    Ecu_Intg_checkWakeup();
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
#if (SS_USE_UP == STD_ON)
#if (SS_USE_SHUTDOWN == STD_ON)
void SS_Pm_shutdownCallout(void)
{
    /* vv User Hook start vv */
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
#endif /* (SS_USE_UP == STD_ON) */
