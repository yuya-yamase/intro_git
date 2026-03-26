/**
 * @file
 ***********************************************************************************************
 * @brief Secure Space Scripting host CSAI interface implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/
/* [$Satisfies $COMPONENT Secure_Space_Scripting_CSAI] */

#include "ecy_hsm_applet_manager.h" /* Applet_Function */
#include "ecy_hsm_applet_sss.h"     /* states of the SSS applet */
#include "ecy_hsm_csai_sss.h"       /* declaration of the exported interfaces implemented in this file */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_ScriptInit(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        uint32                      scriptId,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob,
                                                                                        void*                       pParam,
                                                                                        const uint32                paramSize)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_Sss_ScriptInit_ParamT paramBlock;

    /* Specify the SSS applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SSS, APPLET_SSS_FUNC_INIT_SCRIPT);

    /* Pass a script identifier to the HSM core */
    paramBlock.scriptId  = scriptId;
    paramBlock.pParam    = pParam;
    paramBlock.paramSize = paramSize;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 3673 5 */ /* Justification: Status info is modified by the HSM */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_RunScript(ecy_hsm_Csai_SessionHandleT   hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT     priority,
                                                                                       ecy_hsm_Csai_Sss_StatusInfoT* pStatusInfo,
                                                                                       ecy_hsm_Csai_JobHandleT*      phJob,
                                                                                       void*                         pParam,
                                                                                       const uint32                  paramSize)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_Sss_RunScript_ParamT paramBlock;

    /* Specify the SSS applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SSS, APPLET_SSS_FUNC_RUN_SCRIPT);

    paramBlock.pStatusInfo = pStatusInfo;
    paramBlock.pParam      = pParam;
    paramBlock.paramSize   = paramSize;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Sss_SetScriptInputs(ecy_hsm_Csai_SessionHandleT          hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT            priority,
                                                                                             const ecy_hsm_Csai_Sss_ScriptInputT* pScriptInput,
                                                                                             const uint32                         scriptInputCount,
                                                                                             ecy_hsm_Csai_JobHandleT*             phJob,
                                                                                             void*                                pParam,
                                                                                             const uint32                         paramSize)
{
    Applet_ReturnTypeT            result;
    Applet_Sss_ScriptInput_ParamT paramBlock;

    /* PRQA S 0759 1 */ /* Applet_FunctionT is a union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_SSS, (uint8)APPLET_SSS_FUNC_SET_SCRIPT_INPUTS);

    paramBlock.pScriptInputs     = pScriptInput;
    paramBlock.scriptInputsCount = scriptInputCount;
    paramBlock.pParam            = pParam;
    paramBlock.paramSize         = paramSize;

    /* Places the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    if (NULL_PTR != phJob)
    {
        /* Currently, the job handle and the session handle are equal. */
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
