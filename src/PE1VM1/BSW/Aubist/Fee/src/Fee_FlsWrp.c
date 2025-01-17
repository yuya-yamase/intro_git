/* Fee_FlsWrp.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
#if ( FEE_FORCE_TRUSTED == STD_OFF )
#include <AbPartition.h>
#endif
#include <Fls.h>
#include <Fls_Cdd.h>
#include <Fee_Cbk.h>
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
#define FEE_PROXY_START_SEC_VAR_NO_INIT_SHARE
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
VAR( Fee_FlsWrp_DFlashAccessDataType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_Buffer;
VAR( Fls_AddressType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_NotBlankAddress;
VAR( Fee_FlsWrp_EraseParamType,              FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamErase;
VAR( Fee_FlsWrp_WriteParamType,              FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamWrite;
VAR( MemIf_StatusType,                       FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamGetStatus;
VAR( MemIf_JobResultType,                    FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamGetJobResult;
VAR( Fee_FlsWrp_CddReadParamType,            FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddRead;
VAR( Fee_FlsWrp_CddBlankCheckParamType,      FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddBlankCheck;
VAR( Fee_FlsWrp_CddNotBlankAddressParamType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddNotBlankAddress;
#endif

#define FEE_PROXY_STOP_SEC_VAR_NO_INIT_SHARE
#include <Fee_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Erase                                         */
/* Description   | Function to provide the functionality of Fls_Erase.      */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Erase(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
){
    Std_ReturnType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_Erase( TargetAddress, Length );
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = E_NOT_OK;
        Fee_FlsWrp_ParamErase.TargetAddress = TargetAddress;
        Fee_FlsWrp_ParamErase.Length = Length;
        Fee_FlsWrp_ParamErase.ReturnValue = E_NOT_OK;

        CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallErase, &Fee_FlsWrp_ParamErase );
        if( CFTFRtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_FlsWrp_ParamErase.ReturnValue;
        }
    }
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Write                                         */
/* Description   | Function to provide the functionality of Fls_Write.      */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Write(
    Fls_AddressType TargetAddress,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SourceAddressPtr,
    Fls_LengthType Length
){
    Std_ReturnType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_Write( TargetAddress, SourceAddressPtr, Length );
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = E_NOT_OK;
        if( Length <= (Fls_LengthType)FEE_DFAI_RW_SIZE_MAX )
        {
            Fee_Lib_CopyMemory( Fee_FlsWrp_Buffer.au1RecordData, SourceAddressPtr, Length );

            Fee_FlsWrp_ParamWrite.TargetAddress = TargetAddress;
            Fee_FlsWrp_ParamWrite.SourceAddressPtr = Fee_FlsWrp_Buffer.au1RecordData;
            Fee_FlsWrp_ParamWrite.Length = Length;
            Fee_FlsWrp_ParamWrite.ReturnValue = E_NOT_OK;

            CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallWrite, &Fee_FlsWrp_ParamWrite );
            if( CFTFRtn == (Std_ReturnType)E_OK )
            {
                Rtn = Fee_FlsWrp_ParamWrite.ReturnValue;
            }
        }
    }
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cancel                                        */
/* Description   | Function to provide the functionality of Fls_Cancel.     */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_Cancel( void )
{
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Fls_Cancel();
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        /* Return value is not checked. The trusted mode path does not check the results of the Fls_Cancel(). */
        (void)Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallCancel, NULL_PTR );
    }
#endif

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_GetStatus                                     */
/* Description   | Function to provide the functionality of Fls_GetStatus.  */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_StatusType, FEE_PROXY_CODE )
Fee_FlsWrp_GetStatus( void )
{
    MemIf_StatusType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_GetStatus();
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = MEMIF_UNINIT;
        Fee_FlsWrp_ParamGetStatus = MEMIF_UNINIT;

        CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallGetStatus, &Fee_FlsWrp_ParamGetStatus );
        if( CFTFRtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_FlsWrp_ParamGetStatus;
        }
    }
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_GetJobResult                                  */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_GetJobResult.                                        */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_GetJobResult( void )
{
    MemIf_JobResultType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_GetJobResult();
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = MEMIF_JOB_FAILED;
        Fee_FlsWrp_ParamGetJobResult = MEMIF_JOB_FAILED;

        CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallGetJobResult, &Fee_FlsWrp_ParamGetJobResult );
        if( CFTFRtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_FlsWrp_ParamGetJobResult;
        }
    }
#endif

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_MainFunction                                  */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_MainFunction.                                        */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_MainFunction( void )
{
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Fls_MainFunction();
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        /* Return value is not checked. The trusted mode path does not check the results of the Fls_MainFunction(). */
        (void)Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallMainFunction, NULL_PTR );
    }
#endif

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Cdd_Read                                      */
/* Description   | Function to provide the functionality of                 */
/*               | Fls_Cdd_Read.                                            */
/*               | This function hides the difference of callee modules     */
/*               | by the partitioning setting.                             */
/* Preconditions | None                                                     */
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_Read(
    Fls_AddressType SourceAddress,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) TargetAddressPtr,
    Fls_LengthType Length
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_Cdd_Read( SourceAddress, TargetAddressPtr, Length );
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = FLS_CDD_RSP_NG_INTERNAL;
        if( Length <= (Fls_LengthType)FEE_DFAI_RW_SIZE_MAX )
        {
            Fee_Lib_SetMemory( Fee_FlsWrp_Buffer.au1RecordData, (uint8)FEE_FLSWRP_BUFFER_DEFAULT_VALUE, Length );
            Fee_FlsWrp_ParamCddRead.SourceAddress = SourceAddress;
            Fee_FlsWrp_ParamCddRead.TargetAddressPtr = Fee_FlsWrp_Buffer.au1RecordData;
            Fee_FlsWrp_ParamCddRead.Length = Length;
            Fee_FlsWrp_ParamCddRead.ReturnValue = FLS_CDD_RSP_NG_INTERNAL;

            CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallCddRead, &Fee_FlsWrp_ParamCddRead );
            if( CFTFRtn == (Std_ReturnType)E_OK )
            {
                Rtn = Fee_FlsWrp_ParamCddRead.ReturnValue;
                if( Rtn == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK )
                {
                    Fee_Lib_CopyMemory( TargetAddressPtr, Fee_FlsWrp_Buffer.au1RecordData, Length );
                }
            }
        }
    }
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
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_BlankCheck(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    Std_ReturnType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_Cdd_BlankCheck( TargetAddress, Length );
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = FLS_CDD_RSP_NG_INTERNAL;
        Fee_FlsWrp_ParamCddBlankCheck.TargetAddress = TargetAddress;
        Fee_FlsWrp_ParamCddBlankCheck.Length = Length;
        Fee_FlsWrp_ParamCddBlankCheck.ReturnValue = FLS_CDD_RSP_NG_INTERNAL;

        CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallCddBlankCheck, &Fee_FlsWrp_ParamCddBlankCheck );
        if( CFTFRtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_FlsWrp_ParamCddBlankCheck.ReturnValue;
        }
    }
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
/* Parameters    | See the function of Fls.                                 */
/* Return Value  | See the function of Fls.                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_NotBlankAddress(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length,
    P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) NotBlankAddress
){
    Fls_Cdd_JobResultType Rtn;
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    boolean IsPartitionTrusted;
    StatusType CFTFRtn;
#endif

#if ( FEE_FORCE_TRUSTED == STD_OFF )
    IsPartitionTrusted = Fee_FlsWrp_IsTrusted();
    if( IsPartitionTrusted == (boolean)TRUE )
    {
#endif
        Rtn = Fls_Cdd_NotBlankAddress( TargetAddress, Length, NotBlankAddress );
#if ( FEE_FORCE_TRUSTED == STD_OFF )
    }
    else /* IsPartitionTrusted == FALSE */
    {
        Rtn = FLS_CDD_RSP_NG_INTERNAL;
        Fee_FlsWrp_NotBlankAddress = FEE_FLSWRP_NOT_BLANK_ADDRESS_DEFAULT_VALUE;

        Fee_FlsWrp_ParamCddNotBlankAddress.TargetAddress = TargetAddress;
        Fee_FlsWrp_ParamCddNotBlankAddress.Length = Length;
        Fee_FlsWrp_ParamCddNotBlankAddress.NotBlankAddress = &Fee_FlsWrp_NotBlankAddress;
        Fee_FlsWrp_ParamCddNotBlankAddress.ReturnValue = FLS_CDD_RSP_NG_INTERNAL;

        CFTFRtn = Fee_Os_CallTrustedFunction( Fee_FlsWrp_FuncIdxCallCddNotBlankAddress, &Fee_FlsWrp_ParamCddNotBlankAddress );
        if( CFTFRtn == (Std_ReturnType)E_OK )
        {
            *NotBlankAddress = Fee_FlsWrp_NotBlankAddress;
            Rtn = Fee_FlsWrp_ParamCddNotBlankAddress.ReturnValue;
        }
    }
#endif

    return Rtn;
}

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_PROXY_START_SEC_CODE_TRUST
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF ) 
/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallErase                             */
/* Description   | Function to call Fls_Erase.                              */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallErase(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( Fee_FlsWrp_EraseParamType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (Fee_FlsWrp_EraseParamType *)FunctionParams;

    Params->ReturnValue = Fls_Erase( Params->TargetAddress, Params->Length );

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallWrite                             */
/* Description   | Function to call Fls_Write.                              */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallWrite(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( Fee_FlsWrp_WriteParamType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (Fee_FlsWrp_WriteParamType *)FunctionParams;

    Params->ReturnValue = Fls_Write( Params->TargetAddress, Params->SourceAddressPtr, Params->Length );

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallCancel                            */
/* Description   | Function to call Fls_Cancel.                             */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCancel(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    Fls_Cancel();

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallGetStatus                         */
/* Description   | Function to call Fls_GetStatus.                          */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallGetStatus(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( MemIf_StatusType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (MemIf_StatusType *)FunctionParams;

    *Params = Fls_GetStatus();

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallGetJobResult                      */
/* Description   | Function to call Fls_GetJobResult.                       */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallGetJobResult(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( MemIf_JobResultType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (MemIf_JobResultType *)FunctionParams;

    *Params = Fls_GetJobResult();

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallMainFunction                      */
/* Description   | Function to call Fls_MainFunction.                       */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallMainFunction(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    Fls_MainFunction();

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallCddRead                           */
/* Description   | Function to call Fls_Cdd_Read.                           */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddRead(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( Fee_FlsWrp_CddReadParamType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (Fee_FlsWrp_CddReadParamType *)FunctionParams;

    Params->ReturnValue = Fls_Cdd_Read( Params->SourceAddress, Params->TargetAddressPtr, Params->Length );

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallCddBlankCheck                     */
/* Description   | Function to call Fls_Cdd_BlankCheck.                     */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddBlankCheck(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( Fee_FlsWrp_CddBlankCheckParamType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (Fee_FlsWrp_CddBlankCheckParamType *)FunctionParams;

    Params->ReturnValue = Fls_Cdd_BlankCheck( Params->TargetAddress, Params->Length );

    return;
}

/****************************************************************************/
/* Function Name | Fee_FlsWrp_Trusted_CallCddNotBlankAddress                */
/* Description   | Function to call Fls_Cdd_NotBlankAddress.                */
/*               | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddNotBlankAddress(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
){
    P2VAR( Fee_FlsWrp_CddNotBlankAddressParamType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) Params;
    Params = (Fee_FlsWrp_CddNotBlankAddressParamType *)FunctionParams;

    Params->ReturnValue = Fls_Cdd_NotBlankAddress( Params->TargetAddress, Params->Length, Params->NotBlankAddress );

    return;
}
#endif /* FEE_FORCE_TRUSTED == STD_OFF */ 

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
#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
/****************************************************************************/
/* Function Name | Fee_FlsWrp_IsTrusted                                     */
/* Description   | Function to return whether or not this unit is trusted.  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Whether this unit is trusted.                            */
/*               | Trusted=true means this unit has a supervisory authority.*/
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, FEE_PROXY_CODE )
Fee_FlsWrp_IsTrusted( void )
{
    boolean Rtn = TRUE;
    uint8 Counter;
    uint8 AppNum;
    Fee_ApplicationType AppId;

    AppId = Fee_Os_GetApplicationID();
    AppNum = (uint8)AbPT_u1OsApplicationNum;
    for( Counter = 0U; Counter < AppNum; Counter++ )
    {
        if( AbPT_stOsApplicationInfoList[Counter].u4OsapId == (uint32)AppId )
        {
            Rtn = AbPT_stOsApplicationInfoList[Counter].bIsTrusted;
            break;
        }
    }

    return Rtn;
}
#endif

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2023/01/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
