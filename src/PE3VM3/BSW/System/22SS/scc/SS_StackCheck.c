/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		StackCheck.c
 * [Module]			StackCheck
 * [Function]		StackCheck
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
#include <SS_MemmapProtect_Env.h>

#include <SS_StackCheck_StackTop0Data.h>
#include <SS_StackCheck_StackBottom0Data.h>
#if (SS_USE_CORE_COUNT >= 2u)
#include <SS_StackCheck_StackTop1Data.h>
#include <SS_StackCheck_StackBottom1Data.h>
#endif
#if (SS_USE_CORE_COUNT >= 3u)
#include <SS_StackCheck_StackTop2Data.h>
#include <SS_StackCheck_StackBottom2Data.h>
#endif
#if (SS_USE_CORE_COUNT >= 4u)
#include <SS_StackCheck_StackTop3Data.h>
#include <SS_StackCheck_StackBottom3Data.h>
#endif
#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_CpuCore.h>
#include <SS_Error.h>
#include <SS_StackCheck.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_STACKCHECK_u4STACKCHECKCODE (0xA55AA55AUL)

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Constant Variables
 *--------------------------------------------------------------------------*/

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		void SS_StackCheck_init(void)
 * [Function]	Initialize top and bottom of stack
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
void SS_StackCheck_init(void)
{
#if (SS_USE_CORE_COUNT >= 2u)
    SS_CoreIdType u4_CoreId;

    u4_CoreId = SS_CpuCore_getCoreID();
    if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
#endif
    {
        SS_StackCheck_u4StackTop_0    = SS_STACKCHECK_u4STACKCHECKCODE;
        SS_StackCheck_u4StackBottom_0 = SS_STACKCHECK_u4STACKCHECKCODE;
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
        SS_StackCheck_u4StackTop_1    = SS_STACKCHECK_u4STACKCHECKCODE;
        SS_StackCheck_u4StackBottom_1 = SS_STACKCHECK_u4STACKCHECKCODE;
    }
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
        SS_StackCheck_u4StackTop_2    = SS_STACKCHECK_u4STACKCHECKCODE;
        SS_StackCheck_u4StackBottom_2 = SS_STACKCHECK_u4STACKCHECKCODE;
    }
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
        SS_StackCheck_u4StackTop_3    = SS_STACKCHECK_u4STACKCHECKCODE;
        SS_StackCheck_u4StackBottom_3 = SS_STACKCHECK_u4STACKCHECKCODE;
    }
#endif
#endif
    else
    {
        // is not target core. nothing to do
    }
#endif

    return;
}
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		void SS_StackCheck_exec(void)
 * [Function]	Check top and bottom of stack
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
void SS_StackCheck_exec(void)
{
#if (SS_USE_CORE_COUNT >= 2u)
    SS_CoreIdType u4_CoreId;

    u4_CoreId = SS_CpuCore_getCoreID();
    if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
#endif
    {
        if ((SS_StackCheck_u4StackBottom_0 != SS_STACKCHECK_u4STACKCHECKCODE) ||
            (SS_StackCheck_u4StackTop_0 != SS_STACKCHECK_u4STACKCHECKCODE))

        {
            SS_Error_notify(SS_ERROR_STACKCHECK);
        }
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
        if ((SS_StackCheck_u4StackBottom_1 != SS_STACKCHECK_u4STACKCHECKCODE) ||
            (SS_StackCheck_u4StackTop_1 != SS_STACKCHECK_u4STACKCHECKCODE))

        {
            SS_Error_notify(SS_ERROR_STACKCHECK);
        }
    }
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
        if ((SS_StackCheck_u4StackBottom_2 != SS_STACKCHECK_u4STACKCHECKCODE) ||
            (SS_StackCheck_u4StackTop_2 != SS_STACKCHECK_u4STACKCHECKCODE))

        {
            SS_Error_notify(SS_ERROR_STACKCHECK);
        }
    }
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
        if ((SS_StackCheck_u4StackBottom_3 != SS_STACKCHECK_u4STACKCHECKCODE) ||
            (SS_StackCheck_u4StackTop_3 != SS_STACKCHECK_u4STACKCHECKCODE))

        {
            SS_Error_notify(SS_ERROR_STACKCHECK);
        }
    }
#endif
#endif
    else
    {
        // is not target core. nothing to do
    }
#endif

    return;
}
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */
