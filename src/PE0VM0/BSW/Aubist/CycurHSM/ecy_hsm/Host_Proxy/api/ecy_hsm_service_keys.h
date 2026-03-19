/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Cryptographic key management.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * key management functions for CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_KEYS_H
#define ECY_HSM_SERVICE_KEYS_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_keys.h"

/**
 * @addtogroup GROUP_CSAI_KEY_MANAGEMENT
 * @{
 */

/** Structure for the data passed to a Derive key operation */
typedef struct ecy_hsm_DeriveKeyParamTag {
    ecy_hsm_Csai_KeyDerivationFunctionT kdf;        /**< Key derivation function                                */
    ecy_hsm_Csai_KeyHandleT hParentKey;             /**< Handle to a parent key to derive from. May be set to
                                                         @ref ecy_hsm_CSAI_NO_KEY_HANDLE if the specified
                                                         @c kdf does not use a parent key */
    ecy_hsm_Csai_PinRefT* pPasswd;                  /**< Password to derive from. May be @c NULL_PTR if the
                                                         specified @c kdf  does not use a password as an
                                                         input parameter.                */
    ecy_hsm_Csai_PinRefT* pSalt;                    /**< Caller provided salt. See function notes.              */
    uint32 iterationCount;                          /**< Iteration count for the specified @c kdf.
                                                         May be ignored if the specified @c kdf computes the
                                                         required iteration count from other parameters, e.g, @c keySize. */
    ecy_hsm_Csai_KeySizeT keySize;                  /**< Desired size of the key to generate.                   */
    ecy_hsm_Csai_KeyHandleT* phDerivedKeys;         /**< Receives the handle to the generated keys.             */
    uint8* pKeyCount;                               /**< How many keys to derive with DeriveMultipleKeys        */
} ecy_hsm_DeriveKeyParamT;

/** Structure for the data passed to a Derive Key Ext operation */
typedef struct ecy_hsm_DeriveKeyExtParamTag {
    ecy_hsm_Csai_KeyDerivationFunctionT kdf;        /**< Key derivation function                                */
    ecy_hsm_Csai_KeyHandleT hParentKey;             /**< Handle to a parent key to derive from.                 */
    void* pKdfParam;                                /**< KDF-specific input parameters.                         */
    uint32 kdfParamSize;                            /**< Size of kdfParam structure in bytes                    */
    void* pKeyAttributes;                           /**< KDF-specific output parameters.                        */
    uint32 keyAttributesSize;                       /**< Size of keyAttribute structure in bytes                */
} ecy_hsm_DeriveKeyExtParamT;

/** Structure for the data passed to an Inject key operation     */
typedef struct ecy_hsm_InjectKeyParamTag {
    ecy_hsm_Csai_KeyRefT * pKeyData;                /**< Key data to inject to a RAM key slot                   */
    uint32 keyProperties;                           /**< Property flags of the new key                          */
    ecy_hsm_Csai_KeyHandleT * phKey;                /**< Receives the handle to the key                         */
} ecy_hsm_InjectKeyParamT;

/** Structure for the data passed to Write Key To Key Slot operation */
typedef struct ecy_hsm_WriteKeyToSlotParamTag {
    ecy_hsm_Csai_KeyHandleT hKey;                   /**< Handle of the key to store in the session              */
    ecy_hsm_Csai_KeyIdT keyId;                      /**< Numerical ID of the key slot in the non-volatile       */
} ecy_hsm_WriteKeyToSlotParamT;

/** Structure for the data passed to a Load key operation     */
typedef struct ecy_hsm_LoadKeyParamTag {
    ecy_hsm_Csai_KeyIdT keySlotId;                  /**< ID of the NVM key slot from which to load the key      */
    ecy_hsm_Csai_KeyTypeT expectedKeyType;          /**< Expected key type, error if doesn't match keySlotId    */
    ecy_hsm_Csai_KeyHandleT* phKey;                 /**< Receives the handle to the key                         */
} ecy_hsm_LoadKeyParamT;

/** Structure for the data passed to a Release key operation     */
typedef struct ecy_hsm_ReleaseKeyParamTag {
    ecy_hsm_Csai_KeyHandleT hKey;                   /**< Handle of the key to store in the session              */
} ecy_hsm_ReleaseKeyParamT;

/** Structure for the data passed to a Release key force operation     */
typedef struct ecy_hsm_ReleaseKeyForceParamTag {
    ecy_hsm_Csai_KeyIdT keyId;                      /**< key ID or handle of the key to remove from HSM RAM     */
} ecy_hsm_ReleaseKeyForceParamT;

/** Structure for the data passed to a read the public key operation     */
typedef struct ecy_hsm_ReadPublicKeyParamTag {
    ecy_hsm_Csai_KeyHandleT hKey;                   /**< Handle to a RSA public key to be read    */
    ecy_hsm_Csai_KeyRefT * key;                     /**< Provides space to store the exported public key */
} ecy_hsm_ReadPublicKeyParamT;

/** Structure for the data passed to a Generate Key operation   */
typedef struct ecy_hsm_GenerateKeyParamTag
{
    ecy_hsm_Csai_KeyTypeT keyType;       /**< Type of the key (RSA, ECC)                             */
    ecy_hsm_Csai_KeySizeT keySize;       /**< Size of the key to generate in bits                    */
    uint32                keyProperties; /**< A combination of key properties flags defined
                                              by @ref ecy_hsm_Csai_KeyPropertyFlagsT                 */
    ecy_hsm_Csai_KeyHandleT* phKey;      /**< Receives the handle to the generated key               */
} ecy_hsm_GenerateKeyParamT;

/** Structure for the data passed to a GetStorageLocation operation     */
typedef struct ecy_hsm_GetStorageLocationParamTag
{
    ecy_hsm_Csai_KeyIdT            keyId;            /**< Key ID of unknown storage location                     */
    ecy_hsm_Csai_StorageLocationT* pStorageLocation; /**< Storage location of the given key ID                   */
} ecy_hsm_GetStorageLocationParamT;

/** Structure for the data passed  */
/* PRQA S 0750 2 */ /* <Justification: definition of union is appropriate here */
typedef union ecy_hsm_KeysParamTag
{
    ecy_hsm_DeriveKeyParamT                 DeriveKeyParam;             /**< Parameters for key derivation                   */
    ecy_hsm_InjectKeyParamT                 InjectKeyParam;             /**< Parameters for key injection                    */
    ecy_hsm_WriteKeyToSlotParamT            WriteKeyToSlotParam;        /**< Parameters for key writing                      */
    ecy_hsm_LoadKeyParamT                   LoadKeyParam;               /**< Parameters for loading keys                     */
    ecy_hsm_ReleaseKeyParamT                ReleaseKeyParam;            /**< Parameters for releasing keys                   */
    ecy_hsm_ReleaseKeyForceParamT           ReleaseKeyForceParam;       /**< Parameters for enforcing key releases           */
    ecy_hsm_ReadPublicKeyParamT             ReadPublicKeyParam;         /**< Parameters for reading public keys              */
    ecy_hsm_GenerateKeyParamT               GenerateKeyParam;           /**< Parameters for key generation                   */
    ecy_hsm_DeriveKeyExtParamT              DeriveKeyExtParam;          /**< Parameters for extended key derivation          */
    ecy_hsm_GetStorageLocationParamT        GetStorageLocationParam;    /**< Parameters for get storage location             */
    ecy_hsm_DeriveMultipleKeysExtParamT     DeriveMultiKeysExtParam;    /**< Parameters for Multiple extended Key derivation */
} ecy_hsm_KeysParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_DeriveKeyParamTag
 */
#define HSM_DeriveKeyParamTag ecy_hsm_DeriveKeyParamTag
/**
 * @deprecated by ecy_hsm_DeriveKeyParamT
 */
#define HSM_DeriveKeyParamT ecy_hsm_DeriveKeyParamT
/**
 * @deprecated by ecy_hsm_DeriveKeyExtParamTag
 */
#define HSM_DeriveKeyExtParamTag ecy_hsm_DeriveKeyExtParamTag
/**
 * @deprecated by ecy_hsm_DeriveKeyExtParamT
 */
#define HSM_DeriveKeyExtParamT ecy_hsm_DeriveKeyExtParamT
/**
 * @deprecated by ecy_hsm_InjectKeyParamTag
 */
#define HSM_InjectKeyParamTag ecy_hsm_InjectKeyParamTag
/**
 * @deprecated by ecy_hsm_InjectKeyParamT
 */
#define HSM_InjectKeyParamT ecy_hsm_InjectKeyParamT
/**
 * @deprecated by ecy_hsm_WriteKeyToSlotParamTag
 */
#define HSM_WriteKeyToSlotParamTag ecy_hsm_WriteKeyToSlotParamTag
/**
 * @deprecated by ecy_hsm_WriteKeyToSlotParamT
 */
#define HSM_WriteKeyToSlotParamT ecy_hsm_WriteKeyToSlotParamT
/**
 * @deprecated by ecy_hsm_LoadKeyParamTag
 */
#define HSM_LoadKeyParamTag ecy_hsm_LoadKeyParamTag
/**
 * @deprecated by ecy_hsm_LoadKeyParamT
 */
#define HSM_LoadKeyParamT ecy_hsm_LoadKeyParamT
/**
 * @deprecated by ecy_hsm_ReleaseKeyParamTag
 */
#define HSM_ReleaseKeyParamTag ecy_hsm_ReleaseKeyParamTag
/**
 * @deprecated by ecy_hsm_ReleaseKeyParamT
 */
#define HSM_ReleaseKeyParamT ecy_hsm_ReleaseKeyParamT
/**
 * @deprecated by ecy_hsm_ReleaseKeyForceParamTag
 */
#define HSM_ReleaseKeyForceParamTag ecy_hsm_ReleaseKeyForceParamTag
/**
 * @deprecated by ecy_hsm_ReleaseKeyForceParamT
 */
#define HSM_ReleaseKeyForceParamT ecy_hsm_ReleaseKeyForceParamT
/**
 * @deprecated by ecy_hsm_ReadPublicKeyParamTag
 */
#define HSM_ReadPublicKeyParamTag ecy_hsm_ReadPublicKeyParamTag
/**
 * @deprecated by ecy_hsm_ReadPublicKeyParamT
 */
#define HSM_ReadPublicKeyParamT ecy_hsm_ReadPublicKeyParamT
/**
 * @deprecated by ecy_hsm_GenerateKeyParamTag
 */
#define HSM_GenerateKeyParamTag ecy_hsm_GenerateKeyParamTag
/**
 * @deprecated by ecy_hsm_GenerateKeyParamT
 */
#define HSM_GenerateKeyParamT ecy_hsm_GenerateKeyParamT
/**
 * @deprecated by ecy_hsm_GetStorageLocationParamTag
 */
#define HSM_GetStorageLocationParamTag ecy_hsm_GetStorageLocationParamTag
/**
 * @deprecated by ecy_hsm_GetStorageLocationParamT
 */
#define HSM_GetStorageLocationParamT ecy_hsm_GetStorageLocationParamT
/**
 * @deprecated by ecy_hsm_KeysParamT
 */
#define HSM_KeysParamT ecy_hsm_KeysParamT
/**
 * @deprecated by ecy_hsm_KeysParamTag
 */
#define HSM_KeysParamTag ecy_hsm_KeysParamTag
/**
 * @}
 */

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* ECY_HSM_SERVICE_KEYS_H  */
