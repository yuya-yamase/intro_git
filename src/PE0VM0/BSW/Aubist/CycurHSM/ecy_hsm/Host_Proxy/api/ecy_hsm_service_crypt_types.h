/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Crypto jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * macro for Encryption and Decryption operations with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_SERVICE_CRYPT_TYPES
#define ECY_HSM_SERVICE_CRYPT_TYPES

/* *** defines ********************************************************************************/
#define ecy_hsm_AES_BLOCK_SIZE_BITS             (128U)    /**< Size in bits of a block for the AES hardware   */
#define ecy_hsm_AES_BLOCK_SIZE_BYTES            (16U)     /**< Size in bytes of a block for the AES hardware  */
#define ecy_hsm_AES_BLOCK_SIZE_WORDS            (4U)      /**< Size in words of a block for the AES hardware  */

#define ecy_hsm_SM4_BLOCK_SIZE_BITS             (128U)    /**< Size in bits of a block for the SM4   */
#define ecy_hsm_SM4_BLOCK_SIZE_BYTES            (16U)     /**< Size in bytes of a block for the SM4  */
#define ecy_hsm_SM4_BLOCK_SIZE_WORDS            (4U)      /**< Size in words of a block for the SM4  */

#define ecy_hsm_AES_BLOCK_SIZE_BYTES_LOG2       (4U)      /**< Value used to shift to the next 32-bit value in a byte-block  */
#define ecy_hsm_AES_BLOCK_SIZE_WORDS_LOG2       (2U)      /**< Value used to shift to the next 32-bit value in a word-block  */
/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_AES_BLOCK_SIZE_BITS
 */
#define AES_BLOCK_SIZE_BITS ecy_hsm_AES_BLOCK_SIZE_BITS
/**
 * @deprecated by @ref ecy_hsm_AES_BLOCK_SIZE_BYTES
 */
#define AES_BLOCK_SIZE_BYTES ecy_hsm_AES_BLOCK_SIZE_BYTES
/**
 * @deprecated by @ref ecy_hsm_AES_BLOCK_SIZE_WORDS
 */
#define AES_BLOCK_SIZE_WORDS ecy_hsm_AES_BLOCK_SIZE_WORDS

/**
 * @deprecated by @ref ecy_hsm_SM4_BLOCK_SIZE_BITS
 */
#define SM4_BLOCK_SIZE_BITS ecy_hsm_SM4_BLOCK_SIZE_BITS
/**
 * @deprecated by @ref ecy_hsm_SM4_BLOCK_SIZE_BYTES
 */
#define SM4_BLOCK_SIZE_BYTES ecy_hsm_SM4_BLOCK_SIZE_BYTES
/**
 * @deprecated by @ref ecy_hsm_SM4_BLOCK_SIZE_WORDS
 */
#define SM4_BLOCK_SIZE_WORDS ecy_hsm_SM4_BLOCK_SIZE_WORDS
/**
 * @deprecated by @ref ecy_hsm_AES_BLOCK_SIZE_BYTES_LOG2
 */
#define AES_BLOCK_SIZE_BYTES_LOG2 ecy_hsm_AES_BLOCK_SIZE_BYTES_LOG2
/**
 * @deprecated by @ref ecy_hsm_AES_BLOCK_SIZE_WORDS_LOG2
 */
#define AES_BLOCK_SIZE_WORDS_LOG2 ecy_hsm_AES_BLOCK_SIZE_WORDS_LOG2

#endif /* ECY_HSM_SERVICE_CRYPT_TYPES */
