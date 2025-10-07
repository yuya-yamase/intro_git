/**
 * \file Crypto_82_Hsm_DnExt_BulkMac.c
 * \author      PiNTeam
 * \copyright   (c) DENSO KK, 2022
 * 
 * \brief Implementation of Denso Bulk Mac Extension
 * \details
*/

/**********************************************************************************************************************\
 * INCLUDES
\**********************************************************************************************************************/

#include "Crypto_82_Hsm_Internal.h"
#include "Crypto_82_Hsm_DnExt_BulkMac.h"
#include "Crypto_82_Hsm_KeyManagement.h"
#include "Crypto_82_Hsm_UserCallout.h"
#include "Crypto_82_Hsm_Dispatch.h"
#include "Crypto_82_Hsm_Services.h"
#include "ecy_hsm_csai_mac.h"
#include "SchM_Crypto_82_Hsm.h"
#if ( CRYPTO_82_HSM_CALLBACK_NOTIF_AUTOSAR_VERSION_SELECT == STD_ON )
#include "CryIf_Cbk.h"
#else
#include "CryIf.h"
#endif /* ( CRYPTO_82_HSM_CALLBACK_NOTIF_AUTOSAR_VERSION_SELECT == STD_ON ) */

/**********************************************************************************************************************\
 * PRIVATE MACROS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE TYPE DEFINITIONS
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS DECLARATIONS
\**********************************************************************************************************************/
#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

 /**
 * \brief Returns true if job is found in queue.
 *
 *
 * \param [in]      job             CryptoJob to find in queue
 * \param [in]      objectId        Holds the identifier of the Crypto Driver Object
 *
 */
static FUNC(boolean, CRYPTO_82_HSM_CODE) isJobInQueue(    
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId);


 /**
 * \brief Removes bulkMac jobs from queue.
 *
 * Removes the bulk mac jobs from queue which have been finished.
 *
 * \param [in]      objectId        Holds the identifier of the Crypto Driver Object
 * \param [in]      numberOfJobs    Number of jobs to remove
 *
 */
static FUNC(void, CRYPTO_82_HSM_CODE) removeBulkJobsFromQueue(
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId,
    VAR(uint32, AUTOMATIC) numberOfJobs
);

 /**
 * \brief Fills the BULK LIST with the data of the bulk mac jobs in the queue and returns the number of jobs which have been requested.
 *
 *
 * \param [in]      queue           Queue of the driver object
 * \param [in]      maxRequests     Max number of requests for bulk mac operation for the driver object
 * \param [in]      objectId        Holds the identifier of the Crypto Driver Object
 * 
 * \retval          Number of jobs requested.
 *
 */
static FUNC(uint32, CRYPTO_82_HSM_CODE) fillBulkList(P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, VAR(uint32, AUTOMATIC) maxRequests, VAR(uint32, AUTOMATIC) objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

 /**
 * \brief Processes the result of dispatching the bulk mac operation.
 *
 *
 * \param [in]      queue           Queue of the driver object
 * \param [in]      ret             Value returned by the bulk mac wrapper dispatch function
 * \param [in]      objectId        Holds the identifier of the Crypto Driver Object
 *
 */
static FUNC(void, CRYPTO_82_HSM_CODE) processBulkMacDispatchResult(P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, VAR(Std_ReturnType, AUTOMATIC) ret, VAR(uint32, AUTOMATIC) objectId, VAR(uint32, AUTOMATIC) numberOfJobs);/* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */

/**
 * \brief Adds a new job to the queue without sorting the queue based on job priority.
 *
 * \param [in] job             Pointer to the configuration of the job. Contains structures with job and primitive relevant
 *                             information.
 * \param [in] objectId        Crypto Driver Object Id.
 *
 */
static FUNC(void, CRYPTO_82_HSM_CODE) addJobToQueueWithoutSorting(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
);

#endif

/**********************************************************************************************************************\
 * PRIVATE FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

static FUNC(boolean, CRYPTO_82_HSM_CODE) isJobInQueue(    
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId)
{
    boolean ret = FALSE;
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */      

    for (uint32 i = 0u; i < queueSize; i++)
    {
        if ((*(queue + i)) != NULL_PTR) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            if ((*(queue + i))->jobInfo->jobId == job->jobInfo->jobId) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            {
                ret = TRUE;
            }
        }
    }

    return ret;
}

static FUNC(void, CRYPTO_82_HSM_CODE) removeBulkJobsFromQueue(
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId,
    VAR(uint32, AUTOMATIC) numberOfJobs
)
{
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);
    VAR(uint32, AUTOMATIC) remainingJobs = queueSize - numberOfJobs; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

    /* Set finished jobs in queue to NULL_PTR */
    for (uint32 i = 0; i < numberOfJobs; i++) 
    {
        *(queue + i) = NULL_PTR; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
    }

    /* Move remaining jobs to first positions and set the rest of the queue to NULL_PTR */
    for (uint32 j = 0; j < remainingJobs; j++) 
    {
        *(queue + j) = *(queue + j + numberOfJobs); /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to less than or equal to the array size and will not access out of bounds memory. */
        *(queue + j + numberOfJobs) = NULL_PTR; /* PRQA S 0488  #This rule violation is surpressed because the value of "j" is constrained to less than or equal to the array size and will not access out of bounds memory. */
    }
}

static FUNC(uint32, CRYPTO_82_HSM_CODE) fillBulkList(P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, VAR(uint32, AUTOMATIC) maxRequests, VAR(uint32, AUTOMATIC) objectId) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    VAR(uint32, AUTOMATIC) cryptoKeyId;
    VAR(uint32, AUTOMATIC) keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
    VAR(uint32, AUTOMATIC) numberOfJobs = 0;
    
    for (uint32 i = 0; i < maxRequests; i++)
    {
        if ((*(queue + i)) != NULL_PTR)/* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            keyElementIndex = CRYPTO_82_HSM_INVALID_KEY_INDEX;
            cryptoKeyId = (*(queue + i))->cryptoKeyId; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            (void)Crypto_82_Hsm_findKeyElement(cryptoKeyId, CRYPTO_KE_MAC_KEY, &keyElementIndex);
            
            if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER)
            {
                bulkMacVerifyContext.BULK_LIST_MACVER[i].keyHandle = ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE;

                if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    bulkMacVerifyContext.BULK_LIST_MACVER[i].keyHandle = Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle;
                }

                bulkMacVerifyContext.BULK_LIST_MACVER[i].message = (*(queue + i))->jobPrimitiveInputOutput.inputPtr; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacVerifyContext.BULK_LIST_MACVER[i].messageLength = (*(queue + i))->jobPrimitiveInputOutput.inputLength; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacVerifyContext.BULK_LIST_MACVER[i].mac = (*(queue + i))->jobPrimitiveInputOutput.secondaryInputPtr; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacVerifyContext.BULK_LIST_MACVER[i].macLength = (*(queue + i))->jobPrimitiveInputOutput.secondaryInputLength; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacVerifyContext.BULK_LIST_MACVER[i].isActive = TRUE;
                bulkMacVerifyContext.BULK_LIST_MACVER[i].isValid = FALSE;
                bulkMacVerifyContext.BULK_LIST_ALGORITHMS[i] = get_serviceLayerMacAlgo((*(queue + i))->jobPrimitiveInfo->primitiveInfo->algorithm.family, (*(queue + i))->jobPrimitiveInfo->primitiveInfo->algorithm.mode); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            }
            else
            {
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].keyHandle = ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE;

                if (keyElementIndex != CRYPTO_82_HSM_INVALID_KEY_INDEX)
                {
                    bulkMacGenerateContext.BULK_LIST_MACGEN[i].keyHandle = Crypto_82_Hsm_runtimeKeys[keyElementIndex].keyHandle;
                }                
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].message = (*(queue + i))->jobPrimitiveInputOutput.inputPtr; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].messageLength = (*(queue + i))->jobPrimitiveInputOutput.inputLength; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].mac = (*(queue + i))->jobPrimitiveInputOutput.outputPtr; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].macLength = (*((*(queue + i))->jobPrimitiveInputOutput.outputLengthPtr)) * CRYPTO_82_HSM_NUM_BITS_IN_BYTE; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].isActive = TRUE;
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].isValid = FALSE;
                bulkMacGenerateContext.BULK_LIST_ALGORITHMS[i] = get_serviceLayerMacAlgo((*(queue + i))->jobPrimitiveInfo->primitiveInfo->algorithm.family, (*(queue + i))->jobPrimitiveInfo->primitiveInfo->algorithm.mode); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            }

            numberOfJobs = i + 1u; /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
        }
    }

    return numberOfJobs;
}

static FUNC(void, CRYPTO_82_HSM_CODE) processBulkMacDispatchResult(P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue, VAR(Std_ReturnType, AUTOMATIC) ret, VAR(uint32, AUTOMATIC) objectId, VAR(uint32, AUTOMATIC) numberOfJobs) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    if (ret == E_OK) /* Satisfies DN_BM_SWS_Crypto_020 */
    {
        if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) 
        {
            bulkMacVerifyContext.bulkJobState = TRUE;
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER, TRUE);
        }
        else
        {
            bulkMacGenerateContext.bulkJobState = TRUE;
            setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN, TRUE);
        }

        for (uint32 i = 0; i < numberOfJobs; i++)
        {
            (*(queue + i))->jobState = CRYPTO_JOBSTATE_ACTIVE; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        }
    }
    else /* Remove csm mac jobs from queue and clean bulk mac list if dispatching has failed. Satisfies DN_BM_SWS_Crypto_019 */
    {
        for (uint32 i = 0; i < numberOfJobs; i++)
        {
            (*(queue + i))->jobState = CRYPTO_JOBSTATE_IDLE; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            CryIf_CallbackNotification((*(queue + i)), E_NOT_OK); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        }

        removeBulkJobsFromQueue(queue, objectId, numberOfJobs);

        SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

        if( (*(queue)) == NULL_PTR) /* Queue is empty. */
        {   
            setDriverObjectBusy(objectId, FALSE);
        }

        SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

        Crypto_82_Hsm_Ext_cleanBulkMacList(objectId);
    }
}

static FUNC(void, CRYPTO_82_HSM_CODE) addJobToQueueWithoutSorting(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
)
{
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);
    
    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

    for (uint32 i = 0uL; i < queueSize; i++)
    {
        /* Find the first empty slot in the queue */
        if( *(queue + i) == NULL_PTR ) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            *(queue + i) = job; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            break;
        }
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

}

static FUNC(void, CRYPTO_82_HSM_CODE) replaceJobInQueue(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    VAR(uint32, AUTOMATIC) objectId
)
{
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
    VAR(uint32, AUTOMATIC) queueSize = getQueueSize(objectId);

    SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
    
    for (uint32 i = 0u; i < queueSize; i++)
    {
        if ((*(queue + i))->jobInfo->jobId == job->jobInfo->jobId) /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
        {
            *(queue + i) = job; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            break;
        }
    }

    SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
}

#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/**********************************************************************************************************************\
 * PUBLIC VARIABLES
\**********************************************************************************************************************/

/**********************************************************************************************************************\
 * PUBLIC FUNCTIONS IMPLEMENTATIONS
\**********************************************************************************************************************/

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

#if (CRYPTO_82_HSM_DENSO_BULK_MAC == STD_ON)

FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_cleanBulkMacList(VAR(uint32, AUTOMATIC) objectId)
{

    if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER)
    {
        bulkMacVerifyContext.numberOfJobsMacVer = 0u;
        bulkMacVerifyContext.bulkJobState = FALSE;
        
        for (uint32 i = 0u; i < CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_VER; i++)
        {   
            bulkMacVerifyContext.BULK_LIST_MACVER[i].keyHandle = ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].message = NULL_PTR;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].messageLength = 0u;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].mac = NULL_PTR;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].macLength = 0u;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].isActive = FALSE;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].isValid = FALSE;
            bulkMacVerifyContext.BULK_LIST_MACVER[i].algorithm = ecy_hsm_CSAI_MAC_RESERVED;
        }
    }
    else
    {
        bulkMacGenerateContext.numberOfJobsMacGen = 0u;
        bulkMacGenerateContext.bulkJobState = FALSE;

        for (uint32 i = 0u; i < CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_GEN; i++)
        {            
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].keyHandle = ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE;  
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].message = NULL_PTR;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].messageLength = 0u;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].mac = NULL_PTR;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].macLength = 0u;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].isActive = FALSE;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].isValid = FALSE;
            bulkMacGenerateContext.BULK_LIST_MACGEN[i].algorithm = ecy_hsm_CSAI_MAC_RESERVED;
        }
    }
}

FUNC(Std_ReturnType, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_BulkMac_ProcessJob(
                                                VAR(uint32, AUTOMATIC) objectId, 
                                                P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_82_HSM_VAR) job,  /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
                                                CONST(Crypto_ProcessingType, AUTOMATIC) processingType,
                                                P2VAR(uint8, AUTOMATIC, AUTOMATIC) detErr) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (processingType == CRYPTO_PROCESSING_SYNC) /* Satisfies DN_BM_SWS_Crypto_005 */
    {      
        ret = E_NOT_OK;
    }
    else if (Crypto_82_Hsm_KeyState[job->cryptoKeyId].keyValid == FALSE) /* Satisfies DN_BM_SWS_Crypto_006 */
    {      
        ret = E_NOT_OK;
    }
    else if ( isJobState(job, CRYPTO_JOBSTATE_ACTIVE) ) /* Satisfies DN_BM_SWS_Crypto_009 */
    {
        ret = CRYPTO_E_BUSY;
    }
    else if (job->jobPrimitiveInputOutput.mode != CRYPTO_OPERATIONMODE_SINGLECALL) /* Satisfies DN_BM_SWS_Crypto_004 */
    {
        ret = E_NOT_OK;
    }
    else if ( !( (job->jobPrimitiveInfo->primitiveInfo->service == CRYPTO_MACGENERATE) && (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) ) && !( (job->jobPrimitiveInfo->primitiveInfo->service == CRYPTO_MACVERIFY) && (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) ) ) /* Satisfies DN_BM_SWS_Crypto_007, Satisfies DN_BM_SWS_Crypto_008 */
    {
        ret = E_NOT_OK;
    }
    else
    {
#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)

        Crypto_82_Hsm_Service_MACAlgorithmType Crypto_algo = get_serviceLayerMacAlgo(job->jobPrimitiveInfo->primitiveInfo->algorithm.family, job->jobPrimitiveInfo->primitiveInfo->algorithm.mode);

        if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER)
        {
           *detErr = Crypto_82_Hsm_MacVerify_DET_Checking(
                    job->jobPrimitiveInputOutput.inputPtr, 
                    job->jobPrimitiveInputOutput.secondaryInputPtr,
                    job->jobPrimitiveInputOutput.inputLength,
                    job->jobPrimitiveInputOutput.secondaryInputLength,
                    job->jobPrimitiveInputOutput.mode,
                    Crypto_algo,
                    (uint8*)job->jobPrimitiveInputOutput.verifyPtr  );
        }
        else
        {
            *detErr = Crypto_82_Hsm_MacGenerate_DET_Checking(job->jobPrimitiveInputOutput.inputPtr, 
                    job->jobPrimitiveInputOutput.outputPtr,
                    job->jobPrimitiveInputOutput.inputLength,
                    job->jobPrimitiveInputOutput.outputLengthPtr,
                    job->jobPrimitiveInputOutput.mode,
                    Crypto_algo);
        }
        if (*detErr == CRYPTO_DET_NO_ERROR) 
        {
#endif
            /* Satisfies DN_BM_SWS_Crypto_012, Satisfies DN_BM_SWS_Crypto_013 */

            ret = E_OK;

            if(isJobInQueue(job, objectId) == TRUE)
            {
                /* Replace job with updated job. Satisfies DN_BM_SWS_Crypto_010 */ 
                (void)replaceJobInQueue(job, objectId);

            }
            else if(isQueueFull(objectId) == FALSE)
            {
                addJobToQueueWithoutSorting(job, objectId); /* Satisfies DN_BM_SWS_Crypto_014 */
            }
            else /* Satisfies DN_BM_SWS_Crypto_011 */
            {
                ret = CRYPTO_E_BUSY;
            }
#if (CRYPTO_82_HSM_DEV_ERROR_REPORT == STD_ON)            
        }
#endif        
    }
    return ret;
}

FUNC(void, CRYPTO_82_HSM_CODE)Crypto_82_Hsm_Ext_BulkMac_processJobAsync(VAR(uint32, AUTOMATIC) objectId)
{
    P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(objectId); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    VAR(Std_ReturnType, AUTOMATIC) pollingResult = E_NOT_OK;

    if (objectId == CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER)
    {
        for(uint32 i = 0; i < bulkMacVerifyContext.numberOfJobsMacVer; i++)
        {
            /* If job is finished. */
            if (bulkMacVerifyContext.BULK_LIST_MACVER[i].isValid == TRUE)
            {
                bulkMacVerifyContext.BULK_LIST_MACVER[i].isValid = FALSE;
                (*(queue + i))->jobState = CRYPTO_JOBSTATE_IDLE; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */

                if(bulkMacVerifyContext.BULK_LIST_MACVER[i].errorCode == ecy_hsm_CSAI_SUCCESS) /* Satisfies DN_BM_SWS_Crypto_021 */
                {
                    ret = E_OK;

                    if (bulkMacVerifyContext.BULK_LIST_MACVER[i].resultFlag == TRUE)
                    {
                        *((*(queue + i))->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                    }
                    else
                    {
                        *((*(queue + i))->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                    }
                }
                else /* Satisfies DN_BM_SWS_Crypto_022, DN_BM_SWS_Crypto_024 */
                {
                    ret = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, (*(queue + i))->jobInfo->jobId, bulkMacVerifyContext.BULK_LIST_MACVER[i].errorCode); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */                 
                }

                CryIf_CallbackNotification((*(queue + i)), ret); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            }
        }

        pollingResult = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, objectId);


        /* Polling of the bulk job has finished, remove finished csm mac jobs from the queue and clean the bulkList */
        if (pollingResult != CRYPTO_E_BUSY) /* Satisfies DN_BM_SWS_Crypto_023 */
        {
            removeBulkJobsFromQueue(queue, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER, bulkMacVerifyContext.numberOfJobsMacVer);
            Crypto_82_Hsm_Ext_cleanBulkMacList(objectId);

            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

            
            if(isQueueEmpty(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) == TRUE) /* Queue is empty. */
            {   
                setDriverObjectBusy(objectId, FALSE);
            }

            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
        }
    }
    else
    {
        for(uint32 i = 0; i < bulkMacGenerateContext.numberOfJobsMacGen; i++)
        {
            /* If job is finished. */
            if (bulkMacGenerateContext.BULK_LIST_MACGEN[i].isValid == TRUE)
            {
                bulkMacGenerateContext.BULK_LIST_MACGEN[i].isValid = FALSE;
                (*(queue + i))->jobState = CRYPTO_JOBSTATE_IDLE; /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */

                if(bulkMacGenerateContext.BULK_LIST_MACGEN[i].errorCode == ecy_hsm_CSAI_SUCCESS)
                {
                    ret = E_OK;
                }
                else /* Satisfies DN_BM_SWS_Crypto_022, DN_BM_SWS_Crypto_024*/
                {
                    ret = E_NOT_OK;
                    Crypto_82_Hsm_Error_Callback(CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, (*(queue + i))->jobInfo->jobId, bulkMacGenerateContext.BULK_LIST_MACGEN[i].errorCode); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
                }

                CryIf_CallbackNotification((*(queue + i)), ret); /* PRQA S 0488  #This rule violation is surpressed because the value of "i" is constrained to the array size and will not access out of bounds memory. */
            }
        }

        pollingResult = Crypto_82_Hsm_PollJob(Crypto_82_Hsm_driverObjects[objectId].jobHandle, CRYPTO_82_HSM_SERVICE_ID_PROCESS_JOB, CRYPTO_82_HSM_CALLBACK_NO_JOBID_AVAILABLE, objectId);

        /* Polling of the bulk job has finished, remove finished csm mac jobs from the queue and clean the bulkList */
        if (pollingResult != CRYPTO_E_BUSY) /* Satisfies DN_BM_SWS_Crypto_023 */
        {
            removeBulkJobsFromQueue(queue, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN, bulkMacGenerateContext.numberOfJobsMacGen);
            Crypto_82_Hsm_Ext_cleanBulkMacList(objectId);

            SchM_Enter_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();

            if(isQueueEmpty(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) == TRUE) /* Queue is empty. */
            {   
                setDriverObjectBusy(objectId, FALSE);
            }

            SchM_Exit_Crypto_82_Hsm_CRYPTO_82_HSM_EXCLUSIVEAREA_QUEUE();
        }
    }

}

/* Satisfies DN_BM_SWS_Crypto_015 */
FUNC(void, CRYPTO_82_HSM_CODE) Crypto_82_Hsm_Ext_BulkMac_Main(void)/* PRQA S 1503  #This rule violation is suppressed because API is not supposed to be used in the project */
{
    VAR(Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;

    if(isQueueEmpty(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER) == FALSE)
    {
        /* Attempt to trigger bulk mac verification jobs first as they are higher priority. Satisfies DN_BM_SWS_Crypto_016 */
        if (bulkMacVerifyContext.bulkJobState == FALSE)
        {
            P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case if a correct configuration is provided. */

            bulkMacVerifyContext.numberOfJobsMacVer = fillBulkList(queue, CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_VER, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER); /* Satisfies DN_BM_SWS_Crypto_018 */
            
            ret = Crypto_82_Hsm_Bulk_Mac_Verify_Fast(bulkMacVerifyContext.numberOfJobsMacVer); /* Satisfies DN_BM_SWS_Crypto_017 */
            processBulkMacDispatchResult(queue, ret, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER, bulkMacVerifyContext.numberOfJobsMacVer);
        } 
    }
    else /* Queue Empty */
    {
        setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACVER, FALSE);
    }    
 
    if(isQueueEmpty(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN) == FALSE)
    {
        if (bulkMacGenerateContext.bulkJobState == FALSE)
        {
            P2VAR(Crypto_JobType*, AUTOMATIC, CRYPTO_82_HSM_VAR) queue = getQueue(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN); /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */ /* PRQA S 3383  #Wraparound can not occur in this case */

            bulkMacGenerateContext.numberOfJobsMacGen = fillBulkList(queue, CRYPTO_82_HSM_MAX_NUM_REQUESTS_BULK_MAC_GEN, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN); /* Satisfies DN_BM_SWS_Crypto_018 */

            ret = Crypto_82_Hsm_Bulk_Mac_Generate_Fast(bulkMacGenerateContext.numberOfJobsMacGen); /* Satisfies DN_BM_SWS_Crypto_017 */
            processBulkMacDispatchResult(queue, ret, CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN, bulkMacGenerateContext.numberOfJobsMacGen);
        }
    }
    else /* Queue Empty */
    {
        setDriverObjectBusy(CRYPTO_82_HSM_DRIVEROBJECT_BULKMACGEN, FALSE);
    }
}

#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
