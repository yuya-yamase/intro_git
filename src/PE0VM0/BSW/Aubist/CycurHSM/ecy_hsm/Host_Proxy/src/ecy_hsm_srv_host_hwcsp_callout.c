/**
 * @file
 ***********************************************************************************************
 * @brief Implementation of public and private functions for Host HwCsp Callout
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_Service] */

/* *** prologue  ******************************************************************************/

/**
 * @addtogroup GROUP_SRV_HOST_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_general_host_cfg.h"
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
# include "ecy_hsm_csai_error.h"
# include "ecy_hsm_srv_host_hwcsp_callout.h"
# include "ecy_hsm_hwcsp_keystore_cfg_arch.h"
# include "ecy_hsm_csai_host_hwcsp_callout.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local function prototypes **************************************************************/
/**
 * @brief Dummy Resource Get function. Always returns ecy_hsm_CSAI_SUCCESS
 *
 * @return uint32 ecy_hsm_CSAI_SUCCESS
 */
static uint32 dummy_get(void);

/**
 * @brief Dummy Resource Release function. Does not do anything
 *
 * @return void
 */
static void dummy_release(void);

/* *** local variables ************************************************************************/
/** Array for saving the get Resource Callout functions */
static ecy_hsm_HostHwCsp_GetResourceT* getResourceArray[ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES];
/** Array for saving the release Resource Callout functions */
static ecy_hsm_HostHwCsp_ReleaseResourceT* releaseResourceArray[ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES];

# if (4U == ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES)
static ecy_hsm_HostHwCsp_GetResourceT*     getResourceArray[]     = {dummy_get, dummy_get, dummy_get, dummy_get};
static ecy_hsm_HostHwCsp_ReleaseResourceT* releaseResourceArray[] = {dummy_release, dummy_release, dummy_release, dummy_release};
# elif (7U == ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES)
static ecy_hsm_HostHwCsp_GetResourceT*     getResourceArray[]     = {dummy_get, dummy_get, dummy_get, dummy_get, dummy_get, dummy_get, dummy_get};
static ecy_hsm_HostHwCsp_ReleaseResourceT* releaseResourceArray[] = {dummy_release, dummy_release, dummy_release, dummy_release, dummy_release, dummy_release, dummy_release};
# else
#  error Unsupported number of HwCsp Instances
# endif

/* *** public implementation  *****************************************************************/

/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_HostHwCspSrv_ConfigureCallouts(ecy_hsm_Csai_WorkspaceIdT          hostWksp,
                                       ecy_hsm_HostHwCsp_GetResourceT     pGetResource,
                                       ecy_hsm_HostHwCsp_ReleaseResourceT pReleaseResource)
{
    ecy_hsm_Csai_ErrorT                 errorCode = ecy_hsm_CSAI_SUCCESS;
    ecy_hsm_HostHwCsp_ReleaseResourceT* pLastRelease;

    /* Check that index is smaller than the max number of host workspaces.
     * Function pointers are allowed to be both nullpointer -> use dummy callouts
     * They are allowed to be both not nullpointer -> use the passed get/release functions
     * (There is no way to make sure that the pointers point to something useful, that is the users responsibility)
     * But just one function pointer as nullpointer and the other valid is not allowed.
     */
    if ((hostWksp >= ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES) || ((NULL_PTR != pGetResource) != (NULL_PTR != pReleaseResource)))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* Lock saved resource to prevent the saved pointers from being changed while an operation is running on the hardware */
        /* PRQA S 2842 1 */ /* Justification: hostWksp was checked to be within bounds of the array before this use as an array index */
        if (ecy_hsm_CSAI_SUCCESS == getResourceArray[hostWksp]())
        {
            /* Save release function from previous set */
            /* PRQA S 2842 1 */ /* Justification: hostWksp was checked to be within bounds of the array before this use as an array index */
            pLastRelease = releaseResourceArray[hostWksp];

            /* Set the stored function pointers to their new values. Start with the Release functions for this to prevent race conditions
             * Only check one function for nullpointer because at this point they are either both nullpointer or both valid */
            if (NULL_PTR == pGetResource)
            {
                /* If the passed functions are nullpointer set the stored functions to be the local dummy functions.
                 * This needs to be done so that the stored functions can never be nullpointer, which means that we do not need to check for
                 * nullpointer in the _CalloutCallGet function, which saves time. */
                /* PRQA S 2842 2 */ /* Justification: hostWksp was checked to be within bounds of the array before this use as an array index */
                releaseResourceArray[hostWksp] = dummy_release;
                getResourceArray[hostWksp]     = dummy_get;
            }
            else
            {
                /* Save passed function pointers */
                /* PRQA S 2842 2 */ /* Justification: hostWksp was checked to be within bounds of the array before this use as an array index */
                releaseResourceArray[hostWksp] = pReleaseResource;
                getResourceArray[hostWksp]     = pGetResource;
            }

            /* Release resource from previous set */
            pLastRelease();
        }
        else
        {
            /* We could not lock this resource */
            errorCode = ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED;
        }
    }

    return errorCode;
}

ecy_hsm_Csai_ErrorT ecy_hsm_HostHwCspSrv_GetCallout(ecy_hsm_Csai_WorkspaceIdT hostWksp)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if (hostWksp >= ecy_hsm_HwCsp_NUMBER_OF_HOST_WORKSPACES)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* Call Callout Function, save result */
        uint32 res = getResourceArray[hostWksp]();
        if (ecy_hsm_CSAI_SUCCESS == res)
        {
            /* We locked this resource */
            errorCode = ecy_hsm_CSAI_SUCCESS;
        }
        else
        {
            /* We could not lock this resource */
            errorCode = ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED;
        }
    }

    return errorCode;
}

void ecy_hsm_HostHwCspSrv_ReleaseCallout(ecy_hsm_Csai_WorkspaceIdT hostWksp)
{
    /* Call Callout Function */
    releaseResourceArray[hostWksp]();
}

/* *** private implementation  ****************************************************************/
static uint32 dummy_get(void)
{
    return ecy_hsm_CSAI_SUCCESS;
}

static void dummy_release(void)
{
}
/* *** epilogue  ******************************************************************************/

/** @} */ // GROUP_SRV_HOST_HWCSP
#endif    /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */
