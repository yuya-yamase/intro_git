/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Crypto jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for Encryption and Decryption operations with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_CRYPT_H
#define ECY_HSM_CSAI_CRYPT_H

/**
 * @addtogroup GROUP_CSAI_CRYPT
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_hash.h"
#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_csai_dh.h"
/* *** defines ********************************************************************************/
#define ecy_hsm_CSAI_IV_LENGTH                (16U)       /**< Length in bytes of the initialisation vector for other modes                           */
#define ecy_hsm_CSAI_ECB_MODE_IV_LENGTH        (0U)       /**< Length in bytes of the initialisation vector for ECB mode                              */
#define ecy_hsm_CSAI_GCM_MODE_IV_LENGTH       (12U)       /**< Length in bytes of the initialisation vector for GCM mode                              */
#define ecy_hsm_CSAI_C20_P1305_NONCE_LENGTH   (12U)       /**< Length in bytes of the nonce for C20P1305                                              */
#define ecy_hsm_CSAI_NIST_SP800_PADDING     (0x80U)       /**< Padding character recommended by NIST SP800                                            */

/* *** type declarations **********************************************************************/

/**
 * Declare symmetric block cipher encryption and decryption modes supported by the HSM.
 */
typedef enum ecy_hsm_Csai_SymCipherModeTag
{
    ecy_hsm_CSAI_AES_ECB     = 1, /**< AES cipher suite with electronic code block mode as specified by FIPS-PUB 197 */
    ecy_hsm_CSAI_AES_CBC     = 2, /**< AES cipher suite with cipher block chaining mode as specified by FIPS-PUB 197 */
    ecy_hsm_CSAI_AES_CFB128  = 3, /**< AES cipher suite with cipher feedback mode and 128 bit block size as specified by FIPS-PUB 197 */
    ecy_hsm_CSAI_AES_OFB     = 4, /**< AES cipher suite with output feedback mode as specified by FIPS-PUB 197 */
    ecy_hsm_CSAI_AES_CTR     = 5, /**< AES cipher suite with counter mode as specified by FIPS-PUB 197 */
    ecy_hsm_CSAI_AES_GCM     = 6, /**< AES cipher suite with Galois counter modes specified by FIPS-PUB 197  */
    ecy_hsm_CSAI_AES_XTS     = 7, /**< Xor-encrypt-xor (XEX) based tweaked codebook mode (TCB)with  cipher text stealing (CTS) as specified by NIST SP800-38E
                                       Only 256-bit key is supported */
    ecy_hsm_CSAI_AES_GCM_HW  = 8, /**< AES cipher suite with Galois counter mode with HW support - only for internal use, since it lacks multitasking support  */
    ecy_hsm_CSAI_AES_CMAC_HW = 9, /**< AES-cipher-based message authentication Code as specified by NIST SP 800-38B */
    ecy_hsm_CSAI_SM4_ECB     = 10,/**< SM4 cipher suite with electronic code block mode as specified by GB/T 32907-2016 */
    ecy_hsm_CSAI_C20_P1305   = 11,/**< CHACHA20 cipher suite with POLY1305 Additional assosciated data as specified by RFC 7539 */
    ecy_hsm_CSAI_SYMCIPHER_RESERVED = 0x7fffffffu /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_SymCipherModeT;

/**
 * Declare asymmetric encryption and decryption modes supported by the HSM.
 */
typedef enum ecy_hsm_Csai_AsymCipherModeTag
{
    ecy_hsm_CSAI_RSA_ES_PKCS1_v15    = 1, /**< RSA encryption scheme as specified in PKCS#1 v1.5                                                                          */
    ecy_hsm_CSAI_RSA_ES_OAEP         = 2, /**< RSA encryption scheme with Optimal Asymmetric Encryption Padding as specified in PKCS#1 v2.1 using SHA256 as hash function */
    ecy_hsm_CSAI_ECIES               = 3, /**< Elliptic Curve Integrated Encryption Scheme                                                                                */
    ecy_hsm_CSAI_SM2_PKE             = 4, /**< SM2 encryption scheme as specified in GB/T 32918.4-2016                                                                    */
    ecy_hsm_CSAI_RSA_ES_OAEP_SHA1    = 5, /**< RSA encryption scheme with Optimal Asymmetric Encryption Padding as specified in PKCS#1 v2.1 using SHA1 as hash function   */

    ecy_hsm_CSAI_ASYMCIPHER_RESERVED = 0x7fffffffu /**< Value defined to reserve the unsigned long memory for enums */
} ecy_hsm_Csai_AsymCipherModeT;

/** Define known auto padding modes supported by the HSM. */
typedef enum ecy_hsm_Csai_PaddingModeTag
{
    ecy_hsm_CSAI_PAD_NONE           = 1,                /**< HSM does not pad the message. Caller is
                                                             responsible for padding requirements, otherwise
                                                             an error occurs in the block operation.        */
    ecy_hsm_CSAI_PAD_PKCS7          = 2,                /**< HSM automatically pads the message using
                                                             padding specified in PKCS#7 v1.5 (RFC2315)
                                                             @details Only ECB and CBC support padding      */
    ecy_hsm_CSAI_PAD_NIST_SP800     = 3,                /**< HSM automatically pads the message using
                                                             padding specified in NIST SP800-38A
                                                             @details Only AES in ECB and CBC mode supports padding      */
    ecy_hsm_CSAI_PADDINGMODE_RESERVED = 0x7fffffffu     /**< Value defined to reserve the unsigned long memory for enums */
} ecy_hsm_Csai_PaddingModeT;

/**
 * Structure of extendable parameters for Asymmetric En/De-cryption using extendable CSAI.
 * This struct supports ECIES parameters configuration
 */
typedef struct ecy_hsm_Csai_AsymCrypt_ParamSet_V0Tag
{
    ecy_hsm_Csai_DhAlgorithmT   ecdhAlgorithm;      /**< Key Exchange Algorithms, support for each elliptic curves including P224, P256, and P384. */
    ecy_hsm_Csai_HashAlgorithmT hashAlgorithm;      /**< The hash algorithm is selected for KDF operation specified in ANSI X9.63 and
                                                         only SHA2_224, SHA2_256, SHA2_384, and SHA2_512 are supported.*/
    ecy_hsm_Csai_MACAlgorithmT  macAlgorithm;       /**< Message Authentication Code (MAC) Algorithms used by ECIES Asymmetric Crypt.
                                                         Only HMAC_SHA2_256, HMAC_SHA2_384 and HMAC_SHA2_512 are supported. */
    uint32                      macKeyLength;       /**< HMAC key length in bytes and supports up to corresponding MAC length. */
    ecy_hsm_Csai_SymCipherModeT symCipherMode;      /**< Advanced Encryption Standard (AES) and mode for symmetric block cipher encryption.
                                                         Only ecy_hsm_CSAI_AES_CBC is supported. */
    uint32                      cryptKeyLength;     /**< Length of the encryption/decryption key in bytes. AES key length
                                                         of 128 bit (16 bytes), and 256 bit (32 bytes) are supported. */
    boolean                     isPaddingPkcs7Used; /**< Apply PKCS7 padding scheme for ECIES encryption or not. */
} ecy_hsm_Csai_AsymCrypt_ParamSet_V0T;

/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_AsymDecrypt_ParamSetTag
{
    ecy_hsm_Csai_AsymCrypt_ParamSet_V0T paramV0;  /**< Data structure for Asymmetric Crypt Version 0 */
    /* add structs for each new versions here */
} ecy_hsm_Csai_AsymDecrypt_ParamSetT;

/** Union of extendable data structures. New structures for future parameters shall be added here. */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_AsymEncrypt_ParamSetTag
{
    ecy_hsm_Csai_AsymCrypt_ParamSet_V0T paramV0;  /**< Data structure for Asymmetric Crypt Version 0 */
    /* add structs for each new versions here */
} ecy_hsm_Csai_AsymEncrypt_ParamSetT;

/**
 * Enum for versioning the parameter set used by AsymCrypt CSAIs.
 * New IDs for future structures shall be added here.
 */
typedef enum ecy_hsm_Csai_AsymCrypt_ParamSetVersionTag
{
    ecy_hsm_CSAI_ASYM_CRYPT_V0,                   /**< Corresponds to the @c ecy_hsm_Csai_AsymCrypt_ParamSet_V0T data struct */
    ecy_hsm_CSAI_ASYM_CRYPT_MAX = 0x7FFFFFFFUL    /**< Value defined to use memory size of uint32 for enums                    */
} ecy_hsm_Csai_AsymCrypt_ParamSetVersionT;

/**
 * Structure of parameter set union and its version for ECIES encryption CSAI
 */
typedef struct ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionTag
{
    ecy_hsm_Csai_AsymCrypt_ParamSetVersionT   paramSetVersion;    /**< Version of the selected param set asymCryptParam */
    ecy_hsm_Csai_AsymEncrypt_ParamSetT       *pAsymEncryptParam;  /**< Pointer to the extendable parameter set for encryption */
} ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionT;

/**
 * Structure of parameter set union and its version for ECIES decryption CSAI
 */
typedef struct ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionTag
{
    ecy_hsm_Csai_AsymCrypt_ParamSetVersionT   paramSetVersion;    /**< Version of the selected param set asymCryptParam */
    ecy_hsm_Csai_AsymDecrypt_ParamSetT       *pAsymDecryptParam;  /**< Pointer to the extendable parameter set for decryption */
} ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_CSAI_SYMCIPHER_RESERVED
 */
#define CSAI_SYMCIPHER_RESERVED ecy_hsm_CSAI_SYMCIPHER_RESERVED
/**
 * @deprecated by @ref ecy_hsm_CSAI_PADDINGMODE_RESERVED
 */
#define CSAI_PADDINGMODE_RESERVED ecy_hsm_CSAI_PADDINGMODE_RESERVED

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/



/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_ENCRYPT_START
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 3005]
 * [$Satisfies $SW_ARCH 08322986]
 * Initialize and start a multi part or single shot encryption operation. The caller must
 * specify in which session context the job is to be executed, a cipher suite mode to use,
 * a handle to a key available to the session and a scheduling priority for the job on the
 * HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.  Note that the encrypted data may be up to 16 bytes longer than the clear text.
 *
 * @note
 * - Ensure that @c clearText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c cipherText resides in memory that is writeable by the HSM.
 *   Ensure that the scope of @c cipherText remains valid until either a call
 *   to @ref ecy_hsm_Csai_EncryptUpdate or @ref ecy_hsm_Csai_EncryptFinish returns @ref ecy_hsm_CSAI_SUCCESS
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the encryption operation with further message chunks using
 *      @ref ecy_hsm_Csai_EncryptUpdate.
 * - Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_EncryptFinish.
 *
 * @param[in]   hSession         Handle to the session in which to place the job.
 * @param[in]   priority         Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode       Cipher suite mode to use for the encryption operation.
 * @param[in]   paddingMode      Padding mode to use for the encryption operation.
 * @param[in]   hKey             Handle to a key available in the HSM's session context to
 *                               use for the encryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv               Array of data for the initialisation vector.
 * @param[in]   ivLength         Length of the IV data array
 * @param[in]   clearText        First chunk or entire message to encrypt.
 * @param[in]   clearTextLength  Length of the provided message or chunk.
 * @param[out]  cipherText       Pointer to space where the HSM can store the encrypted chunk.
 * @param[in]   cipherTextLength Length of the provided @c cipherText buffer.
 * @param[out]  pCipherTextCount Pointer to buffer to receive the number of bytes of cipher text written
 * @param[out]  phJob            Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property flags
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported or is combined with the given
 *                                                      padding mode unsupported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            ecy_hsm_Csai_SymCipherModeT cipherMode,
                                            ecy_hsm_Csai_PaddingModeT   paddingMode,
                                            ecy_hsm_Csai_KeyHandleT     hKey,
                                            const uint8                 iv[],
                                            uint32                      ivLength,
                                            const uint8                 clearText[],
                                            uint32                      clearTextLength,
                                            uint8                       cipherText[],
                                            uint32                      cipherTextLength,
                                            uint32*                     pCipherTextCount,
                                            ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ENCRYPT_UPDATE
 * @{
 */

/**
 * [$DD 3006]
 * [$Satisfies $SW_ARCH 5F22757F]
 * Update a running encryption job with another message chunk.
 * @details The number of bytes written to the cipherText buffer will be equal to
 *          clearTextLength rounded down to a multiple of sixteen.  Any final bytes
 *          or padding are written in @ref ecy_hsm_Csai_EncryptFinish call and the number of
 *          such bytes is returned from that call by pLastCipherTextCount.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy encrypting
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob                Handle to the started job
 * @param[in]   clearText           Next chunk or remainder of message to encrypt.
 * @param[in]   clearTextLength     Length of the provided message or chunk.
 * @param[out]  cipherText          Pointer to space where the HSM can store the encrypted chunk.
 * @param[in]   cipherTextLength    Length of the provided @c cipherText buffer.
 * @param[out]  pCipherTextCount    Pointer to buffer to receive the number of bytes of cipher text written
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_EncryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Update call has been made on a port with a job that is not started
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                             const uint8             clearText[],
                                             uint32                  clearTextLength,
                                             uint8                   cipherText[],
                                             uint32                  cipherTextLength,
                                             uint32*                 pCipherTextCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ENCRYPT_FINISH
 * @{
 */

/**
 * [$DD 3007]
 * [$Satisfies $SW_ARCH BE0C6559]
 * Finish an encryption operation.
 *
 * Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy
 * and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                 Handle to the initialized job
 * @param[out]  cipherText           Pointer to buffer where this function can write any residual data
 *                                   such as padding or final encrypted bytes
 * @param[in]   cipherTextLength     Length of the provided @c cipherText buffer
 * @param[out]  pCipherTextCount     Pointer to space, where this function can store
 *                                   the number of bytes written to the final block
 *
 * @note For encryption modes ECB, CBC and CFB128, if no padding is specified then @c cipherText may be
 *       @c NULL_PTR and @c cipherTextLength may be zero
 *
 * @note
 * - Multi-part mode:
 *      The caller may call this function again to provide additional message
 *      chunks.
 * - Finalization and result query:
 *      The caller finishes and polls for the last encrypted chunk of the encryption job
 *      using @ref ecy_hsm_Csai_EncryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Finish call has been made on a port with a job that is not started
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_EncryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                             uint8                   cipherText[],
                                             uint32                  cipherTextLength,
                                             uint32*                 pCipherTextCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ENCRYPT_ONESHOT
 * @{
 */

/**
 * [$DD 3008]
 * [$Satisfies $SW_ARCH 798976CE]
 * Initialize and perform an encryption operation.
 *
 * The caller must specify in which session context the job is to be executed, a cipher suite mode to use, padding mode,
 * a handle to a key available to the session and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length, result buffer plus and initialisation vector buffer
 * and its length. The caller also provides buffer to receive the number of bytes of cipher text written and a buffer to
 * store the number of bytes written to the final block.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should
 *       subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c JobHandle to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be encrypted.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_EncryptStart) if an update of the running job is required.
 *
 * @param[in]   hSession              Handle to the session in which to place the job.
 * @param[in]   priority              Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode            Cipher suite mode to use for the encryption operation.
 * @param[in]   paddingMode           Padding mode to use for the encryption operation.
 * @param[in]   hKey                  Handle to a key available in the HSM's session context to
 *                                    use for the encryption operation, OR a keyId
 * @param[in]   iv                    Array of data for the initialisation vector.
 * @param[in]   ivLength              Length of the IV data array
 * @param[in]   clearText             First chunk or entire message to encrypt.
 * @param[in]   clearTextLength       Length of the provided message or chunk.
 * @param[out]  cipherText            Pointer to space where the HSM can store the encrypted chunk.
 * @param[in]   cipherTextLength      Length of the provided @c cipherText buffer.
 * @param[out]  pCipherTextCount      Pointer to buffer to receive the number of bytes of cipher text written
 * @param[out]  phJob                 Handle to the initialized job
 *
 * @note For encryption modes ECB, CBC and CFB128, if no padding is specified then @c cipherText may be
 *       @c NULL_PTR and @c cipherTextLength may be zero
 *
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported or is combined with the given
 *                                                      padding mode unsupported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Encrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                       ecy_hsm_Csai_JobPriorityT   priority,
                                       ecy_hsm_Csai_SymCipherModeT cipherMode,
                                       ecy_hsm_Csai_PaddingModeT   paddingMode,
                                       ecy_hsm_Csai_KeyHandleT     hKey,
                                       const uint8                 iv[],
                                       uint32                      ivLength,
                                       const uint8                 clearText[],
                                       uint32                      clearTextLength,
                                       uint8                       cipherText[],
                                       uint32                      cipherTextLength,
                                       uint32*                     pCipherTextCount,
                                       ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_DECRYPT_START
 * @{
 */

/**
 * [$DD 3009]
 * [$Satisfies $SW_ARCH 3B2CCF3D]
 * Initialize and start a multi part or single shot decryption operation.
 * The caller must specify in which session context the job is to be executed, a cipher suite
 * mode to use, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 * @note
 * - Ensure that @c cipherText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c clearText resides in memory that is writeable by the HSM.
 *   Ensure that the scope of @c clearText remains valid until either a call
 *   to @ref ecy_hsm_Csai_DecryptUpdate or @ref ecy_hsm_Csai_DecryptFinish returns @ref ecy_hsm_CSAI_SUCCESS
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the decryption operation with further message chunks using
 *      @ref ecy_hsm_Csai_DecryptUpdate.
 * - Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_DecryptFinish.
 *
 * @param[in]   hSession         Handle to the session in which to place the job.
 * @param[in]   priority         Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode       Cipher suite mode to use for the decryption operation.
 * @param[in]   paddingMode      Padding mode to expect for the decryption operation.
 * @param[in]   hKey             Handle to a key available in the HSM's session context to
 *                               use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv               Array of data for the initialisation vector.
 * @param[in]   ivLength         Length of the IV data array in bytes
 * @param[in]   cipherText       First chunk or entire message to decrypt.
 * @param[in]   cipherTextLength Length of the provided message or chunk.
 * @param[out]  clearText        Pointer to space where the HSM can store the decrypted chunk.
 * @param[in]   clearTextLength  Length of the provided @c clearText buffer.  This should be equal to at least
 *                               cipherTextLength.
 * @param[out]  pClearTextCount  Pointer to buffer to receive the number of bytes of clear text written
 * @param[out]  phJob            Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported or is combined with the given
 *                                                      padding mode unsupported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not have
 *                                                      an open session
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            ecy_hsm_Csai_SymCipherModeT cipherMode,
                                            ecy_hsm_Csai_PaddingModeT   paddingMode,
                                            ecy_hsm_Csai_KeyHandleT     hKey,
                                            const uint8                 iv[],
                                            uint32                      ivLength,
                                            const uint8                 cipherText[],
                                            uint32                      cipherTextLength,
                                            uint8                       clearText[],
                                            uint32                      clearTextLength,
                                            uint32*                     pClearTextCount,
                                            ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_DECRYPT_UPDATE
 * @{
 */

/**
 * [$DD 3010]
 * [$Satisfies $SW_ARCH 2B1D6241]
 * Update a running decryption job with another message chunk.
 * @details The number of bytes written to the cipherText buffer will be equal to
 *          clearTextLength rounded down to a multiple of sixteen.  Any final bytes
 *          or padding are written in @ref ecy_hsm_Csai_DecryptFinish call and the number of
 *          such bytes is returned from that call by pLastClearTextCount.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy decrypting
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob                Handle to the started job
 * @param[in]   cipherText          Next chunk or remainder of message to decrypt.
 * @param[in]   cipherTextLength    Length of the provided message or chunk.
 * @param[out]  clearText           Pointer to space where the HSM can store the decrypted chunk.
 * @param[in]   clearTextLength     Length of the provided @c clearText buffer.  This should be equal to at least
 *                                  cipherTextLength.
 * @param[out]  pClearTextCount     Pointer to buffer to receive the number of bytes of clear text written
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_DecryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            update call has been made on a port with a job that is not started
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                             const uint8             cipherText[],
                                             uint32                  cipherTextLength,
                                             uint8                   clearText[],
                                             uint32                  clearTextLength,
                                             uint32*                 pClearTextCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_DECRYPT_FINISH
 * @{
 */

/**
 * [$DD 3011]
 * [$Satisfies $SW_ARCH B74E357F]
 * Finish a decryption operation and query the last chunk.
 *
 * @note
 * This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy decrypting
 * the previous chunk and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                 Handle to the running job
 * @param[out]  clearText            Pointer to buffer where this function can write any residual data
 *                                   such final decrypted bytes
 * @param[in]   clearTextLength      Length of the provided @c clearText buffer
 * @param[out]  pLastClearTextCount  Pointer to space, where this function can store the following:
 *                                   If paddingMode equals ecy_hsm_CSAI_PAD_PKCS7:
 *                                       The complete unpadded plaintext length.
 *                                   In all other cases:
 *                                       The number of bytes written to the clear text buffer.
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note For encryption modes ECB, CBC and CFB128 then @c clearText may be @c NULL_PTR
 *       and @c clearTextLength may be zero, there is never anything to append in these cases
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Finish call has been made on a port with a job that is not started.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DecryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                             uint8                   clearText[],
                                             uint32                  clearTextLength,
                                             uint32*                 pLastClearTextCount);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_DECRYPT_ONESHOT
 * @{
 */

/**
 * [$DD 3012]
 * [$Satisfies $SW_ARCH 979433AA]
 * Initialize and perform a decryption operation.
 * The caller must specify in which session context the job is to be executed, a cipher suite
 * mode to use, padding mode, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * The caller provides a buffer with the input data and its length, result buffer plus length and initialisation vector
 *  buffer
 * and its length. The caller also provides buffer to receive the number of bytes of cipher text written and a buffer to
 * store the number of bytes written to the final block.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should
 * subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c JobHandle to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be decrypted.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_DecryptStart) if an update of the running job is required.
 *
 * @param[in]   hSession             Handle to the session in which to place the job.
 * @param[in]   priority             Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode           Cipher suite mode to use for the decryption operation.
 * @param[in]   paddingMode          Padding mode to expect for the decryption operation.
 * @param[in]   hKey                 Handle to a key available in the HSM's session context to
 *                                   use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv                   Array of data for the initialisation vector.
 * @param[in]   ivLength             Length of the IV data array in bytes
 * @param[in]   cipherText           First chunk or entire message to decrypt.
 * @param[in]   cipherTextLength     Length of the provided message or chunk.
 * @param[out]  clearText            Pointer to space where the HSM can store the decrypted chunk.
 * @param[in]   clearTextLength      Length of the provided @c clearText buffer.  This should be equal to at least
 *                                   cipherTextLength.
 * @param[out]  pClearTextCount      Pointer to buffer to receive the number of bytes of clear text written
 * @param[out]  phJob                Receives the handle to the job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note For encryption modes ECB, CBC and CFB128 then @c clearText may be @c NULL_PTR
 *       and @c clearTextLength may be zero, there is never anything to append in these cases
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property flags
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported or is combined with the given
 *                                                      padding mode unsupported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not
 *                                                      have an open session
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Decrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                       ecy_hsm_Csai_JobPriorityT   priority,
                                       ecy_hsm_Csai_SymCipherModeT cipherMode,
                                       ecy_hsm_Csai_PaddingModeT   paddingMode,
                                       ecy_hsm_Csai_KeyHandleT     hKey,
                                       const uint8                 iv[],
                                       uint32                      ivLength,
                                       const uint8                 cipherText[],
                                       uint32                      cipherTextLength,
                                       uint8                       clearText[],
                                       uint32                      clearTextLength,
                                       uint32*                     pClearTextCount,
                                       ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_ENCRYPT_START
 * @{
 */

/**
 * [$DD 3013]
 * [$Satisfies $SW_ARCH F119D731]
 * Initialize and start a multi part or single shot authenticated encryption operation. The caller must
 * specify in which session context the job is to be executed, a cipher suite mode to use,
 * a handle to a key available to the session and a scheduling priority for the job on the
 * HSM.
 * In subsequent calls to CSA_AuthEncryptUpdate and ecy_hsm_Csai_EncryptUpdate, the user will supply
 * data to be authenticated and data to encrypted.  All the data for authentication must be provided before
 * the data for encryption.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the encryption operation with further message chunks using
 *      @ref ecy_hsm_Csai_AuthUpdate for data for authentication and @ref
 *      ecy_hsm_Csai_EncryptUpdate for data for encryption.
 * - Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_AuthEncryptFinish.
 *
 * @param[in]   hSession         Handle to the session in which to place the job.
 * @param[in]   priority         Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode       Cipher suite mode to use for the encryption operation.
 * @param[in]   paddingMode      Padding mode to use for the encryption operation.
 * @param[in]   hKey             Handle to a key available in the HSM's session context to
 *                               use for the encryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv               Array of data for the initialisation vector.
 * @param[in]   ivLength         Length of the IV data array, should be 12 bytes
 * @param[out]  phJob            Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not have
 *                                                      an open session
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_SymCipherModeT cipherMode,
                                                ecy_hsm_Csai_PaddingModeT   paddingMode,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                const uint8                 iv[],
                                                uint32                      ivLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_UPDATE
 * @{
 */

/**
 * [$DD 3014]
 * [$Satisfies $SW_ARCH BAE20081]
 * Update a running authenticated encryption or decryption job with another chunk of data for authentication.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy processing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob                Handle to the started job
 * @param[in]   aad                 Next chunk or remainder of data for authentication.
 * @param[in]   aadLength           Length of the provided message or chunk.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * @note
 * - Ensure that @c aad resides in MPU protected memory that is
 *   read-only to the HSM
 *
 * Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_AuthEncryptFinish or @ref ecy_hsm_Csai_AuthDecryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Update call has been made on a port with a job that is not started.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                          const uint8             aad[],
                                          uint32                  aadLength);

/**
 * [$DD 3015]
 * [$Satisfies $SW_ARCH F0A414C5]
 * Update a running authenticated decryption job with another chunk of data for authentication.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy processing
 * the previous chunk and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob                Handle to the started job
 * @param[in]   aad                 Next chunk or remainder of data for authentication.
 * @param[in]   aadLength           Length of the provided message or chunk.
 *
 * Multi-part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * @note
 * - Ensure that @c aad resides in MPU protected memory that is
 *   read-only to the HSM
 *
 * Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_AuthDecryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Update call has been made on a port with a job that is not started.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                 const uint8             aad[],
                                                 uint32                  aadLength);
/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_ENCRYPT_FINISH
 * @{
 */

/**
 * [$DD 3016]
 * [$Satisfies $SW_ARCH 6E8CE486]
 * Finish an authenticated encryption operation and get the authentication tag.
 *
 * Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy
 * and cannot provide the result yet. Try again later.
 *
 * @param[in] hJob                   Handle to the initialized job
 * @param[out] cipherText            Buffer to receive any residual cipher text
 * @param[in] cipherTextLength       Length of @c cipherText buffer
 * @param[out] pCipherTextCount      Pointer to space, where this function can store
 *                                   the number of bytes written to the final block
 * @param[out] pTag                  Pointer to buffer to receive the authentication tag data
 * @param[in] tagLength              Length of buffer for authentication tag data (should be at least 16 bytes)
 *
 * @note
 * - Multi-part mode:
 *      The caller may call this function again to provide additional message
 *      chunks.
 * - Finalization and result query:
 *      The caller finishes and polls for the last encrypted chunk of the encryption job
 *      using @ref ecy_hsm_Csai_AuthEncryptFinish.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Finish call has been made on a port with a job that is not started.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8                   cipherText[],
                                                 uint32                  cipherTextLength,
                                                 uint32*                 pCipherTextCount,
                                                 uint8*                  pTag,
                                                 uint32                  tagLength);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_ENCRYPT_ONESHOT
 * @{
 */

/**
 * [$DD 3017]
 * [$Satisfies $SW_ARCH FAD9A3B3]
 * Initialize and perform an authenticated encryption operation and get the authentication tag.
 *
 * The caller must specify in which session context the job is to be executed, a cipher suite mode to use,
 * a handle to a key available to the session and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length, residual cipher text buffer plus length and
 * initialization vector and length. The caller also provides the
 * a buffer for the count of the number of bytes written to the final block, result buffer and its length.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should
 *       subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c JobHandle to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be decrypted.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_AuthEncryptStart) if an update of the running job is required.
 *
 * @param[in]   hSession             Handle to the session in which to place the job.
 * @param[in]   priority             Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode           Cipher suite mode to use for the encryption operation.
 * @param[in]   paddingMode          Padding mode to use for the encryption operation.
 * @param[in]   hKey                 Handle to a key available in the HSM's session context to
 *                                   use for the encryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv                   Array of data for the initialisation vector.
 * @param[in]   ivLength             Length of the IV data array, should be 12 bytes
 * @param[in]   aad                  data for authentication.
 * @param[in]   aadLength            Length of data for authentication.
 * @param[in]   plainText            Pointer to plain text for encryption.
 * @param[in]   plainTextLength      Length of the plain text in bytes.
 * @param[out]  cipherText           Pointer to buffer to the cipher text.
 * @param[in]   cipherTextLength     Length of @c cipherText buffer.
 * @param[out]  pCipherTextCount     Pointer to space, where this function can store
 *                                   the number of bytes of cipherText written.
 * @param[out]  pTag                 Pointer to buffer to receive the authentication tag data
 * @param[in]   tagLength            Length of buffer for authentication tag data (should be at least 16 bytes)
 * @param[out]  phJob                Receives the handle to the job.
 *
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not have
 *                                                      an open session
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthEncrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           ecy_hsm_Csai_SymCipherModeT cipherMode,
                                           ecy_hsm_Csai_PaddingModeT   paddingMode,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           const uint8                 iv[],
                                           uint32                      ivLength,
                                           const uint8                 aad[],
                                           uint32                      aadLength,
                                           const uint8                 plainText[],
                                           uint32                      plainTextLength,
                                           uint8                       cipherText[],
                                           uint32                      cipherTextLength,
                                           uint32*                     pCipherTextCount,
                                           uint8*                      pTag,
                                           uint32                      tagLength,
                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_DECRYPT_START
 * @{
 */

/**
 * [$DD 3018]
 * [$Satisfies $SW_ARCH 4A34F15C]
 * Initialize and start a multi part or single shot authenticated decryption operation.
 * The caller must specify in which session context the job is to be executed, a cipher suite
 * mode to use, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the decryption operation with further message chunks using
 *      @ref ecy_hsm_Csai_DecryptUpdate.
 * - Finalization and result query:
 *      The caller finishes and requests any final operations (such as padding) using
 *      @ref ecy_hsm_Csai_AuthDecryptFinish.
 *
 * @param[in]   hSession         Handle to the session in which to place the job.
 * @param[in]   priority         Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode       Cipher suite mode to use for the decryption operation.
 * @param[in]   paddingMode      Padding mode to expect for the decryption operation.
 * @param[in]   hKey             Handle to a key available in the HSM's session context to
 *                               use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv               Array of data for the initialisation vector.
 * @param[in]   ivLength         Length of the IV data array in bytes, should be 12 bytes
 * @param[out]  phJob            Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not have
 *                                                      an open session
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_SymCipherModeT cipherMode,
                                                ecy_hsm_Csai_PaddingModeT   paddingMode,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                const uint8                 iv[],
                                                uint32                      ivLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_DECRYPT_FINISH
 * @{
 */

/**
 * [$DD 3019]
 * [$Satisfies $SW_ARCH 2019DB02]
 * Finish an authenticated decryption operation and get the authentication tag.
 *
 * @note
 * This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy decrypting
 * the previous chunk and cannot provide the result yet. Try again later.
 *
 * @param[in]  hJob                 Handle to the running job
 * @param[out] clearText            Buffer to receive any residual clear text
 * @param[in]  clearTextLength      Length of @c clearText buffer
 * @param[out] pLastClearTextCount Pointer to space, where this function can store
 *                                  the number of bytes written to the clear text buffer.
 * @param[out] pTag                 Pointer to buffer to receive the authentication tag data
 * @param[in] tagLength             Length of buffer for authentication tag data (should be at least 16 bytes)
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            Finish call has been made on a port with a job that is not started.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecryptFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8                   clearText[],
                                                 uint32                  clearTextLength,
                                                 uint32*                 pLastClearTextCount,
                                                 uint8*                  pTag,
                                                 uint32                  tagLength);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_AUTH_DECRYPT
 * @{
 */

/**
 * [$DD 3020]
 * [$Satisfies $SW_ARCH 1906229E]
 * Initialize and perform an authenticated decryption operation and get the authentication tag.
 * The caller must specify in which session context the job is to be executed, a cipher suite mode to use,
 * a handle to a key available to the session and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length, residual clear text buffer plus length and
 * initialization vector and length. The caller also provides the
 * a buffer for the count of the number of bytes written to the final block, result buffer and its length.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should
 * subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c JobHandle to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be decrypted.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_AuthDecryptStart) if an update of the running job is required.
 *
 * @param[in]   hSession             Handle to the session in which to place the job.
 * @param[in]   priority             Requested scheduling priority for this job on the HSM.
 * @note
 * Asymmetric operations using will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   cipherMode           Cipher suite mode to use for the decryption operation.
 * @param[in]   paddingMode          Padding mode to expect for the decryption operation.
 * @param[in]   hKey                 Handle to a key available in the HSM's session context to
 *                                   use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   iv                   Array of data for the initialisation vector.
 * @param[in]   ivLength             Length of the IV data array in bytes, should be 12 bytes
 * @param[in]   aad                  Pointer to data for authentication.
 * @param[in]   aadLength            Length of the data for authentication.
 * @param[in]  cipherText           Pointer to cipher text for decryption.
 * @param[in]   cipherTextLength     Length of cipher text for decryption.
 * @param[out]  clearText            Buffer to receive any residual clear text
 * @param[in]   clearTextLength      Length of @c clearText buffer
 * @param[out]  pClearTextCount      Pointer to space, where this function can store
 *                                   the number of bytes written to the clear text buffer.
 * @param[out]  pTag                 Pointer to buffer to receive the authentication tag data
 * @param[in]   tagLength            Length of buffer for authentication tag data (should be at least 16 bytes)
 * @param[out]  phJob                Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              One of the given parameter of the call is wrong, invalid or out of
 *                                                      range.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED   The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_IV_LENGTH_NOT_SUPPORTED    The supplied IV length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its property
 *                                                      flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET     The parameters are inconsistent, e.g. the chosen cipher mode
 *                                                      and padding mode are incompatible.
 *   - @ref ecy_hsm_CSAI_ERR_UPDATE_BLOCK_SIZE          The given input or output size do not fit the semantic
 *                                                      requirements for this operation, e.g. the chosen cipher
 *                                                      mode operation requires a multiple of the key size to
 *                                                      operate.
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             A job or operation request has been made on a port which does not
 *                                                      have an open session
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AuthDecrypt(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           ecy_hsm_Csai_SymCipherModeT cipherMode,
                                           ecy_hsm_Csai_PaddingModeT   paddingMode,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           const uint8                 iv[],
                                           uint32                      ivLength,
                                           const uint8                 aad[],
                                           uint32                      aadLength,
                                           const uint8                 cipherText[],
                                           uint32                      cipherTextLength,
                                           uint8                       clearText[],
                                           uint32                      clearTextLength,
                                           uint32*                     pClearTextCount,
                                           uint8*                      pTag,
                                           uint32                      tagLength,
                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ASYM_ENCRYPT
 * @{
 */

/**
 * [$DD 2262]
 * [$Satisfies $SW_ARCH 936] [$Satisfies $SW_ARCH 958] [$Satisfies $SW_ARCH 959] [$Satisfies $ARCH 930] [$Satisfies $ARCH 932] [$Satisfies $ARCH 934]

 * Perform a single shot asymmetric encryption operation. The caller must specify in which session context
 * the job is to be executed, a cipher suite mode to use, a handle to a key available to the
 * session and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 * @note
 * - Ensure that @c clearText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c cipherText resides in memory that is writeable by the HSM.
 *
 * @param[in]   hSession          Handle to the session in which to place the job.
 * @param[in]   priority          Requested scheduling priority for this job on the HSM.
 *                                @note Operation will always be executed on background priority.
 *                                      Parameter will be overridden by implementation.
 * @param[in]   cipherMode        Cipher suite mode to use for the encryption operation.
 * @param[in]   hKey              Handle to a key available in the HSM's session context to
 *                                use for the encryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   clearText         First chunk or entire message to encrypt.
 * @param[in]   clearTextLength   Length of the provided message or chunk.
 * @param[out]  cipherText        Pointer to space where the HSM can store the encrypted chunk.
 * @param[in]   cipherTextLength  Length of the provided @c cipherText buffer.
 * @param[out]  pCipherTextCount  Pointer to space, where the function can store how
 *                                many bytes have been written to the cipher buffer
 *                                provided here.
 * @param[out]  phJob             Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE            The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED  The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION    There has been an attempt to use a key in violation of its
 *                                                     property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL          The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                  An error has been returned by CycurLib.
 *   - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE           The given clear text length is larger than the supported length.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymEncrypt(ecy_hsm_Csai_SessionHandleT  hSession,
                                           ecy_hsm_Csai_JobPriorityT    priority,
                                           ecy_hsm_Csai_AsymCipherModeT cipherMode,
                                           ecy_hsm_Csai_KeyHandleT      hKey,
                                           const uint8                  clearText[],
                                           uint32                       clearTextLength,
                                           uint8                        cipherText[],
                                           uint32                       cipherTextLength,
                                           uint32*                      pCipherTextCount,
                                           ecy_hsm_Csai_JobHandleT*     phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ASYM_ENCRYPT_EXTENDED
 * @{
 */

/**
 * [$DD 2263]
 * [$Satisfies $SW_ARCH 936] [$Satisfies $SW_ARCH 958] [$Satisfies $ARCH 930] [$Satisfies $ARCH 932] [$Satisfies $ARCH 934]
 *
 * Perform a single shot asymmetric encryption operation, using extendable
 * set of parameters. The caller must specify in which session context
 * the job is to be executed, a cipher suite mode to use, a handle to a key available to the
 * session and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionT structure which contains
 * additional parameters related to Asymmetric Encryption. These can be extended in the future
 * by incrementing the paramSetVersion and adding new structures to the @c ecy_hsm_Csai_AsymEncrypt_ParamSetT union.
 *
 * @note
 * - Ensure that @c clearText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c cipherText resides in memory that is writeable by the HSM.
 *
 * @param[in]   hSession                          Handle to the session in which to place the job.
 * @param[in]   priority                          Requested scheduling priority for this job on the HSM.
 *                                                @note Operation will always be executed on background priority.
 *                                                      Parameter will be overridden by implementation.
 * @param[in]   cipherMode                        Cipher suite mode to use for the encryption operation.
 * @param[in]   pAsymEncryptParamSetAndVersion    Pointer to the extendable parameter sets and their corresponding version.
 * @param[in]   hKey                              Handle to a key available in the HSM's session context to
 *                                                use for the encryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   clearText                         First chunk or entire message to encrypt.
 * @param[in]   clearTextLength                   Length of the provided message or chunk.
 * @param[out]  cipherText                        Pointer to space where the HSM can store the encrypted chunk.
 *                                                ECIES encryption will return cipher text which includes
 *                                                ephemeral public key, encrypted msg and MAC tag
 * @param[in]   cipherTextLength                  Length of the provided @c cipherText buffer for ECIES is at least
 *                                                (pLength + public key length + MAC tag length + padding) in bytes.
 * @param[out]  pCipherTextCount                  Pointer to space, where the function can store how
 *                                                many bytes have been written to the cipher buffer
 *                                                provided here.
 * @param[out]  phJob                             Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE            The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED  The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION    There has been an attempt to use a key in violation of its
 *                                                     property flags
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL          The given output buffer is too small.
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                  An error has been returned by CycurLib.
 *   - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE           The given clear text length is larger than the supported length.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymEncryptExtend(ecy_hsm_Csai_SessionHandleT                      hSession,
                                                 ecy_hsm_Csai_JobPriorityT                        priority,
                                                 ecy_hsm_Csai_AsymCipherModeT                     cipherMode,
                                                 ecy_hsm_Csai_AsymEncryptExt_ParamSetAndVersionT* pAsymEncryptParamSetAndVersion,
                                                 ecy_hsm_Csai_KeyHandleT                          hKey,
                                                 const uint8                                      clearText[],
                                                 uint32                                           clearTextLength,
                                                 uint8                                            cipherText[],
                                                 uint32                                           cipherTextLength,
                                                 uint32*                                          pCipherTextCount,
                                                 ecy_hsm_Csai_JobHandleT*                         phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_ASYM_DECRYPT
 * @{
 */

/**
 * [$DD 2264]
 * [$Satisfies $SW_ARCH 937] [$Satisfies $SW_ARCH 959] [$Satisfies $ARCH 939] [$Satisfies $ARCH 931] [$Satisfies $ARCH 933] [$Satisfies $ARCH 935]
 *
 * Perform a single shot decryption operation.
 * The caller must specify in which session context the job is to be executed, a cipher suite
 * mode to use, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 * @note
 * - Ensure that @c cipherText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c clearText resides in memory that is writeable by the HSM.
 *
 * @param[in]   hSession          Handle to the session in which to place the job.
 * @param[in]   priority          Requested scheduling priority for this job on the HSM.
 *                                @note Operation will always be executed on background priority.
 *                                      Parameter will be overridden by implementation.
 * @param[in]   cipherMode        Cipher suite mode to use for the decryption operation.
 * @param[in]   hKey              Handle to a key available in the HSM's session context to
 *                                use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   cipherText        First chunk or entire message to decrypt.
 * @param[in]   cipherTextLength  Length of the provided message or chunk.
 * @param[out]  clearText         Pointer to space where the HSM can store the decrypted chunk.
 * @param[in]   clearTextLength   Length of the provided @c clearText buffer.
 * @param[out]  pClearTextCount   Pointer to space, where the function can store how
 *                                many bytes have been written to the cleartext buffer
 *                                provided here.
 * @param[out]  phJob             Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE            The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION    There has been an attempt to use a key in violation of its
 *                                                     property flags
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED  The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                  An error has been returned by CycurLib
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL          The given output buffer is too small.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymDecrypt(ecy_hsm_Csai_SessionHandleT  hSession,
                                           ecy_hsm_Csai_JobPriorityT    priority,
                                           ecy_hsm_Csai_AsymCipherModeT cipherMode,
                                           ecy_hsm_Csai_KeyHandleT      hKey,
                                           const uint8                  cipherText[],
                                           uint32                       cipherTextLength,
                                           uint8                        clearText[],
                                           uint32                       clearTextLength,
                                           uint32*                      pClearTextCount,
                                           ecy_hsm_Csai_JobHandleT*     phJob);

/** @} */ // GROUP_CSAI_ASYM_DECRYPT

/**
 * @addtogroup GROUP_CSAI_ASYM_DECRYPT_EXTENDED
 * @{
 */

/**
 * [$DD 2265]
 * [$Satisfies $SW_ARCH 937] [$Satisfies $SW_ARCH 959] [$Satisfies $ARCH 939] [$Satisfies $ARCH 931] [$Satisfies $ARCH 933] [$Satisfies $ARCH 935]
 *
 * Perform a single shot decryption operation, using extendable set of parameters.
 * The caller must specify in which session context the job is to be executed, a cipher suite
 * mode to use, a handle to a key available to the session and a scheduling priority for the
 * job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus
 * length. This function does not block but immediately returns when the job is queued on the
 * HSM.
 *
 * The function uses a pointer to @c ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionT structure which contains
 * additional parameters related to Asymmetric Decryption. These can be extended in the future
 * by incrementing the paramSetVersion and adding new structures to the @c ecy_hsm_Csai_AsymDecrypt_ParamSetT union.
 *
 * @note
 * - Ensure that @c cipherText resides in MPU protected memory that is
 *   read-only to the HSM
 * - Ensure that @c clearText resides in memory that is writeable by the HSM.
 *
 * @param[in]   hSession                          Handle to the session in which to place the job.
 * @param[in]   priority                          Requested scheduling priority for this job on the HSM.
 *                                                @note Operation will always be executed on background priority.
 *                                                      Parameter will be overridden by implementation.
 * @param[in]   cipherMode                        Cipher suite mode to use for the decryption operation.
 * @param[in]   pAsymDecryptParamSetAndVersion    Pointer to the extendable parameter sets and their corresponding version.
 * @param[in]   hKey                              Handle to a key available in the HSM's session context to
 *                                                use for the decryption operation, OR a key ID.
 * @note Valid key IDs depend on the value of the <code>cipherMode</code> parameter.
 *       All available key IDs are listed in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   cipherText                        First chunk or entire message to decrypt. ECIES cipher text includes
 *                                                ephemeral public key, encrypted msg and MAC tag
 * @param[in]   cipherTextLength                  Length of the provided @c cipherText buffer for ECIES is at least
 *                                                (pLength + public key length + MAC tag length + padding) in bytes.
 * @param[out]  clearText                         Pointer to space where the HSM can store the decrypted chunk.
 * @param[in]   clearTextLength                   Length of the provided @c clearText buffer.
 * @param[out]  pClearTextCount                   Pointer to space, where the function can store how
 *                                                many bytes have been written to the cleartext buffer
 *                                                provided here.
 * @param[out]  phJob                             Receives the handle to the started job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given session handle was invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                       Another job is still pending completion in this session.
 *                                                     Either finish the previous job or cancel the running job
 *                                                     using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            The given key handle was invalid.
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE            The given key type is wrong for the chosen operation.
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION    There has been an attempt to use a key in violation of its
 *                                                     property flags
 *   - @ref ecy_hsm_CSAI_ERR_KEY_LENGTH_NOT_SUPPORTED  The supplied key length is not supported
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED             The given cipher mode is not supported by this HSM build.
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                  An error has been returned by CycurLib
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL          The given output buffer is too small.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_AsymDecryptExtend(ecy_hsm_Csai_SessionHandleT                      hSession,
                                                 ecy_hsm_Csai_JobPriorityT                        priority,
                                                 ecy_hsm_Csai_AsymCipherModeT                     cipherMode,
                                                 ecy_hsm_Csai_AsymDecryptExt_ParamSetAndVersionT* pAsymDecryptParamSetAndVersion,
                                                 ecy_hsm_Csai_KeyHandleT                          hKey,
                                                 const uint8                                      cipherText[],
                                                 uint32                                           cipherTextLength,
                                                 uint8                                            clearText[],
                                                 uint32                                           clearTextLength,
                                                 uint32*                                          pClearTextCount,
                                                 ecy_hsm_Csai_JobHandleT*                         phJob);

/** @} */ // GROUP_CSAI_ASYM_DECRYPT_EXTENDED

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_CSAI_CRYPT

#endif /* Multiple inclusion lock  */

