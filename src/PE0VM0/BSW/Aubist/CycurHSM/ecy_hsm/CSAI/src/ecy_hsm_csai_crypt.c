/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Encryption and Decryption implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_crypt.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_asym_crypt.h"
#include "ecy_hsm_applet_sym_crypt.h"
#include "ecy_hsm_applet_manager.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            ecy_hsm_Csai_SymCipherModeT cipherMode,
                                            ecy_hsm_Csai_PaddingModeT   paddingMode,
                                            ecy_hsm_Csai_KeyHandleT     hKey,
                                            const uint8                 iv[],
                                            uint32                      ivLength,
                                            const uint8                 clearText[],
                                            uint32                      clearTextLength,
                                            uint8                       cipherText[],
                                            uint32                      cipherTextLength,
                                            uint32*                     pCipherTextCount,
                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_CRYPT_STATE_INIT);

    /* Parameter update */
    /* PRQA S 2983 11 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.inputText        = clearText;
    paramBlock.inputTextLength  = clearTextLength;
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                             const uint8             clearText[],
                                             uint32                  clearTextLength,
                                             uint8                   cipherText[],
                                             uint32                  cipherTextLength,
                                             uint32*                 pCipherTextCount)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_CRYPT_STATE_UPDATE);

    /* Parameter update */
    /* PRQA S 2983 8 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.inputText        = clearText;
    paramBlock.inputTextLength  = clearTextLength;
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                             uint8                   cipherText[],
                                             uint32                  cipherTextLength,
                                             uint32*                 pCipherTextCount)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_CRYPT_STATE_FINAL);

    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Encrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                       ecy_hsm_Csai_JobPriorityT   priority,
                                       ecy_hsm_Csai_SymCipherModeT cipherMode,
                                       ecy_hsm_Csai_PaddingModeT   paddingMode,
                                       ecy_hsm_Csai_KeyHandleT     hKey,
                                       const uint8                 iv[],
                                       uint32                      ivLength,
                                       const uint8                 clearText[],
                                       uint32                      clearTextLength,
                                       uint8                       cipherText[],
                                       uint32                      cipherTextLength,
                                       uint32*                     pCipherTextCount,
                                       ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_CRYPT_STATE_FULL);

    /* Parameter update */
    /* PRQA S 2983 10 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.inputText        = clearText;
    paramBlock.inputTextLength  = clearTextLength;
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
     }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            ecy_hsm_Csai_SymCipherModeT cipherMode,
                                            ecy_hsm_Csai_PaddingModeT   paddingMode,
                                            ecy_hsm_Csai_KeyHandleT     hKey,
                                            const uint8                 iv[],
                                            uint32                      ivLength,
                                            const uint8                 cipherText[],
                                            uint32                      cipherTextLength,
                                            uint8                       clearText[],
                                            uint32                      clearTextLength,
                                            uint32*                     pClearTextCount,
                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_CRYPT_STATE_INIT);

    /* Parameter update */
    /* PRQA S 2983 11 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.inputText        = cipherText;
    paramBlock.inputTextLength  = cipherTextLength;
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pClearTextCount;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                             const uint8             cipherText[],
                                             uint32                  cipherTextLength,
                                             uint8                   clearText[],
                                             uint32                  clearTextLength,
                                             uint32*                 pClearTextCount)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_CRYPT_STATE_UPDATE);

    /* Parameter update */
    /* PRQA S 2983 8 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.inputText        = cipherText;
    paramBlock.inputTextLength  = cipherTextLength;
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pClearTextCount;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                             uint8                   clearText[],
                                             uint32                  clearTextLength,
                                             uint32*                 pLastClearTextCount)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_CRYPT_STATE_FINAL);

    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pLastClearTextCount;
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob,ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Decrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                       ecy_hsm_Csai_JobPriorityT   priority,
                                       ecy_hsm_Csai_SymCipherModeT cipherMode,
                                       ecy_hsm_Csai_PaddingModeT   paddingMode,
                                       ecy_hsm_Csai_KeyHandleT     hKey,
                                       const uint8                 iv[],
                                       uint32                      ivLength,
                                       const uint8                 cipherText[],
                                       uint32                      cipherTextLength,
                                       uint8                       clearText[],
                                       uint32                      clearTextLength,
                                       uint32*                     pClearTextCount,
                                       ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_CRYPT_STATE_FULL);

    /* Parameter update */
    /* PRQA S 2983 12 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.inputText        = cipherText;
    paramBlock.inputTextLength  = cipherTextLength;
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pClearTextCount;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_SymCipherModeT cipherMode,
                                                ecy_hsm_Csai_PaddingModeT   paddingMode,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                const uint8                 iv[],
                                                uint32                      ivLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result   = { HSM_STATUS_IDLE, ecy_hsm_CSAI_SUCCESS };
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_AUTH_CRYPT_STATE_INIT);

    if ((ecy_hsm_CSAI_AES_GCM != cipherMode) && (ecy_hsm_CSAI_C20_P1305 != cipherMode))
    {
        result.stError = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }
    else
    {
        /* Parameter update */
        /* PRQA S 2983 9 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.cipherMode       = cipherMode;
        paramBlock.paddingMode      = paddingMode;
        paramBlock.hKey             = hKey;
        paramBlock.iv               = iv;
        paramBlock.ivLength         = ivLength;
        paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.outputText       = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.pOutputTextCount = NULL_PTR; /* default initialization in context of ffi */


        // execute applet
        result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
        // update given job handle
        if(phJob != NULL_PTR)
        {
            *phJob = hSession;
        }
    }
    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                          const uint8             aad[],
                                          uint32                  aadLength)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_AUTH_CRYPT_STATE_UPDATE);

    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.aad              = aad;
    paramBlock.aadLength        = aadLength;
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.outputText       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pOutputTextCount = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8                   cipherText[],
                                                 uint32                  cipherTextLength,
                                                 uint32*                 pCipherTextCount,
                                                 uint8*                  pTag,
                                                 uint32                  tagLength)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_AUTH_CRYPT_STATE_FINAL);

    /* Parameter update */
    /* PRQA S 2983 8 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.pTag             = pTag;
    paramBlock.tagLength        = tagLength;
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_SymCipherModeT cipherMode,
                                                ecy_hsm_Csai_PaddingModeT   paddingMode,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                const uint8                 iv[],
                                                uint32                      ivLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result   = { HSM_STATUS_IDLE, ecy_hsm_CSAI_SUCCESS };
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_AUTH_CRYPT_STATE_INIT);

    if((ecy_hsm_CSAI_AES_GCM != cipherMode) && (ecy_hsm_CSAI_C20_P1305 != cipherMode))
    {
        result.stError = ecy_hsm_CSAI_ERR_NOT_SUPPORTED;
    }
    else
    {
        /* Parameter update */
        /* PRQA S 2983 9 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.cipherMode       = cipherMode;
        paramBlock.paddingMode      = paddingMode;
        paramBlock.hKey             = hKey;
        paramBlock.iv               = iv;
        paramBlock.ivLength         = ivLength;
        paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.outputText       = NULL_PTR; /* default initialization in context of ffi */
        paramBlock.pOutputTextCount = NULL_PTR; /* default initialization in context of ffi */

        // execute applet
        result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
        // update given job handle
        if(phJob != NULL_PTR)
        {
             *phJob = hSession;
        }
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                 const uint8             aad[],
                                                 uint32                  aadLength)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_AUTH_CRYPT_STATE_UPDATE);

    /* Parameter update */
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.aad              = aad;
    paramBlock.aadLength        = aadLength;
    paramBlock.pTag             = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.outputText       = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pOutputTextCount = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 *//*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8                   clearText[],
                                                 uint32                  clearTextLength,
                                                 uint32*                 pLastClearTextCount,
                                                 uint8*                  pTag,
                                                 uint32                  tagLength)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_AUTH_CRYPT_STATE_FINAL);

    /* Parameter update */
    /* PRQA S 2983 9 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pLastClearTextCount;
    paramBlock.pTag             = pTag;
    paramBlock.tagLength        = tagLength;
    paramBlock.iv               = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.aad              = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.inputText        = NULL_PTR; /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           ecy_hsm_Csai_SymCipherModeT cipherMode,
                                           ecy_hsm_Csai_PaddingModeT   paddingMode,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           const uint8                 iv[],
                                           uint32                      ivLength,
                                           const uint8                 aad[],
                                           uint32                      aadLength,
                                           const uint8                 plainText[],
                                           uint32                      plainTextLength,
                                           uint8                       cipherText[],
                                           uint32                      cipherTextLength,
                                           uint32*                     pCipherTextCount,
                                           uint8*                      pTag,
                                           uint32                      tagLength,
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_ENCRYPT, APPLET_SYM_AUTH_CRYPT_STATE_FULL);

    /* Parameter update */
    /* PRQA S 2983 13 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.aad              = aad;
    paramBlock.aadLength        = aadLength;
    paramBlock.inputText        = plainText;
    paramBlock.inputTextLength  = plainTextLength;
    paramBlock.outputText       = cipherText;
    paramBlock.outputTextLength = cipherTextLength;
    paramBlock.pOutputTextCount = pCipherTextCount;
    paramBlock.pTag             = pTag;
    paramBlock.tagLength        = tagLength;

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           ecy_hsm_Csai_SymCipherModeT cipherMode,
                                           ecy_hsm_Csai_PaddingModeT   paddingMode,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           const uint8                 iv[],
                                           uint32                      ivLength,
                                           const uint8                 aad[],
                                           uint32                      aadLength,
                                           const uint8                 cipherText[],
                                           uint32                      cipherTextLength,
                                           uint8                       clearText[],
                                           uint32                      clearTextLength,
                                           uint32*                     pClearTextCount,
                                           uint8*                      pTag,
                                           uint32                      tagLength,
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_SymCryptParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYM_DECRYPT, APPLET_SYM_AUTH_CRYPT_STATE_FULL);

    /* Parameter update */
    /* PRQA S 2983 13 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.cipherMode       = cipherMode;
    paramBlock.paddingMode      = paddingMode;
    paramBlock.hKey             = hKey;
    paramBlock.iv               = iv;
    paramBlock.ivLength         = ivLength;
    paramBlock.aad              = aad;
    paramBlock.aadLength        = aadLength;
    paramBlock.inputText        = cipherText;
    paramBlock.inputTextLength  = cipherTextLength;
    paramBlock.outputText       = clearText;
    paramBlock.outputTextLength = clearTextLength;
    paramBlock.pOutputTextCount = pClearTextCount;
    paramBlock.pTag             = pTag;
    paramBlock.tagLength        = tagLength;

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
