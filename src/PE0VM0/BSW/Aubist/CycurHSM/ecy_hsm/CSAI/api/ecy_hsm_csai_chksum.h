/**
 * @file
 ***********************************************************************************************
 * @brief CSAI checksum jobs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for calculating checksums and CRCs.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_CHKSUM_H
#define ECY_HSM_CSAI_CHKSUM_H

/**
 * @addtogroup GROUP_CSAI_CHKSUM
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Define checksum algorithms supported by the HSM. */
typedef enum ecy_hsm_Csai_ChksumAlgorithmTag
{
    ecy_hsm_CSAI_CHKSUM8       = 1U,         /**< 2's complement of the sum of all the bytes         */
    ecy_hsm_CSAI_CRC32         = 2U,         /**< CRC32 (Ethernet IEEE 802.3 - 0x04C11DB7)           */
    ecy_hsm_CSAI_CRC_SAE_J1850 = 3U,         /**< 8 bit CRC, polynomial = 0x1D                       */
    ecy_hsm_CSAI_CRC_8H2F      = 4U,         /**< 8 bit CRC, polynomial = 0x2F                       */
    ecy_hsm_CSAI_CRC_CCITT     = 5U,         /**< 16 bit CRC, polynomial = 0x1021                    */
    ecy_hsm_CSAI_CRC_RESERVED  = 0x7fffffffU /**< Reserved value to enforce long enums               */
} ecy_hsm_Csai_ChksumAlgorithmT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_CSAI_CRC_RESERVED
 */
#define CSAI_CRC_RESERVED ecy_hsm_CSAI_CRC_RESERVED
/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_CSAI_CHKSUM_START
 * @{
 */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * Start a multi part or single shot calculation of a checksum or CRC.
 * The caller must specify in which session context the job is to be
 * executed, a checksum algorithm variant to use and a scheduling priority for
 * the job on the HSM.
 * The caller provides a buffer with the input data and its length and a result
 * buffer plus length.This function does not block but immediately returns when
 * the job is queued on the HSM.
 *
 * @note
 * - Multi-part mode:
 *      The caller may update the checksum operation with further message chunks using
 *      @ref ecy_hsm_Csai_ChksumUpdate.
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the checksum calculation using
 *      @ref ecy_hsm_Csai_ChksumFinish.
 *
 * @param[in]   hSession     Handle to the session in which the job is placed.
 * @param[in]   algorithm    Specification of the SHA variant to use.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @param[in]   msg          First chunk or entire message to checksum.
 *                           The caller may set this to @c NULL if msgLength is zero.
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given checksum algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          The Job is in the wrong state to perform this operation
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumStart(ecy_hsm_Csai_SessionHandleT   hSession,
                                           ecy_hsm_Csai_ChksumAlgorithmT algorithm,
                                           ecy_hsm_Csai_JobPriorityT     priority,
                                           const uint8                   msg[],
                                           uint32                        msgLength,
                                           ecy_hsm_Csai_JobHandleT*      phJob);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CHKSUM_UPDATE
 * @{
 */

/**
 * Update a running checksum job with another message chunk.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy calculating the checksum of
 * previous data and cannot queue more data at the moment. Try again later.
 *
 * @param[in]   hJob        Handle to the initialized job
 * @param[in]   chunk       Next chunk or entire message to checksum.  May be NULL_PTR if msgLength is zero.
 * @param[in]   length      Length of the provided chunk.
 *
 * Multi-Part mode:
 * The caller may repeatedly call this function to provide additional message chunks.
 *
 * Finalization and result query:
 * The caller finishes and polls for the result of the checksum calculation using
 * @ref ecy_hsm_Csai_ChksumFinish.
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The checksum algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumUpdate(ecy_hsm_Csai_JobHandleT hJob,
                                            const uint8             chunk[],
                                            const uint32            length);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CHKSUM_FINISH
 * @{
 */

/**
 * Finish a checksum calculation and query its result.
 * Note, that this function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy calculating the checksum
 * and cannot provide the result yet. Try again later.
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[out]  pResult             Pointer to space where the HSM can store the result.
 * @param[in]   resultLength        Length of the provided @c digest buffer.
 * @param[out]  pResultCount        Pointer to space, where the function can store how
 *                                  many bytes have been written to the digest buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't fit
 *                                  in the provided @c digest buffer.  If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned.
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given checksum algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             The output data was too large to fit into the given buffer, nothing
 *                                                      was written.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ChksumFinish(ecy_hsm_Csai_JobHandleT hJob,
                                            uint8*                  pResult,
                                            uint32                  resultLength,
                                            uint32*                 pResultCount,
                                            boolean                 truncationAllowed);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_CHKSUM_ONESHOT
 * @{
 */

/**
 * Initialize and start a checksum calculation and query its result.
 * The caller must specify in which session context the job is to be executed, a checksum algorithm
 * variant to use and a scheduling priority for the job on the HSM.
 * The caller provides a buffer with the input data and its length and a result buffer plus length. The caller also provides the
 * a buffer for the count of the number of bytes Checksum'ed and specifies whether the result to be truncated or not.
 *
 * @note This function does not block but immediately returns when the job is queued on the HSM. The caller should subsequently
 * call @ref ecy_hsm_Csai_PollHandle or @ref ecy_hsm_Csai_WaitForHandle with the returned @c ecy_hsm_Csai_JobHandleT to synchronize with the result.
 *
 * @note This function may return @ref ecy_hsm_CSAI_SUCCESS or @ref ecy_hsm_CSAI_FC_BUSY, an
 * expected flow control value. In the latter case, the HSM is still busy with previous data
 * and cannot provide the result yet. Try again later.
 *
 * @note The fast call interface allows the checksum calculation a single block of data in one call. Alternatively,
 * use the streaming interface (see @ref ecy_hsm_Csai_ChksumStart) if an update of the running job is required.
 *
 * @param[in]   hSession            Handle to the session in which the job is placed.
 * @param[in]   algorithm           Specification of the SHA variant to use.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   msg                 First chunk or entire message to chksum.  May be NULL_PTR if msgLength is zero.
 * @param[in]   msgLength           Length of the provided message or chunk.
 * @param[out]  pResult             Pointer to space where the HSM can store the result.
 * @param[in]   resultLength        Length of the provided @c digest buffer.
 * @param[out]  pResultCount        Pointer to space, where the function can store how
 *                                  many bytes have been written to the digest buffer
 *                                  provided here.
 *                                  The caller may provide @c NULL_PTR in which case no
 *                                  count is provided.
 * @param[in]   truncationAllowed   TRUE if it is permitted to truncate the result if it won't fit
 *                                  in the provided @c digest buffer.  If FALSE and the buffer
 *                                  is too small then ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL is returned.
 * @param[out]   phJob              Receives pointer to job handle.
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
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given checksum algorithm is not supported by this HSM build
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             The output data was too large to fit into the given buffer, nothing
 *                                                      was written.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_Chksum(ecy_hsm_Csai_SessionHandleT   hSession,
                                      ecy_hsm_Csai_ChksumAlgorithmT algorithm,
                                      ecy_hsm_Csai_JobPriorityT     priority,
                                      const uint8                   msg[],
                                      uint32                        msgLength,
                                      uint8*                        pResult,
                                      uint32                        resultLength,
                                      uint32*                       pResultCount,
                                      boolean                       truncationAllowed,
                                      ecy_hsm_Csai_JobHandleT*      phJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * @}
 */
#endif /* Multiple inclusion lock  */
