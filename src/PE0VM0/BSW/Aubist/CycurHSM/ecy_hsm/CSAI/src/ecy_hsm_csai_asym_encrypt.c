/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Asymmetric Encryption implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymEncrypt(ecy_hsm_Csai_SessionHandleT  hSession,
                                           ecy_hsm_Csai_JobPriorityT    priority,
                                           ecy_hsm_Csai_AsymCipherModeT cipherMode,
                                           ecy_hsm_Csai_KeyHandleT      hKey,
                                           const uint8                  clearText[],
                                           uint32                       clearTextLength,
                                           uint8                        cipherText[],
                                           uint32                       cipherTextLength,
                                           uint32                      *pCipherTextCount,
                                           ecy_hsm_Csai_JobHandleT     *phJob)
{
    Applet_ReturnTypeT       result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT         appletFunc = APPFUNC_ID(APPLET_ID_ASYM_ENCRYPT, APPLET_ASYM_CRYPT_STATE_FULL);
    Applet_AsymCryptParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    paramBlock.cipherMode       = cipherMode;
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.hKey             = hKey;
    paramBlock.inputText        = clearText;
    paramBlock.inputTextLength  = clearTextLength;
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymEncryptExtend(ecy_hsm_Csai_SessionHandleT                      hSession,
                                                 ecy_hsm_Csai_JobPriorityT                        priority,
                                                 ecy_hsm_Csai_AsymCipherModeT                     cipherMode,
                                                 ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionT *pAsymEncryptParamSetAndVersion,
                                                 ecy_hsm_Csai_KeyHandleT                          hKey,
                                                 const uint8                                      clearText[],
                                                 uint32                                           clearTextLength,
                                                 uint8                                            cipherText[],
                                                 uint32                                           cipherTextLength,
                                                 uint32                                          *pCipherTextCount,
                                                 ecy_hsm_Csai_JobHandleT                         *phJob)
{
    Applet_ReturnTypeT                       result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                         appletFunc = APPFUNC_ID(APPLET_ID_ASYM_ENCRYPT, ecy_hsm_APPLET_ASYM_CRYPT_EXTENDED_STATE_FULL);
    ecy_hsm_Applet_AsymEncryptExtendedParamT paramBlock;

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    paramBlock.asymCryptBasicParam.cipherMode       = cipherMode;
    paramBlock.pAsymEncryptParamSetAndVersion       = pAsymEncryptParamSetAndVersion;
    paramBlock.asymCryptBasicParam.hKey             = hKey;
    paramBlock.asymCryptBasicParam.inputText        = clearText;
    paramBlock.asymCryptBasicParam.inputTextLength  = clearTextLength;
    paramBlock.asymCryptBasicParam.outputText       = cipherText;
    paramBlock.asymCryptBasicParam.outputTextLength = cipherTextLength;
    paramBlock.asymCryptBasicParam.pOutputTextCount = pCipherTextCount;

    /* Execute applet: force background prio for ECIES extended operations */
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
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
