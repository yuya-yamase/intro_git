/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Error_Callout.c
 * [Module]			Error
 * [Function]		Error
 * [Revision]       1.10
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
/* ^^ include end ^^ */
#include <SS_Error_Callout.h>
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
 * [Format]		void SS_Error_bSyncCallout(SS_ErrorFactorType u4_Factor)
 * [Function]	Error Hook
 * [Arguments]	SS_ErrorFactorType u4_Factor : Error Factor
 * [Return]		None
 * [Notes]		Reset MCU after this hook process
 * 				Never use OS APIs in this Callout
 *--------------------------------------------------------------------------*/
void SS_Error_bSyncCallout(SS_ErrorFactorType u4_Factor)
{
    /* SS_TEST_GET_ERROR_FACTOR */
    /* SS_TP_ERRORSS_CALLOUT_B */
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_immCallout(SS_ErrorFactorType u4_Factor)
 * [Function]	Error Hook
 * [Arguments]	SS_ErrorFactorType u4_Factor : Error Factor
 * [Return]		None
 * [Notes]		Reset MCU after this hook process
 * 				Never use OS APIs in this Callout
 *--------------------------------------------------------------------------*/
void SS_Error_immCallout(SS_ErrorFactorType u4_Factor)
{
    /* SS_TEST_GET_ERROR_FACTOR */
    /* SS_TP_ERRORSS_CALLOUT_B */
    /* vv User Hook start vv */
    /* ^^ User Hook end   ^^ */

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Error_ResetCallout(void)
 * [Function]	Error Hook
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Error_ResetCallout(void)
{
#ifdef ECU_SAMPLE_ON
    /* ユーザが実装したSS異常時処理を行います */
    Ecu_Intg_performSTReset(ECU_INTG_ST_RESET_HARD, ECU_INTG_ST_RESET_BY_SS);
#endif

    /* 実装想定：無限ループでWDG or Ecu_Intg_performSTReset */

    return;
}
