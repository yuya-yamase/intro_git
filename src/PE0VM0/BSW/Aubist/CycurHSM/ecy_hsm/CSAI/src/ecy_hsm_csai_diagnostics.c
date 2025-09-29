/**
 * @file
 ***********************************************************************************************
 * @brief Diagnostics support implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_applet_diagnostics.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai_diagnostics.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/* CSAI Diagnostics - HSM Dump Init Interface */

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpInit(ecy_hsm_Csai_SessionHandleT          hSession,
                                                                                              ecy_hsm_Csai_DiagnosticsDumpUseCaseT useCaseId,
                                                                                              void*                                pExtInfo,
                                                                                              uint32*                              pImageSize,
                                                                                              uint32*                              pImageAddr,
                                                                                              ecy_hsm_Csai_JobPriorityT            priority,
                                                                                              ecy_hsm_Csai_JobHandleT*             phJob)
{
    /* Initialization */
    Applet_ReturnTypeT            result;
    HSM_DiagnosticsDumpInitParamT paramBlock;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_DIAGNOSTICS, APPLET_DIAGNOSTICS_STATE_DUMP_INIT_E);

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pExtInfo   = pExtInfo;
    paramBlock.useCaseId  = useCaseId;
    paramBlock.pImageSize = pImageSize;
    paramBlock.pImageAddr = pImageAddr;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* CSAI Diagnostics - HSM Dump Update Interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpUpdate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                uint8*                      pBuffer,
                                                                                                uint32                      bufferSize,
                                                                                                uint32*                     pNumBytesDumped,
                                                                                                uint32*                     pBytesLeftFlag,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_ReturnTypeT              result;
    HSM_DiagnosticsDumpUpdateParamT paramBlock;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_DIAGNOSTICS, APPLET_DIAGNOSTICS_STATE_DUMP_UPDATE_E);

    /* Parameter update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.bufferSize     = bufferSize;
    paramBlock.pBytesDumped   = pNumBytesDumped;
    paramBlock.pBytesLeftFlag = pBytesLeftFlag;
    paramBlock.pDumpBuffer    = pBuffer;

    /* Call Applet_Function */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* CSAI Diagnostics - HSM Dump Update Interface */
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_Diagnostics_DumpFinalize(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_DIAGNOSTICS, APPLET_DIAGNOSTICS_STATE_DUMP_FINAL_E);

    /* Call Applet_Function */
    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, 0U, NULL_PTR);

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
