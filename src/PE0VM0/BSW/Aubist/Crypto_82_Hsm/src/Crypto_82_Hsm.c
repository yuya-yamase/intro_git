/**
 * \file Crypto_82_Hsm.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 *
 * \brief Main implementation of the Crypto Driver functionality
 *
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Csm.h"

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm.h"
#include "Crypto_82_Hsm_Services.h"
#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_DensoExtensions.h"
#include "Crypto_82_Hsm_Porting.h"
#include "Crypto_82_Hsm_DnExt_BulkMac.h"
#include "Crypto_82_Hsm_Mem.h"
#include "Crypto_82_Hsm_UserCallout.h"

#include "SchM_Crypto_82_Hsm.h"

#include "ecy_hsm_csai_keys.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_key_exchange.h"

#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"

#if ( CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF )
#include "Os.h"
#endif

#if ( CRYPTO_82_HSM_CALLBACK_NOTIF_AUTOSAR_VERSION_SELECT == STD_ON )
#include "CryIf_Cbk.h"
#else
#include "CryIf.h"
#endif /* ( CRYPTO_82_HSM_CALLBACK_NOTIF_AUTOSAR_VERSION_SELECT == STD_ON ) */

#if ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON )
    #include "Det.h"
#endif

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**
 * \def JOB_LOCK_FREE
 * \brief Value used when the Crypto Driver Object job lock is free.
 */
#define JOB_LOCK_FREE                   (0xFFFFFFFFu)

/**
 * \def isLockFree(objectId)
 * \brief Returns whether the Crypto Driver Object job lock is free.
 */
#define isLockFree(objectId)            ((jobLock[(objectId)]) == JOB_LOCK_FREE)

/**
 * \def isJobInLock(objectId, jobId)
 * \brief Returns whether the Crypto Driver Object job lock is occupied by a certain job.
 */
#define isJobInLock(objectId, jobId)    ((jobLock[(objectId)]) == (jobId))

/**
 * \def setLock(objectId, jobId)
 * \brief Sets the Crypto Driver Object job lock.
 */
#define setLock(objectId, jobId)        ((jobLock[(objectId)]) = (jobId))

/* TODO: Move the macros for the Crypto Driver Objects and Queue sizes to the Crypto_82_Hsm_Cfg.h */
/**
 * \def isJobMode(job, opMode)
 * \brief Returns whether the job operating mode is a certain mode.
 */
#define isJobMode(job, opMode)          ((((job)->jobPrimitiveInputOutput.mode) & (opMode)) == (opMode))

/**
 * \def isBulkMacDriverObject(objectId)
 * \brief Returns whether driver object is CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN or CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER.
 */
#define isBulkMacDriverObject(objectId)          ( ( (objectId) == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) || ( (objectId) == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) )

/**
 * \def getJobPriority(job)
 * \brief Returns the job priority.
 */
#define getJobPriority(job)             ((job)->jobInfo->jobPriority)

/**
 * \def getJobId(job)
 * \brief Returns the job id.
 */
#define getJobId(job)                   ((job)->jobInfo->jobId)

/**
 * \def getJobAtTopOfQueue(objectId)
 * \brief Returns the job at the top of the Crypto Driver Object queue.
 */
#define getJobAtTopOfQueue(objectId)    (*(getQueue((objectId))))

/**
 * \def getCurrentJob(objectId)
 * \brief Returns the job that is currently being processed in the Crypto Driver Object.
 */
#define getCurrentJob(objectId)         (Crypto_82_Hsm_driverObjects[(objectId)].job)

/**
 * \def setCurrentJob(objectId, jobPtr)
 * \brief Sets the job that is currently being processed in the Crypto Driver Object.
 */
#define setCurrentJob(objectId, jobPtr) (Crypto_82_Hsm_driverObjects[(objectId)].job = (jobPtr))

/**
 * \def setJobState(job, state)
 * \brief Sets the state of a job.
 */
#define setJobState(job, state)         ((job)->jobState = (state))

/**
 * \def getServiceFromJob(job)
 * \brief Returns the service type of a job (eg. hash, MAC generate, encrypt).
 */
#define getServiceFromJob(job)          ((job)->jobPrimitiveInfo->primitiveInfo->service)


/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**
 * \brief The possible Crypto Driver states.
 */
typedef enum eCrypto_StateType
{
    CRYPTO_STATE_INIT,                      /** Crypto Driver is being initialized                                   */
    CRYPTO_STATE_INIT_KEYS,                 /** Crypto Driver is being initialized, keys are being processed         */
    CRYPTO_STATE_INIT_POLLING_PENDING,      /** Crypto Driver is being initialized, a polling operation is required  */
    CRYPTO_STATE_IDLE,                      /** Crypto Driver is idle, all jobs are in idle state                    */
    CRYPTO_STATE_ACTIVE,                    /** Crypto Driver is active, at least one job is in active state         */
    CRYPTO_STATE_ERROR,                     /** Crypto Driver is in error state                                      */
    CRYPTO_STATE_UNDEFINED,
} Crypto_StateType;

/**
 * \brief The possible HSM initialization states.
 */
typedef enum eHsm_InitStateType
{
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
    HSM_INIT_STATE_WAIT_FOR_BOOTED,    /** HSM is not running in bootloader mode or core application mode          */
    HSM_INIT_STATE_BOOTLOADER,
#endif
    HSM_INIT_STATE_RELEASED,           /** HSM is running in bootloader mode                                        */
    HSM_INIT_STATE_INITIALIZED,        /** HSM is running in core application mode                                  */
} Hsm_InitStateType;

/**
 * \brief Stores information about the Crypto Driver.
 */
typedef struct sCryptoDrvContext
{
    Hsm_InitStateType       hsmInitState;           /** HSM initialization state                                                          */
    Crypto_StateType        driverState;            /** Crypto Driver state                                                               */
    HSM_ModeT               hsmMode;                /** HSM operational mode                                                              */
    uint32                  initTimeout;            /** Crypto Driver initialization timeout value                                        */
    uint32                  currentKeyIndex;        /** Crypto Driver current processed key in initialization                             */
    uint32                  currentKeyElementIndex;  /** Crypto Driver current processed key element in initialization                     */
    boolean                 isInitialized;          /** Crypto Driver initialization state; TRUE means Crypto Driver is fully initialized */
} Crypto_ContextType;

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief Stores information about the Crypto Driver.
 */
static VAR(Crypto_ContextType, CRYPTO_82_HSM_VAR) cryptoDrvContext;

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/**
 * \brief An array for each crypto driver object to track if associated data has been recived for AEAD Encrypt
 */
VAR(uint8, CRYPTO_82_HSM_VAR)Crypto_82_Hsm_AEAD_Encrypt_ADD_received[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

/**
 * \brief An array for each crypto driver object to track if associated data has been recived for AEAD Decrypt
 */
VAR(uint8, CRYPTO_82_HSM_VAR)Crypto_82_Hsm_AEAD_Decrypt_ADD_received[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_8BIT
#include "Crypto_82_Hsm_MemMap.h"

#define CRYPTO_82_HSM_START_SEC_VAR_NOINIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"
/**
 * \brief Stores the job currently locking a driver object. A job lock is set for as long as the job is active.
 */
static VAR(uint32, CRYPTO_82_HSM_VAR) jobLock[CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS];

#define CRYPTO_82_HSM_STOP_SEC_VAR_NOINIT_32BIT
#include "Crypto_82_Hsm_MemMap.h"


/**********************************************************************************************************************\
 * PRIVATE FUNCTION DECLARATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"


#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
/**
 * \brief Locks the OS resource that is dedicated to the HSM Proxy.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) calloutAcquireResource(void);

/**
 * \brief Releases the OS resource that is dedicated to the HSM Proxy.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) calloutReleaseResource(void);

/**
 * \brief Gets the current tick value of the CRYPTO_82_HSM_OS_COUNTER counter. 
 *
 * \param [out]  counterValue Pointer to the buffer where the current tick value is stored.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) calloutGetCounterValue(P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) counterValue); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Gets the number of ticks between the current tick value of the CRYPTO_82_HSM_OS_COUNTER counter and a previously read tick value.
 *
 * \param [in]   value         Previously read tick value.
 * \param [out]  pElapsedValue Number of ticks between current tick value and previously read tick value.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) calloutGetElapsedValue(
    VAR(uint32, AUTOMATIC) value,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) pElapsedValue /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);
#endif /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */

/**
 * \brief Removes a job from the queue.
 *
 * \param [in] job             Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                             information.
 * \param [in] objectId        Crypto Driver Object Id.
 *
 * \retval E_NOT_OK            Job could not be removed from the queue because it was not found in the queue.
 * \retval E_OK                Job was removed from the queue.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) removeJobFromQueue(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
);


/**
 * \brief Sets the Crypto Driver state.
 *
 * \param [in]   state         Value to set the Crypto Driver state to.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) setDriverState(VAR(Crypto_StateType, AUTOMATIC) state);

/**
 * \brief Sets the Crypto Driver state during initialization.
 *
 * \param [in]   state         Value to set the Crypto Driver state to.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) setDriverStateInit(VAR(Crypto_StateType, AUTOMATIC) state);

/**
 * \brief Sets the HSM initialization state.
 *
 * \param [in]   initState      Value to set the HSM initialization state to.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) setHsmInitState(VAR(Hsm_InitStateType, AUTOMATIC) initState);

/**
 * \brief Switches between HSM initialization states in order to call the appropriate initialization function. 
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateMachine(void);

/**
 * \brief Function used during key initalization phase to inject key elements which contain initalContentPtr 
 */
static FUNC(void, CRYPTO_82_HSM_CODE) injectInitalContentPtr(uint32 keyElementIndex);

/**
 * \brief Function used during key initalization phase to poll and process polling result of loading keys from nvm 
 */
static FUNC(void, CRYPTO_82_HSM_CODE) initLoadFromNvmPolling(void);

#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
/**
 * \brief Switches the HSM initialization status if the HSM is running in bootloader mode or core application mode.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateWaitForBooted(void);
#endif

/**
 * \brief Switches the HSM initialization status if the HSM is running in core application mode.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateReleased(void);

/**
 * \brief Initializes Crypto Driver objects.
 *
 * The HSM is initialized, therefore the Crypto Driver can proceed: HSM sessions are openend for each driver object. 
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateInitialized(void);

/**
 * \brief Finishes Crypto Driver initialization.
 *
 * The HSM and Crypto Driver objects have been initialized, therefore the Crypto Driver initialization can be finished: 
 * Key validity statuses are updated and persistent key element handles are saved to the runtime keys. 
 * After this, the Crypto Driver is fully initialized and the state transitions to IDLE.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateKeys(void);

/**
 * \brief Cancels the active job of a Crypto Driver Object.
 *
 * \param [in]   objectId             Crypto Driver Object Id.
 * 
 * \retval E_OK                   Request successful, job has been removed.
 * \retval CRYPTO_E_JOB_CANCELED  The job has been cancelled but is still processed. No results will be returned to the application
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) cancelJobLocal(VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Synchronous Job Processing Interface.
 *
 * This interface directly processes a configured job. This job will be processed in blocking mode.
 *
 * \param [in]  objectId The identifier of the current driver object.
 * \param [in]  job      Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                       information.
 *
 * \retval E_OK          Job has been processed successfully and results are now available in data buffer.
 * \retval E_NOT_OK      Job has not been sucesssfully processed.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) processJobSync(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Asynchronous Job Processing Interface.
 *
 * This interface processes an asynchronous job by either polling the job or dispatching the job. This interface is
 * intended to be called only from \ref Crypto_82_Hsm_MainFunction.
 *
 * \param [in] objectId         The identifier of the current driver object.
 * \param [in] job              Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                              information.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processJobAsync(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Postprocessing for Asynchronous KeySetValid Job.
 *
 * This function performs the postprocessing of KeySetValid asynchronous job
 *
 * \param [in] objectId         The identifier of the current driver object.
 * \param [in] job              Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                              information.
 * \param [in] ret              Final result of processJobAsync
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processJobAsync_KeySetValid(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    Std_ReturnType* ret
);

/**
 * \brief Adds a new job to the queue.
 *
 * \param [in] job             Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                             information.
 * \param [in] objectId        Crypto Driver Object Id.
 *
 * \retval E_NOT_OK            Job could not be added to the queue because of the operation mode.
 * \retval CRYPTO_E_BUSY       Job could not be added to the queue because the queue is already full.
 * \retval E_OK                Job was added to the queue.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) addJobToQueue(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
);

/**
 * \brief Searches for a job in the queue and returns it if found.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 * \param [in] jobId           The job id that is searched in the queue.
 *
 * \return job                 Pointer to the job.
 */
static FUNC(Crypto_JobType*, CRYPTO_82_HSM_CODE) getJobInQueueFromJobId(
    VAR(uint32, AUTOMATIC) objectId,
    VAR(uint32, AUTOMATIC) jobId
);

/**
 * \brief Tries to lock a job in a Crypto Driver object.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 * \param [in] job             Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                             information.
 *
 * \retval E_OK                Job was locked successfully or job was already locked.
 * \retval E_NOT_OK            Job could not be locked because another job was already locked.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) tryToGetJobLock(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Removes the first job from a Crypto Driver object queue.
 *
 * \param [in] objectId        Crypto Driver Object Id.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) popTopJobFromQueue(VAR(uint32, AUTOMATIC) objectId);

/**
 * \brief Calls the corresponding callback function, if any, for job postprocessing.
 *
 * \param [in] service         The AUTOSAR specified service, taken from the job configuration.
 * \param [in] objectId        Crypto Driver Object Id.
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processAsync_LocalCbk(
    VAR(uint32, AUTOMATIC) service,
    VAR(uint32, AUTOMATIC) objectId
);

/**
 * \brief Calls the respective dispatch function from the dispatch table for the given job and with the correct
 *        operation mode.
 *
 * \param [in] objectId Crypto Driver Object Id.
 * \param [in] job      Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                      information.
 *
 * \retval E_OK         The dispatching was successful.
 * \retval E_NOT_OK     The dispatching was unsuccessful.
 */
static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) dispatchJob(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
);

/**
 * \brief Dispatches a asynchronous job and updates the relevant asynchronous processing and crypto driver flags.
 *
 * \param [in] jobAtTopOfQueue      Pointer to a pointer which references the top job in the queue.
 * \param [in] objectId             Crypto Driver Object Id.
 *                                  
 */
static FUNC(void, CRYPTO_82_HSM_CODE) dispatchJobAsync(
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) jobAtTopOfQueue, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
);

/**********************************************************************************************************************\
 * PRIVATE FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) removeJobFromQueue(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);

    if (job != NULL_PTR)
    {
        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
        
        for (uint32 i = 0u; i < queueSize; i++)
        {
            if ((*(queue + i)) != NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            {
                if ((*(queue + i))->jobInfo->jobId == job->jobInfo->jobId) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                {
                    *(queue + i) = NULL_PTR; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */

                    /* Shift elements in queue to cover empty slot. */
                    for (uint32 j = i; j < queueSize - 1uL; j++)   /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a condition checked at another line. */
                    {
                        *(queue + j) = *(queue + j + 1uL);  /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to the array size and will not access out of bounds memory. */

                        if (*(queue + j + 1uL) == NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to the array size and will not access out of bounds memory. */
                        {
                            break;
                        }
                    }

                    if(*(queue + queueSize - 1uL) != NULL_PTR)  /* PRQA S 0488  #This rule violation is surpressed because the value of "queueSize -1 " is less than the array size and will not access out of bounds memory. */
                    {
                        *(queue + queueSize - 1uL) = NULL_PTR;  /* PRQA S 0488  #This rule violation is surpressed because the value of "queueSize -1 " is less than the array size and will not access out of bounds memory. */
                    }

                    ret = E_OK;
                    break;
                }
            }
        }

        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
    }

    return ret;
}

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) cancelJobLocal(VAR(uint32, AUTOMATIC) objectId)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) retCancel;
    VAR(Std_ReturnType, AUTOMATIC) ret = E_OK;

    if ((boolean)isJobState(Crypto_82_Hsm_driverObjects[objectId].job, CRYPTO_JOBSTATE_ACTIVE) == FALSE)
    {
        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

        Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelJobId =  ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
        Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested = FALSE;

        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
        /** No Job  to Cancel */
    }
    else
    {
        /** Job is in state active */
        retCancel = ecy_hsm_Csai_CancelJob(Crypto_82_Hsm_driverObjects[objectId].jobHandle);

        if (retCancel == ecy_hsm_CSAI_SUCCESS)
        {
            setJobState(getCurrentJob(objectId), CRYPTO_JOBSTATE_IDLE);

            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

            Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelJobId = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
            Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested = FALSE;

            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

            ret = E_OK;
        }
        else
        {
            /* Satisfies SWS_Crypto_00143 */
            ret = E_NOT_OK;

            if (Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested == FALSE)
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, Crypto_82_Hsm_driverObjects[objectId].job->jobId, retCancel);
            }
            else
            {
                Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_CANCEL_JOB, Crypto_82_Hsm_driverObjects[objectId].job->jobId, retCancel);
            }
        }
    }

    return ret;
}

#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
static FUNC(void, CRYPTO_82_HSM_CODE) calloutAcquireResource(void)
{
    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD();
}

static FUNC(void, CRYPTO_82_HSM_CODE) calloutReleaseResource(void)
{
    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_LLD();
}

static FUNC(void, CRYPTO_82_HSM_CODE) calloutGetCounterValue(P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) counterValue) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    (void)GetCounterValue(CRYPTO_82_HSM_OS_COUNTER, counterValue);
}

static FUNC(void, CRYPTO_82_HSM_CODE) calloutGetElapsedValue(
    VAR(uint32, AUTOMATIC) value,
    P2VAR(uint32, AUTOMATIC, CRYPTO_82_HSM_VAR) pElapsedValue /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    (void)GetElapsedValue(CRYPTO_82_HSM_OS_COUNTER, &value, pElapsedValue);
}
#endif /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */

static INLINE FUNC(void, CRYPTO_82_HSM_CODE) setDriverState(VAR(Crypto_StateType, AUTOMATIC) state)
{
    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

    cryptoDrvContext.driverState = state;

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
}

static INLINE FUNC(void, CRYPTO_82_HSM_CODE) setDriverStateInit(VAR(Crypto_StateType, AUTOMATIC) state)
{
    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT();

    cryptoDrvContext.driverState = state;

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT();
}

static INLINE FUNC(void, CRYPTO_82_HSM_CODE) setHsmInitState(VAR(Hsm_InitStateType, AUTOMATIC) initState)
{
    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

    cryptoDrvContext.hsmInitState = initState;

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
}

#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateWaitForBooted(void)
{
    VAR(HSM_ModeT, AUTOMATIC) hsmMode;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) err = ecy_hsm_CSAI_SUCCESS;

    err = ecy_HSM_WaitForBooted(10);
 
    if (ecy_hsm_CSAI_SUCCESS == err) 
    { 
        err = ecy_HSM_ClockConfigure(CRYPTO_82_HSM_CLOCK_DIVIDER);

        if (ecy_hsm_CSAI_SUCCESS == err)
        {
            err = ecy_HSM_Release();
            if (err == ecy_hsm_CSAI_SUCCESS)
            {
                setHsmInitState(HSM_INIT_STATE_RELEASED);
            }
        }
    } 
    else 
    { 
        hsmMode = ecy_HSM_GetMode();  
        switch (hsmMode) 
        { 
            case HSM_MODE_CORE_APP: 
                setHsmInitState(HSM_INIT_STATE_INITIALIZED);
                break;

            default: 
                /* Do nothing. */
                break; 
        } 
    } 
}
#endif

static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateReleased(void)
{
    VAR(HSM_ModeT, AUTOMATIC) hsmMode;
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) err = ecy_hsm_CSAI_SUCCESS;

    hsmMode = ecy_HSM_GetMode();

    if (hsmMode == HSM_MODE_CORE_APP)
    {        
        err = ecy_HSM_Configure(NULL_PTR, 0UL); 
        if (err == ecy_hsm_CSAI_SUCCESS)
        {
            setHsmInitState(HSM_INIT_STATE_INITIALIZED);
        }        
    }
}

static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateInitialized(void)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr = ecy_hsm_CSAI_SUCCESS;
    VAR(SHE_ErrorCodeT, AUTOMATIC)  init_err;

    /* Open Hsm session for driver object used for key management */
    csaiErr = ecy_hsm_Csai_OpenSession(
        ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT],
        &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle
    );

#if (CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON)
    /* Open Hsm session for DENSO Extensions driver object */
    csaiErr |= ecy_hsm_Csai_OpenSession(
        ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS],
        &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DENSOEXTENSIONS].sessionHandle
    );

    /* Open Hsm session for DENSO Extensions DFlash Reorg driver object */
    csaiErr |= ecy_hsm_Csai_OpenSession(
        ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG],
        &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_DFLASHREORG].sessionHandle
    );

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

    Crypto_82_Hsm_Ext_cleanBulkMacList(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN);
    
    Crypto_82_Hsm_Ext_cleanBulkMacList(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER);

    /* Open Hsm session for DENSO Bulk Mac Gen driver object */
    csaiErr |= ecy_hsm_Csai_OpenSession(
        ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN],
        &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN].sessionHandle
    );

    /* Open Hsm session for DENSO Bulk Mac Ver driver object */
    csaiErr |= ecy_hsm_Csai_OpenSession(
        ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
        (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER],
        &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER].sessionHandle
    );
#endif

#endif /* ( CRYPTO_82_HSM_DENSO_EXTENSIONS == STD_ON ) */

    /* Open Hsm session for driver objects used for sync and async jobs */
    for (uint32 objectId = CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS; objectId < CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS; objectId++)
    {
        csaiErr |= ecy_hsm_Csai_OpenSession(
            ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING,
            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId],
            &Crypto_82_Hsm_driverObjects[objectId].sessionHandle
        );
    }   

    /* Open SHE session */
    init_err = SHE_Init();

    if ( (csaiErr != ecy_hsm_CSAI_SUCCESS) || (ERC_NO_ERROR != init_err) )
    {
        setDriverState(CRYPTO_STATE_ERROR);

        if (csaiErr != ecy_hsm_CSAI_SUCCESS)
        {
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_INIT, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, csaiErr);
        }

        if (ERC_NO_ERROR != init_err)
        {
            Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_INIT, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, (uint32)init_err);
        }
    }
    else
    {
        cryptoDrvContext.currentKeyIndex = 0uL;
        setDriverState(CRYPTO_STATE_INIT_KEYS);
    }

#if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
    /* Load key "Validity" status from NvM */
    (void)Crypto_82_Hsm_Ext_Init();
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */    
}

static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateKeys(void)
{
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) csaiErr = ecy_hsm_CSAI_SUCCESS;
#if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
    VAR(Crypto_82_Hsm_KeyStatusType, AUTOMATIC) keyStatus = CRYPTO_82_HSM_KEY_INVALID;
    VAR(Crypto_82_Hsm_Ext_ErrorStateType, AUTOMATIC) errDensoExtensions = CRYPTO_82_HSM_EXT_INVALID;
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

    setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, TRUE);


    if (cryptoDrvContext.currentKeyIndex < CRYPTO_82_HSM_NUMBER_OF_KEYS)
    {
        for (uint32 keyIndex = cryptoDrvContext.currentKeyIndex; keyIndex < CRYPTO_82_HSM_NUMBER_OF_KEYS; keyIndex++)
        {
            VAR(uint32,  AUTOMATIC) noOfKeyElements = Crypto_82_Hsm_configKeys[cryptoDrvContext.currentKeyIndex].numberOfKeyElements;
            VAR(uint32, AUTOMATIC) keyElemStartIndex = Crypto_82_Hsm_keyIdToKeyElementIdMap[cryptoDrvContext.currentKeyIndex];

            /* Cycle through all key elements */
            for(uint32 keyElementIndex = keyElemStartIndex; keyElementIndex < keyElemStartIndex + noOfKeyElements; keyElementIndex++) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
            {
                if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT)
                {
                    /* Reset key element validity flag */
                    Crypto_82_Hsm_KeyElementValidity[keyElementIndex] = FALSE;

                    /* If the key element has been configured to be loaded into Hsm RAM during initialization. */
                    if (Crypto_82_Hsm_configKeyElements[keyElementIndex].loadAtInit == TRUE)
                    {
/* If Denso Extensions are used check key validity status */
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)

                        /* Get key "Validity" status  */
                        (void)Crypto_82_Hsm_Ext_KeyStatusRead(cryptoDrvContext.currentKeyIndex, &keyStatus);

                        if (keyStatus == CRYPTO_82_HSM_KEY_VALID)
                        {
                            /* Do nothing -> next step is to load the key into ram*/
                        }
                        else
                        {
                            injectInitalContentPtr(keyElementIndex);
                            continue;
                        }

#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

                        /* Load persistent Key from Nvm into session context. ecy_hsm_CSAI_SUCCESS: key slot is not empty, ecy_hsm_CSAI_ERR_EEPROM_TAG_NOT_FOUND: key slot is empty   */
                        csaiErr = ecy_hsm_Csai_LoadKey(
                            Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].sessionHandle,
                            (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT],
                            Crypto_82_Hsm_configKeys[cryptoDrvContext.currentKeyIndex].HsmKeyId,
                            Crypto_82_Hsm_configKeys[cryptoDrvContext.currentKeyIndex].keyType,
                            &Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle,
                            &Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle);

                        if (csaiErr == ecy_hsm_CSAI_SUCCESS)
                        {
                            /* Successful, start of load key operation. Polling now required. */
                            cryptoDrvContext.currentKeyElementIndex = keyElementIndex;
#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_ON)
                            initLoadFromNvmPolling();
#else  /*(CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)*/
                            setDriverState(CRYPTO_STATE_INIT_POLLING_PENDING);
#endif /* ( CRYPTO_82_HSM_SYNC_POLL_AT_INIT) */
                        }
                    }
                    else
                    {
                        /* Do nothing. */
                    }
                }
                else if (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT)
                {
                    injectInitalContentPtr(keyElementIndex);
                }
                else
                {
                    /* Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType == CRYPTO_82_HSM_DATA_BUFFER_KEY_ELEMENT */

                    if ((Crypto_82_Hsm_configKeyElements[keyElementIndex].keyElementId != CRYPTO_KE_MAC_PROOF) && (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyElementId != CRYPTO_KE_CIPHER_PROOF))
                    {
                        /* If there is an initial value and a data buffer available in the configuration */
                        if ((Crypto_82_Hsm_configKeyElements[keyElementIndex].initialContentPtr != NULL_PTR) && (Crypto_82_Hsm_configKeyElements[keyElementIndex].keyDataPtr != NULL_PTR))
                        {
                           (void)Crypto_82_Hsm_Process_KeyElementSet(
                                cryptoDrvContext.currentKeyIndex,
                                keyElementIndex,
                                Crypto_82_Hsm_configKeyElements[keyElementIndex].initialContentPtr,
                                Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType,
                                Crypto_82_Hsm_configKeyElements[keyElementIndex].keyDataPtr,
                                (Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize));
                        }
                    }
                }
            }
            /* Processing for this key has been finished. (No polling operation required) */
            if (cryptoDrvContext.driverState == CRYPTO_STATE_INIT_KEYS)
            {
                Crypto_82_Hsm_UpdateKeyValidity(cryptoDrvContext.currentKeyIndex);
                cryptoDrvContext.currentKeyIndex = cryptoDrvContext.currentKeyIndex + 1uL;
            }
#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)
            else
            {
                /* cryptoDrvContext.driverState == CRYPTO_STATE_INIT_POLLING_PENDING */

                break;
            }
#endif            
        }
    }
    else
    {
#if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
        do{

            errDensoExtensions = Crypto_82_Hsm_Ext_KeyValiditySerialize();

        }while(errDensoExtensions == CRYPTO_82_HSM_EXT_PROCESSING);
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

        /* Set crypto driver "isInitialized" flag  */
        cryptoDrvContext.isInitialized = TRUE;
        setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT, FALSE);
        /* [SWS_Crypto_00019] */
        setDriverState(CRYPTO_STATE_IDLE);       
    }
}
static FUNC(void, CRYPTO_82_HSM_CODE) initLoadFromNvmPolling(void)
{
    Std_ReturnType ret_poll_request;

#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_ON)
    do
    {
#endif
        ret_poll_request = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT].jobHandle, CRYPTO_82_HSM_SERVICE_ID_INIT, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, CRYPTO_82_HSM_DRIVEROBJECT_KEYMANAGMENT);
#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_ON)
    } while (ret_poll_request == CRYPTO_E_BUSY);
#endif

    if (ret_poll_request == CRYPTO_E_CUSTOM_VAL_TAG_NOT_FOUND)
    {
        injectInitalContentPtr(cryptoDrvContext.currentKeyElementIndex);
    }
    else if (ret_poll_request == E_OK)
    {
        Crypto_82_Hsm_KeyElementValidity[cryptoDrvContext.currentKeyElementIndex] = TRUE;
        Crypto_82_Hsm_UpdateKeyValidity(cryptoDrvContext.currentKeyIndex);
    }
    else
    {
        /*poll failed or busy, key element and key remain unvalid*/
    }

#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)
    {
        if (ret_poll_request != CRYPTO_E_BUSY)
        {
            cryptoDrvContext.currentKeyIndex = cryptoDrvContext.currentKeyIndex + 1uL;
            setDriverState(CRYPTO_STATE_INIT_KEYS);
        }
    }
#endif
}

static FUNC(void, CRYPTO_82_HSM_CODE) injectInitalContentPtr(uint32 keyElementIndex)
{
    Std_ReturnType err;

    /* If there is an initial value available in the configuration */
    if (Crypto_82_Hsm_configKeyElements[keyElementIndex].initialContentPtr != NULL_PTR)
    {
        err = Crypto_82_Hsm_Process_KeyElementSet(
            cryptoDrvContext.currentKeyIndex,
            keyElementIndex,
            Crypto_82_Hsm_configKeyElements[keyElementIndex].initialContentPtr,
            Crypto_82_Hsm_configKeyElements[keyElementIndex].keyStorageType,
            Crypto_82_Hsm_configKeyElements[keyElementIndex].keyDataPtr,
            (Crypto_82_Hsm_configKeyElements[keyElementIndex].keySize));

        if (err == E_OK)
        {
            (void)Crypto_82_Hsm_Process_KeySetValid(cryptoDrvContext.currentKeyIndex);
        }
    }
}

static FUNC(void, CRYPTO_82_HSM_CODE) processInitStateMachine(void)
{
    /* Process init state machine */
    switch (cryptoDrvContext.hsmInitState)
    {
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
    case HSM_INIT_STATE_WAIT_FOR_BOOTED:
        processInitStateWaitForBooted();
        break;
#endif
    case HSM_INIT_STATE_RELEASED:
        processInitStateReleased();
        break;

    case HSM_INIT_STATE_INITIALIZED:

        switch(cryptoDrvContext.driverState)
        {
            case CRYPTO_STATE_INIT:
                processInitStateInitialized();
                break;

            case CRYPTO_STATE_INIT_KEYS:
                processInitStateKeys();
                break;

#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)
            case CRYPTO_STATE_INIT_POLLING_PENDING:
                initLoadFromNvmPolling();
                break;
#endif /*(CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)*/

            default:
                setDriverState(CRYPTO_STATE_ERROR);
                break;
        }

        break;

    default:
        setDriverState(CRYPTO_STATE_ERROR);
        break;
    }
}

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) processJobSync(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType err;
    uint32 csai_err;
    uint8 service = job->jobPrimitiveInfo->primitiveInfo->service;

    /* Set states */
    setDriverObjectBusy(objectId, TRUE);
    setCurrentJob(objectId, job);
    setDriverState(CRYPTO_STATE_ACTIVE);

    /* Call dispatch function for this service */
    err = dispatchJob(objectId, job);

    /* Jobstate is set here to active because otherwise it would conflict with resetting a job using start op mode */
    setJobState(job, CRYPTO_JOBSTATE_ACTIVE);

    if (err == E_OK)
    {
        /* Satisfies SWS_Crypto_00026 */
        err = Crypto_82_Hsm_WaitForJobFinished(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId);
    }

    /* Load results of verification into buffer. This is necessary because cycurHSM interprets results differently, 
    so a switch of value interpretation is required before passing to upper stack */
    if (err == E_OK)
    {
        if ((service == CRYPTO_SIGNATUREVERIFY) || (service == CRYPTO_MACVERIFY))
        {
            if (verificationResult_global[objectId] == TRUE)
            {
                *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
            }
            else
            {
                *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
            }
        }
        else if (service == CRYPTO_AEADDECRYPT)
        {
            if ( (isJobMode(job, CRYPTO_OPERATIONMODE_UPDATE)) && (!isJobMode(job, CRYPTO_OPERATIONMODE_SINGLECALL)) )
            {
                if (FALSE == Crypto_82_Hsm_AEAD_Decrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID])
                {
                    Crypto_82_Hsm_AEAD_Decrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID] = TRUE;

                    csai_err = ecy_hsm_Csai_DecryptUpdate(Crypto_82_Hsm_driverObjects[objectId].jobHandle, job->jobPrimitiveInputOutput.inputPtr, job->jobPrimitiveInputOutput.inputLength,
                                                     job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, job->jobPrimitiveInputOutput.outputLengthPtr);
                    if (csai_err == ecy_hsm_CSAI_SUCCESS)
                    {
                        /* Satisfies SWS_Crypto_00026 */
                        err = Crypto_82_Hsm_WaitForJobFinished(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId);
                    }
                    else
                    {
                        err = E_NOT_OK;
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, csai_err);
                    }
                }
            }

            if (    (err == E_OK) && (isJobMode(job, CRYPTO_OPERATIONMODE_FINISH))      )
            {
                P2CONST(uint8, AUTOMATIC, AUTOMATIC) tagPtr = job->jobPrimitiveInputOutput.tertiaryInputPtr;
                *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;


                for (uint32 index = 0; index < job->jobPrimitiveInputOutput.tertiaryInputLength; index++)
                {
                    if (aeadDecryptTag_global[objectId][index] != tagPtr[index])
                    {						
                        *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                        break;
                    }
                }
            }
        }
        else if (   (service == CRYPTO_AEADENCRYPT) && (isJobMode(job, CRYPTO_OPERATIONMODE_UPDATE)) && (!isJobMode(job, CRYPTO_OPERATIONMODE_SINGLECALL))  )
        {
            if (FALSE == Crypto_82_Hsm_AEAD_Encrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID])
            {
                Crypto_82_Hsm_AEAD_Encrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID] = TRUE;

                csai_err = ecy_hsm_Csai_EncryptUpdate(Crypto_82_Hsm_driverObjects[objectId].jobHandle, job->jobPrimitiveInputOutput.inputPtr, job->jobPrimitiveInputOutput.inputLength,
                                                 job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, job->jobPrimitiveInputOutput.outputLengthPtr);

                if (csai_err == ecy_hsm_CSAI_SUCCESS)
                {
                    /* Satisfies SWS_Crypto_00026 */
                    err = Crypto_82_Hsm_WaitForJobFinished(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId);
                }
                else
                {
                    err = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, csai_err);
                }                
            }
        }
        else if (service == CRYPTO_RANDOMGENERATE)
        {
            P2VAR(uint8, AUTOMATIC, AUTOMATIC) rngOutputPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */                

                rngOutputPtr = job->jobPrimitiveInputOutput.outputPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

                err = CRYPTO_E_ENTROPY_EXHAUSTED;

                uint8 rngOutputValue = rngOutputPtr[0];
            
                for (uint32 index = 1; index < (*job->jobPrimitiveInputOutput.outputLengthPtr); index++)
                {
                    if (rngOutputValue == 0u)
                    {
                        if (rngOutputPtr[index] != 0u)
                        {
                            err = E_OK;
                            break;
                        }
                    }
                    else if (rngOutputValue == 255u)
                    {
                        if (rngOutputPtr[index] != 255u)
                        {
                            err = E_OK;
                            break;
                        }
                    }
                    else
                    {
                        err = E_OK;
                        break;
                    }
                }

            if (err == CRYPTO_E_ENTROPY_EXHAUSTED)
            {
                (void)Crypto_82_Hsm_Memset_s(rngOutputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, 0, *job->jobPrimitiveInputOutput.outputLengthPtr);
            }
        }
        else
        {
            /* Do nothing */
        }           
    }
    /* Reset states */
    setDriverObjectBusy(objectId, FALSE);
    if (E_OK == err)
    {   
        if (isJobMode(job, CRYPTO_OPERATIONMODE_FINISH))
        {
            setCurrentJob(objectId, NULL_PTR);
            setJobState(job, CRYPTO_JOBSTATE_IDLE);
        }    
    }
    else
    {
        setCurrentJob(objectId, NULL_PTR);
        setJobState(job, CRYPTO_JOBSTATE_IDLE);
    }

    return err;
}

static FUNC(void, CRYPTO_82_HSM_CODE) processJobAsync(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    Std_ReturnType ret = E_OK;
    uint32 ret_csai_NVM_Write;
    uint32 ret_csai_LoadKey;
    uint32 ret_csai_ComputeExt;    
    uint32 ret_csai_AEAD;
    
    uint32 service = getServiceFromJob(job);

    /* If no HSM operation has been triggered, and the job handle has not been updated skip polling.*/
    if (Crypto_82_Hsm_driverObjects[objectId].jobHandle != INVALID_JOB_HANDLE_VALUE)
    {
        ret = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, objectId);
    }

    if (service == CRYPTO_KEYSETVALID)
    {
        VAR(uint32, AUTOMATIC) keyMaterialElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;

        getKeyMaterialElementIndex(&keyMaterialElemIndex, job->cryptoKeyId);
        VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(job->cryptoKeyId, keyMaterialElemIndex);

        if (Crypto_82_Hsm_SHE_loadKey[objectId].loadKeyOperationRequired == TRUE) /*this variable is set to true only in case of a she key*/
        {
            if (ret == E_OK)
            {
                /** After the Polling for ecy_hsm_Csai_She_LoadKey/Extended has been finished successfully,
                 *  trigger the Csai_LoadKey() and from the next call of MainFunction poll the ret
                 */
                ret_csai_LoadKey = Crypto_82_Hsm_LoadSHEKey_RAM(objectId, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId);
                if (ret_csai_LoadKey == E_OK)
                {
                        /** Retry the PollingJob for getting the ecy_hsm_Csai_LoadKey() result*/
                        ret = CRYPTO_E_BUSY;
                }
                else
                {
                        /** Error when calling ecy_hsm_Csai_LoadKey() - set Driver State to ERROR*/
                        ret = E_NOT_OK;
                }
            }
#if (CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON)
            else if (ret != CRYPTO_E_BUSY)
            {
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                Crypto_82_Hsm_KeyStatusType densoKeyStatus;
                VAR(uint8, AUTOMATIC) dataSlotByte = keyStatusDataToBeSerialized[(getKeyStatusSlotNumber(job->cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) + getKeyStatusSlotByteNumber(job->cryptoKeyId)]; /* PRQA S 3384  #Wraparound can not occur in this case. */
                densoKeyStatus = (Crypto_82_Hsm_KeyStatusType)((uint8)(dataSlotByte >> getKeyStatusSlotByteStartBitNumber(job->cryptoKeyId) & 0x03u)); /* PRQA S 3384  #Wraparound can not occur in this case. */
                /** For SHE keys */
                if (densoKeyStatus == CRYPTO_82_HSM_KEY_VALID)
                {
#endif
                    Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed = TRUE;
                    ret_csai_LoadKey = Crypto_82_Hsm_LoadSHEKey_RAM(objectId, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId);
                    if (ret_csai_LoadKey == E_OK)
                    {
                        /** Retry the PollingJob for getting the ecy_hsm_Csai_LoadKey() result*/
                        ret = CRYPTO_E_BUSY;
                    }
                    else
                    {
                        /** Error when calling ecy_hsm_Csai_LoadKey() - set Driver State to ERROR*/
                        ret = E_NOT_OK;
                    }
#if (CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON)
                }
#endif
            }
            else
            {
                /* Do nothing */
            }
#endif
        }
        else if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_RAM))
        {
            if (Crypto_82_Hsm_KeySetValid_OperationState[objectId] == CRYPTO_KEY_SET_VALID_INJECT)
            {
                if (ret != CRYPTO_E_BUSY)
                {
                    Crypto_82_Hsm_Process_Inject_Poll_Result(job->cryptoKeyId, ret, keyMaterialElemIndex, retCsaiPersistentOrRamKeyType, objectId);
                }
                if ((ret == E_OK) && (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_NVM))          
                {
                    ret_csai_NVM_Write = Crypto_82_Hsm_WriteToNvm(job->cryptoKeyId, objectId, keyMaterialElemIndex);

                    if (ret_csai_NVM_Write == ecy_hsm_CSAI_SUCCESS)
                    {
                        Crypto_82_Hsm_KeySetValid_OperationState[objectId] = CRYPTO_KEY_SET_VALID_WRITE_TO_NVM;
                        ret = CRYPTO_E_BUSY;
                    }
                    else
                    {
                        ret = E_NOT_OK;
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, ret_csai_NVM_Write);
                    }
                }               
               
            }
        }
        else
        {
            /*empty for MISRA*/
        }
    }
    else if (service == CRYPTO_KEYEXCHANGECALCPUBVAL)
    {
        if (ret == E_OK)
        {
           if (Crypto_82_Hsm_configKeys[job->cryptoKeyId].keyType == ecy_hsm_CSAI_KEYTYPE_RSA_PUBLIC)
           {
                (void)Crypto_82_Hsm_Memcpy_s(&job->jobPrimitiveInputOutput.outputPtr[*(job->jobPrimitiveInputOutput.outputLengthPtr) - 4u], 4u, &keyRef_keyElementGet[objectId].u.rsapair.e, 4u, 4u); /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
           }
        }

    }
    else if (service == CRYPTO_KEYEXCHANGECALCSECRET)
    {
        if (ret == E_OK)
        {
            VAR(uint32, AUTOMATIC) sharedSecretKeyElementIndex;
            P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSharedSecret = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE, &sharedSecretKeyElementIndex);

            switch(Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[objectId])
            {
                case CRYPTO_KEY_EXCHANGE_DHCOMPUTE_EXT_REQUIRED:
                {
                    ret_csai_ComputeExt = ecy_hsm_Csai_DhComputeExt(Crypto_82_Hsm_driverObjects[objectId].sessionHandle,
                                    (ecy_hsm_Csai_JobPriorityT)Crypto_82_Hsm_Driver_Object_Priority[objectId],
                                    job->jobPrimitiveInputOutput.inputPtr,
                                    job->jobPrimitiveInputOutput.inputLength,
                                    elementSharedSecret->keyDataPtr,
                                    elementSharedSecret->keySize,
                                    &keyExchangeCalcSecretCount[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS],
                                    &Crypto_82_Hsm_driverObjects[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS].jobHandle);

                    if (ret_csai_ComputeExt == ecy_hsm_CSAI_SUCCESS)
                    {
                        Crypto_82_Hsm_KeyState[job->cryptoKeyId].keyValid = FALSE;
                        Crypto_82_Hsm_KeyElementValidity[sharedSecretKeyElementIndex] = FALSE;
                        
                        ret = CRYPTO_E_BUSY;
                        Crypto_82_Hsm_KeyExchangeCalcSecret_OperationState[objectId] = CRYPTO_KEY_EXCHANGE_SET_VALIDITY_REQUIRED;
                    }
                    else
                    {
                        ret = E_NOT_OK;
                        Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, ret_csai_ComputeExt);
                    }

                    break;                    
                }

                case CRYPTO_KEY_EXCHANGE_SET_VALIDITY_REQUIRED:
                {
                    Crypto_82_Hsm_KeyElementValidity[sharedSecretKeyElementIndex] = TRUE;
                    
                    break;
                }

                default:
                    ret = E_NOT_OK;
                    break;
            }
        }
    }
    else if ((service == CRYPTO_AEADENCRYPT) && (isJobMode(job, CRYPTO_OPERATIONMODE_UPDATE)) && (!isJobMode(job, CRYPTO_OPERATIONMODE_SINGLECALL)) )
    {
        if (ret == E_OK)
        {
            if (FALSE == Crypto_82_Hsm_AEAD_Encrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID])
            {
                Crypto_82_Hsm_AEAD_Encrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID] = TRUE;

                ret_csai_AEAD = ecy_hsm_Csai_EncryptUpdate(Crypto_82_Hsm_driverObjects[objectId].jobHandle, job->jobPrimitiveInputOutput.inputPtr, job->jobPrimitiveInputOutput.inputLength,
                                                           job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, job->jobPrimitiveInputOutput.outputLengthPtr);

                if (ret_csai_AEAD == ecy_hsm_CSAI_SUCCESS)
                {
                    ret = CRYPTO_E_BUSY;
                }
                else
                {
                    ret = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, ret_csai_AEAD);
                }
            }
        }
    }
    else if ((service == CRYPTO_AEADDECRYPT) && (isJobMode(job, CRYPTO_OPERATIONMODE_UPDATE)) && (!isJobMode(job, CRYPTO_OPERATIONMODE_SINGLECALL)))
    {
        if (ret == E_OK)
        {
            if (FALSE == Crypto_82_Hsm_AEAD_Decrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID])
            {
                Crypto_82_Hsm_AEAD_Decrypt_ADD_received[Crypto_82_Hsm_driverObjects[objectId].objectID] = TRUE;

                ret_csai_AEAD = ecy_hsm_Csai_DecryptUpdate(Crypto_82_Hsm_driverObjects[objectId].jobHandle, job->jobPrimitiveInputOutput.inputPtr, job->jobPrimitiveInputOutput.inputLength,
                                                           job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, job->jobPrimitiveInputOutput.outputLengthPtr);
                
                if (ret_csai_AEAD == ecy_hsm_CSAI_SUCCESS)
                {
                    ret = CRYPTO_E_BUSY;
                }
                else
                {
                    ret = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, job->jobId, ret_csai_AEAD);
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }       

    VAR (uint32, AUTOMATIC) saltKeyElementIndex         = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) iterationsKeyElementIndex   = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR (uint32, AUTOMATIC) passwordKeyElementIndex     = CRYPTO_82_HSM_INVALID_KEY_INDEX;

    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementIterations = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ITERATIONS, &iterationsKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementSalt = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_SALT, &saltKeyElementIndex);
    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) elementPass = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_KEYDERIVATION_PASSWORD, &passwordKeyElementIndex);
  
    switch (ret)
    {
        case E_OK:
        {
            if (service == CRYPTO_KEYSETVALID)
            {
                processJobAsync_KeySetValid(objectId, job, &ret);
            }
            else if (service == CRYPTO_KEYEXCHANGECALCSECRET)
            {
                keyExchangeCalcSecretCount[objectId] = 0;
            }
            else if (service == CRYPTO_KEYDERIVE)
            {
                Crypto_82_Hsm_clearbuffers_KeyDerive(objectId, job->cryptoKeyId, elementIterations, iterationsKeyElementIndex, elementSalt, saltKeyElementIndex, elementPass, passwordKeyElementIndex);
            }
            else if (service == CRYPTO_RANDOMGENERATE)
            {
            P2VAR(uint8, AUTOMATIC, AUTOMATIC) rngOutputPtr; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */                
                
                rngOutputPtr = job->jobPrimitiveInputOutput.outputPtr;
                
                ret = CRYPTO_E_ENTROPY_EXHAUSTED;

                uint8 rngOutputValue = rngOutputPtr[0];
            
                for (uint32 index = 1; index < (*job->jobPrimitiveInputOutput.outputLengthPtr); index++)
                {
                    if (rngOutputValue == 0u)
                    {
                        if (rngOutputPtr[index] != 0u)
                        {
                            ret = E_OK;
                            break;
                        }
                    }
                    else if (rngOutputValue == 255u)
                    {
                        if (rngOutputPtr[index] != 255u)
                        {
                            ret = E_OK;
                            break;
                        }
                    }
                    else
                    {
                        ret = E_OK;
                        break;
                    }
                }

                if (ret == CRYPTO_E_ENTROPY_EXHAUSTED)
                {
                    (void)Crypto_82_Hsm_Memset_s(rngOutputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr, 0, *job->jobPrimitiveInputOutput.outputLengthPtr);
                }
            }            
            else
            {
            	/*do nothing*/
            }                   

            setDriverObjectBusy(objectId, FALSE);
            if (  isJobMode(job, CRYPTO_OPERATIONMODE_FINISH))   
            {
                /* Load results of verification into buffer. This is necessary because cycurHSM interprets results differently, 
                so a switch of value interpretation is required before passing to upper stack */
                if ((service == CRYPTO_SIGNATUREVERIFY) || (service == CRYPTO_MACVERIFY) )
                {
                    if (verificationResult_global[objectId] == TRUE)
                    {
                        *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
                    }
                    else
                    {
                        *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                    }
                }
                else if (service == CRYPTO_AEADDECRYPT)
                {

                    P2CONST(uint8, AUTOMATIC, AUTOMATIC) tagPtr = job->jobPrimitiveInputOutput.tertiaryInputPtr;
                    *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
                    
                    for (uint32 index = 0; index < job->jobPrimitiveInputOutput.tertiaryInputLength; index++)
                    {
                        if (aeadDecryptTag_global[objectId][index] != tagPtr[index])
                        {
                            *(job->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                            break;
                        }
                    }
                }
                else
                {
                    /* Do nothing */
                }                   

                processAsync_LocalCbk(service, objectId);
                setCurrentJob(objectId, NULL_PTR);

                SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

                setJobState(job, CRYPTO_JOBSTATE_IDLE);
                setLock(objectId, JOB_LOCK_FREE);

                SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

                /* Call the CryIf callback */
                CryIf_CallbackNotification(job, ret);

                if(getQueueSize(objectId) > 0uL)
                {
                    Crypto_JobType** jobAtTopOfQueue = &(getJobAtTopOfQueue(objectId)); /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */

                    if (*jobAtTopOfQueue == job)
                    {
                        popTopJobFromQueue(objectId);
                    }

                    if (Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue == FALSE)
                    {
                        dispatchJobAsync(jobAtTopOfQueue, objectId);
                    }
                }  
            }
            else
            {
                CryIf_CallbackNotification(job, ret);
            }

            break;
        }

        case CRYPTO_E_CUSTOM_VAL_TAG_NOT_FOUND:
        case CRYPTO_E_ENTROPY_EXHAUSTED:
        case E_NOT_OK:
        {
            if (service == CRYPTO_KEYSETVALID)
            { 
                processJobAsync_KeySetValid(objectId, job, &ret);
            }
            else if (service == CRYPTO_KEYEXCHANGECALCSECRET)
            {
                keyExchangeCalcSecretCount[objectId] = 0;
            }
            else if (service == CRYPTO_KEYDERIVE)
            {
                Crypto_82_Hsm_clearbuffers_KeyDerive(objectId, job->cryptoKeyId, elementIterations, iterationsKeyElementIndex, elementSalt, saltKeyElementIndex, elementPass, passwordKeyElementIndex);
            }
            else
            {
                /*do nothing*/
            }

            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

            setJobState(job, CRYPTO_JOBSTATE_IDLE);
            setLock(objectId, JOB_LOCK_FREE);
            setCurrentJob(objectId, NULL_PTR);
            setDriverObjectBusy(objectId, FALSE);

            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

            /* Call the CryIf callback */
            CryIf_CallbackNotification(job, ret);

            if(getQueueSize(objectId) > 0uL)
            {
                Crypto_JobType** jobAtTopOfQueue = &(getJobAtTopOfQueue(objectId)); /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */

                /* Remove failed job from the queue */
                if (*jobAtTopOfQueue == job)
                {
                    popTopJobFromQueue(objectId);
                }

                if (Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue == FALSE)
                {
                    dispatchJobAsync(jobAtTopOfQueue, objectId);
                }
            }
            
            break;
        }

        default:
        /* Do nothing. */
            break;
    }
}

static FUNC(void, CRYPTO_82_HSM_CODE) processJobAsync_KeySetValid(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    Std_ReturnType* ret)
{
    VAR(uint32, AUTOMATIC) keyMaterialElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
        
    getKeyMaterialElementIndex(&keyMaterialElementIndex, job->cryptoKeyId);
    VAR(Crypto_82_Hsm_csaiPersistentOrRamKeyType, AUTOMATIC) retCsaiPersistentOrRamKeyType = csaiPersistentOrRamKeyType(job->cryptoKeyId, keyMaterialElementIndex);

    if (Crypto_82_Hsm_KeyState[(job->cryptoKeyId) % CRYPTO_82_HSM_NUMBER_OF_KEYS].keyValid == FALSE)
    {
        if (*ret == E_OK)
        {
            /* If the key element is persistent or ram */
                if ((Crypto_82_Hsm_configKeyElements[keyMaterialElementIndex % CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS].keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT) ||
                    (Crypto_82_Hsm_configKeyElements[keyMaterialElementIndex % CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS].keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT))
                {
                    if (retCsaiPersistentOrRamKeyType != CRYPTO_82_HSM_KEYTYPE_RAM)
                    {
                        Crypto_82_Hsm_KeyElementValidity[keyMaterialElementIndex] = TRUE;
                    }

                    /* If it is a SHE, SHE extended or she ram key */
                    if ((retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED) || (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_RAM))
                    {
    #if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )                        
                    if (Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed == TRUE)
                    {
                        *ret = E_NOT_OK;
                    }
    #endif                
                    VAR(uint32, CRYPTO_82_HSM_VAR) proof_keyElemIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
                    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) proof_element;
                    P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) mac_proof_element;

                    mac_proof_element = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_MAC_PROOF, &proof_keyElemIndex);
                    
                    if (proof_keyElemIndex == CRYPTO_82_HSM_INVALID_KEY_INDEX)
                    {
                        proof_element = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_PROOF, &proof_keyElemIndex);
                    }
                    else
                    {
                        proof_element = mac_proof_element;
                    }

                    /* Clean buffers, set element to valid and memcpy if necessary*/
                    if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE)
                    {
                        if(proof_keyElemIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
    #if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )                                
                            if (Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed != TRUE)
    #endif                                
                            {
                                /* Starting address of sheM4 buffer is used here but data is copied to both sheM4 and sheM5 buffers. */
                                (void)Crypto_82_Hsm_Memcpy_s(proof_element->keyDataPtr, SHE_M4_M5_SIZE, Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM4, SHE_M4_M5_SIZE, SHE_M4_M5_SIZE);
                                Crypto_82_Hsm_KeyElementValidity[proof_keyElemIndex] = TRUE;
                            }
                        }
                    }
                    else if (retCsaiPersistentOrRamKeyType == CRYPTO_82_HSM_KEYTYPE_SHE_EXTENDED)
                    {
                        if(proof_keyElemIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                        {
    #if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )                                
                            if (Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed != TRUE)
    #endif      
                            {                        
                                /* Starting address of sheM4 buffer is used here but data is copied to both sheM4 and sheM5 buffers. */
                                (void)Crypto_82_Hsm_Memcpy_s(proof_element->keyDataPtr, SHE_M4_M5_SIZE, Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM4, SHE_M4_M5_SIZE, SHE_M4_M5_SIZE);
                                Crypto_82_Hsm_KeyElementValidity[proof_keyElemIndex] = TRUE;
                            }
                        }
                    }
                    else
                    {
                        /*empty for MISRA*/
                    }
    #if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )
                            Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed = FALSE;
    #endif                                    
                }

                #if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
                Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_VALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(job->cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES) % KEY_STATUS_DATA_ARRAY_SIZE)], job->cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
                Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(job->cryptoKeyId);
                #endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */

                /* Set key to valid if all key elements are valid */
                Crypto_82_Hsm_UpdateKeyValidity(job->cryptoKeyId);

                if (Crypto_82_Hsm_KeyState[job->cryptoKeyId].keyValid != TRUE)
                {
                    *ret = E_NOT_OK;
                }
            }
        }
        else
        {
            *ret = E_NOT_OK;
#if ( CRYPTO_82_HSM_RELOAD_PREVIOUS_SHE_KEYS == STD_ON )                
            Crypto_82_Hsm_SHE_loadKey[objectId].serializeKeyFailed = FALSE;
#endif

#if ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON )
            Crypto_82_Hsm_Ext_SetKeyStatusBitMask(CRYPTO_82_HSM_KEY_INVALID, &keyStatusDataToBeSerialized[((getKeyStatusSlotNumber(job->cryptoKeyId) * SIZE_OF_SECRET_DATA_SLOT_IN_BYTES))  % KEY_STATUS_DATA_ARRAY_SIZE], job->cryptoKeyId); /* PRQA S 3384  #Wraparound can not occur in this case. */
            Crypto_82_Hsm_Ext_SetKeyStatusDirtyFlag(job->cryptoKeyId);
#endif /* ( CRYPTO_82_HSM_DENSO_KEY_VALIDITY == STD_ON ) */  
        }
    }

    Crypto_82_Hsm_clearbuffers_KeySetValid(job->cryptoKeyId, objectId);
}

static INLINE FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) tryToGetJobLock(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(uint32, AUTOMATIC) jobId = getJobId(job);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    /* The job lock is free, lock it */
    if (isLockFree(objectId))
    {
        setLock(objectId, jobId);
        ret = E_OK;
    }
    /* The job is already locked */
    else if (isJobInLock(objectId, jobId))
    {
        ret = E_OK;
    }
    /* The driver object is occupied by another job */
    else
    {
        ret = E_NOT_OK;
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    return ret;
}

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) addJobToQueue(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret;
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) temp_job; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) temp_job_2; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);
    VAR(uint32, AUTOMATIC) storeIndex = 0uL;
    

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();


    if (isJobMode(job, CRYPTO_OPERATIONMODE_START))
    {
        ret = CRYPTO_E_BUSY;

        /* Add job to the queue and sort (Satisfies SWS_Crypto_00030 )*/
        for (uint32 i = 0uL; i < queueSize; i++)
        {
            if (*(queue + i) != NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            {
                if(job->jobInfo->jobPriority > ((*(queue + i))->jobInfo->jobPriority) ) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                {
                    temp_job = *(queue + i); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                    *(queue + i) = job; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */

                    if (*(queue + i + 1uL) != NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                    {
                        /* Shift elements */
                        for (uint32 j = i+1uL; j < queueSize - 1uL; j++) /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a condition checked at another line. */
                        {
                            temp_job_2 = *(queue + j); /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to the array size and will not access out of bounds memory. */
                            *(queue + j) = temp_job; /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to the array size and will not access out of bounds memory. */
                            temp_job = temp_job_2;
                            storeIndex = j;
                        }                            

                        *(queue + storeIndex + 1uL) = temp_job; /* PRQA S 0488  #This rule violation is surpressed because the value of "storeIndex + 1" is constrained to  the array size and will not access out of bounds memory. */
                    }
                    else
                    {
                        *(queue + i + 1uL) = temp_job; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                    }

                    ret = E_OK;

                    break;
                }
            }
            else
            {
                *(queue + i) = job; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                ret = E_OK;
                break;
            }
        }
    }
    /* Cannot add job to the queue */
    else
    {
        ret = E_NOT_OK;
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    return ret;
}

static FUNC(Crypto_JobType*, CRYPTO_82_HSM_CODE) getJobInQueueFromJobId(
    VAR(uint32, AUTOMATIC) objectId,
    VAR(uint32, AUTOMATIC) jobId
)
{
    P2VAR(Crypto_JobType, AUTOMATIC, AUTOMATIC) ret = NULL_PTR; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(boolean, AUTOMATIC) isFound = FALSE;
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    for (uint32 i = 0u; (i < queueSize) && (isFound == FALSE); i++)
    {
        if (*(queue + i) != NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            if ((*(queue + i))->jobInfo->jobId == jobId) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            {
                isFound = TRUE;
                ret = *(queue + i); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            }
        }
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    return ret;
}

static FUNC(void, CRYPTO_82_HSM_CODE) popTopJobFromQueue(VAR(uint32, AUTOMATIC) objectId)
{
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    for (uint32 i = 0u; i < queueSize; i++)
    {
        if (i < (queueSize - 1uL)) /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a condition checked at another line. */
        {
            *(queue + i) = *(queue + i + 1uL); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        }
    }

    *(queue + queueSize - 1uL) = NULL_PTR; /* PRQA S 0488  #This rule violation is surpressed because the value of "queueSize -1 " is less than the array size and will not access out of bounds memory. */

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
}

static FUNC(void, CRYPTO_82_HSM_CODE) processAsync_LocalCbk(
    VAR(uint32, AUTOMATIC) service,
    VAR(uint32, AUTOMATIC) objectId
)
{
    if (Crypto_82_Hsm_DispatchTable[service].callbackFctPtr != NULL_PTR)
    {
        Crypto_82_Hsm_DispatchTable[service].callbackFctPtr(objectId);
    }
    else
    {
        /** No post-processing function required for this service. */
    }
}

static FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) dispatchJob(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(uint32, AUTOMATIC) service = getServiceFromJob(job);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

    if (Crypto_82_Hsm_DispatchTable[service].isKeyRequired != FALSE)
    {
        VAR(uint32, AUTOMATIC) keyHandleIndex = INVALID_KEY_HANDLE_VALUE;
        P2CONST(Crypto_82_Hsm_ConfigKeyElementType, AUTOMATIC, CRYPTO_82_HSM_CONST) keyMaterialElement = Crypto_82_Hsm_findKeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY, &keyHandleIndex);

        if (keyHandleIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
        {
            Crypto_82_Hsm_driverObjects[objectId].keyHandle = Crypto_82_Hsm_runtimeKeys[keyHandleIndex].keyHandle;
        }
    }


    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

    /* Satisfies SWS_Crypto_00020 */
    /* START or SINGLECALL while IDLE or ACTIVE; SWS_Csm_01028 specifies that a job can only be either IDLE or ACTIVE */
    if (isJobMode(job, CRYPTO_OPERATIONMODE_START))
    {
        if( isJobState(job,CRYPTO_JOBSTATE_ACTIVE))
        {
            (void)cancelJobLocal(objectId);
        }

        /* Clear job handle value. */
        Crypto_82_Hsm_driverObjects[objectId].jobHandle = INVALID_JOB_HANDLE_VALUE;
    }

    ret = Crypto_82_Hsm_DispatchTable[service].functionPtr(&Crypto_82_Hsm_driverObjects[objectId % CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS]);

    return ret;
}

static FUNC(void, CRYPTO_82_HSM_CODE) dispatchJobAsync(
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) jobAtTopOfQueue, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
)
{
    /* Dispatch the next job in the queue */
    if (*jobAtTopOfQueue != NULL_PTR)
    {
        /* Return code is not checked because the dispatchJobAsync function is only called when the driverObject is not currently processing any job. */
        (void)tryToGetJobLock(objectId, *jobAtTopOfQueue);

        VAR(Std_ReturnType, AUTOMATIC) retDispatch;

        setCurrentJob(objectId, *jobAtTopOfQueue);
        retDispatch = dispatchJob(objectId, *jobAtTopOfQueue);

        if (retDispatch == E_OK)
        {
            setJobState(*jobAtTopOfQueue, CRYPTO_JOBSTATE_ACTIVE);
            setDriverObjectBusy(objectId, TRUE);
            setDriverState(CRYPTO_STATE_ACTIVE);
        }
        else
        {
            CryIf_CallbackNotification(*jobAtTopOfQueue, retDispatch);
            setLock(objectId, JOB_LOCK_FREE);
            setCurrentJob(objectId, NULL_PTR);
        }

        popTopJobFromQueue(objectId);
    }
}

/**********************************************************************************************************************\
 * PUBLIC FUNCTION IMPLEMENTATIONS
\**********************************************************************************************************************/

FUNC(boolean, CRYPTO_82_HSM_CODE) isQueueEmpty(VAR(uint32, AUTOMATIC) objectId)
{
    boolean ret = TRUE;
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    if ((*queue) != NULL_PTR)
    {
        ret = FALSE;
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    return ret;
}

FUNC(boolean, CRYPTO_82_HSM_CODE) isQueueFull(VAR(uint32, AUTOMATIC) objectId)
{
    boolean ret = TRUE;
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    for (uint32 i = 0u; i < queueSize; i++)
    {
        if ((*(queue + i)) == NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            ret = FALSE;
            break;
        }
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    return ret;
}

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Init(P2CONST(Crypto_ConfigType, AUTOMATIC, CRYPTO_82_HSM_CONST) configPtr) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)    
    VAR(ecy_hsm_Csai_ErrorT, AUTOMATIC) err;
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)    
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
#endif /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */    
    /* [SWS_Crypto_00215] */
    CRYPTO_UNUSED_PARAM(configPtr);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT();

    (void)Crypto_82_Hsm_Memset_s(&cryptoDrvContext, sizeof(Crypto_ContextType), 0u, sizeof(Crypto_ContextType));
    (void)Crypto_82_Hsm_Memset_s(Crypto_82_Hsm_driverObjects, sizeof(Crypto_82_Hsm_driverObjects), 0u, sizeof(Crypto_82_Hsm_driverObjects));

    for (uint32 objectId = 0; objectId < CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS; objectId++)
    {
        Crypto_82_Hsm_driverObjects[objectId].objectID = objectId;
        Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue = FALSE;

        if (objectId >= CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS_WITHOUT_QUEUE)
        {
            for(uint32 jobIndex = 0; jobIndex < getQueueSize(objectId); jobIndex++)
            {
                *(getQueue(objectId)+jobIndex) = NULL_PTR; /* PRQA S 0488  #This rule violation is surpressed because the value of "jobIndex" is constrained to the array size and will not access out of bounds memory. */
            }
        }

        (void)Crypto_82_Hsm_Memset_s(Crypto_82_Hsm_SHE_Proof_Key_Data_Buffer[objectId].sheM4, SHE_M4_M5_SIZE, 0u, SHE_M4_M5_SIZE);

        Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelJobId = ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE;
        Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested = FALSE;

        jobLock[objectId] = JOB_LOCK_FREE;
        Crypto_82_Hsm_KeySetValid_OperationState[objectId] = CRYPTO_KEY_SET_VALID_NO_OPERATION;

        Crypto_82_Hsm_passParam[objectId].length = 0u;
        Crypto_82_Hsm_passParam[objectId].pin = NULL_PTR;

        Crypto_82_Hsm_saltParam[objectId].length = 0u;
        Crypto_82_Hsm_saltParam[objectId].pin = NULL_PTR;
    }
    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_INIT_DRIVER_OBJECT();

    for (uint32 keyIndex = 0u; keyIndex < CRYPTO_82_HSM_NUMBER_OF_KEYS; keyIndex++)
    {
        Crypto_82_Hsm_KeyState[keyIndex].KeyElementSetKeyDataPtr = NULL_PTR;
        Crypto_82_Hsm_KeyState[keyIndex].KeyElementSetKeyLength = 0u;        
    }

    for (uint32 keyElementIndex = 0u; keyElementIndex < CRYPTO_82_HSM_NUMBER_OF_KEY_ELEMENTS; keyElementIndex++)
    {
        Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle = INVALID_KEY_HANDLE_VALUE;
    }

#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
    err = ecy_HSM_ConfigureCallouts(
        &calloutAcquireResource,
        &calloutReleaseResource,
        &calloutGetCounterValue,
        &calloutGetElapsedValue);

    if (err != ecy_hsm_CSAI_SUCCESS)
    {
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)

        detErr = CRYPTO_E_INIT_FAILED;

#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */

        setDriverStateInit(CRYPTO_STATE_ERROR);
    }
    else
    {
        setDriverStateInit(CRYPTO_STATE_INIT);
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)

        if (detErr != CRYPTO_DET_NO_ERROR)
        {
            (void)Det_ReportError(
                CRYPTO_82_HSM_MODULE_ID,
                CRYPTO_82_HSM_INSTANCE_ID,
                CRYPTO_SERVICE_ID_INIT,
                detErr);
        }

#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

#else
    setDriverStateInit(CRYPTO_STATE_INIT);
#endif
}

#if (CRYPTO_82_HSM_VERSION_INFO_API == STD_ON)

FUNC(void, CRYPTO_82_HSM_CODE)
Crypto_82_Hsm_GetVersionInfo(                                                                     /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
                             P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_82_HSM_VAR) versioninfo /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;
    /* Satisfies SWS_Crypto_00047 */
    if (versioninfo == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }
    else
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        versioninfo->vendorID = CRYPTO_82_HSM_VENDOR_ID;
        versioninfo->moduleID = CRYPTO_82_HSM_MODULE_ID;
        versioninfo->sw_major_version = CRYPTO_82_HSM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = CRYPTO_82_HSM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = CRYPTO_82_HSM_SW_PATCH_VERSION;
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)

    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_SERVICE_ID_GET_VERSION_INFO,
            detErr);
    }

#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */
}

#endif /* (CRYPTO_82_HSM_VERSION_INFO_API == STD_ON) */

/* TODO: Review Design (This will likely change as more functionality is added to ProcessJob) */
FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_ProcessJob( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    /* TODO: Implement SWS 00199, 00025  */

    /* SWS_Crypto_00121 conflict with SWS_Crypto_00143? (from SWS_Crypto_00143 it is deduced that an asynchronous
    job remains in queue while it is being processed) */
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;
    
    /* Satisfies SWS_Crypto_00057 */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
    }
    /* Satisfies SWS_Crypto_00059 */
    else if (job == NULL_PTR)
    {
        detErr = CRYPTO_E_PARAM_POINTER;
    }
    /* Satisfies SWS_Crypto_00058 */
    else if ( (objectId >= CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS) )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    /* Satisfies SWS_Crypto_00064 && SWS_Crypto_00067 - JobKeySetValid does not require ALGO FAMs, MODE etc. */
    else if (((isJobServiceSupported(job)) != TRUE) && (getServiceFromJob(job) != CRYPTO_KEYSETVALID))
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    /* Satisfies SWS_Crypto_00201 && SWS_Crypto_00217 */
    else if ((job->cryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS) && (Crypto_82_Hsm_DispatchTable[getServiceFromJob(job)].isKeyRequired == TRUE))
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    /* Satisfies SWS_Crypto_00202 && SWS_Crypto_00217 */
    else if ((getServiceFromJob(job) == CRYPTO_KEYDERIVE) && (job->targetCryptoKeyId >= CRYPTO_82_HSM_NUMBER_OF_KEYS))
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
    }
    else
#endif /* (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Additional runtime checks as specified by SWSs */
        /* Satisfies SWS_Crypto_00118 */
        if ( ((job->jobState == CRYPTO_JOBSTATE_IDLE) && !(isJobMode(job, CRYPTO_OPERATIONMODE_START))) && (!isBulkMacDriverObject(objectId)) )
        {
            ret = E_NOT_OK;
        }
        /* Satisfies SWS_Crypto_00039 && SWS_Crypto_00072 - JobKeySetValid, JobKeyGenerate, JobKeyExchangeCalcPubVal, JobKeyExchangeCalcPubSecret allow for the key to be invalid */
        else if ( ((Crypto_82_Hsm_KeyState[(job->cryptoKeyId) % CRYPTO_82_HSM_NUMBER_OF_KEYS].keyValid == FALSE) && ( (Crypto_82_Hsm_DispatchTable[getServiceFromJob(job)].isKeyRequired  == TRUE)&& ( ( (1uL << getServiceFromJob(job)) & CRYPTO_82_HSM_KEY_VALIDITY_EXCEPTION_SERVICES) == 0u))) && (!isBulkMacDriverObject(objectId)) )
        {
            ret = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            CONST(Crypto_ProcessingType, AUTOMATIC) processingType = job->jobPrimitiveInfo->processingType;

            if ( (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) || (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) )
            {
#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)
#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)          
                ret = Crypto_82_Hsm_Ext_BulkMac_ProcessJob(objectId, job, processingType, &detErr);
#else                
                ret = Crypto_82_Hsm_Ext_BulkMac_ProcessJob(objectId, job, processingType, NULL_PTR);
#endif
#endif
            }
            else
            {
                /* Satisfies SWS_Crypto_00017 */
                if (isJobMode(job, CRYPTO_OPERATIONMODE_START))
                {
                    (void)removeJobFromQueue(job, objectId);
                }

                if (processingType == CRYPTO_PROCESSING_SYNC)
                {      
                    /* Satisfies SWS_Crypto_00031 */
                    if (!isDriverObjectBusy(objectId))
                    {
                        /** A job Cancel Request has been issued for this job in this Driver Object. */
                        if ((Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelJobId == getJobId(job)) &&
                            (Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested == TRUE))
                        {
                            /* A synchronous job has been cancelled; Satisfies SWS_Crypto_91003 */
                            ret = CRYPTO_E_JOB_CANCELED;
                        }
                        /* Satisfies SWS_Crypto_00199 */
                        else if( (isQueueFull(objectId) == FALSE) || (getQueueSize(objectId) == 0uL))
                        {  
                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                            ret = processJobSync(objectId, job);
                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();


                            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
                        }
                        else
                        {
                            /* Satisfies SWS_Crypto_00032 */
                            ret = CRYPTO_E_BUSY;
                        }
                    }
                    else
                    {
                        P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
                        VAR(boolean, AUTOMATIC) highestPrio = FALSE;

                        /* Satisfies SWS_Crypto_00199 */

                        if ((getQueueSize(objectId) > 0uL) && ((*queue) != NULL_PTR))
                        {   
                            if(job->jobInfo->jobPriority > ((*queue)->jobInfo->jobPriority) )
                            {
                                highestPrio = TRUE;
                            }
                        }

                        if (highestPrio == TRUE)
                        {
                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
                            Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue = TRUE;
                            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
                        }

                        /* Satisfies SWS_Crypto_00034 */
                        ret = CRYPTO_E_BUSY;
                    }
                }
                else /* (processingType == CRYPTO_PROCESSING_ASYNC) */
                {
                    /* Satisfies SWS_Crypto_00020 */
                    if (!isDriverObjectBusy(objectId))
                    {
                        /* The lock is free or the job is already in lock */
                        if (tryToGetJobLock(objectId, job) == E_OK)
                        {
                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
                            
                            setCurrentJob(objectId, job);

                            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                            ret = dispatchJob(objectId, job);

                            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                            /* The job is correctly dispatched based on the operation mode */
                            if (ret == E_OK)
                            {
                                setDriverObjectBusy(objectId, TRUE);
                                setJobState(job, CRYPTO_JOBSTATE_ACTIVE);
                                
                                SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                                setDriverState(CRYPTO_STATE_ACTIVE);
                            }
                            else
                            {
                                setCurrentJob(objectId, NULL_PTR);
                                setLock(objectId, JOB_LOCK_FREE);

                                SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();
                            }
                        }
                        /* The job is not in lock, add it to the queue */
                        else
                        {
                            if(isQueueFull(objectId) == FALSE)
                            {
                                ret = addJobToQueue(job, objectId);
                            }
                            else
                            {
                                ret = CRYPTO_E_BUSY;
                            }
                        }
                    }
                    /* The driver object is busy, try to add the job to the queue */
                    /* Satisfies SWS_Crypto_00033 */
                    else
                    {
                        if (isJobState(job, CRYPTO_JOBSTATE_ACTIVE) && isJobMode(job, CRYPTO_OPERATIONMODE_START))
                        {
                            ret = E_NOT_OK;
                        }
                        else
                        {
                            if(isQueueFull(objectId) == FALSE)
                            {
                                ret = addJobToQueue(job, objectId);
                            }
                            else
                            {
                                ret = CRYPTO_E_BUSY;
                            }

                        }
                    }      
                }
            }
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            detErr
        );

    }
#endif /* (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON) */

#if (CRYPTO_82_HSM_RUNTIME_ERROR_REPORT == STD_ON)
    if (ret == CRYPTO_E_ENTROPY_EXHAUSTED)
    {
        (void)Det_ReportRuntimeError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB,
            CRYPTO_E_RE_ENTROPY_EXHAUSTED
        );
    }
#endif /* (CRYPTO_82_HSM_RUNTIME_ERROR_REPORT == STD_ON) */

    return ret;
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_CancelJob( /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
    VAR(uint32, AUTOMATIC) objectId,
#if ( CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_ON )
    CONSTP2CONST(Crypto_JobInfoType, AUTOMATIC, CRYPTO_82_HSM_CONST) jobInfo)
{
#else /* (CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_ON) */
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
#endif /* (CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_ON) */
    VAR(Std_ReturnType, AUTOMATIC) ret_val = E_OK;

#if (CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC) detErr = CRYPTO_DET_NO_ERROR;

    /* Satisfies SWS_Crypto_00123 */
    if (Crypto_82_Hsm_IsDriverInitialized() == FALSE)
    {
        detErr = CRYPTO_E_UNINIT;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00124 */
    else if ( (objectId >= CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS) || (objectId < CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS) )
    {
        detErr = CRYPTO_E_PARAM_HANDLE;
        ret_val = E_NOT_OK;
    }
    /* Satisfies SWS_Crypto_00125 */
#if ( CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_ON )
    else if (jobInfo == NULL_PTR)
#else
    else if (job == NULL_PTR)
#endif
    {
        detErr = CRYPTO_E_PARAM_POINTER;
        ret_val = E_NOT_OK;
    }
    else
#endif /* ( CRYPTO_82_HSM_DEV_ERROR_DETECT == STD_ON ) */
    {
        if (Crypto_82_Hsm_driverObjects[objectId].job == NULL_PTR) /* No job is in progress */
        {
            ret_val = E_OK;
        }
        else
        {
#if ( CRYPTO_82_HSM_CANCEL_JOB_WITH_JOB_INFO_TYPE == STD_OFF )
            CONSTP2CONST(Crypto_JobInfoType, AUTOMATIC, CRYPTO_82_HSM_CONST) jobInfo = job->jobInfo;
#endif
            if (Crypto_82_Hsm_driverObjects[objectId].job->jobInfo->jobId == jobInfo->jobId) /* Check if job is currently in progress and at the top of the queue */
            {
                SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelJobId = jobInfo->jobId;
                Crypto_82_Hsm_driverObjects[objectId].cancelJob.cancelRequested = TRUE;

                SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_DRIVER_OBJECT();

                ret_val = cancelJobLocal(objectId);
            }
            else /* Job is not currently being processed */
            {
                if (0uL < getQueueSize(objectId))
                {
                    if (isQueueEmpty(objectId) == FALSE)
                    {
                        (void)removeJobFromQueue(getJobInQueueFromJobId(objectId, jobInfo->jobId), objectId); /* check if job is in the queue and remove it */
                    }
                }
                ret_val = E_OK;
            }
        }
    }

#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)
    if (detErr != CRYPTO_DET_NO_ERROR)
    {
        (void)Det_ReportError(
            CRYPTO_82_HSM_MODULE_ID,
            CRYPTO_82_HSM_INSTANCE_ID,
            CRYPTO_82_HSM_SERVICE_ID_CANCEL_JOB,
            detErr
        ); 
    }
#endif  /* ( CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON ) */

    return ret_val;
}

/**
 * \startuml {Crypto_82_Hsm_MainFunction_2.png}
 * [*] --> CRYPTO_STATE_INIT
 *   note left
 *   This state machine diagram describes transitions between 2 different types 
 *   of states (HSM state and CRYPTO DRIVER state).
 * 
 *   During the CRYPTO DRIVER state "CRYPTO_STATE_INIT", the HSM states transition 
 *   between one another.
 *  
 *   After CRYPTO_STATE_INIT the CRYPTO DRIVER states transition between one another, independent of HSM states.
 * 
 *   These transitions take place in the call stack of the Crypto_82_Hsm_MainFunction.
 *   end note
 * state CRYPTO_STATE_INIT{
 *    [*] --> HSM_INIT_STATE_WAIT_FOR_BOOTED
 *    HSM_INIT_STATE_WAIT_FOR_BOOTED --> HSM_INIT_STATE_RELEASED: HSM_MODE_BOOTLOADER
 *    HSM_INIT_STATE_WAIT_FOR_BOOTED --> HSM_INIT_STATE_WAIT_FOR_BOOTED: HSM_MODE_BOOTING
 *    HSM_INIT_STATE_WAIT_FOR_BOOTED --> HSM_INIT_STATE_INITIALIZED : HSM_MODE_CORE_APP
 *    HSM_INIT_STATE_RELEASED --> HSM_INIT_STATE_INITIALIZED : HSM_MODE_CORE_APP
 * }
 * 
 *    HSM_INIT_STATE_RELEASED --> CRYPTO_STATE_ERROR:Timeout or other errors
 *    HSM_INIT_STATE_WAIT_FOR_BOOTED --> CRYPTO_STATE_ERROR:Timeout or other errors
 *    HSM_INIT_STATE_INITIALIZED --> CRYPTO_STATE_ERROR: Timeout or other errors
 *    HSM_INIT_STATE_INITIALIZED --> CRYPTO_STATE_INIT_KEYS: Driver objects initialization successful
 * 
 * 
 * CRYPTO_STATE_INIT_KEYS --> CRYPTO_STATE_INIT_POLLING_PENDING: Poll load key
 * CRYPTO_STATE_INIT_POLLING_PENDING --> CRYPTO_STATE_INIT_KEYS
 * CRYPTO_STATE_INIT_KEYS --> CRYPTO_STATE_IDLE: Loading keys is done
 * \enduml
 */
/**
 * \startuml {Crypto_82_Hsm_MainFunction_1.png}
 *
 * start
 * switch (Crypto Driver State?)
 * case (**CRYPTO_STATE_INIT,**\n**CRYPTO_STATE_INIT_KEYS,**\n**CRYPTO_STATE_INIT_POLLING_PENDING**)
 *  partition "CRYPTO_82_HSM_USER_DEF_INIT is STD_OFF" {
 *   if (ECU Start Up?) then (yes)
 *     :Get Start Up time;
 *     if (Encountered\nerror during\nStart Up time\nacquisition?) then (yes)
 *      #pink:Set Crypto Driver to\nCRYPTO_STATE_ERROR;
 *     else (no)
 *     endif
 *   else (no)
 *   endif
 *   :Get Current time;
 *   if (Time Out during Init?) then (yes)
 *      #pink:Set Crypto Driver to\nCRYPTO_STATE_ERROR;
 *   else (no)
 *     #palegreen:Process initialization;
 *   endif
 * }
 *  partition "CRYPTO_82_HSM_USER_DEF_INIT is STD_ON" {
 *   #palegreen:Process initialization;
 * }
 * case (**CRYPTO_STATE_ACTIVE,**\n**CRYPTO_STATE_IDLE**)
 *     partition "CRYPTO_82_HSM_DENSO_BULKMAC is STD_ON" {
 *       if (BulkVer Job state is active?) then (yes)
 *       #palegreen:Call Crypto_82_Hsm_Ext_BulkMac_processJobAsync;
 *       endif
 *       if (BulkGen Job state is active?) then (yes)
 *       #palegreen:Call Crypto_82_Hsm_Ext_BulkMac_processJobAsync;
 *       endif
 *     }  
 *   while (Crypto Driver Objects left to be checked?) is (yes)
 *       if (Is there a job currently being processed?) then (yes)
 *         if (Is the job asynchronous\nand actively being\nprocessed?) then (yes)
 *           #palegreen:Process ASYNC Job;
 *         else (no)
 *         endif
 *       else (no)
 *         if (Should dispatching a\njob from the queue be skipped?) then (yes)
 *         else (no)
 *           if (Is there a job in the queue?) then (yes)
 *             #palegreen:Dispatch it;
 *           else (no)
 *           endif
 *         endif
 *       endif
 *   endwhile (no)
 *   if (Are all jobs from non reserved crypto driver objects done?) then (yes)
 *     if (BULKMAC Gen and BULKMAC Ver driver object not busy?) then (yes)
 *       :Set Crypto Driver to\nCRYPTO_STATE_IDLE;
 *     else (no)
 *     endif
 *   else (no)
 *   endif
 * case (**CRYPTO_STATE_ERROR**)
 *    #lightgray:       NOP        ;
 * endswitch
 * stop
 * \enduml
 */
/**
 * \brief If asynchronous job processing is configured and there are job queues, the function is called cyclically to
 * process queued jobs.
 *
 * \id 0x0C
*/
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_MainFunction(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
    static boolean firstTime = TRUE;
    static TickType initStartTimestamp = 0;
#endif

    switch (cryptoDrvContext.driverState)
    {
    case CRYPTO_STATE_INIT_KEYS:
#if (CRYPTO_82_HSM_SYNC_POLL_AT_INIT == STD_OFF)    
    case CRYPTO_STATE_INIT_POLLING_PENDING:
#endif    
    case CRYPTO_STATE_INIT:
    {
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
        if (firstTime != FALSE)
        {
            firstTime = FALSE;

            if (GetCounterValue(CRYPTO_82_HSM_OS_COUNTER, &initStartTimestamp) != E_OK)
            {
                setDriverState(CRYPTO_STATE_ERROR);
            }
        }

        (void)GetCounterValue(CRYPTO_82_HSM_OS_COUNTER, &cryptoDrvContext.initTimeout);

        if ((cryptoDrvContext.initTimeout - initStartTimestamp) <= CRYPTO_82_HSM_INIT_TIMEOUT)
#endif  /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */
        {
            processInitStateMachine();
        }
#if (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF)
        else
        {
            setDriverState(CRYPTO_STATE_ERROR);
        }
#endif  /* (CRYPTO_82_HSM_USER_DEF_INIT == STD_OFF) */
        break;
    }

    case CRYPTO_STATE_ACTIVE:
    case CRYPTO_STATE_IDLE:
    {
        VAR(boolean, AUTOMATIC) shouldSwitchToIdle = TRUE;

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)
                if (bulkMacVerifyContext.bulkJobState == TRUE)
                {
                    Crypto_82_Hsm_Ext_BulkMac_processJobAsync(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER);
                }                
                
                if (bulkMacGenerateContext.bulkJobState == TRUE)
                {
                    Crypto_82_Hsm_Ext_BulkMac_processJobAsync(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN);
                }
#endif

        for (uint32 objectId = CRYPTO_82_HSM_NUM_RESERVED_DRIVER_OBJECTS; objectId < CRYPTO_82_HSM_NUMBER_OF_DRIVER_OBJECTS; objectId++)
        {
                /* Process the current job */
                P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) currentJob = Crypto_82_Hsm_driverObjects[objectId].job; /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

                if (currentJob != NULL_PTR)
                {
                    if ( (currentJob->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC) 
                        && (Crypto_82_Hsm_driverObjects[objectId].busy == TRUE) )
                    {
                        processJobAsync(objectId, currentJob);
                    }

                    /* Checking in case there are were no other jobs in queue */
                    if (Crypto_82_Hsm_driverObjects[objectId].job != NULL_PTR)
                    {
                        /* Update the currentJob since it might have changed during async processing */
                        currentJob = Crypto_82_Hsm_driverObjects[objectId].job;
                    }
                    /* Switch the driver state to IDLE if all the jobs are in the idle state */
                    shouldSwitchToIdle &= (uint8)(isJobState(currentJob, CRYPTO_JOBSTATE_IDLE));
                }
                /* Do not dispatch any jobs for one call of MainFunction (Satisfies SWS_Crypto_00199) */
                else if (Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue == TRUE)
                {
                    Crypto_82_Hsm_driverObjects[objectId].skipDispatchFromQueue = FALSE;
                }
                /* Dispatch the next job in queue (if it exists) (Satisfies SWS_Crypto_00199) */
                else
                {
                    if (getQueueSize(objectId) > 0uL)
                    {
                        Crypto_JobType **jobAtTopOfQueue = &(getJobAtTopOfQueue(objectId)); /* PRQA S 3383  #Wraparound can not occur in this case; value is constrained by a modulus operation within the macro definition. */
                        Crypto_JobType *foundJob = NULL_PTR;

                        if (*jobAtTopOfQueue != NULL_PTR)
                        {
                            foundJob = *jobAtTopOfQueue;
                        }

                        dispatchJobAsync(jobAtTopOfQueue, objectId);

                        if (foundJob != NULL_PTR)
                        {
                            shouldSwitchToIdle &= (uint8)(isJobState(foundJob, CRYPTO_JOBSTATE_IDLE));
                        }
                        else
                        {
                            shouldSwitchToIdle &= (uint8)(TRUE);
                        }
                    }
                }        
        }

        if ( (shouldSwitchToIdle != FALSE) && (!(isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) || isDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER)) ) )
        {
            setDriverState(CRYPTO_STATE_IDLE);
        }

        break;
    }
    
    /* TODO: Remove the CRYPTO_STATE_ERROR state */
    case CRYPTO_STATE_ERROR:
        /* Do nothing. */
        break;
    default:
        setDriverState(CRYPTO_STATE_ERROR);
        break;
    }
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_GetDriverStatus(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    VAR(Std_ReturnType, AUTOMATIC) ret;

    if (cryptoDrvContext.driverState == CRYPTO_STATE_ACTIVE)
    {
        ret = CRYPTO_E_BUSY;
    }
    else if (cryptoDrvContext.driverState == CRYPTO_STATE_IDLE)
    {
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }

    return ret;
}

FUNC(boolean, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_IsDriverInitialized(void)/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    return cryptoDrvContext.isInitialized;
}

FUNC(boolean, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_IsHsmInitialized(void) /* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    return (boolean)(cryptoDrvContext.hsmInitState == HSM_INIT_STATE_INITIALIZED);
}

/* TODO: Rename function to GetKeyElementIndexFromStorageType or similar */
/* TODO: Move the implementation to an internal file. This should not be in the public implementation */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_GetKeyElementIndex(uint32 arCryptoKeyId, uint32* keyElementIndexPtr, Crypto_82_Hsm_KeyElementStorageType keyStorageType)/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    uint32 index = 0;
    uint32 startIndex = Crypto_82_Hsm_keyIdToKeyElementIdMap[arCryptoKeyId];

    if ( keyStorageType != CRYPTO_82_HSM_KEY_ELEMENT_STORAGE_TYPE_RESERVED)
    {
        for (index = startIndex; index < startIndex + Crypto_82_Hsm_configKeys[arCryptoKeyId].numberOfKeyElements; index++) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
        {
            if (Crypto_82_Hsm_configKeyElements[index].keyStorageType == keyStorageType)
            {
                *keyElementIndexPtr = index;
            }
        }
    }
    /* Search for both RAM or PERSISTENT key elements */
    else
    {
        for (index = startIndex; index < startIndex + Crypto_82_Hsm_configKeys[arCryptoKeyId].numberOfKeyElements; index++) /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
        {
            if ( (Crypto_82_Hsm_configKeyElements[index].keyStorageType == CRYPTO_82_HSM_PERSISTENT_KEY_ELEMENT) ||
                 (Crypto_82_Hsm_configKeyElements[index].keyStorageType == CRYPTO_82_HSM_RAM_KEY_ELEMENT) )
            {
                *keyElementIndexPtr = index;
            }
        }
    }
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
