/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Error.c
 * [Module]			Error
 * [Function]		Error
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
#include <SS_Error.h>
#include <SS_Error_Callout.h>
#include <SS_CpuCore.h>
#include <SS_ISeq.h>
#include <SS_ISeq_Callout.h>
#include <SS_Memory.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
SS_ErrorFactorType SS_Error_u4Factor;

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_init(void)
 * [Function]	Init Error Factor
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Error_init(void)
{
    SS_Error_u4Factor = SS_ERROR_NONE;
    /* SS_TEST_MEMORY_CHECK_ERROR_INIT */
    SS_Memory_writeScan(&SS_Error_u4Factor, sizeof(SS_ErrorFactorType));
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_check(void)
 * [Function]	Error factor checking and handling
 * [Arguments]	None
 * [Return]		None
 * [Notes]		Do not call after StartOS
 *--------------------------------------------------------------------------*/
void SS_Error_check(void)
{
    
    if (SS_ERROR_NONE != SS_Error_u4Factor)
    {
        SS_ISeq_syncCores(SS_ISEQ_u2SID_ERROR_CHKHNDL_A);
#if (SS_USE_UP == STD_ON)
        SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_ERROR);
#endif /* (SS_USE_UP == STD_ON) */
        SS_ISeq_syncCores(SS_ISEQ_u2SID_ERROR_CHKHNDL_B);
        
        SS_Error_bSyncCallout(SS_Error_u4Factor);
        
        SS_ISeq_syncCores(SS_ISEQ_u2SID_ERROR_CHKHNDL_C);

        {
#if (SS_USE_CORE_COUNT >= 2u)
            SS_CoreIdType u4_CoreId;
            u4_CoreId = SS_CpuCore_getCoreID();
            if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
#endif
            {
                SS_Error_ResetCallout();
            }
#if (SS_USE_CORE_COUNT >= 2u)
            else
            {
                while (1)
                {
                    ; /* 無限ループ */
                }
            }
#endif
        }
    }
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_notify(SS_ErrorFactorType u4_Factor)
 * [Function]	Call user hook and reset
 * [Arguments]	SS_ErrorFactorType u4_Factor : Error Factor
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Error_notify(SS_ErrorFactorType u4_Factor)
{
#if (SS_USE_UP == STD_ON)
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_ERROR);
#endif /* (SS_USE_UP == STD_ON) */
    
    SS_Error_immCallout(u4_Factor);
    
    SS_Error_ResetCallout();
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_setFactor(SS_ErrorFactorType u4_Factor)
 * [Function]	Set Error Factor
 * [Arguments]	SS_ErrorFactorType u4_Factor :Error Factor
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Error_setFactor(SS_ErrorFactorType u4_Factor)
{
    SS_Error_u4Factor = u4_Factor;
    return;
}
