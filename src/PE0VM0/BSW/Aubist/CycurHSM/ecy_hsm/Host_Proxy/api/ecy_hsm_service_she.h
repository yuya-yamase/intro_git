/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Signature verification and generation.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating and verifying digital signatures.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_SHE_H
#define ECY_HSM_SERVICE_SHE_H

/**
 * @addtogroup GROUP_SHE
 * @{
 */

/* *** includes *******************************************************************************/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#endif
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_shecompat.h"

/* *** defines ********************************************************************************/
/** Converts a session handle to a port idx */
#define ecy_hsm_CONVERT_SESSIONHANDLE2IDX(_handle)       ((HSM_PortT)(_handle))

/** This is the chunk size for SHE encryption and decryption operation */
#define ecy_hsm_SHE_CHUNK_SIZE_IN_BYTES                  (768)

/** SHE function declaration type   */
#define ecy_hsm_SHE_DECLSPEC                             extern

/** SHE function cmac quick route max size  */
#define ecy_hsm_SHE_MAX_QUICK_ROUTE_BYTES                (256U)

/** Size of a block of data processed in parallel by the AES hardware */
#define ecy_hsm_SHE_AES_BLOCK_SIZE_BYTES                 (16U) /**< Number of bytes in a SHE data block            */
#define ecy_hsm_SHE_AES_BLOCK_SIZE_WORDS                 (4U)  /**< Number of uint32 words in a SHE data block     */

/** Sizes of the M1-M5 key data blocks   */
#define SHE_M1_BLOCK_SIZE_BYTES                          ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES  /**< Size of the M1 key data block            */
#define SHE_M2_BLOCK_SIZE_BYTES                          ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES  /**< Size of the M2 key data block            */
#define SHE_M3_BLOCK_SIZE_BYTES                          ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES  /**< Size of the M3 key data block            */
#define SHE_M4_BLOCK_SIZE_BYTES                          ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES  /**< Size of the M4 key data block            */
#define SHE_M5_BLOCK_SIZE_BYTES                          ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES  /**< Size of the M5 key data block            */

#define ecy_hsm_SHE_M3_BLOCK_SIZE_BITS                   (128U) /**< Size of the M3 key data block in bits */
#define ecy_hsm_SHE_M5_BLOCK_SIZE_BITS                   (128U) /**< Size of the M3 key data block in bits */

/** Size of the SHE id block    */
#define ecy_hsm_SHE_ID_BLOCK_SIZE_BYTES                  (15U)

/**
 * @anchor SHE_STATUS_BITS SHE status bits
 * @{
 */

/** This bit is set when the SHE module is busy processing a command */
#define SHE_STATUS_BUSY                                  ecy_hsm_CSAI_SHE_STATUS_BUSY

/** This bit is set if secure booting is activated */
#define SHE_STATUS_SECURE_BOOT                           ecy_hsm_CSAI_SHE_STATUS_SECURE_BOOT

/** This bit is set if secure booting has been personalized during the boot sequence */
#define SHE_STATUS_BOOT_INIT                             ecy_hsm_CSAI_SHE_STATUS_BOOT_INIT

/**
 * This bit is set when secure booting has been finished by calling one of
 * @ref SHE_SecureBootFailure(), @ref SHE_SecureBootOk() or if @ref SHE_SecureBoot
 * failed to verify the MAC.
 */
#define SHE_STATUS_BOOT_FINISHED                         ecy_hsm_CSAI_SHE_STATUS_BOOT_FINISHED

/**
 * This bit is set when @ref SHE_SecureBoot succeeded. @ref SHE_SecureBootFailure()
 * erases this bit.
 */
#define SHE_STATUS_BOOT_OK                               ecy_hsm_CSAI_SHE_STATUS_BOOT_OK

/**
 * This bit is set when the random number generator has been initialized.
 */
#define SHE_STATUS_RND_INIT                              ecy_hsm_CSAI_SHE_STATUS_RND_INIT

/**
 * This bit is set when an external debugger is connected to the chip, i.e. it
 * reflects the input for debugger activation.
 */
#define SHE_STATUS_EXT_DEBUGGER                          ecy_hsm_CSAI_SHE_STATUS_EXT_DEBUGGER

/**
 * This bit is set when the internal debugging mechanisms of the SHE module are
 * activated.
 */
#define SHE_STATUS_INT_DEBUGGER                          ecy_hsm_CSAI_SHE_STATUS_INT_DEBUGGER

/** @} */

/* *** defines ********************************************************************************/

/**
 * @anchor ANCHOR_CSAI_ERROR_CLASS_SHE
 * @name   Members of the CSAI error class @ref CSAI_ERROR_CLASS_SHE
 * @brief  These error codes are for the SHE emulation.
 * @{
 */
/* These CSAI_SHE error codes are used so that SHE and CSAI errors can be interleaved in functions_she.c.
 * They are masked into SHE error codes and never returned to the host (particularly, they are not
 * returned from CSAI_SHE_Compat functions)
 */
/** SHE no error */
#define ecy_hsm_ERR_SHE_ERC_NO_ERROR                     (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_NO_ERROR)

/** SHE busy */
#define ecy_hsm_ERR_SHE_ERC_BUSY                         (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_BUSY)

/** SHE general error */
/** @details This includes data non-alignment (not aligned to a 32 bit boundary) */
#define ecy_hsm_ERR_SHE_ERC_GENERAL_ERROR                (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_GENERAL_ERROR)

/** SHE attempt to use a key that is not initialised */
#define ecy_hsm_ERR_SHE_ERC_KEY_EMPTY                    (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_KEY_EMPTY)

/** SHE key is not valid for the operation */
#define ecy_hsm_ERR_SHE_ERC_KEY_INVALID                  (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_KEY_INVALID)

/** SHE key is not available, e.g. locked */
#define ecy_hsm_ERR_SHE_ERC_KEY_NOT_AVAILABLE            (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_KEY_NOT_AVAILABLE)

/** SHE key update did not succeed due to errors in verification of the protocol messages */
#define ecy_hsm_ERR_SHE_ERC_KEY_UPDATE_ERROR             (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_KEY_UPDATE_ERROR)

/** SHE key update attempted on write protected key or when an attempt is made to activate the debugger when a
    key is write protected */
#define ecy_hsm_ERR_SHE_ERC_KEY_WRITE_PROTECTED          (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_KEY_WRITE_PROTECTED)

/** SHE underlying memory technology registered a fault */
#define ecy_hsm_ERR_SHE_ERC_MEMORY_FAILURE               (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_MEMORY_FAILURE)

/** SHE internal debugging is not possible because the challenge response authentication did not
    complete successfully */
#define ecy_hsm_ERR_SHE_ERC_NO_DEBUGGING                 (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_NO_DEBUGGING)

/** SHE
 * This error is returned by the command @ref SHE_SecureBoot when the
 * conditions for a secure boot process are not met and the secure boot
 * process has to be cancelled. It is also returned if a function changing
 * the boot status is called without secure booting or after finishing the
 * secure boot process.
 * It means that Secure boot has failed, keys with the ecy_hsm_CSAI_KEYPROP_SECURE_BOOT_MUST_PASS property will
 * not be available.
 */
#define ecy_hsm_ERR_SHE_ERC_NO_SECURE_BOOT               (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_NO_SECURE_BOOT)

/** SHE Returned by @ref SHE_Rnd if the seed has not been initialized before */
#define ecy_hsm_ERR_SHE_ERC_RNG_SEED                     (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_RNG_SEED)

/** SHE Error in sequence of commands or sub commands */
#define ecy_hsm_ERR_SHE_ERC_SEQUENCE_ERROR               (ecy_hsm_CSAI_ERR_FLAG_ERROR | ecy_hsm_CSAI_ERR_CLASS_SHE | (uint32)ERC_SEQUENCE_ERROR)

/** @} */

/**
 * @anchor ANCHOR_SHE_KEY_FLAGS
 * @name   Members of the SHE key flags
 * @brief  These are the SHE key flags, the bit number is the number of bits from the start of the M2 message
 * @{
 */

/** SHE key is write protected key flag */
#define ecy_hsm_SHE_KEY_FLAG_WRITE_PROTECTED_BIT         (28U)

/** SHE key is disabled on boot failure key flag */
#define ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_BOOT_FAIL_BIT    (29U)

/** SHE key is disabled on debugger activation key flag */
#define ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_DEBUG_BIT        (30U)

/** SHE key usage key flag, clear for encrypt/decrypt, set for MAC generate/verify */
#define ecy_hsm_SHE_KEY_FLAG_USAGE_MAC_BIT               (31U)

/** SHE key cannot be updated with wildcard UID key flag */
#define ecy_hsm_SHE_KEY_FLAG_DISABLE_WILDCARD_UPDATE_BIT (32U)

/** SHE+ key verify only key flag */
#define ecy_hsm_SHE_KEY_FLAG_VERIFY_ONLY_BIT             (33U)

/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_VERIFY_ONLY_BIT
 */
#define SHE_KEY_FLAG_VERIFY_ONLY_BIT                     ecy_hsm_SHE_KEY_FLAG_VERIFY_ONLY_BIT
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_DISABLE_WILDCARD_UPDATE_BIT
 */
#define SHE_KEY_FLAG_DISABLE_WILDCARD_UPDATE_BIT         ecy_hsm_SHE_KEY_FLAG_DISABLE_WILDCARD_UPDATE_BIT
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_USAGE_MAC_BIT
 */
#define SHE_KEY_FLAG_USAGE_MAC_BIT                       ecy_hsm_SHE_KEY_FLAG_USAGE_MAC_BIT
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_DEBUG_BIT
 */
#define SHE_KEY_FLAG_DISABLE_ON_DEBUG_BIT                ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_DEBUG_BIT
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_BOOT_FAIL_BIT
 */
#define SHE_KEY_FLAG_DISABLE_ON_BOOT_FAIL_BIT            ecy_hsm_SHE_KEY_FLAG_DISABLE_ON_BOOT_FAIL_BIT
/**
 * @deprecated by ecy_hsm_SHE_KEY_FLAG_WRITE_PROTECTED_BIT
 */
#define SHE_KEY_FLAG_WRITE_PROTECTED_BIT                 ecy_hsm_SHE_KEY_FLAG_WRITE_PROTECTED_BIT
/**
 * @deprecated by ecy_hsm_SHE_ID_BLOCK_SIZE_BYTES
 */
#define SHE_ID_BLOCK_SIZE_BYTES                          ecy_hsm_SHE_ID_BLOCK_SIZE_BYTES
/**
 * @deprecated by ecy_hsm_SHE_M5_BLOCK_SIZE_BITS
 */
#define SHE_M5_BLOCK_SIZE_BITS                           ecy_hsm_SHE_M5_BLOCK_SIZE_BITS
/**
 * @deprecated by ecy_hsm_SHE_M3_BLOCK_SIZE_BITS
 */
#define SHE_M3_BLOCK_SIZE_BITS                           ecy_hsm_SHE_M3_BLOCK_SIZE_BITS
/**
 * @deprecated by ecy_hsm_SHE_AES_BLOCK_SIZE_WORDS
 */
#define SHE_AES_BLOCK_SIZE_WORDS                         ecy_hsm_SHE_AES_BLOCK_SIZE_WORDS
/**
 * @deprecated by ecy_hsm_SHE_AES_BLOCK_SIZE_BYTES
 */
#define SHE_AES_BLOCK_SIZE_BYTES                         ecy_hsm_SHE_AES_BLOCK_SIZE_BYTES
/**
 * @deprecated by ecy_hsm_SHE_MAX_QUICK_ROUTE_BYTES
 */
#define SHE_MAX_QUICK_ROUTE_BYTES                        ecy_hsm_SHE_MAX_QUICK_ROUTE_BYTES
/**
 * @deprecated by ecy_hsm_SHE_DECLSPEC
 */
#define SHE_DECLSPEC                                     ecy_hsm_SHE_DECLSPEC
/**
 * @deprecated by ecy_hsm_SHE_CHUNK_SIZE_IN_BYTES
 */
#define SHE_CHUNK_SIZE_IN_BYTES                          ecy_hsm_SHE_CHUNK_SIZE_IN_BYTES
/**
 * @deprecated by ecy_hsm_CONVERT_SESSIONHANDLE2IDX
 */
#define CONVERT_SESSIONHANDLE2IDX                        ecy_hsm_CONVERT_SESSIONHANDLE2IDX
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_NO_ERROR
 */
#define CSAI_ERR_SHE_ERC_NO_ERROR                        ecy_hsm_ERR_SHE_ERC_NO_ERROR
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_BUSY
 */
#define CSAI_ERR_SHE_ERC_BUSY                            ecy_hsm_ERR_SHE_ERC_BUSY
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_GENERAL_ERROR
 */
#define CSAI_ERR_SHE_ERC_GENERAL_ERROR                   ecy_hsm_ERR_SHE_ERC_GENERAL_ERROR
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_KEY_EMPTY
 */
#define CSAI_ERR_SHE_ERC_KEY_EMPTY                       ecy_hsm_ERR_SHE_ERC_KEY_EMPTY
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_KEY_INVALID
 */
#define CSAI_ERR_SHE_ERC_KEY_INVALID                     ecy_hsm_ERR_SHE_ERC_KEY_INVALID
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_KEY_NOT_AVAILABLE
 */
#define CSAI_ERR_SHE_ERC_KEY_NOT_AVAILABLE               ecy_hsm_ERR_SHE_ERC_KEY_NOT_AVAILABLE
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_KEY_UPDATE_ERROR
 */
#define CSAI_ERR_SHE_ERC_KEY_UPDATE_ERROR                ecy_hsm_ERR_SHE_ERC_KEY_UPDATE_ERROR
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_KEY_WRITE_PROTECTED
 */
#define CSAI_ERR_SHE_ERC_KEY_WRITE_PROTECTED             ecy_hsm_ERR_SHE_ERC_KEY_WRITE_PROTECTED
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_MEMORY_FAILURE
 */
#define CSAI_ERR_SHE_ERC_MEMORY_FAILURE                  ecy_hsm_ERR_SHE_ERC_MEMORY_FAILURE
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_NO_DEBUGGING
 */
#define CSAI_ERR_SHE_ERC_NO_DEBUGGING                    ecy_hsm_ERR_SHE_ERC_NO_DEBUGGING
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_NO_SECURE_BOOT
 */
#define CSAI_ERR_SHE_ERC_NO_SECURE_BOOT                  ecy_hsm_ERR_SHE_ERC_NO_SECURE_BOOT
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_RNG_SEED
 */
#define CSAI_ERR_SHE_ERC_RNG_SEED                        ecy_hsm_ERR_SHE_ERC_RNG_SEED
/**
 * @deprecated by ecy_hsm_ERR_SHE_ERC_SEQUENCE_ERROR
 */
#define CSAI_ERR_SHE_ERC_SEQUENCE_ERROR                  ecy_hsm_ERR_SHE_ERC_SEQUENCE_ERROR

/** @} */

/* *** type declarations **********************************************************************/

/** SHE key IDs */
/*  SHE must contain a unique secret key, which should be inserted by the manufacturer
 *  This is not the implementation but it shows that CycurHSM supports the SHE SECRET Key   */
typedef enum ecy_hsm_SHE_KeyIdTag
{
    ecy_hsm_SECRET_KEY         = 0x00,       /**< AES hardware secret key    */
    ecy_hsm_MASTER_ECU_KEY     = 0x01,       /**< SHE MASTER_ECU_KEY         */
    ecy_hsm_BOOT_MAC_KEY       = 0x02,       /**< SHE BOOT_MAC_KEY           */
    ecy_hsm_BOOT_MAC           = 0x03,       /**< SHE boot MAC value         */
    ecy_hsm_KEY_1              = 0x04,       /**< General purpose key 1      */
    ecy_hsm_KEY_2              = 0x05,       /**< General purpose key 2      */
    ecy_hsm_KEY_3              = 0x06,       /**< General purpose key 3      */
    ecy_hsm_KEY_4              = 0x07,       /**< General purpose key 4      */
    ecy_hsm_KEY_5              = 0x08,       /**< General purpose key 5      */
    ecy_hsm_KEY_6              = 0x09,       /**< General purpose key 6      */
    ecy_hsm_KEY_7              = 0x0a,       /**< General purpose key 7      */
    ecy_hsm_KEY_8              = 0x0b,       /**< General purpose key 8      */
    ecy_hsm_KEY_9              = 0x0c,       /**< General purpose key 9      */
    ecy_hsm_KEY_10             = 0x0d,       /**< General purpose key 10     */
    ecy_hsm_RAM_KEY            = 0x0e,       /**< SHE RAM key, volatile      */
    ecy_hsm_RES_KEY            = 0x0f,       /**< SHE Reserved key           */
    ecy_hsm_KEY_11             = 0x10,       /**< General purpose key 11     */
    ecy_hsm_KEY_12             = 0x11,       /**< General purpose key 12     */
    ecy_hsm_KEY_13             = 0x12,       /**< General purpose key 13     */
    ecy_hsm_KEY_14             = 0x13,       /**< General purpose key 14     */
    ecy_hsm_KEY_15             = 0x14,       /**< General purpose key 15     */
    ecy_hsm_KEY_16             = 0x15,       /**< General purpose key 16     */
    ecy_hsm_KEY_17             = 0x16,       /**< General purpose key 17     */
    ecy_hsm_KEY_18             = 0x17,       /**< General purpose key 18     */
    ecy_hsm_KEY_19             = 0x18,       /**< General purpose key 19     */
    ecy_hsm_KEY_20             = 0x19,       /**< General purpose key 20     */
    ecy_hsm_KEY_21             = 0x1a,       /**< General purpose key 21     */
    ecy_hsm_KEY_22             = 0x1b,       /**< General purpose key 22     */
    ecy_hsm_KEY_23             = 0x1c,       /**< General purpose key 23     */
    ecy_hsm_KEY_24             = 0x1d,       /**< General purpose key 24     */
    ecy_hsm_KEY_25             = 0x1e,       /**< General purpose key 25     */
    ecy_hsm_KEY_26             = 0x1f,       /**< General purpose key 26     */
    ecy_hsm_KEY_27             = 0x20,       /**< General purpose key 27     */
    ecy_hsm_KEY_28             = 0x21,       /**< General purpose key 28     */
    ecy_hsm_KEY_29             = 0x22,       /**< General purpose key 29     */
    ecy_hsm_KEY_30             = 0x23,       /**< General purpose key 30     */
    ecy_hsm_KEY_31             = 0x24,       /**< General purpose key 31     */
    ecy_hsm_KEY_32             = 0x25,       /**< General purpose key 32     */
    ecy_hsm_KEY_33             = 0x26,       /**< General purpose key 33     */
    ecy_hsm_KEY_34             = 0x27,       /**< General purpose key 34     */
    ecy_hsm_KEY_35             = 0x28,       /**< General purpose key 35     */
    ecy_hsm_KEY_36             = 0x29,       /**< General purpose key 36     */
    ecy_hsm_KEY_37             = 0x2a,       /**< General purpose key 37     */
    ecy_hsm_KEY_38             = 0x2b,       /**< General purpose key 38     */
    ecy_hsm_KEY_39             = 0x2c,       /**< General purpose key 39     */
    ecy_hsm_KEY_40             = 0x2d,       /**< General purpose key 40     */
    ecy_hsm_KEY_41             = 0x2e,       /**< General purpose key 41     */
    ecy_hsm_KEY_42             = 0x2f,       /**< General purpose key 42     */
    ecy_hsm_KEY_43             = 0x30,       /**< General purpose key 43     */
    ecy_hsm_KEY_44             = 0x31,       /**< General purpose key 44     */
    ecy_hsm_KEY_45             = 0x32,       /**< General purpose key 45     */
    ecy_hsm_KEY_46             = 0x33,       /**< General purpose key 46     */
    ecy_hsm_KEY_47             = 0x34,       /**< General purpose key 47     */
    ecy_hsm_KEY_48             = 0x35,       /**< General purpose key 48     */
    ecy_hsm_KEY_49             = 0x36,       /**< General purpose key 49     */
    ecy_hsm_KEY_50             = 0x37,       /**< General purpose key 50     */
    SHE_KEYID_RESERVED = 0x7FFFFFFFU /**< Ensure full 32 bits are used for the enum         */
} ecy_hsm_SHE_KeyIdT;
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_SECRET_KEY
 */
#define SECRET_KEY ecy_hsm_SECRET_KEY
/**
 * @deprecated by ecy_hsm_MASTER_ECU_KEY
 */
#define MASTER_ECU_KEY ecy_hsm_MASTER_ECU_KEY
/**
 * @deprecated by ecy_hsm_BOOT_MAC_KEY
 */
#define BOOT_MAC_KEY ecy_hsm_BOOT_MAC_KEY
/**
 * @deprecated by ecy_hsm_BOOT_MAC
 */
#define BOOT_MAC ecy_hsm_BOOT_MAC
/**
 * @deprecated by ecy_hsm_KEY_1
 */
#define KEY_1 ecy_hsm_KEY_1
/**
 * @deprecated by ecy_hsm_KEY_2
 */
#define KEY_2 ecy_hsm_KEY_2
/**
 * @deprecated by ecy_hsm_KEY_3
 */
#define KEY_3 ecy_hsm_KEY_3
/**
 * @deprecated by ecy_hsm_KEY_4
 */
#define KEY_4 ecy_hsm_KEY_4
/**
 * @deprecated by ecy_hsm_KEY_5
 */
#define KEY_5 ecy_hsm_KEY_5
/**
 * @deprecated by ecy_hsm_KEY_6
 */
#define KEY_6 ecy_hsm_KEY_6
/**
 * @deprecated by ecy_hsm_KEY_7
 */
#define KEY_7 ecy_hsm_KEY_7
/**
 * @deprecated by ecy_hsm_KEY_8
 */
#define KEY_8 ecy_hsm_KEY_8
/**
 * @deprecated by ecy_hsm_KEY_9
 */
#define KEY_9 ecy_hsm_KEY_9
/**
 * @deprecated by ecy_hsm_KEY_10
 */
#define KEY_10 ecy_hsm_KEY_10
/**
 * @deprecated by ecy_hsm_RAM_KEY
 */
#define RAM_KEY ecy_hsm_RAM_KEY
/**
 * @deprecated by ecy_hsm_KEY_11
 */
#define KEY_11 ecy_hsm_KEY_11
/**
 * @deprecated by ecy_hsm_KEY_12
 */
#define KEY_12 ecy_hsm_KEY_12
/**
 * @deprecated by ecy_hsm_KEY_13
 */
#define KEY_13 ecy_hsm_KEY_13
/**
 * @deprecated by ecy_hsm_KEY_14
 */
#define KEY_14 ecy_hsm_KEY_14
/**
 * @deprecated by ecy_hsm_KEY_15
 */
#define KEY_15 ecy_hsm_KEY_15
/**
 * @deprecated by ecy_hsm_KEY_16
 */
#define KEY_16 ecy_hsm_KEY_16
/**
 * @deprecated by ecy_hsm_KEY_17
 */
#define KEY_17 ecy_hsm_KEY_17
/**
 * @deprecated by ecy_hsm_KEY_18
 */
#define KEY_18 ecy_hsm_KEY_18
/**
 * @deprecated by ecy_hsm_KEY_19
 */
#define KEY_19 ecy_hsm_KEY_19
/**
 * @deprecated by ecy_hsm_KEY_20
 */
#define KEY_20 ecy_hsm_KEY_20
/**
 * @deprecated by ecy_hsm_KEY_21
 */
#define KEY_21 ecy_hsm_KEY_21
/**
 * @deprecated by ecy_hsm_KEY_22
 */
#define KEY_22 ecy_hsm_KEY_22
/**
 * @deprecated by ecy_hsm_KEY_23
 */
#define KEY_23 ecy_hsm_KEY_23
/**
 * @deprecated by ecy_hsm_KEY_24
 */
#define KEY_24 ecy_hsm_KEY_24
/**
 * @deprecated by ecy_hsm_KEY_25
 */
#define KEY_25 ecy_hsm_KEY_25
/**
 * @deprecated by ecy_hsm_KEY_26
 */
#define KEY_26 ecy_hsm_KEY_26
/**
 * @deprecated by ecy_hsm_KEY_27
 */
#define KEY_27 ecy_hsm_KEY_27
/**
 * @deprecated by ecy_hsm_KEY_28
 */
#define KEY_28 ecy_hsm_KEY_28
/**
 * @deprecated by ecy_hsm_KEY_29
 */
#define KEY_29 ecy_hsm_KEY_29
/**
 * @deprecated by ecy_hsm_KEY_30
 */
#define KEY_30 ecy_hsm_KEY_30
/**
 * @deprecated by ecy_hsm_KEY_31
 */
#define KEY_31 ecy_hsm_KEY_31
/**
 * @deprecated by ecy_hsm_KEY_32
 */
#define KEY_32 ecy_hsm_KEY_32
/**
 * @deprecated by ecy_hsm_KEY_33
 */
#define KEY_33 ecy_hsm_KEY_33
/**
 * @deprecated by ecy_hsm_KEY_34
 */
#define KEY_34 ecy_hsm_KEY_34
/**
 * @deprecated by ecy_hsm_KEY_35
 */
#define KEY_35 ecy_hsm_KEY_35
/**
 * @deprecated by ecy_hsm_KEY_36
 */
#define KEY_36 ecy_hsm_KEY_36
/**
 * @deprecated by ecy_hsm_KEY_37
 */
#define KEY_37 ecy_hsm_KEY_37
/**
 * @deprecated by ecy_hsm_KEY_38
 */
#define KEY_38 ecy_hsm_KEY_38
/**
 * @deprecated by ecy_hsm_KEY_39
 */
#define KEY_39 ecy_hsm_KEY_39
/**
 * @deprecated by ecy_hsm_KEY_40
 */
#define KEY_40 ecy_hsm_KEY_40
/**
 * @deprecated by ecy_hsm_KEY_41
 */
#define KEY_41 ecy_hsm_KEY_41
/**
 * @deprecated by ecy_hsm_KEY_42
 */
#define KEY_42 ecy_hsm_KEY_42
/**
 * @deprecated by ecy_hsm_KEY_43
 */
#define KEY_43 ecy_hsm_KEY_43
/**
 * @deprecated by ecy_hsm_KEY_44
 */
#define KEY_44 ecy_hsm_KEY_44
/**
 * @deprecated by ecy_hsm_KEY_45
 */
#define KEY_45 ecy_hsm_KEY_45
/**
 * @deprecated by ecy_hsm_KEY_46
 */
#define KEY_46 ecy_hsm_KEY_46
/**
 * @deprecated by ecy_hsm_KEY_47
 */
#define KEY_47 ecy_hsm_KEY_47
/**
 * @deprecated by ecy_hsm_KEY_48
 */
#define KEY_48 ecy_hsm_KEY_48
/**
 * @deprecated by ecy_hsm_KEY_49
 */
#define KEY_49 ecy_hsm_KEY_49
/**
 * @deprecated by ecy_hsm_KEY_50
 */
#define KEY_50 ecy_hsm_KEY_50
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_KeyIdTag
 */
#define SHE_KeyIdTag ecy_hsm_SHE_KeyIdTag
/**
 * @deprecated by ecy_hsm_SHE_KeyIdT
 */
#define SHE_KeyIdT ecy_hsm_SHE_KeyIdT

/** SHE error codes */
typedef enum ecy_hsm_SHE_ErrorCodeTag
{
    /**
     * No error has occurred, command will be executed
     */
    ecy_hsm_ERC_NO_ERROR = 0U,
    /**
     * Error, SHE module is still busy with another function.
     */
    ecy_hsm_ERC_BUSY = 1U,
    /**
     * Error, which is not covered by any other specific error code.
     */
    ecy_hsm_ERC_GENERAL_ERROR = 2U,
    /**
     * Error, attempt to use a key that is not initialized.
     */
    ecy_hsm_ERC_KEY_EMPTY = 3U,
    /**
     * Error, the key is not valid for the operation.
     */
    ecy_hsm_ERC_KEY_INVALID = 4U,
    /**
     * Error, the key is not available, e.g. locked.
     */
    ecy_hsm_ERC_KEY_NOT_AVAILABLE = 5U,
    /**
     * Error, the key update did not succeed due to errors in verification
     * of the protocol messages.
     */
    ecy_hsm_ERC_KEY_UPDATE_ERROR = 6U,
    /**
     * Error, key update attempted on write protected key or when an attempt
     * is made to activate the debugger when a key is write protected
     */
    ecy_hsm_ERC_KEY_WRITE_PROTECTED = 7U,
    /**
     * Error, underlying memory technology registered a fault.
     */
    ecy_hsm_ERC_MEMORY_FAILURE = 8U,
    /**
     * Error, internal debugging is not possible because the challenge
     * response authentication did not complete successfully.
     */
    ecy_hsm_ERC_NO_DEBUGGING = 9U,

    /**
     * This error is returned by the command @ref SHE_SecureBoot when the
     * conditions for a secure boot process are not met and the secure boot
     * process has to be cancelled. It is also returned if a function changing
     * the boot status is called without secure booting or after finishing the
     * secure boot process.
     */
    ecy_hsm_ERC_NO_SECURE_BOOT = 10U,
    /**
     * Returned by @ref SHE_Rnd if the seed has not been initialized before.
     */
    ecy_hsm_ERC_RNG_SEED = 11U,
    /**
     * Error in sequence of commands or sub commands.
     */
    ecy_hsm_ERC_SEQUENCE_ERROR         = 12U,
    ecy_hsm_ERC_SHE_ERRORCODE_RESERVED = 0x7FFFFFFFU /**< Ensure full 32 bits are used for the enum         */
} ecy_hsm_SHE_ErrorCodeT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_ErrorCodeTag
 */
#define SHE_ErrorCodeTag ecy_hsm_SHE_ErrorCodeTag
/**
 * @deprecated by ecy_hsm_SHE_ErrorCodeT
 */
#define SHE_ErrorCodeT ecy_hsm_SHE_ErrorCodeT

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_ERC_NO_ERROR
 */
#define ERC_NO_ERROR ecy_hsm_ERC_NO_ERROR
/**
 * @deprecated by ecy_hsm_ERC_BUSY
 */
#define ERC_BUSY ecy_hsm_ERC_BUSY
/**
 * @deprecated by ecy_hsm_ERC_GENERAL_ERROR
 */
#define ERC_GENERAL_ERROR ecy_hsm_ERC_GENERAL_ERROR
/**
 * @deprecated by ecy_hsm_ERC_KEY_EMPTY
 */
#define ERC_KEY_EMPTY ecy_hsm_ERC_KEY_EMPTY
/**
 * @deprecated by ecy_hsm_ERC_KEY_INVALID
 */
#define ERC_KEY_INVALID ecy_hsm_ERC_KEY_INVALID
/**
 * @deprecated by ecy_hsm_ERC_KEY_NOT_AVAILABLE
 */
#define ERC_KEY_NOT_AVAILABLE ecy_hsm_ERC_KEY_NOT_AVAILABLE
/**
 * @deprecated by ecy_hsm_ERC_KEY_UPDATE_ERROR
 */
#define ERC_KEY_UPDATE_ERROR ecy_hsm_ERC_KEY_UPDATE_ERROR
/**
 * @deprecated by ecy_hsm_ERC_KEY_WRITE_PROTECTED
 */
#define ERC_KEY_WRITE_PROTECTED ecy_hsm_ERC_KEY_WRITE_PROTECTED
/**
 * @deprecated by ecy_hsm_ERC_MEMORY_FAILURE
 */
#define ERC_MEMORY_FAILURE ecy_hsm_ERC_MEMORY_FAILURE
/**
 * @deprecated by ecy_hsm_ERC_NO_DEBUGGING
 */
#define ERC_NO_DEBUGGING ecy_hsm_ERC_NO_DEBUGGING
/**
 * @deprecated by ecy_hsm_ERC_NO_SECURE_BOOT
 */
#define ERC_NO_SECURE_BOOT ecy_hsm_ERC_NO_SECURE_BOOT
/**
 * @deprecated by ecy_hsm_ERC_RNG_SEED
 */
#define ERC_RNG_SEED ecy_hsm_ERC_RNG_SEED
/**
 * @deprecated by ecy_hsm_ERC_SEQUENCE_ERROR
 */
#define ERC_SEQUENCE_ERROR ecy_hsm_ERC_SEQUENCE_ERROR
/**
 * @deprecated by ecy_hsm_ERC_SHE_ERRORCODE_RESERVED
 */
#define ERC_SHE_ERRORCODE_RESERVED ecy_hsm_ERC_SHE_ERRORCODE_RESERVED
/** Structure for the data passed to a LoadKey operation with further extended key support via key bank index  */
typedef struct ecy_hsm_SHE_LoadKeyToBankParamTag
{
    uint32       csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    const uint8* m1;         /**< Pointer to 16 byte M1 parameter                                        */
    const uint8* m2;         /**< Pointer to 32 byte M2 parameter                                        */
    const uint8* m3;         /**< Pointer to 16 byte M3 parameter                                        */
    uint8*       m4;         /**< Pointer to 32 byte M4 parameter                                        */
    uint8*       m5;         /**< Pointer to 16 byte M5 parameter                                        */
    uint32       bankIndex;  /**< Key slot bank index                                                    */
} ecy_hsm_SHE_LoadKeyToBankParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_LoadKeyToBankParamTag
 */
#define SHE_LoadKeyToBankParamTag ecy_hsm_SHE_LoadKeyToBankParamTag
/**
 * @deprecated by ecy_hsm_SHE_LoadKeyToBankParamT
 */
#define SHE_LoadKeyToBankParamT ecy_hsm_SHE_LoadKeyToBankParamT

/** Structure for the data passed to a LoadPlainKey operation   */
typedef struct ecy_hsm_SHE_LoadPlainKeyParamTag
{
    uint32       csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    const uint8* key;        /**< Pointer to 16 byte plain key data                                      */
} ecy_hsm_SHE_LoadPlainKeyParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_LoadPlainKeyParamTag
 */
#define SHE_LoadPlainKeyParamTag ecy_hsm_SHE_LoadPlainKeyParamTag
/**
 * @deprecated by ecy_hsm_SHE_LoadPlainKeyParamT
 */
#define SHE_LoadPlainKeyParamT ecy_hsm_SHE_LoadPlainKeyParamT
/** Structure for the data passed to an ExportRamKey operation   */
typedef struct ecy_hsm_SHE_ExportRamKeyParamTag
{
    uint32 csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    uint8* m1;         /**< Pointer to 16 byte buffer to receive M1                                */
    uint8* m2;         /**< Pointer to 32 byte buffer to receive M2                                */
    uint8* m3;         /**< Pointer to 16 byte buffer to receive M3                                */
    uint8* m4;         /**< Pointer to 32 byte buffer to receive M4                                */
    uint8* m5;         /**< Pointer to 16 byte buffer to receive M5                                */
} ecy_hsm_SHE_ExportRamKeyParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_ExportRamKeyParamTag
 */
#define SHE_ExportRamKeyParamTag ecy_hsm_SHE_ExportRamKeyParamTag
/**
 * @deprecated by ecy_hsm_SHE_ExportRamKeyParamT
 */
#define SHE_ExportRamKeyParamT ecy_hsm_SHE_ExportRamKeyParamT
/** Structure for the data passed to a SHE_GetID operation */
typedef struct ecy_hsm_SHE_GetIDParamTag
{
    uint32       csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    const uint8* challenge;  /**< Pointer to sixteen bytes of challenge data                             */
    uint8*       id;         /**< Pointer to fifteen byte buffer to receive the ID                       */
    uint8*       pStatus;    /**< Pointer to one byte buffer to receive status register                  */
    uint8*       mac;        /**< Pointer to sixteen byte buffer to receive MAC                          */
} ecy_hsm_SHE_GetIDParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_GetIDParamTag
 */
#define SHE_GetIDParamTag ecy_hsm_SHE_GetIDParamTag
/**
 * @deprecated by ecy_hsm_SHE_GetIDParamT
 */
#define SHE_GetIDParamT ecy_hsm_SHE_GetIDParamT
/** Structure for the data passed to a SHE_CmdDebugChallenge operation */
typedef struct ecy_hsm_SHE_DebugChallengeParamTag
{
    uint32 csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    uint8* challenge;  /**< Pointer to sixteen bytes of challenge data                             */
} ecy_hsm_SHE_DebugChallengeParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DebugChallengeParamTag
 */
#define SHE_DebugChallengeParamTag ecy_hsm_SHE_DebugChallengeParamTag
/**
 * @deprecated by ecy_hsm_SHE_DebugChallengeParamT
 */
#define SHE_DebugChallengeParamT ecy_hsm_SHE_DebugChallengeParamT
/** Structure for the data passed to a SHE_CmdDebugAuthorize operation */
typedef struct ecy_hsm_SHE_DebugAuthorizeParamTag
{
    uint32       csaiErrors;         /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    const uint8* debugAuthorization; /**< Pointer to sixteen bytes of authorization data                         */
} ecy_hsm_SHE_DebugAuthorizeParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DebugAuthorizeParamTag
 */
#define SHE_DebugAuthorizeParamTag ecy_hsm_SHE_DebugAuthorizeParamTag
/**
 * @deprecated by ecy_hsm_SHE_DebugAuthorizeParamT
 */
#define SHE_DebugAuthorizeParamT ecy_hsm_SHE_DebugAuthorizeParamT
/** Define different states for SHE Debug */
typedef enum ecy_hsm_SHE_DebugStateTag
{
    ecy_hsm_DEBUG_STATE_RESET           = 0x00000000UL, /**< State reset */
    ecy_hsm_DEBUG_STATE_GETCHALLENGE    = 0x00000001UL, /**< State get challenge */
    ecy_hsm_UPDATE_STATE_NOT_AUTHORIZED = 0x00000002UL, /**< State not authorized */
    ecy_hsm_UPDATE_STATE_AUTHORIZED     = 0x00000003UL, /**< State authorized */
    ecy_hsm_UPDATE_STATE_RESERVED       = 0x7fffffffUL  /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_SHE_DebugStateT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DebugStateTag
 */
#define SHE_DebugStateTag ecy_hsm_SHE_DebugStateTag
/**
 * @deprecated by ecy_hsm_SHE_DebugStateT
 */
#define SHE_DebugStateT ecy_hsm_SHE_DebugStateT
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_DEBUG_STATE_RESET
 */
#define HSM_DEBUG_STATE_RESET ecy_hsm_DEBUG_STATE_RESET
/**
 * @deprecated by ecy_hsm_DEBUG_STATE_GETCHALLENGE
 */
#define HSM_DEBUG_STATE_GETCHALLENGE ecy_hsm_DEBUG_STATE_GETCHALLENGE
/**
 * @deprecated by ecy_hsm_UPDATE_STATE_NOT_AUTHORIZED
 */
#define HSM_UPDATE_STATE_NOT_AUTHORIZED ecy_hsm_UPDATE_STATE_NOT_AUTHORIZED
/**
 * @deprecated by ecy_hsm_UPDATE_STATE_AUTHORIZED
 */
#define HSM_UPDATE_STATE_AUTHORIZED ecy_hsm_UPDATE_STATE_AUTHORIZED
/**
 * @deprecated by ecy_hsm_UPDATE_STATE_RESERVED
 */
#define HSM_UPDATE_STATE_RESERVED ecy_hsm_UPDATE_STATE_RESERVED

/** Structure for the SHE Debug Context */
typedef struct ecy_hsm_SHE_DebugCtxTag
{
    ecy_hsm_SHE_DebugStateT state;               /**< State of debugging */
    uint8                   lastChallenge[16UL]; /**< Array of the last challenge data (sixteen bytes) */
} ecy_hsm_SHE_DebugCtxT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DebugCtxTag
 */
#define SHE_DebugCtxTag ecy_hsm_SHE_DebugCtxTag
/**
 * @deprecated by ecy_hsm_SHE_DebugCtxT
 */
#define SHE_DebugCtxT ecy_hsm_SHE_DebugCtxT
/** Structure for the data passed to a SHE_SecureBoot operation */
typedef struct ecy_hsm_SHE_SecureBootParamTag
{
    uint32       csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
    uint32       size;       /**< Size of data block to check the MAC of                                 */
    const uint8* data;       /**< Pointer to start of data block to check the MAC of                     */
} ecy_hsm_SHE_SecureBootParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_SecureBootParamTag
 */
#define SHE_SecureBootParamTag ecy_hsm_SHE_SecureBootParamTag
/**
 * @deprecated by ecy_hsm_SHE_SecureBootParamT
 */
#define SHE_SecureBootParamT ecy_hsm_SHE_SecureBootParamT

/** Structure for the data passed to a SHE_SecureBootOk or SHE_SecureBootFailure operation  */
typedef struct ecy_hsm_SHE_SecureBootControlParamTag
{
    uint32 csaiErrors; /**< The function shall return CSAI errors if TRUE or SHE errors if FALSE.  */
} ecy_hsm_SHE_SecureBootControlParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_SecureBootControlParamTag
 */
#define SHE_SecureBootControlParamTag ecy_hsm_SHE_SecureBootControlParamTag
/**
 * @deprecated by ecy_hsm_SHE_SecureBootControlParamT
 */
#define SHE_SecureBootControlParamT ecy_hsm_SHE_SecureBootControlParamT

/** Generic structure for ECB SHE En- Decrypt operation
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_CryptEcbParamTag
{
    SHE_KeyIdT   keySlotId;     /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* pDataIn;       /**< Pointer to Input data chunk                            */
    uint32       dataInLength;  /**< Length of the plaintext chunk in bits                  */
    uint8*       pDataOut;      /**< Pointer to buffer for the complete ciphertext          */
    uint32       dataOutLength; /**< Size of the cipher text buffer in bits                 */
} ecy_hsm_SHE_CryptEcbParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_CryptEcbParamTag
 */
#define SHE_CryptEcbParamTag ecy_hsm_SHE_CryptEcbParamTag
/**
 * @deprecated by ecy_hsm_SHE_CryptEcbParamT
 */
#define SHE_CryptEcbParamT ecy_hsm_SHE_CryptEcbParamT

/** Structure for the data passed for a SHE_EncryptEcb operation
 *
 * @deprecated
 * This structure is subject to change with next major update
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_EncryptEcbParamTag
{
    SHE_KeyIdT   keySlotId;       /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* plainText;       /**< Pointer to plaintext chunk                             */
    uint32       plainTextLength; /**< Length of the plaintext chunk in bits                  */
    uint8*       cipherText;      /**< Pointer to buffer for the complete ciphertext          */
    uint32       cipherTextSize;  /**< Size of the cipher text buffer in bits                 */
} ecy_hsm_SHE_EncryptEcbParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_EncryptEcbParamTag
 */
#define SHE_EncryptEcbParamTag ecy_hsm_SHE_EncryptEcbParamTag
/**
 * @deprecated by ecy_hsm_SHE_EncryptEcbParamT
 */
#define SHE_EncryptEcbParamT ecy_hsm_SHE_EncryptEcbParamT

/** Structure for the data passed for a SHE_DecryptEcb operation
 *
 * @deprecated
 * This structure is subject to change with next major update
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_DecryptEcbParamTag
{
    SHE_KeyIdT   keySlotId;        /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* cipherText;       /**< Pointer to ciphertext chunk                            */
    uint32       cipherTextLength; /**< Length of the ciphertext chunk in bits                 */
    uint8*       plainText;        /**< Pointer to buffer for the complete plaintext           */
    uint32       plainTextSize;    /**< Size of the plain text buffer in bits                  */
} ecy_hsm_SHE_DecryptEcbParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DecryptEcbParamTag
 */
#define SHE_DecryptEcbParamTag ecy_hsm_SHE_DecryptEcbParamTag
/**
 * @deprecated by ecy_hsm_SHE_DecryptEcbParamT
 */
#define SHE_DecryptEcbParamT ecy_hsm_SHE_DecryptEcbParamT

/** Generic structure for CBC SHE En- Decrypt operation
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_CryptCbcParamTag
{
    SHE_KeyIdT   keySlotId;     /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* iv;            /**< Pointer to IV, assumed to be 16 bytes long             */
    const uint8* pDataIn;       /**< Pointer to input data                                  */
    uint32       dataInLength;  /**< Length of the input data chunk in bits                 */
    uint8*       pDataOut;      /**< Pointer to buffer for the complete output data         */
    uint32       dataOutLength; /**< Size of the output data buffer in bits                 */
} ecy_hsm_SHE_CryptCbcParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_CryptCbcParamTag
 */
#define SHE_CryptCbcParamTag ecy_hsm_SHE_CryptCbcParamTag
/**
 * @deprecated by ecy_hsm_SHE_CryptCbcParamT
 */
#define SHE_CryptCbcParamT ecy_hsm_SHE_CryptCbcParamT

/** Structure for the data passed for a SHE_EncryptCbc operation
 *
 * @deprecated
 * This structure is subject to change with next major update
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_EncryptCbcParamTag
{
    SHE_KeyIdT   keySlotId;       /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* iv;              /**< Pointer to IV, assumed to be 16 bytes long             */
    const uint8* plainText;       /**< Pointer to plaintext chunk                             */
    uint32       plainTextLength; /**< Length of the plaintext chunk in bits                  */
    uint8*       cipherText;      /**< Pointer to buffer for the complete ciphertext          */
    uint32       cipherTextSize;  /**< Size of the cipher text buffer in bits                 */
} ecy_hsm_SHE_EncryptCbcParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_EncryptCbcParamTag
 */
#define SHE_EncryptCbcParamTag ecy_hsm_SHE_EncryptCbcParamTag
/**
 * @deprecated by ecy_hsm_SHE_EncryptCbcParamT
 */
#define SHE_EncryptCbcParamT ecy_hsm_SHE_EncryptCbcParamT

/** Structure for the data passed for a SHE_DecryptCbc operation
 *
 * @deprecated
 * This structure is subject to change with next major update
 *
 * @internal
 * @note
 * To allow generic parameter checks field @ref iv shall be moved to end of
 * structure to have common base structure for all crypto operations
 * @endinternal
 */
typedef struct ecy_hsm_SHE_DecryptCbcParamTag
{
    SHE_KeyIdT   keySlotId;        /**< SHE ID of the NVM key slot from which to load the key  */
    const uint8* iv;               /**< Pointer to IV, assumed to be 16 bytes long             */
    const uint8* cipherText;       /**< Pointer to ciphertext chunk                            */
    uint32       cipherTextLength; /**< Length of the ciphertext chunk in bits                 */
    uint8*       plainText;        /**< Pointer to buffer for the complete plaintext           */
    uint32       plainTextSize;    /**< Size of the plain text buffer in bits                  */
} ecy_hsm_SHE_DecryptCbcParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_DecryptCbcParamTag
 */
#define SHE_DecryptCbcParamTag ecy_hsm_SHE_DecryptCbcParamTag
/**
 * @deprecated by ecy_hsm_SHE_DecryptCbcParamT
 */
#define SHE_DecryptCbcParamT ecy_hsm_SHE_DecryptCbcParamT

/** Generic structure for SHE MAC operations */
typedef struct ecy_hsm_SHE_MACParamTag
{
    SHE_KeyIdT   keySlotId;           /**< KeyId for the operation                                                                           */
    const uint8* msg;                 /**< Pointer to data block to be MAC'd                                                                 */
    uint32       msgLength;           /**< Length of data block to be MAC'd in @b bits                                                       */
    uint8*       mac;                 /**< Pointer to 16 byte buffer to receive the result                                                   */
    uint32       macLength;           /**< Number of @b bits to compare, according to SHE spec a mac length of 0 is interpreted as 128 bits. */
    uint32*      pVerificationStatus; /**< Pointer to flag to take the result of the MAC compare                                             */
} ecy_hsm_SHE_MACParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_MACParamTag
 */
#define SHE_MACParamTag ecy_hsm_SHE_MACParamTag
/**
 * @deprecated by ecy_hsm_SHE_MACParamT
 */
#define SHE_MACParamT ecy_hsm_SHE_MACParamT

/**
 * Structure for the data passed for a SHE_GenerateMACStart operation
 *
 * @deprecated
 * This structure is subject to be replaced with common @ref SHE_MACParamTag for next major update
 */
typedef struct ecy_hsm_SHE_MACGenerateParamTag
{
    SHE_KeyIdT   keySlotId; /**< KeyId for the operation                                */
    const uint8* msg;       /**< Pointer to data block to be MAC'd                      */
    uint32       msgLength; /**< Length of data block to be MAC'd in @b bits            */
    uint8*       mac;       /**< Pointer to 16 byte buffer to receive the result        */
} ecy_hsm_SHE_MACGenerateParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_MACGenerateParamTag
 */
#define SHE_MACGenerateParamTag ecy_hsm_SHE_MACGenerateParamTag
/**
 * @deprecated by ecy_hsm_SHE_MACGenerateParamT
 */
#define SHE_MACGenerateParamT ecy_hsm_SHE_MACGenerateParamT
/**
 * Copy @ref SHE_MACGenerateParamTag
 * On PowerPC targets, copying must be done field by field, otherwise GHS compiler uses memmove() to copy, which is slower
 *
 * @param[out]   _dst    @ref SHE_MACGenerateParamTag destination object
 * @param[in]    _pSrc   Pointer to @ref SHE_MACGenerateParamTag source object
 */
#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_POWER)
# define ecy_hsm_SHE_COPY_MAC_GEN_PARAM(_dst, _pSrc)                                                                                                 \
    do                                                                                                                                               \
    {                                                                                                                                                \
        (_dst).keySlotId = (_pSrc)->keySlotId;                                                                                                       \
        (_dst).msg       = (_pSrc)->msg;                                                                                                             \
        (_dst).msgLength = (_pSrc)->msgLength;                                                                                                       \
        (_dst).mac       = (_pSrc)->mac;                                                                                                             \
    } while (0)
#else
# define ecy_hsm_SHE_COPY_MAC_GEN_PARAM(_dst, _pSrc)                                                                                                 \
    do                                                                                                                                               \
    {                                                                                                                                                \
        (_dst) = *(_pSrc);                                                                                                                           \
    } while (0)
#endif

/**
 * Structure for the data passed for a SHE_VerifyMACStart operation
 *
 * @deprecated
 * This structure is subject to be replaced with common @ref SHE_MACParamTag for next major update
 */
typedef struct ecy_hsm_SHE_MACVerifyParamTag
{
    SHE_KeyIdT   keySlotId;           /**< KeyId for the operation                                                                           */
    const uint8* msg;                 /**< Pointer to data block to be MAC'd                                                                 */
    uint32       msgLength;           /**< Length of data block to be MAC'd in @b bits                                                       */
    const uint8* mac;                 /**< Pointer to 16 byte buffer to receive the result                                                   */
    uint32       macLength;           /**< Number of @b bits to compare, according to SHE spec a mac length of 0 is interpreted as 128 bits. */
    uint32*      pVerificationStatus; /**< Pointer to flag to take the result of the MAC compare                                             */
} ecy_hsm_SHE_MACVerifyParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_MACVerifyParamTag
 */
#define SHE_MACVerifyParamTag ecy_hsm_SHE_MACVerifyParamTag
/**
 * @deprecated by ecy_hsm_SHE_MACVerifyParamT
 */
#define SHE_MACVerifyParamT ecy_hsm_SHE_MACVerifyParamT
/**
 * Copy @ref SHE_MACVerifyParamTag
 * On PowerPC targets, copying must be done field by field, otherwise GHS compiler uses memmove() to copy, which is slower
 *
 * @param[out]   _dst    @ref SHE_MACVerifyParamTag destination object
 * @param[in]    _pSrc   Pointer to @ref SHE_MACVerifyParamTag source object
 */
#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_POWER)
# define ecy_hsm_SHE_COPY_MAC_VER_PARAM(_dst, _pSrc)                                                                                                 \
    do                                                                                                                                               \
    {                                                                                                                                                \
        (_dst).keySlotId           = (_pSrc)->keySlotId;                                                                                             \
        (_dst).msg                 = (_pSrc)->msg;                                                                                                   \
        (_dst).msgLength           = (_pSrc)->msgLength;                                                                                             \
        (_dst).mac                 = (_pSrc)->mac;                                                                                                   \
        (_dst).macLength           = (_pSrc)->macLength;                                                                                             \
        (_dst).pVerificationStatus = (_pSrc)->pVerificationStatus;                                                                                   \
    } while (0)
#else
# define ecy_hsm_SHE_COPY_MAC_VER_PARAM(_dst, _pSrc)                                                                                                 \
    do                                                                                                                                               \
    {                                                                                                                                                \
        (_dst) = *(_pSrc);                                                                                                                           \
    } while (0)
#endif

/** Structure for the data passed to a SHE_ExtendSeed operation */
typedef struct ecy_hsm_SHE_ExtendSeedParamTag
{
    const uint8* entropy; /**< Pointer to 16 byte buffer containing entropy for the PRNG re-seed  */
} ecy_hsm_SHE_ExtendSeedParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_ExtendSeedParamTag
 */
#define SHE_ExtendSeedParamTag ecy_hsm_SHE_ExtendSeedParamTag
/**
 * @deprecated by ecy_hsm_SHE_ExtendSeedParamT
 */
#define SHE_ExtendSeedParamT ecy_hsm_SHE_ExtendSeedParamT
/** Structure for the data passed to a SHE_Rnd operation */
typedef struct ecy_hsm_SHE_RndParamTag
{
    uint8* rnd; /**< Pointer to 16 byte buffer to be filled with pseudo random data  */
} ecy_hsm_SHE_RndParamT;
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SHE_RndParamTag
 */
#define SHE_RndParamTag ecy_hsm_SHE_RndParamTag
/**
 * @deprecated by ecy_hsm_SHE_RndParamT
 */
#define SHE_RndParamT ecy_hsm_SHE_RndParamT
// clang-format off
/** Structure for the data passed  */
/* PRQA S 0750 2 */ /* Deviation: Use of union provides polymorphism of SHE parameters and reuse of a single API. */
typedef union ecy_hsm_HSM_SheParamTag {
    ecy_hsm_SHE_LoadKeyToBankParamT     SHE_LoadKeyToBankParam;     /**< Structure for the data passed to a SHE_LoadKey operation with further extended key support via key bank index */
    ecy_hsm_SHE_LoadPlainKeyParamT      SHE_LoadPlainKeyParam;      /**< Structure for the data passed to a SHE_LoadPlainKey operation */
    ecy_hsm_SHE_ExportRamKeyParamT      SHE_ExportRamKeyParam;      /**< Structure for the data passed to a SHE_ExportRamKey operation */
    ecy_hsm_SHE_GetIDParamT             SHE_GetIDParam;             /**< Structure for the data passed to a SHE_GetID operation */
    ecy_hsm_SHE_DebugChallengeParamT    SHE_DebugChallengeParam;    /**< Structure for the data passed to a SHE_CmdDebugChallenge operation */
    ecy_hsm_SHE_DebugAuthorizeParamT    SHE_DebugAuthorizeParam;    /**< Structure for the data passed to a SHE_CmdDebugAuthorize operation */
    ecy_hsm_SHE_DebugCtxT               SHE_DebugCtx;               /**< Structure for the SHE Debug Context */
    ecy_hsm_SHE_SecureBootParamT        SHE_SecureBootParam;        /**< Structure for the data passed to a SHE_SecureBoot operation */
    ecy_hsm_SHE_SecureBootControlParamT SHE_SecureBootControlParam; /**< Structure for the data passed to a SHE_SecureBootOk or SHE_SecureBootFailure operation */
    ecy_hsm_SHE_CryptEcbParamT          SHE_CryptEcbParam;          /**< Generic Structure for SHE ECB En- / Decryption */
    ecy_hsm_SHE_EncryptEcbParamT        SHE_EncryptEcbParam;        /**< Structure for the data passed for a SHE_EncryptEcb operation */
    ecy_hsm_SHE_DecryptEcbParamT        SHE_DecryptEcbParam;        /**< Structure for the data passed for a SHE_DecryptEcb operation */
    ecy_hsm_SHE_CryptCbcParamT          SHE_CryptCbcParam;          /**< Generic Structure for SHE CBC En- / Decryption */
    ecy_hsm_SHE_EncryptCbcParamT        SHE_EncryptCbcParam;        /**< Structure for the data passed for a SHE_EncryptCbc operation */
    ecy_hsm_SHE_DecryptCbcParamT        SHE_DecryptCbcParam;        /**< Structure for the data passed for a SHE_DecryptCbc operation */
    ecy_hsm_SHE_MACParamT               SHE_MACParam;               /**< Generic Structure for SHE MAC operations */
    ecy_hsm_SHE_MACGenerateParamT       SHE_MACGenerateParam;       /**< Structure for the data passed for a SHE_GenerateMACStart operation */
    ecy_hsm_SHE_MACVerifyParamT         SHE_MACVerifyParam;         /**< Structure for the data passed for a SHE_VerifyMACStart operation */
    ecy_hsm_SHE_ExtendSeedParamT        SHE_ExtendSeedParam;        /**< Structure for the data passed to a SHE_ExtendSeed operation */
    ecy_hsm_SHE_RndParamT               SHE_RndParam;               /**< Structure for the data passed to a SHE_Rnd operation */
} ecy_hsm_HSM_SheParamT;
// clang-format on
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_HSM_SheParamTag
 */
#define HSM_SheParamTag ecy_hsm_HSM_SheParamTag
/**
 * @deprecated by ecy_hsm_HSM_SheParamT
 */
#define HSM_SheParamT ecy_hsm_HSM_SheParamT
/**
 * @}
 */
#endif /* Multiple inclusion lock  */
