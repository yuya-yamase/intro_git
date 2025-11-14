/**
 * @file
 ***********************************************************************************************
 * @brief CSAI secure HOST debug with challenge response operations.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for secure HOST debug with challenge response.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2022, all rights reserved
 **********************************************************************************************/
/* [$Satisfies $COMPONENT Secure_Host_Debug_CSAI] */

#ifndef ECY_HSM_CSAI_SECURE_HOST_DEBUG_WITH_CR_H
#define ECY_HSM_CSAI_SECURE_HOST_DEBUG_WITH_CR_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
/**
 * @addtogroup GROUP_CSAI_SECURE_HOST_DEBUG_WITH_CR_H
 * @{
 */

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/******************* Get challenge - type definitions ************************/

/**
 * @brief Structure containing parameters for use case version 0.
 */
typedef struct ecy_hsm_Csai_SecureHostDebugWithCR_GetChallengeParamTag_v0 {

    /** Encryption/ authentication key id */
    uint32 encKeyId;

    /** Client IV used for encryption/ decryption of client data */
    uint8* clientIV;

    /** Encrypted client data containing client random number */
    uint8* clientEncData;

    /** Proof of Ownership key id */
    uint32 ownerKeyId;

    /** IV returned by HSM used for encryption/ decryption of server data */
    uint8* serverIV;

    /** Encrypted data returned from HSM */
    uint8* serverEncData;
} ecy_hsm_Csai_SecureHostDebugWithCR_GetChallengeParamT_v0;

/**
 * @brief Enumeration containing actual use cases.
 */
typedef enum ecy_hsm_Csai_getChallengeUseCaseIDTag
{
    /** Use case Secure Host Debug with Challenge Response Version 0 - Get challenge*/
    ecy_hsm_Csai_secure_host_debug_with_cr_get_challenge_v0 = 0U,

    /** Reserved */
    ecy_hsm_Csai_get_challenge_reserved = 0x7FFFFFFFU,
} ecy_hsm_Csai_getChallenge_UseCaseIDT;

/**
 * @brief Union structure containing actual versions of the use case.
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union
{
    /** GetChallenge structure for use case Secure Host Debug with Challenge Response Version 0 */
    ecy_hsm_Csai_SecureHostDebugWithCR_GetChallengeParamT_v0 param0;
} ecy_hsm_Csai_GetChallenge_T;

/**
 * @brief Structure wrapping the use case id and the union containing
 *        corresponding versions of the use case.
 */
typedef struct ecy_hsm_Csai_WrappedGetChallengeParamStructTag
{
    /** Use case Id */
    ecy_hsm_Csai_getChallenge_UseCaseIDT useCaseID;

    /** Union containing getChallenge parameter structures */
    ecy_hsm_Csai_GetChallenge_T          getChallengeParameters;
} ecy_hsm_Csai_WrappedGetChallengeParamStructT;

/******************* Verify response - type definitions **********************/

/**
 * @brief Structure containing parameters for use case version 0.
 */
typedef struct ecy_hsm_Csai_SecureHostDebugWithCR_VerifyResponseParamTag_v0
{
    /** Client IV used for encryption/ decryption of client data */
    uint8*  clientIV;

    /** Response data containing encrypted Client Proof of Ownership */
    uint8*  clientResponseData;

    /** CMAC verification result */
    uint32* verificationResult;
} ecy_hsm_Csai_SecureHostDebugWithCR_VerifyResponseParamT_v0;

/**
 * @brief Enumeration containing actual use cases.
 */
typedef enum ecy_hsm_Csai_verifyResponseUseCaseIDTag
{
    /** Use case Secure Host Debug with Challenge Response Version 0 - Verify response*/
    ecy_hsm_Csai_secure_host_debug_with_cr_verify_response_v0 = 0U,

    /** Reserved */
    ecy_hsm_Csai_verify_response_reserved = 0x7FFFFFFFU,
} ecy_hsm_Csai_verifyResponse_UseCaseIDT;

/**
 * @brief Union structure containing actual versions of the use case.
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union
{
    /** VerifyResponse structure for use case Secure Host Debug with Challenge Response Version 0 */
    ecy_hsm_Csai_SecureHostDebugWithCR_VerifyResponseParamT_v0 param0;
} ecy_hsm_Csai_VerifyResponse_T;

/**
 * @brief Structure wrapping the use case id and the union containing
 *        corresponding versions of the use case.
 */
typedef struct ecy_hsm_Csai_WrappedVerifyResponseParamStructTag
{
    /** Use case Id */
    ecy_hsm_Csai_verifyResponse_UseCaseIDT useCaseID;

    /** Union containing getChallenge parameter structures */
    ecy_hsm_Csai_VerifyResponse_T          verifyResponseParameters;
} ecy_hsm_Csai_WrappedVerifyResponseParamStructT;

/******************* Function prototypes *************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1986] Send client request to getting a challenge from server side.
 * [$Satisfies $SW_ARCH 1184] [$Satisfies $SW_ARCH F7C3A8F3]
 *
 * @details
 * The HSM calculates a Server Proof of Ownership by creating a MAC over a random
 * server number and the decrypted client random number, which is sent by the client.
 * The server random number as well as the encrypted Server Proof of Ownership is
 * expected to be returned.
 *
 * @note
 * This function is customer specific and can be absent in some configurations.
 * Also the interface and the supported return format could change.
 *
 * @param[in]    hSession    Handle to the session in which the job will be placed.
 * @param[in]    priority    Requested scheduling priority for this job on the HSM.
 * @param[inout] pParams     GetChallenge parameter structure.
 * @param[out]   phJob       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE
 * - @ref ecy_hsm_CSAI_ERR_SSS_VM_INSTRUCTION_ERROR
 * - @ref ecy_hsm_CSAI_ERR_SSS_INVALID_INSTRUCTION_CODE
 * - @ref ecy_hsm_CSAI_ERR_SSS_END_OF_BYTECODE
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_secure_host_debug_with_cr_GetChallenge(ecy_hsm_Csai_SessionHandleT                         hSession,
                                                                      ecy_hsm_Csai_JobPriorityT                           priority,
                                                                      const ecy_hsm_Csai_WrappedGetChallengeParamStructT* pParams,
                                                                      ecy_hsm_Csai_JobHandleT*                            phJob);

/**
 * [$DD 1987] Send client challenge response and open the debug port.
 * [$Satisfies $SW_ARCH 1184] [$Satisfies $SW_ARCH EEF50840]
 *
 * @details
 * The client sends the challenge response to the HSM, expecting that the debug port
 * is opened after the Client Proof of Ownership has been verified successfully.
 *
 * @note
 * This function is customer specific and can be absent in some configurations.
 * Also the interface and the supported return format could change.
 *
 * @param[in]    hSession    Handle to the session in which the job will be placed.
 * @param[in]    priority    Requested scheduling priority for this job on the HSM.
 * @param[inout] pParams     VerifyResponse parameter structure.
 * @param[out]   phJob       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE
 * - @ref ecy_hsm_CSAI_ERR_SSS_VM_INSTRUCTION_ERROR
 * - @ref ecy_hsm_CSAI_ERR_SSS_INVALID_INSTRUCTION_CODE
 * - @ref ecy_hsm_CSAI_ERR_SSS_END_OF_BYTECODE
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */ 
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_secure_host_debug_with_cr_VerifyResponse(ecy_hsm_Csai_SessionHandleT                           hSession,
                                                                        ecy_hsm_Csai_JobPriorityT                             priority,
                                                                        const ecy_hsm_Csai_WrappedVerifyResponseParamStructT* pParams,
                                                                        ecy_hsm_Csai_JobHandleT*                              phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/** @} */ // GROUP_CSAI_SECURE_HOST_DEBUG_WITH_CR_H

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* ECY_HSM_CSAI_SECURE_HOST_DEBUG_WITH_CR_H */
