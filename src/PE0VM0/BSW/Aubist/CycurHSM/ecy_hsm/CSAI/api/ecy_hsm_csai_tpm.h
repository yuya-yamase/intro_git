/**
 * @file
 ***********************************************************************************************
 * @brief Trusted Platform Module (TPM) CSAI.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for the Trusted Platform Module (TPM) operations
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_TPM_H
#define ECY_HSM_CSAI_TPM_H

/**
 * @addtogroup GROUP_CSAI_TPM
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_dh.h"
#include "ecy_hsm_csai_hash.h"
#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_keyid.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_CSAI_TPM_DERIVE_UNSALTED_SESSION_KEY (0UL) /**< Salt is not used for session key derivation */
#define ecy_hsm_CSAI_TPM_DERIVE_SALTED_SESSION_KEY   (1UL) /**< Salt is used for session key derivation */

/* *** Type declarations **********************************************************************/

/** Define known authorisation value sizes in bytes */
typedef enum ecy_hsm_Csai_Tpm_AuthValueSizeTag
{
    ecy_hsm_CSAI_TPM_AUTH_VALUE_SIZE_0_BYTE   = 0UL,  /**< Support 0 byte of authorisation value sizes
                                                           Note: This means AuthValue will not be used in the operation */
    ecy_hsm_CSAI_TPM_AUTH_VALUE_SIZE_32_BYTES = 32UL, /**< Support 32 bytes of authorisation value sizes */
    ecy_hsm_CSAI_TPM_AUTH_VALUE_SIZE_64_BYTES = 64UL, /**< Support 64 bytes of authorisation value sizes */

    /* Reserve for authorisation value sizes */
    ecy_hsm_CSAI_TPM_AUTH_VALUE_SIZE_RESERVED = 0x7FFFFFFFUL
} ecy_hsm_Csai_Tpm_AuthValueSizeT;

/**
 * Structure containing parameters for generation of an authorisation value operation.
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSet_V0Tag
{
    ecy_hsm_Csai_Tpm_AuthValueSizeT authValueSize; /**< [in]  Size of the generated authorisation value. Currently support only 32 and 64 bytes */
    ecy_hsm_Csai_KeyIdT             authKeyId;     /**< [in]  Key slot ID of the authorisation value to be persisted */
} ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for generation of an authorisation value CSAIs with extendable interface.
 * New IDs for future structure shall be added here
 */
typedef enum ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetVersionTag
{
    ecy_hsm_CSAI_GENERATE_AUTH_VALUE_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_GENERATE_AUTH_VALUE_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetVersionT;

/**
 * Union of parameter sets for generation of an authorisation value extendable CSAIs.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetTag
{
    ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetT;

/**
 * Structure of parameter set union and its version for generation of an authorisation value CSAIs.
 */
typedef struct ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetVersionT paramSetVersion;         /**< Version of the selected param set within @c pGenerateAuthValueParam union */
    ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetT*       pGenerateAuthValueParam; /**< Pointer to the extendable parameter set for generation of an authorisation value */
} ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetAndVersionT;

/**
 * Structure containing parameters for session key derivation operation.
 */
/** Data format of the TPM ephemeral public key */
typedef enum ecy_hsm_Csai_Tpm_DataFormatTag
{
    ecy_hsm_CSAI_TPM_ECC_PUBLICKEY_NO_FORMAT = 0x00UL,      /**< Data format: Concatenation of X coordinate data + Y coordinate data */
    ecy_hsm_CSAI_TPM_ECC_PUBLICKEY_FORMAT_V0 = 0x01UL,      /**< Data format: Concatenation of X coordinate size + X coordinate data + Y coordinate size + Y coordinate data.
                                                                 The length of the X coordinate size and the Y coordinate size is 2 bytes.
                                                                 The byte array of X/Y coordinate size is assumed to be in big endian byte order.
                                                                 TPM2B_ECC_POINT defined in TPM-Rev-2.0-Part-1-Architecture */
    ecy_hsm_CSAI_TPM_GENERIC_DATA_NO_FORMAT = 0x02UL,       /**< No data format */
    ecy_hsm_CSAI_TPM_GENERIC_DATA_FORMAT_V0 = 0x03UL,       /**< Data format: Concatenation of data size + data
                                                                 The byte array of data size have the length of 2 bytes and is assumed to be in
                                                                 big endian byte order */
    ecy_hsm_CSAI_TPM_GENERIC_DATA_FORMAT_V1 = 0x04UL,       /**< Data format: Concatenation of data size + data + zero padding
                                                                 The byte array of data size have the length of 2 bytes and is assumed to be in
                                                                 big endian byte order
                                                                 Refer to the description of the interfaces that use this format,
                                                                 for more details on the supported length of zero padding */
    ecy_hsm_CSAI_TPM_DATA_FORMAT_MAX         = 0x7FFFFFFFUL /**< Maximum supported format */
} ecy_hsm_Csai_Tpm_DataFormatT;

/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSet_V0Tag
{
    uint32                                  sessionType;        /**< [in] Determines if salt is used for session key derivation or not (0 to use no salt, 1 to use salt) */
    ecy_hsm_Csai_HashAlgorithmT             sessionAlgorithm;   /**< [in] The hash algorithm for the TPM session, to be used within the KDF operations
                                                                     only SHA2_256 and SHA2_512 are supported */
    ecy_hsm_Csai_Tpm_DataFormatT            tpmPublicKeyFormat; /**< [in] Data format of the TPM ephemeral public key,
                                                                     only TPM_ECC_PUBLICKEY_NO_FORMAT and TPM_ECC_PUBLICKEY_FORMAT_V0 are supported. */
    const uint8*                            pTpmPublicKey;      /**< [in] Pointer to buffer containing the ephemeral public key from TPM, to complete the shared secret calculation */
    uint32                                  tpmPublicKeyLength; /**< [in] Size of pTpmPublicKey buffer, depending on the chosen ECDH scheme from ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair.
                                                                     For TPM_ECC_PUBLICKEY_FORMAT_V0 and ECDH scheme is ECDH_CURVE_P_256, applicable length is 64 bytes
                                                                     For TPM_ECC_PUBLICKEY_FORMAT_V1 and ECDH scheme is ECDH_CURVE_P_256, applicable length is 68 bytes
                                                                     For TPM_ECC_PUBLICKEY_FORMAT_V0 and ECDH scheme is ECDH_CURVE_P_521, applicable length is 132 bytes
                                                                     For TPM_ECC_PUBLICKEY_FORMAT_V1 and ECDH scheme is ECDH_CURVE_P_521, applicable length is 136 bytes */
    ecy_hsm_Csai_KeyHandleT                 authValueHandle;    /**< [in] Handle or KeyID of the authorisation value bound to the TPM session */
    ecy_hsm_Csai_Tpm_AuthValueSizeT         authValueSize;      /**< [in] Size of the default AuthValue (all-zero buffer) in case the session AuthValue is not available
                                                                     (i.e. authValueHandle is ecy_hsm_CSAI_NO_KEY_HANDLE).
                                                                     Only 0 (AuthValue not being used entirely), 32 bytes, and 64 bytes are supported */
    const uint8*                            pNonceTpm;          /**< [in] Pointer to buffer containing the nonce generated by the TPM, may be @c NULL_PTR
                                                                          (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                                  nonceTpmLength;     /**< [in] Size of @c pNonceTpm buffer.
                                                                     The minimum size is 0 (@c pNonceTpm may be @c NULL_PTR and @c nonceTpmLength may be zero).
                                                                     The maximum size that may be requested for @c pNonceTpm is the size of the digest produced by the authorisation session hash.
                                                                     For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                            pNonceCaller;       /**< [in] Pointer to buffer containing the nonce provided by the the caller, may be @c NULL_PTR
                                                                          (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                                  nonceCallerLength;  /**< [in] Size of @c pNonceCaller buffer.
                                                                     The minimum size is 0 (@c pNonceCaller may be @c NULL_PTR and @c nonceCallerLength may be zero).
                                                                     The maximum size that may be requested for @c pNonceCaller is the size of the digest produced by the authorisation session hash.
                                                                     For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    ecy_hsm_Csai_KeyHandleT*                phSessionKey;       /**< [out] Pointer to buffer for session key handle */
} ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for session key derivation CSAIs with extendable interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetVersionTag
{
    ecy_hsm_CSAI_DERIVE_SESSION_KEY_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_DERIVE_SESSION_KEY_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetVersionT;

/**
 * Union of parameter sets for session key derivation extendable CSAIs.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetTag
{
    ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetT;

/**
 * Structure of parameter set union and its version for session key derivation CSAIs.
 */
typedef struct ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetVersionT paramSetVersion;        /**< Version of the selected param set within @c pDeriveSessionKeyParam union */
    ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetT*       pDeriveSessionKeyParam; /**< Pointer to the extendable parameter set for session key derivation */
} ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetAndVersionT;

/**
 * Structure containing parameters for ephemeral key pair generation operation.
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSet_V0Tag
{
    ecy_hsm_Csai_DhAlgorithmT             dhAlgorithm;      /**< [in] The key exchange algorithm to be used
                                                                 only Curve P-256 and P-521 are supported */
    ecy_hsm_Csai_Tpm_DataFormatT          publicKeyFormat;  /**< [in] Data format of the output public key,
                                                                 only TPM_ECC_PUBLICKEY_NO_FORMAT
                                                                 and TPM_ECC_PUBLICKEY_FORMAT_V0 are supported. */
    uint8*                                pPublicKey;       /**< [out] Pointer to the buffer to store generated public key data */
    uint32                                publicKeyLength;  /**< [in] Length of the buffer to store generated public key data */
    uint32*                               pPublicKeyCount;  /**< [out] Actual length of the generated public key */
} ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for ephemeral key pair generation CSAIs with extendable interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetVersionTag
{
    ecy_hsm_CSAI_GENERATE_EPHEMERAL_KEY_PAIR_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_GENERATE_EPHEMERAL_KEY_PAIR_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetVersionT;

/**
 * Union of parameter sets for ephemeral key pair generation extendable CSAIs.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetTag
{
    ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetT;

/**
 * Structure of parameter set union and its version for ephemeral key pair generation CSAIs.
 */
typedef struct ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetVersionT paramSetVersion;                /**< Version of the selected param set within @c pGenerateEphemeralKeyPairParam union */
    ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetT*       pGenerateEphemeralKeyPairParam; /**< Pointer to the extendable parameter set for ephemeral key pair generation */
} ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetAndVersionT;

/**
 * Structure containing parameters for HMAC generation operation
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_GenerateHmac_ParamSet_V0Tag
{
    ecy_hsm_Csai_HashAlgorithmT  sessionAlgorithm;       /**< [in]  The hash algorithm for the TPM session, to be used within the KDF operations
                                                                    only SHA2_256 and SHA2_512 are supported */
    ecy_hsm_Csai_KeyHandleT      hSessionKey;            /**< [in]  Handle to session key */
    const uint8*                 pHash;                  /**< [in]  Pointer to the buffer stored the digest of the communication command/response */
    uint32                       hashSize;               /**< [in]  Size of pHash buffer */
    const uint8*                 pNonceNew;              /**< [in]  Pointer to buffer containing the new nonce of the TPM session, may be @c NULL_PTR
                                                                    (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                       nonceNewSize;           /**< [in]  Size of @c pNonceNew buffer
                                                                    The minimum size is 0 (@c pNonceNew may be @c NULL_PTR and @c nonceNewSize may be zero).
                                                                    The maximum size that may be requested for pNonceNew is the size of the digest produced by the authorisation session hash.
                                                                    For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                 pNonceOld;              /**< [in]  Pointer to buffer containing the previous nonce used in the TPM session, may be @c NULL_PTR
                                                                    (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                       nonceOldSize;           /**< [in]  Size of @c pNonceOld buffer
                                                                    The minimum size is 0 (@c pNonceOld may be @c NULL_PTR and @c nonceOldSize may be zero).
                                                                    The maximum size that may be requested for @c pNonceOld is the size of the digest produced by the authorisation session hash.
                                                                    For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    uint8*                       pHmac;                  /**< [out] Pointer to the buffer to store HMAC authentication tag */
    uint32                       hmacSize;               /**< [in]  Size of @c pHmac buffer */
    uint32*                      pHmacCount;             /**< [out] Actual length of the HMAC tag written to @c pHmac */
    uint8                        sessionAttributes;      /**< [in]  Indicating the attributes associated with a particular use of the session */
} ecy_hsm_Csai_Tpm_GenerateHmac_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for extendable HMAC generation interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetVersionTag
{
    ecy_hsm_CSAI_HMAC_GENERATION_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_HMAC_GENERATION_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetVersionT;

/**
 * Union of parameter sets for extendable HMAC generation interface.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetTag
{
    ecy_hsm_Csai_Tpm_GenerateHmac_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetT;

/**
 * Structure of parameter set union and its version for HMAC generation interface.
 */
typedef struct ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetVersionT paramSetVersion;   /**< Version of the selected param set within @c pGenerateHmac union */
    ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetT*       pGenerateHmac;     /**< Pointer to the extendable parameter set for HMAC generation */
} ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetAndVersionT;

/**
 * Structure containing parameters for TPM duplication operation.
 */
/** Structure for extendable parameter set - version 0: TPM duplication with customized input */
typedef struct ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSet_V0Tag
{
    ecy_hsm_Csai_KeyHandleT      hTpmSharedSecret;   /**< [in]  Handle to a TPM value from HSM keystore, used as shared secret Z
                                                                for deriving the decryption key with SP800-56C KDF scheme */
    const uint8*                 pOtherInfo;         /**< [in]  Pointer to buffer containing other information required by the SP800-56C KDF scheme,
                                                                used for deriving the decryption key */
    uint32                       otherInfoSize;      /**< [in]  Size of @c pOtherInfo buffer */
    const uint8*                 pIv;                /**< [in]  Pointer to buffer containing initialization vector for decryption operation */
    uint32                       ivLength;           /**< [in]  Size of @c pIv buffer */
    const uint8*                 pEncData;           /**< [in]  Pointer to buffer containing encrypted contract private key of ISO-15118 */
    uint32                       encDataLength;      /**< [in]  Size of @c pEncData buffer */
    const uint8*                 pName;              /**< [in]  Name of the duplicated object, required by TPM 2.0 */
    uint32                       nameLength;         /**< [in]  Size of @c pName buffer */
    const uint8*                 pTpmPublicKey;      /**< [in]  Pointer to buffer containing public key from the TPM
                                                                as part of a key exchange with the TPM */
    uint32                       tpmPublicKeyLength; /**< [in]  Size of @c pTpmPublicKey buffer */
    ecy_hsm_Csai_Tpm_DataFormatT tpmPublicKeyFormat; /**< [in]  Data format of the TPM public key, expected to be one of ECC public key format */
    ecy_hsm_Csai_KeyHandleT      hAuthValue;         /**< [in]  Handle or KeyID of the authorisation value,
                                                                as part of the sensitive area of the duplicated object */
    uint8*                       pBlob;              /**< [out] Pointer to buffer to receive the generated duplication object */
    uint32                       blobLength;         /**< [in]  Size of @c pBlob buffer */
    uint32*                      pBlobCount;         /**< [out] Length of the returned duplication object written to @c pBlob */
} ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for extendable TPM duplication interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetVersionTag
{
    ecy_hsm_CSAI_TPM_DUPLICATION_BLOB_GEN_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_TPM_DUPLICATION_BLOB_GEN_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetVersionT;

/**
 * Union of parameter sets for extendable TPM duplication interface.
 * New structures for future parameters shall be added here.
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetTag
{
    ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetT;

/**
 * Structure of parameter set union and its version for TPM duplication interface.
 */
typedef struct ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetVersionT paramSetVersion; /**< Version of the selected param set within @c pParamSet union */
    ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetT*       pParamSet;       /**< Pointer to the extendable parameter set for TPM duplication */
} ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetAndVersionT;

/**
 * Structure containing parameters for authorization value encryption operation.
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSet_V0Tag
{
    ecy_hsm_Csai_HashAlgorithmT     sessionAlgorithm;    /**< [in] The hash algorithm for the TPM session, to be used within the KDF operations
                                                                   only SHA2_256 and SHA2_512 are supported */
    ecy_hsm_Csai_KeyHandleT         hSessionKey;         /**< [in] Handle to session key */
    ecy_hsm_Csai_KeyHandleT         hAuthValue;          /**< [in] Handle or KeyID of the authorisation value bound to the TPM session. */
    ecy_hsm_Csai_Tpm_AuthValueSizeT authValueSize;       /**< [in] Size of the default AuthValue (all-zero buffer) in case the session AuthValue is not available
                                                                   (i.e. authValueHandle is ecy_hsm_CSAI_NO_KEY_HANDLE).
                                                                   Only 0 (AuthValue not being used entirely), 32 bytes, and 64 bytes are supported */
    ecy_hsm_Csai_KeyHandleT         hAuthValueToEncrypt; /**< [in] Handle to the chosen AuthValue to be encrypted */
    ecy_hsm_Csai_Tpm_DataFormatT    authValueDataFormat; /**< [in] Data format of the authValue to be encrypted
                                                                   only GENERIC_DATA_NO_FORMAT and GENERIC_DATA_FORMAT_V1 are supported. */
    ecy_hsm_Csai_KeySizeT           aesKeySize;          /**< [in] AES-CFB key size, only 128 bits and 256 bits are supported */
    const uint8*                    pNonceNew;           /**< [in] Pointer to buffer containing the new nonce of the TPM session,  may be @c NULL_PTR
                                                                   (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceNewSize;        /**< [in] Size of @c nonceNewSize buffer.
                                                                   The minimum size is 0 (@c pNonceNew may be @c NULL_PTR and @c nonceNewSize may be zero).
                                                                   The maximum size that may be requested for nonceNewSize is the size of the digest produced by the authorisation session hash.
                                                                   For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                    pNonceOld;           /**< [in] Pointer to buffer containing the previous nonce used in the TPM session,  may be @c NULL_PTR
                                                                  (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceOldSize;        /**< [in] Size of @c pNonceOld buffer.
                                                                   The minimum size is 0 (@c pNonceOld may be @c NULL_PTR and @c nonceOldSize may be zero).
                                                                   The maximum size that may be requested for pNonceOld is the size of the digest produced by the authorisation session hash.
                                                                   For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    uint8*                          pEncryptedData;      /**< [out] Pointer to the buffer to store encrypted data */
    uint32                          encryptedDataSize;   /**< [in] Size of @c pEncryptedData buffer */
    uint32*                         pEncryptedDataCount; /**< [out] Actual length of the encrypted data */
} ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for authorization value encryption CSAIs with extendable interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetVersionTag
{
    ecy_hsm_CSAI_GET_ENCRYPTED_AUTH_VALUE_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_GET_ENCRYPTED_AUTH_VALUE_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetVersionT;

/**
 * Union of parameter sets for authorization value encryption extendable CSAIs.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetTag
{
    ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetT;

/**
 * Structure of parameter set union and its version for authorization value encryption CSAIs.
 */
typedef struct ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetVersionT paramSetVersion;                /**< Version of the selected param set within @c pGetEncryptedAuthValueParam union */
    ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetT*       pGetEncryptedAuthValueParam;    /**< Pointer to the extendable parameter set for authorization value encryption */
} ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetAndVersionT;

/**
 * Structure containing parameters for command encryption operation.
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_EncryptCommand_ParamSet_V0Tag
{
    ecy_hsm_Csai_HashAlgorithmT     sessionAlgorithm;       /**< [in] The hash algorithm for the TPM session, to be used within the KDF operations
                                                                     only SHA2_256 and SHA2_512 are supported */
    ecy_hsm_Csai_KeyHandleT         hSessionKey;            /**< [in] Handle to session key */
    ecy_hsm_Csai_KeyHandleT         hAuthValue;             /**< [in] Handle or KeyID of the authorisation value bound to the TPM session */
    ecy_hsm_Csai_Tpm_AuthValueSizeT authValueSize;          /**< [in] Size of the default AuthValue (all-zero buffer) in case the session AuthValue is not available
                                                                      (i.e. authValueHandle is ecy_hsm_CSAI_NO_KEY_HANDLE).
                                                                      Only 0 (AuthValue not being used entirely), 32 bytes, and 64 bytes are supported */
    ecy_hsm_Csai_KeySizeT           aesKeySize;             /**< [in] AES-CFB key size, only 128 bits and 256 bits are supported */
    const uint8*                    pNonceNew;              /**< [in] Pointer to buffer containing the new nonce of the TPM session, may be @c NULL_PTR
                                                                      (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceNewSize;           /**< [in] Size of @c nonceNewSize buffer.
                                                                      The minimum size is 0 (pNonceNew may be @c NULL_PTR and @c nonceNewSize may be zero).
                                                                      The maximum size that may be requested for @c nonceNewSize is the size of the digest produced by the authorisation session hash.
                                                                      For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                    pNonceOld;              /**< [in] Pointer to buffer containing the previous nonce used in the TPM session, may be @c NULL_PTR
                                                                      (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceOldSize;           /**< [in] [in] Size of @c pNonceOld buffer.
                                                                      The minimum size is 0 (@c pNonceOld may be @c NULL_PTR and @c nonceOldSize may be zero).
                                                                      The maximum size that may be requested for @c pNonceOld is the size of the digest produced by the authorisation session hash.
                                                                      For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                    pInputData;             /**< [in] Pointer to the buffer stored the plain text to be encrypted, this pointer must not be @c NULL_PTR */
    uint32                          inputDataLength;        /**< [in] Size of @c pInputData buffer */
    uint8*                          pEncryptedData;         /**< [out] Pointer to the buffer to store encrypted data, this pointer must not be @c NULL_PTR */
    uint32                          encryptedDataSize;      /**< [in] Size of @c pEncryptedData buffer, the length of @c encryptedDataSize is greater and equal to @c inputDataLength */
    uint32*                         pEncryptedDataCount;    /**< [out] Actual length of the encrypted data */
} ecy_hsm_Csai_Tpm_EncryptCommand_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for extendable command encryption interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetVersionTag
{
    ecy_hsm_CSAI_ENCRYPT_COMMAND_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_ENCRYPT_COMMAND_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetVersionT;

/**
 * Union of parameter sets for extendable command encryption interface.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetTag
{
    ecy_hsm_Csai_Tpm_EncryptCommand_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetT;

/**
 * Structure of parameter set union and its version for command encryption interface.
 */
typedef struct ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetVersionT paramSetVersion;    /**< Version of the selected param set within @c pEncryptCommand union */
    ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetT*       pEncryptCommand;    /**< Pointer to the extendable parameter set for command encryption */
} ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetAndVersionT;

/**
 * Structure of parameter set union and its version for release a selected TPM value interface.
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_Tpm_ReleaseTpmValue_ParamSetAndVersionT;

/**
 * Structure of parameter set union and its version for load a selected TPM value interface.
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_Tpm_LoadTpmValue_ParamSetAndVersionT;

/**
 * Structure of parameter set union and its version for delete the persisted TPM value interface.
 */
/** Placeholder definition for expansion in the future */
typedef uint32 ecy_hsm_Csai_Tpm_DeleteTpmValue_ParamSetAndVersionT;

/**
 * Structure containing parameters for response decryption operation
 */
/** Structure for extendable parameter set - version 0 */
typedef struct ecy_hsm_Csai_Tpm_DecryptResponse_ParamSet_V0Tag
{
    ecy_hsm_Csai_HashAlgorithmT     sessionAlgorithm; /**< [in] The hash algorithm for the TPM session, to be used within the KDF operations
                                                                only SHA2_256 and SHA2_512 are supported */
    ecy_hsm_Csai_KeyHandleT         hSessionKey;      /**< [in] Handle to session key */
    ecy_hsm_Csai_KeyHandleT         hAuthValue;       /**< [in] Handle or KeyID of the authorisation value bound to the TPM session */
    ecy_hsm_Csai_Tpm_AuthValueSizeT authValueSize;    /**< [in] Size of the default AuthValue (all-zero buffer) in case the session AuthValue is not available
                                                                (i.e. authValueHandle is ecy_hsm_CSAI_NO_KEY_HANDLE).
                                                                Only 0 (AuthValue not being used entirely), 32 bytes, and 64 bytes are supported */
    ecy_hsm_Csai_KeySizeT           aesKeySize;       /**< [in] AES-CFB key size, only 128 bits and 256 bits are supported */
    const uint8*                    pNonceNew;        /**< [in] Pointer to buffer containing the new nonce of the TPM session, may be @c NULL_PTR
                                                               (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceNewSize;     /**< [in] Size of @c nonceNewSize buffer.
                                                                The minimum size is 0 (@c pNonceNew may be @c NULL_PTR and @c nonceNewSize may be zero).
                                                                The maximum size that may be requested for @c nonceNewSize is the size of the digest produced by the authorisation session hash.
                                                                For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                    pNonceOld;        /**< [in] Pointer to buffer containing the previous nonce used in the TPM session, may be @c NULL_PTR
                                                                (the primary use of a nonce in a session is to prevent an authorization from being reused). */
    uint32                          nonceOldSize;     /**< [in] Size of pNonceOld buffer.
                                                                The minimum size is 0 (@c pNonceOld may be @c NULL_PTR and @c nonceOldSize may be zero).
                                                                The maximum size that may be requested for @c pNonceOld is the size of the digest produced by the authorisation session hash.
                                                                For SHA2_256 the maximum size is 32 bytes and for SHA2_512 it is 64 bytes. */
    const uint8*                    pCipherText;      /**< [in] Pointer to the buffer stored the cipher text to be decrypted, this pointer must not be @c NULL_PTR */
    uint32                          cipherTextSize;   /**< [in] Size of @c pCipherText buffer
                                                                The minimum size is greater than 0.
                                                                The maximum size is less than or equal to 144 bytes (@c MAX_SIZE_ECCKEYS) when ECDH_SECP521 bit keys are enabled.
                                                                The maximum size is less than or equal to 80 bytes when ECDH_SECP256 bit keys are enabled. */
    ecy_hsm_Csai_Tpm_DataFormatT    decRespFormat;    /**< [in] The format of the decrypted response, currently support
                                                                - @ref ecy_hsm_CSAI_TPM_ECC_PUBLICKEY_NO_FORMAT
                                                                - @ref ecy_hsm_CSAI_TPM_ECC_PUBLICKEY_FORMAT_V0 */
    ecy_hsm_Csai_KeyHandleT*        phResponse;       /**< [out] Pointer to buffer stored the handle to the decrypted data, this pointer must not be @c NULL_PTR */
} ecy_hsm_Csai_Tpm_DecryptResponse_ParamSet_V0T;

/**
 * Enum for versioning the parameter set for extendable response decryption interface.
 * New IDs for future structure shall be added here.
 */
typedef enum ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetVersionTag
{
    ecy_hsm_CSAI_DECRYPT_RESPONSE_PARAMSET_V0  = 0U,          /**< Corresponds to Version 0 of the extendable data struct */
    ecy_hsm_CSAI_DECRYPT_RESPONSE_PARAMSET_MAX = 0x7FFFFFFFUL /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetVersionT;

/**
 * Union of parameter sets for extendable response decryption interface.
 */
/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetTag
{
    ecy_hsm_Csai_Tpm_DecryptResponse_ParamSet_V0T paramV0; /**< Data structure of Version 0 */
} ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetT;

/**
 * Structure of parameter set union and its version for response decryption interface.
 */
typedef struct ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetAndVersionTag
{
    ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetVersionT paramSetVersion;     /**< Version of the selected param set within @c pDecryptResponse union */
    ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetT*       pDecryptResponse;    /**< Pointer to the extendable parameter set for response decryption */
} ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetAndVersionT;

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
 * [$DD 2796]
 * @brief Generation of an authorisation value, and persist it with a specified key ID.
 * [$Satisfies $SW_ARCH 1C0F0F45][$Satisfies $SW_ARCH 91ECA20E]
 *
 * @details Start the generation of an authorisation value in the HSM of the given size of the generated
 *          authorisation value and with the given key slot ID. The authorisation value is generated from
 *          true random numbers using the platform's TRNG hardware peripheral.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished generating the authorisation value.
 * - The authorisation value SHALL be restricted in usage via the TPM CSAIs only, to
 *   ensure TPM-communication secrets cannot be leaked out or replicated.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. Provided an authorisation value is stored in
 *                                                      the session context inside the HSM
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            In general, pointers should be aligned to four-byte boundaries
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             The EEPROM emulation returned an error
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_FULL                  The EEPROM emulation is full
 * - @ref ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY             The key already associated with the specified keyId is read-only
 * - @ref ecy_hsm_CSAI_ERR_TRNG                         True Random Number Generator reports an error
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_KEY_TOO_BIG                  The supplied key is too big to fit in the keystore
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION       There has been an attempt to use a key in violation of its property flags
 * - @ref ecy_hsm_CSAI_ERR_NO_SPACE_SYM_RAM_KEY         There are no spare symmetric RAM key slots left
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_GenerateAuthValue(ecy_hsm_Csai_SessionHandleT                             hSession,
                                                     ecy_hsm_Csai_JobPriorityT                               priority,
                                                     ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetAndVersionT* pParams,
                                                     ecy_hsm_Csai_JobHandleT*                                phJob);

/**
 * [$DD 2816]
 * Generation of ephemeral key pair.
 * [$Satisfies $SW_ARCH 2206D55D] [$Satisfies $SW_ARCH 8D351333]
 *
 * @details Generation of ephemeral key pair, to be used for subsequent TPM interfaces (e.g. Csai_Tpm_DeriveSessionKey).
 *          If @ref ecy_hsm_Csai_Tpm_DeriveSessionKey is to be used with V0 version of the parameter set,
 *          then @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair shall be called prior so that the stored key pair can be obtained
 *          for TPM session key derivation.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished generating the ephemeral key pair.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. Provided a public key with specified format.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             Is returned, if the publicKey buffer is too small
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The curveId is not supported
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     An error has been returned by CycurLib
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair(ecy_hsm_Csai_SessionHandleT                                    hSession,
                                                            ecy_hsm_Csai_JobPriorityT                                      priority,
                                                            ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetAndVersionT* pParams,
                                                            ecy_hsm_Csai_JobHandleT*                                       phJob);

/**
 * [$DD 2841]
 * @brief Encrypt a TPM command using AES-CFB, then return the encrypted data.
 * [$Satisfies $SW_ARCH 8DD3C872] [$Satisfies $SW_ARCH D1DF086A]
 *
 * @details Encrypt a TPM command using AES-CFB with corresponding session key
 *          and the session-associated authorisation value.
 *          Encrypted data and length are then return as outputs.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the encryption of the TPM command.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded.Encrypted data was returned.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the
 *                                                  CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED           The key is not loaded
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE           The key type is not correct
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The supplied key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL         The destination buffer is not big enough (remember that space for padding may be needed)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT        A pointer is not aligned to a four byte boundary
 * - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED The supplied key length is not supported
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET   One given parameter of the call is wrong, invalid or out of range
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            Version or the hash algorithm of the selected param set is not supported
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_EncryptCommand(ecy_hsm_Csai_SessionHandleT                                 hSession,
                                                   ecy_hsm_Csai_JobPriorityT                                  priority,
                                                   ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetAndVersionT*       pParams,
                                                   ecy_hsm_Csai_JobHandleT*                                   phJob);

/**
 * [$DD 2802]
 * @brief Derive a session key for a TPM communication session,
 *        from the associated authorisation value and/or the ephemeral key pair from @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair.
 * [$Satisfies $SW_ARCH B8E73A08] [$Satisfies $SW_ARCH D5AB0BE2]
 *
 * @details Derived keys are stored in the session context in HSM RAM, in an available
 *          session key slot. A handle to the generated key is returned via @c phSessionKey.
 *          Currently, the supported derived session key size depends on @c sessionAlgorithm
 *          (E.g 256 bits for SHA2_256).
 *          If the session-associated AuthValue is not available (authValueHandle = ecy_hsm_CSAI_NO_KEY_HANDLE),
 *          the interface shall accept the provided @c authValueSize to use the default value (00-padded buffer) instead.
 *          If salt is not required, the parent key of the session key is authValue.
 *          If salt is required, the parent key of the session key is authValue || salt.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished generating the key.
 * - When salt is required, the caller must call @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair before this interface,
 *   without any other TPM interface in between.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]     hSession  Handle to an open HSM session
 * @param[in]     priority  Scheduling priority of the operation on the HSM
 * @param[in,out] pParams   Pointer to derive a session key operation parameter structure
 * @param[out]    phJob     Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded. Provided key pair is stored in
 *                                              the session context inside the HSM
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE     The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY                Another job is still pending completion in this session
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED                 The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                      The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                       A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                       Version or the hash algorithm of the selected param set is not supported
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED                      The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID                      The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_TPM_EPHEMERAL_KEYPAIR_NOT_AVAILABLE The ephemeral key pair from @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair
 *                                                             is not available in TPM context
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_DeriveSessionKey(ecy_hsm_Csai_SessionHandleT                            hSession,
                                                    ecy_hsm_Csai_JobPriorityT                              priority,
                                                    ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetAndVersionT* pParams,
                                                    ecy_hsm_Csai_JobHandleT*                               phJob);

/**
 * [$DD 2824]
 * @brief Generate an HMAC authentication tag for a TPM command/response
          within a TPM session, by using the corresponding session key.
 *
 * [$Satisfies $SW_ARCH 4CE6A8AE] [$Satisfies $SW_ARCH A1B00D97]
 *
 * @details Generate an HMAC authentication tag for a TPM command/response
            within a TPM session, by using the corresponding session key.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the generation of the HMAC authentication tag.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided the authentication tag.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the
 *                                                  CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED           The key is not loaded
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE           The key type is not correct
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The supplied key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL         The destination buffer is not big enough
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT        A pointer is not aligned to a four byte boundary
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET   One given parameter of the call is wrong, invalid or out of range
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            Version or the hash algorithm of the selected param set is not supported
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION   Operation not allowed for the given key handles/IDs slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_GenerateHmac(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                ecy_hsm_Csai_JobPriorityT                          priority,
                                                ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetAndVersionT* pParams,
                                                ecy_hsm_Csai_JobHandleT*                           phJob);

/**
 * [$DD 2890]
 * [$Satisfies $SW_ARCH 657F29BC] [$Satisfies $SW_ARCH 9475DA4C]
 * @brief Generate an object undergoing the TPM duplication process.
 *
 * @details This function is responsible for generating a TPM duplicated object and returning it in a buffer to the Host.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the generation of the TPM duplicated object tag.
 * - The caller must call @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair before this interface,
 *   without any other TPM interface in between.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided the authentication tag.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION                   There has been an attempt to access HSM ram address via the
 *                                                             CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED                 The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                      The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                       The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED                      The key is not loaded
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE                      The key type is not correct
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE                      The supplied key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL                    The destination buffer is not big enough
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                       Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT                   A pointer is not aligned to a four byte boundary
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET              One given parameter of the call is wrong, invalid or out of range
 * - @ref ecy_hsm_CSAI_ERR_TPM_EPHEMERAL_KEYPAIR_NOT_AVAILABLE The ephemeral key pair from @ref ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair
 *                                                             is not available in TPM context
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_GenerateDuplicationBlob(ecy_hsm_Csai_SessionHandleT                              hSession,
                                         ecy_hsm_Csai_JobPriorityT                                priority,
                                         ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetAndVersionT* pParams,
                                         ecy_hsm_Csai_JobHandleT*                                 phJob);

/**
 * [$DD 2830]
 * @brief Release a selected TPM value from the keystore, based on the input handle.
 *
 * [$Satisfies $SW_ARCH E18B8A92]
 *
 *
 * @details Release a selected TPM value (e.g. authorisation value, session key, etc.)
 *          from the keystore, based on the input handle.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the releasing a selected TPM value.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in]       hKeyToRelease       Handle to the TPM data that shall be released
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 *                                      (This argument is currently unused and is reserved as a place holder for future extension)
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided the authentication tag.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the
 *                                                  CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_ReleaseTpmValue(ecy_hsm_Csai_SessionHandleT                           hSession,
                                                   ecy_hsm_Csai_JobPriorityT                             priority,
                                                   ecy_hsm_Csai_KeyHandleT                               hKeyToRelease,
                                                   ecy_hsm_Csai_Tpm_ReleaseTpmValue_ParamSetAndVersionT* pParams,
                                                   ecy_hsm_Csai_JobHandleT*                              phJob);

/**
 * [$DD 2843]
 * @brief Load a selected TPM value, based on the input key ID.
 *
 * [$Satisfies $SW_ARCH 3C2BE925]
 *
 * @details Load a selected TPM value (e.g. session key, authorisation
 * value) from the non-volatile memory to HSM RAM, based on the input key ID.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the loading a selected TPM value.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in]       persistedKeyId      Key ID of the persisted TPM value
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 *                                      (This argument is currently unused and is reserved as a place holder for future extension)
 * @param[out]      phTpmValue          Pointer to the handle TPM value
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided the authentication tag.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID           The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND     The requested TPM object is not available for loading
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_LoadTpmValue(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                ecy_hsm_Csai_JobPriorityT                          priority,
                                                ecy_hsm_Csai_KeyIdT                                persistedKeyId,
                                                ecy_hsm_Csai_Tpm_LoadTpmValue_ParamSetAndVersionT* pParams,
                                                ecy_hsm_Csai_KeyHandleT*                           phTpmValue,
                                                ecy_hsm_Csai_JobHandleT*                           phJob);

/**
 * [$DD 2831]
 * @brief Delete the persisted TPM value from Dflash with the given key ID.
 *
 * [$Satisfies $SW_ARCH 6D2C5B9E]
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the deleting the persisted TPM value.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in]       persistedKeyId      Key ID of the persisted TPM value
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 *                                      (This argument is currently unused and is reserved as a place holder for future extension)
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided the authentication tag.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID           The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_DeleteTpmValue(ecy_hsm_Csai_SessionHandleT                          hSession,
                                                  ecy_hsm_Csai_JobPriorityT                            priority,
                                                  ecy_hsm_Csai_KeyIdT                                  persistedKeyId,
                                                  ecy_hsm_Csai_Tpm_DeleteTpmValue_ParamSetAndVersionT* pParams,
                                                  ecy_hsm_Csai_JobHandleT*                             phJob);

/**
 * [$DD 2819]
 * @brief Encrypt a chosen authorization value with specified format using AES-CFB encryption,
 *        return the encrypted data.
 *
 * [$Satisfies $SW_ARCH DE4C2C9C] [$Satisfies $SW_ARCH 13190247]
 *
 * @details Encrypt a chosen authorization value using AES-CFB encryption with corresponding session key
 *          and/or the session-associated authorisation value.
 *          If @ref ecy_hsm_Csai_Tpm_GetEncryptedAuthValue is used with V0 version of the parameter set,
 *          then the format @ref ecy_hsm_CSAI_TPM_GENERIC_DATA_FORMAT_V1 for encrypted data shall have the
 *          fixed zero padding length of 2 bytes.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished encrypting the authorization value.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. Provided encrypted data with specified format.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the
 *                                                  CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED           The key is not loaded
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE           The key type is not correct
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The supplied key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL         The destination buffer is not big enough (remember that space for padding may be needed)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT        A pointer is not aligned to a four byte boundary
 * - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED The supplied key length is not supported
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET   One given parameter of the call is wrong, invalid or out of range
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 *                                                  Version or the hash algorithm of the selected param set is not supported
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION   Operation not allowed for the given key handles/IDs slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_GetEncryptedAuthValue(ecy_hsm_Csai_SessionHandleT                                 hSession,
                                                         ecy_hsm_Csai_JobPriorityT                                   priority,
                                                         ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetAndVersionT* pParams,
                                                         ecy_hsm_Csai_JobHandleT*                                    phJob);

/**
 * [$DD 2822]
 * @brief Decrypt a TPM response using AES-CFB, then return the handle to the decrypted data.
 *
 * [$Satisfies $SW_ARCH 3B448004] [$Satisfies $SW_ARCH 775F46C1]
 *
 * @details Decrypt a cipher-text data using AES-CFB with corresponding session key
 *          and the session-associated authorisation value. Inject the decrypted data
 *          and then return the handle to the data in HSM RAM.
 *
 * @note
 * - The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle to
 *   query when the HSM has finished the decryption of the response.
 *
 * @internal
 * This function forwards the provided parameters via Applet to the HSM, where the parameters will be verified and forwards the Applets status codes to the user.
 * Further more the fuction checks if a valid phJob pointer is provided and if so stores the hSession into phJob.
 * In case user input phJob is NULL_PTR, user can not monitor this job is finished or not.
 * @endinternal
 *
 * @param[in]       hSession            Handle to an open HSM session
 * @param[in]       priority            Scheduling priority of the operation on the HSM
 * @param[in,out]   pParams             Pointer to the extendable parameter sets and their corresponding version
 * @param[out]      phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                    The call succeeded. The handle to decrypted was returned.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE         The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_PENDING                 The operation is still in progress.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                    Another job is still pending completion in this session.
 *                                                  Either finish the previous job or cancel the running job
 *                                                  using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the
 *                                                  CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED      The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED           The key is not loaded
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE           The key type is not correct
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The supplied key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given functionality is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2         Hardware failure or timeout
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL         The destination buffer is not big enough (remember that space for padding may be needed)
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Input parameter not allowed
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT        A pointer is not aligned to a four byte boundary
 * - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED The supplied key length is not supported
 * - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET   One given parameter of the call is wrong, invalid or out of range
 * - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION   Operation not allowed for the given key handles/IDs (not a TPM key/value)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_DecryptResponse(ecy_hsm_Csai_SessionHandleT                           hSession,
                                 ecy_hsm_Csai_JobPriorityT                             priority,
                                 ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetAndVersionT* pParams,
                                 ecy_hsm_Csai_JobHandleT*                              phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* ECY_HSM_CSAI_TPM_H */
