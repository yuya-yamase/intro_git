/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Job handling.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for managing running jobs on the HSM
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_JOB_H
#define ECY_HSM_CSAI_JOB_H

/**
 * @addtogroup GROUP_CSAI_JOB_MANAGEMENT
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_session.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/
/** @brief Enumeration for the status of a job on the HSM    */
typedef enum ecy_hsm_Csai_JobStatusTag {
    ecy_hsm_CSAI_JOBSTATUS_IDLE = 0,                  /**< No operation loaded on this job                       */
    ecy_hsm_CSAI_JOBSTATUS_PENDING,                   /**< Operation loaded on this job, not processing yet      */
    ecy_hsm_CSAI_JOBSTATUS_PROCESSING,                /**< Operation being processed on this job                 */
    ecy_hsm_CSAI_JOBSTATUS_COMPLETE,                  /**< Operation has completed on this job                   */
    ecy_hsm_CSAI_JOBSTATUS_RESERVED = 0x7fffffffu     /**< Value defined to use memory size of uint32 for enums  */
} ecy_hsm_Csai_JobStatusT;

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1037]
 * [$Satisfies $ARCH 868]
 * Asynchronously cancel a running job (streaming service) on the HSM.
 * This function takes a handle of type @ref ecy_hsm_Csai_JobHandleT
 * and asynchronously cancels the running operation on this
 * job handle.  Not to be confused with ecy_hsm_Csai_CancelOperation( ) which
 * cancels a scheduled or in progress operation.
 *
 * @details All this does is reset the port status.  So if a job was in progress on the port
 *          then that job is cancelled and the port is reset into a state where it is ready
 *          to accept a new job.  It does not cancel any job which is already queued on the
 *          HSM or indeed currently executing.
 *
 * @param[in]   hJob        Handle to a running job.
 *
 * @return
 *  - ecy_hsm_CSAI_SUCCESS              The call succeeded. The running job is cancelled.
 *  - ecy_hsm_CSAI_ERR_INVALID_HANDLE   The provided job handle is invalid.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CancelJob(ecy_hsm_Csai_JobHandleT hJob);

/**
 * [$DD 1038]
 * [$Satisfies $ARCH 868]
 * Asynchronously cancel a running or scheduled operation on the HSM.
 * This function takes a handle of type @ref ecy_hsm_Csai_SessionHandleT
 * and asynchronously cancels any operation running on this session or
 * waiting to run on this session.
 *
 * @details The internal operation of this within the HSM depends on whether
 *          the operation has started execution yet.  If the operation is still
 *          waiting then it is simply removed from the queue and never even starts.
 *          In this case, when ecy_hsm_Csai_CancelOperation returns there is nothing further
 *          to do except synchronize by calling ecy_hsm_Csai_PollHandle (using the handle of
 *          the job/operation being cancelled), until it returns
 *          @ref ecy_hsm_CSAI_SUCCESS
 *          However, if the operation has already started processing then it will
 *          take some time before it can be stopped.  Again, when
 *          ecy_hsm_Csai_CancelOperation returns there is nothing further to do except
 *          synchronize by calling ecy_hsm_Csai_PollHandle (using the handle of
 *          the job/operation being cancelled) until it returns @ref ecy_hsm_CSAI_SUCCESS
 *
 * @param[in]   hSession        Handle to the session.
 *
 * @return
 *  - ecy_hsm_CSAI_SUCCESS              The call succeeded. The running job is cancelled.
 *  - ecy_hsm_CSAI_ERR_INVALID_HANDLE   The provided session handle is invalid.
 *  - ecy_hsm_CSAI_ERR_TIMEOUT.         The supplied timeout was exceeded before the operation completed.
 *  - ecy_hsm_CSAI_ERR_HSM_SUSPENDED.   The HSM is suspended.
 *  - ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP.  The HSM is not in expected state.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CancelOperation(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 1039]
 * [$Satisfies $ARCH 362] [$Satisfies $ARCH 360] [$Satisfies $ARCH 361] [$Satisfies $ARCH 315]
 * Wait for an operation to complete on a specific handle.
 *
 * This function takes a CSAI job handle and returns when the running operation
 * on that handle has been completed by the HSM. This call can be used as a
 * synchronization barrier by the host.
 *
 * @note
 * This function busy spins the CPU core on which it is executed.
 * An optional safety feature is built into this function that allows the caller
 * to specify a watchdog callback routine that is periodically called while
 * the function busy spins. Should the watchdog return any other value than @c 0
 * then this function immediately returns thereafter with @ref ecy_hsm_CSAI_ERR_CRASH.
 *
 * @warning
 * Giving the function a timout_ms of 0 will cause it to never return successful.
 * It will not busy spin the CPU. Instead it will return ecy_hsm_CSAI_ERR_TIMEOUT or any of the other possible errors.
 *
 * @param[in]   hJob      A handle to the job or operation to wait on
 * @param[in]   watchdog    A pointer to an application watchdog function.
 *                          May be @c NULL_PTR.
 * @param[in]   pParam      A parameter of type void * passed back to the
 *                          watchdog function.
 * @param[in]   timeout_ms  Timeout in miliseconds
 *
 * @return
 *      - ecy_hsm_CSAI_SUCCESS  The operation on the handle has completed.
 *      - ecy_hsm_CSAI_ERR_CRASH. The call has been aborted by the watchdog.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_WaitForHandle(ecy_hsm_Csai_JobHandleT hJob,
                                             CSAI_WatchdogFunctionT  watchdog,
                                             void*                   pParam,
                                             uint32                  timeout_ms);

/**
 * [$DD 1040]
 * [$Satisfies $ARCH 138]
 * Poll for the completion of an operation on a specific job handle.
 *
 * Returns whether an operation is still
 * in progress with that handle or the running operation has completed.
 *
 * @param[in]   handle      A CSAI handle to poll
 *
 * @return
 *      - @ref ecy_hsm_CSAI_SUCCESS  The operation on the handle has completed.
 *      - @ref ecy_hsm_CSAI_FC_PENDING. The operation is still in progress.
 *      - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The specified job handle was invalid.
 *      - CSAI_ERR_XXXXX. A job-specific error indicating that the job completed with an error.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_PollHandle(ecy_hsm_Csai_JobHandleT handle);

/**
 * [$DD 1041]
 * [$Satisfies $ARCH 138]
 * Poll for the completion of an operation on a specific job handle.
 *
 * Returns whether an operation is still
 * in progress with that handle or the running operation has completed.
 * This implementation does NOT update any states as @ref ecy_hsm_Csai_PollHandle does.
 *
 * @param[in]   handle      A CSAI handle to poll
 *
 * @return
 *      - @ref ecy_hsm_CSAI_SUCCESS  The operation on the handle has completed.
 *      - @ref ecy_hsm_CSAI_FC_PENDING. The operation is still in progress.
 *      - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The specified job handle was invalid.
 *      - CSAI_ERR_XXXXX. A job-specific error indicating that the job completed with an error.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_PollStatus(ecy_hsm_Csai_JobHandleT handle);

/**
 * @deprecated This might be deleted in a future major release
 *
 * [$DD 1042]
 * [$Satisfies $ARCH 138][$Satisfies $ARCH 324]
 * Gets the status of the referenced job.
 *
 * Basically takes the output of ecy_HSM_GetOpStatusNonConsuming() and translates it into its own enumeration format.
 *
 * @param[in]   handle      A CSAI handle to poll
 * @param[out]  pStatus     A pointer to a variable of Csai JobStatus Type to store the queried JobStatus
 *
 * @return
 *      - @ref ecy_hsm_CSAI_SUCCESS  The operation on the handle has completed.
 *      - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM A parameter was invalid, e.g. pStatus was NULL pointer.
 *      - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED The HSM is in suspended state, cannot execute the requested operation.
 *      - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP There is a problem with the HSM2HTS (status) register.
 *      - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE  The specified job handle was invalid.
 *
 *      - CSAI_ERR_XXXXX. A job-specific error indicating that the job completed with an error.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetJobStatus(ecy_hsm_Csai_JobHandleT handle, ecy_hsm_Csai_JobStatusT* pStatus);

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
