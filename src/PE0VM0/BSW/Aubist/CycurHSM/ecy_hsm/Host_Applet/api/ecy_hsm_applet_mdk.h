/**
 * @file
 ***********************************************************************************************
 * @brief MDK Applet interface.
 * This header file is part of the MDK applet
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_MDK_H
# define ECY_HSM_MDK_H

/* *** includes *******************************************************************************/

# include "ecy_hsm_applet.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */

/* *** defines ********************************************************************************/

/**
 * @brief Possible states for MDK applet
 * @details
 * @section APPLET_MDK MDK applet
 *
 * @subsection APPLET_MDK_STATES Applet states
 */

typedef enum ecy_hsm_Applet_MDK_StateT
{
    ecy_hsm_APPLET_MDK_FUNC_INIT,                                       /**< initialize MDK*/
    ecy_hsm_APPLET_MDK_FUNC_SUSPEND,                                    /**< suspend MDK*/
    ecy_hsm_APPLET_MDK_FUNC_GENERATE_COMMAND_AUTH,                      /**< generate CMAC for CAPDU*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_RESPONSE_AUTH,                       /**< validate CMAC of RAPDU*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_LONGTERM_KEYPAIR,                    /**< create long-term keypair*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_EPHEMERAL_KEYPAIR,                   /**< return active ephemeral keypair*/
    ecy_hsm_APPLET_MDK_FUNC_CALC_SECRET_OWNER_PAIRING,                  /**< calculate owner pairing*/
    ecy_hsm_APPLET_MDK_FUNC_SIGN_VEHICLE_AUTH_DATA,                     /**< sign data with vehicle private key*/
    ecy_hsm_APPLET_MDK_FUNC_ENCRYPT_COMMAND,                            /**< encrypt command*/
    ecy_hsm_APPLET_MDK_FUNC_DECRYPT_RESPONSE,                           /**< decrypt command*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_STANDARD,             /**< create secure channel - standard*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_FAST,                 /**< create secure channel - fast*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_OWNER_PAIRING,        /**< conclude key-exchange for secure channel*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_ATTESTATION_PACKAGE,                 /**< verify attestation package*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_AUTHDATA_SIGNATURE,         /**< verify signature of endpoint authentication data*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_CREATION_ATTESTATION_CHAIN, /**< verify endpoint creation attestation chain*/
    ecy_hsm_APPLET_MDK_FUNC_SET_OWNER_PAIRING_VERIFIER,                 /**< set owner pairing verifier*/
    ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEY,                         /**< delete single MDK key*/
    ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEYS,                        /**< delete all MDK keys*/
    ecy_hsm_APPLET_MDK_FUNC_CLOSE_SECURE_CHANNEL,                       /**< close secure channel*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_SHARING_PASSWORD,                    /**< verify sharing password*/
    ecy_hsm_APPLET_MDK_FUNC_SET_OEM_CERTIFICATE,                        /**< set OEM root certificate*/
    ecy_hsm_APPLET_MDK_FUNC_GET_FRIEND_PUBKEY,                          /**< get friend public key*/
    ecy_hsm_APPLET_MDK_FUNC_GEN_KEY_MANAGEMENT_CMAC,                    /**< generate CMAC over key management data*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_KEY_MANAGEMENT_CMAC,                 /**< verify CMAC over key management data*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_URSK,                                /**< create URSK*/
    ecy_hsm_APPLET_MDK_FUNC_GET_URSK,                                   /**< get URSK key*/
    ecy_hsm_APPLET_MDK_FUNC_CREATE_KBLE_OOB,                            /**< create KBLE OOB*/
    ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_SIGNATURE,                  /**< verify endpoint signature*/
    ecy_hsm_APPLET_MDK_FUNC_GET_TAG1_SC,                                /**< get WFS tag1 */
    ecy_hsm_APPLET_MDK_FUNC_ERASE_ENC_KEY_SC,                           /**< erase ENC_KEY_SC */
    ecy_hsm_APPLET_MDK_FUNC_CHECK_TAG2_SC,                              /**< check WFS tag2 */
    ecy_hsm_APPLET_MDK_FUNC_GET_SKC1,                                   /**< return SKC1 */
    ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1,                                 /**< erase SKC1 */
    ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1_ERSATZWERT,                      /**< erase SKC1-Ersatzwert */
    ecy_hsm_APPLET_MDK_FUNC_SET_SC_KEYS,                                /**< set SC keys */

    /* This needs to be the final entry */
    ecy_hsm_APPLET_MDK_NUMSTATES /**< number of states */
} ecy_hsm_Applet_MDK_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_INIT
 */
# define APPLET_MDK_FUNC_INIT                                       ecy_hsm_APPLET_MDK_FUNC_INIT
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_SUSPEND
 */
# define APPLET_MDK_FUNC_SUSPEND                                    ecy_hsm_APPLET_MDK_FUNC_SUSPEND
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GENERATE_COMMAND_AUTH
 */
# define APPLET_MDK_FUNC_GENERATE_COMMAND_AUTH                      ecy_hsm_APPLET_MDK_FUNC_GENERATE_COMMAND_AUTH
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_RESPONSE_AUTH
 */
# define APPLET_MDK_FUNC_VERIFY_RESPONSE_AUTH                       ecy_hsm_APPLET_MDK_FUNC_VERIFY_RESPONSE_AUTH
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_LONGTERM_KEYPAIR
 */
# define APPLET_MDK_FUNC_CREATE_LONGTERM_KEYPAIR                    ecy_hsm_APPLET_MDK_FUNC_CREATE_LONGTERM_KEYPAIR
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_EPHEMERAL_KEYPAIR
 */
# define APPLET_MDK_FUNC_CREATE_EPHEMERAL_KEYPAIR                   ecy_hsm_APPLET_MDK_FUNC_CREATE_EPHEMERAL_KEYPAIR
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CALC_SECRET_OWNER_PAIRING
 */
# define APPLET_MDK_FUNC_CALC_SECRET_OWNER_PAIRING                  ecy_hsm_APPLET_MDK_FUNC_CALC_SECRET_OWNER_PAIRING
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_SIGN_VEHICLE_AUTH_DATA
 */
# define APPLET_MDK_FUNC_SIGN_VEHICLE_AUTH_DATA                     ecy_hsm_APPLET_MDK_FUNC_SIGN_VEHICLE_AUTH_DATA
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_ENCRYPT_COMMAND
 */
# define APPLET_MDK_FUNC_ENCRYPT_COMMAND                            ecy_hsm_APPLET_MDK_FUNC_ENCRYPT_COMMAND
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_DECRYPT_RESPONSE
 */
# define APPLET_MDK_FUNC_DECRYPT_RESPONSE                           ecy_hsm_APPLET_MDK_FUNC_DECRYPT_RESPONSE
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_STANDARD
 */
# define APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_STANDARD             ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_STANDARD
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_FAST
 */
# define APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_FAST                 ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_FAST
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_OWNER_PAIRING
 */
# define APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_OWNER_PAIRING        ecy_hsm_APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_OWNER_PAIRING
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_ATTESTATION_PACKAGE
 */
# define APPLET_MDK_FUNC_VERIFY_ATTESTATION_PACKAGE                 ecy_hsm_APPLET_MDK_FUNC_VERIFY_ATTESTATION_PACKAGE
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_AUTHDATA_SIGNATURE
 */
# define APPLET_MDK_FUNC_VERIFY_ENDPOINT_AUTHDATA_SIGNATURE         ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_AUTHDATA_SIGNATURE
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_CREATION_ATTESTATION_CHAIN
 */
# define APPLET_MDK_FUNC_VERIFY_ENDPOINT_CREATION_ATTESTATION_CHAIN ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_CREATION_ATTESTATION_CHAIN
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_SET_OWNER_PAIRING_VERIFIER
 */
# define APPLET_MDK_FUNC_SET_OWNER_PAIRING_VERIFIER                 ecy_hsm_APPLET_MDK_FUNC_SET_OWNER_PAIRING_VERIFIER
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEY
 */
# define APPLET_MDK_FUNC_DELETE_DIGITAL_KEY                         ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEY
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEYS
 */
# define APPLET_MDK_FUNC_DELETE_DIGITAL_KEYS                        ecy_hsm_APPLET_MDK_FUNC_DELETE_DIGITAL_KEYS
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CLOSE_SECURE_CHANNEL
 */
# define APPLET_MDK_FUNC_CLOSE_SECURE_CHANNEL                       ecy_hsm_APPLET_MDK_FUNC_CLOSE_SECURE_CHANNEL
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_SHARING_PASSWORD
 */
# define APPLET_MDK_FUNC_VERIFY_SHARING_PASSWORD                    ecy_hsm_APPLET_MDK_FUNC_VERIFY_SHARING_PASSWORD
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_SET_OEM_CERTIFICATE
 */
# define APPLET_MDK_FUNC_SET_OEM_CERTIFICATE                        ecy_hsm_APPLET_MDK_FUNC_SET_OEM_CERTIFICATE
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GET_FRIEND_PUBKEY
 */
# define APPLET_MDK_FUNC_GET_FRIEND_PUBKEY                          ecy_hsm_APPLET_MDK_FUNC_GET_FRIEND_PUBKEY
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GEN_KEY_MANAGEMENT_CMAC
 */
# define APPLET_MDK_FUNC_GEN_KEY_MANAGEMENT_CMAC                    ecy_hsm_APPLET_MDK_FUNC_GEN_KEY_MANAGEMENT_CMAC
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_KEY_MANAGEMENT_CMAC
 */
# define APPLET_MDK_FUNC_VERIFY_KEY_MANAGEMENT_CMAC                 ecy_hsm_APPLET_MDK_FUNC_VERIFY_KEY_MANAGEMENT_CMAC
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_URSK
 */
# define APPLET_MDK_FUNC_CREATE_URSK                                ecy_hsm_APPLET_MDK_FUNC_CREATE_URSK
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GET_URSK
 */
# define APPLET_MDK_FUNC_GET_URSK                                   ecy_hsm_APPLET_MDK_FUNC_GET_URSK
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CREATE_KBLE_OOB
 */
# define APPLET_MDK_FUNC_CREATE_KBLE_OOB                            ecy_hsm_APPLET_MDK_FUNC_CREATE_KBLE_OOB
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_SIGNATURE
 */
# define APPLET_MDK_FUNC_VERIFY_ENDPOINT_SIGNATURE                  ecy_hsm_APPLET_MDK_FUNC_VERIFY_ENDPOINT_SIGNATURE
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GET_TAG1_SC
 */
# define APPLET_MDK_FUNC_GET_TAG1_SC                                ecy_hsm_APPLET_MDK_FUNC_GET_TAG1_SC
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_ERASE_ENC_KEY_SC
 */
# define APPLET_MDK_FUNC_ERASE_ENC_KEY_SC                           ecy_hsm_APPLET_MDK_FUNC_ERASE_ENC_KEY_SC
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_CHECK_TAG2_SC
 */
# define APPLET_MDK_FUNC_CHECK_TAG2_SC                              ecy_hsm_APPLET_MDK_FUNC_CHECK_TAG2_SC
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_GET_SKC1
 */
# define APPLET_MDK_FUNC_GET_SKC1                                   ecy_hsm_APPLET_MDK_FUNC_GET_SKC1
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1
 */
# define APPLET_MDK_FUNC_ERASE_SKC1                                 ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1_ERSATZWERT
 */
# define APPLET_MDK_FUNC_ERASE_SKC1_ERSATZWERT                      ecy_hsm_APPLET_MDK_FUNC_ERASE_SKC1_ERSATZWERT
/**
 * @deprecated by ecy_hsm_APPLET_MDK_FUNC_SET_SC_KEYS
 */
# define APPLET_MDK_FUNC_SET_SC_KEYS                                ecy_hsm_APPLET_MDK_FUNC_SET_SC_KEYS
/**
 * @deprecated by ecy_hsm_APPLET_MDK_NUMSTATES
 */
# define APPLET_MDK_NUMSTATES                                       ecy_hsm_APPLET_MDK_NUMSTATES

/**
 * Parameters needed for ephemeral and longterm key generation
 */
typedef struct ecy_hsm_Applet_MDK_DataOut_ParamTag
{
    uint8* pData;           /**< Pointer to output buffer */
    uint32 dataLengthInt;   /**< Intermediate parameter which holds the size of buffer reserved for the output. This value is set to
                                 the content of pOutDataLength during the applet parameter check and must not be set in the host driver. */
    uint32* pOutDataLength; /**< Number of written bytes in output buffer */
} ecy_hsm_Applet_MDK_DataOut_ParamT;

/**
 * Parameters for all MDK functions that are passing a buffer and a fix buffer length
 */
typedef struct ecy_hsm_Applet_MDK_DataIn_ParamTag
{
    const uint8* pData;      /**< Pointer to input data. */
    uint32       dataLength; /**< Length of input data. */
} ecy_hsm_Applet_MDK_DataIn_ParamT;

/**
 * Parameters for all MDK function that process some input data and return the result in an output buffer
 * with fix or variable output size (e.g., EncryptResponse, DecryptResponse, SignVehicleAuthenticationData, etc.).
 */
typedef struct ecy_hsm_Applet_MDK_DataToResult_ParamTag
{
    const uint8* pData;               /**< Pointer to input data. */
    uint32       dataLength;          /**< Length of input data. */
    uint8*       pResult;             /**< Pointer to result. */
    uint32       resultBufferSizeInt; /**< Intermediate parameter which holds the size of buffer the result is written to. The value is set to
                                           the content of pResultLength during the applet parameter check and must not be set in the host driver. */
    uint32* pResultLength;            /**< Pointer to length of result. */
} ecy_hsm_Applet_MDK_DataToResult_ParamT;

/**
 * Parameters for all MDK verification functions where a one byte result is written to an output buffer
 * (e.g., VerifyResponseAuthentication, VerifyKeyManagementCmac, etc.).
 */
typedef struct ecy_hsm_Applet_MDK_ValidateData_ParamTag
{
    const uint8* pData;           /**< Pointer to input data. */
    uint32       dataLength;      /**< Length of input data. */
    const uint8* pReference;      /**< Pointer to array in host RAM where reference to be validated is stored. */
    uint32       referenceLength; /**< Length of the reference buffer */
    uint8*       pResult;         /**< Pointer to memory location where result of the verification is stored. */
} ecy_hsm_Applet_MDK_ValidateData_ParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_MDK_StateT
 */
# define Applet_MDK_StateT                ecy_hsm_Applet_MDK_StateT
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataOut_ParamTag
 */
# define Applet_MDK_DataOut_ParamTag      ecy_hsm_Applet_MDK_DataOut_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataOut_ParamT
 */
# define Applet_MDK_DataOut_ParamT        ecy_hsm_Applet_MDK_DataOut_ParamT
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataIn_ParamTag
 */
# define Applet_MDK_DataIn_ParamTag       ecy_hsm_Applet_MDK_DataIn_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataIn_ParamT
 */
# define Applet_MDK_DataIn_ParamT         ecy_hsm_Applet_MDK_DataIn_ParamT
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataToResult_ParamTag
 */
# define Applet_MDK_DataToResult_ParamTag ecy_hsm_Applet_MDK_DataToResult_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_MDK_DataToResult_ParamT
 */
# define Applet_MDK_DataToResult_ParamT   ecy_hsm_Applet_MDK_DataToResult_ParamT
/**
 * @deprecated by ecy_hsm_Applet_MDK_ValidateData_ParamTag
 */
# define Applet_MDK_ValidateData_ParamTag ecy_hsm_Applet_MDK_ValidateData_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_MDK_ValidateData_ParamT
 */
# define Applet_MDK_ValidateData_ParamT   ecy_hsm_Applet_MDK_ValidateData_ParamT

/* *** extern declarations ********************************************************************/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_START_SEC_CONST_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/**
 * @brief MDK applet control structures
 */
extern const Applet_ts Applet_MDK_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
# ifdef __cplusplus
extern "C" {
# endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
# ifdef __cplusplus
} /* extern "C" */
# endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* Multiple inclusion lock  */

/**
 * @endcond
 */
