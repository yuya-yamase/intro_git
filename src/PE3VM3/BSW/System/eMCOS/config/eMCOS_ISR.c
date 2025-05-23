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

#include <Ecu_Memmap_SdaDisableE_env.h>
/*----------------------------------------------------------------------------
 *		Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM2TINT);
ISR(eMCOS_ISR_INTOSTM3TINT);
ISR(eMCOS_ISR_INTP4);
ISR(eMCOS_ISR_INTRLIN311UR1);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
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
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRLIN311UR1)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRLIN311UR1)
{
    /*    INTRLIN311_ISR;*/
}
#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
