/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines the public structures and enums used for calls into the
 *        HSM Proxy Client. This is the software layer that talks to the HSM Bridge registers
 * @details This is the public header file for the proxy client
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_PROXY_H
#define ECY_HSM_PROXY_H

/**
 * @addtogroup GROUP_HSM_PROXY_TYPES
 * @{
 */

/* *** includes *******************************************************************************/

#include "Platform_Types.h"
#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_csai_trusted_boot.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_service_basic.h"
#include "ecy_hsm_service_misc.h"

/** Macros to release the bridge resource. If error handling is activated, do not overwrite past errors. Otherwise ignore error code. */
#if (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED)
    /** Macro to release bridge resource */
    #define ecy_HSM_RELEASE_BRIDGE_PORT(_error)                                  \
    if(ecy_hsm_CSAI_SUCCESS == _error)                                           \
    {                                                                            \
        _error = ecy_HSM_ReleaseBridgeResource();                                \
    }                                                                            \
    /* if there was another error, we don't want to overwrite it */              \
    else                                                                         \
    {                                                                            \
        (void)ecy_HSM_ReleaseBridgeResource();                                   \
    }

#else
    /** Macro to release bridge resource */
    #define ecy_HSM_RELEASE_BRIDGE_PORT(_error)                                  \
        (void)ecy_HSM_ReleaseBridgeResource();

#endif /* (ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING == ENABLED) */

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
 * [$DD 1389]
 * This function switches the session handle and the port status pointer for two given CSAI sessions.
 * [$Satisfies $ARCH 871]
 *
 * @details Supports the SHE emulation
 *
 * @param[in,out] ppStatus             Pointer pointer variable to space with the main session status
 * @param[in,out] ppStatus_backup      Pointer pointer variable to space with the backup session status
 * @param[in,out] phSession            Pointer to handle of the main session
 * @param[in,out] phSession_backup     Pointer to handle of the backup session
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
ecy_hsm_Csai_ErrorT ecy_HSM_SessionHotSwap(const volatile HSM_PortStatusT** ppStatus,
                                           ecy_hsm_Csai_SessionHandleT*     phSession,
                                           const volatile HSM_PortStatusT** ppStatus_backup,
                                           ecy_hsm_Csai_SessionHandleT*     phSession_backup);
#endif

/**
 * Get a pointer to the status of the specified session.  This permits much quicker access to the session
 * status than calling an accessor function.
 *
 * @details Supports the SHE emulation, without this we cannot meet the 500ns requirement for SHE_GetStatus.
 *
 * @param[out] ppStatus   Pointer to buffer containing a pointer to the session status
 * @param[in]  hSession   Handle to session to check
 *
 * @returns ecy_hsm_CSAI_SUCCESS
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetSessionStatusPointer(const volatile HSM_PortStatusT** ppStatus, ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 986]
 * Get the status of the specified session. If it is @ref HSM_STATUS_COMPLETE then switches
 * it to @ref HSM_STATUS_IDLE.
 * [$Satisfies $ARCH 316] [$Satisfies $ARCH 115]
 *
 * @details Supports the SHE emulation.
 *
 * @param[in] hSession   Handle to session to check
 *
 * @returns ecy_hsm_CSAI_FC_BUSY or completed operation error code, given type is ecy_hsm_Csai_ErrorT but may in fact be SHE_ErrorCodeT
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetSessionStatus(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 987]
 * TODO Only Tracing added. Check Content of Detailed Design description.
 * Open a session onto the HSM, wait for the acknowledgement
 * [$Satisfies $ARCH 115][$Satisfies $ARCH 117][$Satisfies $ARCH 317]
 * [$Satisfies $SW_ARCH B4A1B6EB][$Satisfies $SW_ARCH 09332870][$Satisfies $SW_ARCH D88D6FF7]
 *
 * @note This functions does not perform any NULL_PTR checks and shall not be called directly.
 *
 * @param priority  Default priority for jobs and operations scheduled through this session
 * @param phSession Pointer to a buffer to receive the session handle
 *
 * @returns Error code returned from the HSM
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_OpenSession(ecy_hsm_Csai_JobPriorityT priority, ecy_hsm_Csai_SessionHandleT* phSession);

#if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)
/**
 * Schedule a non-operation onto the HSM.
 *
 * @details This is used for HSM functions (e.g. SHE_InitRNG) that do nothing, but still to be sync'd
 *          for consistency.
 *
 * @param hSession Session to schedule the operation on
 * @param phJob    Pointer to a buffer to receive the job handle
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS     The call succeeded. The operation is scheduled on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY     Another job is still pending completion in this session.
 *                                  Either finish the previous job or cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *                                  hJob will contain the value CSAI_INVALID_JOB_HANDLE.
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_NopRequest(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_Csai_JobHandleT* phJob);
#endif // if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)

/**
 * [$DD 989]
 * TODO Only Tracing added. Check Content of Detailed Design description}
 * Schedule an operation which does not yet have a job handle
 * [$Satisfies $ARCH 115] [$Satisfies $ARCH 305] [$Satisfies $ARCH 306] [$Satisfies $ARCH 345] [$Satisfies $SW_ARCH 1217] [$Satisfies $SW_ARCH 1218]
 *
 * @param hSession          Session to schedule the operation on
 * @param priority          Priority for the job
 * @param function          Operation function code
 * @param paramBlockSize    Size of the operation parameters block
 * @param pParamBlock       Operation parameters block
 * @param phJob             Pointer to a buffer to receive the job handle
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                The call succeeded. The operation is scheduled on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                Another job is still pending completion in this session.
 *                                             Either finish the previous job or cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *                                             hJob will contain the value CSAI_INVALID_JOB_HANDLE.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE     The parameter is not a valid handle or the used handle has the wrong type.
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT       At least one of the callouts ecy_hsm_pCalloutGetCounterValue or ecy_hsm_pCalloutGetElapsedCounterValue is not set
 */
ecy_hsm_Csai_ErrorT ecy_HSM_OpRequest_NoJobHandle(ecy_hsm_Csai_SessionHandleT hSession,
                                                  ecy_hsm_Csai_JobPriorityT   priority,
                                                  HSM_FunctionT               function,
                                                  uint32                      paramBlockSize,
                                                  const void*                 pParamBlock,
                                                  ecy_hsm_Csai_JobHandleT*    phJob);

#if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)
/**
 * [$DD 990]
 * TODO Only Tracing added. Check Content of Detailed Design description}
 * Schedule an operation which does have a job handle
 * [$Satisfies $ARCH 115][$Satisfies $ARCH 305][$Satisfies $ARCH 306][$Satisfies $ARCH 345]
 *
 * @param hJob              Job to schedule the operation on
 * @param function          Operation function code
 * @param paramBlockSize    Size of the operation parameters block
 * @param pParamBlock       Operation parameters block
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded. The operation is scheduled on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                 Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE      The parameter is not a valid handle or the used handle has the wrong type.
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_OpRequest_WithJobHandle(ecy_hsm_Csai_JobHandleT hJob,
                                                    HSM_FunctionT           function,
                                                    uint32                  paramBlockSize,
                                                    const void*             pParamBlock);
#endif // if (ENABLED == ecy_hsm_ENABLE_LEGACY_HOST_PROXY_INTERFACES)

/**
 * [$DD 991]
 * Get the status of the specified operation/job, it is one of type @ref HSM_PortStatusT.
 * Also get the error code of the last operation, if that operation has just completed
 * (if *pStatus == @ref HSM_STATUS_COMPLETE)
 * [$Satisfies $ARCH 138]
 *
 * @details This function will return HSM_STATUS_COMPLETE and the operation error code only once, after which the
 *          operation is considered complete, the port status becomes HSM_STATUS_IDLE and the error code is cleared to @ref ecy_hsm_CSAI_SUCCESS
 *
 * @param hJob      Handle to the job of which we want the status
 * @param pStatus   Pointer to a variable to receive the status
 * @returns         Error code returned from the HSM, unless some parameter of the call is invalid in which case the error code indicates that
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetOpStatus(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus);

/**
 * option flag to allow NONE
 */
#define ecy_hsm_OPT_NONE (0U)

/**
 * option flag to allow state change COMPLETE -> IDLE
 */
#define ecy_hsm_OPT_STAT_IDLE (1UL << 0UL)

/**
 * option flag to reset error code to ecy_hsm_CSAI_SUCCESS
 */
#define ecy_hsm_OPT_RESET_ERR (1U << 1UL)
/**
 * [$DD 992]
 * TODO Only Tracing added. Check Content of Detailed Design description}
 * Get the status of the specified operation/job without consuming it, it is one of type @ref HSM_PortStatusT.
 * [$Satisfies $ARCH 358]
 *
 * @details This function will return the current HSM_PortStatusT of the port related to the given job handle hJob.
 *
 * @param hJob Handle to the job of which we want the status
 * @param pStatus Pointer to a variable to receive the status
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded. The current port status was written via pStatus.
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP      HSM is not properly initialized.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE      The parameter is not a valid handle or the used handle has the wrong type.
 *
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetOpStatusNonConsuming(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus);

/**
 * [$DD 993]
 * Get the status of the specified operation/job, it is one of type @ref HSM_PortStatusT.
 * Also get the error code of the last operation, if that operation has just completed
 * (if *pStatus == @ref HSM_STATUS_COMPLETE)
 * [$Satisfies $ARCH 115] [$Satisfies $ARCH 330] [$Satisfies $ARCH 337]
 *
 * @details This function will return HSM_STATUS_COMPLETE and the operation error code only once, after which the
 *          operation is considered complete, if allowed the port status becomes HSM_STATUS_IDLE and the error code is
 *          cleared to @ref ecy_hsm_CSAI_SUCCESS
 *
 * @param hJob      Handle to the job of which we want the status
 * @param pStatus   Pointer to a variable to receive the status
 * @param options   bitmask of options to allow changing state COMPLETE -> IDLE and error code clearance?
 *                  @see ecy_hsm_OPT_STAT_IDLE, @see ecy_hsm_OPT_RESET_ERR
 * @returns         Error code returned from the HSM, unless some parameter of the call is invalid in which case the
 *                  error code indicates that
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_ReadOpStatus(ecy_hsm_Csai_JobHandleT hJob, HSM_PortStatusT* pStatus, uint32 options);

/**
 * [$DD 994]
 * Get a flag indicating whether the current operation of the specified job has completed with ecy_hsm_CSAI_SUCCESS
 * [$Satisfies $ARCH 138]
 *
 * @details     This function checks the port status.  If it is HSM_STATUS_COMPLETE then it changes
 *              it to HSM_STATUS_IDLE.
 *
 * @param hJob  Handle to the job of which we want the status
 * @returns     TRUE if last operation of the job has completed with ecy_hsm_CSAI_SUCCESS, else FALSE
 *
 */
boolean ecy_HSM_IsOpFinishedOK(ecy_hsm_Csai_JobHandleT hJob);

/**
 * Get the error code returned by the last operation of the specified job, or if the job is not
 * complete then returns @ref ecy_hsm_CSAI_FC_PENDING.  When returning an error code adds the @ref ecy_hsm_CSAI_ERR_FLAG_PREVIOUS_OP
 * flag to indicate that the error pertains to the completed operation, not the one being scheduled.
 *
 * @param hJob Handle to the job of which we want the status
 * @returns @ref ecy_hsm_CSAI_FC_PENDING or error code as described above
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetOpCode(ecy_hsm_Csai_JobHandleT hJob);

/**
 * [$DD 996]
 * Wait for the specified operation/job to complete
 * [$Satisfies $ARCH 360]
 *
 * @param hJob Handle to the job to wait for
 * @param millisecondsToWait Number of milliseconds to wait for before timing out
 *
 * @returns Timeout, or error code returned from the HSM, unless some parameter is invalid in which case the error code indicates that
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_WaitForOpToComplete(ecy_hsm_Csai_JobHandleT hJob, uint16 millisecondsToWait);

/**
 * [$DD 997]
 * Cancel the operation which is currently running or waiting to run on the given session. This
 * uses a dedicated HSM signal to cancel a pending or processing operation on a given session.
 * [$Satisfies $ARCH 115] [$Satisfies $ARCH 868]
 *
 * @details This is different to cancelling a job because a job consists of a start, an update
 *          and a finish, and cancelling it means reseting the HSM state machine so that it is
 *          waiting for another start.  You cannot cancel a job until the current operation of
 *          that job is complete, whereas you can cancel an operation at any time.
 *
 * @param[in] hSession Handle to the session for which the operation is to be cancelled
 *
 * @returns Error code returned from the HSM
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_CancelOp(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 998]
 * Attempt to route a request via the "Quick" path.
 * MUST be called with the HSM Bridge resource locked
 * [$Satisfies $ARCH 115] [$Satisfies $ARCH 331] [$Satisfies $ARCH 339]
 *
 * The function shall actively wait for the HSM Core to respond to the Quick Route ISR
 * (@ref HSM_STATUS_COMPLETE == host2HSM_BridgePorts[hSession].status).
 *
 * In case of MAC verification (@p function == @ref HSM_FUNC_CMAC_VERIFY) the function shall return
 * a pointer to the verification result via @p pParamBlock.
 *
 * In case of MAC generation (@p function == @ref HSM_FUNC_CMAC_GENERATE) the HSM_Client shall return
 * a pointer to the generated MAC via @p pParamBlock.
 *
 * @details The "Quick" path uses a dedicated Cat1 ISR (where hardware permits) to bypass the usual
 *          overhead in operation scheduling.  The operation is executed directly within the ISR
 *          context.  Depending on the state of the hardware, the request may be rejected with a
 *          ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE error.
 *
 * @param[in]  hSession        Handle to the session for the operation
 * @param[in]  function        Operation function code
 * @param[in]  paramBlockSize  Size of the parameter block
 * @param[in]  pParamBlock     Pointer to the parameter block
 * @param[out] phJob           Pointer to buffer to receive the job handle (optional: can be a @c NULL_PTR)
 *
 *
 * @returns Error code returned from the HSM. This is the request error code.
 *  - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded without errors
 *  - @ref ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE  The HSM's internal state meant that the quick route could not be used
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            An invalid session was used
 *  - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED             The HSM is in suspended mode
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM             Invalid arguments (e.g. NULL_PTR)
 *  - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE           paramBlockSize is bigger than HSM_OP_PARAM_BLOCK_SIZE
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT              The HSM Proxy callouts have not been configured (the pointer is NULL_PTR)
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                   An unexpected timeout occurred while trying to communicate with the HSM
 *  - else                                            Error code returned form Quick route call
 */
ecy_hsm_Csai_ErrorT ecy_HSM_QuickRoute(ecy_hsm_Csai_SessionHandleT hSession,
                                       HSM_FunctionT               function,
                                       uint32                      paramBlockSize,
                                       void* const                 pParamBlock,
                                       ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1002]
 * Dedicated function to the truncation required for Quick CMAC.
 * Done here because the Quick CMAC buffers are in this file scope, also its quicker on the host
 * core than the HSM core.
 * [$Satisfies $ARCH 114]
 *
 * @param[in] hSession            Handle to the session
 * @param[in] truncatedLengthBits Required length of the MAC in bits.  The ASW provided buffer may not be shorter
 *                                than this rounded up to the next full byte. The highest useful bit length is AES_BLOCK_SIZE_BITS for CMAC and
 *                                ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BITS for SipHash 2-4.
 * @param[in] truncationAllowed   True if it is permitted to truncate the MAC, if FALSE and truncatedLengthBits
 *                                is insufficient, then an error is returned and nothing is copied.
 * @param[out] pDestination       Pointer to where the MAC should be copied to (This cannot be NULL_PTR)
 * @param[out] pMacCountBytes     Pointer to buffer to receive the number of bytes actually written
 * @param[in]  algorithm          Defines the algorithm which calculated the MAC
 *
 * @note   The error code is returned via a subsequent call to ecy_hsm_Csai_PollHandle( ), the possible error codes are:
 *  - @ref ecy_hsm_CSAI_SUCCESS              The call succeeded without errors.
 *  - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL The host provided buffer was too small and nothing was copied.
 *
 */
void ecy_HSM_TruncateAndCopyMac(ecy_hsm_Csai_SessionHandleT hSession,
                                uint32                      truncatedLengthBits,
                                boolean                     truncationAllowed,
                                uint8*                      pDestination,
                                uint32*                     pMacCountBytes,
                                ecy_hsm_Csai_MACAlgorithmT  algorithm);

/**
 * Dedicated function to a copy required for the Quick CMAC Verification.
 * Done here because the session specific Quick CMAC buffers are in this file scope.
 * Using a fixed buffer for the verification result flag saves 1us because it removes a pointer check.
 *
 * @param[out] pMacResultFlag     Pointer to where the flag should be copied to.
 * @param[in]  hSession           Handle to the session in which the job is placed.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.      Either hSession is greater than maxHostHsmSessions or pMacResultFlag was NULL_PTR.
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_CopyResultFlag(uint32* pMacResultFlag, ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 1004]
 * TODO Only Tracing added. Check Content of Detailed Design description
 * Get the value of whatever counter has been configured through ecy_HSM_ConfigureCallouts.
 * In the case of the internal proxy, the counter used is the MillisecondCounter.
 * [$Satisfies $ARCH 116]
 *
 * @param pStartingValue Pointer to uint32 buffer to receive the current value of the counter.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded. A counter value has been written to *pStartingValue.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.      pStartingValue was NULL_PTR.
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetCounterValue(uint32* pStartingValue);

/**
 * [$DD 1005]
 * TODO Only Tracing added. Check Content of Detailed Design description
 * Get the difference between value and the value of whatever counter has been configured through ecy_HSM_ConfigureCallouts.
 * In the case of the internal proxy, the counter used is the MillisecondCounter.
 * [$Satisfies $ARCH 116]
 *
 * @param value Pointer to uint32 buffer to receive the current value of the counter.
 * @param pElapsedValue Pointer to uint32 buffer to receive the current value of the counter.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call succeeded. A counter value has been written to *pStartingValue.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.      pElapsedValue was NULL_PTR.
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetElapsedCounterValue(uint32 value, uint32* pElapsedValue);

/**
 * [$DD 1006]
 * Function to give access to the HSM Bridge resource locking callout that the user should provide
 * through @ref ecy_HSM_ConfigureCallouts
 *
 * [$Satisfies $ARCH 197]
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                                     The call succeeded.
 *  - @ref ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED.       The resource was already locked.
 */
ecy_hsm_Csai_ErrorT ecy_HSM_GetBridgeResource(void);

/**
 * [$DD 1755]
 * Function to give access to the HSM Bridge resource locking callout that the user should provide
 * through @ref ecy_HSM_ConfigureExtendedCallouts. Mainly used for external callouts needed by external teams
 *
 * [$Satisfies $SW_ARCH F71C604A]
 */
void ecy_hsm_FunctionIRQHandling(void);

/**
 * [$DD 1007]
 * Function to give access to the HSM Bridge resource unlocking callout that the user should provide
 * through @ref ecy_HSM_ConfigureCallouts
 *
 * [$Satisfies $ARCH 197]
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                                     The call succeeded.
 *  - @ref ecy_hsm_CSAI_ERR_RESOURCE_ALREADY_LOCKED_UNLOCKED.       The resource was already unlocked.
 */
ecy_hsm_Csai_ErrorT ecy_HSM_ReleaseBridgeResource(void);

/**
 * Get the HSM's current operating mode
 *
 * @return The HSM operating mode
 */
HSM_ModeT ecy_HSM_GetMode(void);

/**
 * Get the verification table's address
 *
 * @return Pointer to the verification table
 */
volatile ecy_hsm_Host_TB_VerifTableT *HSM_GetTBVerifTable(void);

/**
 * [$DD 1008]
 * @brief Configure the HSM, wait for the acknowledgement
 * [$Satisfies $SW_ARCH 437_v1]
 *
 * @note The parameters are currently ignored by the HSM. No error information data will be written to the given buffer.
 *
 * @param[in] errorMessageBuffer If you would like the HSM to write textual error messages to a buffer in
 *                                shared memory after critical errors, provide a pointer here to a byte buffer.
 *                                Otherwise simply pass NULL_PTR.
 *
 *
 * @param[in] errorMessageBufferLength Provide the size of the errorMessageBuffer. If the errorMessageBuffer is NULL_PTR
 *                                     then pass 0 buffer size.
 * @returns Error code returned from the HSM
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_Configure(uint8* errorMessageBuffer, uint32 errorMessageBufferLength);

/**
 * @}
 */

/**
 * @addtogroup GROUP_CSAI_SECFLASH
 * @{
 * Secure flash programming API
 *
 */

/**
 * @addtogroup GROUP_MGMT_SUSPENDMODE
 * @{
 * functions for handling the HSM suspended mode
 */

/**
 * @brief Trigger a HSM jump to RAM execution, while the HSM runs in Core application
 *
 * [$DD 123]
 * The HSM Core application is suspended, i.e. regular HSM services are not supported anymore.
 * [$Satisfies $ARCH 450] [$Satisfies $ARCH 115]
 *
 * While the HSM is running from RAM, the host may start a host flash reprogramming operation in the same flash bank
 * that is used for the HSM code.
 *
 * This is a synchronous interface. When it returns successfully the HSM is running from RAM.
 *
 * The HSM automatically returns to the Core application after a (configurable, default = 500ms) timeout, since the
 * suspended mode is intended to be a temporary mode (it should be avoided that the HSM remains suspended forever by
 * mistake).
 * The host can keep the HSM in RAM by calling the @ref ecy_hsm_Mgmt_SuspendKeep function before timeout expiration.
 * The host can trigger an immediate return to the Core application by calling the @ref ecy_hsm_Mgmt_SuspendLeave function.
 *
 * @note Because of additional checks performed, this function might actually take longer than the specified timeout and still succeed.
 *
 * @param[in]   numMsTimeout        Timeout[ms] when waiting for HSM to run in RAM. Must not be 0.
 * @note This values is <i>not</i> the time the CycurHSM core will remain in suspended mode but the time the host-side code will wait for
 *       the CycurHSM core to <i>acknowledge</i> the request to switch to suspended mode.
 * @param[out]  pFirstChallengeVal  First challenge to use for the next call to @ref ecy_hsm_Mgmt_SuspendKeep
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded. HSM is ready for programming sequence.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               One of the provided parameters is incorrect
 *  - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED               The HSM is already suspended
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP              The HSM is in an undefined state (possibly crashed)
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                     The provided timeout has expired
 *  - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED              Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Mgmt_SuspendKeep, ecy_hsm_Mgmt_SuspendLeave
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendStart(uint32 numMsTimeout,
                                              uint32 *pFirstChallengeVal);

/**
 * @brief Keep the HSM in the suspended mode (RAM execution)
 *
 * [$DD 124]
 * If it is running in RAM, the delay after which the HSM automatically returns to the Core mode is reset.
 * [$Satisfies $ARCH 451] [$Satisfies $ARCH 115]
 *
 * This is a synchronous interface. When it returns successfully the HSM is running from RAM.
 * The HSM automatically returns to the Core application after a (configurable, default = 500ms) timeout, since the
 * suspended mode is intended to be a temporary mode (it should be avoided that the HSM remains suspended forever by
 * mistake).
 * The host can keep the HSM in RAM by calling the @ref ecy_hsm_Mgmt_SuspendKeep function before timeout expiration.
 * The host can trigger an immediate return to the Core application by calling the @ref ecy_hsm_Mgmt_SuspendLeave function.
 *
 * @note Because of additional checks performed, this function might actually take longer than the specified timeout and still succeed.
 *
 * @param[in]   numMsTimeout        Timeout[ms] when waiting for HSM to answer the request. Must not be 0.
 * @note This values is <i>not</i> the time the CycurHSM core will remain in suspended mode but the time the host-side code will wait for
 *       the CycurHSM core to <i>acknowledge</i> the request to remain in suspended mode.
 *
 * @param[in]   responseVal         expected response to the preceding challenge received in the previous call either
 *                                  to @ref ecy_hsm_Mgmt_SuspendStart or to @ref ecy_hsm_Mgmt_SuspendKeep
 *                                  if this response is not correct, the function returns an error and the timeout is not reset
 *                                  (Algorithm: response = ~challenge)
 * @param[out]  pNewChallengeVal    Challenge to use for the next call to @ref ecy_hsm_Mgmt_SuspendKeep
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               One of the provided parameters is incorrect
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE               The HSM is not running in suspended mode
 *  - @ref ecy_hsm_CSAI_ERR_INCONSISTENT_PARAM_SET      The provided response is incorrect
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                     The provided timeout has expired
 *  - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED              Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 *
 * @see ecy_hsm_Mgmt_SuspendStart, ecy_hsm_Mgmt_SuspendLeave
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendKeep(uint32 numMsTimeout,
                                             uint32 responseVal,
                                             uint32 *pNewChallengeVal);

/**
 * @brief Stop the HSM suspended mode, return to the Core application
 *
 * [$DD 125]
 * If it is running in RAM, the HSM immediately returns to the Core application. If the HSM is already running the Core
 * application, the function does nothing and returns successfully.
 * [$Satisfies $ARCH 452] [$Satisfies $ARCH 115]
 *
 * This is a synchronous interface. When it returns successfully the HSM is running the Core application.
 *
 * @note Because of additional checks performed, this function might actually take longer than the specified timeout and still succeed.
 *
 * @param[in]   numMsTimeout      Timeout[ms] when waiting for HSM to answer the request. Must not be 0.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               One of the provided parameters is incorrect
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                     The provided timeout has expired
 *  - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED              Security critical functions are currently disabled
 *                                                      (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Mgmt_SuspendLeave(uint32 numMsTimeout);

/**
 * @brief Disables security critical functions
 *
 * [$DD 1474]
 * If the HSM is already running suspend mode, this function will run from RAM.
 * [$Satisfies $ARCH 115][$Satisfies $ARCH 141]
 *
 * @note At the moment SECCRIT_DISABLE_ALL_MASK is set, disables all security critical functions at once.
 *
 * @param[in]  hSession         Handle to session for the operation
 * @param[in]  paramBlockSize   Size of the parameter block - for future use
 * @param[in]  pParamBlock      Pointer to the parameter block- for future use
 * @param[out] phJob            Pointer to buffer to receive the job handle (optional: can be a @c NULL_PTR)
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM               One of the provided parameters is incorrect
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                     The provided timeout has expired
 *
 */
ecy_hsm_Csai_ErrorT ecy_HSM_DoDisableSecCritFunctions(ecy_hsm_Csai_SessionHandleT hSession,
                                                      uint32                      paramBlockSize,
                                                      const void*                 pParamBlock,
                                                      ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * @brief Configure secure debug related buffer to be used for debug authentication
 *
 * [$DD 2627]
 * Configure the data buffer to be used for Challenge and Response data exchange to support the debug authentication
 * [$Satisfies $ARCH 115] [$Satisfies $SW_ARCH 6F465323]
 *
 * @note currently only available on Renesas (P1x and U2A) devices.
 *
 * @param[in, out] pSecureDebugParam    Pointer to the structure containing secured debug buffer details
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                         The call succeeded
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                     The provided timeout has expired
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED               The given function is not supported by this HSM build
 */
ecy_hsm_Csai_ErrorT ecy_hsm_SecDebug_ConfigureBuffer(HSM_SecureDebugConfigureParamsT* pSecureDebugParam);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_CSAI_SUSPENDMODE
/** @} */// GROUP_CSAI_SECFLASH


#endif /* Multiple inclusion lock  */
