/* MemAcc_Api.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include "../cfg/MemAcc_Cfg.h"
#include "../inc/MemAcc_Mpu_Const.h"
#include "../inc/MemAcc_Api.h"
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_FlsWrp.h"
#include "../inc/MemAcc_MemWrp.h"
#include "../inc/MemAcc_Api_Internal.h"

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
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

/* Job request manage information */
VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )    MemAcc_ApiJobRequest;

#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

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
/* Function Name | MemAcc_Api_init                                          */
/* Description   | This function initializes ram areas used by MemAcc.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_init( void )
{   
    /* Initialize lock control ram on SemCtl unit */
    MemAcc_SemCtl_Init();
    
    /* Initialize control status ram on Block unit */
    MemAcc_JobCtl_Init();
    
    /* Call Mem initialize API */
    MemAcc_MemWrp_Init();
    
    /* Call Fls initialize API */
    MemAcc_FlsWrp_Init();

} /* MemAcc_Api_init */

/****************************************************************************/
/* Function Name | MemAcc_Api_Execute                                       */
/* Description   | This function initializes ram areas used by MemAcc.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_Execute( void )
{
    uint8   u1_jobControlStatus;
    Std_ReturnType u1_funcRet;
    MemAcc_JobResultType u1_getJobResult;
    MemAcc_JobStatusType u1_getJobStatus;
    
    u1_getJobResult = MEMACC_MEM_FAILED;
    
    /* Get current Job control information and Job request manage information */
    u1_jobControlStatus = MemAcc_JobCtlInfo.jobControlStatus;
    MemAcc_JobCtl_GetJobRequest( MemAcc_JobCtlInfo.jobAddressArea, &MemAcc_ApiJobRequest );

    /* Get job result from Fls driver. If the Fls driver is running, call MainFunction of Fls driver. */
    /* If Fls cancellation fails, Fls status may not become idel even if job result is not running. */
    /*   In that case , it is necessary to proceed with Fls periodic function, so check Fls status. */
    u1_funcRet = MemAcc_FlsWrp_GetJobResult( &u1_getJobResult );
    u1_getJobStatus = MemAcc_FlsWrp_GetStatus();
    if( ( (Std_ReturnType)E_OK != u1_funcRet ) ||
        ( MEMACC_JOB_IDLE !=  u1_getJobStatus ) )
    {
        MemAcc_FlsWrp_MainFunction();
    }

    u1_funcRet = MemAcc_Api_RunningExecute();

    /* If cancel request status is ON, run cancel process */
    if( (uint8)STD_ON == MemAcc_JobCtlInfo.jobCancelStatus )
    {
        /* Run cancel process */
        MemAcc_Api_CancelExecute();
        
        /* Priority judge will run at next period */
        u1_funcRet = E_OK;
    }

    /* If job control does not perform for running job and cancellation, job request monitoring perform. */
    if( (Std_ReturnType)E_OK != u1_funcRet )
    {
        /* Job request monitoring */
        if( MEMACC_JOBCTL_REQUEST == u1_jobControlStatus )
        {
            /* Run Job request monitoring */
            MemAcc_Api_RequestExecute();
        }
    }
    
    /* call MainFunction of Mem driver. */
    MemAcc_MemWrp_MainFunction();
    
} /* MemAcc_Api_Execute */

/****************************************************************************/
/* Function Name | MemAcc_Api_NonPeriodic_Execute                           */
/* Description   | This function is called from                             */
/*               | MemAcc_MainFunction_ExtNonPeriodic and                   */
/*               | controls I/F of lower modules.                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_NonPeriodic_Execute( void )
{
    uint8   u1_jobControlStatus;
    Std_ReturnType u1_funcRet;
    MemAcc_JobResultType u1_getJobResult;
    MemAcc_JobStatusType u1_getJobStatus;
    
    u1_getJobResult = MEMACC_MEM_FAILED;
    
    /* Get current Job control information and Job request manage information */
    u1_jobControlStatus = MemAcc_JobCtlInfo.jobControlStatus;
    MemAcc_JobCtl_GetJobRequest( MemAcc_JobCtlInfo.jobAddressArea, &MemAcc_ApiJobRequest );

    /* Get job result from Fls driver. If the Fls driver is running, call MainFunction of Fls driver. */
    /* If Fls cancellation fails, Fls status may not become idel even if job result is not running. */
    /*   In that case , it is necessary to proceed with Fls periodic function, so check Fls status. */
    u1_funcRet = MemAcc_FlsWrp_GetJobResult( &u1_getJobResult );
    u1_getJobStatus = MemAcc_FlsWrp_GetStatus();
    if( ( (Std_ReturnType)E_OK != u1_funcRet ) ||
        ( MEMACC_JOB_IDLE !=  u1_getJobStatus ) )
    {
        MemAcc_FlsWrp_MainFunction();
    }

    /* Execute current job processs */
    u1_funcRet = MemAcc_Api_RunningExecute();

    /* If cancel request status is ON, run cancel process */
    if( (uint8)STD_ON == MemAcc_JobCtlInfo.jobCancelStatus )
    {
        /* Run cancel process */
        MemAcc_Api_CancelExecute();
        
        /* Priority judge will run at next period */
        u1_funcRet = E_OK;
    }

    /* If job control does not perform for running job and cancellation, job request monitoring perform. */
    if( (Std_ReturnType)E_OK != u1_funcRet )
    {
        /* Job request monitoring */
        if( MEMACC_JOBCTL_REQUEST == u1_jobControlStatus )
        {
            /* Run Job request monitoring */
            MemAcc_Api_RequestExecute();
        }
    }
} /* MemAcc_Api_NonPeriodic_Execute */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | MemAcc_Api_JobEndNotification                            */
/* Description   | When the job end notification function of the specified  */
/*               | address area is registered, this function executes       */
/*               | the job end notification function.                       */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    specified address area id               */
/*               | jobResult        job result                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_JobEndNotification(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobResultType jobResult
)
{
    uint16  u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
         /* Notify when job end notification is required */
        if( NULL_PTR != MemAcc_AddrAreaCfg[addressAreaId].MemAccJobEndNotificationName )
        {
            MemAcc_AddrAreaCfg[addressAreaId].MemAccJobEndNotificationName( addressAreaId, jobResult );
        }
    }

} /* MemAcc_Api_JobEndNotification */

/****************************************************************************/
/* Function Name | MemAcc_Api_RunningExecute                                */
/* Description   | This function checks the result of the running job,      */
/*               | executes the end processing if the job is completed,     */
/*               | and executes the job start processing                    */
/*               | if the job is waiting.                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | E_OK        Job control request executed                 */
/*               | E_NOT_OK    Job control request not executed             */
/* Notes         | When the execution state is running and the job is       */
/*               | waiting, since the job is started after suspend          */
/*               | or retry setting, control of the target job is  executed */
/*               | from the beginning.                                      */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_RunningExecute( void )
{
    Std_ReturnType u1_Rtn;
    MemAcc_JobResultType u1_getJobResult;
    MemAcc_JobStatusType u1_getJobStatus;
    uint8 u1_driverType;    /* Fls/Mem */
    Mem_InstanceIdType u4_instanceId;

    u1_Rtn  = E_NOT_OK;
    u1_getJobResult = MEMACC_MEM_FAILED;

    /* If the current job is running */
    if( ( MEMACC_JOBCTL_IDLE != MemAcc_JobCtlInfo.jobControlStatus ) &&
        ( MEMACC_JOBCTL_ST_RUN ==  MemAcc_ApiJobRequest.innerJobStatus ) )
    {
        /* Get the driver type of Area ID */
        u1_driverType = MemAcc_JobCtl_TargetDriver( MemAcc_JobCtlInfo.jobAddressArea );

        /* If the target dirver exists */
        if( MEMACC_JOBCTL_NOTUSED_DRIVER != u1_driverType )
        {
            /* Get the result of Mem JOB */
            if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
            {
                u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;
                u1_Rtn = MemAcc_MemWrp_GetJobResult( u4_instanceId, &u1_getJobResult );
            }
            /* Get the result of Fls JOB */
            else
            {
                u1_Rtn = MemAcc_FlsWrp_GetJobResult( &u1_getJobResult );

                /* If the Fls execution status is not IDLE and the Fls processing result is not PENDING, the Fls job continues. */
                u1_getJobStatus = MemAcc_FlsWrp_GetStatus();
                if( MEMACC_JOB_IDLE !=  u1_getJobStatus )
                {
                    u1_Rtn = E_NOT_OK;
                }
            }

            /* if the execution result is not PENDING */
            if( (Std_ReturnType)E_OK == u1_Rtn )
            {
                /* Job end process */
                MemAcc_Api_JobEnd( MemAcc_JobCtlInfo.jobAddressArea, u1_getJobResult );

                u1_Rtn  = E_OK;
            }
        }
    }
    /* If the execution status is running and the current job is waiting. */
    else if( ( MEMACC_JOBCTL_RUN == MemAcc_JobCtlInfo.jobControlStatus ) &&
             ( MEMACC_JOBCTL_ST_WAIT == MemAcc_ApiJobRequest.innerJobStatus ) )
    {
        /* Job start process */
        MemAcc_Api_JobStart( MemAcc_JobCtlInfo.jobAddressArea );

        u1_Rtn  = E_OK;
    }
    /* Except for running or waiting */
    else
    {
        /* No process */
    }

    return ( u1_Rtn );

} /* MemAcc_Api_RunningExecute */

/****************************************************************************/
/* Function Name | MemAcc_Api_CancelExecute                                 */
/* Description   | This function sets the result of the waiting job to      */
/*               | cancel and executes the job end processing.              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | When the cancellation target is Fls, this function       */ 
/*               | checks the job execution state, after that when          */
/*               | the job is being executed, this function executes        */
/*               | the cancellation processing of Fls.                      */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_Api_CancelExecute( void )
{
    MemAcc_JobRequestManageType st_JobManage;
    MemAcc_JobStatusType u1_getJobStatus;
    uint8 u1_driverType;    /* Fls/Mem */
    uint16 u2_loopCnt;
    uint16  u2_AdressAreaMax  = MemAcc_AddressArea_Max;

    MemAcc_JobCtlInfo.jobCancelStatus = STD_OFF;
    /* heck whether there is cancel request for each area ID. */
    for( u2_loopCnt = 0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
    {
        MemAcc_JobCtl_GetJobRequest( u2_loopCnt, &st_JobManage );
        /* If there is cancel request */
        if( MEMACC_JOBCTL_ST_CANCEL == st_JobManage.innerJobStatus )
        {
            u1_driverType = MemAcc_JobCtl_TargetDriver( u2_loopCnt );

            if( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_driverType )
            {
                u1_getJobStatus = MemAcc_FlsWrp_GetStatus();

                if( MEMACC_JOB_IDLE ==  u1_getJobStatus )
                {
                    /* Job end process */
                    MemAcc_Api_JobEnd( u2_loopCnt, MEMACC_MEM_CANCELED );
                }
                else
                {
                    MemAcc_JobCtlInfo.jobCancelStatus = STD_ON;
                }
            }
            else
            {
                /* Job end process */
                MemAcc_Api_JobEnd( u2_loopCnt, MEMACC_MEM_CANCELED );
            }
        }
    }
} /* MemAcc_Api_CancelExecute */

/****************************************************************************/
/* Function Name | MemAcc_Api_RequestExecute                                */
/* Description   | This function determines the priority of the job request */
/*               | and executes the job processing.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_RequestExecute( void )
{
    Std_ReturnType u1_funcRet;
    MemAcc_AddressAreaIdType u2_targetAreaId;    /* Traget address area ID */
    Std_ReturnType u1_funcGetJobResult;
    MemAcc_JobResultType u1_getJobResult;
    Mem_InstanceIdType u4_instanceId;

    u1_getJobResult = MEMACC_MEM_FAILED;
    u2_targetAreaId = MemAcc_AddressArea_Max;
    /* Get high priority jobs from Job Request Management TBL */
    u1_funcRet = MemAcc_JobCtl_PriorityJudge( &u2_targetAreaId, &MemAcc_ApiJobRequest );
    u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    /* Branch by return value */
    switch( u1_funcRet )
    {
        case MEMACC_JOBCTL_PRI_JOBSTART:                                    /* Job start */
            MemAcc_Api_JobStart( u2_targetAreaId );                         /* Call job start request */
            break;
        case MEMACC_JOBCTL_PRI_SUSPEND:                                     /* Suspend */
            u1_funcRet = MemAcc_MemWrp_Suspend( u4_instanceId );    /* Execute suspend */
            /* Suspend successful */
            if( (Std_ReturnType)E_OK == u1_funcRet )
            {
                /* Set suspend for job information */
                MemAcc_JobCtl_SetJobSuspend( u2_targetAreaId );
            }
            else
            {
                /* Set the job execution status to REQUEST in order to issue the suspend request again in the next cycle. */
                MemAcc_JobCtl_SetJobControlStatus( MEMACC_JOBCTL_REQUEST );
            }
            break;
        case MEMACC_JOBCTL_PRI_RESUME:                                      /* Resume */
            /* If Mem's job processing result is suspended and not completed, send resume request to Mem */
            u1_funcGetJobResult = MemAcc_MemWrp_GetJobResult( u4_instanceId, &u1_getJobResult );
            if( (Std_ReturnType)E_OK != u1_funcGetJobResult )
            {
                u1_funcRet = MemAcc_MemWrp_Resume( u4_instanceId );     /* Execute resume */

                /* Resume successful */
                if( (Std_ReturnType)E_OK == u1_funcRet )
                {
                    /* Set the resumed job status to running */
                    MemAcc_JobCtl_SetJobResume( u2_targetAreaId, MEMACC_JOBCTL_ST_RUN );
                }
                /* Resume failed */
                else
                {
                    /* Set the job execution status to REQUEST in order to issue a resume request again in the next cycle. */
                    MemAcc_JobCtl_SetJobControlStatus(MEMACC_JOBCTL_REQUEST);
                }
            }
            else
            {
                /* Return value is not checked. Abnormal path.*/
                (void)MemAcc_MemWrp_Resume( u4_instanceId );
                /* When the job processing result of the Mem is completed, the job state is set to the running without resume request because the Mem does not have job. */
                MemAcc_JobCtl_SetJobResume( u2_targetAreaId, MEMACC_JOBCTL_ST_RUN );
            }
            break;
        case MEMACC_JOBCTL_PRI_NOTING:                                      /* No need to execute */
        default:                                                            /* Other */
            /* No process */
            break;
    }

} /* MemAcc_Api_RequestExecute */

/****************************************************************************/
/* Function Name | MemAcc_Api_JobStart                                      */
/* Description   | This function starts the job request management          */
/*               | information that is controlled by MemAcc_Api             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | When a job execution request is successful, the target   */
/*               | job is set to running.                                   */
/*               | When a job execution request fails, end processing is    */
/*               | performed.                                               */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_JobStart(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    Std_ReturnType u1_funcRet;
    uint8 u1_driverType;    /* Fls/Mem */
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;

    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Get driver type of address area ID */
        u1_driverType = MemAcc_JobCtl_TargetDriver( addressAreaId );

        switch( MemAcc_ApiJobRequest.innerJobType )
        {
            /* MemAcc_Wtrie */
            case MEMACC_JOBCTL_JOB_WRITE:
                u1_funcRet = MemAcc_Api_Write( u1_driverType );
                break;
            /* MemAcc_Read */
            case MEMACC_JOBCTL_JOB_READ:
                u1_funcRet = MemAcc_Api_Read( u1_driverType );
                break;
            /* MemAcc_Erase */
            case MEMACC_JOBCTL_JOB_ERASE:
                u1_funcRet = MemAcc_Api_Erase( u1_driverType );
                break;
            /* MemAcc_BlankCheck */
            case MEMACC_JOBCTL_JOB_BLANKCHECK:
                u1_funcRet = MemAcc_Api_BlankCheck( u1_driverType );
                break;
            /* MemAcc_HwSpecificService */
            case MEMACC_JOBCTL_JOB_MEMHWSPECIFIC:
                u1_funcRet = MemAcc_Api_HwSpecificService( u1_driverType );
                break;
            /* other */
            case MEMACC_JOBCTL_JOB_NONE:
            default:
                u1_funcRet = E_NOT_OK;
                break;
        }

        /* Job successful */
        if( (Std_ReturnType)E_OK == u1_funcRet )
        {
            /* Set target job to pending */
            MemAcc_JobCtl_SetJobPending( addressAreaId );
        }
        /* Job failed */
        else
        {
            /* Job failure process */
            MemAcc_Api_JobEnd( addressAreaId, MEMACC_MEM_FAILED );
        }
    }

} /* MemAcc_Api_JobStart */

/****************************************************************************/
/* Function Name | MemAcc_Api_JobEnd                                        */
/* Description   | This function ends the job request management            */ 
/*               | information that is controlled by MemAcc_Api.            */
/*               | If job end notification is required, this function calls */
/*               | the notification.                                        */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    Address area ID                         */
/*               | jobResult        Job result                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_JobEnd(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobResultType jobResult
)
{
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Set job control end */
        MemAcc_JobCtl_SetJobEnd( addressAreaId, jobResult );

        /* Call job end notification */
        MemAcc_Api_JobEndNotification( addressAreaId, jobResult );
    }

}

/****************************************************************************/
/* Function Name | MemAcc_Api_Write                                         */
/* Description   | This function calls the driver's write operation.        */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_Write(
    uint8 u1_driverType
)
{
    Std_ReturnType u1_Rtn;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;
    
    /* Mem */
    if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_MemWrp_Write(  u4_instanceId,
                                       MemAcc_ApiJobRequest.targetAddress,
                                       MemAcc_ApiJobRequest.sourceDataPtr,
                                       MemAcc_ApiJobRequest.length
                                    );
    }
    /* Fls */
    else if( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_FlsWrp_Write( MemAcc_ApiJobRequest.targetAddress,
                                       MemAcc_ApiJobRequest.sourceDataPtr,
                                       MemAcc_ApiJobRequest.length
                                    );
    }
    /* Other */
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_Api_Write */

/****************************************************************************/
/* Function Name | MemAcc_Api_Read                                          */
/* Description   | This function calls the driver's read operation.         */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         | No processing of Fls since Cdd_Read is used              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_Read(
    uint8 u1_driverType
)
{
    Std_ReturnType u1_Rtn;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    /* Mem */
    if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_MemWrp_Read(  u4_instanceId,
                                      MemAcc_ApiJobRequest.targetAddress,
                                      MemAcc_ApiJobRequest.destinationDataPtr,
                                      MemAcc_ApiJobRequest.length
                                   );
    }
    /* Other */
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_Api_Read */

/****************************************************************************/
/* Function Name | MemAcc_Api_Erase                                         */
/* Description   | This function calls the driver's erase operation.        */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_Erase(
    uint8 u1_driverType
)
{
    Std_ReturnType u1_Rtn;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    /* Mem */
    if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_MemWrp_Erase(  u4_instanceId,
                                       MemAcc_ApiJobRequest.targetAddress,
                                       MemAcc_ApiJobRequest.length
                                    );
    }
    /* Fls */
    else if( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_FlsWrp_Erase( MemAcc_ApiJobRequest.targetAddress,
                                       MemAcc_ApiJobRequest.length
                                    );
    }
    /* Other */
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_Api_Erase */

#ifdef MEMACC_DEVICE_CYT2Bx
/****************************************************************************/
/* Function Name | MemAcc_Api_BlankCheck                                    */
/* Description   | This function calls the driver's BlankCheck operation.   */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         | E_NOT_OK is returned as a fixed value in TraveoII.       */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_BlankCheck(
    uint8 u1_driverType
)
{
    return ( E_NOT_OK );

} /* MemAcc_Api_BlankCheck */
#else /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_Api_BlankCheck                                    */
/* Description   | This function calls the driver's BlankCheck operation.   */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         |  No processing of Fls since Cdd_BlankCheck is used       */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_BlankCheck(
    uint8 u1_driverType
)
{
    Std_ReturnType u1_Rtn;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    /* Mem */
    if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_MemWrp_BlankCheck(  u4_instanceId,
                                            MemAcc_ApiJobRequest.targetAddress,
                                            MemAcc_ApiJobRequest.length
                                          );
    }
    /* Other */
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_Api_BlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_Api_HwSpecificService                             */
/* Description   | This function calls the driver's HwSpecificService       */
/*               | operation.                                               */
/* Preconditions | None                                                     */
/* Parameters    | u1_driverType    Type of target flash memory             */
/* Return Value  | E_OK             Job succeeded                           */
/*               | E_NOT_OK         Job failed                              */
/* Notes         | No processing of Fls because there is                    */
/*               | no HwSpecificService                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Api_HwSpecificService(
    uint8 u1_driverType
)
{
    Std_ReturnType u1_Rtn;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    /* Mem */
    if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
    {
        u1_Rtn = MemAcc_MemWrp_HwSpecificService(  u4_instanceId,
                                                   MemAcc_ApiJobRequest.hwServiceId,
                                                   MemAcc_ApiJobRequest.destinationDataPtr,
                                                   MemAcc_ApiJobRequest.lengthPtr
                                                 );
    }
    /* Other */
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_Api_HwSpecificService */

/****************************************************************************/
/* Function Name | MemAcc_Api_AborJob                                       */
/* Description   | This function aborts Jobs when RAM garbled occurs.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Api_AbortJob( void )
{
    boolean b_isIdle;
    uint16 u2_loopCnt;
    uint16 u2_AdressAreaMax;
    Std_ReturnType u1_funcRet;
    MemAcc_JobResultType u1_getJobResult;
    MemAcc_JobStatusType u1_getJobStatus;
    Mem_InstanceIdType u4_instanceId;

    u1_getJobResult = MEMACC_MEM_FAILED;
    u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    MemAcc_MemWrp_MainFunction();
    MemAcc_FlsWrp_MainFunction();

    b_isIdle = TRUE;
    u1_getJobStatus = MemAcc_FlsWrp_GetStatus();
    if( MEMACC_JOB_IDLE !=  u1_getJobStatus )
    {
        b_isIdle = FALSE;
    }
    else
    {
        /* Return value is not checked. Cannot support E_NOT_OK */
        (void)MemAcc_MemWrp_Resume( u4_instanceId );
        u1_funcRet = MemAcc_MemWrp_GetJobResult( u4_instanceId, &u1_getJobResult );
        if( (Std_ReturnType)E_OK != u1_funcRet )
        {
            b_isIdle = FALSE;
        }
    }

    if( b_isIdle == (boolean)FALSE )
    {
        MemAcc_JobCtl_SetRAMGarbled();
    }
    else
    {
        u2_AdressAreaMax = MemAcc_AddressArea_Max;
        for( u2_loopCnt = 0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
        {
            MemAcc_Api_JobEnd( u2_loopCnt, MEMACC_MEM_FAILED );
        }

        MemAcc_JobCtl_ClearJobCtlInfo();
    }
} /* MemAcc_Api_AbortJob */

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/* Version         :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
