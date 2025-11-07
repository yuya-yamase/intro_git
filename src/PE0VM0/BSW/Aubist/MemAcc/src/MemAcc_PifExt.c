/* MemAcc_PifExt.c v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include <MemAcc_Ext.h>
#include "../inc/MemAcc_Api.h"
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/*****************************************************************************
      Synchronous Function
*****************************************************************************/
/****************************************************************************/
/* Function Name | MemAcc_MainFunction_ExtNonPeriodic                       */
/* Description   | This function is invoked from a non-periodic process     */
/*               | and provides a function to execute a job that            */
/*               | has received a request.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_MainFunction_ExtNonPeriodic( void )
{
    uint8 u1_ramGarbled;
    Std_ReturnType u1_funcRet;

    u1_ramGarbled = MemAcc_JobCtl_GetRAMGarbled();
    u1_funcRet = MemAcc_JobCtl_CheckRAM();
    if( ((uint8)STD_OFF == u1_ramGarbled) && ((Std_ReturnType)E_OK == u1_funcRet) )
    {
        MemAcc_Api_NonPeriodic_Execute();
    }
    else
    {
        MemAcc_Api_AbortJob();
    }

    MemAcc_SemCtl_Execute();
    MemAcc_JobCtl_SetRAMSubAll();

} /* MemAcc_MainFunction_ExtNonPeriodic */

/****************************************************************************/
/* Function Name | MemAcc_ExtDfPreExecution                               */
/* Description   | This function checks whether the data flash              */
/*               | can be accessed                                          */
/* Preconditions | None                                                     */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                 Data flash accessible               */
/*               | E_NOT_OK             Data flash inaccessible             */
/* Notes         | (1) If address area ID=0 is locked, E_NOT_OK is returned.*/
/*               | (2) If the address area ID=0 is executing a job,         */
/*               |     E_NOT_OK is returned.                                */
/*               |     If the job status of the Fls module is not IDLE,     */
/*               |     E_NOT_OK is returned.                                */
/*               | (3) When an OTA job is being executed, it is suspended   */
/*               |     by the Mem function.                                 */
/*               |     If it cannot be suspended, E_NOT_OK is returned.     */
/*               | Otherwise, E_OK is returned.                             */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_ExtDfPreExecution( void )
{
    Std_ReturnType u1_rtn;
    uint8 u1_ramGarbled;
    uint8 u1_LockStatus;
    uint8 u1_CtlStatus;
    MemAcc_JobStatusType u1_GetFlsStatus;
    uint8 u1_funcRet;
    
    u1_ramGarbled = MemAcc_JobCtl_GetRAMGarbled();
    if( (uint8)STD_OFF == u1_ramGarbled )
    {
        u1_rtn = E_OK;

        /* Check lock status - Not OK except for unlock */
        /* Since AreaID-0 is defined as DataFlash, the following processing is fixed. */
        u1_LockStatus = MemAcc_SemCtl_CheckAreaLockStatus( MEMACC_ADDRAREA_0 );
        if ( MEMACC_SEMCTL_ST_UNLOCK != u1_LockStatus )
        {
            u1_rtn = E_NOT_OK;
        }
        else
        {
            /* If MemAcc is running a Fee job, */
            /*  or if the job status of Fls module is not IDLE, it is Not OK. */
            u1_CtlStatus = MemAcc_JobCtlExtInfoTbl[MEMACC_ADDRAREA_0].extJobStatus;
            u1_GetFlsStatus = MemAcc_FlsWrp_GetStatus();
            if ( ( MEMACC_JOB_IDLE != u1_CtlStatus ) ||
                ( MEMACC_JOB_IDLE != u1_GetFlsStatus ) )
            {
                u1_rtn = E_NOT_OK;
            }
            else
            {
                /* execute suspend */
                u1_funcRet = MemAcc_JobCtl_ExecJobSuspend();
                
                /* Not OK if suspend failedG */
                if ( MEMACC_JOBCTL_SUSPEND_FAILED == u1_funcRet )
                {
                    u1_rtn = E_NOT_OK;
                }
                /* If suspension is successful, set the job execution status to REQUEST so that the job can be resumed as a periodic process. */
                else if ( MEMACC_JOBCTL_SUSPEND_SUCCESS == u1_funcRet )
                {
                    MemAcc_JobCtl_SetJobControlStatus( MEMACC_JOBCTL_REQUEST );
                    
                    MemAcc_JobCtl_SetJobCtlInfoSub();
                    MemAcc_JobCtl_SetRAMSub( MemAcc_JobCtlInfo.jobAddressArea );
                }
                else
                {
                    /* No process in case of Job not suspended */
                }
            }
        }
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    return ( u1_rtn );
    
} /* MemAcc_ExtDfPreExecution */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
