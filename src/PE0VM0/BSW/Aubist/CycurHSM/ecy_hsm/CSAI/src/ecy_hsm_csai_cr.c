/**
 * @file
 ***********************************************************************************************
 * @brief CSAI challenge response operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for challenge response
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_applet_cr.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_cr.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* CSAI CR Get challenge */
/* PRQA S 1503 4 */  /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 10 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_GetChallenge(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                         ecy_hsm_Csai_CR_UseCaseT    useCaseId,
                                                                                         uint8*                      pResponse,
                                                                                         uint32                      numBytes,
                                                                                         uint32*                     pNumBytesChallenge,
                                                                                         ecy_hsm_Csai_CR_NonceCtrlT  nonceCtrl,
                                                                                         void*                       pChallengeParamT,
                                                                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    Applet_ReturnTypeT        result;
    Applet_CR_ChallengeParamT paramBlock;
    /* PRQA S 0759 1 */ /* Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CR, APPLET_CR_STATE_CHALLENGE_E);

    /* Structure Update */
    /* PRQA S 2983 12 */ /* Deviation: rule_2.2_2983 */

    /* PRQA S 4422,4322 1 */ /* Justification: Casting is important to avoid compiler warning, both enums are synchronized */
    paramBlock.useCaseId          = useCaseId;
    paramBlock.pResponse          = pResponse;
    paramBlock.numBytes           = numBytes;
    paramBlock.pNumBytesChallenge = pNumBytesChallenge;
    paramBlock.nonceCtrl          = nonceCtrl;
    /* PRQA S 0316 1 */ /* Justification: Usage of Void pointer is necessary for the design to pass different types of user specific data */
    paramBlock.pUserSpecificChallengeParam = pChallengeParamT;
    /* Execute applet: Note that CR only allows background priority because it involves stack-consuming RSA operations */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(Applet_CR_ChallengeParamT), (void*)&paramBlock);

    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* Deviation: Number of function parameters is fixed by design */
}

/* PRQA S 1503 3 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 7 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_TransferResponse(ecy_hsm_Csai_JobHandleT  hJob,
                                                                                             ecy_hsm_Csai_CR_UseCaseT useCaseId,
                                                                                             void*                    pTransferParamT,
                                                                                             const uint8*             pResponse,
                                                                                             uint32                   numBytes,
                                                                                             uint32                   numBytesCurrent)
{
    /* Initialization */
    Applet_ReturnTypeT     result;
    Applet_CR_VerifyParamT paramBlock;
    /* PRQA S 0759 1 */ /* Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CR, APPLET_CR_STATE_TRANSFER_E);

    /* PRQA S 2983 9 */      /* Justification: Setting the parameters */
    /* PRQA S 4422,4322 1 */ /* Justification: Casting is important to avoid compiler warning, both enums are synchronized */
    paramBlock.useCaseId       = useCaseId;
    paramBlock.pResponse       = pResponse;
    paramBlock.numBytes        = numBytes;
    paramBlock.numBytesCurrent = numBytesCurrent;
    paramBlock.pResult         = NULL_PTR;
    /* PRQA S 0316 1 */ /* Justification: Usage of Void pointer is necessary for the design to pass different types of user specific data */
    paramBlock.pUserSpecificParam = pTransferParamT;
    /* Execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(Applet_CR_VerifyParamT), (void*)&paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 3 */ /* <Deviation: rule_2.1_1503_CSAI */
/* PRQA S 3673 8 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_CR_VerifyResponse(ecy_hsm_Csai_JobHandleT  hJob,
                                                                                           ecy_hsm_Csai_CR_UseCaseT useCaseId,
                                                                                           void*                    pVerifyParamT,
                                                                                           const uint8*             pResponse,
                                                                                           uint32                   numBytes,
                                                                                           uint32                   numBytesCurrent,
                                                                                           uint32*                  pResult)
{
    /* Initialization */
    Applet_ReturnTypeT     result;
    Applet_CR_VerifyParamT paramBlock;
    /* PRQA S 0759 1 */ /* Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_CR, APPLET_CR_STATE_VERIFY_E);

    /* PRQA S 2983 9 */      /* Setting the parameters */
    /* PRQA S 4422,4322 1 */ /* Casting is important to avoid compiler warning, both enums are synchronized */
    paramBlock.useCaseId       = useCaseId;
    paramBlock.pResponse       = pResponse;
    paramBlock.numBytes        = numBytes;
    paramBlock.numBytesCurrent = numBytesCurrent;
    paramBlock.pResult         = pResult;
    /* PRQA S 0316 1 */ /* Usage of void pointer is necessary for the design to pass different types of user specific data */
    paramBlock.pUserSpecificParam = pVerifyParamT;
    /* Execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(Applet_CR_VerifyParamT), (void*)&paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
