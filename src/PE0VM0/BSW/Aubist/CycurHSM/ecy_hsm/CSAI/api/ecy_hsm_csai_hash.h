/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Hash jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for Hashing with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_HASH_H
#define ECY_HSM_CSAI_HASH_H

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"

/**
 * @addtogroup GROUP_CSAI_HASHING
 * @{
 */

/* *** type declarations **********************************************************************/
/** Define hash algorithms supported by the HSM. */
typedef enum ecy_hsm_Csai_HashAlgorithmTag
{
    ecy_hsm_CSAI_SHA1          = 1u,         /**< SHA-1 with 160 bit digest as specified by FIPS-180-1 */
    ecy_hsm_CSAI_SHA2_256      = 2u,         /**< SHA-2 with 256 bit digest as specified by FIPS-180-2 */
    ecy_hsm_CSAI_SHA2_512      = 3u,         /**< SHA-2 with 512 bit digest as specified by FIPS-180-2 */
    ecy_hsm_CSAI_AES_MP        = 4u,         /**< Compression function constructed according to Miyaguchi-Preneel using AES as the block cipher   */
    ecy_hsm_CSAI_SHA2_224      = 5u,         /**< SHA-2 with 224 bit digest as specified by FIPS-180-3 */
    ecy_hsm_CSAI_SHA2_384      = 6u,         /**< SHA-2 with 384 bit digest as specified by FIPS-180-2 */
    ecy_hsm_CSAI_SM3           = 7u,         /**< SM3 with 256 bit digest as specified by GB/T 32905-2016 */
    ecy_hsm_CSAI_SHA3_224      = 8u,         /**< SHA-3 with 224 bit digest as specified by FIPS-202 */
    ecy_hsm_CSAI_SHA3_256      = 9u,         /**< SHA-3 with 256 bit digest as specified by FIPS-202 */
    ecy_hsm_CSAI_SHA3_384      = 10u,        /**< SHA-3 with 384 bit digest as specified by FIPS-202 */
    ecy_hsm_CSAI_SHA3_512      = 11u,        /**< SHA-3 with 512 bit digest as specified by FIPS-202 */
    ecy_hsm_CSAI_SHAKE_256     = 12u,        /**< SHAKE 256 bit digest as specified by FIPS-202  */
    ecy_hsm_CSAI_HASH_RESERVED = 0x7fffffffu /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_HashAlgorithmT;

/**
 * @addtogroup GROUP_CSAI_HASH_START
 * @{
 */
/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2310]
 * [$Satisfies $SW_ARCH 957] [$Satisfies $ARCH 911]
 * Start a multi part or single shot calculation of a hash digest.
 * The caller must specify in which session context the job is to be
 * executed, a hash algorithm variant to use and a scheduling priority for the job on
 * the HSM.
 * This function does not block but immediately returns when
 * the job is queued on the HSM.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the hash operation with further message chunks using
 *      @ref ecy_hsm_Csai_HashUpdate.
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the hash calculation using
 *      @ref ecy_hsm_Csai_HashFinish.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   algorithm    Specification of the SHA variant to use.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   msg          First chunk or entire message to hash, can be NULL_PTR if msgLength is zero, data is then
 *                           passed by ecy_hsm_Csai_HashUpdate
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
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given hash algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashStart(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_HashAlgorithmT algorithm,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         const uint8                 msg[],
                                         uint32                      msgLength,
                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_HASH_UPDATE
 * @{
 */

/**
 * [$DD 2311]
 * [$Satisfies $SW_ARCH 957] [$Satisfies $ARCH 911]
 * Update a running hash job with another message chunk.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy hashing
 * previous data and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob        Handle to the initialized job
 * @param[in]   chunk       Next chunk or entire message to hash.  May be NULL_PTR if msgLength is zero.
 * @param[in]   length      Length of the provided chunk.
 *
 * Multi-Part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finishes and polls for the result of the hash calculation using
 * @ref ecy_hsm_Csai_HashFinish.
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
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given has algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_WRONG_JOB                    A job update or finish call has been made on a session/port
 *                                                      which is not the started job.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                          const uint8             chunk[],
                                          uint32                  length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_HASH_FINISH
 * @{
 */

/**
 * [$DD 2312]
 * [$Satisfies $SW_ARCH 957] [$Satisfies $ARCH 911]
 * Finish a hash calculation and query its result.
 * Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy hashing
 * and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[out]  digest              Pointer to space where the HSM can store the result.
 * @param[in]   digestLength        Length of the provided @c digest buffer.
 * @param[out]  pDigestCount        Pointer to space, where the function can store how
 *                                  many bytes have been written to the digest buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't
 *                                  in the provided @c digest buffer.  If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given has algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_WRONG_JOB                    A job update or finish call has been made on a session/port
 *                                                      which is not the started job.
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             The AES Accelerator reports an error.
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             The output data was too large to fit into the given buffer, nothing
 *                                                      was written.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_HashFinish(ecy_hsm_Csai_JobHandleT hJob,
                                          uint8*                  digest,
                                          uint32                  digestLength,
                                          uint32*                 pDigestCount,
                                          boolean                 truncationAllowed);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_HASH_ONESHOT
 * @{
 */

/**
 * Perform a hash calculation and query its result.
 * The caller must specify in which session context the job is to be executed, a hash algorithm variant
 * to use and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus length.
 * The caller also provides the
 * buffer to store the number of bytes hashed and also specifies whether the result to be truncated or not.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM.
 * The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c JobHandle to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data and cannot
 * provide the result yet. Try again later.
 *
 * @note The fast call interface allows a single block of data to be Hash'ed.  Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_HashStart) if an update of the running job is required.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   algorithm           Specification of the SHA variant to use.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   msg                 First chunk or entire message to hash, can be NULL_PTR if msgLength is zero,
 data is then passed by ecy_hsm_Csai_HashUpdate
 * @param[in]   msgLength           Length of the provided message or chunk.
 * @param[out]  digest              Pointer to space where the HSM can store the result.
 * @param[in]   digestLength        Length of the provided @c digest buffer.
 * @param[out]  pDigestCount        Pointer to space, where the function can store how
 *                                  many bytes have been written to the digest buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't
 *                                  in the provided @c digest buffer.  If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned
 * @param[out]  phJob               pointer to the job handle
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
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given has algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             The AES Accelerator reports an error.
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             The output data was too large to fit into the given buffer,
 *                                                      nothing was written.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Hash(ecy_hsm_Csai_SessionHandleT hSession,
                                    ecy_hsm_Csai_HashAlgorithmT algorithm,
                                    ecy_hsm_Csai_JobPriorityT   priority,
                                    const uint8                 msg[],
                                    uint32                      msgLength,
                                    uint8*                      digest,
                                    uint32                      digestLength,
                                    uint32*                     pDigestCount,
                                    boolean                     truncationAllowed,
                                    ecy_hsm_Csai_JobHandleT*    phJob);

/** @} */ // GROUP_CSAI_HASH_ONESHOT
/** @} */ // CSAI_HASH

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* Multiple inclusion lock  */
