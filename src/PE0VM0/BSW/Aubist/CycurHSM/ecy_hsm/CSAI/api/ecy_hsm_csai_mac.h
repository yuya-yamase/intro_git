/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Message Authentication Code generation and verification.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating and verifying Message Authentication Codes.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_MAC_H
#define ECY_HSM_CSAI_MAC_H

/**
 * @addtogroup GROUP_CSAI_MAC
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_service_crypt_types.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_SAFETY_MAC_MAX_LEN      16U /**< Number of bytes in safetyMac[] */

/* *** type declarations **********************************************************************/
/** Define Message Authentication Code (MAC) algorithms supported by the HSM */
typedef enum ecy_hsm_Csai_MACAlgorithmTag
{
    ecy_hsm_CSAI_AES_OMAC1      = 1U,                        /**< AES-cipher-based Message authentication Code as specified by NIST SP 800-38B            */
    ecy_hsm_CSAI_AES_CMAC       = ecy_hsm_CSAI_AES_OMAC1,    /**< AES-cipher-based message authentication Code as specified by NIST SP 800-38B            */
    ecy_hsm_CSAI_HMAC_SHA1      = 2U,                        /**< Keyed-hash message authentication code as specified by FIPS-PUB 198a with hashing algorithm SHA1 (160 bit message digest)    */
    ecy_hsm_CSAI_HMAC_SHA2_256  = 3U,                        /**< Keyed-hash message authentication code as specified by FIPS-PUB 198a with hashing algorithm SHA2 (256 bit message digest)    */
    ecy_hsm_CSAI_HMAC_SHA2_512  = 4U,                        /**< Keyed-hash message authentication code as specified by FIPS-PUB 198a with hashing algorithm SHA2 (512 bit message digest)    */
    ecy_hsm_CSAI_SIPHASH_24     = 5U,                        /**< Variant 1 of SipHash 2-4 generation according to Aumasson, Jean-Philippe and Bernstein, Daniel J (64 bit message digest)     */
    ecy_hsm_CSAI_HMAC_SHA2_384  = 6U,                        /**< Keyed-hash message authentication code as specified by FIPS-PUB 198a with hashing algorithm SHA2 (384 bit message digest)    */
    ecy_hsm_CSAI_MAC_NUM_ALGORITHMS,                         /**< Number of algorithms */
    ecy_hsm_CSAI_MAC_RESERVED = 0x7fffffffU                  /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_MACAlgorithmT;

/** Structure for an element of the bulk CMAC verification job control array */
/** @details The actual length of receivedMac is provided in a parameter of CSAI_BulkMacGenerate(). The
    user should make their own copy of this structure, with the length of the receivedMac buffer
    set to the value of macBitLength they intend to pass to ecy_hsm_Csai_BulkMacVerify, converted to bytes
    and rounded up to the next multiple of four. */
typedef struct ecy_hsm_Csai_BulkMacControlVerifyJobTag {
    ecy_hsm_Csai_KeyHandleT keyHandleOrId;                      /**< Key handle or SHE key id                                                     */
    ecy_hsm_Csai_ErrorT     errorCode;                          /**< Error code returned from processing job, ecy_hsm_CSAI_SUCCESS if no error    */
    uint8                   data1LengthBytes;                   /**< Length of the data1 element array in bytes, should be a multiple of four     */
    uint8                   data2LengthBytes;                   /**< Length of the data2 element array in bytes, should be a multiple of four     */
    uint8                   macLengthBits;                      /**< Length in bits of the MAC over which to perform the verification             */
    uint8                   resultFlag;                         /**< Comparison flag, 1 if MAC verified OK, else 0                                */
    const uint8             receivedMac[AES_BLOCK_SIZE_BYTES];  /**< Pointer to received MAC for comparison with calculated                       */
} ecy_hsm_Csai_BulkMacControlVerifyJobT;

/** Structure for an element of the CMAC generate job control array */
/** @details The actual length of calculateMac is provided in a parameter of CSAI_BulkMacGenerate( ).  The
    user should make their own copy of this structure, with the length of the calculatedMac buffer
    set to the value of macBitLength they intend to pass to ecy_hsm_Csai_BulkMacGenerate, converted to bytes
    and rounded up to the next multiple of four.                                     */
typedef struct ecy_hsm_Csai_BulkMacControlGenerateJobTag {
    ecy_hsm_Csai_KeyHandleT keyHandleOrId;                       /**< Key handle or SHE key id                                                           */
    ecy_hsm_Csai_ErrorT     errorCode;                           /**< Error code returned from processing job, ecy_hsm_CSAI_SUCCESS if no error          */
    uint8                   data1LengthBytes;                    /**< Length of the data1 element array in bytes, should be a multiple of four           */
    uint8                   data2LengthBytes;                    /**< Length of the data2 element array in bytes, should be a multiple of four           */
    uint8                   macLengthBits;                       /**< Length in bits of the MAC to be generated                                          */
    uint8                   padding;                             /**< The MAC itself must lie on a 32 bit boundary for compatibility with the AES engine */
    uint8                   calculatedMac[AES_BLOCK_SIZE_BYTES]; /**< Calculated MAC, truncated                                                          */
} ecy_hsm_Csai_BulkMacControlGenerateJobT;

/** This has do be consistent with the ecy_hsm_Csai_BulkMacFastGenJobTag structure (same fields types & order).
 * @note This structure is not needed for the interface. Is just abstracts the status variables of the structure
 * for easy and efficient memory copy. */
typedef struct ecy_hsm_Csai_BulkMacFastGenJobStatusTag
{
    ecy_hsm_Csai_ErrorT errorCode; /**< Error code returned by this MAC generation */
    uint32              isValid;   /**< Indicates if the job has been finished and can be processed. */
} ecy_hsm_Csai_BulkMacFastGenJobStatus;

/** Fast bulk MAC generation job definition */
typedef struct ecy_hsm_Csai_BulkMacFastGenJobTag
{
    ecy_hsm_Csai_KeyHandleT    keyHandle;     /**< Key handle or ID of the key to be used for the MAC generation */
    ecy_hsm_Csai_MACAlgorithmT algorithm;     /**< MAC mechanism to be used                                      */
    ecy_hsm_Csai_ErrorT        errorCode;     /**< Error code returned by this MAC generation                    */
    uint32                     isValid;       /**< Indicates if the job has been finished and can be processed.  */
    const uint8*               message;       /**< Pointer to the message of which the MAC shall be calculated   */
    uint32                     messageLength; /**< Length of the message buffer in bytes                         */
    uint8*                     mac;           /**< Pointer to a buffer where the MAC shall be written            */
    uint32                     macLength;     /**< Length of the MAC in bits                                     */
    uint8                      reserved[4];   /**< reserved for future use (e.g. returning safety MAC)           */
    uint32                     isActive;      /**< Indicates if the job shall be processed or not                */
} ecy_hsm_Csai_BulkMacFastGenJob;

/** This has do be consistent with the ecy_hsm_Csai_BulkMacFastVerJobTag structure (same fields types & order).
 * @note This structure is not needed for the interface. Is just abstracts the status variables of the structure
 * for easy and efficient memory copy. */
typedef struct ecy_hsm_Csai_BulkMacFastVerJobStatusTag
{
    ecy_hsm_Csai_ErrorT errorCode;  /**< Error code returned by this MAC verification                 */
    uint32              isValid;    /**< Indicates if the job has been finished and can be processed. */
    uint32              resultFlag; /**< Result of the MAC verification                               */
} ecy_hsm_Csai_BulkMacFastVerJobStatus;

/** Fast bulk MAC verification job definition */
typedef struct ecy_hsm_Csai_BulkMacFastVerJobTag
{
    ecy_hsm_Csai_KeyHandleT    keyHandle;     /**< Key handle or ID of the key to be used for the verification   */
    ecy_hsm_Csai_MACAlgorithmT algorithm;     /**< MAC mechanism to be used                                      */
    ecy_hsm_Csai_ErrorT        errorCode;     /**< Error code returned by this MAC verification                  */
    uint32                     isValid;       /**< Indicates if the job has been finished and can be processed.  */
    uint32                     resultFlag;    /**< Result of the MAC verification                                */
    const uint8*               message;       /**< Pointer to the message of which the MAC shall be verified     */
    uint32                     messageLength; /**< Length of the message buffer that has to be verified in bytes */
    const uint8*               mac;           /**< Pointer to the expected MAC                                   */
    uint32                     macLength;     /**< Length of the MAC in bits                                     */
    void*                      extensionCtx;  /**< Pointer to context for extension e.g. SafeCmac                */
    uint32                     isActive;      /**< Indicates if the job shall be processed or not                */
} ecy_hsm_Csai_BulkMacFastVerJob;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_MAC_GENERATE_START
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 462]
 * @brief Start a multi part or single shot message authentication code (MAC).
 * [$Satisfies $ARCH 211]
 *
 * The caller must specify in which session context the job is to be executed, a MAC algorithm variant to use and a scheduling priority for the job on
 * the HSM. This function does not block but immediately returns when the job is queued on the HSM.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the MAC computation with further message chunks using
 *      @ref ecy_hsm_Csai_MacGenerateUpdate.
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the MAC computation using
 *      @ref ecy_hsm_Csai_MacGenerateFinish.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   algorithm    Message Authentication Code (MAC) algorithms supported by the HSM.
 * @param[in]   hKey         Handle to a key available in the HSM's session context to
 *                           use for message authentication operation, OR a keyId
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   msg          First chunk or entire message to MAC.
 * @param[in]   msgLength    Length of the provided message or chunk in bytes.
 * @param[out] phJob         Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given MAC scheme is not supported by this HSM build
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type needs to be an asymmetric private key
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateStart(ecy_hsm_Csai_SessionHandleT hSession,
                                                ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                                ecy_hsm_Csai_KeyHandleT     hKey,
                                                ecy_hsm_Csai_JobPriorityT   priority,
                                                const uint8                 msg[],
                                                uint32                      msgLength,
                                                ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_GENERATE_UPDATE
 * @{
 */

/**
 * [$DD 463]
 * @brief Update a running mac job with another message chunk.
 * [$Satisfies $ARCH 212]
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter case, the HSM
 * is still busy with previous data and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob        Handle to the initialized job
 * @param[in]   data        Next chunk or entire message to mac.
 * @param[in]   dataLength  Length of the provided chunk in bytes.
 *
 * Multi-Part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finishes and polls for the result of the mac using
 * @ref ecy_hsm_Csai_MacGenerateFinish.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is busy and cannot take another chunk at the moment.
 *                                                  Please call again later.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter was invalid
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED          The session was found to be closed
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED           The given MAC scheme is not supported by this HSM build
 *  - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED         The Job is in the wrong state to perform this operation
 *  - @ref ecy_hsm_CSAI_ERR_CYCURLIB                CycurLib returned an error.
 *  - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION       There has been an attempt to access HSM ram address via the CSAI interface
 *  - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT       In general, pointers should be aligned to four-byte boundaries
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1        An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2        An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID          The supplied key ID does not map to a valid key slot
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                                 const uint8             data[],
                                                 uint32                  dataLength);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_GENERATE_FINISH
 * @{
 */

/**
 * [$DD 464]
 * @brief Finish a mac calculation and query its result.
 * [$Satisfies $ARCH 213]
 *
 * Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter case, the
 * HSM is still busy with previous data and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[out]  pMac                Pointer to space where the HSM can store the result.
 *                                  The length of the buffer must be sufficiently large
 *                                  to hold the number of bits  given in the parameter
 *                                  @c macBitLength rounded up to the next multiple of 8.
 * @param[in]   macBitLength        Length of the MAC to generate in bits.
 * @param[out]  pMacCount           Pointer to space, where the function can store how
 *                                  many bytes have been written to the provided MAC buffer.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't
 *                                  fit in the provided @c pMAC buffer. If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The operation is pending on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.

 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM            A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED           The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED            The given MAC scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                 CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT        In general, pointers should be aligned to four-byte boundaries
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1         An error was reported by the AES hardware accelerator
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2         An error was reported by the AES hardware accelerator
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION        There has been an attempt to access HSM ram address via the CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID           The supplied key ID does not map to a valid key slot
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL         The output data was too large to fit into the given buffer, nothing was written.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerateFinish(ecy_hsm_Csai_JobHandleT hJob,
                                                 uint8*                  pMac,
                                                 uint32                  macBitLength,
                                                 uint32*                 pMacCount,
                                                 boolean                 truncationAllowed);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_START
 * @{
 */

/**
 * [$DD 467]
 * @brief Start a multi part or single shot message authentication code (MAC) Verify Service.
 * [$Satisfies $ARCH 214]
 *
 * @note The caller must specify in which session context the job is to be executed, a MAC algorithm variant to use and a scheduling priority for the
 * job on the HSM. This function does not block but immediately returns when the job is queued on the HSM.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the MAC computation with further message chunks using
 *      @ref ecy_hsm_Csai_MacVerifyUpdate.
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the MAC computation using
 *      @ref ecy_hsm_Csai_MacVerifyFinish.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   algorithm    Message Authentication Code (MAC) algorithms supported by the HSM.
 * @param[in]   hKey         Handle to a key available in the HSM's session context to
 *                           use for message authentication operation, OR a keyId
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   msg          First chunk or entire message to chksum.
 * @param[in]   msgLength    Length of the provided message or chunk.
 * @param[out]  phJob        Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given mac scheme is not supported by this HSM build
 *   - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED        The Job is in the wrong state to perform this operation
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type needs to be an asymmetric public key
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyStart(ecy_hsm_Csai_SessionHandleT hSession,
                                              ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                              ecy_hsm_Csai_KeyHandleT     hKey,
                                              ecy_hsm_Csai_JobPriorityT   priority,
                                              const uint8                 msg[],
                                              uint32                      msgLength,
                                              ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_UPDATE
 * @{
 */

/**
 * [$DD 468]
 * @brief Update a running mac verify job with another message chunk.
 * [$Satisfies $ARCH 215]
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter case, the HSM
 * is still busy with previous data and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob         Handle to the initialized job
 * @param[in]   data         Next chunk or entire message to mac.
 * @param[in]   dataLength   Length of the provided chunk.
 *
 * Multi-Part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finishes and polls for the result of the mac using
 * @ref ecy_hsm_Csai_MacVerifyFinish.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE              The given session handle is invalid.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                         The HSM is busy and cannot take another chunk at the moment.
 *                                                      Please call again later.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               A parameter was invalid
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED              The session was found to be closed
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED               The given mac scheme is not supported by this HSM build
 *  - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED             The Job is in the wrong state to perform this operation
 *  - @ref ecy_hsm_CSAI_ERR_CYCURLIB                    CycurLib returned an error.
 *  - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION           There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *  - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT           In general, pointers should be aligned to four-byte boundaries
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1            An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2            An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID              The supplied key ID does not map to a valid key slot
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                               const uint8             data[],
                                               uint32                  dataLength);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_FINISH
 * @{
 */

/**
 * [$DD 469]
 * @brief Finish a mac verify calculation and query its result.
 * [$Satisfies $ARCH 216]
 *
 * @note Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter
 * case, the HSM is still busy with previous data and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[in]   pExpectedMac        Pointer to MAC for verification.
 * @param[in]   macBitLength        Length of the MAC to verify in bits.
 *                                  Note: To mitigate the "MAC Forgery Attack", there is a restriction for
 *                                        this parameter. It has to be:
 *                                        >= 27 bits (default) /
 *                                        >= 24 bits (pre-build configuration. Please refer to your delivery notes to identify your configuration)
 *                                        If this restriction is violated, ecy_hsm_CSAI_ERR_INVALID_PARAM is returned.
 * @param[out]  pResultFlag         Pointer to space, where the HSM can write the result of
 *                                  the MAC verify operation.
 Value 0u(FALSE) means MAC does not match and 1u(TRUE) means MAC matches.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.

 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given mac scheme is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            In general, pointers should be aligned to four-byte boundaries
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             An error was reported by the AES hardware accelerator
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2             An error was reported by the AES hardware accelerator
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               The supplied key ID does not map to a valid key slot
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerifyFinish(ecy_hsm_Csai_JobHandleT hJob,
                                               const uint8*            pExpectedMac,
                                               uint32                  macBitLength,
                                               uint32*                 pResultFlag);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_GENERATE_ONESHOT
 * @{
 */

/**
 * [$DD 465]
 * @brief Initialize and start a MAC generation on the HSM.
 * [$Satisfies $ARCH 217] [$Satisfies $SW_ARCH 372] [$Satisfies $SW_ARCH 85758EAB]
 *
 * @note The caller must specify in which session context the job is to be executed, a MAC algorithm variant to use, handle to a key available and a
 * scheduling priority for the job on the HSM. The caller provides a buffer with the input data and its length and a result buffer plus length. The
 * caller also provides the a buffer for the count of the number of bytes Mac'ed and specifies whether the result to be truncated or not.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should subsequently call
 * @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter case, the HSM
 * is still busy with previous data and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be MAC'ed. Alternatively, use the streaming interface (see
 * @ref ecy_hsm_Csai_MacGenerateStart) if an update of the running job is required.
 *
 * The function calls @ref ecy_HSM_QuickRoute if @p msgLength is smaller than or equal to @ref ecy_hsm_MAX_QUICK_ROUTE_BYTES otherwise it calls
 * @ref ecy_HSM_OpRequest_NoJobHandle.
 *
 * The function calls @ref ecy_HSM_QuickRoute for CMACs if supported by the HSM, otherwise it uses standard mode.
 * The function calls @ref ecy_HSM_QuickRoute for SipHash 2-4 if supported by the HSM, otherwise it uses standard mode.
 *
 * If @ref ecy_HSM_QuickRoute is not successful then it will be scheduled as standard MAC generation operation as fallback,
 * unless the @ref ecy_hsm_QUICK_ROUTE_FAILFAST is ENABLED then it will return with errorCode @ref ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE
 *
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   algorithm           Message Authentication Code (MAC) algorithms supported by the HSM.
 * @param[in]   hKey                Handle to a key available in the HSM's session context to
 *                                  use for message authentication operation, OR a keyId
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   msg                 Message to MAC.
 * @param[in]   msgLength           Length of the provided message in bytes.
 * @param[out]  pMac                Pointer to space where the HSM can store the result.
 *                                  The length of the buffer must be sufficiently large
 *                                  to hold the number of bits given in the parameter
 *                                  @c macBitLength rounded up to the next multiple of 8.
 * @param[in]   macBitLength        Length of the MAC to generate in bits.
 * @param[out]  pMacCount           Pointer to space, where the function can store how
 *                                  many bytes have been written to the MAC buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't fit
 *                                  in the provided @c mac buffer.  If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The operation is pending on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.

 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given MAC scheme is not supported by this HSM build
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type needs to be an asymmetric private key
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 *   - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The output data was too large to fit into the given buffer, nothing was written.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                           ecy_hsm_Csai_KeyHandleT     hKey,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           const uint8                 msg[],
                                           uint32                      msgLength,
                                           uint8*                      pMac,
                                           uint32                      macBitLength,
                                           uint32*                     pMacCount,
                                           boolean                     truncationAllowed,
                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_VERIFY_ONESHOT
 * @{
 */

/**
 * [$DD 470]
 * @brief Initialize and start a mac verify calculation and query its result.
 * [$Satisfies $ARCH 218] [$Satisfies $SW_ARCH E4B0BCEC]
 *
 * The caller must specify in which session context the job is to be executed, a MAC algorithm variant to use, handle to a key available and a
 * scheduling priority for the job on the HSM. The caller provides a buffer with the input data and its length and a result buffer plus length. The
 * caller also provides the expected mac buffer and a buffer for the result flag.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should subsequently call @ref
 * ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value. In the latter case, the HSM
 * is still busy with previous data and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be MAC'ed. Alternatively, use the streaming interface (see
 * @ref ecy_hsm_Csai_MacVerifyStart) if an update of the running job is required.
 *
 * The function calls @ref ecy_HSM_QuickRoute if @p msgLength is smaller than or equal to @ref ecy_hsm_MAX_QUICK_ROUTE_BYTES otherwise it calls
 * @ref ecy_HSM_OpRequest_NoJobHandle.
 *
 * The function calls @ref ecy_HSM_QuickRoute for CMACs if supported by the HSM, otherwise it uses standard mode.
 *
 * If @ref ecy_HSM_QuickRoute is not successful then it will be scheduled as standard MAC Verify operation as fallback,
 * unless the @ref ecy_hsm_QUICK_ROUTE_FAILFAST is ENABLED then it will return with errorCode @ref ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   algorithm           Message Authentication Code (MAC) algorithms supported by the HSM.
 * @param[in]   hKey                Handle to a key available in the HSM's session context to
 *                                  use for message authentication operation, OR a keyId
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   msg                 Message for which to verify the MAC.
 * @param[in]   msgLength           Length of the provided message.
 * @param[in]   pExpectedMac        Pointer to MAC for verification.
 * @param[in]   macBitLength        Length of the MAC to verify in bits.
 *                                  Note: To mitigate the "MAC Forgery Attack", there is a restriction for
 *                                        this parameter. It has to be:
 *                                        >= 27 bits (default) /
 *                                        >= 24 bits (pre-build configuration. Please refer to your delivery notes to identify your configuration)
 *                                        If this restriction is violated, ecy_hsm_CSAI_ERR_INVALID_PARAM is returned.
 * @param[out]  pResultFlag         Result of the MAC operation. Value 0u(FALSE) means MAC does not match and 1u(TRUE)
 *                                  means MAC matches.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given mac scheme is not supported by this HSM build
 *
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE             The given key type needs to be an asymmetric public key
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_MacVerify(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_MACAlgorithmT  algorithm,
                                         ecy_hsm_Csai_KeyHandleT     hKey,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 msg[],
                                         uint32                      msgLength,
                                         const uint8*                pExpectedMac,
                                         uint32                      macBitLength,
                                         uint32*                     pResultFlag,
                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_BULKMAC_VERIFY
 * @{
 */
/**
 * [$DD 471]
 * Initialize and start a bulk CMAC Verification.
 * [$Satisfies $ARCH 220]
 *
 * @deprecated
 * THIS FUNCTION IS EXPERIMENTAL AND MAY NOT BE SUPPORTED IN FUTURE VERSIONS
 *
 * @details
 * The caller must specify in which session context the job is to be executed,
 * handle or keyId to a key available and a scheduling priority for the job on the HSM.
 * The caller provides a pointer to an array of MAC job descriptions, see @ref ecy_hsm_Csai_BulkMacControlVerifyJobT
 * and the number of jobs in that array.
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value.
 * In the latter case, the HSM is still busy with previous data and cannot provide the result yet. Try again later.
 * @note the used key needs to be pre-loaded, otherwise a @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED error is returned.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   pTable              Pointer to table of elements of type @ref ecy_hsm_Csai_BulkMacControlVerifyJobT, the
 *                                  table is not actually of this type because the length of the MAC
 *                                  buffer is fixed by macByteSize.
 * @param[in]   numOfEntries        Number of entries in the table.
 * @param[in]   macByteSize         Length in bytes of of the receivedMac field of the job table element,
 *                                  must be a multiple of four.
 * @param[in]   pData1;             Array of first part of data for MACing (array in numOfEntries long).
 * @param[in]   data1Size;          Length in bytes of first part of data for MACing, actual array element length is
 *                                  this rounded up to the next multiple of four.
 * @param[in]   pData2;             Array of second part of data for MACing (array in numOfEntries long).
 * @param[in]   data2Size;          Length in bytes of second part of data for MACing, actual array element
 *                                  length is this rounded up to the next multiple of four.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacVerify(ecy_hsm_Csai_SessionHandleT hSession,
                                             ecy_hsm_Csai_JobPriorityT   priority,
                                             const void*                 pTable,
                                             uint32                      numOfEntries,
                                             uint32                      macByteSize,
                                             uint8*                      pData1,
                                             uint32                      data1Size,
                                             uint8*                      pData2,
                                             uint32                      data2Size,
                                             ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_BULKMAC_GEN
 * @{
 */

/**
 * [$DD 466]
 * Initialize and start a bulk CMAC Generation.
 * [$Satisfies $ARCH 219]
 *
 * @deprecated
 * THIS FUNCTION IS EXPERIMENTAL AND MAY NOT BE SUPPORTED IN FUTURE VERSIONS
 *
 * @details
 * The caller must specify in which session context the job is to be executed,
 * handle or keyId to a key available and a scheduling priority for the job on the HSM.
 * The caller provides a pointer to an array of MAC job descriptions, see @ref ecy_hsm_Csai_BulkMacControlGenerateJobT
 * and the number of jobs in that array.
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value.
 * In the latter case, the HSM is still busy with previous data and cannot provide the result yet. Try again later.
 * @note the used key needs to be pre-loaded, otherwise a @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED error is returned.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   pTable              Pointer to table of elements of type @ref ecy_hsm_Csai_BulkMacControlGenerateJobT,
 *                                  the table is not actually of this type because the length of the MAC buffer is
 *                                  fixed by macByteSize.
 * @param[in]   numOfEntries        Number of entries in the table.
 * @param[in]   macByteSize         Length in bytes of the calculatedMac field in the job table element,
 *                                  must be a multiple of four.
 * @param[in]   pData1;             Array of first part of data for MACing (array is numOfEntries long).
 * @param[in]   data1Size;          Length in bytes of first part of data for MACing, actual array element length is
 *                                  this rounded up to the next multiple of four.
 * @param[in]   pData2;             Array of second part of data for MACing (array is numOfEntries long).
 * @param[in]   data2Size;          Length in bytes of second part of data for MACing, actual array element length is
 *                                  this rounded up to the next multiple of four.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *   - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                      property flags
 *   - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *   - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacGenerate(ecy_hsm_Csai_SessionHandleT hSession,
                                               ecy_hsm_Csai_JobPriorityT   priority,
                                               const void*                 pTable,
                                               uint32                      numOfEntries,
                                               uint32                      macByteSize,
                                               uint8*                      pData1,
                                               uint32                      data1Size,
                                               uint8*                      pData2,
                                               uint32                      data2Size,
                                               ecy_hsm_Csai_JobHandleT*    phJob);
/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_BULKMAC_VERIFYFAST
 * @{
 */

/**
 * [$DD 888]
 * Initialize and start a fast bulk CMAC Verification
 * [$Satisfies $ARCH 220]
 *
 * @details
 * The caller must specify in which session context the job is to be executed,
 * handle or keyId to a key available and a scheduling priority for the job on the HSM.
 * The caller provides a pointer to an array of MAC job descriptions, see @ref ecy_hsm_Csai_BulkMacFastVerJob
 * and the number of jobs in that array.
 *
 * This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle
 * with the returned @ref ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * For better performance, it is recommended that the bulk mac jobs using the same key be placed adjacent to each other
 * in the job table, so that the keys are not loaded multiple times on the HSM.
 *
 * @note the bulk CMAC interface only processes a entries to a maximal number defined in @ref BULK_MAC_FAST_MAX_JOBS
 * @note the used key needs to be pre-loaded, otherwise a @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED error is returned.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed
 * @param[in]   priority            Requested scheduling priority for this job on the HSM
 * @param[in]   pBulkMacJobs        Array of MAC job descriptions
 * @param[in]   numBulkMacJobs      Number of entries in the pBulkMacJobs array
 * @param[out]  phJob               Receives the job handle of the initialized job
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *  - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED             The required key has not been loaded into the session
 *  - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the
 *                                                     CSAI interface
 *  - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION     There has been an attempt to use a key in violation of its
 *                                                     property flags
 *  - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT          In general, pointers should be aligned to four-byte boundaries
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1           An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2           An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID             The supplied key ID does not map to a valid key slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacVerifyFast(ecy_hsm_Csai_SessionHandleT     hSession,
                                                 ecy_hsm_Csai_JobPriorityT       priority,
                                                 ecy_hsm_Csai_BulkMacFastVerJob* pBulkMacJobs,
                                                 uint32                          numBulkMacJobs,
                                                 ecy_hsm_Csai_JobHandleT*        phJob);
/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_MAC_BULKMAC_GENFAST
 * @{
 */

/**
 * [$DD 889]
 * Initialize and start a fast bulk CMAC Generation.
 * [$Satisfies $ARCH 219]
 *
 * @details
 * The caller must specify in which session context the job is to be executed,
 * handle or keyId to a key available and a scheduling priority for the job on the HSM.
 * The caller provides a pointer to an array of MAC job descriptions, see @ref ecy_hsm_Csai_BulkMacFastGenJob
 * and the number of jobs in that array.
 *
 * This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned
 * @ref ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * For better performance, it is recommended that the bulk mac jobs using the same key be placed adjacent to each other
 * in the job table, so that the keys are not loaded multiple times on the HSM.
 *
 * @note the bulk CMAC interface only processes a entries to a maximal number defined in @ref BULK_MAC_FAST_MAX_JOBS
 * @note the used key needs to be pre-loaded, otherwise a @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED error is returned.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed
 * @param[in]   priority            Requested scheduling priority for this job on the HSM
 * @param[in]   pBulkMacJobs        Array of MAC job descriptions
 * @param[in]   numBulkMacJobs      Number of entries in the pBulkMacJobs array
 * @param[out]  phJob               Receives the job handle of the initialized job
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded. The chunk has been queued on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HSM is still busy and the result is not available yet.
 *                                                  Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE          The provided job handle is invalid.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               A parameter was invalid
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED              The session was found to be closed
 *  - @ref ecy_hsm_CSAI_ERR_KEY_NOT_LOADED              The required key has not been loaded into the session
 *  - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION           There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 *  - @ref ecy_hsm_CSAI_ERR_KEY_PROPERTY_VIOLATION      There has been an attempt to use a key in violation of its
 *                                                      property flags
 *  - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT           In general, pointers should be aligned to four-byte boundaries
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1            An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR2            An error was reported by the AES hardware accelerator
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID              The supplied key ID does not map to a valid key slot
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_BulkMacGenerateFast(ecy_hsm_Csai_SessionHandleT     hSession,
                                                   ecy_hsm_Csai_JobPriorityT       priority,
                                                   ecy_hsm_Csai_BulkMacFastGenJob* pBulkMacJobs,
                                                   uint32                          numBulkMacJobs,
                                                   ecy_hsm_Csai_JobHandleT*        phJob);
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

#endif /* Multiple inclusion lock  */
