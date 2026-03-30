/**
 * \file Crypto_82_Hsm_DensoExtensions.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for implementation of Denso Extensions
 * \details
*/

#ifndef CRYPTO_82_HSM_DENSOEXTENSIONS_H
#define CRYPTO_82_HSM_DENSOEXTENSIONS_H


/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/
#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_DnExt_BulkMac.h"
#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_shecompat.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_service_she.h"
#include "ecy_hsm_csai_data.h"
#include "ecy_hsm_flash_sync.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/
#if ( CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON )

/**
 * \def SIZE_OF_SECRET_DATA_SLOT_IN_BYTES
 * \brief Number of bytes per the general usage data blocks of the HSM NVM store
*/
#define SIZE_OF_SECRET_DATA_SLOT_IN_BYTES               (16u)

/**
 * \def BIT_RESOLUTION_OF_KEY_STATUS
 * \brief Number of bits per key validity status
*/
#define BIT_RESOLUTION_OF_KEY_STATUS                    (2u)

/**
 * \def NUM_KEY_SLOTS_PER_BYTE
 * \brief Number of key validity status in one byte
*/
#define NUM_KEY_SLOTS_PER_BYTE                          (CRYPTO_82_HSM_NUM_BITS_IN_BYTE / BIT_RESOLUTION_OF_KEY_STATUS)

/**
 * \def NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT
 * \brief Number of key validity status that fits in one general usage data block of the HSM NVM store
*/
#define NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT       (SIZE_OF_SECRET_DATA_SLOT_IN_BYTES * NUM_KEY_SLOTS_PER_BYTE)

/**
 * \def NUM_KEY_STATUS_SLOTS
 * \brief Total number of key validity data slots. The total number of "groups".
*/
#define NUM_KEY_STATUS_SLOTS                            (1u + (CRYPTO_82_HSM_NUMBER_OF_KEYS / NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT))

/**
 * \def KEY_STATUS_DATA_ARRAY_SIZE
 * \brief Total number of bytes used/needed for key validity status
*/
#define KEY_STATUS_DATA_ARRAY_SIZE                      (SIZE_OF_SECRET_DATA_SLOT_IN_BYTES + (CRYPTO_82_HSM_NUMBER_OF_KEYS / NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)

/**
 * \def KEY_STATUS_BIT_MASK
 * \brief The bit mask for a key validity slot
*/
#define KEY_STATUS_BIT_MASK                             (0x03u)

/**
 * \def getKeyStatusSlotNumber
 * \brief Get the slot number of the data block in the HSM NVM store where the key validity status of a key is stored
*/
#define getKeyStatusSlotNumber(keyId)                   ((keyId) / NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT)

/**
 * \def getKeyStatusSlotByteNumber
 * \brief Get the byte number of the key validity status in the data block of the Hsm Nvm store
*/
#define getKeyStatusSlotByteNumber(keyId)               (((keyId) % NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT) / NUM_KEY_SLOTS_PER_BYTE)

/**
 * \def getKeyStatusSlotByteStartBitNumber
 * \brief Get bit number per byte in the of the key validity status in the data block
*/
#define getKeyStatusSlotByteStartBitNumber(keyId)       ((((keyId) % NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT) % NUM_KEY_SLOTS_PER_BYTE) * BIT_RESOLUTION_OF_KEY_STATUS)

/**
 * \def isKeyStatus
 * \brief Returns true if key status of a key is equal to (keyStatus)
*/
#define isKeyStatus(keyStatus, dataSlotByte, keyId)     ((((dataSlotByte) >> getKeyStatusSlotByteStartBitNumber((keyId))) & KEY_STATUS_BIT_MASK) == ((uint8)(keyStatus)))

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief The possible key injection operations executed by the function Crypto_82_Hsm_Ext_InjectKey
 */
typedef enum eCrypto_82_Hsm_Ext_InjectKey_Operation
{
    EXT_INJECT_KEY_OPERATION_NONE               = 0x00u,    /** The initial state value which can also be used to reset the internal function states    */
    EXT_INJECT_KEY_OPERATION_INJECT             = 0x01u,    /** Inject a key                                                                            */
    EXT_INJECT_KEY_OPERATION_INJECT_AND_PERSIST = 0x02u,    /** Inject a key and persist it to the NvM key store                                        */
    EXT_INJECT_KEY_OPERATION_PERSIST            = 0x03u,    /** Persist a key to the NvM key store                                                      */
} Crypto_82_Hsm_Ext_InjectKey_Operation;

/**
 * \brief The possible sleep mode types for the function Crypto_82_Hsm_Ext_PowerModeConfig
 */
typedef enum eCrypto_82_Hsm_Ext_PowerModeConfig_SleepMode
{
    EXT_POWER_MODE_DEEP_SLEEP                  = 0x00u,    /** All SRAM blocks are retained                                                             */
    EXT_POWER_MODE_DEEP_SLEEP_EXTENDED         = 0x01u     /** Allows user to select which SRAM blocks are retained                                     */
} Crypto_82_Hsm_Ext_PowerModeConfig_SleepMode;

/**
 * \brief Type to abstract the return codes of the DensoExtension APIs
 */
typedef enum eCrypto_82_Hsm_Ext_ErrorStateType
{
    CRYPTO_82_HSM_EXT_DONE,                             /**< The API request and response are completed successfully. Output buffers are valid */
    CRYPTO_82_HSM_EXT_PROCESSING,                       /**< The API is currently processing the given API */
    CRYPTO_82_HSM_EXT_BUSY,                             /**< The API cannot be processed because another API is in progress */
    CRYPTO_82_HSM_EXT_ERROR,                            /**< The API cannot be processed because the CycurHSM returned an error */
    CRYPTO_82_HSM_EXT_FAILED_KEY_RELEASE_AFTER_ERROR,   /**< Key release queued, after failed peristing of key, has failed */
    CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM,               /**< The API was called with an updated parameter value during processing */
    CRYPTO_82_HSM_EXT_INVALID                           /**< Invalid use of the API; SHOULD NEVER BE RETURNED BY ANY API */
} Crypto_82_Hsm_Ext_ErrorStateType;

/* TODO: Some types should be moved to Porting.h */

/**
 * \brief Type to abstract supported key types
*/
typedef enum eCrypto_82_Hsm_KeyType
{
    Crypto_82_Hsm_KEYTYPE_SYMMETRIC          = 1u,      /**< AES key                                */
    Crypto_82_Hsm_KEYTYPE_RSA_PAIR           = 2u,      /**< RSA key pair                           */
    Crypto_82_Hsm_KEYTYPE_RSA_PUBLIC         = 3u,      /**< RSA public key                         */
    Crypto_82_Hsm_KEYTYPE_RSA_PRIVATE        = 4u,      /**< RSA private key                        */
    Crypto_82_Hsm_KEYTYPE_EDDSA_PRIVATE      = 5u,      /**< EDDSA private key (not supported yet)  */
    Crypto_82_Hsm_KEYTYPE_EDDSA_PAIR         = 6u,      /**< EDDSA key pair                         */
    Crypto_82_Hsm_KEYTYPE_EDDSA_PUBLIC       = 7u,      /**< EDDSA public key                       */
    Crypto_82_Hsm_KEYTYPE_ECDSA_PAIR         = 8u,      /**< ECDSA key pair                         */
    Crypto_82_Hsm_KEYTYPE_ECDSA_PUBLIC       = 9u,      /**< ECDSA public key                       */
    Crypto_82_Hsm_KEYTYPE_ECDSA_PRIVATE      = 10u,     /**< ECDSA private key                      */
    Crypto_82_Hsm_KEYTYPE_SECRET_EC_POINT    = 11u,     /**< Secret elliptic curve point            */
    Crypto_82_Hsm_KEYTYPE_NUM_TYPES,                    /**< Number of defined key types            */
    Crypto_82_Hsm_KEYTYPE_RESERVED           = 0xFFu    /**< Invalid key type                       */
} Crypto_82_Hsm_KeyTypeT;

/**
 * \brief Type to abstract supported key-sizes
*/
typedef enum sCrypto_82_Hsm_KeySize
{
    Crypto_82_Hsm_KEYSIZE_128       = 128u,     /**< Key size is 128 bit (AES)                  */
    Crypto_82_Hsm_KEYSIZE_160       = 160u,     /**< Key size is 160 bit (ECC)                  */
    Crypto_82_Hsm_KEYSIZE_224       = 224u,     /**< Key size is 224 bit (ECC)                  */
    Crypto_82_Hsm_KEYSIZE_256       = 256u,     /**< Key size is 256 bit (AES, ECC)             */
    Crypto_82_Hsm_KEYSIZE_320       = 320u,     /**< Key size is 320 bit (HMAC SHA2 256)        */
    Crypto_82_Hsm_KEYSIZE_384       = 384u,     /**< Key size is 384 bit (ECC)                  */
    Crypto_82_Hsm_KEYSIZE_512       = 512u,     /**< Key size is 512 bit (ECC)                  */
    Crypto_82_Hsm_KEYSIZE_1024      = 1024u,    /**< Key size is 1024 bit (RSA)                 */
    Crypto_82_Hsm_KEYSIZE_2048      = 2048u,    /**< Key size is 2048 bit (RSA)                 */
    Crypto_82_Hsm_KEYSIZE_3072      = 3072u,    /**< Key size is 3072 bit (RSA)                 */
    Crypto_82_Hsm_KEYSIZE_4096      = 4096u,    /**< Key size is 4096 bit (RSA)                 */
    Crypto_82_Hsm_KEYSIZE_RESERVED  = 0x7fffu   /**< Value defined to use memory size of uint16 */
} Crypto_82_Hsm_KeySizeT;

/**
 * \brief Compound type to hold a symmetric key
*/
typedef struct sCrypto_82_Hsm_SymmetricKeyRef
{
    uint8*                  keyBuffer;      /**< Pointer to a buffer holding key data   */
    uint32                  bufferLength;   /**< Length of the key data buffer in bytes */
    Crypto_82_Hsm_KeySizeT  keySize;        /**< Size of the key                        */
} Crypto_82_Hsm_SymmetricKeyRefT;

/**
 * \brief Compound type to hold references to a RSA key pair
*/
typedef struct sCrypto_82_Hsm_RSAKeyPairRef
{
    uint8                   *n;         /**< Pointer to the public modulus (uint8 array) */
    uint32                  nLength;    /**< Length of the modulus buffer in bytes */
    uint32                   e;         /**< Public exponent */
    uint8                   *d;         /**< Pointer to private exponent (uint8 array). If this structure
                                             references or requests the public portion of the RSA key pair then
                                             this may be \c NULL_PTR. */
    uint32                  dLength;    /**< Length of private exponent buffer in bytes. If this structure
                                             references or requests the public portion of the RSA key pair then
                                             this may be \c NULL_PTR. */
    Crypto_82_Hsm_KeySizeT  keySize;    /**< Size of the key in bits */
} Crypto_82_Hsm_RsaKeyPairRefT;

/**
 * \brief Compound type to hold references to a RSA key (public part only)
 */
typedef struct sCrypto_82_Hsm_RSAKeyPublicRef
{
    uint8                   *n;         /**< Pointer to the public modulus (uint8 array)    */
    uint32                  nLength;    /**< Length of the modulus buffer in bytes          */
    uint32                  e;          /**< Public exponent                                */
    Crypto_82_Hsm_KeySizeT  keySize;    /**< Size of the key                                */
} Crypto_82_Hsm_RsaKeyPublicRefT;

/**
 * \brief Compound type to hold references to a RSA key (private part only)
 */
typedef struct sCrypto_82_Hsm_RSAKeyPrivateRef
{
    uint8                   *n;         /**< Pointer to the public modulus (uint8 array)    */
    uint32                  nLength;    /**< Length of the modulus buffer in bytes          */
    uint8                   *d;         /**< Pointer to private exponent (uint8 array).     */
    uint32                  dLength;    /**< Length of private exponent buffer in bytes.    */
    Crypto_82_Hsm_KeySizeT  keySize;    /**< Size of the key */
} Crypto_82_Hsm_RsaKeyPrivateRefT;

/**
 * \brief Compound type to hold references to an ECC key pair
 */
typedef struct sCrypto_82_Hsm_EccKeyPairRefT
{
    uint8*                  pubKey;         /**< Public Key pointer (uint8 array). Public key structure is a
                                                 concatenation of X and Y coordinate. */
    uint32                  pubKeyLength;   /**< Length of the Public Key buffer in bytes */
    uint8*                  privKey;        /**< Private Key pointer (uint8 array)  */
    uint32                  privKeyLength;  /**< Length of the private Key buffer in bytes */
    Crypto_82_Hsm_KeySizeT  keySize;        /**< Key length. */
} Crypto_82_Hsm_EccKeyPairRefT;

/**
 * \brief Created to ensure backwards compatibility with CycurHSM versions below V5.2.0
 * \note Might be removed in future!
 */
typedef Crypto_82_Hsm_EccKeyPairRefT Crypto_82_Hsm_EdDsaKeyPairRefT;

/**
 * \brief Compound type to hold references to an ECC public key
 */
typedef struct sCrypto_82_Hsm_EccKeyPublicRefT
{
    uint8*                  pubKey;         /**< Public Key pointer (uint8 array). Public key structure is a
                                                 concatenation of X and Y coordinate. */
    uint32                  pubKeyLength;   /**< Length of the Public Key buffer in bytes. */
    Crypto_82_Hsm_KeySizeT  keySize;        /**< Key length. */
} Crypto_82_Hsm_EccKeyPublicRefT;

/**
 * \brief Created to ensure backwards compatibility with CycurHSM versions below V5.2.0
 * \note Might be removed in future!
 */
typedef Crypto_82_Hsm_EccKeyPublicRefT Crypto_82_Hsm_EdDsaKeyPublicRefT;

/**
 * \brief Compound type to hold references to an ECC private key
 */
typedef struct sCrypto_82_Hsm_EccKeyPrivateRefT
{
    uint8*                  privKey;        /**< Private Key pointer (uint8 array)           */
    uint32                  privKeyLength;  /**< Length of the Private Key buffer in bytes   */
    Crypto_82_Hsm_KeySizeT  keySize;        /**< Key length                                  */
} Crypto_82_Hsm_EccKeyPrivateRefT;

/**
 * \brief Compound type to hold references to a secret elliptic curve point
 */
typedef struct sCrypto_82_Hsm_SecretEcPointRefT
{
    uint8*                  curvePoint;         /** Pointer to the curve point (uint8 array)                        */
    uint32                  curvePointLength;   /** Length of the curve point buffer in bytes                       */
    Crypto_82_Hsm_KeySizeT  curvePointSize;     /** Curve point size, i.e key size of the respective elliptic curve */
} Crypto_82_Hsm_SecretEcPointRefT;

/**
 * \brief Compound type to hold any key reference
*/
typedef union uCrypto_82_Hsm_KeyContainerType
{
    Crypto_82_Hsm_SymmetricKeyRefT      sym;          /**< Key is a symmetric key, e.g. AES */
    Crypto_82_Hsm_RsaKeyPairRefT        rsapair;      /**< Key is an RSA key pair */
    Crypto_82_Hsm_RsaKeyPublicRefT      rsapub;       /**< Key is an RSA public key */
    Crypto_82_Hsm_RsaKeyPrivateRefT     rsapriv;      /**< Key is an RSA private key */
    Crypto_82_Hsm_EccKeyPairRefT        eccpair;      /**< Key is an ECC key pair, e.g. EDDSA or ECDSA.
                                                           \note before CycurHSM V5.2.0 this was just a dummy,
                                                                 now it's actually used as ecc key pair! */
    Crypto_82_Hsm_EccKeyPublicRefT      eccpub;       /**< Key is an ECC public key, e.g. EDDSA or ECDSA */
    Crypto_82_Hsm_EccKeyPrivateRefT     eccpriv;      /**< Key is an ECC private key, e.g. EDDSA or ECDSA */
    Crypto_82_Hsm_EdDsaKeyPairRefT      eddsapair;    /**< Key is an EdDSA key pair. In fact it's the same as eccpair
                                                           above and is just kept for compatibility with versions below
                                                           V5.2.0.
                                                          \note Might be removed in future! */
    Crypto_82_Hsm_EdDsaKeyPublicRefT    eddsapub;     /**< Key is an EdDSA pub pair. In fact it's the same as eccpub above
                                                           and is just kept for compatibility with versions below V5.2.0
                                                           \note Might be removed in future! */
    Crypto_82_Hsm_SecretEcPointRefT     ecpoint;      /**< A point on an elliptic curve, i.e. the format of a public EC key,
                                                           but with private properties. */
} Crypto_82_Hsm_KeyContainerType;

/**
 * \brief Type to pack the key type and the key reference
 * 
*/
typedef struct sCrypto_82_Hsm_KeyDataType
{
    Crypto_82_Hsm_KeyTypeT          keyType;        /**< The key type       */
    Crypto_82_Hsm_KeyContainerType  keyContainer;   /**< The key reference  */
} Crypto_82_Hsm_KeyDataType;

/**
 * \brief Type to manage status of keys
 */
typedef enum eCrypto_82_Hsm_KeyStatusType
{
    CRYPTO_82_HSM_KEY_INVALID   = 0x00,
    CRYPTO_82_HSM_KEY_VALID     = 0x01,
    CRYPTO_82_HSM_KEY_TBD       = 0x02, /* TODO: Rename this to actual status value */
    CRYPTO_82_HSM_KEY_TBD_TWO   = 0x03  /* TODO: Rename this to actual status value */
} Crypto_82_Hsm_KeyStatusType;

/**
 * \brief Type to abstract the extension APIs
 */
typedef enum
{
    CRYPTO_82_HSM_EXT_API_NONE = 0u,                /**< Invalid extension API */
    CRYPTO_82_HSM_EXT_API_INIT,                     /**< Crypto_82_Hsm_Ext_Init API */
    CRYPTO_82_HSM_EXT_API_SHE_LOADKEY,              /**< Crypto_82_Hsm_Ext_SHELoadKey API */
    CRYPTO_82_HSM_EXT_API_KEY_ELEMENT_GET,          /**< Crypto_82_Hsm_Ext_KeyElementGet API */
    CRYPTO_82_HSM_EXT_API_KEY_STATUS_READ,          /**< Crypto_82_Hsm_Ext_KeyStatusRead API */
    CRYPTO_82_HSM_EXT_API_KEY_SET_VALID,            /**< Crypto_82_Hsm_Ext_KeySetValid API */
    CRYPTO_82_HSM_EXT_API_INJECT_KEY,               /**< Crypto_82_Hsm_Ext_InjectKey API */
    CRYPTO_82_HSM_EXT_API_SHE_GET_ID,               /**< Crypto_82 Hsm_Ext_SHEGetID API */
    CRYPTO_82_HSM_EXT_API_SHE_GET_STATUS,           /**< Crypto_82_Hsm_Ext_SHEGetStatus API */
    CRYPTO_82_HSM_EXT_API_SHE_CANCEL,               /**< Crypto_82_Hsm_Ext_SHECancel API */
    CRYPTO_82_HSM_API_SHE_CMDDEBUG,                 /**< Crypto_82_Hsm_Ext_SHECmdDebug API */
    CRYPTO_82_HSM_EXT_API_KEY_VALIDITY_SERIALIZE,   /**< Crypto_82_Hsm_Ext_KeyValiditySerialize API */
    CRYPTO_82_HSM_EXT_API_RELEASE_KEY,              /**< Crypto_82_Hsm_Ext_ReleaseKey API */
    CRYPTO_82_HSM_EXT_API_LOADKEY,                  /**< Crypto_82_Hsm_Ext_LoadKey API */
    CRYPTO_82_HSM_EXT_API_POWERMODE_CONFIG,         /**< Crypto_82_Hsm_Ext_PowerModeConfig API */
    CRYPTO_82_HSM_EXT_API_CHECKREORGONWRITE,        /**< Crypto_82_Hsm_Ext_CheckReorgOnWrite API */
    CRYPTO_82_HSM_EXT_API_TRIGGERFLASHREORG,        /**< Crypto_82_Hsm_Ext_TriggerFlashReorg API */
    CRYPTO_82_HSM_EXT_API_KEY_GET_STATUS,           /**< Crypto_82_Hsm_Ext_KeyGetStatus API */
    CRYPTO_82_HSM_EXT_API_COUNT                     /**< Total number of extension APIs */
} Crypto_82_Hsm_Ext_ApiType;

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief The currently processed extension API.
 */
extern Crypto_82_Hsm_Ext_ApiType currentProcessedApi;

/**
 * \brief The currently processed extension DFlash Reorg API.
 */
extern Crypto_82_Hsm_Ext_ApiType currentProcessedApiDFlashReorg;

/**
 * \brief The current Key ID used in extension API process.
 */
extern uint32 currentProcessed_arCryptoKeyId;

#define CRYPTO_82_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#endif /* (CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON) */

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief The initializer function for the Crypto Driver extensions
 *
 * \details Initializes the context for the extension APIs. Clears buffers, reads the key validity from HSM flash and
 *          initilizes the module to the default state.
 */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)  
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_Init(void);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Update key into the persistent HSM key-store (NVRAM)
 *
 * \details Additionally SHE LoadKey command specifies decryption and authentication of the provided key-material
 *          (SHE key-wrapping protocol)
 *
 * \param [in]  arKeyId                 Id of autosar modelled key
 * \param [in]  m1                      Pointer to array containing data for SHE-M1
 * \param [in]  m2                      Pointer to array containing data for SHE-M2
 * \param [in]  m3                      Pointer to array containing data for SHE-M3
 * \param [out] m4                      Pointer to array containing data for SHE-M4 (response from system)
 * \param [out] m5                      Pointer to array containing data for SHE-M5 (response from system)
 * \param [in]  bankNumber              The SHE+ bank addressed - SHE+ bank that shall receive the key-material
 *
 * \retval CRYPTO_82_HSM_EXT_DONE       The key storage is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key storage is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key storage request returned an error
 */
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHELoadKey(
    uint32      arCryptoKeyId,
    const uint8* m1,
    const uint8* m2,
    const uint8* m3,
    uint8*       m4,
    uint8*       m5,
    uint8       bankNumber
);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

/**
 * \brief Retrieve public key or SHE RAM key from the given AUTOSAR modelled key
 *
 * \details To retrieve a public key might be necessary in certain situations (e.g. asymmetric key-agreement or
 *          certificate signing request). On the other hand the SHE RAM key should be retrievable. This function 
 *          attempts to realize both.
 *
 * \param [in]      arCryptoKeyId       The AUTOSAR modelled key ID
 * \param [in, out] keyBuffer           Buffer to store the key into or read the SHE key material from
 * \param [in]      bufferLen           The length of the key in bytes
 *
 * \note In the case of SHE RAM keys, the keyBuffer must be the concatenated M1,M2,M3 and the bufferLen must be \b 64
 *
 * \retval CRYPTO_82_HSM_EXT_DONE       The key retrieval is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key retrieval is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key retrieval request returned an error
 */
#if (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyElementGet(
    uint32 arCryptoKeyId,
    uint8* keyBuffer,
    uint32 bufferLen
);
#endif /* (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) */

/**
 * \brief Inject a key
 *
 * \param [in]      arCryptoKeyId               ID of AUTOSAR key to use
 * \param [in, out] pKeyContainer               Pointer to data buffer
 * \param [in]      keyProperties               CycurHSM key properties flags
 * \param [in]      operation                   The inject key operation which will be performed
 *
 * \retval CRYPTO_82_HSM_EXT_DONE               The key retrieval is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING         The key retrieval is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY               The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM The key retrieval request returned an error
 * \retval CRYPTO_82_HSM_EXT_ERROR              The key retrieval request returned an error
 */
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_InjectKey(
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyDataType* pKeyData,
    uint32 keyProperties,
    Crypto_82_Hsm_Ext_InjectKey_Operation operation
);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

/**
 * \brief Retrieve status of an AUTOSAR modelled key
 *
 * \param [in]  arCryptoKeyId           The AUTOSAR modelled key ID
 * \param [out] keyStatusPtr            Pointer where to store status of key
 *
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key status retrieval returned an error.
 * \retval CRYPTO_82_HSM_EXT_DONE       Key status has been read successfully.
 */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyStatusRead(
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyStatusType* keyStatusPtr
);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Set status of an AUTOSAR modelled key
 *
 * \param [in]  arCryptoKeyId           The AUTOSAR modelled key ID
 * \param [in]  validity                Status of the key
 *
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key status setting is currently in progress, check later.
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key status setting returned an error.
 * \retval CRYPTO_82_HSM_EXT_DONE       Key status has been set successfully.
 */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeySetValid(
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyStatusType validity
);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Serialize validity status of one key group or all key groups to HSM flash
 *
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key validity serialization is currently in progress, check later.
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key validity serialization returned an error.
 * \retval CRYPTO_82_HSM_EXT_DONE       Key validity status has been serialized successfully.
 */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyValiditySerialize(void);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Returns the identity (UID) and the value of the status register protected by a MAC over a challenge and the
 *        data as specified by SHE V1.1
 *
 * \details To retrieve the unique ID of the SHE chip which might be necessary in certain situations (e.g. provisioning
 *          of the MASTER_ECU_KEY)
 * 
 * \note If the MASTER_ECU_KEY is empty, then the MAC is returned as zero.
 *
 * \param [in]  challenge               Caller provided challenge
 * \param [out] id                      Buffer to receive the SHE module UID
 * \param [out] status                  Pointer to receive the value of the SHE status register
 * \param [out] mac                     Buffer to receive the CMAC of the challenge, UID and status value
 *
 * \retval CRYPTO_82_HSM_EXT_DONE       The key retrieval is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key retrieval is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key retrieval request returned an error
 */
#if (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHEGetID(
    const uint8 challenge[16],
    uint8       id[15],
    uint8*      status,
    uint8       mac[16]
);
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) */

/**
 * \brief Returns the value of the SHE status register
 *
 * \param [out] status              Pointer to receive the value of the SHE status register
 *
 * \retval CRYPTO_82_HSM_EXT_DONE   The key retrieval is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_BUSY   The HSM is busy with another operation, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR  The key retrieval request returned an error.
 */
#if (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHEGetStatus(uint8* status);
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) */

/**
 * \brief Interrupt and cancel any running SHE functionality and discard all calculations and results
 *
 * \note Due to the asynchronous design nature of this SHE interface, the result will not be available when the 
 *       function returns. Use SHE_Sync() to sync the result.
 * 
 * \note The ERC_BUSY error may be returned by a subsequent call to SHE_Cancel. After a cancelation new SHE requests
 *       are then elevated to "medium" priority until the old one is finished. This also means that the elevated
 *       priority request cannot be cancelled.
 * 
 * \note The following values may be returned by a subsequent call to SHE_Sync:
 *          - ERC_NO_ERROR      --> CRYPTO_82_HSM_EXT_DONE
 *          - ERC_GENERAL_ERROR --> CRYPTO_82_HSM_EXT_PROCESSING
 *
 * \retval CRYPTO_82_HSM_EXT_DONE       The key retrieval is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING The key retrievel is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key retrieval request returned an error
 */
#if (CRYPTO_82_HSM_SHE_CANCEL == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHECancel(void);
#endif /* (CRYPTO_82_HSM_SHE_CANCEL == STD_ON) */

/**
 * \brief Wrapper function used to execute SHE_CmdDebugChallenge or SHE_CmdDebugAuthorize
 *
 * \param [in out]  authOrChallenge     Buffer to CMAC to verify or to output the challenge
 * \param [in]      challengeFlag       Select CmdDebug challenge generation or authorization verification
 *
 * \retval CRYPTO_82_HSM_EXT_DONE       Extension job finished, result buffer valid
 * \retval CRYPTO_82_HSM_EXT_BUSY       Another extension job is being processed come again later
 * \retval CRYPTO_82_HSM_EXT_PROCESSING Extension job not finished yet, check later
 */
#if (CRYPTO_82_HSM_SHE_DEBUG == STD_ON) 
Crypto_82_Hsm_Ext_ErrorStateType Crypto_82_Hsm_Ext_SHECmdDebug(uint8* authOrChallenge, boolean challengeFlag);
#endif /* (CRYPTO_82_HSM_SHE_DEBUG == STD_ON) */

/**
 * \brief Set the the dirty flag to TRUE for the correspondent group of the AUTOSAR modelled key ID.
 * 
 * \param [in] arCryptoKeyId The AUTOSAR modelled key ID
*/
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(uint32 arCryptoKeyId);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Set key validity status of a key in RAM status buffer.
 *
 * \param [in]      keyStatus               The current status of the key to be set
 * \param [in, out] bufferPtr               The key validity status in RAM
 * \param [in]      arCryptoKeyId           The AUTOSAR modelled key Id.
 */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SetKeyStatusBitMask(
    Crypto_82_Hsm_KeyStatusType keyStatus,
    uint8* bufferPtr,
    uint32 arCryptoKeyId
);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Release a key
 *
 * \param [in]      arCryptoKeyId               The AUTOSAR modelled key ID
 *
 * \retval CRYPTO_82_HSM_EXT_DONE               The key was successfully released from HSM RAM.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING         The releasing of the key is currently processing, check later
 * \retval CRYPTO_82_HSM_EXT_BUSY               The HSM is busy with another operation, check later
 * \retval CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM The key release request called with wrong Key ID while processing is ongoing
 * \retval CRYPTO_82_HSM_EXT_ERROR              The key release request returned an error
 */
#if (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_ReleaseKey(
    uint32 arCryptoKeyId
);
#endif /* (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) */

/**
 * \brief Loads the persistent key element from the Nvm key store to HSM RAM.
 *
 * \param [in]      arCryptoKeyId                 The AUTOSAR modelled key Id for which the persistent key element will be loaded.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished, result buffer valid.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM   The call cannot be processed becuase the API is already being processed with another key.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING           Extension job not finished yet, check later.
 */
#if (CRYPTO_82_HSM_KEY_LOADING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_LoadKey(
    uint32 arCryptoKeyId
);
#endif /* (CRYPTO_82_HSM_KEY_LOADING == STD_ON) */

/**
 * \brief Configures and initializes the HSM system interrupt control register by setting the given configuration data.
 *
 * \param [in]      pConfigData                   Pointer to configuration data.
 * \param [in]      configDataLen                 Length of the configuration data.
 * \param [in]      sleepMode                     Setting to retain all SRAM blocks or allow user to select which SRAM blocks shall be retained.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished, result buffer valid.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_ERROR                An error has occurred.
 */
#if (CRYPTO_82_HSM_POWER_MODE == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_PowerModeConfig( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    void* pConfigData,
    uint32 configDataLen,
    Crypto_82_Hsm_Ext_PowerModeConfig_SleepMode sleepMode
);
#endif /* (CRYPTO_82_HSM_POWER_MODE == STD_ON) */

/**
 * \brief Checks if a total amount of data to write to the HSM secure storage, for a particular block ID, would trigger an FEE hard reorganization. Returns the status (safe to write or not), as well as the maximum number of write operations possible for that block without triggering a reorganization.
 *
 * \param [in]      arCryptoKeyId                 ID of AUTOSAR key for which the check will be performed (if the key references an HSM block).
 * \param [in]      sizeToCheck                   Desired amount of bytes to be written.
 * \param [out]     isSafeToWrite                 TRUE if writing would not trigger a reorganization. FALSE if writing would trigger a reorganization.
 * \param [out]     possibleNumWrites             The number of times the write operation can be repeated without triggering a reorganization.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished, result buffers valid.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING           Extension job not finished yet, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR                An error has occurred.
 */
#if (CRYPTO_82_HSM_FEE_REORG == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_CheckReorgOnWrite(
    uint32 arCryptoKeyId,
    uint32 sizeToCheck,
    boolean* isSafeToWrite,
    uint32* possibleNumWrites
);
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */

/**
 * \brief Triggers an FEE soft reorganization which cleans up the data flash content and ensures the maximum number of bytes writeable without causing a (hard) reorganization to take place.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished successfully.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING           Extension job not finished yet, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR                An error has occurred.
 */
#if (CRYPTO_82_HSM_FEE_REORG == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_TriggerFlashReorg(void);
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */

/**
 * \brief Changes the Host Flash Access State to Reading if State parameter is 0 or changes the Host Flash Access State to Writing if State parameter is 1.
 *
 * \param [in]      State                         Host Flash Access State.
 * \param [in]      timeout_ms                    Timeout definition for setting new state.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished, result buffer valid.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_ERROR                An error has occurred.
 */
#if (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_FlashSync_HostStart( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 State,
    uint32 timeout_ms 
);
#endif /* (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */

/**
 * \brief Changes the Host Flash Access State to no operation.
 *
 * \param [in]      timeout_ms                    Timeout definition for setting new state.
 * 
 * \retval CRYPTO_82_HSM_EXT_DONE                 Extension job finished, result buffer valid.
 * \retval CRYPTO_82_HSM_EXT_BUSY                 Another extension job is being processed come again later.
 * \retval CRYPTO_82_HSM_EXT_ERROR                An error has occurred.
 */
#if (CRYPTO_82_HSM_FLASH_SYNC == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_FlashSync_HostEnd( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 timeout_ms
);
#endif /* (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */

/**
 * \brief Retrieve AUTOSAR key validity status of an AUTOSAR modelled key
 *
 * \param [in]  arCryptoKeyId           The AUTOSAR modelled key ID
 * \param [out] keyStatusPtr            Pointer where to store status of key
 *
 * \retval CRYPTO_82_HSM_EXT_BUSY       The HSM is busy with another operation, check later.
 * \retval CRYPTO_82_HSM_EXT_ERROR      The key status retrieval returned an error.
 * \retval CRYPTO_82_HSM_EXT_DONE       Key status has been read successfully.
 */
#if (CRYPTO_82_HSM_AUTOSAR_KEY_VALIDITY == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyGetStatus(
    uint32 arCryptoKeyId,
    boolean *keyStatusPtr);
#endif /* (CRYPTO_82_HSM_AUTOSAR_KEY_VALIDITY == STD_ON) */

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif
