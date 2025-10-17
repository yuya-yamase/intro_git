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

#include "xspi.h"

/*----------------------------------------------------------------------------
 *		Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM2TINT);
ISR(eMCOS_ISR_INTOSTM3TINT);
ISR(eMCOS_ISR_INTP4);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"

#if (__AIP_THROUGHPUT__ != 1)
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM2TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM2TINT)
{
    vd_g_SchdlrMainTick();
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM3TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM3TINT)
{
    /*    INTOSTM3_ISR;*/
    xspi_Main( XSPI_CH_03 );
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTP4)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTP4)
{
    /*    INTP4_ISR;*/
}

#else /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM2TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM2TINT)
{
    vd_g_ThroughputIntrptStart();
    vd_g_SchdlrMainTick();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM2TINT);
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM3TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM3TINT)
{
    /*    INTOSTM3_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM3TINT);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTP4)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTP4)
{
    /*    INTP4_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTP4);
}
#endif /* #if (__AIP_THROUGHPUT__ != 1) */

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
