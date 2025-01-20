/* Fee_FlsWrp_Internal.h v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FLSWRP/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_FLSWRP_INTERNAL_H
#define FEE_FLSWRP_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fls.h>
#include <Fls_Cdd.h>
#include "Fee_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
#define FEE_FLSWRP_BUFFER_DEFAULT_VALUE (0x00U)
#define FEE_FLSWRP_NOT_BLANK_ADDRESS_DEFAULT_VALUE (0x00000000U)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( FEE_FORCE_TRUSTED == STD_OFF )
typedef union{
    uint32 au4StrageForAlignment[FEE_DFAI_RW_SIZE_MAX/FEE_BYTE_NUM_04];
    uint8  au1RecordData[FEE_DFAI_RW_SIZE_MAX];
} Fee_FlsWrp_DFlashAccessDataType;

typedef struct{
    Fls_AddressType TargetAddress;
    Fls_LengthType Length;
    Std_ReturnType ReturnValue;
} Fee_FlsWrp_EraseParamType;

typedef struct{
    Fls_AddressType TargetAddress;
    P2CONST( uint8, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) SourceAddressPtr; /* The only data that can be passed is Fee_FlsWrp_Buffer. */
    Fls_LengthType Length;
    Std_ReturnType ReturnValue;
} Fee_FlsWrp_WriteParamType;

typedef struct{
    Fls_AddressType SourceAddress;
    P2VAR( uint8, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) TargetAddressPtr; /* The only data that can be passed is Fee_FlsWrp_Buffer. */
    Fls_LengthType Length;
    Fls_Cdd_JobResultType ReturnValue;
} Fee_FlsWrp_CddReadParamType;

typedef struct{
    Fls_AddressType TargetAddress;
    Fls_LengthType Length;
    Fls_Cdd_JobResultType ReturnValue;
} Fee_FlsWrp_CddBlankCheckParamType;

typedef struct{
    Fls_AddressType TargetAddress;
    Fls_LengthType Length;
    P2VAR( Fls_AddressType, AUTOMATIC, FEE_PROXY_VAR_NO_INIT_SHARE ) NotBlankAddress; /* The only data that can be passed is Fee_FlsWrp_NotBlankAddress. */
    Fls_Cdd_JobResultType ReturnValue;
} Fee_FlsWrp_CddNotBlankAddressParamType;
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_PROXY_START_SEC_CODE
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
FUNC( boolean, FEE_PROXY_CODE )
Fee_FlsWrp_IsTrusted( void );
#endif

#define FEE_PROXY_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_PROXY_START_SEC_VAR_NO_INIT_SHARE
#include <Fee_MemMap.h>

#if ( FEE_FORCE_TRUSTED == STD_OFF )
extern VAR( Fee_FlsWrp_DFlashAccessDataType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_Buffer;
extern VAR( Fls_AddressType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_NotBlankAddress;
extern VAR( Fee_FlsWrp_EraseParamType,              FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamErase;
extern VAR( Fee_FlsWrp_WriteParamType,              FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamWrite;
extern VAR( MemIf_StatusType,                       FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamGetStatus;
extern VAR( MemIf_JobResultType,                    FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamGetJobResult;
extern VAR( Fee_FlsWrp_CddReadParamType,            FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddRead;
extern VAR( Fee_FlsWrp_CddBlankCheckParamType,      FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddBlankCheck;
extern VAR( Fee_FlsWrp_CddNotBlankAddressParamType, FEE_PROXY_VAR_NO_INIT_SHARE ) Fee_FlsWrp_ParamCddNotBlankAddress;
#endif

#define FEE_PROXY_STOP_SEC_VAR_NO_INIT_SHARE
#include <Fee_MemMap.h>

#endif /* FEE_FLSWRP_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
