/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Manual Tabs Verification functions implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/

/* To avoid the Guam specific file includes */
#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif

#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_trusted_boot.h"
#include "ecy_hsm_basicsrvs.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_manual_tabs_verification.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_service.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TabsVerify_SwPart(ecy_hsm_Csai_SessionHandleT               hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT                 priority,
                                                                                           ecy_hsm_Csai_RequestManualVerifyContextT* pManualTabsCtx,
                                                                                           ecy_hsm_Csai_JobHandleT*                  phJob)
{
    Applet_ReturnTypeT                        result;
    ecy_hsm_Csai_TB_RequestManualVerifyParamT paramBlock;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_TB, ecy_hsm_APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI);

    paramBlock.pManualTabsCtx = pManualTabsCtx;

    /* Execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle */
    if (NULL_PTR != phJob)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
