/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Random number generation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/
#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_rng.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_rng.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_RandomGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        uint8                       random[],
                                                                                        uint32                      length,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_RngParamT      paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_RNG, APPLET_RNG_FUNC_RANDOM_GENERATE);

    /*Structure Update */
    paramBlock.randomGenerateParam.random = random;
    paramBlock.randomGenerateParam.length = length;

    // execute applet
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}
/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_TrueRandomGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            uint8                       random[],
                                                                                            uint32                      length,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_RngParamT      paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_RNG, APPLET_RNG_FUNC_TRUE_RANDOM_GENERATE);

    /*Structure Update */
    paramBlock.trueRandomGenerateParam.random = random;
    paramBlock.trueRandomGenerateParam.length = length;

    // execute applet
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    // update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_RandomSeedExtend(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                          const uint8                 seed[],
                                                                                          uint32                      length,
                                                                                          ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_RngParamT      paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_RNG, APPLET_RNG_FUNC_SEED_EXTEND);

    /*Structure Update */
    paramBlock.randomSeedExtendParam.seed   = seed;
    paramBlock.randomSeedExtendParam.length = length;

    // Execute applet
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);
    // Update given job handle
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
