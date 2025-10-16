/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure Log.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for interacting with the HSM secure logging interface of the CycurHSM.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2019, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_SECLOG_H
#define ECY_HSM_CSAI_SECLOG_H

/**
 * @addtogroup GROUP_CSAI_SECLOG
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_keyid.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_vms_pub_data.h"
/* *** defines ********************************************************************************/
/**< Value of the MASK used to filter the bit from status byte */
#define ecy_hsm_CSAI_SECLOG_STATUS_BYTE_MASK                          (0x03)
/** Event visibility for new event **/
#define ecy_hsm_CSAI_SECLOG_EVENT_VISIBILITY_NEW                      (0x01)
/** Event visibility for history event **/
#define ecy_hsm_CSAI_SECLOG_EVENT_VISIBILITY_HISTORY                  (0x02)

/**
 * @brief Enum for the different sw part verification failures modes @c failureCause
 * in @c ecy_hsm_Csai_SecLog_ExtendedLogDataT, The values within this enum must fit an unsigned nibble up to 16.
 */
typedef enum ecy_hsm_Csai_Seclog_Extended_FailureTypeTag
{
    ecy_hsm_Csai_SECLOG_EXTENDED_TB_FAILURETYPE_CMAC        =  0x1U,  /**< indicates sw part cmac verification failure                                       */
    ecy_hsm_Csai_SECLOG_EXTENDED_TB_FAILURETYPE_CERTIFICATE =  0x2U,  /**< indicates sw part certificate parsing failure or certificate verification failure */
    ecy_hsm_Csai_SECLOG_EXTENDED_TB_FAILURETYPE_SIGNATURE   =  0x4U,  /**< indicates sw part signature verification failure during TABS                      */

    ecy_hsm_Csai_SECLOG_EXTENDED_TB_FAILURETYPE_RESERVED    =  16U,   /**< indicates sw part verification failure maximum value                              */
}ecy_hsm_Csai_Seclog_Extended_FailureTypeTagT;
/* *** type declarations **********************************************************************/
typedef struct ecy_hsm_Csai_SecLog_TimestampTag
{
    uint16 reservedBytes;     /**< Padding 16 bits for alignment */
    uint16 totalEventCounter; /**< Total counter of events within the same power cycle */
    uint32 powerCounter;      /**< Power cycle count */
} ecy_hsm_Csai_SecLog_TimestampT;

typedef struct ecy_hsm_Csai_SecLog_Extended_TimestampTag
{
    uint32 totalEventCounter; /**< Total counter of events within the same power cycle */
    uint32 powerCounter;      /**< Power cycle count */
} ecy_hsm_Csai_SecLog_Extended_TimestampT;
typedef struct ecy_hsm_Csai_SecLog_EventEntryTag
{
    uint8                          eventId;              /**< Out: ID for the specific event */
    uint8                          reservedBytes;        /**< Out: Padding byte for alignment */
    uint16                         eventCounter;         /**< Out: Counter of the occurrences of the event */
    ecy_hsm_Csai_SecLog_TimestampT timestamp;            /**< Out: Timing based identifier of the occurred event */
} ecy_hsm_Csai_SecLog_EventEntryT;

/* PRQA S 0635 ++ */ /* Deviation: Bitfields are accepted by design in this structure */
typedef struct ecy_hsm_Csai_Seclog_ExtendedLogDataTag
{
    uint8          swPartID;                             /**< ID of the SW part that failed during verification */

    uint8          failureMode:4;                        /**< The boot mode during the verification failure of the sw part @ref ecy_hsm_Csai_TB_ModeT 
                                                               e.g. @ref ecy_hsm_Csai_TB_TRUSTED_BOOT_MODE*/

    uint8          failureCause:4;                       /**< The cause of the failure during verification of the sw part @ref ecy_hsm_Csai_Seclog_Extended_FailureTypeTagT 
                                                               e.g. @ref ecy_hsm_Csai_SECLOG_EXTENDED_TB_FAILURETYPE_CMAC*/
}ecy_hsm_Csai_SecLog_ExtendedLogDataT;
/* PRQA S 0635 -- */ 

typedef struct ecy_hsm_Csai_SecLog_Extended_EventEntryTag
{
    uint8                                   eventId;            /**< Out: ID for the specific event */
    uint8                                   statusByte;         /**< Out: user specific byte for the event entry visibility to be set as @ref ecy_hsm_CSAI_SECLOG_EVENT_VISIBILITY_NEW and @ref ecy_hsm_CSAI_SECLOG_EVENT_VISIBILITY_HISTORY */
    ecy_hsm_Csai_SecLog_ExtendedLogDataT    extendedLogData;    /**< Out: Extended data used in the seclog extended mode to report the root cause of the sw part verification failure */
    uint32                                  eventCounter;       /**< Out: Counter how often an event */
    ecy_hsm_Csai_SecLog_Extended_TimestampT timestamp;          /**< Out: Timing based identifier of the occurred event */
} ecy_hsm_Csai_SecLogEventEntryFptT;

/**
 * @brief List of all the internal and external event IDs.
 */

typedef enum ecy_hsm_Csai_SeclogExt_UseCase
{
    ecy_hsm_CSAI_SeclogExt_USECASEID_BASIC    = 0,             /**< Basic Seclog id                                                                        */
    ecy_hsm_CSAI_SeclogExt_USECASEID_FPT      = 1,             /**< FPT Seclog extended id for the use case of the FPT seclog data structures              */
    ecy_hsm_CSAI_SeclogExt_USECASEID_RESERVED = 0x7FFFFFFFUL   /**< Reserved value to enforce long enums                                                   */
} ecy_hsm_Csai_SeclogExt_UseCaseT;

typedef struct ecy_hsm_Csai_SecLogReadExt_BasicTag
{
    uint8                                   eventId;               /**< In:  Id of the event to be queried.                                     */
    ecy_hsm_Csai_SecLog_EventEntryT*        pLogEntries;           /**< Out: Pointer to buffer to receive the secure log entries.               */
    uint32                                  logEntriesNumBytes;    /**< In:  Length, in bytes, of the buffer to receive the secure log entries. */
    uint32*                                 pLogEntriesCount;      /**< Out: Pointer to buffer to receive the number of log entries.            */
}ecy_hsm_Csai_SecLogReadExt_Basic;

typedef struct ecy_hsm_Csai_SecLogReadExt_FPTTag
{
    uint8                                            eventId;               /**< In:  Id of the event to be queried.                                     */
    ecy_hsm_Csai_SecLogEventEntryFptT*               pLogEntries;           /**< Out: Pointer to buffer to receive the secure log entries.               */
    uint32                                           logEntriesNumBytes;    /**< In:  Length, in bytes, of the buffer to receive the secure log entries. */
    uint32*                                          pLogEntriesCount;      /**< Out: Pointer to buffer to receive the number of log entries.            */
}ecy_hsm_Csai_SecLogReadExt_FPT;

/* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here */
typedef union  ecy_hsm_Csai_SecLogReadExt_ParamTag
{
    ecy_hsm_Csai_SecLogReadExt_Basic   secLogReadExt_Parambasic;           /**< Basic version of the seclog read extended parameters  */
    ecy_hsm_Csai_SecLogReadExt_FPT     secLogReadExt_Paramfpt;             /**< FPT version of the seclog read extended parameters    */   
}ecy_hsm_Csai_SecLogReadExt_ParamT;

typedef struct ecy_hsm_Csai_SecLogReadExt_UseCaseAndParamTag
{
    ecy_hsm_Csai_SeclogExt_UseCaseT     useCaseId;             /**< In: Use case id of which extended seclog mode to be used  */              
    ecy_hsm_Csai_SecLogReadExt_ParamT   secLogReadExtParam;    /**< Seclog read extended parameters                           */
}ecy_hsm_Csai_SecLogReadExt_UseCaseAndParamT;

typedef struct ecy_hsm_Csai_SecLogWriteExt_V0Tag
{
    uint8            eventId;               /**< In:  Id of the event to be logged using extended seclog write.                      */  
    const void*      pContextData;          /**< In: Pointer to the buffer that includes the data of the event to be logged.         */
    uint32           contextDataNumBytes;   /**< length in bytes of the buffer that includes the data of the event to be logged.     */
}ecy_hsm_Csai_SecLogWriteExt_V0;

/* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here */
typedef union  ecy_hsm_Csai_SecLogWriteExt_ParamTag
{
    ecy_hsm_Csai_SecLogWriteExt_V0 secLogWriteExt_ParamV0;  /**< In, Out: Version zero of the seclog write extended parameters  */
}ecy_hsm_Csai_SecLogWriteExt_ParamT;

typedef struct ecy_hsm_Csai_SecLogWriteExt_UseCaseAndParamTag
{
    ecy_hsm_Csai_SeclogExt_UseCaseT      useCaseId;             /**< In:      Use case id of which extended seclog mode to be used  */ 
    ecy_hsm_Csai_SecLogWriteExt_ParamT   secLogWriteExtParam;   /**< In, Out: Seclog write extended parameters                      */
}ecy_hsm_Csai_SecLogWriteExt_UseCaseAndParamT;

/**
 * @brief List of all the internal and external event IDs.
 */
typedef enum ecy_hsm_Csai_SecLog_EventId
{
    /* List of HSM sided event IDs */
    ecy_hsm_CSAI_INTERNAL_EVENT_BASE                                    =   0x00U,  /**< Base event ID for internal (HSM) events */
    ecy_hsm_CSAI_INTERNAL_EVENT_JTAG_RELEASE_SUCCESS                    =   0x00U,  /**< HSM JTAG release success (secure debug) */
    ecy_hsm_CSAI_INTERNAL_EVENT_JTAG_RELEASE_FAIL                       =   0x01U,  /**< HSM JTAG release no success (secure debug) */
    ecy_hsm_CSAI_INTERNAL_EVENT_LIFECYCLE_SWITCH_SUCCESS                =   0x02U,  /**< Lifecycle switch to different state */
    ecy_hsm_CSAI_INTERNAL_EVENT_LIFECYCLE_SWITCH_FAIL                   =   0x03U,  /**< Lifecycle switch no success */
    ecy_hsm_CSAI_INTERNAL_EVENT_MANIPULATION_FLAG                       =   0x04U,  /**< RTMD Global manipulation counter, indicates if non-authentic sw was detected */
    ecy_hsm_CSAI_INTERNAL_EVENT_MANIPULATION_COUNTER                    =   0x05U,  /**< RTMD Manipulation counter incremented for authentic->non authentic & non authentic -> authentic transitions */
    ecy_hsm_CSAI_INTERNAL_EVENT_LIFECYCLE_SWITCH_PRIVMODESERIAL_SUCCESS =   0x06U,  /**< Counter for every successful lifecycle change in privileged mode */
    ecy_hsm_CSAI_INTERNAL_EVENT_SWPART_VERIFY_FAIL                      =   0x07U,  /**< SW part verification failure */
    ecy_hsm_CSAI_INTERNAL_EVENT_SIZE,                                               /**< Number of internal events */

    /* List of HOST sided event IDs */
    ecy_hsm_CSAI_EXTERNAL_EVENT_BASE = 0x80U, /**< Base event ID for external (HOST) events */
    ecy_hsm_CSAI_EXTERNAL_EVENT_0    = 0x80U, /**< External event 0 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_1    = 0x81U, /**< External event 1 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_2    = 0x82U, /**< External event 2 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_3    = 0x83U, /**< External event 3 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_4    = 0x84U, /**< External event 4 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_5    = 0x85U, /**< External event 5 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_6    = 0x86U, /**< External event 6 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_7    = 0x87U, /**< External event 7 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_8    = 0x88U, /**< External event 8 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_9    = 0x89U, /**< External event 9 */
    ecy_hsm_CSAI_EXTERNAL_EVENT_SIZE, /**< (ecy_hsm_CSAI_EXTERNAL_EVENT_SIZE - ecy_hsm_CSAI_EXTERNAL_EVENT_BASE) gives the number of external events
                                       */

    ecy_hsm_CSAI_EVENT_INVALID = 0xFFU /**< Constant to signal an invalid event ID */
} ecy_hsm_Csai_SecLog_EventIdT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1352]
 * @brief
 * Provide access to environment data given by the Host which will be added to internal HSM Events.
 *
 * @details
 * [$Satisfies $SW_ARCH 372F9C96]
 *
 * @note
 * DFLASH data operations will always performed in background priority.
 *
 * @param[in]    hSession         Handle to the session in which the job will be placed.
 * @param[in]    priority         Requested scheduling priority for this job on the HSM.
 * @param[in]    pEnvData         Pointer to the environment data.
 * @param[in]    envDataNumBytes  Length, in bytes, of the environment data.
 * @param[out]   phJob            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session. Either finish the previous job or
 *                                                      cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note  The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle.
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session.
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogConfig(ecy_hsm_Csai_SessionHandleT hSession,
                                            ecy_hsm_Csai_JobPriorityT   priority,
                                            void*                       pEnvData,
                                            uint32                      envDataNumBytes,
                                            ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1362]
 * @brief
 * Read stored secure log entries for a specific event.
 *
 * @details
 * This interface returns all Secure Log events stored in the HSM for a given event. The returned data might be parsed to a customer specific
 * structure.
 *
 * [$Satisfies $SW_ARCH 372F9C96]
 *
 * @note
 * DFLASH data operations will always performed in background priority.
 *
 * @param[in]   hSession           Handle to the session in which the job will be placed.
 * @param[in]   priority           Requested scheduling priority for this job on the HSM.
 * @param[in]   eventId            Id of the event to be queried.
 * @param[out]  pLogEntries        Pointer to buffer to receive the secure log entries.
 * @param[in]   logEntriesNumBytes Length, in bytes, of the buffer to receive the secure log entries.
 * @param[out]  pLogEntriesCount   Pointer to buffer to receive the number of log entries.
 * @param[out]  phJob              Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session. Either finish the previous job or
 *                                                      cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle.
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session.
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             If @p pEventData is not large enough.
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               If @p eventId could not be matched to any configured event.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogRead(ecy_hsm_Csai_SessionHandleT hSession,
                                          ecy_hsm_Csai_JobPriorityT   priority,
                                          uint8                       eventId,
                                          void*                       pLogEntries,
                                          uint32                      logEntriesNumBytes,
                                          uint32*                     pLogEntriesCount,
                                          ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 1363]
 * @brief
 * Write secure log entry to the HSM secure storage, enhanced with additional environment information.
 *
 * @details
 * Finalization and result query:
 * - The caller finishes and polls for the result of the write operation using @ref ecy_hsm_Csai_PollHandle.
 *
 * [$Satisfies $SW_ARCH 372F9C96]
 *
 * @note
 * DFLASH data operations will always performed in background priority.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @param[in]   eventId             ID of the event to be logged.
 * @param[in]   pContextData        Pointer to buffer of data which shall be added to the log entry.
 * @param[in]   contextDataNumBytes Length, in bytes, of the provided data.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session. Either finish the previous job or
 *                                                      cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle.
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session.
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               If @p eventId could not be matched to any configured event.
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_FULL                  Maximum amount of stored log entries for the @p eventId is reached.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogWrite(ecy_hsm_Csai_SessionHandleT hSession,
                                           ecy_hsm_Csai_JobPriorityT   priority,
                                           uint8                       eventId,
                                           const void*                 pContextData,
                                           uint32                      contextDataNumBytes,
                                           ecy_hsm_Csai_JobHandleT*    phJob);

/**
 * [$DD 2577]
 * @brief
 * Read extended, stored secure log entries for a specific event.
 *
 * @details
 * This interface returns all Secure Log events stored in the HSM for a given event. The returned data might be parsed to a customer specific
 * structure, supporting different @p useCaseId and accordingly the equivalent data structure types will be chosen.
 *
 * [$Satisfies $SW_ARCH 0934E6EA][$Satisfies $SW_ARCH 03F30648]
 *
 * @note
 * DFLASH data operations will always performed in background priority.
 *
 * @param[in]         hSession                         Handle to the session in which the job will be placed.
 * @param[in]         priority                         Requested scheduling priority for this job on the HSM.
 * @param[in, out]    pSecLogReadExtUseCaseAndParam    Data structure that carries the output arrays of the desired event ids to be read.
 * @param[out]        phJob                            Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session. Either finish the previous job or
 *                                                      cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle.
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session.
 * - @ref ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL             If @p pEventData is not large enough.
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               If @p eventId could not be matched to any configured event.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogReadExt(ecy_hsm_Csai_SessionHandleT                           hSession,
                                             ecy_hsm_Csai_JobPriorityT                             priority,
                                             ecy_hsm_Csai_SecLogReadExt_UseCaseAndParamT*          pSecLogReadExtUseCaseAndParam,
                                             ecy_hsm_Csai_JobHandleT*                              phJob);

/**
 * [$DD 2578]
 * @brief
 * Write extended, secure log entry to the HSM secure storage, enhanced with additional environment information,
 * supporting different @p useCaseId and accordingly the equivalent data structure types will be chosen.
 *
 * @details
 * Finalization and result query:
 * - The caller finishes and polls for the result of the write operation using @ref ecy_hsm_Csai_PollHandle.
 *
 * [$Satisfies $SW_ARCH 0934E6EA][$Satisfies $SW_ARCH 03F30648]
 *
 * @note
 * DFLASH data operations will always performed in background priority.
 *
 * @param[in]        hSession                        Handle to the session in which the job will be placed.
 * @param[in]        priority                        Requested scheduling priority for this job on the HSM.
 * @param[in, out]   pSecLogWriteExtUseCaseAndParam  Data structure that carries the input arrays of the desired event ids to be logged in the logentry.
 * @param[out]       phJob                           Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session. Either finish the previous job or
 *                                                      cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle.
 *
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid.
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session.
 * - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID               If @p eventId could not be matched to any configured event.
 * - @ref ecy_hsm_CSAI_ERR_EEPROM_FULL                  Maximum amount of stored log entries for the @p eventId is reached.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecLogWriteExt(ecy_hsm_Csai_SessionHandleT                          hSession,
                                              ecy_hsm_Csai_JobPriorityT                            priority,
                                              ecy_hsm_Csai_SecLogWriteExt_UseCaseAndParamT*        pSecLogWriteExtUseCaseAndParam,
                                              ecy_hsm_Csai_JobHandleT*                             phJob);
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */

#endif /* Multiple inclusion lock  */

