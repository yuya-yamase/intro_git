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
#include "L3R_Scheduler.h"

#include <Ecu_Memmap_SdaDisableE_env.h>

/* Processing load */
#include "gpt_drv_frt.h"
/* Processing load */

/*----------------------------------------------------------------------------
 *		ProtoTypes
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Idle);
TASK(eMCOS_TASK_High);
TASK(eMCOS_TASK_Medium);

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
/* Processing load */
static volatile U4              u4_s_time_Task_High[10000];
static U4                       u4_s_timecnt_Task_High;

static volatile U4              u4_s_time_TASK_Medium[2000];
static U4                       u4_s_timecnt_TASK_Medium;
/* Processing load */

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
/* Processing load */
    U4                  u4_t_sta_Task_High;
    U4                  u4_t_end_Task_High;

    SuspendAllInterrupts();
    u4_t_sta_Task_High = u4_g_Gpt_FrtGetUsElapsed((void *)0) & (U4)0x7fffffffU;
/* Processing load */

    BswM_CS_MainFunctionHigh();
    L3R_System_DriverTask();

/* Processing load */
    u4_t_end_Task_High = u4_g_Gpt_FrtGetUsElapsed((void *)0);
    ResumeAllInterrupts();

    if(u4_s_timecnt_Task_High < (U4)10000U){
        u4_s_time_Task_High[u4_s_timecnt_Task_High] = (U4)((u4_t_end_Task_High - u4_t_sta_Task_High) & (U4)0x7fffffffU);
        u4_s_timecnt_Task_High++;
    }    
/* Processing load */
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
/* Processing load */
    U4                  u4_t_sta_Task_Medium;
    U4                  u4_t_end_Task_Medium;
 
    SuspendAllInterrupts();
    u4_t_sta_Task_Medium = u4_g_Gpt_FrtGetUsElapsed((void *)0) & (U4)0x7fffffffU;
/* Processing load */

    vd_g_SchdlrMainTask();

/* Processing load */
    u4_t_end_Task_Medium = u4_g_Gpt_FrtGetUsElapsed((void *)0);
    ResumeAllInterrupts();
    
    if(u4_s_timecnt_TASK_Medium < (U4)2000U){
        u4_s_time_TASK_Medium[u4_s_timecnt_TASK_Medium] = (U4)((u4_t_end_Task_Medium - u4_t_sta_Task_Medium) & (U4)0x7fffffffU);
        u4_s_timecnt_TASK_Medium++;
    }
/* Processing load */
    (void)TerminateTask();
}

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
