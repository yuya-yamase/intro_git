/**
 * @file
 ***********************************************************************************************
 * @brief This header file is part of the interface to MDK applet.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/

/**
 * @addtogroup GROUP_CSAI CSAI - Cryptographic Service Abstraction Interface
 * @{
 * @addtogroup  GROUP_MDK CSAI Mobile Device Key
 * @brief
 * @{
 * @addtogroup GROUP_MDK_CSAI MDK Interface Definitions
 * @{
 *
 */

#ifndef ECY_HSM_CSAI_DIGITAL_KEY_H
# define ECY_HSM_CSAI_DIGITAL_KEY_H

/* *** includes *******************************************************************************/

# if defined(GUAM)
#  include "ecy_hsm_general.h"
# endif
# include "ecy_hsm_csai.h"
# include "ecy_hsm_csai_keys.h"

/* *** defines ********************************************************************************/

/** Length of MDK slot ID */
# define ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN                 4U
/** Maximal CAPDU length for the ecy_hsm_Csai_MDK_EncryptCommand() interface */
# define ecy_hsm_CSAI_MDK_ENCRYPT_CAPDU_MAX_LEN           255U
/** Length of the seed used during verification of the sharing password */
# define ecy_hsm_CSAI_MDK_SHARING_PASSWORD_SEED_LEN       8U
/** Length of sharing password */
# define ecy_hsm_CSAI_MDK_SHARING_PASSWORD_MAX_LEN        16U
/** Length of the SCP03 CMAC in bytes */
# define ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN                  8U
/** Length of the SCP03 CMAC in bits */
# define ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN_BITS             (ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN * BITS_PER_BYTE)
/** Length of the SCP03 RMAC in bytes */
# define ecy_hsm_CSAI_MDK_SCP03_RMAC_LEN                  8U
/** Length of the SCP03 RMAC in bits */
# define ecy_hsm_CSAI_MDK_SCP03_RMAC_LEN_BITS             (ecy_hsm_CSAI_MDK_SCP03_RMAC_LEN * BITS_PER_BYTE)
/** Length of the CMAC in bytes */
# define ecy_hsm_CSAI_MDK_CMAC_LEN                        16U
/** Length of the CMAC in bits */
# define ecy_hsm_CSAI_MDK_CMAC_LEN_BITS                   (ecy_hsm_CSAI_MDK_CMAC_LEN * BITS_PER_BYTE)
/** Length of ECC public key encoding */
# define ecy_hsm_CSAI_MDK_PUBKEY_ENCODING_LEN             1U
/** Length of an ECC coordinate */
# define ecy_hsm_CSAI_MDK_COORDINATE_LEN                  ecy_hsm_CSAI_ECDSA_SECP256_COORDINATE_SIZE_BYTES
/** Length of an ECC public key */
# define ecy_hsm_CSAI_MDK_PUBKEY_LEN                      ecy_hsm_CSAI_ECDSA_SECP256_PUB_KEY_SIZE_BYTE
/** Length of an ECC signature */
# define ecy_hsm_CSAI_MDK_SIGNATURE_LEN                   ecy_hsm_CSAI_ECDSA_SECP256_SIGNATURE_LENGTH
/** Length of an encoded ECC public key */
# define ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN              (ecy_hsm_CSAI_MDK_PUBKEY_ENCODING_LEN + ecy_hsm_CSAI_MDK_PUBKEY_LEN)
/** Identifier for an ECC public key in uncompressed form */
# define ecy_hsm_CSAI_MDK_PUBKEY_KEY_FORMAT_UNCOMPRESSED  0x04U
/** Minimum length of TLV5C element */
# define ecy_hsm_CSAI_MDK_TLV5C_MIN_LEN                   2U
/** Maximum length of TLV5C element */
# define ecy_hsm_CSAI_MDK_TLV5C_MAX_LEN                   16U
/** Offset of TLV5C in the channel creation parameters for the ecy_hsm_Csai_MDK_CreateSecureChannelFast() interface */
# define ecy_hsm_CSAI_MDK_CHANNEL_CREATION_TLV5C_OFFSET   107U
/** Minimal length of the channel creation parameters for the ecy_hsm_Csai_MDK_CreateSecureChannelFast() interface */
# define ecy_hsm_CSAI_MDK_CHANNEL_CREATION_PARAMS_MIN_LEN (ecy_hsm_CSAI_MDK_CHANNEL_CREATION_TLV5C_OFFSET + ecy_hsm_CSAI_MDK_TLV5C_MIN_LEN)
/** Maximal length of the channel creation parameters for the ecy_hsm_Csai_MDK_CreateSecureChannelFast() interface */
# define ecy_hsm_CSAI_MDK_CHANNEL_CREATION_PARAMS_MAX_LEN (ecy_hsm_CSAI_MDK_CHANNEL_CREATION_TLV5C_OFFSET + ecy_hsm_CSAI_MDK_TLV5C_MAX_LEN)
/** Offset of TLV5C in KDF info parameters, for interfaces ecy_hsm_Csai_MDK_CreateSecureChannelStandard() and ecy_hsm_Csai_MDK_CreateUrsk() */
# define ecy_hsm_CSAI_MDK_CHANNEL_KDF_TLV5C_OFFSET        116U
/** Minimal length of KDF info parameters for the ecy_hsm_Csai_MDK_CreateSecureChannelStandard() and ecy_hsm_Csai_MDK_CreateUrsk() interface */
# define ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MIN_LEN       (ecy_hsm_CSAI_MDK_CHANNEL_KDF_TLV5C_OFFSET + ecy_hsm_CSAI_MDK_TLV5C_MIN_LEN)
/** Maximal length of KDF info parameters for the ecy_hsm_Csai_MDK_CreateSecureChannelStandard() and ecy_hsm_Csai_MDK_CreateUrsk() interface */
# define ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MAX_LEN       (ecy_hsm_CSAI_MDK_CHANNEL_KDF_TLV5C_OFFSET + ecy_hsm_CSAI_MDK_TLV5C_MAX_LEN)
/** Length of the verification result flag */
# define ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN           1U
/** Maximal length of the entitlement field */
# define ecy_hsm_CSAI_MDK_ENTITLEMENTS_MAX_LEN            158U
/** Minimal length of the attestation package for the @ref ecy_hsm_Csai_MDK_VerifyAttestationPackage() interface */
# define ecy_hsm_CSAI_MDK_ATTESTATION_PACKAGE_MIN_LEN     92U
/** Maximal length of the attestation package for the @ref ecy_hsm_Csai_MDK_VerifyAttestationPackage() interface */
# define ecy_hsm_CSAI_MDK_ATTESTATION_PACKAGE_MAX_LEN     (ecy_hsm_CSAI_MDK_ATTESTATION_PACKAGE_MIN_LEN + ecy_hsm_CSAI_MDK_ENTITLEMENTS_MAX_LEN)
/** Length of input data for the ecy_hsm_Csai_MDK_VerifyEndpointSignature() interface */
# define ecy_hsm_CSAI_MDK_ENDPOINT_DATA_AND_SIG_MIN_LEN   (ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN + ecy_hsm_CSAI_MDK_SIGNATURE_LEN + 1U)
/** Length of the signed authentication data that is verified by the ecy_hsm_Csai_MDK_VerifyEndpointAuthenticationDataSignature() */
# define ecy_hsm_CSAI_MDK_ENDPOINT_AUTH_DATA_LEN          102U
/** Length of input data for the ecy_hsm_Csai_MDK_VerifyEndpointAuthenticationDataSignature() interface  */
# define ecy_hsm_CSAI_MDK_ENDPOINT_AUTH_DATA_AND_SIG_LEN                                                                                             \
        (ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN + ecy_hsm_CSAI_MDK_ENDPOINT_AUTH_DATA_LEN + ecy_hsm_CSAI_MDK_SIGNATURE_LEN)
/** Length of context used for key derivation */
# define ecy_hsm_CSAI_MDK_CONTEXT_LEN                11U
/** Length of the immobilizer token indicator */
# define ecy_hsm_CSAI_MDK_IMMOTOKEN_INDICATOR_LEN    1U
/** Immotoken indicator value foa a generic RAPDU */
# define ecy_hsm_CSAI_MDK_TOKEN_INDICATOR_RAPDU      0U
/** Immotoken indicator value for a RAPDU containing an immobilizer token */
# define ecy_hsm_CSAI_MDK_TOKEN_INDICATOR_IMMOTOKEN  1U
/** Minimal RAPDU length for the @ref ecy_hsm_Csai_MDK_DecryptResponse interface */
# define ecy_hsm_CSAI_MDK_DECRYPT_RAPDU_MIN_LEN      (ecy_hsm_CSAI_MDK_IMMOTOKEN_INDICATOR_LEN + AES_BLOCK_SIZE_BYTES)
/** Maximal RAPDU length for the @ref ecy_hsm_Csai_MDK_DecryptResponse interface */
# define ecy_hsm_CSAI_MDK_DECRYPT_RAPDU_MAX_LEN      257U
/** Length of verifier parameter w0 */
# define ecy_hsm_CSAI_MDK_OWNER_PAIRING_W0_LEN       32U
/** Length of the complete verifier parameters w0 || L to be set by the ecy_hsm_Csai_MDK_SetOwnerPairingVerifier() */
# define ecy_hsm_CSAI_MDK_OWNER_PAIRING_VERIFIER_LEN (ecy_hsm_CSAI_MDK_OWNER_PAIRING_W0_LEN + ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN)
/** Length of the evidence tag M1 */
# define ecy_hsm_CSAI_MDK_M1_LEN                     16U
/** Maximum length of input to @ref ecy_hsm_Csai_MDK_CreateKBleOob interface */
# define ecy_hsm_Csai_MDK_PADDED_SLOT_IDS_MAX_LEN    128U
/** Length of header data in the @ref ecy_hsm_Csai_MDK_SetOemCertificate interface */
# define ecy_hsm_Csai_MDK_HEADER_LEN                 52U
/** Maximal certificate length */
# define ecy_hsm_CSAI_MDK_MAX_CERTIFICATE_LEN        650U
/** Length of the TLV header for certificates */
# define ecy_hsm_CSAI_MDK_TLV_CERT_HEADER_LEN        5U
/** Length of the TLV header for a MAC */
# define ecy_hsm_CSAI_MDK_TLV_MAC_HEADER_LEN         2U
/** Minimal data length for the @ref ecy_hsm_Csai_MDK_SetOemCertificate interface */
# define ecy_hsm_CSAI_MDK_SET_OEM_CERT_MIN_LEN                                                                                                       \
        (ecy_hsm_CSAI_MDK_CONTEXT_LEN + ecy_hsm_Csai_MDK_HEADER_LEN + ecy_hsm_CSAI_MDK_TLV_CERT_HEADER_LEN + ecy_hsm_CSAI_MDK_TLV_MAC_HEADER_LEN     \
         + ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN)
/** Maximal data length for the @ref ecy_hsm_Csai_MDK_SetOemCertificate interface */
# define ecy_hsm_CSAI_MDK_SET_OEM_CERT_MAX_LEN                                                                                                       \
        (ecy_hsm_CSAI_MDK_CONTEXT_LEN + ecy_hsm_Csai_MDK_HEADER_LEN + ecy_hsm_CSAI_MDK_TLV_CERT_HEADER_LEN + ecy_hsm_CSAI_MDK_MAX_CERTIFICATE_LEN    \
         + ecy_hsm_CSAI_MDK_TLV_MAC_HEADER_LEN + ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN)
/** Number of certificates in an creation attestation chain */
# define ecy_hsm_CSAI_MDK_NUM_CERTS_IN_CHAIN 3U
/** Maximal length of a creation attestation chain */
# define ecy_hsm_CSAI_MDK_ATTESTATION_CHAIN_MAX_LEN                                                                                                  \
        (ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN                                                                                                            \
         + (ecy_hsm_CSAI_MDK_NUM_CERTS_IN_CHAIN * (ecy_hsm_CSAI_MDK_MAX_CERTIFICATE_LEN + ecy_hsm_CSAI_MDK_TLV_CERT_HEADER_LEN)))
/** Length of UWB session ID */
# define ecy_hsm_CSAI_MDK_UWB_SESSIONID_LEN           4U
/** Length of URSK */
# define ecy_hsm_CSAI_MDK_URSK_KEY_LEN                32U
/** Minimal length of WFS TAG1 */
# define ecy_hsm_CSAI_MDK_TAG1_MIN_LEN                25U
/** Length of WFS TAG2 */
# define ecy_hsm_CSAI_MDK_TAG2_LENGTH                 32U
/** Length of padded MDK slot ID */
# define ecy_hsm_CSAI_MDK_OFK_PADDED_SLOTID_LEN       8U
/** Length of generated BLE keys in bytes */
# define ecy_hsm_CSAI_MDK_BLE_KEY_LEN                 ((uint32)ecy_hsm_CSAI_KEYSIZE_128 / BITS_PER_BYTE)
/** Maximal length of an RAPDU when verifying response authentication */
# define ecy_hsm_CSAI_MDK_AUTH_RAPDU_MAX_LEN          242U
/** Maximal length of a CAPDU when generating command authentication */
# define ecy_hsm_CSAI_MDK_AUTH_CAPDU_MAX_LEN          245U
/** Maximal length of data to be signed by @ref ecy_hsm_Csai_MDK_VerifyKeyManagementCmac and @ref ecy_hsm_Csai_MDK_GenerateKeyManagementCmac */
# define ecy_hsm_CSAI_MDK_DATA_TO_BE_SIGNED_MAX_LEN   725U
/** Maximal length of key authentication data */
# define ecy_hsm_CSAI_MDK_KEY_MANAGEMENT_DATA_MAX_LEN (ecy_hsm_CSAI_MDK_CONTEXT_LEN + ecy_hsm_CSAI_MDK_DATA_TO_BE_SIGNED_MAX_LEN)
/** Length of the vehicle authentication data that is signed by @ref ecy_hsm_Csai_MDK_SignVehicleAuthenticationData */
# define ecy_hsm_CSAI_MDK_VEHICLE_AUTH_DATA_LEN       250U
/** Length of the string "ConfirmationKeys" */
# define ecy_hsm_CSAI_MDK_CONF_KEYS_STR_LEN           16U
/** Minimal length of additional authentication data */
# define ecy_hsm_CSAI_MDK_AAD_MIN_LEN                 8U
/** Minimal length of authentication data to be used for K1 and K2 derivation */
# define ecy_hsm_CSAI_MDK_OVERALL_AUTH_DATA_MIN_LEN   (ecy_hsm_CSAI_MDK_CONF_KEYS_STR_LEN + ecy_hsm_CSAI_MDK_AAD_MIN_LEN)
/** Flag value indicating success */
# define ecy_hsm_CSAI_MDK_FLAG_OK                     0x00U
/** Flag value indicating failure */
# define ecy_hsm_CSAI_MDK_FLAG_NOT_OK                 0x01U
/** Flag value indicating that the specified MDK slot was not found */
# define ecy_hsm_CSAI_MDK_FLAG_SLOT_ID_NOT_FOUND      0x02U
/** Length of three SC keys */
# define ecy_hsm_CSAI_MDK_SC_KEY_LENGTH               48U

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
# ifdef __cplusplus
extern "C" {
# endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
# define ECY_HSM_START_SEC_CODE
# include "ecy_hsm_MemMap.h"

/**
 * [$DD 1479]
 * @brief
 * This function initializes MDK.
 *
 * @details
 * This function initializes data structures related to MDK. It must be called prior to any other MDK function.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                 The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE      The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM       A parameter was invalid.
 *  - Others                                    HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_Init(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1553]
 * @brief
 * This function sets the OEM certificate.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function stores the OEM Root CA certificate in the certificate store.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM.
 * @param[in]       pCert               A buffer containing the DER-encoded X.509 OEM Root CA certificate.
 * @param[in]       certLength          The length of pCert. Must be >= @ref ecy_hsm_CSAI_MDK_SET_OEM_CERT_MIN_LEN and
 *                                      <= @ref ecy_hsm_CSAI_MDK_SET_OEM_CERT_MAX_LEN. The included certificate can have
 *                                      a maximum length of @ref ecy_hsm_CSAI_MDK_MAX_CERTIFICATE_LEN.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                             The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                             The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE                  The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                   Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED             MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_CERT_VERIFICATION_FAILED    The verification of the MAC over the certificate failed.
 *  - Others                                                HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SetOemCertificate(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                               ecy_hsm_Csai_JobPriorityT   priority,
                                                                                               const uint8*                pCert,
                                                                                               uint32                      certLength,
                                                                                               ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1486]
 * @brief This function suspends MDK.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function writes all keys of the ephemeral key ring buffer to NVM. It must be invoked, and its execution must have been completed, before the
 * HSM core is powered down.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_Suspend(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1524]
 * @brief
 * Generates a Cipher-based Message Authentication Code (CMAC) for a command Application Protocol Data Unit (APDU/CAPDU) in an APDU exchange that
 * conforms to the Secure Channel Protocol 03 (SCP03) specification. CMAC chaining is managed by the CycurHSM MDK Implementation.
 * An active secure channel must be established beforehand. The MAC is calculated using the MAC key derived for the secure channel communication.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession     Handle to the session in which the job is placed.
 * @param[in]       priority     Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pCapdu       Pointer to array in host RAM containing the data that should be covered by the CMAC.
 * @param[in]       capduLength  Length of the data in pCapdu, may be 0. Must be <= @ref ecy_hsm_CSAI_MDK_AUTH_CAPDU_MAX_LEN.
 * @param[out]      pCmac        Pointer to array in host RAM where the calculated, truncated CMAC will be stored.
 * @param[in,out]   pCmacLength  Pointer to the length of pCmac (must be >= @ref ecy_hsm_CSAI_MDK_SCP03_CMAC_LEN). Returns the number of bytes written
 *                               to pCmac.
 * @param[out]      phJob        Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           SCP03 session is inactive.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GenerateCommandAuthentication(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                           const uint8*                pCapdu,
                                                                                                           uint32                      capduLength,
                                                                                                           uint8*                      pCmac,
                                                                                                           uint32*                     pCmacLength,
                                                                                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1480]
 * @brief
 * This function returns a public ephemeral key and creates new ephemeral key pairs.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * The function releases the last used ephemeral key from RAM and triggers a generation of new keys in the background. It then reads out the next
 * public key from the key ring buffer and returns it to the caller.
 *
 * @param[in]       hSession                Handle to the session in which the job is placed.
 * @param[in]       priority                Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[out]      pEphemeralPuK           Pointer to public key array. Returned public key has the format 0x04 || VehicleEPK (65 bytes).
 * @param[in,out]   pEphemeralPuKLength     Pointer to the size of ephemeralPuK (must be >= @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN). Returns the
 *                                          number of bytes written to ephemeralPuK.
 * @param[out]      phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NO_VALID_KEYS       There are no ephemeral keys left in the ring buffer.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateEphemeralKeyPair(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                    ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                    uint8*                      pEphemeralPuK,
                                                                                                    uint32*                     pEphemeralPuKLength,
                                                                                                    ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1477]
 * @brief
 * This function generates the ECDSA key pair of the vehicle and stores it in a dedicated key slot of CycurHSM.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function generates the ECDSA key pair of the vehicle, stores it in the HSM and returns the public key to the caller.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession              Handle to the session in which the job is placed.
 * @param[in]       priority              Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[out]      pVehiclePubKey        Pointer to array in HOST RAM where the generated public key will be returned. Returned public key has the
 *                                        format 0x04 || VehiclePK (65 bytes).
 * @param[in,out]   pVehiclePubKeyLength  Pointer to the size of VehiclePubKey (must be >= @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN). Returns the
 *                                        number of bytes written to VehiclePubKey.
 * @param[out]      phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateLongTermKeyPair(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                   uint8*                      pVehiclePubKey,
                                                                                                   uint32*                     pVehiclePubKeyLength,
                                                                                                   ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1526]
 * @brief
 * This function is used during establishment of a secure channel using the fast protocol.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function is used during establishment of a secure channel using the Elliptic Curve Key Agreement protocol in Diffie-Hellman mode when a
 * symmetric key for a Fast Transaction is available.
 *
 * @param[in]       hSession                        Handle to the session in which the job is placed.
 * @param[in]       priority                        Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pChannelCreationParams          Pointer to array in host RAM holding the "channel creation" parameters, which are used to locate
 *                                                  the MDK slot containing the required symmetric key to establish a secure connection.
 *                                                  Format: VehicleEPK.x (32 bytes) || EndpointEPK.x (32 bytes) || TransactionIdentifier (16 bytes) ||
 * Interface byte (1 byte) || Flag (2 bytes) || ReaderIdentifier (8 bytes) || Cryptogram (16 bytes) || TLV 5C (4 bytes)
 * @param[in]       channelCreationParamsLength     Length of @p channelCreationParams (must be >=
 *                                                  @ref ecy_hsm_CSAI_MDK_CHANNEL_CREATION_PARAMS_MIN_LEN).
 * @param[out]      pSlotId                         Pointer to a buffer which, on success, will hold the ID of the MDK slot containing the required
 *                                                  symmetric key. The first byte of this buffer will be equal to @ref ecy_hsm_CSAI_MDK_FLAG_OK if the
 *                                                  key is found, and @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK otherwise.
 * @param[in,out]   pSlotIdLength                   Pointer to a uint32. When the function is called, the value should be the length of the @p pSlotId
 *                                                  buffer (at least @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN +
 *                                                  @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN bytes). On return, the value will be the number of bytes
 *                                                  written to pSlotId.
 * @param[out]      phJob                           Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           Session slotId is not valid.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_ALREADY_OPEN    There is already an active secure channel.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelFast(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8* pChannelCreationParams,
                                                                                                     uint32       channelCreationParamsLength,
                                                                                                     uint8*       pSlotId,
                                                                                                     uint32*      pSlotIdLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1499]
 * @brief
 * This function generates an ECDSA signature using the private key of the key pair of the vehicle.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function generates an ECDSA signature over provided authentication data using the private key of the key pair of the vehicle. It is invoked
 * during the Owner Pairing procedure.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession              Handle to the session in which the job is placed.
 * @param[in]       priority              Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pDataToBeSigned       Pointer to array in host RAM where data to be signed has been stored.
 * @param[in]       dataToBeSignedLength  Length of data to be signed (must >= 1 and <= @ref ecy_hsm_CSAI_MDK_VEHICLE_AUTH_DATA_LEN).
 * @param[out]      pSignature            Pointer to array in host RAM where the signature will be stored.
 * @param[in,out]   pSignatureLength      Pointer to length of memory area reserved for signature in bytes, must be >=
 *                                        @ref ecy_hsm_CSAI_MDK_PUBKEY_LEN. On successful return contains the number of bytes written to the signature
 *                                        buffer.
 * @param[out]      phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SignVehicleAuthenticationData(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                           const uint8* pDataToBeSigned,
                                                                                                           uint32       dataToBeSignedLength,
                                                                                                           uint8*       pSignature,
                                                                                                           uint32*      pSignatureLength,
                                                                                                           ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1527]
 * @brief
 * This function validates the signature of an attestation package.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function validates the signature of an Attestation package using the owner public key, extracts the public key of the mobile device and stores
 * it in an MDK key slot if the verification succeeds. This function may either be called "standalone" if the Friend device is paired while the
 * vehicle is online, or as part of the Standard Transaction control flow.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pAttestationPackage         Pointer to array in host RAM where the attestation package data is stored.
 *                                              Format: SlotID (4 bytes) || TLV 41: certificate_version (2 + 1 bytes) || TLV 92: random (2 + 8 bytes)
 *                                                      || TLV 5A: EndpointPK (2 + 65 bytes) || TLV 58: entitlements (var., max. 2 + 102 bytes)
 *                                                      || TLV 93: usage (2 + 4 bytes)
 * @param[in]       attestationPackageLength    Length of the attestation package. Must be >= @ref ecy_hsm_CSAI_MDK_ATTESTATION_PACKAGE_MIN_LEN and <=
 *                                              @ref ecy_hsm_CSAI_MDK_ATTESTATION_PACKAGE_MAX_LEN.
 * @param[in]       pSignature                  Pointer to array in host RAM memory where the signature is stored.
 * @param[in]       signatureLength             Length of the signature, must be equal to @ref ecy_hsm_CSAI_MDK_PUBKEY_LEN.
 * @param[out]      pVerificationResult         Pointer to variable in host RAM where the result of the signature verification will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successful, @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK
 *                                              otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           No owner key available.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NO_EMPTY_SLOT       There is no empty MDK slot left.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyAttestationPackage(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                      ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                      const uint8*                pAttestationPackage,
                                                                                                      uint32       attestationPackageLength,
                                                                                                      const uint8* pSignature,
                                                                                                      uint32       signatureLength,
                                                                                                      uint8*       pVerificationResult,
                                                                                                      ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1484]
 * @brief
 * This function is used during establishment of a secure channel.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function is used during establishment of a secure channel using the Elliptic Curve Key Agreement protocol in Diffie-Hellman mode if no
 * symmetric key for a Fast Transaction is available.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                Handle to the session in which the job is placed.
 * @param[in]       priority                Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pKdfInfoParam           Pointer to array in host RAM where the "info" parameters for deriving the symmetric secrets have been
 *                                          stored.
 *                                          Format: VehicleEPK.x (32 bytes) || EndpointEPK (65 bytes) || TransactionIdentifier (16 bytes) || Interface
 * byte (1 byte) || Flag (2 bytes) || TLV 5C (2-16 bytes)
 * @param[in]       kdfInfoParamLength      Length of kdfInfoParam (must be >= @ref ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MIN_LEN and <=
 *                                          @ref ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MAX_LEN).
 * @param[out]      phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_ALREADY_OPEN    There is already an active secure channel.
 *  - Others                                        HSM internal errors.
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelStandard(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                         const uint8*                pKdfInfoParam,
                                                                                                         uint32                   kdfInfoParamLength,
                                                                                                         ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1567]
 * @brief
 * This function calculates the URSK key for a given session.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * Calculate the URSK and store it in the mdkContext.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pPartnerPublicValue         Pointer to array in host RAM where the "info" parameters for deriving the symmetric secrets have been
 *                                              stored. This has a fixed format based on the MDK specifications.
 *                                              Format: VehicleEPK.x (32 bytes) || EndpointEPK (65 bytes) || TransactionIdentifier (16 bytes) ||
 * Interface byte (1 Byte) || Flag (2 bytes) || Tag 5C (4 bytes)
 * @param[in]       partnerPublicValueLength    Length of partnerPublicValue. The length is constrained by the fixed format of pPartnerPublicValue.
 *                                              Only the last field of pPartnerPublicValue, tlv5c, has variable length. Therefore,
 *                                              partnerPublicValueLength must be >= @ref ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MIN_LEN and <=
 *                                              @ref ecy_hsm_CSAI_MDK_CHANNEL_KDF_PARAM_MAX_LEN.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      The call succeeded. The job has been queued on the HSM.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            The provided status pointer or the job pointer is NULL.
 * - @ref ecy_hsm_CSAI_FC_BUSY                      Another job is still pending completion in this session. Either finish the previous job or cancel
 *                                                  the running job using @ref ecy_hsm_Csai_CancelJob.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The parameter is not a valid session handle or the used handle has the wrong type.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 * - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED      MDK applet was not initialized before.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_STATE            SCP03 session is inactive.
 * - Others                                         HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateUrsk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                                                        const uint8*                pPartnerPublicValue,
                                                                                        uint32                      partnerPublicValueLength,
                                                                                        ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1538]
 * @brief
 * This function is used for closing an established secure channel.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @param[in]       hSession              Handle to the session in which the job is placed.
 * @param[in]       priority              Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[out]      phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           A secure channel was not active before.
 *  - Others                                        HSM internal errors.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CloseSecureChannel(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1546]
 * @brief
 * This function validates a signature over arbitrary data using the public key of the indicated key slot.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function validates a signature over arbitrary data using the public key of the indicated key slot. It is called at the end of the Standard
 * Transaction control flow. On successful verification the symmetric key for fast transaction (calculated in
 * @ref ecy_hsm_Csai_MDK_CreateSecureChannelStandard) will be persisted.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pData                       Pointer to array in host RAM where the slot ID, followed by data and signature to be verified is
 *                                              stored.
 *                                              Format: SlotId (4 bytes) || data (102 bytes) || signature (64 bytes)
 * @param[in]       dataLength                  Length of data. Must be equal to @ref ecy_hsm_CSAI_MDK_ENDPOINT_AUTH_DATA_AND_SIG_LEN.
 * @param[out]      pVerificationResult         Pointer to byte in host RAM where the verification result will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successful, @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK or
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_SLOT_ID_NOT_FOUND otherwise.
 * @param[in,out]   pVerificationResultLength   Pointer to length of memory area reserved for the verification result (at least
 *                                              @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN bytes). On successful return contains the number of bytes
 *                                              written to the memory location indicated by pVerificationResult, zero otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                         The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE              The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           SCP03 session is inactive.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_MDK_VerifyEndpointAuthenticationDataSignature(ecy_hsm_Csai_SessionHandleT hSession,
                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                           const uint8*                pData,
                                                           uint32                      dataLength,
                                                           uint8*                      pVerificationResult,
                                                           uint32*                     pVerificationResultLength,
                                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1540]
 * @brief
 * This function validates a CMAC of a response APDU in an APDU exchange that conforms to the SCP03 specification (cf. Secure Channel Protocol '03'
 * v2.2 - Amendment from GlobalPlatform Card Technology Card Specification).
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * CMAC chaining is managed by the CycurHSM MDK implementation. The incoming RAPDU gets verified according to the following scheme:
 *
 * @verbatim
 *                +-------------------------------+----------+
 *                |      MAC chaining value       |  RAPDU   |
 *                | (stored in HSM's global RAM)  |          |
 *                +-------------------+-----------+----------+
 *                                    |
 *                                    v
 *                           +--------+--------+
 *       Key S-RMAC +----->  | calculate CMAC  |
 *                           +--+--------------+
 *                              |
 *                              |
 *                              v
 *         +--------------------+--+      +-----------------+
 *         | First 8 bytes of CMAC |  ==  | expected value  |  ?
 *         +-----------------------+      +-----------------+
 *                                     +
 *                                     |
 *                                     v
 *                      then:       result = 0 (success);
 *                      otherwise:  result = 1 (failure);
 * @endverbatim
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                Handle to the session in which the job is placed.
 * @param[in]       priority                Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pRapdu                  Pointer to array in host RAM containing the data whose CMAC should be validated.
 * @param[in]       rapduLength             Length of memory area reserved for the RAPDU (in bytes), must be <=
 *                                          @ref ecy_hsm_CSAI_MDK_AUTH_RAPDU_MAX_LEN.
 * @param[in]       pReferenceCmac          Pointer to array in host RAM where the reference CMAC to be validated is stored.
 * @param[in]       referenceCmacLength     Length of memory area reserved for the reference CMAC to be validated, in bits. Note that only the first
 *                                          @ref ecy_hsm_CSAI_MDK_SCP03_RMAC_LEN_BITS bits will be taken into account. If the buffer is smaller, an
 *                                          error will be returned.
 * @param[out]      pVerificationResult     Pointer to a memory location where the result of the CMAC comparison will be stored:
 *                                          - @ref ecy_hsm_CSAI_MDK_FLAG_OK : The rapdu is valid
 *                                          - @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK : The rapdu is invalid
 * @param[out]      phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is
 *                                                  out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           SCP03 session is inactive.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyResponseAuthentication(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                          ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                          const uint8*                pRapdu,
                                                                                                          uint32                      rapduLength,
                                                                                                          const uint8*                pReferenceCmac,
                                                                                                          uint32 referenceCmacLength,
                                                                                                          uint8* pVerificationResult,
                                                                                                          ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1541]
 * @brief
 * This function decrypts a response APDU.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function decrypts the data field of a response APDU using a derived session key and manages the encryption counter used in the SCP03 protocol.
 * If the immoToken indicator (first byte referenced by @p pEncryptedRapdu ) is equal to @ref ecy_hsm_CSAI_MDK_TOKEN_INDICATOR_RAPDU, the RAPDU is a
 * generic RAPDU. It gets decrypted and the result is copied to @p pDecryptedRapdu . The resulting length is written to @p pDecryptedRapduLength .
 * If the immoToken indicator is equal to @ref ecy_hsm_CSAI_MDK_TOKEN_INDICATOR_IMMOTOKEN, the immoToken gets processed depending on the availability
 * of an immobilizer implementation:
 * - None: The interface can only be used to decrypt APDUs. The immoToken indicator must be set to @ref ecy_hsm_CSAI_MDK_TOKEN_INDICATOR_RAPDU.
 * - WFS6: The RAPDU gets decrypted and the result (encrypted immoToken) is further processed in order to derive SKC1 and the WFS keys. On
 *         successful WFS key derivation, pDecryptedRapdu[0] will be @ref ecy_hsm_CSAI_MDK_FLAG_OK, on failure it will be
 *         @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK. The value references by @p pDecryptedRapduLength will be set to
 *         @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN.
 * - WFS5d (WFS SHE emulation): The RAPDU is further processed to derive Skc1*-Ersatzwert and persisted in HSM RAM. pDecryptedRapdu[0] will be
 *                              @ref ecy_hsm_CSAI_MDK_FLAG_OK, on failure it will be @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK. The value references by
 *                              @p pDecryptedRapduLength will be set to @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                Handle to the session in which the job is placed.
 * @param[in]       priority                Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pEncryptedRapdu         Pointer to array in host RAM where the immobilizer token indicator and the RAPDU to be decrypted has been
 *                                          stored.
 * @param[in]       encryptedRapduLength    Length of ImmoToken indicator (@ref ecy_hsm_CSAI_MDK_IMMOTOKEN_INDICATOR_LEN) + length of RAPDU to be
 *                                          decrypted, where length of RAPDU has to be a multiple of the @ref AES_BLOCK_SIZE_BYTES. Furthermore,
 *                                          encryptedRapduLength must be >= @ref ecy_hsm_CSAI_MDK_DECRYPT_RAPDU_MIN_LEN and <=
 *                                          @ref ecy_hsm_CSAI_MDK_DECRYPT_RAPDU_MAX_LEN.
 * @param[out]      pDecryptedRapdu         Pointer to array in host RAM where the decrypted RAPDU or key derivation result will be stored.
 * @param[in,out]   pDecryptedRapduLength   Pointer to length of memory area reserved for the decrypted RAPDU in bytes, must initially >=
 *                                          @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN. On successful return contains the number of bytes written to
 *                                          the decrypted RAPDU buffer, zero otherwise.
 * @param[out]      phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                             The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                             The HSM is still busy and the result is not available yet.
 *                                                          Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE                  The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED             MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE                   SCP03 session is inactive.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                   Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *                                                          Byte at memory location pointed to by parameter pEncryptedRapdu (immoToken indicator) is
 *                                                          invalid (neither 0x00 nor 0x01).
 *  - @ref ecy_hsm_CSAI_MDK_ERR_GENERAL                     Internal error while processing the RAPDU.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_WFS_KEYS_ALREADY_DERIVED    WFS keys were already derived. Immobilizer token not processed.
 *  - Others                                                HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DecryptResponse(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                             const uint8*                pEncryptedRapdu,
                                                                                             uint32                      encryptedRapduLength,
                                                                                             uint8*                      pDecryptedRapdu,
                                                                                             uint32*                     pDecryptedRapduLength,
                                                                                             ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1542]
 * @brief
 * This function encrypts a command APDU.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function encrypts the data field of a command APDU using a derived session key and manages the encryption counter used in the SCP03 protocol.
 * Padding according to ISO 7816-4 is appended before encryption.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pPlainCapdu         Pointer to array in host RAM where the APDU to be encrypted has been stored.
 * @param[in]       plainCapduLength    Length of APDU to be encrypted. Must be > 0 and <= @ref ecy_hsm_CSAI_MDK_ENCRYPT_CAPDU_MAX_LEN.
 * @param[out]      pEncCapdu           Pointer to array in host RAM where the encrypted APDU will be stored.
 * @param[in,out]   pEncCapduLength     Pointer to length of memory area reserved for the encrypted APDU in bytes. On successful return contains the
 *                                      number of bytes written to the encrypted APDU buffer, zero otherwise. Note that the value of this parameter at
 *                                      start must >= plainCapduLength and provide sufficient memory to append the ISO 7816-4 padding (up to
 *                                      @ref AES_BLOCK_SIZE_BYTES additional bytes).
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL        Buffer too small for padding.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           No SCP03 session active.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_EncryptCommand(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                            ecy_hsm_Csai_JobPriorityT   priority,
                                                                                            const uint8*                pPlainCapdu,
                                                                                            uint32                      plainCapduLength,
                                                                                            uint8*                      pEncCapdu,
                                                                                            uint32*                     pEncCapduLength,
                                                                                            ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1560]
 * @brief
 * This function verifies the endpoint signature.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function verifies a signature generated by an endpoint, over a message of length 81 bytes.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pData                       Pointer to array in host RAM where the data including the signature is stored.
 *                                              Format: SlotId (4 bytes) || data (variable length) || signature (64 bytes)
 * @param[in]       dataLength                  Length of data including the signature (must be >=
 *                                              @ref ecy_hsm_CSAI_MDK_ENDPOINT_DATA_AND_SIG_MIN_LEN).
 * @param[out]      pVerificationResult         Pointer to array in host RAM where the verification result will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_SLOT_ID_NOT_FOUND if the slotId was not found,
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successful,
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK otherwise.
 * @param[in,out]   pVerificationResultLength   Pointer to length of memory area reserved for the verification result. On successful return contains
 *                                              the number of bytes written to the memory location indicated by pVerificationResult, zero otherwise
 *                                              (must be >= @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN).
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_INVALID_KEY_SLOT    Invalid MDK key slot.
 *  - Others                                        HSM internal errors.
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifyEndpointSignature(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8*                pData,
                                                                                                     uint32                      dataLength,
                                                                                                     uint8*                      pVerificationResult,
                                                                                                     uint32* pVerificationResultLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1548]
 * @brief
 * This function stores owner pairing verifier parameters.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function stores the data needed to execute the Owner Pairing protocol in HSM D-Flash.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pOwnerPairingVerifier       Pointer to array in host RAM where the concatenated owner pairing verifier parameters w0 (
 *                                              @ref ecy_hsm_CSAI_MDK_OWNER_PAIRING_W0_LEN bytes) and L ( @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN
 *                                              bytes) are stored.
 *                                              Format: w0 (32 bytes) || L (65 bytes)
 * @param[in]       ownerPairingVerifierLength  Length of the owner pairing verifier parameters. Must be equal to
 *                                              @ref ecy_hsm_CSAI_MDK_OWNER_PAIRING_VERIFIER_LEN.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_SetOwnerPairingVerifier(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8* pOwnerPairingVerifier,
                                                                                                     uint32       ownerPairingVerifierLength,
                                                                                                     ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1562]
 * @brief   This function creates the BLE OOB keys.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function creates BLE OOB keys and returns them concatenated with the BLE intro key.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                Handle to the session in which the job is placed.
 * @param[in]       priority                Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pPaddedSlotIds          Pointer to array in host RAM where the padded slot IDs are stored. If NULL_PTR is passed, only the BLE
 *                                          intro key will be returned.
 *                                          Format: N * SlotId (padded to 8 bytes, N * 8 bytes)
 * @param[in]       paddedSlotIdsLength     Length of padded slot IDs. Must be 0 if pPaddedSlotIds == NULL_PTR. Otherwise must be <=
 *                                          @ref ecy_hsm_Csai_MDK_PADDED_SLOT_IDS_MAX_LEN and must be a multiple of
 *                                          @ref ecy_hsm_CSAI_MDK_OFK_PADDED_SLOTID_LEN.
 * @param[out]      pKBleOob                Pointer to array in host RAM where the BLE OOB and BLE intro keys will be stored.
 * @param[in,out]   pKBleOobLength          Pointer to length of memory area reserved for the BLE OOB and BLE intro keys. Must be at least
 *                                          @ref ecy_hsm_CSAI_MDK_BLE_KEY_LEN + (requested number of keys * @ref ecy_hsm_CSAI_MDK_BLE_KEY_LEN. On
 *                                          successful return contains the actual number of bytes written to the memory location referenced by
 *                                          pKBleOob.
 * @param[out]      phJob                   Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateKBleOob(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                           ecy_hsm_Csai_JobPriorityT   priority,
                                                                                           const uint8*                pPaddedSlotIds,
                                                                                           uint32                      paddedSlotIdsLength,
                                                                                           uint8*                      pKBleOob,
                                                                                           uint32*                     pKBleOobLength,
                                                                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1565]
 * @brief
 * This function returns the UWB (Ultra-wide-band) Ranging Secret Key (URSK).
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function returns the URSK that belongs to a given MDK slot id and UWB session. If only a slot ID is passed, the corrsponding URSK is deleted
 * (set to zero).
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM.
 * @param[in]       pSlotIdAndSessionId         Pointer to array in host RAM where the ID of the slot in which the UWB session ID should be searched,
 *                                              and optionally the UWB session ID to search, is stored.
 *                                              Format: SlotId (4 bytes) || UWB session ID (4 bytes, optional)
 * @param[in]       slotIdAndSessionIdLength    Length of MDK slot ID + UWB session ID. Must be equal to @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN or
 *                                              @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN + @ref ecy_hsm_CSAI_MDK_UWB_SESSIONID_LEN.
 * @param[out]      pUrsk                       Pointer to array in host RAM where the URSK will be stored.
 * @param[in,out]   pUrskLength                 Length of URSK, must be >= @ref ecy_hsm_CSAI_MDK_URSK_KEY_LEN. On successful return contains the
 *                                              actual number of bytes written to the memory location referenced by pUrsk.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GetUrsk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                     const uint8*                pSlotIdAndSessionId,
                                                                                     uint32                      slotIdAndSessionIdLength,
                                                                                     uint8*                      pUrsk,
                                                                                     uint32*                     pUrskLength,
                                                                                     ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1571]
 * @brief
 * This function returns the public key stored in an MDK key slot.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function returns the public key stored in an MDK key slot identified by a MDK slot ID.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pSlotId                     Pointer to slot ID of the MDK slot to read the public key from.
 * @param[in]       slotIdLength                Length of the slot ID in bytes. Must be equal to @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN.
 * @param[out]      pFriendPk                   Pointer to array in host RAM where the public key will be stored.
 * @param[in,out]   pFriendPkLength             Pointer to length of memory area reserved for the public key, must initially be >=
 *                                              @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN. On successful return contains the number of bytes written to
 *                                              the memory location indicated by pFriendPk and zero otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_GetFriendPk(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                         const uint8*                pSlotId,
                                                                                         uint32                      slotIdLength,
                                                                                         uint8*                      pFriendPk,
                                                                                         uint32*                     pFriendPkLength,
                                                                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1569]
 * @brief
 * This function calculates the first part of the SPAKE2+ protocol.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function calculates the symmetric secrets K1 and K2, as well as the verification value M[1] for the SPAKE2+ protocol.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @note
 * This function must only be called with priority @ref ecy_hsm_CSAI_PRIO_BACKGROUND or @ref ecy_hsm_CSAI_PRIO_LOW .
 *
 * @param[in]       hSession              Handle to the session in which the job is placed.
 * @param[in]       priority              Requested scheduling priority for this job on the HSM.
 * @param[in]       pData                 Pointer to array in host RAM where a concatenation of the curve point of the mobile device in uncompressed
 *                                        format ( @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN bytes) and the input for the HKDF (at least
 *                                        @ref ecy_hsm_CSAI_MDK_OVERALL_AUTH_DATA_MIN_LEN) are stored.
 *                                        Format: (0x04 || curve point (1 + 64 bytes) || "ConfirmationKeys" (ASCII, 16 bytes) || TLV 5B (4 bytes) ||
 * TLV 5C (4 bytes)).
 * @param[in]       dataLength            Length of data, must be >= ( @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN +
 *                                        @ref ecy_hsm_CSAI_MDK_OVERALL_AUTH_DATA_MIN_LEN).
 * @param[out]      pResult               Pointer to array in host RAM where the concatenation of the curve point of the vehicle in uncompressed
 *                                        format (exactly @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN bytes) and the verification tag M1
 *                                        ( @ref ecy_hsm_CSAI_MDK_M1_LEN) will be stored.
 * @param[in,out]   pResultLength         Pointer to length of memory area reserved for the result, must initially be >=
 *                                        ( @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN + @ref ecy_hsm_CSAI_MDK_OVERALL_AUTH_DATA_MIN_LEN bytes). On
 *                                        successful return contains the number of bytes written to the result buffer, zero otherwise.
 * @param[out]      phJob                 Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_GENERAL             General MDK error.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CalculateSecretOwnerPairing(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                         ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                         const uint8*                pData,
                                                                                                         uint32                      dataLength,
                                                                                                         uint8*                      pResult,
                                                                                                         uint32*                     pResultLength,
                                                                                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1578]
 * @brief
 * This function concludes the SPAKE2+ key exchange.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function concludes the SPAKE2+ key exchange by validating the M[2] message, and creates a secure channel as part of the owner pairing process.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM. @ref ecy_hsm_CSAI_PRIO_HIGH is not allowed.
 * @param[in]       pY                          Pointer to array in host RAM where the Y curve point in uncompressed encoding is stored. This variable
 *                                              has been calculated by the mobile device as part of the owner pairing protocol.
 * @param[in]       yLength                     Length of curve point Y, must be equal to @ref ecy_hsm_CSAI_MDK_ENCODED_PUBKEY_LEN.
 * @param[in]       pReferenceMac               Pointer to array in host RAM memory where the MAC calculated by the mobile device over coordinate Y is
 *                                              stored.
 * @param[in]       referenceMacLength          Length of the reference CMAC, in bits. Must be equal to @ref ecy_hsm_CSAI_MDK_CMAC_LEN_BITS.
 * @param[out]      pVerificationResult         Pointer to array in host RAM where the result of the MAC validation will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successful, @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK
 *                                              otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_CreateSecureChannelOwnerPairing(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                             ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                             const uint8*                pY,
                                                                                                             uint32                      yLength,
                                                                                                             const uint8* pReferenceMac,
                                                                                                             uint32       referenceMacLength,
                                                                                                             uint8*       pVerificationResult,
                                                                                                             ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 1581]
 * @brief
 * This function verifies the sharing password.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function verifies the sharing password by re-calculating it from the seed and the long-term shared secret stored in secure data slot
 * MDK_CSAI_ID_DATA_LT_SHARED_SECRET.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM.
 * @param[in]       pSeed                       Pointer to array in host RAM where the seed value to be used during the verification procedure is
 *                                              stored.
 * @param[in]       seedLength                  Length of the seed. Must be > 0 and <= @ref ecy_hsm_CSAI_MDK_SHARING_PASSWORD_SEED_LEN
 * @param[in]       pSharingPassword            Pointer to array in host RAM where the sharing password is stored.
 * @param[in]       sharingPasswordLength       Length of the sharing password. Must be > 0 and <= @ref ecy_hsm_CSAI_MDK_SHARING_PASSWORD_MAX_LEN
 * @param[out]      pVerificationResult         Pointer to array in host RAM where the result of the signature verification will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successfull,  @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK
 *                                              otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                  The call succeeded. The job has been queued on the HSM.
 * - @ref ecy_hsm_CSAI_FC_BUSY                  Another job is still pending completion in this session. Either finish the previous job or cancel the
 *                                              running job using @ref ecy_hsm_Csai_CancelJob.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE       The parameter is not a valid session handle or the used handle has the wrong type.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM        Any of the provided pointers is NULL_PTR or any of the provided lengths is out of bounds.
 * - @ref ecy_hsm_CSAI_MDK_ERR_GENERAL          Error during calculation of the sharing password.
 * - Others                                     HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_VerifySharingPassword(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                   const uint8*                pSeed,
                                                                                                   uint32                      seedLength,
                                                                                                   const uint8*                pSharingPassword,
                                                                                                   uint32                      sharingPasswordLength,
                                                                                                   uint8*                      pVerificationResult,
                                                                                                   ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1545]
 * @brief
 * This function deletes a digital key from the MDK key slots
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function deletes a digital key from the MDK key slots. If the key to be deleted is the owner key, it is marked as invalid instead so it cannot
 * be used for performing a fast transaction or standard transaction.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM.
 * @param[in]       pSlotId             Pointer to array in host RAM where the ID of the slot to be deleted has been stored. Length of slot ID must be
 *                                      equal to @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DeleteDigitalKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                              ecy_hsm_Csai_JobPriorityT   priority,
                                                                                              const uint8*                pSlotId,
                                                                                              ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1550]
 * @brief
 * This function deletes the keys from all MDK key slots as well as persisted symmetric keys and longterm shared secrets.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function indiscriminately deletes the keys from all MDK key slots. In contrast to @ref ecy_hsm_Csai_MDK_DeleteDigitalKey owner keys as well as
 * longterm keys are also deleted. The owner key can hence not be used for @ref ecy_hsm_Csai_MDK_VerifyAttestationPackage anymore.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession            Handle to the session in which the job is placed.
 * @param[in]       priority            Requested scheduling priority for this job on the HSM.
 * @param[out]      phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 *  - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED     MDK applet was not initialized before.
 *  - Others                                        HSM internal errors.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_MDK_DeleteAllDigitalKeys(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                  ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1597]
 * @brief
 * This function terminates the Owner Pairing protocol.
 *
 * [$Satisfies $SW_ARCH  1261]
 *
 * @details
 * This function terminates the Owner Pairing protocol by verifying the chain of X.509 certificates leading from the OEM root CA to the device key
 * creation attestation using the OEM Root CA in HSM D-Flash. On successful validation of the certificate chain, the public key of the Digital Key
 * Certificate is stored as new owner public key.
 *
 * @note
 * The caller must use @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the job handle to query if the HSM has finished this job.
 *
 * @param[in]       hSession                    Handle to the session in which the job is placed.
 * @param[in]       priority                    Requested scheduling priority for this job on the HSM.
 * @param[in]       pAttestationChain           Pointer to array in host RAM where the attestation chain is stored.
 * @param[in]       attestationChainLength      Length of attestation chain. Must be > @ref ecy_hsm_CSAI_MDK_OFK_SLOT_ID_LEN and <=
 *                                              @ref ecy_hsm_CSAI_MDK_ATTESTATION_CHAIN_MAX_LEN.
 *                                              Format: SlotID des Owners (4 bytes) ||
 *                                                      Tag 0x7F20 (2 bytes) || 0x82 + Length (1 + 2 bytes) || Device OEM CA Certificate (max. 650
 * bytes) || Tag 0x7F22 (2 bytes) || 0x82 + Length (1 + 2 bytes) || Instance CA Certificate (max. 650 bytes)   || Tag 0x7F24 (2 bytes) || 0x82 +
 * Length (1 + 2 bytes) || Digital Key Certificate (max. 650 bytes)
 * @param[out]      pVerificationResult         Pointer to byte in host RAM where the verification result will be stored. Will be
 *                                              @ref ecy_hsm_CSAI_MDK_FLAG_OK if verification was successful, @ref ecy_hsm_CSAI_MDK_FLAG_NOT_OK
 *                                              otherwise. Length is equal to @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN.
 * @param[in,out]   pVerificationResultLength   Pointer to length of memory area reserved for the verification result
 *                                              ( @ref ecy_hsm_CSAI_MDK_VERIFICATION_FLAG_LEN bytes). On successful return contains the number of
 *                                              bytes written to the memory location indicated by pVerificationResult, zero otherwise.
 * @param[out]      phJob                       Receives the job handle of the initialized job.
 *
 * @return
 * - @ref ecy_hsm_CSAI_SUCCESS                      The call succeeded. The job has been queued on the HSM.
 * - @ref ecy_hsm_CSAI_FC_BUSY                      Another job is still pending completion in this session. Either finish the previous job or cancel
 *                                                  the running job using @ref ecy_hsm_Csai_CancelJob.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE           The parameter is not a valid session handle or the used handle has the wrong type.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            Error while parsing input data (i.e. input data too short, maximum length restrictions exceeded).
 * - @ref ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED      MDK applet was not initialized before.
 * - @ref ecy_hsm_CSAI_MDK_ERR_NO_EMPTY_SLOT        There is no empty MDK slot left.
 * - Others                                         HSM internal errors.
 */
/* PRQA S 0777 2 */ /* Deviation: rule_5.1_0777 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_MDK_VerifyEndpointCreationAttestationChain(ecy_hsm_Csai_SessionHandleT hSession,
                                                        ecy_hsm_Csai_JobPriorityT   priority,
                                                        const uint8*                pAttestationChain,
                                                        uint32                      attestationChainLength,
                                                        uint8*                      pVerificationResult,
                                                        uint32*                     pVerificationResultLength,
                                                        ecy_hsm_Csai_JobHandleT*    phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
# define ECY_HSM_STOP_SEC_CODE
# include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
# ifdef __cplusplus
} /* extern "C" */
# endif
/* *INDENT-ON* */

#endif /* ECY_HSM_CSAI_DIGITAL_KEY_H */

/**
 * End of Doxygen grouping
 * @}
 * @}
 * @}
 * @endcond
 */
