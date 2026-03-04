/**
 * @file
 ***********************************************************************************************
 * @brief Implementation of CSAI Secure Host Debug with Challenge Response operations.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2022, all rights reserved
 **********************************************************************************************/
/* [$Satisfies $COMPONENT Secure_Host_Debug_CSAI] */

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_secure_host_debug_with_cr.h"
#include "ecy_hsm_csai_sss.h"

#ifdef ECY_HSM_VMS_SSS_SECURE_HOST_DEBUG_WITH_CR_SCRIPT_ID
#if ECY_HSM_VMS_SSS_SECURE_HOST_DEBUG_WITH_CR_SCRIPT_ID != 3U
#error "SCRIPT ID inconsistent"
#endif
#else
#define ECY_HSM_VMS_SSS_SECURE_HOST_DEBUG_WITH_CR_SCRIPT_ID 3U
#endif

/* Number of Script Inputs for different use cases */
#define ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_GET_CHALLENGE_NUM_INPUTS    6U
#define ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_VERIFY_RESPONSE_NUM_INPUTS  3U
#define ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT                     5U

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* CSAI Secure HOST Debug with CR - Get challenge */
/* [$Satisfies $DD 1986] */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_secure_host_debug_with_cr_GetChallenge(ecy_hsm_Csai_SessionHandleT                         hSession,
                                                                      ecy_hsm_Csai_JobPriorityT                           priority,
                                                                      const ecy_hsm_Csai_WrappedGetChallengeParamStructT* pParams,
                                                                      ecy_hsm_Csai_JobHandleT*                            phJob)
{
    ecy_hsm_Csai_ErrorT             errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    ecy_hsm_Csai_Sss_StatusInfoT    statusInfo;

    if ((NULL_PTR == pParams) || (NULL_PTR == phJob))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* Check use case ID */
        if (ecy_hsm_Csai_secure_host_debug_with_cr_get_challenge_v0 == pParams->useCaseID)
        {
            /* Prepare script inputs */
            ecy_hsm_Csai_Sss_ScriptInputT scriptInputs[ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_GET_CHALLENGE_NUM_INPUTS];

            scriptInputs[0].inputIndex = (uint32) 0UL;
            scriptInputs[0].inputValue = pParams->getChallengeParameters.param0.encKeyId;
            scriptInputs[1].inputIndex = (uint32) 1UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[1].inputValue = (uint32)pParams->getChallengeParameters.param0.clientIV;
            scriptInputs[2].inputIndex = (uint32) 2UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[2].inputValue = (uint32)pParams->getChallengeParameters.param0.clientEncData;
            scriptInputs[3].inputIndex = (uint32) 3UL;
            scriptInputs[3].inputValue = pParams->getChallengeParameters.param0.ownerKeyId;
            scriptInputs[4].inputIndex = (uint32) 4UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[4].inputValue = (uint32)pParams->getChallengeParameters.param0.serverIV;
            scriptInputs[5].inputIndex = (uint32) 5UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[5].inputValue = (uint32)pParams->getChallengeParameters.param0.serverEncData;

            /* Execute Script Init */
            errorCode = ecy_hsm_Csai_Sss_ScriptInit(hSession,
                                                    priority,
                                                    ECY_HSM_VMS_SSS_SECURE_HOST_DEBUG_WITH_CR_SCRIPT_ID,
                                                    phJob,
                                                    NULL_PTR,
                                                    0U);

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* In case of no error, wait for the job to be finished */
                errorCode = ecy_hsm_Csai_WaitForHandle(*phJob, NULL_PTR, NULL_PTR, ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* Add script input */
                errorCode = ecy_hsm_Csai_Sss_SetScriptInputs(hSession,
                                                            priority,
                                                            scriptInputs,
                                                            sizeof(scriptInputs) / sizeof(scriptInputs[0]),
                                                            phJob,
                                                            NULL_PTR,
                                                            0U);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* In case of no error, wait for the job to be finished */
                errorCode = ecy_hsm_Csai_WaitForHandle(*phJob, NULL_PTR, NULL_PTR, ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* Execute RunScript */
                errorCode = ecy_hsm_Csai_Sss_RunScript(hSession, priority, &statusInfo, phJob, NULL_PTR, 0U);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* In case of no error, wait for the job to be finished */
                errorCode = ecy_hsm_Csai_WaitForHandle(*phJob, NULL_PTR, NULL_PTR, ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT);
            }

            if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (ecy_hsm_SSS_VM_WAITING != statusInfo.vmState))
            {
                errorCode = ecy_hsm_CSAI_ERR_INVALID_STATE;
            }
        }

        /* Update given job handle */
        *phJob = hSession;
    }

    return errorCode;
}

/* CSAI Secure HOST Debug with CR - Get challenge response */
/* [$Satisfies $DD 1987] */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_secure_host_debug_with_cr_VerifyResponse(ecy_hsm_Csai_SessionHandleT                           hSession,
                                                                        ecy_hsm_Csai_JobPriorityT                             priority,
                                                                        const ecy_hsm_Csai_WrappedVerifyResponseParamStructT* pParams,
                                                                        ecy_hsm_Csai_JobHandleT*                              phJob)
{
    ecy_hsm_Csai_ErrorT             errorCode = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    ecy_hsm_Csai_Sss_StatusInfoT    statusInfo;

    if ((NULL_PTR == pParams) || (NULL_PTR == phJob))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* Check use case ID */
        if (ecy_hsm_Csai_secure_host_debug_with_cr_verify_response_v0 == pParams->useCaseID)
        {
        /* Prepare script input parameters */
            ecy_hsm_Csai_Sss_ScriptInputT scriptInputs[ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_VERIFY_RESPONSE_NUM_INPUTS];

            scriptInputs[0].inputIndex = (uint32) 0UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[0].inputValue = (uint32)pParams->verifyResponseParameters.param0.clientIV;
            scriptInputs[1].inputIndex = (uint32) 1UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[1].inputValue = (uint32)pParams->verifyResponseParameters.param0.clientResponseData;
            scriptInputs[2].inputIndex = (uint32) 2UL;
            /* PRQA S 0306 1 *//* Justification: This conversion does not affect functionality, as the script input expects a 32 bit address */
            scriptInputs[2].inputValue = (uint32)pParams->verifyResponseParameters.param0.verificationResult;

            /* Set valid script inputs */
            errorCode = ecy_hsm_Csai_Sss_SetScriptInputs(hSession,
                                                        priority,
                                                        scriptInputs,
                                                        sizeof(scriptInputs) / sizeof(scriptInputs[0]),
                                                        phJob,
                                                        NULL_PTR,
                                                        0U);

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* In case of no error, wait for the job to be finished */
                errorCode = ecy_hsm_Csai_WaitForHandle(*phJob, NULL_PTR, NULL_PTR, ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* Execute RunScript */
                errorCode = ecy_hsm_Csai_Sss_RunScript(hSession, priority, &statusInfo, phJob, NULL_PTR, 0U);
            }

            if (ecy_hsm_CSAI_SUCCESS == errorCode)
            {
                /* In case of no error, wait for the job to be finished */
                errorCode = ecy_hsm_Csai_WaitForHandle(*phJob, NULL_PTR, NULL_PTR, ECY_HSM_SSS_SECURE_HOST_DEBUG_WITH_CR_TIMEOUT);
            }

            if ((ecy_hsm_CSAI_SUCCESS == errorCode) && (ecy_hsm_SSS_VM_FINISHED != statusInfo.vmState))
            {
                errorCode = ecy_hsm_CSAI_ERR_INVALID_STATE;
            }
        }

        /* Update given job handle */
        *phJob = hSession;
    }

    return errorCode;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
