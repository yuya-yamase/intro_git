/**
 * @file
 ***********************************************************************************************
 * @brief CSAI ECC DH file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_applet_dh.h"
#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_csai_dh.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /*Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhPublicKeyGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                   uint8                       publicKey[],
                                                   uint32*                     length,
                                                   ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_EccDhParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_DH, APPLET_DH_FUNC_PUBLIC_KEY_GENERATE);

    CSAI_PARAM_UNUSED(priority);

    if(length == NULL_PTR)
    {
        result.stError = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /*Structure Update */
        /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
        paramBlock.dhPublicKeyGenParam.pPublicKey = publicKey;
        paramBlock.dhPublicKeyGenParam.pLength = length;

        /* Priority reduced to background as it uses the sign resource */
        /* execute applet */
        result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

        /* update given job handle */
        if(phJob != NULL_PTR)
        {
            *phJob = hSession;
        }
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DhSharedSecretCompute(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     const uint8                 remotePublicKey[],
                                                     const uint32                publicKeyLength,
                                                     uint8                       sharedSecret[],
                                                     uint32*                     sharedSecretLength,
                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Initialization */
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    HSM_EccDhParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* <Deviation: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_DH, APPLET_DH_FUNC_SHARED_SECRET_COMPUTE);

    CSAI_PARAM_UNUSED(priority);

    if(sharedSecretLength == NULL_PTR)
    {
        result.stError = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else
    {
        /*Structure Update */
        paramBlock.dhSharedSecretComputeParam.pRemotePublicKey = remotePublicKey;
        paramBlock.dhSharedSecretComputeParam.publicKeyLength = publicKeyLength;
        paramBlock.dhSharedSecretComputeParam.pSharedSecret = sharedSecret;
        paramBlock.dhSharedSecretComputeParam.pSharedSecretLength = sharedSecretLength;

        /* Priority reduced to background as it uses the sign resource */
        /* execute applet */
        result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

        /* update given job handle */
        if(phJob != NULL_PTR)
        {
            *phJob = hSession;
        }
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
