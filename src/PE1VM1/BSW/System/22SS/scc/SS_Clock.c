/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Clock.c
 * [Module]			Clock
 * [Function]		Management of Clock resources
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#if (SS_USE_LWH == SS_LWH_NONE)
#include <Mcu.h>
#endif /* SS_USE_LWH == SS_LWH_NONE */

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#if (SS_USE_LWH == SS_LWH_NONE)
#include <SS_Error.h>
#endif /* SS_USE_LWH == SS_LWH_NONE */
#include <SS_Clock.h>
#include <SS_Boot.h>

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_Clock_up(void)
 * [Function]	Clock_up
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_Clock_up(void)
{

    Mcu_PllStatusType ePllStatus;
    Std_ReturnType    u1InitClk;
    Std_ReturnType    u1DistributePllClk;

    
    
    u1InitClk = Mcu_InitClock(MCU_CLOCK_TYPE_0);
    
    
    

    if (u1InitClk == E_OK)
    {
        ePllStatus = MCU_PLL_UNLOCKED;
        while (ePllStatus == MCU_PLL_UNLOCKED)
        {
            ePllStatus = Mcu_GetPllStatus();
        }
        
        if (ePllStatus == MCU_PLL_LOCKED)
        {
            
            
            u1DistributePllClk = Mcu_DistributePllClock();
            
        }
    }

    if (u1InitClk != E_OK ||
        ePllStatus != MCU_PLL_LOCKED ||
        u1DistributePllClk != E_OK)
    {
        SS_Error_setFactor(SS_ERROR_CLOCK);
    }

#if (SS_USE_CORE_COUNT >= 2u)
    SS_Boot_startSlaveCore();
#endif

    return;
}
#endif /* SS_USE_LWH == SS_LWH_NONE */
