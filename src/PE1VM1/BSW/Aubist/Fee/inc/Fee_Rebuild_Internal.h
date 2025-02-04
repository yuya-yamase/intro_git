/* Fee_Rebuild_Internal.h v1-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/REBUILD/INTERNAL/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_REBUILD_INTERNAL_H
#define FEE_REBUILD_INTERNAL_H

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

/* データ転送状態管理(アイドル) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoIdle( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* データ転送状態管理(転送元最終データ位置検索中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingWriteLastPos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* データ転送状態管理(転送元データ検索準備中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* データ転送状態管理(転送元データ検索中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* データ転送状態管理(転送先データ検索準備中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* データ転送状態管理(転送先データ検索中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* データ転送状態管理(データ書き込み中) */
FUNC(uint32, FEE_CODE) Fee_MoveData_DoMovingRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitSuccess(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitFailure(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_REBUILD_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
