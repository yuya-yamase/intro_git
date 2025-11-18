/* MemAcc_FlsWrp.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemAcc FlsWrp HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_FLSWRP_H
#define MEMACC_FLSWRP_H

#include "MemAcc.h"
#include "MemAcc_Mpu_Const.h"
#include "Fls.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_PROXY_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_Init( void );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_Erase( MemAcc_AddressType targetAddress, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_Write( MemAcc_AddressType targetAddress, P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr, MemAcc_LengthType length );
FUNC( void, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_Cancel( void );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_GetJobResult( P2VAR(MemAcc_JobResultType, AUTOMATIC, TYPEDEF) pt_getResult );


FUNC( MemAcc_JobStatusType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_GetStatus( void );
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_Cdd_Read( Fls_AddressType targetAddress, P2VAR( uint8, AUTOMATIC, TYPEDEF ) destinationDataPtr, Fls_LengthType length );
#endif /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_BlankCheck( Fls_AddressType targetAddress, Fls_LengthType length );
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_NotBlankCheck( Fls_AddressType targetAddress, Fls_LengthType length, P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) notBlankAddress );
#endif /* MEMACC_DEVICE_CYT2Bx */
FUNC( void, MEMACC_PROXY_CODE ) MemAcc_FlsWrp_MainFunction( void );

#define MEMACC_PROXY_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* MEMACC_FLSWRP_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
