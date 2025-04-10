/* NvM_Job.h v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOB_H
#define     NVM_JOB_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "NvM_Jobm.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* JOB status */
#define NVM_JOB_IDLE                 (0x00U)
#define NVM_JOB_BUSY                 (0x01U)
#define NVM_JOB_BUSY_CANCEL          (0x02U)

/* JOB destructive cancel kind */
#define NVM_JOB_DSTRCTV_CXL_PREEMPTION  (0x00U)
#define NVM_JOB_DSTRCTV_CXL_TIMEOUT     (0x01U)
#define NVM_JOB_DSTRCTV_CXL_USERREQUEST (0x02U)

/* JOB extended request result */
#define NVM_JOB_REQ_CANCELED_PREEMPTION     (0x16U)
#define NVM_JOB_REQ_CANCELED_TIMEOUT        (0x26U)
#define NVM_JOB_REQ_CANCELED_USERREQUEST    (0x36U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8 NvM_Job_StatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Job_Init( void );

FUNC( NvM_Job_StatusType, NVM_CODE )
NvM_Job_GetStatus(
    P2VAR( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) stJobInfo
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_RequestJob(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) stJobInfo
);

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Job_CancelJob( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

FUNC( void, NVM_CODE )
NvM_Job_DestructiveCancelJob(
    uint8 u1Kind
);

FUNC( void, NVM_CODE )
NvM_Job_MainFunction(
    uint8 CallMode
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Job_GetExecBlockId(
    P2VAR( NvM_BlockIdType, AUTOMATIC, TYPEDEF ) BlockIdPtr
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/12/06                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
