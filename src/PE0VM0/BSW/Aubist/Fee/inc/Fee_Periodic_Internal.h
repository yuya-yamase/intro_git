/* Fee_Periodic_Internal.h v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PERIODIC/INTERNAL/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_PERIODIC_INTERNAL_H
#define FEE_PERIODIC_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    FEE_PFNS_PERIODIC_FUNC_NUM              (4U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubCont(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubDone(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecUnderLayer(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo ,
    uint8 u1_callmode
);

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingCancel( uint8 u1_callmode );

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingAbort( uint8 u1_callmode );

FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecMngDfc(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo ,
    uint8 u1_callmode
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_PERIODIC_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/06/28                                              */
/*  2-0-0          :2024/07/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
