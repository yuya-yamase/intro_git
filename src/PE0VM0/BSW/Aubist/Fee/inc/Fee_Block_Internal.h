/* Fee_Block_Internal.h v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/BLOCK/INTERNAL/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_BLOCK_INTERNAL_H
#define FEE_BLOCK_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_FIX_BS_JUDGE_TBL_OFFSET     (1U)    /* Block status data fixed transition destination decision table offset */

#define FEE_FIX_BSTBLINDEX_SSTATUS      (0U)    /* Block status data fixed transition destination decision table substate storage destination index */
#define FEE_FIX_BSTBLINDEX_SSSTATUS     (1U)    /* Block status data fixed transition destination decision table subsubstate storage destination index */

#define FEE_TOP_BLOCK_IN_AREA           (0U)    /* First block in area */
#define FEE_SECOND_BLOCK_IN_AREA        (1U)    /* Next block in first block in area */
#define FEE_NEXT_BLOCKNUM_OFFSET        (1U)    /* Offset indicating next block number */
#define FEE_LAST_BLOCKNUM_OFFSET        (1U)    /* Offset when calculating last block number */

#define FEE_BSJUDGESTATUSKINDNUM        (5U)
#define FEE_BSJUDGESTATUSNUM            (2U)
#define FEE_BSDATARANGE                 (3U)
#define FEE_BSDATAPOSNUM                (3U)
#define FEE_BSDATAKINDNUM               (3U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* In-use block creation status management (erasing) */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoErasing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* In-use block creation status management (In use and set) */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoWritingUsing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* In-use block selection (0 effective blocks) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfZero( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, uint32 u4UnUsedCount,
                                       P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* In-use block selection (1 effective block) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfOne( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                      P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* In-use block selection (2 or more valid blocks) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfTwoAndMore( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                             P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* Block status combination judgment */
FUNC(uint32, FEE_CODE) Fee_JudgeBlockStatusCombination(uint8 u1MainBlockStatus, uint8 u1SubBlockStatus, uint8 u1BlockNum, P2VAR(boolean, AUTOMATIC, TYPEDEF) u1Swap);
/* Valid block count */
FUNC(void, FEE_CODE) Fee_CountValidBlock( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlock,
                                 P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4UnUsedNum );

/* Block status data pending status management */
FUNC(uint32, FEE_CODE) Fee_FixBlockStatus( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* In-use block creation status management */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* In-transit block creation status management */
FUNC(uint32, FEE_CODE) Fee_MakeMoveBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* State Management Setting Reorg Termination */
FUNC(uint32, FEE_CODE) Fee_SetMoveEnd( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Area Disabled/Used Setting State Management */
FUNC(uint32, FEE_CODE) Fee_SetInvalidArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Used and fault setting status management */
FUNC(uint32, FEE_CODE) Fee_SetFailBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Full block status judgment */
FUNC(uint32, FEE_CODE) Fee_JudgeAllBS( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Full block status judgment for reading */
FUNC( void, FEE_CODE )
Fee_JudgeAllBSRead(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
);

/* Block status determination */
FUNC(uint32, FEE_CODE) Fee_JudgeBS( P2VAR(Fee_UseBlockType, AUTOMATIC, TYPEDEF) ptstUseBlock );

/* Block status judgment for reading */
FUNC( uint32, FEE_CODE )
Fee_JudgeBSForRead(
    P2VAR( Fee_UseBlockType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstUseBlock
);

FUNC(uint32, FEE_CODE) Fee_JudgeBSData(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4FixKind,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) ptu1WritePlace
);

/* Read Block Status Data */
FUNC(uint32, FEE_CODE) Fee_ReadBSData( uint8 u1BlockNo, uint32 u4BSDataKind, uint32 u4DuplicateDataKind );

/* Block in use selection */
FUNC(uint32, FEE_CODE) Fee_SelectUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC(void, FEE_CODE) Fee_SetBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_FixBSJudgeTBL[FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSNUM];
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSTBL[FEE_BSDATARANGE][FEE_BSDATAPOSNUM][FEE_BSDATAKINDNUM];
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_A[FEE_BSDATARANGE][FEE_BSDATARANGE];
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_C[FEE_BSDATARANGE][FEE_BSDATARANGE];
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_B[FEE_BSDATARANGE][FEE_BSDATARANGE];

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_BLOCK_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2021/05/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
