/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_Task.c
 * [Module]		Ecu_Task
 * [Function]		Ecu_Task
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>
#if (SS_INTG_ASR_PKG == SS_INTG_AB)
#include <mcos/mcos_ar.h>
#endif

/* #include <Wdg.h> */
#if (SS_INTG_ASR_PKG == SS_INTG_VC)
#include <SchM_BswM.h>
#include <SchM_EcuM.h>
#endif

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Internal.h>

#include <Ecu_CtgOs.h>

#include <Ecu_Task.h>
#ifdef ECU_SAMPLE_ON
#include <Ecu_App.h>
#include <Ecu_Port.h>
#endif
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_Int.h>

#if (SS_INTG_RTE != STD_ON)
TASK(Ecu_InitTask);
TASK(Ecu_IdleTask);
TASK(Task_MM_High);
//  TASK(Task_MM_MediumHigh);
TASK(Task_MM_Medium);
// TASK(Task_MM_MediumLow);
TASK(Task_MM_Low);

#if ((SS_INTG_ASR_PKG == SS_INTG_AB) && (ECU_SQT_ENV == STD_OFF))
TASK(Task_TEST);
#endif
#else
static void Ecu_HighTask(void);
static void Ecu_MediumTask(void);
static void Ecu_MediumLowTask(void);
static void Ecu_LowTask(void);

#endif /* (SS_INTG_RTE != STD_ON) */


#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *		ProtoTypes
 *--------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format] 	void Ecu_HighTask(void)
 * [Function]	Ecu_HighTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_HighTask(void)
{

    
    
    
#ifdef ECU_SAMPLE_ON
    Ecu_Port_out(ECU_SIG_HI, u1PRT_OUT_INV);
#endif

    //
    // BSW/CDD input&output step
    //
    Ecu_Intg_mainFuncCddHigh();

    return;
}
#if 0u
/**---------------------------------------------------------------------------
 * [Format] 	void Ecu_MediumHighTask(void)
 * [Function]	Ecu_MediumHighTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_MediumHighTask(void)
{
    
#ifdef ECU_SAMPLE_ON
    Ecu_Port_out(ECU_SIG_MIDHI, u1PRT_OUT_INV);
#endif
    
    
    
    

    return;
}
#endif
/**---------------------------------------------------------------------------
 * [Format] 	void Ecu_MediumTask(void)
 * [Function]	Ecu_MediumTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_MediumTask(void)
{
    

#ifdef ECU_SAMPLE_ON
    Ecu_Port_out(ECU_SIG_MID, u1PRT_OUT_INV);
#endif

    /* Wdg_SetTriggerCondition(30U); */

    //
    // BSW/CDD input step
    //
    Ecu_Intg_mainFuncCddMidIn();

    //
    // APP processing step
    //
    Ecu_Intg_mainFuncApp();

    //
    // mode arbitrationstep step
    //

#if (SS_USE_MODE == STD_ON)
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
    SS_Mm_mainFunction();
#else
    {
        SS_Mm_modeType u4_State;
        u4_State = SS_Mm_getMode();
        (void)Ecu_Intg_arbitrate(u4_State);
    }
#endif
#elif (SS_USE_MODE == STD_OFF)
#if (SS_USE_UP == STD_ON)
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
    SS_Pm_mainFunction();
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */
#endif /* (SS_USE_UP == STD_ON) */
#endif
#if (SS_INTG_ASR_PKG == SS_INTG_VC)
    /* call runnable */
    EcuM_MainFunction();
    BswM_MainFunction();
#endif /* SS_INTG_ASR_PKG == SS_INTG_VC */

    //
    // BSW/CDD output step
    //
    Ecu_Intg_mainFuncCddMidOut();

    return;
}

#if 0u /* for future extention */
/**---------------------------------------------------------------------------
 * [Format] 	void Ecu_MediumLowTask(void)
 * [Function]	MediumLowTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_MediumLowTask(void)
{
    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format] 	void Ecu_LowTask(void)
 * [Function]	RefreshTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_LowTask(void)
{
    
    
    
#ifdef ECU_SAMPLE_ON
    Ecu_Port_out(ECU_SIG_LO, u1PRT_OUT_INV);
    Ecu_App_refresh();
#endif

    SS_CpuCore_entryMasterSection();
    {
        // Ecu_Int_refresh();
        // Ecu_Int_refreshEcc();
        Ecu_Int_refreshMcu();
    }
    SS_CpuCore_exitMasterSection();

#if (SS_INTG_ASR_PKG == SS_INTG_AB)
    SS_CpuCore_entryMasterSection();
    {
        mcos_refresh_err_t s4_CheckVal;

        s4_CheckVal = mcos_refresh_register_values(FALSE);
        if (s4_CheckVal != MCOS_E_REFRESH_OK)
        {
            Ecu_Int_performReset();
        }
    }
    SS_CpuCore_exitMasterSection();
#endif /* SS_INTG_ASR_PKG == SS_INTG_AB */

    
    
    
    SS_SafetyM_mainFunction();
    
    
    

#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)
#if (SS_USE_MODE == STD_ON)
    SS_Mm_transit();
#else
    SS_Pm_transit();
#endif /* (SS_USE_MODE == STD_ON) */
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT) */

    /* SS_TEST_SETFLAG_REFRESH_TASK */
    /* SS_TEST_REFRESH_SECOND_CALL */

    Ecu_Intg_mainFuncCddLow();

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	TASKEcu_InitTask
 * [Function]	InitializeTask
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		Launched from the OS
 *--------------------------------------------------------------------------*/
TASK(Ecu_InitTask)
{
    
#if (SS_INTG_RTE != STD_ON)
    (void)SetRelAlarm((AlarmType)ECU_u2HIGHTASK_ALM,
                      (TickType)ECU_TASK_u4ALARMOFFSET,
                      (TickType)ECU_TASK_u4HIGHTASK_ACTIVATECYCLE);
    (void)SetRelAlarm((AlarmType)ECU_u2MEDIUMTASK_ALM,
                      (TickType)ECU_TASK_u4ALARMOFFSET,
                      (TickType)ECU_TASK_u4MEDIUMTASK_ACTIVATECYCLE);
    (void)SetRelAlarm((AlarmType)ECU_u2LOWTASK_ALM,
                      (TickType)ECU_TASK_u4ALARMOFFSET,
                      (TickType)ECU_TASK_u4LOWTASK_ACTIVATECYCLE);
#endif /* (SS_INTG_RTE != STD_ON) */

    
    Ecu_CtgOs_start(ECU_CTGOS_TMRES_OWNVM);

    SS_Pm_postStartOS();
    

    (void)TerminateTask();
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	Ecu_IdleTask
 * [Function]	Idle
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Ecu_IdleTask)
{
    
    while (1)
    {
#ifdef ECU_SAMPLE_ON
        Ecu_App_idle();
#endif
        Ecu_Intg_idleFuncOut();
    }
}

#if (SS_INTG_RTE == STD_ON)
#else
/**---------------------------------------------------------------------------
 * [Format] 	Task_MM_High
 * [Function]	Idle
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Task_MM_High)
{
    Ecu_HighTask();
    (void)TerminateTask();
}

#if 0u
/**---------------------------------------------------------------------------
 * [Format] 	Task_MM_MediumHigh
 * [Function]	MM_MediumHigh
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Task_MM_MediumHigh)
{
    Ecu_MediumHighTask();
    (void)TerminateTask();
}
#endif
/**---------------------------------------------------------------------------
 * [Format] 	Task_MM_Medium
 * [Function]	MM_Medium
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Task_MM_Medium)
{
    Ecu_MediumTask();
    (void)TerminateTask();
}

#if 0u /* for future extention */
/**---------------------------------------------------------------------------
 * [Format] 	Task_MM_MediumLow
 * [Function]	MM_MediumLow
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Task_MM_MediumLow)
{
    Ecu_MediumLowTask();
    (void)TerminateTask();
}
#endif

/**---------------------------------------------------------------------------
 * [Format] 	Task_MM_Low
 * [Function]	Idle
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(Task_MM_Low)
{
    Ecu_LowTask();
    (void)TerminateTask();
}

#endif /*  (SS_INTG_RTE == STD_OFF) */
