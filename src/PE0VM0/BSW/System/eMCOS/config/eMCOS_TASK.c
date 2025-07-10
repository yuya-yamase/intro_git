/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      eMCOS_TASK.c
 * [Module]         Task body of eMCOS configuration
 * [Function]       Task body implementation
 * [Notes]          None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Internal.h>

#include "scheduler.h"
#include "run_m.h"

#include "oxcan.h"
#include "oxdocan.h"

#include <Ecu_Memmap_SdaDisableE_env.h>

#if (PROCESSING_LOAD_MEASURE_TIME > 0)
#include "gpt_drv_frt.h"

#define MEASURE_TIME_TASK_1MS      (U4)(PROCESSING_LOAD_MEASURE_TIME)
#define MEASURE_TIME_TASK_5MS      (U4)(PROCESSING_LOAD_MEASURE_TIME / (U4)5U)
#endif

/*----------------------------------------------------------------------------
 *		ProtoTypes
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Idle);
TASK(eMCOS_TASK_High);
TASK(eMCOS_TASK_Medium);

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
static volatile U4              u4s_TimeTaskHigh_1ms[MEASURE_TIME_TASK_1MS] = {(U4)0U};
static U4                       u4s_TimeCntTaskHigh_1ms = (U4)0U;

static volatile U4              u4s_TimeTaskMedium_5ms[MEASURE_TIME_TASK_5MS] = {(U4)0U};
static U4                       u4s_TimeCntTaskMedium_5ms = (U4)0U;
#endif

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_Idle
 * [Function]	Idle
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Idle)
{
    SS_Pm_postStartOS();
    vd_g_RunMInit();
    vd_g_SchdlrInit();

    vd_g_SchdlrIdleTask();      /* Infinity loop here */
}

/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_High
 * [Function]	TASK_High
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_High)
{
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
    U4                  u4t_StaTaskHigh_1ms = (U4)0U;
    U4                  u4t_EndTaskHigh_1ms = (U4)0U;

    SuspendAllInterrupts();
    u4t_StaTaskHigh_1ms = u4_g_Gpt_FrtGetUsElapsed((void *)0) & (U4)0x7fffffffU;
#endif
/* Task hook start */

    BswM_CS_MainFunctionHigh();

/* Task hook end */
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
    u4t_EndTaskHigh_1ms = u4_g_Gpt_FrtGetUsElapsed((void *)0);
    ResumeAllInterrupts();

    if(u4s_TimeCntTaskHigh_1ms < MEASURE_TIME_TASK_1MS){
        u4s_TimeTaskHigh_1ms[u4s_TimeCntTaskHigh_1ms] = (U4)((u4t_EndTaskHigh_1ms - u4t_StaTaskHigh_1ms) & (U4)0x7fffffffU);
        u4s_TimeCntTaskHigh_1ms++;
    }    
#endif
    (void)TerminateTask();
}

/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_Medium
 * [Function]	TASK_Medium
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Medium)
{
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
    U4                  u4t_StaTaskMedium_5ms = (U4)0U;
    U4                  u4t_EndTaskMedium_5ms = (U4)0U;

    SuspendAllInterrupts();
    u4t_StaTaskMedium_5ms = u4_g_Gpt_FrtGetUsElapsed((void *)0) & (U4)0x7fffffffU;
#endif
/* Task hook start */

    vd_g_SchdlrMainTask();

/* Task hook end */
#if (PROCESSING_LOAD_MEASURE_TIME > 0)
    u4t_EndTaskMedium_5ms = u4_g_Gpt_FrtGetUsElapsed((void *)0);
    ResumeAllInterrupts();

    if(u4s_TimeCntTaskMedium_5ms < MEASURE_TIME_TASK_5MS){
        u4s_TimeTaskMedium_5ms[u4s_TimeCntTaskMedium_5ms] = (U4)((u4t_EndTaskMedium_5ms - u4t_StaTaskMedium_5ms) & (U4)0x7fffffffU);
        u4s_TimeCntTaskMedium_5ms++;
    }
#endif
    (void)TerminateTask();
}

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
