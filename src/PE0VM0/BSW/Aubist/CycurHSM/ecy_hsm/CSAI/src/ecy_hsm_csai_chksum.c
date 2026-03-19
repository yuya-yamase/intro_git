/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Checksum implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_chksum.h"
#include "ecy_hsm_applet_chksum.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_timing_diagnostics.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                           ecy_hsm_Csai_ChksumAlgorithmT algorithm,
                                           ecy_hsm_Csai_JobPriorityT     priority,
                                           const uint8                   msg[],
                                           uint32                        msgLength,
                                           ecy_hsm_Csai_JobHandleT*      phJob)
{
    /* Initialization */
    HSM_CheckSumParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CHKSUM, APPLET_CHKSUM_STATE_INIT);

    /* Parameter update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.algorithm = algorithm;
    paramBlock.msg = msg;
    paramBlock.msgLength = msgLength;
    paramBlock.pResult = NULL_PTR;              /* default initialization in context of ffi */
    paramBlock.pResultCount = NULL_PTR;         /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('S');

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );
    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                            const uint8             chunk[],
                                            const uint32            length)
{
    /* Initialization */
    HSM_CheckSumParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CHKSUM, APPLET_CHKSUM_STATE_UPDATE);


    /*Structure Update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = chunk;
    paramBlock.msgLength = length;
    paramBlock.pResult = NULL_PTR;              /* default initialization in context of ffi */
    paramBlock.pResultCount = NULL_PTR;         /* default initialization in context of ffi */

    ecy_hsm_AddDiagnosticStopwatch('U');

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumFinish(ecy_hsm_Csai_JobHandleT hJob,
                                            uint8*                  pResult,
                                            uint32                  resultLength,
                                            uint32*                 pResultCount,
                                            boolean                 truncationAllowed)
{
    /* Initialization */
    HSM_CheckSumParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CHKSUM, APPLET_CHKSUM_STATE_FINAL);

    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = NULL_PTR;              /* default initialization in context of ffi */
    paramBlock.pResult = pResult;
    paramBlock.resultLength = resultLength;
    paramBlock.pResultCount = pResultCount;
    /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.truncationAllowed = (uint32)truncationAllowed;

    ecy_hsm_AddDiagnosticStopwatch('F');

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Chksum(ecy_hsm_Csai_SessionHandleT   hSession,
                                      ecy_hsm_Csai_ChksumAlgorithmT algorithm,
                                      ecy_hsm_Csai_JobPriorityT     priority,
                                      const uint8                   msg[],
                                      uint32                        msgLength,
                                      uint8*                        pResult,
                                      uint32                        resultLength,
                                      uint32*                       pResultCount,
                                      boolean                       truncationAllowed,
                                      ecy_hsm_Csai_JobHandleT*      phJob)
{
    HSM_CheckSumParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CHKSUM, APPLET_CHKSUM_STATE_FULL);

    CSAI_PARAM_UNUSED(priority);
    paramBlock.algorithm = algorithm;
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = msg;
    paramBlock.msgLength = msgLength;
    paramBlock.pResult = pResult;
    paramBlock.resultLength = resultLength;
    paramBlock.pResultCount = pResultCount;
    /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.truncationAllowed = (uint32)truncationAllowed;

    // execute applet
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    // update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }
    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
