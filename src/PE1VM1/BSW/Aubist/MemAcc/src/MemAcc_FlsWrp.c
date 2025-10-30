/* MemAcc_FlsWrp.c v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include "../inc/MemAcc_Mpu_Const.h"
#include "../inc/MemAcc_FlsWrp.h"
#include <Fls.h>

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
/* Function Name | MemAcc_FlsWrp_Init                                       */
/* Description   | This function calls the Fls Driver initialization API.   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_Init( void )
{
    /* Call the Fls Driver initialization API */
    Fls_Init( NULL_PTR );

} /* MemAcc_FlsWrp_Init */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_Erase                                      */
/* Description   | This function calls the Fls Driver Erase API.            */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress            target physical address         */
/*               | length                   erase size                      */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_Erase(
    MemAcc_AddressType targetAddress,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Fls Driver Erase API */
    u1_rtn = Fls_Erase( (Fls_AddressType)targetAddress, (Fls_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_FlsWrp_Erase */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_Write                                      */
/* Description   | This function calls the Fls Driver Write API.None        */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress            target physical address         */
/*               | sourceDataPtr            source pointer for write data   */
/*               | length                   write data size                 */
/* Return Value  | E_OK                     Request Accepted Successfully   */
/*               | E_NOT_OK                 Request Acceptance Failed       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_Write(
    MemAcc_AddressType targetAddress,
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr,
    MemAcc_LengthType length
)
{
    Std_ReturnType u1_rtn;
    
    /* Call the Fls Driver Write API */
    u1_rtn = Fls_Write( (Fls_AddressType)targetAddress, (const uint8 *)sourceDataPtr, (Fls_LengthType)length );
    
    return ( u1_rtn );

} /* MemAcc_FlsWrp_Write */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_Cancel                                     */
/* Description   | This function calls the Fls Driver Cancel API.           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_Cancel( void )
{
    /* Call the Fls Driver Cancel API. */
    Fls_Cancel();

} /* MemAcc_FlsWrp_Cancel */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_GetJobResult                               */
/* Description   | This function obtains the execution result of Fls Driver.*/
/* Preconditions | None                                                     */
/* Parameters    | pt_getResult      pointer to sore the execution result   */
/* Return Value  | E_OK              Result obtained successfully           */
/*               | E_NOT_OK          Result acquisition failed. Fls running */
/* Notes         | This function replaces the execution result from Fls with*/
/*               | the return value as follows:                             */
/*               | MEMIF_JOB_OK            ->MEMACC_MEM_OK                  */
/*               | MEMIF_JOB_FAILED        ->MEMACC_MEM_FAILED              */
/*               | MEMIF_JOB_PENDING       ->Notify E_NOT_OK on return value*/
/*               | MEMIF_JOB_CANCELED      ->MEMACC_MEM_CANCELED            */
/*               | MEMIF_BLOCK_INCONSISTENT->MEMACC_MEM_INCONSISTENT        */
/*               | MEMIF_BLOCK_INVALID     ->MEMACC_MEM_FAILED              */
/*               | MEMIF_JOB_FATALFAILED   ->MEMACC_MEM_FAILED              */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_GetJobResult(
    P2VAR(MemAcc_JobResultType, AUTOMATIC, TYPEDEF) pt_getResult
)
{
    Std_ReturnType u1_rtn;
    MemIf_JobResultType u1_fls_JobResult;
    
    u1_rtn = E_OK;
    
    /* Call the Fls Driver GetJobResult API. */
    u1_fls_JobResult = Fls_GetJobResult();
    
    /* Convert for MemAcc */
    switch ( u1_fls_JobResult )
    {
        case MEMIF_JOB_OK:                                            /* Job OK */
            /* Convert to MEMACC_MEM_OK */
            *(pt_getResult) = MEMACC_MEM_OK;
            break;
        case MEMIF_JOB_FAILED:                                        /* Unspecified error */
            /* Convert to MEMACC_MEM_FAILED */
            *(pt_getResult) = MEMACC_MEM_FAILED;
            break;
        case MEMIF_JOB_PENDING:                                       /* Processing */
            /* Set to E_NOT_OK by return value because Fls is in progress */
            u1_rtn = E_NOT_OK;
            break;
        case MEMIF_JOB_CANCELED:                                      /* Cancel */
            /* Convert to MEMACC_MEM_CANCELED */
            *(pt_getResult) = MEMACC_MEM_CANCELED;
            break;
        case MEMIF_BLOCK_INCONSISTENT:                                /* Expected value mismatch error */
            /* Convert to MEMACC_MEM_INCONSISTENT */
            *(pt_getResult) = MEMACC_MEM_INCONSISTENT;
            break;
        case MEMIF_BLOCK_INVALID:                                     /* Block Invalid error */
        case MEMIF_JOB_FATALFAILED:                                   /* Fatal Failed error */
            /* Convert to MEMACC_MEM_FAILED */
            *(pt_getResult) = MEMACC_MEM_FAILED;
            break;
        default:
            /* Convert to MEMACC_MEM_FAILED if unintended value obtained */
            *(pt_getResult) = MEMACC_MEM_FAILED;
            break;
    }
    
    return( u1_rtn );

} /* MemAcc_FlsWrp_GetJobResult */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_GetStatus                                  */
/* Description   | This function obtains the execution status of Fls Driver.*/
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | MEMACC_JOB_IDLE               Job not executed           */
/*               | MEMACC_JOB_PENDING            Job processing             */
/* Notes         | This function replaces the execution status from Fls     */
/*               | with the return value as follows:                        */
/*               |  MEMIF_IDLE              ->  MEMACC_JOB_IDLE             */
/*               |  MEMIF_BUSY              ->  MEMACC_JOB_PENDING          */
/*               |  Other than the above, PENDING                           */
/****************************************************************************/
FUNC( MemAcc_JobStatusType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_GetStatus( void )
{
    MemAcc_JobStatusType u1_rtn;
    MemIf_StatusType u1_fls_Status;
    
    /* Call the Fls Driver Getstatus API. */
    u1_fls_Status = Fls_GetStatus();
    
    if( MEMIF_IDLE == u1_fls_Status )
    {
        u1_rtn = MEMACC_JOB_IDLE;
    }
    else
    {
        u1_rtn = MEMACC_JOB_PENDING;
    }
    
    return( u1_rtn );

} /* MemAcc_FlsWrp_GetStatus */

#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_Cdd_Read - Synchronous function            */
/* Description   | This function calls the Fls Driver Synchronous Read API. */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress            target physical address         */
/*               | destinationDataPtr       destination pointer to          */
/*               |                          store ReadData                  */
/*               | length                   target data size                */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_Cdd_Read(
    Fls_AddressType targetAddress,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) destinationDataPtr,
    Fls_LengthType length
)
{
    Fls_Cdd_JobResultType u1_rtn;
    
    /* Call the Fls Driver Cdd_Read API */
    u1_rtn = Fls_Cdd_Read( targetAddress, destinationDataPtr, length );
    
    return ( u1_rtn );

} /* MemAcc_FlsWrp_Cdd_Read */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | BMemAcc_FlsWrp_BlankCheck - Synchronous function         */
/* Description   | This function calls the Fls Driver Synchronous           */
/*               | BlankCheck API.                                          */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress            target physical address         */
/*               | length                   target data size                */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_BlankCheck(
    Fls_AddressType targetAddress,
    Fls_LengthType length
)
{
    Fls_Cdd_JobResultType u1_rtn;
    
    /* Call the Fls Driver Cdd_BlankCheck API */
    u1_rtn = Fls_Cdd_BlankCheck( targetAddress, length );
    
    return ( u1_rtn );

} /* MemAcc_FlsWrp_BlankCheck */

#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_NotBlankCheck - Synchronous function       */
/* Description   | This function calls the Fls Driver Synchronous           */
/*               | NotBlankCheck API.                                       */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress            target physical address         */
/*               | length                   target data size                */
/*               | notBlankAddress          destination pointer             */
/*               |                          to store BlankAddress           */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_NotBlankCheck(
    Fls_AddressType targetAddress,
    Fls_LengthType length,
    P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) notBlankAddress
)
{
    Fls_Cdd_JobResultType u1_rtn;
    
    /* Call the Fls Driver Cdd_NotBlankAddress API */
    u1_rtn = Fls_Cdd_NotBlankAddress( targetAddress, length, notBlankAddress);
    
    return ( u1_rtn );

} /* MemAcc_FlsWrp_NotBlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_FlsWrp_MainFunction                               */
/* Description   | This function calls the Fls Driver Periodic process API. */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, MEMACC_PROXY_CODE ) 
MemAcc_FlsWrp_MainFunction( void )
{
    /* Call the Fls Driver MainFunction API */
    Fls_MainFunction();

} /* MemAcc_FlsWrp_MainFunction */

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
