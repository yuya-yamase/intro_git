/**
 * @file
 ***********************************************************************************************
 * @brief Implementation of public and private functions for Host HwCsp Callout
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_CSAI] */

/* *** prologue  ******************************************************************************/

/**
 * @addtogroup GROUP_CSAI_HOST_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_host_hwcsp_callout.h"
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
# include "ecy_hsm_srv_host_hwcsp_callout.h"
#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local function prototypes **************************************************************/

/* *** local variables ************************************************************************/

/* *** public implementation  *****************************************************************/

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_ConfigureCallouts(ecy_hsm_Csai_WorkspaceIdT          hostWksp,
                                         ecy_hsm_HostHwCsp_GetResourceT     pGetResource,
                                         ecy_hsm_HostHwCsp_ReleaseResourceT pReleaseResource)
{
    ecy_hsm_Csai_ErrorT errorCode;
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
    errorCode = ecy_hsm_HostHwCspSrv_ConfigureCallouts(hostWksp, pGetResource, pReleaseResource);
#else
    CSAI_PARAM_UNUSED(hostWksp);
    CSAI_PARAM_UNUSED(pGetResource);
    CSAI_PARAM_UNUSED(pReleaseResource);
    errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */
    return errorCode;
}

/* *** private implementation  ****************************************************************/

/* *** epilogue  ******************************************************************************/

/** @} */ // GROUP_CSAI_HOST_HWCSP
