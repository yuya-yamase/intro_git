/**
 * @file
 ***********************************************************************************************
 * @brief CSAI security access implementation file
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
#include "ecy_hsm_applet_secacc.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_secacc.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* CSAI SecAcc Get Challenge */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecAcc_GetChallenge(ecy_hsm_Csai_SessionHandleT    hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT      priority,
                                                                                             uint8*                         pChallenge,
                                                                                             uint32                         numBytesChallenge,
                                                                                             uint32*                        pNumBytesChallengeCurr,
                                                                                             ecy_hsm_Csai_SecAcc_UseCaseT   useCaseId,
                                                                                             ecy_hsm_Csai_SecAcc_NonceCtrlT nonceCtrl,
                                                                                             uint32                         slotIdTrustAnchor,
                                                                                             uint32                         slotIdAuthzOid,
                                                                                             uint8                          authLevel,
                                                                                             const uint8* const             pAuthzValue,
                                                                                             const uint8* const             pAuthzMask,
                                                                                             ecy_hsm_Csai_JobHandleT*       phJob)
{
    /* Initialization */
    HSM_SecAcc_ParamT  paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECACC, APPLET_SECACC_STATE_CHALLENGE_E);

    CSAI_PARAM_UNUSED(priority);
    /* default return value of numBytesChallengeCurr is always 0 */
    if (pNumBytesChallengeCurr != NULL_PTR)
    {
        *pNumBytesChallengeCurr = (uint32) 0UL;
    }

    /* Structure Update */
    /* PRQA S 2983 12 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.challenge_st.pData              = pChallenge;
    paramBlock.challenge_st.numBytes           = numBytesChallenge;
    paramBlock.challenge_st.pNumBytesChallenge = pNumBytesChallengeCurr;
    paramBlock.challenge_st.typeId             = (uint8)APPLET_SECACC_CHALLENGE_PFRB_E;
    paramBlock.challenge_st.authLevel          = authLevel;
    paramBlock.challenge_st.useCaseId          = (uint8)useCaseId;
    paramBlock.challenge_st.nonceCtrl          = (uint8)nonceCtrl;
    paramBlock.challenge_st.slotIdTrustAnchor  = slotIdTrustAnchor;
    paramBlock.challenge_st.slotIdAuthzOid     = slotIdAuthzOid;
    paramBlock.challenge_st.pAuthzValue        = pAuthzValue;
    paramBlock.challenge_st.pAuthzMask         = pAuthzMask;
    paramBlock.challenge_st.numAuthzBits       = ecy_hsm_CSAI_SECACC_AUTHBITS_LEN;

    /* Execute applet: Force Background priority because it involves stack-consuming RSA operations */
    result = Applet_Function(hSession,
                             /* @deprecated: Only required for backwards compatibility. Applet already restricts to background prio. */
                             ecy_hsm_CSAI_PRIO_BACKGROUND,
                             appletFunc,
                             sizeof(paramBlock),
                             &paramBlock);
    /* Update given job handle */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: Number of function parameters is fixed by design */
}

/* CSAI SecuAcc Transfer Response */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_SecAcc_TransferResponse(ecy_hsm_Csai_JobHandleT hJob, const uint8* pChunk, uint32 numChunk, uint32 numResponse, uint32* pResultFlag)
{
    /* Initialization */
    HSM_SecAcc_ParamT  paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECACC, APPLET_SECACC_STATE_TRANSFER_RESPONSE_E);

    /* Structure Update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.verify_st.pData           = pChunk;
    paramBlock.verify_st.numBytes        = numResponse;
    paramBlock.verify_st.numBytesCurrent = numChunk;
    paramBlock.verify_st.typeId          = (uint8)APPLET_SECACC_RESPONSE_PFRB_E;
    paramBlock.verify_st.pResult         = pResultFlag;

    /* Execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* CSAI SecuAcc Verify Response */
/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecAcc_VerifyResponse(ecy_hsm_Csai_JobHandleT hJob,
                                                                                               const uint8*            pResponse,
                                                                                               uint32                  numResponse,
                                                                                               uint32*                 pResultFlag)
{
    /* Initialization */
    HSM_SecAcc_ParamT  paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: Usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_SECACC, APPLET_SECACC_STATE_VERIFY_E);

    /* Structure Update */
    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.verify_st.pData           = pResponse;
    paramBlock.verify_st.numBytes        = numResponse;
    paramBlock.verify_st.numBytesCurrent = (uint32) 0UL;
    paramBlock.verify_st.typeId          = (uint8)APPLET_SECACC_RESPONSE_PFRB_E;
    paramBlock.verify_st.pResult         = pResultFlag;

    /* Execute applet */
    result = Applet_Function(hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock);

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
