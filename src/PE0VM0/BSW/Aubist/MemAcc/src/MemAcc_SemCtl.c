/* MemAcc_SemCtl.c v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_SemCtl_Internal.h"

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

/* Lock execution status management information */
VAR( uint8, MEMACC_VAR_NO_INIT ) MemAcc_Sem_CtlStatus;                                           /* Lock execution control status */

/* Fee lock status (for providing external modules) */
VAR( uint8, MEMACC_VAR_NO_INIT ) MemAcc_Sem_ExtFeeLockStatus;                                    /* Fee lock status */

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
/* Function Name | MemAcc_SemCtl_Init                                       */
/* Description   | This function initializes lock related information       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Call when MemAcc_Init is invoked                         */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_SemCtl_Init( void )
{
    uint16 u2_count;                                     /* Counter */
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    /* Initialize the lock execution status management information. */
    MemAcc_Sem_CtlStatus = MEMACC_SEMCTL_JOB_NONE;       /* Initialize No request */
    
    /* Initialize the lock information management TBL */
    for ( u2_count = 0U ; u2_count < u2_AdressAreaMax ; u2_count++ )
    {
        /* Initialize the management information */
        MemAcc_SemCtl_CtlTbl_Init( u2_count );
    }
    
    /* Initialize the Fee lock state */
    MemAcc_Sem_ExtFeeLockStatus = MEMACC_SEMCTL_ST_EXT_UNLOCK;

} /* MemAcc_SemCtl_Init */


/****************************************************************************/
/* Function Name | MemAcc_SemCtl_RequestLock                                */
/* Description   | This function requests lock with the AreaID, Address,    */
/* Preconditions | None                                                     */
/*               | and Length specified in the parameters.                  */
/* Parameters    | targetAreaId             AreaID                          */
/*               | targetAddress            Address (unused)                */
/*               | targetLength             Length (unused)                 */
/*               | pt_notificationPtr       Notification function pointer   */
/*               |                          to call upon lock completion    */
/* Return Value  | E_OK       : Lock request accepted successfully          */
/*               | E_NOT_OK   : Lock request acceptance failure             */
/* Notes         | Returns E_NOT_OK if the specified AreaID is out of range */
/*               | Returns E_NOT_OK if a control request is being executed  */
/*               | with the specified AreaID.                               */
/*               | Not used for the specified Address and Length            */
/*               | Returns E_NOT_OK if the given function pointer is Null   */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_SemCtl_RequestLock(
    MemAcc_AddressAreaIdType targetAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType targetLength,
    MemAcc_LockNotificationType pt_notificationPtr
)
{
    Std_ReturnType u1_rtn;
    MemAcc_JobStatusType u1_jobStatus;
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    /* If AreaID is in range */
    if( targetAreaId < u2_AdressAreaMax )
    {
        /* Check if the job processing of the corresponding AreaID is being executed. */
        u1_jobStatus = MemAcc_JobCtl_GetExtJobInfoStatus( targetAreaId );
        if ( MEMACC_JOB_IDLE == u1_jobStatus )
        {
            /* When already locked */
            if ( MEMACC_SEMCTL_ST_LOCK == MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus )
            {
                /* Change Status to LockEvent */
                MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus = MEMACC_SEMCTL_ST_LOCKEVENT;
            }
            else
            {
                /* Change Status to LockWait */
                MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus = MEMACC_SEMCTL_ST_LOCKWAIT;
            }
            /* Parameter information stored in internal status */
            MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemNotificationFunc = pt_notificationPtr;
            
            /* Set Lock Enforcement Management Status to Requested */
            MemAcc_Sem_CtlStatus = MEMACC_SEMCTL_JOB_REQ;
            
            /* Update External RAM */
            MemAcc_JobCtl_SetExtJobInfoType( targetAreaId, MEMACC_REQUESTLOCK_JOB );   /* Update JobType */
            MemAcc_JobCtl_SetExtJobInfoStatus( targetAreaId, MEMACC_JOB_PENDING );     /* Update JobStatus */
            
            /* Update lock status if trying to lock address area ID=0 */
            if ( MEMACC_ADDRAREA_0 == targetAreaId )
            {
                MemAcc_Sem_ExtFeeLockStatus = MEMACC_SEMCTL_ST_EXT_LOCK;
            }

            MemAcc_JobCtl_SetJobCtlInfoSub();
            MemAcc_JobCtl_SetRAMSub( targetAreaId );

            u1_rtn = E_OK;
        }
        else
        {
            /* Not accepted because a Job is being executed with the corresponding AreaID */
            u1_rtn = E_NOT_OK;
        }
    }
    else
    {
        /* Not OK if AreaID is out of range */
        u1_rtn = E_NOT_OK;
    }
    
    return ( u1_rtn );

} /* MemAcc_SemCtl_RequestLock */


/****************************************************************************/
/* Function Name | MemAcc_SemCtl_ReleaseLock                                */
/* Description   | This function requests unlock with the AreaID, Address,  */
/*               | and Length specified in the parameters.                  */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId          AreaID                             */
/*               | targetAddress         Address (unused)                   */
/*               | targetLength          Length (unused)                    */
/* Return Value  | E_OK       : Unlock request accepted successfully        */
/*               | E_NOT_OK   : Unlock request acceptance failure           */
/* Notes         | Returns E_NOT_OK if the specified AreaID is out of range */
/*               | Returns E_OK if the specified AreaID is unlocked         */
/*               | Not used for the specified Address and Length            */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_SemCtl_ReleaseLock(
    MemAcc_AddressAreaIdType targetAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType targetLength
)
{
    Std_ReturnType u1_rtn;
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    /* If AreaID is in range */
    if( targetAreaId < u2_AdressAreaMax )
    {
        /* Switch by the execution status of the lock */
        switch ( MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus )
        {
            case MEMACC_SEMCTL_ST_LOCK:                                              /* Locked */
                /* Clear Internal State */
                MemAcc_SemCtl_CtlTbl_Init( (uint16)targetAreaId );
                
                /* If locked, event notification because control requests may be queued */
                MemAcc_JobCtl_UnlockEvent( targetAreaId );
                break;
            case MEMACC_SEMCTL_ST_LOCKEVENT:                                         /* Locked (Before notification) */
                /* Clear Internal State */
                MemAcc_SemCtl_CtlTbl_Init( (uint16)targetAreaId );
                
                /* Update External RAM */
                MemAcc_JobCtl_SetExtJobInfoType( targetAreaId, MEMACC_NO_JOB );      /* Update JobType */
                MemAcc_JobCtl_SetExtJobInfoStatus( targetAreaId, MEMACC_JOB_IDLE );  /* Update JobStatus */
                
                /* If locked, event notification because control requests may be queued */
                MemAcc_JobCtl_UnlockEvent( targetAreaId );
                break;
            case MEMACC_SEMCTL_ST_LOCKWAIT:                                          /* Waiting for lock */
                /* Clear Internal State */
                MemAcc_SemCtl_CtlTbl_Init( (uint16)targetAreaId );
                
                /* Update External RAM */
                MemAcc_JobCtl_SetExtJobInfoType( targetAreaId, MEMACC_NO_JOB );      /* Update JobType */
                MemAcc_JobCtl_SetExtJobInfoStatus( targetAreaId, MEMACC_JOB_IDLE );  /* Update JobStatus */
                break;
            case MEMACC_SEMCTL_ST_UNLOCK:                                            /* Unlock */
            default:
                /* No process. Keep of initialize value. */
                break;
        }
        
        /* Update lock status if trying to lock address area ID=0 */
        if ( MEMACC_ADDRAREA_0 == targetAreaId )
        {
            MemAcc_Sem_ExtFeeLockStatus = MEMACC_SEMCTL_ST_EXT_UNLOCK;
        }
        
        MemAcc_JobCtl_SetJobCtlInfoSub();
        MemAcc_JobCtl_SetRAMSub( targetAreaId );
        
        u1_rtn = E_OK;
    }
    else
    {
        /* Not OK if AreaID is out of range */
        u1_rtn = E_NOT_OK;
    }
    
    return ( u1_rtn );

} /* MemAcc_SemCtl_ReleaseLock */


/****************************************************************************/
/* Function Name | MemAcc_SemCtl_CheckAreaLockStatus                        */
/* Description   | This function gets the lock status of the AreaID         */
/*               | specified in the parameter.                              */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId               AreaID to check               */
/* Return Value  | MEMACC_SEMCTL_ST_UNLOCK    Unlock                        */
/*               | MEMACC_SEMCTL_ST_LOCK      Locked                        */
/*               | MEMACC_SEMCTL_ST_LOCKEVENT Locked (waiting for           */
/*               |                            Notification to be issued)    */
/*               | MEMACC_SEMCTL_ST_LOCKWAIT  Waiting for lock              */
/* Notes         | Locked                                                   */
/*               | -> Returns MEMACC_SEMCTL_ST_LOCK                         */
/*               |    or MEMACC_SEMCTL_ST_LOCKEVENT                         */
/*               | Lock control in progress                                 */
/*               | -> Returns MEMACC_SEMCTL_ST_LOCKWAIT                     */
/*               |    or MEMACC_SEMCTL_ST_LOCKEVENT                         */
/*               | AreaID is out of range                                   */
/*               | -> Returns MEMACC_SEMCTL_ST_UNLOCK                       */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE ) 
MemAcc_SemCtl_CheckAreaLockStatus(
    MemAcc_AddressAreaIdType targetAreaId
)
{
    uint8 u1_rtn;
    uint16 u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    if( targetAreaId < u2_AdressAreaMax )
    {
        /* Get the lock status of the specified AreaID */
        u1_rtn = MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus;
    }
    else
    {
        /* Set unlock if AreaID is out of range */
        u1_rtn = MEMACC_SEMCTL_ST_UNLOCK;
    }
    
    return ( u1_rtn );

} /* MemAcc_SemCtl_CheckAreaLockStatus */


/****************************************************************************/
/* Function Name | MemAcc_SemCtl_Execute (periodic process)                 */
/* Description   | This function is invoked from a cyclic process and locks */
/*               | the higher priority AreaID from the state of the         */
/*               | lock request.                                            */
/* Preconditions | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_SemCtl_Execute( void )
{
    uint16  u2_count;                                        /* counter */
    uint16  u2_AdressAreaMax;
    
    /* udged by whether the status is Request */
    if ( MEMACC_SEMCTL_JOB_REQ == MemAcc_Sem_CtlStatus )
    {
        u2_AdressAreaMax  = MemAcc_AddressArea_Max;
        /* Check Lock Information Management TBL */
        for ( u2_count = 0U ; u2_count < u2_AdressAreaMax ; u2_count++ )
        {
            /* Check if the area ID is waiting for lock. */
            if ( ( MEMACC_SEMCTL_ST_LOCKEVENT == MemAcc_Sem_CtlTBL[u2_count].MemAccSemStatus ) ||
                 ( MEMACC_SEMCTL_ST_LOCKWAIT == MemAcc_Sem_CtlTBL[u2_count].MemAccSemStatus ) )
            {
                /* Change Status to Lock */
                MemAcc_Sem_CtlTBL[u2_count].MemAccSemStatus = MEMACC_SEMCTL_ST_LOCK;
                
                /* Update External RAM */
                MemAcc_JobCtl_SetExtJobInfoResult( u2_count, MEMACC_MEM_OK );          /* Update JobResult */
                MemAcc_JobCtl_SetExtJobInfoType( u2_count, MEMACC_NO_JOB );            /* Update JobType */
                MemAcc_JobCtl_SetExtJobInfoStatus( u2_count, MEMACC_JOB_IDLE );        /* Update JobStatus */
                
                /* Issue Notification */ /* Compiler Warning 1777 Countermeasures, copy to a const variable and then call function pointer */
                {
                    volatile const MemAcc_LockNotificationType pt_notificationPtr = MemAcc_Sem_CtlTBL[u2_count].MemAccSemNotificationFunc;
                    pt_notificationPtr();
                }
            }
        }
        /* Update Lock Management State */
        MemAcc_Sem_CtlStatus = MEMACC_SEMCTL_JOB_NONE;
    }

} /* MemAcc_SemCtl_Execute */


/****************************************************************************/
/* Function Name | MemAcc_SemCtl_GetExtLockStatus                           */
/* Description   | This function obtains the lock status of address area    */
/*               | ID=0 used by Fee exposed to external module.             */
/* Preconditions | None                                                     */
/* Parameters    | -                                                        */
/* Return Value  | MEMACC_SEMCTL_ST_EXT_UNLOCK             Unlock           */
/*               | MEMACC_SEMCTL_ST_EXT_LOCK               Locked           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE )
MemAcc_SemCtl_GetExtLockStatus( void )
{
    return ( MemAcc_Sem_ExtFeeLockStatus );

} /* MemAcc_SemCtl_GetExtLockStatus */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | MemAcc_SemCtl_CtlTbl_Init                                */
/* Description   | This function initializes the lock manager TBL member    */
/*               | information set in the argument.                         */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId     AreaID                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_SemCtl_CtlTbl_Init(
    uint16 targetAreaId
)
{
    uint16  u2_AdressAreaMax  = MemAcc_AddressArea_Max;
    
    /* out of range access check */
    if ( targetAreaId < u2_AdressAreaMax )
    {
        /* Initialization of management information */
        MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemStatus           = MEMACC_SEMCTL_ST_UNLOCK;
        MemAcc_Sem_CtlTBL[targetAreaId].MemAccSemNotificationFunc = NULL_PTR;
    }

} /* MemAcc_SemCtl_CtlTbl_Init */


#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
