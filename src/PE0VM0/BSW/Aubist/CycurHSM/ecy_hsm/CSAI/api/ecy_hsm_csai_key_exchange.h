/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Key Exchange functions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for key exchange with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_KEY_EXCHANGE_H
#define ECY_HSM_CSAI_KEY_EXCHANGE_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_dh.h"

/* *** defines ********************************************************************************/

/**
 * @addtogroup GROUP_CSAI_KEY_EXCHANGE
 * @{
 */

/* *** type declarations **********************************************************************/
/**
 * Controls the curve over which the ECBD operations are performed on
 */
typedef enum ecy_hsm_Csai_EcbdCurveType
{
    ecy_hsm_CSAI_ECBD_CURVE_P_224, /**< Perform ECBD over Curve P-224 */
    ecy_hsm_CSAI_ECBD_CURVE_P_256, /**< Perform ECBD over Curve P-256 */
    ecy_hsm_CSAI_ECBD_CURVE_P_384, /**< Perform ECBD over Curve P-384 */
    /* This needs to be the final entry */
    ecy_hsm_CSAI_ECBD_NUMCURVES /**< number of curves */
} ecy_hsm_Csai_EcbdCurveT;

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
 * [$DD 2457]
 * [$Satisfies $ARCH 684] [$Satisfies $ARCH 696] [$Satisfies $ARCH 687] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 696_v1]
 * @brief Prepares a Burmester-Desmedt Key Exchange operation (BD1).
 *
 * This function prepares an ECBD operation for a specific elliptic curve by storing all given parameters internally
 * and by giving out a key handle to the generated key pair. The public key of this key pair has to be broadcasted
 * to all communication partners. In order to restart calculation of the shared point after a power loss
 * the corresponding key pair should be persisted by the user. In this case, the function shall be called with
 * the corresponding key handle as phKey input, otherwise @ref ecy_hsm_CSAI_NO_KEY_HANDLE shall be used as input.
 *
 * @note
 * This function currently does not support the use of curves other than @ref ecy_hsm_CSAI_ECBD_CURVE_P_224.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one distinct session at a
 * time.
 *
 * @note
 * All ECBD functions can only be called with background priority, due to stack limitations.
 *
 * @param[in]      hSession            Handle to the session in which the job will be placed.
 * @param[in]      priority            Scheduling priority of the operation on the HSM.
 * @param[in]      curveId             Curve selector, contains the curve's ID.
 * @param[in,out]  phKey               Key handle to a key pair to be used to prepare the ECBD operation.
 * @param[in]      assignedNumber      The assigned number (i) in the ring of participants
 * @param[in]      partyCount          The total number of participants in the ring
 * @param[out]     phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. The operation is pending on the HSM.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 * - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                Either finish the previous job or cancel the running job
 *                                                using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED     There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                  ecy_hsm_Csai_EcbdCurveT     curveId,
                                                                                  uint32                      assignedNumber,
                                                                                  uint32                      partyCount,
                                                                                  ecy_hsm_Csai_KeyHandleT*    phKey,
                                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2458]
 * [$Satisfies $ARCH 685] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 685_v1]
 * @brief Performs the first step of the Burmester-Desmedt Key Exchange operation.
 *
 * This function creates a second public key (X_i) using the parameters set by the last call of ecy_hsm_Csai_EcbdInit().
 * To be called after receiving the first public keys (Z_(i-1) and Z_(i+1)) of both neighboring parties.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one distinct session at a
 * time.
 *
 * @note
 * All ECBD functions can only be called with background priority, due to stack limitations.
 *
 * @param[in]   hSession             Handle to the session in which the job will be placed.
 * @param[in]   priority             Scheduling priority of the operation on the HSM.
 * @param[in]   pPublicKeyPreceding  Public key of preceding party Z_(i-1)
 * @param[in]   pPublicKeyNext       Public key of following party Z_(i+1)
 * @param[out]  pPublicKey           Buffer to receive the public key for the second broadcast (X_i)
 * @param[in]   publicKeyBuffSize    Number of bytes of the buffer to receive the public key
 * @param[out]  pPublicKeyLength     Number of bytes of the actual key written to publicKey[] (depends on the chosen curve)
 * @param[out]  phJob                Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. The operation is pending on the HSM.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 * - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                Either finish the previous job or cancel the running job
 *                                                using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED     There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdCompute2ndPubKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                              ecy_hsm_Csai_JobPriorityT   priority,
                                                                                              const uint8                 pPublicKeyPreceding[],
                                                                                              const uint8                 pPublicKeyNext[],
                                                                                              uint8                       pPublicKey[],
                                                                                              uint32                      publicKeyBuffSize,
                                                                                              uint32*                     pPublicKeyLength,
                                                                                              ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2459]
 * [$Satisfies $ARCH 686] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 686_v1]
 * @brief Performs the second step of the Burmester-Desmedt Key Exchange operation.
 *
 * To be called repeatedly after receiving a public key (X_j) during the second broadcast phase.
 *
 * @note
 * The party's own public key must also be input to this function in order to compute correctly the shared point.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one distinct session at a
 * time.
 *
 * @note
 * All ECBD functions can only be called with background priority, due to stack limitations.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Scheduling priority of the operation on the HSM.
 * @param[in]   pPublicKey          2nd public key (X_j) of a party member
 * @param[in]   publicKeyLength     Number of bytes of the publickey buffer
 * @param[in]   assignedNumber      Assigned party number (j) corresponding to the received public key
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. The operation is pending on the HSM.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 * - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                Either finish the previous job or cancel the running job
 *                                                using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED     There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                    const uint8                 pPublicKey[],
                                                                                    uint32                      publicKeyLength,
                                                                                    uint32                      assignedNumber,
                                                                                    ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2460]
 * [$Satisfies $ARCH 687] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 687_v1]
 * @brief
 * Performs the last step of the Burmester-Desmedt Key Exchange operation. To be called after all second
 * public keys (X_j) of the other participants and the own second public key have been incorporated
 * with the ecy_hsm_Csai_EcbdUpdate() function.
 * This function returns a pointer to the key handle to the shared secret that shall be used to derive a shared key.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one distinct session at a
 * time.
 *
 * @note
 * All ECBD functions can only be called with background priority, due to stack limitations.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Scheduling priority of the operation on the HSM.
 * @param[out]  phKey               Pointer to the key handle to the shared secret.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. The operation is pending on the HSM.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 * - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                Either finish the previous job or cancel the running job
 *                                                using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED     There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdFinish(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                    ecy_hsm_Csai_KeyHandleT*    phKey,
                                                                                    ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2313]
 * [$Satisfies $SW_ARCH 590_v1] [$Satisfies $SW_ARCH 591_v3] [$Satisfies $ARCH 603] [$Satisfies $SW_ARCH 855]
 * [$Satisfies $SW_ARCH 598] [$Satisfies $SW_ARCH 853] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 129AA958]
 *
 * @brief
 * Prepares a Diffie-Hellman operation. To be used if more specific options compared to
 * ecy_hsm_Csai_DhPublicKeyGenerate() are needed.
 *
 * This function allows to choose a specific DH algorithm and can make use of keys already stored in the Keystore.
 * It is still possible to generate a new key pair on the fly if @ref ecy_hsm_CSAI_NO_KEY_HANDLE was passed
 * as the keyHandle parameter.
 *
 * @note
 * This function currently supports loading keys from the Keystore for the algorithms @ref ecy_hsm_CSAI_ECDH_CURVE_25519,
 * @ref ecy_hsm_CSAI_ECDH_CURVE_P_224, @ref ecy_hsm_CSAI_ECDH_CURVE_P_256 and @ref ecy_hsm_CSAI_ECDH_CURVE_P_384.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one distinct session at a
 * time.
 *
 * Finalization and result query:
 * The caller finishes and polls for the result of the public key generation using @ref ecy_hsm_Csai_PollHandle.
 *
 * @param[in]     hSession            Handle to the session in which the job will be placed.
 * @param[in]     priority            Requested scheduling priority for this job on the HSM.
 * @param[in]     algorithm           DH algorithm to be used. See @ref ecy_hsm_Csai_DhAlgorithmT for possible values
 * @param[in]     hKey                Key handle to a key pair to be used to prepare the DH operation. Use
 *                                    ecy_hsm_CSAI_NO_KEY_HANDLE to generate a new exclusive key pair
 * @param[out]    pPublicKey          Buffer to receive the public key to be given to a peer.
 *                                    Can be NULL_PTR if no public key should be returned and a key handle is given.
 * @param[in]     publicKeyBuffSize   Number of bytes of the buffer to receive the public key.
 *                                    Has to be 0 if pPublicKey is NULL_PTR.
 * @param[out]    pPublicKeyLength    Number of bytes of the actual key written to publicKey[]
 *                                    (depends on the chosen algorithm)
 * @param[out]    phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     An error returned from the SW library
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                ecy_hsm_Csai_DhAlgorithmT   algorithm,
                                                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                                                uint8                       pPublicKey[],
                                                                                uint32                      publicKeyBuffSize,
                                                                                uint32*                     pPublicKeyLength,
                                                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2314]
 * [$Satisfies $SW_ARCH 592_v1] [$Satisfies $SW_ARCH 593_v3] [$Satisfies $ARCH 604] [$Satisfies $SW_ARCH 855]
 * [$Satisfies $SW_ARCH 598] [$Satisfies $SW_ARCH 853] [$Satisfies $SW_ARCH 589_v1] [$Satisfies $SW_ARCH 129AA958]
 *
 * Computes a shared secret based on the parameters (i.e. algorithm type and personal private key) that were set up
 * with the last call of ecy_hsm_Csai_DhInit() in conjunction with a peer's public key. The shared secret will be
 * made externally available. (The shared secret is the x-coordinate of a point of the chosen elliptic curve.)
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one
 * distinct session at a time.
 *
 * Finalization and result query:
 *      The caller finishes and polls for the result of the share secret computation using @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]     hSession              Handle to the session in which the job will be placed.
 * @param[in]     priority              Requested scheduling priority for this job on the HSM.
 * @param[in]     pRemotePublicKey      Public key of the conversation partner
 * @param[in]     publicKeyLength       Length of the remote public key
 * @param[out]    pSharedSecret         Buffer to receive the shared secret to be used for futher communication
 * @param[in]     sharedSecretLen       Number of bytes of the sharedSecretBuffer
 * @param[out]    pSharedSecretCount    Number of bytes of the actual sharedSecret written to sharedSecret[]
 * @param[out]    phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     An error returned from the SW library
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                The requested operation is not supported in the current status
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhComputeExt(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                      const uint8                 pRemotePublicKey[],
                                                                                      const uint32                publicKeyLength,
                                                                                      uint8                       pSharedSecret[],
                                                                                      uint32                      sharedSecretLen,
                                                                                      uint32*                     pSharedSecretCount,
                                                                                      ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2315]
 * [$Satisfies $SW_ARCH 598_v1] [$Satisfies $SW_ARCH 855] [$Satisfies $SW_ARCH 853] [$Satisfies $SW_ARCH 589_v1]
 * [$Satisfies $SW_ARCH 129AA958] [$Satisfies $SW_ARCH 842E96D7]
 *
 * Computes a common secret based on the parameters (i.e. algorithm type and personal private key) that were set up
 * with the last call of ecy_hsm_Csai_DhInit() in conjunction with a peer's public key.
 *
 * @note
 * This function currently does not support multi-session access and can only be used by one
 * distinct session at a time.
 *
 * Finalization and result query:
 *      The caller finishes and polls for the result of the share secret computation using @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]     hSession              Handle to the session in which the job will be placed.
 * @param[in]     priority              Requested scheduling priority for this job on the HSM.
 * @param[in]     pRemotePublicKey      Public key of the conversation partner
 * @param[in]     publicKeyLength       Number of bytes of the remote public key buffer
 * @param[out]    phSecret              The key handle of the shared secret (the shared secret is stored in
 *                                      the key store)
 * @param[in]     phJob                 Receives the job handle of the initialized job.
 *
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     An error returned from the SW library
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                The requested operation is not supported in the current status
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhComputeInt(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                      const uint8                 pRemotePublicKey[],
                                                                                      const uint32                publicKeyLength,
                                                                                      ecy_hsm_Csai_KeyHandleT*    phSecret,
                                                                                      ecy_hsm_Csai_JobHandleT*    phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_CSAI_KEY_EXCHANGE

#endif /* ECY_HSM_CSAI_KEY_EXCHANGE_H */
