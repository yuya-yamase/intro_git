/* NvM_Job.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOB/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Job.h"
#include "../inc/NvM_Job_Internal.h"
#include <Mscd_Common.h>
#include "../inc/NvM_Romb.h"
#include "../inc/NvM_Rwd.h"
#include "../inc/NvM_Evt.h"
#include "../inc/NvM_Jobm.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Adb.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR     ( uint8,                            NVM_VAR_NO_INIT )             NvM_Job_u1MainStatus;
VAR     ( uint32,                           NVM_VAR_NO_INIT )             NvM_Job_SubStatus;
VAR     ( NvM_Jobm_stJobInfomationType,     NVM_VAR_NO_INIT )             NvM_Job_stExecuteJobInfo;
P2VAR   ( uint8,                            NVM_VAR_NO_INIT,    TYPEDEF ) NvM_Job_ReadDataPtr;
P2CONST ( uint8,                            NVM_VAR_NO_INIT,    TYPEDEF ) NvM_Job_WriteDataPtr;
VAR     ( NvM_Job_stMultiBlockRequestType,  NVM_VAR_NO_INIT )             NvM_Job_stMultiReqInfo;
VAR     ( uint8,                            NVM_VAR_NO_INIT )             NvM_Job_ReadResult;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

/* Job Id Convert Table */
CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )           NvM_Job_arstJobIdBitToSeqNumPair[NVM_JOB_JOBID_NUM] =
{
    { (uint32)NVM_JOB_READ_BLOCK,                  NVM_JOB_JOBID_RD             },
    { (uint32)NVM_JOB_WRITE_BLOCK,                 NVM_JOB_JOBID_WT             },
    { (uint32)NVM_JOB_RESTORE_BLOCK_DEFAULTS,      NVM_JOB_JOBID_RSTR_DFLTS     },
    { (uint32)NVM_JOB_READ_PRAM_BLOCK,             NVM_JOB_JOBID_RD_PRM         },
    { (uint32)NVM_JOB_WRITE_PRAM_BLOCK,            NVM_JOB_JOBID_WT_PRM         },
    { (uint32)NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS, NVM_JOB_JOBID_RSTR_PRM_DFLTS },
    { (uint32)NVM_JOB_READ_ALL,                    NVM_JOB_JOBID_RD_ALL         },
    { (uint32)NVM_JOB_WRITE_ALL,                   NVM_JOB_JOBID_WT_ALL         }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )               NvM_Job_arstJobIdBitToSeqNumTbl =
{
    NVM_JOB_JOBID_NUM,
    NvM_Job_arstJobIdBitToSeqNumPair
};

CONST( AB_83_ConstV uint8, NVM_CONST ) NvM_Job_JobIdSeqToJobClass[NVM_JOB_JOBID_NUM] = 
{
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_RD             */
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_WT             */
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_RSTR_DFLTS     */
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_RD_PRM         */
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_WT_PRM         */
    NVM_JOB_JOBCLASS_SINGLE,    /* NVM_JOB_JOBID_RSTR_PRM_DFLTS */
    NVM_JOB_JOBCLASS_MULTI,     /* NVM_JOB_JOBID_RD_ALL         */
    NVM_JOB_JOBCLASS_MULTI      /* NVM_JOB_JOBID_WT_ALL         */
};

/* SubStatus Number Convert Table */
CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )           NvM_Job_SubStatusBitToSeqNumPair[NVM_JOB_SUB_COMMON_NUM] =
{
    { NVM_RND_NUM_UINT32_01, (uint32)NVM_JOB_SUB_COMMON_SEQ_00 },
    { NVM_RND_NUM_UINT32_02, (uint32)NVM_JOB_SUB_COMMON_SEQ_01 },
    { NVM_RND_NUM_UINT32_03, (uint32)NVM_JOB_SUB_COMMON_SEQ_02 },
    { NVM_RND_NUM_UINT32_04, (uint32)NVM_JOB_SUB_COMMON_SEQ_03 },
    { NVM_RND_NUM_UINT32_05, (uint32)NVM_JOB_SUB_COMMON_SEQ_04 },
    { NVM_RND_NUM_UINT32_06, (uint32)NVM_JOB_SUB_COMMON_SEQ_05 }
};

CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )               NvM_Job_SubStatusBitToSeqNumTbl =
{
    NVM_JOB_SUB_COMMON_NUM,
    NvM_Job_SubStatusBitToSeqNumPair
};

/* Action Table */
CONST( AB_83_ConstV NvM_Job_stJobActTblType,  NVM_CONST ) NvM_Job_arActTbl[NVM_JOB_JOBID_NUM] =
{
    {   /* NVM_JOB_JOBID_RD */
        &NvM_Job_ActStartRD,            /* ptFuncStartJob */
        NVM_JOB_ACTNUM_RD,              /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblRD,     /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_WT */
        &NvM_Job_ActStartWT,            /* ptFuncStartJob */
        NVM_JOB_ACTNUM_WT,              /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblWT,     /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_RSTR_DFLTS */
        &NvM_Job_ActStartRSTR,            /* ptFuncStartJob */
        NVM_JOB_ACTNUM_RSTR,            /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblRSTR,   /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_RD_PRM */
        &NvM_Job_ActStartRD,              /* ptFuncStartJob */
        NVM_JOB_ACTNUM_RD,              /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblRD,     /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_WT_PRM */
        &NvM_Job_ActStartWT,            /* ptFuncStartJob */
        NVM_JOB_ACTNUM_WT,              /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblWT,     /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_RSTR_PRM_DFLTS */
        &NvM_Job_ActStartRSTR,            /* ptFuncStartJob */
        NVM_JOB_ACTNUM_RSTR,            /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblRSTR,   /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionSB,     /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutSB,    /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestSB /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_RD_ALL */
        &NvM_Job_ActStartRdAll,         /* ptFuncStartJob */
        NVM_JOB_ACTNUM_RD_ALL,          /* u1FuncExecJobNum */
        NvM_Job_arFuncExecJobTblRdAll,  /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionRdAll,  /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutRdAll, /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestRdAll /* ptFuncCancelUserrequest */
    },
    {   /* NVM_JOB_JOBID_WT_ALL */
        &NvM_Job_ActStartWtAll,         /* ptFuncStartJob */
        NVM_JOB_ACTNUM_WT_ALL,          /* u1FuncExecJobNum */
        NvM_Job_FuncExecJobTblWtAll,    /* arptFuncExecJob */
        &NvM_Job_ActCancelPreemptionWtAll,  /* ptFuncCancelPreemption */
        &NvM_Job_ActCancelTimeoutWtAll, /* ptFuncCancelTimeout */
        &NvM_Job_ActCancelUserrequestWtAll /* ptFuncCancelUserrequest */
    }
};

/* ReadBlock Action Func Tbl */
CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST ) NvM_Job_arFuncExecJobTblRD[NVM_JOB_ACTNUM_RD] =
{
    &NvM_Job_ActStartRD,                /* NVM_JOB_SUB_RD_START         */
    &NvM_Job_ActNvbChkRspRD,            /* NVM_JOB_SUB_RD_NVB_CHK_RSP   */
    &NvM_Job_ActRspRD                   /* NVM_JOB_SUB_RD_RSP           */
};

/* WriteBlock Action Func Tbl */
CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST ) NvM_Job_arFuncExecJobTblWT[NVM_JOB_ACTNUM_WT] =
{
    &NvM_Job_ActStartWT,                /* NVM_JOB_SUB_WT_START         */
    &NvM_Job_ActReqWT,                  /* NVM_JOB_SUB_WT_REQ             */
    &NvM_Job_ActRspWT                   /* NVM_JOB_SUB_WT_RSP             */
};

/* RestoreBlockDefaults Action Func Tbl */
CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST ) NvM_Job_arFuncExecJobTblRSTR[NVM_JOB_ACTNUM_RSTR] =
{
    &NvM_Job_ActStartRSTR,              /* NVM_JOB_SUB_RSTR_START           */
    &NvM_Job_ActDataNotifyRSTR          /* NVM_JOB_SUB_RSTR_DATA_NOTIFY    */
};

/* ReadAll Action Func Tbl */
CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST ) NvM_Job_arFuncExecJobTblRdAll[NVM_JOB_ACTNUM_RD_ALL] =
{
    &NvM_Job_ActSglBlkStartRdAll,       /* NVM_JOB_SUB_RDALL_SGLBLK_START  */
    &NvM_Job_ActNvbChkRspRdAll,         /* NVM_JOB_SUB_RDALL_NVB_CHK_RSP   */
    &NvM_Job_ActRspRdAll                /* NVM_JOB_SUB_RDALL_RSP           */
};

/* WriteAll Action Func Tbl */
CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST ) NvM_Job_FuncExecJobTblWtAll[NVM_JOB_ACTNUM_WT_ALL] =
{
    &NvM_Job_ActSglBlkStartWtAll,       /* NVM_JOB_SUB_WTALL_SGLBLK_START     */
    &NvM_Job_ActReqWtAll,               /* NVM_JOB_SUB_WTALL_REQ              */
    &NvM_Job_ActRspWtAll,               /* NVM_JOB_SUB_WTALL_RSP              */
    &NvM_Job_ActSglBlkStartCxlWtAll,    /* NVM_JOB_SUB_WTALL_SGLBLK_START_CXL */
    &NvM_Job_ActReqCxlWtAll,            /* NVM_JOB_SUB_WTALL_REQ_CXL          */
    &NvM_Job_ActRspCxlWtAll             /* NVM_JOB_SUB_WTALL_RSP_CXL          */
};

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Job_Init                                             */
/* Description   | Service to initialize the JOB unit.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_Init( void )
{
    NvM_Job_RamInit();

    return ;
}

/****************************************************************************/
/* Function Name | NvM_Job_GetStatus                                        */
/* Description   | Service to return the JOB status.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | JOB status.                                              */
/*               |    NVM_JOB_IDLE                                          */
/*               |    NVM_JOB_BUSY                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( NvM_Job_StatusType, NVM_CODE )
NvM_Job_GetStatus(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) stJobInfo
){
    NvM_Job_StatusType u1Ret = NVM_JOB_BUSY;

    if( (uint32)NVM_JOB_NON == NvM_Job_stExecuteJobInfo.u4JobId )
    {
        u1Ret = NVM_JOB_IDLE;
    }
    else
    {
        if(( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_PREEMPTION == NvM_Job_u1MainStatus )
        || ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT == NvM_Job_u1MainStatus )
        || ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST == NvM_Job_u1MainStatus ))
        {
            u1Ret = NVM_JOB_BUSY_CANCEL;
        }

        stJobInfo -> u4JobId   = NvM_Job_stExecuteJobInfo.u4JobId;
        stJobInfo -> u2BlockId = NvM_Job_stExecuteJobInfo.u2BlockId;
        stJobInfo -> ptDstPtr  = NvM_Job_stExecuteJobInfo.ptDstPtr;
        stJobInfo -> ptSrcPtr  = NvM_Job_stExecuteJobInfo.ptSrcPtr;
    }

    return u1Ret;
}

/****************************************************************************/
/* Function Name | NvM_Job_RequestJob                                       */
/* Description   | Service to request a job.                                */
/* Preconditions | None                                                     */
/* Parameters    | stJobInfo : Structure body of the job information.       */
/* Return Value  | Request result                                           */
/*               |  E_OK     : I accepted a handling of job demand.         */
/*               |  E_NOT_OK : A handling of job demand was not accepted.   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_RequestJob(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) stJobInfo
){
    Std_ReturnType u1Ret = E_NOT_OK;

    if( NvM_Job_stExecuteJobInfo.u4JobId == (uint32)NVM_JOB_NON )
    {
        NvM_Job_stExecuteJobInfo.u4JobId   = stJobInfo -> u4JobId;
        NvM_Job_stExecuteJobInfo.u2BlockId = stJobInfo -> u2BlockId;
        NvM_Job_stExecuteJobInfo.ptDstPtr  = stJobInfo -> ptDstPtr;
        NvM_Job_stExecuteJobInfo.ptSrcPtr  = stJobInfo -> ptSrcPtr;

        NvM_Job_u1MainStatus = NVM_JOB_MAIN_IDLE;

        u1Ret = E_OK;
    }

    return u1Ret;
}

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Job_CancelJob                                        */
/* Description   | Service to cancel the driving job.                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_CancelJob( void )
{

    if( NvM_Job_stExecuteJobInfo.u4JobId == (uint32)NVM_JOB_WRITE_ALL )
    {
        if( NvM_Job_SubStatus == (uint32)NVM_JOB_SUB_WTALL_SGLBLK_START )
        {
            NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_SGLBLK_START_CXL;
        }
        else if( NvM_Job_SubStatus == (uint32)NVM_JOB_SUB_WTALL_REQ )
        {
            NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_REQ_CXL;
        }
        else if( NvM_Job_SubStatus == (uint32)NVM_JOB_SUB_WTALL_RSP )
        {
            NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_RSP_CXL;
        }
        else
        {
            /* No process */
        }
    }

    return;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_DestructiveCancelJob                             */
/* Description   | Service to provide destructive cancellation of the       */
/*               | driving job.                                             */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_DestructiveCancelJob(
    uint8 u1Kind
){
    NvM_Nvb_DestructiveCancelOperation();

    if( (uint32)NVM_JOB_NON != NvM_Job_stExecuteJobInfo.u4JobId )
    {
        if( (uint8)NVM_JOB_DSTRCTV_CXL_PREEMPTION == u1Kind )
        {
            if(( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST != NvM_Job_u1MainStatus )
            && ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT     != NvM_Job_u1MainStatus ))
            {
                NvM_Job_u1MainStatus = NVM_JOB_MAIN_WAIT_CANCEL_PREEMPTION;
            }
        }
        else if( (uint8)NVM_JOB_DSTRCTV_CXL_USERREQUEST == u1Kind )
        {
            NvM_Job_u1MainStatus = NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST;
        }
        else
        {
            if( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST != NvM_Job_u1MainStatus )
            {
                NvM_Job_u1MainStatus = NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT;
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_MainFunction                                     */
/* Description   | Service to handle the requested jobs and the internal    */
/*               | management operations.                                   */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_MainFunction(
    uint8 CallMode
){
    Std_ReturnType ChkResult;
    uint32         JobIdBit             = NvM_Job_stExecuteJobInfo.u4JobId;
    uint32         JobIdSeq;

    if( (uint32)NVM_JOB_NON != JobIdBit )
    {
        JobIdSeq = NvM_Lib_ConvertValue( JobIdBit, NVM_JOB_JOBID_INVALID, &NvM_Job_arstJobIdBitToSeqNumTbl );

        ChkResult = E_NOT_OK;
        if( (uint32)NVM_JOB_JOBID_NUM  > JobIdSeq )
        {
            ChkResult = NvM_Job_ChkExecBlockId( JobIdSeq );
        }

        if( ChkResult == (Std_ReturnType)E_OK )
        {
            NvM_Job_StateChangeAct( CallMode, JobIdSeq );
        }
        else
        {
            /* Ram garbled */
            NvM_Evt_FatalFailedNotification();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_GetExecBlockId                                   */
/* Description   | The function for getting BlockId being executed.         */
/* Preconditions | None                                                     */
/* Parameters    | BlockIdPtr : Pointer to where to store the BlockId.      */
/* Return Value  | Std_ReturnType : Get result.                             */
/*               |  E_OK     : BlockId being executed is exist.             */
/*               |  E_NOT_OK : BlockId being executed is not exist.         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_GetExecBlockId(
    P2VAR( NvM_BlockIdType, AUTOMATIC, TYPEDEF ) BlockIdPtr
){
    Std_ReturnType  Rtn;
    uint32          JobIdBit = NvM_Job_stExecuteJobInfo.u4JobId;
    uint32          JobIdSeq;
    uint8           JobClass;
    NvM_BlockIdType MultiExecBlockId;
    
    Rtn = E_NOT_OK;
    if( JobIdBit != (uint32)NVM_JOB_NON )
    {
        JobIdSeq = NvM_Lib_ConvertValue( JobIdBit, NVM_JOB_JOBID_INVALID, &NvM_Job_arstJobIdBitToSeqNumTbl );
        if( JobIdSeq != (uint32)NVM_JOB_JOBID_INVALID )
        {
            JobClass = NvM_Job_JobIdSeqToJobClass[JobIdSeq];
            if( JobClass == (uint8)NVM_JOB_JOBCLASS_SINGLE )
            {
                *BlockIdPtr = NvM_Job_stExecuteJobInfo.u2BlockId;
                Rtn = E_OK;
            }
            else    /* JobClass == NVM_JOB_JOBCLASS_MULTI */
            {
                MultiExecBlockId = NvM_Job_stMultiReqInfo.u2BlockId;
                if( MultiExecBlockId != (NvM_BlockIdType)NVM_BLOCKID_INVALID )
                {
                    *BlockIdPtr = MultiExecBlockId;
                    Rtn = E_OK;
                }
            }
        }
    }
    
    return Rtn;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | NvM_Job_RamInit                                          */
/* Description   | Service to initialize JOB rams.                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_RamInit( void )
{
    NvM_Job_u1MainStatus = NVM_JOB_MAIN_IDLE;
    NvM_Job_SubStatus  = NVM_JOB_SUB_INVALID_RND;

    NvM_Job_stExecuteJobInfo.u4JobId     = NVM_JOB_NON;
    NvM_Job_stExecuteJobInfo.u2BlockId   = NVM_BLOCKID_INVALID;
    NvM_Job_stExecuteJobInfo.ptDstPtr    = NULL_PTR;
    NvM_Job_stExecuteJobInfo.ptSrcPtr    = NULL_PTR;

    NvM_Job_stMultiReqInfo.u1JobResult   = NVM_REQ_OK;
    NvM_Job_stMultiReqInfo.u2BlockId     = NVM_BLOCKID_INVALID;

    NvM_Job_ReadResult                   = NVM_REQ_OK;

    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_ChkExecBlockId                                   */
/* Description   | The function for checking BlockId being executed.        */
/* Preconditions | None                                                     */
/* Parameters    | JobId     : Sequential job identifier.                   */
/* Return Value  | Std_ReturnType : Check result.                           */
/*               |  E_OK     : BlockId being executed is valid range.       */
/*               |  E_NOT_OK : BlockId being executed is invalid.           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_ChkExecBlockId(
    uint32 JobId
){
    Std_ReturnType  Rtn                 = E_NOT_OK;
    boolean         NeedForCheckBlockId;
    NvM_BlockIdType UserBlkIdMax;
    NvM_BlockIdType ChkTgtBlockId;
    uint8           JobClass;

    JobClass = NvM_Job_JobIdSeqToJobClass[JobId];
    NeedForCheckBlockId = TRUE;
    if( JobClass == (uint8)NVM_JOB_JOBCLASS_SINGLE )
    {
        ChkTgtBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;
    }
    else    /* JobClass == NVM_JOB_JOBCLASS_MULTI */
    {
        if( (uint8)NVM_JOB_MAIN_IDLE != NvM_Job_u1MainStatus )
        {
            ChkTgtBlockId = NvM_Job_stMultiReqInfo.u2BlockId;
        }
        else
        {
            Rtn = E_OK;
            NeedForCheckBlockId = FALSE;
        }
    }

    /* Checks the Block Id */
    if( NeedForCheckBlockId == (boolean)TRUE )
    {
        UserBlkIdMax = NVM_USER_BLOCKID_MAX;
        if(( ChkTgtBlockId <= UserBlkIdMax )
        && ( ChkTgtBlockId >= (NvM_BlockIdType)NVM_USER_BLOCKID_MIN ))
        {
            Rtn = E_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_StateChangeAct                                   */
/* Description   | Service to execute state change action.                  */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/*               | JobId    : Job Identifier that is expressed by           */
/*               |            sequential number.                            */
/* Return Value  | None                                                     */
/* Notes         | In garbled RAM case, the JOB never move again.           */
/*               | The state of JOB is recovered by watchdog timer.         */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_StateChangeAct(
    uint8 CallMode,
    uint32 JobId
){
    uint8  LocalMainStatusCurrent = NvM_Job_u1MainStatus;
    uint8  LocalMainStatusNext    = LocalMainStatusCurrent;
    uint32 SeqSubStatus;

    if( (uint8)NVM_JOB_MAIN_IDLE == LocalMainStatusCurrent )
    {
        LocalMainStatusNext = NvM_Job_arActTbl[JobId].ptFuncStartJob();
    }
    else if( (uint8)NVM_JOB_MAIN_RUN_ACTIVE == LocalMainStatusCurrent )
    {
        SeqSubStatus = NvM_Lib_ConvertValue( NvM_Job_SubStatus, NVM_JOB_SUB_INVALID_SEQ, &NvM_Job_SubStatusBitToSeqNumTbl );
        if( SeqSubStatus < NvM_Job_arActTbl[JobId].u1FuncExecJobNum )        /* Illegal array access guard */
        {
            LocalMainStatusNext = NvM_Job_arActTbl[JobId].arptFuncExecJob[SeqSubStatus]();
        }
    }
    else
    {
        /* No process */
    }

    NvM_Nvb_MainFunction( CallMode );

    if( ( (uint8)NVM_JOB_MAIN_RUN_WAIT_NORMAL == LocalMainStatusNext )
     || ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_PREEMPTION == LocalMainStatusNext )
     || ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST == LocalMainStatusNext )
     || ( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT == LocalMainStatusNext ) )
    {
        LocalMainStatusNext = NvM_Job_StateChangeActForWait( JobId, LocalMainStatusNext );
    }

    if( (uint8)NVM_JOB_MAIN_IDLE == LocalMainStatusNext )
    {
        NvM_Job_stExecuteJobInfo.u4JobId = NVM_JOB_NON;
    }

    NvM_Job_u1MainStatus = LocalMainStatusNext;

    return;
}


/****************************************************************************/
/* Function Name | NvM_Job_StateChangeActForWait                            */
/* Description   | Service to execute state change action for waiting.      */
/* Preconditions | None                                                     */
/* Parameters    | JobId   : Job Identifier that is expressed by sequential */
/*               |           number.                                        */
/* Return Value  | Next main status                                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_StateChangeActForWait(
    uint32 JobId,
    uint8 LocalMainStatus
){
    NvM_Nvb_StatusType  NvbStatus;
    uint8               RtnStatus   = LocalMainStatus;
    uint32              SeqSubStatus;

    NvbStatus = NvM_Nvb_GetStatus();
    if( (NvM_Nvb_StatusType)NVM_NVB_IDLE == NvbStatus )
    {
        if( (uint8)NVM_JOB_MAIN_RUN_WAIT_NORMAL == LocalMainStatus )
        {
            SeqSubStatus = NvM_Lib_ConvertValue( NvM_Job_SubStatus, NVM_JOB_SUB_INVALID_SEQ, &NvM_Job_SubStatusBitToSeqNumTbl );
            if( SeqSubStatus < NvM_Job_arActTbl[JobId].u1FuncExecJobNum )    /* Illegal array access guard */
            {
                RtnStatus = NvM_Job_arActTbl[JobId].arptFuncExecJob[SeqSubStatus]();
            }
        }
        else if( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_PREEMPTION == LocalMainStatus )
        {
            RtnStatus = NvM_Job_arActTbl[JobId].ptFuncCancelPreemption();
        }
        else if( (uint8)NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST == LocalMainStatus )
        {
            RtnStatus = NvM_Job_arActTbl[JobId].ptFuncCancelUserrequest();
        }
        else    /* Only when LocalMainStatus equals NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT. */
        {
            RtnStatus = NvM_Job_arActTbl[JobId].ptFuncCancelTimeout();
        }
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActStartRD                                       */
/* Description   | Action function for ReadBlock job.                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRD( void )
{
    Std_ReturnType PreSglBlkProcExecResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    uint32 ExecJobId = NvM_Job_stExecuteJobInfo.u4JobId;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) ExecDstPtr = NvM_Job_stExecuteJobInfo.ptDstPtr;

    NvM_Evt_SglBlkProcStart( ExecBlockId, ExecJobId );

    PreSglBlkProcExecResult = NvM_Job_SubActPreSglBlkProcExec();
    if( (Std_ReturnType)E_OK == PreSglBlkProcExecResult )
    {
        NvM_Evt_ReadStart( ExecBlockId, ExecDstPtr );

        NvM_Job_ReadDataPtr = NvM_Rwd_GetReadDataBuffer( ExecBlockId );
        RtnStatus = NvM_Job_SubActReqRD();
    }
    else
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_RD_START;   /* Sub status */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActNvbChkRspRD                                   */
/* Description   | Action function for ReadBlock job.                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActNvbChkRspRD( void )
{
    NvM_RequestResultType NvbResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Request */
    NvbResult = NvM_Nvb_GetOperationResult();
    NvM_Job_ReadResult = NvbResult;

    /* Check request result, set status */
    if( (NvM_RequestResultType)NVM_REQ_OK == NvbResult )
    {
        if( ( NvMBlockDescriptors[ExecBlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            NvM_Adb_SetNvBlockProtection( ExecBlockId, NVM_ADB_WRITE_PROT_ENABLED );
        }
        RtnStatus = NvM_Job_SubActRspRD( NvbResult );
    }
    else if(( (NvM_RequestResultType)NVM_REQ_NOT_OK == NvbResult )
         || ( (NvM_RequestResultType)NVM_REQ_INTEGRITY_FAILED == NvbResult ))
    {
        RtnStatus = NvM_Job_SubActRomRcvrRspRD( NvbResult );
    }
    else if( (NvM_RequestResultType)NVM_REQ_NV_INVALIDATED == NvbResult )
    {
        NvM_Evt_ReadEndInFailure( ExecBlockId );
        RtnStatus = NvM_Job_SubActJobEndProcSB( NvbResult );
    }
    else
    {
        /* NVM_REQ_PENDING and NVM_REQ_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActRspRD                                         */
/* Description   | Action function for ReadBlock job.                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActRspRD( void )
{
    uint8 RtnStatus;

    RtnStatus = NvM_Job_SubActRspRD( NvM_Job_ReadResult );

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActStartWT                                       */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartWT( void )
{
    Std_ReturnType PreSglBlkProcExecResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    uint32 ExecJobId = NvM_Job_stExecuteJobInfo.u4JobId;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ExecSrcPtr = NvM_Job_stExecuteJobInfo.ptSrcPtr;

    NvM_Evt_SglBlkProcStart( ExecBlockId, ExecJobId );

    PreSglBlkProcExecResult = NvM_Job_SubActPreSglBlkProcExec();
    if( (Std_ReturnType)E_OK == PreSglBlkProcExecResult )
    {
        NvM_Evt_WriteStart( ExecBlockId, ExecSrcPtr );

        RtnStatus = NvM_Job_RequestWriteOperation();
    }
    else
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_WT_START;   /* Sub status */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActReqWT                                         */
/* Description   | Action function for WriteBlock job.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActReqWT( void )
{
    uint8 u1RtnStatus;
    u1RtnStatus = NvM_Job_RequestWriteOperation();

    return u1RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActRspWT                                         */
/* Description   | Action function for WriteBlock job.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActRspWT( void )
{
    NvM_RequestResultType u1Result;
    uint8 u1RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    u1Result = NvM_Nvb_GetOperationResult();

    if( (NvM_RequestResultType)NVM_REQ_OK == u1Result )
    {
        if( ( NvMBlockDescriptors[ExecBlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            NvM_Adb_SetNvBlockProtection( ExecBlockId, NVM_ADB_WRITE_PROT_ENABLED );
        }
        NvM_Evt_WriteEndInSuccess( ExecBlockId );
        u1RtnStatus = NvM_Job_SubActJobEndProcSB( u1Result );
    }
    else if( (NvM_RequestResultType)NVM_REQ_NOT_OK == u1Result )
    {
        NvM_Evt_WriteEndInFailure( ExecBlockId );
        u1RtnStatus = NvM_Job_SubActJobEndProcSB( u1Result );
    }
    else
    {
        /* NVM_REQ_PENDING and NVM_REQ_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }

    return u1RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActStartRSTR                                     */
/* Description   | Action function for RestoreBlockDefaults job.            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRSTR( void )
{
    Std_ReturnType PreSglBlkProcExecResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    uint32 ExecJobId = NvM_Job_stExecuteJobInfo.u4JobId;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) ExecDstPtr = NvM_Job_stExecuteJobInfo.ptDstPtr;

    NvM_Evt_SglBlkProcStart( ExecBlockId, ExecJobId );

    PreSglBlkProcExecResult = NvM_Job_SubActPreSglBlkProcExec();
    if( (Std_ReturnType)E_OK == PreSglBlkProcExecResult )
    {
        NvM_Evt_RestoreStart( ExecBlockId, ExecDstPtr );

        NvM_Job_ReadDataPtr = NvM_Rwd_GetReadDataBuffer( ExecBlockId );
        RtnStatus = NvM_Job_SubActExecRSTR();
    }
    else
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_RSTR_START;   /* Sub status */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActDataNotifyRSTR                                */
/* Description   | Action function for RestoreBlockDefaults job.            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActDataNotifyRSTR( void )
{
    uint8 RtnStatus;

    RtnStatus = NvM_Job_SubActDataNotifyRSTR();

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActStartRdAll                                    */
/* Description   | Start function for ReadAll job.                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRdAll( void )
{
    uint8 RtnStatus;
    Std_ReturnType SrchResult;
    NvM_BlockIdType Index;
    NvM_BlockIdType SrchStartBlkId;
    NvM_BlockIdType NextBlkId;
    NvM_BlockIdType FirstBlkId;
    boolean Found = FALSE;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;

    NvM_Job_stMultiReqInfo.u1JobResult = NVM_REQ_OK;

    SrchStartBlkId = NVM_USER_BLOCKID_MIN;
    FirstBlkId = NVM_USER_BLOCKID_MIN;
    for( Index = NVM_USER_BLOCKID_MIN; Index <= UserBlkIdMax; Index++ )
    {
        SrchResult = NvM_Job_SubActSrchNextBlkIdMB( SrchStartBlkId, NVM_SELECT_BLOCK_FOR_READ_ALL, &NextBlkId );
        if( (Std_ReturnType)E_OK == SrchResult )
        {
            NvM_Adb_SetErrorStatus( NextBlkId, NvM_Job_stExecuteJobInfo.u4JobId, NVM_REQ_PENDING );
            if( (boolean)FALSE == Found )
            {
                FirstBlkId = NextBlkId;
                Found = TRUE;
            }
            SrchStartBlkId = NextBlkId;
            SrchStartBlkId++;    /* Increment search start position */
        }
        else
        {
            break;
        }
    }

    if( (boolean)TRUE == Found )
    {
        NvM_Job_stMultiReqInfo.u2BlockId = FirstBlkId;
        NvM_Evt_SglBlkProcStart( FirstBlkId, NvM_Job_stExecuteJobInfo.u4JobId );
        RtnStatus = NvM_Job_SubActSglBlkStartRdAll();
    }
    else
    {
        RtnStatus = NvM_Job_SubActJobEndProcMB( NvM_Job_stMultiReqInfo.u1JobResult );
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActSglBlkStartRdAll                              */
/* Description   | Start function for ReadAll job.                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartRdAll( void )
{
    uint8 RtnStatus;
    RtnStatus = NvM_Job_SubActSglBlkStartRdAll();
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActNvbChkRspRdAll                                */
/* Description   | Action function for ReadAll job.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActNvbChkRspRdAll( void )
{
    NvM_RequestResultType NvbResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;

    NvM_BlockIdType SglBlkId = NvM_Job_stMultiReqInfo.u2BlockId;

    /* Request */
    NvbResult = NvM_Nvb_GetOperationResult();
    NvM_Job_ReadResult = NvbResult;

    /* Check request result, set status */
    if( (NvM_RequestResultType)NVM_REQ_OK == NvbResult )
    {
        if( ( NvMBlockDescriptors[SglBlkId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            NvM_Adb_SetNvBlockProtection( SglBlkId, NVM_ADB_WRITE_PROT_ENABLED );
        }
        RtnStatus = NvM_Job_SubActRspRdAll( SglBlkId, NvbResult );
    }
    else if(( (NvM_RequestResultType)NVM_REQ_NOT_OK == NvbResult )
         || ( (NvM_RequestResultType)NVM_REQ_INTEGRITY_FAILED == NvbResult ))
    {
        RtnStatus = NvM_Job_SubActRomRcvrRspRdAll( SglBlkId, NvbResult );
    }
    else if((NvM_RequestResultType)NVM_REQ_NV_INVALIDATED == NvbResult )
    {
        NvM_Evt_ReadEndInFailure( SglBlkId );
        RtnStatus = NvM_Job_SubActSglBlkEndRdAll( SglBlkId, NvbResult );
    }
    else
    {
        /* NVM_REQ_PENDING and NVM_REQ_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActRspRdAll                                      */
/* Description   | Action function for ReadAll job.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActRspRdAll( void )
{
    uint8 RtnStatus;

    RtnStatus = NvM_Job_SubActRspRdAll( NvM_Job_stMultiReqInfo.u2BlockId, NvM_Job_ReadResult );

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActStartWtAll                                    */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartWtAll( void )
{
    uint8 RtnStatus;
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
    Std_ReturnType SrchResult;
    NvM_BlockIdType Index;
    NvM_BlockIdType SrchStartBlkId = NVM_USER_BLOCKID_MIN;
    NvM_BlockIdType NextBlkId;
    NvM_BlockIdType FirstBlkId = NVM_USER_BLOCKID_MIN;
    boolean FoundFlag = FALSE;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;

    NvM_Job_stMultiReqInfo.u1JobResult = NVM_REQ_OK;
    for( Index = NVM_USER_BLOCKID_MIN; Index <= UserBlkIdMax ; Index++ )
    {
        SrchResult = NvM_Job_SubActSrchNextBlkIdMB( SrchStartBlkId, NVM_SELECT_BLOCK_FOR_WRITE_ALL, &NextBlkId );
        if( (Std_ReturnType)E_OK == SrchResult )
        {
            NvM_Adb_SetErrorStatus( NextBlkId, NvM_Job_stExecuteJobInfo.u4JobId, NVM_REQ_PENDING );
            if( (boolean)FALSE == FoundFlag )
            {
                FirstBlkId = NextBlkId;
                FoundFlag = TRUE;
            }
            SrchStartBlkId = NextBlkId;
            SrchStartBlkId++;    /* Increment search start position */
        }
        else
        {
            break;
        }
    }

    if( (boolean)TRUE == FoundFlag )
    {
        NvM_Job_stMultiReqInfo.u2BlockId = FirstBlkId;
        NvM_Evt_SglBlkProcStart( FirstBlkId, NvM_Job_stExecuteJobInfo.u4JobId );
        RtnStatus = NvM_Job_SubActSglBlkStartWtAll();
    }
    else
    {
        RtnStatus = NvM_Job_SubActJobEndProcMB( NvM_Job_stMultiReqInfo.u1JobResult );
    }
#else /* NVM_VALID_WRITE_ALL_API == STD_OFF */
    RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#endif /* NVM_VALID_WRITE_ALL_API */

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActSglBlkStartWtAll                              */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartWtAll( void )
{
    uint8 RtnStatus;
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
    RtnStatus = NvM_Job_SubActSglBlkStartWtAll();
#else /* NVM_VALID_WRITE_ALL_API == STD_OFF */
    RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#endif /* NVM_VALID_WRITE_ALL_API */
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActReqWtAll                                      */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActReqWtAll( void )
{
    uint8 RtnStatus;
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
    RtnStatus = NvM_Job_SubActSglBlkReqWtAll( NvM_Job_stMultiReqInfo.u2BlockId );
#else /* NVM_VALID_WRITE_ALL_API == STD_OFF */
    RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#endif /* NVM_VALID_WRITE_ALL_API */
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActRspWtAll                                      */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActRspWtAll( void )
{
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
    NvM_RequestResultType NvbResult;
    P2VAR( NvM_Job_stMultiBlockRequestType, AUTOMATIC, NVM_VAR_NO_INIT ) MultiReqInfo = &NvM_Job_stMultiReqInfo;


    NvbResult = NvM_Nvb_GetOperationResult();
    if( (NvM_RequestResultType)NVM_REQ_OK == NvbResult )
    {
        if( ( NvMBlockDescriptors[MultiReqInfo->u2BlockId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            NvM_Adb_SetNvBlockProtection( MultiReqInfo->u2BlockId, NVM_ADB_WRITE_PROT_ENABLED );
        }
        NvM_Evt_WriteEndInSuccess( MultiReqInfo->u2BlockId );
        RtnStatus = NvM_Job_SubActSglBlkEndWtAll( MultiReqInfo->u2BlockId, NvbResult );
    }
    else if( (NvM_RequestResultType)NVM_REQ_NOT_OK == NvbResult )
    {
        NvM_Evt_WriteEndInFailure( MultiReqInfo->u2BlockId );
        RtnStatus = NvM_Job_SubActSglBlkEndWtAll( MultiReqInfo->u2BlockId, NvbResult );
    }
    else
    {
        /* NVM_REQ_PENDING and NVM_REQ_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActSglBlkStartCxlWtAll                           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartCxlWtAll( void )
{
    uint8 RtnStatus;
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    NvM_BlockIdType ReqBlkId = NvM_Job_stMultiReqInfo.u2BlockId;
    uint32 ExecJobId = NvM_Job_stExecuteJobInfo.u4JobId;
    /* NvM_Job_ActSglBlkStartCxlWtAll_INT30_01 */
    /* Wraparound may occur */
    NvM_BlockIdType NoticeStartBlkId;
    
    NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_CANCEL_WRT_ALL );
#if ( NVM_USE_CANCEL_NOTIFICATION == STD_ON )
    NvM_Adb_SetErrorStatus( ReqBlkId, ExecJobId, NVM_REQ_CANCELED );
#else /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */
    NvM_Adb_SetErrorStatusNonNotification( ReqBlkId, NVM_REQ_CANCELED );
#endif /* NVM_USE_CANCEL_NOTIFICATION */
    NvM_Evt_SglBlkProcEnd( ReqBlkId, ExecJobId );

    NoticeStartBlkId = ReqBlkId;
    /* NvM_Job_ActSglBlkStartCxlWtAll_INT30_001 */
    /* Wraparound may occur due to garbled RAM. */
    /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
    /* In addition, the safety manual notifies the user that the data may be corrupted. */    
    NoticeStartBlkId++;
    RtnStatus = NvM_Job_SubActEndCxlWtAll( NoticeStartBlkId );
#else /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_OFF */
    RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API */
    
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActReqCxlWtAll                                   */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActReqCxlWtAll( void )
{
    uint8 RtnStatus;
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    RtnStatus = NvM_Job_SubActSglBlkReqCxlWtAll( NvM_Job_stMultiReqInfo.u2BlockId );
#else /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_OFF */
    RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API */
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActRspCxlWtAll                                   */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActRspCxlWtAll( void )
{
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
    NvM_RequestResultType NvbResult;
    /* NvM_Job_ActRspCxlWtAll_INT30_001 */
    /* Wraparound may occur */
    NvM_BlockIdType NoticeStartBlkId;
    NvM_BlockIdType ReqBlkId = NvM_Job_stMultiReqInfo.u2BlockId;

    NvbResult = NvM_Nvb_GetOperationResult();
    if(( (NvM_RequestResultType)NVM_REQ_OK     == NvbResult )
    || ( (NvM_RequestResultType)NVM_REQ_NOT_OK == NvbResult ))
    {
        NvM_Job_SubActSBEndCxlWtAll( ReqBlkId, NvbResult );
        NoticeStartBlkId = ReqBlkId;
        /* NvM_Job_ActRspCxlWtAll_INT30_001 */
        /* Wraparound may occur due to garbled RAM. */
        /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
        /* In addition, the safety manual notifies the user that the data may be corrupted. */
        NoticeStartBlkId++;
        RtnStatus = NvM_Job_SubActEndCxlWtAll( NoticeStartBlkId );
    }
    else
    {
        /* NVM_REQ_PENDING and NVM_REQ_CANCELED is within range but is not returned, so there is no process */
        /* In other cases, No process */
    }
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelPreemptionSB                            */
/* Description   | Action function for destructive canceling single block   */
/*               | job.                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionSB( void )
{
    uint8 Rtn = NvM_Job_SubActCancelSB( NVM_JOB_REQ_CANCELED_PREEMPTION, NVM_EVT_DETAIL_ERR_CANCEL_PREEMPT );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelTimeoutSB                               */
/* Description   | Action function for destructive canceling single block   */
/*               | job.                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutSB( void )
{
    uint8 Rtn = NvM_Job_SubActCancelSB( NVM_JOB_REQ_CANCELED_TIMEOUT, NVM_EVT_DETAIL_ERR_JOB_TIMEOUT );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelUserrequestSB                           */
/* Description   | Action function for destructive canceling single block   */
/*               | job.                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestSB( void )
{
    uint8 Rtn = NvM_Job_SubActCancelSB( NVM_JOB_REQ_CANCELED_USERREQUEST, NVM_EVT_DETAIL_ERR_CANCEL_USER_REQ );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelPreemptionRdAll                         */
/* Description   | Action function for destructive canceling ReadAll.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionRdAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_READ_ALL,          /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,       /* JobId */
        NVM_JOB_REQ_CANCELED_PREEMPTION,        /* MBResult */
        NVM_REQ_CANCELED,                       /* SBResult, This argument which is not used */
        NVM_EVT_DETAIL_ERR_CANCEL_PREEMPT,      /* DetailError */
        TRUE                                    /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelTimeoutRdAll                            */
/* Description   | ction function for destructive canceling ReadAll.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutRdAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_READ_ALL,      /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,   /* JobId */
        NVM_JOB_REQ_CANCELED_TIMEOUT,       /* MBResult */
        NVM_REQ_NOT_OK,                     /* SBResult */
        NVM_EVT_DETAIL_ERR_JOB_TIMEOUT,     /* DetailError */
        TRUE                                /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelUserrequestRdAll                        */
/* Description   | ction function for destructive canceling ReadAll.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestRdAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_READ_ALL,      /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,   /* JobId */
        NVM_JOB_REQ_CANCELED_USERREQUEST,   /* MBResult */
        NVM_REQ_CANCELED,                   /* SBResult */
        NVM_EVT_DETAIL_ERR_CANCEL_USER_REQ, /* DetailError */
        TRUE                                /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelPreemptionWtAll                         */
/* Description   | Action function for destructive canceling WriteAll.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionWtAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_WRITE_ALL,         /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,       /* JobId */
        NVM_JOB_REQ_CANCELED_PREEMPTION,        /* MBResult */
        NVM_REQ_CANCELED,                       /* SBResult, This argument which is not used */
        NVM_EVT_DETAIL_ERR_CANCEL_PREEMPT,      /* DetailError */
        TRUE                                    /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelTimeoutWtAll                            */
/* Description   | ction function for destructive canceling WriteAll.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutWtAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_WRITE_ALL,     /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,   /* JobId */
        NVM_JOB_REQ_CANCELED_TIMEOUT,       /* MBResult */
        NVM_REQ_NOT_OK,                     /* SBResult */
        NVM_EVT_DETAIL_ERR_JOB_TIMEOUT,     /* DetailError */
        TRUE                                /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_ActCancelUserrequestWtAll                        */
/* Description   | ction function for destructive canceling WriteAll.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestWtAll( void )
{
    uint8 Rtn = NvM_Job_SubActCancelMB(
        NVM_SELECT_BLOCK_FOR_WRITE_ALL,     /* BlockFlag */
        NvM_Job_stExecuteJobInfo.u4JobId,   /* JobId */
        NVM_JOB_REQ_CANCELED_USERREQUEST,   /* MBResult */
        NVM_REQ_CANCELED,                   /* SBResult */
        NVM_EVT_DETAIL_ERR_CANCEL_USER_REQ, /* DetailError */
        TRUE                                /* bSBNotification */
    );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActReqRD                                      */
/* Description   | Sub action function for ReadBlock job.                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActReqRD( void )
{
    Std_ReturnType u1Result;
    uint8 u1RtnStatus;
    NvM_Nvb_OperationInformationType ReqOperationInfo;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Set request */
    ReqOperationInfo.OperationId  = NVM_NVB_OPERATION_READ;
    ReqOperationInfo.BlockId      = ExecBlockId;
    ReqOperationInfo.DstPtr       = NvM_Job_ReadDataPtr;
    ReqOperationInfo.SrcPtr       = NULL_PTR;

    /* Request */
    u1Result = NvM_Nvb_RequestOperation( &ReqOperationInfo );

    /* Check request result, set status */
    if( (Std_ReturnType)E_OK == u1Result )
    {
        u1RtnStatus = NVM_JOB_MAIN_RUN_WAIT_NORMAL;         /* Main status */
        NvM_Job_SubStatus = NVM_JOB_SUB_RD_NVB_CHK_RSP;   /* Sub status */
    }
    else
    {
        NvM_Evt_ReadEndInFailure( ExecBlockId );
        u1RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_NOT_OK );
    }

    return u1RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActRspRD                                      */
/* Description   | Service to notify RWD and the upper unit.                */
/* Preconditions | None                                                     */
/* Parameters    | JobResult                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActRspRD(
    uint8 JobResult
){
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Rwd_DataPassingResultType SetPramDataResult;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Request */
    SetPramDataResult = NvM_Rwd_ReadDataNotification( ExecBlockId );

    /* Check request result, set status */
    if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK )
    {
        NvM_Job_SubActSuccessNfyRdJob( ExecBlockId, JobResult );
        RtnStatus = NvM_Job_SubActJobEndProcSB( JobResult );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Evt_ReadEndInFailure( ExecBlockId );
        RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_NOT_OK );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING )
    {
        RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
        NvM_Job_SubStatus = NVM_JOB_SUB_RD_RSP;
    }
    else
    {
        /* No process */
    }
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActRomRcvrRspRD                               */
/* Description   | Service to recovery from ROM,                            */
/*               | and notify RWD and the upper unit.                       */
/* Preconditions | None                                                     */
/* Parameters    | JobResult                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActRomRcvrRspRD(
  uint8 JobResult
){
    uint8 RtnStatus;
    Std_ReturnType GetRomDataResult;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Request */
    GetRomDataResult = NvM_Romb_GetRomData( ExecBlockId, NvM_Job_ReadDataPtr );

    /* Check request result, set status */
    if( (Std_ReturnType)E_OK == GetRomDataResult )
    {
        NvM_Job_ReadResult = NVM_REQ_RESTORED_FROM_ROM;
        RtnStatus = NvM_Job_SubActRspRD( NVM_REQ_RESTORED_FROM_ROM );
    }
    else
    {
        NvM_Evt_ReadEndInFailure( ExecBlockId );
        RtnStatus = NvM_Job_SubActJobEndProcSB( JobResult );
    }
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_RequestWriteOperation                            */
/* Description   | Request Write Operation for NVB.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_RequestWriteOperation( void )
{
    Std_ReturnType u1Result;
    uint8 u1RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Nvb_OperationInformationType ReqOperationInfo;
    NvM_Rwd_DataPassingResultType u1SetPramDataResult;

    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    u1SetPramDataResult = NvM_Rwd_WriteDataAcquisition( ExecBlockId );
    if( u1SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK )
    {
        NvM_Job_WriteDataPtr = NvM_Rwd_GetWriteData( ExecBlockId );

        /* Set request */
        ReqOperationInfo.OperationId  = NVM_NVB_OPERATION_WRITE;
        ReqOperationInfo.BlockId      = ExecBlockId;
        ReqOperationInfo.DstPtr       = NULL_PTR;
        ReqOperationInfo.SrcPtr       = NvM_Job_WriteDataPtr;

        /* Request */
        u1Result = NvM_Nvb_RequestOperation( &ReqOperationInfo );

        /* Check request result */
        if( (Std_ReturnType)E_OK == u1Result )
        {
            u1RtnStatus = NVM_JOB_MAIN_RUN_WAIT_NORMAL;  /* Main status */
            NvM_Job_SubStatus = NVM_JOB_SUB_WT_RSP;     /* Sub status */
        }
        else
        {
            NvM_Evt_WriteEndInFailure( ExecBlockId );
            u1RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_NOT_OK );
        }
    }
    else if( u1SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Evt_WriteEndInFailure( ExecBlockId );
        u1RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_NOT_OK );
    }
    else if( u1SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING )
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_WT_REQ;     /* Sub status */
    }
    else
    {
        /* No process */
    }

    return u1RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActExecRSTR                                   */
/* Description   | Function for restoring RAM from rom data                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActExecRSTR( void )
{
    uint8 RtnStatus;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Request */
    /*  Function, "NvM_Romb_GetRomData", always returns E_OK here.                           */
    /*  This reason is below:                                                                */
    /*      The condition to accept a restore job is the requested BlockId has default data. */
    /*      If ExecBlockId has default data, function, "NvM_Romb_GetRomData", returns E_OK.  */
    (void)NvM_Romb_GetRomData( ExecBlockId, NvM_Job_ReadDataPtr );

    RtnStatus = NvM_Job_SubActDataNotifyRSTR();

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActDataNotifyRSTR                             */
/* Description   | Service to notify RWD and the upper unit.                */
/* Preconditions | None                                                     */
/* Parameters    | JobResult                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActDataNotifyRSTR( void )
{
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Rwd_DataPassingResultType SetPramDataResult;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    /* Request */
    SetPramDataResult = NvM_Rwd_ReadDataNotification( ExecBlockId );

    /* Check request result, set status */
    if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK )
    {
        NvM_Evt_RestoreEndInSuccess( ExecBlockId );
        RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_OK );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Evt_RestoreEndInFailure( ExecBlockId );
        RtnStatus = NvM_Job_SubActJobEndProcSB( NVM_REQ_NOT_OK );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING )
    {
        RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
        NvM_Job_SubStatus = NVM_JOB_SUB_RSTR_DATA_NOTIFY;
    }
    else
    {
        /* No process */
    }
    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActCancelSB                                   */
/* Description   | Function for single block action function.               */
/*               | Code-sharing about destructive cancel action.            */
/* Preconditions | None                                                     */
/* Parameters    | SBResult     : The result for single block job.          */
/* Return Value  | None.                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActCancelSB(
    uint8 SBResult,
    uint8 DetailError
){
    uint8           Rtn;
    uint32          ExecJobId = NvM_Job_stExecuteJobInfo.u4JobId;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    NvM_Nvb_SetMode( NVM_NVB_MODE_SLOW );

    NvM_Evt_DetectionDetailError( DetailError );

    if( ( ExecJobId == (uint32)NVM_JOB_READ_BLOCK ) || ( ExecJobId == (uint32)NVM_JOB_READ_PRAM_BLOCK ) )
    {
        NvM_Evt_ReadEndInFailure( ExecBlockId );
    }
    else if( ( ExecJobId == (uint32)NVM_JOB_WRITE_BLOCK ) || ( ExecJobId == (uint32)NVM_JOB_WRITE_PRAM_BLOCK ) )
    {
        NvM_Evt_WriteEndInFailure( ExecBlockId );
    }
    else if( ( ExecJobId == (uint32)NVM_JOB_RESTORE_BLOCK_DEFAULTS ) || ( ExecJobId == (uint32)NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS ) )
    {
        NvM_Evt_RestoreEndInFailure( ExecBlockId );
    }
    else
    {
        /* No process */
    }
    Rtn = NvM_Job_SubActJobEndProcSB( SBResult );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActJobEndProcSB                               */
/* Description   | Sub action function for single block jobs.               */
/*               | If any job is end completely, call this function.        */
/* Preconditions | None                                                     */
/* Parameters    | JobResult : Current job's result                         */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActJobEndProcSB(
    uint8 JobResult
){
    uint32          ExecJobId   = NvM_Job_stExecuteJobInfo.u4JobId;
    NvM_BlockIdType ExecBlockId = NvM_Job_stExecuteJobInfo.u2BlockId;

    NvM_Evt_SglBlkProcEnd( ExecBlockId, ExecJobId );
    NvM_Jobm_SingleBlockEndNotification( ExecBlockId, ExecJobId, JobResult );

    NvM_Job_SubStatus = NVM_JOB_SUB_INVALID_RND;  /* Sub status */

    return NVM_JOB_MAIN_IDLE;                   /* Main status */
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkStartRdAll                           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkStartRdAll( void )
{
    Std_ReturnType PreSglBlkProcExecResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;

    PreSglBlkProcExecResult = NvM_Job_SubActPreSglBlkProcExec();
    if( (Std_ReturnType)E_OK == PreSglBlkProcExecResult )
    {
        RtnStatus = NvM_Job_SubActSglBlkReqRdAll();
    }
    else
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_RDALL_SGLBLK_START;
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkReqRdAll                             */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqRdAll( void )
{
    boolean IsSkip;
    Std_ReturnType ReqResult;
    uint8 RtnStatus;
    NvM_BlockIdType ReqBlkId = NvM_Job_stMultiReqInfo.u2BlockId;
    NvM_Nvb_OperationInformationType ReqOperationInfo;

    IsSkip = NvM_Job_SubActIsSkpSglBlkProcRdAll( ReqBlkId );
    if( IsSkip == (boolean)TRUE )
    {
        RtnStatus = NvM_Job_SubActSglBlkEndRdAll( ReqBlkId, NVM_REQ_BLOCK_SKIPPED );
    }
    else
    {
        NvM_Evt_ReadStart( ReqBlkId, NULL_PTR );

        NvM_Job_ReadDataPtr = NvM_Rwd_GetReadDataBuffer( ReqBlkId );

        /* Set request */
        ReqOperationInfo.OperationId  = NVM_NVB_OPERATION_READ;
        ReqOperationInfo.BlockId      = ReqBlkId;
        ReqOperationInfo.DstPtr       = NvM_Job_ReadDataPtr;
        ReqOperationInfo.SrcPtr       = NULL_PTR;

        /* Request */
        ReqResult = NvM_Nvb_RequestOperation( &ReqOperationInfo );

        /* Check request result, set status */
        if( (Std_ReturnType)E_OK == ReqResult )
        {
            RtnStatus = NVM_JOB_MAIN_RUN_WAIT_NORMAL;
            NvM_Job_SubStatus = NVM_JOB_SUB_RDALL_NVB_CHK_RSP;
        }
        else
        {
            NvM_Evt_ReadEndInFailure( ReqBlkId );
            RtnStatus = NvM_Job_SubActSglBlkEndRdAll( ReqBlkId, NVM_REQ_NOT_OK );
        }
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActRspRdAll                                   */
/* Description   | Action function for ReadAll job.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActRspRdAll(
    NvM_BlockIdType BlockId,
    uint8 JobResult
){
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Rwd_DataPassingResultType SetPramDataResult;

    /* Request */
    SetPramDataResult = NvM_Rwd_ReadDataNotification( BlockId );

    /* Check request result, set status */
    if( (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK == SetPramDataResult )
    {
        NvM_Job_SubActSuccessNfyRdJob( BlockId, JobResult );
        RtnStatus = NvM_Job_SubActSglBlkEndRdAll( BlockId, JobResult );
    }
    else if( (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK == SetPramDataResult )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Evt_ReadEndInFailure( BlockId );
        RtnStatus = NvM_Job_SubActSglBlkEndRdAll( BlockId, NVM_REQ_NOT_OK );
    }
    else if( (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING == SetPramDataResult )
    {
        RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
        NvM_Job_SubStatus = NVM_JOB_SUB_RDALL_RSP;
    }
    else
    {
        /* No process */
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkEndRdAll                             */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkEndRdAll(
    NvM_BlockIdType SglBlkId,
    NvM_RequestResultType SglBlkResult
){
    uint8 RtnStatus;
    /* NvM_Job_SubActSglBlkEndRdAll_INT30_001 */
    /* Wraparound may occur */
    NvM_BlockIdType SrchSglBlkId = SglBlkId;

    NvM_Job_SetJobResultMB( SglBlkResult );
    NvM_Adb_SetErrorStatus( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId, SglBlkResult );
    NvM_Evt_SglBlkProcEnd( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId );

    /* Request next block read */
    /* NvM_Job_SubActSglBlkEndRdAll_INT30_001 */
    /* Wraparound may occur due to garbled RAM. */
    /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
    /* In addition, the safety manual notifies the user that the data may be corrupted. */
    SrchSglBlkId++;  /* Increment search start position */
    RtnStatus = NvM_Job_SubActShiftNextBlockRdAll( SrchSglBlkId );

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActRomRcvrRspRdAll                            */
/* Description   | Action function for ReadAll job.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActRomRcvrRspRdAll(
    NvM_BlockIdType BlockId,
    uint8 JobResult
){
    uint8 RtnStatus;
    Std_ReturnType GetRomDataResult;

    /* Request */
    GetRomDataResult = NvM_Romb_GetRomData( BlockId, NvM_Job_ReadDataPtr );

    /* Check request result, set status */
    if( (Std_ReturnType)E_OK == GetRomDataResult )
    {
        NvM_Job_ReadResult = NVM_REQ_RESTORED_FROM_ROM;
        RtnStatus = NvM_Job_SubActRspRdAll( BlockId, NVM_REQ_RESTORED_FROM_ROM );
    }
    else
    {
        RtnStatus = NvM_Job_SubActSglBlkEndRdAll( BlockId, JobResult );
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActShiftNextBlockRdAll                        */
/* Description   | Request next read for ReadAll.                           */
/* Preconditions | None                                                     */
/* Parameters    | u2SrchStartBlkId : start BlockId for searching           */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActShiftNextBlockRdAll(
    NvM_BlockIdType u2SrchStartBlkId
){
    Std_ReturnType ReqResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_BlockIdType NextBlkId;

    ReqResult = NvM_Job_SubActSrchNextBlkIdMB( u2SrchStartBlkId, NVM_SELECT_BLOCK_FOR_READ_ALL, &NextBlkId );
    if( (Std_ReturnType)E_OK == ReqResult )
    {
        NvM_Job_stMultiReqInfo.u2BlockId = NextBlkId;
        NvM_Evt_SglBlkProcStart( NextBlkId, NvM_Job_stExecuteJobInfo.u4JobId );
        NvM_Job_SubStatus = NVM_JOB_SUB_RDALL_SGLBLK_START;
    }
    else
    {
        RtnStatus = NvM_Job_SubActJobEndProcMB( NvM_Job_stMultiReqInfo.u1JobResult );
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkStartWtAll                           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkStartWtAll( void )
{
    boolean IsSkip;
    Std_ReturnType PreSglBlkProcExecResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_BlockIdType RequestBlockId;

    PreSglBlkProcExecResult = NvM_Job_SubActPreSglBlkProcExec();
    if( (Std_ReturnType)E_OK == PreSglBlkProcExecResult )
    {
        RequestBlockId = NvM_Job_stMultiReqInfo.u2BlockId;
        IsSkip = NvM_Job_SubActIsSkpSglBlkProcWtAll( RequestBlockId );
        if( IsSkip == (boolean)TRUE )
        {
            RtnStatus = NvM_Job_SubActSglBlkEndWtAll( RequestBlockId, NVM_REQ_BLOCK_SKIPPED );
        }
        else
        {
            NvM_Evt_WriteStart( RequestBlockId, NULL_PTR );

            RtnStatus = NvM_Job_SubActSglBlkReqWtAll( RequestBlockId );
        }
    }
    else
    {
        NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_SGLBLK_START;
    }

    return RtnStatus;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkReqWtAll                             */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqWtAll(
    NvM_BlockIdType ReqBlkId
){
    Std_ReturnType ReqResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Nvb_OperationInformationType ReqNvbInfo;
    NvM_Rwd_DataPassingResultType SetPramDataResult;

    SetPramDataResult = NvM_Rwd_WriteDataAcquisition( ReqBlkId );
    if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK )
    {
        NvM_Job_WriteDataPtr = NvM_Rwd_GetWriteData( ReqBlkId );

        /* Set request */
        ReqNvbInfo.OperationId  = NVM_NVB_OPERATION_WRITE;
        ReqNvbInfo.BlockId      = ReqBlkId;
        ReqNvbInfo.DstPtr       = NULL_PTR;
        ReqNvbInfo.SrcPtr       = NvM_Job_WriteDataPtr;

        /* Request */
        ReqResult = NvM_Nvb_RequestOperation( &ReqNvbInfo );

        /* Check request result */
        if( (Std_ReturnType)E_OK == ReqResult )
        {
            RtnStatus = NVM_JOB_MAIN_RUN_WAIT_NORMAL;       /* Main status */
            NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_RSP;    /* Sub status */
        }
        else
        {
            NvM_Evt_WriteEndInFailure( ReqBlkId );
            RtnStatus = NvM_Job_SubActSglBlkEndWtAll( ReqBlkId, NVM_REQ_NOT_OK );
        }
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Evt_WriteEndInFailure( ReqBlkId );
        RtnStatus = NvM_Job_SubActSglBlkEndWtAll( ReqBlkId, NVM_REQ_NOT_OK );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING )
    {
        /* Waiting to end the NvM_Rwd_WriteDataAcquisition  */
        NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_REQ;
    }
    else
    {
        /* No process */
    }

    return RtnStatus;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkReqCxlWtAll                          */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqCxlWtAll(
    NvM_BlockIdType ReqBlkId
){
    Std_ReturnType ReqResult;
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    NvM_Nvb_OperationInformationType ReqNvbInfo;
    NvM_Rwd_DataPassingResultType SetPramDataResult;
    /* NvM_Job_SubActSglBlkReqCxlWtAll_INT30_001 */
    /* NvM_Job_SubActSglBlkReqCxlWtAll_INT30_002 */
    /* Wraparound may occur */
    NvM_BlockIdType NoticeStartBlkId;

    SetPramDataResult = NvM_Rwd_WriteDataAcquisition( ReqBlkId );
    if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_OK )
    {
        NvM_Job_WriteDataPtr = NvM_Rwd_GetWriteData( ReqBlkId );

        /* Set request */
        ReqNvbInfo.OperationId  = NVM_NVB_OPERATION_WRITE;
        ReqNvbInfo.BlockId      = ReqBlkId;
        ReqNvbInfo.DstPtr       = NULL_PTR;
        ReqNvbInfo.SrcPtr       = NvM_Job_WriteDataPtr;

        /* Request */
        ReqResult = NvM_Nvb_RequestOperation( &ReqNvbInfo );

        /* Check request result */
        if( (Std_ReturnType)E_OK == ReqResult )
        {
            RtnStatus = NVM_JOB_MAIN_RUN_WAIT_NORMAL;       /* Main status */
            NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_RSP_CXL;   /* Sub status */
        }
        else
        {
            NvM_Job_SubActSBEndCxlWtAll( ReqBlkId, NVM_REQ_NOT_OK );
            NoticeStartBlkId = ReqBlkId;
            /* NvM_Job_SubActSglBlkReqCxlWtAll_INT30_001 */
            /* Wraparound may occur due to garbled RAM. */
            /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
            /* In addition, the safety manual notifies the user that the data may be corrupted. */
            NoticeStartBlkId++;
            RtnStatus = NvM_Job_SubActEndCxlWtAll( NoticeStartBlkId );
        }
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_NOT_OK )
    {
        NvM_Evt_DetectionErrorEvent( NVM_EVT_ERR_EVENT_REQ_FAILED );
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_SYNC_MECHANISM_NG );
        NvM_Job_SubActSBEndCxlWtAll( ReqBlkId, NVM_REQ_NOT_OK );
        NoticeStartBlkId = ReqBlkId;
        /* NvM_Job_SubActSglBlkReqCxlWtAll_INT30_002 */
        /* Wraparound may occur due to garbled RAM. */
        /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
        /* In addition, the safety manual notifies the user that the data may be corrupted. */
        NoticeStartBlkId++;
        RtnStatus = NvM_Job_SubActEndCxlWtAll( NoticeStartBlkId );
    }
    else if( SetPramDataResult == (NvM_Rwd_DataPassingResultType)NVM_RWD_REQ_PENDING )
    {
        /* Waiting to end the NvM_Rwd_WriteDataAcquisition  */
        NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_REQ_CXL;     /* Sub status */
    }
    else
    {
        /* No process */
    }

    return RtnStatus;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActSglBlkEndWtAll                             */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkEndWtAll(
    NvM_BlockIdType SglBlkId,
    NvM_RequestResultType SglBlkResult
){
    uint8 RtnStatus = NVM_JOB_MAIN_RUN_ACTIVE;
    Std_ReturnType SrchResult;
    NvM_BlockIdType NextBlkId;
    /* NvM_Job_SubActSglBlkEndWtAll_INT30_001 */
    /* Wraparound may occur */
    NvM_BlockIdType SrchSglBlkId = SglBlkId;

    NvM_Job_SetJobResultMB( SglBlkResult );

    /* Setting the result, and notification the result. */
    NvM_Adb_SetErrorStatus( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId, SglBlkResult );
    NvM_Evt_SglBlkProcEnd( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId );
    /* NvM_Job_SubActSglBlkEndWtAll_INT30_001 */
    /* Wraparound may occur due to garbled RAM. */
    /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
    /* In addition, the safety manual notifies the user that the data may be corrupted. */
    SrchSglBlkId++;     /* Increment search start position */
    SrchResult = NvM_Job_SubActSrchNextBlkIdMB( SrchSglBlkId, NVM_SELECT_BLOCK_FOR_WRITE_ALL, &NextBlkId );
    if( (Std_ReturnType)E_OK == SrchResult )
    {
        NvM_Job_stMultiReqInfo.u2BlockId = NextBlkId;
        NvM_Evt_SglBlkProcStart( NextBlkId, NvM_Job_stExecuteJobInfo.u4JobId );
        NvM_Job_SubStatus = NVM_JOB_SUB_WTALL_SGLBLK_START;
    }
    else
    {
        RtnStatus = NvM_Job_SubActJobEndProcMB( NvM_Job_stMultiReqInfo.u1JobResult );
    }

    return RtnStatus;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActSBEndCxlWtAll                              */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Job_SubActSBEndCxlWtAll(
    NvM_BlockIdType SglBlkId,
    NvM_RequestResultType SglBlkResult
){
    if( SglBlkResult == (NvM_RequestResultType)NVM_REQ_OK )
    {
        if( ( NvMBlockDescriptors[SglBlkId].NvMBlockFlags & (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE ) == (NvM_BlockFlagsType)NVM_WRITE_BLOCK_ONCE )
        {
            NvM_Adb_SetNvBlockProtection( SglBlkId, NVM_ADB_WRITE_PROT_ENABLED );
        }
        NvM_Evt_WriteEndInSuccess( SglBlkId );
    }
    else
    {
        NvM_Evt_WriteEndInFailure( SglBlkId );
    }

    /* Setting the result, and notification the result. */
    NvM_Adb_SetErrorStatus( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId, SglBlkResult );
    NvM_Evt_SglBlkProcEnd( SglBlkId, NvM_Job_stExecuteJobInfo.u4JobId );

    return;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActEndCxlWtAll                                */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActEndCxlWtAll(
    NvM_BlockIdType NoticeStartBlkId
){
    uint8 RtnStatus;
    
    NvM_Job_SubActCancelNoticeAll( NoticeStartBlkId,
                                   NVM_SELECT_BLOCK_FOR_WRITE_ALL,
                                   NvM_Job_stExecuteJobInfo.u4JobId,
                                   NVM_REQ_CANCELED,
                                   NVM_EVT_DETAIL_ERR_CANCEL_WRT_ALL );

    NvM_Nvb_SetMode( NVM_NVB_MODE_SLOW );

    RtnStatus = NvM_Job_SubActJobEndProcMB( NVM_REQ_CANCELED );

    return RtnStatus;
}
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Job_SubActSrchNextBlkIdMB                            */
/* Description   | Search next BlockId for multi block jobs.                */
/* Preconditions | None                                                     */
/* Parameters    | StartBlkId  : start BlockId for searching                */
/*               | NextBlkId   : pointer to buffer to set next BlockId      */
/*               | Flag        : The flag for the search.                   */
/*               |               Set a NvMBlockFlags of BlockDescriptors.   */
/* Return Value  | Result                                                   */
/*               |  E_OK     : found next BlockId                           */
/*               |  E_NOT_OK : not found next BlockId                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_SubActSrchNextBlkIdMB(
    NvM_BlockIdType StartBlkId,
    NvM_BlockFlagsType Flag,
    P2VAR( NvM_BlockIdType, AUTOMATIC, TYPEDEF ) NextBlkId
){
    Std_ReturnType Ret = E_NOT_OK;
    NvM_BlockIdType Index;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;

    for( Index = StartBlkId; Index <= UserBlkIdMax; Index++ )
    {
        if( Flag == ( NvMBlockDescriptors[Index].NvMBlockFlags & Flag ) )
        {
            *NextBlkId = Index;
            Ret = E_OK;
            break;
        }
    }

    return Ret;
}

/****************************************************************************/
/* Function Name | NvM_Job_SetJobResultMB                                   */
/* Description   | Set job result for ReadAll                               */
/* Preconditions | None                                                     */
/* Parameters    | u1JobRes : job result of one block read                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_SetJobResultMB(
    uint8 JobResult
){
    if( ( JobResult != (uint8)NVM_REQ_OK )
     && ( JobResult != (uint8)NVM_REQ_BLOCK_SKIPPED ) )
    {
        NvM_Job_stMultiReqInfo.u1JobResult = NVM_REQ_NOT_OK;
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActCancelMB                                   */
/* Description   | Function for multi block action function.                */
/*               | Code-sharing about destructive cancel action.            */
/* Preconditions | None                                                     */
/* Parameters    | BlockFlag    : The flag to pick up multi block ID.       */
/*               | JobId        : Current job id.                           */
/*               | MBResult     : The result for multi block job.           */
/*               | SBResult     : Each result for single block job in       */
/*               |                multi block job.                          */
/*               | bSBNotification: SB notification of necessity.           */
/* Return Value  | None.                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActCancelMB(
    NvM_BlockFlagsType BlockFlag,
    uint32 JobId,
    uint8 MBResult,
    uint8 SBResult,
    uint8 DetailError,
    boolean bSBNotification
){
    uint8           Rtn;
    /* NvM_Job_SubActCancelMB_INT30_001 */ 
    /* Wraparound may occur */
    NvM_BlockIdType CancelBlockId = NvM_Job_stMultiReqInfo.u2BlockId;

    NvM_Nvb_SetMode( NVM_NVB_MODE_SLOW );

    NvM_Evt_DetectionDetailError( DetailError );

    if( JobId == (uint32)NVM_JOB_READ_ALL )
    {
        NvM_Evt_ReadEndInFailure( CancelBlockId );
    }
    else if( JobId == (uint32)NVM_JOB_WRITE_ALL )
    {
        NvM_Evt_WriteEndInFailure( CancelBlockId );
    }
    else
    {
        /* No process */
    }

    /* Executed job result notification */
    if( (boolean)TRUE == bSBNotification )
    {
#if ( NVM_USE_CANCEL_NOTIFICATION == STD_ON )
        NvM_Adb_SetErrorStatus( CancelBlockId, JobId, SBResult );
#else /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */
        NvM_Adb_SetErrorStatusNonNotification( CancelBlockId, SBResult );
#endif /* NVM_USE_CANCEL_NOTIFICATION */
    }
    NvM_Evt_SglBlkProcEnd( CancelBlockId, JobId );

    /* Pending job result notification */
    if( (boolean)TRUE == bSBNotification )
    {
        /* NvM_Job_SubActCancelMB_INT30_001 */
        /* Wraparound may occur due to garbled RAM. */
        /* In Case wraparound occurs block processing may be performed again, but the error state does not continue. */
        /* In addition, the safety manual notifies the user that the data may be corrupted. */
        CancelBlockId++; /* Incremental notification start position */
        NvM_Job_SubActCancelNoticeAll( CancelBlockId, BlockFlag, JobId, SBResult, DetailError );
    }

    Rtn = NvM_Job_SubActJobEndProcMB( MBResult );

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActCancelNoticeAll                            */
/* Description   | Function for Action function.                            */
/*               | Notification about canceling job of block.               */
/* Preconditions | None                                                     */
/* Parameters    | StartBlockId : Starting position BlockId for searching   */
/*               |                multi block ID.                           */
/*               | BlockFlag    : The flag to pick up multi block ID.       */
/*               | JobId        : Current job id.                           */
/*               | Result       : The result for notification to other unit.*/
/* Return Value  | None.                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_SubActCancelNoticeAll(
    NvM_BlockIdType StartBlockId,
    NvM_BlockFlagsType BlockFlag,
    uint32 JobId,
    uint8 Result,
    uint8 DetailError
){
    NvM_BlockIdType Index;
    NvM_BlockIdType UserBlkIdMax = NVM_USER_BLOCKID_MAX;
#if ( NVM_USE_CANCEL_NOTIFICATION == STD_OFF )
    NvM_BlockIdType FirstTgtBlockId = UserBlkIdMax;
#endif /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */

#if ( NVM_USE_CANCEL_NOTIFICATION == STD_ON )
    for( Index = StartBlockId; Index <= UserBlkIdMax; Index++ )
    {
        if( BlockFlag == ( NvMBlockDescriptors[Index].NvMBlockFlags & BlockFlag ))
        {
            NvM_Evt_SglBlkProcStart( Index, JobId );
            NvM_Evt_DetectionDetailError( DetailError );
            NvM_Adb_SetErrorStatus( Index, JobId, Result );
            NvM_Evt_SglBlkProcEnd( Index, JobId );
        }
    }
#else /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */
    for( Index = StartBlockId; Index <= UserBlkIdMax; Index++ )
    {
        if( BlockFlag == ( NvMBlockDescriptors[Index].NvMBlockFlags & BlockFlag ))
        {
            NvM_Evt_SglBlkProcStart( Index, JobId );
            NvM_Evt_DetectionDetailError( DetailError );
            NvM_Adb_SetErrorStatusNonNotification( Index, Result );
            NvM_Evt_SglBlkProcEnd( Index, JobId );

            FirstTgtBlockId = Index;

            break;
        }
    }

    FirstTgtBlockId++;
    for( Index = FirstTgtBlockId; Index <= UserBlkIdMax; Index++ )
    {
        if( BlockFlag == ( NvMBlockDescriptors[Index].NvMBlockFlags & BlockFlag ))
        {
            NvM_Adb_SetErrorStatusNonNotification( Index, Result );
        }
    }
#endif /* NVM_USE_CANCEL_NOTIFICATION */

    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActJobEndProcMB                               */
/* Description   | Sub action function for multi block jobs.                */
/*               | If any job is end completely, call this function.        */
/* Preconditions | None                                                     */
/* Parameters    | JobResult : Current job's result                         */
/* Return Value  | Next status.                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, NVM_CODE )
NvM_Job_SubActJobEndProcMB(
    uint8 JobResult
){
    NvM_Jobm_MultiBlockEndNotification( NvM_Job_stExecuteJobInfo.u4JobId, JobResult );

    NvM_Job_stMultiReqInfo.u1JobResult   = NVM_REQ_OK;
    NvM_Job_stMultiReqInfo.u2BlockId     = NVM_BLOCKID_INVALID;

    NvM_Job_SubStatus = NVM_JOB_SUB_INVALID_RND;  /* Sub status */

    return NVM_JOB_MAIN_IDLE;                   /* Main status */
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActSuccessNfyRdJob                            */
/* Description   | This function notify EVT that read job is successful.    */
/* Preconditions | None                                                     */
/* Parameters    |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Job_SubActSuccessNfyRdJob(
    NvM_BlockIdType ExecBlockId,
    uint8           ExecJobResult
){
    if( ExecJobResult == (uint8)NVM_REQ_OK )
    {
        NvM_Evt_ReadEndInSuccess( ExecBlockId );
    }
    else if( ExecJobResult == (uint8)NVM_REQ_RESTORED_FROM_ROM )
    {
        NvM_Evt_RestoreEndInSuccess( ExecBlockId );
    }
    else
    {
        /* No process */
    }
    return;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActPreSglBlkProcExec                          */
/* Description   | Check permission to execute process before execution     */
/*               | of process.                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Permission to execute process.                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_SubActPreSglBlkProcExec( void )
{
    Std_ReturnType Rtn = E_NOT_OK;
    Std_ReturnType CheckJobExecResult;

    CheckJobExecResult = Mscd_Cnfm_CheckJobExecHook();
    if( (Std_ReturnType)E_OK == CheckJobExecResult )
    {
        NvM_Jobm_NfyIsSglBlkProcStart( TRUE );
        Rtn = E_OK;
    }
    else
    {
        NvM_Jobm_NfyIsSglBlkProcStart( FALSE );
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActIsSkpSglBlkProcRdAll                       */
/* Description   | Judge whether "BlockId" corresponding job must           */
/*               | be skipped.                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | IsSkip  : Boolean variable which expresses follows.      */
/*               |   TRUE  : The job must be skipped.                       */
/*               |   FALSE : The job must not be skipped.                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Job_SubActIsSkpSglBlkProcRdAll(
    NvM_BlockIdType BlockId
){
    boolean IsSkip = FALSE;
    NvM_Adb_RamBlockStatusType RamBlockStatus;
    Std_ReturnType GetRamBlockStatusResult;

    GetRamBlockStatusResult = NvM_Adb_GetRamBlockStatus( BlockId, &RamBlockStatus );
    if( GetRamBlockStatusResult == (Std_ReturnType)E_OK )
    {
        if( RamBlockStatus == (NvM_Adb_RamBlockStatusType)NVM_ADB_PRAM_VALID_CHANGED )
        {
            NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_READ_TO_VALID_RAM_SKIP );
            IsSkip = TRUE;
        }
    }
    
    return IsSkip;
}

/****************************************************************************/
/* Function Name | NvM_Job_SubActIsSkpSglBlkProcWtAll                       */
/* Description   | Judge whether "BlockId" corresponding job must           */
/*               | be skipped.                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | IsSkip  : Boolean variable which expresses follows.      */
/*               |   TRUE  : The job must be skipped.                       */
/*               |   FALSE : The job must not be skipped.                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( boolean, NVM_CODE )
NvM_Job_SubActIsSkpSglBlkProcWtAll(
    NvM_BlockIdType BlockId
){
    boolean IsSkip = FALSE;
    NvM_Adb_WriteProtectStatusType WriteProtectStatus;
    NvM_Adb_RamBlockStatusType RamBlockStatus;
    Std_ReturnType GetRamBlockStatusResult;

    WriteProtectStatus = NvM_Adb_GetNvBlockProtection( BlockId );
    if(  WriteProtectStatus == (NvM_Adb_WriteProtectStatusType)NVM_ADB_WRITE_PROT_ENABLED )
    {
        NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_WRT_TO_PROT_SKIP );
        IsSkip = TRUE;
    }
    else
    {
        GetRamBlockStatusResult = NvM_Adb_GetRamBlockStatus( BlockId, &RamBlockStatus );
        if( GetRamBlockStatusResult == (Std_ReturnType)E_OK )
        {
            if( RamBlockStatus == (NvM_Adb_RamBlockStatusType)NVM_ADB_PRAM_VALID_UNCHANGED )
            {
                NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_WRT_FRM_UNCHANGE_RAM_SKIP );
                IsSkip = TRUE;
            }
            else if( RamBlockStatus == (NvM_Adb_RamBlockStatusType)NVM_ADB_PRAM_INVALID_UNCHANGED )
            {
                NvM_Evt_DetectionDetailError( NVM_EVT_DETAIL_ERR_WRT_FRM_INVALID_RAM_SKIP );
                IsSkip = TRUE;
            }
            else
            {
                /* No process */
            }
        }
    }
    return IsSkip;
}
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/12/06                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
