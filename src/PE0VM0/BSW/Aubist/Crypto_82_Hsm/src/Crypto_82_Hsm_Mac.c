/**
 * \file Crypto_82_Hsm_Mac.c
 *
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Implementation of the MAC module
 *
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_UserCallout.h"
#include "Crypto_82_Hsm_Services.h"

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_mac.h"

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

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

VAR(Crypto_82_Hsm_BulkMacVerify_Data, CRYPTO_82_HSM_VAR)  bulkMacVerifyContext;
VAR(Crypto_82_Hsm_BulkMacGenerate_Data, CRYPTO_82_HSM_VAR)  bulkMacGenerateContext;

#endif
#define CRYPTO_82_HSM_STOP_SEC_VAR_CRYPTO_SHARED_NOINIT
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Mapping for MAC algorithms.
 *
 * \param [in] algo           Crypto Service layer supported Mac algorithm.
 *
 * \return ret_algo           Corresponding MAC algorithm supported by the Hsm.
 */
static FUNC(ecy_hsm_Csai_MACAlgorithmT, CRYPTO_82_HSM_CODE) get_macAlgo(Crypto_82_Hsm_Service_MACAlgorithmType algo);

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(ecy_hsm_Csai_MACAlgorithmT, CRYPTO_82_HSM_CODE) get_macAlgo(Crypto_82_Hsm_Service_MACAlgorithmType algo)
{
    ecy_hsm_Csai_MACAlgorithmT ret_algo = ecy_hsm_CSAI_MAC_RESERVED;

    switch (algo)
    {
    case CryptoDriver_AES_CMAC:
        ret_algo = ecy_hsm_CSAI_AES_CMAC;
        break;
    case CryptoDriver_HMAC_SHA1:
        ret_algo = ecy_hsm_CSAI_HMAC_SHA1;
        break;
    case CryptoDriver_HMAC_SHA2_256:
        ret_algo = ecy_hsm_CSAI_HMAC_SHA2_256;
        break;
    case CryptoDriver_HMAC_SHA2_512:
        ret_algo = ecy_hsm_CSAI_HMAC_SHA2_512;
        break;
    default:
        ret_algo = ecy_hsm_CSAI_MAC_RESERVED;
        break;
    }

    return ret_algo;
}
/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) mac_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    CONST(boolean, AUTOMATIC) truncationAllowed = TRUE /*[SWS_Crypto_00065]*/;
    ecy_hsm_Csai_MACAlgorithmT csai_macAlgo = get_macAlgo(macAlgo);

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_MacGenerate( csaiSession->hSession, csai_macAlgo, hKey,
                                          csaiSession->priority, msg, msg_len,
                                          mac, *mac_len, mac_len,
                                          truncationAllowed, &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_MACAlgorithmT csai_macAlgo = get_macAlgo(macAlgo);

    errorCode = ecy_hsm_Csai_MacGenerateStart( csaiSession->hSession, csai_macAlgo, hKey,
                                               csaiSession->priority, msg, msg_len,
                                               &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_MacGenerateUpdate( csaiSession.hJob, msg, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Generate_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2VAR(uint8, AUTOMATIC, CRYPTO_82_HSM_VAR) mac, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) mac_len /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    CONST(boolean, AUTOMATIC) truncationAllowed = TRUE /*[SWS_Crypto_00065]*/;

    /* Satisfies SWS_Crypto_00135 */
    errorCode = ecy_hsm_Csai_MacGenerateFinish( csaiSession.hJob, mac, *mac_len, mac_len, truncationAllowed );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) mac,
    VAR(uint32, AUTOMATIC) mac_size,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_MACAlgorithmT csai_macAlgo = get_macAlgo(macAlgo);

    errorCode = ecy_hsm_Csai_MacVerify( csaiSession->hSession, csai_macAlgo, hKey,
                                        csaiSession->priority, msg, msg_len,
                                        mac, mac_size, verificationResult,
                                        &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Start
(
    P2VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC, CRYPTO_82_HSM_VAR) csaiSession, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(ecy_hsm_Csai_KeyHandleT, AUTOMATIC) hKey,
    VAR(Crypto_82_Hsm_Service_MACAlgorithmType, AUTOMATIC) macAlgo,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;
    ecy_hsm_Csai_MACAlgorithmT csai_macAlgo = get_macAlgo(macAlgo);

    errorCode = ecy_hsm_Csai_MacVerifyStart( csaiSession->hSession, csai_macAlgo, hKey,
                                             csaiSession->priority, msg, msg_len,
                                             &(csaiSession->hJob) );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Update
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) msg,
    VAR(uint32, AUTOMATIC) msg_len
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_MacVerifyUpdate( csaiSession.hJob, msg, msg_len );

    return errorCode;
}

FUNC(ecy_hsm_Csai_ErrorT, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Mac_Verify_Finish
(
    VAR(Crypto_82_Hsm_Service_CsaiSessionType, AUTOMATIC) csaiSession,
    P2CONST(uint8, AUTOMATIC, CRYPTO_82_HSM_CONST) mac,
    VAR(uint32, AUTOMATIC) mac_size,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) verificationResult /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) errorCode;

    errorCode = ecy_hsm_Csai_MacVerifyFinish( csaiSession.hJob, mac, mac_size,
                                              verificationResult );

    return errorCode;
}

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Bulk_Mac_Generate_Fast(VAR(uint32, AUTOMATIC) numBulkMacJobs)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;

    for (uint32 i = 0; i< numBulkMacJobs; i++)
    {
        bulkMacGenerateContext.BULK_LIST_MACGEN[i].algorithm = get_macAlgo(bulkMacGenerateContext.BULK_LIST_ALGORITHMS[i]);
    }

    csai_err = ecy_hsm_Csai_BulkMacGenerateFast(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN].sessionHandle,
                                              (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN],
                                              bulkMacGenerateContext.BULK_LIST_MACGEN,
                                              numBulkMacJobs,
                                              &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN].jobHandle));

    if (csai_err == ecy_hsm_CSAI_SUCCESS)
    {
        ret = E_OK;
    }
    else /* Satisfies DN_BM_SWS_Crypto_024 */
    {
        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
    }

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Bulk_Mac_Verify_Fast(VAR(uint32, AUTOMATIC) numBulkMacJobs)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csai_err = ecy_hsm_CSAI_ERR_UNDEFINED;
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;

    for (uint32 i = 0; i< numBulkMacJobs; i++)
    {
        bulkMacVerifyContext.BULK_LIST_MACVER[i].algorithm = get_macAlgo(bulkMacVerifyContext.BULK_LIST_ALGORITHMS[i]);
    }

    csai_err = ecy_hsm_Csai_BulkMacVerifyFast(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER].sessionHandle,
                                              (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER],
                                              bulkMacVerifyContext.BULK_LIST_MACVER,
                                              numBulkMacJobs,
                                              &(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER].jobHandle));

    if (csai_err == ecy_hsm_CSAI_SUCCESS)
    {
        ret = E_OK;
    }
    else /* Satisfies DN_BM_SWS_Crypto_024 */
    {
        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csai_err);
    }

    return ret;
}

#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

