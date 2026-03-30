/**
 * @file
 **********************************************************************************************
 * @brief Extended MAC CSAI implementation.
 *
 **********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved
 **********************************************************************************************/

/* *** prologue *******************************************************************************/

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_EXTENDED
 * @{
 */

/* *** includes *******************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_mac_extended.h"
#include "ecy_hsm_applet_mac_verify.h"
#include "ecy_hsm_applet_manager.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local variables ************************************************************************/

/* *** local function prototypes **************************************************************/

/* *** public implementation ******************************************************************/

/* [$Satisfies $DD 2928] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_MacVerifyExtended(ecy_hsm_Csai_SessionHandleT                         hSession,
                                                   ecy_hsm_Csai_JobPriorityT                           priority,
                                                   ecy_hsm_Csai_MacVerifyExtended_ParamSetAndVersionT* pParams,
                                                   ecy_hsm_Csai_JobHandleT*                            phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, ecy_hsm_APPLET_MACVERIFY_STATE_EXTENDED_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* *** private implementation *****************************************************************/

/* *** epilogue *******************************************************************************/

/**
 * @} // GROUP_CSAI_MAC_VERIFY_EXTENDED
 */
