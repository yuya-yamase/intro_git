/* Fee_Block.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/BLOCK/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Block_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_BSDATAPOS_USED            (0U)
#define FEE_BSDATAPOS_MOVE            (1U)
#define FEE_BSDATAPOS_USING           (2U)
#define FEE_VALIDBLKNUM               (2U)

#define FEE_VALIDBLKNUM_00            (0U)
#define FEE_VALIDBLKNUM_01            (1U)
#define FEE_VALIDBLKNUM_02            (2U)

#define FEE_USEBLKNUM_02              (2U)
#define FEE_USEBLKNUM_03              (3U)
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* ブロックステータスデータ確定遷移先判定テーブル */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_FixBSJudgeTBL[FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSNUM] = 
{
    /* 遷移先サブ状態       遷移先サブサブ状態      メインブロック      サブブロック */
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* 使用中           使用中       */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* 使用中           転送中       */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID},   /* 使用中           使用済       */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID},   /* 使用中           未使用       */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID}},  /* 使用中           不正         */
    
    {{FEE_SSTATUSWSMOV,     FEE_SSSTATUSWSMWERSG},  /* 転送中           使用中       */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG},  /* 転送中           転送中       */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWUSD},   /* 転送中           使用済       */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG},  /* 転送中           未使用       */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG}}, /* 転送中           不正         */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* 使用済           使用中       */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* 使用済           転送中       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 使用済           使用済       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 使用済           未使用       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}, /* 使用済           不正         */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* 未使用           使用中       */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* 未使用           転送中       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 未使用           使用済       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 未使用           未使用       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}, /* 未使用           不正         */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* 不正             使用中       */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* 不正             転送中       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 不正             使用済       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* 不正             未使用       */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}  /* 不正             不正         */
};

/* ブロックステータス判定テーブル */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSTBL[FEE_BSDATARANGE][FEE_BSDATAPOSNUM][FEE_BSDATAKINDNUM] = 
{
    /* ブロックステータス    使用中      転送中      使用済 */
    {{FEE_BS_UNUSED,     /*  消去        消去        消去   */
      FEE_BS_ILLEGAL,    /*  消去        消去        5A     */
      FEE_BS_ILLEGAL},   /*  消去        消去        以外   */
    
    {FEE_BS_ILLEGAL,     /*  消去        5A          消去   */
     FEE_BS_ILLEGAL,     /*  消去        5A          5A     */
     FEE_BS_ILLEGAL},    /*  消去        5A          以外   */
    
    {FEE_BS_ILLEGAL,     /*  消去        以外        消去   */
     FEE_BS_ILLEGAL,     /*  消去        以外        5A     */
     FEE_BS_ILLEGAL}},   /*  消去        以外        以外   */
    
    {{FEE_BS_USING,      /*  5A          消去        消去   */
      FEE_BS_USED,       /*  5A          消去        5A     */
      FEE_BS_USED},      /*  5A          消去        以外   */
    
    {FEE_BS_MOVE,        /*  5A          5A          消去   */
     FEE_BS_USED  ,      /*  5A          5A          5A     */
     FEE_BS_USED},       /*  5A          5A          以外   */
    
    {FEE_BS_USING,       /*  5A          以外        消去   */
     FEE_BS_USED,        /*  5A          以外        5A     */
     FEE_BS_USED}},      /*  5A          以外        以外   */
    
    {{FEE_BS_ILLEGAL,    /*  以外        消去        消去   */
      FEE_BS_ILLEGAL,    /*  以外        消去        5A     */
      FEE_BS_ILLEGAL},   /*  以外        消去        以外   */
    
    {FEE_BS_ILLEGAL,     /*  以外        5A          消去   */
     FEE_BS_ILLEGAL,     /*  以外        5A          5A     */
     FEE_BS_ILLEGAL},    /*  以外        5A          以外   */
    
    {FEE_BS_ILLEGAL,     /*  以外        以外        消去   */
     FEE_BS_ILLEGAL,     /*  以外        以外        5A     */
     FEE_BS_ILLEGAL}}    /*  以外        以外        以外   */
};

/* ２重化ブロックステータスデータ判定テーブル（エリアステータス） */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_A[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* ブロックステータスデータ     確定種別          2個目読出し結果     1個目読出し結果 */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 消去             消去            */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 消去             5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)},      /* 消去             以外            */
    
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 5A               消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A               5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)},      /* 5A               以外            */
    
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 以外             消去            */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 以外             5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)}       /* 以外             以外            */
};

/* ２重化ブロックステータスデータ判定テーブル（使用済） */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_C[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* ブロックステータスデータ     確定種別          2個目読出し結果     1個目読出し結果 */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 消去             消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 消去             5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* 消去             以外            */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 5A               消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A               5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* 5A               以外            */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 以外             消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 以外             5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)}       /* 以外             以外            */
};

/* ２重化ブロックステータスデータ判定テーブル（使用中・転送中） */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_B[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* ブロックステータスデータ     確定種別          2個目読出し結果     1個目読出し結果 */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 消去             消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 消去             5A              */
     (FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX)},      /* 消去             以外            */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 5A               消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A               5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* 5A               以外            */
    
    {(FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX),       /* 以外             消去            */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 以外             5A              */
     (FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX)}       /* 以外             以外            */
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：書込みブロック選択状態管理                                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込みブロック選択中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込みブロック選択終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込みブロック選択中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SelectWriteBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* サブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubStatus )
    {
        case FEE_SSTATUSWSFIX:  /* 「ブロックステータスデータ確定中」の場合 */
            /* ブロックステータスデータ確定状態管理処理 */
            u4tReturn = Fee_FixBlockStatus( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSUSG:  /* 「使用中ブロック作成中」の場合 */
            /* 使用中ブロック作成中状態管理処理 */
            u4tReturn = Fee_MakeUseBlock( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSMOV:  /* 「転送中ブロック作成中」の場合 */
            /* 転送中ブロック作成中状態管理処理 */
            u4tReturn = Fee_MakeMoveBlock( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSWEMOV:    /* 「再編終了設定中」の場合 */
            /* 再編終了設定中状態管理処理 */
            u4tReturn = Fee_SetMoveEnd( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSALLU: /* 「エリア無効・使用済設定中」の場合 */
            /* エリア無効・使用済設定中状態管理処理 */
            u4tReturn = Fee_SetInvalidArea( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSFAIL: /* 「使用済・故障設定中」の場合 */
            /* 使用済・故障設定中状態管理処理 */
            u4tReturn = Fee_SetFailBlock( ptstCPUDTFInfo );
            break;
        default:                            /* 上記以外の場合 */
            /* 有効レコード位置TBL初期化 */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* 処理結果を「再編失敗」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* 戻り値に「書込みブロック選択終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ブロックステータスデータ確定中状態管理                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：確定処理中・継続不可       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：確定処理終了               */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：確定処理中・継続可         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_FixBlockStatus( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 選択結果 */
    uint8           FixBSJudgeTBLMainBlockIndex;
    uint8           FixBSJudgeTBLSubBlockIndex;
    
    /* 選択結果を「選択失敗」で初期化 */
    u4tResult = FEE_STATUS_NG;

    /* ブロックステータスを記憶済みでない場合 */
    if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_INVALID)
        || (ptstCPUDTFInfo->u1SubBlockStatus == FEE_BS_INVALID) )
    {
        /* 全ブロックステータス判定処理 */
        u4tReturn = Fee_JudgeAllBS( ptstCPUDTFInfo );
        /* 「判定終了」の場合 */
        if ( u4tReturn == FEE_STATUS_DONE )
        {
            /* 使用中ブロック選択処理 */
            u4tResult = Fee_SelectUseBlock( ptstCPUDTFInfo );
            /* 「選択成功」の場合 */
            if ( u4tResult == FEE_STATUS_OK )
            {
                /* ブロックステータスを記憶済みの場合と同様の処理を行う */
                /* ブロックステータスの組み合わせから次のサブ状態とサブサブ状態を選択 */
            }
            /* 「ブロック未使用」の場合 */
            else if ( u4tResult == FEE_STATUS_NODATA )
            {
                /* サブ状態を「使用中ブロック作成中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSUSG;
                /* サブサブ状態を「使用中ブロック作成中－使用中設定待ち」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUWUSG;
            }
            /* 「選択失敗」の場合 */
            else
            {
                /* サブ状態を「エリア無効・使用済設定中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSALLU;
                /* サブサブ状態を「エリア無効・使用済設定中－アイドル」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSAIDLE;
            }
            /* 戻り値をEXITに設定 */
            u4tReturn = FEE_STATUS_EXIT;
        }
        /* 「判定中・継続不可」の場合 */
        else
        {
            /* No process to return the return value */
        }
    }
    /* ブロックステータスを記憶済みの場合 */
    else
    {
        /* 戻り値に「確定処理中・継続可」を設定 */
        u4tReturn = FEE_STATUS_CONT;
        /* 選択結果に「選択成功」を設定 */
        u4tResult = FEE_STATUS_OK;
    }
    
    /* 選択結果が「選択成功」の場合 */
    if ( u4tResult == FEE_STATUS_OK )
    {
        FixBSJudgeTBLMainBlockIndex = ptstCPUDTFInfo->u1MainBlockStatus - (uint8)FEE_FIX_BS_JUDGE_TBL_OFFSET;
        FixBSJudgeTBLSubBlockIndex  = ptstCPUDTFInfo->u1SubBlockStatus - (uint8)FEE_FIX_BS_JUDGE_TBL_OFFSET;
        /* ブロックステータスの値域チェック */
        if ( ( FixBSJudgeTBLMainBlockIndex < (uint8)FEE_BSJUDGESTATUSKINDNUM ) && ( FixBSJudgeTBLSubBlockIndex < (uint8)FEE_BSJUDGESTATUSKINDNUM ) )
        {
            /* ブロックステータスの組み合わせから次のサブ状態、サブサブ状態を選択 */
            ptstCPUDTFInfo->u1SubStatus = Fee_FixBSJudgeTBL[FixBSJudgeTBLMainBlockIndex][FixBSJudgeTBLSubBlockIndex][FEE_FIX_BSTBLINDEX_SSTATUS];
            ptstCPUDTFInfo->u1SubSubStatus = Fee_FixBSJudgeTBL[FixBSJudgeTBLMainBlockIndex][FixBSJudgeTBLSubBlockIndex][FEE_FIX_BSTBLINDEX_SSSTATUS];

            /* サブ状態がレコード書込み中－アイドル */
            if ( ptstCPUDTFInfo->u1SubStatus == FEE_SSTATUSWWIDLE )
            {
                /* 動作状態が「データ再編中」の場合 */
                if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSMOVE )
                {
                    /* 次のサブ状態、サブサブ状態を上書き */
                    /* サブ状態を「転送中ブロック作成中」に設定 */
                    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSMOV;
                    /* サブサブ状態を「転送中ブロック作成中－転送中設定待ち」に設定 */
                    ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMWMOVE;
                }
                /* 動作状態が「書込み中」の場合 */
                else
                {
                    /* メイン状態を「レコード書込み中」に設定 */
                    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
                }
            }
            /* サブ状態が不正 */
            else if ( ptstCPUDTFInfo->u1SubStatus == FEE_SSTATUSINVALID )
            {
                /* 処理結果を「再編失敗」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* 戻り値をDONEに設定 */
                u4tReturn = FEE_STATUS_DONE;
            }
            /* 上記以外の場合 */
            else
            {
                /* No process */
            }
        }
        /* 上記以外の場合 */
        else
        {
            /* No process */
        }
    }
    /* 上記以外の場合 */
    else
    {
        /* No process */
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック作成中状態管理                               */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：使用中ブロック作成中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：使用中ブロック作成終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：使用中ブロック作成中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* 戻り値に「使用中ブロック作成中・継続不可」を設定 */
    u4tReturn = FEE_STATUS_EXIT;
    /* サブサブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSUWERSG:  /* 「消去待ち」の場合 */
            /* メインブロックを消去開始 */
            Fee_StartErase( ptstCPUDTFInfo->u1MainBlockNo );
            /* サブサブ状態を「消去中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUERSG;
            break;
        case FEE_SSSTATUSWSUWUSG:   /* 「使用中設定待ち」の場合 */
            /* メインブロックステータスに「使用中」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USING,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「使用中設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUUSG;
            break;
        case FEE_SSSTATUSWSUERSG:   /* 「消去中」の場合 */
            u4tReturn = Fee_MakeUseBlock_DoErasing( ptstCPUDTFInfo );
            break;
        case FEE_SSSTATUSWSUUSG:        /* 「使用中設定中」の場合 */
            u4tReturn = Fee_MakeUseBlock_DoWritingUsing( ptstCPUDTFInfo );
            break;
        default:                                /* 上記以外の場合 */
            /* 有効レコード位置TBL初期化 */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
            if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
            {
                /* 処理結果を「再編失敗」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            }
            /* 処理結果が「書込み成功・対象ブロックなし」の場合 */
            else
            {
                /* 処理結果を「書込み失敗・対象ブロックなし」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
            }
            /* 戻り値に「使用中ブロック作成終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック作成中状態管理(消去中)                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：使用中ブロック作成中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：使用中ブロック作成終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：使用中ブロック作成中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoErasing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */

    u4tReturn = FEE_STATUS_EXIT;

    /* データFlash制御結果取得 */
    u4tResult = Fee_GetMngDfcResult( NULL_PTR );
    /* エラーなしの場合 */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* メインブロックステータスに「使用中」を設定 */
        Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                        (uint32)FEE_BS_USING,
                                        FEE_BSWRITE_ALL );
        /* サブサブ状態を「使用中設定中」に設定 */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUUSG;
    }
    /* エラーありの場合 */
    else
    {
        /* サブサブ状態を先に設定したほうが16byte減るためこの順番とする */
        /* サブサブ状態を「使用済・故障設定中－メインブロック故障設定待ち」に設定 */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWMF;
        /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
        if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
        {
            /* 処理結果を「再編失敗」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
        }
        /* 処理結果が「書込み成功・対象ブロックなし」の場合 */
        else
        {
            /* 処理結果を「書込み失敗・対象ブロックなし」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
        }
        /* サブ状態を「使用済・故障設定中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    }
    
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック作成中状態管理(使用中設定中)                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：使用中ブロック作成中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：使用中ブロック作成終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：使用中ブロック作成中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoWritingUsing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */

    u4tReturn = FEE_STATUS_EXIT;

    /* データFlash制御結果取得 */
    u4tResult = Fee_GetMngDfcResult( NULL_PTR );
    /* エラーなしの場合 */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* メインブロックステータスを使用中に設定 */
        ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
        /* 動作状態が「書込み中」の場合 */
        if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
        {
            /* メイン状態を「レコード書込み中」に設定 */
            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
            /* サブ状態を「レコード書込み中－アイドル」に設定 */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWIDLE;
        }
        /* 上記以外の場合 */
        else
        {
            /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
            if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
            {
                /* 処理結果を「再編成功」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
            }
            /* 戻り値に「使用中ブロック作成終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
        }
    }
    /* エラーありの場合 */
    else
    {
        /* サブサブ状態を先に設定したほうが16byte減るためこの順番とする */
        /* サブサブ状態を「使用済・故障設定中－メインブロック使用済設定待ち」に設定 */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWMUSD;
        /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
        if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
        {
            /* 処理結果を「再編失敗」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
        }
        /* 処理結果が「書込み成功・対象ブロックなし」の場合 */
        else
        {
            /* 処理結果を「書込み失敗・対象ブロックなし」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
        }
        /* サブ状態を「使用済・故障設定中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    }
    
    return u4tReturn;
}


/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：転送中ブロック作成中状態管理                               */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中ブロック作成中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送中ブロック作成終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中ブロック作成中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MakeMoveBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */
    
    /* 戻り値に「転送中ブロック作成中・継続不可」を設定 */
    u4tReturn = FEE_STATUS_EXIT;
    /* サブサブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSMWMOVE:      /* 「転送中設定待ち」の場合 */
            /* メインブロックステータスに「転送中」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_MOVE,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「転送中設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMMOVE;
            break;
        case FEE_SSSTATUSWSMWUSD:       /* 「使用済設定待ち」の場合 */
            /* サブブロックステータスに「使用済」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「使用済設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMUSD;
            break;
        case FEE_SSSTATUSWSMWERSG:      /* 「消去待ち」の場合 */
            /* サブブロックを消去開始 */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* サブサブ状態を「消去中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMMOVE:       /* 「転送中設定中」の場合 */
            /* メインブロックステータスを転送中に設定 */
            ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_MOVE;
            /* サブブロックを消去開始 */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* サブサブ状態を「消去中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMUSD:            /* 「使用済設定中」の場合 */
            /* サブブロックを消去開始 */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* サブサブ状態を「消去中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMERSG:       /* 「消去中」の場合 */
            /* データFlash制御結果取得 */
            u4tResult = Fee_GetMngDfcResult( NULL_PTR );
            /* エラーなしの場合 */
            if ( u4tResult == FEE_STATUS_OK )
            {
                /* サブブロックステータスを未使用に設定 */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_UNUSED;
                /* メイン状態を「データ転送中」に設定 */
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBMOVE;
                /* サブ状態を「データ転送中－アイドル」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMIDLE;
            }
            /* エラーありの場合 */
            else
            {
                /* 処理結果を「再編失敗」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* サブ状態を「使用済・故障設定中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
                /* サブサブ状態を「使用済・故障設定中－サブブロック故障設定待ち」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSF;
            }
            break;
        default:                                    /* 上記以外の場合 */
            /* 有効レコード位置TBL初期化 */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* 処理結果を「再編失敗」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* 戻り値に「転送中ブロック作成終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：再編終了設定中状態管理                                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：再編終了設定中・継続不可   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：再編終了設定終了           */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：再編終了設定中・継続可     */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SetMoveEnd( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;          /* 戻り値 */
    uint32          u4tResult;          /* 結果 */
    uint8           u1tWorkBlockNo;     /* 一時ワーク用 */
    Fee_UseBlockType    sttUseBlock;        /* 使用中ブロックデータ構造体 */

    /* サブサブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSEIDLE:       /* 「アイドル」の場合 */
            /* サブブロックステータスに「使用中」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USING,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「使用中設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEUSG;
            /* 戻り値に「再編終了設定中・継続不可」を設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSEUSG:            /* 「使用中設定中」の場合 */
            /* 戻り値にEXITを設定 */
            u4tReturn = FEE_STATUS_EXIT;
            /* データFlash制御結果取得 */
            u4tResult = Fee_GetMngDfcResult( NULL_PTR );
            /* エラーなしの場合 */
            if ( u4tResult == FEE_STATUS_OK )
            {
                /* メインブロックステータスに「使用済」を設定 */
                Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                                (uint32)FEE_BS_USED,
                                                FEE_BSWRITE_ALL );
                /* サブサブ状態を「使用済設定中」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEUSD;
            }
            /* エラーありの場合 */
            else
            {
                /* 有効レコード位置TBL初期化 */
                Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
                /* 処理結果を「再編失敗」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* サブ状態を「使用済・故障設定中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
                /* サブサブ状態を「使用済・故障設定中－サブブロック使用済設定待ち」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSUSD;
            }
            break;
        case FEE_SSSTATUSWSEUSD:            /* 「使用済設定中」の場合 */
            /* ブロック数=2の場合 */
            if ( ptstCPUDTFInfo->ptstAreaInf->u1BlockNum == (uint8)FEE_USEBLKNUM_02 )
            {
                /* メインブロックとサブブロックを入れ替え */
                u1tWorkBlockNo = ptstCPUDTFInfo->u1MainBlockNo;
                ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                ptstCPUDTFInfo->u1SubBlockNo = u1tWorkBlockNo;
                /* メインブロックステータスを使用中に設定 */
                ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
                /* サブブロックステータスを使用済に設定 */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_USED;
            }
            /* ブロック数が3以上の場合 */
            else
            {
                /* 本来のサブブロック番号にサブブロック番号を設定 */
                u1tWorkBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                /* サブブロックをメインブロックに設定 */
                ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                /* メインブロックステータスを使用中に設定 */
                ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
                /* 本来のサブブロックがエリアの最終ブロックの場合 */
                if ( u1tWorkBlockNo >= (ptstCPUDTFInfo->ptstAreaInf->u1AreaLastBlockNum) )
                {
                    /* エリアの先頭ブロックをサブブロックに設定 */
                    ptstCPUDTFInfo->u1SubBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;
                }
                /* 上記以外の場合 */
                else
                {
                    /* 本来のサブブロックの次のブロックをサブブロックに設定 */
                    ptstCPUDTFInfo->u1SubBlockNo = u1tWorkBlockNo + (uint8)FEE_NEXT_BLOCKNUM_OFFSET;
                }
                /* サブブロックのブロックステータスを判定 */
                /* 使用中ブロックデータ構造体にサブブロックを設定 */
                sttUseBlock.u1BlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                sttUseBlock.u1BlockStatus = FEE_BS_INVALID;
                /* ブロックステータス判定 */
                /* Note: The return value of Fee_JudgeBSForRead is not checked. */
                /*       It indicates whether FEE needs to fix BS. */
                /*       In reading jobs, FEE do not fix BS. */
                (void)Fee_JudgeBSForRead( &sttUseBlock );
                /* サブブロックを設定 */
                ptstCPUDTFInfo->u1SubBlockNo = sttUseBlock.u1BlockNo;
                ptstCPUDTFInfo->u1SubBlockStatus = sttUseBlock.u1BlockStatus;
            }
            
            /* 動作状態が「書込み中」の場合 */
            if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
            {
                /* メイン状態を「レコード書込み中」に設定 */
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
                /* サブ状態を「レコード書込み中－アイドル」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWIDLE;
                /* 戻り値にEXITを設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* 上記以外の場合 */
            else
            {
                /* データ書込み時・転送時書込み先アドレスがある場合 */
                if(( ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr != FEE_ADDRESS_INVALID )
                && ( ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr != FEE_ADDRESS_INVALID ))
                {
                    /* 最終書込みレコード位置更新許可フラグを「許可」に設定 */
                    ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
                }
                /* 上記以外の場合 */
                else
                {
                    /* No process */
                }
                /* 処理結果を「再編成功」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
                /* 戻り値に「再編終了設定終了」を設定 */
                u4tReturn = FEE_STATUS_DONE;
            }
            break;
        default:                                    /* 上記以外の場合 */
            /* 有効レコード位置TBL初期化 */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* 処理結果を「再編失敗」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* 戻り値に「再編終了設定終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：エリア無効・使用済設定中状態管理                           */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：エリア無効・使用済設定中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：エリア無効・使用済設定終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：エリア無効・使用済設定中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SetInvalidArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */
    uint8           u1tBlockNum;                                /* ブロック番号 */
    uint32          u4tBSFixKind;                               /* 確定処理種別 */
    uint8           u1tWritePlace = FEE_BSWRITE_NOTWRITE;
    
    /* サブサブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSAIDLE:       /* 「アイドル」の場合 */
            /* ブロックカウンタ初期化 */
            ptstCPUDTFInfo->u4BlockCount = 0x00000000UL;
            /* サブサブ状態を「設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSASET;
            /* ブロックステータスデータ判定（エリアステータス） */
            u4tResult = Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                                    (uint32)FEE_BS_AREA,
                                                    &u4tBSFixKind,
                                                    &u1tWritePlace );
            /* エリアステータスの領域がブランクの場合 */
            if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
            {
                /* エリアステータス設定 */
                Fee_WriteBlockStatus( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                                (uint32)FEE_BS_AREA,
                                                u1tWritePlace );
                /* 戻り値に「エリア無効・使用済設定中・継続不可」を設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* 上記以外の場合 */
            else
            {
                /* 戻り値に「エリア無効・使用済設定中・継続可」を設定 */
                u4tReturn = FEE_STATUS_CONT;
            }
            break;
        case FEE_SSSTATUSWSASET:            /* 「設定中」の場合 */
            /* 全ブロック終了の場合 */
            if ( (ptstCPUDTFInfo->u4BlockCount) >= (ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
            {
                /* 処理結果を「書込み成功・対象ブロックなし」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_INITIALIZE;
                /* エリアの先頭ブロックをメインブロックに設定 */
                ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;
                /* エリアの先頭ブロック＋１をサブブロックに設定 */
                ptstCPUDTFInfo->u1SubBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum + (uint8)FEE_NEXT_BLOCKNUM_OFFSET;
                /* メインブロックステータスを使用済に設定 */
                ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USED;
                /* サブブロックステータスを使用済に設定 */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_USED;
                /* サブ状態を「使用中ブロック作成中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSUSG;
                /* サブサブ状態を「使用中ブロック作成中－消去待ち」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUWERSG;
                /* 戻り値にEXITを設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* 上記以外の場合 */
            else
            {
                /* 先頭ブロックから順に「使用済」設定 */
                /* 対象ブロックのブロック番号算出 */
                u1tBlockNum = Fee_UseBlockInfo[ptstCPUDTFInfo->u4BlockCount].u1BlockNo;
                /* ブロックカウンタインクリメント */
                ptstCPUDTFInfo->u4BlockCount++;
                /* ブロックステータスデータ判定（使用済） */
                u4tResult = Fee_JudgeBSData( u1tBlockNum,
                                                        (uint32)FEE_BS_USED,
                                                        &u4tBSFixKind,
                                                        &u1tWritePlace );
                /* ブロックステータスの領域がブランクの場合 */
                if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
                {
                    /* 対象ブロックステータスに「使用済」を設定 */
                    Fee_WriteBlockStatus( u1tBlockNum,
                                                    (uint32)FEE_BS_USED,
                                                    u1tWritePlace );
                    /* 戻り値に「エリア無効・使用済設定中・継続不可」を設定 */
                    u4tReturn = FEE_STATUS_EXIT;
                }
                /* 上記以外の場合 */
                else
                {
                    /* 戻り値に「エリア無効・使用済設定中・継続可」を設定 */
                    u4tReturn = FEE_STATUS_CONT;
                }
            }
            break;
        default:                                    /* 上記以外の場合 */
            /* 処理結果を「書込み失敗・対象ブロックなし」に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
            /* 戻り値に「エリア無効・使用済設定終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用済・故障設定中状態管理                                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：使用済・故障設定中・継続不可 */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：使用済・故障設定終了         */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：使用済・故障設定中・継続可   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SetFailBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */

    /* サブサブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSFWMUSD:          /* 「メインブロック使用済設定待ち」の場合 */
            /* メインブロックステータスに「使用済」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* 戻り値に「使用済・故障設定中・継続不可」を設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWSUSD:          /* 「サブブロック使用済設定待ち」の場合 */
            /* サブブロックステータスに「使用済」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* 戻り値に「使用済・故障設定中・継続不可」を設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWMF:            /* 「メインブロック故障設定待ち」の場合 */
            /* メインブロックステータスに「使用済」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* 戻り値に「使用済・故障設定中・継続不可」を設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWSF:            /* 「サブブロック故障設定待ち」の場合 */
            /* サブブロックステータスに「使用済」を設定 */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* サブサブ状態を「設定中」に設定 */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* 戻り値に「使用済・故障設定中・継続不可」を設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        default:                                    /* 上記以外の場合 */
            /* 戻り値に「使用済・故障設定終了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：全ブロックステータス判定                                   */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                               ：MHA[データFlash]管理データ */
/* 出  力        ：判定結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：判定中・継続不可           */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：判定終了                   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_JudgeAllBS( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */
    uint8           u1tWriteReqFlag;                            /* 書込み要求フラグ */
    uint32          u4tBSFixKind;                               /* 確定処理種別 */
    uint8           u1tWritePlace = FEE_BSWRITE_NOTWRITE;
    uint8           BlockNum;
    boolean         DummyNeedsToFixBS = FALSE;
    
    /* 書込み要求フラグクリア */
    u1tWriteReqFlag = FEE_FLAG_OFF;
    /* 連続書込み用バッファ初期化 */
    Fee_ClearCWriteBuf();
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    
    /* ブロックカウンタ = 0（エリアステータス）の場合 */
    if ( ptstCPUDTFInfo->u4BlockCount == (uint32)FEE_TOP_BLOCK_IN_AREA )
    {
        /* ブロックステータスデータ判定（エリアステータス） */
        /* Return value is not checked. */
        /* This process is to set BlockStatus and does not use return value that is judgment of BlockStatus. */
        (void)Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                (uint32)FEE_BS_AREA,
                                &u4tBSFixKind,
                                &u1tWritePlace );
        /* 確定処理が必要な場合 */
        if ( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            /* ブロックステータス設定（エリアステータス） */
            Fee_SetBlockStatus( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                            (uint32)FEE_BS_AREA,
                                            u1tWritePlace );
            /* 書込み要求フラグを設定 */
            u1tWriteReqFlag = FEE_FLAG_ON;
            /* エリアステータスの確定が必要な場合は、エリア異常の時なので、                   */
            /* 次にブロックステータスの確定を行う必要はないため、ブロックカウンタを進めておく */
            ptstCPUDTFInfo->u4BlockCount = BlockNum;
            /* ただし、使用中ブロックデータ構造体(Fee_UseBlockInfo)にブロックステータスの */
            /* 判定結果を入れる必要があるため、読出し用全ブロックステータス判定を呼び出しておく      */
            /* 読出し用全ブロックステータス判定処理 */
            Fee_JudgeAllBSRead( ptstCPUDTFInfo, &DummyNeedsToFixBS );
        }
        /* 上記以外の場合 */
        else
        {
            /* No process */
        }
    }
    /* 上記以外の場合 */
    else
    {
        /* No process */
    }
    
    /* 全ブロック終了 or 書込み要求フラグが設定されるまで、ブロックステータス判定 */
    while ( ((ptstCPUDTFInfo->u4BlockCount) < BlockNum )
            && (u1tWriteReqFlag == FEE_FLAG_OFF) )
    {
        /* ブロックステータス判定 */
        u4tResult = Fee_JudgeBS( &(Fee_UseBlockInfo[ptstCPUDTFInfo->u4BlockCount]) );
        /* 「判定終了・確定処理あり」の場合 */
        if ( u4tResult == FEE_STATUS_EXIT )
        {
            /* 書込み要求フラグを設定 */
            u1tWriteReqFlag = FEE_FLAG_ON;
        }
        /* 「判定終了・確定処理なし」の場合 */
        else
        {
            /* No process */
        }
        /* ブロックカウンタインクリメント */
        ptstCPUDTFInfo->u4BlockCount++;
    }
    
    /* 書込み要求フラグが設定されている場合 */
    if ( u1tWriteReqFlag == FEE_FLAG_ON )
    {
        /* 連続書込み開始 */
        Fee_StartCWrite();
        /* 戻り値に「判定中・継続不可」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* 上記以外の場合 */
    else
    {
        /* 戻り値に「判定終了」を設定 */
        u4tReturn = FEE_STATUS_DONE;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：読出し用全ブロックステータス判定                           */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*                 NeedsToFix , An output argument.                           */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_JudgeAllBSRead(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
){
    uint32          u4tCounter;                                 /* カウンタ */
    uint32          ResultNeedsToFix;
    uint8           BlockNum;
    boolean         TmpNeedsToFix;

    /* カウンタクリア */
    u4tCounter = 0U;
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    TmpNeedsToFix = FALSE;
    /* 全ブロック終了まで、ブロックステータス判定 */
    do {
        /* ブロックステータス判定 */
        ResultNeedsToFix = Fee_JudgeBSForRead( &(Fee_UseBlockInfo[u4tCounter]) );
        if( ResultNeedsToFix == FEE_STATUS_EXIT )
        {
            TmpNeedsToFix = TRUE;
        }
        /* ブロックカウンタインクリメント */
        u4tCounter++;
    } while ( u4tCounter < (uint32)BlockNum );

    (*NeedsToFix) = TmpNeedsToFix;

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ブロックステータス判定                                     */
/* 入  力        ：FEE_stUSEBLOCK *ptstUseBlock                               */
/*                                               ：使用中ブロック構造体       */
/* 出  力        ：判定結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：判定終了・確定処理あり     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：判定終了・確定処理なし     */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_JudgeBS( P2VAR(Fee_UseBlockType, AUTOMATIC, TYPEDEF) ptstUseBlock )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tBSFixKind;                               /* 確定処理種別 */
    uint32          u4tBSData[FEE_BSDATAKINDNUM];       /* ブロックステータスデータ判定結果 */
    uint8           u1tWritePlace;
    uint32          u4tCounter;                                 /* カウンタ */
    uint8           u1tWriteReqFlag;                            /* 書込み要求フラグ */
    
    /* ブロックステータスデータ判定結果初期化 */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_BSDATAKINDNUM; u4tCounter++ )
    {
        u4tBSData[u4tCounter] = (uint32)FEE_BSDATA_OTHER;
    }
    
    /* 書込み要求フラグクリア */
    u1tWriteReqFlag = FEE_FLAG_OFF;
    /* カウンタクリア */
    u4tCounter = 0U;
    
    /* 「使用済」「転送中」「使用中」の順番にブロックステータスデータを判定 */
    while ( u4tCounter < (uint32)FEE_BSDATAKINDNUM )
    {
        u1tWritePlace = FEE_BSWRITE_NOTWRITE;
        /* ブロックステータスデータ判定 */
        u4tBSData[u4tCounter] = Fee_JudgeBSData( ptstUseBlock->u1BlockNo,
                                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                                            &u4tBSFixKind,
                                                            &u1tWritePlace );
        /* 確定処理が必要な場合 */
        if ( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            /* ブロックステータス設定(0x55AA55AA上書き) */
            Fee_SetBlockStatus( ptstUseBlock->u1BlockNo,
                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                             u1tWritePlace );
            /* 書込み要求フラグを設定 */
            u1tWriteReqFlag = FEE_FLAG_ON;
        }
        /* 上記以外の場合 */
        else
        {
            /* No process */
        }
        
        /* カウンタインクリメント */
        u4tCounter++;
    }
    
    /* ブロックステータスデータ判定結果からブロックステータスを決定 */
    ptstUseBlock->u1BlockStatus = Fee_JudgeBSTBL[u4tBSData[FEE_BSDATAPOS_USING]][u4tBSData[FEE_BSDATAPOS_MOVE]][u4tBSData[FEE_BSDATAPOS_USED]];
    
    /* 書込み要求フラグが設定されている場合 */
    if ( u1tWriteReqFlag == FEE_FLAG_ON )
    {
        /* 戻り値に「判定終了・確定処理あり」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* 上記以外の場合 */
    else
    {
        /* 戻り値に「判定終了・確定処理なし」を設定 */
        u4tReturn = FEE_STATUS_DONE;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：読出し用ブロックステータス判定                             */
/* 入  力        ：FEE_stUSEBLOCK *ptstUseBlock                               */
/*                                               ：使用中ブロック構造体       */
/* 出  力        ：確定処理要否                                               */
/*                      FEE_STATUS_EXIT                                       */
/*                      FEE_STATUS_DONE                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_JudgeBSForRead(
    P2VAR( Fee_UseBlockType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstUseBlock
){
    uint32          u4tBSFixKind;                               /* 確定処理種別 */
    uint32          u4tBSData[FEE_BSDATAKINDNUM];       /* ブロックステータスデータ判定結果 */
    uint32          u4tCounter;                                 /* カウンタ */
    uint32          Rtn;
    uint8           u1tDummyWritePlace;

    /* ブロックステータスデータ判定結果初期化 */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_BSDATAKINDNUM; u4tCounter++ )
    {
        u4tBSData[u4tCounter] = (uint32)FEE_BSDATA_OTHER;
    }
    
    /* カウンタクリア */
    u4tCounter = 0U;
    
    /* 「使用済」「転送中」「使用中」の順番にブロックステータスデータを判定 */
    Rtn = FEE_STATUS_DONE;
    while ( u4tCounter < (uint32)FEE_BSDATAKINDNUM )
    {
        /* ブロックステータスデータ判定 */
        u4tBSData[u4tCounter] = Fee_JudgeBSData( ptstUseBlock->u1BlockNo,
                                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                                            &u4tBSFixKind,
                                                            &u1tDummyWritePlace );
        if( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            Rtn = FEE_STATUS_EXIT;
        }
        /* カウンタインクリメント */
        u4tCounter++;
    }
    
    /* ブロックステータスデータ判定結果からブロックステータスを決定 */
    ptstUseBlock->u1BlockStatus = Fee_JudgeBSTBL[u4tBSData[FEE_BSDATAPOS_USING]][u4tBSData[FEE_BSDATAPOS_MOVE]][u4tBSData[FEE_BSDATAPOS_USED]];

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_JudgeBSData                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | ptu4FixKind                                              */
/*               | ptu1WritePlace                                           */
/* Return Value  | FEE_BSDATA_ERASE                                         */
/*               | FEE_BSDATA_VALID                                         */
/*               | FEE_BSDATA_OTHER                                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_JudgeBSData(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4FixKind,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) ptu1WritePlace
){
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tBSData1;                                 /* ブロックステータスデータ読出し結果（1個目） */
    uint32          u4tBSData2;                                 /* ブロックステータスデータ読出し結果（2個目） */
    uint8           u1tTmpWritePlace = (uint8)FEE_BSWRITE_NOTWRITE;
    
    /* ブロックステータスデータ読出し（1個目） */
    u4tBSData1 = Fee_ReadBSData( u1BlockNo, u4BSDataKind, FEE_DUPLIDATA_1ST );
    /* ブロックステータスデータ読出し（2個目） */
    u4tBSData2 = Fee_ReadBSData( u1BlockNo, u4BSDataKind, FEE_DUPLIDATA_2ND );

    if( u4tBSData1 == (uint32)FEE_BSDATA_ERASE )
    {
        u1tTmpWritePlace = (uint8)FEE_BSWRITE_MAIN;
    }
    if( u4tBSData2 == (uint32)FEE_BSDATA_ERASE )
    {
        u1tTmpWritePlace |= (uint8)FEE_BSWRITE_SUB;
    }
    *ptu1WritePlace = u1tTmpWritePlace;

    /* ブロックステータスデータ読出し結果からブロックステータスデータを決定 */
    /* ブロックステータスデータ種別が「エリアステータス」の場合 */
    if ( u4BSDataKind == FEE_BS_AREA )
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_A[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_A[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    /* ブロックステータスデータ種別が「使用済」の場合 */
    else if ( u4BSDataKind == FEE_BS_USED )
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_C[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_C[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    /* 上記以外の場合 */
    else
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_B[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_B[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ブロックステータスデータ読出し                             */
/* 入  力        ：uint8 u1BlockNo                ：ブロック番号              */
/*               ：uint32 u4BSDataKind             ：ブロックステータスデータ種別 */
/*               ：uint32 u4DuplicateDataKind      ：２重化データ種別         */
/* 出  力        ：ブロックステータスデータ判定結果                           */
/*               ：  0x00000000 ：FEE_BSDATA_ERASE   ：消去状態               */
/*               ：  0x00000001 ：FEE_BSDATA_VALID   ：0x55AA55AA             */
/*               ：  0x00000002 ：FEE_BSDATA_OTHER   ：上記以外               */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_ReadBSData( uint8 u1BlockNo, uint32 u4BSDataKind, uint32 u4DuplicateDataKind )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tReadAddress;                             /* 読出しアドレス */
    uint8           u1tCompareResult;
    uint32          u4tBlockStartAddr;

    /* 読出しアドレス算出 */
    u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[u1BlockNo];
    u4tReadAddress    = u4tBlockStartAddr + Fee_ASBSDataTBL[u4DuplicateDataKind][u4BSDataKind];

    /* Compare data flash. */
    u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( u4tReadAddress, &Fee_FixBSData[0] );

    /* Judge the result of comparision. */
    switch ( u1tCompareResult )
    {
        case FEE_DFCMPU_RESULT_BLANK:
            /* Set return value as ERASE. */
            u4tReturn = (uint32)FEE_BSDATA_ERASE;
            break;
        case FEE_DFCMPU_RESULT_OK:
            /* Set return value as VALID (0x55AA55AA). */
            u4tReturn = (uint32)FEE_BSDATA_VALID;
            break;
        default:
            /* Set return value as OTHER. */
            u4tReturn = (uint32)FEE_BSDATA_OTHER;
            break;
    }

    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック選択                                         */
/* 入  力        ：uint8 u1MainBlockStatus ：メインブロックステータス         */
/*               ：uint8 u1SubBlockStatus  ：サブブロックステータス           */
/*               ：uint8 u1BlockNum        ：エリア内ブロック数               */
/*               ：boolean *u1Swap         ：メイン・サブ入れ替え要否         */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/*               ：  0x00000001 ：u4gSTATUS_NG     ：選択失敗                 */
/* グローバル変数：使用中ブロックデータ構造体(Fee_UseBlockInfo)               */
/* その他        ：使用中ブロックデータ構造体は前もって                       */
/*               ：(読出し用)全ブロックステータス判定処理で判定しておく       */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SelectUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */
    uint32          u4tBSFixKind;                               /* 確定処理種別 */
    uint32          u4tCounter;                                 /* カウンタ */
    uint32          u4tUnUsedCount;                             /* 未使用ブロック数 */
    uint32          u4tValidCount;                              /* 有効ブロック数 */
    uint32          u4tValidBlockNum[FEE_VALIDBLKNUM];  /* 有効ブロック格納配列番号 */
    uint32          u4tMainValidBlockNum;                       /* メインブロック候補格納配列番号 */
    uint32          u4tSubValidBlockNum;                        /* サブブロック候補格納配列番号 */
    uint8           u1tDummyWritePlace;
    
    /* 有効ブロック格納配列初期化 */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_VALIDBLKNUM; u4tCounter++ )
    {
        u4tValidBlockNum[u4tCounter] = 0U;
    }
    u4tMainValidBlockNum = 0U;
    u4tSubValidBlockNum = 0U;
    
    /* ブロックステータスデータ判定（エリアステータス） */
    u4tResult = Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                            (uint32)FEE_BS_AREA,
                                            &u4tBSFixKind,
                                            &u1tDummyWritePlace );
    /* エリアステータスが正常な場合 */
    if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
    {
        
        /* 有効ブロック数カウント */
        Fee_CountValidBlock( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tValidCount, &u4tUnUsedCount );
        
        /* 有効ブロック数により分岐 */
        switch ( u4tValidCount )
        {
            case FEE_VALIDBLKNUM_00:                    /* 0個の場合 */
                u4tReturn = Fee_FixUseBlockInCaseOfZero( ptstCPUDTFInfo, u4tUnUsedCount, &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            case FEE_VALIDBLKNUM_01:                    /* 1個の場合 */
                u4tReturn = Fee_FixUseBlockInCaseOfOne( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            case FEE_VALIDBLKNUM_02:                    /* 2個の場合 */
                u4tReturn = Fee_FixUseBlockInCaseOfTwoAndMore( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            default:                /* 上記以外の場合 */
                /* 戻り値に「選択失敗」を設定 */
                u4tReturn = FEE_STATUS_NG;
                break;
        }
    }
    /* 上記以外の場合 */
    else
    {
        /* 戻り値に「選択失敗」を設定 */
        u4tReturn = FEE_STATUS_NG;
    }
    
    /* 戻り値が「選択失敗」以外の場合 */
    if ( u4tReturn != FEE_STATUS_NG )
    {
        /* MHA[データFlash]管理データのメインブロックを設定 */
        ptstCPUDTFInfo->u1MainBlockNo = Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockNo;
        ptstCPUDTFInfo->u1MainBlockStatus = Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockStatus;
        /* MHA[データFlash]管理データのサブブロックを設定 */
        ptstCPUDTFInfo->u1SubBlockNo = Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockNo;
        ptstCPUDTFInfo->u1SubBlockStatus = Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockStatus;
    }
    /* 戻り値が「選択失敗」の場合は処理なし */

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：有効ブロックカウント                                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 *ptu4ValidBlock：有効ブロック格納配列番号           */
/*               ：uint32 *ptu4ValidNum  ：有効ブロック数                     */
/*               ：uint32 *ptu4UnUsedNum ：未使用ブロック数                   */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_CountValidBlock( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlock,
                                 P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4UnUsedNum )
{
    uint32          u4tCounter;                                 /* カウンタ */
    uint32          u4tUnUsedCount;                             /* 未使用ブロック数 */
    uint32          u4tValidCount;                              /* 有効ブロック数 */
    uint8           BlockNum;

    /* 未使用ブロック数クリア */
    u4tUnUsedCount = 0U;
    /* 有効ブロック数クリア */
    u4tValidCount = 0U;
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    /* 使用中ブロックデータから未使用ブロック数、有効ブロック数をカウント（ブロック数分ループ） */
    for ( u4tCounter = 0U; u4tCounter < (uint32)BlockNum; u4tCounter++ )
    {
        /* ブロックステータスが「未使用」の場合 */
        if ( Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_UNUSED )
        {
            /* 未使用ブロック数インクリメント */
            u4tUnUsedCount++;
        }
        /* ブロックステータスが「使用中」or「転送中」の場合 */
        else if ( (Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_USING)
                || (Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_MOVE) )
        {
            /* 見つかった有効ブロックが格納されている配列番号を最大２個分記憶する */
            if ( u4tValidCount < (uint32)FEE_VALIDBLKNUM )
            {
                /* 有効ブロック格納配列番号を設定 */
                ptu4ValidBlock[u4tValidCount] = u4tCounter;
            }
            /* 有効ブロック数インクリメント */
            u4tValidCount++;
        }
        /* 上記以外の場合 */
        else
        {
            /* No process */
        }
    }
    
    *ptu4UnUsedNum = u4tUnUsedCount;
    *ptu4ValidNum = u4tValidCount;
    
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック選択(有効ブロック数０)                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 u4UnUsedCount  ：未使用ブロック数                   */
/*               ：uint32 *ptu4MainValidBlockNum                              */
/*                                           ：メインブロック候補格納配列番号 */
/*               ：uint32 *ptu4SubValidBlockNum                               */
/*                                           ：サブブロック候補格納配列番号   */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/*               ：  0x00000007 ：u4gSTATUS_NODATA ：ブロック未使用           */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfZero( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, uint32 u4UnUsedCount,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* エリア先頭ブロックをメインブロックとする */
    *ptu4MainValidBlockNum = (uint32)FEE_TOP_BLOCK_IN_AREA;
    /* メインブロックの次のブロックをサブブロックとする */
    *ptu4SubValidBlockNum = (uint32)FEE_SECOND_BLOCK_IN_AREA;
    /* 全ブロック未使用の場合 */
    if ( u4UnUsedCount >= (uint32)(ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
    {
        /* 戻り値に「ブロック未使用」を設定 */
        u4tReturn = FEE_STATUS_NODATA;
    }
    /* 上記以外の場合 */
    else
    {
        /* 戻り値に「選択成功」を設定 */
        u4tReturn = FEE_STATUS_OK;
    }
    
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック選択(有効ブロック数１)                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 *ptu4ValidBlockNum                                  */
/*                                           ：有効ブロック格納配列番号       */
/*               ：uint32 *ptu4MainValidBlockNum                              */
/*                                           ：メインブロック候補格納配列番号 */
/*               ：uint32 *ptu4SubValidBlockNum                               */
/*                                           ：サブブロック候補格納配列番号   */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfOne( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* 有効ブロックをメインブロックとする */
    *ptu4MainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
    /* メインブロックの次のブロックをサブブロックに設定 */
    *ptu4SubValidBlockNum = (*ptu4MainValidBlockNum) + (uint32)FEE_NEXT_BLOCKNUM_OFFSET;
    /* サブブロックが最終ブロックを超えていた場合 */
    if ( (*ptu4SubValidBlockNum) >= (uint32)(ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
    {
        /* エリア先頭ブロックをサブブロックに設定 */
        (*ptu4SubValidBlockNum) = (uint32)FEE_TOP_BLOCK_IN_AREA;
    }
    /* 戻り値に「選択成功」を設定 */
    u4tReturn = FEE_STATUS_OK;
    
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロック選択(有効ブロック数２以上)                   */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 *ptu4ValidBlockNum                                  */
/*                                           ：有効ブロック格納配列番号       */
/*               ：uint32 *ptu4MainValidBlockNum                              */
/*                                           ：メインブロック候補格納配列番号 */
/*               ：uint32 *ptu4SubValidBlockNum                               */
/*                                           ：サブブロック候補格納配列番号   */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/*               ：  0x00000001 ：u4gSTATUS_NG     ：選択失敗                 */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfTwoAndMore( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tMainValidBlockNum;                       /* メインブロック候補格納配列番号 */
    uint32          u4tSubValidBlockNum;                        /* サブブロック候補格納配列番号 */
    uint32          u4tWorkValidBlockNum;                       /* 候補格納配列番号ワーク */
    boolean     u1tSwap;

    /* 戻り値に「選択成功」を設定 */
    u4tReturn = FEE_STATUS_OK;

    u4tMainValidBlockNum = 0U;
    u4tSubValidBlockNum = 0U;

    /* 最初のブロックと最後のブロックが有効ブロックの場合 */
    if ( (ptu4ValidBlockNum[FEE_ARRAY_INDEX_00] == (uint32)FEE_TOP_BLOCK_IN_AREA) 
        && (ptu4ValidBlockNum[FEE_ARRAY_INDEX_01] == ((uint32)ptstCPUDTFInfo->ptstAreaInf->u1BlockNum - (uint32)FEE_LAST_BLOCKNUM_OFFSET)) )
    {
        u4tMainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_01];
        u4tSubValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
    }
    /* 有効ブロックが連続している場合 */
    else if ( ptu4ValidBlockNum[FEE_ARRAY_INDEX_01] == (ptu4ValidBlockNum[FEE_ARRAY_INDEX_00] + (uint32)FEE_NEXT_BLOCKNUM_OFFSET) )
    {
        u4tMainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
        u4tSubValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_01];
    }
    else
    {
        /* 戻り値に「選択失敗」を設定 */
        u4tReturn = FEE_STATUS_NG;
    }
    /* 戻り値が「選択成功」の場合 */
    if ( u4tReturn == FEE_STATUS_OK )
    {
        
        u4tReturn = Fee_JudgeBlockStatusCombination( Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockStatus,
                                                    Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockStatus,
                                                    ptstCPUDTFInfo->ptstAreaInf->u1BlockNum,
                                                    &u1tSwap );
        if ( u1tSwap == ( boolean )TRUE )
        {
            /* メインとサブを入れ替え */
            u4tWorkValidBlockNum = u4tMainValidBlockNum;
            u4tMainValidBlockNum = u4tSubValidBlockNum;
            u4tSubValidBlockNum = u4tWorkValidBlockNum;
        }
    }
    
    /* 確定したメインブロック番号、サブブロック番号を設定して終了 */
    *ptu4MainValidBlockNum = u4tMainValidBlockNum;
    *ptu4SubValidBlockNum = u4tSubValidBlockNum;
    
    return u4tReturn;
    
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ブロックステータス組み合わせ判定                           */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 *ptu4ValidBlockNum                                  */
/*                                           ：有効ブロック格納配列番号       */
/*               ：uint32 *ptu4MainValidBlockNum                              */
/*                                           ：メインブロック候補格納配列番号 */
/*               ：uint32 *ptu4SubValidBlockNum                               */
/*                                           ：サブブロック候補格納配列番号   */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/*               ：  0x00000001 ：u4gSTATUS_NG     ：選択失敗                 */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_JudgeBlockStatusCombination(uint8 u1MainBlockStatus, uint8 u1SubBlockStatus, uint8 u1BlockNum, P2VAR(boolean, AUTOMATIC, TYPEDEF) u1Swap)
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    u4tReturn = FEE_STATUS_NG;
    *u1Swap   = FALSE;
    
    /* メインが「転送中」の場合 */
    if (u1MainBlockStatus == FEE_BS_MOVE)
    {
        /* メインが「転送中」、サブが「使用中」の場合 */
        if (u1SubBlockStatus == FEE_BS_USING)
        {
            /* 選択成功 */
            u4tReturn = FEE_STATUS_OK;
        }
        /* メインが「転送中」、サブが「転送中」、ブロック数が3以上の場合 */
        else if (( u1SubBlockStatus == FEE_BS_MOVE ) && ( u1BlockNum >= (uint8)FEE_USEBLKNUM_03 ))
        {
            /* 選択成功 */
            u4tReturn = FEE_STATUS_OK;
        }
        else
        {
            /* No process in case of selection failure */
        }
    }
    /* メインが「使用中」の場合 */
    else if (u1MainBlockStatus == FEE_BS_USING){
        
        /* メインが「使用中」、サブが「転送中」、ブロック数が2の場合 */
        if (( u1SubBlockStatus == FEE_BS_MOVE )&&(u1BlockNum == (uint8)FEE_USEBLKNUM_02))
        {
            /* 選択成功 */
            u4tReturn = FEE_STATUS_OK;
            /* メインとサブを入れ替え */
            *u1Swap = TRUE;
        }
    }
    else
    {
        /* No process in case of selection failure */
    }
    
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_WriteBlockStatus                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | u1WritePlace                                             */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_WriteBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
){
    /* 連続書込み用バッファ初期化処理 */
    Fee_ClearCWriteBuf();

    Fee_SetBlockStatus( u1BlockNo, u4BSDataKind, u1WritePlace );
    /* 連続書込み開始処理 */
    Fee_StartCWrite();

    return;
}

/****************************************************************************/
/* Function Name | Fee_SetBlockStatus                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | u1WritePlace                                             */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_SetBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
){
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1WriteData;                       /* 書込みデータポインタ */
    uint32          u4tAddress1;                                /* アドレス（１個目） */
    uint32          u4tAddress2;                                /* アドレス（２個目） */
    uint16          u2tCWriteFlag;                              /* 連続書込み用フラグ */
    uint32          u4tBlockStartAddress;                       /* ブロック先頭アドレス */

    /* 書込みデータ初期化（0x55AA55AA55AA55AA） */
    ptu1WriteData = &Fee_FixBSData[0];
    u2tCWriteFlag = FEE_CWFLG_VOLMINCHK;
    /* ブロック先頭アドレス */
    u4tBlockStartAddress = FEE_BLKSTARTADDRTBL[u1BlockNo];

    if ( u4BSDataKind <= FEE_BS_USED )
    {
        /* ブロックステータスのアドレス算出 */
        u4tAddress1 = u4tBlockStartAddress + Fee_ASBSDataTBL[FEE_DUPLIDATA_1ST][u4BSDataKind];
        u4tAddress2 = u4tBlockStartAddress + Fee_ASBSDataTBL[FEE_DUPLIDATA_2ND][u4BSDataKind];
        
        /* ブロックステータス種別が「使用中」の場合 */
        if ( u4BSDataKind == FEE_BS_USING )
        {
            u2tCWriteFlag = FEE_CWFLG_VOLMINCHK | FEE_CWFLG_VRFYERRCHK;
        }
        /* 上記以外の場合 */
        else
        {
            /* No process */
        }
        
        if( (u1WritePlace & (uint8)FEE_BSWRITE_MAIN) == (uint8)FEE_BSWRITE_MAIN )
        {
            Fee_AddCWriteBuf( u4tAddress1, ptu1WriteData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, u2tCWriteFlag );
        }
        if( (u1WritePlace & (uint8)FEE_BSWRITE_SUB) == (uint8)FEE_BSWRITE_SUB )
        {
            Fee_AddCWriteBuf( u4tAddress2, ptu1WriteData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, u2tCWriteFlag );
        }
    }
    /* 上記以外の場合 */
    else
    {
        /* No process */
    }

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：読出し／空き領域確認用ブロック選択                         */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo：MHA[データFlash]管理データ       */
/* 出  力        ：選択結果                                                   */
/*               ：  0x00000000 ：u4gSTATUS_OK     ：選択成功                 */
/*               ：  0x00000001 ：u4gSTATUS_NG     ：選択失敗(データなし)     */
/*               ：  0x00000007 ：u4gSTATUS_NODATA ：選択失敗(ブロック未使用) */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 選択結果 */
    boolean         DummyNeedsToFixBS = FALSE;
    
    /* 戻り値に「選択失敗(データなし)」を設定 */
    u4tReturn = FEE_STATUS_NG;
    
    /* ブロックステータスを記憶済みでない場合 */
    if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_INVALID)
        || (ptstCPUDTFInfo->u1SubBlockStatus == FEE_BS_INVALID) )
    {
        /* 読出し用全ブロックステータス判定処理 */
        Fee_JudgeAllBSRead( ptstCPUDTFInfo, &DummyNeedsToFixBS );
        /* 使用中ブロック選択処理 */
        u4tResult = Fee_SelectUseBlock( ptstCPUDTFInfo );
    }
    /* ブロックステータスを記憶済みの場合 */
    else
    {
        /* 選択結果に「選択成功」を設定 */
        u4tResult = FEE_STATUS_OK;
    }
    
    /* 選択結果が「選択成功」の場合 */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* メインブロックのステータスが「使用中」or「転送中」の場合 */
        if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_USING)
            || (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_MOVE) )
        {
            /* 戻り値に「選択成功」を設定 */
            u4tReturn = FEE_STATUS_OK;
        }
        /* 上記以外の場合 */
        else
        {
            /* 戻り値に「選択失敗(データなし)」を設定 */
            u4tReturn = FEE_STATUS_NG;
        }
    }
    /* 「ブロック未使用」の場合 */
    else if ( u4tResult == FEE_STATUS_NODATA )
    {
        /* 戻り値に「選択失敗(ブロック未使用)」を設定 */
        u4tReturn = FEE_STATUS_NODATA;
    }
    /* 「選択失敗」の場合 */
    else
    {
        /* No process */
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：使用中ブロックデータ初期化                                 */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_ClrUseBlockInfo( void )
{
    uint32          u4tCounter;                                 /* 一時ワーク用 */
    uint32          u4CounterMax;
    
    u4CounterMax = Fee_UseBlockInfoSize;
    
    for ( u4tCounter = 0U; u4tCounter < u4CounterMax; u4tCounter++ )
    {
        Fee_UseBlockInfo[u4tCounter].u1BlockNo = FEE_BLOCKNUM_INVALID;
        Fee_UseBlockInfo[u4tCounter].u1BlockStatus = FEE_BS_INVALID;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Block_CheckUseBlockInfo                              */
/* Description   | Function to check Fee_UseBlockInfo.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Block_CheckUseBlockInfo( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType  Rtn = E_OK;
    uint32          Counter;
    uint32          CounterMax;

    CounterMax = Fee_UseBlockInfoSize;

    for( Counter = 0U; Counter < CounterMax; Counter++ )
    {
        if((( Fee_UseBlockInfo[Counter].u1BlockNo     ^ Fee_UseBlockInfoSub[Counter].u1BlockNo     ) != (uint8)FEE_MIRROR_CHECK_UINT8 )
        || (( Fee_UseBlockInfo[Counter].u1BlockStatus ^ Fee_UseBlockInfoSub[Counter].u1BlockStatus ) != (uint8)FEE_MIRROR_CHECK_UINT8 ))
        {
            Rtn = E_NOT_OK;
            break;
        }
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_Block_SetUseBlockInfoSub                             */
/* Description   | Function to set value to sub Fee_UseBlockInfo from main. */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Block_SetUseBlockInfoSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    uint32  Counter;
    uint32  CounterMax;

    CounterMax = Fee_UseBlockInfoSubSize;

    for ( Counter = 0U; Counter < CounterMax; Counter++ )
    {
        Fee_UseBlockInfoSub[Counter].u1BlockNo     = (uint8)(~Fee_UseBlockInfo[Counter].u1BlockNo);
        Fee_UseBlockInfoSub[Counter].u1BlockStatus = (uint8)(~Fee_UseBlockInfo[Counter].u1BlockStatus);
    }
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_Block_GetSectorInfo                                  */
/* Description   | Function to get a main sector number.                    */
/* Preconditions | Set Fee_UseBlockInfo.                                    */
/* Parameters    | None                                                     */
/* Return Value  | FEE_STATUS_OK                                            */
/*               | FEE_STATUS_NODATA                                        */
/*               | FEE_STATUS_NG                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Block_GetSectorInfo(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
){
    uint32 Rtn;

    Fee_JudgeAllBSRead( CPUDTFInfo, NeedsToFix );
    Rtn = Fee_SelectUseBlock( CPUDTFInfo );

    return Rtn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
