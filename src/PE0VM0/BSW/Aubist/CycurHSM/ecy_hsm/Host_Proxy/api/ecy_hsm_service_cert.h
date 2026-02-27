/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Certificate handling.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for handling of certificates.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_CERT_H
#define ECY_HSM_SERVICE_CERT_H

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_cert.h"

/**
 * @addtogroup GROUP_CSAI_CERT
 * @{
 */

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/
/** Structure for the data passed to a inject certificate and release certificate operation */
typedef struct ecy_hsm_CertParamT
{
    ecy_hsm_Csai_CertTypeT   certType;     /**< Certificate type */
    const uint8*             cert;         /**< Pointer to buffer containing the certificate to be injected */
    uint32                   certLength;   /**< Effective length of the certificate in cert  */
    const uint8*             authzValue;   /**< Pointer to buffer containing authorization bits */
    const uint8*             authzMask;    /**< Pointer to buffer containing authorization mask */
    uint32                   authzLength;  /**< Length of the buffers authzValue and authzLength */
    ecy_hsm_Csai_KeyHandleT* phKey;        /**< Pointer to variable which contains the key handle after successful injection */
    ecy_hsm_Csai_KeyHandleT  hKey2Release; /**< Certificate/key handle to be released from key store */
} ecy_hsm_CertParamT;

/** Structure for the data passed to a generic inject certificate and release certificate operation */
typedef struct ecy_hsm_CertParamGenericT
{
    ecy_hsm_Csai_CertTypeT    certType;     /**< Certificate type */
    const uint8*              cert;         /**< Pointer to buffer containing the certificate to be injected */
    uint32                    certLength;   /**< Effective length of the certificate in cert  */
    ecy_hsm_Csai_CertHandleT* phCert;       /**< Pointer to variable which contains the cert handle after successful injection */
    ecy_hsm_Csai_CertHandleT  hCert2Use;    /**< Certificate/key handle to be used for release from key store or for get public key */
    void*                     pParam;       /**< Void Pointer to a type defined parameter */
    uint32                    pParamSize;   /**< Size of the parameters from the void pointer */
    ecy_hsm_Csai_KeyHandleT*  phKey;        /**< Pointer to variable which contains the key handle after Get Public Key function call */
    ecy_hsm_Csai_KeyHandleT   hKey2Release; /**< Certificate/key handle to be released from key store */
} ecy_hsm_CertParamGenericT;

/** Structure for the data passed to a generic certificate parser.*/
typedef struct ecy_hsm_CertParamGenericParserT {
    ecy_hsm_Csai_CertTypeT   certType;      /**< Certificate type */
    ecy_hsm_Csai_CertHandleT hCert;         /**< Certificate handle to be used for parsing */
    uint16 occurrence;                      /**< Value for the search depth in the certificate (needed for X509 - multiple Tag trees possible )*/
    uint16 tagTreeLength;                   /**< Length of TagTree Elements */
    const uint32 *pTagTree;                 /**< Pointer to a List of Tagtrees */
    uint8* pData;                           /**< Pointer to variable which contains the key handle after Get Public Key function call */
    uint32* pDataSize;                      /**< Pointer to the size of the pData and returns the written data size */
} ecy_hsm_CertParamGenericParserT;

/** Structure for the data passed for the installation of the root certificate. */
typedef struct ecy_hsm_CertParamInstallRootCertificateTag
{
    ecy_hsm_Csai_RootCertificateInstallationContextT* pRootCertificateInstallationCtx; /**< Pointer to the root certificate installation context */
} ecy_hsm_CertParamInstallRootCertificateT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_CertParamT
 */
#define HSM_CertParamT ecy_hsm_CertParamT
/**
 * @deprecated by @ref ecy_hsm_CertParamGenericT
 */
#define HSM_CertParamGenericT ecy_hsm_CertParamGenericT
/**
 * @deprecated by @ref ecy_hsm_CertParamGenericParserT
 */
#define HSM_CertParamGenericParserT ecy_hsm_CertParamGenericParserT
/**
 * @deprecated by @ref ecy_hsm_CertParamInstallRootCertificateTag
 */
#define HSM_CertParamInstallRootCertificateT ecy_hsm_CertParamInstallRootCertificateT
/**
 * @deprecated by @ref ecy_hsm_CertParamInstallRootCertificateTag
 */
#define HSM_CertParamInstallRootCertificateTag ecy_hsm_CertParamInstallRootCertificateTag

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
