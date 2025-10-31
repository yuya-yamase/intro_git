/* MemAcc.c v2-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include "../inc/MemAcc_Api.h"
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_Mpu_Const.h"
#include "../inc/MemAcc_Internal.h"
#include "../usr/MemAcc_Pif_UserHook.h"
#include <SchM_MemAcc.h>
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
#define MEMACC_START_SEC_CONST_32
#include <MemAcc_MemMap.h>

/* MemAcc module version information */
CONST( AB_83_ConstV Std_VersionInfoType, MEMACC_CONST ) MemAcc_VersionInfo = {
    MEMACC_VENDOR_ID,          /* vendorID          */
    MEMACC_MODULE_ID,          /* moduleID          */
    MEMACC_SW_MAJOR_VERSION,   /* sw_major_version  */
    MEMACC_SW_MINOR_VERSION,   /* sw_minor_version  */
    MEMACC_SW_PATCH_VERSION    /* sw_patch_version  */
};

#define MEMACC_STOP_SEC_CONST_32
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
/* Function Name | MemAcc_Init                                              */
/* Description   | Initialize all variables and set the module state        */
/*               | to Initialized.                                          */
/*               | It also starts the Flash Driver Initial function         */
/*               | and initializes the Driver state.                        */
/* Preconditions | None                                                     */
/* Parameters    | configPtr    Pointer to selected configuration structure */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Init(
    P2CONST( MemAcc_ConfigType, AUTOMATIC, MEMACC_CONFIG_DATA ) configPtr
)
{
    /* Update the initialization execution state */
    MemAcc_Api_init();
    
} /* MemAcc_Init */

/****************************************************************************/
/* Function Name | MemAcc_DeInit                                            */
/* Description   | Uninitialize the module. If there are pending            */
/*               | operations, terminate them immediately.                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | To accept a new request, the MemAcc must be              */
/*               | reinitialized.                                           */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_DeInit( void )
{
    
} /* MemAcc_DeInit */

/****************************************************************************/
/* Function Name | MemAcc_GetVersionInfo                                    */
/* Description   | This function gets the Version information               */
/*               | of the MemAcc module.                                    */
/* Preconditions | None                                                     */
/* Parameters    | versionInfoPtr   Pointer to store the version information*/
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_GetVersionInfo( 
    P2VAR( Std_VersionInfoType, AUTOMATIC, MEMACC_APPL_DATA ) versionInfoPtr
)
{
    if( (Std_VersionInfoType *)NULL_PTR != versionInfoPtr )
    {
        *( versionInfoPtr ) = MemAcc_VersionInfo;
    }
    
} /* MemAcc_GetVersionInfo */

/****************************************************************************/
/* Function Name | MemAcc_GetJobResult                                      */
/* Description   | This function reports the result of processing the API   */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/* Return Value  | MEMACC_MEM_OK                 Normal end                 */
/*               | MEMACC_MEM_FAILED             Abnormal end               */
/*               | MEMACC_MEM_INCONSISTENT       result mismatch            */
/*               | MEMACC_MEM_CANCELED           canceled                   */
/*               | MEMACC_MEM_ECC_UNCORRECTED    uncorrectable ECC error    */
/*               | MEMACC_MEM_ECC_CORRECTED      correctable ECC error      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemAcc_JobResultType, MEMACC_CODE ) 
MemAcc_GetJobResult( 
    MemAcc_AddressAreaIdType addressAreaId
)
{
    MemAcc_JobResultType u1_rtn;
    
    /* AreaID range check is performed by the following API */
    u1_rtn = MemAcc_JobCtl_GetExtJobInfoResult( addressAreaId );
    
    return ( u1_rtn );
    
} /* MemAcc_GetJobResult */

/****************************************************************************/
/* Function Name | MemAcc_GetJobStatus                                      */
/* Description   | This function reports the Job status of the MEMACC       */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/* Return Value  | MEMACC_JOB_IDLE               Job not executed           */
/*               | MEMACC_JOB_PENDING            Job processing             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemAcc_JobStatusType, MEMACC_CODE ) 
MemAcc_GetJobStatus(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    MemAcc_JobStatusType u1_rtn;
    
   /* AreaID range check is performed by the following API */
    u1_rtn = MemAcc_JobCtl_GetExtJobInfoStatus( addressAreaId );
    
    return ( u1_rtn );

} /* MemAcc_GetJobStatus */

/****************************************************************************/
/* Function Name | MemAcc_GetMemoryInfo                                     */
/* Description   | This function obtains memory information for the address */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | address                       address                    */
/*               | memoryInfoPtr                 pointer to store the memory*/
/*               |                               information                */
/* Return Value  | E_OK                          Request Accepted Successful*/
/*               | E_NOT_OK                      Request Accepted Failed    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_GetMemoryInfo(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType address,
    P2VAR( MemAcc_MemoryInfoType, AUTOMATIC, TYPEDEF ) memoryInfoPtr
)
{
    return ( E_NOT_OK );

} /* MemAcc_GetMemoryInfo */

/****************************************************************************/
/* Function Name | MemAcc_GetProcessedLength                                */
/* Description   | This function returns the cumulative number of bytes     */
/*               | already processed by the Job specified by AreaID.        */
/* Preconditions | None                                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                address area ID             */
/* Return Value  | Length                       Processed length of         */
/*               |                              current job(in bytes).      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemAcc_LengthType, MEMACC_CODE ) 
MemAcc_GetProcessedLength(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    return ( MEMACC_LENGTHTYPE_VAL_0 );

} /* MemAcc_GetProcessedLength */

/****************************************************************************/
/* Function Name | MemAcc_GetJobInfo                                        */
/* Description   | This function obtains detailed information such          */
/*               | as the processing status of the Job specified by AreaID. */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId       address area ID                      */
/*               | obInfoPtr           pointer to store the Job information */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_GetJobInfo(
    MemAcc_AddressAreaIdType addressAreaId,
    P2VAR( MemAcc_JobInfoType, AUTOMATIC, TYPEDEF ) jobInfoPtr
)
{
    
} /* MemAcc_GetJobInfo */

/****************************************************************************/
/* Function Name | MemAcc_ActivateMem                                       */
/* Description   | Dynamic activation and initialization of a Mem driver    */
/*               | referenced by hwId and headerAddress.                    */
/* Preconditions | None                                                     */
/* Parameters    | headerAddress    Physical start address of               */
/*               |                  Mem driver header structure.            */
/*               | hwId             Unique numeric memory driver identifier.*/
/* Return Value  | E_OK             Mem driver activation successful.       */
/*               | E_NOT_OK         Mem driver activation failed.           */
/* Notes         | None                                                     */
/****************************************************************************/

FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_ActivateMem(
    MemAcc_AddressType headerAddress,
    MemAcc_HwIdType hwId
)
{
    
    return ( E_NOT_OK );

} /* MemAcc_ActivateMem */

/****************************************************************************/
/* Function Name | MemAcc_DeactivateMem                                     */
/* Description   | Dynamic deactivation of a Mem driver referenced          */
/*               | by hwId and headerAddress.                               */
/* Preconditions | None                                                     */
/* Parameters    | hwId             Unique numeric memory driver identifier.*/
/*               | headerAddress    Physical start address of               */
/*               |                  Mem driver header structure.            */
/* Return Value  | E_OK             Mem driver activation successful.       */
/*               | E_NOT_OK         Mem driver activation failed.           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_DeactivateMem(
    MemAcc_HwIdType hwId,
    MemAcc_AddressType headerAddress
)
{
    
    return ( E_NOT_OK );

} /* MemAcc_DeactivateMem */

/*****************************************************************************
      Asynchronous Function
*****************************************************************************/
/****************************************************************************/
/* Function Name | MemAcc_Cancel                                            */
/* Description   | This function cancels the Job specified by AreaID.       */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId         address area ID                    */
/* Return Value  | None                                                     */
/* Notes         | For the Mem Driver, execute only for pending Jobs.       */
/*               | For the Fls Driver, also execute for the Job             */
/*               | that is running.                                         */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_Cancel(
    MemAcc_AddressAreaIdType addressAreaId
)
{
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Execute cancel request */
        MemAcc_JobCtl_Cancel( addressAreaId );
    }
    
} /* MemAcc_Cancel */

/****************************************************************************/
/* Function Name | MemAcc_Read                                              */
/* Description   | This function accepts a Read request for the Job         */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId         address area ID                    */
/*               | sourceAddress         source address for read            */
/*               | destinationDataPtr    pointer to store the read data     */
/*               | length                data length                        */
/* Return Value  | E_OK                  The requested job was accepted     */
/*               | E_NOT_OK              The requested job was not accepted */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Read(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType sourceAddress,
    P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) destinationDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;

    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Check null parameter */
        if ( NULL_PTR == destinationDataPtr )
        {
            u1_rtn = E_NOT_OK;
        }
        else
        {
            /* Check specified information range */
            u1_rtn = MemAcc_JobCtl_ChkInputAreaDt( addressAreaId, MEMACC_READ_JOB, sourceAddress, length );
        }
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    /* If the Parameter check is OK */
    if ( (Std_ReturnType)E_OK == u1_rtn )
    {
        /* Executes the acceptance determination process for the Read request */
        u1_rtn = MemAcc_JobCtl_Read( addressAreaId, sourceAddress, destinationDataPtr, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Read */

/****************************************************************************/
/* Function Name | MemAcc_Write                                             */
/* Description   | This function accepts a Write request for the Job        */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId       address area ID                      */
/*               | targetAddress       target address for write             */
/*               | sourceDataPtr       pointer to store the source data     */
/*               | length              data length                          */
/* Return Value  | E_OK                The requested job was accepted       */
/*               | E_NOT_OK            The requested job was not accepted   */
/* Notes         | Returns E_NOT_OK if initialization has not been performed*/
/*               | Returns E_NOT_OK if an AreaID out of range is specified  */
/*               | Returns E_NOT_OK if out of bounds from the specified     */
/*               | Address, Length                                          */
/*               | Returns E_NOT_OK if given a locked region                */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Write(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Check null parameter */
        if ( NULL_PTR == sourceDataPtr )
        {
            u1_rtn = E_NOT_OK;
        }
        else
        {
            /* Check specified information range */
            u1_rtn = MemAcc_JobCtl_ChkInputAreaDt( addressAreaId, MEMACC_WRITE_JOB, targetAddress, length );
        }
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    /* If the Parameter check is OK */
    if ( (Std_ReturnType)E_OK == u1_rtn )
    {
        /* Executes the acceptance determination process for the Write request */
        u1_rtn = MemAcc_JobCtl_Write( addressAreaId, targetAddress, sourceDataPtr, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Write */

/****************************************************************************/
/* Function Name | MemAcc_Erase                                             */
/* Description   | This function accepts a Erase request for the Job        */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | targetAddress                 target address for erase   */
/*               | length                        erase length               */
/* Return Value  | E_OK                          The requested job          */
/*               |                               was accepted               */
/*               | E_NOT_OK                      The requested job          */
/*               |                               was not accepted           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Erase(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Check specified information range */
        u1_rtn = MemAcc_JobCtl_ChkInputAreaDt( addressAreaId, MEMACC_ERASE_JOB, targetAddress, length );
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    /* If the Parameter check is OK */
    if ( (Std_ReturnType)E_OK == u1_rtn )
    {
        /* Executes the acceptance determination process for the Erase request */
        u1_rtn = MemAcc_JobCtl_Erase( addressAreaId, targetAddress, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Erase */

/****************************************************************************/
/* Function Name | MemAcc_Compare                                           */
/* Description   | This function accepts a Compare request for the Job      */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | sourceAddress                 compare address            */
/*               | dataPtr                       pointer to user data       */
/*               | length                        compare length             */
/* Return Value  | E_OK                          The requested job          */
/*               |                               was accepted               */
/*               | E_NOT_OK                      The requested job          */
/*               |                               was not accepted           */
/*               | E_MEM_SERVICE_NOT_AVAIL       not available              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Compare(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType sourceAddress,
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) dataPtr,
    MemAcc_LengthType length
)
{
    return ( E_MEM_SERVICE_NOT_AVAIL );

} /* MemAcc_Compare */

#ifdef MEMACC_DEVICE_CYT2Bx
/****************************************************************************/
/* Function Name | MemAcc_BlankCheck                                        */
/* Description   | This function accepts a BlankCheck request for the Job   */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | targetAddress                 blank check address        */
/*               | length                        blank check size           */
/* Return Value  | E_OK                          The requested job          */
/*               |                               was accepted               */
/*               | E_NOT_OK                      The requested job          */
/*               |                               was not accepted           */
/*               | E_MEM_SERVICE_NOT_AVAIL       not available              */
/* Notes         | On TraveoII, returns E_MEM_SERVICE_NOT_AVAIL             */
/*               | as a fixed value                                         */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_BlankCheck(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{

    return ( E_MEM_SERVICE_NOT_AVAIL );

} /* MemAcc_BlankCheck */
#else /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_BlankCheck                                        */
/* Description   | This function accepts a BlankCheck request for the Job   */
/*               | specified by AreaID.                                     */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | targetAddress                 blank check address        */
/*               | length                        blank check size           */
/* Return Value  | E_OK                          The requested job          */
/*               |                               was accepted               */
/*               | E_NOT_OK                      The requested job          */
/*               |                               was not accepted           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_BlankCheck(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Check specified information range */
        u1_rtn = MemAcc_JobCtl_ChkInputAreaDt( addressAreaId, MEMACC_BLANKCHECK_JOB, targetAddress, length );
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    /* If the Parameter check is OK */
    if ( (Std_ReturnType)E_OK == u1_rtn )
    {
        /* Executes the acceptance determination process for the BlankCheck request */
        u1_rtn = MemAcc_JobCtl_BlankCheck( addressAreaId, targetAddress, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_BlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_HwSpecificService                                 */
/* Description   | This function accepts a HwSpecificService request        */
/*               | for the Job specified by AreaID.                         */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId                 address area ID            */
/*               | hwId                          memory driver identifier   */
/*               | hwServiceId                   hardware specific service  */
/*               |                               request identifier         */
/*               | dataPtr                       pointer for job buffer     */
/*               | lengthPtr                     pointer for length         */
/* Return Value  | E_OK                          The requested job          */
/*               |                               was accepted               */
/*               | E_NOT_OK                      The requested job          */
/*               |                               was not accepted           */
/*               | E_MEM_SERVICE_NOT_AVAIL       not available              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_HwSpecificService(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_HwIdType hwId,
    MemAcc_MemHwServiceIdType hwServiceId,
    P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) dataPtr,
    P2VAR(MemAcc_LengthType, AUTOMATIC, TYPEDEF) lengthPtr
)
{
    Std_ReturnType u1_rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Hardware-specific service ID is other than "memory valid plane switch request ID." */
        if( MEMACC_SRV_ID_SWITCHVALIDAREA != hwServiceId )
        {
            u1_rtn = E_MEM_SERVICE_NOT_AVAIL;
        }
        else
        {
            /* Job buffer storage pointer NULL check */
            if( ( NULL_PTR == dataPtr ) || ( NULL_PTR == lengthPtr ) )
            {
                u1_rtn = E_NOT_OK;
            }
            else
            {
                /* HwID only supports Code Flash */
                if( MEMACC_HWID_CODEFLASH == hwId )
                {
                    /* Executes the acceptance determination process for the HwSpecificService request */
                    u1_rtn = MemAcc_JobCtl_HwSpecificService( addressAreaId, hwId, hwServiceId, dataPtr, lengthPtr );
                }
                /* HwID is not Code Flash */
                else
                {
                    u1_rtn = E_NOT_OK;
                }
            }
        }
    }
    else
    {
        u1_rtn = E_NOT_OK;
    }
    
    return ( u1_rtn );
    
} /* MemAcc_HwSpecificService */

/****************************************************************************/
/* Function Name | MemAcc_RequestLock                                       */
/* Description   | This function accepts lock request for the memory area   */
/*               | specified by AreaID, Address, and Lengt.                 */
/* Preconditions | None                                                     */
/* Parameters    | addressAreaId              address area ID               */
/*               | address                    target address                */
/*               | length                     target length                 */
/*               | lockNotificationFctPtr     Notification function pointer */
/*               |                            to call upon lock completion  */
/* Return Value  | E_OK                       The requested job             */
/*               |                            was accepted                  */
/*               | E_NOT_OK                   The requested job             */
/*               |                            was not accepted              */
/* Notes         | Returns E_NOT_OK if initialization has not been          */
/*               | performed.                                               */
/*               | Since it is designed to perform lock control             */
/*               | for Data Flash and Code Flash,                           */
/*               | Address and Length used for parameters are not used.     */
/*               | Returns E_NOT_OK if given an AreaID out of range.        */
/*               | Returns E_NOT_OK if the specified region is              */
/*               | already locked.                                          */
/*               | Returns E_NOT_OK if the given function pointer is NULL.  */
/*               | The lock is not released until MemAcc_ReleaseLock()      */
/*               | is called.                                               */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_RequestLock(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType address,
    MemAcc_LengthType length,
    MemAcc_LockNotificationType lockNotificationFctPtr
)
{
    Std_ReturnType u1_Rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Job buffer storage pointer NULL check */
        if( NULL_PTR == lockNotificationFctPtr )
        {
            u1_Rtn = E_NOT_OK;
        }
        else
        {
            /* Register the Lock Request */
            u1_Rtn = MemAcc_SemCtl_RequestLock( addressAreaId, address, length, lockNotificationFctPtr );
        }
    }
    else
    {
        u1_Rtn = E_NOT_OK;
    }
    
    /* Return the result of the request */
    return ( u1_Rtn );

} /* MemAcc_RequestLock */

/****************************************************************************/
/* Function Name | MemAcc_ReleaseLock                                       */
/* Description   | This function accepts unlock request for the memory area */
/*               | specified by AreaID, Address, and Length.                */
/* Parameters    | addressAreaId           address area ID                  */
/*               | address                 target address                   */
/*               | length                  target length                    */
/* Return Value  | E_OK                    The requested                    */
/*               |                         job was accepted                 */
/*               | E_NOT_OK                The requested job                */
/*               |                         was not accepted                 */
/* Notes         | Returns E_NOT_OK if initialization has                   */
/*               | not been performed.                                      */
/*               | Since it is designed to perform lock control             */
/*               | for Data Flash and Code Flash,                           */
/*               | Address and Length used for parameters are not used.     */
/*               | Returns E_NOT_OK if given an AreaID out of range.        */
/*               | Returns E_OK if the specified AreaID is unlocked         */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_ReleaseLock(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_AddressType address,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_Rtn;
    uint16  u2_AdressAreaMax = MemAcc_AddressArea_Max;
    
    /* Check address area range */
    if( addressAreaId < u2_AdressAreaMax )
    {
        /* Register the Unlock RequestUnLock */
        u1_Rtn = MemAcc_SemCtl_ReleaseLock( addressAreaId, address, length );
    }
    else
    {
        u1_Rtn = E_NOT_OK;
    }
    
    /* Return the result of the request */
    return ( u1_Rtn );

} /* MemAcc_ReleaseLock */

/****************************************************************************/
/* Function Name | MemAcc_MainFunction                                      */
/* Description   | Periodic function to perform MemAcc processing           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_CODE ) 
MemAcc_MainFunction( void )
{
    Std_ReturnType u1_initStatus;
    uint8 u1_ramGarbled;
    Std_ReturnType u1_funcRet;

    /* Check initialization execution status */
    u1_initStatus = MemAcc_Pif_InitCheckHook();
    if ( (Std_ReturnType)E_OK == u1_initStatus )
    {
        u1_ramGarbled = MemAcc_JobCtl_GetRAMGarbled();
        u1_funcRet = MemAcc_JobCtl_CheckRAM();
        if( ((uint8)STD_OFF == u1_ramGarbled) && ((Std_ReturnType)E_OK == u1_funcRet) )
        {
            MemAcc_Api_Execute();
        }
        else
        {
            MemAcc_Api_AbortJob();
        }

        MemAcc_SemCtl_Execute();
        MemAcc_JobCtl_SetRAMSubAll();
    }
    
} /* MemAcc_MainFunction */


#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
