/* Fee_Pif_Internal.h v1-1-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PIF/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_PIF_INTERNAL_H
#define FEE_PIF_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_PIF_AREANO_INVALID          (0xFFU)
#define FEE_PIF_BLK_CFG_ACCESS_OFFSET   (2U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void,   FEE_CODE ) Fee_Pif_RamInit( void );

FUNC( void, FEE_CODE )
Fee_Pif_RejectRequestHook(
    uint8 ReqResult
);

FUNC( void, FEE_CODE ) Fee_Pif_WriteErrorResponseHook(
    uint8 JobResult
);

FUNC( void, FEE_CODE ) Fee_Pif_ReadErrorResponseHook(
    uint8 JobResult
);

FUNC( void, FEE_CODE ) Fee_Pif_RebuildErrorResponseHook(
    uint8 JobResult
);

FUNC( uint16, FEE_CODE )
Fee_Pif_GetFeeBlockIdFromBlockNumber(
    uint16 SrcBlockNumber
);

FUNC( boolean, FEE_CODE )
Fee_Pif_IsIntentionalRebuildBlockNumber(
    uint8 AreaNo,
    uint16 BlockNumber
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

extern VAR  ( MemIf_JobResultType, FEE_VAR_NO_INIT )          Fee_RequestResult;

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

extern CONST( AB_83_ConstV Std_VersionInfoType, FEE_CONST )   Fee_Pif_VersionInfo;

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

#endif /* FEE_PIF_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
