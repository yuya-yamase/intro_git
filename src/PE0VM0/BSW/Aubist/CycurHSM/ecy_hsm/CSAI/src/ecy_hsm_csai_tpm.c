/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Trusted Platform Module (TPM) implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2024, all rights reserved.
 **********************************************************************************************/
/* [$Satisfies $COMPONENT TPM_CSAI] */

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet.h"
#include "ecy_hsm_applet_tpm.h"
#include "ecy_hsm_basicsrvs.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_tpm.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_service.h"
#include "ecy_hsm_service_tpm.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_GenerateAuthValue(ecy_hsm_Csai_SessionHandleT                             hSession,
                                   ecy_hsm_Csai_JobPriorityT                               priority,
                                   ecy_hsm_Csai_Tpm_GenerateAuthValue_ParamSetAndVersionT* pParams,
                                   ecy_hsm_Csai_JobHandleT*                                phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_GENERATE_AUTH_VALUE_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair(ecy_hsm_Csai_SessionHandleT                                    hSession,
                                          ecy_hsm_Csai_JobPriorityT                                      priority,
                                          ecy_hsm_Csai_Tpm_GenerateEphemeralKeyPair_ParamSetAndVersionT* pParams,
                                          ecy_hsm_Csai_JobHandleT*                                       phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_GENERATE_EPHEMERAL_KEY_PAIR_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_DeriveSessionKey(ecy_hsm_Csai_SessionHandleT                            hSession,
                                  ecy_hsm_Csai_JobPriorityT                              priority,
                                  ecy_hsm_Csai_Tpm_DeriveSessionKey_ParamSetAndVersionT* pParams,
                                  ecy_hsm_Csai_JobHandleT*                               phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage) and HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_DERIVE_SESSION_KEY_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);
    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 2824] */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_GenerateHmac(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                ecy_hsm_Csai_JobPriorityT                          priority,
                                                ecy_hsm_Csai_Tpm_GenerateHmac_ParamSetAndVersionT* pParams,
                                                ecy_hsm_Csai_JobHandleT*                           phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_GENERATE_HMAC_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_GenerateDuplicationBlob(ecy_hsm_Csai_SessionHandleT                              hSession,
                                         ecy_hsm_Csai_JobPriorityT                                priority,
                                         ecy_hsm_Csai_Tpm_DuplicationBlobGen_ParamSetAndVersionT* pParams,
                                         ecy_hsm_Csai_JobHandleT*                                 phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_DUPLICATION_BLOB_GEN_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_GetEncryptedAuthValue(ecy_hsm_Csai_SessionHandleT                                 hSession,
                                       ecy_hsm_Csai_JobPriorityT                                   priority,
                                       ecy_hsm_Csai_Tpm_GetEncryptedAuthValue_ParamSetAndVersionT* pParams,
                                       ecy_hsm_Csai_JobHandleT*                                    phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_GET_ENCRYPTED_AUTH_VALUE_E);
    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_EncryptCommand(ecy_hsm_Csai_SessionHandleT                                hSession,
                                ecy_hsm_Csai_JobPriorityT                                  priority,
                                ecy_hsm_Csai_Tpm_EncryptCommand_ParamSetAndVersionT*       pParams,
                                ecy_hsm_Csai_JobHandleT*                                   phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_ENCRYPT_COMMAND_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_ReleaseTpmValue(ecy_hsm_Csai_SessionHandleT                           hSession,
                                                   ecy_hsm_Csai_JobPriorityT                             priority,
                                                   ecy_hsm_Csai_KeyHandleT                               hKeyToRelease,
                                                   ecy_hsm_Csai_Tpm_ReleaseTpmValue_ParamSetAndVersionT* pParams,
                                                   ecy_hsm_Csai_JobHandleT*                              phJob)
{
    /* Initialization */
    ecy_hsm_Tpm_ReleaseParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_RELEASE_VALUE_E);

    /* Parameter update */
    paramBlock.hKeyToRelease            = hKeyToRelease;
    paramBlock.pTpmReleaseExtendedParam = pParams;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_LoadTpmValue(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                ecy_hsm_Csai_JobPriorityT                          priority,
                                                ecy_hsm_Csai_KeyIdT                                persistedKeyId,
                                                ecy_hsm_Csai_Tpm_LoadTpmValue_ParamSetAndVersionT* pParams,
                                                ecy_hsm_Csai_KeyHandleT*                           phTpmValue,
                                                ecy_hsm_Csai_JobHandleT*                           phJob)
{
    /* Initialization */
    ecy_hsm_Tpm_LoadParamT paramBlock;
    Applet_ReturnTypeT     result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_LOAD_VALUE_E);

    /* Parameter update */
    paramBlock.persistedKeyId        = persistedKeyId;
    paramBlock.phTpmValue            = phTpmValue;
    paramBlock.pTpmLoadExtendedParam = pParams;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Tpm_DeleteTpmValue(ecy_hsm_Csai_SessionHandleT                          hSession,
                                                  ecy_hsm_Csai_JobPriorityT                            priority,
                                                  ecy_hsm_Csai_KeyIdT                                  persistedKeyId,
                                                  ecy_hsm_Csai_Tpm_DeleteTpmValue_ParamSetAndVersionT* pParams,
                                                  ecy_hsm_Csai_JobHandleT*                             phJob)
{
    /* Initialization */
    ecy_hsm_Tpm_DeleteParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_DELETE_VALUE_E);

    /* Parameter update */
    paramBlock.persistedKeyId          = persistedKeyId;
    paramBlock.pTpmDeleteExtendedParam = pParams;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 2822] */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Tpm_DecryptResponse(ecy_hsm_Csai_SessionHandleT                           hSession,
                                 ecy_hsm_Csai_JobPriorityT                             priority,
                                 ecy_hsm_Csai_Tpm_DecryptResponse_ParamSetAndVersionT* pParams,
                                 ecy_hsm_Csai_JobHandleT*                              phJob)
{
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* <Justification: Applet_FunctionT is an union, applet function ID (for applet usage); HSM function ID (for compatibility with Proxy). So usage of union is safe */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TPM, ecy_hsm_APPLET_TPM_DECRYPT_RESPONSE_E);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
