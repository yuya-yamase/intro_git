/**
 * \file Crypto_82_Hsm_KeyManagement.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for implementation of Key Management module
 * \details
*/

#ifndef CRYPTO_82_HSM_KEYMANAGEMENT_H
#define CRYPTO_82_HSM_KEYMANAGEMENT_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Csm.h"
#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif
#include "CryIf.h"
#include "Crypto_82_Hsm_Porting.h"
#include "Crypto_82_Hsm_Cfg.h"

#include "ecy_hsm_csai_session.h"
#include "ecy_hsm_csai_job.h"
#include "ecy_hsm_csai_keys.h"

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

#define CRYPTO_KEYDERIVE_TARGETKEYELEMENT_ID   (1u)

#define SHE_M1_M2_M3_SIZE       (M1_SIZE + M2_SIZE + M3_SIZE)
#define SHE_M4_M5_SIZE          (M4_SIZE + M5_SIZE)

#define SHE_RAM_KEY_SIZE        (16u)


/**
 * \def isSheRamKey(cryptoKeyId)
 * \brief Returns TRUE if cryptoKeyId is configured with Hsm Key Id as SHE RAM key ID, otherwise it shall returns FALSE
*/
#define isSheRamKey(cryptoKeyId) (Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId == (ecy_hsm_Csai_KeyIdT)SHE_RAM_KEY)

/* Key derive key element necessary for CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP80056C, CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP800108 and CRYPTO_ALGOFAM_CUSTOM_KDF_ANSIX963*/
#define CRYPTO_KE_KEYDERIVE_CUSTOM_PARENTKEY                             (30u)

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief Type used for SHE key update in the HSM session context.
 */
typedef struct sCrypto_82_Hsm_SHE_KeyOperation
{
    VAR(boolean, CRYPTO_82_HSM_VAR)   loadKeyOperationRequired;  /** If true, the SHE key must be updated in the HSM session context */
#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )    
    VAR(boolean, CRYPTO_82_HSM_VAR)   serializeKeyFailed;  /** If true, the SHE key must be updated in the HSM session context */
#endif    
    VAR(uint32,  CRYPTO_82_HSM_VAR)   keyElement;                /** Crypto Key Element Id                                           */
    VAR(uint32,  CRYPTO_82_HSM_VAR)   cryptoKeyId;               /** Crypto Key Id                                                   */
} Crypto_82_Hsm_SHE_KeyOperation;


/**
 * \brief Type used for SHE key update in the HSM session context.
 */
typedef enum eCrypto_82_Hsm_KeyExchangeCalcSecretOperation
{
    CRYPTO_KEY_EXCHANGE_DHINIT_REQUIRED = 0x01,
    CRYPTO_KEY_EXCHANGE_DHCOMPUTE_EXT_REQUIRED = 0x02,
    CRYPTO_KEY_EXCHANGE_SET_VALIDITY_REQUIRED = 0x03
} Crypto_82_Hsm_KeyExchangeCalcSecretOperation;

/**
 * \brief Type used for KeySetValid process.
 */
typedef enum eCrypto_82_Hsm_KeySetValidOperation
{
    CRYPTO_KEY_SET_VALID_NO_OPERATION = 0x00,
    CRYPTO_KEY_SET_VALID_INJECT = 0x01,
    CRYPTO_KEY_SET_VALID_WRITE_TO_NVM = 0x02
} Crypto_82_Hsm_KeySetValidOperation;

/**
 * \brief SHE data type which contains SHE specific buffers.
 */
typedef struct sCrypto_82_Hsm_SHE_DataType
{
    VAR(uint8, CRYPTO_82_HSM_VAR) sheM4[M4_SIZE];   /** SHE reply         */
    VAR(uint8, CRYPTO_82_HSM_VAR) sheM5[M5_SIZE];   /** SHE reply         */
} Crypto_82_Hsm_SHE_DataType;

/**
 * \brief Type for the key format as specified by ASN.1.
 */
typedef enum eCrypto_82_Hsm_KeyElementFormatType
{
    CRYPTO_KE_FORMAT_BIN_OCTET                  = 0x01,
    CRYPTO_KE_FORMAT_BIN_SHEKEYS                = 0x02,
    CRYPTO_KE_FORMAT_BIN_IDENT_PRIVATEKEY_PKCS8 = 0x03,
    CRYPTO_KE_FORMAT_BIN_IDENT_PUBLICKEY        = 0x04,
    CRYPTO_KE_FORMAT_BIN_RSA_PRIVATEKEY         = 0x05,
    CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY          = 0x06

} Crypto_82_Hsm_KeyElementFormatType;

/**
 * \brief Key element read access type.
 */
typedef enum eCrypto_82_Hsm_KeyElementReadAccessType
{
    CRYPTO_82_HSM_RA_ALLOWED        = 0x00, /** Key element can be read as plaintext.                                       */
    CRYPTO_82_HSM_RA_ENCRYPTED      = 0x01, /** Key element can be read encrypted. E.g. SHE Ram-Key export.                 */
    CRYPTO_82_HSM_RA_INTERNAL_COPY  = 0x02, /** Key element can be copied to another key element in the same crypto driver. */
    CRYPTO_82_HSM_RA_DENIED         = 0x03  /** Key element cannot be read from outside the Crypto Driver.                  */

} Crypto_82_Hsm_KeyElementReadAccessType;

/**
 * \brief Key element write access type.
 */
typedef enum eCrypto_82_Hsm_KeyElementWriteAccessType
{
    CRYPTO_82_HSM_WA_ALLOWED        = 0x00, /** Key element can be rewritten as plaintext.                                    */
    CRYPTO_82_HSM_WA_ENCRYPTED      = 0x01, /** Key element can be written encrypted. E.g. SHE load key.                      */
    CRYPTO_82_HSM_WA_INTERNAL_COPY  = 0x02, /** Key element can be filled with another key element in the same crypto driver. */
    CRYPTO_82_HSM_WA_DENIED         = 0x03  /** Key element can not be written from outside the Crypto Driver.                */

} Crypto_82_Hsm_KeyElementWriteAccessType;

/**
 * \brief State type: FALSE means invalid, TRUE means valid.
 */
typedef boolean Crypto_82_Hsm_ConfigKeyTypeStateType;

/**
 * \brief Key element write access type.
 */
typedef enum eCrypto_82_Hsm_RuntimeKeystateType
{
    CRYPTO_82_HSM_KEY_IN_USE        = 0x01, /** Key is currently being used in a session.          */
    CRYPTO_82_HSM_KEY_NOT_USED      = 0x02, /** Key is currently not being used in a session.      */
    CRYPTO_82_HSM_KEY_LOADED        = 0x03, /** Key is currently available in session context.     */
    CRYPTO_82_HSM_KEY_NOT_LOADED    = 0x04  /** Key is currently not available in session context. */

} Crypto_82_Hsm_RuntimeKeystateType;

/**
 * \brief Key element storage type.
 */
typedef enum eCrypto_82_Hsm_KeyElementStorageType
{
    CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT           = 0x00,  /** Key element is stored directly into the keyDataPtr member of Crypto_82_Hsm_ConfigKeyElementType. */
    CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT            = 0x01,  /** Key element is stored in SHE or the Nvm.                                                         */
    CRYPTO_82_HSM_RAM_KEY_ELEMENT                   = 0x02,  /** Key element is injected into hsm session context.                                                */
    CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED = 0xFF,  /** Reserved enum id.                                                                                */

} Crypto_82_Hsm_KeyElementStorageType;

/**
 * \brief Csai key type.
 */
typedef enum eCrypto_82_Hsm_csaiPersistentOrRamKeyType
{
    CRYPTO_82_HSM_KEYTYPE_UNDEFINED              = 0x00,  /** Key type is undefined          */
    CRYPTO_82_HSM_KEYTYPE_SHE                    = 0x01,  /** Key type is SHE                */
    CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED           = 0x02,  /** Key type is SHE extended       */
    CRYPTO_82_HSM_KEYTYPE_SHE_RAM                = 0x03,  /** Key type is SHE RAM            */
    CRYPTO_82_HSM_KEYTYPE_NVM                    = 0x04,  /** Key type is NvM                */ 
    CRYPTO_82_HSM_KEYTYPE_RAM                    = 0x05,  /** Key type is RAM                */ 
} Crypto_82_Hsm_csaiPersistentOrRamKeyType;

/**
 * \brief Holds information about a configured key.
 *
 * Certain keys have multiple key elements (e.g. an AES Key has AES_CTR_IV and AES_CTR_Key as elements).
 */
typedef struct sCrypto_82_Hsm_ConfigKeyType
{
    CONST(ecy_hsm_Csai_KeyIdT, CRYPTO_82_HSM_CONST) HsmKeyId;                 /** CycurHSM key id.                */
    CONST(ecy_hsm_Csai_KeyTypeT, CRYPTO_82_HSM_CONST) keyType;             /** CycurHSM key type.              */
    CONST(uint32, CRYPTO_82_HSM_CONST) keyProperties;                      /** CycurHSM key properties.        */
    VAR(Crypto_82_Hsm_ConfigKeyTypeStateType, CRYPTO_82_HSM_VAR) keyState; /** Key state (valid or invalid).   */
    CONST(uint32, CRYPTO_82_HSM_CONST) numberOfKeyElements;                /** Number of key elements.         */

} Crypto_82_Hsm_ConfigKeyType;

/**
 * \brief Holds information about a runtime key element.
 *
 * The information necessary to access a certain runtime key element is the keyHandle value. 
 */
typedef struct sCrypto_82_Hsm_RuntimeKeyType
{
    VAR(ecy_hsm_Csai_KeyHandleT, CRYPTO_82_HSM_VAR) keyHandle;          /** If a key element is available in a session context it will be acessed by this value.             */
} Crypto_82_Hsm_RuntimeKeyType;

/**
 * \brief Holds information about a configured key element.
 */
typedef struct sCrypto_82_Hsm_ConfigKeyElementType
{
    CONST(Crypto_82_Hsm_KeyElementReadAccessType, CRYPTO_82_HSM_CONST) readAccess;      /** Key element read access rights.                                                                      */
    CONST(Crypto_82_Hsm_KeyElementWriteAccessType, CRYPTO_82_HSM_CONST) writeAccess;    /** Key element write access rights.                                                                     */
    CONSTP2CONST(uint8, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) initialContentPtr;    /** Buffer which may be filled with initial value after Crypto_Init().                                   */
    CONST(uint32, CRYPTO_82_HSM_CONST) keySize;                                         /** The key size in bytes.                                                                               */
    CONST(Crypto_82_Hsm_KeyElementFormatType, CRYPTO_82_HSM_CONST) keyFormat;           /** The key format as specified by ASN.1.                                                                */
    CONST(boolean, CRYPTO_82_HSM_CONST) allowPartialAccess;                             /** Is partial access allowed.                                                                           */
    CONST(Crypto_82_Hsm_KeyElementStorageType, CRYPTO_82_HSM_CONST) keyStorageType;     /** Key storage type (buffer, persistent or RAM).                                                        */
    CONST(uint32, CRYPTO_82_HSM_CONST) keyElementId;                                    /** The ID of the key element.                                                                           */
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyDataPtr;                                      /** Pointer to the key data buffer in case of storage type 'Buffer'.                                     */ /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONST(boolean, CRYPTO_82_HSM_CONST) loadAtInit;                                     /** Is key element going to be loaded into RAM from persistent key storage during initialization phase.  */

} Crypto_82_Hsm_ConfigKeyElementType;

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

/**
 * \startuml {Crypto_82_Hsm_KeyElementSet.png}
 * !pragma useVerticalIf on
 * start
 * 
 * #palegreen:set return E_OK;
 * 
 * partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is **STD_ON**" {
 * if (Errors occured?) then (yes)
 *   #pink:return E_NOT_OK;
 *   stop
 * else(no)
 * endif
 * }
 * 
 * if (Driver Object Busy?) then (yes)
 *   #pink: Return Crypto_E_BUSY;
 * 
 * 
 * (no) elseif (Key length is shorter than the configured data length AND
 *  partial access NOT ALLOWED?) then (yes)
 *   #pink: Return CRYPTO_E_KEY_SIZE_MISMATCH;
 * 
 * (no) elseif (Key length is larger than the configured data length?) then (yes)
 *   #pink: Return CRYPTO_E_KEY_SIZE_MISMATCH;
 * 
 * (no) elseif (write access is DENIED or INTERNAL COPY?) then (yes)
 *   #pink: Return CRYPTO_E_KEY_WRITE_FAIL;
 * 
 * else (no)
 *   #palegreen:NO Errors Detected;
 * endif
 * 
 * if (No ERRORS detected?) then (yes)
 *   #palegreen:Crypto_82_Hsm_Process_KeyElementSet() >
 * else (no)
 * endif
 * 
 * stop
 * \enduml
 */
/**
 * \brief Sets the given key element bytes to the key identified by cryptoKeyId.
 *
 * \id 0x04
 * \sync Synchronous
 * \reentrant Non Reentrant
 *
 * \param [in] cryptoKeyId  Holds the identifier of the key whose key element shall be set.
 * \param [in] keyElementId Holds the identifier of the key element which shall be set.
 * \param [in] keyPtr       Holds the pointer to the key data which shall be set as key element.
 * \param [in] keyLength    Contains the length of the key element in bytes.
 *
 * \retval E_OK                         Request successful
 * \retval E_NOT_OK                     Request Failed
 * \retval CRYPTO_E_BUSY                Request Failed, Crypto Driver Object is Busy
 * \retval CRYPTO_E_KEY_WRITE_FAIL      Request failed because write access was denied
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE   Request failed because the key is not available
 * \retval CRYPTO_E_KEY_SIZE_MISMATCH   Request failed, key element size does not match size of provided data
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementSet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(uint32, AUTOMATIC) keyLength
);

/**
 * \startuml {Crypto_82_Hsm_KeySetValid.png}
 * !pragma useVerticalIf on
 * start
 * 
 * partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is STD_ON" {
 * if (Errors occured?) then (yes)
 *   #pink:Return E_NOT_OK;
 *   stop
 * elseif (Driver Object Busy?) then (yes)
 *   #pink:Return CRYPTO_E_BUSY;
 *   stop
 * else (no)
 * endif
 * }
 * 
 * 
 * #palegreen:Crypto_82_Hsm_Process_KeySetValid();
 * 
 * 
 * stop
 * \enduml
 */
/**
 * \brief Sets the key state of the key identified by cryptoKeyId to valid.
 *
 * \id 0x05
 * \sync Synchronous
 * \reentrant Non Reentrant
 *
 * \param [in] cryptoKeyId Holds the identifier of the key which shall be set to valid.
 *
 * \retval E_OK                       Request successful
 * \retval E_NOT_OK                   Request Failed
 * \retval CRYPTO_E_BUSY              Request Failed, Crypto Driver Object is Busy
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeySetValid(VAR(uint32, AUTOMATIC) cryptoKeyId);

/**
 * \brief Returns a key element.
 *
 * This interface shall be used to get a key element of the key identified by the cryptoKeyId and store the key element
 * in the memory location pointed by the result pointer.
 *
 * \id 0x06
 * \sync Synchronous
 * \reentrant Reentrant
 * 
 * \note If the actual key element is directly mapped to flash memory, there could be a bigger delay when calling this
 * function (synchronous operation).
 *
 * \param [in]       cryptoKeyId     Holds the identifier of the key whose key element shall be returned.
 * \param [in]       keyElementId    Holds the identifier of the key element which shall be returned.
 * \param [in, out]  resultLengthPtr Holds a pointer to a memory location in which the length information is stored.
 *                                   On calling this function this parameter shall contain the size of the buffer
 *                                   provided by resultPtr. If the key element is configured to allow partial access,
 *                                   this parameter contains the amount of data which should be read from the key
 *                                   element. The size may not be equal to the size of the provided buffer anymore.
 *                                   When the request has finished, the amount of data that has been stored shall be
 *                                   stored.
 * \param [out]      resultPtr       Holds the pointer of the buffer for the returned key element.
 *
 * \retval E_OK                         Request successful
 * \retval E_NOT_OK                     Request Failed
 * \retval CRYPTO_E_BUSY                Request Failed, Crypto Driver Object is Busy
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE   Request failed, the requested key element is not available
 * \retval CRYPTO_E_KEY_READ_FAIL       Request failed because read access was denied
 * \retval CRYPTO_E_KEY_EMPTY           Request failed because of uninitialized source key element
 *
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Copies a key element to another key element in the same crypto driver.
 *
 * \id 0x0F
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \note If the actual key element is directly mapped to flash memory, there could be a bigger delay when calling this
 * function (synchronous operation).
 *
 * \param [in] cryptoKeyId          Holds the identifier of the key whose key element shall be the source element.
 * \param [in] keyElementId         Holds the identifier of the key element which shall be the source for the copy
 *                                  operation.
 * \param [in] targetCryptoKeyId    Holds the identifier of the key whose key element shall be the destination element.
 * \param [in] targetKeyElementId   Holds the identifier of the key element which shall be the destination for the copy
 *                                  operation.
 * 
 * \retval E_OK                           Request successful
 * \retval E_NOT_OK                       Request failed
 * \retval CRYPTO_E_BUSY                  Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE     Request failed, the requested key element is not available
 * \retval CRYPTO_E_KEY_READ_FAIL         Request failed, not allowed to extract key element
 * \retval CRYPTO_E_KEY_WRITE_FAIL        Request failed, not allowed to write key element
 * \retval CRYPTO_E_KEY_SIZE_MISMATCH     Request failed, key element sizes are not compatible
 * \retval CRYPTO_E_KEY_EMPTY             Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementCopy(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
);

/**
 * \brief Copies a key element to another key element in the same crypto driver.
 *
 * The keyElementSourceOffset and keyElementCopyLength allows to copy just a part of the source key element into the
 * destination. The offset of the target key is also specified with this function.
 *
 * \id 0x13
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 * 
 * \note If the actual key element is directly mapped to flash memory, there could be a bigger delay when calling this
 * function (synchronous operation).
 *
 * \param [in] cryptoKeyId             Holds the identifier of the key whose key element shall be the source element.
 * \param [in] keyElementId            Holds the identifier of the key element which shall be the source for the copy operation.
 * \param [in] keyElementSourceOffset  This is the offset of the of the source key element indicating the start index of
 *                                     the copy operation.
 * \param [in] keyElementTargetOffset  This is the offset of the of the target key element indicating the start index of
 *                                     the copy operation.
 * \param [in] keyElementCopyLength    Specifies the number of bytes that shall be copied.
 * \param [in] targetCryptoKeyId       Holds the identifier of the key whose key element shall be the destination element.
 * \param [in] targetKeyElementId      Holds the identifier of the key element which shall be the destination for the copy
 *                                     operation.
 *
 * \retval E_OK                          Request successful
 * \retval E_NOT_OK                      Request failed
 * \retval CRYPTO_E_BUSY                 Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE    Request failed, the requested key element is not available
 * \retval CRYPTO_E_KEY_READ_FAIL        Request failed, not allowed to extract key element
 * \retval CRYPTO_E_KEY_WRITE_FAIL       Request failed, not allowed to write key element
 * \retval CRYPTO_E_KEY_SIZE_MISMATCH    Request failed, key element sizes are not compatible
 * \retval CRYPTO_E_KEY_EMPTY            Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementCopyPartial(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) keyElementSourceOffset,
    VAR(uint32, AUTOMATIC) keyElementTargetOffset,
    VAR(uint32, AUTOMATIC) keyElementCopyLength,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
);


/**
 * \brief Copies a key with all its elements to another key in the same crypto driver.
 *
 * \id 0x10
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 * 
 * \note If the actual key element is directly mapped to flash memory, there could be a bigger delay when calling this
 * function (synchronous operation)
 *
 * \param [in] cryptoKeyId         Holds the identifier of the key whose key element shall be the source element.
 * \param [in] targetCryptoKeyId   Holds the identifier of the key whose key element shall be the destination element.
 *
 * \retval E_OK                          Request successful
 * \retval E_NOT_OK                      Request failed
 * \retval CRYPTO_E_BUSY                 Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE    Request failed, the requested key element is not available
 * \retval CRYPTO_E_KEY_READ_FAIL        Request failed, not allowed to extract key element
 * \retval CRYPTO_E_KEY_WRITE_FAIL       Request failed, not allowed to write key element
 * \retval CRYPTO_E_KEY_SIZE_MISMATCH    Request failed, key element sizes are not compatible
 * \retval CRYPTO_E_KEY_EMPTY            Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyCopy(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
);

/**
 * \brief Used to retrieve information which key elements are available in a given key.
 *
 * \id 0x11
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \param [in]  cryptoKeyId             Holds the identifier of the key whose available element ids shall be exported.
 * \param [out] keyElementIdsPtr        Contains the pointer to the array where the ids of the key elements shall be stored.
 * \param [in]  keyElementIdsLengthPtr  Holds a pointer to the memory location in which the number of key elements in the
 *                                      given key is stored. On calling this function, this parameter shall contain the
 *                                      size of the buffer provided by keyElementIdsPtr. When the request has finished,
 *                                      the actual number of key elements shall be stored.
 *
 * \retval E_OK             Request successful
 * \retval E_NOT_OK         Request failed
 * \retval CRYPTO_E_BUSY    Request failed, Crypto Driver Object is busy
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementIdsGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) keyElementIdsPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) keyElementIdsLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief This function generates the internal seed state using the provided entropy source.
 *
 * Furthermore, this function can be used to update the seed state with new entropy.
 *
 * \id 0x0D
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \param [in] cryptoKeyId  Holds the identifier of the key for which a new seed shall be generated.
 * \param [in] seedPtr      Holds a pointer to the memory location which contains the data to feed the seed.
 * \param [in] seedLength   Contains the length of the seed in bytes.
 *
 * \retval E_OK             Request successful
 * \retval E_NOT_OK         Request failed
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_RandomSeed(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) seedPtr,
    VAR(uint32, AUTOMATIC) seedLength
);

/**
 * \brief Generates new key material store it in the key identified by cryptoKeyId.
 *
 * \id 0x07
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \param [in] cryptoKeyId      Holds the identifier of the key which is to be updated with the generated value.
 *
 * \retval E_OK                 Request successful
 * \retval E_NOT_OK             Request failed
 * \retval CRYPTO_E_BUSY        Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_EMPTY   Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyGenerate(
    VAR(uint32, AUTOMATIC) cryptoKeyId
);

/**
 * \brief Derives a new key by using the key elements in the given key identified by the cryptoKeyId.
 *
 * The given key contains the key elements for the password, salt. The derived key is stored in the key element with the
 * id 1 of the key identified by targetCryptoKeyId. The number of iterations is given in the key element
 * CRYPTO_KE_KEYDERIVATION_ITERATIONS.
 *
 * \id 0x08
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \param [in] cryptoKeyId        Holds the identifier of the key which is used for key derivation.
 * \param [in] targetCryptoKeyId  Holds the identifier of the key which is used to store the derived key.
 *
 * \retval E_OK                   Request successful
 * \retval E_NOT_OK               Request failed
 * \retval CRYPTO_E_BUSY          Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_EMPTY     Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyDerive(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
);

/**
 * \brief Calculates the public value for the key exchange and stores the public key in the memory location pointed by
 *        the public value pointer.
 * 
 * \id 0x09
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 * 
 * \note  The Key element used for algo selection ( CRYPTO_KE_KEYEXCHANGE_ALGORITHM ) can be either NULL or stored in CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT.
 *
 * \param [in]      cryptoKeyId           Holds the identifier of the key which shall be used for the key exchange protocol.
 * \param [in, out] publicValueLengthPtr  Holds a pointer to the memory location in which the public value length
 *                                        information is stored. On calling this function, this parameter shall contain
 *                                        the size of the buffer provided by publicValuePtr. When the request has
 *                                        finished, the actual length of the returned value shall be stored.
 * \param [out]     publicValuePtr        Contains the pointer to the data where the public value shall be stored.
 *
 * \retval E_OK                           Request successful
 * \retval E_NOT_OK                       Request failed
 * \retval CRYPTO_E_KEY_NOT_VALID         Key Element CRYPTO_KE_KEYEXCHANGE_ALGORITHM has incorrect data or is a NULL_PTR
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcPubVal(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) publicValuePtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) publicValueLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Calculates the shared secret key for the key exchange with the key material of the key identified by the
 *        cryptoKeyId and the partner public key.
 *
 * The shared secret key is stored as a key element in the same key.
 *
 * \id 0x0A
 * \sync Synchronous
 * \reentrant Reentrant but not for the same cryptoKeyId
 *
 * \param [in] cryptoKeyId               Holds the identifier of the key which shall be used for the key exchange protocol.
 * \param [in] partnerPublicValuePtr     Holds the pointer to the memory location which contains the partner's public value.
 * \param [in] partnerPublicValueLength  Contains the length of the partner's public value in bytes.
 *
 * \retval E_OK                          Request successful
 * \retval E_NOT_OK                      Request failed
 * \retval CRYPTO_E_BUSY                 Request failed, Crypto Driver Object is busy
 * \retval CRYPTO_E_KEY_EMPTY            Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcSecret(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) partnerPublicValuePtr,
    VAR(uint32, AUTOMATIC) partnerPublicValueLength
);

/**
 * \brief Returns a pointer to a key element.
 *
 * \param [in]  keyId            Crypto Key Id.
 * \param [in]  keyElementId     Crypto Key Element Id.
 * \param [out] keyElementIndex  Key Element Index.
 *
 * \return element               The pointer to the configured key element.
*/
FUNC(const Crypto_82_Hsm_ConfigKeyElementType*, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_findKeyElement(
    VAR(uint32, AUTOMATIC) keyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2VAR(uint32,  AUTOMATIC, AUTOMATIC) keyElementIndex /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

#if ((CRYIF_AR_RELEASE_MAJOR_VERSION == 4u) && (CRYIF_AR_RELEASE_MINOR_VERSION <= 4u))

/**
 * \note Ensure compatibility with previous versions of AUTOSAR. However, the following functions are stubbed and always
 * return NOT_OK.
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CertificateParse(VAR(uint32, AUTOMATIC) cryptoKeyId);

/**
 * \note Ensure compatibility with previous versions of AUTOSAR. However, the following functions are stubbed and always
 * return NOT_OK.
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CertificateVerify(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) verifyCryptoKeyId,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_82_HSM_VAR) verifyPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

#endif /* ((CRYIF_AR_RELEASE_MAJOR_VERSION == 4u) && (CRYIF_AR_RELEASE_MINOR_VERSION <= 4u)) */

/**
 * \brief Wrapper to call the Csai_LoadKey() after Crypto_82_Hsm_Job_KeySetValid was called for SHE Keys.
 * 
 * This is already included in Crypto_82_Hsm_KeySetValid, it is only needed after Crypto_82_Hsm_Job_KeySetValid.
 * This is called after all Crypto_82_Hsm_Job_KeySetValid operations, but will only load the key for SHE Keys.
 *
 * \param [in] objectId     Crypto Object Id on which the KeySetValid Job is configured.
 * \param [in] serviceId    The service ID from which the function is called.
 * \param [in] jobId        The jobID from which the function is called.
 * 
 * \retval E_OK             Key was loaded or key loading was not neccesary (for keys other than SHE)
 * \retval E_NOT_OK         Function call was not successful
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_LoadSHEKey_RAM(VAR(uint32, AUTOMATIC) objectId, uint8 serviceId, uint32 jobId);

/**
 * \brief Function which cycles through all key elements of a respective key and checks their validity. If
 * all key elements are valid the key status will be set to valid.
 * 
 * \param [in]      cryptoKeyId     Id of an AUTOSAR modelled key.
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_UpdateKeyValidity( VAR(uint32, AUTOMATIC) cryptoKeyId);

/**
 * \brief Function which gets the index of a key material key element in the Crypto_82_Hsm_configKeyElements array.
 *
 * \param [in, out] keyMaterialElemIndex    Pointer to index of the key material key element.
 * \param [in]      cryptoKeyId             Id of an AUTOSAR modelled key.
 * 
 */
FUNC(void, CRYPTO_82_HSM_CODE) getKeyMaterialElementIndex(uint32* keyMaterialElemIndex, uint32 cryptoKeyId);


/**
 * \startuml {Crypto_82_Hsm_Process_KeySetValid.png}
 * !pragma useVerticalIf on
 *   start
 *   
 *   if (AUTOSAR Key Validity is INVALID?) then (yes)
 * 
 *       if (Key Material Element found?) then (yes)
 * 
 *           if (Key Material Element Validity is INVALID?) then (yes)
 * 
 *               #palegreen: Serialize Key;
 * 
 *               if (Serialization successful?) then (yes)
 * 
 *                   if (SHE key?) then (yes)
 * 
 *                       #palegreen: Load key into session context;
 * 
 *                       if (Operation successful?) then (yes)
 * 
 *                           if (Is SHE RAM key?) then (no)
 * 
 *                               #palegreen: Copy M4 and M5 to Proof key element;
 *                               #palegreen: Set Proof Key Element Validity to VALID;
 *                           else (yes)
 *                           endif
 * 
 *                           #palegreen: Clean SHE buffers;
 *                       
 *                       else (no)
 * 
 *                           #pink: Return E_NOT_OK;
 *                           stop
 * 
 *                       endif
 *                   else (no)
 *                   
 *                   endif
 *                   #palegreen: Set Key Material Element Validity to VALID;
 * 
 *               else (no)
 * 
 *               #pink: Return E_NOT_OK;
 *               stop
 * 
 *               endif
 * 
 *           else (no)
 * 
 *           endif
 * 
 *                 partition "CRYPTO_82_HSM_DENSO_KEY_VALIDITY is STD_ON" {
 *                         #palegreen:Set Denso Key Validity to VALID;
 *                         }
 * 
 *                 if (All key elements are valid?) then (yes)
 * 
 *               #palegreen: Set AUTOSAR Key Validity to VALID;
 *                 else(no)
 *                 endif
 * 
 *               #palegreen: Return E_OK;
 * 
 * 
 *       else (no)
 * 
 *       #pink: Return E_NOT_OK;
 * 
 *       endif 
 * 
 *   else (no)
 * 
 *   #palegreen: Return E_OK;
 * 
 *   endif
 *   
 *   stop
 * \enduml
 */
/**
 * \brief Function which processes a keySetValid operation.
 * 
 * \param [in]      cryptoKeyId     Id of an AUTOSAR modelled key.
 * 
 * \retval E_OK                     Operation successful.
 * \retval E_NOT_OK                 Operation failed.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeySetValid(VAR(uint32,AUTOMATIC) cryptoKeyId);

/**
 * \startuml {Crypto_82_Hsm_Process_KeyElementSet.png}
 * !pragma useVerticalIf on
 * start
 * 
 * if (Is it a SHE 
 * RAM KEY Element?) then (yes)
 *   if (Is SHE RAM Buffer EMPTY?) then (yes)
 *     #palegreen:Copy passed Key Data 
 *     to Buffer;
 *     :Set AUTOSAR Key Validity and Key Element Validity 
 *      to INVALID;
 *   else (no)
 *     #pink:return E_NOT_OK;
 *   endif
 * 
 * (no) elseif (Is it a Persistent 
 * SHE Key Element?) then (yes)
 *   if (Is SHE Key Buffer EMPTY?) then (yes)
 *     #palegreen:Copy Key Data 
 *     (M1~M3) to Buffer;
 *     :Set AUTOSAR Key Validity and Key Element Validity 
 *      to INVALID;
 *   else (no)
 *     #pink:return E_NOT_OK;
 *   endif
 * 
 * (no) elseif (Is it a Persistent 
 * SHE Extended 
 * Key Element?) then (yes)
 *   if (Is SHE Extended Buffer EMPTY?) then (yes)
 *     #palegreen:Copy Key Data 
 *     (M1~M3) to Buffer;
 *     :Set AUTOSAR Key Validity and Key Element Validity 
 *      to INVALID;
 *   else (no)
 *     #pink:return E_NOT_OK;
 *   endif
 * 
 * (no) elseif (Is it 
 * a Persistent 
 * NvM Key Element 
 * OR 
 * RAM Key Element?) then (yes)
 * 
 *   :Check and prepare injection data;
 *   :ecy_hsm_Csai_InjectKey() >
 *   
 *   if (Is Inject Key successful?) then (yes)
 *     :Poll Handle Job Operation;
 * 
 *     if (Is Job COMPLETED successfully?) then (yes)
 *       :set AUTOSAR Key Validity 
 *        to INVALID;
 *       if (Is it a RAM key Storage?) then (yes)
 *         #palegreen:set Key Element Validity
 *         to VALID;
 *         partition "CRYPTO_82_HSM_DENSO_KEY_VALIDITY is **STD_ON**" {
 *           :Set Denso Key Validity to VALID;
 *         }
 *       else (no)
 *         :set Key Element Validity
 *          to INVALID;
 *       endif
 *     else (no)
 *       #pink:return 
 *       CRYPTO_E_KEY_NOT_AVAILABLE;
 *     endif
 *   else (no)
 *     #pink:return 
 *     E_NOT_OK;
 *   endif
 * 
 * (no) elseif (Is it a Data 
 * Buffer Storage?) then (yes)
 *   if (Is passed Key Data VALID?) then (yes)
 *     #palegreen:Copy passed Key Data 
 *      to Buffer;
 *     :set AUTOSAR Key Validity to INVALID;
 *     #palegreen:set Key Element Validity
 *     to VALID;
 *   else (no)
 *     #pink:return E_NOT_OK;
 *   endif
 * 
 * else (no)
 *    #pink:return E_NOT_OK;
 * endif
 * 
 * stop
 * \enduml
 */
/**
 * \brief Function which processes a keyElementSet operation.
 * 
 * \param [in]      cryptoKeyId     Id of an AUTOSAR modelled key.
 * \param [in]      keyElemIndex    Index of a keyElement in the Crypto_82_Hsm_configKeyElements array.
 * \param [in]      keyPtr          Pointer to data which is to be set for the respective key element.
 * \param [in]      keyStorageType  Storage type of the key element.
 * \param [in]      keyDataPtr      Data buffer element adress.
 * \param [in]      keyLength       Length of the key.
 * 
 * \retval E_OK                     Operation successful.
 * \retval E_NOT_OK                 Operation failed.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyElementSet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElemIndex,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(Crypto_82_Hsm_KeyElementStorageType, AUTOMATIC) keyStorageType,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) keyDataPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyLength
);

/**
 * \brief Function which processes a Crypto_82_Hsm_KeyElementGet operation.
 * 
 * \param [in]      cryptoKeyId     Id of an AUTOSAR modelled key.
 * \param [in]      objectId        Crypto Driver Object id.
 * \param [in]      element         Pointer to a Crypto_82_Hsm_ConfigKeyElementType. 
 * \param [in]      keyElemIndex    Index of the keyElement.
 * \param [in, out] jobHandle       Value of a jobHandle.
 * \param [out]     resultPtr       Pointer to the buffer where the data will be stored.
 * \param [in]      resultLengthPtr Length of the buffer where the data will be stored.
 * \param [in]      serviceId       Either KEY_ELEMENT_GET or KEY_EXCHANGE_CALC_PUB_VAL service.
 * \param [in]      jobId           The jobID from which the function is called.
 * 
 * \retval E_OK                     Operation successful.
 * \retval E_NOT_OK                 Operation failed.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) objectId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element,
    VAR(uint32, AUTOMATIC) keyElemIndex,
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    uint8 serviceId, 
    uint32 jobId
);

/**
 * \brief Function which polls a Crypto_82_Hsm_Process_KeyElementGet operation.
 * 
 * \param [in]      cryptoKeyId     Id of an AUTOSAR modelled key.
 * \param [in]      objectId        Crypto Driver Object id.
 * \param [in]      element         Pointer to a Crypto_82_Hsm_ConfigKeyElementType. 
 * \param [in]      jobHandle       Value of a jobHandle.
 * \param [out]     resultPtr       Pointer to the buffer where the data will be stored.
 * \param [in]      resultLengthPtr Length of the buffer where the data will be stored.
 * \param [in]      serviceId       The service for which polling is done.
 * 
 * \retval E_OK                     Operation successful.
 * \retval E_NOT_OK                 Operation failed.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Poll_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,    
    VAR(uint32, AUTOMATIC) objectId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element,
    VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC) jobHandle,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    uint8 serviceId
);

/**
 * \brief Function which handles the clearing of internal buffers and key element data buffers for key derive.
 *
 * \param [in]      objectId                    Crypto Driver Object id.
 * \param [in]      cryptoKeyId                 Id of an AUTOSAR modelled key.
 * \param [in]      elementIterations           Pointer to Iteration Key Element.
 * \param [in]      iterationsKeyElementIndex   Iteration Key Element Index.
 * \param [in]      elementSalt                 Pointer to Salt Key Element.
 * \param [in]      saltKeyElementIndex         Salt Key Element Index.
 * \param [in]      elementPass                 Pointer to Password Key Element.
 * \param [in]      passwordKeyElementIndex     Password Key Element Index.
 * 
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_clearbuffers_KeyDerive(
    VAR(uint32, AUTOMATIC) objectID,
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementIterations,
    VAR(uint32, AUTOMATIC) iterationsKeyElementIndex,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSalt,
    VAR(uint32, AUTOMATIC) saltKeyElementIndex,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPass,
    VAR(uint32, AUTOMATIC) passwordKeyElementIndex
    );

/**
 * \brief This function does the post processing after the polling for an injection operation is finished
 *
 * \param [in]  cryptoKeyId                 Crypto Key Id.
 * \param [in]  pollStatus                  result of Crypto_82_Hsm_PollJob operation. 
 * \param [in]  keyMaterialElemIndex        Index of the key material element. 
 * \param [in]  CsaiPersistentOrRamKeyType  Persistent or ram key type
 * \param [in]  objectId                    Id of crypto driver object.
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_Inject_Poll_Result(VAR(uint32,AUTOMATIC) cryptoKeyId, Std_ReturnType pollStatus, VAR(uint32, AUTOMATIC) keyMaterialElemIndex, VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) CsaiPersistentOrRamKeyType, VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Function which handles the clearing of internal she buffers and for KeySetValid.
 *
 * \param [in]      objectId          Crypto Driver Object id.
 * \param [in]      cryptoKeyId       Id of an AUTOSAR modelled key.
 * 
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_clearbuffers_KeySetValid( 
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) objectID
    );

/**
 * \brief Returns the key type which shall be used to differentiate between calling certain csai key management APIs.
 * 
 * \param [in] arCryptoKeyId       The AUTOSAR modelled key Id.
 * \param [in] keyElementIndex     Key element index.
 * 
 * \retval CRYPTO_82_HSM_KEYTYPE_UNDEFINED     Key type could not be determined.
 * \retval CRYPTO_82_HSM_KEYTYPE_SHE           Key type is SHE.
 * \retval CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED  Key type is SHE extended.
 * \retval CRYPTO_82_HSM_KEYTYPE_SHE_RAM       Key type is SHE RAM.
 * \retval CRYPTO_82_HSM_KEYTYPE_NVM           Key type is NvM.
 * \retval CRYPTO_82_HSM_KEYTYPE_RAM           Key type is RAM.
 */
FUNC(Crypto_82_Hsm_csaiPersistentOrRamKeyType, CRYPTO_82_HSM_CODE) csaiPersistentOrRamKeyType( 
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementIndex 
);

/**
 * \brief This function performs the writting to nvm of a key on specified crypto driver object
 * 
 * \param [in] arCryptoKeyId       The AUTOSAR modelled key Id.
 * \param [in] objectID            Crypto driver object id.
 * \param [in] keyElementIndex     Key element index.
 * 
 * \retval csai_err                CycurHSM error code. Returns ecy_hsm_Csai_SUCCESS if everything was successful.
 */
FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_WriteToNvm(VAR(uint32, AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) objectId, VAR(uint32, AUTOMATIC) keyElemIndex);

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif /* CRYPTO_82_HSM_KEYMANAGEMENT_H */
