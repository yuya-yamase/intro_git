/**
 * \file Crypto_82_Hsm_KeyManagement.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of Key Management module
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "SchM_Crypto_82_Hsm.h"

#include "Crypto_82_Hsm_Internal.h"

#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_Dispatch.h"
#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm.h"
#include "Crypto_82_Hsm_Services.h"
#include "Crypto_82_Hsm_Mem.h"
#include "Crypto_82_Hsm_UserCallout.h"

#include "ecy_hsm_csai_shecompat.h"
#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_host_proxy.h"

#if ( ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON ) || ( CRYPTO_82_HSM_RUNTIME_ERROR_REPORT == STD_ON ) )
    #include "Det.h"
#endif

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

#define SHARED_SECRET_SIZE (32u)

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

VAR(Crypto_82_Hsm_SHE_KeyOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_SHE_loadKey[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

VAR(Crypto_82_Hsm_KeyExchangeCalcSecretOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

VAR(Crypto_82_Hsm_KeySetValidOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeySetValid_OperationState[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h" 
/**
 * \brief Shared Memory from Crypto to HSM
 */
VAR(Crypto_82_Hsm_SHE_DataType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

VAR(ecy_hsm_Csai_KeyRefT, AUTOMATIC) keyRef_keyElementGet[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/* Variable which is written in the context of the Crypto_82_Hsm_KeyExchangeCalcSecret function call and is passed to a cycurHsm API */
VAR(uint32, CRYPTO_82_HSM_VAR) keyExchangeCalcSecretCount[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

VAR(ecy_hsm_Csai_PinRefT, AUTOMATIC)  Crypto_82_Hsm_saltParam[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

VAR(ecy_hsm_Csai_PinRefT, AUTOMATIC)  Crypto_82_Hsm_passParam[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h" 

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

static VAR(ecy_hsm_Csai_KeyRefT, AUTOMATIC) Crypto_82_Hsm_keyData[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/* No data will be written to this variable, it is passed to the cycurHSM api only out of necessity to pass error checks. */
static VAR(uint8, AUTOMATIC) keyExchangePublicKeyDataBuffer[MAX_SIZE_ECDSA_PUBLIC_KEY];

/* No data will be written to this variable, it is passed to the cycurHSM api only out of necessity to pass error checks. */
static VAR(uint32, AUTOMATIC) keyExchangePublicValueLength;

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h" 

#define CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )
/**
 * \brief Loads a she key into ram. Returns ecy_hsm_CSAI_SUCCESS if successful or other value if unsuccessful.
 * 
 * \param [out]     cryptoKeyId                 Id of autosar modelled key.
 * \param [in]      keyMaterialElemIndex        Index of the key material element.
 * \param [in]      sessionHandle               Session handle.
 * \param [in]      jobHandle                   Job handle.
 * 
 * \retval  ecy_hsm_CSAI_SUCCESS            She key loaded successfully.
 */
static FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) loadSheKey(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyMaterialElemIndex,
    VAR(uint32, AUTOMATIC) sessionHandle,
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
#endif /* (CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON) */

/**
 * \brief Initializes the key data pointer depending on the key type. 
 * 
 * This will be used as input for setting the key/key pair.
 *
 * \param [out] keyDataPtr          Pointer to variable which holds key type and information about the key depending on the key type, such as pointers to the key data buffers, buffer lengths in bytes, key sizes in bits etc.
 * \param [in]  keyType             The key type, which will be saved in the keyDataPtr and based on which other fields from keyDataPtr will be filled.
 * \param [in]  keyPtr              Pointer to the buffer which contains the new key/key pair.
 * \param [in]  keyLength           The length of the buffer.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) assignKeyData(
    P2VAR(ecy_hsm_Csai_KeyRefT, AUTOMATIC, AUTOMATIC) keyDataPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyType,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(uint32, AUTOMATIC) keyLength
);

/**
 * \brief This function performs injection of key using the specified crypto driver object
 *
 * \param [in] cryptoKeyId         Id of autosar modelled key.
 * \param [in] objectID            Crypto driver object id.
 * 
 * \retval csai_err                CycurHSM error code. Returns ecy_hsm_Csai_SUCCESS if everything was successful.
 */
static FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_InjectKey(VAR(uint32,AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Function which starts the processing of a keySetValid operation for she keys.
 *
 * \param [in]      objectID                    Crypto driver object id.
 * \param [in]      CsaiPersistentOrRamKeyType  Persistent or ram key type
 * \param [in]      cryptoKeyId                 Id of autosar modelled key.
 *
 * \retval csai_err                  CycurHSM error code. Returns ecy_hsm_Csai_SUCCESS if everything was successful.
 */
static FUNC(ecy_hsm_Csai_ErrorT , CRYPTO_82_HSM_CODE) SheSerializeKeySetValid(
    VAR(uint32, AUTOMATIC) objectId,
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) CsaiPersistentOrRamKeyType,
    VAR(uint32,AUTOMATIC) cryptoKeyId
);

/**
 * \brief Function which processes a key derive operation.
 *
 * \param [in]      cryptoKeyId                 Id of autosar modelled key.
 * \param [in]      targetCryptoKeyId           Id of target autosar modelled key.
 * \param [in]      objectId                    Id of crypto driver object.
 * \param [in]      elementTargetIndex          Index of the targetCryptoKeyId key element in the key elements array.
 * \param [in]      elementPassIndex            Index of the password key element in the key elements array.
 * \param [in]      algoKeyElementIndex         Index of the algo key element in the key elements array.
 * \param [in]      elementSaltIndex            Index of the salt key element in the key elements array.
 * \param [in]      elementIterationsIndex      Index of the iterations key element in the key elements array.
 * \param [in]      elementParentKeyIndex       Index of the parent key element in the key elements array.
 *
 * \retval E_OK         Processing successful.
 * \retval E_NOT_OK     Processing failed.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyDerive(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) elementTargetIndex,
    VAR(uint32, AUTOMATIC) elementPassIndex,
    VAR(uint32, AUTOMATIC) algoKeyElementIndex,
    VAR(uint32, AUTOMATIC) elementSaltIndex,
    VAR(uint32, AUTOMATIC) elementIterationsIndex,
    VAR(uint32, AUTOMATIC) elementParentKeyIndex,
    P2VAR(uint8, CRYPTO_82_HSM_VAR, AUTOMATIC) detErr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */    
);

/**
 * \brief Mapping for keyDerive algorithm.
 *
 * \param [in] algo           Algorithm.
 *
 * \return ret_algo           Corresponding key derive algorithm supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_KeyDeriveFunctionType, CRYPTO_82_HSM_CODE) get_keyDeriveAlgo(uint32 algo);

/**
 * \brief Mapping for keyDerive algorithm for HSM.
 *
 * \param [in] algo           Algorithm.
 *
 * \return ret_algo           Corresponding key derive algorithm supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_KeyDerivationFunctionT, CRYPTO_82_HSM_CODE) get_keyDeriveAlgoHsm(Crypto_82_Hsm_KeyDeriveFunctionType algo);

/**
 * \brief Get key element size for key exchange.
 *
 * \param [in] cryptoKeyId           Id of autosar modelled key.
 * \param [in] elementPrivKey        Private key element.
 *
 * \return keyElementSize            Size of the key element.
 */
static FUNC(uint32, CRYPTO_82_HSM_CODE) get_keyElementSizeKeyExchange(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey
);

/**
 * \brief Mapping for keyExchangeCalcSecret algorithm.
 *
 * \param [in] keyType              Key type.
 * \param [in, out] keySize         Key size.
 *
 * \return ret_algo           Corresponding key exchange calc secret algorithm supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType, CRYPTO_82_HSM_CODE) get_keyExchangeCalcSecretAlgo(ecy_hsm_Csai_KeyTypeT keyType, uint32* keySize);

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
/**
 * \brief Checking shared secret key size against algorithm.
 *
 * \param [in] keyType              Key Type.
 * \param [in] keySize              Key pair size.
 * \param [in] sharedSecretSize     Shared secret size.
 *
 * \return ret              Result of checking. (E_OK if successful or E_NOT_OK otherwise )
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) check_KeyExchangeSharedSecretSize(ecy_hsm_Csai_KeyTypeT keyType, uint32 keyPairSize, uint32 sharedSecretSize);
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */

/**
 * \brief Mapping for keyExchangeCalcSecret algorithm for HSM.
 *
 * \param [in] algo           Algorithm.
 *
 * \return ret_algo           Corresponding key exchange calc secret algorithm supported by the HSM.
 */
static FUNC(ecy_hsm_Csai_DhAlgorithmT, CRYPTO_82_HSM_CODE) get_keyExchangeCalcSecretAlgoHsm(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType algo);

/**
 * \brief Returns key size based on the key type needed by HSM key generation service.
 *
 * \param [in] cryptoKeyId                  Crypto Key Id.
 * \param [in] elementKeyGenerate           Key element for which size is returned.
 *
 * \return size                             Key size.
 */
static FUNC(uint32, CRYPTO_82_HSM_CODE) get_keyGenerateKeySize(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC) elementKeyGenerate
);
/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(void, CRYPTO_82_HSM_CODE) assignKeyData(
    P2VAR(ecy_hsm_Csai_KeyRefT, AUTOMATIC, AUTOMATIC) keyDataPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyType,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(uint32, AUTOMATIC) keyLength
)
{
    VAR(uint32, AUTOMATIC) keySize;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufferPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    bufferPtr = (uint8*)keyPtr; /* PRQA S 0311  #This rule violation is suppressed because the Autosar interface uses a pointer to constant, while the CycurHSM interface uses structure which has a pointer to variable */
    keyDataPtr->type = KEYTYPE_RESERVED;

    switch(keyType)
    {
        case ecy_hsm_CSAI_KEYTYPE_SYMMETRIC:
        {
            keySize = keyLength;

            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_SYMMETRIC;
            keyDataPtr->u.sym.keySize =  (ecy_hsm_Csai_KeySizeT)((uint32)(keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.sym.key = bufferPtr;
            keyDataPtr->u.sym.length = keySize;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR:
        {
            keySize = (keyLength - 4u) / 2u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_RSA_PAIR;
            keyDataPtr->u.rsapair.keySize = (ecy_hsm_Csai_KeySizeT)((uint32)(keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.rsapair.n = bufferPtr;
            keyDataPtr->u.rsapair.nLength = keySize;
            (void)Crypto_82_Hsm_Memcpy_s(&keyDataPtr->u.rsapair.e, 4u, &bufferPtr[keySize], 4u, 4u);
            keyDataPtr->u.rsapair.d = &bufferPtr[keySize + 4u]; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.rsapair.dLength = keySize;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC:
        {
            keySize = keyLength - 4u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC;
            keyDataPtr->u.rsapub.keySize = (uint16)((uint32)(keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.rsapub.n = bufferPtr;
            keyDataPtr->u.rsapub.nLength = keySize;
            (void)Crypto_82_Hsm_Memcpy_s(&keyDataPtr->u.rsapub.e, 4u, &bufferPtr[keySize], 4u, 4u);

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR:
        {
            keySize = keyLength / 2u;

            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR;
            keyDataPtr->u.eddsapair.keySize = (ecy_hsm_Csai_KeySizeT)((uint32)(keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eddsapair.privKey = bufferPtr;
            keyDataPtr->u.eddsapair.privKeyLength = keySize;
            keyDataPtr->u.eddsapair.pubKey = &bufferPtr[keySize];
            keyDataPtr->u.eddsapair.pubKeyLength = keySize;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC;
            keyDataPtr->u.eddsapub.keySize =(ecy_hsm_Csai_KeySizeT)((uint32)(keyLength * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eddsapub.pubKey = bufferPtr;
            keyDataPtr->u.eddsapub.pubKeyLength = keyLength;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR:
        {
            keySize = keyLength / 3u;

            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR;
            keyDataPtr->u.eccpair.keySize = (ecy_hsm_Csai_KeySizeT)((uint32)(keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eccpair.pubKey = bufferPtr;
            keyDataPtr->u.eccpair.pubKeyLength = keySize * 2u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eccpair.privKey = &bufferPtr[2u * keySize]; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eccpair.privKeyLength = keySize;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC;
            keyDataPtr->u.eccpub.keySize = (ecy_hsm_Csai_KeySizeT)((uint32)((keyLength/2uL) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eccpub.pubKey = bufferPtr;
            keyDataPtr->u.eccpub.pubKeyLength = keyLength;

            break;
        }
        
         case ecy_hsm_CSAI_KEYTYPE_ECDSA_PRIVATE:
        {            
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PRIVATE;
            keyDataPtr->u.eccpriv.keySize = (ecy_hsm_Csai_KeySizeT)((uint32)(keyLength * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.eccpriv.privKey = bufferPtr;
            keyDataPtr->u.eccpriv.privKeyLength = keyLength;

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_SECRET_EC_POINT:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_SECRET_EC_POINT;
            keyDataPtr->u.ecpoint.curvePointSize = (ecy_hsm_Csai_KeySizeT)((uint32)(keyLength/2uL * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)); /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyDataPtr->u.ecpoint.curvePoint = bufferPtr;
            keyDataPtr->u.ecpoint.curvePointLength =keyLength;

            break;
        }

        default:

            /* Do nothing. CycurHsm will return error code in this case */
            break;
    }

}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_UpdateKeyValidity( VAR(uint32, AUTOMATIC) cryptoKeyId)
{
    VAR(uint32,  AUTOMATIC) noOfKeyElements;
    VAR(uint32, AUTOMATIC) keyElemStartIndex;
    VAR(boolean, AUTOMATIC) keyValidStatus = TRUE; 
    noOfKeyElements = Crypto_82_Hsm_configKeys[cryptoKeyId].numberOfKeyElements;
    keyElemStartIndex = Crypto_82_Hsm_keyIdToKeyElementIdMap[cryptoKeyId];

    /* Cycle through all key elements */
    for(uint32 keyIndex = keyElemStartIndex; keyIndex < keyElemStartIndex + noOfKeyElements; keyIndex++) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
    {
        if ( (Crypto_82_Hsm_KeyElementValidity[keyIndex] == FALSE) && ( (Crypto_82_Hsm_configKeyElements[keyIndex].keyElementId != CRYPTO_KE_MAC_PROOF) && (Crypto_82_Hsm_configKeyElements[keyIndex].keyElementId != CRYPTO_KE_CIPHER_PROOF) ) )
        {
            keyValidStatus = FALSE;
        }
    }

    Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = keyValidStatus;
}

static FUNC(ecy_hsm_Csai_ErrorT , CRYPTO_82_HSM_CODE) SheSerializeKeySetValid(
    VAR(uint32, AUTOMATIC) objectId,
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) CsaiPersistentOrRamKeyType,
    VAR(uint32,AUTOMATIC) cryptoKeyId    
)
{
    /* Initialize error as success */
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_SUCCESS;

    if (CsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE)
    {
        /* This function does not accept PRIO_HIGH. It will return an error code. */

        csai_err = ecy_hsm_Csai_She_LoadKey(
            Crypto_82_Hsm_driverObjects[objectId].sessionHandle,
            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY,
            Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr,
            &(Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr[M1_SIZE]),
            &(Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr[M1_SIZE + M2_SIZE]),
            Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM4,
            Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM5,
            &(Crypto_82_Hsm_driverObjects[objectId].jobHandle));
    }
    else if (CsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED)
    {
        csai_err = ecy_hsm_Csai_She_LoadKeyExtended(
            Crypto_82_Hsm_driverObjects[objectId].sessionHandle,
            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY,
            Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr,
            &(Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr[M1_SIZE]),
            &(Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr[M1_SIZE + M2_SIZE]),
            Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM4,
            Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM5,
            &(Crypto_82_Hsm_driverObjects[objectId].jobHandle));
    }
    else/*(CsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM)*/
    {
        csai_err = ecy_hsm_Csai_She_LoadPlainKey(
            Crypto_82_Hsm_driverObjects[objectId].sessionHandle,
            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],
            Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr,
            &(Crypto_82_Hsm_driverObjects[objectId].jobHandle));
    }

    return csai_err;
}

FUNC(void, CRYPTO_82_HSM_CODE) getKeyMaterialElementIndex(uint32* keyMaterialElemIndex, uint32 cryptoKeyId)
{
    /* The keyMaterialElement with the keyElementId equal to "CRYPTO_KE_KEYDERIVE_CUSTOM_PARENTKEY" is used only for keyDerive */
    (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVE_CUSTOM_PARENTKEY , keyMaterialElemIndex);
    
    if (*keyMaterialElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        /* The keyMaterialElement with the keyElementId equal to "CRYPTO_KE_KEYEXCHANGE_PRIVKEY" is used only for keyExchange */
        (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY , keyMaterialElemIndex);
    }
    
    if (*keyMaterialElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_CIPHER_KEY , keyMaterialElemIndex);
    }

    if (*keyMaterialElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_MAC_KEY , keyMaterialElemIndex);
    }
}

static FUNC(Crypto_82_Hsm_KeyDeriveFunctionType, CRYPTO_82_HSM_CODE) get_keyDeriveAlgo(uint32 algo)
{
    Crypto_82_Hsm_KeyDeriveFunctionType ret_algo = CryptoDriver_KDF_RESERVED;

    switch (algo)
    {
    case CRYPTO_ALGOFAM_PBKDF2:
        ret_algo = CryptoDriver_KDF_PKCS5_PBKDF2;
        break;
    case CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP80056C:
        ret_algo = CryptoDriver_KDF_NIST_SP800_56C_ONESTEP_AES_SHA256;
        break;
    case CRYPTO_ALGOFAM_CUSTOM_KDF_NISTSP800108:
        ret_algo = CryptoDriver_KDF_NIST_SP800_108_AES_CMAC;
        break;
    case CRYPTO_ALGOFAM_CUSTOM_KDF_ANSIX963:
        ret_algo = CryptoDriver_KDF_ANSI_X9_63;
        break;
    default:
        ret_algo = CryptoDriver_KDF_RESERVED;
        break;
    }

    return ret_algo;
}

static FUNC(uint32, CRYPTO_82_HSM_CODE) get_keyElementSizeKeyExchange(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey)
{
    uint32 keyElementSize = 0xFFFFFFFFu;

    switch(Crypto_82_Hsm_configKeys[cryptoKeyId].keyType)
    {
        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR: 
        {  
            keyElementSize = (elementPrivKey->keySize / 3u) * 2u; /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
            break;
        }

        default:
        { 
            /* Do nothing */ 
            break;
        }
    }

    return keyElementSize;
}

static FUNC(ecy_hsm_Csai_KeyDerivationFunctionT, CRYPTO_82_HSM_CODE) get_keyDeriveAlgoHsm(Crypto_82_Hsm_KeyDeriveFunctionType algo)
{
    ecy_hsm_Csai_KeyDerivationFunctionT ret_algo = ecy_hsm_CSAI_KDF_RESERVED;

    switch (algo)
    {
    case CryptoDriver_KDF_PKCS5_PBKDF2:
        ret_algo = ecy_hsm_CSAI_KDF_PKCS5_PBKDF2;
        break;

    case CryptoDriver_KDF_NIST_SP800_56C_ONESTEP_AES_SHA256:
        ret_algo = ecy_hsm_CSAI_KDF_NIST_SP800_56C_ONESTEP_AES_SHA256;
        break;

    case CryptoDriver_KDF_NIST_SP800_108_AES_CMAC:
        ret_algo = ecy_hsm_CSAI_KDF_NIST_SP800_108_AES_CMAC;
        break;

    case CryptoDriver_KDF_ANSI_X9_63:
        ret_algo = ecy_hsm_CSAI_KDF_ANSI_X9_63;
        break;

    default:
        ret_algo = ecy_hsm_CSAI_KDF_RESERVED;

        break;
    }

    return ret_algo;
}

static FUNC(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType, CRYPTO_82_HSM_CODE) get_keyExchangeCalcSecretAlgo(ecy_hsm_Csai_KeyTypeT keyType, uint32* keySize)
{
    Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType ret_algo = CryptoDriver_ECDH_RESERVED;
    uint32 publicKeySize = 0u;

    if(keyType == ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR)
    {
        publicKeySize = (*keySize / 3u) * 2u; /* PRQA S 3384  #Wraparound can not occur in this case. */

        if (publicKeySize == 56u)
        {
            ret_algo = CryptoDriver_ECDH_CURVE_P_224;
        }
        else if (publicKeySize == 64u)
        {
            ret_algo = CryptoDriver_ECDH_CURVE_P_256;
        }
        else if (publicKeySize == 96u)
        {
            ret_algo = CryptoDriver_ECDH_CURVE_P_384;
        }
        else
        {
            /* Do Nothing */
        }
    }

    *keySize = publicKeySize;
    return ret_algo;
}

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) check_KeyExchangeSharedSecretSize(ecy_hsm_Csai_KeyTypeT keyType, uint32 keyPairSize, uint32 sharedSecretSize)
{
    Std_ReturnType ret = E_OK;
    uint32 publicKeySize = (keyPairSize / 3u) * 2u; /* PRQA S 3384  #Wraparound can not occur in this case. */
    /* Satisfies DN_SWS_Crypto_057 */
    if(keyType == ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR)
    {
        if ( ((publicKeySize == 56u) && (sharedSecretSize != 28u)) || ((publicKeySize == 64u) && (sharedSecretSize != 32u)) || ((publicKeySize == 96u) && (sharedSecretSize != 48u)) )
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */

static FUNC(ecy_hsm_Csai_DhAlgorithmT, CRYPTO_82_HSM_CODE) get_keyExchangeCalcSecretAlgoHsm(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType algo)
{
    ecy_hsm_Csai_DhAlgorithmT ret_algo = ecy_hsm_CSAI_DH_NUMALGORITHMS;

    switch (algo)
    {
    case CryptoDriver_ECDH_CURVE_P_224:
        ret_algo = ecy_hsm_CSAI_ECDH_CURVE_P_224;
        break;

    case CryptoDriver_ECDH_CURVE_P_256:
        ret_algo = ecy_hsm_CSAI_ECDH_CURVE_P_256;
        break;
        
    case CryptoDriver_ECDH_CURVE_P_384:
        ret_algo = ecy_hsm_CSAI_ECDH_CURVE_P_384;
        break;

    default:
        ret_algo = ecy_hsm_CSAI_DH_NUMALGORITHMS;
        break;
    }

    return ret_algo;
}

static FUNC(uint32, CRYPTO_82_HSM_CODE) get_keyGenerateKeySize(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC) elementKeyGenerate
)
{
    uint32 size;
    ecy_hsm_Csai_KeyTypeT type = Crypto_82_Hsm_configKeys[cryptoKeyId].keyType;
    uint32 keySize = elementKeyGenerate.keySize;

    switch (type)
    {
    case ecy_hsm_CSAI_KEYTYPE_SYMMETRIC:
        size = keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
        break;

    case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR:
        size = (keySize / 3u) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE; /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
        break;

    case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR:
        size = (keySize / 2u) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE; /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
        break; 

    case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR:
        size = ((keySize - 4u) / 2u) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE; /* PRQA S 3383,3384 #Wraparound can not occur in this case if a correct configuration is provided. */
        break;  
         
    default:
        size = 0u;
        break;
    }

    return size;
}

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(Crypto_82_Hsm_csaiPersistentOrRamKeyType, CRYPTO_82_HSM_CODE) csaiPersistentOrRamKeyType( 
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementIndex 
)
{
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) keyType = CRYPTO_82_HSM_KEYTYPE_UNDEFINED;

    if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT)
    {
        if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyFormat != CRYPTO_KE_FORMAT_BIN_SHEKEYS)
        {
            keyType = CRYPTO_82_HSM_KEYTYPE_NVM;
        }
        else
        {
            if (Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId < (ecy_hsm_Csai_KeyIdT)SHE_RAM_KEY)
            {
                keyType = CRYPTO_82_HSM_KEYTYPE_SHE;
            }
            else if (Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId > (ecy_hsm_Csai_KeyIdT)SHE_RAM_KEY)
            {
                keyType = CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED;
            }
            else
            {
                /* Do nothing. In this case the key type remains undefined. The SHE RAM key should not have the material key element format as SHEKEYS */
            }
        }
    }
    else if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT)
    {
        if (isSheRamKey(arCryptoKeyId))
        {
            keyType = CRYPTO_82_HSM_KEYTYPE_SHE_RAM;
        }
        else
        {
            keyType = CRYPTO_82_HSM_KEYTYPE_RAM;
        }
    }
    else
    {
        /* Do nothing. In this case the key type remains undefined. E.g keyStorageType = CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT*/
    }

    return keyType;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyElementSet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElemIndex,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(Crypto_82_Hsm_KeyElementStorageType, AUTOMATIC) keyStorageType,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) keyDataPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyLength
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, keyElemIndex);
    
    if (retCsaiPersistentOrRamKeyType != CRYPTO_82_HSM_KEYTYPE_UNDEFINED)
    {
        Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr = keyPtr;
        Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyLength = keyLength;
        Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
        Crypto_82_Hsm_KeyElementValidity[keyElemIndex] = FALSE;
    }
    /* TODO: Check CycurHSM API usage in the case of "data buffer" key elements */
    else if (keyStorageType == CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT)
    {
        /*if PROOF type of key element, return NOK; */
        if ((Crypto_82_Hsm_configKeyElements[keyElemIndex].keyElementId == CRYPTO_KE_MAC_PROOF) || (Crypto_82_Hsm_configKeyElements[keyElemIndex].keyElementId == CRYPTO_KE_CIPHER_PROOF))
        {
            ret = E_NOT_OK;
        }
        else if (keyDataPtr != NULL_PTR)
        {
            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

            (void)Crypto_82_Hsm_Memcpy_s(keyDataPtr, keyLength, keyPtr, keyLength, keyLength);
            Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
            Crypto_82_Hsm_KeyElementValidity[keyElemIndex] = TRUE;
        

            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    else
    {
        ret = E_NOT_OK;
    }

    return ret;
}

static FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_InjectKey(VAR(uint32,AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) objectId)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;

    assignKeyData(&Crypto_82_Hsm_keyData[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], Crypto_82_Hsm_configKeys[cryptoKeyId].keyType, Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr, Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyLength);

    csai_err = ecy_hsm_Csai_InjectKey(Crypto_82_Hsm_driverObjects[objectId ].sessionHandle, (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY, &Crypto_82_Hsm_keyData[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], Crypto_82_Hsm_configKeys[cryptoKeyId].keyProperties,
                                                      &(Crypto_82_Hsm_driverObjects[objectId].keyHandle), &(Crypto_82_Hsm_driverObjects[objectId].jobHandle));
    
    return csai_err;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_WriteToNvm(VAR(uint32, AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) objectId, VAR(uint32, AUTOMATIC) keyElemIndex)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) keyHandle = Crypto_82_Hsm_runtimeKeys[keyElemIndex].keyHandle;
    
    csai_err = ecy_hsm_Csai_WriteKeyToNvmKeyStore(Crypto_82_Hsm_driverObjects[objectId].sessionHandle, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], keyHandle, Crypto_82_Hsm_configKeys[cryptoKeyId].HsmKeyId,
                                                  &(Crypto_82_Hsm_driverObjects[objectId].jobHandle));

    return csai_err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeySetValid(VAR(uint32,AUTOMATIC) cryptoKeyId)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;    
#endif    
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    
    if (Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid != TRUE)
    {
        VAR(uint32, AUTOMATIC) keyMaterialElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
        VAR(uint32, AUTOMATIC) proof_keyElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
        P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) proof_element;
        P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) mac_proof_element;

        getKeyMaterialElementIndex(&keyMaterialElemIndex, cryptoKeyId);

        Std_ReturnType pollStatus = E_NOT_OK;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
        if (keyMaterialElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            ret = E_NOT_OK;
            detErr = CRYPTO_E_PARAM_VALUE;
        }
        else 
#endif      
        {
            VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, keyMaterialElemIndex);

            if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM))
            {
                if (Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr != NULL_PTR) /*differentiate between keyelementset and keygenerate*/
                {
                    csai_err = Crypto_82_Hsm_InjectKey(cryptoKeyId, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);

                    if (csai_err != ecy_hsm_CSAI_SUCCESS)
                    {
                        ret = E_NOT_OK;
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
                    }
                    else
                    {
                        do
                        {
                            pollStatus = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle, CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);
                        } while (pollStatus == CRYPTO_E_BUSY);

                        Crypto_82_Hsm_Process_Inject_Poll_Result(cryptoKeyId, pollStatus, keyMaterialElemIndex, retCsaiPersistentOrRamKeyType, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);

                        if (pollStatus != E_OK)
                        {
                            ret = E_NOT_OK;
                        }
                    }
                }
            }

            if ((Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] != TRUE) && (ret != E_NOT_OK) && (retCsaiPersistentOrRamKeyType != CRYPTO_82_HSM_KEYTYPE_RAM)) /*injected/generated ram key element will be valid at this point*/
            {
                P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle = &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle;

                if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM)
                {
                    csai_err = Crypto_82_Hsm_WriteToNvm(cryptoKeyId, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, keyMaterialElemIndex);
                }
                else
                {
                    csai_err = SheSerializeKeySetValid(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, retCsaiPersistentOrRamKeyType, cryptoKeyId);
                }
               
                if (csai_err != ecy_hsm_CSAI_SUCCESS)
                {
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);

#if (CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON)
                    csai_err = loadSheKey(cryptoKeyId, keyMaterialElemIndex, sessionHandle, jobHandle);
#endif

                    ret = E_NOT_OK;
                }
                else
                {
                    do
                    {
                        csai_err = ecy_hsm_Csai_PollHandle(*jobHandle);
                    }
                    while(ecy_hsm_CSAI_FC_PENDING == csai_err);
                    
                    if (csai_err == ecy_hsm_CSAI_SUCCESS)
                    {
                        /** For SHE keys */
                        if( (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) || (retCsaiPersistentOrRamKeyType== CRYPTO_82_HSM_KEYTYPE_SHE_RAM) )
                        {
                            if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED))
                            {
                                mac_proof_element = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_MAC_PROOF, &proof_keyElemIndex);
            
                                if (proof_keyElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
                                {
                                    proof_element = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_CIPHER_PROOF, &proof_keyElemIndex);
                                }

                                else
                                {
                                    proof_element = mac_proof_element;
                                }
                            }

                            /* proof_keyElemIndex must be valid only for SHE keys or extended SHE keys*/
                            if ( (proof_keyElemIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM) )
                            {
                                csai_err = ecy_hsm_Csai_LoadKey(sessionHandle, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT], Crypto_82_Hsm_configKeys[cryptoKeyId].HsmKeyId,
                                                                Crypto_82_Hsm_configKeys[cryptoKeyId].keyType,
                                                                &Crypto_82_Hsm_runtimeKeys[keyMaterialElemIndex].keyHandle, jobHandle);
                                if (csai_err == ecy_hsm_CSAI_SUCCESS)
                                {
                                    do
                                    {
                                        csai_err = ecy_hsm_Csai_PollHandle(*jobHandle);
                                    } while (ecy_hsm_CSAI_FC_PENDING == csai_err);
                                }

                                if (csai_err != ecy_hsm_CSAI_SUCCESS)
                                {
                                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
                                }
                            }
                            else
                            {
                                csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
                            }
                        }
                    }
                    else
                    {
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);

#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )
                        csai_err = loadSheKey(cryptoKeyId, keyMaterialElemIndex, sessionHandle, jobHandle);
#endif

                        ret = E_NOT_OK;
                    }

                    if ( (csai_err == ecy_hsm_CSAI_SUCCESS) && (ret != E_NOT_OK) )
                    {
                        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

                        if(retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE)
                        {
                            /* Starting address of sheM4 buffer is used here but data is copied to both sheM4 and sheM5 buffers. */
                            (void)Crypto_82_Hsm_Memcpy_s(proof_element->keyDataPtr, SHE_M4_M5_SIZE, Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sheM4, SHE_M4_M5_SIZE, SHE_M4_M5_SIZE);
                            Crypto_82_Hsm_KeyElementValidity[proof_keyElemIndex] = TRUE;
                        }
                        else if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED)
                        {
                            /* Starting address of sheM4 buffer is used here but data is copied to both sheM4 and sheM5 buffers. */
                            (void)Crypto_82_Hsm_Memcpy_s(proof_element->keyDataPtr, SHE_M4_M5_SIZE, Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sheM4, SHE_M4_M5_SIZE, SHE_M4_M5_SIZE);
                            Crypto_82_Hsm_KeyElementValidity[proof_keyElemIndex] = TRUE;
                        }
                        else
                        {
                            /* Do nothing in case keyIdT == SHE_RAM_KEY or any other key id type*/
                        }

                        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();
                    }
                    else
                    {
                        ret = E_NOT_OK;
					}
                }

                if (ret == E_OK)
                {
                    Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] = TRUE;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                    Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE)], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */

                    /* code reachable only for persistent key elements -> set the dirty flag */

                    Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(cryptoKeyId);

#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
                }
                else
                {
#if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )

#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_OFF )
                    Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE)], cryptoKeyId);
                    Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(cryptoKeyId);
#else
                    if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM)
                    {
                        Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE)], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
                        Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(cryptoKeyId);                        
                    }
#endif                
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */ 



#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )

                    if (csai_err == ecy_hsm_CSAI_SUCCESS)
                    {    
                        Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] = TRUE;
                    }                               
#endif
                }
            }
            else
            {
            /* Do nothing */
            }                

            /* Set key to valid if all key elements are valid */
            Crypto_82_Hsm_UpdateKeyValidity(cryptoKeyId);

            Crypto_82_Hsm_clearbuffers_KeySetValid(cryptoKeyId, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);
            }
    }
    else
    {
        ret = E_OK;
    }
    
#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */    

    if (Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid != TRUE)
    {
        ret = E_NOT_OK;
    }

    return ret;
}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_Inject_Poll_Result(VAR(uint32,AUTOMATIC) cryptoKeyId, Std_ReturnType pollStatus, VAR(uint32, AUTOMATIC) keyMaterialElemIndex, VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) CsaiPersistentOrRamKeyType, VAR(uint32, AUTOMATIC) objectId)
{   
    if (pollStatus == E_OK)
    {
        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

        Crypto_82_Hsm_runtimeKeys[keyMaterialElemIndex].keyHandle = Crypto_82_Hsm_driverObjects[objectId].keyHandle;     
        
        if(CsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM)
        {
            Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] = TRUE;

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE)], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case.*/
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
        }
        else
        {
            Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] = FALSE;
        }

        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();
    }

    /* Clear Crypto_82_Hsm_keyData data                                    *
     * Note: data "u" is union. Symmetric data structure is used for RESET */
    Crypto_82_Hsm_keyData[objectId].type = ecy_hsm_CSAI_KEYTYPE_RESERVED;
    Crypto_82_Hsm_keyData[objectId].u.sym.keySize = (ecy_hsm_Csai_KeySizeT)0u;
    Crypto_82_Hsm_keyData[objectId].u.sym.key = NULL_PTR;
    Crypto_82_Hsm_keyData[objectId].u.sym.length = 0u;
}

FUNC(const Crypto_82_Hsm_ConfigKeyElementType*, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_findKeyElement(
    VAR(uint32, AUTOMATIC) keyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2VAR(uint32,  AUTOMATIC, AUTOMATIC) keyElementIndex /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(uint32,  AUTOMATIC) noOfKeyElements;
    VAR(uint32, AUTOMATIC) keyElemStartIndex;

    const Crypto_82_Hsm_ConfigKeyElementType* element = NULL_PTR;

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

    if (keyId < CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        noOfKeyElements = Crypto_82_Hsm_configKeys[keyId].numberOfKeyElements;
        keyElemStartIndex = Crypto_82_Hsm_keyIdToKeyElementIdMap[keyId];

        for (uint32 keyIndex = keyElemStartIndex; keyIndex < keyElemStartIndex + noOfKeyElements; keyIndex++) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
        {
            if (keyIndex < CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS)
            {
                if (Crypto_82_Hsm_configKeyElements[keyIndex].keyElementId == keyElementId)
                {
                    if (keyElementIndex != NULL_PTR)
                    {
                        *keyElementIndex = keyIndex;
                        element = &Crypto_82_Hsm_configKeyElements[*keyElementIndex];
                    }
                }
            }
        }
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

    return element;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyExchangeCalcSecret(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
)
{
    Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[driverObject->objectID] = CRYPTO_KEY_EXCHANGE_DHINIT_REQUIRED;
    VAR(Std_ReturnType, AUTOMATIC) ret_val = E_OK;
    VAR(uint32, AUTOMATIC) privKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) sharedSecretKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSharedSecret = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE, &sharedSecretKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &privKeyElementIndex); 

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 */
    if (job->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00142 */
    else if (job->jobPrimitiveInputOutput.inputLength == 0x00u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_053 */
    else if (sharedSecretKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_053 */
    else if (privKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    else if (check_KeyExchangeSharedSecretSize(Crypto_82_Hsm_configKeys[job->cryptoKeyId].keyType, Crypto_82_Hsm_configKeyElements[privKeyElementIndex].keySize, Crypto_82_Hsm_configKeyElements[sharedSecretKeyElementIndex].keySize) == E_NOT_OK)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }    
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        /* Satisfies SWS_Crypto_91003 */
        if (Crypto_82_Hsm_KeyElementValidity[privKeyElementIndex] != TRUE)
        {
            ret_val = CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            /* Do nothing */
        }

        if (ret_val == E_OK)
        {
            VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = driverObject->sessionHandle;
            VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiError;
            VAR(uint32, AUTOMATIC) keySize = Crypto_82_Hsm_configKeyElements[privKeyElementIndex].keySize;
            VAR(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyPairType = Crypto_82_Hsm_configKeys[job->cryptoKeyId].keyType;
            VAR(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType, AUTOMATIC) keyExchangeAlgo = get_keyExchangeCalcSecretAlgo(keyPairType, &keySize); 
 
            csaiError = ecy_hsm_Csai_DhInit(sessionHandle, 
                                            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[driverObject->objectID],
                                            get_keyExchangeCalcSecretAlgoHsm(keyExchangeAlgo),
                                            Crypto_82_Hsm_runtimeKeys[privKeyElementIndex].keyHandle,
                                            keyExchangePublicKeyDataBuffer,
                                            keySize,
                                            &keyExchangePublicValueLength,
                                            &Crypto_82_Hsm_driverObjects[driverObject->objectID].jobHandle);

            if (csaiError != ecy_hsm_CSAI_SUCCESS)
            {
                ret_val = E_NOT_OK;
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, csaiError);
            }
            else
            {
                Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[driverObject->objectID] = CRYPTO_KEY_EXCHANGE_DHCOMPUTE_EXT_REQUIRED;
            }
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)

    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );
    }

#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret_val;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyExchangeCalcPubVal(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val = E_OK;
    VAR (uint32, AUTOMATIC) privKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) cryptoKeyId = job->cryptoKeyId;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &privKeyElementIndex);

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;
    
    /* Satisafies SWS_Crypto_00070 */
    if (job->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00070 */
    else if (job->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00142 */
    else if (*(job->jobPrimitiveInputOutput.outputLengthPtr) == 0x00u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_053 */
    else if (privKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {        
        uint32 keyElementSize = get_keyElementSizeKeyExchange(cryptoKeyId, elementPrivKey);

        /* Satisfies SWS_Crypto_91003 */
        if (Crypto_82_Hsm_KeyElementValidity[privKeyElementIndex] != TRUE)
        {
            ret_val = CRYPTO_E_KEY_EMPTY;
        }
        else if (*(job->jobPrimitiveInputOutput.outputLengthPtr) < keyElementSize)
        {
            ret_val = E_NOT_OK; /* Satisfies SWS_Crypto_00195 (Deviated into DV_Crypto_006) */
        }
        else
        {
            ret_val = Crypto_82_Hsm_Process_KeyElementGet(cryptoKeyId, 
                                                          driverObject->objectID, 
                                                          elementPrivKey, 
                                                          privKeyElementIndex, 
                                                          &(Crypto_82_Hsm_driverObjects[driverObject->objectID].jobHandle), 
                                                          job->jobPrimitiveInputOutput.outputPtr, 
                                                          job->jobPrimitiveInputOutput.outputLengthPtr,
                                                          CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
                                                          job->jobId);
        }
    }
    
#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)

    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );
    }

#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret_val;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyDerive(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
)
{  
    VAR (uint32, AUTOMATIC) algoKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) saltKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) iterationsKeyElementIndex   = CRYPTO_82_HSM_INVALID_KEY_INDEX;   
    VAR (uint32, AUTOMATIC) targetKeyElementIndex       = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) passwordKeyElementIndex     = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) parentKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementAlgo = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ALGORITHM, &algoKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementIterations = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ITERATIONS, &iterationsKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSalt = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_SALT, &saltKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPass = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_PASSWORD, &passwordKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementParentKey = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVE_CUSTOM_PARENTKEY, &parentKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementTarget = Crypto_82_Hsm_findKeyElement(job->targetCryptoKeyId, CRYPTO_KEYDERIVE_TARGETKEYELEMENT_ID, &targetKeyElementIndex);

    ret = Crypto_82_Hsm_Process_KeyDerive(job->cryptoKeyId, job->targetCryptoKeyId, driverObject, targetKeyElementIndex, passwordKeyElementIndex, algoKeyElementIndex, saltKeyElementIndex, iterationsKeyElementIndex, parentKeyElementIndex, &detErr);

    if (ret == E_NOT_OK)
    {
        Crypto_82_Hsm_clearbuffers_KeyDerive(driverObject->objectID, job->cryptoKeyId, elementIterations, iterationsKeyElementIndex, elementSalt, saltKeyElementIndex, elementPass, passwordKeyElementIndex);
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}



FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeyGenerate(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_SUCCESS;
    VAR(uint32, AUTOMATIC) cryptoKeyId = job->cryptoKeyId;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00094 */
    if(Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
    }
    /* Satisfies SWS_Crypto_00095 */
    else if(cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        /* Satisfies SWS_Crypto_00165 */
        CONST(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyType = Crypto_82_Hsm_configKeys[cryptoKeyId].keyType;
        CONST(uint32, AUTOMATIC) keyProperties = Crypto_82_Hsm_configKeys[cryptoKeyId].keyProperties;     
        VAR(uint32, AUTOMATIC) keySize = 0u;

        VAR(uint32, AUTOMATIC) indexKeyGenerate = CRYPTO_82_HSM_INVALID_KEY_INDEX;

        /* The keyMaterialElement with the keyElementId equal to "CRYPTO_KE_KEYEXCHANGE_PRIVKEY" used for keyExchange */
        P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementKeyGenerate = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &indexKeyGenerate);

        if (indexKeyGenerate == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            elementKeyGenerate = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYGENERATE_KEY, &indexKeyGenerate);

            if (indexKeyGenerate != CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
                keySize = get_keyGenerateKeySize(cryptoKeyId, *elementKeyGenerate);
            }
        }
        else
        {
            keySize = get_keyGenerateKeySize(cryptoKeyId, *elementKeyGenerate);
        }

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
        if (indexKeyGenerate == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            detErr = CRYPTO_E_PARAM_VALUE;
        }
        else
#endif     
       {
            VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, indexKeyGenerate);

            if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM))
            {
                csai_err = ecy_hsm_Csai_GenerateKey(driverObject->sessionHandle, ecy_hsm_CSAI_PRIO_LOW, keyType,
                                                (ecy_hsm_Csai_KeySizeT)keySize, keyProperties, &driverObject->keyHandle,
                                                &driverObject->jobHandle);

                if(ecy_hsm_CSAI_SUCCESS == csai_err)
                {
                    Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
                    Crypto_82_Hsm_KeyElementValidity[indexKeyGenerate %  CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS] = FALSE;
                    ret = E_OK;
                }
                else
                {
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, csai_err);
                }
            }
        }      
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}


FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Job_KeySetValid(
    CONSTP2CONST(Crypto_JobType, CRYPTO_82_HSM_CONST, CRYPTO_82_HSM_CONST) job,
    VAR(uint32, AUTOMATIC) objectId)
{
    /* TODO: Investigate how DNJP wants key status (valid, invalid, etc.) */
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_SUCCESS;
    VAR(uint32, AUTOMATIC) cryptoKeyId = job->cryptoKeyId;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto 00196 */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto 00197 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        if (Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid != TRUE)
        {
            VAR(uint32, AUTOMATIC) keyMaterialElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
            
            getKeyMaterialElementIndex(&keyMaterialElemIndex, cryptoKeyId);

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
            if (keyMaterialElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
                ret = E_NOT_OK;
                detErr = CRYPTO_E_PARAM_VALUE;
            }
            else
#endif
            {
                VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, keyMaterialElemIndex);

                if ((Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] != TRUE))
                {
                    if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM))
                    {
                        if (Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr != NULL_PTR) /*differentiate between keyelementset and keygenerate*/
                        {
                            csai_err = Crypto_82_Hsm_InjectKey(cryptoKeyId, objectId);

                            if (csai_err == ecy_hsm_CSAI_SUCCESS)
                            {
                                Crypto_82_Hsm_KeySetValid_OperationState[objectId] = CRYPTO_KEY_SET_VALID_INJECT;
                            }
                        }
                        else
                        {
                            if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM)
                            {
                                csai_err = Crypto_82_Hsm_WriteToNvm(cryptoKeyId, objectId, keyMaterialElemIndex);

                                if (csai_err == ecy_hsm_CSAI_SUCCESS)
                                {
                                    Crypto_82_Hsm_KeySetValid_OperationState[objectId] = CRYPTO_KEY_SET_VALID_WRITE_TO_NVM;
                                }                               
                            }                            
                        }
                    }
                    else
                    {
                        csai_err = SheSerializeKeySetValid(objectId, retCsaiPersistentOrRamKeyType, cryptoKeyId);
                    }                    

                    if (csai_err != ecy_hsm_CSAI_SUCCESS)
                    {
                        if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM))
                        {
#if (CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON)
                            /*If reload she key feature is active, return E_OK and reload previous she key from main function*/

                            Crypto_82_Hsm_SHE_loadKey[objectId].loadKeyOperationRequired = TRUE;
                            Crypto_82_Hsm_SHE_loadKey[objectId].keyElement = keyMaterialElemIndex;
                            Crypto_82_Hsm_SHE_loadKey[objectId].cryptoKeyId = cryptoKeyId;
                            Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed = TRUE;
#else
                            ret = E_NOT_OK;
                            Crypto_82_Hsm_clearbuffers_KeySetValid(cryptoKeyId, objectId);
#endif /*( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )*/
                        }
                        else
                        {
                            ret = E_NOT_OK;
                            Crypto_82_Hsm_KeySetValid_OperationState[objectId] = CRYPTO_KEY_SET_VALID_NO_OPERATION;
                        }
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, csai_err);
                    }
                    else
                    {
                        if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM))
                        {
                            Crypto_82_Hsm_SHE_loadKey[objectId].loadKeyOperationRequired = TRUE;
                            Crypto_82_Hsm_SHE_loadKey[objectId].keyElement = keyMaterialElemIndex;
                            Crypto_82_Hsm_SHE_loadKey[objectId].cryptoKeyId = cryptoKeyId;
                        }
                    }
                }
                else
                {
                    /* Set key to valid if all key elements are valid */
                    Crypto_82_Hsm_UpdateKeyValidity(cryptoKeyId);

                    if (Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid != TRUE)
                    {
                        ret = E_NOT_OK;
                    }
                }
            }
        }
        else
        {
            ret = E_OK;
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
             CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementSet( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) keyPtr,
    VAR(uint32, AUTOMATIC) keyLength
)
{
    /* TODO: Investigate what SWS_00039 means for this API */

    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) keyDataPtr = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    VAR(uint32, AUTOMATIC) keyElemIndex;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_VAR) element = Crypto_82_Hsm_findKeyElement(cryptoKeyId, keyElementId, &keyElemIndex);

    VAR(Crypto_82_Hsm_KeyElementStorageType, AUTOMATIC) keyStorageType;

    /* ERROR CHECKING */
#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto 00075 */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto 00076 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto 00078 */
    else if (keyPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto 00077 */
    else if ( element == NULL_PTR )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00079 */
    else if (keyLength == 0uL)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret = E_NOT_OK;
    }
    else
#endif  /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        /* This most likely will never happen, since the driver object is
         * reserved for Key Operations and all are synchronous */
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret = CRYPTO_E_BUSY;
        }
        else
        {
            keyStorageType = element->keyStorageType;
            keyDataPtr = element->keyDataPtr;

            /* Satisfies SWS_Crypto_00146 */
            if ((keyLength < element->keySize) &&
                    (Crypto_82_Hsm_configKeyElements[keyElemIndex].allowPartialAccess == FALSE))
            {
                ret = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            /* Satisfies DN_SWS_Crypto_015*/
            else if (keyLength > element->keySize)
            {
                ret = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            /* [SWS_Crypto_00223] */
            else if ((element->writeAccess == CRYPTO_82_HSM_WA_DENIED) ||
                    (element->writeAccess == CRYPTO_82_HSM_WA_INTERNAL_COPY))
            {
                ret = CRYPTO_E_KEY_WRITE_FAIL;
            }
            else
            {
                setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

                ret = Crypto_82_Hsm_Process_KeyElementSet(cryptoKeyId, keyElemIndex, keyPtr, keyStorageType, keyDataPtr, keyLength);

                setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
            }

        }
    }
    

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_SET,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeySetValid(VAR(uint32, AUTOMATIC) cryptoKeyId) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    /* TODO: Investigate how DNJP wants key status (valid, invalid, etc.) */
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;
    /* Satisfies SWS_Crypto 00196 */
    if ( Crypto_82_Hsm_IsDriverInitialized() == FALSE )
    {
        detErr = CRYPTO_E_UNINIT;
        ret = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto 00197 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            ret = Crypto_82_Hsm_Process_KeySetValid(cryptoKeyId);

            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }        
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) objectId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element,
    VAR(uint32, AUTOMATIC) keyElemIndex,
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    uint8 serviceId, 
    uint32 jobId)
{
    Std_ReturnType ret = E_OK;
    VAR(uint32, AUTOMATIC) keyExchangeElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

    if ( (element->keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT) || (element->keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT) )
    {
        VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err;

        /* TODO: Add objectId handling */
        VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = Crypto_82_Hsm_driverObjects[objectId].sessionHandle;
        VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) keyHandle = Crypto_82_Hsm_runtimeKeys[keyElemIndex].keyHandle;                

        CONST(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyType = Crypto_82_Hsm_configKeys[cryptoKeyId].keyType;

        switch (keyType)
        {
        case ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC:
        case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR:
            keyRef_keyElementGet[objectId].type = ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC;
            keyRef_keyElementGet[objectId].u.rsapub.nLength = *resultLengthPtr - 4u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            keyRef_keyElementGet[objectId].u.rsapub.n = resultPtr;
            break;

        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC:
        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR:
            keyRef_keyElementGet[objectId].type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC;
            keyRef_keyElementGet[objectId].u.eddsapub.pubKey = resultPtr;
            keyRef_keyElementGet[objectId].u.eddsapub.pubKeyLength = *resultLengthPtr;
            break;

        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC:
        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR:
            keyRef_keyElementGet[objectId].type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC;
            keyRef_keyElementGet[objectId].u.eccpub.pubKey = resultPtr;
            keyRef_keyElementGet[objectId].u.eccpub.pubKeyLength = *resultLengthPtr;
            break;

        default:
            keyRef_keyElementGet[objectId].type = ecy_hsm_CSAI_KEYTYPE_RESERVED;
            keyRef_keyElementGet[objectId].u.eccpub.pubKey = resultPtr;
            keyRef_keyElementGet[objectId].u.eccpub.pubKeyLength = *resultLengthPtr;
            break;
        }

        csai_err = ecy_hsm_Csai_ReadPublicKey(sessionHandle, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], keyHandle, &keyRef_keyElementGet[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], jobHandle);

        if (csai_err != ecy_hsm_CSAI_SUCCESS)
        {
            ret = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(serviceId, jobId, csai_err);        
        }
    }
    else
    {
        /*element->keyStorageType == CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT*/
        
        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

        if (element->keyDataPtr == NULL_PTR)
        {
            ret = CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            (void)Crypto_82_Hsm_Memcpy_s(resultPtr, element->keySize, element->keyDataPtr, element->keySize, element->keySize);
            *resultLengthPtr = element->keySize;
        }

        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

        /*Clear key element data buffers*/
        if ((element->keyElementId == CRYPTO_KE_MAC_PROOF) || (element->keyElementId == CRYPTO_KE_CIPHER_PROOF))
        {
            (void)Crypto_82_Hsm_Memset_s(element->keyDataPtr, element->keySize, 0, element->keySize);
            Crypto_82_Hsm_KeyElementValidity[keyElemIndex] = FALSE;
        }

        (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &keyExchangeElementIndex);
        if (keyExchangeElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            if ((element->keyDataPtr != NULL_PTR) && (element->keyElementId == CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE))
            {
                (void)Crypto_82_Hsm_Memset_s(element->keyDataPtr, element->keySize, 0, element->keySize);
                Crypto_82_Hsm_KeyElementValidity[keyElemIndex] = FALSE;
                Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
            }
        }
    }

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Poll_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) objectId,
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element,
    VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC) jobHandle,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    uint8 serviceId
)
{
    VAR(Std_ReturnType, AUTOMATIC) pollStatus;

    do
    {
        pollStatus = Crypto_82_Hsm_PollJob(jobHandle, serviceId, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, objectId);
    } while (pollStatus == CRYPTO_E_BUSY);

    if (pollStatus != E_OK)
    {
        /* Do nothing. */
    }
    else if ( (Crypto_82_Hsm_configKeys[cryptoKeyId].keyType == ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC) || (Crypto_82_Hsm_configKeys[cryptoKeyId].keyType == ecy_hsm_CSAI_KEYTYPE_RSA_PAIR) )
    {
        (void)Crypto_82_Hsm_Memcpy_s(&resultPtr[*resultLengthPtr - 4u], 4u, &keyRef_keyElementGet[objectId].u.rsapair.e, 4u, 4u); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
    }
    else
    {
        /* Do nothing */
    }

    keyRef_keyElementGet[objectId].type = ecy_hsm_CSAI_KEYTYPE_RESERVED;
    keyRef_keyElementGet[objectId].u.sym.keySize = (ecy_hsm_Csai_KeySizeT)0u;
    keyRef_keyElementGet[objectId].u.sym.key = NULL_PTR;
    keyRef_keyElementGet[objectId].u.sym.length = 0u;

    return pollStatus;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementGet( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) resultLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    VAR(uint32, AUTOMATIC) keyElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) keyMaterialElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element = Crypto_82_Hsm_findKeyElement(cryptoKeyId, keyElementId, &keyElemIndex);
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = CRYPTO_82_HSM_KEYTYPE_UNDEFINED;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
    }
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else if (keyElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else if (resultPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }
    else if (resultLengthPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }
    else if (*resultLengthPtr == 0u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
    }
    else
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            getKeyMaterialElementIndex(&keyMaterialElemIndex, cryptoKeyId);

            if (keyMaterialElemIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
                retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, keyMaterialElemIndex);
            }

            uint32 keyElementSize = 0u;

            switch(Crypto_82_Hsm_configKeys[cryptoKeyId].keyType)
            {
                case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR: 
                {  
                    keyElementSize = ((element->keySize - 4u) / 2u) + 4u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
                    break;
                }

                case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR: 
                {  
                    keyElementSize = (element->keySize / 3u) * 2u; /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
                    break;
                }

                case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR: 
                {  
                    keyElementSize = element->keySize/ 2u;
                    break;
                }

                default:
                {  
                    keyElementSize = element->keySize;
                    break;
                }
            }

            if(*resultLengthPtr < keyElementSize)
            {
                ret = E_NOT_OK;
            }
            else if ((element->readAccess == CRYPTO_82_HSM_RA_DENIED) || (element->readAccess == CRYPTO_82_HSM_RA_INTERNAL_COPY))
            {
                ret = CRYPTO_E_KEY_READ_FAIL;
            }
            else if (Crypto_82_Hsm_KeyElementValidity[keyElemIndex] != TRUE)
            {
                ret = CRYPTO_E_KEY_EMPTY;
            }
            else if ( ( (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) ) && (Crypto_82_Hsm_KeyElementValidity[keyMaterialElemIndex] != TRUE) )
            {
                ret = CRYPTO_E_KEY_EMPTY; /* Satisfies DN_SWS_CRYPTO_055 */
            }
            else 
            {
                CONST(Crypto_82_Hsm_KeyElementStorageType, AUTOMATIC) keyStorage = element->keyStorageType;
                
                /* Satisfies SWS_Crypto_00092 */
                if(*resultLengthPtr > keyElementSize)
                {
                    *resultLengthPtr = keyElementSize;
                }
                
                P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

                ret = Crypto_82_Hsm_Process_KeyElementGet(cryptoKeyId, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, element, keyElemIndex, jobHandle, resultPtr, resultLengthPtr, CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_GET, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE);

                if ( (ret == E_OK) && (keyStorage != CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT) )
                {
                    ret = Crypto_82_Hsm_Poll_KeyElementGet(cryptoKeyId, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, element, *jobHandle, resultPtr, resultLengthPtr, CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_GET);
                }
            }

            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }          
       

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_GET,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

#if (CRYPTO_82_HSM_RUNTIME_ERROR_REPORT == STD_ON)
    if (ret == CRYPTO_E_KEY_READ_FAIL)
    {
        (void)Det_ReportRuntimeError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_GET,
            CRYPTO_E_RE_KEY_READ_FAIL
        );
    }
    else
    {
        /* Do nothing */
    }

#endif /* (CRYPTO_82_HSM_RUNTIME_ERROR_REPORT == STD_ON) */


    return ret;
}

#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )
static FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) loadSheKey(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyMaterialElemIndex,
    VAR(uint32, AUTOMATIC) sessionHandle,
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_FLAG_ERROR;
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, keyMaterialElemIndex);
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
    uint8 loadkeytriggered = FALSE;
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

    /** For SHE keys */
    if((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM))
    {

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
        Crypto_82_Hsm_KeyStatusType densoKeyStatus;
        VAR(uint8, AUTOMATIC) dataSlotByte = keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) + getKeyStatusSlotByteNumber(cryptoKeyId)]; /* PRQA S 3384  #Wraparound can not occur in this case. */
        densoKeyStatus = (Crypto_82_Hsm_KeyStatusType)((uint8)(dataSlotByte >> getKeyStatusSlotByteStartBitNumber(cryptoKeyId) & 0x03u)); /* PRQA S 3384  #Wraparound can not occur in this case. */

        /* If denso key validity is CRYPTO_82_HSM_KEY_VALID, reload the she key into session context and keep it valid. */
        if (densoKeyStatus == CRYPTO_82_HSM_KEY_VALID)
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
        {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            loadkeytriggered = TRUE;
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

            csai_err = ecy_hsm_Csai_LoadKey(sessionHandle, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT], Crypto_82_Hsm_configKeys[cryptoKeyId].HsmKeyId,
                                            Crypto_82_Hsm_configKeys[cryptoKeyId].keyType, 
                                            &Crypto_82_Hsm_runtimeKeys[keyMaterialElemIndex].keyHandle, jobHandle);
            if (csai_err == ecy_hsm_CSAI_SUCCESS)
            {
                do
                {
                    csai_err = ecy_hsm_Csai_PollHandle(*jobHandle);
                }
                while(ecy_hsm_CSAI_FC_PENDING == csai_err);
            }
        }

        if(csai_err != ecy_hsm_CSAI_SUCCESS)
        {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            if (loadkeytriggered == TRUE)
            {
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)) % KEY_STATUS_DATA_ARRAY_SIZE], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */

                /* Set the dirty flag ->all she keys are persistent */
                Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(cryptoKeyId);
            }
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
        }
    }

    return csai_err;
}
#endif /* (CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON) */

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Process_KeyDerive(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) elementTargetIndex,
    VAR(uint32, AUTOMATIC) elementPassIndex,
    VAR(uint32, AUTOMATIC) algoKeyElementIndex,
    VAR(uint32, AUTOMATIC) elementSaltIndex,
    VAR(uint32, AUTOMATIC) elementIterationsIndex,
    VAR(uint32, AUTOMATIC) elementParentKeyIndex,
    P2VAR(uint8, CRYPTO_82_HSM_VAR, AUTOMATIC) detErr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(uint32, AUTOMATIC) iterations; 
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) keyHandle = ecy_hsm_CSAI_NO_KEY_HANDLE;
    VAR(Crypto_82_Hsm_KeyDeriveFunctionType, AUTOMATIC) keyDeriveAlgo = CryptoDriver_KDF_RESERVED;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    if (elementTargetIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        ret = E_NOT_OK;
        *detErr = CRYPTO_E_PARAM_VALUE;
    }
    else if (algoKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        ret = E_NOT_OK;
        *detErr = CRYPTO_E_PARAM_VALUE;
    }
    else
#endif
    {
        keyDeriveAlgo = get_keyDeriveAlgo(Crypto_82_Hsm_configKeyElements[algoKeyElementIndex].keyDataPtr[0]);

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
        if (keyDeriveAlgo == CryptoDriver_KDF_RESERVED)
        {
            ret = E_NOT_OK;
            *detErr = CRYPTO_E_PARAM_VALUE;
        }
        else
#endif
        {
            if ((keyDeriveAlgo == CryptoDriver_KDF_NIST_SP800_56C_ONESTEP_AES_SHA256) || (keyDeriveAlgo == CryptoDriver_KDF_ANSI_X9_63) || (keyDeriveAlgo == CryptoDriver_KDF_NIST_SP800_108_AES_CMAC))
            {
                if (elementParentKeyIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    keyHandle = INVALID_KEY_HANDLE_VALUE;
                }
                else
                {
                    keyHandle = Crypto_82_Hsm_runtimeKeys[elementParentKeyIndex].keyHandle;
                }
            }
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    if (ret == E_OK)
    {
#endif
        VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = driverObject->sessionHandle;
        VAR(uint32, AUTOMATIC) keySize = Crypto_82_Hsm_configKeyElements[elementTargetIndex].keySize * 8uL; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
   
        if (elementPassIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            Crypto_82_Hsm_passParam[driverObject->objectID].pin = NULL_PTR;
            Crypto_82_Hsm_passParam[driverObject->objectID].length = 0;
        }
        else
        {
            Crypto_82_Hsm_passParam[driverObject->objectID].pin = Crypto_82_Hsm_configKeyElements[elementPassIndex].keyDataPtr;
            Crypto_82_Hsm_passParam[driverObject->objectID].length = Crypto_82_Hsm_configKeyElements[elementPassIndex].keySize;
        }

        /* Optional element. */
        if (elementSaltIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            Crypto_82_Hsm_saltParam[driverObject->objectID].pin = NULL_PTR;
            Crypto_82_Hsm_saltParam[driverObject->objectID].length = 0;
        }
        else
        {
            Crypto_82_Hsm_saltParam[driverObject->objectID].pin = Crypto_82_Hsm_configKeyElements[elementSaltIndex].keyDataPtr;
            Crypto_82_Hsm_saltParam[driverObject->objectID].length = Crypto_82_Hsm_configKeyElements[elementSaltIndex].keySize;
        }

        /* Optional element. Default value is 0.*/
        if ((elementIterationsIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX) && (Crypto_82_Hsm_configKeyElements[elementIterationsIndex].keyDataPtr != NULL_PTR))
        {
            iterations = ((uint32)Crypto_82_Hsm_configKeyElements[elementIterationsIndex].keyDataPtr[0] << 24) + ((uint32)Crypto_82_Hsm_configKeyElements[elementIterationsIndex].keyDataPtr[1] << 16) + ((uint32)Crypto_82_Hsm_configKeyElements[elementIterationsIndex].keyDataPtr[2] << 8) + (uint32)Crypto_82_Hsm_configKeyElements[elementIterationsIndex].keyDataPtr[3];/* PRQA S 3384, 3383  #The QAC tool is not correctly evaluating the expression, wraparound cannot occur in this case. */
        }
        else
        {
            iterations = 0;
        }

        csai_err = ecy_hsm_Csai_DeriveKey (
            sessionHandle ,                                                                                                                                /* ecy_hsm_Csai_SessionHandleT          hSession,       */
            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],           /* ecy_hsm_Csai_JobPriorityT            priority,       */
            get_keyDeriveAlgoHsm(keyDeriveAlgo),                                                                                                           /* ecy_hsm_Csai_KeyDerivationFunctionT  kdf,            */
            keyHandle,                                                                                                                                     /* ecy_hsm_Csai_KeyHandleT              hParentKey,     */
            &Crypto_82_Hsm_passParam[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],                                                   /* ecy_hsm_Csai_PinRefT *               pPasswd,        */
            &Crypto_82_Hsm_saltParam[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],                                                   /* ecy_hsm_Csai_PinRefT *               pSalt,          */
            iterations,                                                                                                                                    /* uint32                               iterationCount  */
            (ecy_hsm_Csai_KeySizeT)keySize,                                                                                                                /* ecy_hsm_Csai_KeySizeT                keySize         */
            &(driverObject->keyHandle),                                                                                                                    /* ecy_hsm_Csai_KeyHandleT *            phDerivedKey,   */
            &(driverObject->jobHandle)                                                                                                                     /* ecy_hsm_Csai_JobHandleT *            phJob           */
        );

        if (csai_err == ecy_hsm_CSAI_SUCCESS)
        {
            Crypto_82_Hsm_KeyState[targetCryptoKeyId].keyValid = FALSE;
            Crypto_82_Hsm_KeyElementValidity[elementTargetIndex] = FALSE;

            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;

            if (driverObject->objectID != CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT)
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, csai_err);
            }
            else
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_DERIVE, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
            }
        }
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)        
    }
#endif

    return ret;
}
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_clearbuffers_KeySetValid( VAR(uint32, AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) objectID)
{
    /* Clean buffers*/
    Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyDataPtr = NULL_PTR;
    Crypto_82_Hsm_KeyState[cryptoKeyId].KeyElementSetKeyLength = 0u;

    (void)Crypto_82_Hsm_Memset_s(&Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectID % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], SHE_M4_M5_SIZE, 0u, SHE_M4_M5_SIZE);
    
    Crypto_82_Hsm_KeySetValid_OperationState[objectID] = CRYPTO_KEY_SET_VALID_NO_OPERATION;
}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_clearbuffers_KeyDerive(
    VAR(uint32, AUTOMATIC) objectID, 
    VAR(uint32, AUTOMATIC) cryptoKeyId, 
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementIterations, 
    VAR(uint32, AUTOMATIC) iterationsKeyElementIndex, 
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSalt, 
    VAR(uint32, AUTOMATIC) saltKeyElementIndex, 
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPass, 
    VAR(uint32, AUTOMATIC) passwordKeyElementIndex)
{
    /* Clear Crypto_82_Hsm_saltParam and Crypto_82_Hsm_passParam internal data */
    if (Crypto_82_Hsm_saltParam[objectID].pin != NULL_PTR)
    {
        (void)Crypto_82_Hsm_Memset_s(Crypto_82_Hsm_saltParam[objectID].pin, Crypto_82_Hsm_saltParam[objectID].length, 0, Crypto_82_Hsm_saltParam[objectID].length);
        Crypto_82_Hsm_saltParam[objectID].pin = NULL_PTR;
        Crypto_82_Hsm_saltParam[objectID].length = 0u;
    }

    if (Crypto_82_Hsm_passParam[objectID].pin != NULL_PTR)
    {
        (void)Crypto_82_Hsm_Memset_s(Crypto_82_Hsm_passParam[objectID].pin, Crypto_82_Hsm_passParam[objectID].length, 0, Crypto_82_Hsm_passParam[objectID].length);
        Crypto_82_Hsm_passParam[objectID].pin = NULL_PTR;
        Crypto_82_Hsm_passParam[objectID].length = 0u;
    }

    /* Satisfies DN_SWS_Crypto_028 */
    /*Clear key element data buffers*/
    if ((elementIterations != NULL_PTR) && (elementIterations->keyDataPtr != NULL_PTR))
    {
        (void)Crypto_82_Hsm_Memset_s(elementIterations->keyDataPtr, elementIterations->keySize, 0, elementIterations->keySize);
        Crypto_82_Hsm_KeyElementValidity[iterationsKeyElementIndex] = FALSE;
        Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
    }
    if ((elementSalt != NULL_PTR) && (elementSalt->keyDataPtr != NULL_PTR))
    {
        (void)Crypto_82_Hsm_Memset_s(elementSalt->keyDataPtr, elementSalt->keySize, 0, elementSalt->keySize);
        Crypto_82_Hsm_KeyElementValidity[saltKeyElementIndex] = FALSE;
        Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
    }
    if ((elementPass != NULL_PTR) && (elementPass->keyDataPtr != NULL_PTR))
    {
        (void)Crypto_82_Hsm_Memset_s(elementPass->keyDataPtr, elementPass->keySize, 0, elementPass->keySize);
        Crypto_82_Hsm_KeyElementValidity[passwordKeyElementIndex] = FALSE;
        Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
    }
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementCopy( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
)
{
    return E_NOT_OK;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementCopyPartial( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) keyElementSourceOffset,
    VAR(uint32, AUTOMATIC) keyElementTargetOffset,
    VAR(uint32, AUTOMATIC) keyElementCopyLength,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
)
{
    return E_NOT_OK;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyCopy( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
)
{
    return E_NOT_OK;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyElementIdsGet( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) keyElementIdsPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) keyElementIdsLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    return E_NOT_OK;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_RandomSeed( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) seedPtr,
    VAR(uint32, AUTOMATIC) seedLength
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) sessionData;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00128 */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00129 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }

     /* Satisfies SWS_Crypto_00130 */
    else if (seedPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00131 */
    else if ( (seedLength == 0u) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {        
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            err = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            /* TODO: Investigate objectId handling */
            sessionData.hSession = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle;
            sessionData.priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT];

            csai_err = Crypto_82_Hsm_Rng_Reseed(&sessionData, seedPtr, seedLength);

            if (csai_err != ecy_hsm_CSAI_SUCCESS)
            {
                err = E_NOT_OK;
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_RANDOM_SEED, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
            }
            else
            {
                err = Crypto_82_Hsm_WaitForJobFinished(sessionData.hJob, CRYPTO_82_HSM_SERVICE_ID_RANDOM_SEED, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE);
            }

            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_RANDOM_SEED,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyGenerate( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_SUCCESS;
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR; 

    /* Satisfies SWS_Crypto_00094 */
    if(Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
    }
    /* Satisfies SWS_Crypto_00095 */
    else if(cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            /* Satisfies SWS_Crypto_00165 */
            VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle;
            P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle = &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
            P2VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) keyHandle = &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].keyHandle); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
            CONST(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyType = Crypto_82_Hsm_configKeys[cryptoKeyId].keyType;
            CONST(uint32, AUTOMATIC) keyProperties = Crypto_82_Hsm_configKeys[cryptoKeyId].keyProperties;         
            VAR(uint32, AUTOMATIC) keySize = 0u;

            VAR(uint32, AUTOMATIC) indexKeyGenerate = CRYPTO_82_HSM_INVALID_KEY_INDEX;

            /* The keyMaterialElement with the keyElementId equal to "CRYPTO_KE_KEYEXCHANGE_PRIVKEY" used for keyExchange */
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementKeyGenerate = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &indexKeyGenerate);

            if (indexKeyGenerate == CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
                elementKeyGenerate = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYGENERATE_KEY, &indexKeyGenerate);

                if (indexKeyGenerate != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    keySize = get_keyGenerateKeySize(cryptoKeyId, *elementKeyGenerate);
                }
            }
            else
            {
                keySize = get_keyGenerateKeySize(cryptoKeyId, *elementKeyGenerate);
            }

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
            if (indexKeyGenerate != CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
#endif               
                VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, indexKeyGenerate);

                if ( (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM) )
                {
                    csai_err = ecy_hsm_Csai_GenerateKey(sessionHandle, ecy_hsm_CSAI_PRIO_LOW, keyType,
                                                    (ecy_hsm_Csai_KeySizeT)keySize, keyProperties, keyHandle,
                                                    jobHandle);

                    if(ecy_hsm_CSAI_SUCCESS == csai_err)
                    {
                        Crypto_82_Hsm_KeyState[cryptoKeyId % CRYPTO_82_HSM_NUMBER_OF_KEYS].keyValid = FALSE;
                        Crypto_82_Hsm_KeyElementValidity[indexKeyGenerate % CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS] = FALSE;

                        err = Crypto_82_Hsm_WaitForJobFinished(*(jobHandle), CRYPTO_82_HSM_SERVICE_ID_KEY_GENERATE, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE);

                        if(E_OK == err)
                        {
                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

                            Crypto_82_Hsm_runtimeKeys[indexKeyGenerate  % CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS].keyHandle = *(keyHandle);

                            if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM)
                            {
                                Crypto_82_Hsm_KeyElementValidity[indexKeyGenerate % CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS] = TRUE;
                                #if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
                                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)% KEY_STATUS_DATA_ARRAY_SIZE], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
                                #endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
                            }
                            
                            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

                            ret = E_OK;
                        }
                    }
                    else
                    {
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_GENERATE, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
                    }
                }
#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )                
            }
            else
            {
                detErr = CRYPTO_E_PARAM_VALUE;
            }
#endif            

            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_GENERATE,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret;
}

/* SWS_Crypto_91008 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyDerive( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
)
{
    VAR (uint32, AUTOMATIC) saltKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) iterationsKeyElementIndex   = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) algoKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) targetKeyElementIndex       = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) passwordKeyElementIndex     = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) parentKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )

    /* [SWS_Crypto_00097] */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret = E_NOT_OK;
    }
    /* [SWS_Crypto_00098] */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    /* [SWS_Crypto_00180] */
    else if (targetCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementAlgo = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ALGORITHM, &algoKeyElementIndex);
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementIterations = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ITERATIONS, &iterationsKeyElementIndex);
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSalt = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_SALT, &saltKeyElementIndex);
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPass = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_PASSWORD, &passwordKeyElementIndex);
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementParentKey = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVE_CUSTOM_PARENTKEY, &parentKeyElementIndex);
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementTarget = Crypto_82_Hsm_findKeyElement(targetCryptoKeyId, CRYPTO_KEYDERIVE_TARGETKEYELEMENT_ID, &targetKeyElementIndex);
       
            ret = Crypto_82_Hsm_Process_KeyDerive(cryptoKeyId, targetCryptoKeyId, &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT]), targetKeyElementIndex, passwordKeyElementIndex, algoKeyElementIndex, saltKeyElementIndex, iterationsKeyElementIndex, parentKeyElementIndex, &detErr);

            if (ret == E_OK)
            {
                ret = Crypto_82_Hsm_WaitForJobFinished(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle, CRYPTO_82_HSM_SERVICE_ID_KEY_DERIVE, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE);

                if (ret == E_OK)
                {
                    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();

                    Crypto_82_Hsm_runtimeKeys[targetKeyElementIndex].keyHandle = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].keyHandle;
                    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(targetCryptoKeyId, targetKeyElementIndex);

                    if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM))
                    {
                        Crypto_82_Hsm_KeyElementValidity[targetKeyElementIndex] = TRUE;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                        Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(targetCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)% KEY_STATUS_DATA_ARRAY_SIZE], targetCryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
#endif
                    }

                    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_KEYS();
                }
            }

            Crypto_82_Hsm_clearbuffers_KeyDerive(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, cryptoKeyId, elementIterations, iterationsKeyElementIndex, elementSalt, saltKeyElementIndex, elementPass, passwordKeyElementIndex);
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }

#if ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON )
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_DERIVE,
            detErr
        );
    }
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON ) */

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcPubVal( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) publicValuePtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) publicValueLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR (Std_ReturnType, AUTOMATIC) ret_val = E_OK;
    VAR (uint32, AUTOMATIC) privKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &privKeyElementIndex);

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00103 */
    if(Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret_val = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00104 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret_val = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00105 */
    else if (publicValuePtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00106 */
    else if (publicValueLengthPtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00107 */
    else if (*publicValueLengthPtr == 0x00u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_052 */
    else if (privKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret_val = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            /* Satisfies SWS_Crypto_91009 */
            if (Crypto_82_Hsm_KeyElementValidity[privKeyElementIndex] != TRUE)
            {
                ret_val = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
            /* Do nothing */
            }                

            uint32 keyElementSize = get_keyElementSizeKeyExchange(cryptoKeyId, elementPrivKey);

            if (*publicValueLengthPtr < keyElementSize)
            {
                ret_val = E_NOT_OK; /* Satisfies SWS_Crypto_00195 (Deviated into DV_Crypto_006) */
            }

            /* Satisfies SWS_Crypto 00167 */
            if (ret_val == E_OK)
            {
                /* Satisfies SWS_Crypto_00109 */
                if(*publicValueLengthPtr > keyElementSize)
                {
                    *publicValueLengthPtr = keyElementSize;
                }

                ret_val = Crypto_82_Hsm_Process_KeyElementGet(cryptoKeyId, 
                                                            CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, 
                                                            elementPrivKey, 
                                                            privKeyElementIndex, 
                                                            &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle), 
                                                            publicValuePtr, 
                                                            publicValueLengthPtr,
                                                            CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_PUB_VAL,
                                                            CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE);
                                                            
                if (ret_val == E_OK)
                {
                    ret_val = Crypto_82_Hsm_Poll_KeyElementGet(cryptoKeyId, 
                                                            CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT,
                                                            elementPrivKey,
                                                            Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle,
                                                            publicValuePtr,
                                                            publicValueLengthPtr,
                                                            CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_PUB_VAL);
                }
            }

            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_PUB_VAL,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret_val;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcSecret( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) partnerPublicValuePtr,
    VAR(uint32, AUTOMATIC) partnerPublicValueLength
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val = E_OK;
    VAR(Std_ReturnType, AUTOMATIC) pollStatus;
    VAR(uint32, AUTOMATIC) algoKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) privKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) sharedSecretKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSharedSecret = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE, &sharedSecretKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPrivKey = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &privKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementAlgo = Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_ALGORITHM, &algoKeyElementIndex);

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00111 */
    if(Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00112 */
    else if (cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00113 */
    else if (partnerPublicValuePtr == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00115 */
    else if (partnerPublicValueLength == 0x00u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
     /* Satisfies DN_SWS_Crypto_053 */
    else if (sharedSecretKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_053 */
    else if (privKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies DN_SWS_Crypto_053 */
    else if (algoKeyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    else if (check_KeyExchangeSharedSecretSize(Crypto_82_Hsm_configKeys[cryptoKeyId].keyType, Crypto_82_Hsm_configKeyElements[privKeyElementIndex].keySize, Crypto_82_Hsm_configKeyElements[sharedSecretKeyElementIndex].keySize) == E_NOT_OK)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        ret_val = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT))
        {
            ret_val = CRYPTO_E_BUSY;
        }
        else
        {
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);

            /* Satisfies SWS_Crypto_91010 */
            if (Crypto_82_Hsm_KeyElementValidity[privKeyElementIndex] != TRUE)
            {
                ret_val = CRYPTO_E_KEY_EMPTY;
            }
            /* Satisfies SWS_Crypto_91010 */
            else if (Crypto_82_Hsm_KeyElementValidity[algoKeyElementIndex] != TRUE)
            {
                ret_val = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
                /* Do nothing */
            } 

            /* Satisfies SWS_Crypto 00167 */
            if (ret_val == E_OK)
            {
                VAR(uint32, AUTOMATIC) keySize = Crypto_82_Hsm_configKeyElements[privKeyElementIndex].keySize;
                VAR(ecy_hsm_Csai_KeyTypeT, AUTOMATIC) keyPairType = Crypto_82_Hsm_configKeys[cryptoKeyId].keyType;
                VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) sessionHandle = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle;
                VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiError;
                VAR(Crypto_82_Hsm_KeyExchangeCalcSecretFunctionType, AUTOMATIC) keyExchangeAlgo = CryptoDriver_ECDH_RESERVED;

                if(elementAlgo->keyDataPtr[0] == CRYPTO_ALGOFAM_DH)
                {   
                    keyExchangeAlgo = get_keyExchangeCalcSecretAlgo(keyPairType, &keySize); 
                }

                csaiError = ecy_hsm_Csai_DhInit(sessionHandle, 
                                                (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT],
                                                get_keyExchangeCalcSecretAlgoHsm(keyExchangeAlgo),
                                                Crypto_82_Hsm_runtimeKeys[privKeyElementIndex].keyHandle,
                                                keyExchangePublicKeyDataBuffer,
                                                keySize,
                                                &keyExchangePublicValueLength,
                                                &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle);

                if (csaiError == ecy_hsm_CSAI_SUCCESS)
                {
                    do
                    {
                        pollStatus = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle, CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);
                    } while (pollStatus == CRYPTO_E_BUSY);

                    if (pollStatus != E_OK)   
                    {
                        ret_val = E_NOT_OK;
                    }
                }
                else
                {
                    ret_val = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csaiError);
                }

                if(ret_val == E_OK)
                {
                    /* Satisfies SWS_Crypto 00109 */
                    csaiError = ecy_hsm_Csai_DhComputeExt(sessionHandle,
                                                    (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT],
                                                    partnerPublicValuePtr,
                                                    partnerPublicValueLength,
                                                    elementSharedSecret->keyDataPtr,
                                                    elementSharedSecret->keySize,
                                                    &keyExchangeCalcSecretCount[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT],
                                                    &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle);

                    if (csaiError == ecy_hsm_CSAI_SUCCESS)
                    {
                        Crypto_82_Hsm_KeyState[cryptoKeyId].keyValid = FALSE;
                        Crypto_82_Hsm_KeyElementValidity[sharedSecretKeyElementIndex] = FALSE;

                        do
                        {
                            pollStatus = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle, CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);
                        } while (pollStatus == CRYPTO_E_BUSY);

                        if (pollStatus != E_OK)
                        {
                            ret_val = E_NOT_OK;
                        }
                        else
                        {
                            Crypto_82_Hsm_KeyElementValidity[sharedSecretKeyElementIndex] = TRUE;
                        }
                    }
                    else
                    {
                        ret_val = E_NOT_OK;
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csaiError);
                    }
                }                                   
            }

            keyExchangeCalcSecretCount[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT] = 0;
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        }
    }


#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET,
            detErr
        );
    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

    return ret_val;
}

#if ((CRYIF_AR_RELEASE_MAJOR_VERSION == 4u) && (CRYIF_AR_RELEASE_MINOR_VERSION <= 4u))

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CertificateParse(VAR(uint32, AUTOMATIC) cryptoKeyId) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    return E_NOT_OK;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CertificateVerify( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) verifyCryptoKeyId,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_82_HSM_VAR) verifyPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    return E_NOT_OK;
}

#endif /* ((CRYIF_AR_RELEASE_MAJOR_VERSION == 4u) && (CRYIF_AR_RELEASE_MINOR_VERSION <= 4u)) */

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_LoadSHEKey_RAM(VAR(uint32, AUTOMATIC) objectId, uint8 serviceId, uint32 jobId)
{

    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err;
    VAR(Std_ReturnType, AUTOMATIC) ret_val = E_OK;

    csai_err = ecy_hsm_Csai_LoadKey(Crypto_82_Hsm_driverObjects[objectId].sessionHandle, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId], Crypto_82_Hsm_configKeys[Crypto_82_Hsm_SHE_loadKey[objectId].cryptoKeyId].HsmKeyId,
                                                Crypto_82_Hsm_configKeys[Crypto_82_Hsm_SHE_loadKey[objectId].cryptoKeyId].keyType, 
                                                &Crypto_82_Hsm_runtimeKeys[Crypto_82_Hsm_SHE_loadKey[objectId].keyElement].keyHandle, &Crypto_82_Hsm_driverObjects[objectId].jobHandle);

    if(ecy_hsm_CSAI_SUCCESS == csai_err)
    {
        ret_val = E_OK;
    }
    else
    {
        ret_val = E_NOT_OK;
        Crypto_82_Hsm_Error_Callback(serviceId, jobId, csai_err);
    }

    Crypto_82_Hsm_SHE_loadKey[objectId].loadKeyOperationRequired = FALSE;
    Crypto_82_Hsm_SHE_loadKey[objectId].keyElement = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    Crypto_82_Hsm_SHE_loadKey[objectId].cryptoKeyId = CRYPTO_82_HSM_INVALID_KEY_INDEX;

    return ret_val;

}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
