/**
 * @file
 ***********************************************************************************************
 * @brief CSAI ECDH functions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for ECC DH with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_DH_H
#define ECY_HSM_CSAI_DH_H


/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *** defines ********************************************************************************/

/**
 * @addtogroup GROUP_CSAI_KEY_EXCHANGE
 * @{
 */

/* *** type declarations **********************************************************************/

/**
 * Controls the curve over which the ECDH operations are performed on
 */
typedef enum ecy_hsm_Csai_DhAlgorithmTag
{
    ecy_hsm_CSAI_ECDH_CURVE_25519,         /**< Perform ECDH over Curve25519  */
    ecy_hsm_CSAI_ECDH_CURVE_P_224,         /**< Perform ECDH over Curve P-224 */
    ecy_hsm_CSAI_ECDH_CURVE_P_256,         /**< Perform ECDH over Curve P-256 */
    ecy_hsm_CSAI_ECDH_CURVE_P_384,         /**< Perform ECDH over Curve P-384 */
    ecy_hsm_CSAI_ECDH_CURVE_P_521,         /**< Perform ECDH over Curve P-521 */
    ecy_hsm_CSAI_ECDH_CURVE_448,           /**< Perform ECDH over Curve448  */
    /* This needs to be the final entry */
    ecy_hsm_CSAI_DH_NUMALGORITHMS          /**< number of curves */
} ecy_hsm_Csai_DhAlgorithmT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * Generates a random private key and computes the public key using ECC Curve25519. Returns the
 * public key for use with ecy_hsm_Csai_DhSharedSecretCompute().
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one
 * distinct session at a time.
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the public key generation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]     hSession     Handle to the session in which the job will be placed.
 * @param[in]     priority     Requested scheduling priority for this job on the HSM.
 * @param[out]    publicKey    Pointer to buffer to receive the computed public key
 * @param[in,out] length       Length of buffer to receive the computed public key
 * @param[out]    phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE     The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM         A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED        The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED   There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB              An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhPublicKeyGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                   uint8                       publicKey[],
                                                   uint32*                     length,
                                                   ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * Computes a common secret based on the ECDH algorithm over Curve25519, using a peer's public key and an internally
 * stored private key from the last invocation of ecy_hsm_Csai_DhPublicKeyGenerate()
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one
 * distinct session at a time.
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the share secret computation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]     hSession              Handle to the session in which the job will be placed.
 * @param[in]     priority              Requested scheduling priority for this job on the HSM.
 * @param[in]     remotePublicKey       Address of the buffer containing the public key of the conversation partner
 * @param[in]     publicKeyLength       Length of the remote public key
 * @param[out]    sharedSecret          Address of the buffer to receive the computed shared secret
 * @param[in,out] sharedSecretLength    Length of the computed shared secret
 * @param[out]    phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE     The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     An error returned from the SW library
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                The requested operation is not supported in the current status
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhSharedSecretCompute(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     const uint8                 remotePublicKey[],
                                                     const uint32                publicKeyLength,
                                                     uint8                       sharedSecret[],
                                                     uint32*                     sharedSecretLength,
                                                     ecy_hsm_Csai_JobHandleT*    phJob);

/** @} */ // GROUP_CSAI_KEY_EXCHANGE

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* Multiple inclusion lock  */
