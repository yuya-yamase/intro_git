/* NvM_Job_Internal.h v2-1-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOB/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOB_INTERNAL_H
#define     NVM_JOB_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "NvM_Jobm.h"
#include "NvM_Lib.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Internal main status */
#define NVM_JOB_MAIN_IDLE                        (0x01U)
#define NVM_JOB_MAIN_RUN_ACTIVE                  (0x02U)
#define NVM_JOB_MAIN_RUN_WAIT_NORMAL             (0x04U)
#define NVM_JOB_MAIN_WAIT_CANCEL_PREEMPTION      (0x08U)
#define NVM_JOB_MAIN_WAIT_CANCEL_TIMEOUT         (0x10U)
#define NVM_JOB_MAIN_WAIT_CANCEL_USERREQUEST     (0x20U)

/* Internal sub status */
#define NVM_JOB_SUB_COMMON_SEQ_00                (0U)
#define NVM_JOB_SUB_COMMON_SEQ_01                (1U)
#define NVM_JOB_SUB_COMMON_SEQ_02                (2U)
#define NVM_JOB_SUB_COMMON_SEQ_03                (3U)
#define NVM_JOB_SUB_COMMON_SEQ_04                (4U)
#define NVM_JOB_SUB_COMMON_SEQ_05                (5U)
#define NVM_JOB_SUB_INVALID_SEQ                  (0xFFU)

#define NVM_JOB_SUB_COMMON_NUM                   (6U)

#define NVM_JOB_SUB_INVALID_RND                  (NVM_RND_NUM_UINT32_00)

/* ReadBlock */
#define NVM_JOB_SUB_RD_START                     (NVM_RND_NUM_UINT32_01)
#define NVM_JOB_SUB_RD_NVB_CHK_RSP               (NVM_RND_NUM_UINT32_02)
#define NVM_JOB_SUB_RD_RSP                       (NVM_RND_NUM_UINT32_03)
/* WriteBlock */
#define NVM_JOB_SUB_WT_START                     (NVM_RND_NUM_UINT32_01)
#define NVM_JOB_SUB_WT_REQ                       (NVM_RND_NUM_UINT32_02)
#define NVM_JOB_SUB_WT_RSP                       (NVM_RND_NUM_UINT32_03)
/* RestoreBlockDefaults */
#define NVM_JOB_SUB_RSTR_START                   (NVM_RND_NUM_UINT32_01)
#define NVM_JOB_SUB_RSTR_DATA_NOTIFY             (NVM_RND_NUM_UINT32_02)
/* ReadAll */
#define NVM_JOB_SUB_RDALL_SGLBLK_START           (NVM_RND_NUM_UINT32_01)
#define NVM_JOB_SUB_RDALL_NVB_CHK_RSP            (NVM_RND_NUM_UINT32_02)
#define NVM_JOB_SUB_RDALL_RSP                    (NVM_RND_NUM_UINT32_03)
/* WriteAll */
#define NVM_JOB_SUB_WTALL_SGLBLK_START           (NVM_RND_NUM_UINT32_01)
#define NVM_JOB_SUB_WTALL_REQ                    (NVM_RND_NUM_UINT32_02)
#define NVM_JOB_SUB_WTALL_RSP                    (NVM_RND_NUM_UINT32_03)
#define NVM_JOB_SUB_WTALL_SGLBLK_START_CXL       (NVM_RND_NUM_UINT32_04)
#define NVM_JOB_SUB_WTALL_REQ_CXL                (NVM_RND_NUM_UINT32_05)
#define NVM_JOB_SUB_WTALL_RSP_CXL                (NVM_RND_NUM_UINT32_06)

/* sub action functions number */
#define NVM_JOB_ACTNUM_RD                        (3U)
#define NVM_JOB_ACTNUM_WT                        (3U)
#define NVM_JOB_ACTNUM_RSTR                      (2U)
#define NVM_JOB_ACTNUM_RD_ALL                    (3U)
#define NVM_JOB_ACTNUM_WT_ALL                    (6U)

/* JobId sequencial number */
#define NVM_JOB_JOBID_RD                         (0x00000000U)
#define NVM_JOB_JOBID_WT                         (0x00000001U)
#define NVM_JOB_JOBID_RSTR_DFLTS                 (0x00000002U)
#define NVM_JOB_JOBID_RD_PRM                     (0x00000003U)
#define NVM_JOB_JOBID_WT_PRM                     (0x00000004U)
#define NVM_JOB_JOBID_RSTR_PRM_DFLTS             (0x00000005U)
#define NVM_JOB_JOBID_RD_ALL                     (0x00000006U)
#define NVM_JOB_JOBID_WT_ALL                     (0x00000007U)

#define NVM_JOB_JOBID_NUM                        (0x00000008U)

#define NVM_JOB_JOBID_INVALID                    (0xFFU)

/* Job class */
#define NVM_JOB_JOBCLASS_SINGLE                  (0U)
#define NVM_JOB_JOBCLASS_MULTI                   (1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef P2FUNC( uint8, NVM_CODE, NvM_Job_ActFuncType )( void );

typedef struct{
    CONST( NvM_Job_ActFuncType, NVM_CONST )                           ptFuncStartJob;
    uint8                                                             u1FuncExecJobNum;
    P2CONST( AB_83_ConstV NvM_Job_ActFuncType, NVM_CONST, NVM_CONST ) arptFuncExecJob;
    CONST( NvM_Job_ActFuncType, NVM_CONST )                           ptFuncCancelPreemption;
    CONST( NvM_Job_ActFuncType, NVM_CONST )                           ptFuncCancelTimeout;
    CONST( NvM_Job_ActFuncType, NVM_CONST )                           ptFuncCancelUserrequest;
} NvM_Job_stJobActTblType;

typedef struct {
    uint8                   u1JobResult;
    NvM_BlockIdType         u2BlockId;
} NvM_Job_stMultiBlockRequestType;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR      ( uint8,                            NVM_VAR_NO_INIT )             NvM_Job_u1MainStatus;
extern VAR      ( uint32,                           NVM_VAR_NO_INIT )             NvM_Job_SubStatus;
extern VAR      ( NvM_Jobm_stJobInfomationType,     NVM_VAR_NO_INIT )             NvM_Job_stExecuteJobInfo;
extern P2VAR    ( uint8,                            NVM_VAR_NO_INIT,    TYPEDEF ) NvM_Job_ReadDataPtr;
extern P2CONST  ( uint8,                            NVM_VAR_NO_INIT,    TYPEDEF ) NvM_Job_WriteDataPtr;
extern VAR      ( NvM_Job_stMultiBlockRequestType,  NVM_VAR_NO_INIT )             NvM_Job_stMultiReqInfo;
extern VAR      ( uint8,                            NVM_VAR_NO_INIT )             NvM_Job_ReadResult;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,      NVM_CONST ) NvM_Job_arstJobIdBitToSeqNumPair[NVM_JOB_JOBID_NUM];
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,     NVM_CONST ) NvM_Job_arstJobIdBitToSeqNumTbl;

extern CONST( AB_83_ConstV uint8,                             NVM_CONST ) NvM_Job_JobIdSeqToJobClass[NVM_JOB_JOBID_NUM];

extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,      NVM_CONST ) NvM_Job_SubStatusBitToSeqNumPair[NVM_JOB_SUB_COMMON_NUM];
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,     NVM_CONST ) NvM_Job_SubStatusBitToSeqNumTbl;

extern CONST( AB_83_ConstV NvM_Job_stJobActTblType,           NVM_CONST ) NvM_Job_arActTbl[NVM_JOB_JOBID_NUM];

extern CONST( AB_83_ConstV NvM_Job_ActFuncType,               NVM_CONST ) NvM_Job_arFuncExecJobTblRD[NVM_JOB_ACTNUM_RD];
extern CONST( AB_83_ConstV NvM_Job_ActFuncType,               NVM_CONST ) NvM_Job_arFuncExecJobTblWT[NVM_JOB_ACTNUM_WT];
extern CONST( AB_83_ConstV NvM_Job_ActFuncType,               NVM_CONST ) NvM_Job_arFuncExecJobTblRSTR[NVM_JOB_ACTNUM_RSTR];
extern CONST( AB_83_ConstV NvM_Job_ActFuncType,               NVM_CONST ) NvM_Job_arFuncExecJobTblRdAll[NVM_JOB_ACTNUM_RD_ALL];
extern CONST( AB_83_ConstV NvM_Job_ActFuncType,               NVM_CONST ) NvM_Job_FuncExecJobTblWtAll[NVM_JOB_ACTNUM_WT_ALL];

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>


FUNC( void, NVM_CODE )
NvM_Job_RamInit( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_ChkExecBlockId(
    uint32 JobId
);

FUNC( void, NVM_CODE )
NvM_Job_StateChangeAct(
    uint8 CallMode,
    uint32 JobId
);

FUNC( uint8, NVM_CODE )
NvM_Job_StateChangeActForWait(
    uint32 JobId,
    uint8 LocalMainStatus
);

/* Action Functions */
/* ReadBlock */
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRD( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActNvbChkRspRD( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActRspRD( void );

/* WriteBlock */
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartWT( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActReqWT( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActRspWT( void );

/* RestoreBlockDefaults */
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRSTR( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActDataNotifyRSTR( void );

/* ReadAll */
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActNvbChkRspRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActRspRdAll( void );

/* WriteAll */
FUNC( uint8, NVM_CODE )
NvM_Job_ActStartWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActReqWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActRspWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActSglBlkStartCxlWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActReqCxlWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActRspCxlWtAll( void );

/* Cancel */
FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionSB( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutSB( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestSB( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelPreemptionWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelTimeoutWtAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_ActCancelUserrequestWtAll( void );

/* Sub Functions */
/* ReadBlock */
FUNC( uint8, NVM_CODE )
NvM_Job_SubActReqRD( void );

FUNC( uint8, NVM_CODE )
NvM_Job_SubActRspRD(
    uint8 JobResult
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActRomRcvrRspRD(
  uint8 JobResult 
);

/* WriteBlock */
FUNC( uint8, NVM_CODE )
NvM_Job_RequestWriteOperation( void );

/* RestoreBlockDefaults */
FUNC( uint8, NVM_CODE )
NvM_Job_SubActExecRSTR( void );

FUNC( uint8, NVM_CODE )
NvM_Job_SubActDataNotifyRSTR( void );

/* SingleBlockJob Common */
FUNC( uint8, NVM_CODE )
NvM_Job_SubActCancelSB(
    uint8 SBResult,
    uint8 DetailError
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActJobEndProcSB(
    uint8 JobResult
);

/* ReadAll */
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkStartRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqRdAll( void );

FUNC( uint8, NVM_CODE )
NvM_Job_SubActRspRdAll(
    NvM_BlockIdType BlockId,
    uint8 JobResult
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkEndRdAll(
    NvM_BlockIdType SglBlkId, 
    NvM_RequestResultType SglBlkResult
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActRomRcvrRspRdAll(
    NvM_BlockIdType BlockId,
    uint8 JobResult
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActShiftNextBlockRdAll(
    NvM_BlockIdType u2SrchStartBlkId
);

/* WriteAll */
#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkStartWtAll( void );
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqWtAll(
    NvM_BlockIdType ReqBlkId
);
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkReqCxlWtAll(
    NvM_BlockIdType ReqBlkId
);
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActSglBlkEndWtAll(
    NvM_BlockIdType SglBlkId, 
    NvM_RequestResultType SglBlkResult
);
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Job_SubActSBEndCxlWtAll(
    NvM_BlockIdType SglBlkId, 
    NvM_RequestResultType SglBlkResult
);
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Job_SubActEndCxlWtAll(
    NvM_BlockIdType NoticeStartBlkId
);
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

/* MultiBlockJob Common */
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_SubActSrchNextBlkIdMB(
    NvM_BlockIdType StartBlkId,
    NvM_BlockFlagsType Flag,
    P2VAR( NvM_BlockIdType, AUTOMATIC, TYPEDEF ) NextBlkId
);

FUNC( void, NVM_CODE )
NvM_Job_SetJobResultMB(
    uint8 JobResult
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActCancelMB(
    NvM_BlockFlagsType BlockFlag,
    uint32 JobId,
    uint8 MBResult,
    uint8 SBResult,
    uint8 DetailError,
    boolean bSBNotification
);

FUNC( void, NVM_CODE )
NvM_Job_SubActCancelNoticeAll(
    NvM_BlockIdType StartBlockId,
    NvM_BlockFlagsType BlockFlag,
    uint32 JobId,
    uint8 Result,
    uint8 DetailError
);

FUNC( uint8, NVM_CODE )
NvM_Job_SubActJobEndProcMB(
    uint8 JobResult
);

/* Common Read job(Read, ReadAll) */
FUNC( void, NVM_CODE )
NvM_Job_SubActSuccessNfyRdJob(
    NvM_BlockIdType ExecBlockId,
    uint8           ExecJobResult
);

/* Common */
FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_SubActPreSglBlkProcExec( void );

FUNC( boolean, NVM_CODE )
NvM_Job_SubActIsSkpSglBlkProcRdAll(
    NvM_BlockIdType BlockId
);

#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( boolean, NVM_CODE )
NvM_Job_SubActIsSkpSglBlkProcWtAll(
    NvM_BlockIdType BlockId
);
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOB_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
