/* Fee_Os_Connector.h v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/OS/CONNECTOR/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_OS_CONNECTOR_H
#define FEE_OS_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Fee.h>
#include "../inc/Fee_Mpu_Const.h"

#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
#include <Os.h>
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#if ( FEE_FORCE_TRUSTED == STD_OFF )
/* [Manual configuration] Add the necessary description for the user below. */
typedef ApplicationType                 Fee_ApplicationType;
typedef TrustedFunctionIndexType        Fee_TrustedFunctionIndexType;
typedef TrustedFunctionParameterRefType Fee_TrustedFunctionParameterRefType;
/* [Manual configuration] Add the necessary description for the user above. */
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF ) 
FUNC( Fee_ApplicationType, FEE_PROXY_CODE ) 
Fee_Os_GetApplicationID( void );
#endif /* FEE_FORCE_TRUSTED == STD_OFF */ 

#if ( FEE_FORCE_TRUSTED == STD_OFF )
FUNC( Std_ReturnType, FEE_PROXY_CODE )
Fee_Os_CallTrustedFunction(
      Fee_TrustedFunctionIndexType FunctionIndex, 
      Fee_TrustedFunctionParameterRefType FunctionParams
);
#endif /* FEE_FORCE_TRUSTED == STD_OFF */ 

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_PROXY_START_SEC_CONST_CONFIG
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallErase;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallWrite;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCancel;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallGetStatus;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallGetJobResult;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallMainFunction;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddRead;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddBlankCheck;
extern CONST( AB_83_ConstV Fee_TrustedFunctionIndexType, FEE_PROXY_CONFIG_DATA ) Fee_FlsWrp_FuncIdxCallCddNotBlankAddress;
#endif /* FEE_FORCE_TRUSTED == STD_OFF */

#define FEE_PROXY_STOP_SEC_CONST_CONFIG
#include <Fee_MemMap.h>

#endif /* FEE_OS_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
