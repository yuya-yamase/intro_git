/**
 * @file
 ***********************************************************************************************
 * @brief CSAI challenge response operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for challenge response
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_CR_H
#define ECY_HSM_CSAI_CR_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_vms_pub_cr.h"
/**
 * @addtogroup GROUP_CSAI_CR
 * @{
 *
 * The challenge response service provides interfaces to perform certain challenge-response protocols.
 * The supported challenge-response protocols depend on which features are enabled in the variant
 * configuration.
 *
 * The currently supported protocols are: APPLET_CHALLENGE_RESPONSE_VERLOG6 & APPLET_CHALLENGE_RESPONSE_VERLOG7.
 * The same CSAI calls support both protocols, with a @c useCaseId parameter specifying which protocol is used.
 * Although both protocols may be supported in a given application, they may not be used concurrently (i.e. at
 * the same time) in the same session.
 *
 * Since the protocols are normally user/customer/OEM specific, the details of each protocol are not
 * documented within the common challenge-response interfaces, but instead in the use-case specific
 * documentation (see @ref GROUP_VERLOG6 & @ref GROUP_VERLOG7).
 */

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/**
 * Define different nonce types
 */
typedef enum ecy_hsm_Csai_CR_NonceCtrl
{
    ecy_hsm_CSAI_CR_NONCE_RND      = 0UL,         /**< Nonce from RND                       */
    ecy_hsm_CSAI_CR_NONCE_RESERVED = 0x7fffffffUL /**< Reserved value to enforce long enums */
} ecy_hsm_Csai_CR_NonceCtrlT;

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2304]
 * [$Satisfies $SW_ARCH 892][$Satisfies $SW_ARCH 889][$Satisfies $SW_ARCH 891]
 * @brief Generate a challenge message for the specified use case.
 *
 * @details This function is responsible to generate a challenge and returns it in a buffer to the Host. The generated
 * challenge is stored in the internal workspace as it is needed to calculate the expected response.
 *
 * @param[in]  hSession                      Handle to the session in which the job will be placed
 * @param[in]  priority                      Requested scheduling priority for this job on the HSM
 *                                           (NOTE: Operation can only be executed on background priority)
 * @param[in]  useCaseId                     Use Case as defined by @c ecy_hsm_Csai_CR_UseCaseT
 * @param[out] pResponse                     Pointer to buffer to receive challenge
 * @param[in]  numBytes                      Size of the @p pResponse buffer
 * @param[out] pNumBytesChallenge            It returns the number of the generated challenge bytes
 * @param[in]  nonceCtrl                     Enum to determine the type of the nonce to be generated
 * @param[in]  pChallengeParamT              Pointer to the structure to receive the use case specific parameters
 *                                           The structure to be used depends on the @p useCaseId . Please refer
 *                                           to the use case specific headers for details.
 * @param[out] phJob                         Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS             The call succeeded. HSM is ready for programming sequence
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY             Another job is still pending completion in this session
 *                                           Either finish the previous job or cancel the running job
 *                                           using @ref ecy_hsm_Csai_CancelJob
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                  A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                 The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                  The given challenge response parameter is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED            The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT              In general, pointers should be aligned to four-byte boundaries
 * - @ref ecy_hsm_CSAI_ERR_TRNG                           True Random Number Generator reports an error
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_GetChallenge(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                         ecy_hsm_Csai_CR_UseCaseT    useCaseId,
                                                                                         uint8*                      pResponse,
                                                                                         uint32                      numBytes,
                                                                                         uint32*                     pNumBytesChallenge,
                                                                                         ecy_hsm_Csai_CR_NonceCtrlT  nonceCtrl,
                                                                                         void*                       pChallengeParamT,
                                                                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2305]
 * [$Satisfies $SW_ARCH 892][$Satisfies $SW_ARCH 891]
 * @brief Transfer add-on data or response data for a later verification.
 *
 * @details This function transfers data to the HSM. It can be used as a single call or as a streaming interface:
 * - As a single call, @c pResponse and @c numBytes represent a complete transfer of the response data
 * - As a streaming interface call, @c pResponse and @c numBytes represent a chunk of data
 *
 * @note
 * - some use cases (as Verlog7) make use of this API to transfer add-on data (not response data). The kind of data which
 * shall be transfered is specified in the @c pTransferParamT parameter.
 * - usage of this API may be optional in some use cases (as Verlog6), as the response data may also be transfered in one
 * chunk within the call to @ref ecy_hsm_Csai_CR_VerifyResponse.
 *
 * @param[in]  hJob             Handle to the initialized job
 * @param[in]  useCaseId        Use Case as defined by @c ecy_hsm_Csai_CR_UseCaseT.
 *                              Must be the same as the use case provided initially to @ref ecy_hsm_Csai_CR_GetChallenge.
 * @param[in]  pTransferParamT  Pointer to the structure to receive the use case specific parameters
 *                              The structure to be used depends on the @c useCaseId. Please refer
 *                              to the use case specific headers for details.
 * @param[in]  pResponse        Pointer to a buffer to send a chunk or all of the challenge response
 * @param[in]  numBytes         Length of the whole response data
 * @param[in]  numBytesCurrent  Number of bytes of response sent for this call
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS             The call succeeded. The operation is pending on the HSM
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY             Another job is still pending completion in this session.
 *                                           Either finish the previous job or cancel the running job
 *                                           using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                          A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                         The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED                    There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE                         The keyId referred to a key which was not of type
 *                                                                @c ecy_hsm_Csai_KeyTypeT
 * - @ref ecy_hsm_CSAI_ERR_NO_SPACE_FOR_KEY_HANDLE                No more key handles are available
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT                      In general, pointers should be aligned to four-byte boundaries
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                       The output data was too large to fit into the given buffer, nothing was written
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET                 At least one given parameter of the call is wrong, invalid or out of range.
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID                         The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                          The chosen use-case requires add-on data that have not been provided yet
 * - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE                        The response input is too large
 * */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_TransferResponse(ecy_hsm_Csai_JobHandleT  hJob,
                                                                                             ecy_hsm_Csai_CR_UseCaseT useCaseId,
                                                                                             void*                    pTransferParamT,
                                                                                             const uint8*             pResponse,
                                                                                             uint32                   numBytes,
                                                                                             uint32                   numBytesCurrent);

/**
 * [$DD 2306]
 * [$Satisfies $SW_ARCH 892][$Satisfies $SW_ARCH 889][$Satisfies $SW_ARCH 891]
 * @brief Verify a response of the challenge-response protocol.
 *
 * @details In combination with @ref ecy_hsm_Csai_CR_TransferResponse a chunk wise transfer of the response is possible.
 * This means that this function may provide part of the response, the whole response, or no response at all in the @c pResponse parameter.
 * Whatever method is chosen for transferring the response, the whole response must be available for it to be verified. The response is
 * checked against an internally-calculated expected response, based on the previously returned challenge and according to the chosen
 * challenge-response protocol (by means of @c useCaseId).
 *
 * After successful completion of this function the received response is consumed, i.e. a new response must be provided if a new verification
 * is requested.
 *
 * @param[in]  hJob             Handle to the initialized job
 * @param[in]  useCaseId        Use Case as defined by @c ecy_hsm_Csai_CR_UseCaseT
 *                              Must be the same as the use case provided initially to @ref ecy_hsm_Csai_CR_GetChallenge.
 * @param[in]  pVerifyParamT    Pointer to the structure to receive the use case specific parameters
 *                              The structure to be used depends on the @c useCaseId. Please refer
 *                              to the use case specific headers for details.
 * @param[in]  pResponse        Pointer to a buffer to send a chunk or all of the response
 * @param[in]  numBytes         Length of the whole response data
 * @param[in]  numBytesCurrent  Number of bytes of response sent for this call
 * @param[out] pResult          A flag that carries the result of the verification
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS             The call succeeded. The operation is pending on the HSM
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY             Another job is still pending completion in this session.
 *                                           Either finish the previous job or cancel the running job
 *                                           using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                          A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                         The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED                    There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                          Any subtype of challenge or response that is not supported
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                          The chosen use-case requires add-on data that have not been provided yet
 * - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE                        The response input is too large
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_VerifyResponse(ecy_hsm_Csai_JobHandleT  hJob,
                                                                                           ecy_hsm_Csai_CR_UseCaseT useCaseId,
                                                                                           void*                    pVerifyParamT,
                                                                                           const uint8*             pResponse,
                                                                                           uint32                   numBytes,
                                                                                           uint32                   numBytesCurrent,
                                                                                           uint32*                  pResult);

/** @} */ // GROUP_CR

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* ECY_HSM_CSAI_CR_H */
