/**
 * @file
 ***********************************************************************************************
 * @brief CSAI key implementation file
 *
 * [$Satisfies $COMPONENT KeyManagement_CSAI]
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_service_keys.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_keys.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeriveKey(ecy_hsm_Csai_SessionHandleT         hSession,
                                         ecy_hsm_Csai_JobPriorityT           priority,
                                         ecy_hsm_Csai_KeyDerivationFunctionT kdf,
                                         ecy_hsm_Csai_KeyHandleT             hParentKey,
                                         ecy_hsm_Csai_PinRefT*               pPasswd,
                                         ecy_hsm_Csai_PinRefT*               pSalt,
                                         uint32                              iterationCount,
                                         ecy_hsm_Csai_KeySizeT               keySize,
                                         ecy_hsm_Csai_KeyHandleT*            phDerivedKey,
                                         ecy_hsm_Csai_JobHandleT*            phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_DERIVE_KEY);

    /* Parameter update */
    paramBlock.DeriveKeyParam.kdf = kdf;
    paramBlock.DeriveKeyParam.hParentKey = hParentKey;
    paramBlock.DeriveKeyParam.pPasswd = pPasswd;
    paramBlock.DeriveKeyParam.pSalt = pSalt;
    paramBlock.DeriveKeyParam.iterationCount = iterationCount;
    paramBlock.DeriveKeyParam.keySize = keySize;
    paramBlock.DeriveKeyParam.phDerivedKeys = phDerivedKey;
    paramBlock.DeriveKeyParam.pKeyCount = NULL_PTR;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
/* PRQA S 6007 1 */ /* <Justification: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeriveKeyExt(ecy_hsm_Csai_SessionHandleT         hSession,
                                            ecy_hsm_Csai_JobPriorityT           priority,
                                            ecy_hsm_Csai_KeyDerivationFunctionT kdf,
                                            ecy_hsm_Csai_KeyHandleT             hParentKey,
                                            void*                               pKdfParam,
                                            uint32                              kdfParamSize,
                                            void*                               pKeyAttributes,
                                            uint32                              keyAttributeSize,
                                            ecy_hsm_Csai_JobHandleT*            phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT     paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_DERIVE_KEY_EXT);

    /* Parameter update */
    paramBlock.DeriveKeyExtParam.kdf               = kdf;
    paramBlock.DeriveKeyExtParam.hParentKey        = hParentKey;
    paramBlock.DeriveKeyExtParam.pKdfParam         = pKdfParam;
    paramBlock.DeriveKeyExtParam.kdfParamSize      = kdfParamSize;
    paramBlock.DeriveKeyExtParam.pKeyAttributes    = pKeyAttributes;
    paramBlock.DeriveKeyExtParam.keyAttributesSize = keyAttributeSize;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Justification: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeriveMultipleKeys(ecy_hsm_Csai_SessionHandleT         hSession,
                                                  ecy_hsm_Csai_JobPriorityT           priority,
                                                  ecy_hsm_Csai_KeyDerivationFunctionT kdf,
                                                  ecy_hsm_Csai_KeyHandleT             hParentKey,
                                                  ecy_hsm_Csai_PinRefT*               pInfo,
                                                  ecy_hsm_Csai_PinRefT*               pSalt,
                                                  uint32                              iterationCount,
                                                  ecy_hsm_Csai_KeySizeT               keySize,
                                                  uint8*                              pKeyCount,
                                                  ecy_hsm_Csai_KeyHandleT*            phDerivedKeys,
                                                  ecy_hsm_Csai_JobHandleT*            phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS);

    /* Parameter update */
    paramBlock.DeriveKeyParam.kdf = kdf;
    paramBlock.DeriveKeyParam.hParentKey = hParentKey;
    paramBlock.DeriveKeyParam.pPasswd = pInfo;
    paramBlock.DeriveKeyParam.pSalt = pSalt;
    paramBlock.DeriveKeyParam.iterationCount = iterationCount;
    paramBlock.DeriveKeyParam.keySize = keySize;
    paramBlock.DeriveKeyParam.phDerivedKeys = phDerivedKeys;
    paramBlock.DeriveKeyParam.pKeyCount = pKeyCount;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
/* PRQA S 6007 1 */ /* <Justification: number of function parameters is fixed by design */
}

/* PRQA S 3673 6 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeriveMultipleKeysExt(ecy_hsm_Csai_SessionHandleT            hSession,
                                                     ecy_hsm_Csai_JobPriorityT              priority,
                                                     ecy_hsm_Csai_JobHandleT*               phJob,
                                                     ecy_hsm_DeriveMultipleKeysExtParamT*   pDerivedKeysParam)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT      paramBlock;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_KEYS, ecy_hsm_APPLET_KEYS_FUNC_DERIVE_MULTIPLE_KEYS_EXT);

    /* Parameter update */
    paramBlock.DeriveMultiKeysExtParam.useCaseId                   = pDerivedKeysParam->useCaseId;
    paramBlock.DeriveMultiKeysExtParam.pDeriveMultipleKeysExtParam = pDerivedKeysParam->pDeriveMultipleKeysExtParam;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
/* PRQA S 6007 1 */ /* <Justification: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InjectKey(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         ecy_hsm_Csai_KeyRefT*       pKey,
                                         uint32                      keyProperties,
                                         ecy_hsm_Csai_KeyHandleT*    phKey,
                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_INJECT_KEY);

    /* Parameter update */
    paramBlock.InjectKeyParam.pKeyData = pKey;
    paramBlock.InjectKeyParam.keyProperties = keyProperties;
    paramBlock.InjectKeyParam.phKey = phKey;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_WriteKeyToNvmKeyStore(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     ecy_hsm_Csai_KeyHandleT     hKey,
                                                     ecy_hsm_Csai_KeyIdT         keyId,
                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_WRITE_KEY_TO_NVM_KEY_STORE);

    /* Parameter update */
    paramBlock.WriteKeyToSlotParam.hKey = hKey;
    paramBlock.WriteKeyToSlotParam.keyId = keyId;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_LoadKey(ecy_hsm_Csai_SessionHandleT hSession,
                                       ecy_hsm_Csai_JobPriorityT   priority,
                                       ecy_hsm_Csai_KeyIdT         keySlotId,
                                       ecy_hsm_Csai_KeyTypeT       expectedKeyType,
                                       ecy_hsm_Csai_KeyHandleT*    phKey,
                                       ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_LOAD_KEY);

    /* Parameter update */
    paramBlock.LoadKeyParam.keySlotId = keySlotId;
    paramBlock.LoadKeyParam.expectedKeyType = expectedKeyType;
    paramBlock.LoadKeyParam.phKey = phKey;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseKey(ecy_hsm_Csai_SessionHandleT hSession,
                                          ecy_hsm_Csai_JobPriorityT   priority,
                                          ecy_hsm_Csai_KeyHandleT     hKey,
                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <DJustification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_RELEASE_KEY);

    /* Parameter update */
    paramBlock.ReleaseKeyParam.hKey = hKey;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseKeyForce(ecy_hsm_Csai_SessionHandleT hSession,
                                               ecy_hsm_Csai_JobPriorityT   priority,
                                               ecy_hsm_Csai_KeyIdT         keyId,
                                               ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_RELEASE_KEY_FORCE);

    /* Parameter update */
    paramBlock.ReleaseKeyForceParam.keyId = keyId;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReadPublicKey(ecy_hsm_Csai_SessionHandleT hSession,
                                             ecy_hsm_Csai_JobPriorityT   priority,
                                             ecy_hsm_Csai_KeyHandleT     hKey,
                                             ecy_hsm_Csai_KeyRefT*       pKey,
                                             ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_READ_PUBLIC_KEY);

    if(NULL_PTR == pKey)
    {
        result.stError = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* Private keys should never be exported */
        /* No function should export anything other than a public key that's difficult (except a code review)  to prove,
         * but at least here is the check where anything other than a public key leads to an error
         */
        if ((pKey->type != ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC) && (pKey->type != ecy_hsm_CSAI_KEYTYPE_EDDSA_PUBLIC) &&
            (pKey->type != ecy_hsm_CSAI_KEYTYPE_ECDSA_PUBLIC))
        {
            result.stError = ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE;
        }
        else
        {
            /* Parameter update */
            paramBlock.ReadPublicKeyParam.hKey = hKey;
            paramBlock.ReadPublicKeyParam.key = pKey;

            // execute applet
            result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock),
                                      &paramBlock );
            // update given job handle
            if(phJob != NULL_PTR)
            {
                *phJob = hSession;
            }
        }
    }
    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GenerateKey(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           ecy_hsm_Csai_KeyTypeT       keyType,
                                           ecy_hsm_Csai_KeySizeT       keySize,
                                           uint32                      keyProperties,
                                           ecy_hsm_Csai_KeyHandleT*    phKey,
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_GENERATE_KEY);

    /* Parameter update */
    paramBlock.GenerateKeyParam.keyType = keyType;
    paramBlock.GenerateKeyParam.keySize = keySize;
    paramBlock.GenerateKeyParam.keyProperties = keyProperties;
    paramBlock.GenerateKeyParam.phKey = phKey;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetStorageLocation(ecy_hsm_Csai_SessionHandleT    hSession,
                                                  ecy_hsm_Csai_JobPriorityT      priority,
                                                  ecy_hsm_Csai_KeyIdT            key,
                                                  ecy_hsm_Csai_StorageLocationT* pStorageLocation,
                                                  ecy_hsm_Csai_JobHandleT*       phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT     paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_GET_STORAGE_LOCATION);

    /* Parameter update */
    paramBlock.GetStorageLocationParam.keyId            = key;
    paramBlock.GetStorageLocationParam.pStorageLocation = pStorageLocation;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AssignRamKeyToRamSlot(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     ecy_hsm_Csai_KeyHandleT     hKey,
                                                     ecy_hsm_Csai_KeyIdT         keyId,
                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    HSM_KeysParamT     paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEYS, APPLET_KEYS_FUNC_ASSIGN_RAM_KEY_TO_RAM_SLOT);

    /* Parameter update */
    paramBlock.WriteKeyToSlotParam.hKey  = hKey;
    paramBlock.WriteKeyToSlotParam.keyId = keyId;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
