/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Certificate handling.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/


/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_CERT_H
#define ECY_HSM_CSAI_CERT_H

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"

/**
 * @addtogroup GROUP_CSAI_CERT
 * @{
 */


/* *** defines ********************************************************************************/

#define ECY_HSM_CVCPROF1_IGNORE_OID_CHECK       0U           /**< No OID Check */
#define ECY_HSM_CVCPROF1_COUPLED_OID            0xFFFFFFFFU  /**< Check OID from cert with coupled root cert OID */

/* *** type declarations **********************************************************************/

/** Declaration of the root certificate use case type */
typedef enum ecy_hsm_Csai_RootCertificateUseCaseT
{
    ecy_hsm_CSAI_ROOTCERTINSTALL_X509_V1  = 1U,         /**< Root certificate installation for X509 certificates with software verification */
    ecy_hsm_CSAI_ROOTCERTINSTALL_RESERVED = 0x7FFFFFFFU /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_RootCertificateUseCaseT;

/** Declare digital signature schemes supported by the HSM */
typedef enum ecy_hsm_Csai_CertTypeT
{
    ecy_hsm_CSAI_CVC_PROFILE1      = 1U,                /**< Certificate type "CVC profile1"    */
    ecy_hsm_CSAI_X_509             = 2U,                /**< Certificate type "X509"            */
    ecy_hsm_CSAI_CERTTYPE_RESERVED = 0x7FFFFFFFU        /**< Value defined to use memory size of uint32 for enums   */
} ecy_hsm_Csai_CertTypeT;

/** Declare struct for CVC Profile 1 additional parameter */
typedef struct ecy_hsm_Csai_CertParamCVCProfile1T
{
    uint32 OID;    /**< OID Value @ref ECY_HSM_CVCPROF1_IGNORE_OID_CHECK = No Check, @ref ECY_HSM_CVCPROF1_COUPLED_OID = check OID from cert with coupled root cert OID, every value else used as OID slot ID for OID check */
} ecy_hsm_Csai_CertParamCVCProfile1T;

/** Data structure declaration that contains all necessary data for the root certificate installation of X509v3 certificates */
typedef struct ecy_hsm_Csai_RootCertificateInstallationData_V1T
{
    ecy_hsm_Csai_CertTypeT   type;               /**< Certificate type */
    const uint8*             pRootCertificate;   /**< Pointer to the location of the root certificate */
    uint32                   rootCertLength;     /**< Length of the root certificate in bytes */
    uint32                   rootCertSlotID;     /**< Slot ID of the root certificate */
    uint32                   swPartAddr;         /**< The Address of the SW Part, if SwPartId is 0 */
    uint8                    swPartId;           /**< The identifier of the SW part to be verified */
} ecy_hsm_Csai_RootCertificateInstallationData_V1T;

/** Structure for the root certificate installation context which contains the useCase and a pointer to the data */
typedef struct ecy_hsm_Csai_RootCertificateInstallationContextT
{
    ecy_hsm_Csai_RootCertificateUseCaseT useCase;                          /**< Use case for the current job. This use case will determine how to interpret the data pointer. */
    void*                                pRootCertificateInstallationData; /**< Pointer to the data structure. Interpretation of the data depends on @ref ecy_hsm_Csai_RootCertificateUseCaseT */
} ecy_hsm_Csai_RootCertificateInstallationContextT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_CERT_INJECT
 * @{
 */


/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"
/**
 * [$DD 1208]
 * Initiates a CSAI Inject Certificate process.
 * The caller must specify in which session context the job is to be executed, the certificate format to use,
 * and a pointer which will return a key handle of the public key, contained in the certificate.
 * The caller provides a buffer with the certificate data and its length.
 * [$Satisfies $SW_ARCH 667_v1] [$Satisfies $SW_ARCH 1067_v1] [$Satisfies $SW_ARCH 1068_v1] [$Satisfies $SW_ARCH 1069_v1]
 * [$Satisfies $SW_ARCH 691_v1] [$Satisfies $SW_ARCH 692_v1]
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   type                Specification of the certificate type to use.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM. Parameter will be overridden with background priority.
 * @param[in]   cert                Buffer which contains the certificate content.
 * @param[in]   certLength          Length of cert buffer.
 * @param[out]  phJob               Job handle to the initialized job.
 * @param[out]  phKey               Returned key handle of the injected certificate.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_PARAM_BLOCK_TOO_LARGE      The parameter block is too large
 *   - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP             There is a problem with the HSM2HTS (status) register.
 *   - @ref ecy_hsm_CSAI_ERR_PORT_OUT_OF_RANGE          The specified HSM port phJob is out of range.
 *   - @ref ecy_hsm_CSAI_ERR_TIMEOUT                    An unexpected timeout occurred while trying to communicate with the HSM.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_PARAMETER     Certificate Parser function called with invalid parameter.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INSUFFICIENT_DATA     A DER encoded element cannot be parsed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_NESTED_LEVEL          During parsing process the amount of nested levels was exceeded.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_TAG_SIZE      A DER encoded element is considered invalid since its tag is either too
 *                                                      long or malformed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_LENGTH_SIZE   A DER encoded element is considered invalid since its length is either
 *                                                      too long or malformed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_MALFORMED_DATA        During DER encoding a malformed DER element was found.
 * - @ref ecy_hsm_CSAI_ERR_FLAG_ERROR                   In all other error cases.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InjectCertificate(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_CertTypeT      type,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 const uint8                 cert[],
                                                 uint32                      certLength,
                                                 ecy_hsm_Csai_JobHandleT*    phJob,
                                                 ecy_hsm_Csai_KeyHandleT*    phKey);

/**
 * [$DD 1209]
 * Initiates a generic CSAI Inject Certificate process.
 * The caller must specify in which session context the job is to be executed, the certificate format to use,
 * and a pointer which will return a certificate handle of the injected certificate.
 * The caller provides a buffer with the certificate data and its length.
 * The certificate handle can be used for all asymmetric crypto functions. The HSM will internally check if this handle is a certificate and will
 * readout the public key from the injected certificate.
 * [$Satisfies $SW_ARCH 666_v1] [$Satisfies $SW_ARCH 674_v1] [$Satisfies $SW_ARCH 665_v1]
 * [$Satisfies $SW_ARCH 1067_v1] [$Satisfies $SW_ARCH 1068_v1] [$Satisfies $SW_ARCH 1069_v1]
 *
 * @note The generic parser can be used with the certificate handle to readout all values from the certificate like OID, Authbits or public key.
 *
 * @note The interface @ref ecy_hsm_Csai_WriteCryObjectToNvmStore can be used to persist an injected certificate in the NvmStore.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   type                Specification of the certificate type to use.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM. Parameter will be overridden with background priority.
 * @param[in]   cert                Buffer which contains the certificate content.
 * @param[in]   certLength          Length of cert buffer.
 * @param[out]  phJob               Job handle to the initialized job.*
 * @param[out]  phCert              Returned cert handle of the injected certificate.
 * @param[in]   pParam              Pointer to type specific parameter structure. If the pParam is a NULL Pointer the OID check will be ignored in
 *                                  the type @ref ecy_hsm_CSAI_CVC_PROFILE1.
 * @param[in]   pParamSize          Size of pParam structure in Bytes.
 *
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_PARAM_BLOCK_TOO_LARGE      The parameter block is too large
 *   - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP             There is a problem with the HSM2HTS (status) register.
 *   - @ref ecy_hsm_CSAI_ERR_PORT_OUT_OF_RANGE          The specified HSM port phJob is out of range.
 *   - @ref ecy_hsm_CSAI_ERR_TIMEOUT                    An unexpected timeout occurred while trying to communicate with the HSM.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given function is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_PARAMETER     Certificate Parser function called with invalid parameter.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INSUFFICIENT_DATA     A DER encoded element cannot be parsed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_NESTED_LEVEL          During parsing process the amount of nested levels was exceeded.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_TAG_SIZE      A DER encoded element is considered invalid since its tag is either too
 *                                                      long or malformed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_LENGTH_SIZE   A DER encoded element is considered invalid since its length is either
 *                                                      too long or malformed.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_MALFORMED_DATA        During DER encoding a malformed DER element was found.
 * - @ref ecy_hsm_CSAI_ERR_FLAG_ERROR                   In all other error cases.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InjectCertificateGeneric(ecy_hsm_Csai_SessionHandleT hSession,
                                                        ecy_hsm_Csai_CertTypeT      type,
                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                        const uint8                 cert[],
                                                        uint32                      certLength,
                                                        ecy_hsm_Csai_JobHandleT*    phJob,
                                                        ecy_hsm_Csai_CertHandleT*   phCert,
                                                        void*                       pParam,
                                                        uint32                      pParamSize);
/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CERT_RELEASE
 * @{
 */

/**
 * [$DD 1210]
 * Terminates a CSAI Inject Certificate process.
 * The caller specifies a key handle which shall be released now and which was generated by a former call of
 * ecy_hsm_Csai_InjectCertificate
 * [$Satisfies $SW_ARCH 675_v1]
 *
 * @param[in]   hJob               Job handle to the initialized job.
 * @param[in]   hKey               Returned key handle of the injected certificate.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE               The key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED               The required key has not been loaded into the session
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseCertificate(ecy_hsm_Csai_JobHandleT hJob,
                                                  ecy_hsm_Csai_KeyHandleT hKey);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CERT_GETPUBKEY
 * @{
 */

/**
 * [$DD 1211]
 * Get a key handle of the public key from the injected cert.
 * The public key will be extracted from the injected certificate and stored temporary in the RAM Keystore. The Key handle can be used
 * like other key handles with the CSAI key functions (@ref ecy_hsm_Csai_WriteCryObjectToNvmStore, @ref ecy_hsm_Csai_WriteKeyToNvmKeyStore, @ref
 * ecy_hsm_Csai_ReleaseKey).
 * [$Satisfies $SW_ARCH 677_v1]
 *
 * @param[in]   hJob               Job handle to the initialized job.
 * @param[in]   priority           Requested scheduling priority for this job on the HSM. Parameter will be overridden with low priority for
 *                                 asymmetric operations.
 * @param[in]   hCert              Handle of certificate.
 * @param[out]  phKey              Returned key handle of the public key from certificate.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE               The certificate handle is invalid
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetPubkeyFromCert(ecy_hsm_Csai_JobHandleT   hJob,
                                                 ecy_hsm_Csai_JobPriorityT priority,
                                                 ecy_hsm_Csai_CertHandleT  hCert,
                                                 ecy_hsm_Csai_KeyHandleT*  phKey);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CERT_GENERICPARSER
 * @{
 */

/**
 * [$DD 1212]
 * Parse an injected certificate for a specific tag tree and return the data of the DER element.
 * [$Satisfies $SW_ARCH 676_v1]
 *
 * @note The maximum limit of Tagtree elements is set to 4. Only final DER values can be parsed.
 *
 * @param[in]       hJob               Job handle to the initialized job.
 * @param[in]       hCert              Handle of certificate from @ref ecy_hsm_Csai_InjectCertificateGeneric or stored element ID.
 * @param[in]       occurrence         Number to search the X. tag tree of the transmitted tag tree.
 * @param[in]       pTagTree           Pointer to a tag tree.
 * @param[in]       tagTreeLength      Number of tag tree elements.
 * @param[out]      pData              Pointer to buffer to store the parsed data.
 * @param[in, out]  pDataSize          Pointer to the size of the buffer to get the maximum size and return the written length.
 *
 * @note The complete certificate can be extracted with the constellation of the parameters occurrence=1, tagTreeLength=1 and pTagTree[0] =
 * 0x0000. Get ensure that the Data buffer is big enough for a complete certificate.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE               The certificate handle is invalid.
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               Certificate handle is not supported.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_NO_ELEMENTS_FOUND     Tag tree not found.
 * - @ref ecy_hsm_CSAI_ERR_PARSER_MALFORMED_DATA        The provided certificate contains malformed data.
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             Size of @p pData is too small to store the tag tree element.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ParseCertificate(ecy_hsm_Csai_JobHandleT  hJob,
                                                ecy_hsm_Csai_CertHandleT hCert,
                                                uint16                   occurrence,
                                                const uint32*            pTagTree,
                                                uint16                   tagTreeLength,
                                                uint8*                   pData,
                                                uint32*                  pDataSize);

/**
 * [$DD 1738]
 * Interface for installing a new X509v3 root certificate and persist it in HSM internal non volatile memory.
 * [$Satisfies $SW_ARCH 1101_v1]
 *
 * @details
 * Before the new certificate is persisted and can be used to verify child certificates the following verification steps
 * have to be successful.
 * The given certificate will be parsed. This step also verifies that the certificate complies to X509v3. After that a consistency check of the
 * basic certificate fields is made. If this stage is passed the signature of the given certificate will be verified and additionally the storage
 * location of the certificate in HOST memory is verified as well. If all the above steps are completed successfully the root certificate is
 * persisted in HSM internal non volatile memory and the certificate is ready for further usage.
 *
 * @param[in]       hSession             Handle for the active session
 * @param[in]       priority             Requested scheduling priority for this job on the HSM. Parameter will be overridden with background priority.
 * @param[in]       pRootCertInstallCtx  Pointer to the @ref ecy_hsm_Csai_RootCertificateInstallationContextT, which contains
 *                                       the @ref ecy_hsm_Csai_RootCertificateUseCaseT and a pointer to the data needed for the task.
 *                                       Currently the data has to be a pointer to an object of @ref ecy_hsm_Csai_RootCertificateInstallationData_V1T
 * @param[out]      phJob                Pointer to the active job handle
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session
 *                                                      Either finish the previous job or cancel the running job using @ref
 *                                                      ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              At least one parameter in the context was invalid
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              Not supported useCase set in @p pRootCertInstallCtx.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_SUCCESS                        The new root certificate was validated and stored successfully.
 *  - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   If the parsing or the signature verification of the certificate failed.
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The given key id for a datastore slot is invalid to store the root certificate.
 *  - @ref ecy_hsm_CSAI_ERR_NO_SPACE_ASYM_RAM_KEY      Certificate couldn't be injected because all RAM slots are already in use.
 *  - @ref ecy_hsm_CSAI_ERR_NO_SPACE_FOR_KEY_HANDLE    Certificate couldn't be injected because all key handles for the session are already in use.
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given certificate type is not supported in general.
 *  - @ref ecy_hsm_CSAI_ERR_PARSER_INVALID_LENGTH_SIZE If the common name of issuer or subject is missing.
 *  - @ref ecy_hsm_CSAI_ERR_PARSER_NULL_POINTER        If the given certificate is a null pointer.
 *  - @ref ecy_hsm_CSAI_ERR_PARSER_WRONG_SIZE          If the certificate has the wrong size.
 *  - @ref ecy_hsm_CSAI_ERR_PARSER_WRONG_TYPE          If the certificate has the wrong type.
 *  - Other error codes if the certificate couldn't be persisted.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_InstallRootCertificate(ecy_hsm_Csai_SessionHandleT                       hSession,
                                                      ecy_hsm_Csai_JobPriorityT                         priority,
                                                      ecy_hsm_Csai_RootCertificateInstallationContextT* pRootCertInstallCtx,
                                                      ecy_hsm_Csai_JobHandleT*                          phJob);

/**
 * @}
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* Multiple inclusion lock  */
