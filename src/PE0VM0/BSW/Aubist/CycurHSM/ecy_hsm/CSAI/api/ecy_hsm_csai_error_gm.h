/**
 * @file
 ***********************************************************************************************
 * @brief This header file is part of the interface of GM realted functionality.
 * the errors returned from GM interfaces are defined here.
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_ERROR_GM_H
# define ECY_HSM_CSAI_ERROR_GM_H

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_CUST_GM
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_CUST_GM
 * @brief  These error codes are for the GM related interface.
 * @{
 */

/**** Includes *************************************************************/
# include "ecy_hsm_csai_error.h"

/**** C preprocessor definitions *******************************************/

/** These CSAI_GM error codes are used so that GM and CSAI errors can be interleaved. Error codes start at 0xF00 to avoid conflicts with other CSAI_ERROR_CLASS_CUST */
# define ecy_hsm_CSAI_GM_ERROR_MASK                                   (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | 0xF00U)

/** Mac operation flag to indicate HSM shall check MGAL before MAC generation. See @ref ecy_hsm_CSAI_OP_FLAG_MASK */
# define ecy_hsm_CSAI_OP_FLAG_GM_MGAL_RESTRICTED_KEY                  (0x00400000U)

/* ************************** GHSM Error codes ********************************/

/** The ECU ID in the Signed Header does not match the one provided by FSKA */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_ECU_ID                            (ecy_hsm_CSAI_GM_ERROR_MASK | 0x00U)

/** HSM SW update was requested prior to the HSM having its regional root public key provisioned */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_NOT_REGIONALIZED                  (ecy_hsm_CSAI_GM_ERROR_MASK | 0x01U)

/** HSM SW update was requested but the HSM was unable to verify the region info provided by the host */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_INVALID_REGION_INFO               (ecy_hsm_CSAI_GM_ERROR_MASK | 0x02U)

/** The ECU ID Ext. in the Signed Header does not match the one provided by FSKA */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_ECU_ID_EXT                        (ecy_hsm_CSAI_GM_ERROR_MASK | 0x03U)

/** Application software- Not Before Identifier in the Host Signed Header is smaller than the latest one known to the HSM */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_APP_NBID                          (ecy_hsm_CSAI_GM_ERROR_MASK | 0x04U)

/** The CCID in the Calibration Signed Header is not compatible with the host application */
# define ecy_hsm_CSAI_GM_ERR_INVALID_CCID                             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x05U)

/** Indicates App SW or Cal file update failure due to an invalid info in the secure boot info table (SBIT) */
# define ecy_hsm_CSAI_GM_ERR_INVALID_SBIT                             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x06U)

/** Additional Authentication failed. */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_ADD_AUTH_FAILED                   (ecy_hsm_CSAI_GM_ERROR_MASK | 0x07U)

/** Full Message digest verification was requested but there is no pending verified Signed Header */
# define ecy_hsm_CSAI_GM_ERR_UPDATE_INVALID_MESSAGE_DIGEST_REQUEST    (ecy_hsm_CSAI_GM_ERROR_MASK | 0x08U)

/** HSM is unable to process command because it has already initialized the region info. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_REGION_INFO_ALREADY_INITIALIZED     (ecy_hsm_CSAI_GM_ERROR_MASK | 0x09U)

/** HSM is unable to process command because provided data is invalid. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_INVALID_DATA                        (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0AU)

/** MAC1 (over the region info block) fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_MAC1_VERIFY_FAIL                    (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0BU)

/** MAC1 (over the RPuKs) fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_MAC2_VERIFY_FAIL                    (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0CU)

/** The MAC over the region update record fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RID_MAC_VERIFY_FAIL                 (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0DU)

/** There is an error when validating the ECU IDs in the region update record. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RID_ECU_ID_INVALID                  (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0EU)

/** The signature over the region update record fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RID_SIGN_VERIFY_FAIL                (ecy_hsm_CSAI_GM_ERROR_MASK | 0x0FU)

/** The MAC over the root public key update record fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_MAC_VERIFY_FAIL         (ecy_hsm_CSAI_GM_ERROR_MASK | 0x10U)

/** The region in the root public key update record is invalid. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_INVALID_REGION          (ecy_hsm_CSAI_GM_ERROR_MASK | 0x11U)

/** The record type in the root public key update record is invalid. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_INVALID_RECORD_TYPE     (ecy_hsm_CSAI_GM_ERROR_MASK | 0x12U)

/** The root update count in the root public key update record is invalid. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_INVALID_ROOT_UPDATE_CNT (ecy_hsm_CSAI_GM_ERROR_MASK | 0x13U)

/** The ECU ID in the root public key update record is not equal to the ECU ID saved in the HSM. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_ECU_ID_MISMATCH         (ecy_hsm_CSAI_GM_ERROR_MASK | 0x14U)

/** The root signature over the root public key update record fails to verify. */
# define ecy_hsm_CSAI_GM_ERR_FSKA_RPUK_UPDATE_SIGN_VERIFY_FAIL        (ecy_hsm_CSAI_GM_ERROR_MASK | 0x15U)

/** The ticket parameters do not match the ones in HSM info block */
# define ecy_hsm_CSAI_GM_ERR_SBAT_PARAM_MISMATCH                      (ecy_hsm_CSAI_GM_ERROR_MASK | 0x16U)

/** The digital signature algorithm in the signer info doesn't match the one in the HSM info block */
# define ecy_hsm_CSAI_GM_ERR_SBAT_SIGNER_INFO                         (ecy_hsm_CSAI_GM_ERROR_MASK | 0x17U)

/** The ticket MAC verification failed or provided MAC is invalid */
# define ecy_hsm_CSAI_GM_ERR_SBAT_MAC_VERIFICATION                    (ecy_hsm_CSAI_GM_ERROR_MASK | 0x18U)

/** The ticket signature verification failed or provided signature is invalid */
# define ecy_hsm_CSAI_GM_ERR_SBAT_SIGNATURE_VERIFICATION              (ecy_hsm_CSAI_GM_ERROR_MASK | 0x19U)

/** The SV key could not be derived */
# define ecy_hsm_CSAI_GM_ERR_SBAT_KDF                                 (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1AU)

/** The sbit or reference table is invalid */
# define ecy_hsm_CSAI_GM_ERR_SB_TABLE_INVALID                         (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1BU)

/** Conditions not correct for host bootloader MAC generation */
# define ecy_hsm_CSAI_GM_ERR_SB_BOOTMAC_GEN                           (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1CU)

/** The Secure Boot Init flag is already set to TRUE */
# define ecy_hsm_CSAI_GM_ERR_SB_ALREADY_INITIALIZED                   (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1DU)

/** The Secure Boot Init flag is not set */
# define ecy_hsm_CSAI_GM_ERR_SB_INIT_FLAG_NOT_SET                     (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1EU)

/** The SBIT present flag is not set */
# define ecy_hsm_CSAI_GM_ERR_SB_SBIT_PRESENT_FLAG_NOT_SET             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x1FU)

/** Invalid SBIT length */
# define ecy_hsm_CSAI_GM_ERR_SB_INVALID_TABLE_LENGTH                  (ecy_hsm_CSAI_GM_ERROR_MASK | 0x20U)

/** Error in the secure boot MAC verificaiton */
# define ecy_hsm_CSAI_GM_ERR_SB_MAC_VERIFICATION                      (ecy_hsm_CSAI_GM_ERROR_MASK | 0x21U)

/** Invalid address for MAC */
# define ecy_hsm_CSAI_GM_ERR_SB_INVALID_MAC_ADDRESS                   (ecy_hsm_CSAI_GM_ERROR_MASK | 0x22U)

/** Secure boot MAC verificaiton key is not set */
# define ecy_hsm_CSAI_GM_ERR_SB_MISSING_MAC_VERIF_KEY                 (ecy_hsm_CSAI_GM_ERROR_MASK | 0x23U)

/** Secure boot R1 autoverificaiton flag is not set */
# define ecy_hsm_CSAI_GM_ERR_SB_SBIT_R1_AUTO_VERIF_NOT_SET            (ecy_hsm_CSAI_GM_ERROR_MASK | 0x24U)

/** Secure boot Region 1 is invalid */
# define ecy_hsm_CSAI_GM_ERR_SB_SBIT_INVALID_REGION_R1                (ecy_hsm_CSAI_GM_ERROR_MASK | 0x25U)

/** An address referenced in the SBIT is invalid */
# define ecy_hsm_CSAI_GM_ERR_SB_SBIT_INVALID_ADDRESS                  (ecy_hsm_CSAI_GM_ERROR_MASK | 0x26U)

/** Verifying a digest failed */
# define ecy_hsm_CSAI_GM_ERR_SB_DIGEST_VERIFICATION                   (ecy_hsm_CSAI_GM_ERROR_MASK | 0x27U)

/** Verification Data Set flag was already set for the attempted operation */
# define ecy_hsm_CSAI_GM_ERR_SB_VD_FLAG_SET                           (ecy_hsm_CSAI_GM_ERROR_MASK | 0x28U)

/** MAC update failed */
# define ecy_hsm_CSAI_GM_ERR_SB_MAC_UPDATE                            (ecy_hsm_CSAI_GM_ERROR_MASK | 0x29U)

/** Cys Info Block (CIB) update is not allowed */
# define ecy_hsm_CSAI_GM_ERR_SB_CIB_UPDATE_NOT_ALLOWED                (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2AU)

/** General Verification Data Set flag was already set for the attempted operation */
# define ecy_hsm_CSAI_GM_ERR_SB_GEN_DATA_VD_FLAG_SET                  (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2BU)

/** Valid additional authentication data is not present */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_INVALID                    (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2CU)

/** The ECU ID in the additional auth data does not match the stored ID */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_ECU_ID_INVALID             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2DU)

/** The additional auth counter in the additional auth data is less than the stored counter */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_COUNTER_INVALID            (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2EU)

/** The additional auth type is invalid */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_TYPE_INVALID               (ecy_hsm_CSAI_GM_ERROR_MASK | 0x2FU)

/** The number of parts in the additional auth data is invalid */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_NUMBER_PARTS_INVALID       (ecy_hsm_CSAI_GM_ERROR_MASK | 0x30U)

/** The length of the additional auth data is invalid */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_LENGTH_INVALID             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x31U)

/** Verification of the additional auth data MAC failed */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_VERIFY_FAIL                (ecy_hsm_CSAI_GM_ERROR_MASK | 0x32U)

/** Failed to derive the key needed to verify the additional auth data */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_KDF                        (ecy_hsm_CSAI_GM_ERROR_MASK | 0x33U)

/** The given additional auth data does not contain data for the requested soft part */
# define ecy_hsm_CSAI_GM_ERR_FSKA_ADD_AUTH_PART_NOT_FOUND             (ecy_hsm_CSAI_GM_ERROR_MASK | 0x34U)

/** The specified service ID does not exist in the MGAL */
# define ecy_hsm_CSAI_GM_ERR_MGAL_SERVICE_ID_NOT_FOUND                (ecy_hsm_CSAI_GM_ERROR_MASK | 0xE6U)

/** The MGAL in the provided SBIT was invalid */
# define ecy_hsm_CSAI_GM_ERR_INVALID_MGAL                             (ecy_hsm_CSAI_GM_ERROR_MASK | 0xE7U)

/** The provided message is malformed or invalid. */
# define ecy_hsm_CSAI_GM_ERR_MGAL_INVALID_MESSAGE                     (ecy_hsm_CSAI_GM_ERROR_MASK | 0xE8U)

/** The mac generation is prohibited. */
# define ecy_hsm_CSAI_GM_ERR_MGAL_AUTH_ERROR                          (ecy_hsm_CSAI_GM_ERROR_MASK | 0xE9U)

/* ************************** GHSM - Error list end **************************/
/**
 * @}
 */

/**** Type definitions *****************************************************/

#endif /*ECY_HSM_CSAI_ERROR_MDK_H*/

/**
 * @endcond
 */
