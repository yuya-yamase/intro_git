/**
 * @file
 ***********************************************************************************************
 * @brief Public header for Callout functions which should be publicly available
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_CSAI] */

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_CSAI_HOST_HWCSP_CALLOUT_H
#define ECY_HSM_CSAI_HOST_HWCSP_CALLOUT_H

/**
 * @addtogroup GROUP_CSAI_HOST_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/
/**
 * @brief Type of getResource function: void parameter, uint32 return
 *
 * @return uint32 ecy_hsm_CSAI_SUCCESS (0UL) if locking was successful, any other value otherwise
 */
typedef uint32 ecy_hsm_HostHwCsp_GetResourceT(void);

/**
 * @brief Type of releaseResource function: void parameter, void return
 */
typedef void ecy_hsm_HostHwCsp_ReleaseResourceT(void);
/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * [$DD 2698]
 * @brief Set Callout functions for Get/Release resource for one workspace
 *
 * @note: Number of Hardware Instances for known targets: STSR6P5/P6/P7: 4, STSR6P2/P3: 2
 *
 * [$Satisfies $SW_ARCH ECF48608]
 *
 * @param hostWksp          ID of the hardware resource. This is an ascending number from 0 to (Number of HW instances - 1).
 * @param pGetResource      Function pointer for the Get function.
 *                          The passed function shall return ecy_hsm_CSAI_SUCCESS (0UL) if locking was successful and any other value otherwise.
 *                          Function pointers may be both nullpointer to disable the Callout functionality
 *                          One function pointer being nullpointer and one being valid is not supported.
 * @param pReleaseResource  Function pointer for the Release function.
 * @return ecy_hsm_Csai_ErrorT
 * - @ref ecy_hsm_CSAI_SUCCESS                      The call succeeded, the passed function pointers are saved
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            One of the passed parameters was invalid
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED    The currently saved Resource could not be locked via the stored Get function pointer.
 *                                                  Likely an operation is running on this instance.
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            This function is not enabled in VMS.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_ConfigureCallouts(ecy_hsm_Csai_WorkspaceIdT          hostWksp,
                                         ecy_hsm_HostHwCsp_GetResourceT     pGetResource,
                                         ecy_hsm_HostHwCsp_ReleaseResourceT pReleaseResource);

/** @} */ // GROUP_CSAI_HOST_HWCSP

#endif /* ECY_HSM_CSAI_HOST_HWCSP_CALLOUT_H */
