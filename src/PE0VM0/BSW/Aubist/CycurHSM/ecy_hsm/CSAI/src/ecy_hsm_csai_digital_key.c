/**
 * @file
 ***********************************************************************************************
 * @brief This file implements the interface of generic MDK.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_digital_key.h" /* declaration of the exported interfaces implemented in this file */
#include "ecy_hsm_applet.h"           /* Applet_ReturnTypeT */
#include "ecy_hsm_applet_manager.h"   /* Applet_Function */
#include "ecy_hsm_applet_mdk.h"       /* states of the MDK applet */
#include "ecy_hsm_proxy.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** local variables ************************************************************************/

/* *** local function prototypes **************************************************************/

/* *** public implementation  *****************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 4 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_Init(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_INIT);

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, 0U, NULL_PTR);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 6 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateEphemeralKeyPair(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                    uint8*                      pEphemeralPuK,
                                                                                                    uint32*                     pEphemeralPuKLength,
                                                                                                    ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT        result;
    Applet_MDK_DataOut_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_EPHEMERAL_KEYPAIR);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData          = pEphemeralPuK;
    paramBlock.pOutDataLength = pEphemeralPuKLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 6 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SetOemCertificate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                               ecy_hsm_Csai_JobPriorityT   priority,
                                                                                               const uint8*                pCert,
                                                                                               uint32                      certLength,
                                                                                               ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT       result;
    Applet_MDK_DataIn_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_SET_OEM_CERTIFICATE);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData      = pCert;
    paramBlock.dataLength = certLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 4 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_Suspend(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_SUSPEND);

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, 0U, NULL_PTR);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GenerateCommandAuthentication(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                           const uint8*                pCapdu,
                                                                                                           uint32                      capduLength,
                                                                                                           uint8*                      pCmac,
                                                                                                           uint32*                     pCmacLength,
                                                                                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_GENERATE_COMMAND_AUTH);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pCapdu;
    paramBlock.dataLength    = capduLength;
    paramBlock.pResult       = pCmac;
    paramBlock.pResultLength = pCmacLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 6 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateLongTermKeyPair(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                   uint8*                      pVehiclePubKey,
                                                                                                   uint32*                     pVehiclePubKeyLength,
                                                                                                   ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT        result;
    Applet_MDK_DataOut_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_LONGTERM_KEYPAIR);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData          = pVehiclePubKey;
    paramBlock.pOutDataLength = pVehiclePubKeyLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SignVehicleAuthenticationData(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                           const uint8* pDataToBeSigned,
                                                                                                           uint32       dataToBeSignedLength,
                                                                                                           uint8*       pSignature,
                                                                                                           uint32*      pSignatureLength,
                                                                                                           ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_SIGN_VEHICLE_AUTH_DATA);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pDataToBeSigned;
    paramBlock.dataLength    = dataToBeSignedLength;
    paramBlock.pResult       = pSignature;
    paramBlock.pResultLength = pSignatureLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 9 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyAttestationPackage(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                      const uint8*                pAttestationPackage,
                                                                                                      uint32       attestationPackageLength,
                                                                                                      const uint8* pSignature,
                                                                                                      uint32       signatureLength,
                                                                                                      uint8*       pVerificationResult,
                                                                                                      ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_ValidateData_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_ATTESTATION_PACKAGE);

    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData           = pAttestationPackage;
    paramBlock.dataLength      = attestationPackageLength;
    paramBlock.pReference      = pSignature;
    paramBlock.referenceLength = signatureLength;
    paramBlock.pResult         = pVerificationResult;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 6 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelStandard(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                         const uint8*                pKdfInfoParam,
                                                                                                         uint32                   kdfInfoParamLength,
                                                                                                         ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT       result;
    Applet_MDK_DataIn_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_STANDARD);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData      = pKdfInfoParam;
    paramBlock.dataLength = kdfInfoParamLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 6 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateUrsk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        const uint8*                pPartnerPublicValue,
                                                                                        uint32                      partnerPublicValueLength,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT       result;
    Applet_MDK_DataIn_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_URSK);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData      = pPartnerPublicValue;
    paramBlock.dataLength = partnerPublicValueLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelFast(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8* pChannelCreationParams,
                                                                                                     uint32       channelCreationParamsLength,
                                                                                                     uint8*       pSlotId,
                                                                                                     uint32*      pSlotIdLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_FAST);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pChannelCreationParams;
    paramBlock.dataLength    = channelCreationParamsLength;
    paramBlock.pResult       = pSlotId;
    paramBlock.pResultLength = pSlotIdLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 4 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CloseSecureChannel(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CLOSE_SECURE_CHANNEL);

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, 0U, NULL_PTR);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_MDK_VerifyEndpointAuthenticationDataSignature(ecy_hsm_Csai_SessionHandleT hSession,
                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                           const uint8*                pData,
                                                           uint32                      dataLength,
                                                           uint8*                      pVerificationResult,
                                                           uint32*                     pVerificationResultLength,
                                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_ENDPOINT_AUTHDATA_SIGNATURE);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pData;
    paramBlock.dataLength    = dataLength;
    paramBlock.pResult       = pVerificationResult;
    paramBlock.pResultLength = pVerificationResultLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 9 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyResponseAuthentication(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                          const uint8*                pRapdu,
                                                                                                          uint32                      rapduLength,
                                                                                                          const uint8*                pReferenceCmac,
                                                                                                          uint32 referenceCmacLength,
                                                                                                          uint8* pVerificationResult,
                                                                                                          ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_ValidateData_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_RESPONSE_AUTH);

    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData           = pRapdu;
    paramBlock.dataLength      = rapduLength;
    paramBlock.pReference      = pReferenceCmac;
    paramBlock.referenceLength = referenceCmacLength;
    paramBlock.pResult         = pVerificationResult;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DecryptResponse(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             const uint8*                pEncryptedRapdu,
                                                                                             uint32                      encryptedRapduLength,
                                                                                             uint8*                      pDecryptedRapdu,
                                                                                             uint32*                     pDecryptedRapduLength,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_DECRYPT_RESPONSE);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pEncryptedRapdu;
    paramBlock.dataLength    = encryptedRapduLength;
    paramBlock.pResult       = pDecryptedRapdu;
    paramBlock.pResultLength = pDecryptedRapduLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_EncryptCommand(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            const uint8*                pPlainCapdu,
                                                                                            uint32                      plainCapduLength,
                                                                                            uint8*                      pEncCapdu,
                                                                                            uint32*                     pEncCapduLength,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_ENCRYPT_COMMAND);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pPlainCapdu;
    paramBlock.dataLength    = plainCapduLength;
    paramBlock.pResult       = pEncCapdu;
    paramBlock.pResultLength = pEncCapduLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyEndpointSignature(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8*                pData,
                                                                                                     uint32                      dataLength,
                                                                                                     uint8*                      pVerificationResult,
                                                                                                     uint32* pVerificationResultLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_ENDPOINT_SIGNATURE);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pData;
    paramBlock.dataLength    = dataLength;
    paramBlock.pResult       = pVerificationResult;
    paramBlock.pResultLength = pVerificationResultLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 7 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SetOwnerPairingVerifier(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8* pOwnerPairingVerifier,
                                                                                                     uint32       ownerPairingVerifierLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT       result;
    Applet_MDK_DataIn_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_SET_OWNER_PAIRING_VERIFIER);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData      = pOwnerPairingVerifier;
    paramBlock.dataLength = ownerPairingVerifierLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateKBleOob(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           const uint8*                pPaddedSlotIds,
                                                                                           uint32                      paddedSlotIdsLength,
                                                                                           uint8*                      pKBleOob,
                                                                                           uint32*                     pKBleOobLength,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_KBLE_OOB);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pPaddedSlotIds;
    paramBlock.dataLength    = paddedSlotIdsLength;
    paramBlock.pResult       = pKBleOob;
    paramBlock.pResultLength = pKBleOobLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GetUrsk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     const uint8*                pSlotIdAndSessionId,
                                                                                     uint32                      slotIdAndSessionIdLength,
                                                                                     uint8*                      pUrsk,
                                                                                     uint32*                     pUrskLength,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_GET_URSK);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pSlotIdAndSessionId;
    paramBlock.dataLength    = slotIdAndSessionIdLength;
    paramBlock.pResult       = pUrsk;
    paramBlock.pResultLength = pUrskLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GetFriendPk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                         const uint8*                pSlotId,
                                                                                         uint32                      slotIdLength,
                                                                                         uint8*                      pFriendPk,
                                                                                         uint32*                     pFriendPkLength,
                                                                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_GET_FRIEND_PUBKEY);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pSlotId;
    paramBlock.dataLength    = slotIdLength;
    paramBlock.pResult       = pFriendPk;
    paramBlock.pResultLength = pFriendPkLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CalculateSecretOwnerPairing(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                         const uint8*                pData,
                                                                                                         uint32                      dataLength,
                                                                                                         uint8*                      pResult,
                                                                                                         uint32*                     pResultLength,
                                                                                                         ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CALC_SECRET_OWNER_PAIRING);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pData;
    paramBlock.dataLength    = dataLength;
    paramBlock.pResult       = pResult;
    paramBlock.pResultLength = pResultLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 9 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelOwnerPairing(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                             const uint8*                pY,
                                                                                                             uint32                      yLength,
                                                                                                             const uint8* pReferenceMac,
                                                                                                             uint32       referenceMacLength,
                                                                                                             uint8*       pVerificationResult,
                                                                                                             ecy_hsm_Csai_JobHandleT* phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_ValidateData_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_CREATE_SECURE_CHANNEL_OWNER_PAIRING);

    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData           = pY;
    paramBlock.dataLength      = yLength;
    paramBlock.pReference      = pReferenceMac;
    paramBlock.referenceLength = referenceMacLength;
    paramBlock.pResult         = pVerificationResult;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 9 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifySharingPassword(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                   const uint8*                pSeed,
                                                                                                   uint32                      seedLength,
                                                                                                   const uint8*                pSharingPassword,
                                                                                                   uint32                      sharingPasswordLength,
                                                                                                   uint8*                      pVerificationResult,
                                                                                                   ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_ValidateData_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_SHARING_PASSWORD);

    /* PRQA S 2983 5 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData           = pSeed;
    paramBlock.dataLength      = seedLength;
    paramBlock.pReference      = pSharingPassword;
    paramBlock.referenceLength = sharingPasswordLength;
    paramBlock.pResult         = pVerificationResult;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 5 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DeleteDigitalKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                              ecy_hsm_Csai_JobPriorityT   priority,
                                                                                              const uint8*                pSlotId,
                                                                                              ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT       result;
    Applet_MDK_DataIn_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_DELETE_DIGITAL_KEY);

    /* PRQA S 2983 2 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData      = pSlotId;
    paramBlock.dataLength = ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 4 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DeleteAllDigitalKeys(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                  ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT result;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_DELETE_DIGITAL_KEYS);

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, 0u, NULL_PTR);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 8 */ /* Deviation: rule_2.1 */ /* Justification: As this is a library interface, appearing unused is acceptable. */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_MDK_VerifyEndpointCreationAttestationChain(ecy_hsm_Csai_SessionHandleT hSession,
                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                        const uint8*                pAttestationChain,
                                                        uint32                      attestationChainLength,
                                                        uint8*                      pVerificationResult,
                                                        uint32*                     pVerificationResultLength,
                                                        ecy_hsm_Csai_JobHandleT*    phJob)
{
    /* Result returned by the applet */
    Applet_ReturnTypeT             result;
    Applet_MDK_DataToResult_ParamT paramBlock;

    /* Specify the MDK applet and the request-specific state to be executed by HSM's applet manager */
    /* PRQA S 0759 1 */ /* <Justification: usage of union is appropriate here */
    Applet_FunctionT appletFunc = APPFUNC_ID(APPLET_ID_MDK, APPLET_MDK_FUNC_VERIFY_ENDPOINT_CREATION_ATTESTATION_CHAIN);

    /* PRQA S 2983 4 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.pData         = pAttestationChain;
    paramBlock.dataLength    = attestationChainLength;
    paramBlock.pResult       = pVerificationResult;
    paramBlock.pResultLength = pVerificationResultLength;

    /* Place the request for the corresponding applet and state to be performed. */
    result = Applet_Function(hSession, priority, appletFunc, sizeof(paramBlock), &paramBlock);

    /* Update given job handle. Currently, the job handle and the session handle are equal. */
    if (phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *** private implementation  ****************************************************************/

/* *** epilogue  ******************************************************************************/

/**
 * @endcond
 *
 */
