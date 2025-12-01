/**
 * \file Crypto_82_Hsm_DensoExtensions.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of Denso Extensions
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Compiler.h"
#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Porting.h"
#include "Crypto_82_Hsm_DensoExtensions.h"
#include "Crypto_82_Hsm_Mem.h"
#include "Crypto_82_Hsm_UserCallout.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/


/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/
#if ( CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON )
/**
 * \brief The different states of the process within the Crypto_82_Hsm_Ext_InjectKey function.
 */
typedef enum eExtInjectKey_State
{
    EXT_INJECT_KEY_NO_PROCESSING            = 0x00u,    /** This state represents the first call of the function                        */
    EXT_INJECT_KEY_PROCESS_INJECT           = 0x01u,    /** Process Key injection                                                       */
    EXT_INJECT_KEY_PROCESS_PERSIST          = 0x02u,    /** Process persisting of a key                                                 */
    EXT_INJECT_KEY_PROCESS_LOAD             = 0x03u,    /** Process loading of key from persistent storage to session context           */
    EXT_INJECT_KEY_PROCESS_RELEASE          = 0x04u,    /** Process Key releasing                                                       */
} ExtInjectKey_State;

/**
 * \brief The different states of the process within the Crypto_82_Hsm_Ext_SHELoadKey function.
 */
typedef enum eExtSHELoadKey_State
{
    EXT_SHE_LOAD_KEY_UPDATE                   = 0x00u,    /** Update she key material in persistent storage                               */
    EXT_SHE_LOAD_KEY_LOAD                     = 0x01u,    /** Load updated key material into session context                              */
    EXT_SHE_LOAD_KEY_FAILED_UPDATE            = 0x02u     /** Update she key material has failed                                          */
} ExtSHELoadKey_State;

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_INIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON)
static ExtSHELoadKey_State extSHELoadKeyState = EXT_SHE_LOAD_KEY_UPDATE;
static ExtInjectKey_State extInjectKeyState = EXT_INJECT_KEY_NO_PROCESSING;
static Crypto_82_Hsm_Ext_InjectKey_Operation extInjectKeyCurrentRequestedOperation = EXT_INJECT_KEY_OPERATION_NONE;
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */



#define CRYPTO_82_HSM_STOP_SEC_VAR_INIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"
#endif /* (CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON) */

#if ( CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON )

#define CRYPTO_82_HSM_START_SEC_VAR_INIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
/**
 * \brief Flags used by Crypto_82_Hsm_Ext_KeyValidtySerialize API in order to determine current location in process flow.
 */
static uint32 currentDirtyGroup = 0u;
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */


#define CRYPTO_82_HSM_STOP_SEC_VAR_INIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/* Array which holds key validity status only for persistent key material
 * This array will be serialized to HSM flash when Crypto_82_Hsm_Ext_KeyValiditySerialize is called
 */
uint8 keyStatusDataToBeSerialized[KEY_STATUS_DATA_ARRAY_SIZE];

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
/* Variable which is passed to ecy_hsm_Csai_ReadData, in Crypto_82_Hsm_Ext_Init. */
static uint32 dataCount;
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON)
/* KeyRef variable used in Crypto_82_Hsm_Ext_KeyElementGet and passed to CycurHSM function */
static ecy_hsm_Csai_KeyRefT publicKey_ext_keyElementGet;
#endif /* (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) */

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON)
/* KeyRef variable used in Crypto_82_Hsm_Ext_InjectKey and passed to CycurHSM function */
static ecy_hsm_Csai_KeyRefT hsmKeyData_inject;
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if (CRYPTO_82_HSM_FEE_REORG == STD_ON)
/* Variable which is passed to ecy_hsm_Csai_FEEMGR_CheckReorgOnWrite, in Crypto_82_Hsm_Ext_CheckReorgOnWrite. */
static ecy_hsm_Csai_FeeMgr_FeeParamT feeParams;
#endif /* (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) */

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
/**
 * \brief Array which holds the status of the key validity groups.
 * 
 * A value of TRUE in the array signifies that the key validity was changed and needs to be persisted.
*/
static boolean keyStatusGroupDirtyFlags[NUM_KEY_STATUS_SLOTS];
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

VAR(Crypto_82_Hsm_Ext_ApiType, CRYPTO_82_HSM_VAR) currentProcessedApi = CRYPTO_82_HSM_EXT_API_NONE;
VAR(Crypto_82_Hsm_Ext_ApiType, CRYPTO_82_HSM_VAR) currentProcessedApiDFlashReorg = CRYPTO_82_HSM_EXT_API_NONE;
VAR(uint32, CRYPTO_82_HSM_VAR) currentProcessed_arCryptoKeyId = CRYPTO_82_HSM_NUMBER_OF_KEYS;

#define CRYPTO_82_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"
#endif /* (CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON) */

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/


#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Choose the starting state of the Crypto_82_Hsm_Ext_InjectKey function.
 * 
 * \param[in] operation The requested injection operation.
 * 
 * \retval EXT_INJECT_KEY_PROCESS_INJECT        The requested operation begins with a key injection.
 * \retval EXT_INJECT_KEY_PROCESS_PERSIST       The requested operation is to persist a previously injected key to the NvM key store or to update the she ram key.
 * \retval EXT_INJECT_KEY_ERROR                 The requested operation is invalid.
*/
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
static FUNC(ExtInjectKey_State, CRYPTO_82_HSM_CODE) chooseInitialInjectKeyState(Crypto_82_Hsm_Ext_InjectKey_Operation operation);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

/**
 * \brief Choose the next state of the Crypto_82_Hsm_Ext_InjectKey function.
 * 
 * \param[in]       operation The requested injection operation.
 * \param[in]       currentFunctionState The current function state.
 * \param[in, out]  ret Pointer to the current return value of Crypto_82_Hsm_Ext_InjectKey.
 * \param[in]       arCryptoKeyId Id of AUTOSAR modelled key
 * 
 * \retval EXT_INJECT_KEY_PROCESS_INJECT        The inject operation is still in progress.
 * \retval EXT_INJECT_KEY_PROCESS_PERSIST       Next step in operation process is persisting of key.
 * \retval EXT_INJECT_KEY_PROCESS_LOAD          Next step in operation process is persisting of loading of key from persistent key storage.
 * \retval EXT_INJECT_KEY_PROCESS_RELEASE       Next step in operation process is releasing of key from session context.
*/
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON)
static FUNC(ExtInjectKey_State, CRYPTO_82_HSM_CODE) processExtInjectKeyStateMachine(Crypto_82_Hsm_Ext_InjectKey_Operation operation, ExtInjectKey_State currentFunctionState, Crypto_82_Hsm_Ext_ErrorStateType* ret, uint32 arCryptoKeyId);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if ( (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) )
/**
 * \brief Process the response of an immediate return CSAI call and return the appropriate error code.
 *
 * \note  This function is used with CSAI calls which returns its result immediately, there is no need for further
 * synchronization with CSAI_PollHandle(). This function tries to generalize the CSAI errors into the Crypto_82_Hsm_Ext_ErrorStateType type. The function
 * can be extended to accommodate more than one type for CSAI call by testing for a specific CSAI return error code.
 *
 * \param [in] csai_err The CSAI call response to be processed
 *
 * \retval CRYPTO_82_HSM_EXT_DONE  The CSAI request and response is complete, the output data can be used
 * \retval CRYPTO_82_HSM_EXT_BUSY  The CycurHSM is busy with another operation
 * \retval CRYPTO_82_HSM_EXT_ERROR The CSAI call returned an error
 */
static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIImmediateResponse(
    ecy_hsm_Csai_ErrorT csai_err
);
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */ 
#if ( (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_DENSO_KEY_VALIDITY  == STD_ON) || (CRYPTO_82_HSM_KEY_SETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) || (CRYPTO_82_HSM_KEY_LOADING  == STD_ON) || (CRYPTO_82_HSM_SHE_CANCEL  == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG  == STD_ON) || (CRYPTO_82_HSM_POWER_MODE  == STD_ON) || (CRYPTO_82_HSM_FEE_REORG == STD_ON) )
/**
 * \brief Process the response of a CSAI call and return the appropriate error code.
 *
 * \note This function tries to generalize the CSAI errors into the Crypto_82_Hsm_Ext_ErrorStateType type. The function
 * can be extended to accommodate more than one type for CSAI call by testing for a specific CSAI return error code.
 *
 * \param [in] api          The current processed API (see Crypto_82_Hsm_Ext_ApiType)
 * \param [in] csai_err     The CSAI call response to be processed
 *
 * \retval CRYPTO_82_HSM_EXT_PROCESSING     The current CSAI API is currently processing
 * \retval CRYPTO_82_HSM_EXT_BUSY           The CycurHSM is busy with another operation
 * \retval CRYPTO_82_HSM_EXT_ERROR          The CSAI call returned an error
 */
static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIResponse(
    const Crypto_82_Hsm_Ext_ApiType api,
    ecy_hsm_Csai_ErrorT csai_err
);

/**
 * \brief Process the job status for a CSAI call for the given API and job handle and return the appropriate error code.
 *
 * \param [in] api          The current processed API (see Crypto_82_Hsm_Ext_ApiType)
 * \param [in] jobHandle    The CSAI job handle
 *
 * \retval CRYPTO_82_HSM_EXT_DONE           The CSAI request and response is complete, the output data can be used.
 * \retval CRYPTO_82_HSM_EXT_PROCESSING     The current CSAI API is currently processing
 * \retval CRYPTO_82_HSM_EXT_ERROR          The CSAI call returned an error
 */
static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIPollStatus(
    const Crypto_82_Hsm_Ext_ApiType api,
    ecy_hsm_Csai_JobHandleT jobHandle
);
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_DENSO_KEY_VALIDITY  == STD_ON) || (CRYPTO_82_HSM_KEY_SETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) || (CRYPTO_82_HSM_KEY_LOADING  == STD_ON) || (CRYPTO_82_HSM_SHE_CANCEL  == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG  == STD_ON) || (CRYPTO_82_HSM_POWER_MODE  == STD_ON) || (CRYPTO_82_HSM_FEE_REORG == STD_ON) */

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
/**
 * \brief Determine if at least one key validity group is dirty.
 * 
 * \param [in]  groups      Pointer to the start of the dirty flag array
 * \param [in]  numGroups   The total nuber of groups in the array (the number of elements)
 * \param [out] whichGroup  Index of the first dirty group in the array
 * 
 * \retval TRUE     At least one group is dirty
 * \retval FALSE    No group is dirty
*/
static INLINE FUNC(boolean, CRYPTO_82_HSM_CODE) isAtLeastOneKeyStatusGroupDirty(
    boolean* groups,
    uint32 numGroups,
    uint32* whichGroup
);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

/**
 * \brief Initializes one key data pointer with the content of another key data pointer.
 *
 * \param [out] keyDataPtr          Pointer to variable which will be set with the key type and information about the key depending on the key type.
 * \param [in]  pKeyData            Pointer to variable which holds key type and information about the key depending on the key type.
 */
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON)
static FUNC(void, CRYPTO_82_HSM_CODE) assignKeyData(
    ecy_hsm_Csai_KeyRefT* keyDataPtr,
    Crypto_82_Hsm_KeyDataType* pKeyData
);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

/**
 * \brief Determines whether the input key data matches the key element index type/size. This check is used for the injection data.
 * 
 * \param [in] arCryptoKeyId       The AUTOSAR modelled key Id.
 * \param [in] keyElementIndex     Key element index.
 * \param [in] pKeyData            Pointer to variable which holds key type and information about the key depending on the key type.
 * 
 * \retval TRUE     Key data matches the key element index type/size.
 * \retval FALSE    Key data does not match the key element index type/size.
*/
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON)
static FUNC(boolean, CRYPTO_82_HSM_CODE) isKeyDataValid (
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementIndex,
    P2VAR(Crypto_82_Hsm_KeyDataType, AUTOMATIC, AUTOMATIC) pKeyData /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/
#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
static FUNC(ExtInjectKey_State, CRYPTO_82_HSM_CODE) chooseInitialInjectKeyState(Crypto_82_Hsm_Ext_InjectKey_Operation operation)
{
    VAR(ExtInjectKey_State, AUTOMATIC) injectKeyState = EXT_INJECT_KEY_NO_PROCESSING;

    switch(operation)
    {   
        case EXT_INJECT_KEY_OPERATION_INJECT:

            injectKeyState =  EXT_INJECT_KEY_PROCESS_INJECT;

        break;

        case EXT_INJECT_KEY_OPERATION_INJECT_AND_PERSIST:

            injectKeyState =  EXT_INJECT_KEY_PROCESS_INJECT;

        break;

        case EXT_INJECT_KEY_OPERATION_PERSIST:

            injectKeyState =  EXT_INJECT_KEY_PROCESS_PERSIST;

        break;

        default:
        /* Do nothing; shoud never get here */
        break;
    }

    return injectKeyState;
}
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
static FUNC(ExtInjectKey_State, CRYPTO_82_HSM_CODE) processExtInjectKeyStateMachine(Crypto_82_Hsm_Ext_InjectKey_Operation operation, ExtInjectKey_State currentFunctionState, Crypto_82_Hsm_Ext_ErrorStateType* ret, uint32 arCryptoKeyId)
{
    VAR(ExtInjectKey_State, AUTOMATIC) injectKeyState = EXT_INJECT_KEY_NO_PROCESSING;
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

    if (*ret == CRYPTO_82_HSM_EXT_DONE)
    {
        /* Transition into the next internal function states based on the operation and the previous internal function state */
        switch(operation)
        {
            case EXT_INJECT_KEY_OPERATION_INJECT:

                if ( (isSheRamKey(arCryptoKeyId)) && (currentFunctionState == EXT_INJECT_KEY_PROCESS_INJECT) )
                {
                    injectKeyState =  EXT_INJECT_KEY_PROCESS_LOAD;
                    *ret = CRYPTO_82_HSM_EXT_PROCESSING;
                }

            break;

            case EXT_INJECT_KEY_OPERATION_INJECT_AND_PERSIST:

                if (currentFunctionState == EXT_INJECT_KEY_PROCESS_INJECT)
                {
                    injectKeyState = EXT_INJECT_KEY_PROCESS_PERSIST;

                    *ret = CRYPTO_82_HSM_EXT_PROCESSING;
                }
                else if (currentFunctionState == EXT_INJECT_KEY_PROCESS_RELEASE)
                {
                    /* Persisting the key failed, but the injected key was succesfully released from session context */
                    *ret = CRYPTO_82_HSM_EXT_ERROR;

                    Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);
                    
                    Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle = INVALID_KEY_HANDLE_VALUE;
                }
                else
                {
                    /* Do nothing */
                 }

            break;


            default:
            /* Do nothing */
            break;
        }
    }
    else if (*ret == CRYPTO_82_HSM_EXT_ERROR)
    {
        if (operation == EXT_INJECT_KEY_OPERATION_INJECT_AND_PERSIST)
        {

            if (currentFunctionState == EXT_INJECT_KEY_PROCESS_PERSIST)
            {
                injectKeyState = EXT_INJECT_KEY_PROCESS_RELEASE;
                *ret = CRYPTO_82_HSM_EXT_PROCESSING;
            }
            else if (currentFunctionState == EXT_INJECT_KEY_PROCESS_RELEASE)
            {
                *ret = CRYPTO_82_HSM_EXT_FAILED_KEY_RELEASE_AFTER_ERROR;
            }
            else
            {
                /* Do nothing; should never get here */
            }
        }
    }
    else /*  *ret == CRYPTO_82_HSM_EXT_PROCESSING */
    {
        injectKeyState = currentFunctionState;
    }

    return injectKeyState;
}
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
static INLINE FUNC(boolean, CRYPTO_82_HSM_CODE) isAtLeastOneKeyStatusGroupDirty(
    boolean* groups,
    uint32 numGroups,
    uint32* whichGroup
)
{
    boolean atLeastOneGroupIsDirty = FALSE;

    /* Find at least one dirty flag */
    for (uint32 i = 0; (i < numGroups) && (atLeastOneGroupIsDirty == FALSE); ++i)
    {
        if (groups[i] == TRUE)
        {
            atLeastOneGroupIsDirty = TRUE;

            if (whichGroup != NULL_PTR)
            {
                *whichGroup = i;
            }
        }
    }

    return atLeastOneGroupIsDirty;
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if ( (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) )
static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIImmediateResponse(
    ecy_hsm_Csai_ErrorT csai_err
)
{
    Crypto_82_Hsm_Ext_ErrorStateType ret;

    if (csai_err == ecy_hsm_CSAI_SUCCESS)
    {
        currentProcessedApi = CRYPTO_82_HSM_EXT_API_NONE;
        ret = CRYPTO_82_HSM_EXT_DONE;
    }
    else if (csai_err == ecy_hsm_CSAI_FC_BUSY)
    {
        ret = CRYPTO_82_HSM_EXT_BUSY;
    }
    else
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
static FUNC(void, CRYPTO_82_HSM_CODE) assignKeyData(
    ecy_hsm_Csai_KeyRefT* keyDataPtr,
    Crypto_82_Hsm_KeyDataType* pKeyData
)
{
    keyDataPtr->type = KEYTYPE_RESERVED;

    switch(pKeyData->keyType)
    {
        case Crypto_82_Hsm_KEYTYPE_SYMMETRIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_SYMMETRIC;
            keyDataPtr->u.sym.key = pKeyData->keyContainer.sym.keyBuffer;
            keyDataPtr->u.sym.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.sym.keySize;
            keyDataPtr->u.sym.length = pKeyData->keyContainer.sym.bufferLength;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_RSA_PAIR:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_RSA_PAIR;
            keyDataPtr->u.rsapair.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.rsapair.keySize;
            keyDataPtr->u.rsapair.n = pKeyData->keyContainer.rsapair.n;
            keyDataPtr->u.rsapair.nLength = pKeyData->keyContainer.rsapair.nLength;
            keyDataPtr->u.rsapair.d = pKeyData->keyContainer.rsapair.d;
            keyDataPtr->u.rsapair.dLength = pKeyData->keyContainer.rsapair.dLength;
            keyDataPtr->u.rsapair.e = pKeyData->keyContainer.rsapair.e;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_RSA_PUBLIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC;
            keyDataPtr->u.rsapub.keySize = (uint16)pKeyData->keyContainer.rsapub.keySize;
            keyDataPtr->u.rsapub.n = pKeyData->keyContainer.rsapub.n;
            keyDataPtr->u.rsapub.nLength = pKeyData->keyContainer.rsapub.nLength;
            keyDataPtr->u.rsapub.e = pKeyData->keyContainer.rsapub.e;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_EDDSA_PAIR:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR;
            keyDataPtr->u.eddsapair.privKeyLength = pKeyData->keyContainer.eddsapair.privKeyLength;
            keyDataPtr->u.eddsapair.pubKeyLength = pKeyData->keyContainer.eddsapair.pubKeyLength;
            keyDataPtr->u.eddsapair.privKey = pKeyData->keyContainer.eddsapair.privKey;
            keyDataPtr->u.eddsapair.pubKey = pKeyData->keyContainer.eddsapair.pubKey;
            keyDataPtr->u.eddsapair.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.eddsapair.keySize;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_EDDSA_PUBLIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC;
            keyDataPtr->u.eddsapub.pubKeyLength = pKeyData->keyContainer.eddsapub.pubKeyLength;
            keyDataPtr->u.eddsapub.pubKey = pKeyData->keyContainer.eddsapub.pubKey;
            keyDataPtr->u.eddsapub.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.eddsapub.keySize;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_ECDSA_PAIR:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR;
            keyDataPtr->u.eccpair.privKeyLength = pKeyData->keyContainer.eccpair.privKeyLength;
            keyDataPtr->u.eccpair.pubKeyLength = pKeyData->keyContainer.eccpair.pubKeyLength;
            keyDataPtr->u.eccpair.privKey = pKeyData->keyContainer.eccpair.privKey;
            keyDataPtr->u.eccpair.pubKey = pKeyData->keyContainer.eccpair.pubKey;
            keyDataPtr->u.eccpair.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.eccpair.keySize;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_ECDSA_PUBLIC:
        {
            keyDataPtr->type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC;
            keyDataPtr->u.eccpub.pubKeyLength = pKeyData->keyContainer.eccpub.pubKeyLength;
            keyDataPtr->u.eccpub.pubKey = pKeyData->keyContainer.eccpub.pubKey;
            keyDataPtr->u.eccpub.keySize = (ecy_hsm_Csai_KeySizeT)pKeyData->keyContainer.eccpub.keySize;

            break;
        }

        case Crypto_82_Hsm_KEYTYPE_SECRET_EC_POINT:

            /* TODO: Implement key injection for this key type */

            break;

        default:

            /* Do nothing. CycurHsm will return error code in this case */
            break;
    }

}

static FUNC(boolean, CRYPTO_82_HSM_CODE) isKeyDataValid (
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementIndex,
    P2VAR(Crypto_82_Hsm_KeyDataType, AUTOMATIC, AUTOMATIC) pKeyData /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    boolean result = TRUE;
    VAR(uint32, AUTOMATIC) keySize;

        switch(Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType)
    {
        case ecy_hsm_CSAI_KEYTYPE_SYMMETRIC:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize;

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_SYMMETRIC)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.sym.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.sym.bufferLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.sym.keyBuffer == NULL_PTR)
            {
                result = FALSE;
            }            
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR:
        {
            keySize = (Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize - 4u) / 2u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_RSA_PAIR)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.rsapair.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapair.nLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapair.dLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapair.n == NULL_PTR)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapair.d == NULL_PTR)
            {
                result = FALSE;
            }                          
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize - 4u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_RSA_PUBLIC)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.rsapub.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapub.nLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.rsapub.n == NULL_PTR)
            {
                result = FALSE;
            }            
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize / 2u;
            
            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_EDDSA_PAIR)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.eddsapair.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapair.privKeyLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapair.pubKeyLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapair.privKey == NULL_PTR)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapair.pubKey == NULL_PTR)
            {
                result = FALSE;
            }                        
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize;

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_EDDSA_PUBLIC)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.eddsapub.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapub.pubKeyLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eddsapub.pubKey == NULL_PTR)
            {
                result = FALSE;
            }               
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize / 3u;

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_ECDSA_PAIR)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.eccpair.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpair.pubKeyLength != (keySize * 2u)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpair.privKeyLength != keySize)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpair.privKey == NULL_PTR)
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpair.pubKey == NULL_PTR)
            {
                result = FALSE;
            }             
            else
            {
                /* Do nothing */
            }               

            break;
        }

        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC:
        {
            keySize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize / 2u;

            if(pKeyData->keyType != Crypto_82_Hsm_KEYTYPE_ECDSA_PUBLIC)
            {
                result = FALSE;
            }
            else if((uint32)pKeyData->keyContainer.eccpub.keySize != (keySize * CRYPTO_82_HSM_NUM_BITS_IN_BYTE)) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpub.pubKeyLength != (keySize * 2u)) /* PRQA S 3383  #Wraparound can not occur in this case. */
            {
                result = FALSE;
            }
            else if (pKeyData->keyContainer.eccpub.pubKey == NULL_PTR)
            {
                result = FALSE;
            }               
            else
            {
                /* Do nothing */
            }               

            break;
        }
        
        case ecy_hsm_CSAI_KEYTYPE_SECRET_EC_POINT:
        {
            /* TODO: Implement key injection for this key type */
            break;
        }

        default:
            result = FALSE;
            break;
    }

    return result;
}
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if ( (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_DENSO_KEY_VALIDITY  == STD_ON) || (CRYPTO_82_HSM_KEY_SETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) || (CRYPTO_82_HSM_KEY_LOADING  == STD_ON) || (CRYPTO_82_HSM_SHE_CANCEL  == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG  == STD_ON) || (CRYPTO_82_HSM_POWER_MODE  == STD_ON) || (CRYPTO_82_HSM_FEE_REORG == STD_ON) )
static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIResponse(
    const Crypto_82_Hsm_Ext_ApiType api,
    ecy_hsm_Csai_ErrorT csai_err
)
{
    Crypto_82_Hsm_Ext_ErrorStateType ret;

    if (csai_err == ecy_hsm_CSAI_SUCCESS)
    {
#if (CRYPTO_82_HSM_FEE_REORG == STD_ON)
            if ((api == CRYPTO_82_HSM_EXT_API_CHECKREORGONWRITE) || (api == CRYPTO_82_HSM_EXT_API_TRIGGERFLASHREORG))
            {
                currentProcessedApiDFlashReorg = api;
            }
            else
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */
            {
                currentProcessedApi = api;
            }

            ret = CRYPTO_82_HSM_EXT_PROCESSING;
    }
    else if (csai_err == ecy_hsm_CSAI_FC_BUSY)
    {
        ret = CRYPTO_82_HSM_EXT_BUSY;
    }
    else
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }

    return ret;
}

static FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) processCSAIPollStatus(
    const Crypto_82_Hsm_Ext_ApiType api,
    ecy_hsm_Csai_JobHandleT jobHandle
)
{
    Crypto_82_Hsm_Ext_ErrorStateType ret;
    ecy_hsm_Csai_ErrorT status;
#if ((CRYPTO_82_HSM_SHE_CANCEL == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG == STD_ON))
    SHE_ErrorCodeT she_err;

    /** For SHE_ interfaces, the SHE_Sync() shall be used */
    if (api == CRYPTO_82_HSM_EXT_API_SHE_CANCEL ||
        api == CRYPTO_82_HSM_API_SHE_CMDDEBUG )
    {
        she_err = SHE_Sync();

        if (she_err == ERC_NO_ERROR)
        {
            status = ecy_hsm_CSAI_SUCCESS;
        }
        else if (she_err == ERC_BUSY)
        {
            status = ecy_hsm_CSAI_FC_PENDING;
        }
        else
        {
            status = ecy_hsm_CSAI_ERR_UNDEFINED;
        }
    }
    else
#endif /* ((CRYPTO_82_HSM_SHE_CANCEL == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG == STD_ON))*/
    {
        /* Process the CSAI response */
        status = ecy_hsm_Csai_PollHandle(jobHandle);
    }


    switch (status)
    {
    case ecy_hsm_CSAI_SUCCESS:
#if (CRYPTO_82_HSM_FEE_REORG == STD_ON)
        if((api == CRYPTO_82_HSM_EXT_API_CHECKREORGONWRITE)||(api == CRYPTO_82_HSM_EXT_API_TRIGGERFLASHREORG))
        {
            currentProcessedApiDFlashReorg = CRYPTO_82_HSM_EXT_API_NONE;
        }
        else
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */
        {
            currentProcessedApi = CRYPTO_82_HSM_EXT_API_NONE;
        }
        ret = CRYPTO_82_HSM_EXT_DONE;
        currentProcessed_arCryptoKeyId = CRYPTO_82_HSM_NUMBER_OF_KEYS;  /*reset value*/
        break;

    case ecy_hsm_CSAI_FC_PENDING:
        ret = CRYPTO_82_HSM_EXT_PROCESSING;
        break;

    default:
#if (CRYPTO_82_HSM_FEE_REORG == STD_ON)
        if((api == CRYPTO_82_HSM_EXT_API_CHECKREORGONWRITE)||(api == CRYPTO_82_HSM_EXT_API_TRIGGERFLASHREORG))
        {
            currentProcessedApiDFlashReorg = CRYPTO_82_HSM_EXT_API_NONE;
        }
        else
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */
        {
            currentProcessedApi = CRYPTO_82_HSM_EXT_API_NONE;
        }
        ret = CRYPTO_82_HSM_EXT_ERROR;
        currentProcessed_arCryptoKeyId = CRYPTO_82_HSM_NUMBER_OF_KEYS; /*reset value*/
        break;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) || (CRYPTO_82_HSM_DENSO_KEY_VALIDITY  == STD_ON) || (CRYPTO_82_HSM_KEY_SETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) || (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) || (CRYPTO_82_HSM_KEY_LOADING  == STD_ON) || (CRYPTO_82_HSM_SHE_CANCEL  == STD_ON) || (CRYPTO_82_HSM_SHE_DEBUG  == STD_ON) || (CRYPTO_82_HSM_POWER_MODE  == STD_ON) || (CRYPTO_82_HSM_FEE_REORG == STD_ON) */
/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)  
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_Init(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyStatusPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

    currentDirtyGroup = 0u;

    /* TODO: replace with Crypto_Memset_s */
    /* Set initial key status in ram buffer to invalid */
    for (i = 0u; i < KEY_STATUS_DATA_ARRAY_SIZE; i++)
    {
        keyStatusDataToBeSerialized[i] = 0x00u;
    }

    /* Consider all the groups as not dirty */
    for (i = 0u; i < NUM_KEY_STATUS_SLOTS; i++)
    {
        keyStatusGroupDirtyFlags[i] = FALSE;
    }

    for(i = 0u; i <= CRYPTO_82_HSM_NUMBER_OF_KEYS/NUM_KEY_STATUS_SLOTS_PER_SECRET_DATA_SLOT; i++)
    {
        csai_err = ecy_hsm_Csai_ReadData(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], (uint32)KEY_STATUS_STORE_ID_START + i, (void*) &keyStatusDataToBeSerialized[i * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES], SIZE_OF_SECRET_DATA_SLOT_IN_BYTES, &dataCount, jobHandle); /* PRQA S 3383  #Wraparound can not occur in this case. */

        ret = processCSAIResponse(CRYPTO_82_HSM_EXT_API_INIT, csai_err);

        if (ret == CRYPTO_82_HSM_EXT_PROCESSING)
        {
            do
            {
                ret = processCSAIPollStatus(CRYPTO_82_HSM_EXT_API_INIT, *jobHandle);
            }
            while(ret == CRYPTO_82_HSM_EXT_PROCESSING);
        }

        ret = CRYPTO_82_HSM_EXT_DONE;
    }

    for (i = 0u; i < CRYPTO_82_HSM_NUMBER_OF_KEYS; i++)
    {
        Crypto_82_Hsm_GetKeyElementIndex(i, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

        /* If this is a RAM key element set to invalid. */
        if (keyElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            keyStatusPtr = &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(i) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)]; /* PRQA S 3384  #Wraparound can not occur in this case. */

            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, keyStatusPtr, i);
        }
        
        /* TODO: add this as the default value in Crypto_82_Hsm_GetKeyElementIndex */
        keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHELoadKey( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId,
    const uint8* m1,
    const uint8* m2,
    const uint8* m3,
    uint8* m4,
    uint8* m5,
    uint8 bankNumber
)
{
    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_SHE_LOADKEY;

    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_FLAG_ERROR;
    VAR(uint32, AUTOMATIC) keyMaterialElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) proofElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
    Crypto_82_Hsm_KeyStatusType keyStatus;
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */


    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if ((m1 == NULL_PTR) || (m2 == NULL_PTR) || (m3 == NULL_PTR) || (m4 == NULL_PTR) || (m5 == NULL_PTR))
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
        P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyStatusPtr = &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)% KEY_STATUS_DATA_ARRAY_SIZE]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3384  #Wraparound can not occur in this case. */
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            switch(extSHELoadKeyState)
            {
                case EXT_SHE_LOAD_KEY_UPDATE:

                    /* The SHE key is within the first range */
                    if (bankNumber == 0u)
                    {
                        csai_err = ecy_hsm_Csai_She_LoadKey(
                            session,
                            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY,
                            m1, m2, m3, m4, m5,
                            jobHandle
                        );
                    }
                    /* The SHE key is in the extended range */
                    else if (bankNumber == 1u)
                    {
                        csai_err = ecy_hsm_Csai_She_LoadKeyExtended(
                            session,
                            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY,
                            m1, m2, m3, m4, m5,
                            jobHandle
                        );
                    }
                    else
                    {
                        /** TODO: Verify the return code for invalid bankNumber */
                        csai_err = ecy_hsm_Csai_She_LoadKeyToBank(
                            session,
                            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY,
                            m1, m2, m3, m4, m5,
                            bankNumber,
                            jobHandle
                        );
                    }

                    if(csai_err == ecy_hsm_CSAI_SUCCESS)
                    {
                        Crypto_82_Hsm_KeyState[arCryptoKeyId].keyValid = FALSE;
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyMaterialElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);
            
                        if (keyMaterialElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
                            Crypto_82_Hsm_KeyElementValidity[keyMaterialElementIndex] = FALSE;
                        }
                    }

                break;

                /* LoadKey into session context */
                case EXT_SHE_LOAD_KEY_LOAD:
                case EXT_SHE_LOAD_KEY_FAILED_UPDATE:                

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)  
                    (void)Crypto_82_Hsm_Ext_KeyStatusRead(arCryptoKeyId, &keyStatus);
                    if ( (extSHELoadKeyState == EXT_SHE_LOAD_KEY_LOAD) || (keyStatus == CRYPTO_82_HSM_KEY_VALID) )
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */
                    {
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyMaterialElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

                        if (keyMaterialElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
                            csai_err = ecy_hsm_Csai_LoadKey(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId,
                                                        Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType,
                                                        &Crypto_82_Hsm_runtimeKeys[keyMaterialElementIndex].keyHandle, jobHandle);

                        }
                    }

                break;

                default:
                /*Do Nothing*/
                break;
            }


            ret = processCSAIResponse(thisApi, csai_err);
        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }

        if (ret == CRYPTO_82_HSM_EXT_DONE)
        {
            if ( extSHELoadKeyState == EXT_SHE_LOAD_KEY_UPDATE)
            {
                extSHELoadKeyState = EXT_SHE_LOAD_KEY_LOAD;

                ret = CRYPTO_82_HSM_EXT_PROCESSING;
            }
            else
            {
                /* Update key validity and availability in ram */
                Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyMaterialElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

                Crypto_82_Hsm_KeyElementValidity[keyMaterialElementIndex] = TRUE;

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                /* Set Denso Extensions validity */
                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, keyStatusPtr, arCryptoKeyId);

                Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(arCryptoKeyId);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

                (void)Crypto_82_Hsm_findKeyElement(arCryptoKeyId, CRYPTO_KE_MAC_PROOF, &proofElementIndex);

                if (proofElementIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    (void)Crypto_82_Hsm_findKeyElement(arCryptoKeyId, CRYPTO_KE_CIPHER_PROOF, &proofElementIndex);
                }

                if (proofElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {

                    /* There is no m4,m5 to copy if update failed. */
                    if (extSHELoadKeyState != EXT_SHE_LOAD_KEY_FAILED_UPDATE)
                    {
                        Crypto_82_Hsm_KeyElementValidity[proofElementIndex] = TRUE;
                        (void)Crypto_82_Hsm_Memcpy_s(Crypto_82_Hsm_configKeyElements[proofElementIndex].keyDataPtr, M4_SIZE, m4, M4_SIZE, M4_SIZE);
                        (void)Crypto_82_Hsm_Memcpy_s(&(Crypto_82_Hsm_configKeyElements[proofElementIndex].keyDataPtr[M4_SIZE]), M5_SIZE, m5, M5_SIZE, M5_SIZE);
                    }
                }
            }

            if (extSHELoadKeyState == EXT_SHE_LOAD_KEY_FAILED_UPDATE)
            {
                ret = CRYPTO_82_HSM_EXT_ERROR;
                Crypto_82_Hsm_UpdateKeyValidity(arCryptoKeyId); /* Setting the key back to valid since the previous valid SHE Key has been loaded back into session context - DN_EXT_SWS_Crypto_064 */
            }
        }
#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )
        else if ( (extSHELoadKeyState == EXT_SHE_LOAD_KEY_UPDATE) && (ret == CRYPTO_82_HSM_EXT_ERROR) )
        {
            extSHELoadKeyState = EXT_SHE_LOAD_KEY_FAILED_UPDATE;

            ret = CRYPTO_82_HSM_EXT_PROCESSING;
        }
#endif
        else if (ret == CRYPTO_82_HSM_EXT_ERROR)
        {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
            /* Set Denso Extensions validity */
            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, keyStatusPtr, arCryptoKeyId);

            Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(arCryptoKeyId);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */
        }
        else
        {
            /* Do nothing. */
        }

        /* Make sure flags are always reset */
        if ( (ret == CRYPTO_82_HSM_EXT_DONE) || (ret == CRYPTO_82_HSM_EXT_ERROR) )
        {
            extSHELoadKeyState = EXT_SHE_LOAD_KEY_UPDATE;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyElementGet( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) keyBuffer, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) bufferLen
)
{
    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_KEY_ELEMENT_GET;

    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC)  ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err;
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, CRYPTO_82_HSM_VAR) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (keyBuffer == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (bufferLen == 0u)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            if (isSheRamKey(arCryptoKeyId))
            {
                if(bufferLen < TOTAL_SHE_RAM_KEY_BUFFER_LEN)
                {
                    ret = CRYPTO_82_HSM_EXT_ERROR;
                }
                else
                {
                    uint8 *m1 = &keyBuffer[0];
                    uint8 *m2 = &keyBuffer[M1_SIZE];
                    uint8 *m3 = &keyBuffer[M1_SIZE + M2_SIZE];
                    uint8 *m4 = &keyBuffer[M1_SIZE + M2_SIZE + M3_SIZE];
                    uint8 *m5 = &keyBuffer[M1_SIZE + M2_SIZE + M3_SIZE + M4_SIZE];

                    csai_err = ecy_hsm_Csai_She_ExportRamKey(
                        session,
                        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
                        m1, m2, m3, m4, m5,
                        jobHandle
                    );
                    ret = processCSAIResponse(thisApi, csai_err);
                }
            }
            else
            {
                Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);
                if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    uint32 keyElementSize = 0u;

                    switch(Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType)
                    {
                        case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR: 
                        {  
                            keyElementSize = ((Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize - 4u) / 2u) + 4u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
                            break;
                        }

                        case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR: 
                        {  
                            keyElementSize = (Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize / 3u) * 2u; /* PRQA S 3384  #Wraparound can not occur in this case if a correct configuration is provided. */
                            break;
                        }

                        case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR: 
                        {  
                            keyElementSize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize/ 2u;
                            break;
                        }

                        default:
                        {  
                            keyElementSize = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize;
                            break;
                        }
                    }

                    if(bufferLen < keyElementSize)
                    {
                        ret = CRYPTO_82_HSM_EXT_ERROR;
                    }
                    else
                    {
                        if (bufferLen > Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize)
                        {
                            bufferLen = Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize;
                        }

                        switch (Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType)
                        {
                            case ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC:
                            case ecy_hsm_CSAI_KEYTYPE_RSA_PAIR:
                                publicKey_ext_keyElementGet.type = ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC;
                                publicKey_ext_keyElementGet.u.rsapub.n = keyBuffer;
                                publicKey_ext_keyElementGet.u.rsapub.nLength = bufferLen - 4u; /* PRQA S 3383 #Wraparound can not occur in this case if a correct configuration is provided. */
                                break;

                            case ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC:
                            case ecy_hsm_CSAI_KEYTYPE_EDDSA_PAIR:
                                publicKey_ext_keyElementGet.type = ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC;
                                publicKey_ext_keyElementGet.u.eddsapub.pubKey = keyBuffer;
                                publicKey_ext_keyElementGet.u.eddsapub.pubKeyLength = bufferLen;
                                break;

                            case ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC:
                            case ecy_hsm_CSAI_KEYTYPE_ECDSA_PAIR:
                                publicKey_ext_keyElementGet.type = ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC;
                                publicKey_ext_keyElementGet.u.eccpub.pubKey = keyBuffer;
                                publicKey_ext_keyElementGet.u.eccpub.pubKeyLength = bufferLen;
                                break;

                            default:
                                publicKey_ext_keyElementGet.type = ecy_hsm_CSAI_KEYTYPE_RESERVED;
                                publicKey_ext_keyElementGet.u.rsapub.n = NULL_PTR;
                                publicKey_ext_keyElementGet.u.rsapub.nLength = 0u;
                                break;
                        }

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
                        if(publicKey_ext_keyElementGet.type == ecy_hsm_CSAI_KEYTYPE_RESERVED)
                        {
                            ret = CRYPTO_82_HSM_EXT_ERROR;
                        }
                        else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
                        {
                            csai_err = ecy_hsm_Csai_ReadPublicKey(
                                session,
                                (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
                                Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle,
                                &publicKey_ext_keyElementGet,
                                jobHandle
                            );

                            ret = processCSAIResponse(thisApi, csai_err);
                        }
                    }
                }
                else
                {
                    ret = CRYPTO_82_HSM_EXT_ERROR;
                }
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
            if (ret == CRYPTO_82_HSM_EXT_DONE)
            {
                if ((Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType == ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC) || (Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType == ecy_hsm_CSAI_KEYTYPE_RSA_PAIR))
                {             
                    P2VAR(uint32, AUTOMATIC, AUTOMATIC)  rsaPub_e_Ptr = &publicKey_ext_keyElementGet.u.rsapub.e; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                    (void)Crypto_82_Hsm_Memcpy_s(&keyBuffer[bufferLen - 4u], 4u, rsaPub_e_Ptr, 4u, 4u); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
                }
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_KEY_RETRIEVAL == STD_ON) */

#if (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHEGetID( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    const uint8 challenge[16],
    uint8 id[15],
    uint8* status,
    uint8 mac[16]
)
{
    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_SHE_GET_ID;

    Crypto_82_Hsm_Ext_ErrorStateType ret = CRYPTO_82_HSM_EXT_INVALID;
    ecy_hsm_Csai_ErrorT csai_err;

    ecy_hsm_Csai_SessionHandleT session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    ecy_hsm_Csai_JobHandleT* jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (status == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON) */
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            csai_err = ecy_hsm_Csai_She_GetID(
                    session,
                    (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
                    challenge,
                    id,
                    status,
                    mac,
                    jobHandle
            );
            ret = processCSAIResponse(thisApi, csai_err);
        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }
    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) */

#if (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHEGetStatus( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint8* status
)
{
    Crypto_82_Hsm_Ext_ErrorStateType ret = CRYPTO_82_HSM_EXT_INVALID;
    ecy_hsm_Csai_ErrorT csai_err;

    ecy_hsm_Csai_SessionHandleT session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (status == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON) */
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            csai_err = ecy_hsm_Csai_She_GetStatus(
                    session,
                    status
            );
            ret = processCSAIImmediateResponse(csai_err);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }
    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_GET_ID_AND_STATUS == STD_ON) */

#if (CRYPTO_82_HSM_SHE_CANCEL == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHECancel( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    void
)
{
    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_SHE_CANCEL;
    Crypto_82_Hsm_Ext_ErrorStateType ret = CRYPTO_82_HSM_EXT_INVALID;
    ecy_hsm_Csai_ErrorT csai_err;
    ecy_hsm_Csai_JobHandleT* jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret =  CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
        }
        else if (currentProcessedApi != CRYPTO_82_HSM_EXT_API_NONE)
        {
            if (SHE_Cancel() == ERC_NO_ERROR)
            {
                csai_err = ecy_hsm_CSAI_SUCCESS;
            }
            else
            {
                csai_err = ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR;
            }

            ret = processCSAIResponse(thisApi, csai_err);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_DONE; /*nothing to cancel*/
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_CANCEL == STD_ON) */

#if (CRYPTO_82_HSM_KEY_SETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_InjectKey( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyDataType* pKeyData,
    uint32 keyProperties,
    Crypto_82_Hsm_Ext_InjectKey_Operation operation
)
{
    const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_INJECT_KEY;
    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC)  session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC)  jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = 0xFFFFFFFFUL;
    VAR(uint32, AUTOMATIC) WrongOpForRamKey = FALSE;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if ( (operation != EXT_INJECT_KEY_OPERATION_PERSIST)  && (pKeyData == NULL_PTR) )
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    } 
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            /* This is the first call of the function */
            if (extInjectKeyState == EXT_INJECT_KEY_NO_PROCESSING)
            {
                if (operation != EXT_INJECT_KEY_OPERATION_INJECT)
                {
                    Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_RAM_KEY_ELEMENT);
                    if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                    {
                        WrongOpForRamKey = TRUE;
                    }
                }

                if (WrongOpForRamKey != TRUE)
                {
                    extInjectKeyCurrentRequestedOperation = operation;
                    extInjectKeyState = chooseInitialInjectKeyState(operation);
                }
            }        

            if (operation != extInjectKeyCurrentRequestedOperation)
            {
                /* Function has been called with another operation mode before current operation has finished. Return error. */
                /* or wrong operation value for a RAM key*/
                ret = CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM;
            }
            else
            {
                /* Process a key operation based on the function state */
                switch(extInjectKeyState)
                {
                    case EXT_INJECT_KEY_PROCESS_INJECT:
                    {
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED);

                        if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
                            if ((isSheRamKey(arCryptoKeyId)) && (pKeyData->keyContainer.sym.bufferLength == SHE_RAM_KEY_SIZE))
                            {
                                csai_err = ecy_hsm_Csai_She_LoadPlainKey(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], pKeyData->keyContainer.sym.keyBuffer, jobHandle);
                            }
                            else if (!(isSheRamKey(arCryptoKeyId)))
                            {
                                ecy_hsm_Csai_KeyHandleT *keyHandle = &Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle;

                                if (isKeyDataValid(arCryptoKeyId, keyElementIndex, pKeyData) == TRUE)
                                {
                                    assignKeyData(&hsmKeyData_inject, pKeyData);

                                    csai_err = ecy_hsm_Csai_InjectKey(session, (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_MEDIUM_PRIORITY, &hsmKeyData_inject, keyProperties, keyHandle, jobHandle);
                                }
                            }
                            else
                            {
                                /* Do nothing. */
                            }

                            if (csai_err == ecy_hsm_CSAI_SUCCESS)
                            {
                                Crypto_82_Hsm_KeyState[arCryptoKeyId].keyValid = FALSE;
                                Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = FALSE;
                            }
                        }

                        break;
                    }

                    case EXT_INJECT_KEY_PROCESS_PERSIST:
                    {
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

                        if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
                            ecy_hsm_Csai_KeyHandleT *keyHandle = &Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle;

                            csai_err = ecy_hsm_Csai_WriteKeyToNvmKeyStore(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], *keyHandle, Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId, jobHandle);

                            if ((csai_err == ecy_hsm_CSAI_SUCCESS) && (operation == EXT_INJECT_KEY_OPERATION_PERSIST))
                            {
                                Crypto_82_Hsm_KeyState[arCryptoKeyId].keyValid = FALSE;
                                Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = FALSE;
                            }
                        }

                        break;
                    }         

                    case EXT_INJECT_KEY_PROCESS_LOAD:
                    {
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED);

                        csai_err = ecy_hsm_Csai_LoadKey(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId,
                                                        Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType, 
                                                        &Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle, jobHandle);

                        break;
                    }

                    case EXT_INJECT_KEY_PROCESS_RELEASE:
                    {
                        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

                        csai_err = ecy_hsm_Csai_ReleaseKey(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle, jobHandle);

                        break;
                    }
                            
                    default:
                    /* Do nothing; should never get here */
                    break;
                }

                ret = processCSAIResponse(thisApi, csai_err);

                if ( (ret == CRYPTO_82_HSM_EXT_ERROR) && (extInjectKeyState == EXT_INJECT_KEY_PROCESS_RELEASE) )
                {
                    ret = CRYPTO_82_HSM_EXT_FAILED_KEY_RELEASE_AFTER_ERROR;
                }    
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            if (operation != extInjectKeyCurrentRequestedOperation)
            {
                ret = CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM;
            }
            else
            {
                ret = processCSAIPollStatus(thisApi, *jobHandle);
                extInjectKeyState = processExtInjectKeyStateMachine(operation, extInjectKeyState, &ret, arCryptoKeyId);
            }

        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    /* Set key validity */
    if (ret == CRYPTO_82_HSM_EXT_DONE)
    {
        Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED);

        if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT)
        {
            Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = TRUE;
        }

        if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT)
        {
            if (operation != EXT_INJECT_KEY_OPERATION_INJECT)
            {
                Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = TRUE;
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyStatusPtr = &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */    /* PRQA S 3384  #Wraparound can not occur in this case. */
                /* Set Denso Extensions validity */
                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, keyStatusPtr, arCryptoKeyId);
                Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(arCryptoKeyId);
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */   
            }
        }
    }
    else if (ret == CRYPTO_82_HSM_EXT_ERROR)
    {
        if ( (operation == EXT_INJECT_KEY_OPERATION_INJECT_AND_PERSIST) && (extInjectKeyState == EXT_INJECT_KEY_PROCESS_PERSIST) )
        {
            ret = CRYPTO_82_HSM_EXT_PROCESSING;
            extInjectKeyState = EXT_INJECT_KEY_PROCESS_RELEASE;
        }
    }
    else
    {
        /* Do nothing. */
    }     

    if ((WrongOpForRamKey == TRUE) || ((ret != CRYPTO_82_HSM_EXT_PROCESSING) && (ret != CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM)) )
    {
        /* Reset state tracking variables */
        extInjectKeyState = EXT_INJECT_KEY_NO_PROCESSING;
        extInjectKeyCurrentRequestedOperation = EXT_INJECT_KEY_OPERATION_NONE;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_KEY_SETTING == STD_ON) */

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyStatusRead( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyStatusType* keyStatusPtr)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC)  ret = CRYPTO_82_HSM_EXT_INVALID;
  
#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsHsmInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if(keyStatusPtr == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
  
        VAR(uint8, AUTOMATIC) dataSlotByte = keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) + getKeyStatusSlotByteNumber(arCryptoKeyId)]; /* PRQA S 3384  #Wraparound can not occur in this case. */

        *keyStatusPtr = (Crypto_82_Hsm_KeyStatusType)((uint8)(dataSlotByte >> getKeyStatusSlotByteStartBitNumber(arCryptoKeyId) & 0x03u)); /* PRQA S 3384  #Wraparound can not occur in this. */

        ret = CRYPTO_82_HSM_EXT_DONE;       
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeySetValid( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId,
    Crypto_82_Hsm_KeyStatusType validity
)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC)  ret = CRYPTO_82_HSM_EXT_INVALID;

    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_KEY_SET_VALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            VAR(uint8, AUTOMATIC) dataSlotByte = keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) + getKeyStatusSlotByteNumber(arCryptoKeyId)]; /* PRQA S 3384  #Wraparound can not occur in this case. */
            P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyStatusPtr = &keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES)% KEY_STATUS_DATA_ARRAY_SIZE]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3384  #Wraparound can not occur in this case. */

            /* Once a key has been set to invalid it can't be set to valid by use of this API.*/
            if ( !(isKeyStatus(CRYPTO_82_HSM_KEY_INVALID, dataSlotByte, arCryptoKeyId)) ) /* PRQA S 3384  #Wraparound can not occur in this case. */
            {
                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(validity, keyStatusPtr, arCryptoKeyId);
                Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(arCryptoKeyId);

                /* If set status to invalid, releaseKey */
                if (validity == CRYPTO_82_HSM_KEY_INVALID)
                {
                    Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED);
                    Crypto_82_Hsm_KeyState[arCryptoKeyId].keyValid = FALSE;

                    if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                    {
                        Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = FALSE;

                        csai_err = ecy_hsm_Csai_ReleaseKey(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle, jobHandle);

                        ret = processCSAIResponse(thisApi, csai_err);
                    }
                    else
                    {
                        ret = CRYPTO_82_HSM_EXT_ERROR;
                    }

                }
                else
                {
                    ret = CRYPTO_82_HSM_EXT_DONE;
                }

            }
            else
            {
                ret = CRYPTO_82_HSM_EXT_ERROR;
            }

        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);

            Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED);

            if (ret == CRYPTO_82_HSM_EXT_DONE)
            {
                Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle = INVALID_KEY_HANDLE_VALUE;
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */  

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)  
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyValiditySerialize(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    Crypto_82_Hsm_Ext_ErrorStateType ret = CRYPTO_82_HSM_EXT_INVALID;

    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_KEY_VALIDITY_SERIALIZE;

    boolean atLeastOneGroupIsDirty = FALSE;

    ecy_hsm_Csai_ErrorT csai_err;

    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsHsmInitialized() == FALSE)
    {
        ret =  CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            /* Find at least one dirty flag */
            atLeastOneGroupIsDirty = isAtLeastOneKeyStatusGroupDirty(keyStatusGroupDirtyFlags, NUM_KEY_STATUS_SLOTS, &currentDirtyGroup);

            if (atLeastOneGroupIsDirty != FALSE)
            {
                VAR(uint32, AUTOMATIC) offset = SIZE_OF_SECRET_DATA_SLOT_IN_BYTES * currentDirtyGroup; /* PRQA S 3383  #Wraparound can not occur in this case. */
                VAR(uint32, AUTOMATIC) dataSlotId = (uint32) KEY_STATUS_STORE_ID_START + currentDirtyGroup; /* PRQA S 3383  #Wraparound can not occur in this case. */

                csai_err = ecy_hsm_Csai_WriteData(
                    session,
                    (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
                    dataSlotId,
                    (void*) &keyStatusDataToBeSerialized[offset % KEY_STATUS_DATA_ARRAY_SIZE],
                    SIZE_OF_SECRET_DATA_SLOT_IN_BYTES,
                    jobHandle
                );

                ret = processCSAIResponse(thisApi, csai_err);
            }
            else
            {
                currentDirtyGroup = 0u;

                /* Nothing to do. No dirty flag */
                ret = CRYPTO_82_HSM_EXT_DONE;
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        } 
    }
    if (ret == CRYPTO_82_HSM_EXT_DONE)
    {
        /* The current dirty group has been serialized */
        keyStatusGroupDirtyFlags[currentDirtyGroup] = FALSE;

        /* Verify if there are remaining dirty groups */
        atLeastOneGroupIsDirty = isAtLeastOneKeyStatusGroupDirty(keyStatusGroupDirtyFlags, NUM_KEY_STATUS_SLOTS, NULL_PTR);

        if (atLeastOneGroupIsDirty != FALSE)
        {
            ret = CRYPTO_82_HSM_EXT_PROCESSING;
        }
    }
    /* Make sure flags are reset if error occurs */
    else if (ret == CRYPTO_82_HSM_EXT_ERROR)
    {
        currentDirtyGroup = 0u;
    }
    else
    {
        /** Do nothing */
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId
)
{
    uint32 keyStatusGroup = getKeyStatusSlotNumber(arCryptoKeyId);

    keyStatusGroupDirtyFlags[keyStatusGroup] = TRUE;  
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */    

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SetKeyStatusBitMask( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    Crypto_82_Hsm_KeyStatusType keyStatus,
    uint8* bufferPtr,
    uint32 arCryptoKeyId
)
{
    uint32 keyStatusByte = getKeyStatusSlotByteNumber(arCryptoKeyId);
    uint8 keyStatusStartBit = (uint8)getKeyStatusSlotByteStartBitNumber(arCryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
    
     /* Set the 2 bits which will hold the key status to 0 */
    bufferPtr[keyStatusByte] &= ~(KEY_STATUS_BIT_MASK << keyStatusStartBit);

    /* Set the 2 bits which will hold the key status to the appropriate validity value */
    bufferPtr[keyStatusByte] |= (uint8)keyStatus << keyStatusStartBit;  
}
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */    

#if (CRYPTO_82_HSM_SHE_DEBUG == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_SHECmdDebug( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint8* authOrChallenge,
    boolean challengeFlag
)
{
    static const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_API_SHE_CMDDEBUG;
    Crypto_82_Hsm_Ext_ErrorStateType ret = CRYPTO_82_HSM_EXT_INVALID;
    ecy_hsm_Csai_ErrorT csai_err;
    SHE_ErrorCodeT err;
    ecy_hsm_Csai_JobHandleT* jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret =  CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            if(authOrChallenge != NULL_PTR)
            {
                if(TRUE == challengeFlag)
                {
                    err = SHE_CmdDebugChallenge(authOrChallenge);
                }else
                {
                    err = SHE_CmdDebugAuthorize((const uint8*)authOrChallenge);
                }

                if ( ERC_NO_ERROR == err)
                {
                    csai_err = ecy_hsm_CSAI_SUCCESS;
                }
                else
                {
                    csai_err = ecy_hsm_CSAI_LOCAL_ERR_SHE_ERC_GENERAL_ERROR;
                }

                ret =  processCSAIResponse(thisApi, csai_err);
            }
            else
            {
                ret = CRYPTO_82_HSM_EXT_ERROR;
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, *jobHandle);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_SHE_DEBUG == STD_ON) */

#if (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_ReleaseKey( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId
)
{
    const Crypto_82_Hsm_Ext_ApiType thisApi = CRYPTO_82_HSM_EXT_API_RELEASE_KEY;
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(ecy_hsm_Csai_SessionHandleT, AUTOMATIC) session = Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle;
    P2VAR(ecy_hsm_Csai_JobHandleT, AUTOMATIC, AUTOMATIC) jobHandle = &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)   
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /*CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT*/
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            getKeyMaterialElementIndex(&keyElementIndex, arCryptoKeyId);
            
            if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
            {
                csai_err = ecy_hsm_Csai_ReleaseKeyForce(session, (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS], (ecy_hsm_Csai_KeyIdT)Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle, jobHandle);

                ret = processCSAIResponse(thisApi, csai_err);
                currentProcessed_arCryptoKeyId = arCryptoKeyId;
            }
            else
            {
                ret = CRYPTO_82_HSM_EXT_ERROR;
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            if (currentProcessed_arCryptoKeyId != arCryptoKeyId)
            {
                /*During processing, the update of the key parameter is not allowed*/
                ret = CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM;
            }
            else
            {
                ret = processCSAIPollStatus(thisApi, *jobHandle);

                if (ret == CRYPTO_82_HSM_EXT_DONE)
                {
                    getKeyMaterialElementIndex(&keyElementIndex, arCryptoKeyId);

                    /*Invalid keyElementIndex is detected in first function call*/
                    Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = FALSE;
                    Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle = INVALID_KEY_HANDLE_VALUE;

                    /* Update Autosar validity to FALSE */
                    Crypto_82_Hsm_UpdateKeyValidity(arCryptoKeyId);
                }
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_KEY_RESETTING == STD_ON) */

#if (CRYPTO_82_HSM_KEY_LOADING == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_LoadKey( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId
)
{
    CONST(Crypto_82_Hsm_Ext_ApiType, AUTOMATIC) thisApi = CRYPTO_82_HSM_EXT_API_LOADKEY;
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;

    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
    /* Get Denso key validity */
    VAR(uint8, AUTOMATIC) dataSlotByte;
    VAR(Crypto_82_Hsm_KeyStatusType, AUTOMATIC) keyStatus;
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)

            dataSlotByte = keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(arCryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) + getKeyStatusSlotByteNumber(arCryptoKeyId)]; /* PRQA S 3384  #Wraparound can not occur in this case. */
            keyStatus = (Crypto_82_Hsm_KeyStatusType)((uint8)(dataSlotByte >> getKeyStatusSlotByteStartBitNumber(arCryptoKeyId) & 0x03u)); /* PRQA S 3384  #Wraparound can not occur in this case. */

            /* Check Denso key validity */
            if (keyStatus != CRYPTO_82_HSM_KEY_VALID)
            {
                ret = CRYPTO_82_HSM_EXT_ERROR;
            }
            else 
#endif /* (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON) */
            {
                currentProcessed_arCryptoKeyId = arCryptoKeyId;
                /* Check if key has a persistent element */
                Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);
                if(keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    ecy_hsm_Csai_KeyHandleT* keyHandle = &Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle;

                    csaiErr = ecy_hsm_Csai_LoadKey(
                    Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle,
                    (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
                    Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId,
                    Crypto_82_Hsm_configKeys[arCryptoKeyId].keyType,
                    keyHandle,
                    &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle
                    );

                    ret = processCSAIResponse(thisApi, csaiErr);
                }
                else
                {
                    ret = CRYPTO_82_HSM_EXT_ERROR;
                }
            }
        }
        else if (currentProcessedApi == thisApi)
        {
            if(arCryptoKeyId != currentProcessed_arCryptoKeyId)
            {
                ret = CRYPTO_82_HSM_EXT_INCONSISTENT_PARAM;
            }
            else
            {
                ret = processCSAIPollStatus(thisApi, Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle);

                if (ret == CRYPTO_82_HSM_EXT_DONE)
                {
                    Crypto_82_Hsm_GetKeyElementIndex(arCryptoKeyId, &keyElementIndex, CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT);

                    /* Set key element validity */
                    Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = TRUE;

                    /* Set Autosar key validity */
                    Crypto_82_Hsm_UpdateKeyValidity(arCryptoKeyId);
                }
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_KEY_LOADING == STD_ON) */

#if (CRYPTO_82_HSM_POWER_MODE == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_PowerModeConfig( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    void* pConfigData,
    uint32 configDataLen,
    Crypto_82_Hsm_Ext_PowerModeConfig_SleepMode sleepMode
)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;

    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)   
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (pConfigData == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (configDataLen == 0uL)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if ((sleepMode != EXT_POWER_MODE_DEEP_SLEEP) && (sleepMode != EXT_POWER_MODE_DEEP_SLEEP_EXTENDED))
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /*CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT*/
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            csaiErr = ecy_hsm_Csai_Config_PowerMode(
            Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle,
            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
            (ecy_hsm_Csai_ConfigPowerModeT)sleepMode,
            pConfigData,
            configDataLen,
            &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle
            );

            ret = processCSAIResponse(CRYPTO_82_HSM_EXT_API_NONE, csaiErr);

            if (ret == CRYPTO_82_HSM_EXT_PROCESSING)
            {
                do
                {
                    ret = processCSAIPollStatus(CRYPTO_82_HSM_EXT_API_NONE, Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].jobHandle);
                } while (ret == CRYPTO_82_HSM_EXT_PROCESSING);
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_POWER_MODE == STD_ON) */

#if (CRYPTO_82_HSM_FEE_REORG == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_CheckReorgOnWrite( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    VAR(uint32, AUTOMATIC) sizeToCheck,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) isSafeToWrite, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) possibleNumWrites /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    CONST(Crypto_82_Hsm_Ext_ApiType, AUTOMATIC) thisApi = CRYPTO_82_HSM_EXT_API_CHECKREORGONWRITE;
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (isSafeToWrite == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (possibleNumWrites == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (sizeToCheck == 0u)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApiDFlashReorg == CRYPTO_82_HSM_EXT_API_NONE)
        { 
            feeParams.tag = (uint32)Crypto_82_Hsm_configKeys[arCryptoKeyId].HsmKeyId;
            feeParams.sizeToCheck = sizeToCheck;

            csaiErr = ecy_hsm_Csai_FEEMGR_CheckReorgOnWrite(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].sessionHandle,
                                                            (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_BACKGROUND_PRIORITY,
                                                            ecy_hsm_CSAI_FEEMGR_STRUCT_VERSION_0,
                                                            &feeParams,
                                                            sizeof(ecy_hsm_Csai_FeeMgr_FeeParamT),
                                                            &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].jobHandle);

            ret = processCSAIResponse(thisApi, csaiErr);
        }
        else if (currentProcessedApiDFlashReorg == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].jobHandle);

            if (ret == CRYPTO_82_HSM_EXT_DONE)
            {
                if(feeParams.isSafeToWrite == 0u)
                {
                    *isSafeToWrite = FALSE;
                }
                else
                {
                    *isSafeToWrite = TRUE;
                }
                *possibleNumWrites = feeParams.possibleNumWrites;
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }
    return ret;
}
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */

#if (CRYPTO_82_HSM_FEE_REORG == STD_ON) 
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_TriggerFlashReorg(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    CONST(Crypto_82_Hsm_Ext_ApiType, AUTOMATIC) thisApi = CRYPTO_82_HSM_EXT_API_TRIGGERFLASHREORG;
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        if (currentProcessedApiDFlashReorg == CRYPTO_82_HSM_EXT_API_NONE)
        {
            csaiErr = ecy_hsm_Csai_FEEMGR_TriggerReorg(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].sessionHandle,
                                                       (ecy_hsm_Csai_JobPriorityT)CRYPTO_82_HSM_BACKGROUND_PRIORITY,
                                                       &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].jobHandle);

            ret = processCSAIResponse(thisApi, csaiErr);
        }
        else if (currentProcessedApiDFlashReorg == thisApi)
        {
            ret = processCSAIPollStatus(thisApi, Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].jobHandle);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }
    return ret;
}
#endif /* (CRYPTO_82_HSM_FEE_REORG == STD_ON) */

#if (CRYPTO_82_HSM_FLASH_SYNC == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_FlashSync_HostStart(/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
                                      uint32 State,
                                      uint32 timeout_ms)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;

    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (State > 1u)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /*CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT*/
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            if (State == 0u)
            {
                csaiErr = ecy_hsm_Csai_FlashSync_HostRead(
                    NULL_PTR,
                    timeout_ms);

                ret = processCSAIImmediateResponse(csaiErr);
            }

            if (State == 1u)
            {
                csaiErr = ecy_hsm_Csai_FlashSync_HostWrite(
                    NULL_PTR,
                    timeout_ms);

                ret = processCSAIImmediateResponse(csaiErr);
            }
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */

#if (CRYPTO_82_HSM_FLASH_SYNC == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_FlashSync_HostEnd(/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
                                    uint32 timeout_ms)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) ret = CRYPTO_82_HSM_EXT_INVALID;

    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /*CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT*/
    {
        if (currentProcessedApi == CRYPTO_82_HSM_EXT_API_NONE)
        {
            csaiErr = ecy_hsm_Csai_FlashSync_HostEnd(
                NULL_PTR,
                timeout_ms);

            ret = processCSAIImmediateResponse(csaiErr);
        }
        else
        {
            ret = CRYPTO_82_HSM_EXT_BUSY;
        }
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_FLASH_SYNC == STD_ON) */

#if (CRYPTO_82_HSM_AUTOSAR_KEY_VALIDITY == STD_ON)
FUNC(Crypto_82_Hsm_Ext_ErrorStateType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_KeyGetStatus(/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    uint32 arCryptoKeyId,
    boolean *keyStatusPtr)
{
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC)ret = CRYPTO_82_HSM_EXT_INVALID;

#if (CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON)

    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (arCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else if (keyStatusPtr == NULL_PTR)
    {
        ret = CRYPTO_82_HSM_EXT_ERROR;
    }
    else
#endif /* CRYPTO_82_HSM_EXT_DEV_ERROR_DETECT == STD_ON */
    {
        *keyStatusPtr = (boolean)(Crypto_82_Hsm_KeyState[arCryptoKeyId].keyValid);

        ret = CRYPTO_82_HSM_EXT_DONE;
    }

    return ret;
}
#endif /* (CRYPTO_82_HSM_AUTOSAR_KEY_VALIDITY == STD_ON) */

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
