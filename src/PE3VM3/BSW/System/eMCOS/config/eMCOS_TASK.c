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
#warning "BEVCDCFD-822"
#if 0 /* BEVCDCFD-822 */
#include "l3r_test.h"
#endif /* BEVCDCFD-822 */

#include <Ecu_Memmap_SdaDisableE_env.h>

#include "EthSW_Task.h"

/*----------------------------------------------------------------------------
 *		ProtoTypes
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Idle);
TASK(eMCOS_TASK_High);
TASK(eMCOS_TASK_Medium);
TASK(eMCOS_TASK_Low);

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
    #warning "BEVCDCFD-822"
    #if 0 /* BEVCDCFD-822 */
    vd_g_L3rTestCycleHigh();
    #endif /* BEVCDCFD-822 */
    BswM_CS_MainFunctionHigh();
    EthSW_HighTask();

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

/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_Low
 * [Function]	TASK_Low
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_Low)
{
    EthSW_LowTask();
    (void)TerminateTask();
}

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
