/**
 * @file
 ***********************************************************************************************
 * @brief Interfaces for secure boot with direct release
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_SERVICE_SECURE_BOOT_STARTUP_H
#define ECY_HSM_SERVICE_SECURE_BOOT_STARTUP_H

/**
 * @addtogroup GROUP_SECURE_BOOT_DIRECT_RELEASE
 * @{
 */

/* *** includes *******************************************************************************/

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"
/**
 * [$DD 1711]
 * [$Satisfies $SW_ARCH 744] [$Satisfies $SW_ARCH 1064]
 *
 * @brief
 * The function checks the bridge registers if the verification of a software part was successful
 * and acknowledges the finished secure boot.
 *
 * @details
 * \par HSM:
 *  If the HSM successfully verifies sw part for direct release during startup it sets @ref HSM2HTF_SECBOOT_FINISHED
 *  and releases the HOST (= @ref HSM2HTF_HSM_READY ) afterwards.
 * \par On HOST side the following steps need to be performed:
 *  1. Wait for the HSM to set HSM2HTF_HSM_READY (= HOST released)
 *  2. Call @ref ecy_hsm_SecureBoot_GetValidBootAddress to
 *      - read the sw part address of the direct release sw part
 *      - acknowledge HSM2HTF_SECBOOT_FINISHED
 *      - send @ref HT2HSMF_HOST_SECBOOT_PROCESSED to the HSM
 *  3. Use @ref ecy_hsm_PollSecBoot to wait for the HSM to acknowledge HT2HSMF_HOST_SECBOOT_PROCESSED
 *  4. Release the HSM with @ref ecy_HSM_Release
 *  5. Wait for the HSM to reach HSM_MODE_CORE_APP with @ref ecy_HSM_WaitForMode
 *
 * @param[in,out]   pSwPartStartAddress  Pointer to read out the start address of the software part
 *
 * @return
 *  - 0 Host received HSM2HTF_SECBOOT_FINISHED and a SW Part address from the HSM
 *  - return value of @ref ecy_hsm_IpcDrv_GetHsmStatus Error in Secure Boot sequence
 */
uint32 ecy_hsm_SecureBoot_GetValidBootAddress(uint32* pSwPartStartAddress);

/**
 * [$DD 1712]
 * [$Satisfies $SW_ARCH 744] [$Satisfies $SW_ARCH 1064]
 *
 * @brief
 * The function checks the bridge registers if the secure boot with direct release was processed
 * on the HSM side.
 *
 * @return
 *  - TRUE  Secure boot with direct release has been finished on HSM side
 *  - FALSE Secure boot with direct release has not been finished on HSM side
 */
boolean ecy_hsm_PollSecBoot(void);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/** @} */ //GROUP_SECURE_BOOT_DIRECT_RELEASE

#endif /* ECY_HSM_SERVICE_SECURE_BOOT_STARTUP_H */
