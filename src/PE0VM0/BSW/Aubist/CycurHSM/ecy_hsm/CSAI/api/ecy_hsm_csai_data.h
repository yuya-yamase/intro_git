/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Storage.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for reading/writing data to the HSM secure storage with CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2016, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_DATA_H
#define ECY_HSM_CSAI_DATA_H

/**
 * @addtogroup GROUP_CSAI_DATA
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_error.h"

/* *** defines ********************************************************************************/

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
 * [$DD 933]
 * Read secure data from the HSM secure storage (EEPROM and HSM RAM)
 * [$Satisfies $ARCH 347] [$Satisfies $SW_ARCH 347_v1]
 * @note
 * Only indivisible secure data blocks may be read from secure storage. Partial reads that do not return the whole data object are not possible.
 * If the selected secure data was mirrored during startup in the HSM RAM with the configuration attribute
 * @ref STARTUP_HSM or @ref BACKGROUND, the data will be read from the HSM RAM.
 * Mirrored data will be read only once from the HSM RAM and automatically removed from the
 * RAM array after read. Further calls for the same mirrored data are performed
 * at low speed (reading the data from DFlash). After the function call @ref ecy_hsm_Csai_ReleaseMirroredData
 * all mirrored data will be removed from the RAM array too.
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the read operation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @note
 * DFLASH data operations will always performed in low priority.
 * Parameter will be overridden by runtime.
 * @param[in]   tag          Id of the data block to be read.
 * @note Valid IDs are in the range between the <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_start</code> and
 *       <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_end</code> entries of the <code>ecy_hsm_Csai_KeyIdT</code>
 *       enum in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[out]  pData        Pointer to buffer to receive the secure data
 * @param[in]   dataLength   Length of buffer to receive the secure data. Must have at least the same length as the data object to be read.
 * @param[out]  pDataCount   Pointer to buffer to receive the secure data length
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
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReadData(ecy_hsm_Csai_SessionHandleT hSession,
                                        ecy_hsm_Csai_JobPriorityT   priority,
                                        uint32                      tag,
                                        void*                       pData,
                                        uint32                      dataLength,
                                        uint32*                     pDataCount,
                                        ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 935]
 * Write secure data to the HSM secure storage (EEPROM)
 * [$Satisfies $ARCH 349][$Satisfies $SW_ARCH 349_v1]
 *
 * @note
 * Only indivisible secure data blocks may be written to secure storage.
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the write operation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @note
 * DFLASH data operations will always performed in low priority.
 * Parameter will be overridden by runtime.
 * @param[in]   tag          Id of the data block to be written.
 * @note Valid IDs are in the range between the <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_start</code> and
 *       <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_end</code> entries of the <code>ecy_hsm_Csai_KeyIdT</code>
 *       enum in the file <code>ecy_hsm_csai_keyid.h</code>.
 * @param[in]   pData        Pointer to buffer containing the secure data to be written
 * @param[in]   dataLength   Length of secure data buffer
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
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_WriteData(ecy_hsm_Csai_SessionHandleT hSession,
                                         ecy_hsm_Csai_JobPriorityT   priority,
                                         uint32                      tag,
                                         const void*                 pData,
                                         uint32                      dataLength,
                                         ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 936]
 * Delete secure data from the HSM secure storage (EEPROM)
 * [$Satisfies $ARCH 348][$Satisfies $SW_ARCH 348_v1]
 *
 * @note
 *
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the delete operation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM.
 * @note
 * DFLASH data operations will always performed in low priority.
 * Parameter will be overridden by runtime.
 * @param[in]   tag          Id of the data block to be deleted
 * @note Valid IDs are in the range between the <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_start</code> and
 *       <code>ecy_hsm_CSAI_KEYID_SECRET_DATA_end</code> entries of the <code>ecy_hsm_Csai_KeyIdT</code>
 *       enum in the file <code>ecy_hsm_csai_keyid.h</code>.
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
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_DeleteData(ecy_hsm_Csai_SessionHandleT hSession,
                                          ecy_hsm_Csai_JobPriorityT   priority,
                                          uint32                      tag,
                                          ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1344]
 * Release all mirrored secure data from the HSM RAM
 * [$Satisfies $SW_ARCH 842][$Satisfies $SW_ARCH 842_v1]
 *
 * @note
 * - Finalization and result query:
 *      The caller finishes and polls for the result of the release operation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * @note
 * Be careful, this function will release all still available mirrored secure data from the HSM RAM.
 * After this call, all data are only read from the DFLash.
 *
 *
 * @param[in]   hSession     Handle to the session in which the job will be placed.
 * @param[in]   priority     Requested scheduling priority for this job on the HSM. (just BACKGROUND priority is allowed)
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
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED         The priority is not allowed
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_ReleaseMirroredData(ecy_hsm_Csai_SessionHandleT hSession,
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
