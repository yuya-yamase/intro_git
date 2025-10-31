/* MemAcc_JobCtl.c v2-0-0                                                   */
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
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_FlsWrp.h"
#include "../inc/MemAcc_MemWrp.h"
#include "../inc/MemAcc_Api.h"
#include "../inc/MemAcc_Internal.h"
#include "../inc/MemAcc_JobCtl_Internal.h"
#include <Mem.h>

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

/* Job execution control information */
VAR ( MemAcc_JobCtlInfoType, MEMACC_VAR_NO_INIT )    MemAcc_JobCtlInfo;
VAR ( MemAcc_JobCtlInfoType, MEMACC_VAR_NO_INIT )    MemAcc_JobCtlInfoSub;

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
/* Function Name | MemAcc_JobCtl_Init                                       */
/* Description   | This function initializes the job execution              */
/*               | control function. Initialize RAM                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_Init( void )
{
    uint16 u2_loopCnt;
    uint16 u2_AdressAreaMax;

    /* Initialize job execution control information */
    MemAcc_JobCtlInfo.jobControlStatus   = MEMACC_JOBCTL_IDLE;
    MemAcc_JobCtlInfo.jobAddressArea     = MEMACC_U2_VAL_0;
    MemAcc_JobCtlInfo.suspendStatus      = STD_OFF;
    MemAcc_JobCtlInfo.suspendAddressArea = MEMACC_U2_VAL_0;
    MemAcc_JobCtlInfo.jobCancelStatus    = STD_OFF;
    MemAcc_JobCtlInfo.jobRamGarbled      = STD_OFF;

    /* Initialize each management TBLs */
    u2_AdressAreaMax = MemAcc_AddressArea_Max;
    for( u2_loopCnt = 0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
    {
        /* Initialize job information management TBL */
        MemAcc_JobCtl_JobRequestTbl_Init( (MemAcc_AddressAreaIdType)u2_loopCnt );
        
        /* Initialize job execution status management information TBL */
        MemAcc_JobCtl_JobCtlExtInfoTbl_Init( (MemAcc_AddressAreaIdType)u2_loopCnt );
    }

    MemAcc_JobCtl_SetRAMSubAll();

} /* MemAcc_JobCtl_Init */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobControlStatus                        */
/* Description   | This function sets the execution status of job           */
/*               | execution control according to the parameter value.      */
/* Preconditions | None                                                     */
/* Parameters    | u1_jobControlStatus       Job execution control status   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_SetJobControlStatus(
    uint8 u1_jobControlStatus
)
{
    /* Check Parameter Range */
    switch( u1_jobControlStatus )
    {
        /* IDLE */
        case MEMACC_JOBCTL_IDLE:
            /* Initialize job execution control information */
            MemAcc_JobCtlInfo.jobControlStatus   = MEMACC_JOBCTL_IDLE;
            MemAcc_JobCtlInfo.jobAddressArea     = MEMACC_U2_VAL_0;
            MemAcc_JobCtlInfo.suspendStatus      = STD_OFF;
            MemAcc_JobCtlInfo.suspendAddressArea = MEMACC_U2_VAL_0;
            MemAcc_JobCtlInfo.jobCancelStatus    = STD_OFF;
            break;
        /* Request monitoring */
        case MEMACC_JOBCTL_REQUEST:
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;
            break;
        /* Job Running */
        case MEMACC_JOBCTL_RUN:
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
            break;
        /* Other */
        default:
            /* No process */
            break;
    }

} /* MemAcc_JobCtl_SetJobControlStatus */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_UnlockEvent                                */
/* Description   | This function is called when a lock is released          */
/*               | from a locked state.                                     */
/* Preconditions | None                                                     */
/* Parameters    | u1_areaid       target areaID                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_UnlockEvent(
    MemAcc_AddressAreaIdType u1_areaid
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    /* Check address area ID range */
    if( u1_areaid < u2_AdressAreaMax )
    {
        /* Check whether a request is received with the corresponding AreaID in the job information management TBL. */
        if ( MEMACC_JOBCTL_JOB_NONE != MemAcc_JobRequestTbl[u1_areaid].innerJobType )
        {
            /* Set job execution control information to request monitoring */
             MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;
        }
    }
} /* MemAcc_JobCtl_UnlockEvent */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_TargetDriver                               */
/* Description   | This function determines the target Driver               */
/*               | from the parameter AreaID.                               */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId  target area ID                             */
/* Return Value  | MEMACC_JOBCTL_CODEFLASH_DRIVER      Mem Driver           */
/*               | MEMACC_JOBCTL_DATAFLASH_DRIVER      Fls Driver           */
/*               | MEMACC_JOBCTL_NOTUSED_DRIVER        No target driver     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8 , MEMACC_CODE ) 
MemAcc_JobCtl_TargetDriver(
    MemAcc_AddressAreaIdType targetAreaId
)
{
    uint8   u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    uint32  u4_NamePrefix;

    /* Check address area ID range */
    if( targetAreaId < u2_AdressAreaMax )
    {
        u4_NamePrefix = MemAcc_AddrAreaCfg[targetAreaId].MemAccSubAddressAreaConfiguration[MEMACC_U2_VAL_0].MemAccMemNamePrefix;
        if( u4_NamePrefix == (uint32)MEMACC_NAMEPREFIX_DATAFLASH )
        {
            u1_rtn = MEMACC_JOBCTL_DATAFLASH_DRIVER;
        }
        else
        {
            u1_rtn = MEMACC_JOBCTL_CODEFLASH_DRIVER;
        }
    }
    else
    {
        /* Set no target driver*/
        u1_rtn = MEMACC_JOBCTL_NOTUSED_DRIVER;
    }

    /* return target driver */
    return ( u1_rtn );

} /* MemAcc_JobCtl_TargetDriver */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_Cancel                                     */
/* Description   | The cancel request status of the job execution control   */
/*               | information is set to ON, and the internal job processing*/
/*               | status of the target area ID is set to cancel.           */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/* Return Value  | None                                                     */
/* Notes         | Fls: Set cancel when there is job request                */
/*               | Mem: Set cancel when job is pendding                     */
/*               |      In the case of Mem, do not cancel during execution  */
/*               |and suspension because the processing continues.          */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_Cancel(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    uint8 u1_driverType;    /* Fls/Mem */
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    MemAcc_JobStatusType u1_getJobStatus;

    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Get driver type of address area ID */
        u1_driverType = MemAcc_JobCtl_TargetDriver( addressAreaId );

        /* In case of Fls */
        if( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_driverType )
        {
            /* Etxecute Fls Cancel */
            MemAcc_FlsWrp_Cancel();

            /* If job request is waiting */
            if( MEMACC_JOBCTL_ST_WAIT == MemAcc_JobRequestTbl[addressAreaId].innerJobStatus )
            {
                /* Etxecute job control end settings */
                MemAcc_JobCtl_SetJobEnd( addressAreaId, MEMACC_MEM_CANCELED );
                /* Etxecute job end notification */
                MemAcc_Api_JobEndNotification( addressAreaId, MEMACC_MEM_CANCELED );
                MemAcc_JobCtl_SetJobCtlInfoSub();
                MemAcc_JobCtl_SetRAMSub( addressAreaId );
            }
            else if( MEMACC_JOBCTL_ST_RUN == MemAcc_JobRequestTbl[addressAreaId].innerJobStatus )
            {

                /* Get Fls execution status */
                u1_getJobStatus = MemAcc_FlsWrp_GetStatus();

                /* If the Fls execution status is IDLE, the Fls job has been canceled. */
                if( MEMACC_JOB_IDLE ==  u1_getJobStatus )
                {
                    /* Etxecute job control end settings */
                    MemAcc_JobCtl_SetJobEnd( addressAreaId, MEMACC_MEM_CANCELED );

                    /* Etxecute job end notification */
                    MemAcc_Api_JobEndNotification( addressAreaId, MEMACC_MEM_CANCELED );
                }
                /* If the Fls execution state is not IDLE, the Fls job has not been canceled. */
                else
                {
                    /* Set the cancel request status of the job execution control information to ON. */
                    MemAcc_JobCtlInfo.jobCancelStatus = STD_ON;

                    /* Set Internal Job Processing State to Canceled */
                    MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_CANCEL;
                }
                
                MemAcc_JobCtl_SetJobCtlInfoSub();
                MemAcc_JobCtl_SetRAMSub( addressAreaId );
            }
            else
            {
                /* No process */
            }
        }
        /* In case of Mem */
        else if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
        {
            /* If job request is waiting */
            if( MEMACC_JOBCTL_ST_WAIT == MemAcc_JobRequestTbl[addressAreaId].innerJobStatus )
            {
                /* Set the cancel request status of the job execution control information to ON. */
                MemAcc_JobCtlInfo.jobCancelStatus = STD_ON;

                /* Set Internal Job Processing State to Canceled */
                MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_CANCEL;
                MemAcc_JobCtl_SetJobCtlInfoSub();
                MemAcc_JobCtl_SetRAMSub( addressAreaId );
            }
        }
        /* In case of non target driver */
        else
        {
            /* No process */
        }
    }

} /* MemAcc_JobCtl_Cancel */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_Write                                      */
/* Description   | Determine whether to accept MemAcc_Write job request     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | targetAddress    target address for write                */
/*               | sourceDataPtr    pointer to store the source data        */
/*               | length           data length                             */
/* Return Value  | E_OK             The requested job was accepted          */
/*               |                  by the module                           */
/*               | E_NOT_OK         The requested job was not accepted      */
/*               |                  by the module                           */
/* Notes         | Returns E_NOT_OK if AreaID is out of range               */
/*               | Returns E_NOT_OK if the job execution management         */
/*               | TBL status of the target AreaID is not IDLE              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_Write(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_Rtn;
    Std_ReturnType u1_immediateAccess;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    u1_Rtn = E_NOT_OK;

    if( addressAreaId < u2_AdressAreaMax )
    {
        if( MEMACC_JOB_IDLE == MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus )
        {
            u1_immediateAccess = MemAcc_JobCtl_ImmediateAccessPossible( addressAreaId );
            if( (Std_ReturnType)E_OK == u1_immediateAccess )
            {
                u1_Rtn = MemAcc_FlsWrp_Write( targetAddress, sourceDataPtr, length );
            }
            else
            {
                u1_Rtn = E_OK;
            }
            
            if( (Std_ReturnType)E_OK == u1_Rtn )
            {
                MemAcc_JobRequestTbl[addressAreaId].innerJobType = MEMACC_JOBCTL_JOB_WRITE;
                MemAcc_JobRequestTbl[addressAreaId].innerRetryCount = MemAcc_AddrAreaCfg[addressAreaId].MemAccSubAddressAreaConfiguration[MEMACC_U2_VAL_0].MemAccNumberOfWriteRetries;
                MemAcc_JobRequestTbl[addressAreaId].targetAddress = targetAddress;
                MemAcc_JobRequestTbl[addressAreaId].sourceDataPtr = sourceDataPtr;
                MemAcc_JobRequestTbl[addressAreaId].length = length;
                
                if( (Std_ReturnType)E_OK == u1_immediateAccess )
                {
                    MemAcc_JobCtl_SetJobPending( addressAreaId );
                }
                else
                {
                    MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;
                    MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_WAIT;
                }
                
                MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_WRITE_JOB;
                MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_PENDING;

                MemAcc_JobCtl_SetJobCtlInfoSub();
                MemAcc_JobCtl_SetRAMSub( addressAreaId );
            }
        }
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_Write */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_Read                                       */
/* Description   | Determine whether to accept MemAcc_Read job request      */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId         address area ID                    */
/*               | sourceAddress         source address for read            */
/*               | destinationDataPtr    pointer to store the read data     */
/*               | length                data length                        */
/* Return Value  | E_OK                  The requested job was accepted     */
/*               |                       by the module                      */
/*               | E_NOT_OK              The requested job was not accepted */
/*               |                       by the module                      */
/* Notes         | Returns E_NOT_OK if AreaID is out of range               */
/*               | Returns E_NOT_OK if the job execution management         */
/*               |TBL status of the target AreaID is not IDLE               */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_Read(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType sourceAddress,
    P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF ) destinationDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_Rtn;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* If there is no job request for the target address area, the request is held. */
        /* The request is accepted only if the target area ID of the external RAM is IDLE. */
        if( MEMACC_JOB_IDLE == MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus )
        {
            /* Set job execution control status to request monitoring */
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;

            /* Set job management information */
            MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_WAIT;
            MemAcc_JobRequestTbl[addressAreaId].innerJobType = MEMACC_JOBCTL_JOB_READ;
            MemAcc_JobRequestTbl[addressAreaId].innerRetryCount = MEMACC_U1_VAL_0;
            MemAcc_JobRequestTbl[addressAreaId].targetAddress = sourceAddress;
            MemAcc_JobRequestTbl[addressAreaId].destinationDataPtr = destinationDataPtr;
            MemAcc_JobRequestTbl[addressAreaId].length = length;
            
            /* Update Public RAM */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_READ_JOB;           /* Update JobType */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_PENDING;      /* Update JobStatus */
            
            MemAcc_JobCtl_SetJobCtlInfoSub();
            MemAcc_JobCtl_SetRAMSub( addressAreaId );
            
            u1_Rtn = E_OK;
        }
        else
        {
            u1_Rtn = E_NOT_OK;
        }
    }
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_Read */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_Erase                                      */
/* Description   | Determine whether to accept MemAcc_Erase job request     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | targetAddress    target address for erase                */
/*               | length           data length                             */
/* Return Value  | E_OK             The requested job was accepted          */
/*               |                  by the module                           */
/*               | E_NOT_OK         The requested job was not accepted      */
/*               |                  by the module                           */
/* Notes         | Returns E_NOT_OK if AreaID is out of range               */
/*               | Returns E_NOT_OK if the job execution management         */
/*               | TBL status of the target AreaID is not IDLE              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_Erase(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_Rtn;
    Std_ReturnType u1_immediateAccess;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    u1_Rtn = E_NOT_OK;

    if( addressAreaId < u2_AdressAreaMax )
    {
        if( MEMACC_JOB_IDLE == MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus )
        {
            u1_immediateAccess = MemAcc_JobCtl_ImmediateAccessPossible( addressAreaId );
            if( (Std_ReturnType)E_OK == u1_immediateAccess )
            {
                u1_Rtn = MemAcc_FlsWrp_Erase( targetAddress, length );
            }
            else
            {
                u1_Rtn = E_OK;
            }
            
            if( (Std_ReturnType)E_OK == u1_Rtn )
            {
                MemAcc_JobRequestTbl[addressAreaId].innerJobType = MEMACC_JOBCTL_JOB_ERASE;
                MemAcc_JobRequestTbl[addressAreaId].innerRetryCount = MemAcc_AddrAreaCfg[addressAreaId].MemAccSubAddressAreaConfiguration[MEMACC_U2_VAL_0].MemAccNumberOfEraseRetries;
                MemAcc_JobRequestTbl[addressAreaId].targetAddress = targetAddress;
                MemAcc_JobRequestTbl[addressAreaId].length = length;
                
                if( (Std_ReturnType)E_OK == u1_immediateAccess )
                {
                    MemAcc_JobCtl_SetJobPending( addressAreaId );
                }
                else
                {
                    MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;
                    MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_WAIT;
                }
                
                MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_ERASE_JOB;
                MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_PENDING;

                MemAcc_JobCtl_SetJobCtlInfoSub();
                MemAcc_JobCtl_SetRAMSub( addressAreaId );
            }
        }
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_Erase */

#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_JobCtl_BlankCheck                                 */
/* Description   | Determine whether to accept MemAcc_BlankCheck            */
/*               | job request                                              */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | targetAddress    target address for write blank check    */
/*               | length           data length                             */
/* Return Value  | E_OK             The requested job was accepted          */
/*               |                  by the module                           */
/*               | E_NOT_OK         The requested job was not accepted      */
/*               |                  by the module                           */
/* Notes         | Returns E_NOT_OK if AreaID is out of range               */
/*               | Returns E_NOT_OK if the job execution management         */
/*               | TBL status of the target AreaID is not IDLE              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_BlankCheck(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_Rtn;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* If there is no job request for the target address area, the request is held. */
        /* The request is accepted only if the target area ID of the external RAM is IDLE. */
        if( MEMACC_JOB_IDLE == MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus )
        {
            /* Set job execution control status to request monitoring */
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;

            /* Set job management information */
            MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_WAIT;
            MemAcc_JobRequestTbl[addressAreaId].innerJobType = MEMACC_JOBCTL_JOB_BLANKCHECK;
            MemAcc_JobRequestTbl[addressAreaId].innerRetryCount = MEMACC_U1_VAL_0;
            MemAcc_JobRequestTbl[addressAreaId].targetAddress = targetAddress;
            MemAcc_JobRequestTbl[addressAreaId].length = length;
            
            /* Update Public RAM */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_BLANKCHECK_JOB;     /* Update JobType */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_PENDING;      /* Update JobStatus */
            
            MemAcc_JobCtl_SetJobCtlInfoSub();
            MemAcc_JobCtl_SetRAMSub( addressAreaId );

            u1_Rtn = E_OK;
        }
        else
        {
            u1_Rtn = E_NOT_OK;
        }
    }
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_BlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_HwSpecificService                          */
/* Description   | Determine whether to accept MemAcc_HwSpecificService     */
/*               | job request                                              */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | hwId             Hardware ID                             */
/*               | hwServiceId      Hardware specific service ID            */
/*               | dataPtr          pointer to store job buffer             */
/*               | lengthPtr        pointer ot store job buffer length      */
/* Return Value  | E_OK             The requested job was accepted          */
/*               |                  by the module                           */
/*               | E_NOT_OK         The requested job was not accepted      */
/*               |                  by the module                           */
/* Notes         | Returns E_NOT_OK if AreaID is out of range               */
/*               | Returns E_NOT_OK if the job execution management         */
/*               | TBL status of the target AreaID is not IDLE              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_HwSpecificService(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_HwIdType hwId,
    MemAcc_MemHwServiceIdType hwServiceId,
    P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF ) dataPtr,
    P2VAR( MemAcc_LengthType, AUTOMATIC, TYPEDEF ) lengthPtr
)
{
    Std_ReturnType u1_Rtn;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* If there is no job request for the target address area, the request is held. */
        /* The request is accepted only if the target area ID of the external RAM is IDLE. */
        if( MEMACC_JOB_IDLE == MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus )
        {
            /* Set job execution control status to request monitoring */
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;

            /* Set job management information */
            MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_WAIT;
            MemAcc_JobRequestTbl[addressAreaId].innerJobType = MEMACC_JOBCTL_JOB_MEMHWSPECIFIC;
            MemAcc_JobRequestTbl[addressAreaId].innerRetryCount = MEMACC_U1_VAL_0;
            MemAcc_JobRequestTbl[addressAreaId].hwId = hwId;
            MemAcc_JobRequestTbl[addressAreaId].hwServiceId = hwServiceId;
            MemAcc_JobRequestTbl[addressAreaId].destinationDataPtr = dataPtr;
            MemAcc_JobRequestTbl[addressAreaId].lengthPtr = lengthPtr;

            /* Update Public RAM */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_MEMHWSPECIFIC_JOB;  /* Update JobType */
            MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_PENDING;      /* Update JobStatus */
            
            MemAcc_JobCtl_SetJobCtlInfoSub();
            MemAcc_JobCtl_SetRAMSub( addressAreaId );

            u1_Rtn = E_OK;
        }
        else
        {
            u1_Rtn = E_NOT_OK;
        }
    }
    else
    {
        u1_Rtn = E_NOT_OK;
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_HwSpecificService */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_PriorityJudge                              */
/* Description   | This function determines the priority from the job       */
/*               | information management table and selects a target job.   */
/* Preconditions | None                                                     */
/* Parameters    | pt_targetAreaId    pointer to store a target             */
/*               |                    address area ID                       */
/*               | pt_jobRequest      pointer to store a job management     */
/*               |                    infomation                            */
/* Return Value  | E_OK      : A job request detected to execute            */
/*               | E_NOT_OK  : No job requests detected to execute          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE ) 
MemAcc_JobCtl_PriorityJudge(
    P2VAR( MemAcc_AddressAreaIdType, AUTOMATIC, TYPEDEF ) pt_targetAreaId,
    P2VAR( MemAcc_JobRequestManageType, AUTOMATIC, TYPEDEF ) pt_jobRequest
)
{
    uint8 u1_Rtn;
    MemAcc_AddressAreaIdType u2_targetAreaId; /* target address area ID */
    uint16 u2_highestPriority;                /* highest priority */
    uint16 u2_loopCnt;
    uint8 u1_settingFlag;                     /* flag for detected or not */
    uint8 u1_checkLockArea;                   /* For checking the lock status */
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    u1_settingFlag = STD_OFF;
    u2_targetAreaId = MEMACC_ADDRAREA_0;

    /* Check priority */
    for( u2_loopCnt = 0U; u2_loopCnt< u2_AdressAreaMax; u2_loopCnt++ )
    {
        /* If there is a job request, store the job in the address area with higher priority. */
        if( MEMACC_JOBCTL_ST_IDLE != MemAcc_JobRequestTbl[u2_loopCnt].innerJobStatus )
        {
            /* Locked address areas are not subject to priority detection. */
            u1_checkLockArea = MemAcc_SemCtl_CheckAreaLockStatus( (MemAcc_AddressAreaIdType)u2_loopCnt );
            if( (MEMACC_SEMCTL_ST_LOCK != u1_checkLockArea) && (MEMACC_SEMCTL_ST_LOCKEVENT != u1_checkLockArea) )
            {
                /* When extracting for the first time */
                if ( (uint8)STD_OFF == u1_settingFlag )
                {
                    /* Set to extracted and save AreaID/Priority. */
                    u1_settingFlag = STD_ON;
                    u2_targetAreaId = (MemAcc_AddressAreaIdType)u2_loopCnt;
                    u2_highestPriority = MemAcc_AddrAreaCfg[u2_loopCnt].MemAccAddressAreaPriority;
                }
                else
                {
                    if( u2_highestPriority < MemAcc_AddrAreaCfg[u2_loopCnt].MemAccAddressAreaPriority )
                    {
                        u2_targetAreaId = (MemAcc_AddressAreaIdType)u2_loopCnt;
                        u2_highestPriority = MemAcc_AddrAreaCfg[u2_loopCnt].MemAccAddressAreaPriority;
                    }
                }
            }
        }
    }

    /* Set to return value and arguments from extracted data */
    if( (uint8)STD_ON == u1_settingFlag )
    {
        if( (NULL_PTR != pt_targetAreaId) && (NULL_PTR != pt_jobRequest) )
        {
            /* Determine whether to perform higher-level processing from the extracted jobs */
            u1_Rtn = MemAcc_JobCtl_ChangePriority( MemAcc_JobRequestTbl[u2_targetAreaId].innerJobStatus );
            
            /* Store the extracted information in the argument */
            *(pt_targetAreaId) = u2_targetAreaId;
            pt_jobRequest->innerJobStatus     = MemAcc_JobRequestTbl[u2_targetAreaId].innerJobStatus;
            pt_jobRequest->innerJobType       = MemAcc_JobRequestTbl[u2_targetAreaId].innerJobType;
            pt_jobRequest->innerRetryCount    = MemAcc_JobRequestTbl[u2_targetAreaId].innerRetryCount;
            pt_jobRequest->hwId               = MemAcc_JobRequestTbl[u2_targetAreaId].hwId;
            pt_jobRequest->hwServiceId        = MemAcc_JobRequestTbl[u2_targetAreaId].hwServiceId;
            pt_jobRequest->lengthPtr          = MemAcc_JobRequestTbl[u2_targetAreaId].lengthPtr;
            pt_jobRequest->targetAddress      = MemAcc_JobRequestTbl[u2_targetAreaId].targetAddress;
            pt_jobRequest->sourceDataPtr      = MemAcc_JobRequestTbl[u2_targetAreaId].sourceDataPtr;
            pt_jobRequest->destinationDataPtr = MemAcc_JobRequestTbl[u2_targetAreaId].destinationDataPtr;
            pt_jobRequest->length             = MemAcc_JobRequestTbl[u2_targetAreaId].length;
        }
        /* Since the parameter storage area is never specified as NULL, it is not initialized here. */
        else
        {
            /* Set Job Execution Status to IDLE */
            MemAcc_JobCtl_SetJobControlStatus( MEMACC_JOBCTL_IDLE );
            
            /* Set MEMACC_JOBCTL_PRI_NOTIN to the return value, because no processing is required in the upper processing. */
            u1_Rtn = MEMACC_JOBCTL_PRI_NOTING;
        }
    }
    else
    {
        /* Set Job Execution Status to IDLE */
        MemAcc_JobCtl_SetJobControlStatus( MEMACC_JOBCTL_IDLE );
        
        /* Set MEMACC_JOBCTL_PRI_NOTIN to the return value, because no processing is required in the upper processing. */
        u1_Rtn = MEMACC_JOBCTL_PRI_NOTING;
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_PriorityJudge */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_GetJobRequest                              */
/* Description   | This function acquires job information management        */
/*               | for the specified address area ID.                       */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | pt_jobRequest    poiter to store job                     */
/*               |                  information management                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_GetJobRequest(
    MemAcc_AddressAreaIdType addressAreaId,
    P2VAR( MemAcc_JobRequestManageType, AUTOMATIC, TYPEDEF ) pt_jobRequest
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        if( NULL_PTR != pt_jobRequest )
        {
            pt_jobRequest->innerJobStatus     = MemAcc_JobRequestTbl[addressAreaId].innerJobStatus;
            pt_jobRequest->innerJobType       = MemAcc_JobRequestTbl[addressAreaId].innerJobType;
            pt_jobRequest->innerRetryCount    = MemAcc_JobRequestTbl[addressAreaId].innerRetryCount;
            pt_jobRequest->hwId               = MemAcc_JobRequestTbl[addressAreaId].hwId;
            pt_jobRequest->hwServiceId        = MemAcc_JobRequestTbl[addressAreaId].hwServiceId;
            pt_jobRequest->lengthPtr          = MemAcc_JobRequestTbl[addressAreaId].lengthPtr;
            pt_jobRequest->targetAddress      = MemAcc_JobRequestTbl[addressAreaId].targetAddress;
            pt_jobRequest->sourceDataPtr      = MemAcc_JobRequestTbl[addressAreaId].sourceDataPtr;
            pt_jobRequest->destinationDataPtr = MemAcc_JobRequestTbl[addressAreaId].destinationDataPtr;
            pt_jobRequest->length             = MemAcc_JobRequestTbl[addressAreaId].length;
        }
    }
    else
    {
        if( NULL_PTR != pt_jobRequest )
        {
            /* Sets the initial value when an area outside the range is specified. */
            pt_jobRequest->innerJobStatus     = MEMACC_JOBCTL_ST_IDLE;
            pt_jobRequest->innerJobType       = MEMACC_JOBCTL_JOB_NONE;
            pt_jobRequest->innerRetryCount    = MEMACC_U1_VAL_0;
            pt_jobRequest->Dummy_1            = MEMACC_U1_VAL_0;
            pt_jobRequest->hwId               = MEMACC_U4_VAL_0;
            pt_jobRequest->hwServiceId        = MEMACC_U4_VAL_0;
            pt_jobRequest->lengthPtr          = NULL_PTR;
            pt_jobRequest->targetAddress      = MEMACC_ADDRESSTYPE_VAL_0;
            pt_jobRequest->sourceDataPtr      = NULL_PTR;
            pt_jobRequest->destinationDataPtr = NULL_PTR;
            pt_jobRequest->length             = MEMACC_LENGTHTYPE_VAL_0;
        }
    }

} /* MemAcc_JobCtl_GetJobRequest */


/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobPending                              */
/* Description   | This function sets the job processing status             */
/*               | of the specified address area ID to the pending status.  */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId     address area ID                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetJobPending(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Update job processing status to running */
        MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = MEMACC_JOBCTL_ST_RUN;

        /* Update job execution control information to running */
        MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
        MemAcc_JobCtlInfo.jobAddressArea = addressAreaId;
    }

} /* MemAcc_JobCtl_SetJobPending */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobEnd                                  */
/* Description   | This function sets the job information management        */
/*               | of the specified address area ID to the end state,       */
/*               | and sets the job execution state to REQUEST in order to  */
/*               | execute the job request determination in the next cycle. */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | jobResult        job result                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetJobEnd(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobResultType jobResult
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Initializes the job information management TBL and updates the job execution results. */
        MemAcc_JobCtl_JobRequestTbl_Init( addressAreaId );

        /* Set the job priority to be judged in the next cycle. */
        MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_REQUEST;
        
        /* Update Public RAM */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobResult = jobResult;               /* Update JobResult */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = MEMACC_NO_JOB;             /* Update JobType */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = MEMACC_JOB_IDLE;         /* Update JobStatus */
    }

} /* MemAcc_JobCtl_SetJobEnd */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobSuspend                              */
/* Description   | This function sets the running job to suspended.         */
/*               | The job currently being executed is set as the suspend   */
/*               | information, and the job of the specified address area ID*/
/*               | is set to the execution state.                           */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetJobSuspend(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Set the currently running job to suspend information */
        MemAcc_JobRequestTbl[MemAcc_JobCtlInfo.jobAddressArea].innerJobStatus = MEMACC_JOBCTL_ST_SUSPEND;
        MemAcc_JobCtlInfo.suspendStatus = STD_ON;
        MemAcc_JobCtlInfo.suspendAddressArea = MemAcc_JobCtlInfo.jobAddressArea;

        /* Set the specified address area ID to the execution status and set the job status to running. */
        MemAcc_JobCtlInfo.jobAddressArea = addressAreaId;
        
        /* Set the job execution status to the job running */
        MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
    }

} /* MemAcc_JobCtl_SetJobSuspend */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobResume                               */
/* Description   | This function sets the suspended job to resume.          */
/*               | Sets the job of the specified address area ID            */
/*               | to the specified processing state and clears the suspend */
/*               | information.                                             */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | u1_jobStatus     job status                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetJobResume(
    MemAcc_AddressAreaIdType addressAreaId,
    uint8 u1_jobStatus
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Sets the job with the specified address area ID to the specified processing status. */
        MemAcc_JobRequestTbl[addressAreaId].innerJobStatus = u1_jobStatus;

        /* Clear the suspend information in the job execution control information. */
        MemAcc_JobCtlInfo.suspendStatus = STD_OFF;
        MemAcc_JobCtlInfo.suspendAddressArea = MEMACC_U2_VAL_0;
        
        /* Set the specified address area ID to the execution status and set the job status to running. */
        MemAcc_JobCtlInfo.jobAddressArea = addressAreaId;
        
        /* Set the job execution status to the job running */
        MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
    }

} /* MemAcc_JobCtl_SetJobResume */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkInputAreaDt                             */
/* Description   | This function checks whether the access area is within   */
/*               | the valid range.                                         */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | jobStatus        job type                                */
/*               | addressStart     start address                           */
/*               | length           length                                  */
/* Return Value  | E_OK             success                                 */
/*               | E_NOT_OK         failed                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ChkInputAreaDt(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length
)
{
    Std_ReturnType  u1_Rtn;
    uint8 u1_targetDriver;
    
    /* Get driver type of address area ID */
    u1_targetDriver = MemAcc_JobCtl_TargetDriver( addressAreaId );
    
    /* In case of Code Flash */
    if ( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_targetDriver )
    {
        u1_Rtn = MemAcc_JobCtl_ChkCodeFlashArea( jobStatus, addressStart, length );
    }
    /* In case of Data Flash */
    else if ( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_targetDriver )
    {
        u1_Rtn = MemAcc_JobCtl_ChkDataFlashArea( jobStatus, addressStart, length );
    }
    /* In case of non target driver */
    else
    {
        u1_Rtn = E_NOT_OK;
    }
    
    return(u1_Rtn);

} /* MemAcc_JobCtl_ChkInputAreaDt */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetExtJobInfoStatus                        */
/* Description   | This function updates the job execution status of        */
/*               | the specified AreaID in the job execution management     */
/*               | information to be published to the external module.      */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | setJobStatus     job status                              */
/*               | length           length                                  */
/* Return Value  | E_OK             success                                 */
/*               | E_NOT_OK         failed                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetExtJobInfoStatus(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobStatusType setJobStatus
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Update job status on the job infomation management table */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus = setJobStatus;
    }

} /* MemAcc_JobCtl_SetExtJobInfoStatus */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_GetExtJobInfoStatus                        */
/* Description   | This function acquires the job execution status of       */
/*               | the specified AreaID in the job execution management     */
/*               | information to be published to the external module.      */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId             address area ID                */
/* Return Value  | MEMACC_JOB_IDLE           Job not executed               */
/*               | MEMACC_JOB_PENDING        Job running                    */
/* Notes         | If the AreaID provided is out of range,                  */
/*               | this function returns MEMACC_JOB_IDLE.                   */
/****************************************************************************/
FUNC( MemAcc_JobStatusType, MEMACC_CODE )
MemAcc_JobCtl_GetExtJobInfoStatus(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    MemAcc_JobStatusType u1_getJobStatus;
    Std_ReturnType       u1_memJobStatus;
    MemAcc_JobResultType u1_memJobResult;
    Mem_InstanceIdType   u4_instanceId;
    uint8   u1_targetDriver;
    uint16  u2_AdressAreaMax;
    
    u1_memJobResult = MEMACC_MEM_FAILED;
    u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    if( addressAreaId < u2_AdressAreaMax )
    {
        u1_getJobStatus = MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus;
        
        /* when memacc=idle, check lower layer status.*/
        if( u1_getJobStatus == MEMACC_JOB_IDLE )
        {
            u1_targetDriver = MemAcc_JobCtl_TargetDriver( addressAreaId );
            if( u1_targetDriver == MEMACC_JOBCTL_DATAFLASH_DRIVER )
            {
                u1_getJobStatus = MemAcc_FlsWrp_GetStatus();
            }
            else if( u1_targetDriver == MEMACC_JOBCTL_CODEFLASH_DRIVER )
            {
                u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;
                u1_memJobStatus = MemAcc_MemWrp_GetJobResult( u4_instanceId, &u1_memJobResult );
                if( u1_memJobStatus != (Std_ReturnType)E_OK )
                {
                    u1_getJobStatus = MEMACC_JOB_PENDING;
                }
            }
            else{
                /* Nothing To do */
            }
        }
    }
    else
    {
        /* Return Job not executed if out of range */
        u1_getJobStatus = MEMACC_JOB_IDLE;
    }
    
    return ( u1_getJobStatus );

} /* MemAcc_JobCtl_GetExtJobInfoStatus */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetExtJobInfoType                          */
/* Description   | This function updates the job type of the specified      */
/*               | AreaID in the job execution management information to be */
/* Preconditions | None                                                     */
/*               | published to the external module.                        */
/* Parameters    | addressAreaId    address area ID                         */
/*               | setJobType       job type                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetExtJobInfoType(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobType setJobType
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Update job type on the job infomation management table */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType = setJobType;
    }

} /* MemAcc_JobCtl_SetExtJobInfoType */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetExtJobInfoResult                        */
/* Description   | This function updates the job result of the specified    */
/*               | AreaID in the job execution management information       */
/*               | to be published to the external module.                  */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/*               | setJobResult     job result                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetExtJobInfoResult(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobResultType setJobResult
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Update job result on the job infomation management table */
        MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobResult = setJobResult;
    }

} /* MemAcc_JobCtl_SetExtJobInfoResult */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_GetExtJobInfoResult                        */
/* Description   | This function acquires the job result of the specified   */
/*               | AreaID in the job execution management information       */
/*               | to be published to the external module.                  */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                    address area ID         */
/* Return Value  | MEMACC_MEM_OK                    normal end              */
/*               | MEMACC_MEM_FAILED                abnormal end            */
/*               | MEMACC_MEM_INCONSISTENT          expected value mismatch */
/*               | MEMACC_MEM_CANCELED              cancel                  */
/*               | MEMACC_MEM_ECC_UNCORRECTED       unrecoverable ECC error */
/*               | MEMACC_MEM_ECC_CORRECTED         coverable ECC error     */
/* Notes         | If the AreaID provided is out of range,                  */
/*               | this function returns MEMACC_MEM_OK.                     */
/****************************************************************************/
FUNC( MemAcc_JobResultType, MEMACC_CODE )
MemAcc_JobCtl_GetExtJobInfoResult(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    MemAcc_JobResultType u1_getJobResult;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area ID range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Get job result on the job infomation management table */
        u1_getJobResult = MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobResult;
    }
    else
    {
        /* Return normal end if out of range */
        u1_getJobResult = MEMACC_MEM_FAILED;
    }
    
    return ( u1_getJobResult);
    
} /* MemAcc_JobCtl_GetExtJobInfoResult */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ExecJobSuspend                             */
/* Description   | This function exetutes the suspend operation if          */
/*               | the OTA job is running.                                  */
/* Parameters    | None                                                     */
/* Return Value  | MEMACC_JOBCTL_SUSPEND_NONE       Suspend not executed    */
/*               | MEMACC_JOBCTL_SUSPEND_SUCCESS    Suspend success         */
/*               | MEMACC_JOBCTL_SUSPEND_FAILED     Suspend failed          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE )
MemAcc_JobCtl_ExecJobSuspend( void )
{
    uint8 u1_rtn;
    Std_ReturnType u1_funcRet;
    MemAcc_AddressAreaIdType u2_targetAreaId;
    Mem_InstanceIdType u4_instanceId = (Mem_InstanceIdType)MemAcc_MemInstance.MemAcc_MemInstanceId;

    u2_targetAreaId = MemAcc_JobCtlInfo.jobAddressArea;

    /* Set initial return value: Suspend not executed */
    u1_rtn = MEMACC_JOBCTL_SUSPEND_NONE;
    
    /* Currently, if the job is running */
    if ( ( MEMACC_ADDRAREA_0 != u2_targetAreaId ) &&
         ( MEMACC_JOBCTL_ST_RUN == MemAcc_JobRequestTbl[u2_targetAreaId].innerJobStatus ) )
    {
        /* If suspend has not been executed */
        if( (uint8)STD_OFF == MemAcc_JobCtlInfo.suspendStatus )
        {
            u1_funcRet = MemAcc_MemWrp_Suspend( u4_instanceId );    /* Execute suspend operation */
            /* Suspend operation successful */
            if( (Std_ReturnType)E_OK == u1_funcRet )
            {
                /* Set the currently running job to suspend information */
                MemAcc_JobRequestTbl[u2_targetAreaId].innerJobStatus = MEMACC_JOBCTL_ST_SUSPEND;
                MemAcc_JobCtlInfo.suspendStatus = STD_ON;
                MemAcc_JobCtlInfo.suspendAddressArea = u2_targetAreaId;

                /* Set return value to suspend success */
                u1_rtn = MEMACC_JOBCTL_SUSPEND_SUCCESS;
            }
            /* Suspend operation failed */
            else
            {
                /* Set return value to suspend failed */
                u1_rtn = MEMACC_JOBCTL_SUSPEND_FAILED;
            }
        }
        else
        {
            /* Set return value to suspend failed because suspend cannot be executed during suspend. */
            u1_rtn = MEMACC_JOBCTL_SUSPEND_FAILED;
        }
    }

    return ( u1_rtn );

} /* MemAcc_JobCtl_ExecJobSuspend */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | MemAcc_JobCtl_JobRequestTbl_Init                         */
/* Description   | This function initializes the job information management */
/*               | TBL for the specified address area ID.                   */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId    address area ID	                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_JobRequestTbl_Init(
    MemAcc_AddressAreaIdType targetAreaId
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    if( targetAreaId < u2_AdressAreaMax )
    {
        /* Initialize job infomation management table */
        MemAcc_JobRequestTbl[targetAreaId].innerJobStatus     = MEMACC_JOBCTL_ST_IDLE;
        MemAcc_JobRequestTbl[targetAreaId].innerJobType       = MEMACC_JOBCTL_JOB_NONE;
        MemAcc_JobRequestTbl[targetAreaId].innerRetryCount    = MEMACC_U1_VAL_0;
        MemAcc_JobRequestTbl[targetAreaId].Dummy_1            = MEMACC_U1_VAL_0;
        MemAcc_JobRequestTbl[targetAreaId].hwId               = MEMACC_U4_VAL_0;
        MemAcc_JobRequestTbl[targetAreaId].hwServiceId        = MEMACC_U4_VAL_0;
        MemAcc_JobRequestTbl[targetAreaId].lengthPtr          = NULL_PTR;
        MemAcc_JobRequestTbl[targetAreaId].targetAddress      = MEMACC_ADDRESSTYPE_VAL_0;
        MemAcc_JobRequestTbl[targetAreaId].sourceDataPtr      = NULL_PTR;
        MemAcc_JobRequestTbl[targetAreaId].destinationDataPtr = NULL_PTR;
        MemAcc_JobRequestTbl[targetAreaId].length             = MEMACC_LENGTHTYPE_VAL_0;
    }
} /* MemAcc_JobCtl_JobRequestTbl_Init */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_JobCtlExtInfoTbl_Init	                    */
/* Description   | This function initializes the job execution status       */
/*               | management information for the specified add	            */
/* Preconditions | None                                                     */
/* Parameters    | targetAreaId    address area ID	                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_JobCtlExtInfoTbl_Init(
    MemAcc_AddressAreaIdType targetAreaId
)
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    if( targetAreaId < u2_AdressAreaMax )
    {
        /*  Initialize job execution status management information */
        MemAcc_JobCtlExtInfoTbl[targetAreaId].extJobStatus     = MEMACC_JOB_IDLE;
        MemAcc_JobCtlExtInfoTbl[targetAreaId].extJobType       = MEMACC_NO_JOB;
        MemAcc_JobCtlExtInfoTbl[targetAreaId].extJobResult     = MEMACC_MEM_OK;
        MemAcc_JobCtlExtInfoTbl[targetAreaId].Dummy_1          = MEMACC_U1_VAL_0;
    }
    
} /* MemAcc_JobCtl_JobCtlExtInfoTbl_Init */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChangePriority                             */
/* Description   | This function determines what to do with the selected    */
/*               | high priority job.                                       */
/* Preconditions | None                                                     */
/* Parameters    | targetJobStatus    internal job status                   */
/* Return Value  | MEMACC_JOBCTL_PRI_NOTING    No need to execute           */
/*               | MEMACC_JOBCTL_PRI_JOBSTART  Start job execution required */
/*               | MEMACC_JOBCTL_PRI_SUSPEND   Suspend execution required   */
/*               | MEMACC_JOBCTL_PRI_RESUME    Resume execution required    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE ) 
MemAcc_JobCtl_ChangePriority(
    uint8 targetJobStatus
)
{
    uint8 u1_Rtn;
    
    /* When the internal job status is Waiting */
    if( MEMACC_JOBCTL_ST_WAIT == targetJobStatus )
    {
        /* When a job with any address area ID is suspended */
        if( (uint8)STD_ON == MemAcc_JobCtlInfo.suspendStatus )
        {
            /* Set the job execution status to RUN to run the target job. */
            MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
            
            /* When there is no job to be executed due to suspension for synchronous API execution, the priority determined job is started. */
            if( MEMACC_JOBCTL_ST_RUN != MemAcc_JobRequestTbl[MemAcc_JobCtlInfo.jobAddressArea].innerJobStatus )
            {
                u1_Rtn = MEMACC_JOBCTL_PRI_JOBSTART;
            }
            else
            {
                u1_Rtn = MEMACC_JOBCTL_PRI_NOTING;
            }
        }
        else
        {
            /* Judging whether to suspend */
            u1_Rtn = MemAcc_JobCtl_ChkJobSuspend();
            if ( MEMACC_JOBCTL_PRI_NOTING == u1_Rtn )
            {
                /* Set the job execution status to RUN to continue the currently running operation. */
                MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
            }
        }
    }
    /* When the internal job status is Suspend */
    else if( MEMACC_JOBCTL_ST_SUSPEND == targetJobStatus )
    {
        /* Instruct to execute Resume */
        u1_Rtn = MEMACC_JOBCTL_PRI_RESUME;
    }
    /* The internal job status is not Waiting or Suspend. */
    else
    {   /* Set the job execution status to RUN to continue the currently running operation. */
        MemAcc_JobCtlInfo.jobControlStatus = MEMACC_JOBCTL_RUN;
        u1_Rtn = MEMACC_JOBCTL_PRI_NOTING;
    }
    
    /* Set the operation instruction after priority judgment as the return value */
    return ( u1_Rtn );
    
} /* MemAcc_JobCtl_ChangePriority */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkJobSuspend                              */
/* Description   | This function determines whether a running job           */
/*               | can be suspended.                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | MEMACC_JOBCTL_PRI_NOTING    No need to execute           */
/*               | MEMACC_JOBCTL_PRI_JOBSTART  Start job execution required */
/*               | MEMACC_JOBCTL_PRI_SUSPEND   Suspend execution required   */
/* Notes         | Only drivers with the suspend function can be suspended. */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE )
MemAcc_JobCtl_ChkJobSuspend( void )
{
    uint8 u1_Rtn;
    uint8 u1_driverType;    /* Fls/Mem */
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* When a job is being executed and there is no suspend information */
    if ( MemAcc_JobCtlInfo.jobAddressArea < u2_AdressAreaMax )
    {
        /* It is necessary to check whether the job is suspended since it cannot be switched during suspension, but it has been checked before calling this API. */
        if( MEMACC_JOBCTL_ST_RUN == MemAcc_JobRequestTbl[MemAcc_JobCtlInfo.jobAddressArea].innerJobStatus ) 
        {
            /* Get the driver type of area ID */
            u1_driverType = MemAcc_JobCtl_TargetDriver( MemAcc_JobCtlInfo.jobAddressArea );

            /* Get the driver type. It is suspendable if the driver type is the code flash */
            if( MEMACC_JOBCTL_CODEFLASH_DRIVER == u1_driverType )
            {
                /* Execute suspend */
                u1_Rtn = MEMACC_JOBCTL_PRI_SUSPEND;
            }
            else
            {
                /* Unable to Suspend, continue current operation */
                u1_Rtn = MEMACC_JOBCTL_PRI_NOTING;
            }
        }
        else
        {
            /* Execute the job */
            u1_Rtn = MEMACC_JOBCTL_PRI_JOBSTART;
        }
    }
    else
    {
        /* If it is out of range, the job is executed because it is not currently operating. */
        u1_Rtn = MEMACC_JOBCTL_PRI_JOBSTART;
    }

    return ( u1_Rtn );

} /* MemAcc_JobCtl_ChkJobSuspend */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkCodeFlashArea                           */
/* Description   | This function checks the address and length of the       */
/*               | Code Flash set in the argument.                          */
/* Preconditions | None                                                     */
/* Parameters    | jobStatus       job type                                 */
/*               | addressStart    start address                            */
/*               | length          size                                     */
/* Return Value  | E_OK            OK                                       */
/*               | E_NOT_OK        Not OK                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ChkCodeFlashArea(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length
)
{
    Std_ReturnType  u1_Rtn = E_NOT_OK;
    uint16 u2_count;
    uint16 u2_MembankMax;
    MemAcc_AddressType u4_startAddress;
    MemAcc_AddressType u4_endAddress;
    MemAcc_LengthType u4_eraseSize;
    MemAcc_LengthType u4_readSize;
    MemAcc_LengthType u4_blankSize;
    MemAcc_LengthType u4_writeSize;
    
    u2_MembankMax = MemAcc_MemBank_Max;
    
    for( u2_count = 0U ; u2_count < u2_MembankMax ; u2_count++ )
    {
        /* Extract from Config */
        u4_eraseSize = MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemEraseSectorSize;
        u4_readSize = MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemReadPageSize;
        u4_blankSize = MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemWritePageSize;          /* BlankCheck is the same as Write */
        u4_writeSize = MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemWritePageSize;
        
        u4_startAddress = MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemStartAddress;
        u4_endAddress = ( ( u4_startAddress + ( u4_eraseSize * MemAcc_MemInstance.MemAcc_MemSectorBatch[u2_count].MemAcc_MemNumberOfSectors ) ) - MEMACC_U4_VAL_1 );
        
        /* Address valid value check */
        u1_Rtn = MemAcc_JobCtl_ChkAddress( addressStart, length, u4_startAddress, u4_endAddress );
        if ( (Std_ReturnType)E_OK == u1_Rtn )
        {
            /* Length valid value check */
            u1_Rtn = MemAcc_JobCtl_ChkLength( jobStatus, addressStart, length, u4_writeSize, u4_readSize, u4_blankSize, u4_eraseSize );
            if ( (Std_ReturnType)E_OK == u1_Rtn )
            {
                /* Since it is valid data, it is finished with OK. */
                break;
            }
        }
    }
    
    return(u1_Rtn);

} /* MemAcc_JobCtl_ChkCodeFlashArea */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkDataFlashArea                           */
/* Description   | This function checks the address and length of the       */
/*               | Data Flash set in the argument.                          */
/* Preconditions | None                                                     */
/* Parameters    | jobStatus       job type                                 */
/*               | addressStart    start address                            */
/*               | length          size                                     */
/* Return Value  | E_OK            OK                                       */
/*               | E_NOT_OK        Not OK                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ChkDataFlashArea(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length
)
{
    Std_ReturnType  u1_Rtn;
    
    /* Address Valid value check */
    /* Although different from the original start address, set the start address to 0x00000000UL in accordance with the current Fls. */
    u1_Rtn = MemAcc_JobCtl_ChkAddress( addressStart, length, MEMACC_ADDRESSTYPE_VAL_0, ( MEMACC_DATA_FLASH_ADDRESS_END - MEMACC_DATA_FLASH_ADDRESS_START ) );
    if ( (Std_ReturnType)E_OK == u1_Rtn )
    {
        /* Length valid value Check */
        u1_Rtn = MemAcc_JobCtl_ChkLength( jobStatus, addressStart, length, MEMACC_WRITE_SIZE, MEMACC_READ_SIZE, MEMACC_BLANKCHECK_SIZE, MEMACC_ERASE_SIZE );
    }
    
    return(u1_Rtn);

} /* MemAcc_JobCtl_ChkDataFlashArea */


/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkAddress                                 */
/* Description   | This function checks the valid range of the specified    */
/*               | address.                                                 */
/* Preconditions | None                                                     */
/* Parameters    | addressStart    start address                            */
/*               | length          size                                     */
/*               | startAddress    start address of target Flash Memory     */
/*               | endAddress      end address of target Flash Memory       */
/* Return Value  | E_OK            OK                                       */
/*               | E_NOT_OK        Not OK                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ChkAddress(
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length,
    MemAcc_AddressType startAddress,
    MemAcc_AddressType endAddress
)
{
    Std_ReturnType  u1_Rtn;
    MemAcc_AddressType addressEnd;
    
    u1_Rtn = E_NOT_OK;
    
    /* Check if the address is within range */
    if ( ( startAddress <= addressStart ) && ( addressStart <= endAddress ) )
    {
        addressEnd = addressStart + length;
        /* Check access area */
        if ( addressEnd != MEMACC_ADDRESSTYPE_VAL_0 )
        {
            addressEnd = addressEnd - MEMACC_ADDRESSTYPE_VAL_1;
            if ( addressEnd <= endAddress )
            {
                u1_Rtn = E_OK;
            }
        }
    }
    
    return(u1_Rtn);

} /* MemAcc_JobCtl_ChkAddress */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ChkLength                                  */
/* Description   | This function checks the validity of the specified size. */
/* Preconditions | None                                                     */
/* Parameters    | jobStatus       job type                                 */
/*               | addressStart    start address                            */
/*               | length          size                                     */
/*               | writeSize       minimum write size                       */
/*               | readSize        minimum read size                        */
/*               | blankSize       minimum blank check size                 */
/*               | eraseSize       minimum erase size                       */
/* Return Value  | E_OK            OK                                       */
/*               | E_NOT_OK        Not OK                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ChkLength(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length,
    MemAcc_LengthType writeSize,
    MemAcc_LengthType readSize,
    MemAcc_LengthType blankSize,
    MemAcc_LengthType eraseSize
)
{
    Std_ReturnType  u1_Rtn;
    
    u1_Rtn = E_NOT_OK;
    
    /* If the specified size is not 0, check the range, and if it is 0, return Not OK. */
    if ( MEMACC_U4_VAL_0 != length ) 
    {
        
        /* Check for integral multiples of address and length for each job type */
        switch ( jobStatus )
        {
            case MEMACC_WRITE_JOB:                                /* Write job */
                /* OK if divisible by write size */
                if ( ( MEMACC_U4_VAL_0 == ( addressStart & ( writeSize - MEMACC_U4_VAL_1 ) ) ) &&
                     ( MEMACC_U4_VAL_0 == ( length & ( writeSize - MEMACC_U4_VAL_1 ) ) ) )
                {
                    u1_Rtn = E_OK;
                }
                break;
            case MEMACC_READ_JOB:                                 /* Read job */
                /* OK if divisible by read size */
                if ( ( MEMACC_U4_VAL_0 == ( addressStart & ( readSize - MEMACC_U4_VAL_1 ) ) ) &&
                     ( MEMACC_U4_VAL_0 == ( length & ( readSize - MEMACC_U4_VAL_1 ) ) ) )
                {
                    u1_Rtn = E_OK;
                }
                break;
            case MEMACC_BLANKCHECK_JOB:                           /* BlankCheck job */
                /* OK if divisible by blank check size */
                if ( ( MEMACC_U4_VAL_0 == ( addressStart & ( blankSize - MEMACC_U4_VAL_1 ) ) ) &&
                     ( MEMACC_U4_VAL_0 == ( length & ( blankSize - MEMACC_U4_VAL_1 ) ) ) )
                {
                    u1_Rtn = E_OK;
                }
                break;
            case MEMACC_ERASE_JOB:                                /* Erase job */
                /* OK if divisible by erase size */
                if ( ( MEMACC_U4_VAL_0 == ( addressStart & ( eraseSize - MEMACC_U4_VAL_1 ) ) ) &&
                     ( MEMACC_U4_VAL_0 == ( length & ( eraseSize - MEMACC_U4_VAL_1 ) ) ) )
                {
                   u1_Rtn = E_OK;
                }
                break;
            default:
                /* No process */
                break;
        }
    }
    
    return(u1_Rtn);

} /* MemAcc_JobCtl_ChkLength */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ImmediateAccessPossible                    */
/* Description   | This function checks the immediate flash access.         */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/* Return Value  | E_OK             immediate access possible               */
/*               | E_NOT_OK         immediate access impossible             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_ImmediateAccessPossible( 
    MemAcc_AddressAreaIdType addressAreaId
)
{
    Std_ReturnType u1_Rtn;
    uint8 u1_driverType;
    uint8 u1_LockStatus;
    uint16 u2_loopCnt;
    uint16 u2_AdressAreaMax;
    
    u1_Rtn = E_NOT_OK;

    u1_driverType = MemAcc_JobCtl_TargetDriver( addressAreaId );
    if( MEMACC_JOBCTL_DATAFLASH_DRIVER == u1_driverType )
    {
        u1_LockStatus = MemAcc_SemCtl_CheckAreaLockStatus( addressAreaId );
        if ( MEMACC_SEMCTL_ST_UNLOCK == u1_LockStatus )
        {
            u1_Rtn = E_OK;
            
            u2_AdressAreaMax = MemAcc_AddressArea_Max;
            for( u2_loopCnt = 0x0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
            {
                if( MEMACC_JOB_IDLE != MemAcc_JobCtlExtInfoTbl[u2_loopCnt].extJobStatus)
                {
                    u1_Rtn = E_NOT_OK;
                    break;
                }
            }
        }
    }

    return( u1_Rtn );

} /* MemAcc_JobCtl_ImmediateAccessPossible */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_CheckRAM                                   */
/* Description   | Checks for garbled RAM.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | E_OK             RAM is not garbled                      */
/*               | E_NOT_OK         RAM is garbled                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_JobCtl_CheckRAM( void )
{
    uint16 u2_loopCnt;
    uint16 u2_AdressAreaMax;
    Std_ReturnType Rtn = E_NOT_OK;

    if((( MemAcc_JobCtlInfo.jobControlStatus   ^ MemAcc_JobCtlInfoSub.jobControlStatus   ) == (uint8)MEMACC_MIRROR_CHECK_UINT8 )
    && (( MemAcc_JobCtlInfo.jobAddressArea     ^ MemAcc_JobCtlInfoSub.jobAddressArea     ) == (MemAcc_AddressAreaIdType)MEMACC_MIRROR_CHECK_UINT16 )
    && (( MemAcc_JobCtlInfo.suspendStatus      ^ MemAcc_JobCtlInfoSub.suspendStatus      ) == (uint8)MEMACC_MIRROR_CHECK_UINT8 )
    && (( MemAcc_JobCtlInfo.suspendAddressArea ^ MemAcc_JobCtlInfoSub.suspendAddressArea ) == (MemAcc_AddressAreaIdType)MEMACC_MIRROR_CHECK_UINT16 )
    && (( MemAcc_JobCtlInfo.jobCancelStatus    ^ MemAcc_JobCtlInfoSub.jobCancelStatus    ) == (uint8)MEMACC_MIRROR_CHECK_UINT8 )
    && (( MemAcc_JobCtlInfo.jobRamGarbled      ^ MemAcc_JobCtlInfoSub.jobRamGarbled      ) == (uint8)MEMACC_MIRROR_CHECK_UINT8 ))
    {
        Rtn = E_OK;
        u2_AdressAreaMax = MemAcc_AddressArea_Max;
        for( u2_loopCnt = 0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
        {
            if((( MemAcc_JobRequestTbl[u2_loopCnt].innerJobStatus      ^ MemAcc_JobRequestTblSub[u2_loopCnt].innerJobStatus     ) != (uint8)MEMACC_MIRROR_CHECK_UINT8 )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].innerJobType        ^ MemAcc_JobRequestTblSub[u2_loopCnt].innerJobType       ) != (uint8)MEMACC_MIRROR_CHECK_UINT8 )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].innerRetryCount     ^ MemAcc_JobRequestTblSub[u2_loopCnt].innerRetryCount    ) != (uint8)MEMACC_MIRROR_CHECK_UINT8 )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].hwId                ^ MemAcc_JobRequestTblSub[u2_loopCnt].hwId               ) != (MemAcc_HwIdType)MEMACC_MIRROR_CHECK_UINT32 )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].hwServiceId         ^ MemAcc_JobRequestTblSub[u2_loopCnt].hwServiceId        ) != (MemAcc_MemHwServiceIdType)MEMACC_MIRROR_CHECK_UINT32 )
            || (  MemAcc_JobRequestTbl[u2_loopCnt].lengthPtr          != MemAcc_JobRequestTblSub[u2_loopCnt].lengthPtr          )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].targetAddress       ^ MemAcc_JobRequestTblSub[u2_loopCnt].targetAddress      ) != (MemAcc_AddressType)MEMACC_MIRROR_CHECK_UINT32 )
            || (  MemAcc_JobRequestTbl[u2_loopCnt].sourceDataPtr      != MemAcc_JobRequestTblSub[u2_loopCnt].sourceDataPtr      )
            || (  MemAcc_JobRequestTbl[u2_loopCnt].destinationDataPtr != MemAcc_JobRequestTblSub[u2_loopCnt].destinationDataPtr )
            || (( MemAcc_JobRequestTbl[u2_loopCnt].length              ^ MemAcc_JobRequestTblSub[u2_loopCnt].length             ) != (MemAcc_LengthType)MEMACC_MIRROR_CHECK_UINT32 )
            || (( MemAcc_JobCtlExtInfoTbl[u2_loopCnt].extJobStatus     ^ MemAcc_JobCtlExtInfoTblSub[u2_loopCnt].extJobStatus    ) != (MemAcc_JobStatusType)MEMACC_MIRROR_CHECK_UINT8 )
            || (( MemAcc_JobCtlExtInfoTbl[u2_loopCnt].extJobType       ^ MemAcc_JobCtlExtInfoTblSub[u2_loopCnt].extJobType      ) != (MemAcc_JobType)MEMACC_MIRROR_CHECK_UINT8 )
            || (( MemAcc_JobCtlExtInfoTbl[u2_loopCnt].extJobResult     ^ MemAcc_JobCtlExtInfoTblSub[u2_loopCnt].extJobResult    ) != (MemAcc_JobResultType)MEMACC_MIRROR_CHECK_UINT8 ))
            {
                Rtn = E_NOT_OK;
                break;
            }
        }
    }

    return Rtn;

} /* MemAcc_JobCtl_CheckRAM */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetJobCtlInfoSub                           */
/* Description   | Sets redundancy RAM if RAM is not garbled.               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_SetJobCtlInfoSub( void )
{
    MemAcc_JobCtlInfoSub.jobControlStatus   = (uint8)(~MemAcc_JobCtlInfo.jobControlStatus);
    MemAcc_JobCtlInfoSub.jobAddressArea     = (MemAcc_AddressAreaIdType)(~MemAcc_JobCtlInfo.jobAddressArea);
    MemAcc_JobCtlInfoSub.suspendStatus      = (uint8)(~MemAcc_JobCtlInfo.suspendStatus);
    MemAcc_JobCtlInfoSub.suspendAddressArea = (MemAcc_AddressAreaIdType)(~MemAcc_JobCtlInfo.suspendAddressArea);
    MemAcc_JobCtlInfoSub.jobCancelStatus    = (uint8)(~MemAcc_JobCtlInfo.jobCancelStatus);
    MemAcc_JobCtlInfoSub.jobRamGarbled      = (uint8)(~MemAcc_JobCtlInfo.jobRamGarbled);
    
} /* MemAcc_JobCtl_SetJobCtlInfoSub */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetRAMSub                                  */
/* Description   | Sets redundancy RAM if RAM is not garbled.               */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId    address area ID                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_SetRAMSub( MemAcc_AddressAreaIdType addressAreaId )
{
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    if ( addressAreaId < u2_AdressAreaMax )
    {
        MemAcc_JobRequestTblSub[addressAreaId].innerJobStatus     = (uint8)(~MemAcc_JobRequestTbl[addressAreaId].innerJobStatus);
        MemAcc_JobRequestTblSub[addressAreaId].innerJobType       = (uint8)(~MemAcc_JobRequestTbl[addressAreaId].innerJobType);
        MemAcc_JobRequestTblSub[addressAreaId].innerRetryCount    = (uint8)(~MemAcc_JobRequestTbl[addressAreaId].innerRetryCount);
        MemAcc_JobRequestTblSub[addressAreaId].hwId               = (MemAcc_HwIdType)(~MemAcc_JobRequestTbl[addressAreaId].hwId);
        MemAcc_JobRequestTblSub[addressAreaId].hwServiceId        = (MemAcc_MemHwServiceIdType)(~MemAcc_JobRequestTbl[addressAreaId].hwServiceId);
        MemAcc_JobRequestTblSub[addressAreaId].lengthPtr          = MemAcc_JobRequestTbl[addressAreaId].lengthPtr;
        MemAcc_JobRequestTblSub[addressAreaId].targetAddress      = (MemAcc_AddressType)(~MemAcc_JobRequestTbl[addressAreaId].targetAddress);
        MemAcc_JobRequestTblSub[addressAreaId].sourceDataPtr      = MemAcc_JobRequestTbl[addressAreaId].sourceDataPtr;
        MemAcc_JobRequestTblSub[addressAreaId].destinationDataPtr = MemAcc_JobRequestTbl[addressAreaId].destinationDataPtr;
        MemAcc_JobRequestTblSub[addressAreaId].length             = (MemAcc_LengthType)(~MemAcc_JobRequestTbl[addressAreaId].length);
        
        MemAcc_JobCtlExtInfoTblSub[addressAreaId].extJobStatus    = (MemAcc_JobStatusType)(~MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobStatus);
        MemAcc_JobCtlExtInfoTblSub[addressAreaId].extJobType      = (MemAcc_JobType)(~MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobType);
        MemAcc_JobCtlExtInfoTblSub[addressAreaId].extJobResult    = (MemAcc_JobResultType)(~MemAcc_JobCtlExtInfoTbl[addressAreaId].extJobResult);
    }
    
} /* MemAcc_JobCtl_SetRAMSub */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetRAMSubAll                               */
/* Description   | Sets redundancy RAM if RAM is not garbled.               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_SetRAMSubAll( void )
{
    uint16 u2_loopCnt;
    uint16 u2_AdressAreaMax = MemAcc_AddressArea_Max;

    MemAcc_JobCtl_SetJobCtlInfoSub();
    for( u2_loopCnt = 0U; u2_loopCnt < u2_AdressAreaMax; u2_loopCnt++ )
    {
        MemAcc_JobCtl_SetRAMSub( u2_loopCnt );
    }
    
} /* MemAcc_JobCtl_SetRAMSubAll */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_SetRAMGarbled                              */
/* Description   | Sets RAM garbled.                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_SetRAMGarbled( void )
{
    MemAcc_JobCtlInfo.jobRamGarbled = STD_ON;
} /* MemAcc_JobCtl_SetRAMGarbled */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_GetRAMGarbled                              */
/* Description   | Gets RAM garbled.                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | STD_OFF        RAM is not garbled                        */
/*               | STD_ON         RAM is garbled                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE )
MemAcc_JobCtl_GetRAMGarbled( void )
{
    return MemAcc_JobCtlInfo.jobRamGarbled;
} /* MemAcc_JobCtl_GetRAMGarbled */

/****************************************************************************/
/* Function Name | MemAcc_JobCtl_ClearJobCtlInfo                            */
/* Description   | Clears MemAcc_JobCtlInfo and RAMGarbled                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_JobCtl_ClearJobCtlInfo( void )
{
    MemAcc_JobCtlInfo.jobAddressArea     = MEMACC_U2_VAL_0;
    MemAcc_JobCtlInfo.suspendStatus      = STD_OFF;
    MemAcc_JobCtlInfo.suspendAddressArea = MEMACC_U2_VAL_0;
    MemAcc_JobCtlInfo.jobCancelStatus    = STD_OFF;
    MemAcc_JobCtlInfo.jobRamGarbled      = STD_OFF;
} /* MemAcc_JobCtl_ClearJobCtlInfo */

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

