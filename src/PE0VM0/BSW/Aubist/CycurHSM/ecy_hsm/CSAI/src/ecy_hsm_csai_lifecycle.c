/**
 * @file ecy_hsm_csai_lifecycle.c
 ***********************************************************************************************
 * @brief CSAI Lifecycle implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_lifecycle.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_lifecycle.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_host_mcal.h"
#include "ecy_hsm_host_proxy.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SetLifecycleState(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           uint32                      nextState,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_LifecycleParamT paramBlock;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_LIFECYCLE, APPLET_LIFECYCLE_UPDATE_STATE_E);

    /* Parameter update */
    paramBlock.nextState = nextState;
    /* PRQA S 2983 2 */              /* <Deviation: rule_2.2_2983 */
    paramBlock.pCurState = NULL_PTR; /* default initialization in context of ffi */
    paramBlock.pHwState  = NULL_PTR; /* default initialization in context of ffi */

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/**************************************************************************************************/
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetLifecycleState(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           uint32*                     pCurState,
                                                                                           uint32*                     pHwState,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_LifecycleParamT paramBlock;
    Applet_ReturnTypeT  result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_LIFECYCLE, APPLET_LIFECYCLE_READ_STATE_E);

    /* Parameter update */
    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pCurState = pCurState;
    paramBlock.pHwState  = pHwState;

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

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
