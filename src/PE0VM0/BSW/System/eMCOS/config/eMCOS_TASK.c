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
#include "oxsec.h"
#include "vCryPx.h"

#if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1))
#include "throughput.h"
#endif

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

#if (__AIP_THROUGHPUT__ != 1)
/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_High
 * [Function]	TASK_High
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_High)
{
#if (OXSEC_MAIN_HIGH == 1U)
    vd_g_oXSECMainPreHigh();
    BswM_CS_MainFunctionHigh();
    vd_g_vCryPx_MainFunction();
    vd_g_oXSECMainPosHigh();
#else
    BswM_CS_MainFunctionHigh();
#endif /* #if (OXSEC_MAIN_HIGH == 1U) */
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

#else /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/**---------------------------------------------------------------------------
 * [Format] 	eMCOS_TASK_High
 * [Function]	TASK_High
 * [Arguments]	None
 * [Return] 	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
TASK(eMCOS_TASK_High)
{
    vd_g_ThroughputIntrptStart();

#if (OXSEC_MAIN_HIGH == 1U)
    vd_g_oXSECMainPreHigh();
    BswM_CS_MainFunctionHigh();
    vd_g_vCryPx_MainFunction();
    vd_g_oXSECMainPosHigh();
#else
    BswM_CS_MainFunctionHigh();
#endif /* #if (OXSEC_MAIN_HIGH == 1U) */

    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_EMCOS_TASK_HIGH);

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
    vd_g_ThroughputIntrptStart();
    vd_g_SchdlrMainTask();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_EMCOS_TASK_MEDIUM);

    (void)TerminateTask();
}
#endif /* #if (__AIP_THROUGHPUT__ != 1) */

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
