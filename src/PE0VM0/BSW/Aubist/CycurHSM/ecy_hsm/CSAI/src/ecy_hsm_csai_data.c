/**
 * @file
 ***********************************************************************************************
 * @brief CSAI secure storage file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_applet_data.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai_data.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReadData(ecy_hsm_Csai_SessionHandleT hSession,
                                        ecy_hsm_Csai_JobPriorityT   priority,
                                        uint32                      tag,
                                        void*                       pData,
                                        uint32                      dataLength,
                                        uint32*                     pDataCount,
                                        ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureStorageParamT paramBlock;
    Applet_FunctionT        appletFunc = APPFUNC_ID(APPLET_ID_SECURESTORAGE, APPLET_SECURESTORAGE_READ);
    Applet_ReturnTypeT      result;

    CSAI_PARAM_UNUSED(priority);

    /* Structure Update */
    paramBlock.readDataParam.tag        = tag;
    paramBlock.readDataParam.pData      = pData;
    paramBlock.readDataParam.pDataCount = pDataCount;
    paramBlock.readDataParam.dataLength = dataLength;

    /* execute applet */
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}


/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_WriteData(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         uint32                      tag,
                                         const void*                 pData,
                                         uint32                      dataLength,
                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureStorageParamT paramBlock;
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECURESTORAGE, APPLET_SECURESTORAGE_WRITE);
    Applet_ReturnTypeT result;
    CSAI_PARAM_UNUSED(priority);

    /* Structure Update */
    paramBlock.writeDataParam.tag = tag;
    paramBlock.writeDataParam.pData = pData;
    paramBlock.writeDataParam.dataLength = dataLength;

    /* execute applet */
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

    /* update given job handle*/
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}


/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeleteData(ecy_hsm_Csai_SessionHandleT hSession,
                                          ecy_hsm_Csai_JobPriorityT   priority,
                                          uint32                      tag,
                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureStorageParamT paramBlock;
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECURESTORAGE, APPLET_SECURESTORAGE_DELETE);
    Applet_ReturnTypeT result;
    CSAI_PARAM_UNUSED(priority);

    /* Structure Update */
    paramBlock.deleteDataParam.tag = tag;
    paramBlock.deleteDataParam.dummy = 0;

    /* execute applet */
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

    /* update given job handle */
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseMirroredData(ecy_hsm_Csai_SessionHandleT hSession,
                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                   ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Justification: Usage of a union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECURESTORAGE, APPLET_SECURESTORAGE_RELEASE);
    Applet_ReturnTypeT result;

    /* execute applet */
    result = Applet_Function( hSession, priority, appletFunc, 0, NULL_PTR );

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
