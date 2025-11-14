/**
 * @file
 ***********************************************************************************************
 * @brief Public CSAI key exchange interfaces
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_applet_key_exchange.h"
#include "ecy_hsm_service_key_exchange.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai_key_exchange.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                ecy_hsm_Csai_DhAlgorithmT   algorithm,
                                                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                                                uint8                       pPublicKey[],
                                                                                uint32                      publicKeyBuffSize,
                                                                                uint32*                     pPublicKeyLength,
                                                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_DH_INIT);

    /* Structure update */
    paramBlock.keyExchangeDhInitParam.algorithm         = (uint32)algorithm;
    paramBlock.keyExchangeDhInitParam.hKey              = hKey;
    paramBlock.keyExchangeDhInitParam.pPublicKey        = pPublicKey;
    paramBlock.keyExchangeDhInitParam.publicKeyBuffSize = publicKeyBuffSize;
    paramBlock.keyExchangeDhInitParam.pPublicKeyLength  = pPublicKeyLength;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhComputeExt(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                      const uint8                 pRemotePublicKey[],
                                                                                      const uint32                publicKeyLength,
                                                                                      uint8                       pSharedSecret[],
                                                                                      uint32                      sharedSecretLen,
                                                                                      uint32*                     pSharedSecretCount,
                                                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_EXT);

    CSAI_PARAM_UNUSED(priority);

    /* Structure update */
    paramBlock.keyExchangeDhComputeExtParam.pRemotePublicKey   = pRemotePublicKey;
    paramBlock.keyExchangeDhComputeExtParam.publicKeyLength    = publicKeyLength;
    paramBlock.keyExchangeDhComputeExtParam.pSharedSecret      = pSharedSecret;
    paramBlock.keyExchangeDhComputeExtParam.sharedSecretLen    = sharedSecretLen;
    paramBlock.keyExchangeDhComputeExtParam.pSharedSecretCount = pSharedSecretCount;

    /* Priority reduced to background as it uses the sign resource */
    /* execute applet */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhComputeInt(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                      const uint8                 pRemotePublicKey[],
                                                                                      const uint32                publicKeyLength,
                                                                                      ecy_hsm_Csai_KeyHandleT*    phSecret,
                                                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_DH_COMPUTE_INT);

    CSAI_PARAM_UNUSED(priority);

    /* Structure update */
    paramBlock.keyExchangeDhComputeIntParam.pRemotePublicKey = pRemotePublicKey;
    paramBlock.keyExchangeDhComputeIntParam.publicKeyLength  = publicKeyLength;
    paramBlock.keyExchangeDhComputeIntParam.phSecret         = phSecret;

    /* Priority reduced to background as it uses the sign resource */
    /* execute applet */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                  ecy_hsm_Csai_EcbdCurveT     curveId,
                                                                                  uint32                      assignedNumber,
                                                                                  uint32                      partyCount,
                                                                                  ecy_hsm_Csai_KeyHandleT*    phKey,
                                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_ECBD_INIT);

    /* Structure update */
    paramBlock.keyExchangeEcbdInitParam.curveId        = (uint32)curveId;
    paramBlock.keyExchangeEcbdInitParam.assignedNumber = assignedNumber;
    paramBlock.keyExchangeEcbdInitParam.partyCount     = partyCount;
    paramBlock.keyExchangeEcbdInitParam.phKey          = phKey;

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
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdCompute2ndPubKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                              ecy_hsm_Csai_JobPriorityT   priority,
                                                                                              const uint8                 pPublicKeyPreceding[],
                                                                                              const uint8                 pPublicKeyNext[],
                                                                                              uint8                       pPublicKey[],
                                                                                              uint32                      publicKeyBuffSize,
                                                                                              uint32*                     pPublicKeyLength,
                                                                                              ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_ECBD_2ND_PUBKEY);

    /* Structure update */
    paramBlock.keyExchangeEcbdComp2ndPubKeyParam.pPublicKeyPreceding = pPublicKeyPreceding;
    paramBlock.keyExchangeEcbdComp2ndPubKeyParam.pPublicKeyNext      = pPublicKeyNext;
    paramBlock.keyExchangeEcbdComp2ndPubKeyParam.pPublicKey          = pPublicKey;
    paramBlock.keyExchangeEcbdComp2ndPubKeyParam.publicKeyBuffSize   = publicKeyBuffSize;
    paramBlock.keyExchangeEcbdComp2ndPubKeyParam.pPublicKeyLength    = pPublicKeyLength;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                    const uint8                 pPublicKey[],
                                                                                    uint32                      publicKeyLength,
                                                                                    uint32                      assignedNumber,
                                                                                    ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_ECBD_UPDATE);

    /* Structure update */
    paramBlock.keyExchangeEcbdUpdateParam.pPublicKey      = pPublicKey;
    paramBlock.keyExchangeEcbdUpdateParam.publicKeyLength = publicKeyLength;
    paramBlock.keyExchangeEcbdUpdateParam.assignedNumber  = assignedNumber;

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
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_EcbdFinish(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                    ecy_hsm_Csai_KeyHandleT*    phKey,
                                                                                    ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_KeyExchangeParamT paramBlock;
    Applet_ReturnTypeT    result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_KEY_EXCHANGE, APPLET_KEY_EXCHANGE_FUNC_ECBD_FINISH);

    /* Structure update */
    paramBlock.keyExchangeEcbdFinishParam.phKey = phKey;

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
