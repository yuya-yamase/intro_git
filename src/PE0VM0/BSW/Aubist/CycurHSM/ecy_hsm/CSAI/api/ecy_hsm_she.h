/**
 * @file
 ***********************************************************************************************
 * @brief SHE (+) command interface.
 * This header file is part of the CycurHSM's Secure Hardware Extensions command interface
 * and specifies types and functions for interfacing with the SHE emulation in the HSM.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CYCURHSM_SHE_H
#define ECY_HSM_CYCURHSM_SHE_H

/**
 * @defgroup GROUP_SHE CycurHSM SHE emulation Application Programming Interface
 * @addtogroup GROUP_SHE
 * @{
 *   @defgroup GROUP_SHE_PRIVATE SHE Host internal functions
 */

/* *** includes *******************************************************************************/

#include "Std_Types.h"
#include "ecy_hsm_service.h"

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"
/**
 * [$DD 2426]
 * [$Satisfies $ARCH 652] [$Satisfies $ARCH 640]
 * @brief
 * Start the SHE session.
 *
 * The session may remain open for the duration of the ECU run
 * time, but it does occupy a session which could otherwise be used for CSAI calls.
 * This call waits for the session to be opened and does not need to be synchronized.
 *
 * Any subsequent call to this function, without prior execution of @ref SHE_DeInit(),
 * will return an error because the session is already open.
 *
 * @return
 * - @ref ERC_NO_ERROR          No error
 * - @ref ERC_GENERAL_ERROR     Other error
 * - @ref ERC_SEQUENCE_ERROR    Session already open
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_Init(void);

/**
 * [$DD 2427]
 * [$Satisfies $ARCH 653]
 * @brief
 * Close the SHE session.
 *
 * This call waits for the session to be closed and does not need to be synchronized.
 *
 * @return
 * - @ref ERC_NO_ERROR          No error
 * - @ref ERC_GENERAL_ERROR     Other error
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_DeInit(void);

/**
 * [$DD 2428]
 * [$Satisfies $ARCH 621][$Satisfies $ARCH 643]
 * @brief
 * Perform an ECB encryption.
 *
 * This function can process exactly 128 bits.
 * SHE does not pad, so it is in the caller's responsibility to pad properly.
 *
 * @note Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 * @ref SHE_Sync() must be called at least once to complete the sequence, but it may
 * be called more often than that. @ref SHE_Sync() returns @ref ERC_BUSY while the
 * function is in progress.
 *
 * @param[in]   keyId            Identifies the key to use.
 * @param[in]   pPlainText       Pointer to the plaintext buffer, must be @c n * 128 bits long,
 *                               where @c n is a natural number >= 1.
 * @param[in]   plainTextLength  Length of the @c plaintext buffer provided with this call in @b bits.
 * @param[out]  pCipherText      Pointer to caller provided space, where this function can
 *                               store the plain text result. The length of the provided buffer
 *                               must be large enough to hold @c plainTextLength bits.
 * @param[in]   cipherTextSize   Size of the cipherText buffer in @b bits, must be greater than or equal to
 *                               plainTextLength.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_EncryptEcb(SHE_KeyIdT  keyId,
                                           const uint8 pPlainText[SHE_AES_BLOCK_SIZE_BYTES],
                                           uint32      plainTextLength,
                                           uint8       pCipherText[SHE_AES_BLOCK_SIZE_BYTES],
                                           uint32      cipherTextSize);

/**
 * [$DD 2429]
 * [$Satisfies $ARCH 621][$Satisfies $ARCH 643]
 * @brief
 * Perform an ECB decryption.
 *
 * This function can process exactly 128 bits.
 * SHE does not pad, so it is in the caller's responsibility to pad properly.
 *
 * @note Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 * @ref SHE_Sync() must be called at least once to complete the sequence, but it may
 * be called more often than that. @ref SHE_Sync() returns @ref ERC_BUSY while the
 * function is in progress.
 *
 * @param[in]   keyId       Identifies the key to use.
 * @param[in]   cipherText      Pointer to the ciphertext buffer, must be @c n * 128 bits long,
 *                              where @c n is a natural number >= 1.
 * @param[in]   cipherTextLength Length of the @c ciphertext buffer provided with this call in @b bits.
 * @param[out]  plainText       Pointer to caller provided space,
 *                              where this function can store the plain text result.
 *                              The length of the provided buffer must be large enough to hold
 *                              @c cipherTextLength bits.
 * @param[in]   plainTextSize   Size of the plainText buffer in @b bits, must be greater than or equal to
 *                              cipherTextLength.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_DecryptEcb(SHE_KeyIdT  keyId,
                                           const uint8 cipherText[SHE_AES_BLOCK_SIZE_BYTES],
                                           uint32      cipherTextLength,
                                           uint8       plainText[SHE_AES_BLOCK_SIZE_BYTES],
                                           uint32      plainTextSize);

/**
 * [$DD 2430]
 * [$Satisfies $ARCH 621][$Satisfies $ARCH 643]
 * @brief
 * Perform a CBC encryption.
 *
 * SHE does not pad, thus a chunk must be a multiple of the supported block width,
 * 128 bits. It is the caller's duty to pad properly.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   keyId            Identifies the key to use.
 * @param[in]   iv               Sixteen byte array for the initialisation vector
 * @param[in]   plainText        Pointer to the plaintext buffer, must be @c n * 128 bits long,
 *                               where @c n is a natural number >= 1.
 * @param[in]   plainTextLength  Length of the @c plaintext buffer provided with this call in @b bits.
 * @param[out]  cipherText       Pointer to caller provided space, where this function can
 *                               store the plain text result. The length of the provided buffer
 *                               must be large enough to hold @c plainTextLength bits.
 * @param[in]   cipherTextSize   Size of the cipherText buffer in @b bits, must be greater than or equal to
 *                               plainTextLength.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_EncryptCbc(SHE_KeyIdT   keyId,
                                           const uint8  iv[SHE_AES_BLOCK_SIZE_BYTES],
                                           const uint8* plainText,
                                           uint32       plainTextLength,
                                           uint8*       cipherText,
                                           uint32       cipherTextSize);

/**
 * [$DD 2431]
 * [$Satisfies $ARCH 621][$Satisfies $ARCH 643]
 * @brief
 * Perform a CBC decryption.
 *
 * SHE does not pad, thus a chunk must be a multiple of the supported block width,
 * 128 bits. It is the caller's duty to pad properly.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   keyId           Identifies the key to use.
 * @param[in]   iv               Sixteen byte array for the initialisation vector
 * @param[in]   cipherText      Pointer to the ciphertext buffer, must be @c n * 128 bits long,
 *                              where @c n is a natural number >= 1.
 * @param[in]   cipherTextLength Length of the @c ciphertext buffer provided with this call in @b bits.
 * @param[out]  plainText       Pointer to caller provided space,
 *                              where this function can store the plain text result.
 *                              The length of the provided buffer must be large enough to hold
 *                              @c cipherTextLength bits.
 * @param[in]   plainTextSize   Size of the plainText buffer in @b bits, must be greater than or equal to
 *                              cipherTextLength.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_DecryptCbc(SHE_KeyIdT   keyId,
                                           const uint8  iv[SHE_AES_BLOCK_SIZE_BYTES],
                                           const uint8* cipherText,
                                           uint32       cipherTextLength,
                                           uint8*       plainText,
                                           uint32       plainTextSize);
/**
 * [$DD 2432]
 * [$Satisfies $ARCH 622][$Satisfies $ARCH 643][$Satisfies $ARCH 649]
 * @brief
 * Performs a MAC generation.
 *
 * SHE does not pad, thus a chunk must be a multiple of the supported block width,
 * 128 bits. It is the caller's duty to pad properly.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   keyId       Identifies the key to use.
 * @param[in]   msg         Entire message to MAC.
 * @param[in]   msgLength   Length of the @c message buffer provided with this call in @b bits.
 *                          Must be a multiple of eight.
 * @param[out]  mac         Pointer to 128 bits of caller provided space,
 *                          where this function can store the MAC.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_GenerateMAC(SHE_KeyIdT keyId, const uint8* msg, uint32 msgLength, uint8 mac[SHE_AES_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2433]
 * @brief
 * Performs a MAC verification.
 * [$Satisfies $ARCH 622] [$Satisfies $ARCH 643] [$Satisfies $ARCH 649]
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   keyId       Identifies the key to use.
 * @param[in]   msg         Entire message to MAC.
 * @param[in]   msgLength   Length in @b bits of the @c message buffer provided with this call.
 *                          Must be a multiple of eight.
 * @param[in]   mac         Caller provided MAC to verify
 * @param[in]   macLength   The number of bits to compare, started from the leftmost bit
 *                          of the MAC, given in parameter MAC_LENGTH. The value 0 is not
 *                          allowed and is interpreted by SHE as to compare all bits of the
 *                          MAC.
 * @param[out]  pVerificationStatus  Pointer to space where this function can store the verification result.
 *                                   Value of 0 means MAC verification successful and
 *                                   value of 1 means MAC verification failed.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_VerifyMAC(SHE_KeyIdT   keyId,
                                          const uint8* msg,
                                          uint32       msgLength,
                                          const uint8  mac[SHE_AES_BLOCK_SIZE_BYTES],
                                          uint32       macLength,
                                          uint32*      pVerificationStatus);

/**
 * [$DD 2434]
 * [$Satisfies $ARCH 618] [$Satisfies $ARCH 609] [$Satisfies $ARCH 616]
 * @brief
 * This function updates an internal key of SHE with the protocol described in chapter 9
 * of the SHE specification.
 *
 * This function is for the MASTER_ECU_KEY, BOOT_MAC_KEY, BOOT_MAC and
 * KEY_1 to KEY_10. For KEY_11 to KEY_20 see @ref SHE_LoadKeyExtended.
 * For further extended keys, see @ref SHE_LoadKeyToBank.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   m1  see SHE specification
 * @param[in]   m2  see SHE specification
 * @param[in]   m3  see SHE specification
 * @param[out]  m4  see SHE specification
 * @param[out]  m5  see SHE specification
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_LoadKey(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                        const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                        const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                        uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                                        uint8       m5[SHE_M5_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2435]
 * [$Satisfies $ARCH 644] [$Satisfies $ARCH 646] [$Satisfies $ARCH 661]
 * @brief
 * This function updates an extended internal key (KEY_11 to KEY_20) of SHE with
 * the protocol described in chapter 9 of the SHE specification.
 *
 * The id of the key for update embedded in M1 has ten added to it, so specifying a
 * keyId with a numerical value of 4 (normally KEY_1) would result in an update of KEY_11.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   m1  see SHE specification
 * @param[in]   m2  see SHE specification
 * @param[in]   m3  see SHE specification
 * @param[out]  m4  see SHE specification
 * @param[out]  m5  see SHE specification
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_LoadKeyExtended(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                                const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                                const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                                uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                                                uint8       m5[SHE_M5_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2436]
 * [$Satisfies $ARCH 644] [$Satisfies $ARCH 646] [$Satisfies $ARCH 661]
 * @brief
 * This function updates a further extended internal key of SHE with the protocol described in chapter 9
 * of the specification and initially in CYS2200.
 *
 * This function is for any of the general keys in accordance with additional key slot requirements where
 * keys exist in numbered banks of ten keys, described initially by CYS2200.
 * E.g. under CYS2200, five banks of ten keys exist, with indexes 0-4 to access keys 1-10, 11-20, 21-30, 31-40
 * and 41-50 respectively. Specifying a keyId with a numerical value of 4 (i.e. KEY_1) and a bank index
 * of 4 would result in an update of KEY_41.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   m1          Message M1 as described in the SHE specification.
 * @param[in]   m2          Message M2 as described in the SHE specification.
 * @param[in]   m3          Message M3 as described in the SHE specification.
 * @param[out]  m4          Message M4 as described in the SHE specification.
 * @param[out]  m5          Message M5 as described in the SHE specification.
 * @param[in]   bankIndex   Key bank index as initially described by CYS2200 specification, if updating a general purpose key (ignored otherwise).
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_LoadKeyToBank(const uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                              const uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                              const uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                              uint8       m4[SHE_M4_BLOCK_SIZE_BYTES],
                                              uint8       m5[SHE_M5_BLOCK_SIZE_BYTES],
                                              uint32      bankIndex);

/**
 * [$DD 2437]
 * [$Satisfies $ARCH 624]
 * @brief
 * Loads a plain text key without verification and without encryption.
 *
 * The provided key is always loaded to the @ref RAM_KEY.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   key  Sixteen bytes of plain key data
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_LoadPlainKey( const uint8 key[SHE_AES_BLOCK_SIZE_BYTES] );

/**
 * [$DD 2438]
 * [$Satisfies $ARCH 641]
 * @brief
 * Export the @ref RAM_KEY from the SHE module in a format that was protected by @ref
 * SECRET_KEY.
 *
 * The key can later be imported again using @ref SHE_LoadKey().
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[out]   m1  see SHE specification
 * @param[out]   m2  see SHE specification
 * @param[out]   m3  see SHE specification
 * @param[out]   m4  see SHE specification
 * @param[out]   m5  see SHE specification
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_ExportRAMKey(uint8 m1[SHE_M1_BLOCK_SIZE_BYTES],
                                             uint8 m2[SHE_M2_BLOCK_SIZE_BYTES],
                                             uint8 m3[SHE_M3_BLOCK_SIZE_BYTES],
                                             uint8 m4[SHE_M4_BLOCK_SIZE_BYTES],
                                             uint8 m5[SHE_M5_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2439]
 * [$Satisfies $ARCH 651]
 * @brief
 * Sets the bit for RND_INIT in the SHE status register.
 * (HSM TRNG and PRNG require no special initialization.)
 *
 * @note
 * CycurHSM securely initializes its internal PRNG with seeds from a
 * high entropy TRNG peripheral.
 *
 * @return
 * - @ref ERC_NO_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_InitRNG(void);

/**
 * [$DD 2440]
 * [$Satisfies $ARCH 619]
 * @brief
 * Extend the seed of the PRNG with the caller supplied entropy.
 *
 * @details As the HSM uses a high quality TRNG for the PRNG seed, the entropy provided to this
 * function is ignored.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]   entropy     Caller provided entropy
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_ExtendSeed(const uint8 entropy[SHE_AES_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2441]
 * [$Satisfies $ARCH 620]
 * @brief
 * Start the generation of a vector of 128 bits random data.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[out] buffer  Pointer to space where this function can store the generated data.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_Rnd( uint8 buffer[SHE_AES_BLOCK_SIZE_BYTES] );

/**
 * [$DD 2442]
 * [$Satisfies $ARCH 639][$Satisfies $ARCH 643]
 * @brief
 * Start the secure boot process.
 *
 * This functionality is only available when Secure Boot is supported by the HSM,
 * otherwise it returns @ref ERC_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in] size Length of FLASH block to protect with BOOT_MAC and BOOT_MAC_KEY
 * @param[in] data Pointer start of FLASH block to protect with BOOT_MAC and BOOT_MAC_KEY
 *
 * @return
 * - @ref ERC_NO_SECURE_BOOT
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_SecureBoot(uint32 size, const uint8* data);

/**
 * [$DD 2461]
 * @brief
 * Mark the secure boot process as failed.
 * [$Satisfies $ARCH 639]
 *
 * This function is not reversible before the next power cycle. This functionality
 * is only available when Secure Boot is supported by the HSM, otherwise it returns
 * @ref ERC_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @return
 * - @ref ERC_NO_SECURE_BOOT
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_SecureBootFailure(void);

/**
 * [$DD 2462]
 * @brief
 * Mark the secure boot process as OK.
 * [$Satisfies $ARCH 639]
 *
 * This functionality is only available when Secure Boot is supported by the HSM,
 * otherwise it returns @ref ERC_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @return
 * - @ref ERC_NO_SECURE_BOOT
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_SecureBootOk(void);

/**
 * [$DD 2463]
 * [$Satisfies $ARCH 608] [$Satisfies $ARCH 654] [$Satisfies $ARCH 658] [$Satisfies $ARCH 662]
 * @brief
 * Get the status register contents.
 *
 * This function immediately returns the result, there's no need to call @ref SHE_Sync().
 * This function can be called at any time in any state of the SHE module and still
 * returns the proper status.
 * @details Currently only implements the SHE_STATUS_BUSY_BIT flag.
 *
 * @param[out] pStatus Pointer to a single byte to receive the value of the SHE status register
 *
 * @return
 * - @ref ERC_NO_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_GetStatus( uint8* pStatus );

/**
 * [$DD 2424]
 * [$Satisfies $ARCH 630] [$Satisfies $ARCH 871]
 * @brief
 * Get the identity (UID) and the value of the status register protected by a MAC over
 * a challenge and the data.
 *
 * If @ref MASTER_ECU_KEY is empty, then the returned MAC is always all zeroes. This
 * function may not be called while another functionality is
 * still in progress.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @param[in]  challenge Sixteen bytes of data for the challenge
 * @param[out] id Fifteen byte buffer to receive the SHE module UID
 * @param[out] pStatus Pointer to a single byte to receive the value of the SHE status register
 * @param[out] mac Sixteen byte buffer to receive the CMAC of the challenge, UID and status value
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_GetID(const uint8 challenge[SHE_AES_BLOCK_SIZE_BYTES],
                                      uint8       id[SHE_ID_BLOCK_SIZE_BYTES],
                                      uint8*      pStatus,
                                      uint8       mac[SHE_AES_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2425]
 * [$Satisfies $ARCH 871]
 * @brief
 * Interrupt and cancel any running functionality and discard all calculations and results.
 *
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use @ref SHE_Sync() to sync the result.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Cancel.
 *       After a cancellation new SHE requests are then elevated to "medium" priority until
 *       the old one is finished. This also means that the elevated priority request cannot be cancelled.
 *
 * - @ref ERC_BUSY
 *
 * @note The following errors may be returned by a subsequent call to @ref SHE_Sync
 * - @ref ERC_NO_ERROR
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_Cancel(void);

/**
 * [$DD 2443]
 * Synchronize the results of a running functionality. This function returns @ref ERC_BUSY
 * while the HSM is still busy.
 * [$Satisfies $ARCH 660]
 *
 * @note
 * This is a local convenience function and a cover for calling @ref SHE_GetStatus and
 * checking @ref SHE_STATUS_BUSY.
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_BUSY
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_Sync(void);

/**
 * [$DD 2358]
 * @brief
 * Activate any internal debug facilities in the SHE module.
 * [$Satisfies $ARCH 631] [$Satisfies $SW_ARCH 632]
 *
 * Activating the debugger implies erasing all keys except @ref SECRET_KEY, UID, and the
 * PRNG seed and will only work if no keys are write protected.
 *
 * @param[in] challenge Challenge data
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_SEQUENCE_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_CmdDebugChallenge( uint8 challenge[SHE_AES_BLOCK_SIZE_BYTES]);

/**
 * [$DD 2359]
 * @brief
 * Start a authorization verify job for the CMD_DEBUG command.
 * [$Satisfies $SW_ARCH 632]
 *
 * @param[in] authorization Authorization data
 *
 * @return
 * - @ref ERC_NO_ERROR
 * - @ref ERC_SEQUENCE_ERROR
 * - @ref ERC_KEY_NOT_AVAILABLE
 * - @ref ERC_KEY_INVALID
 * - @ref ERC_KEY_EMPTY
 * - @ref ERC_MEMORY_FAILURE
 * - @ref ERC_BUSY
 * - @ref ERC_GENERAL_ERROR
 */
SHE_DECLSPEC SHE_ErrorCodeT SHE_CmdDebugAuthorize(const uint8 authorization[SHE_AES_BLOCK_SIZE_BYTES]);

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
