/* Fee_Block_Internal.h v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
#define FEE_FIX_BS_JUDGE_TBL_OFFSET     (1U)    /* ブロックステータスデータ確定遷移先判定テーブル オフセット */

#define FEE_FIX_BSTBLINDEX_SSTATUS      (0U)    /* ブロックステータスデータ確定遷移先判定テーブル サブ状態格納先インデックス */
#define FEE_FIX_BSTBLINDEX_SSSTATUS     (1U)    /* ブロックステータスデータ確定遷移先判定テーブル サブサブ状態格納先インデックス */

#define FEE_TOP_BLOCK_IN_AREA           (0U)    /* エリア内の先頭ブロック */
#define FEE_SECOND_BLOCK_IN_AREA        (1U)    /* エリア内の先頭ブロックの次ブロック */
#define FEE_NEXT_BLOCKNUM_OFFSET        (1U)    /* 次ブロック番号を示すオフセット */
#define FEE_LAST_BLOCKNUM_OFFSET        (1U)    /* 最終ブロック番号算出時のオフセット */

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

/* 使用中ブロック作成中状態管理(消去中) */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoErasing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* 使用中ブロック作成中状態管理(使用中設定中) */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoWritingUsing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* 使用中ブロック選択(有効ブロック数０) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfZero( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, uint32 u4UnUsedCount,
                                       P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* 使用中ブロック選択(有効ブロック数１) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfOne( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                      P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* 使用中ブロック選択(有効ブロック数２以上) */
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfTwoAndMore( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                             P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum );
/* ブロックステータス組み合わせ判定 */
FUNC(uint32, FEE_CODE) Fee_JudgeBlockStatusCombination(uint8 u1MainBlockStatus, uint8 u1SubBlockStatus, uint8 u1BlockNum, P2VAR(boolean, AUTOMATIC, TYPEDEF) u1Swap);
/* 有効ブロック数カウント */
FUNC(void, FEE_CODE) Fee_CountValidBlock( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlock,
                                 P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4UnUsedNum );

/* ブロックステータスデータ確定中状態管理 */
FUNC(uint32, FEE_CODE) Fee_FixBlockStatus( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 使用中ブロック作成中状態管理 */
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 転送中ブロック作成中状態管理 */
FUNC(uint32, FEE_CODE) Fee_MakeMoveBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 再編終了設定中状態管理 */
FUNC(uint32, FEE_CODE) Fee_SetMoveEnd( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* エリア無効・使用済設定中状態管理 */
FUNC(uint32, FEE_CODE) Fee_SetInvalidArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 使用済・故障設定中状態管理 */
FUNC(uint32, FEE_CODE) Fee_SetFailBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 全ブロックステータス判定 */
FUNC(uint32, FEE_CODE) Fee_JudgeAllBS( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* 読出し用全ブロックステータス判定 */
FUNC( void, FEE_CODE )
Fee_JudgeAllBSRead(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
);

/* ブロックステータス判定 */
FUNC(uint32, FEE_CODE) Fee_JudgeBS( P2VAR(Fee_UseBlockType, AUTOMATIC, TYPEDEF) ptstUseBlock );

/* 読出し用ブロックステータス判定 */
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

/* ブロックステータスデータ読出し */
FUNC(uint32, FEE_CODE) Fee_ReadBSData( uint8 u1BlockNo, uint32 u4BSDataKind, uint32 u4DuplicateDataKind );

/* 使用中ブロック選択 */
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
