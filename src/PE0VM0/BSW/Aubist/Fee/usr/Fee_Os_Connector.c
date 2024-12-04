/* Fee_Os_Connector.c v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/OS/CONNECTOR/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Fee.h>
#include "Fee_Os_Connector.h"
#include "../inc/Fee_FlsWrp.h"
#include "../inc/Fee_Mpu_Const.h"

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_PROXY_START_SEC_CONST_CONFIG
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallErase              = Fee_FlsWrp_CallErase;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallWrite              = Fee_FlsWrp_CallWrite;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCancel             = Fee_FlsWrp_CallCancel;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallGetStatus          = Fee_FlsWrp_CallGetStatus;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallGetJobResult       = Fee_FlsWrp_CallGetJobResult;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallMainFunction       = Fee_FlsWrp_CallMainFunction;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddRead            = Fee_FlsWrp_CallCddRead;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddBlankCheck      = Fee_FlsWrp_CallCddBlankCheck;
CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddNotBlankAddress = Fee_FlsWrp_CallCddNotBlankAddress;
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

#define FEE_PROXY_STOP_SEC_CONST_CONFIG
#include <Fee_MemMap.h>

#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_Os_GetApplicationID                                  */
/* Description   | Service to get Application ID from OS module             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Application ID                                           */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF ) 
FUNC( Fee_ApplicationType, FEE_PROXY_CODE ) 
Fee_Os_GetApplicationID( void )
{
    Fee_ApplicationType AppId;

    AppId = (Fee_ApplicationType)0U;

    /* [Manual configuration] Add the necessary description for the user below. */
    AppId = (Fee_ApplicationType)GetApplicationID();
    /* [Manual configuration] Add the necessary description for the user above. */

    return AppId;

}
#endif /* FEE_FORCE_TRUSTED == STD_OFF */ 

/****************************************************************************/
/* Function Name | Fee_Os_CallTrustedFunction                               */
/* Description   | Service to call CallTrustedFunction                      */
/* Preconditions | None                                                     */
/* Parameters    | FunctionIndex  : Identification of call function         */
/*               | FunctionParams : parameter                               */
/* Return Value  | Request result                                           */
/*               |  E_OK     : I accepted a call of demand.                 */
/*               |  E_NOT_OK : A handling ofdemand was not accepted.        */
/* Notes         |                                                          */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_Os_CallTrustedFunction(
      Fee_TrustedFunctionIndexType FunctionIndex,
      Fee_TrustedFunctionParameterRefType FunctionParams
){
    Std_ReturnType Ret = E_NOT_OK;

    /* [Manual configuration] Add the necessary description for the user below. */
    StatusType CFTFRtn;

    CFTFRtn = CallTrustedFunction( FunctionIndex, FunctionParams );
    if( CFTFRtn == (StatusType)E_OK )  /* If the return value is E_OS_SERVICEID, the callee function does not exist. */
    {
        Ret = E_OK;
    }
    /* [Manual configuration] Add the necessary description for the user above. */

    return Ret;
}
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_PROXY_START_SEC_CODE_TRUST
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallErase                             */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallErase(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallErase( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallWrite                             */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallWrite(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallWrite( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallCancel                            */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallCancel(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallCancel( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallGetStatus                         */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallGetStatus(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallGetStatus( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallGetJobResult                      */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallGetJobResult(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallGetJobResult( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallMainFunction                      */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallMainFunction(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallMainFunction( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallCddRead                           */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallCddRead(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallCddRead( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallCddBlankCheck                     */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallCddBlankCheck(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallCddBlankCheck( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/****************************************************************************/
/* Function Name | TRUSTED_Fee_FlsWrp_CallCddNotBlankAddress                */
/* Description   | This is a TrustedFunction and is called by only the OS   */
/*               | CallTrustedFunction.                                     */
/* Preconditions | None                                                     */
/* Parameters    | See the function CallTrustedFunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
FUNC( void, FEE_PROXY_CODE_TRUST )
TRUSTED_Fee_FlsWrp_CallCddNotBlankAddress(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
){
    Fee_FlsWrp_Trusted_CallCddNotBlankAddress( (Fee_TrustedFunctionIndexType)FunctionIndex, (Fee_TrustedFunctionParameterRefType)FunctionParams );

    return;
}
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

#define FEE_PROXY_STOP_SEC_CODE_TRUST
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
