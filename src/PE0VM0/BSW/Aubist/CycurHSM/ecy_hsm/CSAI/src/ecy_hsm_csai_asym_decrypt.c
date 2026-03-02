/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Asymmetric Decryption implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2010, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_crypt.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_asym_crypt.h"
#include "ecy_hsm_applet_manager.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymDecrypt(ecy_hsm_Csai_SessionHandleT  hSession,
                                           ecy_hsm_Csai_JobPriorityT    priority,
                                           ecy_hsm_Csai_AsymCipherModeT cipherMode,
                                           ecy_hsm_Csai_KeyHandleT      hKey,
                                           const uint8                  cipherText[],
                                           uint32                       cipherTextLength,
                                           uint8                        clearText[],
                                           uint32                       clearTextLength,
                                           uint32                      *pClearTextCount,
                                           ecy_hsm_Csai_JobHandleT     *phJob)
{
    Applet_ReturnTypeT       result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT         appletFunc = APPFUNC_ID(APPLET_ID_ASYM_DECRYPT, APPLET_ASYM_CRYPT_STATE_FULL);
    Applet_AsymCryptParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    paramBlock.cipherMode       = cipherMode;
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey             = hKey;
    paramBlock.inputText        = cipherText;
    paramBlock.inputTextLength  = cipherTextLength;
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pClearTextCount;

    // execute applet: force background prio for RSA operations */
    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession,
                             ecy_hsm_CSAI_PRIO_BACKGROUND,
                             appletFunc,
                             sizeof(paramBlock),
                             &paramBlock);
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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymDecryptExtend(ecy_hsm_Csai_SessionHandleT                      hSession,
                                                 ecy_hsm_Csai_JobPriorityT                        priority,
                                                 ecy_hsm_Csai_AsymCipherModeT                     cipherMode,
                                                 ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionT *pAsymDecryptParamSetAndVersion,
                                                 ecy_hsm_Csai_KeyHandleT                          hKey,
                                                 const uint8                                      cipherText[],
                                                 uint32                                           cipherTextLength,
                                                 uint8                                            clearText[],
                                                 uint32                                           clearTextLength,
                                                 uint32                                          *pClearTextCount,
                                                 ecy_hsm_Csai_JobHandleT                         *phJob)
{
    Applet_ReturnTypeT                       result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                         appletFunc = APPFUNC_ID(APPLET_ID_ASYM_DECRYPT, ecy_hsm_APPLET_ASYM_CRYPT_EXTENDED_STATE_FULL);
    ecy_hsm_Applet_AsymDecryptExtendedParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    paramBlock.asymCryptBasicParam.cipherMode       = cipherMode;
    paramBlock.pAsymDecryptParamSetAndVersion       = pAsymDecryptParamSetAndVersion;
    paramBlock.asymCryptBasicParam.hKey             = hKey;
    paramBlock.asymCryptBasicParam.inputText        = cipherText;
    paramBlock.asymCryptBasicParam.inputTextLength  = cipherTextLength;
    paramBlock.asymCryptBasicParam.outputText       = clearText;
    paramBlock.asymCryptBasicParam.outputTextLength = clearTextLength;
    paramBlock.asymCryptBasicParam.pOutputTextCount = pClearTextCount;

    /* Execute applet: force background prio for ECIES extended operations */
    /* @deprecated: Only required for backwards compatibility. Applet is already restricted to background prio. */
    result = Applet_Function(hSession,
                             ecy_hsm_CSAI_PRIO_BACKGROUND,
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
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
