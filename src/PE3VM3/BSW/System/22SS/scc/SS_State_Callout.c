/*****************************************************************************
 *	Copyright DENSO Corporation and AUBASS Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_State_Callout.c
 * [Module] 		System State Management
 * [Function]		SS_State
 * [Revision]		1.10
 * [Notes]			Customize file
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <SS_State_Callout.h>
#ifdef ECU_SAMPLE_ON
#include <Ecu_App.h>
#endif
#include <Ecu_Intg.h>
#include <Ecu_Arb.h>
/* ^^ include end ^^ */
/* vv extern start vv */
/* ^^ extern end ^^ */

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableE_env.h>
/* ^^ include end ^^ */

#if (SS_USE_MODE == STD_ON)
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_entryRunCallout(void)
 * [Function]	Hook to notify users of the state of SS enters Run
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Mm_entryRunCallout(void)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_entryRUN();
#endif
    Ecu_Arb_init();
    Ecu_Arb_clearWkUpFctr(); /* Wfdで置き換え予定 */
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_entryPostRunCallout(void)
 * [Function]	Hook to notify users of the state of SS enters PostRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Mm_entryPostRunCallout(void)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_entryPOSTRUN();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_entryPreRunCallout(void)
 * [Function]	Hook to notify users of the state of SS enters PreRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Mm_entryPreRunCallout(void)
{
    
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_entryPRERUN();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_reEntryPreRunCallout(void)
 * [Function]	Hook to notify users of the state of SS re-enters PreRun
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Mm_reEntryPreRunCallout(void)
{
    /* vv User Hook start vv */
#ifdef ECU_SAMPLE_ON
    Ecu_App_reEntryPRERUN();
#endif
    /* ^^ User Hook end   ^^ */
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Mm_preArbitrationCallout(void)
 * [Function]	システム状態調停直前のタイミングを提供する
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Mm_preArbitrationCallout(void)
{
    /* vv User Hook start vv */

    {
        SS_Mm_modeType u4_State;

        u4_State = SS_Mm_getMode();
        (void)Ecu_Intg_arbitrate(u4_State);
#ifdef ECU_SAMPLE_ON
        (void)Ecu_App_arbitrate(u4_State);
#endif
    }
    /* ^^ User Hook end   ^^ */
    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)) */

#if (SS_USE_SLEEP == STD_ON)
/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_sleepCheckCallout(void)
 * [Function]	Hook to notify users of Sleep check
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_sleepCheckCallout(void)
{
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

#endif /* (SS_USE_MODE == STD_ON) */
