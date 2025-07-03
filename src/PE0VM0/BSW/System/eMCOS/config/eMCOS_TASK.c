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

/*----------------------------------------------------------------------------
 *		ProtoTypes
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Idle);
TASK(eMCOS_TASK_High);
TASK(eMCOS_TASK_Medium);

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

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
    BswM_CS_MainFunctionHigh();
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
    vd_g_SchdlrMainTask();
    (void)TerminateTask();
}

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
