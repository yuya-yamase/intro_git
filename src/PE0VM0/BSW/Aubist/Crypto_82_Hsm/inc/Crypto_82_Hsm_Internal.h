/**
 * \file Crypto_82_Hsm_Internal.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file used internally.
 * \details This file should contain "protected" information used ONLY INSIDE the module.
*/

#ifndef CRYPTO_82_HSM_INTERNAL_H
#define CRYPTO_82_HSM_INTERNAL_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Csm.h"
#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif

#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_DensoExtensions.h"

#include "ecy_hsm_proxy.h"
#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_keyid.h"
#include "ecy_hsm_csai_dh.h"
#include "ecy_hsm_csai_key_exchange.h"
#include "ecy_hsm_she.h"

/**********************************************************************************************************************\
 * PROTECTED MACROS
\**********************************************************************************************************************/

/**
 * \def   SIZE_IN_BYTES_AEAD_TAG
 * \brief Size of AEAD tag in bytes.
*/
#define SIZE_IN_BYTES_AEAD_TAG       (16u)

#define CRYPTO_UNUSED_PARAM(param)                      (void)(param)

/**
 * \def CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS
 * \brief Number of reserved Crypto Driver objects.
 * 
 * \note The design of the CSAI sessions is the following: \n
 * 0. Session 0 is reserved for DENSO extensions \n
 * 1. Session 1 is reserved for Key Management \n
 * 2. Session 2 is reserved for DENSO extensions DFlash Reorg \n
 * 3. Session 3 is reserved for DENSO extensions Bulk Mac Gen \n
 * 4. Session 4 is reserved for DENSO extensions Bulk Mac Ver \n
 * 5. Sessions 5 to N are used for synchronous and asynchronous jobs \n
 */
#define CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS            (5u)

/**
 * \def CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS_WITHOUT_QUEUE
 * \brief Number of reserved Crypto Driver objects without queue.
 * 
 */
#define CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS_WITHOUT_QUEUE       (3u)

/**
 * \def CRYPTO_82_HSM_NUM_DRIVER_OBJECTS_WITH_QUEUE
 * \brief Number of Crypto Driver objects which may have a queue.
 */
#define CRYPTO_82_HSM_NUM_DRIVER_OBJECTS_WITH_QUEUE         (CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS - CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS_WITHOUT_QUEUE)

/**
 * \def CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS
 * \brief The Crypto Driver object reserved for Denso Extenstions.
 */
#define CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS      (0u)

/**
 * \def CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT
 * \brief The Crypto Driver object reserved for Key Management.
 */
#define CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT         (1u)

/**
 * \def CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG
 * \brief The Crypto Driver object reserved for Denso Extenstions DFlash Reorg.
 */
#define CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG          (2u)

/**
 * \def CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG
 * \brief The Crypto Driver object reserved for Denso Bulk Mac Verification.
 */
#define CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER         (3u)

/**
 * \def CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG
 * \brief The Crypto Driver object reserved for Denso Bulk Mac Generation.
 */
#define CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN          (4u)

/**
 * \def CRYPTO_82_HSM_INVALID_KEY_INDEX
 * \brief Invalid key index.
 */
#define CRYPTO_82_HSM_INVALID_KEY_INDEX                 (0xFFFFFFFFu)

/**
 * \def CRYPTO_82_HSM_NUMBER_OF_SERVICES
 * \brief Count of AUTOSAR specified services.
 */
#define CRYPTO_82_HSM_NUMBER_OF_SERVICES                (20u)

/** 
 * \def CRYPTO_82_HSM_NUM_BITS_IN_BYTE
 * \brief Number of bits in a byte.
 */
#define CRYPTO_82_HSM_NUM_BITS_IN_BYTE                  (8u)

/** 
 * \def isDriverObjectBusy(objectId)
 * \brief Returns whether a Crypto Driver object is busy.
 */
#define isDriverObjectBusy(objectId)                    (Crypto_82_Hsm_driverObjects[(objectId)].busy == TRUE)

/** 
 * \def setDriverObjectBusy(objectId, isBusy)
 * \brief Sets a Crypto Driver object to busy.
 */
#define setDriverObjectBusy(objectId, isBusy)           (Crypto_82_Hsm_driverObjects[(objectId)].busy = (isBusy))

#define CRYPTO_E_CUSTOM_VAL_TAG_NOT_FOUND           (7u)

/**
 * \def getQueue(objectId)
 * \brief Returns a pointer to the Crypto Driver Object queue.
 */
#define getQueue(objectId)              (Crypto_82_Hsm_queues[((objectId)-CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS_WITHOUT_QUEUE)%CRYPTO_82_HSM_NUM_DRIVER_OBJECTS_WITH_QUEUE])

/**
 * \def getQueueSize(objectId)
 * \brief Returns a Crypto Driver Object queue size.
 */
#define getQueueSize(objectId)          (Crypto_82_Hsm_Queue_Sizes[(objectId)])

/**********************************************************************************************************************\
 * PROTECTED TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief Crypto Service layer supported Mac algorithms.
 */
typedef enum eCrypto_82_Hsm_Service_MACAlgorithmType
{
    CryptoDriver_AES_CMAC       = 1,
    CryptoDriver_HMAC_SHA1      = 2,
    CryptoDriver_HMAC_SHA2_256  = 3,
    CryptoDriver_HMAC_SHA2_512  = 4,
    CryptoDriver_MAC_RESERVED   = 0xffu
} Crypto_82_Hsm_Service_MACAlgorithmType;

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

/**
 * \brief A structure that holds information about a bulk mac verification operation.
 *
 * bulkJobState - TRUE if a bulk mac verification job is active; FALSE if no bulk mac verification job is active
 */
typedef struct sCrypto_82_Hsm_BulkMacVerify_Data
{
    VAR(boolean, CRYPTO_82_HSM_VAR) bulkJobState;
    VAR(uint32, CRYPTO_82_HSM_VAR) numberOfJobsMacVer;
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, CRYPTO_82_HSM_VAR) BULK_LIST_ALGORITHMS[CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_VER];
    VAR(ecy_hsm_Csai_BulkMacFastVerJob, CRYPTO_82_HSM_VAR) BULK_LIST_MACVER[CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_VER];
} Crypto_82_Hsm_BulkMacVerify_Data;

/**
 * \brief A structure that holds information about a bulk mac generation operation.
 *
 * bulkJobState - TRUE if a bulk mac generation job is active; FALSE if no bulk mac generation job is active
 */
typedef struct sCrypto_82_Hsm_BulkMacGenerate_Data
{
    VAR(boolean, CRYPTO_82_HSM_VAR) bulkJobState;
    VAR(uint32, CRYPTO_82_HSM_VAR) numberOfJobsMacGen;
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, CRYPTO_82_HSM_VAR) BULK_LIST_ALGORITHMS[CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_GEN];
    VAR(ecy_hsm_Csai_BulkMacFastGenJob, CRYPTO_82_HSM_VAR) BULK_LIST_MACGEN[CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_GEN];
} Crypto_82_Hsm_BulkMacGenerate_Data;

#endif

/**
 * \brief A structure that holds information about a Cancel Job request.
 *
 * This data type is necessary because, for Async Jobs, a Job Cancel operation can be issued and the respective job
 * should be removed from the queue or stopped from processing.
 */
typedef struct sCrypto_82_Hsm_CancelJob
{
    VAR(boolean, CRYPTO_82_HSM_VAR) cancelRequested;
    VAR(uint32, CRYPTO_82_HSM_VAR) cancelJobId;
} Crypto_82_Hsm_CancelJobType;

/**
 * \brief A structure that holds information about a Crypto Driver Object.
 */
typedef struct sCrypto_82_Hsm_DriverObjectType
{
    VAR(ecy_hsm_Csai_HandleT, CRYPTO_82_HSM_VAR) objectID;
    VAR(ecy_hsm_Csai_SessionHandleT, CRYPTO_82_HSM_VAR) sessionHandle;
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) keyHandle;
    VAR(ecy_hsm_Csai_JobHandleT, CRYPTO_82_HSM_VAR) jobHandle;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_CancelJobType, CRYPTO_82_HSM_VAR) cancelJob;
    VAR(boolean, CRYPTO_82_HSM_VAR) busy;
    VAR(boolean, CRYPTO_82_HSM_VAR) skipDispatchFromQueue;
  } Crypto_82_Hsm_DriverObjectType;

/**
 * \brief Generic function prototype used in dispatch table.
 *
 * This contains all necessary information for any CycurHSM primitive to be called.
 */
typedef Std_ReturnType (*Crypto_82_Hsm_Service_Func_PtrType)
(
    P2VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR, AUTOMATIC) driverObject /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Generic callback function prototype used in dispatch table.
 *
 * This contains all necessary information for any post-processing CycurHSM primitive to be called.
 */
typedef void (*Crypto_82_Hsm_Service_Cbk_PtrType)
(
    VAR(uint32, AUTOMATIC) objectId
);

/**
 * \brief Datatype that stores information about state of service (supported/not supported).
 *
 * Masks are used to determine if a service, with it's particular algorithm mode/family and operating mode is supported.
 */
typedef struct sCrypto_82_Hsm_ServiceDataType
{
    CONST(uint64, CRYPTO_82_HSM_CONST)  supportedAlgorithmFamily;
    CONST(uint64, CRYPTO_82_HSM_CONST)  supportedAlgorithmSecondaryFamily;
    CONST(uint32, CRYPTO_82_HSM_CONST)  supportedProcessingTypes;
    CONST(uint32, CRYPTO_82_HSM_CONST)  supportedAlgorithmMode;
    CONST(uint32, CRYPTO_82_HSM_CONST)  supportedOperatingMode;
    CONST(boolean, CRYPTO_82_HSM_CONST) serviceSupported;

} Crypto_82_Hsm_ServiceDataType;

/**
 * \brief Dispatch table which stores function pointers.
 *
 * This dispatch table is used to call the algorithm implementation in order to perform a cryptographic primitive
 */
typedef struct sCrypto_82_Hsm_ServiceTableType
{
    CONST(Crypto_82_Hsm_Service_Func_PtrType, CRYPTO_82_HSM_CONST) functionPtr;
    CONST(Crypto_82_Hsm_Service_Cbk_PtrType,  CRYPTO_82_HSM_CONST) callbackFctPtr;
    CONST(boolean, CRYPTO_82_HSM_CONST) isKeyRequired;
} Crypto_82_Hsm_ServiceTableType;

typedef struct sCrypto_82_Hsm_KeyStateType
{
    VAR(boolean, CRYPTO_82_HSM_VAR) keyValid;
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) KeyElementSetKeyDataPtr;
    VAR(uint32, AUTOMATIC) KeyElementSetKeyLength;
} Crypto_82_Hsm_KeyStateType;

/**
 * \brief Type used for driver object priority.
 */
typedef enum eCrypto_82_Hsm_DriverObjectPriority
{
    CRYPTO_82_HSM_BACKGROUND_PRIORITY = 0x00,
    CRYPTO_82_HSM_LOW_PRIORITY = 0x01,
    CRYPTO_82_HSM_MEDIUM_PRIORITY = 0x02,
    CRYPTO_82_HSM_HIGH_PRIORITY = 0x03,

} Crypto_82_Hsm_DriverObjectPriority;

/**********************************************************************************************************************\
 * EXTERN PROTECTED VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CONST_32BIT
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief The mapping of keys to their first element in the Crypto_82_Hsm_configKeyElements.
 */
extern CONST(uint32, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_keyIdToKeyElementIdMap[CRYPTO_82_HSM_NUMBER_OF_KEYS];
/**
 * \brief An array of the size of the queue of each driver object.
 */
extern CONST(uint32, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_Queue_Sizes[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];
/**
 * \brief An array of the priority each driver object.
 */
extern CONST(Crypto_82_Hsm_DriverObjectPriority, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_CONST_32BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_CRYPTO_SHARED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief An array of configured keys.
 */
extern CONST(Crypto_82_Hsm_ConfigKeyType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_configKeys[CRYPTO_82_HSM_NUMBER_OF_KEYS];

/**
 * \brief An array of configured key elements.
 */
extern CONST(Crypto_82_Hsm_ConfigKeyElementType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_configKeyElements[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS];

#define CRYPTO_82_HSM_STOP_SEC_CONST_CRYPTO_SHARED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief An array that holds information on whether a service is supported or not and also what specific combination of algorithms, processing mode and operation mode it supports.
 */
extern CONST(Crypto_82_Hsm_ServiceDataType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_ServiceDataArray[CRYPTO_82_HSM_NUMBER_OF_SERVICES];
/**
 * \brief Dispatch Table which holds the function addresses corresponding to the supported services.
 */
extern CONST(Crypto_82_Hsm_ServiceTableType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_DispatchTable[CRYPTO_82_HSM_NUMBER_OF_SERVICES];

/**
 * \brief Array for all queue pointers.
 */
extern CONSTP2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_queues[CRYPTO_82_HSM_NUM_DRIVER_OBJECTS_WITH_QUEUE]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

#define CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief A variable to determine at what step in the process the key exchange job interface is.
 */
extern VAR(Crypto_82_Hsm_KeyExchangeCalcSecretOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief A variable to determine at what step in the process the key set valid job interface is.
 */
extern VAR(Crypto_82_Hsm_KeySetValidOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeySetValid_OperationState[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * An array that holds key status.
 */
extern VAR(Crypto_82_Hsm_KeyStateType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyState[CRYPTO_82_HSM_NUMBER_OF_KEYS];
/**
 * \brief Variable used for SHE key update in the HSM session context.
 */
extern VAR(Crypto_82_Hsm_SHE_KeyOperation, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_SHE_loadKey[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/* TODO: To rename the variable name to Crypto_82_Hsm_runtimeKeyElements */
/**
 * \brief An array that holds the dynamic runtime information for key elements.
 */
extern VAR(Crypto_82_Hsm_RuntimeKeyType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_runtimeKeys[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS];
/**
 * \brief An array of driver objects.
 */
extern VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief A buffer for SHE proof Key Data.
 */
extern VAR(Crypto_82_Hsm_SHE_DataType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief Key element get key ref data.
 */
extern VAR(ecy_hsm_Csai_KeyRefT, AUTOMATIC) keyRef_keyElementGet[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief Intermediary variable to store verificationResult for macVerify and singatureVerify.
 */
extern VAR(uint32, CRYPTO_82_HSM_VAR) verificationResult_global[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief Buffers for AEAD DECRYPT tag data.
*/
extern VAR(uint8, AUTOMATIC) aeadDecryptTag_global[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS][SIZE_IN_BYTES_AEAD_TAG];

/* Variable which is written in the context of the Crypto_82_Hsm_KeyExchangeCalcSecret function call and is passed to a cycurHsm API */
extern VAR(uint32, CRYPTO_82_HSM_VAR) keyExchangeCalcSecretCount[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

extern VAR(ecy_hsm_Csai_PinRefT, AUTOMATIC)  Crypto_82_Hsm_saltParam[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

extern VAR(ecy_hsm_Csai_PinRefT, AUTOMATIC)  Crypto_82_Hsm_passParam[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#if ( CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON )

extern VAR(Crypto_82_Hsm_BulkMacVerify_Data, CRYPTO_82_HSM_VAR)  bulkMacVerifyContext;
extern VAR(Crypto_82_Hsm_BulkMacGenerate_Data, CRYPTO_82_HSM_VAR)  bulkMacGenerateContext;

#endif

#if ( CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON )
/**
 * \brief An array that holds Denso Extension key validity status at runtime and is then serialized when the key status serialization API is called.
 */
extern VAR(uint8, CRYPTO_82_HSM_VAR) keyStatusDataToBeSerialized[KEY_STATUS_DATA_ARRAY_SIZE];
#endif /* (CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON) */

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief An array that holds key element validity status.
 */
extern VAR(boolean, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyElementValidity[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS];

/**
 * \brief An array for each crypto driver object to track if associated data has been recived for AEAD Encrypt
 */
extern VAR(uint8, CRYPTO_82_HSM_VAR)Crypto_82_Hsm_AEAD_Encrypt_ADD_received[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief An array for each crypto driver object to track if associated data has been recived for AEAD Decrypt
 */
extern VAR(uint8, CRYPTO_82_HSM_VAR)Crypto_82_Hsm_AEAD_Decrypt_ADD_received[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PROTECTED FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \def isJobState(job, state)
 * \brief Returns whether the state of a job is a certain state.
 */
#define isJobState(job, state)          ((job)->jobState == (state))

/**
 * \brief Returns whether the queue is full or not.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 *
 * \retval TRUE                Queue is empty.
 * \retval FALSE               Queue is not empty.
 */
FUNC(boolean, CRYPTO_82_HSM_CODE) isQueueEmpty(VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Returns whether the queue is full or not. 
 *
 * \param [in] objectId        Crypto Driver Object Id.
 *
 * \retval TRUE                Queue is full.
 * \retval FALSE               Queue is not full.
 */
FUNC(boolean, CRYPTO_82_HSM_CODE) isQueueFull(VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Returns the status of the driver.
 *
 * This function shall return E_OK if the driver is either in the IDLE or ACTIVE state. Otherwise, it shall return E_NOT_OK.
 *
 * \retval E_OK         Driver is in the IDLE or ACTIVE state
 * \retval E_NOT_OK     Driver is not in the IDLE or ACTIVE state
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_GetDriverStatus(void);

/**
 * \brief Returns whether the driver is initialized or not.
 *
 * \retval TRUE        The driver is initialized
 * \retval FALSE       The driver is not initialized
 */
FUNC(boolean, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_IsDriverInitialized(void);

/**
 * \brief Returns whether the hsm is initialized or not.
 *
 * \retval TRUE        The hsm is initialized
 * \retval FALSE       The hsm is not initialized
 */
FUNC(boolean, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_IsHsmInitialized(void);

/**
 * \brief Gets the index of the Crypto Key Element with a certain storage type for a certain Crypto Key.
 *
 * \param [in]      arCryptoKeyId           Id of autosar modelled key.
 * \param [out]     keyElementIndexPtr      Pointer to a buffer where the key element index will be stored.
 * \param [in]      keyStorageType          Storage type of key element (persistent, ram, dataBuffer).
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_GetKeyElementIndex(
    VAR(uint32, AUTOMATIC) arCryptoKeyId,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) keyElementIndexPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(Crypto_82_Hsm_KeyElementStorageType, AUTOMATIC) keyStorageType
);

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif
