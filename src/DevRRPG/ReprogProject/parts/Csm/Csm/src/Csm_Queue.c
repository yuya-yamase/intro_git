/* Csm_Queue_c_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/Queue/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_Csm.h>
#include <Csm.h>
#include <CryIf.h>
#include "../inc/Csm_General.h"
#include "../inc/Csm_Queue.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CSM_DEQUEUE_STOP_TEMPORARY  ((uint32)1UL)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_SyncProcessJob
(
    uint16 u2JobIndex
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_AsyncProcessJob
(
    uint16 u2JobIndex
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_Enqueue
(
    uint16 u2JobIndex
);

static FUNC(void, CSM_CODE) Csm_Queue_ChannelCountProc
(
    void
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncChannel
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncPriority
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig,
    uint16 u2PriorityIndex
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncQueue
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig,
    uint16 u2PriorityIndex,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptQueueEmptyFlag
);

static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_Dequeue
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptPriorityConfig,
    uint16 u2HeadIndex,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptQueueEmptyFlag
);

#if (CSM_RAM_ERROR_CHECK == STD_ON)
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_DequeueRamCheck
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptPriorityConfig
);
#endif

static FUNC(void, CSM_CODE) Csm_Queue_DetectTimeOut
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* Function Name | Csm_Queue_ProcessJob                                     */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | u2JobIndex :                                             */
/*               | ptInOut    :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : request successful                          */
/*               | E_NOT_OK   : request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : the key is not valid            */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : a key element has the       */
/*               |                              wrong size                  */
/*               | CRYPTO_E_KEY_READ_FAIL :  key element extraction is      */
/*               |                           not allowed                    */
/*               | CRYPTO_E_KEY_WRITE_FAIL : the writing access failed      */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : the key is not available    */
/*               | CRYPTO_E_JOB_CANCELED : the synchronous Job has been     */
/*               |                         canceled                         */
/*               | CRYPTO_E_KEY_EMPTY : uninitialized source key element    */
/*               | CRYPTO_E_ENTROPY_EXHAUSTED :  Entropy is depleted        */
/* Notes         | SWS_Csm_01041                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_ProcessJob
(
    uint16 u2JobIndex,
    P2CONST(Crypto_JobPrimitiveInputOutputType, AUTOMATIC, AUTOMATIC) ptInOut
)
{
    P2CONST(Csm_Cfg_JobConfigType, AUTOMATIC, CSM_CONFIG_DATA)          pt_config;
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_subConfig;
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_SHARED_VAR_NO_INIT)   pt_jobData;
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)       pt_jobSubData;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT) pt_channelData;
    Std_ReturnType   ud_ret;
    Csm_JobStateType ud_csmJobState;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16           u2_highestPriority;
    uint16           u2_highestPriorityRed;
#endif
    uint16           u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16           u2_jobProcessingNumRedTmp;
#endif
    
    pt_config = &Csm_Cfg_stJob.ptConfig[u2JobIndex];
    pt_subConfig = &Csm_Cfg_stJob.ptSubConfig[u2JobIndex];
    pt_jobData = &Csm_Cfg_stJob.ptData[u2JobIndex];
    pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u2JobIndex];
    pt_channelData = pt_subConfig->ptJobQueue->ptChannelData;
    
    SchM_Enter_Csm_General();
    
    ud_csmJobState = pt_jobSubData->udCsmJobState;
    
    if( ud_csmJobState == CSM_S_JOB_IDLE )
    {
        if( pt_config->stJobPrimitiveInfo.processingType == CRYPTO_PROCESSING_ASYNC )
        {
            u2_jobProcessingNumTmp = pt_channelData->u2JobProcessingNum;
            u2_jobProcessingNumTmp++;
            pt_channelData->u2JobProcessingNum = u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            u2_jobProcessingNumRedTmp = pt_channelData->u2JobProcessingNumRed;
            u2_jobProcessingNumRedTmp--;
            pt_channelData->u2JobProcessingNumRed = u2_jobProcessingNumRedTmp;
#endif
        }
        
        pt_jobSubData->udCsmJobState = CSM_S_JOB_ACCEPT;
        
        pt_jobData->stJob.jobId = (uint32)u2JobIndex;
        
        pt_jobData->stJob.jobPrimitiveInputOutput.inputPtr                  = ptInOut->inputPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.inputLength               = ptInOut->inputLength;
        pt_jobData->stJob.jobPrimitiveInputOutput.secondaryInputPtr         = ptInOut->secondaryInputPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.secondaryInputLength      = ptInOut->secondaryInputLength;
        pt_jobData->stJob.jobPrimitiveInputOutput.tertiaryInputPtr          = ptInOut->tertiaryInputPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.tertiaryInputLength       = ptInOut->tertiaryInputLength;
        pt_jobData->stJob.jobPrimitiveInputOutput.outputPtr                 = ptInOut->outputPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.outputLengthPtr           = ptInOut->outputLengthPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.secondaryOutputPtr        = ptInOut->secondaryOutputPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.secondaryOutputLengthPtr  = ptInOut->secondaryOutputLengthPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.verifyPtr                 = ptInOut->verifyPtr;
        pt_jobData->stJob.jobPrimitiveInputOutput.mode                      = ptInOut->mode;
        pt_jobData->stJob.jobPrimitiveInputOutput.cryIfKeyId                = ptInOut->cryIfKeyId;
        pt_jobData->stJob.jobPrimitiveInputOutput.targetCryIfKeyId          = ptInOut->targetCryIfKeyId;
        
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        pt_jobSubData->stJobInOutRed.u4InputPtr                             = ~(uint32)ptInOut->inputPtr;                   /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4SecondaryInputPtr                    = ~(uint32)ptInOut->secondaryInputPtr;          /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4TertiaryInputPtr                     = ~(uint32)ptInOut->tertiaryInputPtr;           /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4OutputPtr                            = ~(uint32)ptInOut->outputPtr;                  /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4OutputLengthPtr                      = ~(uint32)ptInOut->outputLengthPtr;            /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4SecondaryOutputPtr                   = ~(uint32)ptInOut->secondaryOutputPtr;         /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4SecondaryOutputLengthPtr             = ~(uint32)ptInOut->secondaryOutputLengthPtr;   /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4VerifyPtr                            = ~(uint32)ptInOut->verifyPtr;                  /* MISRA DEVIATION: */
        pt_jobSubData->stJobInOutRed.u4CryIfKeyId                           = ~(uint32)ptInOut->cryIfKeyId;
        pt_jobSubData->stJobInOutRed.u4TargetCryIfKeyId                     = ~(uint32)ptInOut->targetCryIfKeyId;
#endif
        
        pt_jobData->stJob.jobPrimitiveInfo                                  = &pt_config->stJobPrimitiveInfo;
        pt_jobData->stJob.jobInfo                                           = &pt_config->stJobInfo;
        
        if( pt_subConfig->ptJobRedirectionInfo != NULL_PTR )
        {
            pt_jobData->stJobRedirectionInfo.redirectionConfig              = pt_subConfig->ptJobRedirectionInfo->redirectionConfig;
            pt_jobData->stJobRedirectionInfo.inputKeyId                     = pt_subConfig->ptJobRedirectionInfo->inputKeyId;
            pt_jobData->stJobRedirectionInfo.inputKeyElementId              = pt_subConfig->ptJobRedirectionInfo->inputKeyElementId;
            pt_jobData->stJobRedirectionInfo.secondaryInputKeyId            = pt_subConfig->ptJobRedirectionInfo->secondaryInputKeyId;
            pt_jobData->stJobRedirectionInfo.secondaryInputKeyElementId     = pt_subConfig->ptJobRedirectionInfo->secondaryInputKeyElementId;
            pt_jobData->stJobRedirectionInfo.tertiaryInputKeyId             = pt_subConfig->ptJobRedirectionInfo->tertiaryInputKeyId;
            pt_jobData->stJobRedirectionInfo.tertiaryInputKeyElementId      = pt_subConfig->ptJobRedirectionInfo->tertiaryInputKeyElementId;
            pt_jobData->stJobRedirectionInfo.outputKeyId                    = pt_subConfig->ptJobRedirectionInfo->outputKeyId;
            pt_jobData->stJobRedirectionInfo.outputKeyElementId             = pt_subConfig->ptJobRedirectionInfo->outputKeyElementId;
            pt_jobData->stJobRedirectionInfo.secondaryOutputKeyId           = pt_subConfig->ptJobRedirectionInfo->secondaryOutputKeyId;
            pt_jobData->stJobRedirectionInfo.secondaryOutputKeyElementId    = pt_subConfig->ptJobRedirectionInfo->secondaryOutputKeyElementId;
            
            pt_jobData->stJob.jobRedirectionInfoRef = &pt_jobData->stJobRedirectionInfo;
        }
        else
        {
            pt_jobData->stJob.jobRedirectionInfoRef = NULL_PTR;
        }
        
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        u2_highestPriority      = pt_channelData->u2HighestPriority;
        u2_highestPriorityRed   = (uint16)~pt_channelData->u2HighestPriorityRed;
        
        if( u2_highestPriority == u2_highestPriorityRed )
        {
#endif
            if( pt_config->stJobPrimitiveInfo.processingType == CRYPTO_PROCESSING_SYNC )
            {
                ud_ret = Csm_Queue_SyncProcessJob( u2JobIndex );
            }
            else
            {
                ud_ret = Csm_Queue_AsyncProcessJob( u2JobIndex );
            }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        }
        else
        {
            Csm_General_udStatus = CSM_S_RAMERROR;
            ud_ret = (Std_ReturnType)E_NOT_OK;
        }
#endif
        if( (ud_ret != (Std_ReturnType)E_OK)
         || (pt_config->stJobPrimitiveInfo.processingType == CRYPTO_PROCESSING_SYNC) )
        {
            if( pt_config->stJobPrimitiveInfo.processingType == CRYPTO_PROCESSING_ASYNC )
            {
                u2_jobProcessingNumTmp = pt_channelData->u2JobProcessingNum;
                u2_jobProcessingNumTmp--;
                pt_channelData->u2JobProcessingNum = u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                u2_jobProcessingNumRedTmp = pt_channelData->u2JobProcessingNumRed;
                u2_jobProcessingNumRedTmp++;
                pt_channelData->u2JobProcessingNumRed = u2_jobProcessingNumRedTmp;
#endif
                pt_channelData->u2TimeOutCount = 0U;
            }
            
            pt_jobSubData->udCsmJobState = CSM_S_JOB_IDLE;
        }
    }
    else
    {
        ud_ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    
    SchM_Exit_Csm_General();
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_MainFunction                                   */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | SWS_Csm_01041, SWS_Csm_00037                             */
/****************************************************************************/
FUNC(void, CSM_CODE) Csm_Queue_MainFunction
(
    void
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigAccessType, AUTOMATIC, CSM_CONFIG_DATA) pt_queueConfigAccess = &Csm_Cfg_stQueue;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfigTop = pt_queueConfigAccess->ptConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfig;
    Std_ReturnType  ud_ret;
    uint16          u2_configIndex;
    uint8           u1_dequeueFlag;
    
    Csm_Queue_ChannelCountProc();
    
    for( u2_configIndex = 0U; u2_configIndex < (uint16)pt_queueConfigAccess->u4ConfigNum; u2_configIndex++ )
    {
        pt_queueConfig = &pt_queueConfigTop[u2_configIndex];
        u1_dequeueFlag = pt_queueConfig->ptChannelData->u1DequeueFlag;
        
        if( u1_dequeueFlag == CSM_FLG_TRUE )
        {
            ud_ret = Csm_Queue_MainFuncChannel( pt_queueConfig );
            
            if( (ud_ret != (Std_ReturnType)E_OK)
             && (ud_ret != (Std_ReturnType)CRYPTO_E_BUSY) )
            {
                break;
            }
        }
        
        Csm_Queue_DetectTimeOut( pt_queueConfig );
    }
    
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Csm_Queue_SyncProcessJob                                 */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | u2JobIndex :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : request successful                          */
/*               | E_NOT_OK   : request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : the key is not valid            */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : a key element has the       */
/*               |                              wrong size                  */
/*               | CRYPTO_E_KEY_READ_FAIL :  key element extraction is      */
/*               |                           not allowed                    */
/*               | CRYPTO_E_KEY_WRITE_FAIL : the writing access failed      */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : the key is not available    */
/*               | CRYPTO_E_JOB_CANCELED : the synchronous Job has been     */
/*               |                         canceled                         */
/*               | CRYPTO_E_KEY_EMPTY : uninitialized source key element    */
/*               | CRYPTO_E_ENTROPY_EXHAUSTED :  Entropy is depleted        */
/* Notes         | SWS_Csm_01041                                            */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_SyncProcessJob
(
    uint16 u2JobIndex
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_JobConfigType, AUTOMATIC, CSM_CONFIG_DATA)         pt_jobConfig = &Csm_Cfg_stJob.ptConfig[u2JobIndex];
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)                   pt_jobSubConfig = &Csm_Cfg_stJob.ptSubConfig[u2JobIndex];
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfig = pt_jobSubConfig->ptJobQueue;
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_SHARED_VAR_NO_INIT)               pt_jobData = &Csm_Cfg_stJob.ptData[u2JobIndex];
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)           pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u2JobIndex];
    Std_ReturnType  ud_ret;
    uint32          u4_highestPriority;
    uint32          u4_jobChannelId = pt_queueConfig->u4CryIfChannelId;
    
    if( pt_jobData->stJob.jobState == CRYPTO_JOBSTATE_ACTIVE )
    {
        pt_jobSubData->udCsmJobState = CSM_S_JOB_BUSY;
        
        SchM_Exit_Csm_General();
        
        ud_ret = CryIf_ProcessJob( u4_jobChannelId, &(pt_jobData->stJob) );
        
        SchM_Enter_Csm_General();
    }
    else
    {
        u4_highestPriority = (uint32)pt_queueConfig->ptChannelData->u2HighestPriority;
        
        if( pt_jobConfig->stJobInfo.jobPriority > u4_highestPriority )
        {
            pt_jobSubData->udCsmJobState = CSM_S_JOB_BUSY;
            pt_queueConfig->ptChannelData->u4DequeueStopCount = pt_queueConfig->u4DequeueStop;
            
            SchM_Exit_Csm_General();
            
            ud_ret = CryIf_ProcessJob( u4_jobChannelId, &(pt_jobData->stJob) );
            
            SchM_Enter_Csm_General();
            
            if( (ud_ret != (Std_ReturnType)CRYPTO_E_BUSY)
             && (pt_queueConfig->u4DequeueStop > CSM_DEQUEUE_STOP_TEMPORARY) )
            {
                pt_queueConfig->ptChannelData->u4DequeueStopCount = CSM_DEQUEUE_STOP_TEMPORARY;
            }
        }
        else
        {
            ud_ret = (Std_ReturnType)CRYPTO_E_BUSY;
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_AsyncProcessJob                                */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | u2JobIndex :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : request successful                          */
/*               | E_NOT_OK   : request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : the key is not valid            */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : a key element has the       */
/*               |                              wrong size                  */
/*               | CRYPTO_E_KEY_READ_FAIL :  key element extraction is      */
/*               |                           not allowed                    */
/*               | CRYPTO_E_KEY_WRITE_FAIL : the writing access failed      */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : the key is not available    */
/*               | CRYPTO_E_JOB_CANCELED : the synchronous Job has been     */
/*               |                         canceled                         */
/*               | CRYPTO_E_KEY_EMPTY : uninitialized source key element    */
/*               | CRYPTO_E_ENTROPY_EXHAUSTED :  Entropy is depleted        */
/* Notes         | SWS_Csm_01041                                            */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_AsyncProcessJob
(
    uint16 u2JobIndex
)
{
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)               pt_jobSubConfig = &Csm_Cfg_stJob.ptSubConfig[u2JobIndex];
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_queueConfig = pt_jobSubConfig->ptJobQueue;
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_SHARED_VAR_NO_INIT)           pt_jobData = &Csm_Cfg_stJob.ptData[u2JobIndex];
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)               pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u2JobIndex];
    Std_ReturnType          ud_ret;
    uint32                  u4_jobChannelId = pt_queueConfig->u4CryIfChannelId;
    uint32                  u4_dequeueStopCount;
    uint16                  u2_highestPriority;
    
    if( pt_jobData->stJob.jobState == CRYPTO_JOBSTATE_ACTIVE )
    {
        pt_jobSubData->udCsmJobState = CSM_S_JOB_BUSY;
        
        SchM_Exit_Csm_General();
        
        ud_ret = CryIf_ProcessJob( u4_jobChannelId, &(pt_jobData->stJob) );
        
        SchM_Enter_Csm_General();
    }
    else
    {
        u2_highestPriority = pt_queueConfig->ptChannelData->u2HighestPriority;
        u4_dequeueStopCount = pt_queueConfig->ptChannelData->u4DequeueStopCount;
        
        if( ( u2_highestPriority != (uint16)0U )
         || ( u4_dequeueStopCount > 0UL ) )
        {
            ud_ret = Csm_Queue_Enqueue( u2JobIndex );
        }
        else
        {
            pt_jobSubData->udCsmJobState = CSM_S_JOB_BUSY;
            
            SchM_Exit_Csm_General();
            
            ud_ret = CryIf_ProcessJob( u4_jobChannelId, &(pt_jobData->stJob) );
            
            SchM_Enter_Csm_General();
            
            if( ud_ret == (Std_ReturnType)CRYPTO_E_BUSY )
            {
                pt_jobSubData->udCsmJobState = CSM_S_JOB_ACCEPT;
                
                ud_ret = Csm_Queue_Enqueue( u2JobIndex );
            }
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_Enqueue                                        */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | u2JobIndex :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : request successful                          */
/*               | E_NOT_OK   : request failed                              */
/*               | CSM_S_JOB_BUSY   : Queue is full of elements             */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_Enqueue
(
    uint16 u2JobIndex
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)            pt_queueConfig = Csm_Cfg_stJob.ptSubConfig[u2JobIndex].ptJobQueue;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)    pt_priorityConfigTop = pt_queueConfig->ptPriorityConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)    pt_priorityConfig;
    P2VAR(Csm_Cfg_Ram_QueueElementType, AUTOMATIC, CSM_VAR_NO_INIT)                      pt_queueElement;
    Std_ReturnType  ud_ret = E_OK;
    uint32          u4_priorityIndex = (uint32)Csm_Cfg_stJob.ptSubConfig[u2JobIndex].u2QueuePriorityIndex;
    uint16          u2_tailIndex;
    uint16          u2_jobIndex;
    
    if( (pt_priorityConfigTop != NULL_PTR)
     && (u4_priorityIndex < pt_queueConfig->u4ConfigNum) )
    {
        pt_priorityConfig = &pt_priorityConfigTop[u4_priorityIndex];
        
        u2_tailIndex = pt_priorityConfig->ptRingBuffData->u2TailIndex;
        
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        if( u2_tailIndex == (uint16)(~pt_priorityConfig->ptRingBuffData->u2TailIndexRed) )
        {
#endif
            pt_queueElement =  &pt_priorityConfig->ptElementData[u2_tailIndex];
            u2_jobIndex = pt_queueElement->u2JobIndex;
            
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            if( u2_jobIndex == (uint16)(~pt_queueElement->u2JobIndexRed) )
            {
#endif
                if( u2_jobIndex == CSM_QUEUE_NOT_USE )
                {
                    pt_queueElement->u2JobIndex = u2JobIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                    pt_queueElement->u2JobIndexRed = (uint16)(~u2JobIndex);
#endif
                    
                    if( pt_queueConfig->ptChannelData->u2HighestPriority < pt_priorityConfig->u2Priority )
                    {
                        pt_queueConfig->ptChannelData->u2HighestPriority = pt_priorityConfig->u2Priority;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                        pt_queueConfig->ptChannelData->u2HighestPriorityRed = (uint16)~pt_priorityConfig->u2Priority;
#endif
                    }
                }
                else
                {
                    u2_tailIndex++;
                    
                    if( u2_tailIndex >= pt_priorityConfig->u4QueueSize )
                    {
                        u2_tailIndex = 0U;
                    }
                    
                    pt_queueElement = &pt_priorityConfig->ptElementData[u2_tailIndex];
                    u2_jobIndex = pt_queueElement->u2JobIndex;
                    
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                    if( u2_jobIndex == (uint16)(~pt_queueElement->u2JobIndexRed) )
                    {
#endif
                        if( u2_jobIndex == CSM_QUEUE_NOT_USE )
                        {
                            pt_queueElement->u2JobIndex = u2JobIndex;
                            pt_priorityConfig->ptRingBuffData->u2TailIndex = u2_tailIndex;
                            
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                            pt_queueElement->u2JobIndexRed = (uint16)(~u2JobIndex);
                            pt_priorityConfig->ptRingBuffData->u2TailIndexRed = (uint16)(~u2_tailIndex);
#endif
                        }
                        else
                        {
                            ud_ret = (Std_ReturnType)CRYPTO_E_BUSY;
                        }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                    }
                    else
                    {
                        Csm_General_udStatus = CSM_S_RAMERROR;
                        ud_ret = E_NOT_OK;
                    }
#endif
                }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            }
            else
            {
                Csm_General_udStatus = CSM_S_RAMERROR;
                ud_ret = E_NOT_OK;
            }
        }
        else
        {
            Csm_General_udStatus = CSM_S_RAMERROR;
            ud_ret = E_NOT_OK;
        }
#endif
    }
    else
    {
        ud_ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_ChannelCountProc                               */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(void, CSM_CODE) Csm_Queue_ChannelCountProc
(
    void
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigAccessType, AUTOMATIC, CSM_CONFIG_DATA) pt_queueConfigAccess = &Csm_Cfg_stQueue;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfigTop = pt_queueConfigAccess->ptConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfig;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT)             pt_channelData;
    uint32  u4_dequeueStopCount;
    uint16  u2_timeOutCount;
    uint16  u2_configIndex;
    uint16  u2_jobProcessingNum;
    
    SchM_Enter_Csm_General();
    
    for( u2_configIndex = 0U; u2_configIndex < (uint16)pt_queueConfigAccess->u4ConfigNum; u2_configIndex++ )
    {
        pt_queueConfig = &pt_queueConfigTop[u2_configIndex];
        pt_channelData = pt_queueConfig->ptChannelData;
        u4_dequeueStopCount = pt_channelData->u4DequeueStopCount;
        
        if( u4_dequeueStopCount > 0UL )
        {
            u4_dequeueStopCount--;
            pt_channelData->u4DequeueStopCount = u4_dequeueStopCount;
            pt_channelData->u1DequeueFlag = CSM_FLG_FALSE;
        }
        else
        {
            pt_channelData->u1DequeueFlag = CSM_FLG_TRUE;
        }
        
        if( pt_queueConfig->u2ChannelTimeOut != (uint16)0U )
        {
            u2_timeOutCount = pt_channelData->u2TimeOutCount;
            u2_jobProcessingNum = pt_channelData->u2JobProcessingNum;
            
            if( u2_jobProcessingNum > (uint16)0U )
            {
                if( (pt_channelData->u1DequeueFlag == CSM_FLG_TRUE)
                 && (u2_timeOutCount < pt_queueConfig->u2ChannelTimeOut) )
                {
                    u2_timeOutCount++;
                }
            }
            else
            {
                u2_timeOutCount = 0U;
            }
            
            pt_channelData->u2TimeOutCount = u2_timeOutCount;
        }
    }
    
    SchM_Exit_Csm_General();
    
    return;
}

/****************************************************************************/
/* Function Name | Csm_Queue_MainFuncChannel                                */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptQueueConfig :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : request successful                       */
/*               | E_NOT_OK      : request failed                           */
/*               | CRYPTO_E_BUSY : request busy                             */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncChannel
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig
)
{
    Std_ReturnType  ud_ret = E_OK;
    uint16          u2_highestPriority;
    uint16          u2_configIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfigTop = ptQueueConfig->ptPriorityConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfig;
    P2CONST(Csm_Cfg_Ram_QueueRingBufferType, AUTOMATIC, CSM_VAR_NO_INIT)                pt_ringBuffData;
    P2CONST(Csm_Cfg_Ram_QueueElementType, AUTOMATIC, CSM_VAR_NO_INIT)                   pt_elementData;
    uint16          u2_headIndex;
    uint16          u2_headIndexRed;
    uint16          u2_jobIndex;
    uint16          u2_jobIndexRed;
    
    SchM_Enter_Csm_General();
    
    for( u2_configIndex = 0U; u2_configIndex < (uint16)ptQueueConfig->u4ConfigNum; u2_configIndex++ )
    {
        pt_priorityConfig = &pt_priorityConfigTop[u2_configIndex];
        pt_ringBuffData = pt_priorityConfig->ptRingBuffData;
        
        u2_headIndex = pt_ringBuffData->u2HeadIndex;
        u2_headIndexRed = (uint16)(~pt_ringBuffData->u2HeadIndexRed);
        
        if( u2_headIndex == u2_headIndexRed )
        {
            pt_elementData = &pt_priorityConfig->ptElementData[u2_headIndex];
            
            u2_jobIndex = pt_elementData->u2JobIndex;
            u2_jobIndexRed = (uint16)(~pt_elementData->u2JobIndexRed);
            
            if( u2_jobIndex != u2_jobIndexRed )
            {
                ud_ret = E_NOT_OK;
            }
        }
        else
        {
            ud_ret = E_NOT_OK;
        }
        
        if( ud_ret != (Std_ReturnType)E_OK )
        {
            Csm_General_udStatus = CSM_S_RAMERROR;
            break;
        }
    }
    
    SchM_Exit_Csm_General();
    
    if( ud_ret == (Std_ReturnType)E_OK )
    {
#endif
        u2_highestPriority = ptQueueConfig->ptChannelData->u2HighestPriority;
        
        for( u2_configIndex = 0U; u2_configIndex < (uint16)ptQueueConfig->u4ConfigNum; u2_configIndex++ )
        {
            if( u2_highestPriority >= ptQueueConfig->ptPriorityConfig[u2_configIndex].u2Priority )
            {
                ud_ret = Csm_Queue_MainFuncPriority( ptQueueConfig, u2_configIndex );
                
                if( ud_ret != (Std_ReturnType)E_OK )
                {
                    break;
                }
            }
        }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    }
#endif
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_MainFuncPriority                               */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptQueueConfig   :                                        */
/*               | u2PriorityIndex :                                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : request successful                       */
/*               | E_NOT_OK      : request failed                           */
/*               | CRYPTO_E_BUSY : request busy                             */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncPriority
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig,
    uint16 u2PriorityIndex
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfigTop = ptQueueConfig->ptPriorityConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfig = &pt_priorityConfigTop[u2PriorityIndex];
    Std_ReturnType  ud_ret = E_OK;
    uint16          u2_queueElementCount;
    uint8           u1_queueEmptyFlag = CSM_FLG_FALSE;
    
    for( u2_queueElementCount = 0U; u2_queueElementCount < (uint16)pt_priorityConfig->u4QueueSize; u2_queueElementCount++ )
    {
        ud_ret = Csm_Queue_MainFuncQueue( ptQueueConfig, u2PriorityIndex, &u1_queueEmptyFlag );
        
        if( (ud_ret != (Std_ReturnType)E_OK)
         || (u1_queueEmptyFlag == CSM_FLG_TRUE) )
        {
            break;
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_MainFuncQueue                                  */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptQueueConfig    :                                       */
/*               | u2PriorityIndex  :                                       */
/*               | ptQueueEmptyFlag :                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : request successful                       */
/*               | E_NOT_OK      : request failed                           */
/*               | CRYPTO_E_BUSY : request busy                             */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_MainFuncQueue
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig,
    uint16 u2PriorityIndex,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptQueueEmptyFlag
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfigTop = ptQueueConfig->ptPriorityConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA)   pt_priorityConfig = &pt_priorityConfigTop[u2PriorityIndex];
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_SHARED_VAR_NO_INIT)                   pt_jobData;
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)                       pt_jobSubData;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT)                 pt_channelData = ptQueueConfig->ptChannelData;
    Csm_JobStateType    ud_csmJobState;
    Std_ReturnType      ud_ret = E_OK;
    Std_ReturnType      ud_jobRet;
    uint32              u4_jobChannelId;
    uint16              u2_headIndex = pt_priorityConfig->ptRingBuffData->u2HeadIndex;
    uint16              u2_jobIndex;
    uint16              u2_tmpJobIndex;
    uint16              u2_nextPriorityIndex;
    uint16              u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16              u2_jobProcessingNumRedTmp;
#endif
    uint8               u1_callbackFlag = CSM_FLG_FALSE;
    uint8               u1_queueEmptyFlag = CSM_FLG_FALSE;
    uint8               u1_dequeueFlag = CSM_FLG_FALSE;
    
    u2_jobIndex = pt_priorityConfig->ptElementData[u2_headIndex].u2JobIndex;
    
    if( u2_jobIndex != CSM_QUEUE_NOT_USE )
    {
        pt_jobData = &Csm_Cfg_stJob.ptData[u2_jobIndex];
        pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u2_jobIndex];
        
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        ud_jobRet = Csm_Queue_DequeueRamCheck( pt_priorityConfig );
        
        if( ud_jobRet == (Std_ReturnType)E_OK )
        {
#endif
            ud_csmJobState = pt_jobSubData->udCsmJobState;
            
            if( ud_csmJobState == CSM_S_JOB_ACCEPT )
            {
                pt_jobSubData->udCsmJobState = CSM_S_JOB_BUSY;
                
                u4_jobChannelId = ptQueueConfig->u4CryIfChannelId;
                
                ud_jobRet = CryIf_ProcessJob( u4_jobChannelId, &(pt_jobData->stJob) );
                
                if( ud_jobRet == (Std_ReturnType)E_OK )
                {
                    ; /* No Processing */
                }
                else if( ud_jobRet == (Std_ReturnType)CRYPTO_E_BUSY )
                {
                    pt_jobSubData->udCsmJobState = CSM_S_JOB_ACCEPT;
                    
                    ud_ret = (Std_ReturnType)CRYPTO_E_BUSY;
                }
                else
                {
                    u1_callbackFlag = CSM_FLG_TRUE;
                }
            }
            else if( ud_csmJobState == CSM_S_JOB_CANCEL_ACCEPT )
            {
                ud_jobRet = CRYPTO_E_JOB_CANCELED;
                u1_callbackFlag = CSM_FLG_TRUE;
            }
            else
            {
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                Csm_General_udStatus = CSM_S_RAMERROR;
#endif
                ud_jobRet = E_NOT_OK;
            }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        }
        else
        {
            u1_callbackFlag = CSM_FLG_TRUE;
        }
#endif
        
        if( ud_jobRet != (Std_ReturnType)CRYPTO_E_BUSY )
        {
            u1_dequeueFlag = CSM_FLG_TRUE;
        }
    }
    else
    {
        u1_queueEmptyFlag = CSM_FLG_TRUE;
    }
    
    SchM_Enter_Csm_General();
    
    if( u1_dequeueFlag == CSM_FLG_TRUE )
    {
        ud_ret = Csm_Queue_Dequeue( pt_priorityConfig, u2_headIndex, &u1_queueEmptyFlag );
    }
    
    if( u1_queueEmptyFlag == CSM_FLG_TRUE )
    {
        u2_tmpJobIndex = pt_priorityConfig->ptElementData[u2_headIndex].u2JobIndex;
        if( u2_tmpJobIndex == CSM_QUEUE_NOT_USE )
        {
            if( pt_channelData->u2HighestPriority == pt_priorityConfig->u2Priority )
            {
                u2_nextPriorityIndex = u2PriorityIndex;
                u2_nextPriorityIndex++;
                
                if( u2_nextPriorityIndex < ptQueueConfig->u4ConfigNum )
                {
                    pt_channelData->u2HighestPriority = ptQueueConfig->ptPriorityConfig[u2_nextPriorityIndex].u2Priority;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                    pt_channelData->u2HighestPriorityRed = (uint16)~ptQueueConfig->ptPriorityConfig[u2_nextPriorityIndex].u2Priority;
#endif
                }
                else
                {
                    pt_channelData->u2HighestPriority = 0U;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                    pt_channelData->u2HighestPriorityRed = CSM_RED_INIT_U2;
#endif
                }
            }
            
            *ptQueueEmptyFlag = CSM_FLG_TRUE;
        }
    }
    
    if( u1_callbackFlag == CSM_FLG_TRUE )
    {
        u2_jobProcessingNumTmp = pt_channelData->u2JobProcessingNum;
        u2_jobProcessingNumTmp--;
        pt_channelData->u2JobProcessingNum = u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        u2_jobProcessingNumRedTmp = pt_channelData->u2JobProcessingNumRed;
        u2_jobProcessingNumRedTmp++;
        pt_channelData->u2JobProcessingNumRed = u2_jobProcessingNumRedTmp;
#endif
        pt_channelData->u2TimeOutCount = 0U;
        
        pt_jobSubData->udCsmJobState = CSM_S_JOB_IDLE;
    }
    
    SchM_Exit_Csm_General();
    
    if( u1_callbackFlag == CSM_FLG_TRUE )
    {
        if( Csm_Cfg_stJob.ptSubConfig[u2_jobIndex].ptJobPrimitiveCallbackFunc != NULL_PTR )
        {
            Csm_Cfg_stJob.ptSubConfig[u2_jobIndex].ptJobPrimitiveCallbackFunc( Csm_Cfg_stJob.ptConfig[u2_jobIndex].stJobInfo.jobId,
                                                                               (Crypto_ResultType)ud_jobRet );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Queue_Dequeue                                        */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptPriorityConfig :                                       */
/*               | u2HeadIndex      :                                       */
/*               | ptQueueEmptyFlag :                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : request successful                          */
/*               | E_NOT_OK   : request failed                              */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_Dequeue
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptPriorityConfig,
    uint16 u2HeadIndex,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptQueueEmptyFlag
)
{
    Std_ReturnType  ud_ret = E_OK;
    uint16          u2_headIndex = u2HeadIndex;
    uint16          u2_jobIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16          u2_jobIndexRed;
#endif
    
    ptPriorityConfig->ptElementData[u2_headIndex].u2JobIndex = CSM_QUEUE_NOT_USE;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    ptPriorityConfig->ptElementData[u2_headIndex].u2JobIndexRed = 0U;
#endif
    
    u2_headIndex++;
    if( u2_headIndex >= (uint16)ptPriorityConfig->u4QueueSize )
    {
        u2_headIndex = 0U;
    }
    
    u2_jobIndex = ptPriorityConfig->ptElementData[u2_headIndex].u2JobIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    u2_jobIndexRed = (uint16)(~ptPriorityConfig->ptElementData[u2_headIndex].u2JobIndexRed);
    
    if( u2_jobIndex == u2_jobIndexRed )
    {
#endif
        if( u2_jobIndex != CSM_QUEUE_NOT_USE )
        {
            ptPriorityConfig->ptRingBuffData->u2HeadIndex = u2_headIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            ptPriorityConfig->ptRingBuffData->u2HeadIndexRed = (uint16)(~ptPriorityConfig->ptRingBuffData->u2HeadIndex);
#endif
        }
        else
        {
            *ptQueueEmptyFlag = CSM_FLG_TRUE;
        }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        Csm_General_udStatus = CSM_S_RAMERROR;
        ud_ret = E_NOT_OK;
    }
#endif
    
    return ud_ret;
}

#if (CSM_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Csm_Queue_DequeueRamCheck                                */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptPriorityConfig :                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : no RAM garbled data.                        */
/*               | E_NOT_OK   : detect RAM garbled data                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_Queue_DequeueRamCheck
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptPriorityConfig
)

{
    P2CONST(Csm_Cfg_JobConfigType, AUTOMATIC, CSM_CONFIG_DATA)          pt_jobConfig;
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_jobSubConfig;
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_VAR_NO_INIT)          pt_jobData;
    P2CONST(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)     pt_jobSubData;
    P2CONST(Csm_Cfg_Ram_QueueElementType, AUTOMATIC, CSM_VAR_NO_INIT)   pt_queueElement = (const Csm_Cfg_Ram_QueueElementType *)ptPriorityConfig->ptElementData;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint16          u2_headIndex = ptPriorityConfig->ptRingBuffData->u2HeadIndex;
    uint16          u2_jobIndex = pt_queueElement[u2_headIndex].u2JobIndex;
    
    pt_jobConfig = &Csm_Cfg_stJob.ptConfig[u2_jobIndex];
    pt_jobSubConfig = &Csm_Cfg_stJob.ptSubConfig[u2_jobIndex];
    pt_jobData = &Csm_Cfg_stJob.ptData[u2_jobIndex];
    pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u2_jobIndex];
    
    if( ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.inputPtr                 == ~pt_jobSubData->stJobInOutRed.u4InputPtr )                  /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.secondaryInputPtr        == ~pt_jobSubData->stJobInOutRed.u4SecondaryInputPtr )         /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.tertiaryInputPtr         == ~pt_jobSubData->stJobInOutRed.u4TertiaryInputPtr )          /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.outputPtr                == ~pt_jobSubData->stJobInOutRed.u4OutputPtr )                 /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.outputLengthPtr          == ~pt_jobSubData->stJobInOutRed.u4OutputLengthPtr )           /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.secondaryOutputPtr       == ~pt_jobSubData->stJobInOutRed.u4SecondaryOutputPtr )        /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.secondaryOutputLengthPtr == ~pt_jobSubData->stJobInOutRed.u4SecondaryOutputLengthPtr )  /* MISRA DEVIATION: */
     && ( (uint32)pt_jobData->stJob.jobPrimitiveInputOutput.verifyPtr                == ~pt_jobSubData->stJobInOutRed.u4VerifyPtr )                 /* MISRA DEVIATION: */
     && ( pt_jobData->stJob.jobPrimitiveInputOutput.cryIfKeyId                       == ~pt_jobSubData->stJobInOutRed.u4CryIfKeyId )
     && ( pt_jobData->stJob.jobPrimitiveInputOutput.targetCryIfKeyId                 == ~pt_jobSubData->stJobInOutRed.u4TargetCryIfKeyId ) )
    {
        pt_jobData->stJob.jobPrimitiveInfo  = &pt_jobConfig->stJobPrimitiveInfo;
        pt_jobData->stJob.jobInfo           = &pt_jobConfig->stJobInfo;
        
        if( pt_jobSubConfig->ptJobRedirectionInfo != NULL_PTR )
        {
            pt_jobData->stJobRedirectionInfo.redirectionConfig           = pt_jobSubConfig->ptJobRedirectionInfo->redirectionConfig;
            pt_jobData->stJobRedirectionInfo.inputKeyId                  = pt_jobSubConfig->ptJobRedirectionInfo->inputKeyId;
            pt_jobData->stJobRedirectionInfo.inputKeyElementId           = pt_jobSubConfig->ptJobRedirectionInfo->inputKeyElementId;
            pt_jobData->stJobRedirectionInfo.secondaryInputKeyId         = pt_jobSubConfig->ptJobRedirectionInfo->secondaryInputKeyId;
            pt_jobData->stJobRedirectionInfo.secondaryInputKeyElementId  = pt_jobSubConfig->ptJobRedirectionInfo->secondaryInputKeyElementId;
            pt_jobData->stJobRedirectionInfo.tertiaryInputKeyId          = pt_jobSubConfig->ptJobRedirectionInfo->tertiaryInputKeyId;
            pt_jobData->stJobRedirectionInfo.tertiaryInputKeyElementId   = pt_jobSubConfig->ptJobRedirectionInfo->tertiaryInputKeyElementId;
            pt_jobData->stJobRedirectionInfo.outputKeyId                 = pt_jobSubConfig->ptJobRedirectionInfo->outputKeyId;
            pt_jobData->stJobRedirectionInfo.outputKeyElementId          = pt_jobSubConfig->ptJobRedirectionInfo->outputKeyElementId;
            pt_jobData->stJobRedirectionInfo.secondaryOutputKeyId        = pt_jobSubConfig->ptJobRedirectionInfo->secondaryOutputKeyId;
            pt_jobData->stJobRedirectionInfo.secondaryOutputKeyElementId = pt_jobSubConfig->ptJobRedirectionInfo->secondaryOutputKeyElementId;
            
            pt_jobData->stJob.jobRedirectionInfoRef                      = &pt_jobData->stJobRedirectionInfo;
        }
        else
        {
            pt_jobData->stJob.jobRedirectionInfoRef = NULL_PTR;
        }
        
        ud_ret = E_OK;
    }
    
    return ud_ret;
}
#endif

/****************************************************************************/
/* Function Name | Csm_Queue_DetectTimeOut                                  */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptQueueConfig :                                          */
/* Return Value  | -                                                        */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(void, CSM_CODE) Csm_Queue_DetectTimeOut
(
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA) ptQueueConfig
)
{
    P2CONST(AB_83_ConstV Csm_TimeOutCalloutType, AUTOMATIC, CSM_CONFIG_DATA)  pt_timeOutCalloutConfig = Csm_Cfg_stTimeOutCallout.ptConfig;
    uint32  u4_channelId;
    uint16  u2_timeOutCount;
    uint16  u2_loop;
    
    if( ptQueueConfig->u2ChannelTimeOut != (uint16)0U )
    {
        u2_timeOutCount = ptQueueConfig->ptChannelData->u2TimeOutCount;
        
        if( u2_timeOutCount >= ptQueueConfig->u2ChannelTimeOut )
        {
            for( u2_loop = 0U; u2_loop < (uint16)Csm_Cfg_stTimeOutCallout.u4ConfigNum; u2_loop++ )
            {
                if( pt_timeOutCalloutConfig[u2_loop] != NULL_PTR )
                {
                    u4_channelId = ptQueueConfig->u4CryIfChannelId;
                    pt_timeOutCalloutConfig[u2_loop]( u4_channelId );
                }
            }
        }
    }
    
    return;
}

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
