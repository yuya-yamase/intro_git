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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                               ecy_hsm_Csai_SignatureSchemeT scheme,
                                               ecy_hsm_Csai_KeyHandleT       hKey,
                                               ecy_hsm_Csai_JobPriorityT     priority,
                                               const uint8                   msg[],
                                               uint32                        msgLength,
                                               ecy_hsm_Csai_JobHandleT*      phJob)
{
    /* Initialization */
    Applet_SignVerifyParamT paramBlock;
    Applet_ReturnTypeT      result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, APPLET_SIGN_VERIFY_STATE_INIT);

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    paramBlock.scheme = scheme;
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey        = hKey;
    paramBlock.msg         = msg;
    paramBlock.msgLength   = msgLength;
    paramBlock.pSign       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag = NULL_PTR; /* default initialization in context of ffi */

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                const uint8             chunk[],
                                                uint32                  length)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, APPLET_SIGN_VERIFY_STATE_UPDATE);
    Applet_SignVerifyParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg         = chunk;
    paramBlock.msgLength   = length;
    paramBlock.pSign       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pResultFlag = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                const uint8*            pSign,
                                                uint32                  signLength,
                                                uint32*                 pResultFlag)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, APPLET_SIGN_VERIFY_STATE_FINAL);
    Applet_SignVerifyParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */                /* <Deviation: rule_2.2_2983 */
    paramBlock.msg         = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pSign       = pSign;
    paramBlock.signLength  = signLength;
    paramBlock.pResultFlag = pResultFlag;

    ecy_hsm_AddDiagnosticStopwatch('F');

    // execute applet
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedStart(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                       ecy_hsm_Csai_JobPriorityT                         priority,
                                                       ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                       ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignStartParamSetAndVersion,
                                                       ecy_hsm_Csai_KeyHandleT                           hKey,
                                                       const uint8*                                      pMsg,
                                                       uint32                                            msgLength,
                                                       ecy_hsm_Csai_JobHandleT*                          phJob)
{
    /* Initialization */
    ecy_hsm_Applet_SignVerifyExtendedParamT paramBlock;
    Applet_ReturnTypeT                      result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_INIT);

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam         = pSignStartParamSetAndVersion;
    paramBlock.signBasicParam.hKey        = hKey;
    paramBlock.signBasicParam.scheme      = scheme;
    paramBlock.signBasicParam.msg         = pMsg;
    paramBlock.signBasicParam.msgLength   = msgLength;
    paramBlock.signBasicParam.pSign       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pResultFlag = NULL_PTR; /* default initialization in context of ffi */

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedUpdate(ecy_hsm_Csai_JobHandleT                           hJob,
                                                        ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignUpdateParamSetAndVersion,
                                                        const uint8*                                      pChunk,
                                                        uint32                                            length)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_UPDATE);
    ecy_hsm_Applet_SignVerifyExtendedParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam         = pSignUpdateParamSetAndVersion;
    paramBlock.signBasicParam.msg         = pChunk;
    paramBlock.signBasicParam.msgLength   = length;
    paramBlock.signBasicParam.pSign       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pResultFlag = NULL_PTR; /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    /* execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtendedFinish(ecy_hsm_Csai_JobHandleT                           hJob,
                                                        ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignFinishParamSetAndVersion,
                                                        const uint8*                                      pSign,
                                                        uint32                                            signLength,
                                                        uint32*                                           pResultFlag)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_FINAL);
    ecy_hsm_Applet_SignVerifyExtendedParamT paramBlock;

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam         = pSignFinishParamSetAndVersion;
    paramBlock.signBasicParam.msg         = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.signBasicParam.pSign       = pSign;
    paramBlock.signBasicParam.signLength  = signLength;
    paramBlock.signBasicParam.pResultFlag = pResultFlag;

    ecy_hsm_AddDiagnosticStopwatch('F');

    /* execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerify(ecy_hsm_Csai_SessionHandleT   hSession,
                                          ecy_hsm_Csai_SignatureSchemeT scheme,
                                          ecy_hsm_Csai_KeyHandleT       hKey,
                                          ecy_hsm_Csai_JobPriorityT     priority,
                                          const uint8*                  msg,
                                          uint32                        msgLength,
                                          const uint8*                  pSign,
                                          uint32                        signLength,
                                          uint32*                       pResultFlag,
                                          ecy_hsm_Csai_JobHandleT*      phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, APPLET_SIGN_VERIFY_STATE_FULL);
    Applet_SignVerifyParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    paramBlock.scheme = scheme;
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey        = hKey;
    paramBlock.msg         = msg;
    paramBlock.msgLength   = msgLength;
    paramBlock.pSign       = pSign;
    paramBlock.signLength  = signLength;
    paramBlock.pResultFlag = pResultFlag;

    ecy_hsm_AddDiagnosticStopwatch('V');

    // execute applet: force background prio for RSA operations */
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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SignVerifyExtended(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                  ecy_hsm_Csai_JobPriorityT                         priority,
                                                  ecy_hsm_Csai_SignatureSchemeT                     scheme,
                                                  ecy_hsm_Csai_SignVerExtended_ParamSetAndVersionT* pSignParamSetAndVersion,
                                                  ecy_hsm_Csai_KeyHandleT                           hKey,
                                                  const uint8*                                      pMsg,
                                                  uint32                                            msgLength,
                                                  const uint8*                                      pSign,
                                                  uint32                                            signLength,
                                                  uint32*                                           pResultFlag,
                                                  ecy_hsm_Csai_JobHandleT*                          phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                        appletFunc = APPFUNC_ID(APPLET_ID_SIGN_VERIFY, ecy_hsm_APPLET_SIGN_VERIFY_EXTENDED_STATE_FULL);
    ecy_hsm_Applet_SignVerifyExtendedParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);
    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pSignExtendedParam         = pSignParamSetAndVersion;
    paramBlock.signBasicParam.hKey        = hKey;
    paramBlock.signBasicParam.scheme      = scheme;
    paramBlock.signBasicParam.msg         = pMsg;
    paramBlock.signBasicParam.msgLength   = msgLength;
    paramBlock.signBasicParam.pSign       = pSign;
    paramBlock.signBasicParam.signLength  = signLength;
    paramBlock.signBasicParam.pResultFlag = pResultFlag;

    ecy_hsm_AddDiagnosticStopwatch('V');

    /* execute applet: force background prio for RSA operations */
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
