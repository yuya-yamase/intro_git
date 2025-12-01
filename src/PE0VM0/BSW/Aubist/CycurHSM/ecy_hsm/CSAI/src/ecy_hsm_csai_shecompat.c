/**
 * @file
 ***********************************************************************************************
 * @brief CSAI SHE compatible functions implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_csai_shecompat.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_she.h"
#include "ecy_hsm_ipcdrv.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_GetStatus(ecy_hsm_Csai_SessionHandleT hSession, uint8* pStatus)
{
    ecy_hsm_Csai_ErrorT retVal;

    if(NULL_PTR == pStatus)
    {
        retVal = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /* The RNG bit is always set    */
        //TODO_F1H : HSM2HTS not accessible from here without using pointer gymnastics ... find a solution ?
        *pStatus = (uint8)(ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_SHE_MASK);

        if(ecy_hsm_CSAI_FC_BUSY == ecy_HSM_GetSessionStatus(hSession))
        {
            *pStatus |= ecy_hsm_CSAI_SHE_STATUS_BUSY;
        }

        retVal = ecy_hsm_CSAI_SUCCESS;
    }

    return(retVal);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_GetID(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 challenge[16],
                                         uint8                       id[15],
                                         uint8*                      pStatus,
                                         uint8                       mac[16],
                                         ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_GET_ID);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_GetIDParam.csaiErrors = TRUE;
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.SHE_GetIDParam.challenge = challenge;
    paramBlock.SHE_GetIDParam.id = id;
    paramBlock.SHE_GetIDParam.pStatus = pStatus;
    paramBlock.SHE_GetIDParam.mac = mac;

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKey(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                           const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                           const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                           uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                           uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_LOAD_KEY);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = TRUE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = 0xFF;

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

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKeyExtended(ecy_hsm_Csai_SessionHandleT hSession,
                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                   const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                   const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                   const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                   uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                   uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                   ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_LOAD_KEY_EXTENDED);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = TRUE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = 0xFF;

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

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKeyToBank(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                 const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                 const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                 uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                 uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                 uint32                      bankIndex,
                                                 ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_LOAD_KEY_TO_BANK);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadKeyToBankParam.csaiErrors = TRUE;
    paramBlock.SHE_LoadKeyToBankParam.m1         = m1;
    paramBlock.SHE_LoadKeyToBankParam.m2         = m2;
    paramBlock.SHE_LoadKeyToBankParam.m3         = m3;
    paramBlock.SHE_LoadKeyToBankParam.m4         = m4;
    paramBlock.SHE_LoadKeyToBankParam.m5         = m5;
    paramBlock.SHE_LoadKeyToBankParam.bankIndex  = bankIndex;

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

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadPlainKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                const uint8                 key[16],
                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_LOAD_PLAIN_KEY);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_LoadPlainKeyParam.csaiErrors = TRUE;
    paramBlock.SHE_LoadPlainKeyParam.key        = key;

    // execute applet
    result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_She_ExportRamKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                  uint8                       m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                  uint8                       m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                  uint8                       m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                  uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                  uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_EXPORT_RAM_KEY);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_ExportRamKeyParam.csaiErrors = TRUE;
    paramBlock.SHE_ExportRamKeyParam.m1         = m1;
    paramBlock.SHE_ExportRamKeyParam.m2         = m2;
    paramBlock.SHE_ExportRamKeyParam.m3         = m3;
    paramBlock.SHE_ExportRamKeyParam.m4         = m4;
    paramBlock.SHE_ExportRamKeyParam.m5         = m5;

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

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBoot(ecy_hsm_Csai_SessionHandleT hSession,
                                              ecy_hsm_Csai_JobPriorityT   priority,
                                              uint32                      dataLength,
                                              const uint8                 data[],
                                              ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_SECURE_BOOT);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootParam.csaiErrors = TRUE;
    paramBlock.SHE_SecureBootParam.size = dataLength;
    paramBlock.SHE_SecureBootParam.data = data;

    // execute applet
    result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBootOk(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_SECURE_BOOT_OK);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootControlParam.csaiErrors =TRUE;

    // execute applet
    result = Applet_Function( hSession,priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBootFailure(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    HSM_SheParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Justification: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SHE, APPLET_SHE_FUNC_SECURE_BOOT_FAILURE);

    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootControlParam.csaiErrors = TRUE;

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
