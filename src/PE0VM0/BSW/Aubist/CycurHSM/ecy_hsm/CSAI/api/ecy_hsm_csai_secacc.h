/**
 * @file
 ***********************************************************************************************
 * @brief CSAI secure flash operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for secure flash programming
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_SECACC
#define ECY_HSM_CSAI_SECACC

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/**
 * @addtogroup GROUP_CSAI_SECACC
 * @{
 *
 * functions to perform security access
 *
 * Security access provides following functionality:
 * * challenge/response authentication of a session
 *
 */

/* *** defines ********************************************************************************/

/** Length of the authentication bits. */
#define ecy_hsm_CSAI_SECACC_AUTHBITS_LEN               16U

/** Parameter shall be absent in Challenge. */
#define ecy_hsm_CSAI_SECACC_CHALLENGE_PARAMETER_ABSENT 0xFFFFFFFFU

/* *** type declarations **********************************************************************/

/**
 * Define different nonce types
 */
typedef enum ecy_hsm_Csai_SecAcc_NonceCtrl
{
    ecy_hsm_CSAI_NONCE_ZERO             = 1UL, /**< Use Nonce = 0 (Only possible in Production Mode )         */
    ecy_hsm_CSAI_NONCE_RND              = 2UL, /**< Nonce from RND                                            */
    ecy_hsm_CSAI_NONCE_RND_STORE_DFLASH = 3UL, /**< Nonce from RND and store it to DFlash for recall purposes */
    ecy_hsm_CSAI_NONCE_FROM_DFLASH      = 4UL, /**< Use Nonce from DFlash                                     */
    ecy_hsm_CSAI_NONCE_DEVICE_ID        = 5UL, /**< Use device ID as nonce                                    */
    ecy_hsm_CSAI_NONCE_HASHED_DEVICE_ID = 6UL, /**< Use hashed device ID as nonce                             */
    /* This needs to be the final entry */
    ecy_hsm_CSAI_NONCE_NUMTYPES,               /**< number of types                                           */
    ecy_hsm_CSAI_NONCE_RESERVED = 0x7fffffffUL /**< Reserved value to enforce long enums                      */
} ecy_hsm_Csai_SecAcc_NonceCtrlT;

/**
 * Define Use Cases for getting access
 */
typedef enum ecy_hsm_Csai_SecAcc_UseCase
{
    ecy_hsm_CSAI_SECUACC               = 0UL, /**< Use case: Security access                                              */
    ecy_hsm_CSAI_SECUACC_PLAIN_CVC     = 1UL, /**< Response consists of CVC certificate + signature (not DER encoded)     */
    ecy_hsm_CSAI_SECUACC_OEM_LIFECYCLE = 2UL, /**< Challenge response for a LifeCycle State change                        */
    /* This needs to be the final entry */
    ecy_hsm_CSAI_SECUACC_NUMTYPES,                 /**< number of types                                                        */
    ecy_hsm_CSAI_USECASEID_RESERVED = 0x7fffffffUL /**< Reserved value to enforce long enums                                   */
} ecy_hsm_Csai_SecAcc_UseCaseT;

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2451]
 * [$Satisfies $ARCH 191][$Satisfies $ARCH 510]
 * @brief Builds a challenge message for the specified use case.
 *
 * This function is responsible, to build the challenge by means of its calling parameters and returns the challenge
 * (ASN.1 notation) in a buffer on the Host-side.
 * Challenge format: @see secacc_challenge
 *
 * @param[in]  hSession                Handle to the session in which the job will be placed
 * @param[in]  priority                Requested scheduling priority for this job on the HSM
 *                                     @note Operation using will always be executed on background priority.
 *                                           Parameter will be overridden by implementation.
 * @param[out] pChallenge              Pointer to buffer to receive the challenge data
 * @param[in]  numBytesChallenge       useCase ecy_hsm_CSAI_SECUACC: Length of the provided @c pChallenge buffer
 *                                     useCase ecy_hsm_CSAI_SECUACC_PLAIN_CVC: Actual challenge/nonce size
 * @param[out] pNumBytesChallengeCurr  Length of challenge data that is really generated
 * @param[in]  useCaseId               Use Case inside the Challenge Message. For SecAcc = ecy_hsm_CSAI_SECUACC
 * @param[in]  nonceCtrl               Parameter defines the requested behavior of the Nonce for the Challenge
 *                                     @ref ecy_hsm_Csai_SecAcc_NonceCtrlT
 * @param[in]  slotIdTrustAnchor       Parameter determines a certificate via index residing inside the HSM
 *                                     certificate storage. @ref ecy_hsm_CSAI_SECACC_CHALLENGE_PARAMETER_ABSENT if parameter is absent.
 * @param[in]  slotIdAuthzOid          Parameter determines an OID via index residing inside the
 *                                     HSM OID storage. @ref ecy_hsm_CSAI_SECACC_CHALLENGE_PARAMETER_ABSENT if parameter is absent.
 * @param[in]  authLevel               ID of auth level; not supported at the moment
 * @param[in]  pAuthzValue             Authorization bits the user certificate shall fulfill
 * @param[in]  pAuthzMask              Mask of authorization bits the user certificate: they specify if a bit in
 *                                     @c pAuthzValue is relevant or not
 * @param[out] phJob                   Receives the job handle of the initialized job
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                  The given SecuAcc parameter is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED            The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                  Any subtype of challenge or response that is not of the type RBPF
 *                                                        (Robert Bosch platform) is not supported
 * - @ref ecy_hsm_CSAI_ERR_ENCODING_NULL_PTR              Output buffer pointer not initialized
 * - @ref ecy_hsm_CSAI_ERR_ENCODING_METHOD_NOT_SUPPORTED  Not supported encoding method, class
 * - @ref ecy_hsm_CSAI_ERR_ENCODING_TYPE_NOT_SUPPORTED    Not supported type, class
 * - @ref ecy_hsm_CSAI_ERR_ENCODING_NOT_ENOUGH_SPACE      Not enough space in output buffer
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION              Access failure for RBNS or chip ID
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                       Failure during computation of the challenge digest
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecAcc_GetChallenge(ecy_hsm_Csai_SessionHandleT    hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT      priority,
                                                                                             uint8*                         pChallenge,
                                                                                             uint32                         numBytesChallenge,
                                                                                             uint32*                        pNumBytesChallengeCurr,
                                                                                             ecy_hsm_Csai_SecAcc_UseCaseT   useCaseId,
                                                                                             ecy_hsm_Csai_SecAcc_NonceCtrlT nonceCtrl,
                                                                                             uint32                         slotIdTrustAnchor,
                                                                                             uint32                         slotIdAuthzOid,
                                                                                             uint8                          authLevel,
                                                                                             const uint8* const             pAuthzValue,
                                                                                             const uint8* const             pAuthzMask,
                                                                                             ecy_hsm_Csai_JobHandleT*       phJob);

/**
 * [$DD 2452]
 * [$Satisfies $ARCH 192][$Satisfies $ARCH 510]
 * @brief Transfers response data for a later verification
 *
 * This function copies response data to the internal buffer:
 * * At the first call after the challenge generation the parameters numChunk and numRespData indicate if all response
 *   data is transferred with one call (single-transfer mode) or if further calls will follow because only a chunk of
 *   data is transferred (multi-transfer mode)
 *    * if parameter @c numResponse is bigger than 0 and @c numChunk is 0 or equal to numResponse the whole response
 *      data is inside the buffer @c chunk and no further calls of @c ecy_hsm_Csai_SecAcc_TransferResponse are expected
 *    * if parameter @c numResponse is bigger than 0 and @c numChunk is bigger than 0 but less than @c numResponse
 *      additional calls are necessary until the sum of all values @c numChunk is equal to  @c numRespData
 * * At the second until the last call the parameter @c numResponse is ignored and the parameter @c numChunk must be
 *   bigger than 0
 *
 * @param[in]  hJob         Handle to the initialized job
 * @param[in]  pChunk       Pointer to response data chunk for verification
 * @param[in]  numChunk     Length of response data chunk for verification
 * @param[in]  numResponse  Length of response data (in bytes) to be verified
 * @param[out] pResultFlag  Pointer to a buffer to receive the result of the verify operation.
 *                          Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                          Any subtype of challenge or response that is not of the type RBPF
 *                                                                (Robert Bosch platform) is not supported
 * - @ref ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_TOTALDATA_SIZE_WRONG  This error occurs in the first call when @c numResponse is 0
 *                                                                or @c numResponse is less than @c numChunk
 * - @ref ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_CHUNK_SIZE_WRONG      This error occurs in the second or later calls when
 *                                                                @c numChunk is 0 or the actual @c numChunk would exceed the
 *                                                                remaining data
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_SecAcc_TransferResponse(ecy_hsm_Csai_JobHandleT hJob, const uint8* pChunk, uint32 numChunk, uint32 numResponse, uint32* pResultFlag);

/**
 * [$DD 2508]
 * @brief Verifies a response of a secure access request.
 * [$Satisfies $ARCH 453]
 *
 * This function verifies a given response to a security request:
 * * When one or more TransferResponse calls were applied before then the parameters @c numResponse and @c pResponse
 *   should contain the remaining data to complete the response data (multi-transfer mode).
 * * When no TransferResponse call was applied before the parameters @c numResponse and @c pResponse apply implicitly
 *   a complete transfer of the response data (single-transfer mode)
 *
 * Functional description:
 * In contrast to the general CR definition (@see secacc_response) the presence of ONE User Certificate is required.
 *
 * To verify the response the Host-SW has to call the CSAI_SecAcc_VerifyResponse function and to poll the state until the result will be evaluated by
 * the EcuCybSec-SW.
 *
 * For the response verification the following steps are necessary:
 * 1.  Parse the response, to get access to the data elements (Especially the Signature and the CertChain).
 *   - Signature: Signature of the Challenge, calculated with the private key of the User Certificate
 *   - CertChain: User Certificate that contains the public key to verify the response and that is signed with the effective root for the device. The
 * User Certificate could be validated with the effective root of the device (could be a public key for RSA 2048 or a full Bosch CV Certificate
 * Profile 1)
 * 2.  Verify the User Certificate with the effective root belonging to the Bosch PKI (Bosch CV Certificate Profile 1) conform to RSASSA-PSS.
 * 3.  Extract the public key of the received user certificate
 * 4.  The received signature will be verified (encrypted with public key of the User Certificate)
 *   - Hash value of the Challenge (calculated by the PKI)
 * 5.  If the Hash value from the Challenge and the Hash value of the received signature are identical, the verification is successful.
 *
 * Dynamic behavior:
 * Because the verification requires certificate operations, which are time consuming, the call is implemented as an asynchronous call. Hence, the
 * Host-SW has to poll the state with the job handle while the Response will be verified by the EcuCybSec-SW. In combination with the @ref
 * ecy_hsm_Csai_SecAcc_TransferResponse a chunk wise transfer is possible.
 *
 * @param[in]  hJob         Handle to the initialized job
 * @param[in]  pResponse    Pointer to response data for verification.
 * @param[in]  numResponse  Length of response data (in bytes) to be verified
 * @param[out] pResultFlag  Pointer to a buffer to receive the result of the verify operation.
 *                           Value 0u(FALSE) means signature does not match and 1u(TRUE) means signature matches.
 *                          Note: To be considered only if the function succeeded (@ref ecy_hsm_Csai_PollHandle returns @ref ecy_hsm_CSAI_SUCCESS)
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                          Any subtype of challenge or response that is not of the type RBPF
 *                                                                (Robert Bosch platform) is not supported
 * - @ref ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_TOTALDATA_SIZE_WRONG  This error occurs when the expected response data (specified
 *                                                                in the first call of ecy_hsm_Csai_SecAcc_TransferResponse) is not
 *                                                                equal to the transferred data until now (the summary of all
 *                                                                chunk values)
 * - @ref ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_INVALID_VERSION       Unsupported scheme version
 * - @ref ecy_hsm_CSAI_ERR_SECUACC_RESPONSE_INVALID_MSG_TYPE      Unsupported response message type
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_PARAMETER               When an wrong parameter is given to the certificate parser
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INSUFFICIENT_DATA               When an wrong parameter is given to the certificate parser
 * - @ref ecy_hsm_CSAI_ERR_PARSER_NESTED_LEVEL                    When during parsing the reached level is reached to early
 * - @ref ecy_hsm_CSAI_ERR_PARSER_NO_ELEMENTS_FOUND               When during parsing necessary data is missing
 * - @ref ecy_hsm_CSAI_ERR_WRONG_CERT_ATTRIBS                     When the check of the auth bits was unsuccessful
 * - @ref ecy_hsm_CSAI_ERR_UNDEFINED                              When something went wrong during checking the root cert of the user cert
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                               When the access of the public key in the root cert was not successful
 * - @ref ecy_hsm_CSAI_ERR_CERT_WRONG_SIGNATURE                   When the signature of the user cert fits not to its body
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                          When parameters of KeystoreInjectRsaKey were invalid
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION                 When key properties are not valid during key injection
 * - @ref ecy_hsm_CSAI_ERR_NO_SPACE_ASYM_RAM_KEY                  When no RAM anymore available during key injection
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND                   When EEPROM success is not possible during key load
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE                         When key type is wrong during key load
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID                         When key id is wrong during key load
 * - @ref ecy_hsm_CSAI_ERR_KEY_LOCKED_BY_DEBUG                    When key is locked during debug
 * - @ref ecy_hsm_CSAI_ERR_KEY_LOCKED_BY_SECURE_BOOT              When key is locked during secure boot
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE                         When handle is not valid or has the wrong type
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED                         When key is not loaded during unpacking it
 * - @ref ecy_hsm_CSAI_ERR_KEY_WRONG_SESSION                      When session is wrong
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                               When an error happens during verification of the signature
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecAcc_VerifyResponse(ecy_hsm_Csai_JobHandleT hJob,
                                                                                               const uint8*            pResponse,
                                                                                               uint32                  numResponse,
                                                                                               uint32*                 pResultFlag);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_SECACC

#endif /* ECY_HSM_CSAI_SECACC_H */
