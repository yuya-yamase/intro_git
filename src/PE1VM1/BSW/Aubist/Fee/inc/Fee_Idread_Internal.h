/* Fee_Idread_Internal.h v1-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/IDREAD/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_IDREAD_INTERNAL_H
#define FEE_IDREAD_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* ID-specified data read status management (idle) */
FUNC(uint32, FEE_CODE) Fee_ReadMainSelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* ID-specified data read status management (searching for free space) */
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* ID-specified data read status management (preparing to read ID-specified data) */
FUNC(uint32, FEE_CODE) Fee_ReadMainPrepSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* ID-specified data reading status management (ID-specified data reading) */
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_IDREAD_INTERNAL_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
