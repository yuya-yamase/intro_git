/* Fee_Lib_Internal.h v1-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LIB/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_LIB_INTERNAL_H
#define FEE_LIB_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_NEXT_AREANUM_OFFSET     (1U)    /* 次エリア番号を示すオフセット */

#define FEE_START_AREANUM           (0U)    /* 開始エリア番号 */

#define FEE_LIB_RESIDUAL_VAL_CALC_MULTIPLES_REC  ( 0U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC(uint32, FEE_CODE) Fee_ChkLastWritePos( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosRedundancyData(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo1,
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo2
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosBlock(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, TYPEDEF         ) CPUDTFInfo
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosLastRecAddr(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, TYPEDEF         ) CPUDTFInfo
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_LIB_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
