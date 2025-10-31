/* Fee_FlsWrp.c v2-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FLSWRP/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Fee_Ext.h>
#include "../inc/Fee_Common.h"
#include "../inc/Fee_FlsWrp.h"
#include "../inc/Fee_FlsWrp_Internal.h"
#if ( FEE_USE_MEMACC == STD_ON )
#include <MemAcc.h>
#include <MemAcc_Cdd.h>
#include <MemAcc_Ext.h>
#include "../inc/Fee_Legacy.h"
#else
#include <Fls.h>
#include <Fls_Cdd.h>
#include <Fee_Cbk.h>
#endif
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Mpu_Const.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Erase                                         */
/* Description   | Function to provide the functionality of Erase.          */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Erase(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
){
    Std_ReturnType Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_Erase( MEMACC_ADDRAREA_0, (MemAcc_AddressType)TargetAddress, (MemAcc_LengthType)Length );
#else
    Rtn = Fls_Erase( TargetAddress, Length );
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Write                                         */
/* Description   | Function to provide the functionality of Write.          */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Write(
    Fls_AddressType TargetAddress,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SourceAddressPtr,
    Fls_LengthType Length
){
    Std_ReturnType Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_Write( MEMACC_ADDRAREA_0, (MemAcc_AddressType)TargetAddress, SourceAddressPtr, (MemAcc_LengthType)Length );
#else
    Rtn = Fls_Write( TargetAddress, SourceAddressPtr, Length );
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cancel                                        */
/* Description   | Function to provide the functionality of Cancel.         */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_Cancel( void )
{
#if ( FEE_USE_MEMACC == STD_ON )
    MemAcc_Cancel(MEMACC_ADDRAREA_0);
#else
    Fls_Cancel();
#endif

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_GetStatus                                     */
/* Description   | Function to provide the functionality of GetStatus.      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_StatusType, FEE_PROXY_CODE )
Fee_FlsWrp_GetStatus( void )
{
    MemIf_StatusType Rtn;

#if ( FEE_USE_MEMACC == STD_ON )
    MemAcc_JobStatusType MemAcc_JobStatus;

    MemAcc_JobStatus = MemAcc_GetJobStatus(MEMACC_ADDRAREA_0);
    if( MemAcc_JobStatus == MEMACC_JOB_IDLE )
    {
        Rtn = MEMIF_IDLE;
    }
    else if( MemAcc_JobStatus == MEMACC_JOB_PENDING )
    {
        Rtn = MEMIF_BUSY;
    }
    else
    {
        Rtn = MEMIF_BUSY_INTERNAL;
    }
#else
    Rtn = Fls_GetStatus();
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_GetJobResult                                  */
/* Description   | Function to provide the functionality of                 */
/*               | GetJobResult.                                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_GetJobResult( void )
{
    MemIf_JobResultType Rtn;

#if ( FEE_USE_MEMACC == STD_ON )
    MemAcc_JobResultType MemAcc_JobResult;
    MemAcc_JobStatusType MemAcc_JobStatus;

    MemAcc_JobResult = MemAcc_GetJobResult(MEMACC_ADDRAREA_0);
    MemAcc_JobStatus = MemAcc_GetJobStatus(MEMACC_ADDRAREA_0);
    if( MemAcc_JobStatus == MEMACC_JOB_PENDING)
    {
        Rtn = MEMIF_JOB_PENDING;
    }
    else if( ( MemAcc_JobResult == MEMACC_MEM_OK ) ||
             ( MemAcc_JobResult == MEMACC_MEM_ECC_CORRECTED ) )
    {
        Rtn = MEMIF_JOB_OK;
    }
    else if( MemAcc_JobResult == MEMACC_MEM_FAILED )
    {
        Rtn = MEMIF_JOB_FAILED;
    }
    else if( MemAcc_JobResult == MEMACC_MEM_INCONSISTENT )
    {
        Rtn = MEMIF_BLOCK_INCONSISTENT;
    }
    else if( MemAcc_JobResult == MEMACC_MEM_CANCELED )
    {
        Rtn = MEMIF_JOB_CANCELED;
    }
    else
    {
        Rtn = MEMIF_JOB_FAILED;
    }
#else
    Rtn = Fls_GetJobResult();
#endif
    
    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_MainFunction                                  */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_MainFunction.                                        */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_MainFunction( uint8 u1_callmode )
{
#if ( FEE_USE_MEMACC == STD_ON )
    if ( u1_callmode == (uint8)FEE_CALL_TIMING_NOT_PERIODIC )
    {
        MemAcc_MainFunction_ExtNonPeriodic();
    }
#else
    Fls_MainFunction();
#endif

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_ExtDfPreExecution                             */
/* Description   | Function to provide the functionality of                 */
/*               | Cdd_GetLockStatus(USE MEMACC).                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | See the function of MemAcc.                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType , FEE_PROXY_CODE )
Fee_FlsWrp_ExtDfPreExecution( void )
{
    Std_ReturnType Rtn;

#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_ExtDfPreExecution();
#else
    Rtn = E_OK;
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cdd_Read                                      */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_Cdd_Read.                                            */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_Read(
    Fls_AddressType SourceAddress,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) TargetAddressPtr,
    Fls_LengthType Length
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_Cdd_Read( SourceAddress, TargetAddressPtr, Length );
#else
    Rtn = Fls_Cdd_Read( SourceAddress, TargetAddressPtr, Length );
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cdd_BlankCheck                                */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_Cdd_BlankCheck.                                      */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_BlankCheck(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_Cdd_BlankCheck( TargetAddress, Length );
#else
    Rtn = Fls_Cdd_BlankCheck( TargetAddress, Length );
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cdd_NotBlankAddress                           */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_Cdd_NotBlankAddress.                                 */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls or MemAcc.                       */
/* Return Value  | See the function of Fls or MemAcc.                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_NotBlankAddress(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length,
    P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) NotBlankAddress
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    Rtn = MemAcc_Cdd_NotBlankCheck( TargetAddress, Length, NotBlankAddress );
#else
    Rtn = Fls_Cdd_NotBlankAddress( TargetAddress, Length, NotBlankAddress );
#endif

    return Rtn;
}


/****************************************************************************/
/* Function Name | Fee_FlsWrp_IsLockStatus                                  */
/* Description   | Function to provide the functionality of                 */
/*               | Cdd_GetLockStatus(USE MEMACC).                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  |  TRUE  : Lock State                                      */
/*               |  FALSE : UnLock State                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean , FEE_PROXY_CODE )
Fee_FlsWrp_IsLockStatus( void )
{
    boolean Rtn;
#if ( FEE_USE_MEMACC == STD_ON )
    uint8 u1_LockStatus;

    u1_LockStatus = MemAcc_Cdd_GetLockStatus();

    if ( u1_LockStatus != MEMACC_LOCKST_UNLOCK )
    {
        Rtn = (boolean)TRUE;   /* Lock State */
    } 
    else 
    {
        Rtn = (boolean)FALSE;  /* UnLock State */
    }
#else
    Rtn = (boolean)FALSE;
#endif

    return Rtn;
}

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_PROXY_START_SEC_CODE_TRUST
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_JobEndNotification                                   */
/* Description   | Function to notify the general layer of job end          */
/*               | and success.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST ) Fee_JobEndNotification(void)
{
    return;
}

/****************************************************************************/
/* Function Name | Fee_JobErrorNotification                                 */
/* Description   | Function to notify the general layer of job end          */
/*               | and failure.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST ) Fee_JobErrorNotification(void)
{
    return;
}

#define FEE_PROXY_STOP_SEC_CODE_TRUST
#include <Fee_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2023/01/27                                              */
/*  2-1-0          :2024/10/21                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
