/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Logging source file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_seclog.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_seclog.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogConfig(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            void*                       pEnvData,
                                            uint32                      envDataNumBytes,
                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureLoggingCfgParamT paramBlock;
    Applet_FunctionT           appletFunc = APPFUNC_ID(APPLET_ID_SECLOG, APPLET_SECLOG_CFG);
    Applet_ReturnTypeT         result;

    /* Structure Update */
    paramBlock.envDataAddr = pEnvData;
    /* PRQA S 2983 1 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.envDataNumBytes = envDataNumBytes;

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogRead(ecy_hsm_Csai_SessionHandleT hSession,
                                          ecy_hsm_Csai_JobPriorityT   priority,
                                          uint8                       eventId,
                                          void*                       pLogEntries,
                                          uint32                      logEntriesNumBytes,
                                          uint32*                     pLogEntriesCount,
                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureLoggingRdParamT paramBlock;
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SECLOG, APPLET_SECLOG_READ);
    Applet_ReturnTypeT        result;

    /* Structure Update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.eventId           = eventId;
    paramBlock.pEventData        = pLogEntries;
    paramBlock.pEventCount       = pLogEntriesCount;
    paramBlock.eventDataNumBytes = logEntriesNumBytes;

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogWrite(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           uint8                       eventId,
                                           const void*                 pContextData,
                                           uint32                      contextDataNumBytes,
                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    HSM_SecureLoggingWrParamT paramBlock;
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SECLOG, APPLET_SECLOG_WRITE);
    Applet_ReturnTypeT        result;

    /* Structure Update */
    /* PRQA S 2983 3 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.eventId           = eventId;
    paramBlock.pEventData        = pContextData;
    paramBlock.eventDataNumBytes = contextDataNumBytes;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle*/
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogReadExt(ecy_hsm_Csai_SessionHandleT                           hSession,
                                             ecy_hsm_Csai_JobPriorityT                             priority,
                                             ecy_hsm_Csai_SecLogReadExt_UseCaseAndParamT*          pSecLogReadExtUseCaseAndParam,
                                             ecy_hsm_Csai_JobHandleT*                              phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SECLOG, ecy_hsm_APPLET_SECLOG_READ_EXT);
    Applet_ReturnTypeT        result;

    /* Structure Update */
    /* PRQA S 2961 10 */ /* <Deviation: rule_2.2_2983 */

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*(pSecLogReadExtUseCaseAndParam)), pSecLogReadExtUseCaseAndParam);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogWriteExt(ecy_hsm_Csai_SessionHandleT                          hSession,
                                              ecy_hsm_Csai_JobPriorityT                            priority,
                                              ecy_hsm_Csai_SecLogWriteExt_UseCaseAndParamT*        pSecLogWriteExtUseCaseAndParam,
                                              ecy_hsm_Csai_JobHandleT*                             phJob)
{
    /* Initialization */
    /* PRQA S 0759 2 */ /* <Justification: Usage of a union is appropriate here */
    Applet_FunctionT          appletFunc = APPFUNC_ID(APPLET_ID_SECLOG, ecy_hsm_APPLET_SECLOG_WRITE_EXT);
    Applet_ReturnTypeT        result;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*(pSecLogWriteExtUseCaseAndParam)), pSecLogWriteExtUseCaseAndParam);

    /* update given job handle*/
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
