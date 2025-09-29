/**
 * @file
 ***********************************************************************************************
 * @brief Private header for Callout functions which should not be publicly available
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_Service] */

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_SRV_HOST_HWCSP_CALLOUT_H
#define ECY_HSM_SRV_HOST_HWCSP_CALLOUT_H

/**
 * @addtogroup GROUP_SRV_HOST_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_general_host_cfg.h"
#include "ecy_hsm_csai_host_hwcsp_callout.h"
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
# include "ecy_hsm_csai.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * [$DD 2720]
 * @brief Set Callout functions for Get/Release resource for one workspace
 *
 * @note: Number of Hardware Instances for known targets: STSR6P5/P6/P7: 4, STSR6P2/P3: 2
 *
 * [$Satisfies $SW_ARCH 92F364BA]
 *
 * @param hostWksp          ID of the hardware resource. This is an ascending number from 0 to (Number of HW instances - 1).
 * @param pGetResource      Function pointer for the Get function.
 *                          Function pointers may be both nullpointer to disable the Callout functionality.
 *                          One function pointer being nullpointer and one being valid is not supported.
 * @param pReleaseResource  Function pointer for the Release function.
 * @return ecy_hsm_Csai_ErrorT
 * - @ref ecy_hsm_CSAI_SUCCESS                      The call succeeded, the passed function pointers are saved
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            One of the passed parameters was invalid
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED    The currently saved Resource could not be locked via the stored Get function pointer.
 *                                                  Likely an operation is running on this instance.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_HostHwCspSrv_ConfigureCallouts(ecy_hsm_Csai_WorkspaceIdT          hostWksp,
                                       ecy_hsm_HostHwCsp_GetResourceT     pGetResource,
                                       ecy_hsm_HostHwCsp_ReleaseResourceT pReleaseResource);

/**
 * [$DD 2699]
 * @brief Call the GetResource function for the passed workspace
 *
 * [$Satisfies $SW_ARCH 2D14875B]
 *
 * @param hostWksp                                  ID of the hardware resource. This is an ascending number from 0 to (Number of HW instances - 1).
 * @return ecy_hsm_Csai_ErrorT
 * - @ref ecy_hsm_CSAI_SUCCESS                      The call succeeded, the resource has been locked (or no Callout has been configured
 *                                                  using ecy_hsm_HostHwCspSrv_ConfigureCallouts for the passed host workspace ID)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            hostWksp was higher than possible
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED    The currently saved Resource could not be locked via the stored Get function pointer.
 *                                                  Likely an operation is already running on this instance.
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostHwCspSrv_GetCallout(ecy_hsm_Csai_WorkspaceIdT hostWksp);

/**
 * [$DD 2700]
 * @brief Call the ReleaseResource function for the passed workspace
 *
 * [$Satisfies $SW_ARCH 632FC606]
 *
 * @warning This function performs no checks on its input parameters to increase performance. All the checks it could do have already been done by
 * ecy_hsm_HostHwCspSrv_GetCallout, which must have been called before ecy_hsm_HostHwCspSrv_ReleaseCallout anyway.
 *
 * @param hostWksp                                  ID of the hardware resource. This is an ascending number from 0 to (Number of HW instances - 1).
 */
void ecy_hsm_HostHwCspSrv_ReleaseCallout(ecy_hsm_Csai_WorkspaceIdT hostWksp);

/** @} */ // GROUP_SRV_HOST_HWCSP

#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */
#endif /* ECY_HSM_SRV_HOST_HWCSP_CALLOUT_H */
