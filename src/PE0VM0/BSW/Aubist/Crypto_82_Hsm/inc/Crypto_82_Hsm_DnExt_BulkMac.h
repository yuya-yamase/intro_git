/**
 * \file Crypto_82_Hsm_DnExt_BulkMac.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 * 
 * \brief Header file for implementation of Denso Bulk Mac Extension
 * \details
*/

#ifndef CRYPTO_82_HSM_EXT_DENSOBULKMAC_H
#define CRYPTO_82_HSM_EXT_DENSOBULKMAC_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Cfg.h"

#include "Csm.h"

#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"


#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

/**
 * \brief Cleans the BULK list of the specified bulk mac driver object.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 *
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_cleanBulkMacList(VAR(uint32, AUTOMATIC) objectId);


/**
 * \startuml {Crypto_82_Hsm_Ext_BulkMac_processJobAsync.png}
 * !pragma useVerticalIf on
 *   start
 *     while (Job in BULK List with isValid flag TRUE?) is (yes) 
 * floating note left
 * ====
 * As can be observed, the flow is the same 
 * for both the verification and generation driver objects, 
 * with the exception that the verification driver object
 * sets the verification pointer in case of success.
 * ====
 * end note    
 *         #palegreen: Set JobState idle;
 *         #palegreen: Set isValid flag to false;
 *         if (Job finished successfully?) then (yes)
 *             if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) then (yes)
 *             #palegreen: Set output verify ptr to returned value;
 *             else (no)
 *             endif
 *             #palegreen: Call CryIfCallbackNotification with E_OK;
 *         else (no)
 *             #pink: Call CryIfCallbackNotification with E_NOT_OK;
 *             #pink: Call Crypto_82_Hsm_Error_CallBack with job error code;
 *         endif
 *     endwhile
 *     if (BULK Job polling result CRYPTO_E_BUSY?) then (yes)
 *     else (no)
 *         #palegreen: Remove finished jobs from Queue;
 *         #palegreen: Clean BULK List;
 *         #palegreen: Set bulkJobState to inactive;
 *         if (Driver object queue is empty?) then (yes)
 *         #palegreen: Set driver object state to not busy;
 *         else (no)
 *         endif
 *     endif
 * stop
 * \enduml
 */
/**
 * \brief Processes the bulk mac operation as it is being polled.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 *
 */
FUNC(void, CRYPTO_82_HSM_CODE)Crypto_82_Hsm_Ext_BulkMac_processJobAsync(VAR(uint32, AUTOMATIC) objectId);

/**
 * \startuml {Crypto_82_Hsm_Ext_BulkMac_ProcessJob.png}
 * !pragma useVerticalIf on
 *   start
 *     if (ProcessingType is SYNC?) then (yes)
 *         #pink: Return E_NOT_OK;
 *         stop
 *     (no) elseif (Key state is invalid?) then (yes)
 *         #pink: Return E_NOT_OK;
 *         stop
 *     (no) elseif (Job state is active?) then (yes)
 *         #pink: Return CRYPTO_E_BUSY;
 *         stop
 *     (no) elseif (Operation mode is not SINGLECALL?) then (yes)
 *         #pink: Return E_NOT_OK;
 *         stop
 *     (no) elseif (Service is not MACGENERATE or MACVERIFY or wrong object id?) then (yes)
 *         #pink: Return E_NOT_OK;
 *         stop
 *     else
 *     partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is STD_ON" {
 *     if (AR Det Errors occured?) then (yes)
 *     #pink:Return E_NOT_OK;
 *     stop
 *     else(no)
 *     endif
 *     }      
 *     if (Job in queue?) then (yes)
 *     #palegreen: Replace job in queue;
 *     (no) elseif (Is queue full?) then (no)
 *     #palegreen: Add job to queue;
 *     else(yes)
 *     #pink: Return CRYPTO_E_BUSY;
 *     endif
 *     endif
 * stop
 * \enduml
 */
/**
 * \brief Processes the bulk mac operation as it is being polled.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 * \param [in] job             Pointer to a Crypto_JobType variable.
 * \param [in] processingType  Processing type (SYNC/ASYNC).
 * \param [in] detErr          Pointer to a uint8 variable which stores DET error.
 *
 *  \retval CRYPTO_E_BUSY      The function is unable to queue the job.
 *  \retval E_NOT_OK           The job configuration does not correspond.
 *  \retval E_OK               Job successfully queued.
 */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_BulkMac_ProcessJob(
                                                VAR(uint32, AUTOMATIC) objectId, 
                                                P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                                CONST(Crypto_ProcessingType, AUTOMATIC) processingType,
                                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) detErr); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \startuml {Crypto_82_Hsm_Ext_BulkMac_Main.png}
 * !pragma useVerticalIf on
 *   start
 *     if (Jobs exist in BULK MAC Ver queue?) then (yes)
 *         if (Bulk job in progress?) then (no)
 *             #palegreen: Fill BULK List with data;
 *             #palegreen: Dispatch Bulk Job;
 *             if (Dispatch successful?) then (yes)
 *             #palegreen: Set Bulk Job state to active;
 *             #palegreen: Set Crypto Driver Object state to busy;
 *             #palegreen: Set Job states to active;
 *             else (no)
 *             #pink: Call Crypto_82_Hsm_Error_CallBack;
 *             #pink: Set jobstates to idle for failed jobs;
 *             #pink: Call CryIfCallback for failed jobs;
 *             #pink: Remove failed jobs from queue;
 *             if (Queue is empty?) then (yes)
 *             #pink: Set Crypto Driver Object state to not busy;
 *             else (no)
 *             endif            
 *             #pink: Clean bulklist;
 *             endif
 *         else (yes)
 *         endif
 *     else(no)
 *     #palegreen: Set Crypto Driver Object state to not busy;
 *     endif
 *     if (Jobs exist in BULK MAC Gen queue?) then (yes)
 *         if (Bulk job in progress?) then (no)
 *         #palegreen: Fill BULK List with data;
 *         #palegreen: Dispatch Bulk Job;
 *             if (Dispatch successful?) then (yes)
 *             #palegreen: Set Bulk Job state to active;
 *             #palegreen: Set Crypto Driver Object state to busy;
 *             #palegreen: Set Job states to active;
 *             else (no)   
 *             #pink: Call Crypto_82_Hsm_Error_CallBack;
 *             #pink: Set jobstates to idle for failed jobs;            
 *             #pink: Call CryIfCallback for failed jobs;
 *             #pink: Remove failed jobs from queue;
 *             if (Queue is empty?) then (yes)
 *             #pink: Set Crypto Driver Object state to not busy;
 *             else (no)
 *             endif                     
 *             #pink: Clean bulklist;
 *             endif
 *         else (yes)
 *         endif
 *     else (no)
 *     #palegreen: Set Crypto Driver Object state to not busy;
 *     endif    
 * stop
 * \enduml
 */
/**
 * \brief Cyclical function which triggers bulk mac operations using jobs in the bulk mac crypto driver objects queues.
 *
 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_BulkMac_Main(void);

#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif
