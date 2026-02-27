/**
 * @file
 ***********************************************************************************************
 * @brief BULK MAC generation and verification service
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2018, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_applet_mac_gen.h"
#include "ecy_hsm_applet_mac_verify.h"
#include "ecy_hsm_applet_manager.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* [$Satisfies $DD 889] CSAI Bulk MAC Generate interface, defined in dox */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacGenerateFast(ecy_hsm_Csai_SessionHandleT     hSession,
                                                   ecy_hsm_Csai_JobPriorityT       priority,
                                                   ecy_hsm_Csai_BulkMacFastGenJob* pBulkMacJobs,
                                                   uint32                          numBulkMacJobs,
                                                   ecy_hsm_Csai_JobHandleT*        phJob)
{
    /* Initialization */
    HSM_BulkMacFastGenParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 *//* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MACGEN, APPLET_MACGEN_STATE_BULKFAST_E);

    /* Parameter update */
    /* PRQA S 2983 8 *//* <Deviation: rule_2.2_2983 */
    paramBlock.pTable = pBulkMacJobs;
    paramBlock.numOfEntries = numBulkMacJobs;

    // execute applet
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR( result.stError );
}

/* [$Satisfies $DD 888] CSAI Bulk safe MAC verify interface */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacVerifyFast(ecy_hsm_Csai_SessionHandleT     hSession,
                                                 ecy_hsm_Csai_JobPriorityT       priority,
                                                 ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                 uint32                          numBulkMacJobs,
                                                 ecy_hsm_Csai_JobHandleT*        phJob)
{
    /* Initialization */
    HSM_BulkMacFastVerParamT paramBlock;
    Applet_ReturnTypeT result; /* initialized by Applet_Function() */
    /* PRQA S 0759 1 *//* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MAC_VERIFY, APPLET_MACVERIFY_STATE_BULKFAST_E);

    /* Parameter update */
    /* PRQA S 2983 20 *//* <Deviation: rule_2.2_2983 */
    paramBlock.pTable = pBulkMacJobs;
    paramBlock.numOfEntries = numBulkMacJobs;

    /* Execute applet */
    result = Applet_Function( hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock );

    /* Update given job handle */
    if( phJob != NULL_PTR )
    {
        *phJob = hSession;
    }

    return CSAI_ERR( result.stError );
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
