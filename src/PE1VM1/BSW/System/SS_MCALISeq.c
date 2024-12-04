/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_MCALISeq.c
 * [Module]			Initialize Sequencer for SS_MCAL
 * [Function]		Initialize Sequencer for SS_MCAL
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#if (SS_USE_UP == STD_ON)
#include <Os.h>
#if (SS_INTG_ASR_PKG == SS_INTG_AB)
#include <mcos/mcos_ar.h>
#endif
#endif // (SS_USE_UP == STD_ON)
#if (SS_USE_LWH == SS_LWH_NONE)
#include <Mcu.h>
#endif /* SS_USE_LWH == SS_LWH_NONE */

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_MCALISeq.h>
#include <SS_CpuCore.h>
#include <SS_ISeq_Callout.h>
#include <SS_Boot.h>
#include <SS_Clock.h>
/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_MCALISeq_initOs(void)
 * [Function]	Initialize OS
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_UP == STD_ON)
void SS_MCALISeq_initOs(void)
{
    
#if (SS_INTG_ASR_PKG == SS_INTG_AB)

    SS_CpuCore_entryMasterSection();
    {
        mcos_initialize();
    }
    SS_CpuCore_exitMasterSection();

#if (SS_USE_CORE_COUNT >= 2u)
    {
        CoreIdType u4CoreId;
        u4CoreId = GetCoreID();

        if (u4CoreId != OS_CORE_ID_MASTER)
        {
            mcos_slave_initialize(u4CoreId);
        }
    }
#endif
#endif

    return;
}
#endif /* (SS_USE_UP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		void SS_MCALISeq_initMcu(void)
 * [Function]	Initialize OS
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_MCALISeq_initMcu(void)
{
    Mcu_Init((Mcu_ConfigType *)NULL_PTR);
    return;
}
#endif /* SS_USE_LWH == SS_LWH_NONE */

#if (SS_USE_SLEEP == STD_ON)

/**---------------------------------------------------------------------------
 * [Format]		void SS_MCALISeq_goStandby(void)
 * [Function]	Go to standby mode at first sleep
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_MCALISeq_goStandby(void)
{
    

    
    
    
    Mcu_SetMode(MCU_MODE_DEEPSTOP);

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_MCALISeq_goReStandby(void)
 * [Function]	Go to standby mode at re-sleep
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_MCALISeq_goReStandby(void)
{
    
    Mcu_SetMode(MCU_MODE_DEEPSTOP);

    return;
}

#endif /* (SS_USE_SLEEP == STD_ON) */
