/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Miscellaneous implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_misc.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_system.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* [$Satisfies $DD 2465] */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetCoreVersion(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        ecy_hsm_Csai_VersionDataT*  pVersionData,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_VERSION_QUERY_E);
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stVersion.pVersionData = pVersionData;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    /* Wait for the operation to complete */
    if (ecy_hsm_CSAI_SUCCESS == result.stError)
    {
        result.stError = ecy_HSM_WaitForOpToComplete(hSession, 10u);
    }

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 277] */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SetSerialNo(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     uint8                       bufferLengthSerialNo,
                                                                                     uint8*                      pBufferSerialNo,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_SYSTEM, (uint16)APPLET_SYSTEM_STATE_SETSERIALNO_E);
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stSetSerialNo.pBufferSerialNo      = pBufferSerialNo;
    params.stSetSerialNo.bufferLengthSerialNo = bufferLengthSerialNo;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 2535]*/
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetDeviceId(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     uint8*                      pNumBytesBufferSerialNo,
                                                                                     uint8*                      pBufferSerialNo,
                                                                                     uint8*                      pNumBytesBufferChipId,
                                                                                     uint8*                      pBufferChipId,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_SYSTEM, (uint16)APPLET_SYSTEM_STATE_GETDEVICEID_E);
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stGetDeviceId.pNumBytesBufferSerialNo = pNumBytesBufferSerialNo;
    params.stGetDeviceId.pBufferSerialNo         = pBufferSerialNo;
    params.stGetDeviceId.pNumBytesBufferChipId   = pNumBytesBufferChipId;
    params.stGetDeviceId.pBufferChipId           = pBufferChipId;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Config_ReadGenericData(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                uint8*                      pData,
                                                                                                uint32                      numBytesData,
                                                                                                uint32*                     pNumBytesDataRead,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_SYSTEM, (uint16)APPLET_SYSTEM_STATE_CONFIG_READ_GENDATA_E);
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stConfigReadGenericData.pData             = pData;
    params.stConfigReadGenericData.numBytesData      = numBytesData;
    params.stConfigReadGenericData.pNumBytesDataRead = pNumBytesDataRead;

    // execute applet
    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* [$Satisfies $DD 2967]*/
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_ReadRegister(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             uint32                      registerAddress,
                                                                                             uint8*                      pRegisterSize,
                                                                                             uint8*                      pRegisterValue,
                                                                                             uint8*                      pRegisterBitmask,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_SystemParamT paramBlock;
    Applet_ReturnTypeT  result;

    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_READ_REGISTER_E);

    /* Structure update */
    paramBlock.stReadRegisterData.registerAddress  = registerAddress;
    paramBlock.stReadRegisterData.pRegisterSize    = pRegisterSize;
    paramBlock.stReadRegisterData.pRegisterValue   = pRegisterValue;
    paramBlock.stReadRegisterData.pRegisterBitmask = pRegisterBitmask;

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

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Verify_HSM_Firmware(ecy_hsm_Csai_SessionHandleT           hSession,
                                 ecy_hsm_Csai_JobPriorityT             priority,
                                 const uint32                          memRangeStart,
                                 ecy_hsm_Csai_FwVerificationStateRefT* pVerificationResult,
                                 ecy_hsm_Csai_JobHandleT*              phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_VERIFY_FIRMWARE_E);
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stVerificationState.memRangeStart     = memRangeStart;
    params.stVerificationState.pVerificationData = pVerificationResult;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetVersion(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT     priority,
                                                                                    ecy_hsm_Csai_JobHandleT*      phJob,
                                                                                    ecy_hsm_Csai_VersionFormatIdT requestFormat,
                                                                                    void*                         pRequestParams,
                                                                                    void*                         pVersionData)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_VERSION_QUERY_FORMAT_ID_E);
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stGetVersion.pRequestParams = pRequestParams;
    params.stGetVersion.pVersionData   = pVersionData;
    params.stGetVersion.requestFormat  = requestFormat;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Config_PowerMode(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT     priority,
                                                                                          ecy_hsm_Csai_ConfigPowerModeT configType,
                                                                                          void*                         pConfigData,
                                                                                          uint32                        configDataLen,
                                                                                          ecy_hsm_Csai_JobHandleT*      phJob)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_SYSTEM, (uint16)APPLET_SYSTEM_STATE_POWER_MODE_CONFIG_E);
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stPowerModeConfigData.configType    = configType;
    params.stPowerModeConfigData.pConfigData   = pConfigData;
    params.stPowerModeConfigData.configDataLen = configDataLen;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_FEEMGR_TriggerReorg(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: Usage of a union is appropriate here */
    Applet_FunctionT   appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_FEEMGR_TRIGGER_REORG_E);
    Applet_ReturnTypeT result;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0, NULL_PTR);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_FEEMGR_CheckReorgOnWrite(ecy_hsm_Csai_SessionHandleT          hSession,
                                      ecy_hsm_Csai_JobPriorityT            priority,
                                      ecy_hsm_Csai_FeeMgr_StructVersionIdT feeParamsVersion,
                                      void*                                pFeeParams,
                                      uint32                               feeParamsLength,
                                      ecy_hsm_Csai_JobHandleT*             phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;
    Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_FEEMGR_CHECK_REORG_ON_WRITE_E);
    Applet_ReturnTypeT  result;

    /* Structure Update */
    params.stCheckReorgOnWriteData.version         = feeParamsVersion;
    params.stCheckReorgOnWriteData.pFeeParams      = pFeeParams;
    params.stCheckReorgOnWriteData.feeParamsLength = feeParamsLength;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_Misc_GetHsmIntegrityData(ecy_hsm_Csai_SessionHandleT          hSession,
                                      ecy_hsm_Csai_JobPriorityT            priority,
                                      ecy_hsm_Csai_FwIntegrityDataVersionT fwIntegrityDataVersion,
                                      void*                                pValidationData,
                                      ecy_hsm_Csai_JobHandleT*             phJob)
{

    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_SYSTEM, (uint16)APPLET_SYSTEM_STATE_SYSTEM_VERIFICATION_VALUE);
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;
    params.stPartVerificationData.fwIntegrityDataVersion = fwIntegrityDataVersion;
    params.stPartVerificationData.pVerificationData      = pValidationData;

    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 3 */ /*Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 5 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_VerifyRegister(ecy_hsm_Csai_SessionHandleT          hSession,
                                                     ecy_hsm_Csai_JobPriorityT            priority,
                                                     ecy_hsm_Csai_VerifyRegisterUseCaseT  useCaseId,
                                                     void*                                pRegisterParam,
                                                     uint16                               totalNumOfRegisters,
                                                     ecy_hsm_Csai_JobHandleT*             phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Deviation: Usage of union is appropriate here */
    Applet_SystemParamT params;
    Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_VERIFY_REGISTER_E);
    Applet_ReturnTypeT  result;

    /* Structure Update */
    params.stVerifyRegister.pVerifyRegister      = pRegisterParam;
    params.stVerifyRegister.useCaseId            = useCaseId;
    params.stVerifyRegister.totalNumOfRegisters  = totalNumOfRegisters;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(params), &params);

    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_System_VerifyHsmConfiguration(ecy_hsm_Csai_SessionHandleT          hSession,
                                                             ecy_hsm_Csai_JobPriorityT            priority,
                                                             ecy_hsm_Csai_JobHandleT*             phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: Usage of a union is appropriate here */
    Applet_FunctionT    appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_VERIFY_HSM_CONFIGURATION_E);
    Applet_ReturnTypeT  result;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, 0, NULL_PTR);

    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
