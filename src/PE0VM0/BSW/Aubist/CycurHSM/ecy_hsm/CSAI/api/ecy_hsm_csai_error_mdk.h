/**
 * @cond MDK_DOXYGEN_ENABLED
 * @file
 ***********************************************************************************************
 * @brief This header file is part of the interface to MDK applet.
 * the errors returned from the MDK interface are defined here.
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2020, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_ERROR_MDK_H
#define ECY_HSM_CSAI_ERROR_MDK_H

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_CUST_MDK
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_CUST_MDK
 * @brief  These error codes are for the MDK interface.
 * @{
 */

/**** Includes *************************************************************/
#include "ecy_hsm_csai_error.h"

/**** C preprocessor definitions *******************************************/

/* These CSAI_MDK error codes are used so that MDK and CSAI errors can be interleaved.
 */
/** MDK Exit success */
#define ecy_hsm_CSAI_MDK_ERR_NONE                                                                        \
    (ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_NONE)
/** MDK General failure */
#define ecy_hsm_CSAI_MDK_ERR_GENERAL                                                                     \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_GENERAL)
/** MDK was not initialized */
#define ecy_hsm_CSAI_MDK_ERR_NOT_INITIALIZED                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_NOT_INITIALIZED)
/** Size of the provided output buffer is not sufficient. */
#define ecy_hsm_CSAI_MDK_ERR_SMALL_BUFFER                                                                \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_SMALL_BUFFER)
/** Error reading a key from the HSM key store. */
#define ecy_hsm_CSAI_MDK_ERR_HW_KEY_READ_FAIL                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_HW_KEY_READ_FAIL)
/** Error writing a key to the HSM key store. */
#define ecy_hsm_CSAI_MDK_ERR_HW_KEY_WRITE_FAIL                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_HW_KEY_WRITE_FAIL)
/** Error writing a key to the HSM key store: wrong key length */
#define ecy_hsm_CSAI_MDK_ERR_HW_CRYPTO_KEY_SIZE_MISMATCH                                                 \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_HW_CRYPTO_KEY_SIZE_MISMATCH)
/** Error using the crypto hw */
#define ecy_hsm_CSAI_MDK_ERR_HW_CRYPTO_OTHER                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_HW_CRYPTO_OTHER)
/** All ephemeral keys are used and removed from RAM */
#define ecy_hsm_CSAI_MDK_ERR_NO_VALID_KEYS                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_NO_VALID_KEYS)
/** MDK was initialized in another session */
#define ecy_hsm_CSAI_MDK_ERR_INVALID_SESSION                                                             \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_INVALID_SESSION)
/** Chosen MDK slot is empty */
#define ecy_hsm_CSAI_MDK_ERR_EMPTY_SLOT                                                                  \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_EMPTY_SLOT)
/** No empty MDK slot available */
#define ecy_hsm_CSAI_MDK_ERR_NO_EMPTY_SLOT                                                               \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_NO_EMPTY_SLOT)
/** Invalid signature */
#define ecy_hsm_CSAI_MDK_ERR_INVALID_SIGNATURE                                                           \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_INVALID_SIGNATURE)
/** MDK Unknown Slot Id failure */
#define ecy_hsm_CSAI_MDK_ERR_UNKNOWN_SLOT_ID                                                        \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_UNKNOWN_SLOT_ID)
/** Key slot is not valid */
#define ecy_hsm_CSAI_MDK_ERR_INVALID_KEY_SLOT                                                            \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_INVALID_KEY_SLOT)
/** WFS keys were already derived */
#define ecy_hsm_CSAI_MDK_ERR_WFS_KEYS_ALREADY_DERIVED                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_WFS_KEYS_ALREADY_DERIVED)
/** MDK Unknown Session Id failure */
#define ecy_hsm_CSAI_MDK_ERR_UNKNOWN_SESSION_ID                                                          \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_UNKNOWN_SESSION_ID)
/** The provided certificate could not be verified */
#define ecy_hsm_CSAI_MDK_ERR_CERT_VERIFICATION_FAILED                                                    \
    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_CUST | (uint32)ecy_hsm_MDK_ERR_CERT_VERIFICATION_FAILED)
/**
 * @}
 */

/**** Type definitions *****************************************************/
/** Internal MDK error codes */
typedef enum ecy_hsm_Csai_MDKErrorCodeTag
{
    /**
     * Exit success.
     */
    ecy_hsm_MDK_ERR_NONE                        = 80U,        /**< No error */
    ecy_hsm_MDK_ERR_GENERAL                     = 81U,        /**< General failure */
    ecy_hsm_MDK_ERR_NOT_INITIALIZED             = 82U,        /**< MDK is was not initialized */
    ecy_hsm_MDK_ERR_SMALL_BUFFER                = 83U,        /**< Target buffer too small */
    ecy_hsm_MDK_ERR_HW_KEY_READ_FAIL            = 84U,        /**< Error reading a key from the HSM key store */
    ecy_hsm_MDK_ERR_HW_KEY_WRITE_FAIL           = 85U,        /**< Error writing a key from the HSM key store */
    ecy_hsm_MDK_ERR_HW_CRYPTO_KEY_SIZE_MISMATCH = 86U,        /**< Error writing a key to the HSM key store: wrong key length */
    ecy_hsm_MDK_ERR_HW_CRYPTO_OTHER             = 87U,        /**< Error using the crypto hw */
    ecy_hsm_MDK_ERR_NO_VALID_KEYS               = 88U,        /**< All ephemeral keys are used and removed from RAM */
    ecy_hsm_MDK_ERR_INVALID_SESSION             = 89U,        /**< MDK was initialized in another session */
    ecy_hsm_MDK_ERR_EMPTY_SLOT                  = 90U,        /**< Chosen MDK slot is empty */
    ecy_hsm_MDK_ERR_NO_EMPTY_SLOT               = 91U,        /**< No empty MDK slot available */
    ecy_hsm_MDK_ERR_INVALID_SIGNATURE           = 92U,        /**< Invalid signature */
    ecy_hsm_MDK_ERR_UNKNOWN_SLOT_ID             = 93U,        /**< MDK Unknown Slot Id failure */
    ecy_hsm_MDK_ERR_INVALID_KEY_SLOT            = 94U,        /**< Key slot is not valid */
    ecy_hsm_MDK_ERR_WFS_KEYS_ALREADY_DERIVED    = 95U,        /**< WFS Keys are already derived */
    ecy_hsm_MDK_ERR_UNKNOWN_SESSION_ID          = 96U,        /**< MDK Unknown Session Id failure */
    ecy_hsm_MDK_ERR_CERT_VERIFICATION_FAILED    = 97U,        /**< The provided certificate could not be verified */
    ecy_hsm_MDK_ERR_RESERVED                    = 0x7FFFFFFFU /**< Ensure full 32 bits are used for the enum */

} ecy_hsm_Csai_MDKErrorCodeT;

#endif /*ECY_HSM_CSAI_ERROR_MDK_H*/

/**
 * @endcond
 */
