/* MemAcc_MemWrp.c v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include "../inc/MemAcc_Mpu_Const.h"
#include "../inc/MemAcc_MemWrp.h"
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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define MEMACC_PROXY_START_SEC_CODE
#include <MemAcc_MemMap.h>
/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Init                                       */
/* Description   | This function calls the Mem Driver initialization API.   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Init( void )
{
    /* Call the Mem Driver initialization API */
    Mem_Init( NULL_PTR );

} /* MemAcc_MemWrp_Init */

/****************************************************************************/
/* Function Name | MemAcc_MemWrp_MainFunction                               */
/* Description   | This function calls the Mem Driver Periodic process API. */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_MainFunction( void )
{
    /* Call the Mem Driver MainFunction API */
    Mem_MainFunction();

} /* MemAcc_MemWrp_MainFunction */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_GetJobResult                               */
/* Description   | This function obtains the execution result of Mem Driver.*/
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | pt_getResult             pointer to sore                 */
/*               |                          the execution result            */
/* Return Value  | E_OK                     Result obtained successfully    */
/*               | E_NOT_OK                 Result acquisition failed.      */
/*               |                          Mem running                     */
/* Notes         | This function replaces the execution result from Fls     */
/*               | with the return value as follows:                        */
/*               |  MEM_JOB_OK          ->  MEMACC_MEM_OK                   */
/*               |  MEM_JOB_PENDING     ->  Notify E_NOT_OK on return value */
/*               |  MEM_JOB_FAILED      ->  MEMACC_MEM_FAILED               */
/*               |  MEM_INCONSISTENT    ->  MEMACC_MEM_INCONSISTENT         */
/*               |  MEM_ECC_UNCORRECTED ->  MEMACC_MEM_ECC_UNCORRECTED      */
/*               |  MEM_ECC_CORRECTED   ->  MEMACC_MEM_ECC_CORRECTED        */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_GetJobResult(
    Mem_InstanceIdType instanceId,
    P2VAR(MemAcc_JobResultType, AUTOMATIC, TYPEDEF) pt_getResult
)
{
    Std_ReturnType u1_rtn;
    Mem_JobResultType u1_mem_JobResult;
    
    u1_rtn = E_OK;
    
    /* Call the Mem Driver GetJobResult API. */
    u1_mem_JobResult = Mem_GetJobResult(instanceId);
    
    /* Convert for MemAcc */
    switch ( u1_mem_JobResult )
    {
        case MEM_JOB_OK:                                            /* Job OK */
            /* Convert to MEMACC_MEM_OK */
            *(pt_getResult) = MEMACC_MEM_OK;
            break;
        case MEM_JOB_PENDING:                                       /* Processing */
            /* Set to E_NOT_OK by return value because Mem is in progress */
            u1_rtn = E_NOT_OK;
            break;
        case MEM_JOB_FAILED:                                        /* Unspecified error */
            /* Convert to MEMACC_MEM_FAILED */
            *(pt_getResult) = MEMACC_MEM_FAILED;
            break;
        case MEM_INCONSISTENT:                                      /* Expected value mismatch error */
            /* Convert to MEMACC_MEM_INCONSISTEN */
            *(pt_getResult) = MEMACC_MEM_INCONSISTENT;
            break;
        case MEM_ECC_UNCORRECTED:                                   /* Uncorrectable ECC error */
            /* Convert to MEMACC_MEM_ECC_UNCORRECTED */
            *(pt_getResult) = MEMACC_MEM_ECC_UNCORRECTED;
            break;
        case MEM_ECC_CORRECTED:                                     /* Correctable ECC error */
            /* Convert to MEMACC_MEM_ECC_CORRECTED */
            *(pt_getResult) = MEMACC_MEM_ECC_CORRECTED;
            break;
        default:
            /* Convert to MEMACC_MEM_FAILED if unintended value obtained */
            *(pt_getResult) = MEMACC_MEM_FAILED;
            break;
    }
    
    return( u1_rtn );

} /* MemAcc_MemWrp_GetJobResult */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Read                                       */
/* Description   | This function calls the Mem Driver Read API.             */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | sourceAddress            target Flash physical address   */
/*               | destinationDataPtr       destination pointer             */
/*               |                          to store ReadData               */
/*               | length                   target data size                */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/* Notes         | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/*               |  MEM_JOB_FAILED          ->  MEMACC_MEM_FAILED           */
/*               |  MEM_INCONSISTENT        ->  MEMACC_MEM_INCONSISTENT     */
/*               |  MEM_ECC_UNCORRECTED     ->  MEMACC_MEM_ECC_UNCORRECTED  */
/*               |  MEM_ECC_CORRECTED       ->  MEMACC_MEM_ECC_CORRECTED    */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Read(
    Mem_InstanceIdType instanceId,
    MemAcc_AddressType sourceAddress,
    P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) destinationDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver Read API */
    u1_rtn = Mem_Read( instanceId, (Mem_AddressType)sourceAddress, (Mem_DataType*)destinationDataPtr, (Mem_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_Read */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Write                                      */
/* Description   | This function calls the Mem Driver Write API.            */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | targetAddress            target physical address         */
/*               | sourceDataPtr            source pointer for write data   */
/*               | length                   write data size                 */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/* Notes         | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Write(
    Mem_InstanceIdType instanceId,
    MemAcc_AddressType targetAddress,
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver Write API */
    u1_rtn = Mem_Write( instanceId, (Mem_AddressType)targetAddress, (const Mem_DataType *)sourceDataPtr, (Mem_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_Write */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Erase                                      */
/* Description   | This function calls the Mem Driver Erase API.            */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | targetAddress            target physical address         */
/*               | length                   erase size                      */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/* Notes         | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Erase(
    Mem_InstanceIdType instanceId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver Erase API */
    u1_rtn = Mem_Erase( instanceId, (Mem_AddressType)targetAddress, (Mem_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_Erase */

#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_MemWrp_BlankCheck                                 */
/* Description   | This function calls the Mem Driver BlankCheck API.       */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | targetAddress            target physical address         */
/*               | length                   check size                      */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/*               | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_BlankCheck(
    Mem_InstanceIdType instanceId,
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver BlankCheck API */
    u1_rtn = Mem_BlankCheck( instanceId, (Mem_AddressType)targetAddress, (Mem_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_BlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_HwSpecificService                          */
/* Description   | This function calls the Mem Driver                       */
/*               | HwSpecificService API.                                   */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/*               | hwServiceId              HwServiceID                     */
/*               | dataPtr                  Data pointer                    */
/*               | lengthPtr                Length pointer                  */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/*               | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_HwSpecificService(
    Mem_InstanceIdType instanceId,
    MemAcc_MemHwServiceIdType hwServiceId,
    P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) dataPtr,
    P2VAR(MemAcc_LengthType, AUTOMATIC, TYPEDEF) lengthPtr
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver HwSpecificService API */
    u1_rtn = Mem_HwSpecificService( instanceId, (Mem_HwServiceIdType)hwServiceId, (Mem_DataType*)dataPtr, (Mem_LengthType*)lengthPtr );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_HwSpecificService */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Suspend                                    */
/* Description   | This function calls the Mem Driver Suspend API.          */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/*               | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/* Notes         | Returns E_OK if the return value is changed              */
/*               | to void to accommodate SWS.                              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Suspend(
    Mem_InstanceIdType instanceId
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver Suspend API */
    u1_rtn = Mem_Suspend( instanceId );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_Suspend */


/****************************************************************************/
/* Function Name | MemAcc_MemWrp_Resume                                     */
/* Description   | This function calls the Mem Driver Resume API.           */
/* Preconditions | None                                                     */
/* Parameters    | instanceId               instance ID                     */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/*               | E_MEM_SERVICE_NOT_AVAIL  Service not available           */
/* Notes         | Returns E_OK if the return value is changed to void      */
/*               | to accommodate SWS.                                      */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_MemWrp_Resume(
    Mem_InstanceIdType instanceId
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Mem Driver Resume API */
    u1_rtn = Mem_Resume( instanceId );
    
    return ( u1_rtn );

} /* MemAcc_MemWrp_Resume */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MEMACC_PROXY_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
