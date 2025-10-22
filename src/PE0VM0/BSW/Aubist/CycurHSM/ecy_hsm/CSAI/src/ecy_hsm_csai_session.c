/**
 * @file ecy_hsm_csai_session.c
 ***********************************************************************************************
 * @brief CSAI Checksum implementation file
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_system.h"
#include "ecy_hsm_csai_session.h"
#include "ecy_hsm_proxy.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1532 2 */ /*  non optimal reference of this function is tested and does not hinder functionality */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_OpenSession(ecy_hsm_Csai_SessionModeT    mode,
                                           ecy_hsm_Csai_JobPriorityT    initialPriority,
                                           ecy_hsm_Csai_SessionHandleT* phSession)
{
    ecy_hsm_Csai_ErrorT retVal;
    CSAI_PARAM_UNUSED(mode);

    if (NULL_PTR == phSession)
    {
        retVal = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        retVal = ecy_HSM_OpenSession(initialPriority, phSession);
    }

    return (retVal);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetSessionStatus(ecy_hsm_Csai_SessionHandleT  hSession,
                                                ecy_hsm_Csai_SessionStatusT* pStatus)
{
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_SESSION_QUERY_E);
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_SystemParamT params;

    params.stSession.pSessionStatus = pStatus;

    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_HIGH, appletFunc, sizeof(params), &params);

    /* Wait for the operation to complete */
    if (ecy_hsm_CSAI_SUCCESS == result.stError)
    {
        result.stError = ecy_HSM_WaitForOpToComplete(hSession, 10u);
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CloseSessionSync(ecy_hsm_Csai_SessionHandleT hSession)
{
    ecy_hsm_Csai_ErrorT     errorCode;
    ecy_hsm_Csai_JobHandleT hJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;

    errorCode = ecy_hsm_Csai_CloseSessionAsync(hSession, &hJob);

    /* Wait for the operation to complete. */
    if (ecy_hsm_CSAI_SUCCESS == errorCode)
    {
        errorCode = ecy_HSM_WaitForOpToComplete(hJob, 10u);
    }
    return (errorCode);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CloseSessionAsync(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_JobHandleT*    phJob)
{
    Applet_ReturnTypeT result;

    /* Schedule at high priority so it is guaranteed to be done before any subsequently scheduled non-safety operations.
     * This avoids the session being re-opened at a higher priority after it has been closed, and the closing
     * actually being actioned after the re-opening.
     * Possibly we should have a "super-high" priority worker task to process these operations, but must also
     * need to avoid interfering with the safety task */
    ecy_hsm_Csai_JobPriorityT priority = ecy_hsm_CSAI_PRIO_HIGH;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SYSTEM, APPLET_SYSTEM_STATE_SESSION_CLOSE_E);

    result = Applet_Function(hSession, priority, appletFunc, 0, NULL_PTR);

    if (ecy_hsm_CSAI_SUCCESS == result.stError)
    {
        if (NULL_PTR != phJob)
        {
            *phJob = hSession;
        }
    }
    else
    {
        if (NULL_PTR != phJob)
        {
            *phJob = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
        }
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
