/**
 * @file
 **********************************************************************************************
 * @brief CSAI Message Authentication Code extended verification
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for verifying Message Authentication Codes using the extended API.
 *
 **********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved
 **********************************************************************************************/

/* *** prologue *******************************************************************************/

#ifndef ECY_HSM_CSAI_MAC_EXTENDED_H
#define ECY_HSM_CSAI_MAC_EXTENDED_H

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_EXTENDED
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Extended MAC verification parameter structure version identifiers */
typedef enum ecy_hsm_Csai_MacVerifyExtended_ParamSetVersionTag
{
    ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0 = 0,          /**< Version 0 parameter structure identifier */
    ecy_hsm_Csai_MacVerifyExtended_RESERVED     = 0x7FFFFFFF,
} ecy_hsm_Csai_MacVerifyExtended_ParamSetVersionT;

/** Extended MAC verification parameter struct version 0. */
typedef struct ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0Tag
{
    ecy_hsm_Csai_KeyHandleT hKey;         /**< In: Handle to a host key */
    const uint8*            pMsg;         /**< In: Message for which to verify the MAC. Buffer should be 32-Bit aligned for performance reasons */
    uint32                  msgLength;    /**< In: Length of the provided message in bytes */
    const uint8*            pExpectedMac; /**< In: Pointer to expected MAC for verification */
    uint32                  macBitLength; /**< In: Length of the MAC to verify in bits */
    uint32*                 pResultFlag;  /**< Out: Result of the MAC verify operation. Value 0u(FALSE) means MAC does not match and 1u(TRUE) means MAC matches */
} ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0T;

/** Extended MAC verification structure union */
/* PRQA S 0750 3 */ /* <Justification: Definition of a union is appropriate here */
typedef union ecy_hsm_Csai_MacVerifyExtended_ParamSetUnionTag
{
    ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0T cmacQuick_V0; /**< Version 0 of the parameter structure used for extended MAC verification feature */
} ecy_hsm_Csai_MacVerifyExtended_ParamSetUnionT;

/** Extended MAC verification wrapper structure for interface parameter extensibility */
typedef struct ecy_hsm_Csai_MacVerifyExtended_ParamSetAndVersionTag
{
    ecy_hsm_Csai_MacVerifyExtended_ParamSetVersionT paramSetVersion; /**< Parameter set version identifier */
    ecy_hsm_Csai_MacVerifyExtended_ParamSetUnionT   paramSet;        /**< Parameter set union */
} ecy_hsm_Csai_MacVerifyExtended_ParamSetAndVersionT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * [$DD 2928]
 * [$Satisfies $SW_ARCH AC517F1B] [$Satisfies $SW_ARCH 24039562]
 *
 * @brief Extended MAC verification for specific use cases
 *
 * Supported use cases:
 * - @ref ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0 : quick, non-interruptible verification using a user-defined key and hardware accelerators
 * on supported targets.
 *
 * @details
 * Detailed description of the @ref ecy_hsm_Csai_MacVerifyExtended_CmacQuick_V0 use case:
 * - The MAC verification is performed using the @ref ecy_hsm_CSAI_AES_CMAC algorithm (not user-selectable)
 * - The function may only be called with the @ref ecy_hsm_CSAI_PRIO_HIGH priority
 * - ECC error detection is disabled during the CMAC calculation operation
 *
 * @param[in]  hSession  Handle to an open HSM session.
 * @param[in]  priority  Scheduling priority of the operation on the HSM.
 * @param[in]  pParams   Pointer to the structure @c ecy_hsm_Csai_MacVerifyExtended_ParamSetAndVersionT which specifies
 *                       the requested use case and contains related data.
 * @param[out] phJob     Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The job has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED    The given priority is not supported
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED           The MAC Verify Extended feature is not supported by the HSM
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter or the whole parameter structure is invalid (null pointer or out of range)
 *  - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT       In general, pointers should be aligned to four-byte boundaries
 *  - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION       There has been an attempt to access HSM addresses via the CSAI interface
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID          The supplied key ID does not map to a valid key slot
 *  - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE          The key may not have the appropriate attributes
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1        An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2        An error was reported by the AES hardware accelerator
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_MacVerifyExtended(ecy_hsm_Csai_SessionHandleT                         hSession,
                                                   ecy_hsm_Csai_JobPriorityT                           priority,
                                                   ecy_hsm_Csai_MacVerifyExtended_ParamSetAndVersionT* pParams,
                                                   ecy_hsm_Csai_JobHandleT*                            phJob);

/* *** epilogue *******************************************************************************/

/**
 * @}
 */

#endif /* ECY_HSM_CSAI_MAC_EXTENDED_H */
