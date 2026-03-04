/**
 * \file Crypto_82_Hsm_Dispatch.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Identify corresponding cycurHSM algorithm and dispatch to Service Layer
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_Dispatch.h"
#include "Crypto_82_Hsm.h"
#include "Crypto_82_Hsm_Mem.h"
#include "Crypto_82_Hsm_UserCallout.h"

#if ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON )
    #include "Det.h"
#endif

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT 
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Shared Memory from Crypto to HSM
 */
VAR(uint32, AUTOMATIC) verificationResult_global[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief Buffers for AEAD DECRYPT tag data ; Shared Memory from Crypto to HSM
*/
VAR(uint8, AUTOMATIC) aeadDecryptTag_global[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS][SIZE_IN_BYTES_AEAD_TAG];

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT  
#include "Crypto_82_Hsm_MemMap.h" 

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT 
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Shared Memory from Crypto to HSM
 */
static  VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) sessionData[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT  
#include "Crypto_82_Hsm_MemMap.h" 

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Maps the job configuration to a supported signature algorithm.
 *
 * \param [in] job             Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                             information.
 *
 * \return algorithm           Signature algorithm.
 */
static FUNC(Crypto_82_Hsm_Service_SignAlgorithmType, CRYPTO_82_HSM_CODE) MapSignAlgorithm(const Crypto_JobType* job);

/**
 * \brief Function which initializes Shared Memory Data.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Dispatch_SharedMemory_Clear(uint32 objectid);

/**
 * \brief Mapping for hash algorithms.
 *
 * \param [in] algo           Algorithm family.
 *
 * \return ret_algo           Corresponding hash algorithm supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_Service_HashAlgorithmType, CRYPTO_82_HSM_CODE) get_serviceLayerHashAlgo(uint32 algo);

/**
 * \brief Mapping for symmetric cipher modes.
 *
 * \param [in] mode           Algorithm mode.
 *
 * \return ret_mode           Corresponding symmetric cipher mode supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_Service_SymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymCipherMode(uint32 mode);

/**
 * \brief Mapping for symmetric cipher modes for authenticatated encryption.
 *
 * \param [in] mode           Algorithm mode.
 *
 * \return ret_mode           Corresponding symmetric cipher mode supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_Service_SymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymCipherMode_AEAD(uint32 mode);


/**
 * \brief Mapping for symmetric cipher padding modes.
 *
 * \param [in] padding        Padding mode.
 *
 * \return ret_padding        Corresponding symmetric cipher padding mode supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_Service_PaddingModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymPadMode(uint32 padding);

/**
 * \brief Mapping for asymmetric cipher modes.
 *
 * \param [in] mode           Algorithm mode.
 *
 * \return ret_mode           Corresponding asymmetric cipher mode supported by the Crypto Service layer.
 */
static FUNC(Crypto_82_Hsm_Service_AsymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerAsymCipherMode(uint32 mode);

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(Crypto_82_Hsm_Service_SignAlgorithmType, CRYPTO_82_HSM_CODE) MapSignAlgorithm(const Crypto_JobType* job)
{
    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) algo = CryptoDriver_SIGN_RESERVED;
    VAR(uint8, AUTOMATIC) algoFam = job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(uint8, AUTOMATIC) algoSecFam = job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily;
    VAR(uint8, AUTOMATIC) algoMode = job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(uint32, AUTOMATIC) keyElementIndex;
    CONST(uint32, AUTOMATIC) msg_len = job->jobPrimitiveInputOutput.inputLength;
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) keyElementPtr = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY, &keyElementIndex);
    CONST(ecy_hsm_Csai_KeyTypeT, CRYPTO_82_HSM_CONST) keyType = Crypto_82_Hsm_configKeys[job->cryptoKeyId].keyType;

    /** Make sure the Crypto Key from Job config has a KeyElement with ID = 1*/
    if (keyElementPtr != NULL_PTR)
    {
        VAR(uint32, AUTOMATIC) keySize = keyElementPtr->keySize;

        if ( (algoFam ==  CRYPTO_ALGOFAM_RSA) && (algoMode == CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_256))
        {
            algo = CryptoDriver_RSA_SSA_PKCS1_1V5_SHA256;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_RSA) && (algoMode == CRYPTO_ALGOMODE_RSASSA_PSS) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_256))
        {
            algo = CryptoDriver_RSA_SSA_PSS_SHA256;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_ED25519) && (algoSecFam == CRYPTO_ALGOFAM_NOT_SET ) && (msg_len == 64uL) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR == keyType) && (64u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC == keyType) && (32u == keySize)) ) )
        {
            algo = CryptoDriver_ED25519_SHA_512_PURE;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_ED25519) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_512) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR == keyType) && (64u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC == keyType) && (32u == keySize)) ) )
        {
            algo = CryptoDriver_ED25519_SHA_512_DOM2_PH;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_ECCNIST) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_224) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (84u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (56u == keySize)) ) )
        {
            algo = CryptoDriver_SECP224_SHA_224;
        } 
        else if ( (algoFam == CRYPTO_ALGOFAM_ECCNIST) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_256) && 
                ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (96u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (64u == keySize)) ) )
        {
            algo = CryptoDriver_SECP256_SHA_256;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_ECCNIST) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_384) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (144u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (96u == keySize)) ) )
        {
            algo = CryptoDriver_SECP384_SHA_384;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_ECCNIST) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_512) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (144u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (96u == keySize)) ) )
        {
            algo = CryptoDriver_SECP384_SHA_512;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_256) && (msg_len == 32uL) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (144u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (96u == keySize)) ) )
        {
            algo = CryptoDriver_SECP384_SHA_256_USERHASHED;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_384) && (msg_len == 48uL) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (144u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (96u == keySize)) ) )
        {
            algo = CryptoDriver_SECP384_SHA_384_USERHASHED;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_CUSTOM_ECCNIST_USERHASHED) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_512) && (msg_len == 64uL) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR == keyType) && (144u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC == keyType) && (96u == keySize)) ) )
        {
            algo = CryptoDriver_SECP384_SHA_512_USERHASHED;
        }
        else if ( (algoFam == CRYPTO_ALGOFAM_CUSTOM_ED25519_SHA_512_DOM2_PH_USERHASHED) && (algoSecFam == CRYPTO_ALGOFAM_SHA2_512) && (msg_len == 64uL) && 
                  ( ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR == keyType) && (64u == keySize)) || ((ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC == keyType) && (32u == keySize)) ) )
        {
            algo = CryptoDriver_ED25519_SHA_512_DOM2_PH_USERHASHED;
        }
        else
        {
            /* Do nothing */
        }           
    }

    return algo;
}

static FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Dispatch_SharedMemory_Clear(uint32 objectid)
{
    /* sessionData Clear */
    sessionData[objectid].hSession = 0U;
    sessionData[objectid].hJob = 0U;
    sessionData[objectid].priority = (ecy_hsm_Csai_JobPriorityT)0U;

    /* Invalidate/Clear verification result */
    verificationResult_global[objectid] = FALSE;

    /* Clear AEAD tag buffers */
    (void)Crypto_82_Hsm_Memset_s(&(aeadDecryptTag_global[objectid][0]), SIZE_IN_BYTES_AEAD_TAG, 0, SIZE_IN_BYTES_AEAD_TAG);
}

static FUNC(Crypto_82_Hsm_Service_HashAlgorithmType, CRYPTO_82_HSM_CODE) get_serviceLayerHashAlgo(uint32 algo)
{
    Crypto_82_Hsm_Service_HashAlgorithmType ret_algo = CryptoDriver_HASH_RESERVED;

    switch (algo)
    {
    case CRYPTO_ALGOFAM_SHA1:
        ret_algo = CryptoDriver_SHA1;
        break;
    case CRYPTO_ALGOFAM_SHA2_224:
        ret_algo = CryptoDriver_SHA2_224;
        break;
    case CRYPTO_ALGOFAM_SHA2_256:
        ret_algo = CryptoDriver_SHA2_256;
        break;
    case CRYPTO_ALGOFAM_SHA2_384:
        ret_algo = CryptoDriver_SHA2_384;
        break;
    case CRYPTO_ALGOFAM_SHA2_512:
        ret_algo = CryptoDriver_SHA2_512;
        break;
    case CRYPTO_ALGOFAM_CUSTOM_AES_MP:
        ret_algo = CryptoDriver_AES_MP;
        break;
    default:
        ret_algo = CryptoDriver_HASH_RESERVED;
        break;
    }

    return ret_algo;
}

FUNC(Crypto_82_Hsm_Service_MACAlgorithmType, CRYPTO_82_HSM_CODE) get_serviceLayerMacAlgo(uint32 algofam, uint32 algomode)
{
    Crypto_82_Hsm_Service_MACAlgorithmType ret_algo = CryptoDriver_MAC_RESERVED;

    if ((algofam == CRYPTO_ALGOFAM_AES) && (algomode == CRYPTO_ALGOMODE_CMAC))
    {
        ret_algo = CryptoDriver_AES_CMAC;
    }
    else if ((algofam == CRYPTO_ALGOFAM_SHA1) && (algomode == CRYPTO_ALGOMODE_HMAC))
    {
        ret_algo = CryptoDriver_HMAC_SHA1;
    }
    else if ((algofam == CRYPTO_ALGOFAM_SHA2_256) && (algomode == CRYPTO_ALGOMODE_HMAC))
    {
        ret_algo = CryptoDriver_HMAC_SHA2_256;
    }
    else if ((algofam == CRYPTO_ALGOFAM_SHA2_512) && (algomode == CRYPTO_ALGOMODE_HMAC))
    {
        ret_algo = CryptoDriver_HMAC_SHA2_512;
    }
    else
    {
      /* Do nothing */
    }
    return ret_algo;
}

static FUNC(Crypto_82_Hsm_Service_SymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymCipherMode(uint32 mode)
{
    Crypto_82_Hsm_Service_SymCipherModeType ret_mode = CryptoDriver_SYMCIPHER_RESERVED;

    switch (mode)
    {
    case CRYPTO_ALGOMODE_ECB:
        ret_mode = CryptoDriver_AES_ECB;
        break;
    case CRYPTO_ALGOMODE_CBC:
        ret_mode = CryptoDriver_AES_CBC;
        break;
    case CRYPTO_ALGOMODE_CFB:
        ret_mode = CryptoDriver_AES_CFB128;
        break;
    case CRYPTO_ALGOMODE_OFB:
        ret_mode = CryptoDriver_AES_OFB;
        break;
    case CRYPTO_ALGOMODE_CTR:
        ret_mode = CryptoDriver_AES_CTR;
        break;
    case CRYPTO_ALGOMODE_XTS:
        ret_mode = CryptoDriver_AES_XTS;
        break;
    default:
        ret_mode = CryptoDriver_SYMCIPHER_RESERVED;
        break;
    }

    return ret_mode;
}

static FUNC(Crypto_82_Hsm_Service_SymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymCipherMode_AEAD(uint32 mode)
{
    Crypto_82_Hsm_Service_SymCipherModeType ret_mode = CryptoDriver_SYMCIPHER_RESERVED;

    switch (mode)
    { 
    case CRYPTO_ALGOMODE_GCM:
        ret_mode = CryptoDriver_AES_GCM;
        break;
    default:
        ret_mode = CryptoDriver_SYMCIPHER_RESERVED;
        break;
    }

    return ret_mode;
}

static FUNC(Crypto_82_Hsm_Service_PaddingModeType, CRYPTO_82_HSM_CODE) get_serviceLayerSymPadMode(uint32 padding)
{
    Crypto_82_Hsm_Service_PaddingModeType ret_padding = CryptoDriver_PADDINGMODE_RESERVED;

    switch (padding)
    {
    case CRYPTO_ALGOFAM_NOT_SET:
        ret_padding = CryptoDriver_PAD_NONE;
        break;
    case CRYPTO_ALGOFAM_PADDING_PKCS7:
        ret_padding = CryptoDriver_PAD_PKCS7;
        break;
    case CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS:
        ret_padding = CryptoDriver_NIST_SP800;
        break;
    default:
        ret_padding = CryptoDriver_PADDINGMODE_RESERVED;
        break;
    }

    return ret_padding;
}

static FUNC(Crypto_82_Hsm_Service_AsymCipherModeType, CRYPTO_82_HSM_CODE) get_serviceLayerAsymCipherMode(uint32 mode)
{
    Crypto_82_Hsm_Service_AsymCipherModeType ret_mode = CryptoDriver_ASYMCIPHER_RESERVED;

    switch (mode)
    {
    case CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5:
        ret_mode = CryptoDriver_RSA_ES_PKCS1_v15;
        break;
    case CRYPTO_ALGOMODE_RSAES_OAEP:
        ret_mode = CryptoDriver_RSA_ES_OAEP;
        break;
    default:
        ret_mode = CryptoDriver_ASYMCIPHER_RESERVED;
        break;
    }
    return ret_mode;
}

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Hash_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(uint8, AUTOMATIC) hashAlgoIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) digest = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    Crypto_82_Hsm_Service_HashAlgorithmType Crypto_algo = get_serviceLayerHashAlgo(hashAlgoIndex);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

/* Input data; Satisfies SWS_Crypto_00073 */
/* Output data; Satisfies SWS_Crypto_00073 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    digest = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONST(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) digest_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;


    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 */
    if ( (msg == NULL_PTR) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) ||
        (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 */
    else if ( ( (digest == NULL_PTR) || (digest_len == NULL_PTR) ) &&
         ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (msg_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) ||
        (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if (  ( digest_len != NULL_PTR )  && ( (*digest_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00067 */
    else if (Crypto_algo == CryptoDriver_HASH_RESERVED)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
		err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:

            ret = Crypto_82_Hsm_Hash_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], Crypto_algo, msg, msg_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        /* TODO: Investigate if this is correct implementation of start with respect to cycurHSM */
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Hash_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], Crypto_algo, NULL_PTR, 0);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_Hash_Update(sessionData[driverObject->objectID], msg, msg_len);

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Hash_Finish(sessionData[driverObject->objectID], digest, digest_len);

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Hash_Compute(
                &sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],
                Crypto_algo,
                msg, msg_len,
                digest, digest_len);

            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
FUNC(uint8, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacGenerate_DET_Checking(
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg, 
                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                CONST(uint32, AUTOMATIC) msg_len,
                                P2VAR(uint32, AUTOMATIC, AUTOMATIC) mac_len, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                VAR(Crypto_OperationModeType, AUTOMATIC) opMode,
                                VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) Crypto_algo
                                )
{
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071  */
    if ( (msg == NULL_PTR) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) ||
        (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 */
    else if ( ( (mac == NULL_PTR) || (mac_len == NULL_PTR) ) &&
         ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (msg_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) ||
            (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (mac_len != NULL_PTR) && ( (*mac_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
    }
	
	/* Satisfies SWS_Crypto_00067 */
    else if (Crypto_algo == CryptoDriver_MAC_RESERVED)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else
    {
          /* Do nothing. */
     }

    return detErr;
}
#endif

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) mac = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    VAR(uint8, AUTOMATIC) macAlgoFamIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(uint8, AUTOMATIC) macAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;
    Crypto_82_Hsm_Service_MACAlgorithmType Crypto_algo = get_serviceLayerMacAlgo(macAlgoFamIndex, macAlgoModeIndex);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

/* Input data; Satisfies SWS_Crypto_00073 */
/* Output data; Satisfies SWS_Crypto_00073 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    mac = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONST(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) mac_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    detErr = Crypto_82_Hsm_MacGenerate_DET_Checking(msg, mac, msg_len, mac_len, opMode, Crypto_algo);

    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        err = E_NOT_OK;
    }
    else
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:

            ret = Crypto_82_Hsm_Mac_Generate_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                                   msg, msg_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        /* TODO: Investigate if this is correct implementation of start with respect to cycurHSM */
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Mac_Generate_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                                   NULL_PTR, 0);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_Mac_Generate_Update(sessionData[driverObject->objectID], msg, msg_len);

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            *mac_len = *mac_len * CRYPTO_82_HSM_NUM_BITS_IN_BYTE;/* PRQA S 3383  #In case the output length is too high, *mac_len will be overwritten by the csai with correct value. */
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Mac_Generate_Finish(sessionData[driverObject->objectID], mac, mac_len);

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:

            *mac_len = *mac_len * CRYPTO_82_HSM_NUM_BITS_IN_BYTE;/* PRQA S 3383  #In case the output length is too high, *mac_len will be overwritten by the csai with correct value. */
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Mac_Generate(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                             msg, msg_len, mac, mac_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

#if ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )
FUNC(uint8, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacVerify_DET_Checking(
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg, 
                                P2CONST(uint8, AUTOMATIC, AUTOMATIC) mac,
                                CONST(uint32, AUTOMATIC) msg_len,
                                VAR(uint32, AUTOMATIC) mac_size,
                                VAR(Crypto_OperationModeType, AUTOMATIC) opMode,
                                VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) Crypto_algo,
                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) verifyPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                )
{
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    if ( (msg == NULL_PTR) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
         (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    else if ( ((mac == NULL_PTR) || (verifyPtr == NULL_PTR) ) 
    && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142 */
    else if ( (msg_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
             (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ))
    {
        detErr = CRYPTO_E_PARAM_VALUE;
    }
    else if ( (mac_size == 0u)  && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
    }
	/* Satisfies SWS_Crypto_00067 */
    else if (Crypto_algo == CryptoDriver_MAC_RESERVED)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else
    {
          /* Do nothing. */
     }

    return detErr;
}
#endif

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MacVerify_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) mac = NULL_PTR;

    VAR(uint8, AUTOMATIC) macAlgoFamIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(uint8, AUTOMATIC) macAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;
    Crypto_82_Hsm_Service_MACAlgorithmType Crypto_algo = get_serviceLayerMacAlgo(macAlgoFamIndex, macAlgoModeIndex);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

/* Input data; Satisfies SWS_Crypto_00073 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    mac = driverObject->job->jobPrimitiveInputOutput.secondaryInputPtr;

    CONST(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;
    VAR(uint32, AUTOMATIC) mac_size = (driverObject->job->jobPrimitiveInputOutput.secondaryInputLength);
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    detErr = Crypto_82_Hsm_MacVerify_DET_Checking(msg, mac, msg_len, mac_size, opMode, Crypto_algo, (uint8*)driverObject->job->jobPrimitiveInputOutput.verifyPtr);

    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        err = E_NOT_OK;
    }
    else
#endif /*  (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:

            ret = Crypto_82_Hsm_Mac_Verify_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                                 msg, msg_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        /* TODO: Investigate if this is correct implementation of start with respect to cycurHSM */
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Mac_Verify_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                                 NULL_PTR, 0);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_Mac_Verify_Update(sessionData[driverObject->objectID], msg, msg_len);

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Mac_Verify_Finish(sessionData[driverObject->objectID], mac, mac_size, &verificationResult_global[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS]);

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Mac_Verify(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_algo,
                                           msg, msg_len, mac, mac_size, &verificationResult_global[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS]);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Encrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(uint32, AUTOMATIC) keyElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) cipher = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) iv = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) iv_len = 0u;    
    VAR(uint8, AUTOMATIC) cryptAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(uint8, AUTOMATIC) cryptAlgoFam = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(uint8, AUTOMATIC) symCryptPaddingIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;
    Crypto_82_Hsm_Service_SymCipherModeType Crypto_mode_sym = get_serviceLayerSymCipherMode(cryptAlgoModeIndex);
    Crypto_82_Hsm_Service_PaddingModeType Crypto_padding = get_serviceLayerSymPadMode(symCryptPaddingIndex);
    Crypto_82_Hsm_Service_AsymCipherModeType Crypto_mode_asym = get_serviceLayerAsymCipherMode(cryptAlgoModeIndex);
    uint8 csaitriggered = FALSE;

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

/* Input data; Satisfies SWS_Crypto_00071 */
/* Output data; Satisfies SWS_Crypto_00071 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    cipher = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONST(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) cipher_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    CONSTP2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) ivElement = Crypto_82_Hsm_findKeyElement(driverObject->job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, &keyElemIndex);
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;


    if ((ivElement == NULL_PTR) && (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex))
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    else if ( (msg == NULL_PTR) &&  (opMode != CRYPTO_OPERATIONMODE_FINISH) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    else if ( (cipher == NULL_PTR) || (cipher_len == NULL_PTR) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142 */
    else if ( (msg_len == 0u) && (opMode != CRYPTO_OPERATIONMODE_FINISH) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142 */
    else if ( *cipher_len == 0u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err =  E_NOT_OK;
    }

	/* Satisfies SWS_Crypto_00067 */
    else if ( (cryptAlgoFam == CRYPTO_ALGOFAM_AES) && (   (Crypto_mode_sym == CryptoDriver_SYMCIPHER_RESERVED) || (Crypto_padding == CryptoDriver_PADDINGMODE_RESERVED) )    )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00067 */
    else if ( (cryptAlgoFam == CRYPTO_ALGOFAM_RSA) && (Crypto_mode_asym == CryptoDriver_ASYMCIPHER_RESERVED)    )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {

        case CRYPTO_OPERATIONMODE_STREAMSTART:
        case CRYPTO_OPERATIONMODE_START:
        {
            if ((cryptAlgoFam == CRYPTO_ALGOFAM_AES))
            {
                if (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex)
                {
                    iv = ivElement->keyDataPtr;
                    iv_len = ivElement->keySize;
                }

                ret = Crypto_82_Hsm_SymC_Encrypt_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                       Crypto_padding, msg, msg_len, (const uint8 *)iv, iv_len, cipher, cipher_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }

            break;
        }

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_SymC_Encrypt_Update(sessionData[driverObject->objectID], msg, msg_len, cipher, cipher_len);
            csaitriggered = TRUE;

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_SymC_Encrypt_Finish(sessionData[driverObject->objectID], cipher, cipher_len);
            csaitriggered = TRUE;

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:
        {

            if ((cryptAlgoFam == CRYPTO_ALGOFAM_AES))
            {
                if (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex)
                {
                    iv = ivElement->keyDataPtr;
                    iv_len = ivElement->keySize;
                }

                /* Satisfies SWS_Crypto_00023 */
                ret = Crypto_82_Hsm_SymC_Encrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                 Crypto_padding, msg, msg_len, (const uint8 *)iv, iv_len,
                                                 cipher, cipher_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }
            else if (cryptAlgoFam == CRYPTO_ALGOFAM_RSA)
            {
                sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_LOW_PRIORITY;

                /* Satisfies SWS_Crypto_00023 */
                ret = Crypto_82_Hsm_AsymC_Encrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_asym,
                                                  msg, msg_len, cipher, cipher_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }
            else
            {
                /* Do nothing */
            }

            break;
        }

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            if (csaitriggered == TRUE)
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AEADEncrypt_Dispatch (
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(uint32, AUTOMATIC) keyElemIndex;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) pPlainText = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) pAssociatedData = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) pTag = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) cipher = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyId = driverObject->job->cryptoKeyId;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) iv = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) iv_len = 0u;

    VAR(uint8, AUTOMATIC) cryptAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(uint8, AUTOMATIC) symCryptPaddingIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;

    /* Satisfies SWS_Crypto_00134 */
    CONST(uint32, AUTOMATIC) plainText_len      = driverObject->job->jobPrimitiveInputOutput.inputLength;
    CONST(uint32, AUTOMATIC) associatedData_len = driverObject->job->jobPrimitiveInputOutput.secondaryInputLength;
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) tag_len            = driverObject->job->jobPrimitiveInputOutput.secondaryOutputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    /* Satisfies SWS_Crypto_00135 */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) cipher_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    Crypto_82_Hsm_Service_SymCipherModeType Crypto_mode_sym = get_serviceLayerSymCipherMode_AEAD(cryptAlgoModeIndex);
    Crypto_82_Hsm_Service_PaddingModeType Crypto_padding = get_serviceLayerSymPadMode(symCryptPaddingIndex);
    
    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

    /* Input data; Satisfies SWS_Crypto_00073 */
    /* Output data; Satisfies SWS_Crypto_00071 && SWS_Crypto_00073 */

    pPlainText      = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    pAssociatedData = driverObject->job->jobPrimitiveInputOutput.secondaryInputPtr;
    cipher             = driverObject->job->jobPrimitiveInputOutput.outputPtr;
    pTag            = driverObject->job->jobPrimitiveInputOutput.secondaryOutputPtr;

    CONSTP2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element = Crypto_82_Hsm_findKeyElement(keyId, CRYPTO_KE_CIPHER_IV, &keyElemIndex);

    if(element != NULL_PTR)
    {
        iv = element->keyDataPtr;
        iv_len = element->keySize;
    }

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    if (element == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 
        OPERATIONMODE_UPDATE for InputPtr, secondaryInputPtr, OutputPtr, outputLenghtPtr  (actually includes STREAMSTART & SINGLECALL & UPDATE) */
    else if (    (   (pPlainText == NULL_PTR) || (cipher == NULL_PTR) || (cipher_len == NULL_PTR) ||
         (  (Crypto_82_Hsm_AEAD_Encrypt_ADD_received[driverObject->objectID] == FALSE) && (pAssociatedData == NULL_PTR)   )   ) &&
        (   (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) )   )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }    
    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071
        OPERATIONMODE_Finish for OutputPtr, OutputLengthPtr, SecondaryInputPtr and secondaryOutputLengthPtr  */
    else if (  (    (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) )  && 
        ( (cipher == NULL_PTR) || (cipher_len == NULL_PTR) || (pTag == NULL_PTR) || (tag_len == NULL_PTR) )    )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
        /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142
        OPERATIONMODE_UPDATE for inputLength, secondaryInputLength, val of outputLengthPtr(actually includes STREAMSTART & SINGLECALL & UPDATE) */
    else if (  (cipher_len != NULL_PTR) &&  (  (plainText_len == 0u) || ( *cipher_len == 0u) ||
         (  (Crypto_82_Hsm_AEAD_Encrypt_ADD_received[driverObject->objectID] == FALSE) && (associatedData_len == 0u)    )   ) &&
        (   (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) )   )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
         /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142
        OPERATIONMODE_Finish for val of OutputLengthPtr and val of secondaryOutputLengthPtr */
    else if (       (   (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) &&
             (  (*cipher_len == 0u) || (*tag_len == 0u) )       )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
	/* Satisfies SWS_Crypto_00067 */
    else if (   (Crypto_mode_sym == CryptoDriver_SYMCIPHER_RESERVED) || (Crypto_padding == CryptoDriver_PADDINGMODE_RESERVED) )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON )  */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Auth_Encrypt_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                   Crypto_padding, (const uint8 *)iv, iv_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
            Crypto_82_Hsm_AEAD_Encrypt_ADD_received[driverObject->objectID] = FALSE;
            break;
        case CRYPTO_OPERATIONMODE_SINGLECALL:

            ret = Crypto_82_Hsm_Auth_Encrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                             Crypto_padding, pPlainText, plainText_len, (const uint8 *)iv, iv_len,
                                             pAssociatedData, associatedData_len, cipher, cipher_len, pTag, *tag_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;                                             
            break;
        case CRYPTO_OPERATIONMODE_UPDATE:
            if (Crypto_82_Hsm_AEAD_Encrypt_ADD_received[driverObject->objectID] == FALSE)
            {
                ret = Crypto_82_Hsm_Auth_Encrypt_Update(sessionData[driverObject->objectID], pAssociatedData, associatedData_len);
            }
            else
            {
                ret = Crypto_82_Hsm_SymC_Encrypt_Update(sessionData[driverObject->objectID], pPlainText, plainText_len, cipher, cipher_len);
            }
            break;

        case CRYPTO_OPERATIONMODE_FINISH:
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Auth_Encrypt_Finish(sessionData[driverObject->objectID], cipher, cipher_len, pTag, *tag_len);
            Crypto_82_Hsm_AEAD_Encrypt_ADD_received[driverObject->objectID] = FALSE;
            break;
        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_AEADDecrypt_Dispatch (
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) cipher = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) pAssociatedData = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyElemIndex;
    VAR(uint8, AUTOMATIC) cryptAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(uint8, AUTOMATIC) symCryptPaddingIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily;
    VAR(uint32, AUTOMATIC) keyId = driverObject->job->cryptoKeyId;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) iv = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) iv_len = 0u;
    /* Satisfies SWS_Crypto_00134 */
    CONST(uint32, AUTOMATIC) cipher_len         = driverObject->job->jobPrimitiveInputOutput.inputLength;
    CONST(uint32, AUTOMATIC) associatedData_len = driverObject->job->jobPrimitiveInputOutput.secondaryInputLength;
    CONST(uint32, AUTOMATIC) tag_len            = driverObject->job->jobPrimitiveInputOutput.tertiaryInputLength;

    /* Satisfies SWS_Crypto_00135 */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    Crypto_82_Hsm_Service_SymCipherModeType Crypto_mode_sym = get_serviceLayerSymCipherMode_AEAD(cryptAlgoModeIndex);
    Crypto_82_Hsm_Service_PaddingModeType Crypto_padding = get_serviceLayerSymPadMode(symCryptPaddingIndex);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

    /* Input data; Satisfies SWS_Crypto_00073 */
    /* Output data; Satisfies SWS_Crypto_00071 && SWS_Crypto_00073 */

    cipher          = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    pAssociatedData = driverObject->job->jobPrimitiveInputOutput.secondaryInputPtr;
    msg             = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONSTP2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) element = Crypto_82_Hsm_findKeyElement(keyId, CRYPTO_KE_CIPHER_IV, &keyElemIndex);
    if (element != NULL_PTR)
    {
        iv = element->keyDataPtr;
        iv_len = element->keySize;
    }

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    if (element == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071
        OPERATIONMODE_UPDATE for inputPtr, secondaryInputPtr, outputPtr, outputLengthPtr  (actually includes STREAMSTART & SINGLECALL & UPDATE) */
    else if ( ( (cipher == NULL_PTR) || (msg == NULL_PTR) || (msg_len == NULL_PTR) ||
     (  (Crypto_82_Hsm_AEAD_Decrypt_ADD_received[driverObject->objectID] == FALSE) &&  (pAssociatedData == NULL_PTR)   ) ) &&
         ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) )
        )
    {       
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071
        OPERATIONMODE_Finish for tertiaryInputPtr, outputPtr, verifyPtr */
    else if (       (   (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) &&
    ( (driverObject->job->jobPrimitiveInputOutput.tertiaryInputPtr == NULL_PTR ) || (msg == NULL_PTR) || (msg_len == NULL_PTR) || (driverObject->job->jobPrimitiveInputOutput.verifyPtr == NULL_PTR))
    )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
         /* SWS_Crypto_00071 && SWS_Crypto_00142
        OPERATIONMODE_UPDATE for inputLength, val of outputLengthPtr and secondaryInputLength  (actually includes STREAMSTART & SINGLECALL & UPDATE) */
    else if ( (msg_len != NULL_PTR)&& (   ( cipher_len == 0u) || (*msg_len == 0u)   ||
     (  (Crypto_82_Hsm_AEAD_Decrypt_ADD_received[driverObject->objectID] == FALSE) && (associatedData_len == 0u) ) ) &&
         ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) || (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) )
        )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
        /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142
        OPERATIONMODE_Finish for val of msg_len, tertiaryInputLength */
    else if (       (   (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) &&
    (   ( *msg_len == 0u) || (tag_len == 0uL) )   )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
	/* Satisfies SWS_Crypto_00067 */
    else if (   (Crypto_mode_sym == CryptoDriver_SYMCIPHER_RESERVED) || (Crypto_padding == CryptoDriver_PADDINGMODE_RESERVED) )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Auth_Decrypt_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                   Crypto_padding, (const uint8 *)iv, iv_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
            Crypto_82_Hsm_AEAD_Decrypt_ADD_received[driverObject->objectID] = FALSE;
            break;
        case CRYPTO_OPERATIONMODE_SINGLECALL:

            ret = Crypto_82_Hsm_Auth_Decrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                             Crypto_padding, cipher, cipher_len, (const uint8 *)iv, iv_len,
                                             pAssociatedData, associatedData_len, msg, msg_len, &(aeadDecryptTag_global[driverObject->objectID][0]), tag_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
            break;
        case CRYPTO_OPERATIONMODE_UPDATE:
            if (Crypto_82_Hsm_AEAD_Decrypt_ADD_received[driverObject->objectID] == FALSE)
            {
                ret = Crypto_82_Hsm_Auth_Decrypt_Update(sessionData[driverObject->objectID], pAssociatedData, associatedData_len);
            }
            else
            {
                ret = Crypto_82_Hsm_SymC_Decrypt_Update(sessionData[driverObject->objectID], cipher, cipher_len, msg, msg_len);
            }
            break;
        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Auth_Decrypt_Finish(sessionData[driverObject->objectID], msg, msg_len, &(aeadDecryptTag_global[driverObject->objectID][0]), tag_len);
            Crypto_82_Hsm_AEAD_Decrypt_ADD_received[driverObject->objectID] = FALSE;
            break;
        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Decrypt_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) cipher = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint8, AUTOMATIC) cryptAlgoModeIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.mode;
    VAR(uint8, AUTOMATIC) cryptAlgoFam = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;
    VAR(uint8, AUTOMATIC) symCryptPaddingIndex = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) iv = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) iv_len = 0u;
    VAR(uint32, AUTOMATIC) keyElemIndex;
    Crypto_82_Hsm_Service_SymCipherModeType Crypto_mode_sym = get_serviceLayerSymCipherMode(cryptAlgoModeIndex);
    Crypto_82_Hsm_Service_PaddingModeType Crypto_padding = get_serviceLayerSymPadMode(symCryptPaddingIndex);
    Crypto_82_Hsm_Service_AsymCipherModeType Crypto_mode_asym = get_serviceLayerAsymCipherMode(cryptAlgoModeIndex);
    uint8 csaitriggered = FALSE;

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

/* Input data; Satisfies SWS_Crypto_00073 */
/* Output data; Satisfies SWS_Crypto_00071 && SWS_Crypto_00073 */

    cipher = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    msg = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONST(uint32, AUTOMATIC) cipher_len = driverObject->job->jobPrimitiveInputOutput.inputLength;

    /* TODO: Investigate how to handle this parameter with respect to output redirection */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    CONSTP2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) ivElement = Crypto_82_Hsm_findKeyElement(driverObject->job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, &keyElemIndex);
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;


    if ((ivElement == NULL_PTR) && (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex))
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    else if ( (cipher == NULL_PTR) && ( (opMode != CRYPTO_OPERATIONMODE_FINISH) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00070 */
    else if ( (msg == NULL_PTR) || (msg_len == NULL_PTR) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142 */
    else if ( (cipher_len == 0u) && (opMode != CRYPTO_OPERATIONMODE_FINISH) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00071 && SWS_Crypto_00142 */
    else if ( *msg_len == 0u)
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

	/* Satisfies SWS_Crypto_00067 */
    else if ( (cryptAlgoFam == CRYPTO_ALGOFAM_AES) && (   (Crypto_mode_sym == CryptoDriver_SYMCIPHER_RESERVED) || (Crypto_padding == CryptoDriver_PADDINGMODE_RESERVED) )    )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00067 */
    else if ( (cryptAlgoFam == CRYPTO_ALGOFAM_RSA) && (Crypto_mode_asym == CryptoDriver_ASYMCIPHER_RESERVED)    )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        switch (opMode)
        {

        case CRYPTO_OPERATIONMODE_STREAMSTART:
        case CRYPTO_OPERATIONMODE_START:
        {
            if ((cryptAlgoFam == CRYPTO_ALGOFAM_AES))
            {
                if (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex)
                {
                    iv = ivElement->keyDataPtr;
                    iv_len = ivElement->keySize;
                }

                ret = Crypto_82_Hsm_SymC_Decrypt_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                       Crypto_padding, cipher, cipher_len, (const uint8 *)iv, iv_len, msg, msg_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }

            break;
        }

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_SymC_Decrypt_Update(sessionData[driverObject->objectID], cipher, cipher_len, msg, msg_len);
            csaitriggered = TRUE;

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_SymC_Decrypt_Finish(sessionData[driverObject->objectID], msg, msg_len);
            csaitriggered = TRUE;

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:
        {
            if ((cryptAlgoFam == CRYPTO_ALGOFAM_AES))
            {
                if (CRYPTO_ALGOMODE_ECB != cryptAlgoModeIndex)
                {
                    iv = ivElement->keyDataPtr;
                    iv_len = ivElement->keySize;
                }

                /* Satisfies SWS_Crypto_00023 */
                ret = Crypto_82_Hsm_SymC_Decrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_sym,
                                                 Crypto_padding, cipher, cipher_len, (const uint8 *)iv, iv_len,
                                                 msg, msg_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }
            else if (cryptAlgoFam == CRYPTO_ALGOFAM_RSA)
            {
                sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_LOW_PRIORITY;

                /* Satisfies SWS_Crypto_00023 */
                ret = Crypto_82_Hsm_AsymC_Decrypt(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, Crypto_mode_asym,
                                                  cipher, cipher_len, msg, msg_len);
                driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
                csaitriggered = TRUE;
            }
            else
            {
                /* Do nothing */
            }

            break;
        }
        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            if (csaitriggered == TRUE)
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Rng_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) rng = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    VAR(uint8, AUTOMATIC) mode = driverObject->job->jobPrimitiveInfo->primitiveInfo->algorithm.family;

    /* Output data; Satisfies SWS_Crypto_00071 */
    /* Satisfies SWS_Crypto_00203 && SWS_Crypto_00204 */
   
    rng = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    /* TODO: Investigate how to handle this parameter with respect to output redirection */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) rng_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071*/
    if ( (rng == NULL_PTR) || (rng_len == NULL_PTR) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (*rng_len == 0u) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00067 */
    else if (!(   (mode == CRYPTO_ALGOFAM_RNG) || (mode == CRYPTO_ALGOFAM_DRBG)))
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        if (mode == CRYPTO_ALGOFAM_RNG)
        {
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Rng_True(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], rng, *rng_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
        }
        else
        {
            /* Do nothing */
        }

        if (mode == CRYPTO_ALGOFAM_DRBG)
        {
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Rng_Pseudo(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], rng, *rng_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;
        }
        else
        {
            /* Do nothing */
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_RngReseed_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) seed = NULL_PTR;

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

    /* Input data; Satisfies SWS_Crypto_00073 */

    seed = driverObject->job->jobPrimitiveInputOutput.inputPtr;

    /* TODO: Investigate how to handle this parameter with respect to input redirection */
    CONST(uint32, AUTOMATIC) seed_len = driverObject->job->jobPrimitiveInputOutput.inputLength;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071*/
    if (seed == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071*/
    else if ( (seed_len == 0u) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT  == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

        ret = Crypto_82_Hsm_Rng_Reseed(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], seed, seed_len);
        driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SignatureGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = NULL_PTR;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) sign = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;

    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo = MapSignAlgorithm(driverObject->job);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

    /* Input data; Satisfies SWS_Crypto_00073 */
    /* Output data; Satisfies SWS_Crypto_00071 && SWS_Crypto_00073 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    sign = driverObject->job->jobPrimitiveInputOutput.outputPtr;

    CONST(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;

    /* TODO: Investigate how to handle this parameter with respect to output redirection */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) sign_len = driverObject->job->jobPrimitiveInputOutput.outputLengthPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 */
    if ( (msg == NULL_PTR) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
       (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071*/
    else if ( ( (sign == NULL_PTR) || (sign_len == NULL_PTR) ) &&
         ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (msg_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
       (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (sign_len != NULL_PTR) && ( (*sign_len == 0u) && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) ))
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }
    
    /* Satisfies SWS_Crypto_00067 */
    else if (signAlgo == CryptoDriver_SIGN_RESERVED)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }

    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_LOW_PRIORITY;

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:

            ret = Crypto_82_Hsm_Sign_Generate_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, msg, msg_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        /* TODO: Investigate if this is correct implementation of start with respect to cycurHSM */
        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Sign_Generate_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, NULL_PTR, 0);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_Sign_Generate_Update(sessionData[driverObject->objectID], msg, msg_len);

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            (*sign_len) = (*sign_len) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE;/* PRQA S 3383  #In case the output length is too high, *sign_len will be overwritten by the csai with correct value. */
            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Sign_Generate_Finish(sessionData[driverObject->objectID], sign, sign_len);

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:

            (*sign_len) = (*sign_len) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE;/* PRQA S 3383  #In case the output length is too high, *sign_len will be overwritten by the csai with correct value. */

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Sign_Generate(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, msg, msg_len, sign, sign_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_SignatureVerify_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) err = E_OK;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) ret = ecy_hsm_CSAI_ERR_UNDEFINED;

    P2CONST(uint8, AUTOMATIC, AUTOMATIC) msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) sign = driverObject->job->jobPrimitiveInputOutput.secondaryInputPtr;
    VAR(Crypto_OperationModeType, AUTOMATIC) opMode = driverObject->job->jobPrimitiveInputOutput.mode;

    VAR(Crypto_82_Hsm_Service_SignAlgorithmType, AUTOMATIC) signAlgo = MapSignAlgorithm(driverObject->job);

    /* Clear Shared Memory Data for current Driver Object ID */
    Crypto_82_Hsm_Dispatch_SharedMemory_Clear(driverObject->objectID);

    /* Input data; Satisfies SWS_Crypto_00073 */
    /* Output data; Satisfies SWS_Crypto_00071 && SWS_Crypto_00073 */

    msg = driverObject->job->jobPrimitiveInputOutput.inputPtr;
    sign = driverObject->job->jobPrimitiveInputOutput.secondaryInputPtr;

    /* TODO: Investigate how to handle these parameters with respect to input redirection */
    VAR(uint32, AUTOMATIC) msg_len = driverObject->job->jobPrimitiveInputOutput.inputLength;
    VAR(uint32, AUTOMATIC) sign_len = driverObject->job->jobPrimitiveInputOutput.secondaryInputLength;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00070 && SWS_Crypto_00071 */
    if ( (msg == NULL_PTR) &&  ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
       (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    else if (  ((sign == NULL_PTR) || (driverObject->job->jobPrimitiveInputOutput.verifyPtr == NULL_PTR))
    && ( (opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00142 && SWS_Crypto_00071 */
    else if ( (msg_len == 0u) &&  ( (opMode == CRYPTO_OPERATIONMODE_STREAMSTART) ||
       (opMode == CRYPTO_OPERATIONMODE_UPDATE) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL) ) )
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    else if ( (sign_len == 0u) && ((opMode == CRYPTO_OPERATIONMODE_FINISH) || (opMode == CRYPTO_OPERATIONMODE_SINGLECALL)))
    {
        detErr = CRYPTO_E_PARAM_VALUE;
        err = E_NOT_OK;
    }

    /* Satisfies SWS_Crypto_00067 */
    else if (signAlgo == CryptoDriver_SIGN_RESERVED)
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        err = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        sessionData[driverObject->objectID].hSession = driverObject->sessionHandle;
        sessionData[driverObject->objectID].hJob = driverObject->jobHandle;
        sessionData[driverObject->objectID].priority = (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_LOW_PRIORITY;

        switch (opMode)
        {
        case CRYPTO_OPERATIONMODE_STREAMSTART:

            ret = Crypto_82_Hsm_Sign_Verify_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, msg, msg_len);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_START:

            ret = Crypto_82_Hsm_Sign_Verify_Start(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, NULL_PTR, 0);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        case CRYPTO_OPERATIONMODE_UPDATE:

            ret = Crypto_82_Hsm_Sign_Verify_Update(sessionData[driverObject->objectID], msg, msg_len);

            break;

        case CRYPTO_OPERATIONMODE_FINISH:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Sign_Verify_Finish(sessionData[driverObject->objectID], sign, sign_len, &verificationResult_global[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS]);

            break;

        case CRYPTO_OPERATIONMODE_SINGLECALL:

            /* Satisfies SWS_Crypto_00023 */
            ret = Crypto_82_Hsm_Sign_Verify(&sessionData[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS], driverObject->keyHandle, signAlgo, msg, msg_len, sign, sign_len, &verificationResult_global[(driverObject->objectID) % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS]);
            driverObject->jobHandle = sessionData[driverObject->objectID].hJob;

            break;

        default:

            ret = ecy_hsm_CSAI_ERR_UNDEFINED;

            break;
        }

        if (ret != ecy_hsm_CSAI_SUCCESS)
        {
            err = E_NOT_OK;
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, driverObject->job->jobId, ret);
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

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeySetValid_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;

    err = Crypto_82_Hsm_Job_KeySetValid(driverObject->job, driverObject->objectID);

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyGenerate_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;

    err = Crypto_82_Hsm_Job_KeyGenerate(driverObject, driverObject->job);

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyDerive_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;

    err = Crypto_82_Hsm_Job_KeyDerive(driverObject, driverObject->job);

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcPubVal_Dispatch (
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;

    err = Crypto_82_Hsm_Job_KeyExchangeCalcPubVal(driverObject, driverObject->job);

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_KeyExchangeCalcSecret_Dispatch(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;

    err = Crypto_82_Hsm_Job_KeyExchangeCalcSecret(driverObject, driverObject->job);

    return err;
}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_JobKeyGenerate_Cbk(
    VAR(uint32, AUTOMATIC) objectId
)
{
    VAR(uint32, AUTOMATIC) cryptoKeyId = Crypto_82_Hsm_driverObjects[objectId].job->cryptoKeyId;
    VAR(uint32, AUTOMATIC) indexKeyGenerate = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY, &indexKeyGenerate);

    if (indexKeyGenerate == CRYPTO_82_HSM_INVALID_KEY_INDEX)
    {
        (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_KEYGENERATE_KEY, &indexKeyGenerate);
    }

    if ((indexKeyGenerate != CRYPTO_82_HSM_INVALID_KEY_INDEX) && (cryptoKeyId < CRYPTO_82_HSM_NUMBER_OF_KEYS))
    {
        Crypto_82_Hsm_runtimeKeys[indexKeyGenerate].keyHandle = Crypto_82_Hsm_driverObjects[objectId].keyHandle;
        VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(cryptoKeyId, indexKeyGenerate);

        if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM)
        {
            Crypto_82_Hsm_KeyElementValidity[indexKeyGenerate] = TRUE;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)], cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */
        }
    }
}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_JobKeyDerive_Cbk(
    VAR(uint32, AUTOMATIC) objectId
)
{
    VAR(uint32, AUTOMATIC) targetCryptoKeyId = Crypto_82_Hsm_driverObjects[objectId].job->targetCryptoKeyId;
    VAR (uint32, AUTOMATIC) targetKeyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    (void)Crypto_82_Hsm_findKeyElement(targetCryptoKeyId, CRYPTO_KEYDERIVE_TARGETKEYELEMENT_ID, &targetKeyElementIndex);

    if ((targetKeyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX) && (targetCryptoKeyId < CRYPTO_82_HSM_NUMBER_OF_KEYS))
    {
        Crypto_82_Hsm_runtimeKeys[targetKeyElementIndex].keyHandle = Crypto_82_Hsm_driverObjects[objectId].keyHandle;

        VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(targetCryptoKeyId, targetKeyElementIndex);

        if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM)
        {
            Crypto_82_Hsm_KeyElementValidity[targetKeyElementIndex] = TRUE;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(targetCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)], targetCryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
#endif
        }
    }
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
