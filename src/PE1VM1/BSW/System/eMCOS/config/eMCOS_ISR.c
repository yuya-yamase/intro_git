/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		eMCOS_ISR.c
 * [Module]			ISR body of eMCOS configuration
 * [Function]		ISR body implementation
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>


#include "scheduler.h"

#if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1))
#include "throughput.h"
#endif

#include <Ecu_Memmap_SdaDisableE_env.h>
/*----------------------------------------------------------------------------
 *		Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM6TINT);
ISR(eMCOS_ISR_INTOSTM0TINT);
ISR(eMCOS_ISR_INTSDMAC1CH0);
ISR(eMCOS_ISR_INTSDMAC1CH1);
ISR(eMCOS_ISR_INTSDMAC1CH2);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"

#if (__AIP_THROUGHPUT__ != 1)
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM6TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM6TINT)
{
    vd_g_SchdlrMainTick();
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM0TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM0TINT)
{
    /*    INTOSTM0_ISR;*/
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH0)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH0)
{
    /* INTSDMAC1CH0 */
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH1)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH1)
{
    /* INTSDMAC1CH1 */
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH2)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH2)
{
    /* INTSDMAC1CH2 */
}

#else /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM6TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM6TINT)
{
    vd_g_ThroughputIntrptStart();
    vd_g_SchdlrMainTick();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM6TINT);
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM0TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM0TINT)
{
    /*    INTOSTM0_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM0TINT);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH0)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH0)
{
    /* INTSDMAC1CH0 */
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTSDMAC1CH0);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH1)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH1)
{
    /* INTSDMAC1CH1 */
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTSDMAC1CH1);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTSDMAC1CH2)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTSDMAC1CH2)
{
    /* INTSDMAC1CH2 */
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTSDMAC1CH2);
}
#endif /* #if (__AIP_THROUGHPUT__ != 1) */

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
