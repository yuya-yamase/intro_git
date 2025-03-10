/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Boot.c
 * [Module]			Boot
 * [Function]		Boot
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_ISeq.h>
#include <SS_CpuCore.h>
#include <SS_Error_Callout.h>
#include <SS_Memory.h>
#include <SS_Boot.h>
#include <EcuM.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define REG_u4RESF  (*(volatile uint32 *)((uintptr_t)0xFF988500UL)) /* RESF */
#define REG_u4RESFC (*(volatile uint32 *)((uintptr_t)0xFF980C00UL)) /* RESFC */
#if (SS_GEN_PRODUCT == SS_GEN_U2A)
#define MSK_u4RESF_CAUSE (0x0003F5DDUL)
#define VAL_u4RESFC_CLR  (0x0000F5DDUL) /* R_RESF_CLR */
#elif (SS_GEN_PRODUCT == SS_GEN_RCARS4)
#define MSK_u4RESF_CAUSE (0x0700B0DDUL)
#define VAL_u4RESFC_CLR  (0x0700B0DDUL) /* R_RESF_CLR */
#else
#error "Illegal configuration."
#endif
#define VAL_u4RESF_ISO (0x00008000UL)

#define REG_u4BOOTCTRL      (*(volatile uint32 *)((uintptr_t)0xFFFB2000UL))
#define SS_BOOT_u4WAIT_TIME (0x4E20UL)

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 3u)
static void SS_Boot_busyWait(uint32 u4LoopCnt);
#endif

#if (SS_USE_CORE_COUNT >= 3u)
static void SS_Boot_busyWait(uint32 u4LoopCnt)
{

    uint32 u4LoopNow;

    for (u4LoopNow = 0; u4LoopNow < u4LoopCnt; u4LoopNow++)
    {
    }
    return;
}
#endif

#if (SS_USE_CORE_COUNT >= 2u)
void SS_Boot_startSlaveCore(void)
{
    volatile uint32 u4Dummy;

    REG_u4BOOTCTRL = 2UL;
    u4Dummy        = REG_u4BOOTCTRL;
    SS_CpuCore_syncp();

#if (SS_USE_CORE_COUNT >= 3u)
    SS_Boot_busyWait(SS_BOOT_u4WAIT_TIME);
    REG_u4BOOTCTRL = 4UL;
    u4Dummy        = REG_u4BOOTCTRL;
    SS_CpuCore_syncp();
#endif
#if (SS_USE_CORE_COUNT >= 4u)
    SS_Boot_busyWait(SS_BOOT_u4WAIT_TIME);
    REG_u4BOOTCTRL = 8UL;
    u4Dummy        = REG_u4BOOTCTRL;
    SS_CpuCore_syncp();
#endif

    return;
}
#endif

#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
static void SS_Boot_initStackTopBottom(void)
{
#if (SS_USE_CORE_COUNT >= 2u)
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    if (u4CoreId == SS_CPUCORE_u4MASTERCORE)
#endif
    {
        (void)SS_Memory_set(__ghsbegin_ss_stack_top, 0UL, (uintptr_t)__ghssize_ss_stack_top);
        (void)SS_Memory_set(__ghsbegin_ss_stack_bottom, 0UL, (uintptr_t)__ghssize_ss_stack_bottom);
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
        SS_ISeq_u4SyncCheck_1 = 0UL;
        (void)SS_Memory_set(__ghsbegin_ss_stack1_top, 0UL, (uintptr_t)__ghssize_ss_stack1_top);
        (void)SS_Memory_set(__ghsbegin_ss_stack1_bottom, 0UL, (uintptr_t)__ghssize_ss_stack1_bottom);
    }
#endif
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
        SS_ISeq_u4SyncCheck_2 = 0UL;
        (void)SS_Memory_set(__ghsbegin_ss_stack2_top, 0UL, (uintptr_t)__ghssize_ss_stack2_top);
        (void)SS_Memory_set(__ghsbegin_ss_stack2_bottom, 0UL, (uintptr_t)__ghssize_ss_stack2_bottom);
    }
#endif
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
        SS_ISeq_u4SyncCheck_3 = 0UL;
        (void)SS_Memory_set(__ghsbegin_ss_stack3_top, 0UL, (uintptr_t)__ghssize_ss_stack3_top);
        (void)SS_Memory_set(__ghsbegin_ss_stack3_bottom, 0UL, (uintptr_t)__ghssize_ss_stack3_bottom);
    }
#endif
#if (SS_USE_CORE_COUNT >= 2u)
    else
    {
        // nothing to do
    }
#endif
    return;
}
#endif /*  (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		void SS_Boot_CompleteHook(void)
 * [Function]	Early Section Initialization
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Boot_CompleteHook(void)
{
    
    
    

    SS_BootType u4BootSource;

#if (SS_USE_SLEEP == STD_ON)
    if ((REG_u4RESF & MSK_u4RESF_CAUSE) == VAL_u4RESF_ISO)
    { // wakeup case

        SS_CpuCore_entryMasterSection();
        {
            
            (void)SS_Memory_set(__ghsbegin_ss_nvar_e_top, 0UL, (uintptr_t)SS_NVAR_E_SIZE);
            

            
            
        }
        SS_CpuCore_exitMasterSection();
        u4BootSource = SS_PM_BOOT_WUP;
    }
    else
#endif // (SS_USE_SLEEP == STD_ON)
    {  // startup case

        
        
#if (SS_USE_PRISTACKCHECK == STD_ON)
        SS_Memory_checkPriStack();
#endif
        SS_CpuCore_entryMasterSection();
        {
            (void)SS_Memory_set(__ghsbegin_ss_nvar_e_top, 0UL, (uintptr_t)SS_NVAR_E_SIZE);
            
            (void)SS_Memory_set(__ghsbegin_ss_rvar_e_top, 0UL, (uintptr_t)SS_RVAR_E_SIZE);
        }
        SS_CpuCore_exitMasterSection();
        u4BootSource = SS_PM_BOOT_SUP;
    }

#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
    SS_Boot_initStackTopBottom();
#endif
    

    SS_ISeq_stupBoot(u4BootSource);

    EcuM_Init();
    
    SS_Error_ResetCallout();
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Boot_clearResetFactor(void)
 * [Function]	Clear Reset factor register
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_Boot_clearResetFactor(void)
{
    {
        volatile uint32 u4Dummy;

        REG_u4RESFC = VAL_u4RESFC_CLR;

        u4Dummy = REG_u4RESFC; /* dummy read */
        SS_CpuCore_syncp();    /* syncp */
    }

    return;
}
#endif
