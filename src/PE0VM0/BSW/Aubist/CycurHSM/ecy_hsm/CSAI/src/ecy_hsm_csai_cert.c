/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Cert implementation file
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/


#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_cert.h"
#include "ecy_hsm_applet_cert.h"
#include "ecy_hsm_applet_manager.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InjectCertificate(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_CertTypeT      type,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 const uint8                 cert[],
                                                 uint32                      certLength,
                                                 ecy_hsm_Csai_JobHandleT*    phJob,
                                                 ecy_hsm_Csai_KeyHandleT*    phKey)
{
    /* Initialization */
    HSM_CertParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_INJECTCERT_E);

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    /* PRQA S 2983 6 */ /* <Deviation: rule_2.2_2983 */
    paramBlock.certType     = type;
    paramBlock.cert         = cert;
    paramBlock.certLength   = certLength;
    paramBlock.phKey        = phKey;
    paramBlock.authzValue   = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.authzMask    = NULL_PTR;     /* Default initialization in context of ffi */

    // Execute applet: force Background priority because it involves stack-consuming RSA operations
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

    // Update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseCertificate(ecy_hsm_Csai_JobHandleT hJob,
                                                  ecy_hsm_Csai_KeyHandleT hKey)
{
    /* Initialization */
    HSM_CertParamT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_RELEASECERT_E);

    /* Parameter update */
    /* PRQA S 2983 5 */ /* Assignment relevant. Struct passed by reference */
    paramBlock.hKey2Release   = hKey;
    paramBlock.cert         = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.phKey        = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.authzValue   = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.authzMask    = NULL_PTR;     /* Default initialization in context of ffi */

    // Execute applet
    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InjectCertificateGeneric(ecy_hsm_Csai_SessionHandleT hSession,
                                                        ecy_hsm_Csai_CertTypeT      type,
                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                        const uint8                 cert[],
                                                        uint32                      certLength,
                                                        ecy_hsm_Csai_JobHandleT*    phJob,
                                                        ecy_hsm_Csai_CertHandleT*   phCert,
                                                        void*                       pParam,
                                                        uint32                      pParamSize)
{
    /* Initialization */
    HSM_CertParamGenericT paramBlock;
    Applet_ReturnTypeT result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_INJECTCERTGENERIC_E);

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    /* PRQA S 2983 7 */ /* Assignments relevant. Struct passed by reference */
    paramBlock.certType     = type;
    paramBlock.cert         = cert;
    paramBlock.certLength   = certLength;
    paramBlock.phCert       = phCert;
    paramBlock.pParam       = pParam;
    paramBlock.pParamSize   = pParamSize;
    paramBlock.phKey        = NULL_PTR;     /* Default initialization in context of ffi */

    // Execute applet: force Background priority because it involves stack-consuming RSA operations
    result = Applet_Function( hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock );

    // Update given job handle
    if(phJob != NULL_PTR)
    {
        *phJob = hSession;
    }

    return CSAI_ERR(result.stError);
    /* PRQA S 6007 1 */ /* <Deviation: number of function parameters is fixed by design */
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetPubkeyFromCert(ecy_hsm_Csai_JobHandleT   hJob,
                                                 ecy_hsm_Csai_JobPriorityT priority,
                                                 ecy_hsm_Csai_CertHandleT  hCert,
                                                 ecy_hsm_Csai_KeyHandleT*  phKey)
{
  /* Initialization */
    HSM_CertParamGenericT paramBlock;
    Applet_ReturnTypeT result;
   /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_GETPUBKEYFROMCERT_E);

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    /* PRQA S 2983 5 */ /* Assignments relevant. Struct passed by reference */
    paramBlock.hCert2Use     = hCert;
    paramBlock.phKey         = phKey;
    paramBlock.cert          = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.phCert        = NULL_PTR;     /* Default initialization in context of ffi */
    paramBlock.pParam        = NULL_PTR;     /* Default initialization in context of ffi */

    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ParseCertificate(ecy_hsm_Csai_JobHandleT  hJob,
                                                ecy_hsm_Csai_CertHandleT hCert,
                                                uint16                   occurrence,
                                                const uint32*            pTagTree,
                                                uint16                   tagTreeLength,
                                                uint8*                   pData,
                                                uint32*                  pDataSize)
{

    /* Initialization */
    HSM_CertParamGenericParserT paramBlock;
    Applet_ReturnTypeT result;
   /* PRQA S 0759 1 */ /* Applet_FunctionT is an union */
    Applet_FunctionT appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_GENERICPARSER_E);

    /* Parameter update */
    /* PRQA S 2983 6 */ /* Assignments relevant. Struct passed by reference */
    paramBlock.hCert            = hCert;
    paramBlock.occurrence       = occurrence;
    paramBlock.pTagTree         = pTagTree;
    paramBlock.tagTreeLength    = tagTreeLength;
    paramBlock.pData            = pData;
    paramBlock.pDataSize        = pDataSize;

    result = Applet_Function( hJob, ecy_hsm_CSAI_PRIO_UNCHANGED, appletFunc, sizeof(paramBlock), &paramBlock );

    return CSAI_ERR(result.stError);
}

/* PRQA S 1503 2 */ /* <Deviation: rule_2.1_1503_CSAI */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InstallRootCertificate(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                      ecy_hsm_Csai_JobPriorityT                         priority,
                                                      ecy_hsm_Csai_RootCertificateInstallationContextT* pRootCertInstallCtx,
                                                      ecy_hsm_Csai_JobHandleT*                          phJob)
{
    /* Initialization */
    HSM_CertParamInstallRootCertificateT paramBlock;
    Applet_ReturnTypeT                   result;
    /* PRQA S 0759 1 */ /* Applet_FunctionT is a union */
    Applet_FunctionT                     appletFunc = APPFUNC_ID((uint8)APPLET_ID_CERT, (uint8)APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E);

    CSAI_PARAM_UNUSED(priority);

    /* Parameter update */
    paramBlock.pRootCertificateInstallationCtx = pRootCertInstallCtx;

    result = Applet_Function(hSession, ecy_hsm_CSAI_PRIO_BACKGROUND, appletFunc, sizeof(paramBlock), &paramBlock);

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
