/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Sign implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if !defined(GUAM)
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_sign_generate.h"
#include "ecy_hsm_applet_sign_verify.h"
#include "ecy_hsm_csai_sign.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                                 ecy_hsm_Csai_SignatureSchemeT scheme,
                                                 ecy_hsm_Csai_KeyHandleT       hKey,
                                                 ecy_hsm_Csai_JobPriorityT     priority,
                                                 const uint8                   msg[],
                                                 uint32                        msgLength,
                                                 ecy_hsm_Csai_JobHandleT*      phJob)
{
    /* Initialization */
    Applet_SignGenerateParamT paramBlock;
    Applet_ReturnTypeT        result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, APPLET_SIGN_GENERATE_STATE_INIT);

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    paramBlock.scheme = scheme;
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey       = hKey;
    paramBlock.msg        = msg;
    paramBlock.msgLength  = msgLength;
    paramBlock.pSign      = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSignCount = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('S');

    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession,
                             ecy_hsm_CSAI_PRIO_BACKGROUND, /* force background prio for RSA operations */
                             appletFunc,
                             sizeof(paramBlock),
                             &paramBlock);
    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                  const uint8             chunk[],
                                                  uint32                  length)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, APPLET_SIGN_GENERATE_STATE_UPDATE);
    Applet_SignGenerateParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg        = chunk;
    paramBlock.msgLength  = length;
    paramBlock.pSign      = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSignCount = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                  uint8*                  pSign,
                                                  uint32                  signLength,
                                                  uint32*                 pSignCount)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, APPLET_SIGN_GENERATE_STATE_FINAL);
    Applet_SignGenerateParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */               /* <Deviation: rule_2.2_2983 */
    paramBlock.msg        = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSign      = pSign;
    paramBlock.signLength = signLength;
    paramBlock.pSignCount = pSignCount;

    ecy_hsm_AddDiagnosticStopwatch('F');

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedStart(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                         ecy_hsm_Csai_JobPriorityT                         priority,
                                                         ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                         ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignStartParamSetAndVersion,
                                                         ecy_hsm_Csai_KeyHandleT                           hKey,
                                                         const uint8*                                      pMsg,
                                                         uint32                                            msgLength,
                                                         ecy_hsm_Csai_JobHandleT*                          phJob)
{
    /* Initialization */
    ecy_hsm_Applet_SignGenerateExtendedParamT paramBlock;
    Applet_ReturnTypeT                        result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_INIT);

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam        = pSignStartParamSetAndVersion;
    paramBlock.signBasicParam.scheme     = scheme;
    paramBlock.signBasicParam.hKey       = hKey;
    paramBlock.signBasicParam.msg        = pMsg;
    paramBlock.signBasicParam.msgLength  = msgLength;
    paramBlock.signBasicParam.pSign      = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pSignCount = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('S');

    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession,
                             ecy_hsm_CSAI_PRIO_BACKGROUND, /* force background prio for RSA operations */
                             appletFunc,
                             sizeof(paramBlock),
                             &paramBlock);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 3 */ /*Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 2 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedUpdate(ecy_hsm_Csai_JobHandleT                           hJob,
                                                          ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignUpdateParamSetAndVersion,
                                                          const uint8*                                      pChunk,
                                                          uint32                                            length)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_UPDATE);
    ecy_hsm_Applet_SignGenerateExtendedParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam        = pSignUpdateParamSetAndVersion;
    paramBlock.signBasicParam.msg        = pChunk;
    paramBlock.signBasicParam.msgLength  = length;
    paramBlock.signBasicParam.pSign      = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pSignCount = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    /* execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtendedFinish(ecy_hsm_Csai_JobHandleT                           hJob,
                                                          ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignFinishParamSetAndVersion,
                                                          uint8*                                            pSign,
                                                          uint32                                            signLength,
                                                          uint32*                                           pSignCount)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_FINAL);
    ecy_hsm_Applet_SignGenerateExtendedParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam        = pSignFinishParamSetAndVersion;
    paramBlock.signBasicParam.msg        = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pSign      = pSign;
    paramBlock.signBasicParam.signLength = signLength;
    paramBlock.signBasicParam.pSignCount = pSignCount;

    ecy_hsm_AddDiagnosticStopwatch('F');

    /* execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerate(ecy_hsm_Csai_SessionHandleT   hSession,
                                            ecy_hsm_Csai_SignatureSchemeT scheme,
                                            ecy_hsm_Csai_KeyHandleT       hKey,
                                            ecy_hsm_Csai_JobPriorityT     priority,
                                            const uint8*                  msg,
                                            uint32                        msgLength,
                                            uint8*                        pSign,
                                            uint32                        signLength,
                                            uint32*                       pSignCount,
                                            ecy_hsm_Csai_JobHandleT*      phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, APPLET_SIGN_GENERATE_STATE_FULL);
    Applet_SignGenerateParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    paramBlock.scheme = scheme;
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey       = hKey;
    paramBlock.msg        = msg;
    paramBlock.msgLength  = msgLength;
    paramBlock.pSign      = pSign;
    paramBlock.signLength = signLength;
    paramBlock.pSignCount = pSignCount;

    if (pSignCount != NULL_PTR)
    {
        *pSignCount = 0;
    }

    ecy_hsm_AddDiagnosticStopwatch('G');

    // execute applet: force background prio for RSA operations */
    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);
    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignGenerateExtended(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                    ecy_hsm_Csai_JobPriorityT                         priority,
                                                    ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                    ecy_hsm_Csai_SignGenExtended_ParamSetAndVersionT* pSignParamSetAndVersion,
                                                    ecy_hsm_Csai_KeyHandleT                           hKey,
                                                    const uint8*                                      pMsg,
                                                    uint32                                            msgLength,
                                                    uint8*                                            pSign,
                                                    uint32                                            signLength,
                                                    uint32*                                           pSignCount,
                                                    ecy_hsm_Csai_JobHandleT*                          phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                          appletFunc = APPFUNC_ID(APPLET_ID_SIGN_GENERATE, ecy_hsm_APPLET_SIGN_GENERATE_EXTENDED_STATE_FULL);
    ecy_hsm_Applet_SignGenerateExtendedParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam        = pSignParamSetAndVersion;
    paramBlock.signBasicParam.hKey       = hKey;
    paramBlock.signBasicParam.scheme     = scheme;
    paramBlock.signBasicParam.msg        = pMsg;
    paramBlock.signBasicParam.msgLength  = msgLength;
    paramBlock.signBasicParam.pSign      = pSign;
    paramBlock.signBasicParam.signLength = signLength;
    paramBlock.signBasicParam.pSignCount = pSignCount;

    ecy_hsm_AddDiagnosticStopwatch('G');

    /* execute applet: force background prio for RSA operations */
    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
