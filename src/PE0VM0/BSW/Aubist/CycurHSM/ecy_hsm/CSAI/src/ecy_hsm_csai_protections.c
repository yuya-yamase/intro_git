/**
 * @file
 ***********************************************************************************************
 * @brief CSAI PFlash protections code implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_protections.h"
#include "ecy_hsm_csai_protections.h"
#include "ecy_hsm_host_mcal.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"

/**
@details

*/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_FlashUnlock(ecy_hsm_Csai_SessionHandleT hSession,
                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                      uint32                      memRangeAddStart,
                                                      uint32                      memRangeNumBytes,
                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_ProtParamT     paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT   appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_PROT_STATE_FLASHUNLOCK_E);

    /* Parameter update */
    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.memRangeAddStart = memRangeAddStart;
    paramBlock.memRangeNumBytes = memRangeNumBytes;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return  CSAI_ERR(result.stError);
}

/**
@details

*/
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_FlashResume(ecy_hsm_Csai_SessionHandleT hSession,
                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                      ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_ProtParamT     paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT   appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_PROT_STATE_FLASHRESUME_E);

    /* Parameter update (no parameter required for this operation) */

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return  CSAI_ERR(result.stError);
}

/* CSAI Protection disable security critical functions Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_DisableSecCritFunctions(ecy_hsm_Csai_SessionHandleT hSession,
                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                  ecy_hsm_Csai_ProtSecLevelT  secLevel,
                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    HSM_ProtParamT      paramBlock;
    ecy_hsm_Csai_ErrorT result;

    /* in Suspend Mode we don't go over the Applet, since the HSM runs in RAM */
    if (HSM_MODE_SUSPENDED == ecy_hsm_HsmMCAL_GetMode())
    {
        CSAI_PARAM_UNUSED(priority);

        /* Parameter update */
        paramBlock.secLevel = secLevel;
        result              = ecy_HSM_DoDisableSecCritFunctions(hSession, sizeof(paramBlock), &paramBlock, phJob);
    }
    else
    {
        Applet_ReturnTypeT appResult;
        /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
        Applet_FunctionT appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_SECCRITFUNC_STATE_DEACTIVATE_E);

        /* Parameter update */
        paramBlock.secLevel = secLevel;

        /* execute applet */
        appResult = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
        result = appResult.stError;
    }

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return  CSAI_ERR(result);
}

/* [$Satisfies $DD 252] */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_SetPasswords(ecy_hsm_Csai_SessionHandleT hSession,
                                                       ecy_hsm_Csai_JobPriorityT   priority,
                                                       uint8                       numListEntries,
                                                       ecy_hsm_Csai_ProtPasswordT* pList,
                                                       ecy_hsm_Csai_JobHandleT*    phJob)
{

    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_ProtectionParamT paramBlock;
    Applet_ReturnTypeT      result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_PROT_STATE_SETPASSWORDS_E);

    /* Parameter update */
    paramBlock.stProtSetPassword.numListEntries = numListEntries;
    paramBlock.stProtSetPassword.pList          = pList;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    // Update given job handle
    if(phJob != NULL_PTR)
    {
         *phJob = hSession;
    }

    return  CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_Unlock(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 ecy_hsm_Csai_ProtUseCaseIdT useCaseId,
                                                 void*                       pUseCaseIdParam,
                                                 ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_ProtectionParamT paramBlock;
    Applet_ReturnTypeT      result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_PROT_STATE_GENERICUNLOCK_E);

    /* Parameter update */
    paramBlock.stProtUnlockParam.useCaseId       = useCaseId;
    paramBlock.stProtUnlockParam.pUseCaseIdParam = pUseCaseIdParam;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return  CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Protection_Resume(ecy_hsm_Csai_SessionHandleT    hSession,
                                                 ecy_hsm_Csai_JobPriorityT      priority,
                                                 ecy_hsm_Csai_ProtResumeProtIdT resumeProtId,
                                                 void*                          pResumeProtIdParam,
                                                 ecy_hsm_Csai_JobHandleT*       phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_ProtectionParamT paramBlock;
    Applet_ReturnTypeT      result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT        appletFunc = APPFUNC_ID((uint16)APPLET_ID_PROTECTIONS, (uint16)APPLET_PROT_STATE_RESUMEPROTECTION_E);

    /* Parameter update */
    paramBlock.stProtResumeParam.resumeProtId       = resumeProtId;
    paramBlock.stProtResumeParam.pResumeProtIdParam = pResumeProtIdParam;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(ecy_hsm_Csai_ProtResumeProtIdT), &paramBlock);

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return  CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
