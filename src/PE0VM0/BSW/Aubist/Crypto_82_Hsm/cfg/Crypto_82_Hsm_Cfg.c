/**
 * \file Crypto_82_Hsm_Cfg.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Generated configuration file
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_Services.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/* Data buffer for SHE PROOF KeyElement */
static VAR(uint8, CRYPTO_82_HSM_VAR) CryptoKeyElement_SHE_PROOF_DataBuffer[48];


#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

VAR(boolean, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyElementValidity[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Rationale: Crypto_82_Hsm_KeyState[keyId].keyValid = TRUE => Key of keyId is valid.
 */
VAR(Crypto_82_Hsm_KeyStateType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_KeyState[CRYPTO_82_HSM_NUMBER_OF_KEYS];

/* Queue for Crypto Driver Object: CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer */
static P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer_Queue[28]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/* Queue for Crypto Driver Object: CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen */
static P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen_Queue[14]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/* Queue for Crypto Driver Object: CryptoDriverObjectCryptoDriverObject_General */
static P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_General_Queue[1]; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */


#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Rationale: runtimeKeys[KeyElementId] = runtimeKey
 * The mapping of a Crypto_82_Hsm_RuntimeKey to a Crypto_82_Hsm_ConfigKeyElement.
 */
VAR(Crypto_82_Hsm_RuntimeKeyType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_runtimeKeys[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS];
VAR(Crypto_82_Hsm_DriverObjectType, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/* Key Element Init Values */

/* Buffer for initial value of KeyElement 1 : CryptoKeyElement_KeyVerify_SecOC_Mac_PROOF */
static CONST(uint8, CRYPTO_82_HSM_CONST) CryptoKeyElement_KeyVerify_SecOC_Mac_PROOF_initValue[48] = {0};

/* Buffer for initial value of KeyElement 3 : CryptoKeyElement_MASTER_ECU_KEY_PROOF */
static CONST(uint8, CRYPTO_82_HSM_CONST) CryptoKeyElement_MASTER_ECU_KEY_PROOF_initValue[48] = {0};


#define CRYPTO_82_HSM_STOP_SEC_CONST_8BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_32BIT
#include "Crypto_82_Hsm_MemMap.h"

CONST(uint32, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_Queue_Sizes[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS] =
{
    0u, /* Queue size, CryptoDriverObjectCryptoDriverObject_DensoExt */
    0u, /* Queue size, CryptoDriverObjectCryptoDriverObject_KeyManagement */
    0u, /* Queue size, CryptoDriverObjectCryptoDriverObject_DensoExtDFlashReorg */
    28u, /* Queue size, CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer */
    14u, /* Queue size, CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen */
    1u  /* Queue size, CryptoDriverObjectCryptoDriverObject_General */
};

CONST(Crypto_82_Hsm_DriverObjectPriority, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS] =
{
    CRYPTO_82_HSM_MEDIUM_PRIORITY, /* Driver object priority, CryptoDriverObjectCryptoDriverObject_DensoExt */
    CRYPTO_82_HSM_MEDIUM_PRIORITY, /* Driver object priority, CryptoDriverObjectCryptoDriverObject_KeyManagement */
    CRYPTO_82_HSM_BACKGROUND_PRIORITY, /* Driver object priority, CryptoDriverObjectCryptoDriverObject_DensoExtDFlashReorg */
    CRYPTO_82_HSM_HIGH_PRIORITY, /* Driver object priority, CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer */
    CRYPTO_82_HSM_HIGH_PRIORITY, /* Driver object priority, CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen */
    CRYPTO_82_HSM_MEDIUM_PRIORITY  /* Driver object priority, CryptoDriverObjectCryptoDriverObject_General */
};

CONST(uint32, CRYPTO_82_HSM_CONST)  Crypto_82_Hsm_keyIdToKeyElementIdMap[CRYPTO_82_HSM_NUMBER_OF_KEYS] =
{
    0u,          /* KeyId 0 : CryptoKey_KeyVerify_SecOC_Mac */
    2u           /* KeyId 1 : CryptoKey_MASTER_ECU_KEY */
};

#define CRYPTO_82_HSM_STOP_SEC_CONST_32BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_CRYPTO_SHARED
#include "Crypto_82_Hsm_MemMap.h"


	


CONST(Crypto_82_Hsm_ConfigKeyType, CRYPTO_82_HSM_CONST)  Crypto_82_Hsm_configKeys[CRYPTO_82_HSM_NUMBER_OF_KEYS] =
{

    /* KeyId 0 : CryptoKey_KeyVerify_SecOC_Mac */
    {
        /* HsmKeyId             */  ecy_hsm_CSAI_KEYID_AES_KEY_DYNAMIC_BASIC_SHE_DFLASH_KEY_BASE_0,
        /* keyType              */  ecy_hsm_CSAI_KEYTYPE_SYMMETRIC,
        /* keyProperties        */  (ecy_hsm_CSAI_KEYPROP_MAC_ONLY | ecy_hsm_CSAI_KEYPROP_ALL_SESSIONS),
        /* keyState             */  FALSE,
        /* numberOfKeyElements  */  2u
    },

    /* KeyId 1 : CryptoKey_MASTER_ECU_KEY */
    {
        /* HsmKeyId             */  ecy_hsm_CSAI_KEYID_AES_KEY_DYNAMIC_BASIC_SHE_MASTER_KEY,
        /* keyType              */  ecy_hsm_CSAI_KEYTYPE_SYMMETRIC,
        /* keyProperties        */  ecy_hsm_CSAI_KEYPROP_ALL_SESSIONS,
        /* keyState             */  FALSE,
        /* numberOfKeyElements  */  2u
    }

};

CONST(Crypto_82_Hsm_ConfigKeyElementType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_configKeyElements[CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS] =
{
    /* KeyElement 0 : CryptoKeyElement_KeyVerify_SecOC_Mac_KEY */
    {
        /* readAccess           */  CRYPTO_82_HSM_RA_DENIED,
        /* writeAccess          */  CRYPTO_82_HSM_WA_ALLOWED,
        /* initialContentPtr    */  NULL_PTR,
        /* keySize              */  64u,
        /* keyFormat            */  CRYPTO_KE_FORMAT_BIN_SHEKEYS,
        /* allowPartialAccess   */  FALSE,
        /* keyStorageType       */  CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT,
        /* keyElementId         */  1u,
        /* keyDataPtr           */  NULL_PTR,
		/* loadAtInit           */  TRUE
    },

    /* KeyElement 1 : CryptoKeyElement_KeyVerify_SecOC_Mac_PROOF */
    {
        /* readAccess           */  CRYPTO_82_HSM_RA_ALLOWED,
        /* writeAccess          */  CRYPTO_82_HSM_WA_DENIED,
        /* initialContentPtr    */  CryptoKeyElement_KeyVerify_SecOC_Mac_PROOF_initValue,
        /* keySize              */  48u,
        /* keyFormat            */  CRYPTO_KE_FORMAT_BIN_OCTET,
        /* allowPartialAccess   */  FALSE,
        /* keyStorageType       */  CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT,
        /* keyElementId         */  2u,
        /* keyDataPtr           */  CryptoKeyElement_SHE_PROOF_DataBuffer,
		/* loadAtInit           */  FALSE
    },

    /* KeyElement 2 : CryptoKeyElement_MASTER_ECU_KEY */
    {
        /* readAccess           */  CRYPTO_82_HSM_RA_DENIED,
        /* writeAccess          */  CRYPTO_82_HSM_WA_ALLOWED,
        /* initialContentPtr    */  NULL_PTR,
        /* keySize              */  64u,
        /* keyFormat            */  CRYPTO_KE_FORMAT_BIN_SHEKEYS,
        /* allowPartialAccess   */  FALSE,
        /* keyStorageType       */  CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT,
        /* keyElementId         */  1u,
        /* keyDataPtr           */  NULL_PTR,
		/* loadAtInit           */  TRUE
    },

    /* KeyElement 3 : CryptoKeyElement_MASTER_ECU_KEY_PROOF */
    {
        /* readAccess           */  CRYPTO_82_HSM_RA_ALLOWED,
        /* writeAccess          */  CRYPTO_82_HSM_WA_DENIED,
        /* initialContentPtr    */  CryptoKeyElement_MASTER_ECU_KEY_PROOF_initValue,
        /* keySize              */  48u,
        /* keyFormat            */  CRYPTO_KE_FORMAT_BIN_OCTET,
        /* allowPartialAccess   */  FALSE,
        /* keyStorageType       */  CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT,
        /* keyElementId         */  2u,
        /* keyDataPtr           */  CryptoKeyElement_SHE_PROOF_DataBuffer,
		/* loadAtInit           */  FALSE
    }};

#define CRYPTO_82_HSM_STOP_SEC_CONST_CRYPTO_SHARED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

CONSTP2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) Crypto_82_Hsm_queues[CRYPTO_82_HSM_NUM_DRIVER_OBJECTS_WITH_QUEUE] = /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer_Queue, /* Queue ptr, CryptoDriverObjectCryptoDriverObject_DensoBulkMacVer  */
    Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen_Queue, /* Queue ptr, CryptoDriverObjectCryptoDriverObject_DensoBulkMacGen  */
    Crypto_82_Hsm_CryptoDriverObjectCryptoDriverObject_General_Queue, /* Queue ptr, CryptoDriverObjectCryptoDriverObject_General  */
};

/*
* Array which holds information about the state of a service (supported/not supported).
*/
CONST(Crypto_82_Hsm_ServiceDataType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_ServiceDataArray[CRYPTO_82_HSM_NUMBER_OF_SERVICES] = 
{
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        CRYPTO_82_HSM_MACGEN_ALGOFAM,
        CRYPTO_82_HSM_MACGEN_SECALGOFAM,
        CRYPTO_82_HSM_MACGEN_PROCESSING_MODE,
        CRYPTO_82_HSM_MACGEN_ALGO_MODE,
        CRYPTO_82_HSM_MACGEN_OPERATING_MODE,
        TRUE
    },
    {
        CRYPTO_82_HSM_MACVERIFY_ALGOFAM,
        CRYPTO_82_HSM_MACVERIFY_SECALGOFAM,
        CRYPTO_82_HSM_MACVERIFY_PROCESSING_MODE,
        CRYPTO_82_HSM_MACVERIFY_ALGO_MODE,
        CRYPTO_82_HSM_MACVERIFY_OPERATING_MODE,
        TRUE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        0u,
        0u,
        0u,
        0u,
        0u,
        FALSE
    },
    {
        CRYPTO_82_HSM_KEY_SET_VALID_ALGOFAM,
        CRYPTO_82_HSM_KEY_SET_VALID_SECALGOFAM,
        CRYPTO_82_HSM_KEY_SET_VALID_PROCESSING_MODE,
        CRYPTO_82_HSM_KEY_SET_VALID_ALGO_MODE,
        CRYPTO_82_HSM_KEY_SET_VALID_OPERATING_MODE,
        TRUE
    }
};


#define CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/


