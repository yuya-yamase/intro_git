/**
 * @file
 ***********************************************************************************************
 * @brief MCAL implementation of the MAC Generation and Verification on the Host side using the Hardware Crypto Service Provider.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_MCAL] */

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_HOST_HWCSP_MAC_MCAL_H
#define ECY_HSM_HOST_HWCSP_MAC_MCAL_H

/**
 * @addtogroup GROUP_HOST_HWCSP_MAC_MCAL
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_general_host_cfg.h"
#if (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED)
# include "ecy_hsm_csai_mac.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * [$DD 2610]
 * @brief
 * Generate a CMAC in cpu mode in a single step
 *
 * [$Satisfies $SW_ARCH DAC7C198]
 *
 * @param[in]   hostWksp            Host Workspace determines the channel/instance of the HostHwCsp to be used.
 * @param[in]   hKey                Handle to a host key available in the HwCsp keystore.
 * @param[in]   pMsg                Message to MAC.
 * @param[in]   msgLength           Length of the provided message in bytes.
 * @param[in]   macBitLength        Length of the MAC to generate in bits.
 * @param[out]  pMac                Pointer to space where the HostHwCsp can store the result. The length of the buffer must be sufficiently
 *                                  large to hold the number of bits given in the parameter @c macBitLength rounded up to the next multiple of 8.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS             Cmac generation successful.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM   Parameter check failed.
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID  Lookup in Host key handle to HW key slot table failed. Table may be uninitialized or the host key handle
 *                                          may not exist in the table.
 *  - @ref ecy_hsm_CSAI_FC_BUSY             Hardware reports that it is busy.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT         Timeout reached before other event could occur.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE   Hardware has set Overflow flag.
 *  - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE  Hardware reports a problem with the key.
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP           Hardware reports a problem not covered with the above options
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_HostHwCspMcal_MacGenerate_Reg_Cmac(ecy_hsm_Csai_WorkspaceIdT   hostWksp,
                                                                                 ecy_hsm_Csai_HostKeyHandleT hKey,
                                                                                 const uint8                 pMsg[],
                                                                                 uint32                      msgLength,
                                                                                 uint32                      macBitLength,
                                                                                 uint8*                      pMac);

/**
 * [$DD 2611]
 * @brief
 * Verify a CMAC in cpu mode in a single step
 *
 * [$Satisfies $SW_ARCH 16C25A24]
 *
 * @param[in]   hostWksp            Host Workspace determines the channel/instance of the HostHwCsp to be used.
 * @param[in]   hKey                Handle to a host key available in the HwCsp keystore.
 * @param[in]   pMsg                Message for which to verify the MAC.
 * @param[in]   msgLength           Length of the provided message.
 * @param[in]   macBitLength        Length of the MAC to verify in bits.
 * @param[in]   pExpectedMac        Pointer to MAC to be verified.
 * @param[out]  pResultFlag         Result of the MAC operation. Value 0u(FALSE) means MAC does not match and 1u(TRUE) means MAC matches.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS             Operation Cmac verification successful. Result of operation is returned via pResultFlag.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM   Parameter check failed.
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID  Lookup in Host key handle to HW key slot table failed. Table may be uninitialized or the host key handle
 *                                          may not exist in the table.
 *  - @ref ecy_hsm_CSAI_FC_BUSY             Hardware reports that it is busy.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT         Timeout reached before other event could occur.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE   Hardware has set Overflow flag.
 *  - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE  Hardware reports a problem with the key.
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP           Hardware reports a problem not covered with the above options
 *
 * @note
 * The return code only provides information about whether the call succeeded. SUCCESS does not mean that the expected MAC matches the
 * calculated MAC, this is encoded in pResultFlag.
 */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_HostHwCspMcal_MacVerify_Reg_Cmac(ecy_hsm_Csai_WorkspaceIdT   hostWksp,
                                                                               ecy_hsm_Csai_HostKeyHandleT hKey,
                                                                               const uint8                 pMsg[],
                                                                               uint32                      msgLength,
                                                                               uint32                      macBitLength,
                                                                               const uint8*                pExpectedMac,
                                                                               uint32*                     pResultFlag);

/** @} */ // GROUP_HOST_HWCSP_MAC_MCAL

#endif /* (ecy_hsm_HOST_HWCSP_MAC_QUICK == ENABLED) */
#endif /* ECY_HSM_HOST_HWCSP_MAC_MCAL_H */
