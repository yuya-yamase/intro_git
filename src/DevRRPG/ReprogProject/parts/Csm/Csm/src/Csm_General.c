/* Csm_General_c_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/General/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Csm.h>
#include <CryIf.h>
#include <SchM_Csm.h>
#include "../inc/Csm_Queue.h"
#include "../inc/Csm_General.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

#if (CSM_RAM_ERROR_CHECK == STD_ON)
static FUNC(void, CSM_CODE) Csm_General_DetectError
(
    void
);
#endif

static FUNC(void, CSM_CODE) Csm_General_NotificationError
(
    void
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_VAR_CLEARED_WAKEUP
#include <Csm_MemMap.h>

VAR(Csm_StatusType, CSM_VAR_CLEARED_WAKEUP) Csm_General_udStatus;

#define CSM_STOP_SEC_VAR_CLEARED_WAKEUP
#include <Csm_MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT
#include <Csm_MemMap.h>

#if (CSM_RAM_ERROR_CHECK == STD_ON)
static VAR(uint16, CSM_VAR_NO_INIT) Csm_General_u2RamCheckCount;
#endif

#define CSM_STOP_SEC_VAR_NO_INIT
#include <Csm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* Function Name | Csm_Init                                                 */
/* Description   | Initializes the CSM module.                              */
/* Preconditions | -                                                        */
/* Parameters    | configPtr : No use                                       */
/* Return Value  | -                                                        */
/* Notes         | SWS_Csm_00646                                            */
/****************************************************************************/
FUNC(void, CSM_CODE) Csm_Init
(
    P2CONST(Csm_ConfigType, AUTOMATIC, CSM_APPL_DATA) configPtr
)
{
    uint16  u2_configNum;
    uint16  u2_priorityNum;
    uint16  u2_queueNum;
    
    for( u2_configNum = 0U; u2_configNum < (uint16)Csm_Cfg_stJob.u4ConfigNum; u2_configNum++ )
    {
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobId                                              = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobState                                           = CRYPTO_JOBSTATE_IDLE;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.inputPtr                   = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.inputLength                = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.secondaryInputPtr          = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.secondaryInputLength       = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.tertiaryInputPtr           = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.tertiaryInputLength        = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.outputPtr                  = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.outputLengthPtr            = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.secondaryOutputPtr         = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.secondaryOutputLengthPtr   = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.verifyPtr                  = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.mode                       = CRYPTO_OPERATIONMODE_START;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.cryIfKeyId                 = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInputOutput.targetCryIfKeyId           = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobPrimitiveInfo                                   = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobInfo                                            = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.cryptoKeyId                                        = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobRedirectionInfoRef                              = NULL_PTR;
        Csm_Cfg_stJob.ptData[u2_configNum].stJob.targetCryptoKeyId                                  = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.redirectionConfig                   = 0U;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.inputKeyId                          = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.inputKeyElementId                   = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.secondaryInputKeyId                 = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.secondaryInputKeyElementId          = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.tertiaryInputKeyId                  = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.tertiaryInputKeyElementId           = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.outputKeyId                         = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.outputKeyElementId                  = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.secondaryOutputKeyId                = 0UL;
        Csm_Cfg_stJob.ptData[u2_configNum].stJobRedirectionInfo.secondaryOutputKeyElementId         = 0UL;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4InputPtr                              = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4SecondaryInputPtr                     = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4TertiaryInputPtr                      = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4OutputPtr                             = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4OutputLengthPtr                       = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4SecondaryOutputPtr                    = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4SecondaryOutputLengthPtr              = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4VerifyPtr                             = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4CryIfKeyId                            = CSM_RED_INIT_U4;
        Csm_Cfg_stJob.ptSubData[u2_configNum].stJobInOutRed.u4TargetCryIfKeyId                      = CSM_RED_INIT_U4;
#endif
        Csm_Cfg_stJob.ptSubData[u2_configNum].udCsmJobState                                         = CSM_S_JOB_IDLE;
    }
    
    for( u2_configNum = 0U; u2_configNum < (uint16)Csm_Cfg_stQueue.u4ConfigNum; u2_configNum++ )
    {
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u2HighestPriority     = 0U;
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u4DequeueStopCount    = 0UL;
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u2TimeOutCount        = 0U;
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u2JobProcessingNum    = 0U;
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u1DequeueFlag         = CSM_FLG_TRUE;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u2HighestPriorityRed  = CSM_RED_INIT_U2;
        Csm_Cfg_stQueue.ptConfig[u2_configNum].ptChannelData->u2JobProcessingNumRed = CSM_RED_INIT_U2;
#endif
        
        for( u2_priorityNum = 0U; u2_priorityNum < (uint16)Csm_Cfg_stQueue.ptConfig[u2_configNum].u4ConfigNum; u2_priorityNum++ )
        {
            Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptRingBuffData->u2HeadIndex     = 0U;
            Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptRingBuffData->u2TailIndex     = 0U;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptRingBuffData->u2HeadIndexRed  = CSM_RED_INIT_U2;
            Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptRingBuffData->u2TailIndexRed  = CSM_RED_INIT_U2;
#endif
            
            for( u2_queueNum = 0U; u2_queueNum < (uint16)Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].u4QueueSize; u2_queueNum++ )
            {
                Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptElementData[u2_queueNum].u2JobIndex    = CSM_QUEUE_NOT_USE;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                Csm_Cfg_stQueue.ptConfig[u2_configNum].ptPriorityConfig[u2_priorityNum].ptElementData[u2_queueNum].u2JobIndexRed = 0U;
#endif
            }
        }
    }
    
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    Csm_General_u2RamCheckCount = 0U;
#endif
    Csm_General_udStatus        = CSM_S_INIT;
    
    return;
}

/****************************************************************************/
/* Function Name | Csm_GetVersionInfo                                       */
/* Description   | Returns the version information of this module.          */
/* Preconditions | -                                                        */
/* Parameters    | versioninfo : Pointer to where to store the version      */
/*               |               information of this module.                */
/* Return Value  | -                                                        */
/* Notes         | SWS_Csm_00705                                            */
/****************************************************************************/
FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versioninfo
)
{
    boolean b_versionInfoApi = Csm_Cfg_bVersionInfoApi;
    
    if( b_versionInfoApi == (boolean)TRUE )
    {
        if( versioninfo != NULL_PTR )
        {
            versioninfo->vendorID         = (uint16)CSM_VENDOR_ID;
            versioninfo->moduleID         = (uint16)CSM_MODULE_ID;
            versioninfo->sw_major_version = (uint8)CSM_SW_MAJOR_VERSION;
            versioninfo->sw_minor_version = (uint8)CSM_SW_MINOR_VERSION;
            versioninfo->sw_patch_version = (uint8)CSM_SW_PATCH_VERSION;
        }
    }
    
    return;
}

/****************************************************************************/
/* Function Name | Csm_MainFunction                                         */
/* Description   | API to be called cyclically to process                   */
/*               | the requested jobs. The Csm_MainFunction shall check     */
/*               | the queues for jobs to pass to the underlying CRYIF.     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | SWS_Csm_00479                                            */
/****************************************************************************/
FUNC(void, CSM_CODE) Csm_MainFunction
(
    void
)
{
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    Csm_General_DetectError();
#endif
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        Csm_Queue_MainFunction();
    }
    
    Csm_General_NotificationError();
    
    return;
}

/****************************************************************************/
/* Function Name | Csm_CancelJob                                            */
/* Description   | Cancels the job processing from                          */
/*               | asynchronous or streaming jobs.                          */
/* Preconditions | -                                                        */
/* Parameters    | job    : Holds the identifier of the job to be canceled. */
/*               | mode   : Not used, just for                              */
/*               |          interface compatibility provided.               */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful. Job removed from        */
/*               |              any queue and potentially                   */
/*               |              from crypto driver hardware.                */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_JOB_CANCELED : Immediate cancelation            */
/*               |                         not possible. The cancelation    */
/*               |                         will be done at next suitable    */
/*               |                         processing step and notified via */
/*               |                         a negative job closing callback  */
/* Notes         | SWS_Csm_00968                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
    uint32 job,
    Crypto_OperationModeType mode
)
{
    P2CONST(Csm_Cfg_JobConfigType, AUTOMATIC, CSM_CONFIG_DATA)          pt_config;
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_subConfig;
    P2VAR(Csm_Cfg_Ram_JobDataType, AUTOMATIC, CSM_SHARED_VAR_NO_INIT)   pt_jobData;
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)       pt_jobSubData;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT) pt_channelData;
    Std_ReturnType      ud_ret = E_NOT_OK;
    Csm_JobStateType    ud_csmJobState;
    uint32              u4_jobChannelId;
    uint16              u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16              u2_jobProcessingNumRedTmp;
#endif
    uint8               u1_calloutFlag = CSM_FLG_FALSE;
    
    if( (Csm_General_udStatus == CSM_S_INIT)
     && (job < Csm_Cfg_stJob.u4ConfigNum) )
    {
        pt_config = &Csm_Cfg_stJob.ptConfig[job];
        pt_subConfig = &Csm_Cfg_stJob.ptSubConfig[job];
        pt_jobData = &Csm_Cfg_stJob.ptData[job];
        pt_jobSubData = &Csm_Cfg_stJob.ptSubData[job];
        pt_channelData = pt_subConfig->ptJobQueue->ptChannelData;
        
        if( pt_config->stJobPrimitiveInfo.processingType == CRYPTO_PROCESSING_ASYNC )
        {
            SchM_Enter_Csm_General();
            
            ud_csmJobState = pt_jobSubData->udCsmJobState;
            
            if( ud_csmJobState == CSM_S_JOB_ACCEPT )
            {
                pt_jobSubData->udCsmJobState = CSM_S_JOB_CANCEL_ACCEPT;
                ud_ret = (Std_ReturnType)CRYPTO_E_JOB_CANCELED;
            }
            else if( ud_csmJobState == CSM_S_JOB_CANCEL_ACCEPT )
            {
                ud_ret = (Std_ReturnType)CRYPTO_E_JOB_CANCELED;
            }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            else if( (ud_csmJobState == CSM_S_JOB_IDLE)
                  || (ud_csmJobState == CSM_S_JOB_BUSY)
                  || (ud_csmJobState == CSM_S_JOB_CANCEL_BUSY) )
#else
            else
#endif
            {
                pt_jobData->stJob.jobId             = job;
                pt_jobData->stJob.jobPrimitiveInfo  = &pt_config->stJobPrimitiveInfo;
                pt_jobData->stJob.jobInfo           = &pt_config->stJobInfo;
                
                u4_jobChannelId = pt_subConfig->ptJobQueue->u4CryIfChannelId;
                
                ud_ret = CryIf_CancelJob( u4_jobChannelId, &(pt_jobData->stJob) );
                
                if( ud_ret == (Std_ReturnType)E_OK )
                {
                    u1_calloutFlag = CSM_FLG_TRUE;
                    
                    if( ud_csmJobState != CSM_S_JOB_IDLE )
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
                else if( ud_ret == (Std_ReturnType)CRYPTO_E_JOB_CANCELED )
                {
                    if( ud_csmJobState == CSM_S_JOB_IDLE )
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
                    
                    pt_jobSubData->udCsmJobState = CSM_S_JOB_CANCEL_BUSY;
                }
                else
                {
                    ; /* No Processing */
                }
            }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            else
            {
                ; /* No Processing */
            }
#endif
            
            SchM_Exit_Csm_General();
            
            if( u1_calloutFlag == CSM_FLG_TRUE )
            {
                if( pt_subConfig->ptJobPrimitiveCallbackFunc != NULL_PTR )
                {
                    pt_subConfig->ptJobPrimitiveCallbackFunc( pt_config->stJobInfo.jobId,
                                                              (Crypto_ResultType)CRYPTO_E_JOB_CANCELED );
                }
            }
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_CallbackNotification                                 */
/* Description   | Notifies the CSM that a job has finished. This function  */
/*               | is used by the underlying layer.                         */
/* Preconditions | -                                                        */
/* Parameters    | job    : Holds a pointer to the job, which has finished. */
/*               | result : Contains the result of                          */
/*               |          the cryptographic operation.                    */
/* Return Value  | -                                                        */
/* Notes         | SWS_Csm_00970                                            */
/****************************************************************************/
FUNC(void, CSM_CODE) Csm_CallbackNotification
(
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
    Crypto_ResultType result
)
{
    P2CONST(Csm_Cfg_JobSubConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_subConfig;
    P2VAR(Csm_Cfg_Ram_JobSubDataType, AUTOMATIC, CSM_VAR_NO_INIT)       pt_jobSubData;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT) pt_channelData;
    Crypto_ResultType   ud_result = result;
    Csm_JobStateType    ud_csmJobState;
    uint32              u4_jobIndex;
    uint16              u2_jobProcessingNumTmp;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16              u2_jobProcessingNumRedTmp;
#endif
    uint8               u1_calloutFlag = CSM_FLG_FALSE;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( job != NULL_PTR )
        {
            u4_jobIndex = job->jobInfo->jobId;
            
            if( u4_jobIndex < Csm_Cfg_stJob.u4ConfigNum )
            {
                pt_subConfig = &Csm_Cfg_stJob.ptSubConfig[u4_jobIndex];
                pt_jobSubData = &Csm_Cfg_stJob.ptSubData[u4_jobIndex];
                pt_channelData = pt_subConfig->ptJobQueue->ptChannelData;
                
                SchM_Enter_Csm_General();
                
                ud_csmJobState = pt_jobSubData->udCsmJobState;
                
                if( (ud_csmJobState == CSM_S_JOB_BUSY)
                 || (ud_csmJobState == CSM_S_JOB_CANCEL_BUSY) )
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
                    
                    if( ud_csmJobState == CSM_S_JOB_CANCEL_BUSY )
                    {
                        ud_result = (Crypto_ResultType)CRYPTO_E_JOB_CANCELED;
                    }
                    
                    u1_calloutFlag = CSM_FLG_TRUE;
                    
                    pt_jobSubData->udCsmJobState = CSM_S_JOB_IDLE;
                }
                
                SchM_Exit_Csm_General();
                
                if( u1_calloutFlag == CSM_FLG_TRUE )
                {
                    if( pt_subConfig->ptJobPrimitiveCallbackFunc != NULL_PTR )
                    {
                        pt_subConfig->ptJobPrimitiveCallbackFunc( u4_jobIndex, ud_result );
                    }
                }
            }
        }
    }
    
    return;
}

/****************************************************************************/
/* Function Name | Csm_Ab_GetMode                                           */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptMode :                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful.                         */
/*               | E_NOT_OK   : Request failed.                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Ab_GetMode
(
    P2VAR(Csm_Ab_ModeType, AUTOMATIC, CSM_APPL_DATA) ptMode
)
{
    Std_ReturnType      ud_ret = E_NOT_OK;
    Csm_StatusType      ud_status;
    Crypto_JobStateType ud_cryptoJobState;
    Csm_JobStateType    ud_csmJobState;
    uint16              u2_configNum;
    uint8               u1_runFlag;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint8               u1_abnormalFlag;
#endif
    
    if( ptMode != NULL_PTR )
    {
        ud_ret = E_OK;
        ud_status = Csm_General_udStatus;
        
        if( ud_status == CSM_S_INIT )
        {
            u1_runFlag = CSM_FLG_FALSE;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            u1_abnormalFlag = CSM_FLG_FALSE;
#endif
            
            for( u2_configNum = 0U; u2_configNum < (uint16)Csm_Cfg_stJob.u4ConfigNum; u2_configNum++ )
            {
                ud_cryptoJobState = Csm_Cfg_stJob.ptData[u2_configNum].stJob.jobState;
                if( ud_cryptoJobState == CRYPTO_JOBSTATE_IDLE )
                {
                    ; /* No Processing */
                }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                else if( ud_cryptoJobState == CRYPTO_JOBSTATE_ACTIVE )
                {
                    u1_runFlag = CSM_FLG_TRUE;
                }
                else
                {
                    u1_abnormalFlag = CSM_FLG_TRUE;
                }
#else
                else
                {
                    u1_runFlag = CSM_FLG_TRUE;
                }
#endif
                
                ud_csmJobState = Csm_Cfg_stJob.ptSubData[u2_configNum].udCsmJobState;
                if( ud_csmJobState == CSM_S_JOB_IDLE )
                {
                    ; /* No Processing */
                }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
                else if( (ud_csmJobState == CSM_S_JOB_ACCEPT)
                      || (ud_csmJobState == CSM_S_JOB_BUSY)
                      || (ud_csmJobState == CSM_S_JOB_CANCEL_ACCEPT)
                      || (ud_csmJobState == CSM_S_JOB_CANCEL_BUSY) )
                {
                    u1_runFlag = CSM_FLG_TRUE;
                }
                else
                {
                    u1_abnormalFlag = CSM_FLG_TRUE;
                }
#else
                else
                {
                    u1_runFlag = CSM_FLG_TRUE;
                }
#endif
            }
            
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            if( u1_abnormalFlag == CSM_FLG_TRUE )
            {
                *ptMode = CSM_AB_M_ABNORMAL;
            }
            else
            {
#endif
                if( u1_runFlag == CSM_FLG_TRUE )
                {
                    *ptMode = CSM_AB_M_RUN;
                }
                else
                {
                    *ptMode = CSM_AB_M_IDLE;
                }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
            }
#endif
        }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        else if( ud_status == CSM_S_UNINIT )
        {
            *ptMode = CSM_AB_M_UNINIT;
        }
        else
        {
            *ptMode = CSM_AB_M_ABNORMAL;
        }
#else
        else
        {
            *ptMode = CSM_AB_M_UNINIT;
        }
#endif
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Ab_GetErrorStatus                                    */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptErrorStatus :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful.                         */
/*               | E_NOT_OK   : Request failed.                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Ab_GetErrorStatus
(
    P2VAR(Csm_Ab_ErrorStatusType, AUTOMATIC, CSM_APPL_DATA) ptErrorStatus
)
{
    Std_ReturnType  ud_ret = E_NOT_OK;
    Csm_StatusType  ud_status;
    
    if( ptErrorStatus != NULL_PTR )
    {
        ud_ret = E_OK;
        ud_status = Csm_General_udStatus;
        
        if( ud_status == CSM_S_INIT )
        {
            *ptErrorStatus = CSM_AB_E_NONE;
        }
#if (CSM_RAM_ERROR_CHECK == STD_ON)
        else if( ud_status == CSM_S_UNINIT )
        {
            *ptErrorStatus = CSM_AB_E_NOT_INITIALIZED;
        }
        else
        {
            *ptErrorStatus = CSM_AB_E_RAM_CHECK_FAIL;
        }
#else
        else
        {
            *ptErrorStatus = CSM_AB_E_NOT_INITIALIZED;
        }
#endif
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if (CSM_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Csm_General_DetectError                                  */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CSM_CODE) Csm_General_DetectError
(
    void
)
{
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigAccessType, AUTOMATIC, CSM_CONFIG_DATA) pt_queueConfigAccess = &Csm_Cfg_stQueue;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfigTop = pt_queueConfigAccess->ptConfig;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, AUTOMATIC, CSM_CONFIG_DATA)       pt_queueConfig;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, AUTOMATIC, CSM_VAR_NO_INIT)             pt_channelData;
    Csm_StatusType      ud_status;
    Crypto_JobStateType ud_jobState = CRYPTO_JOBSTATE_IDLE;
    Csm_JobStateType    ud_csmJobState = CSM_S_JOB_IDLE;
    uint32              u4_dequeueStopCount;
    uint16              u2_ramCheckCount;
    uint16              u2_loop;
    uint16              u2_highestPriority;
    uint16              u2_highestPriorityRed;
    uint16              u2_jobProcessingNum;
    uint16              u2_jobProcessingNumRed;
    
    ud_status = Csm_General_udStatus;
    u2_ramCheckCount = Csm_General_u2RamCheckCount;
    
    if( Csm_Cfg_stJob.u4ConfigNum > 0UL )
    {
        u2_ramCheckCount++;
        if( u2_ramCheckCount >= (uint16)Csm_Cfg_stJob.u4ConfigNum )
        {
            u2_ramCheckCount = 0U;
        }
        
        ud_jobState = Csm_Cfg_stJob.ptData[u2_ramCheckCount].stJob.jobState;
        ud_csmJobState = Csm_Cfg_stJob.ptSubData[u2_ramCheckCount].udCsmJobState;
    }
    
    if( ud_status == CSM_S_INIT )
    {
        if( ((ud_jobState == CRYPTO_JOBSTATE_IDLE)
          || (ud_jobState == CRYPTO_JOBSTATE_ACTIVE))
         && ((ud_csmJobState == CSM_S_JOB_IDLE)
          || (ud_csmJobState == CSM_S_JOB_ACCEPT)
          || (ud_csmJobState == CSM_S_JOB_BUSY)
          || (ud_csmJobState == CSM_S_JOB_CANCEL_ACCEPT)
          || (ud_csmJobState == CSM_S_JOB_CANCEL_BUSY)) )
        {
            SchM_Enter_Csm_General();
            
            for( u2_loop = 0U; u2_loop < (uint16)Csm_Cfg_stQueue.u4ConfigNum; u2_loop++ )
            {
                pt_queueConfig = &pt_queueConfigTop[u2_loop];
                pt_channelData = pt_queueConfig->ptChannelData;
                
                u2_highestPriority      = pt_channelData->u2HighestPriority;
                u2_highestPriorityRed   = (uint16)~pt_channelData->u2HighestPriorityRed;
                u2_jobProcessingNum     = pt_channelData->u2JobProcessingNum;
                u2_jobProcessingNumRed  = (uint16)~pt_channelData->u2JobProcessingNumRed;
                u4_dequeueStopCount     = pt_channelData->u4DequeueStopCount;
                
                if( u4_dequeueStopCount > pt_queueConfig->u4DequeueStop )
                {
                    pt_channelData->u4DequeueStopCount = pt_queueConfig->u4DequeueStop;
                }
                
                if( (u2_highestPriority != u2_highestPriorityRed)
                 || (u2_jobProcessingNum != u2_jobProcessingNumRed) )
                {
                    Csm_General_udStatus = CSM_S_RAMERROR;
                    break;
                }
            }
            
            SchM_Exit_Csm_General();
        }
        else
        {
            Csm_General_udStatus = CSM_S_RAMERROR;
        }
    }
    
    Csm_General_u2RamCheckCount = u2_ramCheckCount;
    
    return;
}
#endif

/****************************************************************************/
/* Function Name | Csm_General_NotificationError                            */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CSM_CODE) Csm_General_NotificationError
(
    void
)
{
    P2CONST(AB_83_ConstV Csm_ErrorCalloutType, AUTOMATIC, CSM_CONFIG_DATA)          pt_errorCalloutConfig = Csm_Cfg_stErrorCallout.ptConfig;
    Csm_Ab_ErrorStatusType  ud_errorStatus = CSM_AB_E_NONE;
    uint16                  u2_loop;
    
    (void)Csm_Ab_GetErrorStatus( &ud_errorStatus ); /* no return check required */
    
    if( ud_errorStatus != CSM_AB_E_NONE )
    {
        for( u2_loop = 0U; u2_loop < (uint16)Csm_Cfg_stErrorCallout.u4ConfigNum; u2_loop++ )
        {
            if( pt_errorCalloutConfig[u2_loop] != NULL_PTR )
            {
                pt_errorCalloutConfig[u2_loop]( ud_errorStatus );
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
