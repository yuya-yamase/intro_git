/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Memory.c
 * [Module]			SS_Memory
 * [Function]		Memory
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>
#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#if (SS_USE_CORE_COUNT >= 2u)
#include <SS_CpuCore.h>
#endif
#include <SS_Memory.h>
#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define SS_MEMORY_ptPRIMARYSTACKADDR_0 \
    (&__ghsbegin_ss_stack[(uint32)(SS_STACKSIZE_0 - SS_u4PRIMARYSTACKSIZE_0) / 4UL])
#if (SS_USE_CORE_COUNT >= 2u)
#define SS_MEMORY_ptPRIMARYSTACKADDR_1 \
    (&__ghsbegin_ss_stack[(uint32)(SS_STACKSIZE_1 - SS_u4PRIMARYSTACKSIZE_1) / 4UL])
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#if (SS_USE_CORE_COUNT >= 3u)
#define SS_MEMORY_ptPRIMARYSTACKADDR_2 \
    (&__ghsbegin_ss_stack[(uint32)(SS_STACKSIZE_2 - SS_u4PRIMARYSTACKSIZE_2) / 4UL])
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#if (SS_USE_CORE_COUNT >= 4u)
#define SS_MEMORY_ptPRIMARYSTACKADDR_3 \
    (&__ghsbegin_ss_stack[(uint32)(SS_STACKSIZE_3 - SS_u4PRIMARYSTACKSIZE_3) / 4UL])
#endif /* (SS_USE_CORE_COUNT >= 4u) */

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		void SS_Memory_checkPriStack(void)
 * [Function]	Check Primary Stack
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_PRISTACKCHECK == STD_ON)
void SS_Memory_checkPriStack(void)
{
#if (SS_USE_CORE_COUNT >= 2u)
    SS_CoreIdType u4CoreId;

    u4CoreId = SS_CpuCore_getCoreID();
    if (u4CoreId == SS_CPUCORE_u4MASTERCORE)
#endif /* (SS_USE_CORE_COUNT >= 2u) */
    {
        SS_Memory_writeScan(SS_MEMORY_ptPRIMARYSTACKADDR_0, SS_u4PRIMARYSTACKSIZE_0);
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE1)
    {
        SS_Memory_writeScan(SS_MEMORY_ptPRIMARYSTACKADDR_1, SS_u4PRIMARYSTACKSIZE_1);
    }
#endif /* (SS_USE_CORE_COUNT >= 2u) */
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE2)
    {
        SS_Memory_writeScan(SS_MEMORY_ptPRIMARYSTACKADDR_2, SS_u4PRIMARYSTACKSIZE_2);
    }
#endif /* (SS_USE_CORE_COUNT >= 3u) */
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4CoreId == SS_CPUCORE_u4SLAVECORE3)
    {
        SS_Memory_writeScan(SS_MEMORY_ptPRIMARYSTACKADDR_3, SS_u4PRIMARYSTACKSIZE_3);
    }
#endif /* (SS_USE_CORE_COUNT >= 4u) */
#if (SS_USE_CORE_COUNT >= 2u)
    else
    {
        /* Nothing to do */
    }
#endif /* (SS_USE_CORE_COUNT >= 2u) */

    return;
}
#endif /* (SS_USE_PRISTACKCHECK == STD_ON) */
