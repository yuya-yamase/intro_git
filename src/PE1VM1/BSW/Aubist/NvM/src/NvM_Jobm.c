/* NvM_Jobm.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBM/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Jobm.h"
#include "../inc/NvM_Jobm_Internal.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Jobq.h"
#include "../inc/NvM_WdtExt.h"
#include "../inc/NvM_Job.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Adb.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( NvM_BlockIdType, NVM_VAR_NO_INIT )   NvM_Jobm_ExecBlockId;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Jobm_Init                                            */
/* Description   | Function for resetting this unit.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_Init( void )
{
    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_RequestJob                                      */
/* Description   | Function to accept request.                              */
/* Preconditions | None                                                     */
/* Parameters    | u4JobId   : The kind of job.                             */
/*               | u2BlockId : The block identifier uniquely identifies     */
/*               |             one NVRAM block descriptor.                  */
/*               | ptDstPtr  : Pointer to the RAM data block to read NV     */
/*               |             block                                        */
/*               | ptSrcPtr  : Pointer to the RAM data block to write NV    */
/*               |             block                                        */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : request has  been accepted.                  */
/*               |  E_NOT_OK : request has not been accepted.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobm_RequestJob(
    uint32 u4JobId,
    NvM_BlockIdType u2BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) ptDstPtr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrcPtr
){
    Std_ReturnType u1Rtn;
    NvM_Jobm_stJobInfomationType stRequestJobInfo;

    stRequestJobInfo.u4JobId    = u4JobId;
    stRequestJobInfo.u2BlockId  = u2BlockId;
    stRequestJobInfo.ptDstPtr   = ptDstPtr;
    stRequestJobInfo.ptSrcPtr   = ptSrcPtr;

    if( (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB == u2BlockId )
    {
        u1Rtn = NvM_Jobq_MultiEnqueue( &stRequestJobInfo );
    }
    else
    {
        u1Rtn = NvM_Jobq_SglEnqueue( &stRequestJobInfo );
    }

    if( u1Rtn == (Std_ReturnType)E_OK )
    {
        NvM_Adb_SetErrorStatus( u2BlockId, u4JobId, NVM_REQ_PENDING );
    }

    return u1Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_MainFunction                                    */
/* Description   | Function for performing the processing of the jobs.      */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_MainFunction(
    uint8 CallMode
){
    NvM_Job_StatusType JobStatus;
    NvM_Nvb_StatusType NvbStatus;
    NvM_Jobm_stJobInfomationType CurrentJobInfo;

    JobStatus = NvM_Job_GetStatus( &CurrentJobInfo );

    if( JobStatus == (NvM_Job_StatusType)NVM_JOB_IDLE )
    {
        NvbStatus = NvM_Nvb_GetStatus();
        if( NvbStatus == (NvM_Nvb_StatusType)NVM_NVB_IDLE )
        {
            NvM_Jobm_SubMainfuncJobIdle();
        }
        else
        {
            /* JOB status and NVB status are inconsistent. */
            NvM_Evt_FatalFailedNotification();
        }
    }
    else if( JobStatus == (NvM_Job_StatusType)NVM_JOB_BUSY_CANCEL )
    {
        NvM_Jobm_SubMainfuncJobBusyCxl( &CurrentJobInfo );
    }
    else
    {
        NvM_Jobm_SubMainfuncJobBusy( &CurrentJobInfo );
    }

    NvM_Job_MainFunction( CallMode );

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_CancelJobs                                      */
/* Description   | Function to cancel a requested job.                      */
/* Preconditions | None                                                     */
/* Parameters    | ReqBlockId : The block identifier uniquely identifies    */
/*               |              one NVRAM block descriptor.                 */
/* Return Value  | Std_ReturnType : Request result.                         */
/*               |  E_OK     : The job  was successfully removed from       */
/*               |             queue.                                       */
/*               |  E_NOT_OK : The job could not be found in the queue.     */
/*               |             Or the job is already executing.             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobm_CancelJobs(
    NvM_BlockIdType ReqBlockId
){
    boolean IsExecute;
    Std_ReturnType CancelJobsResult = E_NOT_OK;
    Std_ReturnType DequeueResult;
    NvM_Jobm_stJobInfomationType JobInfo;
    NvM_BlockIdType CanceledBlockId;
    uint32 CanceledJobId;

    IsExecute = NvM_Jobm_IsReqBlockExecuting( ReqBlockId );

    if( IsExecute == (boolean)FALSE )
    {
        DequeueResult = NvM_Jobq_SglDequeueSrchBlockId( ReqBlockId, &JobInfo );

        if( DequeueResult == (Std_ReturnType)E_OK )
        {
            CanceledBlockId = JobInfo.u2BlockId;
            CanceledJobId = JobInfo.u4JobId;
            NvM_Adb_SetErrorStatus( CanceledBlockId, CanceledJobId, NVM_REQ_CANCELED );
            CancelJobsResult = E_OK;
        }

    }

    return CancelJobsResult;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_DestructiveCancelJobs                           */
/* Description   | Function to destructively cancel a executing job.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
/* Check 1st argument's value */
#if( NVM_JOBM_DSTRCTV_CXL_PREEMPTION     != NVM_JOB_DSTRCTV_CXL_PREEMPTION )
    #error "NVM_JOBM_DSTRCTV_CXL_PREEMPTION != NVM_JOB_DSTRCTV_CXL_PREEMPTION"
#endif
#if( NVM_JOBM_DSTRCTV_CXL_TIMEOUT    != NVM_JOB_DSTRCTV_CXL_TIMEOUT )
    #error "NVM_JOBM_DSTRCTV_CXL_TIMEOUT != NVM_JOB_DSTRCTV_CXL_TIMEOUT"
#endif
FUNC( void, NVM_CODE )
NvM_Jobm_DestructiveCancelJobs( uint8 Kind )
{
    NvM_Job_DestructiveCancelJob( Kind );
    
    return ;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_AbortJobs                                       */
/* Description   | Function to destructively abort all jobs pending.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_AbortJobs( void )
{
    NvM_Job_StatusType           JobStatus;
    NvM_Jobm_stJobInfomationType CurrentJobInfo;

    JobStatus = NvM_Job_GetStatus( &CurrentJobInfo );
    if( JobStatus != (NvM_Job_StatusType)NVM_JOB_IDLE )
    {
        NvM_Jobm_ExecBlockId = CurrentJobInfo.u2BlockId;
    }
    else
    {
        NvM_Jobm_ExecBlockId = NVM_BLOCKID_INVALID;
    }

    NvM_Jobq_Abort();

    if( JobStatus != (NvM_Job_StatusType)NVM_JOB_IDLE )
    {
        /* Functions, "NvM_Jobq_MultiEnqueue" and "NvM_Jobq_SglEnqueue", always return E_OK here.   */
        /* This reason is below:                                                                    */
        /*      Queue overflow or JOBQ's RAM garbled doesn't occur after "NvM_Jobq_Abort",          */
        /*      because JOBQ is initialized completely.                                             */
        /*      Which means that these functions don't return E_NOT_OK.                             */
        if( CurrentJobInfo.u2BlockId == (NvM_BlockIdType)NVM_RESERVED_BLOCKID_MULTIJOB )
        {
            (void)NvM_Jobq_MultiEnqueue( &CurrentJobInfo );
        }
        else
        {
            (void)NvM_Jobq_SglEnqueue( &CurrentJobInfo );
        }
    }

    NvM_Job_DestructiveCancelJob( NVM_JOB_DSTRCTV_CXL_USERREQUEST );

    return ;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_CancelWriteAll                                  */
/* Description   | Function to cancel a running WriteAll request.           */
/* Preconditions | Set NVM_VALID_CANCEL_WRITE_ALL_API to STD_ON.            */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Jobm_CancelWriteAll( void )
{
    Std_ReturnType GetJobInfoResult;
    NvM_Jobm_stJobInfomationType MultiJobInfo;
    uint32 MultiJobId;

    GetJobInfoResult = NvM_Jobq_MultiGetJobInfo( &MultiJobInfo );

    if( GetJobInfoResult == (Std_ReturnType)E_OK )
    {
        MultiJobId = MultiJobInfo.u4JobId;
        if( MultiJobId == (uint32)NVM_JOB_WRITE_ALL )
        {
            NvM_Jobq_CxlWtAllEnqueue();
        }
    }

    return ;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Jobm_SingleBlockEndNotification                      */
/* Description   | Function to be used by the underlying unit to signal end */
/*               | of single block job.                                     */
/* Preconditions | None                                                     */
/* Parameters    | u2BlockId   : The block Id executed in underlying unit.  */
/*               | u4JobId     : Kind of the job executed in underlying     */
/*               |               unit.                                      */
/*               | u1JobResult : The result of the job executed in          */
/*               |               underlying unit.                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_SingleBlockEndNotification(
    NvM_BlockIdType u2BlockId,
    uint32 u4JobId,
    uint8 u1JobResult
){
    Std_ReturnType DequeueResult;
    NvM_Jobm_stJobInfomationType JobInfo;
    NvM_RequestResultType NoticeResult;
    NvM_BlockIdType DequeuedBlockId;
    uint32 DequeuedJobId;

    if ( u1JobResult != (uint8)NVM_JOB_REQ_CANCELED_PREEMPTION )
    {
        DequeueResult = NvM_Jobq_SglDequeue( u2BlockId, u4JobId, &JobInfo );
        if( DequeueResult == (Std_ReturnType)E_OK )
        {
            DequeuedBlockId = JobInfo.u2BlockId;
            DequeuedJobId = JobInfo.u4JobId;
            NoticeResult = NvM_Jobm_NvbResultToReqResult( u1JobResult );
            NvM_Adb_SetErrorStatus( DequeuedBlockId, DequeuedJobId, NoticeResult );
            NvM_Evt_JobEnd( u2BlockId, u4JobId );
        }
    }
    NvM_WdtExt_WatchDogEnd( NVM_WDTEXT_ID_NVM );

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_MultiBlockEndNotification                       */
/* Description   | Function to be used by the underlying unit to signal end */
/*               | of multi block job.                                      */
/* Preconditions | None                                                     */
/* Parameters    | u4JobId     : Kind of the job executed in underlying     */
/*               |               unit.                                      */
/*               | u1JobResult : The result of the job executed in          */
/*               |               underlying unit.                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_MultiBlockEndNotification(
    uint32 u4JobId,
    uint8 u1JobResult
){
    NvM_RequestResultType NoticeResult;

    if ( u1JobResult != (uint8)NVM_JOB_REQ_CANCELED_PREEMPTION )
    {
        NvM_Jobq_MultiDequeue();
        NvM_Jobq_CxlWtAllDequeue();
        NoticeResult = NvM_Jobm_NvbResultToReqResult( u1JobResult );
        NvM_Adb_SetErrorStatus( NVM_RESERVED_BLOCKID_MULTIJOB, u4JobId, NoticeResult );
        NvM_Evt_JobEnd( NVM_RESERVED_BLOCKID_MULTIJOB, u4JobId );
    }
    NvM_WdtExt_WatchDogEnd( NVM_WDTEXT_ID_NVM );

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_NfyIsSglBlkProcStart                            */
/* Description   | Function to be used by the underlying unit to signal     */
/*               | that a job is start status or wait status.               */
/* Preconditions | None                                                     */
/* Parameters    | IsStart : TRUE  : A job started.                         */
/*               |           FALSE : A job is waiting.                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_NfyIsSglBlkProcStart(
    boolean IsStart
){
    uint32 TimeoutValue;

    if( (boolean)TRUE == IsStart )
    {
        TimeoutValue = NVM_JOBM_TIMEOUT_VALUE_START;
    }
    else
    {
        TimeoutValue = NVM_JOBM_TIMEOUT_VALUE_WAIT;
    }
    NvM_WdtExt_WatchDogStart( NVM_WDTEXT_ID_NVM, TimeoutValue );

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_NfyAbortJob                                     */
/* Description   | Function to be used by the underlying unit to signal     */
/*               | that a job abort in queue.                               */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : Aborted block Id.                              */
/*               | JobId   : Aborted job Id.                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_NfyAbortJob(
    NvM_BlockIdType BlockId,
    uint32 JobId
){
    if( NvM_Jobm_ExecBlockId != BlockId )
    {
#if ( NVM_USE_CANCEL_NOTIFICATION == STD_ON )
        NvM_Adb_SetErrorStatus( BlockId, JobId, NVM_REQ_CANCELED );
#else /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */
        NvM_Adb_SetErrorStatusNonNotification( BlockId, NVM_REQ_CANCELED );
#endif /* NVM_USE_CANCEL_NOTIFICATION */
    }
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Jobm_SubMainfuncJobIdle                              */
/* Description   | Function for performing the processing of the jobs when  */
/*               | the underlying unit status is idle.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobIdle( void )
{
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    Std_ReturnType CxlWtAllChkResult;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */
    Std_ReturnType u1Result;
    NvM_Jobm_stJobInfomationType stRequestJobInfo;

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    /* Execute CancelWriteAll */
    CxlWtAllChkResult = NvM_Jobq_CxlWtAllGetJobInfo();
    if( CxlWtAllChkResult == (Std_ReturnType)E_OK )
    {
        NvM_Jobm_CancelPreExecWtAll();
    }
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

    /* Get request job. */
    u1Result = NvM_Jobq_SglGetJobInfo( &stRequestJobInfo );
    if( u1Result != (Std_ReturnType)E_OK )
    {
        u1Result = NvM_Jobq_MultiGetJobInfo( &stRequestJobInfo );
    }

    /* Request job */
    if( u1Result == (Std_ReturnType)E_OK )
    {
        /* The function "NvM_Job_RequestJob" always returns E_OK here.                                              */
        /* This reason is below:                                                                                    */
        /*   1 When the state of JOB unit is not idle, funtion "NvM_Job_RequestJob" returns E_NOT_OK.               */
        /*   2 Before here is passed, the state of JOB unit has been checked at function "NvM_Jobm_MainFunction".   */
        /*     When the result of check is idle, function "NvM_Jobm_SubMainfuncJobIdle" is called.                  */
        (void)NvM_Job_RequestJob( &stRequestJobInfo );
        NvM_WdtExt_WatchDogStart( NVM_WDTEXT_ID_NVM, NVM_JOBM_TIMEOUT_VALUE_WAIT );
        NvM_Evt_JobStart( stRequestJobInfo.u2BlockId, stRequestJobInfo.u4JobId);
    }
    else
    {
        NvM_Adb_CheckRamError();
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_SubMainfuncJobBusyCxl                           */
/* Description   | Function for performing the processing of the jobs when  */
/*               | the underlying unit status is busy cancel.               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobBusyCxl(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
){
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    Std_ReturnType CxlWtAllChkResult;
    uint32 CurrentJobId;

    CxlWtAllChkResult = NvM_Jobq_CxlWtAllGetJobInfo();

    if( CxlWtAllChkResult == (Std_ReturnType)E_OK )
    {
        CurrentJobId = CurrentJobInfo->u4JobId;
        if( CurrentJobId != (uint32)NVM_JOB_WRITE_ALL )
        {
            NvM_Jobm_CancelPreExecWtAll();
        }
    }
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_SubMainfuncJobBusy                              */
/* Description   | Function for performing the processing of the jobs when  */
/*               | the underlying unit status is busy.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobBusy(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
){
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    Std_ReturnType CxlWtAllChkResult;
    uint32 CurrentJobId;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */
    boolean ChkCxlForImmWtResult;

    /* Destructive cancel for immediately write */
    ChkCxlForImmWtResult = NvM_Jobm_ChkCancelForImmWrite( CurrentJobInfo );
    if( (boolean)TRUE == ChkCxlForImmWtResult )
    {
        NvM_Job_DestructiveCancelJob( NVM_JOB_DSTRCTV_CXL_PREEMPTION );
    }
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    else
    {
        /* Cancel WriteAll */
        CxlWtAllChkResult = NvM_Jobq_CxlWtAllGetJobInfo();
        if( CxlWtAllChkResult == (Std_ReturnType)E_OK )
        {
            CurrentJobId = CurrentJobInfo->u4JobId;
            if( CurrentJobId == (uint32)NVM_JOB_WRITE_ALL )
            {
                NvM_Job_CancelJob();
            }
            else
            {
                NvM_Jobm_CancelPreExecWtAll();
            }
        }
    }
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_ChkCancelForImmWrite                            */
/* Description   | Function to check whether to cancel underlying unit for  */
/*               | immediate writing.                                       */
/* Preconditions | None                                                     */
/* Parameters    | CurrentJobInfo : Job executing on underlying unit.       */
/* Return Value  | TRUE  : It is necessary to cancel.                       */
/*               | FALSE : It is not necessary to cancel.                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Jobm_ChkCancelForImmWrite(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
){

    NvM_Jobm_stJobInfomationType stRequestJobInfo;
    Std_ReturnType SglGetImmInfoResult;
    boolean ChkImmJobResult;
    boolean Rtn = FALSE;

    SglGetImmInfoResult = NvM_Jobq_SglGetJobInfoSrchImm( &stRequestJobInfo );
    if( (Std_ReturnType)E_OK == SglGetImmInfoResult )
    {
        ChkImmJobResult = NvM_Jobq_ChkImmJob( CurrentJobInfo -> u2BlockId, CurrentJobInfo -> u4JobId );
        if( (boolean)TRUE != ChkImmJobResult )
        {
            Rtn = TRUE;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_NvbResultToReqResult                            */
/* Description   | Function to convert from result of underlying unit to    */
/*               | RequestResultType.                                       */
/* Preconditions | None                                                     */
/* Parameters    | JobResult         : The result of underlying unit        */
/* Return Value  | RequestResultType : See NvM_RequestResultType            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_RequestResultType, NVM_CODE )
NvM_Jobm_NvbResultToReqResult(
    uint8 JobResult
){
    NvM_RequestResultType Rtn;

    /* Notice result decision */
    if( JobResult == (uint8)NVM_JOB_REQ_CANCELED_TIMEOUT )
    {
        Rtn = NVM_REQ_NOT_OK;
    }
    else if( JobResult == (uint8)NVM_JOB_REQ_CANCELED_USERREQUEST)
    {
        Rtn = NVM_REQ_CANCELED;
    }
    else
    {
        Rtn = JobResult;
    }
    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_IsReqBlockExecuting                             */
/* Description   | Function to judge whether requested block is currently   */
/*               | executing or not.                                        */
/* Preconditions | None                                                     */
/* Parameters    | ReqBlockId : The block identifier uniquely identifies    */
/*               |              one NVRAM block descriptor.                 */
/* Return Value  | TRUE: Requested block is currently executing.            */
/*               | FALSE: Requested block is not currently executing.       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Jobm_IsReqBlockExecuting(
    NvM_BlockIdType ReqBlockId
){
    boolean JudgeResult = FALSE;
    NvM_Job_StatusType CurrentJobChkResult;
    NvM_Jobm_stJobInfomationType CurrentJobInfo;
    NvM_BlockIdType CurrentBlockId;

    CurrentJobChkResult = NvM_Job_GetStatus( &CurrentJobInfo );

    if(( CurrentJobChkResult == (NvM_Job_StatusType)NVM_JOB_BUSY )
    || ( CurrentJobChkResult == (NvM_Job_StatusType)NVM_JOB_BUSY_CANCEL ))
    {
        CurrentBlockId = CurrentJobInfo.u2BlockId;
        if( CurrentBlockId == ReqBlockId )
        {
            JudgeResult = TRUE;
        }
    }

    return JudgeResult;
}

/****************************************************************************/
/* Function Name | NvM_Jobm_CancelPreExecWtAll                              */
/* Description   | Function to cancel pre-execute write all job.            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Jobm_CancelPreExecWtAll( void )
{

    NvM_Jobq_MultiDequeue();
    NvM_Jobq_CxlWtAllDequeue();
    NvM_Adb_SetErrorStatus( NVM_RESERVED_BLOCKID_MULTIJOB, NVM_JOB_WRITE_ALL, NVM_REQ_CANCELED );

    return;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2020/11/30                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
