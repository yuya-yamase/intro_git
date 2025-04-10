/* NvM_Jobq.h v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBQ/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOBQ_H
#define     NVM_JOBQ_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "NvM_Jobm.h"

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Jobq_Init( void );

FUNC( void, NVM_CODE )
NvM_Jobq_Abort( void );

FUNC( boolean, NVM_CODE )
NvM_Jobq_SglQueueIsNotEmpty( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfo(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglGetJobInfoSrchImm(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglEnqueue(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) SrcJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeue(
    NvM_BlockIdType SrcBlockId,
    uint32          SrcJobId,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_SglDequeueSrchBlockId(
    NvM_BlockIdType SrcBlockId,
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) DstJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_MultiGetJobInfo(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) JobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_MultiEnqueue(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) JobInfo
);

FUNC( void, NVM_CODE )
NvM_Jobq_MultiDequeue( void );

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobq_CxlWtAllGetJobInfo( void );

FUNC( void, NVM_CODE )
NvM_Jobq_CxlWtAllEnqueue( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

FUNC( void, NVM_CODE )
NvM_Jobq_CxlWtAllDequeue( void );

FUNC( boolean, NVM_CODE )
NvM_Jobq_ChkImmJob(
    NvM_BlockIdType BlockId,
    uint32          JobId
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOBQ_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
