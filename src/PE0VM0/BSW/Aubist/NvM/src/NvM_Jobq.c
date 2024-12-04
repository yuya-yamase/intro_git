/* NvM_Jobq.c v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBQ/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Jobq.h"
#include "../inc/NvM_Jobq_Internal.h"
#include "../inc/NvM_Evt.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/* Single block job queue */
VAR( NvM_Jobq_SglJobQueueElemType,   NVM_VAR_NO_INIT )   NvM_Jobq_SglJobQueueElem[NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE];
VAR( NvM_Jobq_SglJobMgtQueueType,    NVM_VAR_NO_INIT )   NvM_Jobq_SglJobMgtQueue[NVM_JOBQ_MGT_QUEUE_NUM];
VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumImmUnuse;
VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumStdUnuse;
VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumImmUse;
VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumStdUse;

/* Multi block job queue */
VAR( NvM_Jobm_stJobInfomationType,   NVM_VAR_NO_INIT )   NvM_Jobq_MultiJobQueue;
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
VAR( uint32,                         NVM_VAR_NO_INIT )   NvM_Jobq_CxlWtAllQueue;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Jobq_Init                                            */
/* Description   | Service to initialize the JOBQ unit.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE ) NvM_Jobq_Init( void )
{
    NvM_Jobq_InitSglQueue( FALSE );
    NvM_Jobq_InitMultiQueue( FALSE );

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_Abort                                           */
/* Description   | Service to abort the JOBQ unit.                          */
/*               | This function initializes queues, and notifies.          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_Abort( void )
{
    NvM_Jobq_InitSglQueue( TRUE );
    NvM_Jobq_InitMultiQueue( TRUE );

    return;
}


/****************************************************************************/
/* Function Name | NvM_Jobq_SglQueueIsNotEmpty                              */
/* Description   | This function checks the number of requested jobs        */
/*               | is not zero.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/*               |  TRUE  : The number of requested jobs is zero.           */
/*               |  FALSE : The number of requested jobs is not zero.       */
/* Notes         | If two RAMs, the number of requested jobs,  don't match, */
/*               | this function returns FALSE.                             */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Jobq_SglQueueIsNotEmpty( void )
{
    boolean Rtn                  = FALSE;
    uint16  QueueElemNumImmUse   = NvM_Jobq_SglJobElemNumImmUse;
    uint16  QueueElemNumStdUse   = NvM_Jobq_SglJobElemNumStdUse;
    uint16  QueueElemNumImm;
    uint16  QueueElemNumStd;
    uint16  EnqueueElemNum;

    QueueElemNumImm = NvM_Jobq_SglJobElemNumImmUnuse + QueueElemNumImmUse;
    QueueElemNumStd = NvM_Jobq_SglJobElemNumStdUnuse + QueueElemNumStdUse;

    if(( QueueElemNumImm == (uint16)NVM_SIZE_IMMEDIATE_JOB_QUEUE )
    && ( QueueElemNumStd == (uint16)NVM_SIZE_STANDARD_JOB_QUEUE ))
    {
        EnqueueElemNum = QueueElemNumImmUse + QueueElemNumStdUse;
        if( EnqueueElemNum > (uint16)NVM_JOBQ_QUEUE_ELEM_NUM_ZERO )
        {
            Rtn = TRUE;
        }
    }
    else
    {
        /* Ram garbled */
        NvM_Evt_FatalFailedNotification();
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglGetJobInfo                                   */
/* Description   | Service to get job information out of the queue.         */
/* Preconditions | None                                                     */
/* Parameters    | DstJobInfo : The job information in the top of           */
/*               |              the single block queue.                     */
/* Return Value  | Result                                                   */
/*               |      E_OK   : A job information is found.                */
/*               |      E_NOTOK: A job information is not found.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfo(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn                  = E_NOT_OK;
    Std_ReturnType  GetResult;
    boolean         EnqueueChkResult;
    uint16          SrchNum;
    uint32          DstJobId;

    EnqueueChkResult = NvM_Jobq_SglQueueIsNotEmpty();
    if( EnqueueChkResult == (boolean)TRUE )
    {
        SrchNum = NVM_JOBQ_KIND_NUM_IMM_USE + NVM_JOBQ_KIND_NUM_STD_USE;
        GetResult = NvM_Jobq_SglGetJobInfoSub( NVM_JOBQ_KIND_IMM_USE, NVM_PRIORITY_IMMEDIATE, SrchNum, DstJobInfo );

        if( GetResult == (Std_ReturnType)E_OK )
        {
            DstJobId = DstJobInfo -> u4JobId;
            if(( DstJobId == (uint32)NVM_JOB_READ_BLOCK )
            || ( DstJobId == (uint32)NVM_JOB_WRITE_BLOCK )
            || ( DstJobId == (uint32)NVM_JOB_RESTORE_BLOCK_DEFAULTS )
            || ( DstJobId == (uint32)NVM_JOB_READ_PRAM_BLOCK )
            || ( DstJobId == (uint32)NVM_JOB_WRITE_PRAM_BLOCK )
            || ( DstJobId == (uint32)NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS ))
            {
                Rtn = E_OK;
            }
        }

        if( Rtn != (Std_ReturnType)E_OK )
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglGetJobInfoSrchImm                            */
/* Description   | Service to get job information out of the queue.         */
/*               | This function searches the immediate queue only.         */
/* Preconditions | None                                                     */
/* Parameters    | DstJobInfo  : The job information in the top of          */
/*               |               the single block queue.                    */
/* Return Value  | Result                                                   */
/*               |      E_OK   : A job information is found.                */
/*               |      E_NOTOK: A job information is not found.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfoSrchImm(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn                  = E_NOT_OK;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    Std_ReturnType  GetResult;
    boolean         EnqueueChkResult;
    boolean         ImmJobChkResult;

    EnqueueChkResult = NvM_Jobq_SglQueueIsNotEmpty();
    if( EnqueueChkResult == (boolean)TRUE )
    {
        GetResult = NvM_Jobq_SglGetJobInfoSub( NVM_JOBQ_KIND_IMM_USE, NVM_PRIORITY_IMMEDIATE, NVM_JOBQ_KIND_NUM_IMM_USE, DstJobInfo );
        if( GetResult == (Std_ReturnType)E_OK )
        {
            ImmJobChkResult = NvM_Jobq_ChkImmJob( DstJobInfo -> u2BlockId, DstJobInfo -> u4JobId );
            if( ImmJobChkResult == (boolean)TRUE )
            {
                Rtn = E_OK;
            }
            else
            {
                /* Ram garbled */
                NvM_Evt_FatalFailedNotification();
            }
        }
    }
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglEnqueue                                      */
/* Description   | Service to enqueue the job information to                */
/*               | the single block queue.                                  */
/* Preconditions | None                                                     */
/* Parameters    | SrcJobInfo : A job Information to enqueue in             */
/*               |              the single block queue.                     */
/* Return Value  | Result                                                   */
/*               |      E_OK     : Enqueue is successful.                   */
/*               |      E_NOT_OK : Enqueue is failure.                      */
/*               |                 Queue is overflow or RAM garbled.        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglEnqueue(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) SrcJobInfo
){
    Std_ReturnType  Rtn             = E_NOT_OK;
    Std_ReturnType  RemoveResult;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    boolean         IsImmJob;
    uint32          TgtJobId        = SrcJobInfo -> u4JobId;
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */
    uint16          EnQueueKind;
    uint16          DeQueueKind;
    uint16          EnQueueKindIdx;
    uint16          DeQueueKindIdx;
    uint16          MgtEnQueueIdx;
    uint16          MgtDeQueueIdx;
    uint16          QueueElemIdx    = NVM_JOBQ_QUEUE_INVALID_IDX;
    NvM_BlockIdType TgtBlockId      = SrcJobInfo -> u2BlockId;
    /* NvM_Jobq_SglEnqueue_INT30_001 */ 
    /* Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUnusePtr;
    /* NvM_Jobq_SglEnqueue_INT30_002 */ 
    /* Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUsePtr;

    /* Decides queue kind for queuing. */
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    IsImmJob = NvM_Jobq_ChkImmJob( TgtBlockId, TgtJobId );
    if( IsImmJob == (boolean)TRUE )
    {
        DeQueueKind    = NVM_JOBQ_KIND_IMM_UNUSE;
        DeQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        EnQueueKind    = NVM_JOBQ_KIND_IMM_USE;
        EnQueueKindIdx = NVM_PRIORITY_IMMEDIATE;
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumImmUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumImmUse;
    }
    else
    {
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */
        DeQueueKind    = NVM_JOBQ_KIND_STD_UNUSE;
        DeQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        EnQueueKind    = NVM_JOBQ_KIND_STD_USE;
        EnQueueKindIdx = NvM_Jobq_GetBlockIdJobPriority( TgtBlockId );
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumStdUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumStdUse;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    }
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */

    /* Dequeues from an unuse queue. */
    MgtDeQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( DeQueueKind, DeQueueKindIdx );
    RemoveResult = NvM_Jobq_SglMgtRemoveHead( MgtDeQueueIdx, &QueueElemIdx );

    if( RemoveResult == (Std_ReturnType)E_OK )
    {
        if( NvM_Jobq_SglJobQueueElem[QueueElemIdx].JobId == (uint32)NVM_JOB_NON )
        {
            /* Copies data and enqueues to an use queue. */
            MgtEnQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( EnQueueKind, EnQueueKindIdx );
            Rtn = NvM_Jobq_SglEnqueueSubAddUse( MgtEnQueueIdx, QueueElemIdx, SrcJobInfo );

            if( Rtn == (Std_ReturnType)E_OK )
            {
                /* NvM_Jobq_SglEnqueue_INT30_001 */
                /* Wraparound may occur due to garbled RAM. */
                /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
                (*JobElemNumUnusePtr)--;
                /* NvM_Jobq_SglEnqueue_INT30_002 */
                /* Wraparound may occur due to garbled RAM. */
                /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
                (*JobElemNumUsePtr)++;
            }
        }
        else
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }
    else
    {
        if( (*JobElemNumUnusePtr) != (uint16)NVM_JOBQ_QUEUE_ELEM_NUM_ZERO )
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglDequeue                                      */
/* Description   | Service to dequeue the job information from              */
/*               | the single block queue.                                  */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockId : BlockID of request infomation to be dequeue.*/
/*               | SrcJobId   : JobID of request infomation to be dequeue.  */
/*               | DstJobInfo : A dequeued job Information.                 */
/* Return Value  | Result                                                   */
/*               |      E_OK     : Dequeue is successful.                   */
/*               |      E_NOT_OK : Dequeue is failure.                      */
/*               |                 RAM garbled.                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeue(
    NvM_BlockIdType SrcBlockId,
    uint32          SrcJobId,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn             = E_NOT_OK;
    Std_ReturnType  RemoveResult;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    boolean         IsImmJob;
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */
    uint16          EnQueueKind;
    uint16          DeQueueKind;
    uint16          EnQueueKindIdx;
    uint16          DeQueueKindIdx;
    uint16          MgtEnQueueIdx;
    uint16          MgtDeQueueIdx;
    uint16          QueueElemIdx    = NVM_JOBQ_QUEUE_INVALID_IDX;
    /* NvM_Jobq_SglDequeue_INT30_001 */ 
    /* Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUnusePtr;
    /* NvM_Jobq_SglDequeue_INT30_002 */
    /* Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUsePtr;

    /* Decides queue kind for queuing. */
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    IsImmJob = NvM_Jobq_ChkImmJob( SrcBlockId, SrcJobId );
    if( IsImmJob == (boolean)TRUE )
    {
        DeQueueKind    = NVM_JOBQ_KIND_IMM_USE;
        DeQueueKindIdx = NVM_PRIORITY_IMMEDIATE;
        EnQueueKind    = NVM_JOBQ_KIND_IMM_UNUSE;
        EnQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumImmUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumImmUse;
    }
    else
    {
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */
        DeQueueKind    = NVM_JOBQ_KIND_STD_USE;
        DeQueueKindIdx = NvM_Jobq_GetBlockIdJobPriority( SrcBlockId );
        EnQueueKind    = NVM_JOBQ_KIND_STD_UNUSE;
        EnQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumStdUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumStdUse;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    }
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */

    /* Dequeues from an use queue. */
    MgtDeQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( DeQueueKind, DeQueueKindIdx );
    RemoveResult = NvM_Jobq_SglMgtRemoveHead( MgtDeQueueIdx, &QueueElemIdx );

    if( RemoveResult == (Std_ReturnType)E_OK )
    {
        if( SrcBlockId == NvM_Jobq_SglJobQueueElem[QueueElemIdx].BlockId )
        {
            /* Enqueues to an unuse queue. */
            MgtEnQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( EnQueueKind, EnQueueKindIdx );
            Rtn = NvM_Jobq_SglDequeueSubAddUnuse( MgtEnQueueIdx, QueueElemIdx, DstJobInfo );

            if( Rtn == (Std_ReturnType)E_OK )
            {
                /* NvM_Jobq_SglDequeue_INT30_001 */
                /* Wraparound may occur due to garbled RAM. */
                /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
                (*JobElemNumUnusePtr)++;
                /* NvM_Jobq_SglDequeue_INT30_002 */
                /* Wraparound may occur due to garbled RAM. */
                /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
                (*JobElemNumUsePtr)--;
            }
        }
        else
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglDequeueSrchBlockId                           */
/* Description   | Service to queueing.                                     */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockId : BlockID of request infomation to be dequeue.*/
/*               | DstJobInfo : Output dequeued job Information.            */
/* Return Value  | Result                                                   */
/*               |      E_OK     : Dequeue is successful.                   */
/*               |      E_NOT_OK : Dequeue is failure.                      */
/*               |                 RAM garbled.                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeueSrchBlockId(
    NvM_BlockIdType SrcBlockId,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn             = E_NOT_OK;
    Std_ReturnType  RemoveResult;
    uint16          Priority;
    uint16          EnQueueKind;
    uint16          EnQueueKindIdx;
    uint16          MgtEnQueueIdx;
    uint16          MgtDeQueueIdx;
    uint16          QueueElemIdx    = NVM_JOBQ_QUEUE_INVALID_IDX;
    /* NvM_Jobq_SglDequeueSrchBlockId_INT30_001 */ 
    /*  Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUnusePtr;
    /* NvM_Jobq_SglDequeueSrchBlockId_INT30_002 */ 
    /* Wraparound may occur */
    P2VAR( uint16, AUTOMATIC, NVM_VAR_NO_INIT ) JobElemNumUsePtr;

#if( NVM_JOB_PRIORITIZATION == STD_ON )
    RemoveResult = E_NOT_OK;

    /* Decides necessity to dequeue from the immediate queue, and dequeues. */
    Priority = NvM_Jobq_GetBlockIdJobPriority( SrcBlockId );
    if( Priority == (uint8)NVM_PRIORITY_IMMEDIATE )
    {
        MgtDeQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( NVM_JOBQ_KIND_IMM_USE, NVM_PRIORITY_IMMEDIATE );
        RemoveResult = NvM_Jobq_SglMgtRemoveSrch( SrcBlockId, MgtDeQueueIdx, &QueueElemIdx );

        EnQueueKind    = NVM_JOBQ_KIND_IMM_UNUSE;
        EnQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumImmUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumImmUse;
    }
#else  /* NVM_JOB_PRIORITIZATION != STD_ON */
    Priority = NVM_JOBQ_NON_PRIORITY_VALUE;
#endif /* NVM_JOB_PRIORITIZATION */

#if( NVM_JOB_PRIORITIZATION == STD_ON )
    /* Dequeues from the standard queue. */
    if( RemoveResult != (Std_ReturnType)E_OK )
    {
#endif /* NVM_JOB_PRIORITIZATION */
        MgtDeQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( NVM_JOBQ_KIND_STD_USE, Priority );
        RemoveResult = NvM_Jobq_SglMgtRemoveSrch( SrcBlockId, MgtDeQueueIdx, &QueueElemIdx );

        EnQueueKind    = NVM_JOBQ_KIND_STD_UNUSE;
        EnQueueKindIdx = NVM_JOBQ_KINDIDX_ZERO;
        JobElemNumUnusePtr = &NvM_Jobq_SglJobElemNumStdUnuse;
        JobElemNumUsePtr   = &NvM_Jobq_SglJobElemNumStdUse;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    }
#endif /* NVM_JOB_PRIORITIZATION */

    if( ( RemoveResult == (Std_ReturnType)E_OK ) && ( QueueElemIdx < (uint16)NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE ) )
    {
        /* Enqueues to an unuse queue. */
        MgtEnQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( EnQueueKind, EnQueueKindIdx );
        Rtn = NvM_Jobq_SglDequeueSubAddUnuse( MgtEnQueueIdx, QueueElemIdx, DstJobInfo );

        if( Rtn == (Std_ReturnType)E_OK )
        {
            /* NvM_Jobq_SglDequeueSrchBlockId_INT30_001 */
            /* Wraparound may occur due to garbled RAM. */
            /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
            (*JobElemNumUnusePtr)++;
            /* NvM_Jobq_SglDequeueSrchBlockId_INT30_002 */
            /* Wraparound may occur due to garbled RAM. */
            /* However, safety is ensured because it is checked whether the data is valid at the time of reading. */
            (*JobElemNumUsePtr)--;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_MultiGetJobInfo                                 */
/* Description   | Service to queueing.                                     */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | Result                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_MultiGetJobInfo(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) JobInfo
){
    Std_ReturnType u1Rtn = E_NOT_OK;

    if( (uint32)NVM_JOB_NON != NvM_Jobq_MultiJobQueue.u4JobId )
    {
        JobInfo -> u4JobId   = NvM_Jobq_MultiJobQueue.u4JobId;
        JobInfo -> u2BlockId = NvM_Jobq_MultiJobQueue.u2BlockId;
        JobInfo -> ptDstPtr  = NvM_Jobq_MultiJobQueue.ptDstPtr;
        JobInfo -> ptSrcPtr  = NvM_Jobq_MultiJobQueue.ptSrcPtr;

        u1Rtn = E_OK;
    }

    return u1Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_MultiEnqueue                                    */
/* Description   | Service to queueing.                                     */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | Result                                                   */
/*               |      E_OK     : Enqueue is successful.                   */
/*               |      E_NOT_OK : Enqueue is failure. Queue is overflow.   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_MultiEnqueue(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) JobInfo
){
    Std_ReturnType u1Rtn = E_NOT_OK;

    if( (uint32)NVM_JOB_NON == NvM_Jobq_MultiJobQueue.u4JobId )
    {
        NvM_Jobq_MultiJobQueue.u4JobId   = JobInfo -> u4JobId;
        NvM_Jobq_MultiJobQueue.u2BlockId = JobInfo -> u2BlockId;
        NvM_Jobq_MultiJobQueue.ptDstPtr  = JobInfo -> ptDstPtr;
        NvM_Jobq_MultiJobQueue.ptSrcPtr  = JobInfo -> ptSrcPtr;

        u1Rtn = E_OK;
    }

    return u1Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_MultiDequeue                                    */
/* Description   | Service to queueing.                                     */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_MultiDequeue( void )
{
    NvM_Jobq_MultiJobQueue.u4JobId    = NVM_JOB_NON;
    NvM_Jobq_MultiJobQueue.u2BlockId  = NVM_BLOCKID_INVALID;
    NvM_Jobq_MultiJobQueue.ptDstPtr   = NULL_PTR;
    NvM_Jobq_MultiJobQueue.ptSrcPtr   = NULL_PTR;

    return;
}

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Jobq_CxlWtAllGetJobInfo                         */
/* Description   | Service to provide "Cancel WriteAll" request infomation. */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | Result                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_CxlWtAllGetJobInfo( void )
{
    Std_ReturnType rtn = E_NOT_OK;
    
    if( NvM_Jobq_CxlWtAllQueue == (uint32)NVM_JOB_CANCEL_WRITE_ALL )
    {
        rtn = E_OK;
    }
    return rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_CxlWtAllEnqueue                                 */
/* Description   | Service to enqueue "Cancel WriteAll" request.            */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | Result                                                   */
/*               |      E_OK     : Enqueue is successful.                   */
/*               |      E_NOT_OK : Enqueue is failure. Queue is overflow.   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_CxlWtAllEnqueue( void )
{

    NvM_Jobq_CxlWtAllQueue = NVM_JOB_CANCEL_WRITE_ALL;

    return;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Jobq_CxlWtAllDequeue                                 */
/* Description   | Service to dequeue "Cancel WriteAll" request.            */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_CxlWtAllDequeue( void )
{
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    NvM_Jobq_CxlWtAllQueue = NVM_JOB_NON;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */
    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_ChkImmJob                                       */
/* Description   | Service to check whether the job is immediate write.     */
/* Preconditions | None                                                     */
/* Parameters    | JobInfo : Check target job information.                  */
/* Return Value  | Result                                                   */
/*               |      TRUE  : JobInfo's job is immediate write job.       */
/*               |      FALSE : JobInfo's job is not immediate write job.   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Jobq_ChkImmJob(
    NvM_BlockIdType BlockId,
    uint32          JobId
){
    boolean Rtn = FALSE;
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    uint8 BlockJobPriority = NvMBlockDescriptors[BlockId].NvMBlockJobPriority;

    if( (uint8)NVM_PRIORITY_IMMEDIATE == BlockJobPriority )
    {
        if(( (uint32)NVM_JOB_WRITE_BLOCK      == JobId )
        || ( (uint32)NVM_JOB_WRITE_PRAM_BLOCK == JobId ))
        {
            Rtn = TRUE;
        }
    }
#endif /* NVM_JOB_PRIORITIZATION == STD_ON */

    return Rtn;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Jobq_InitSglQueue                                    */
/* Description   | This function initializes the single block job queue.    */
/* Preconditions | None                                                     */
/* Parameters    | SrcIsAbortNfy: If this parameter is TRUE,                */
/*               |                this function notifies to other unit.     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_InitSglQueue(
    boolean SrcIsAbortNfy
){
    uint16 ImmMgtQueueIdx;
    uint16 StdMgtQueueIdx;

    /* Initializes all management queue */
    NvM_Jobq_InitSglMgtQueue();

    /* Initializes the unuse queue */
    ImmMgtQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( NVM_JOBQ_KIND_IMM_UNUSE, NVM_JOBQ_KINDIDX_ZERO );
    StdMgtQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( NVM_JOBQ_KIND_STD_UNUSE, NVM_JOBQ_KINDIDX_ZERO );
    if( SrcIsAbortNfy == (boolean)TRUE )
    {
        NvM_Jobq_InitAndNfySglQueueElem( ImmMgtQueueIdx, NVM_JOBQ_IMM_ELEM_TOP_IDX, NVM_JOBQ_IMM_ELEM_LAST_IDX );
        NvM_Jobq_InitAndNfySglQueueElem( StdMgtQueueIdx, NVM_JOBQ_STD_ELEM_TOP_IDX, NVM_JOBQ_STD_ELEM_LAST_IDX );
    }
    else
    {
        NvM_Jobq_InitSglQueueElem( ImmMgtQueueIdx, NVM_JOBQ_IMM_ELEM_TOP_IDX, NVM_JOBQ_IMM_ELEM_LAST_IDX );
        NvM_Jobq_InitSglQueueElem( StdMgtQueueIdx, NVM_JOBQ_STD_ELEM_TOP_IDX, NVM_JOBQ_STD_ELEM_LAST_IDX );
    }

    /* Initializes element num of each queue kind */
    NvM_Jobq_SglJobElemNumImmUnuse = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
    NvM_Jobq_SglJobElemNumStdUnuse = NVM_SIZE_STANDARD_JOB_QUEUE;
    NvM_Jobq_SglJobElemNumImmUse   = NVM_JOBQ_QUEUE_ELEM_NUM_ZERO;
    NvM_Jobq_SglJobElemNumStdUse   = NVM_JOBQ_QUEUE_ELEM_NUM_ZERO;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_InitMultiQueue                                  */
/* Description   | This function initializes the multi block job queue      */
/*               | including CancelWriteAll queue.                          */
/* Preconditions | None                                                     */
/* Parameters    | SrcIsAbortNfy: If this parameter is TRUE,                */
/*               |                this function notifies to other unit.     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_InitMultiQueue(
    boolean SrcIsAbortNfy
){
    uint32 MultiJobId;
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, NVM_VAR_NO_INIT ) MultiJobInfo;

    /* Initializing multi job queue. */
    MultiJobInfo = &NvM_Jobq_MultiJobQueue;

    if( SrcIsAbortNfy == (boolean)TRUE )
    {
        MultiJobId = MultiJobInfo -> u4JobId;
        if( MultiJobId != (uint32)NVM_JOB_NON )
        {
            NvM_Jobm_NfyAbortJob( NVM_RESERVED_BLOCKID_MULTIJOB, MultiJobId );
        }
    }

    MultiJobInfo -> u4JobId    = NVM_JOB_NON;
    MultiJobInfo -> u2BlockId  = NVM_BLOCKID_INVALID;
    MultiJobInfo -> ptDstPtr   = NULL_PTR;
    MultiJobInfo -> ptSrcPtr   = NULL_PTR;
    
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    /* Initializing CancelWriteAll queue. */
    NvM_Jobq_CxlWtAllQueue = NVM_JOB_NON;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */
}

/****************************************************************************/
/* Function Name | NvM_Jobq_InitSglMgtQueue                                 */
/* Description   | This function initializes management queues.             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_InitSglMgtQueue( void )
{
    uint16 Counter;
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) SglQueueInfo;

    for( Counter = 0U; Counter < NVM_JOBQ_MGT_QUEUE_NUM; Counter++ )
    {
        SglQueueInfo = &NvM_Jobq_SglJobMgtQueue[Counter];
        SglQueueInfo -> FrontSideIdx = NVM_JOBQ_QUEUE_INVALID_IDX;
        SglQueueInfo -> TailSideIdx  = NVM_JOBQ_QUEUE_INVALID_IDX;
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_InitSglQueueElem                                */
/* Description   | This function initializes queue elememnts and            */
/*               | a management queue.                                      */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx      : A management queue of the          */
/*               |                       initialization target.             */
/*               | SrcQueueElemTopIdx  : The top index of elements          */
/*               |                       connecting with the mgt queue.     */
/*               | SrcQueueElemLastIdx : The last index of elements         */
/*               |                       connecting with the mgt queue.     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_InitSglQueueElem(
    uint16  SrcMgtQueueIdx,
    uint16  SrcQueueElemTopIdx,
    uint16  SrcQueueElemLastIdx
){
    uint16 Counter;
    P2VAR( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) SglJobQueueElem;
    P2VAR( NvM_Jobq_SglJobMgtQueueType,  AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    /* Initializes management queue. */
    TgtQueue -> FrontSideIdx = SrcQueueElemTopIdx;
    TgtQueue -> TailSideIdx  = SrcQueueElemLastIdx;

    /* Initializes queue elem. */
    for( Counter = SrcQueueElemTopIdx; Counter <= SrcQueueElemLastIdx; Counter++ )
    {
        SglJobQueueElem = &NvM_Jobq_SglJobQueueElem[Counter];
        
        /* Sets job information to empties. */
        SglJobQueueElem -> JobId    = NVM_JOB_NON;
        SglJobQueueElem -> DstPtr   = NULL_PTR;
        SglJobQueueElem -> SrcPtr   = NULL_PTR;
        SglJobQueueElem -> BlockId  = NVM_BLOCKID_INVALID;
        
        /* Sets next queue index. */
        SglJobQueueElem -> NextElementIndex = Counter + (uint16)NVM_JOBQ_QUEUE_INIT_REF_IDX_SIZE;
    }

    /* Sets last element to invalid value. */
    NvM_Jobq_SglJobQueueElem[SrcQueueElemLastIdx].NextElementIndex = (uint16)NVM_JOBQ_QUEUE_INVALID_IDX;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_InitAndNfySglQueueElem                          */
/* Description   | This function initializes queue elememnts and            */
/*               | a management queue. And notifies to other unit.          */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx      : A management queue of the          */
/*               |                       initialization target.             */
/*               | SrcQueueElemTopIdx  : The top index of elements          */
/*               |                       connecting with the mgt queue.     */
/*               | SrcQueueElemLastIdx : The last index of elements         */
/*               |                       connecting with the mgt queue.     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_InitAndNfySglQueueElem(
    uint16  SrcMgtQueueIdx,
    uint16  SrcQueueElemTopIdx,
    uint16  SrcQueueElemLastIdx
){
    uint16 Counter;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;
    NvM_BlockIdType QueueBlockId;
    uint32 QueueJobId;
    P2VAR( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) SglJobQueueElem;
    P2VAR( NvM_Jobq_SglJobMgtQueueType,  AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    /* Initializes management queue. */
    TgtQueue -> FrontSideIdx = SrcQueueElemTopIdx;
    TgtQueue -> TailSideIdx  = SrcQueueElemLastIdx;

    /* Initializes queue elem, and notifies to other unit. */
    for( Counter = SrcQueueElemTopIdx; Counter <= SrcQueueElemLastIdx; Counter++ )
    {
        SglJobQueueElem = &NvM_Jobq_SglJobQueueElem[Counter];
        QueueJobId = SglJobQueueElem -> JobId;
        
        /* Notifies to other unit */
        if( QueueJobId != (uint32)NVM_JOB_NON )
        {
            QueueBlockId = SglJobQueueElem -> BlockId;

            if(( QueueBlockId <= UserBlkIdMax )
            && ( QueueBlockId >= (NvM_BlockIdType)NVM_USER_BLOCKID_MIN ))
            {
                NvM_Jobm_NfyAbortJob( QueueBlockId, QueueJobId );
            }
            else
            {
                /* Ram garbled */
                NvM_Evt_FatalFailedNotification();
            }
        }
        
        /* Sets job information to empties. */
        SglJobQueueElem -> JobId    = NVM_JOB_NON;
        SglJobQueueElem -> DstPtr   = NULL_PTR;
        SglJobQueueElem -> SrcPtr   = NULL_PTR;
        SglJobQueueElem -> BlockId  = NVM_BLOCKID_INVALID;
        
        /* Sets next queue index. */
        SglJobQueueElem -> NextElementIndex = Counter + (uint16)NVM_JOBQ_QUEUE_INIT_REF_IDX_SIZE;
    }

    /* Sets last element to invalid value. */
    NvM_Jobq_SglJobQueueElem[SrcQueueElemLastIdx].NextElementIndex = (uint16)NVM_JOBQ_QUEUE_INVALID_IDX;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglGetJobInfoSub                                */
/* Description   | Sub function for NvM_Jobq_SglGetJobInfo.                 */
/*               | This function gets job information out of the queue.     */
/* Preconditions | None                                                     */
/* Parameters    | SrcStartQueueKind    : Search start queue kind.          */
/*               | SrcStartQueueKindIdx : Search start queue kind index.    */
/*               | SrcSrchMgtQueueNum   : Search num of management queue.   */
/*               | DstJobInfo           :The job information in the top of  */
/*               |                       the single block queue.            */
/* Return Value  | Result                                                   */
/*               |      E_OK   : A job information is found.                */
/*               |      E_NOTOK: A job information is not found.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfoSub(
    uint16  SrcStartQueueKind,
    uint16  SrcStartQueueKindIdx,
    uint16  SrcSrchMgtQueueNum,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn;
    uint16          QueueElemIdx         = NVM_JOBQ_QUEUE_INVALID_IDX;
    uint16          StartMgtQueueIdx;

    /* Searches immediate queues */
    StartMgtQueueIdx = NvM_Jobq_SglQueueKindToMgtIdx( SrcStartQueueKind, SrcStartQueueKindIdx );
    Rtn = NvM_Jobq_SglQueueGetJobInfo( StartMgtQueueIdx, SrcSrchMgtQueueNum, &QueueElemIdx );

    if( Rtn == (Std_ReturnType)E_OK )
    {
        /* Copies to output parameters */
        NvM_Jobq_CpyQueueElemToJobInfo( DstJobInfo, &NvM_Jobq_SglJobQueueElem[QueueElemIdx] );
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglEnqueueSubAddUse                             */
/* Description   | Sub function for NvM_Jobq_SglEnqueue.                    */
/*               | This function copies data and enqueues to an use queue.  */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx  : An index of a management queue         */
/*               | SrcQueueElemIdx : An index of a queue element            */
/*               | SrcJobInfo      : A job Information to enqueue in        */
/*               |                   the single block queue.                */
/* Return Value  | Execute result                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglEnqueueSubAddUse(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx,
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) SrcJobInfo
){
    Std_ReturnType Rtn;

    /* Enqueues to an use queue. */
    Rtn = NvM_Jobq_SglMgtAddTail( SrcMgtQueueIdx, SrcQueueElemIdx );

    if( Rtn == (Std_ReturnType)E_OK )
    {
        /* Sets job information. */
        NvM_Jobq_CpyJobInfoToQueueElem( &NvM_Jobq_SglJobQueueElem[SrcQueueElemIdx], SrcJobInfo );
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglDequeueSubAddUnuse                           */
/* Description   | Sub function for NvM_Jobq_SglEnqueue.                    */
/*               | This function enqueues to an unuse queue.                */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx  : An index of a management queue         */
/*               | SrcQueueElemIdx : An index of a queue element            */
/*               | DstJobInfo : A dequeued job Information.                 */
/* Return Value  | Execute result                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeueSubAddUnuse(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
){
    Std_ReturnType  Rtn;
    P2VAR( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) DequeueJobQueueElem;

    /* Enqueues to an unuse queue. */
    Rtn = NvM_Jobq_SglMgtAddTail( SrcMgtQueueIdx, SrcQueueElemIdx );

    if( Rtn == (Std_ReturnType)E_OK )
    {
        DequeueJobQueueElem = &NvM_Jobq_SglJobQueueElem[SrcQueueElemIdx];

        /* Gets job information */
        NvM_Jobq_CpyQueueElemToJobInfo( DstJobInfo, DequeueJobQueueElem );

        /* Sets(Initializes) job information */
        DequeueJobQueueElem -> JobId    = NVM_JOB_NON;
        DequeueJobQueueElem -> DstPtr   = NULL_PTR;
        DequeueJobQueueElem -> SrcPtr   = NULL_PTR;
        DequeueJobQueueElem -> BlockId  = NVM_BLOCKID_INVALID;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglQueueKindToMgtIdx                            */
/* Description   | This function calculates index of management queue array.*/
/* Preconditions | None                                                     */
/* Parameters    | SrcQueueKind    : Kind of the single block queue.        */
/*               | SrcQueueKindIdx : The relative index from SrcQueueKind.  */
/* Return Value  | The index of management queue array.                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint16, NVM_CODE )
NvM_Jobq_SglQueueKindToMgtIdx(
    uint16 SrcQueueKind,
    uint16 SrcQueueKindIdx
){
    return (SrcQueueKind + SrcQueueKindIdx);
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglQueueGetJobInfo                              */
/* Description   | This function gets the top index from queues.            */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx     : An index of a management queue.     */
/*               | SrcSrchMgtQueueNum : Number of size for searching.       */
/*               | DstQueueElemIdx    : The index which found queue elem.   */
/* Return Value  | Result                                                   */
/*               |      E_OK   : An index is found.                         */
/*               |      E_NOTOK: An index is not found.                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglQueueGetJobInfo(
    uint16 SrcMgtQueueIdx,
    uint16 SrcSrchMgtQueueNum,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
){
    Std_ReturnType  Rtn                = E_NOT_OK;
    Std_ReturnType  EachResult;
    boolean         IsFatalFailed;
    uint16          IdxCounter;
    uint16          CountEndCond       = SrcMgtQueueIdx + SrcSrchMgtQueueNum;
    uint16          ResultQueueElemIdx = NVM_JOBQ_QUEUE_INVALID_IDX;

    for( IdxCounter = SrcMgtQueueIdx; IdxCounter < CountEndCond; IdxCounter++ )
    {
        EachResult = NvM_Jobq_SglMgtGetJobInfoHead( IdxCounter, &ResultQueueElemIdx );
        if( EachResult == (Std_ReturnType)E_OK )
        {
            /* Checks whether a fatal error occurred in NvM_Jobq_SglMgtGetJobInfoHead. */
            /* If a fatal error occurred, This function's result is failure. */
            IsFatalFailed = NvM_Evt_IsFatalFailed();
            if( IsFatalFailed == (boolean)FALSE )
            {
                (*DstQueueElemIdx) = ResultQueueElemIdx;
                Rtn = E_OK;
            }
            break;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglMgtAddTail                                   */
/* Description   | This function adds an index in the last of               */
/*               | a management queue.                                      */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx  : An index of a management queue         */
/*               | SrcQueueElemIdx : An index of a queue element            */
/* Return Value  | Dequeue result.                                          */
/*               |  E_OK    : The index was enqueued successfully.          */
/*               |  E_NOT_OK: An error occurred. RAM garbled.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtAddTail(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx
){
    Std_ReturnType Rtn          = E_NOT_OK;
    Std_ReturnType IdxChkResult;
    uint16         TmpTailSideIdx;
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    if( SrcQueueElemIdx < (uint16)NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE )
    {
        TmpTailSideIdx = TgtQueue -> TailSideIdx;
        if(TmpTailSideIdx == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
        {
            /* Queue is empty. */
            TgtQueue -> FrontSideIdx = SrcQueueElemIdx;
            TgtQueue -> TailSideIdx  = SrcQueueElemIdx;
            Rtn = E_OK;
        }
        else
        {
            /* Queue is not empty. */
            IdxChkResult = NvM_Jobq_SglElemCheckIdx( TmpTailSideIdx, SrcMgtQueueIdx );
            if( IdxChkResult == (Std_ReturnType)E_OK )
            {
                NvM_Jobq_SglJobQueueElem[TmpTailSideIdx].NextElementIndex = SrcQueueElemIdx;
                TgtQueue -> TailSideIdx  = SrcQueueElemIdx;
                Rtn = E_OK;
            }
        }
    }

    if( Rtn == (Std_ReturnType)E_OK )
    {
        NvM_Jobq_SglJobQueueElem[SrcQueueElemIdx].NextElementIndex = NVM_JOBQ_QUEUE_INVALID_IDX;
    }

    return Rtn;
}


/****************************************************************************/
/* Function Name | NvM_Jobq_SglMgtRemoveHead                                */
/* Description   | This function removes an index from the head of          */
/*               | a management queue.                                      */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx  : An index of a management queue         */
/*               | DstQueueElemIdx : An index of a queue element            */
/* Return Value  | Dequeue result.                                          */
/*               |  E_OK    : The index was dequeued successfully.          */
/*               |  E_NOT_OK: An error occurred. The queue is empty.        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtRemoveHead(
    uint16 SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
){
    Std_ReturnType Rtn          = E_NOT_OK;
    Std_ReturnType EmpChkRtn;
    Std_ReturnType IdxChkResult;
    boolean        EmpChkResult = FALSE;
    uint16         RemoveIdx;
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    EmpChkRtn = NvM_Jobq_SglElemIsQueueEmpty( TgtQueue, &EmpChkResult );
    if( EmpChkRtn == (Std_ReturnType)E_OK )
    {
        if( EmpChkResult == (boolean)FALSE )
        {
            RemoveIdx = TgtQueue -> FrontSideIdx;
            IdxChkResult = NvM_Jobq_SglElemCheckIdx( RemoveIdx, SrcMgtQueueIdx );
            if( IdxChkResult == (Std_ReturnType)E_OK )
            {
                NvM_Jobq_SglElemRemove( TgtQueue, RemoveIdx, NVM_JOBQ_QUEUE_INVALID_IDX );
                (*DstQueueElemIdx) = RemoveIdx;
                Rtn = E_OK;
            }
        }
    }
    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglMgtRemoveSrch                                */
/* Description   | This function searches index by BlockId,                 */
/*               | and removes the index of a management queue.             */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockId      : BlockId for searches                   */
/*               | SrcMgtQueueIdx  : An index of a management queue         */
/*               | DstQueueElemIdx : An index of a queue element            */
/* Return Value  | Dequeue result.                                          */
/*               |  E_OK    : The index was dequeued successfully.          */
/*               |  E_NOT_OK: An error occurred.                            */
/*               |            The queue is empty, or not found BlockId      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtRemoveSrch(
    NvM_BlockIdType SrcBlockId,
    uint16          SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
){
    Std_ReturnType Rtn          = E_NOT_OK;
    Std_ReturnType EmpChkRtn;
    boolean        EmpChkResult = FALSE;
    uint16                       RemoveTgtIdx = NVM_JOBQ_QUEUE_INVALID_IDX;
    uint16                       RemovePrvIdx = NVM_JOBQ_QUEUE_INVALID_IDX;
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    EmpChkRtn = NvM_Jobq_SglElemIsQueueEmpty( TgtQueue, &EmpChkResult );
    if( EmpChkRtn == (Std_ReturnType)E_OK )
    {
        if( EmpChkResult == (boolean)FALSE )
        {
            Rtn = NvM_Jobq_SglElemSrchBlockId( TgtQueue, SrcBlockId, &RemoveTgtIdx, &RemovePrvIdx );
            if( ( Rtn == (Std_ReturnType)E_OK ) && ( RemoveTgtIdx < (uint16)NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE ) )
            {
                NvM_Jobq_SglElemRemove( TgtQueue, RemoveTgtIdx, RemovePrvIdx );
                (*DstQueueElemIdx) = RemoveTgtIdx;
            }
        }
    }
    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglMgtGetJobInfoHead                            */
/* Description   | This function gets the top index from an queue.          */
/* Preconditions | None                                                     */
/* Parameters    | SrcMgtQueueIdx  : An index of a management queue         */
/*               | DstQueueElemIdx : The index which found queue elem.      */
/* Return Value  | Result                                                   */
/*               |      E_OK    : An index is found.                        */
/*               |      E_NOT_OK: An index is not found.                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtGetJobInfoHead(
    uint16 SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
){
    Std_ReturnType Rtn          = E_NOT_OK;
    Std_ReturnType EmpChkRtn;
    Std_ReturnType IdxChkResult;
    Std_ReturnType PriorityChkResult;
    boolean        EmpChkResult = FALSE;
    uint16         OutputElemIdx;
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueue = &NvM_Jobq_SglJobMgtQueue[SrcMgtQueueIdx];

    EmpChkRtn = NvM_Jobq_SglElemIsQueueEmpty( TgtQueue, &EmpChkResult );
    if( EmpChkRtn == (Std_ReturnType)E_OK )
    {
        if( EmpChkResult == (boolean)FALSE )
        {
            OutputElemIdx = TgtQueue -> FrontSideIdx;
            IdxChkResult = NvM_Jobq_SglElemCheckIdx( OutputElemIdx, SrcMgtQueueIdx );
            if( IdxChkResult == (Std_ReturnType)E_OK )
            {
                PriorityChkResult = NvM_Jobq_SglElemCheckPriority( OutputElemIdx, SrcMgtQueueIdx );
                if( PriorityChkResult == (Std_ReturnType)E_OK )
                {
                    (*DstQueueElemIdx) = OutputElemIdx;
                    Rtn = E_OK;
                }
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglElemIsQueueEmpty                             */
/* Description   | This function checks that the queue is empty.            */
/* Preconditions | None                                                     */
/* Parameters    | SrcQueueInfo : target queue                              */
/*               | DstCheckResult : Check result                            */
/* Return Value  | Request Result                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemIsQueueEmpty(
    P2CONST( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    P2VAR  ( boolean,                     AUTOMATIC, TYPEDEF         ) DstCheckResult
){
    Std_ReturnType Rtn             = E_OK;
    uint16         SrcFrontSideIdx = SrcQueueInfo -> FrontSideIdx;
    uint16         SrcTailSideIdx  = SrcQueueInfo -> TailSideIdx;

    if( ( SrcFrontSideIdx == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
     && ( SrcTailSideIdx  == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX ) )
    {
        /* SrcQueueInfo is empty. */
        (*DstCheckResult) = TRUE;
    }
    else if( ( SrcFrontSideIdx != (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
          && ( SrcTailSideIdx  != (uint16)NVM_JOBQ_QUEUE_INVALID_IDX ) )
    {
        /* SrcQueueInfo is not empty. */
        (*DstCheckResult) = FALSE;
    }
    else
    {
        /* Ram garbled */
        NvM_Evt_FatalFailedNotification();
        Rtn = E_NOT_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglElemRemove                                   */
/* Description   | Dequeue                                                  */
/* Preconditions | None                                                     */
/* Parameters    | SrcQueueInfo : Queue management info of remove.          */
/*               | SrcTargetIdx : Queue elem index of remove target.        */
/*               | SrcPrevIdx   : Queue elem index of previous SrcTargetIdx.*/
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_SglElemRemove(
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    uint16 SrcTargetIdx,
    uint16 SrcPrevIdx
){
    P2VAR( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) TargetQueueElem;
    
    TargetQueueElem = &NvM_Jobq_SglJobQueueElem[SrcTargetIdx];
    if( SrcPrevIdx == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
    {
        SrcQueueInfo -> FrontSideIdx = TargetQueueElem -> NextElementIndex;
        
        if( TargetQueueElem -> NextElementIndex == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
        {
            SrcQueueInfo -> TailSideIdx = NVM_JOBQ_QUEUE_INVALID_IDX;
        }
    }
    else
    {
        NvM_Jobq_SglJobQueueElem[SrcPrevIdx].NextElementIndex = TargetQueueElem -> NextElementIndex;
        
        if( TargetQueueElem -> NextElementIndex == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
        {
            SrcQueueInfo -> TailSideIdx = SrcPrevIdx;
        }
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglElemSrchBlockId                              */
/* Description   | This function searches the queue element using BlockId.  */
/* Preconditions | None                                                     */
/* Parameters    | DstTgtQueueElemIdx : The index of which found elem.      */
/*               | DstPrvQueueElemIdx : The index previous TgtQueueElemIdx. */
/*               | SrcQueueInfo       : Target queue.                       */
/*               | SrcBlockId         : Block ID for searches               */
/* Return Value  | Result                                                   */
/*               |      E_OK   : Indexes are found.                         */
/*               |      E_NOTOK: Indexes are not found.                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemSrchBlockId(
    P2CONST( NvM_Jobq_SglJobMgtQueueType,  AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    NvM_BlockIdType SrcBlockId,
    P2VAR  ( uint16,                       AUTOMATIC, TYPEDEF         ) DstTgtQueueElemIdx,
    P2VAR  ( uint16,                       AUTOMATIC, TYPEDEF         ) DstPrvQueueElemIdx
){
    Std_ReturnType  Rtn              = E_NOT_OK;
    boolean         SrchContinueFlag = TRUE;
    uint16          Counter;
    uint16          SrchPrvIdx       = NVM_JOBQ_QUEUE_INVALID_IDX;
    uint16          SrchTgtIdx       = SrcQueueInfo -> FrontSideIdx;
    P2VAR( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) TgtQueueElem;

    for( Counter = 0U; Counter < NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE; Counter++ )
    {
        if( SrchTgtIdx == (uint16)NVM_JOBQ_QUEUE_INVALID_IDX )
        {
            SrchContinueFlag = FALSE;
        }
        else
        {
            if( SrchTgtIdx < (uint16)NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE )
            {
                TgtQueueElem = &NvM_Jobq_SglJobQueueElem[SrchTgtIdx];
                if( SrcBlockId == TgtQueueElem -> BlockId )
                {
                    (*DstTgtQueueElemIdx) = SrchTgtIdx;
                    (*DstPrvQueueElemIdx) = SrchPrvIdx;
                    Rtn = E_OK;
                    SrchContinueFlag = FALSE;
                }
                else
                {
                    SrchPrvIdx = SrchTgtIdx;
                    SrchTgtIdx = TgtQueueElem -> NextElementIndex;
                }
            }
            else
            {
                /* The index is invalid range. Ram garbled */
                NvM_Evt_FatalFailedNotification();
                SrchContinueFlag = FALSE;
            }
        }
        
        if( SrchContinueFlag == (boolean)FALSE )
        {
            break;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglElemCheckIdx                                 */
/* Description   | This function checks the index of a queue element        */
/*               | is valid range.                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/*               |  E_OK     : The index is valid range.                    */
/*               |  E_NOT_OK : The index is not valid range.                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemCheckIdx(
    uint16 SrcElemIdx,
    uint16 SrcMgtQueueIdx
){
    Std_ReturnType Rtn          = E_OK;
    uint16         ValidIdxTop;
    uint16         ValidIdxLast;

    /* Identifies valid range. */
    if(( SrcMgtQueueIdx == (uint16)NVM_JOBQ_KIND_IMM_UNUSE )
    || ( SrcMgtQueueIdx == (uint16)NVM_JOBQ_KIND_IMM_USE ))
    {
        ValidIdxTop  = NVM_JOBQ_IMM_ELEM_TOP_IDX;
        ValidIdxLast = NVM_JOBQ_IMM_ELEM_LAST_IDX;
    }
    else
    {
        ValidIdxTop  = NVM_JOBQ_STD_ELEM_TOP_IDX;
        ValidIdxLast = NVM_JOBQ_STD_ELEM_LAST_IDX;
    }

    /* Checks the the index of a queue element is valid range. */
    if(( SrcElemIdx > ValidIdxLast )
    || ( SrcElemIdx < ValidIdxTop ))
    {
        /* The index is invalid range. Ram garbled */
        NvM_Evt_FatalFailedNotification();
        Rtn = E_NOT_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_SglElemCheckPriority                            */
/* Description   | This function checks the index of a queue element        */
/*               | is enqueued into an expected management queue,           */
/*               | using BlockId and BlockId's priority.                    */
/* Preconditions | None                                                     */
/* Parameters    | SrcTgtQueueElemIdx : An index of queue element.          */
/*               | SrcTgtMgtQueueIdx  : An index of management queue.       */
/* Return Value  | Check Result                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemCheckPriority(
    uint16 SrcTgtQueueElemIdx,
    uint16 SrcTgtMgtQueueIdx
){
    Std_ReturnType  Rtn                   = E_NOT_OK;
    NvM_BlockIdType TgtBlockId            = NvM_Jobq_SglJobQueueElem[SrcTgtQueueElemIdx].BlockId;
    NvM_BlockIdType UserBlockIdMax        = NVM_USER_BLOCKID_MAX;
    uint16          TgtBlockIdPriority;
    uint16          ExpectPriority;

    if(( TgtBlockId <= UserBlockIdMax )
    && ( TgtBlockId >= (NvM_BlockIdType)NVM_USER_BLOCKID_MIN ))
    {
        TgtBlockIdPriority = NvM_Jobq_GetBlockIdJobPriority( TgtBlockId );
        if( SrcTgtMgtQueueIdx == (uint16)NVM_JOBQ_KIND_IMM_USE )
        {
            ExpectPriority = NVM_PRIORITY_IMMEDIATE;
        }
        else
        {
            ExpectPriority = SrcTgtMgtQueueIdx - (uint16)NVM_JOBQ_KIND_STD_USE;
        }

        if( TgtBlockIdPriority == ExpectPriority )
        {
            Rtn = E_OK;
        }

    }

    if( Rtn != (Std_ReturnType)E_OK )
    {
        /* the index is invalid range. Ram garbled */
        NvM_Evt_FatalFailedNotification();
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_CpyJobInfoToQueueElem                           */
/* Description   | This function sets the job information to                */
/*               | the queue element.                                       */
/* Preconditions | None                                                     */
/* Parameters    | DstQueueElem : Destination pointer of the queue element. */
/*               | SrcJobInfo   : Source pointer of the job information.    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_CpyJobInfoToQueueElem(
    P2VAR  ( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) DstQueueElem,
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF         ) SrcJobInfo
){
    DstQueueElem -> JobId   = SrcJobInfo -> u4JobId;
    DstQueueElem -> BlockId = SrcJobInfo -> u2BlockId;
    DstQueueElem -> DstPtr  = SrcJobInfo -> ptDstPtr;
    DstQueueElem -> SrcPtr  = SrcJobInfo -> ptSrcPtr;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_CpyQueueElemToJobInfo                           */
/* Description   | This function sets the queue element to                  */
/*               | the job information.                                     */
/* Preconditions | None                                                     */
/* Parameters    | DstJobInfo   : Destination pointer of the job            */
/*               |                information.                              */
/*               | SrcQueueElem : Source pointer of the queue element.      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobq_CpyQueueElemToJobInfo(
    P2VAR  ( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF         ) DstJobInfo,
    P2CONST( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueElem
){
    DstJobInfo -> u4JobId   = SrcQueueElem -> JobId;
    DstJobInfo -> u2BlockId = SrcQueueElem -> BlockId;
    DstJobInfo -> ptDstPtr  = SrcQueueElem -> DstPtr;
    DstJobInfo -> ptSrcPtr  = SrcQueueElem -> SrcPtr;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Jobq_GetBlockIdJobPriority                           */
/* Description   | This function gets JobPriority of BlockId.               */
/* Preconditions | None                                                     */
/* Parameters    | SrcBlockId : Block ID to be acquired.                    */
/* Return Value  | JobPriority of the BlockId                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Jobq_GetBlockIdJobPriority(
    NvM_BlockIdType SrcBlockId
){
    uint8 Rtn;
    
#if( NVM_JOB_PRIORITIZATION == STD_ON )
    Rtn = NvMBlockDescriptors[SrcBlockId].NvMBlockJobPriority;
#else  /* NVM_JOB_PRIORITIZATION != STD_ON */
    Rtn = NVM_JOBQ_NON_PRIORITY_VALUE;
#endif /* NVM_JOB_PRIORITIZATION */

    return Rtn;
}

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
