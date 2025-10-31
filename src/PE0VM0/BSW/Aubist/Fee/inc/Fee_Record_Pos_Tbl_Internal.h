/* Fee_Record_Pos_Tbl_Internal.h v1-1-0                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/POS/TBL/INTERNAL/HEADER                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_RECORD_POS_TBL_INTERNAL_H
#define FEE_RECORD_POS_TBL_INTERNAL_H

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

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_MakePosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
);

FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetStatusArea(
    uint8 u1AreaNum
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_RecordPosTbl_GetTblIdx(
    uint8  AreaNo,
    uint16 BlockNumber,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) RecPosTblIdx
);

FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetMemoryU2(
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) ptu2Dst,
    uint16 u2Data,
    uint16 u2SetLen
);

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#if ( FEE_RECORDPOSTBL_ENABLE == STD_ON )

extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddress;
extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddressMrr;

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_RECORD_POS_TBL_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/10                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
