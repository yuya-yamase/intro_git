/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ResetM_Callout.c
 * [Module]			ResetM
 * [Function]		Manage reset
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
/* ^^ include end ^^ */
#include <SS_ResetM_Callout.h>
/* vv extern start vv */
/* ^^ extern end ^^ */
/* SS_TP_INCLUDE */
/* vv include start vv */
#include <Ecu_Memmap_SdaDisableE_env.h>
/* ^^ include end ^^ */

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_resetCallout(void)
 * [Function]	コア間同期リセットをする前のタイミングを提供する
 * [Arguments]	None
 * [Return]		None
 * [Notes]		Never use OS APIs in this Callout.
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
void SS_Pm_resetCallout(void)
{
    /* SS_TP_RESET_CALLOUT_B */
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */
    return;
}
#endif
