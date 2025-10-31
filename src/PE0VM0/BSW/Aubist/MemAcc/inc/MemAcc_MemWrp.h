/* MemAcc_MemWrp.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemAcc MemWrp HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_MEMWRP_H
#define MEMACC_MEMWRP_H

#include "MemAcc.h"
#include "MemAcc_Mpu_Const.h"
#include "Mem.h"

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

FUNC( void, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Init( void );
FUNC( void, MEMACC_PROXY_CODE ) MemAcc_MemWrp_MainFunction( void );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_GetJobResult( Mem_InstanceIdType instanceId, P2VAR(MemAcc_JobResultType, AUTOMATIC, TYPEDEF) pt_getResult );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Read( Mem_InstanceIdType instanceId, MemAcc_AddressType sourceAddress, P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) destinationDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Write( Mem_InstanceIdType instanceId, MemAcc_AddressType targetAddress, P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Erase( Mem_InstanceIdType instanceId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_BlankCheck( Mem_InstanceIdType instanceId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
#endif  /* MEMACC_DEVICE_CYT2Bx */
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_HwSpecificService( Mem_InstanceIdType instanceId, MemAcc_MemHwServiceIdType hwServiceId, P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) dataPtr, P2VAR(MemAcc_LengthType, AUTOMATIC, TYPEDEF) lengthPtr );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Suspend( Mem_InstanceIdType instanceId );
FUNC( Std_ReturnType, MEMACC_PROXY_CODE ) MemAcc_MemWrp_Resume( Mem_InstanceIdType instanceId );

#define MEMACC_PROXY_STOP_SEC_CODE
#include <MemAcc_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* MEMACC_MEMWRP_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
