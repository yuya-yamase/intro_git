/* MemAcc_JobCtl.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemAcc JobCtl HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_JOBCTL_H
#define MEMACC_JOBCTL_H


#include "MemAcc.h"
#include "MemAcc_Mpu_Const.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Job control stats */
#define MEMACC_JOBCTL_IDLE               ((uint8)0x00U)        /* Job nothing */
#define MEMACC_JOBCTL_REQUEST            ((uint8)0x01U)        /* Job request monitoring */
#define MEMACC_JOBCTL_RUN                ((uint8)0x02U)        /* Job running */

/* Job status */
#define MEMACC_JOBCTL_ST_IDLE            ((uint8)0x00U)        /* Job status idle */
#define MEMACC_JOBCTL_ST_WAIT            ((uint8)0x01U)        /* Job status wait */
#define MEMACC_JOBCTL_ST_RUN             ((uint8)0x02U)        /* Job status running */
#define MEMACC_JOBCTL_ST_SUSPEND         ((uint8)0x03U)        /* Job status suspend */
#define MEMACC_JOBCTL_ST_CANCEL          ((uint8)0x04U)        /* Job status cancel */

/* Driver type */
#define MEMACC_JOBCTL_CODEFLASH_DRIVER   ((uint8)0x00U)        /* Code Flash Driver */
#define MEMACC_JOBCTL_DATAFLASH_DRIVER   ((uint8)0x01U)        /* Data Flash Driver */
#define MEMACC_JOBCTL_NOTUSED_DRIVER     ((uint8)0xFFU)        /* No target driver */

/* Job type */
#define MEMACC_JOBCTL_JOB_NONE           ((uint8)0x00U)        /* No job */
#define MEMACC_JOBCTL_JOB_WRITE          ((uint8)0x01U)        /* Write */
#define MEMACC_JOBCTL_JOB_READ           ((uint8)0x02U)        /* Read */
#define MEMACC_JOBCTL_JOB_ERASE          ((uint8)0x03U)        /* Erase */
#define MEMACC_JOBCTL_JOB_MEMHWSPECIFIC  ((uint8)0x04U)        /* Hardware specific service */
#define MEMACC_JOBCTL_JOB_BLANKCHECK     ((uint8)0x05U)        /* Blank check */

/* Instruct job execution after priority judged */
#define MEMACC_JOBCTL_PRI_NOTING         ((uint8)0x00U)        /* Not need to run */
#define MEMACC_JOBCTL_PRI_JOBSTART       ((uint8)0x01U)        /* Start job */
#define MEMACC_JOBCTL_PRI_SUSPEND        ((uint8)0x02U)        /* Execute suspend */
#define MEMACC_JOBCTL_PRI_RESUME         ((uint8)0x03U)        /* Execute resume */

/* Result of suspend */
#define MEMACC_JOBCTL_SUSPEND_NONE       ((uint8)0x00U)        /* Not execute */
#define MEMACC_JOBCTL_SUSPEND_SUCCESS    ((uint8)0x01U)        /* Suspend success */
#define MEMACC_JOBCTL_SUSPEND_FAILED     ((uint8)0x02U)        /* Suspend failed */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Job control information */
typedef struct
{
    uint8                       jobControlStatus;              /* Job control status */
    MemAcc_AddressAreaIdType    jobAddressArea;                /* Address area of current job */
    uint8                       suspendStatus;                 /* Suspend status */
    MemAcc_AddressAreaIdType    suspendAddressArea;            /* Address area of susdended */
    uint8                       jobCancelStatus;               /* Job cancel status */
    uint8                       jobRamGarbled;                 /* RAM Garbled */
} MemAcc_JobCtlInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_Init( void );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobControlStatus( uint8 u1_jobControlStatus );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_UnlockEvent( MemAcc_AddressAreaIdType u1_areaid );
FUNC( uint8 , MEMACC_CODE ) MemAcc_JobCtl_TargetDriver( MemAcc_AddressAreaIdType targetAreaId );

FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_Cancel( MemAcc_AddressAreaIdType addressAreaId );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_Write( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_Read( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType sourceAddress, P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF ) destinationDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_Erase( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_BlankCheck( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
#endif /* MEMACC_DEVICE_CYT2Bx */
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_HwSpecificService( MemAcc_AddressAreaIdType addressAreaId, MemAcc_HwIdType hwId, MemAcc_MemHwServiceIdType hwServiceId, P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF ) dataPtr, P2VAR( MemAcc_LengthType, AUTOMATIC, TYPEDEF ) lengthPtr );

FUNC( uint8, MEMACC_CODE ) MemAcc_JobCtl_PriorityJudge( P2VAR( MemAcc_AddressAreaIdType, AUTOMATIC, TYPEDEF ) pt_targetAreaId, P2VAR( MemAcc_JobRequestManageType, AUTOMATIC, TYPEDEF ) pt_jobRequest );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_GetJobRequest( MemAcc_AddressAreaIdType addressAreaId, P2VAR( MemAcc_JobRequestManageType, AUTOMATIC, TYPEDEF ) pt_jobRequest );

FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobPending( MemAcc_AddressAreaIdType addressAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobEnd( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobResultType jobResult );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobSuspend( MemAcc_AddressAreaIdType addressAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobResume( MemAcc_AddressAreaIdType addressAreaId, uint8 u1_jobStatus );

FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_ChkInputAreaDt( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobType jobStatus, MemAcc_AddressType addressStart, MemAcc_LengthType length );

FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetExtJobInfoStatus( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobStatusType setJobStatus );
FUNC( MemAcc_JobStatusType, MEMACC_CODE ) MemAcc_JobCtl_GetExtJobInfoStatus( MemAcc_AddressAreaIdType addressAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetExtJobInfoType( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobType setJobType );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetExtJobInfoResult( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobResultType setJobResult );
FUNC( MemAcc_JobResultType, MEMACC_CODE ) MemAcc_JobCtl_GetExtJobInfoResult( MemAcc_AddressAreaIdType addressAreaId );

FUNC( uint8, MEMACC_CODE ) MemAcc_JobCtl_ExecJobSuspend( void );

FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_JobCtl_CheckRAM( void );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetJobCtlInfoSub( void );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetRAMSub( MemAcc_AddressAreaIdType addressAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetRAMSubAll( void );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_SetRAMGarbled( void );
FUNC( uint8, MEMACC_CODE ) MemAcc_JobCtl_GetRAMGarbled( void );
FUNC( void, MEMACC_CODE ) MemAcc_JobCtl_ClearJobCtlInfo( void );


#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

/* Job execution control information */
extern VAR ( MemAcc_JobCtlInfoType, MEMACC_VAR_NO_INIT )    MemAcc_JobCtlInfo;
extern VAR ( MemAcc_JobCtlInfoType, MEMACC_VAR_NO_INIT )    MemAcc_JobCtlInfoSub;

#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* MEMACC_JOBCTL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

