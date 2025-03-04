/*****************************************************************************
 *	Copyright DENSO Corporation and AUBASS Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_State.c
 * [Module] 		System State Management
 * [Function]		SS_State
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#include <Os.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_State.h>
#include <SS_State_Callout.h>
#include <SS_ISeq.h>
#include <SS_ISeq_Callout.h>
#include <SS_Error.h>
#include <SS_CpuCore.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

#if ((SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) && (SS_MM_USE_ASYNC_ARB == STD_OFF))
#define SS_REQUEST_INITVAL SS_REQUEST_NONE
#else
#define SS_REQUEST_INITVAL SS_REQUEST_EXIST
#endif

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_MODE == STD_ON)
static uint32         SS_State_u4SystemState_PE[SS_USE_CORE_COUNT];
static uint32         SS_State_u4ArbitrateResult_g;
static uint32         SS_State_u4ArbitrateResult_PE[SS_USE_CORE_COUNT];
static uint32         SS_State_u4PreRunReason;
static SS_RequestType SS_State_u4ShutdownCancelReq;
static SS_RequestType SS_State_u4PreRunRequest_g;
static SS_RequestType SS_State_u4PreRunRequest_PE[SS_USE_CORE_COUNT];
static SS_RequestType SS_State_u4RunRequest_g;
static SS_RequestType SS_State_u4RunRequest_PE[SS_USE_CORE_COUNT];

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
static SS_RequestType SS_State_u4PostRunRequest_g;
static SS_RequestType SS_State_u4PostRunRequest_PE[SS_USE_CORE_COUNT];
#endif
#if ((SS_USE_SLEEP == STD_ON) && (SS_USE_SHUTDOWN == STD_ON))
static SS_Pm_shutdownTargetType SS_State_u4ShutdownTarget;
#endif
#endif /* (SS_USE_MODE == STD_ON) */

#include <SS_MemmapSdaSelectE_Env.h>

#if (SS_USE_MODE == STD_ON)
/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
static void SS_State_Arbitrate(void);
static void SS_State_Arb_ExitPostRun_Intrnl(void);
static void SS_State_EntryModeAction(void);
static void SS_State_transit(void);
static void SS_State_ArbitrateRequest_PE(void);

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
static void   SS_State_EntryPhaseAction(void);
static uint32 SS_State_GetArbResultForPostRun(void);
#endif

#if (SS_USE_SLEEP == STD_ON)
static void SS_State_Arbitrate_CheckSleep(void);
static void SS_State_EntrySleepAction(void);
#endif

#if (SS_MM_USE_ASYNC_ARB == STD_ON)
static void SS_State_distributeArbitrateResult(void);
#endif

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format] 	SS_Mm_modeType SS_Mm_getMode(void)
 * [Function]	To notification the current mode of SS
 * [Arguments]	None
 * [Return] 	Current mode of SS
 * [Notes]		Do not call before StartOS
 *--------------------------------------------------------------------------*/
SS_Mm_modeType SS_Mm_getMode(void)
{
    SS_Mm_modeType u4_state;
    SS_CoreIdType  u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    u4_state = (SS_Mm_modeType)SS_State_u4SystemState_PE[u4CoreId];

    

    switch (u4_state)
    {
    case SS_MM_PRERUN_SUP:
    case SS_MM_PRERUN_WUP:
    case SS_MM_RUN:
    case SS_MM_POSTRUN:
        /* 処理なし */
        break;
    default:
        SS_Error_notify(SS_ERROR_DATA);
        break;
    }

    return u4_state;
}

/**---------------------------------------------------------------------------
 * [Format] 	SS_Mm_viaType SS_Mm_getPreRunSource(void)
 * [Function]	Return PreRunEntry/ReEntry Hook Reason
 * [Arguments]	None
 * [Return] 	SS_MM_VIA_RESET 		 : RESET
 *				SS_MM_VIA_DEEPSTOP		 : WAKEUP(POWER OFF SLEEP)
 *				SS_MM_VIA_STOP			 : WAKEUP(Exclude POWER OFF SLEEP)
 *				SS_MM_VIA_SLEEPCANCEL	 : SLEEP CANCEL
 *				SS_MM_VIA_POSTRUNCANCEL  : POSTRUN CANCEL
 * [Notes]		Do not call before StartOS
 *--------------------------------------------------------------------------*/
SS_Mm_viaType SS_Mm_getPreRunSource(void)
{
    SS_Mm_viaType u1_state;

    u1_state = (SS_Mm_viaType)SS_State_u4PreRunReason;

    
    switch (u1_state)
    {
    case SS_MM_VIA_RESET:
    case SS_MM_VIA_DEEPSTOP:
    case SS_MM_VIA_STOP:
    case SS_MM_VIA_SLEEPCANCEL:
    case SS_MM_VIA_POSTRUNCANCEL:
        /* 処理なし */
        break;
    default:
        SS_Error_notify(SS_ERROR_DATA);
        break;
    }

    return u1_state;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_requestPreRun(void)
 * [Function]	Requests to stay for StUpPreRun or WkUpPreRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#if (SS_MM_USE_ASYNC_ARB == STD_OFF)
void SS_Mm_requestPreRun(void)
{
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4PreRunRequest_PE[u4CoreId] = SS_REQUEST_EXIST;

    return;
}
#endif /* (SS_MM_USE_ASYNC_ARB == STD_OFF) */
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_requestRun(void)
 * [Function]	Requests to stay for Run
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Mm_requestRun(void)
{
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4RunRequest_PE[u4CoreId] = SS_REQUEST_EXIST;

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_requestPostRun(void)
 * [Function]	Requests to stay for POST_RUN
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Mm_requestPostRun(void)
{
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))

    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4PostRunRequest_PE[u4CoreId] = SS_REQUEST_EXIST;
#endif

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */
/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_releasePreRun(void)
 * [Function]	Request to release from StUpPreRun or WkUpPreRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
void SS_Mm_releasePreRun(void)
{
    SS_State_u4PreRunRequest_g = SS_REQUEST_NONE;

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT) */

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
void SS_Mm_releasePreRun(void)
{
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4PreRunRequest_PE[u4CoreId] = SS_REQUEST_NONE;

    return;
}
#endif
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_releaseRun(void)
 * [Function]	Request to release from Run
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
void SS_Mm_releaseRun(void)
{
    SS_State_u4RunRequest_g = SS_REQUEST_NONE;

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT) */

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
void SS_Mm_releaseRun(void)
{
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4RunRequest_PE[u4CoreId] = SS_REQUEST_NONE;

    return;
}
#endif
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_releasePostRun(void)
 * [Function]	Request to release from POST_RUN
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
void SS_Mm_releasePostRun(void)
{
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    SS_State_u4PostRunRequest_g = SS_REQUEST_NONE;
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT) */

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
void SS_Mm_releasePostRun(void)
{
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();

    SS_State_u4PostRunRequest_PE[u4CoreId] = SS_REQUEST_NONE;

#endif
    return;
}
#endif /* (SS_MM_USE_ASYNC_ARB == STD_ON) */
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_cancelShutdown(void)
 * [Function]	Request for Sleep Cancel
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Mm_cancelShutdown(void)
{
    SS_State_u4ShutdownCancelReq = SS_REQUEST_EXIST;

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_transit(void)
 * [Function]	Request to transit State
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
void SS_Mm_transit(void)
{
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_TRANSIT);
    SS_State_transit();
    SS_Pm_EnableInterruptsCallout(SS_PM_u4REQSRC_TRANSIT);

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_mainFunction(void)
 * [Function]	定期調停用の状態遷移処理を実行
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Mm_mainFunction(void)
{
    
    SS_Mm_preArbitrationCallout();
    

    SS_State_transit();

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_State_init(void)
 * [Function]	Call State Transition Hook On Enter PreRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_State_init(SS_BootType u4_BootSource)
{
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_INIT_A);

    SS_CpuCore_entryMasterSection();
    {
        uint32 u4CoreId;

        if (u4_BootSource != SS_PM_BOOT_WUP)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_DO_PRERUNENTRY;
            SS_State_u4PreRunReason      = SS_MM_VIA_RESET;
        }
        else
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_DO_PRERUNREENTRY;
            SS_State_u4PreRunReason      = SS_MM_VIA_DEEPSTOP;
        }

        for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
        {
            SS_State_u4PreRunRequest_PE[u4CoreId] = SS_REQUEST_INITVAL;
        }

        SS_State_u4PreRunRequest_g = SS_REQUEST_INITVAL;
        SS_State_u4RunRequest_g    = SS_REQUEST_INITVAL;
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
        SS_State_u4PostRunRequest_g = SS_REQUEST_INITVAL;
#endif

#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        SS_State_distributeArbitrateResult();
#endif
    }
    SS_CpuCore_exitMasterSection();

    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_INIT_B);

    
    SS_State_EntryModeAction();

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_State_transit(void)
 * [Function]	Transit State
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_USE_ASYNC_ARB == STD_OFF)
static void SS_State_transit(void)
{
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_TRANSIT_A);

    SS_CpuCore_entryMasterSection();
    {
        SS_State_ArbitrateRequest_PE();
        SS_State_Arbitrate();
    }
    SS_CpuCore_exitMasterSection();

    SS_State_EntryModeAction();

    SS_CpuCore_entryMasterSection();
    {
        SS_State_ArbitrateRequest_PE();
        SS_State_Arbitrate();
    }
    SS_CpuCore_exitMasterSection();

    SS_State_EntryModeAction();

    SS_CpuCore_entryMasterSection();
    {
        SS_State_ArbitrateRequest_PE();
        SS_State_Arbitrate();
    }
    SS_CpuCore_exitMasterSection();

    SS_State_EntryModeAction();

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    SS_State_EntryPhaseAction();
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */

    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_TRANSIT_B);

    return;
}
#else /* (SS_MM_USE_ASYNC_ARB == STD_OFF) */
static void SS_State_transit(void)
{
    SS_CpuCore_entryMasterSection();
    {
        SS_State_ArbitrateRequest_PE();
        SS_State_Arbitrate();

        SS_State_distributeArbitrateResult();
    }
    SS_CpuCore_exitMasterSection();

    SS_State_EntryModeAction();

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    SS_State_EntryPhaseAction();
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */

    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_State_Arbitrate(void)
 * [Function]	Arbitration PreRun for State of SS
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void SS_State_Arbitrate(void)
{
    uint32         u4CoreId;
    SS_Mm_modeType u4_state;

    
    

    /* Initialize Arbitrate Result */
    SS_State_u4ArbitrateResult_g = SS_STATE_ARBITRATE_ERROR;

    u4_state = SS_Mm_getMode();

    switch (u4_state)
    {
    case SS_MM_PRERUN_SUP:
        if (SS_State_u4PreRunRequest_g == SS_REQUEST_EXIST)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_NOTDO_HOOK;
        }
        else if (SS_State_u4PreRunRequest_g == SS_REQUEST_NONE)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_DO_RUNENTRY;
            for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
            {
                SS_State_u4RunRequest_PE[u4CoreId] = SS_REQUEST_INITVAL;
            }
        }
        else
        {
            SS_Error_notify(SS_ERROR_DATA);
        }

        break;

    case SS_MM_RUN:
        if (SS_State_u4RunRequest_g == SS_REQUEST_EXIST)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_NOTDO_HOOK;
        }
        else if (SS_State_u4RunRequest_g == SS_REQUEST_NONE)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_DO_POSTRUNENTRY;
            SS_State_u4ShutdownCancelReq = SS_REQUEST_NONE;
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
            for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
            {
                SS_State_u4PostRunRequest_PE[u4CoreId] = SS_REQUEST_INITVAL;
            }
#endif
        }
        else
        {
            SS_Error_notify(SS_ERROR_DATA);
        }

        break;

    case SS_MM_POSTRUN:
        SS_State_Arb_ExitPostRun_Intrnl();

        break;

    case SS_MM_PRERUN_WUP:
        if (SS_State_u4PreRunRequest_g == SS_REQUEST_EXIST)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_NOTDO_HOOK;
        }
        else if (SS_State_u4PreRunRequest_g == SS_REQUEST_NONE)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_DO_RUNENTRY;
            for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
            {
                SS_State_u4RunRequest_PE[u4CoreId] = SS_REQUEST_INITVAL;
            }
        }
        else
        {
            SS_Error_notify(SS_ERROR_DATA);
        }

        break;

    default:
        /* getMode()側で判定済なので、ここでは処理なし */

        break;
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_State_Arb_ExitPostRun_Intrnl(void)
 * [Function]	Arbitration ExitPostRun for State of SS (Internal)
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		Do not call before StartOS
 *--------------------------------------------------------------------------*/
static void SS_State_Arb_ExitPostRun_Intrnl(void)
{
    uint32 u4CoreId;

    
    /* Initialize Arbitrate Result */
    SS_State_u4ArbitrateResult_g = SS_STATE_ARBITRATE_ERROR;

    if (SS_State_u4ShutdownCancelReq == SS_REQUEST_EXIST)
    {
        SS_State_u4ArbitrateResult_g = SS_STATE_DO_PRERUNREENTRY;
        SS_State_u4PreRunReason      = SS_MM_VIA_POSTRUNCANCEL;
        for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
        {
            SS_State_u4PreRunRequest_PE[u4CoreId] = SS_REQUEST_INITVAL;
        }
    }
    else if (SS_State_u4ShutdownCancelReq == SS_REQUEST_NONE)
    {

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
        if (SS_State_u4PostRunRequest_g == SS_REQUEST_EXIST)
        {
            SS_State_u4ArbitrateResult_g = SS_STATE_NOTDO_HOOK;
        }
        else if (SS_State_u4PostRunRequest_g == SS_REQUEST_NONE)
        {
            SS_State_u4ArbitrateResult_g = SS_State_GetArbResultForPostRun();
        }
        else
        {
            SS_Error_notify(SS_ERROR_DATA);
        }
#else  /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */
        SS_State_u4ArbitrateResult_g = SS_STATE_NOTDO_HOOK;
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */
    }
    else
    {
        SS_Error_notify(SS_ERROR_DATA);
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_State_GetArbResultForPostRun(void)
 * [Function]	Get Arbitration Result For Exit PostRun
 * [Arguments]	None
 * [Return] 	SS_STATE_DO_SLEEP 		: Do Sleep
 *				SS_STATE_DO_SHUTDOWN	: Do Shutdown
 * [Notes]		Do not call before StartOS
 *--------------------------------------------------------------------------*/
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
static uint32 SS_State_GetArbResultForPostRun(void)
{
    uint32 u4_Result;
#if ((SS_USE_SLEEP == STD_ON) && (SS_USE_SHUTDOWN == STD_ON))
    if (SS_PM_TARGET_SHUTDOWN == SS_State_u4ShutdownTarget)
    {
        u4_Result = SS_STATE_DO_SHUTDOWN;
    }
    else if (SS_PM_TARGET_SLEEP == SS_State_u4ShutdownTarget)
    {
        u4_Result = SS_STATE_DO_SLEEP;
    }
    else
    {
        SS_Error_notify(SS_ERROR_DATA);
    }
#elif (SS_USE_SHUTDOWN == STD_ON)

    u4_Result = SS_STATE_DO_SHUTDOWN;
#else
    u4_Result = SS_STATE_DO_SLEEP;
#endif

    return u4_Result;
}
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_State_Arbitrate_CheckSleep(void)
 * [Function]	Arbitration CheckSleep for State of SS
 * [Arguments]	wakeupSource : Wakeup Source For Sleep Cancel
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
static void SS_State_Arbitrate_CheckSleep(void)
{
    
    /* Initialize Arbitrate Result */
    SS_State_u4ArbitrateResult_g = SS_STATE_ARBITRATE_ERROR;

    if (SS_State_u4ShutdownCancelReq == SS_REQUEST_EXIST)
    {
        SS_State_u4ArbitrateResult_g = SS_STATE_DO_PRERUNREENTRY;
        SS_State_u4PreRunReason      = SS_MM_VIA_SLEEPCANCEL;
    }
    else if (SS_State_u4ShutdownCancelReq == SS_REQUEST_NONE)
    {
        SS_State_u4ArbitrateResult_g = SS_STATE_DO_SLEEP;
    }
    else
    {
        SS_Error_notify(SS_ERROR_DATA);
    }

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_State_EntryModeAction(void)
 * [Function]	Action on Entry Mode
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void SS_State_EntryModeAction(void)
{

    SS_CoreIdType u4CoreId;
    uint32 *      u4State;
    uint32 *      u4ActionCmd;

    u4CoreId = SS_CpuCore_getCoreID();
    u4State  = &(SS_State_u4SystemState_PE[u4CoreId]);

#if (SS_MM_USE_ASYNC_ARB == STD_OFF)
    u4ActionCmd = &SS_State_u4ArbitrateResult_g;
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_ENTMODE_A);
#else
    u4ActionCmd = &(SS_State_u4ArbitrateResult_PE[u4CoreId]);
#endif

    switch (*u4ActionCmd)
    {
    case SS_STATE_DO_RUNENTRY:
        *u4State = SS_MM_RUN;
        
        SS_Mm_entryRunCallout();
        
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        *u4ActionCmd = SS_STATE_NOTDO_HOOK;
#endif
        break;
    case SS_STATE_DO_POSTRUNENTRY:
        *u4State = SS_MM_POSTRUN;
        
        SS_Mm_entryPostRunCallout();
        
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        *u4ActionCmd = SS_STATE_NOTDO_HOOK;
#endif
        break;
    case SS_STATE_DO_PRERUNENTRY:
        *u4State = SS_MM_PRERUN_SUP;
        
        SS_Mm_entryPreRunCallout();
        
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        *u4ActionCmd = SS_STATE_NOTDO_HOOK;
#endif
        break;
    case SS_STATE_DO_PRERUNREENTRY:
        *u4State = SS_MM_PRERUN_WUP;
        
        SS_Mm_reEntryPreRunCallout();
        
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        *u4ActionCmd = SS_STATE_NOTDO_HOOK;
#endif
        break;
    case SS_STATE_NOTDO_HOOK:
        /* do nothing */
        break;
#if (SS_USE_SHUTDOWN == STD_ON)
    case SS_STATE_DO_SHUTDOWN:
        /* do nothing */
        break;
#endif /* (SS_USE_SHUTDOWN == STD_ON) */
#if (SS_USE_SLEEP == STD_ON)
    case SS_STATE_DO_SLEEP:
        /* do nothing */
        break;
#endif /* (SS_USE_SLEEP == STD_ON) */
    default:
        SS_Error_notify(SS_ERROR_DATA);
        break;
    }

#if (SS_MM_USE_ASYNC_ARB == STD_OFF)
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_ENTMODE_B);
#endif

    return;
}

/**---------------------------------------------------------------------------
 * [Format]  	static void SS_State_EntryPhaseAction(void)
 * [Function]	Action of Entry Phase
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
static void SS_State_EntryPhaseAction(void)
{
    
    switch (SS_State_u4ArbitrateResult_g)
    {
    case SS_STATE_DO_RUNENTRY:
        /* do nothing */
        break;
    case SS_STATE_DO_POSTRUNENTRY:
        /* do nothing */
        break;
    case SS_STATE_DO_PRERUNENTRY:
        /* do nothing */
        break;
    case SS_STATE_DO_PRERUNREENTRY:
        /* do nothing */
        break;
    case SS_STATE_NOTDO_HOOK:
        /* do nothing */
        break;
#if (SS_USE_SHUTDOWN == STD_ON)
    case SS_STATE_DO_SHUTDOWN:
        SS_ISeq_shutdown();
        break;
#endif /* (SS_USE_SHUTDOWN == STD_ON) */
#if (SS_USE_SLEEP == STD_ON)
    case SS_STATE_DO_SLEEP:
        
        SS_State_EntrySleepAction();
        /* SS_State_EntrySleepActionからreturnした場合はSleepキャンセル */
        SS_State_EntryModeAction();
        break;
#endif /* (SS_USE_SLEEP == STD_ON) */
    default:
        SS_Error_notify(SS_ERROR_DATA);
        break;
    }

    return;
}
#endif /* ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON)) */

/**---------------------------------------------------------------------------
 * [Format]  	static void SS_State_EntrySleepAction(void)
 * [Function]	Action of Entry Sleep Phase
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
static void SS_State_EntrySleepAction(void)
{
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_D);
    
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_SLEEP);
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_A);

    /* Call Sleep Check Hook */
    
    SS_Pm_sleepCheckCallout();
    

    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_B);

    /* Call Arbitrare CheckSleep */
    SS_CpuCore_entryMasterSection();
    {
        SS_State_Arbitrate_CheckSleep();
    }
    SS_CpuCore_exitMasterSection();

    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_C);
    
    if (SS_State_u4ArbitrateResult_g == SS_STATE_DO_SLEEP)
    {
        SS_ISeq_sleep();
    }
    else if (SS_State_u4ArbitrateResult_g == SS_STATE_DO_PRERUNREENTRY)
    {
        /* do nothing */
    }
    else
    {
        SS_Error_notify(SS_ERROR_DATA);
    }

    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_E);
    
    SS_Pm_EnableInterruptsCallout(SS_PM_u4REQSRC_SLEEP);
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_STATE_CHKSLEEP_F);

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	Std_ReturnType SS_Pm_selectShutdownTarget(SS_Pm_shutdownTargetType u4_target)
 * [Function]	Select shutdown target
 * [Arguments]	SS_PM_TARGET_SHUTDOWN : go on to ShutdownPhase
 *				SS_PM_TARGET_SLEEP : go on to SleepPhase
 * [Return] 	E_OK : Argument is OK
 *				E_NOT_OK : Argument is error
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
#if (SS_USE_SHUTDOWN == STD_ON)
Std_ReturnType SS_Pm_selectShutdownTarget(SS_Pm_shutdownTargetType u4_target)
{
    Std_ReturnType u1_Result;

    u1_Result = E_NOT_OK;

    if ((u4_target == SS_PM_TARGET_SLEEP) || (u4_target == SS_PM_TARGET_SHUTDOWN))
    {
        SS_State_u4ShutdownTarget = u4_target;
        u1_Result                 = E_OK;
    }

    return u1_Result;
}
#endif /* (SS_USE_SHUTDOWN == STD_ON) */
#endif /* (SS_USE_SLEEP == STD_ON) */

static void SS_State_ArbitrateRequest_PE(void)
{

    SS_CoreIdType u4CoreId;

    uint32 u4LeavePreRunCnt;
    uint32 u4LeaveRunCnt;
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    uint32 u4LeavePostRunCnt;
#endif

    u4LeavePreRunCnt = 0UL;
    u4LeaveRunCnt    = 0UL;
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    u4LeavePostRunCnt = 0UL;
#endif
    /* 状態維持要求なしのコア数をカウント */
    for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
    {
        if (SS_State_u4PreRunRequest_PE[u4CoreId] == SS_REQUEST_NONE)
        {
            u4LeavePreRunCnt++;
        }
        if (SS_State_u4RunRequest_PE[u4CoreId] == SS_REQUEST_NONE)
        {
            u4LeaveRunCnt++;
        }
#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
        if (SS_State_u4PostRunRequest_PE[u4CoreId] == SS_REQUEST_NONE)
        {
            u4LeavePostRunCnt++;
        }
#endif
    }

    /* 全コア状態維要求なしならグローバルフラグに反映 */
    if (u4LeavePreRunCnt == SS_USE_CORE_COUNT)
    {
        SS_State_u4PreRunRequest_g = SS_REQUEST_NONE;
    }

    if (u4LeaveRunCnt == SS_USE_CORE_COUNT)
    {
        SS_State_u4RunRequest_g = SS_REQUEST_NONE;
    }

#if ((SS_USE_SLEEP == STD_ON) || (SS_USE_SHUTDOWN == STD_ON))
    if (u4LeavePostRunCnt == SS_USE_CORE_COUNT)
    {
        SS_State_u4PostRunRequest_g = SS_REQUEST_NONE;
    }
#endif
    return;
}

#if (SS_MM_USE_ASYNC_ARB == STD_ON)

static void SS_State_distributeArbitrateResult(void)
{

    SS_CoreIdType u4CoreId;

    if (SS_State_u4ArbitrateResult_g == SS_STATE_DO_PRERUNENTRY ||
        SS_State_u4ArbitrateResult_g == SS_STATE_DO_RUNENTRY ||
        SS_State_u4ArbitrateResult_g == SS_STATE_DO_POSTRUNENTRY ||
        SS_State_u4ArbitrateResult_g == SS_STATE_DO_PRERUNREENTRY)
    {
        for (u4CoreId = 0UL; u4CoreId < SS_USE_CORE_COUNT; u4CoreId++)
        {
            SS_State_u4ArbitrateResult_PE[u4CoreId] = SS_State_u4ArbitrateResult_g;
        }
    }
    return;
}

#endif /* (SS_MM_USE_ASYNC_ARB == STD_ON) */

#endif /* (SS_USE_MODE == STD_ON) */