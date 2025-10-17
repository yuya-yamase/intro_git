/**
 * @file
 ***********************************************************************************************
 * @brief CSAI session management.
 * This header file declares functions to manage a session with the HSM.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_SESSION_H
#define ECY_HSM_CSAI_SESSION_H

/**
 * @addtogroup GROUP_CSAI_SESSION_MANAGEMENT
 * @{
 */

/* *** includes *******************************************************************************/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#endif /* #if defined(GUAM) */
#include "ecy_hsm_csai_types.h"

/* *** defines ********************************************************************************/

/**
 * @anchor ANCHOR_CSAI_SESSION_FLAGS
 * @name   CSAI Session Flags
 * @brief  Predefined values that are or'ed into the @c flags member of @c ecy_hsm_Csai_SessionStatusT.
 * @{
 */

/** Valid login credentials have been provided to the session and the session is privileged */
#define ecy_hsm_CSAI_SESSION_FLAG_PRIV          (1U)
/** A job is currently running on this session */
#define ecy_hsm_CSAI_JOB_RUNNING                (2U)

/** @} */

/* Switch the ecy_hsm_Csai_CloseSession() API between synchronous & asynchronous interfaces according to the configuration */
#if (CYCURHSM_CONFIG_WITH_CLOSESESSION_LEGACY == ENABLED)
/* the synchronous (=legacy) CloseSession interface shall be used (compatible with older CycurHSM versions) */
#if !defined(GUAM)
/* PRQA S 3115 2 */ /* <Deviation: rule_20.13_3115 */
#warning "Calling ecy_hsm_Csai_CloseSession without polling handle is no longer recommended."
#warning "For further information please refer to the CycurHSM 2.x User Guide, chapter 4.10.2"
#endif
#define ecy_hsm_Csai_CloseSession(hSession)             ecy_hsm_Csai_CloseSessionSync(hSession)
#else
/* the asynchronous CloseSession interface shall be used (recommended for better reliability) */
#define ecy_hsm_Csai_CloseSession(hSession, phJob)      ecy_hsm_Csai_CloseSessionAsync(hSession, phJob)
#endif

/* *** type declarations **********************************************************************/

/** An aggregated type holding CSAI session status information */
typedef struct ecy_hsm_Csai_SessionStatusTag
{
    uint16 slotID;          /**< Unique slot ID of this session                 */
    uint8  keyCount;        /**< Number of keys loaded into the session context */
    uint8  reserved;        /**< Reserved field                                 */
    uint32 flags;           /**< A combination of session flags                 */
} ecy_hsm_Csai_SessionStatusT;

/** @deprecated Define known session modes. No longer functional; exists only for backward
  * compatibility of the @ref ecy_hsm_Csai_OpenSession interface. */
typedef enum ecy_hsm_CSAI_SessionModeTag
{
    /**
     * This has no effect, and should be supplied by default to the interface
     * @ref ecy_hsm_Csai_OpenSession.
     * All HSM services now run asynchronously to the main core and do not
     * block. To synchronize HSM services, @ref ecy_hsm_Csai_WaitForHandle
     * should be used where blocking of the calling host core task is desired,
     * whereas @ref ecy_hsm_Csai_PollHandle should be used if it is not.
     */
    ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING = 1u,

    /**
     * No longer functional and should not be used.
     */
    ecy_hsm_CSAI_SESSION_MODE_BLOCKING = 2u,

    /**< Value defined to use memory size of uint32 for enums */
    ecy_hsm_CSAI_SESSION_MODE_RESERVED = 0x7fffffffu
} ecy_hsm_Csai_SessionModeT;

/**
 * A function pointer type to a user supplied watchdog function
 * The watchdog function should normally return zero, if it returns anything
 * else then the function which has called it (generally @ref ecy_hsm_Csai_WaitForHandle)
 * will stop waiting and return.
 */
typedef uint32(*CSAI_WatchdogFunctionT)(void *param);


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
 * [$DD 981]
 * Open a new session with the HSM. Returns a session handle to the caller.
 * [$Satisfies $ARCH 125] [$Satisfies $ARCH 136] [$Satisfies $ARCH 317] [$Satisfies $SW_ARCH 8B07130B]
 *
 * @details This is always a blocking (synchronous) call
 *
 * @param[in]   mode            Session mode. Defunct (exists for backward compatibility); use ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING.
 * @param[in]   initialPriority Initial priority for session
 * @param[out]  phSession       Receives the handle to the open session. This handle must be used
 *                              in subsequent calls to the CSAI for all calls concerning this
 *                              session.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS
 *    The call was successful. The session is open and @c hSession can be used in subsequent
 *    calls to the API.
 *  - @ref ecy_hsm_CSAI_ERR_OUT_OF_SESSION_PORTS
 *    The call failed because there are no free ports available.
 *    phSession will be populated with @ref ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_OpenSession(ecy_hsm_Csai_SessionModeT    mode,
                                           ecy_hsm_Csai_JobPriorityT    initialPriority,
                                           ecy_hsm_Csai_SessionHandleT* phSession);

/**
 * [$DD 982]
 * Query the session status on the HSM.
 * [$Satisfies $ARCH 130]
 *
 * @param[in]  hSession    Handle of the privileged session.
 * @param[out] pStatus     Pointer to space where this function can store
 *                         the session status.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS  The call was successful. The session is privileged.
 *  - @ref ecy_hsm_CSAI_FC_PENDING. The call is pending on the HSM.
 *  - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE. The provided pin buffer is too large.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_CREDENTIALS. The provided credentials are invalid.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_GetSessionStatus(ecy_hsm_Csai_SessionHandleT  hSession,
                                                ecy_hsm_Csai_SessionStatusT* pStatus);

/**
 * [$DD 983]
 * Close an open session and release all resources associated with the session on the HSM.
 * [$Satisfies $ARCH 137]
 *
 * @details This is a synchronous call (active wait), when it returns the session has been closed.
 *          It may return a timeout error when the HSM is too busy to process the request (default value: 10ms).
 *          Beware of the potential watchdog / task scheduling violation issues because of the (up to 10ms) active wait.
 *          Therefore it is recommended to use the asynchronous interface ecy_hsm_Csai_CloseSessionAsync() instead.
 *
 * Note: ecy_hsm_Csai_CloseSession() is mapped to ecy_hsm_Csai_CloseSessionSync() when CYCURHSM_CONFIG_WITH_CLOSESESSION_LEGACY==1
 *
 * @param[in]   hSession    The handle of the session to close.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call was successful. The session is closed and @c hSession
 *                                              is now an invalid session handle.
 *  - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED      The session was found to be closed.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE      The call was not successful. The given handle was invalid.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT             The call timed out.
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP      The HSM is locked up.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                 Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob. Call CSAI_CloseSession again when the session is idle.
 *
 */

ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CloseSessionSync(ecy_hsm_Csai_SessionHandleT hSession);

/**
 * [$DD 984]
 * Close an open session and release all resources associated with the session on the HSM.
 * [$Satisfies $ARCH 137]
 *
 * @details This is an asynchronous call, it returns before the close operation has completed.
 * Finalization and result query:
 *      The caller finishes and polls for the result of the close session operation using
 *      @ref ecy_hsm_Csai_PollHandle
 *
 * Note: ecy_hsm_Csai_CloseSession() is mapped to ecy_hsm_Csai_CloseSessionAsync() when CYCURHSM_CONFIG_WITH_CLOSESESSION_LEGACY==0
 *
 * @param[in]   hSession    The handle of the session to close.
 * @param[out]  phJob       Receives the job handle of the initialized job.
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                 The call was successful. The session is closed and @c hSession
 *                                              is now an invalid session handle.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE      The call was not successful. The given handle was invalid.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT             The call timed out.
 *  - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP      The HSM is locked up.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                 Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job
 *                                              using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE       The call was not successful. The given handle was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED       The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_HSM2HTS_LOCKUP       The HSM is locked up.
 */

ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_CloseSessionAsync(ecy_hsm_Csai_SessionHandleT hSession, ecy_hsm_Csai_JobHandleT *phJob);


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
