/**
 * @file
 ***********************************************************************************************
 * @brief Trusted Platform Module (TPM) applet interface.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * TPM functions for CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_TPM_H
#define ECY_HSM_APPLET_TPM_H

/*
************************************************************************************************
* Includes
************************************************************************************************
*/
#include "ecy_hsm_applet.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */
/*
************************************************************************************************
* Type definitions
************************************************************************************************
*/
/**
 * @brief Possible states for TPM applet
 * @details
 * @section APPLET_TPM Trusted Platform Module applet
 *
 */
typedef enum ecy_hsm_Applet_Tpm_StateT
{
    ecy_hsm_APPLET_TPM_GENERATE_AUTH_VALUE_E,         /**< Generation of an authorisation value in the HSM */
    ecy_hsm_APPLET_TPM_GENERATE_EPHEMERAL_KEY_PAIR_E, /**< Generation of ephemeral key pair, to be used for subsequent TPM interfaces */
    ecy_hsm_APPLET_TPM_DERIVE_SESSION_KEY_E,          /**< Derive a session key for a TPM communication session
                                                           from the associated authorisation value and the ephemeral key pair */
    ecy_hsm_APPLET_TPM_DUPLICATION_BLOB_GEN_E,        /**< Generate an object undergoing the TPM duplication process */
    ecy_hsm_APPLET_TPM_GET_ENCRYPTED_AUTH_VALUE_E,    /**< Encrypt a given authorisation value within a TPM session */
    ecy_hsm_APPLET_TPM_GENERATE_HMAC_E,               /**< Generate an HMAC authentication tag for a TPM command/response */
    ecy_hsm_APPLET_TPM_ENCRYPT_COMMAND_E,             /**< Encrypt a plaintext data with the derived AES key and IV using AES-CFB with corresponding session key and the session-associated authorisation value */
    ecy_hsm_APPLET_TPM_LOAD_VALUE_E,                  /**< Load a persisted TPM value */
    ecy_hsm_APPLET_TPM_RELEASE_VALUE_E,               /**< Release a selected TPM value */
    ecy_hsm_APPLET_TPM_DELETE_VALUE_E,                /**< Delete a persisted TPM value from DFlash */
    ecy_hsm_APPLET_TPM_DECRYPT_RESPONSE_E,            /**< Decrypt a cipher-text data using AES-CFB with corresponding session key and the session-associated authorisation value */

    /* This needs to be the final entry */
    ecy_hsm_APPLET_TPM_NUMSTATES /**< Number of states */
} ecy_hsm_Applet_Tpm_StateT;

/*
************************************************************************************************
* Extern declarations
************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief TPM applet control structures
 */
extern const Applet_ts Applet_Tpm_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_TPM_H */
