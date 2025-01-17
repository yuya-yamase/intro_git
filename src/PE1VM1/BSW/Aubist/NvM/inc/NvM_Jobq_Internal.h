/* NvM_Jobq_Internal.h v1-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBQ/INTERNAL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOBQ_INTERNAL_H
#define     NVM_JOBQ_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "../cfg/NvM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Single block job queue kind size */
#define NVM_JOBQ_KIND_NUM_IMM_UNUSE             (1U)
#define NVM_JOBQ_KIND_NUM_STD_UNUSE             (1U)
#define NVM_JOBQ_KIND_NUM_IMM_USE               (1U)
#if( NVM_JOB_PRIORITIZATION == STD_ON )
#define NVM_JOBQ_KIND_NUM_STD_USE               (NVM_MAX_OF_BLOCK_JOB_PRIORITY + 1U)
#else /* NVM_JOB_PRIORITIZATION == STD_OFF */
#define NVM_JOBQ_KIND_NUM_STD_USE               (1U)
#endif /* NVM_JOB_PRIORITIZATION */

#define NVM_JOBQ_MGT_QUEUE_NUM                  ((( NVM_JOBQ_KIND_NUM_IMM_UNUSE   \
                                                  + NVM_JOBQ_KIND_NUM_STD_UNUSE ) \
                                                  + NVM_JOBQ_KIND_NUM_IMM_USE   ) \
                                                  + NVM_JOBQ_KIND_NUM_STD_USE   )

/* Single block job queue kind. These macro's value is array index of queue kind. */
#define NVM_JOBQ_KIND_IMM_UNUSE                 (0U)
#define NVM_JOBQ_KIND_STD_UNUSE                 (1U)
#define NVM_JOBQ_KIND_IMM_USE                   (2U)
#define NVM_JOBQ_KIND_STD_USE                   (3U)

/* Single block job queue kind index */
#define NVM_JOBQ_KINDIDX_ZERO                   (0U)

/* Single block job queue elem size */
#define NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE          (NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE)

/* Single block job queue elem index */
#define NVM_JOBQ_STD_ELEM_TOP_IDX               (0U)
#define NVM_JOBQ_STD_ELEM_LAST_IDX              (NVM_SIZE_STANDARD_JOB_QUEUE - 1U)
#define NVM_JOBQ_IMM_ELEM_TOP_IDX               (NVM_SIZE_STANDARD_JOB_QUEUE)
#define NVM_JOBQ_IMM_ELEM_LAST_IDX              ((NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE) - 1U)

/* Single block job priority in case of the prioritization switch is off */
#define NVM_JOBQ_NON_PRIORITY_VALUE             (0U)

#define NVM_JOBQ_QUEUE_INVALID_IDX              (0xFFFFU)
#define NVM_JOBQ_QUEUE_INIT_REF_IDX_SIZE        (1U)
#define NVM_JOBQ_QUEUE_ELEM_NUM_ZERO            (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct{
    uint32 JobId;
    P2VAR( uint8, NVM_VAR_NO_INIT, NVM_APPL_DATA ) DstPtr;
    P2CONST( uint8, NVM_VAR_NO_INIT, TYPEDEF ) SrcPtr;
    NvM_BlockIdType BlockId;
    uint16 NextElementIndex;
} NvM_Jobq_SglJobQueueElemType;

typedef struct{
    uint16 FrontSideIdx;
    uint16 TailSideIdx;
} NvM_Jobq_SglJobMgtQueueType;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/* Single block job queue */
extern VAR( NvM_Jobq_SglJobQueueElemType,   NVM_VAR_NO_INIT )   NvM_Jobq_SglJobQueueElem[NVM_JOBQ_SIZE_SINGLE_JOB_QUEUE];
extern VAR( NvM_Jobq_SglJobMgtQueueType,    NVM_VAR_NO_INIT )   NvM_Jobq_SglJobMgtQueue[NVM_JOBQ_MGT_QUEUE_NUM];
extern VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumImmUnuse;
extern VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumStdUnuse;
extern VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumImmUse;
extern VAR( uint16,                         NVM_VAR_NO_INIT )   NvM_Jobq_SglJobElemNumStdUse;

/* Multi block job queue */
extern VAR( NvM_Jobm_stJobInfomationType,   NVM_VAR_NO_INIT )   NvM_Jobq_MultiJobQueue;

/* CanelWriteAll queue */
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
extern VAR( uint32,                         NVM_VAR_NO_INIT )   NvM_Jobq_CxlWtAllQueue;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Jobq_InitSglQueue(
    boolean SrcIsAbortNfy
);

FUNC( void, NVM_CODE )
NvM_Jobq_InitMultiQueue(
    boolean SrcIsAbortNfy
);

FUNC( void, NVM_CODE )
NvM_Jobq_InitSglMgtQueue( void );

FUNC( void, NVM_CODE )
NvM_Jobq_InitSglQueueElem(
    uint16  SrcMgtQueueIdx,
    uint16  SrcQueueElemTopIdx,
    uint16  SrcQueueElemLastIdx
);

FUNC( void, NVM_CODE )
NvM_Jobq_InitAndNfySglQueueElem(
    uint16  SrcMgtQueueIdx,
    uint16  SrcQueueElemTopIdx,
    uint16  SrcQueueElemLastIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfoSub(
    uint16  SrcStartQueueKind,
    uint16  SrcStartQueueKindIdx,
    uint16  SrcSrchMgtQueueNum,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglEnqueueSubAddUse(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx,
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) SrcJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeueSubAddUnuse(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( uint16, NVM_CODE )
NvM_Jobq_SglQueueKindToMgtIdx(
    uint16 SrcQueueKind,
    uint16 SrcQueueKindIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglQueueGetJobInfo(
    uint16 SrcMgtQueueIdx,
    uint16 SrcSrchMgtQueueNum,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtAddTail(
    uint16 SrcMgtQueueIdx,
    uint16 SrcQueueElemIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtRemoveHead(
    uint16 SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtRemoveSrch(
    NvM_BlockIdType SrcBlockId,
    uint16          SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglMgtGetJobInfoHead(
    uint16 SrcMgtQueueIdx,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) DstQueueElemIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemIsQueueEmpty(
    P2CONST( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    P2VAR  ( boolean,                     AUTOMATIC, TYPEDEF         ) DstCheckResult
);

FUNC( void, NVM_CODE )
NvM_Jobq_SglElemRemove(
    P2VAR( NvM_Jobq_SglJobMgtQueueType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    uint16 SrcTargetIdx,
    uint16 SrcPrevIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemCheckIdx(
    uint16 SrcElemIdx,
    uint16 SrcMgtQueueIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemCheckPriority(
    uint16 SrcTgtQueueElemIdx,
    uint16 SrcTgtMgtQueueIdx
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglElemSrchBlockId(
    P2CONST( NvM_Jobq_SglJobMgtQueueType,  AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueInfo,
    NvM_BlockIdType SrcBlockId,
    P2VAR  ( uint16,                       AUTOMATIC, TYPEDEF         ) DstTgtQueueElemIdx,
    P2VAR  ( uint16,                       AUTOMATIC, TYPEDEF         ) DstPrvQueueElemIdx
);

FUNC( void, NVM_CODE )
NvM_Jobq_CpyJobInfoToQueueElem(
    P2VAR  ( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) DstQueueElem,
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF         ) SrcJobInfo
);

FUNC( void, NVM_CODE )
NvM_Jobq_CpyQueueElemToJobInfo(
    P2VAR  ( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF         ) DstJobInfo,
    P2CONST( NvM_Jobq_SglJobQueueElemType, AUTOMATIC, NVM_VAR_NO_INIT ) SrcQueueElem
);

FUNC( uint8, NVM_CODE )
NvM_Jobq_GetBlockIdJobPriority(
    NvM_BlockIdType SrcBlockId
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOBQ_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
