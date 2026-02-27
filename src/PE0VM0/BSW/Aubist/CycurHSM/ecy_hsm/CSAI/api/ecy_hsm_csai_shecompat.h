/**
 * @file
 ***********************************************************************************************
 * @brief CSAI SHE compatibility interface.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * key management functions for CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_SHECOMPAT
#define ECY_HSM_CSAI_SHECOMPAT

/**
 * @addtogroup GROUP_CSAI_SHECOMPAT
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/* *** defines ********************************************************************************/

/**
 * @anchor ECY_HSM_CSAI_SHE_STATUS_BITS SHE status bits
 * @{
 */

/** This bit is set when the SHE module is busy processing a command */
#define ecy_hsm_CSAI_SHE_STATUS_BUSY                (0x01u)

/** This bit is set if secure booting is activated */
#define ecy_hsm_CSAI_SHE_STATUS_SECURE_BOOT         (0x02u)

/** This bit is set if secure booting has been personalized during the boot sequence */
#define ecy_hsm_CSAI_SHE_STATUS_BOOT_INIT           (0x04u)

/**
 * This bit is set when secure booting has been finished by calling one of
 * SHE_SecureBootFailure(), SHE_SecureBootOk() or if SHE_SecureBoot
 * failed to verify the MAC.
 */
#define ecy_hsm_CSAI_SHE_STATUS_BOOT_FINISHED       (0x08u)

/**
 * This bit is set when SHE_SecureBoot succeeded. SHE_SecureBootFailure()
 * erases this bit.
 */
#define ecy_hsm_CSAI_SHE_STATUS_BOOT_OK             (0x10u)

/**
 * This bit is set when the random number generator has been initialized.
 */
#define ecy_hsm_CSAI_SHE_STATUS_RND_INIT            (0x20u)

/**
 * This bit is set when an external debugger is connected to the chip, i.e. it
 * reflects the input for debugger activation.
 */
#define ecy_hsm_CSAI_SHE_STATUS_EXT_DEBUGGER        (0x40u)

/**
 * This bit is set when the internal debugging mechanisms of the SHE module are
 * activated.
 */
#define ecy_hsm_CSAI_SHE_STATUS_INT_DEBUGGER        (0x80u)


/** Size of the M1 key data block */
#define ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES        (16u)
/** Size of the M2 key data block */
#define ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES        (32u)
/** Size of the M3 key data block */
#define ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES        (16u)
/** Size of the M4 key data block */
#define ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES        (32u)
/** Size of the M5 key data block */
#define ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES        (16u)

/** @} */

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
 * [$DD 2466]
 * @brief
 * Return SHE's status as specified by SHE v1.1.  This function returns immediately with the
 * result and does not need to be sync'd.
 * [$Satisfies $ARCH 647]
 *
 * @param[in]  hSession    Handle to an open HSM session.
 * @param[out] pStatus     Pointer to a byte where the function can write the status
 *                         register as defined by SHE.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_GetStatus(ecy_hsm_Csai_SessionHandleT hSession,
                                             uint8*                      pStatus);

/**
 * [$DD 2467]
 * @brief
 * The function returns the identity (UID) and the value of the status register protected by a
 * MAC over a challenge and the data as specified by SHE V1.1. in section 7.17.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * @note If the MASTER_ECU_KEY is empty, then the MAC is returned as zero.
 *
 * @param[in]  hSession  Handle to an open HSM session.
 * @param[in]  priority  Scheduling priority of the operation on the HSM.
 * @param[in]  challenge Caller provided challenge
 * @param[out] id        Fifteen byte buffer to receive the SHE module UID.
 * @param[out] pStatus   Pointer to a single byte to receive the value of the SHE status register
 * @param[out] mac       Sixteen byte buffer to receive the CMAC of the challenge, UID and status value
 * @param[out] phJob     Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_GetID(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 challenge[16],
                                         uint8                       id[15],
                                         uint8*                      pStatus,
                                         uint8                       mac[16],
                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2468]
 * @brief
 * Update a key according to the key update protocol specified by SHE v1.1 in section 9.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * The functional behaviour of this function is identical to SHE's CMD_LOAD_KEY and can update
 * any of the keys defined by SHE. Other keys, especially asymmetric keys cannot be updated
 * using this function.
 *
 * @note Before the MASTER_ECU_KEY has been provisioned, no other keys can be provisioned
 *       using this interface.
 *
 * @note This function cannot be used to update the extended keys 11-20.
 *       Use @ref ecy_hsm_Csai_She_LoadKeyExtended.
 *
 * @note If the key for update is already loaded into another session (it's OK if it is loaded only
 *       in the current session), then the update will fail with the error ecy_hsm_CSAI_ERR_KEY_ID_IN_USE
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  m1               Message 1 as specified by SHE
 * @param[in]  m2               Message 2 as specified by SHE
 * @param[in]  m3               Message 3 as specified by SHE
 * @param[out] m4               Message 4 as specified by SHE
 * @param[out] m5               Message 5 as specified by SHE
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         The specified EEPROM tag value was not found by an EEPROM read attempt
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             There has been error reported from the EEPROM emulation
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The key ID encoded in M1 is invalid or not suitable for update.
 * - @ref ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY             The key ID encoded in M1 is write protected.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER          The counter not being greater than the current counter
 * - @ref ecy_hsm_CSAI_ERR_INVALID_UID                  The supplied UID is incorrect
 * - @ref ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY               The authorizing key is empty
 * - @ref ecy_hsm_CSAI_ERR_INVALID_M3                   Message M3 is not matching the expected value
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_IN_USE                The key for update is already loaded into another session
 *
 * @note Mapping of SHE errors to CSAI errors:
 * - ERC_KEY_NOT_AVAILABLE,
 * - ERC_KEY_INVALID            -   ecy_hsm_CSAI_ERR_POLICY_VIOLATION, ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION, ecy_hsm_CSAI_ERR_KEY_ID_INVALID
 * - ERC_KEY_WRITE_PROTECTED    -   ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY
 * - ERC_KEY_UPDATE_ERROR       -   ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER, ecy_hsm_CSAI_ERR_INVALID_UID, ecy_hsm_CSAI_ERR_INVALID_M3,
 *                                  ecy_hsm_CSAI_ERR_KEY_ID_IN_USE
 * - ERC_MEMORY_FAILURE,
 * - ERC_KEY_EMPTY              -   ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND, ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY
 * - ERC_SEQUENCE_ERROR         -   ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED, ecy_hsm_CSAI_ERR_JOB_NOT_STARTED, ecy_hsm_CSAI_ERR_SESSION_CLOSED
 * - ERC_BUSY,
 * - ERC_GENERAL_ERROR          -   ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION, ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKey(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                           const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                           const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                           uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                           uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2469]
 * @brief
 * Update an extended key (11 - 20) according to the key update protocol specified by SHE v1.1 in section 9.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * This function can be used to update SHE+ extended keys (11 - 20).
 * The functional behaviour of this function is identical to SHE+ CMD_LOAD_KEY_EXTENDED
 * and can update any of the keys defined by SHE+.
 * Other keys, especially asymmetric keys cannot be updated using this function.
 *
 * @note Before the MASTER_ECU_KEY has been provisioned, no other keys can be provisioned
 *       using this interface.
 *
 * @note If the key for update is already loaded into another session (it's OK if it is loaded only
 *       in the current session), then the update will fail with the error ecy_hsm_CSAI_ERR_KEY_ID_IN_USE
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  m1               Message 1 as specified by SHE
 * @param[in]  m2               Message 2 as specified by SHE
 * @param[in]  m3               Message 3 as specified by SHE
 * @param[out] m4               Message 4 as specified by SHE
 * @param[out] m5               Message 5 as specified by SHE
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         The specified EEPROM tag value was not found by an EEPROM read attempt
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             There has been error reported from the EEPROM emulation
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The key ID encoded in M1 is invalid or not suitable for update.
 * - @ref ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY             The key ID encoded in M1 is write protected.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER          The counter not being greater than the current counter
 * - @ref ecy_hsm_CSAI_ERR_INVALID_UID                  The supplied UID is incorrect
 * - @ref ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY               The authorizing key is empty
 * - @ref ecy_hsm_CSAI_ERR_INVALID_M3                   Message M3 is not matching the expected value
 *
 * @note Mapping of SHE errors to CSAI errors:
 * - ERC_KEY_NOT_AVAILABLE,
 * - ERC_KEY_INVALID            -   ecy_hsm_CSAI_ERR_POLICY_VIOLATION, ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION, ecy_hsm_CSAI_ERR_KEY_ID_INVALID
 * - ERC_KEY_WRITE_PROTECTED    -   ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY
 * - ERC_KEY_UPDATE_ERROR       -   ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER, ecy_hsm_CSAI_ERR_INVALID_UID, ecy_hsm_CSAI_ERR_INVALID_M3,
 *                                  ecy_hsm_CSAI_ERR_KEY_ID_IN_USE
 * - ERC_MEMORY_FAILURE,
 * - ERC_KEY_EMPTY              -   ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND, ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY
 * - ERC_SEQUENCE_ERROR         -   ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED, ecy_hsm_CSAI_ERR_JOB_NOT_STARTED, ecy_hsm_CSAI_ERR_SESSION_CLOSED
 * - ERC_BUSY,
 * - ERC_GENERAL_ERROR          -   ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION, ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKeyExtended(ecy_hsm_Csai_SessionHandleT hSession,
                                                   ecy_hsm_Csai_JobPriorityT   priority,
                                                   const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                   const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                   const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                   uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                   uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                   ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2470]
 * @brief
 * Update a bank-numbered extended key according to the key update protocol specified by SHE v1.1 in section 9.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * This function is used to update any of the keys stipulated by additional requirements,
 * initially in CYS2200. The functional behaviour of this function is identical to CMD_LOAD_KEY and
 * can update any of the further extended keys defined initially by CYS2200.
 * Other keys, especially asymmetric keys cannot be updated using this function.
 * The general purpose keys exist in "banks" of ten keys, with a bank index referring to the key
 * bank (bank index 0 -> keys 1-10, bank index 1 -> keys 11-20, etc). E.g. specifying a keyId with a numerical
 * value of 4 (i.e. KEY_1) and a bank index of 4 would result in an update of KEY_41.
 *
 * @note Before the MASTER_ECU_KEY has been provisioned, no other keys can be provisioned
 *       using this interface.
 *
 * @note If the key for update is already loaded into another session (it's OK if it is loaded only
 *       in the current session), then the update will fail with the error ecy_hsm_CSAI_ERR_KEY_ID_IN_USE
 *
 * @note  Due to the asynchronous design nature of this SHE interface, the result will not be available
 *        when the function returns. Use @ref ecy_hsm_Csai_PollHandle() to sync the result.
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  m1               Message 1 as specified by SHE
 * @param[in]  m2               Message 2 as specified by SHE
 * @param[in]  m3               Message 3 as specified by SHE
 * @param[out] m4               Message 4 as specified by SHE
 * @param[out] m5               Message 5 as specified by SHE
 * @param[in] bankIndex         Bank index as specified initially by CYS2200 if updating a general purpose key (ignored otherwise).
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         The specified EEPROM tag value was not found by an EEPROM read attempt
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_EMULATION             There has been error reported from the EEPROM emulation
 * - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE               The key ID encoded in M1 is invalid or not suitable for update.
 * - @ref ecy_hsm_CSAI_ERR_KEY_IS_READ_ONLY             The key ID encoded in M1 is write protected.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_KEY_COUNTER          The counter not being greater than the current counter
 * - @ref ecy_hsm_CSAI_ERR_INVALID_UID                  The supplied UID is incorrect
 * - @ref ecy_hsm_CSAI_ERR_EMPTY_AUTH_KEY               The authorizing key is empty
 * - @ref ecy_hsm_CSAI_ERR_INVALID_M3                   Message M3 is not matching the expected value
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadKeyToBank(ecy_hsm_Csai_SessionHandleT hSession,
                                                 ecy_hsm_Csai_JobPriorityT   priority,
                                                 const uint8                 m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                 const uint8                 m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                 const uint8                 m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                 uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                 uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                 uint32                      bankIndex,
                                                 ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2471]
 * @brief
 * Load a key without encryption or verification into the RAM_KEY slot of SHE according
 * SHE v1.1 section 7.8.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * The functional behaviour of this function is identical to SHE's CMD_LOAD_PLAIN_KEY.
 * The key can be exported in an encryption and authenticated format defined by SHE
 * with @ref ecy_hsm_Csai_She_ExportRamKey().
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  key              Message 1 as specified by SHE
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 *
 * @note Mapping of SHE errors to CSAI errors:
 * - ERC_SEQUENCE_ERROR         -   ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED, ecy_hsm_CSAI_ERR_JOB_NOT_STARTED, ecy_hsm_CSAI_ERR_SESSION_CLOSED
 * - ERC_BUSY,
 * - ERC_GENERAL_ERROR          -   ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_LoadPlainKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                const uint8                 key[16],
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2472]
 * @brief
 * Export a previously loaded RAM_KEY into a format protected by SECRET_KEY.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * The key can be imported again by using @ref ecy_hsm_Csai_She_LoadKey.
 * A RAM_KEY can only be exported if it was written into SHE in plain text,
 * i.e. by @ref ecy_hsm_Csai_She_LoadPlainKey.
 *
 * For loading a RAM_KEY and therefore for exporting a RAM_KEY the reserved fields for the
 * security flags and the counter have to be set to 0. For further explanation on message details
 * and contents as well as for arithmetic and padding, see Chapter 9 of the SHE v1.1 spec.
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  m1               Message 1 as specified by SHE
 * @param[in]  m2               Message 2 as specified by SHE
 * @param[in]  m3               Message 3 as specified by SHE
 * @param[out] m4               Message 4 as specified by SHE
 * @param[out] m5               Message 5 as specified by SHE
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         No RAM key loaded to export
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                Invalid addresses for m1-m5
 *
 * @note Mapping of SHE errors to CSAI errors:
 * - ERC_KEY_EMPTY              -   ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND
 * - ERC_SEQUENCE_ERROR         -   ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED, ecy_hsm_CSAI_ERR_JOB_NOT_STARTED, ecy_hsm_CSAI_ERR_SESSION_CLOSED
 * - ERC_BUSY,
 * - ERC_GENERAL_ERROR          -   ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_ExportRamKey(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                uint8                       m1[ecy_hsm_CSAI_SHE_M1_BLOCK_SIZE_BYTES],
                                                uint8                       m2[ecy_hsm_CSAI_SHE_M2_BLOCK_SIZE_BYTES],
                                                uint8                       m3[ecy_hsm_CSAI_SHE_M3_BLOCK_SIZE_BYTES],
                                                uint8                       m4[ecy_hsm_CSAI_SHE_M4_BLOCK_SIZE_BYTES],
                                                uint8                       m5[ecy_hsm_CSAI_SHE_M5_BLOCK_SIZE_BYTES],
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2473]
 * @brief
 * Start the secure boot process.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * This functionality is only available when Secure Boot is supported by the HSM,
 * otherwise it returns ecy_hsm_CSAI_ERR_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use ecy_hsm_Csai_PollHandle() to sync the result.
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[in]  dataLength       Length of FLASH block to protect with BOOT_MAC and BOOT_MAC_KEY
 * @param[in]  data             Pointer start of FLASH block to protect with BOOT_MAC and BOOT_MAC_KEY
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND         No BOOT_MAC key found
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                Invalid address for data
 * - @ref ecy_hsm_CSAI_ERR_NO_SECURE_BOOT               The secure boot has already completed
 *                                              (allowed only once after each reset)
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBoot(ecy_hsm_Csai_SessionHandleT hSession,
                                              ecy_hsm_Csai_JobPriorityT   priority,
                                              uint32                      dataLength,
                                              const uint8                 data[],
                                              ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2474]
 * @brief
 * Mark the secure boot process as OK.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * This functionality is only available when Secure Boot is supported by the HSM,
 * otherwise it returns ecy_hsm_CSAI_ERR_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use ecy_hsm_Csai_PollHandle() to sync the result.
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_NO_SECURE_BOOT               The secure boot has failed. This is only returned the first time that
 *                                              ecy_hsm_Csai_She_SecureBootOk is called after each reset.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBootOk(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2475]
 * @brief
 * Mark the secure boot process of failed.
 * [$Satisfies $ARCH 647] [$Satisfies $ARCH 642]
 *
 * This function is not reversible before the next power cycle. This functionality is
 * only available when Secure Boot is supported by the HSM, otherwise it returns
 * ecy_hsm_CSAI_ERR_NO_SECURE_BOOT.
 * See SHE specification for details.
 *
 * @note
 * Due to the asynchronous design nature of this SHE interface, the result will
 * not be available when the function returns. Use CSAI_PollHandlec() to sync the result.
 *
 * @param[in]  hSession         Handle to an open HSM session.
 * @param[in]  priority         Scheduling priority of the operation on the HSM.
 * @param[out] phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_NO_SECURE_BOOT               The secure boot has failed.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_She_SecureBootFailure(ecy_hsm_Csai_SessionHandleT hSession,
                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                     ecy_hsm_Csai_JobHandleT*    phJob);

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
