/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Hash implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_applet_hash.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai_hash.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashStart(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_HashAlgorithmT algorithm,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 msg[],
                                         uint32                      msgLength,
                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_HashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HASH, APPLET_HASH_STATE_INIT);

    /*Structure Update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.algorithm = algorithm;
    paramBlock.msg = msg;
    paramBlock.msgLength = msgLength;
    paramBlock.digest = NULL_PTR;           /* default initialization in context of ffi */
    paramBlock.pDigestCount = NULL_PTR;     /* default initialization in context of ffi */

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
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashUpdate(ecy_hsm_Csai_JobHandleT hJob, const uint8 chunk[], uint32 length)
{
    HSM_HashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HASH, APPLET_HASH_STATE_UPDATE);

    /*Structure Update */
    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = chunk;
    paramBlock.msgLength = length;
    paramBlock.digest = NULL_PTR;           /* default initialization in context of ffi */
    paramBlock.pDigestCount = NULL_PTR;     /* default initialization in context of ffi */

    // execute applet
    result = Applet_Function( hJob,  ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashFinish(ecy_hsm_Csai_JobHandleT hJob,
                                          uint8*                  digest,
                                          uint32                  digestLength,
                                          uint32*                 pDigestCount,
                                          boolean                 truncationAllowed)
{
    /* Initialization */
    HSM_HashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HASH, APPLET_HASH_STATE_FINAL);

    /*Structure Update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.digest = digest;
    paramBlock.digestLength = digestLength;
    paramBlock.pDigestCount = pDigestCount;
    paramBlock.msg = NULL_PTR;          /* default initialization in context of ffi */
    /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.truncationAllowed = (uint32)truncationAllowed;

    // execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Hash(ecy_hsm_Csai_SessionHandleT hSession,
                                    ecy_hsm_Csai_HashAlgorithmT algorithm,
                                    ecy_hsm_Csai_JobPriorityT   priority,
                                    const uint8                 msg[],
                                    uint32                      msgLength,
                                    uint8*                      digest,
                                    uint32                      digestLength,
                                    uint32*                     pDigestCount,
                                    boolean                     truncationAllowed,
                                    ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    HSM_HashParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_HASH, APPLET_HASH_STATE_FULL);

    /*Structure Update */
    paramBlock.algorithm = algorithm;
    /* PRQA S 2983 7 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.msg = msg;
    paramBlock.msgLength = msgLength;
    paramBlock.digest = digest;
    paramBlock.digestLength = digestLength;
    paramBlock.pDigestCount = pDigestCount;
    /* PRQA S 4304 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.truncationAllowed = (uint32)truncationAllowed;

    // execute applet
    result = Applet_Function( hSession,  priority, appletFunc, sizeof(paramBlock), &paramBlock );
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
