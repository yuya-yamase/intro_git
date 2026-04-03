/**
 * \file Crypto_82_Hsm.h
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Header file for main implementation of the Crypto Driver functionality
 * \details
*/

#ifndef CRYPTO_82_HSM_H
#define CRYPTO_82_HSM_H

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Csm.h"

#if ( (CSM_AR_RELEASE_MAJOR_VERSION == 4u) && (CSM_AR_RELEASE_MINOR_VERSION >= 5u) )
#include "Crypto_GeneralTypes.h"
#else
#include "Csm_Types.h"
#endif

#include "CryIf.h"
#include "Crypto_82_Hsm_Cfg.h"
#include "Crypto_82_Hsm_KeyManagement.h"

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC MACROS
\**********************************************************************************************************************/

/**
 * \def CRYPTO_82_HSM_VENDOR_ID
 * \brief Crypto Driver Vendor ID.
 */
#define CRYPTO_82_HSM_VENDOR_ID                                 (82u)

/**
 * \def CRYPTO_82_HSM_MODULE_ID
 * \brief Crypto Driver Module ID.
 */
#define CRYPTO_82_HSM_MODULE_ID                                 (0x72u)

/**
 * \def CRYPTO_DET_NO_ERROR
 * \brief Macro used to initialize DET error to no error.
 */
#define CRYPTO_DET_NO_ERROR                                     (0xFFu)

/**
 * \def CRYPTO_SERVICE_ID_INIT
 * \brief Init service ID.
 */
#define CRYPTO_SERVICE_ID_INIT                                  (0x00u)

/**
 * \def CRYPTO_SERVICE_ID_GET_VERSION_INFO
 * \brief Get Version service ID.
 */
#define CRYPTO_SERVICE_ID_GET_VERSION_INFO                      (0x01u)

/* TODO: Initial version TBD */
/**
 * \def CRYPTO_82_HSM_SW_MAJOR_VERSION
 * \brief Crypto Driver software major version.
 */
#define CRYPTO_82_HSM_SW_MAJOR_VERSION                          (1u)

/**
 * \def CRYPTO_82_HSM_SW_MINOR_VERSION
 * \brief Crypto Driver software minor version.
 */
#define CRYPTO_82_HSM_SW_MINOR_VERSION                          (10u)

/**
 * \def CRYPTO_82_HSM_SW_PATCH_VERSION
 * \brief Crypto Driver software patch version.
 */
#define CRYPTO_82_HSM_SW_PATCH_VERSION                          (0u)


#ifndef CRYPTO_E_BUSY
/**
 * \def CRYPTO_E_BUSY
 * \brief The service request failed because the service is still busy.
*/
#define CRYPTO_E_BUSY                                           ((Std_ReturnType)0x02u)
#endif

#ifndef CRYPTO_E_ENTROPY_EXHAUSTED
/**
 * \def CRYPTO_E_ENTROPY_EXHAUSTED
 * \brief The service request failed because the entropy of the random number generator is exhausted.
*/
#define CRYPTO_E_ENTROPY_EXHAUSTED                              ((Std_ReturnType)0x04u)
#endif

/* Deviation from SWS_Csm_91043 */
#ifndef CRYPTO_E_QUEUE_FULL
/**
 * \def CRYPTO_E_QUEUE_FULL
 * \brief The service request failed because the queue is full.
*/
#define CRYPTO_E_QUEUE_FULL                                     ((Std_ReturnType)0x05u)
#endif

#ifndef CRYPTO_E_KEY_READ_FAIL
/**
 * \def CRYPTO_E_KEY_READ_FAIL
 * \brief The service request failed because read access was denied.
*/
#define CRYPTO_E_KEY_READ_FAIL                                  ((Std_ReturnType)0x06u)
#endif

#ifndef CRYPTO_E_KEY_WRITE_FAIL
/**
 * \def CRYPTO_E_KEY_WRITE_FAIL
 * \brief The service request failed because the writing access failed.
*/
#define CRYPTO_E_KEY_WRITE_FAIL                                 ((Std_ReturnType)0x07u)
#endif

#ifndef CRYPTO_E_KEY_NOT_AVAILABLE
/**
 * \def CRYPTO_E_KEY_NOT_AVAILABLE
 * \brief The service request failed because the key is not available.
*/
#define CRYPTO_E_KEY_NOT_AVAILABLE                              ((Std_ReturnType)0x08u)
#endif

#ifndef CRYPTO_E_KEY_NOT_VALID
/**
 * \def CRYPTO_E_KEY_NOT_VALID
 * \brief The service request failed because the key is invalid.
*/
#define CRYPTO_E_KEY_NOT_VALID                                  ((Std_ReturnType)0x09u)
#endif

#ifndef CRYPTO_E_KEY_SIZE_MISMATCH
/**
 * \def CRYPTO_E_KEY_SIZE_MISMATCH
 * \brief The service request failed because the key size does not match.
*/
#define CRYPTO_E_KEY_SIZE_MISMATCH                              ((Std_ReturnType)0x0Au)
#endif

#ifndef CRYPTO_E_JOB_CANCELED
/**
 * \def CRYPTO_E_JOB_CANCELED
 * \brief The service request failed because the Job has been canceled.
*/
#define CRYPTO_E_JOB_CANCELED                                   ((Std_ReturnType)0x0Cu)
#endif

#ifndef CRYPTO_E_KEY_EMPTY
/**
 * \def CRYPTO_E_KEY_EMPTY
 * \brief The service request failed because of uninitialized source key element.
*/
#define CRYPTO_E_KEY_EMPTY                                      ((Std_ReturnType)0x0Du)
#endif


/* Crypto DET error ID macros */
/* Satisfies SWS_Crypto_00040 */

#ifndef CRYPTO_E_UNINIT
/**
 * \def CRYPTO_E_UNINIT
 * \brief API request called before initialization of Crypto Driver.
*/
#define CRYPTO_E_UNINIT                                         (0x00u)
#endif

#ifndef CRYPTO_E_INIT_FAILED
/**
 * \def CRYPTO_E_INIT_FAILED
 * \brief Initialization of Crypto Driver failed.
*/
#define CRYPTO_E_INIT_FAILED                                    (0x01u)
#endif

#ifndef CRYPTO_E_PARAM_POINTER
/**
 * \def CRYPTO_E_PARAM_POINTER
 * \brief API request called with invalid parameter (Nullpointer without redirection).
*/
#define CRYPTO_E_PARAM_POINTER                                  (0x02u)
#endif

#ifndef CRYPTO_E_PARAM_HANDLE
/**
 * \def CRYPTO_E_PARAM_HANDLE
 * \brief API request called with invalid parameter (out of range).
*/
#define CRYPTO_E_PARAM_HANDLE                                   (0x04u)
#endif

#ifndef CRYPTO_E_PARAM_VALUE
/**
 * \def CRYPTO_E_PARAM_VALUE
 * \brief API request called with invalid parameter (invalid value).
*/
#define CRYPTO_E_PARAM_VALUE                                    (0x05u)
#endif

#ifndef CRYPTO_E_SMALL_BUFFER
/**
 * \def CRYPTO_E_SMALL_BUFFER
 * \brief API request called with buffer too small.
*/
#define CRYPTO_E_SMALL_BUFFER                                    (0x06u)
#endif

/* Runtime errors ID macros */
/* Satisfies SWS_Crypto_00194 */
#ifndef CRYPTO_E_RE_KEY_NOT_AVAILABLE
/**
 * \def CRYPTO_E_RE_KEY_NOT_AVAILABLE
 * \brief Requested key is not available.
*/
#define CRYPTO_E_RE_KEY_NOT_AVAILABLE                           (0x01u)
#endif

#ifndef CRYPTO_E_RE_KEY_READ_FAIL
/**
 * \def CRYPTO_E_RE_KEY_READ_FAIL
 * \brief Key cannot be read.
*/
#define CRYPTO_E_RE_KEY_READ_FAIL                               (0x02u)
#endif

#ifndef CRYPTO_E_RE_ENTROPY_EXHAUSTED
/**
 * \def CRYPTO_E_RE_ENTROPY_EXHAUSTED
 * \brief Entropy is too low.
*/
#define CRYPTO_E_RE_ENTROPY_EXHAUSTED                           (0x03u)
#endif

/* Service ID macros */
#define CRYPTO_82_HSM_SERVICE_ID_INIT                           (0x00u)
#define CRYPTO_82_HSM_SERVICE_ID_GET_VERSION_INFO               (0x01u)
#define CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB                    (0x03u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_SET                (0x04u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_SET_VALID                  (0x05u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_ELEMENT_GET                (0x06u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_GENERATE                   (0x07u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_DERIVE                     (0x08u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_PUB_VAL      (0x09u)
#define CRYPTO_82_HSM_SERVICE_ID_KEY_EXCHANGE_CALC_SECRET       (0x0Au)
#define CRYPTO_82_HSM_SERVICE_ID_MAIN_FUNCTION                  (0x0Cu)
#define CRYPTO_82_HSM_SERVICE_ID_RANDOM_SEED                    (0x0Du)
#define CRYPTO_82_HSM_SERVICE_ID_CANCEL_JOB                     (0x0Eu)

#define CRYPTO_82_HSM_KEY_VALIDITY_EXCEPTION_SERVICES           ((1uL << CRYPTO_KEYSETVALID) | \
                                                                 (1uL << CRYPTO_KEYEXCHANGECALCPUBVAL) | \
                                                                 (1uL << CRYPTO_KEYEXCHANGECALCSECRET) | \
                                                                 (1uL << CRYPTO_KEYGENERATE) | \
                                                                 (1uL << CRYPTO_KEYDERIVE) | \
                                                                 (1uL << CRYPTO_RANDOMSEED))

/**********************************************************************************************************************\
 * PUBLIC TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * [SWS_Crypto_91016] - The content of the configuration data structure is implementation specific
 * Currently, the existence of this datatype is not necessary.
*/
typedef struct sCrypto_ConfigType Crypto_ConfigType;

/**********************************************************************************************************************\
 * EXTERN PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTION DECLARATIONS
\**********************************************************************************************************************/

/**
 * \startuml {Crypto_82_Hsm_Init.png}
 * start
 *  :Initialize the Crypto Driver's:
 *   - State and information
 *   - Queue list
 *   - Objects;
 * 
 *   :Initialize each Crypto Driver object's:
 *    - Queue types
 *    - Cancel job related items
 *    - Job lock;
 * 
 *  fork
 *   partition "CRYPTO_82_HSM_USER_DEF_INIT is **STD_OFF**" {
 *    :ecy_HSM_ConfigureCallouts() >
 * 
 *   if (callouts has errors?) then (yes)
 *    partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is **STD_ON**" {
 *     #pink:Report Error to DET >
 *    }
 *    #pink:set Driver State 
 *    to CRYPTO_STATE_ERROR;
 *   else (no)
 *    : SHE_Init() >
 * 
 *    if (No errors during SHE init?) then (yes)
 *     #palegreen:set Driver State 
 *     to CRYPTO_STATE_INIT;
 *    else (no)
 *    endif
 *   endif
 *   }
 *  fork again
 *   partition "CRYPTO_82_HSM_USER_DEF_INIT is **STD_ON**" {
 *    #palegreen:set Driver State 
 *    to CRYPTO_STATE_INIT;
 *   }
 *  end fork
 * 
 * stop
 * \enduml
 */
/**
 *
 * \brief Initializes the Crypto Driver.
 *
 * \id 0x00
 * \sync Synchronous
 * \reentrant Non Reentrant
 *
 * \param [in] configPtr Pointer to a selected configuration structure.
 *
 * \note [SWS_Crypto_00215] The Configuration pointer configPtr shall always have a null pointer value.
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Init(P2CONST(Crypto_ConfigType, AUTOMATIC, CRYPTO_82_HSM_CONST) configPtr);

#if (CRYPTO_82_HSM_VERSION_INFO_API == STD_ON)
/**
 *
 * \brief Returns the version information of the Crypto Driver.
 *
 * \id 0x01
 * \sync Synchronous
 * \reentrant Reentrant
 *
 * \param [out] versioninfo Pointer to where to store the version information of this module.
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_GetVersionInfo(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_82_HSM_VAR) versioninfo /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);
#endif

/**
 * \startuml {Crypto_82_Hsm_ProcessJob.png}
 * !pragma useVerticalIf on
 *   start
 *     
 *  partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is STD_ON" {
 *  if (Errors occured?) then (yes)
 *     #pink:Return E_NOT_OK;
 *     stop
 *  else(no)
 *  endif
 * }
 * if (ObjectId is for a BULKMAC driver object?) then (yes)
 * partition "CRYPTO_82_HSM_DENSO_BULKMAC is STD_ON" {
 * #palegreen: Call Crypto_82_Hsm_Ext_BulkMac_ProcessJob;
 * }
 * else (no)
 * if (If job state compatible with operation mode?) then (yes)
 *   #palegreen:Continue;
 *   floating note left
 *   Job state compatible means that either:
 *   ====
 *   * Operation mode is start/singlecall
 *     (job state irrelevant in this case)
 *   * Job state is idle 
 *     (Operation mode <b>must</b> be start)
 *   * Job state is active but not actively processed
 *     (Operation mode is update/finish)
 *   ====
 *   end note
 * 
 * if (Key state is compatible with job service?) then (yes)
 *   if (If operation mode start?) then (yes)
 *   :Remove job from queue if it exists;
 *   else(no)
 *   endif
 *    #palegreen:Continue;
 *   floating note left
 *   Key state is compatible means that either:
 *   ====
 *   * Key state is valid.
 *   * Service does not require key.
 *   * Service is JobKeySetValid, JobKeyGenerate, 
 *   JobKeyExchangeCalcPubVal or JobKeyExchangeCalcPubSecret.
 *     (these services allow the key to be invalid).
 *   ====
 *   end note
 *    if (Processing mode Sync?) then (yes)
 *   
 *        if (Driver Object Busy?) then (yes)
 * 
 *           if (Job prio higher than any queued job?) then (yes)
 * 
 *               #palegreen: Skip queue dispatching next MainFunction Call;
 * 
 *           else(no)
 * 
 *           endif
 *   
 *            #pink: Return CRYPTO_E_BUSY;
 *   
 *        (no) elseif (Cancel Requested?) then (yes)
 *   
 *            #palegreen: Return CRYPTO_E_JOB_CANCELLED;
 *   
 *        (no) elseif (Queue Full AND Queue Size !=0 ?) then (yes)
 *   
 *            #pink: Return CRYPTO_E_BUSY;
 *   
 *        else(no)
 *   
 *           #palegreen:Process Job Synchronously;
 *   
 *           if (Successful Processing?) then (yes)
 *   
 *              #palegreen: Return E_OK;
 *   
 *           else(no)
 * 
 *             if (RNG Entropy Exhausted?) then (yes)
 * 
 *             #pink: Return CRYPTO_E_ENTROPY_EXHAUSTED;
 *             else (no)
 *             #pink: Return E_NOT_OK;
 *             endif
 * 
 *           endif
 *   
 *        endif
 *   
 *    else(no)
 *   
 *             if (Driver Object Busy?) then (yes)
 *   
 *                 if (Operation Mode Start?) then (yes)
 * 
 *                   if (Job State Active?) then (yes)
 * 
 *                   #pink: Return E_NOT_OK;
 * 
 *                   else(no)
 *   
 *                     if (Queue is Full?) then (yes)
 * 
 *                       #pink: Return CRYPTO_E_BUSY;
 * 
 *                     else(no)
 * 
 *                     #palegreen: Add to Queue;
 *                       
 *                     #palegreen: Return E_OK;
 * 
 *                     endif       
 * 
 *                   endif
 *   
 *                 else(no)
 *   
 *                   #pink: Return E_NOT_OK;
 *   
 *                 endif
 *   
 *             (no) elseif (Job Locked Successfully?) then (yes)
 *   
 *                 #palegreen: Dispatch Job;
 *   
 *                 if (Dispatch Successful?) then (yes)
 *   
 *                   #palegreen: Return E_OK;
 *   
 *                 else(no)
 *   
 *                   #pink: Return E_NOT_OK;
 *   
 *                 endif
 *   
 *             else(no)
 * 
 *               if (Queue is Full?) then (yes)
 * 
 *                 #pink: Return CRYPTO_E_BUSY;
 * 
 *               else(no)
 * 
 *               #palegreen: Add to Queue;
 *                 
 *               #palegreen: Return E_OK;
 * 
 *               endif                
 *   
 *   
 *             endif
 *   
 *      endif
 * 
 * else (no)
 * 
 *    #pink: Return CRYPTO_E_KEY_NOT_VALID;
 * 
 * endif
 * 
 * else (no)
 * 
 *    #pink: Return E_NOT_OK;
 * 
 * endif
 * endif
 * stop
 * \enduml
 */
 /**
 * \brief Job Processing Interface
 *
 * Performs the crypto primitive, that is configured in the job parameter.
 *
 * \id 0x03
 * \sync Asynchronous or Synchronous, depends on the job configuration
 * \reentrant Reentrant
 *
 * \param [in]      objectId Holds the identifier of the Crypto Driver Object
 * \param [in, out] job      Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                           information but also pointer to result buffers.
 *
 * \retval E_OK                          Request successful
 * \retval E_NOT_OK                      Request failed
 * \retval CRYPTO_E_BUSY                 Request failed, Crypro Driver Object is busy
 * \retval CRYPTO_E_KEY_NOT_VALID        Request failed, the key is not valid
 * \retval CRYPTO_E_KEY_SIZE_MISMATCH    Request failed, a key element has the wrong size
 * \retval CRYPTO_E_QUEUE_FULL           Request failed, the queue is full
 * \retval CRYPTO_E_KEY_READ_FAIL        The service request failed, because key element extraction is not allowed
 * \retval CRYPTO_E_KEY_WRITE_FAIL       The service request failed because the writing access failed
 * \retval CRYPTO_E_KEY_NOT_AVAILABLE    The service request failed because the key is not available
 * \retval CRYPTO_E_ENTROPY_EXHAUSTED    Request failed, the entropy is exhausted
 * \retval CRYPTO_E_JOB_CANCELED         The service request failed because the synchronous Job has been canceled
 * \retval CRYPTO_E_KEY_EMPTY            Request failed because of uninitialized source key element
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_ProcessJob(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);


/**
 * \startuml {Crypto_82_Hsm_CancelJob.png}
 * !pragma useVerticalIf on
 * start
 * 
 * partition "CRYPTO_82_HSM_DEV_ERROR_REPORT is STD_ON" {
 *  if (Errors occured?) then (yes)
 *     #pink:Return E_NOT_OK;
 *     stop
 *  else(no)
 *  endif
 * }
 * 
 *  if (Is there any job that is currently in progress?) then (yes)
 * 
 *      if (Is the job that is currently in progress the job that needs to be cancelled?) then (yes)
 * 
 *          #palegreen: Cancel Job;
 * 
 *      if(Cancel operation successful?) then (yes)
 * 
 *          #palegreen:Return E_OK;
 * 
 *      else(no)
 * 
 *          #palegreen:Return CRYPTO_E_JOB_CANCELLED;
 * 
 *      endif
 * 
 *      else(no)
 * 
 *      if(Job that needs to be cancelled is found in queue?) then (yes)
 *          #palegreen:Pop job from queue;
 *      else(no)
 *      endif
 *      #palegreen:Return E_OK;
 * 
 *      endif
 * 
 *  else(no)
 * 
 *      #palegreen:Return E_OK;
 * 
 *  endif
 * 
 * 
 * stop
 * \enduml
 */
/**
 * \brief Crypto Driver Job Cancellation Interface
 *
 * This interface removes the provided job from the queue and cancels the
 * processing of the job if possible.
 *
 * \id 0x0E
 * \sync Synchronous
 * \reentrant Reentrant but not for same Crypto Driver Object
 *
 * \param [in]       objectId   Holds the identifier of the Crypto Driver Object.
 * \param [in, out]  job        Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                              information.
 *
 * \note
 * Configuraton parameter "CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE" can be set to true to support AUTOSAR release 4.4.0 or older releases. \n
 * Second parameter will be of a type Crypto_JobInfoType instead of Crypto_JobType.
 *
 * \retval E_OK                   Request successful, job has been removed.
 * \retval E_NOT_OK               Request Failed, job couldn't be removed.
 * \retval CRYPTO_E_JOB_CANCELED  The job has been cancelled but is still processed. No results will be returned to the application
*/
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CancelJob(
    VAR(uint32, AUTOMATIC) objectId,
#if ( CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_ON )
    CONSTP2CONST(Crypto_JobInfoType, AUTOMATIC, CRYPTO_82_HSM_CONST) jobInfo);
#else
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#endif /* CRYPTO_82_HSM_H */
