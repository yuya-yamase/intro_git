/* Fee_FlsWrp.h v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FLSWRP/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_FLSWRP_H
#define FEE_FLSWRP_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fls.h>
#include <Fls_Cdd.h>
#include "../usr/Fee_Os_Connector.h"

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Erase(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
);

FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_FlsWrp_Write(
    Fls_AddressType TargetAddress,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SourceAddressPtr,
    Fls_LengthType Length
);

FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_Cancel( void );

FUNC( MemIf_StatusType, FEE_PROXY_CODE )
Fee_FlsWrp_GetStatus( void );

FUNC( MemIf_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_GetJobResult( void );

FUNC( void, FEE_PROXY_CODE )
Fee_FlsWrp_MainFunction( void );

FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_Read(
    Fls_AddressType SourceAddress,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) TargetAddressPtr,
    Fls_LengthType Length
);

FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_BlankCheck(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
);

FUNC( Fls_Cdd_JobResultType, FEE_PROXY_CODE )
Fee_FlsWrp_Cdd_NotBlankAddress(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length,
    P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) NotBlankAddress
);

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_PROXY_START_SEC_CODE_TRUST
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF ) 
FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallErase(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallWrite(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCancel(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallGetStatus(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallGetJobResult(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallMainFunction(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddRead(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddBlankCheck(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);

FUNC( void, FEE_PROXY_CODE_TRUST )
Fee_FlsWrp_Trusted_CallCddNotBlankAddress(
    Fee_TrustedFunctionIndexType FunctionIndex,
    Fee_TrustedFunctionParameterRefType FunctionParams
);
#endif /* FEE_FORCE_TRUSTED == STD_OFF */ 

#define FEE_PROXY_STOP_SEC_CODE_TRUST
#include <Fee_MemMap.h>

#endif /* FEE_FLSWRP_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
