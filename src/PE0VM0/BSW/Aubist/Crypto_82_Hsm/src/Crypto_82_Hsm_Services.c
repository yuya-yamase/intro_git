/**
 * \file Crypto_82_Hsm_Services.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Services implementation file
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_Services.h"
#include "Crypto_82_Hsm_Dispatch.h"
#include "Crypto_82_Hsm_UserCallout.h"

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

CONST(Crypto_82_Hsm_ServiceTableType, CRYPTO_82_HSM_CONST) Crypto_82_Hsm_DispatchTable[CRYPTO_82_HSM_NUMBER_OF_SERVICES] = 
{
    {   /* CRYPTO_HASH                                                  0x00u */
        /* functionPtr          */  &Crypto_82_Hsm_Hash_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  FALSE
    },

    {   /* CRYPTO_MACGENERATE                                           0x01u */
        /* functionPtr          */  &Crypto_82_Hsm_MacGenerate_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_MACVERIFY                                             0x02u */
        /* functionPtr          */  &Crypto_82_Hsm_MacVerify_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_ENCRYPT                                               0x03u */
        /* functionPtr          */  &Crypto_82_Hsm_Encrypt_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_DECRYPT                                               0x04u */
        /* functionPtr          */  &Crypto_82_Hsm_Decrypt_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_AEADENCRYPT                                           0x05u */
        /* functionPtr          */  &Crypto_82_Hsm_AEADEncrypt_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_AEADDECRYPT                                           0x06u */
        /* functionPtr          */  &Crypto_82_Hsm_AEADDecrypt_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_SIGNATUREGENERATE                                     0x07u */
        /* functionPtr          */  &Crypto_82_Hsm_SignatureGenerate_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_SIGNATUREVERIFY                                       0x08u */
        /* functionPtr          */  &Crypto_82_Hsm_SignatureVerify_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_SECCOUNTERINCREMENT                                   0x09u */
        /* functionPtr          */  NULL_PTR,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },
    
    {   /* CRYPTO_SECCOUNTERREAD                                        0x0Au */
        /* functionPtr          */  NULL_PTR,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_RANDOMGENERATE                                        0x0Bu */
        /* functionPtr          */  &Crypto_82_Hsm_Rng_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  FALSE
    },

    {   /* CRYPTO_RANDOMSEED                                            0x0Cu */
        /* functionPtr          */  &Crypto_82_Hsm_RngReseed_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_KEYGENERATE                                           0x0Du */
        /* functionPtr          */  &Crypto_82_Hsm_KeyGenerate_Dispatch,
        /* callbackFctPtr       */  &Crypto_82_Hsm_JobKeyGenerate_Cbk,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_KEYDERIVE                                             0x0Eu */
        /* functionPtr          */  &Crypto_82_Hsm_KeyDerive_Dispatch,
        /* callbackFctPtr       */  &Crypto_82_Hsm_JobKeyDerive_Cbk,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_KEYEXCHANGECALCPUBVAL                                 0x0Fu */
        /* functionPtr          */  &Crypto_82_Hsm_KeyExchangeCalcPubVal_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_KEYEXCHANGECALCSECRET                                 0x10u */
        /* functionPtr          */  &Crypto_82_Hsm_KeyExchangeCalcSecret_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_CERTIFICATEPARSE                                      0x11u */
        /* functionPtr          */  NULL_PTR,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_CERTIFICATEVERIFY                                     0x12u */
        /* functionPtr          */  NULL_PTR,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    },

    {   /* CRYPTO_KEYSETVALID                                           0x13u */
        /* functionPtr          */  &Crypto_82_Hsm_KeySetValid_Dispatch,
        /* callbackFctPtr       */  NULL_PTR,
        /* isKeyRequired        */  TRUE
    }
};

#define CRYPTO_82_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_WaitForJobFinished(ecy_hsm_Csai_JobHandleT jobHandle, uint8 serviceId, uint32 jobId)
{
    ecy_hsm_Csai_ErrorT ret = ecy_hsm_CSAI_SUCCESS;
    Std_ReturnType err = E_OK;

    do
    {
        ret = ecy_hsm_Csai_PollHandle(jobHandle);
    }
    while(ecy_hsm_CSAI_FC_PENDING == ret);

    /* Satisfies SWS_Crypto_00141 */
    if (ret == ecy_hsm_CSAI_ERR_TRNG)
    {
        err = CRYPTO_E_ENTROPY_EXHAUSTED;
    }
    else if (ret != ecy_hsm_CSAI_SUCCESS)
    {
        err = E_NOT_OK;
    }
    else
    {
        /* Do nothing */
    }

    if (ret != ecy_hsm_CSAI_SUCCESS)
    {
        Crypto_82_Hsm_Error_Callback(serviceId, jobId, ret);
    }

    return err;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_PollJob(ecy_hsm_Csai_JobHandleT jobHandle, uint8 serviceId, uint32 jobId, uint32 objectId)
{
    ecy_hsm_Csai_ErrorT csai_err;
    Std_ReturnType ret;

    csai_err = ecy_hsm_Csai_PollHandle(jobHandle);

    switch (csai_err)
    {
    case ecy_hsm_CSAI_SUCCESS:
        ret = E_OK;
        break;

    case ecy_hsm_CSAI_ERR_TRNG:
        ret = CRYPTO_E_ENTROPY_EXHAUSTED;
        break;

    case ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND:
        ret = CRYPTO_E_CUSTOM_VAL_TAG_NOT_FOUND;
        break;
    
    case ecy_hsm_CSAI_FC_PENDING:
        ret = CRYPTO_E_BUSY;
        break;
    
    default:
        ret = E_NOT_OK;
        break;
    }

    if ((csai_err != ecy_hsm_CSAI_SUCCESS) && (csai_err != ecy_hsm_CSAI_FC_PENDING))
    {
        if ( (objectId != CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) && (objectId != CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN))
        {
            Crypto_82_Hsm_Error_Callback(serviceId, jobId, csai_err);
        }
    }

    return ret;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
