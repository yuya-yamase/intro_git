/**
 * @file
 ***********************************************************************************************
 * @brief CSAI hwcsp implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/
/* [$Satisfies $COMPONENT HWCSP_CSAI] */

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_hwcsp.h"
#include "ecy_hsm_csai_hwcsp.h"
#include "ecy_hsm_hwcsp_cfg.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_basicsrvs.h"

#if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED)

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_START_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/* PRQA S 1514 1 */ /** <Deviation: Used by Host HwCsp features which can be enabled by define. */
volatile ecy_hsm_HwCspKeystore_KeyTableT ecy_hsm_HwCspKeystore_SharedTable;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_STOP_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

#endif /* #if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED) */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* [$Satisfies $DD 2635] */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_LoadKey(ecy_hsm_Csai_SessionHandleT                     hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT                       priority,
                                                                                       ecy_hsm_Csai_JobHandleT*                        phJob,
                                                                                       ecy_hsm_Csai_HwCsp_LoadKey_ParamSetAndVersionT* pParams)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HWCSP, ecy_hsm_APPLET_HWCSP_FUNC_LOAD_KEY);

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
/* [$Satisfies $DD 2636] */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_ReleaseKey(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT                          priority,
                                                                                          ecy_hsm_Csai_JobHandleT*                           phJob,
                                                                                          ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetAndVersionT* pParams)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HWCSP, ecy_hsm_APPLET_HWCSP_FUNC_RELEASE_KEY);

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(*pParams), pParams);
    /* update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 3 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 5 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
/* [$Satisfies $DD 2634] */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_Init(ecy_hsm_Csai_SessionHandleT                  hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT                    priority,
                                                                                    ecy_hsm_Csai_JobHandleT*                     phJob,
                                                                                    ecy_hsm_Csai_HwCsp_Init_ParamSetAndVersionT* pParams)
{
    /* Initialization */
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT                      appletFunc = APPFUNC_ID(APPLET_ID_HWCSP, ecy_hsm_APPLET_HWCSP_FUNC_INIT);
    ecy_hsm_Applet_HwCsp_Init_ParametersT appletInitParams;

    /* Parameter update */
#if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED)
    ecy_hsm_HwCspKeystore_SharedTable.version = ecy_hsm_HwCspKeystore_KeyTable_VID0;
    appletInitParams.size                     = sizeof(ecy_hsm_HwCspKeystore_SharedTable);
    appletInitParams.pSharedTable             = (volatile void*)&ecy_hsm_HwCspKeystore_SharedTable;
#else
    appletInitParams.size         = 0U;
    appletInitParams.pSharedTable = NULL_PTR;
#endif
    (void) ecy_memcpy((void *) &appletInitParams.params, (void *) pParams, sizeof(*pParams));

    /* execute applet */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(appletInitParams), &appletInitParams);
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
