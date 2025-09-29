/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Trusted Boot- Athenticated Boot functions implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2017, all rights reserved
 **********************************************************************************************/

#include "ecy_hsm_csai_trusted_boot.h"

#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_service.h"
#include "ecy_hsm_basicsrvs.h"

/* To avoid the Guam specific file includes*/
#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif

#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_trusted_boot.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* Local helper function for @ref ecy_hsm_Csai_TbGetSwIdStatus(), not part of public API */
/* pReadVerifTableInfoArray is used for a read-only Operation from shared memory: constant pointer to volatile memory */
LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_hsm_Csai_TbFillTable(uint8                                         swPartId,
                                                          uint32                                        swPartAddr,
                                                          const volatile ecy_hsm_TB_VerifTable_RecordT* pReadVerifTableInfoArray,
                                                          uint8*                                        pSwPartVerifBootMode,
                                                          ecy_hsm_TB_Verification_StatesT*              pSwPartCurrVerifState,
                                                          ecy_hsm_TB_Verification_StatesT*              pLastSwPartVerifState);

LOCAL_INLINE ecy_hsm_Csai_ErrorT ecy_hsm_Csai_TbFillTable(uint8                                         swPartId,
                                                          uint32                                        swPartAddr,
                                                          const volatile ecy_hsm_TB_VerifTable_RecordT* pReadVerifTableInfoArray,
                                                          uint8*                                        pSwPartVerifBootMode,
                                                          ecy_hsm_TB_Verification_StatesT*              pSwPartCurrVerifState,
                                                          ecy_hsm_TB_Verification_StatesT*              pLastSwPartVerifState)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    uint32              i;

    for (i = 0U; i < TB_REF_TABLE_SIZE; i++)
    {
        if ((0U == swPartId) && (pReadVerifTableInfoArray->swPartAddress == swPartAddr))
        {
            *pSwPartVerifBootMode = pReadVerifTableInfoArray->swPartVerifBootMode;
            /* PRQA S 4332 2 */ /* <Deviation: conversion of uint8 to enum does not affect functionality */
            *pSwPartCurrVerifState = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTableInfoArray->swPartCurrVerifState);
            *pLastSwPartVerifState = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTableInfoArray->swPartLastVerifState);

            /* ErrorCode set to success*/
            errorCode = ecy_hsm_CSAI_SUCCESS;
        }
        else if ((0U != swPartId) && (pReadVerifTableInfoArray->swPartId == swPartId))
        {
            /* PRQA S 4332 3 */ /* <Deviation: conversion of uint8 to enum does not affect functionality */
            *pSwPartVerifBootMode  = pReadVerifTableInfoArray->swPartVerifBootMode;
            *pSwPartCurrVerifState = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTableInfoArray->swPartCurrVerifState);
            *pLastSwPartVerifState = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTableInfoArray->swPartLastVerifState);

            /* ErrorCode set to success*/
            errorCode = ecy_hsm_CSAI_SUCCESS;
        }
        else
        {
            /* Do nothing */
        }

        /* exit for-loop after hit */
        if (ecy_hsm_CSAI_SUCCESS == errorCode)
        {
            break;
        }

        /* Set read pointer to next entry  */
        pReadVerifTableInfoArray++;
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRequestSwVerification(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                 uint8                       swPartId,
                                                                                                 uint32                      swPartAddr,
                                                                                                 ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                    appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI);
    ecy_hsm_Csai_TB_RequestVerifyParamT paramBlock;

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.swPartId   = swPartId;
    paramBlock.swPartAddr = swPartAddr;

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
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetHSMMaxNumberOfElements(uint32* pNumOfElements)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if (NULL_PTR == pNumOfElements)
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        *pNumOfElements = ecy_hsm_TbGetVerifTableMaxNumOfElementsHSM();
        errorCode       = ecy_hsm_CSAI_SUCCESS;
    }
    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetSwIdStatus(uint8                            swPartId,
                                                                                         uint32                           swPartAddr,
                                                                                         uint8*                           pSwPartVerifBootMode,
                                                                                         ecy_hsm_TB_Verification_StatesT* pSwPartCurrVerifState,
                                                                                         ecy_hsm_TB_Verification_StatesT* pLastSwPartVerifState,
                                                                                         ecy_hsm_TB_Verification_StatesT* pGblVerifStateFlag,
                                                                                         ecy_hsm_TB_Verification_StatesT* pMnplVerifStateFlag)
{
    ecy_hsm_Csai_ErrorT                   errorCode;
    volatile ecy_hsm_Host_TB_VerifTableT* pReadVerifTable = HSM_GetTBVerifTable();

    if ((NULL_PTR == pSwPartVerifBootMode) || (NULL_PTR == pSwPartCurrVerifState) || (NULL_PTR == pLastSwPartVerifState)
        || (NULL_PTR == pGblVerifStateFlag) || (NULL_PTR == pMnplVerifStateFlag))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        // Version check of the verification table (Host version and HSM version)
        if (TB_REF_TABLE_VERSION != (ecy_hsm_CSAI_TB_VER_VERSION_MSK & pReadVerifTable->verifTableVersion))
        {
            errorCode = ecy_hsm_CSAI_ERR_CFG_VERSION_MISSMATCH;
        }
        else
        {
            /* Read Operation from shared Memory: constant pointer to volatile memory */
            const volatile ecy_hsm_TB_VerifTable_RecordT* pReadVerifTableInfoArray = pReadVerifTable->verifTableInfoArray;
            /* read global flag, because they are every time available */
            /* PRQA S 4332 2 */ /* <Deviation: conversion of uint8 to enum does not affect functionality */
            *pGblVerifStateFlag  = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTable->gblVerifStateFlag);
            *pMnplVerifStateFlag = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTable->mnplVerifStateFlag);

            errorCode = ecy_hsm_Csai_TbFillTable(swPartId,
                                                 swPartAddr,
                                                 pReadVerifTableInfoArray,
                                                 pSwPartVerifBootMode,
                                                 pSwPartCurrVerifState,
                                                 pLastSwPartVerifState);
        }
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbGetGlobalStatus(ecy_hsm_TB_Verification_StatesT* pGblVerifStateFlag,
                                                                                           ecy_hsm_TB_Verification_StatesT* pMnplVerifStateFlag)
{
    ecy_hsm_Csai_ErrorT                   errorCode;
    volatile ecy_hsm_Host_TB_VerifTableT* pReadVerifTable = HSM_GetTBVerifTable();

    if ((NULL_PTR == pGblVerifStateFlag) || (NULL_PTR == pMnplVerifStateFlag))
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        // Version check of the verification table (Host version and HSM version)
        if (TB_REF_TABLE_VERSION != (ecy_hsm_CSAI_TB_VER_VERSION_MSK & pReadVerifTable->verifTableVersion))
        {
            errorCode = ecy_hsm_CSAI_ERR_CFG_VERSION_MISSMATCH;
        }
        else
        {
            /* read global flags */
            /* PRQA S 4332 2 */ /* <Deviation: conversion of uint8 to enum does not affect functionality */
            *pGblVerifStateFlag  = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTable->gblVerifStateFlag);
            *pMnplVerifStateFlag = (ecy_hsm_TB_Verification_StatesT)(pReadVerifTable->mnplVerifStateFlag);

            errorCode = ecy_hsm_CSAI_SUCCESS;
        }
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* [$Satisfies $DD 2768] */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbInit(ecy_hsm_Csai_SessionHandleT               hSession,
                                                                                ecy_hsm_Csai_JobPriorityT                 priority,
                                                                                ecy_hsm_Csai_TB_Init_ParamSetAndVersionT* pParams,
                                                                                ecy_hsm_Csai_JobHandleT*                  phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT      appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_INIT);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 3 */ /* <Deviation: rule_2.1_1503_CSAI */
/* [$Satisfies $DD 2769] */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_TbRequestVerification(ecy_hsm_Csai_SessionHandleT                         hSession,
                                   ecy_hsm_Csai_JobPriorityT                           priority,
                                   ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT* pParams,
                                   ecy_hsm_Csai_JobHandleT*                            phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REQUEST_VERIFICATION);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbEndOfBootChain(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_END_AUTH_BOOT);
    uint32           paramBlock = 0U;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          uint8                       swPartId,
                                                                                          uint32                      swPartAddr,
                                                                                          uint8                       swPartBootMode,
                                                                                          uint8                       swPartRtmdOrder,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT       appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT);
    ecy_hsm_Csai_TB_ParamT paramBlock;

    paramBlock.TB_ReferenceTablePartInitParam.swPartId        = swPartId;
    paramBlock.TB_ReferenceTablePartInitParam.swPartAddr      = swPartAddr;
    paramBlock.TB_ReferenceTablePartInitParam.swPartBootMode  = swPartBootMode;
    paramBlock.TB_ReferenceTablePartInitParam.swPartRtmdOrder = swPartRtmdOrder;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    errorCode = CSAI_ERR(result.stError);
    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartSetSignWithKeyId(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                      uint32                   swPartSignatureAddress,
                                                                                                      uint16                   swPartSignatureType,
                                                                                                      ecy_hsm_Csai_KeyIdT      swPartKeyId,
                                                                                                      uint8                    swPartVerifSignMode,
                                                                                                      ecy_hsm_Csai_JobHandleT* phJob)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                           appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE);
    ecy_hsm_Csai_TB_ReferenceTablePartSetSignT paramBlock;

    if ((swPartVerifSignMode == ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY) || (swPartVerifSignMode == ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT))
    {
        paramBlock.swPartVerifParams.KeystoreRecord.swPartKeyId            = swPartKeyId;
        paramBlock.swPartVerifParams.KeystoreRecord.swPartSignatureAddress = swPartSignatureAddress;
        paramBlock.swPartVerifParams.KeystoreRecord.swPartSignatureType    = swPartSignatureType;
        /* PRQA S 2983 1 */ /* Assignment relevant. Struct passed by reference */
        paramBlock.swPartVerifSignMode = swPartVerifSignMode;

        /* Execute applet */
        result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

        /* Update given job handle */
        if (phJob != NULL_PTR)
        {
            *phJob = hSession;
        }

        errorCode = CSAI_ERR(result.stError);
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartSetSignWithCertAddress(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                            uint32 swPartSignatureAddress,
                                                                                                            uint32 swPartCertAddress,
                                                                                                            uint8  swPartVerifSignMode,
                                                                                                            ecy_hsm_Csai_JobHandleT* phJob)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT                           appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE);
    ecy_hsm_Csai_TB_ReferenceTablePartSetSignT paramBlock;

    if ((swPartVerifSignMode == ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT)
        || (ecy_hsm_CSAI_TB_VERIFMODE_MANUAL_HEADER_BASED_VERIFICATION_V1 == swPartVerifSignMode))
    {
        paramBlock.swPartVerifParams.MemMappedRecord.swPartSignatureAddress = swPartSignatureAddress;
        paramBlock.swPartVerifParams.MemMappedRecord.swPartCertAddress      = swPartCertAddress;
        /* PRQA S 2983 1 */ /* Assignment relevant. Struct passed by reference */
        paramBlock.swPartVerifSignMode = swPartVerifSignMode;

        /* Execute applet */
        result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

        /* Update given job handle */
        if (phJob != NULL_PTR)
        {
            *phJob = hSession;
        }

        errorCode = CSAI_ERR(result.stError);
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            const uint8                 swPartChunk[],
                                                                                            uint32                      swPartChunkNumBytes,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT       appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE);
    ecy_hsm_Csai_TB_ParamT paramBlock;

    paramBlock.TB_ReferenceTablePartUpdateParam.swPartChunkNumBytes = swPartChunkNumBytes;
    paramBlock.TB_ReferenceTablePartUpdateParam.pSwPartChunk        = swPartChunk;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    errorCode = CSAI_ERR(result.stError);

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblPartFinish(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0, NULL_PTR);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    errorCode = CSAI_ERR(result.stError);
    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblFinalize(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          uint32*                     pNumPersistedEntries,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT       appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE);
    ecy_hsm_Csai_TB_ParamT paramBlock;

    if (NULL_PTR == pNumPersistedEntries)
    {
        errorCode = CSAI_ERR(ecy_hsm_CSAI_ERR_INVALID_PARAM);
    }
    else
    {
        paramBlock.TB_ReferenceTablePartFinalizeParam.pNumPersistedEntries = pNumPersistedEntries;

        /* Execute applet */
        result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

        /* Update given job handle */
        if (NULL_PTR != phJob)
        {
            *phJob = hSession;
        }

        errorCode = CSAI_ERR(result.stError);
    }

    return errorCode;
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRefTblFullInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_Table_FULL_INIT);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0, NULL_PTR);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }
    errorCode = CSAI_ERR(result.stError);

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRtmdSuspend(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT   priority,
                                                                                       ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_RTMD_SUSPEND);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0x00U, NULL_PTR);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }
    errorCode = CSAI_ERR(result.stError);

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbRtmdReactivate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_RTMD_REACTIVATION);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0x00U, NULL_PTR);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }
    errorCode = CSAI_ERR(result.stError);

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TbReadRtmdSuspensionData(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                  void*                       pData,
                                                                                                  uint32                      dataLength,
                                                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    ecy_hsm_Csai_ErrorT errorCode;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 2 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT       appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA);
    ecy_hsm_Csai_TB_ParamT paramBlock;

    paramBlock.TB_RTMDSuspendDataParam.pData      = pData;
    paramBlock.TB_RTMDSuspendDataParam.dataLength = dataLength;
    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }
    errorCode = CSAI_ERR(result.stError);

    return errorCode;
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HandleInactiveBankTbRefTbl(ecy_hsm_Csai_SessionHandleT hSession,
                                                                              ecy_hsm_Csai_JobPriorityT   priority,
                                                                              ecy_hsm_Csai_TB_FOTA_DataT* pTBFOTAData,
                                                                              ecy_hsm_Csai_JobHandleT*    phJob)
{

    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_TB_FOTA_USECASE);

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(ecy_hsm_Csai_TB_FOTA_DataT), pTBFOTAData);

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
