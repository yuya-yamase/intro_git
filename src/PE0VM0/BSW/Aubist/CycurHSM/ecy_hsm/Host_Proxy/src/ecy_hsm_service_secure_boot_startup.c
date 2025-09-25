/**
 * @file
 ***********************************************************************************************
 * @brief Interfaces for secure boot with direct release
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

/**
 * @addtogroup GROUP_SECURE_BOOT_DIRECT_RELEASE
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_ipcdrv.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_service_basic.h"
#include "ecy_hsm_service_secure_boot_startup.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local variables ************************************************************************/

/* *** local function prototypes **************************************************************/

/* *** public implementation  *****************************************************************/
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
uint32 ecy_hsm_SecureBoot_GetValidBootAddress(uint32* pSwPartStartAddress)
{
    uint32 secBootError;

    uint32 hsmEventFlags   = ecy_hsm_IpcDrv_GetHsmEvents();
    uint32 hsmStatusBuffer = ecy_hsm_IpcDrv_GetHsmStatus();

    if (HSM2HTF_SECBOOT_FINISHED == (hsmEventFlags & HSM2HTF_SECBOOT_FINISHED))
    {
        /* Get access to the HSM Bridge, ignore errors to prevent secure boot lock-up */
        (void)ecy_HSM_GetBridgeResource();

        ecy_hsm_IpcDrv_SendEvents(HT2HSMF_HOST_SECBOOT_PROCESSED);
        ecy_hsm_IpcDrv_AcknowledgeEvents(HSM2HTF_SECBOOT_FINISHED);

        /* Release access to the HSM Bridge */
        (void)ecy_HSM_ReleaseBridgeResource();

        /* status contains the start address */
        *pSwPartStartAddress = hsmStatusBuffer;
        secBootError         = (uint32) 0UL;
    }
    else
    {
        *pSwPartStartAddress = 0;
        /* status contains the actual HSM status */
        secBootError = hsmStatusBuffer;
    }

    return secBootError;
}

/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
boolean ecy_hsm_PollSecBoot(void)
{
    return ((ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_HOST_SECBOOT_PROCESSED) == HT2HSMF_HOST_SECBOOT_PROCESSED) ? TRUE : FALSE;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *** private implementation  ****************************************************************/

/* *** epilogue  ******************************************************************************/

/** @} */ // GROUP_SECURE_BOOT_DIRECT_RELEASE
