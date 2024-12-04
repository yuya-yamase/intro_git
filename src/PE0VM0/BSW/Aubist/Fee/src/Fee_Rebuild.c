/* Fee_Rebuild.c v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/REBUILD/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

/* MHA[データFlash]I/Fヘッダ */
#include "../inc/Fee_Legacy.h"

/* MHA[データFlash]ヘッダ */
#include "../inc/Fee_Lib.h"

/* MHA[データFlash]ライブラリヘッダ */
#include "../inc/Fee_Common.h"
#include "../inc/Fee_Rebuild_Internal.h"

/* D.F.C.ヘッダ */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理                                         */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中(定期処理終了)       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送完了                   */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中(再実行可能)         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* サブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubStatus )
    {
        case FEE_SSTATUSWMIDLE:     /* 「アイドル」の場合 */
            u4tReturn = Fee_MoveData_DoIdle( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHMPS:  /* 「転送元最終データ位置検索中」の場合 */
            u4tReturn = Fee_MoveData_DoSrchingWriteLastPos( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMPREPSRCHMDT:      /* 「転送元データ検索準備中」の場合 */
            u4tReturn = Fee_MoveData_DoPrepSrchMoveRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHMDT:  /* 「転送元データ検索中」の場合 */
            u4tReturn = Fee_MoveData_DoSrchingMoveRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMPREPSRCHSDT:      /* 「転送先データ検索準備中」の場合 */
            u4tReturn = Fee_MoveData_DoPrepSrchDestRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMSRCHSDT:  /* 「転送先データ検索中」の場合 */
            u4tReturn = Fee_MoveData_DoSrchingDestRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWMWRITE:        /* 「データ書き込み中」の場合 */
            u4tReturn = Fee_MoveData_DoMovingRecord( ptstCPUDTFInfo );
            break;
        default:                                /* 上記以外の場合 */
            u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理(アイドル)                               */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中(定期処理終了)       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送完了                   */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中(再実行可能)         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoIdle( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tLastDestWritePosAddress;
    uint32          u4tRcrdDataAreaStartAbsAddr;
    uint32          u4tBlockStartAddr;

    /* 有効レコード位置TBL初期化 */
    Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
    u4tLastDestWritePosAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
    /* 末尾レコードを保持している場合 */
    if ( u4tLastDestWritePosAddress != FEE_ADDRESS_INVALID )
    {
        /* 転送元データがある場合 */
        if ( u4tLastDestWritePosAddress >= (FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo] + FEE_STARTRECORDPOS) )
        {
            /* データ転送時転送元アドレスに末尾レコードを設定 */
            ptstCPUDTFInfo->u4MoveSrcAddress = u4tLastDestWritePosAddress;
            /* サブ状態を「転送元データ検索準備中」に設定 */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            /* 戻り値にEXITを設定 */
            u4tReturn = FEE_STATUS_EXIT;
        }
        /* 転送元データがない場合 */
        else
        {
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
        }
    }
    /* 末尾レコードを保持していない場合 */
    else
    {
        /* データ転送時転送元アドレスに無効値を設定 */
        ptstCPUDTFInfo->u4MoveSrcAddress = FEE_ADDRESS_INVALID;
        /* 読出し検索開始アドレスを設定 */
        u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
        u4tRcrdDataAreaStartAbsAddr = u4tBlockStartAddr
                                      + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr );
        ptstCPUDTFInfo->u4ReadSrchAddress = u4tRcrdDataAreaStartAbsAddr - (uint32)FEE_RECORDMNGINFOLEN;
        /* サブ状態を「転送元最終データ位置検索中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHMPS;
        /* 戻り値に「転送中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    
    /* データ書込み時・転送時書込み先アドレスにサブブロックのレコード先頭アドレス－１レコード分を設定 */
    u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1SubBlockNo];
    ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ( u4tBlockStartAddr
                                            + FEE_STARTRECORDPOS )
                                            - (uint32)FEE_RECORDMNGINFOLEN;
    ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = ( u4tBlockStartAddr
                                            + (uint32)(ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr) )
                                            - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理(転送元最終データ位置検索中)             */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：STATUS_EXIT ：検索完了 or 検索中            */
/*               ：                                (定期処理終了)             */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingWriteLastPos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32 u4tSrchFSResult;
    uint32 u4tReturn = FEE_STATUS_EXIT;

    u4tSrchFSResult = Fee_SrchFreeSpace( ptstCPUDTFInfo );

    switch ( u4tSrchFSResult )
    {
        case FEE_STATUS_OK:
            ptstCPUDTFInfo->u4MoveSrcAddress = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            break;
        case FEE_STATUS_BUSY:
            break;
        case FEE_STATUS_NG:
        default:
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
            break;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MoveData_DoPrepSrchMoveRecord                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    Fee_Record_StateScMsStart();
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHMDT;

    return FEE_STATUS_CONT;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理(転送元データ検索中)                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中(定期処理終了)       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送完了                   */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中(再実行可能)         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingMoveRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tSearchActStatus;
    uint32          u4tSearchExecResult;

    /* データ転送用有効データ検索 */
    u4tSearchActStatus = Fee_Record_StateScMsExec( ptstCPUDTFInfo, &u4tSearchExecResult );
    /* 「検索中」の場合 */
    if ( u4tSearchActStatus == FEE_STATUS_EXIT )
    {
        /* 戻り値に「転送中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else if ( u4tSearchActStatus == FEE_STATUS_DONE )
    {
        /* 「データあり」の場合 */
        if ( u4tSearchExecResult == FEE_STATUS_OK )
        {
            /* ID指定データ読出し先アドレスにデータ転送時書込み先アドレスを設定 */
            ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
            /* サブ状態を「転送先データ検索準備中」に設定 */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHSDT;
            /* 戻り値に「転送中(再実行可能)」を設定 */
            u4tReturn = FEE_STATUS_CONT;
        }
        /* 「データなし」の場合 */
        else /* u4tSearchExecResult == FEE_STATUS_NG */
        {
            u4tReturn = Fee_Rebuild_QuitSuccess( ptstCPUDTFInfo );
        }
    }
    else /* u4tSearchActStatus == FEE_STATUS_NG */
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}


/****************************************************************************/
/* Function Name | Fee_MoveData_DoPrepSrchDestRecord                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoPrepSrchDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    Fee_Record_StateScMdStart();
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMSRCHSDT;

    return FEE_STATUS_CONT;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理(転送先データ検索中)                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中(定期処理終了)       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送完了                   */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中(再実行可能)         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoSrchingDestRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tSearchActStatus;
    uint32          u4tSearchExecResult;
    boolean         btCheckWriteSpaceResult;

    /* データ読み出し用データ検索 */
    u4tSearchActStatus = Fee_Record_StateScMdExec( ptstCPUDTFInfo, &u4tSearchExecResult );
    /* 「処理継続中」の場合 */
    if ( u4tSearchActStatus == FEE_STATUS_EXIT )
    {
        /* 戻り値に「転送中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else if ( u4tSearchActStatus == FEE_STATUS_DONE )
    {
        /* 「有効データあり」の場合 */
        if ( u4tSearchExecResult == FEE_STATUS_OK )
        {
            /* データ転送時転送元アドレスを１レコード分デクリメント */
            ptstCPUDTFInfo->u4MoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
            /* サブ状態を「転送元データ検索準備中」に設定 */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
            /* On the way to execution */
            u4tReturn = FEE_STATUS_EXIT;
        }
        /* 「データなし」or「無効データあり」の場合 */
        else /* u4tSearchExecResult == FEE_STATUS_INVALID, FEE_STATUS_NG */
        {
            btCheckWriteSpaceResult = Fee_Record_CheckWriteSpace( ptstCPUDTFInfo->u2MovDataLen,
                                                                  (uint16)(ptstCPUDTFInfo->u1SubBlockNo),
                                                                  ptstCPUDTFInfo );
            /* 書込み位置の空きがある場合 */
            if ( btCheckWriteSpaceResult == (boolean)TRUE )
            {
                Fee_Record_StateWtMvStart( ptstCPUDTFInfo );

                /* サブ状態を「データ書き込み中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMWRITE;
                /* 戻り値に「転送中(定期処理終了)」を設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* 書込み位置の空きがない場合 */
            else
            {
                u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
            }
        }
    }
    else /* u4tSearchActStatus == FEE_STATUS_NG */
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }

    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送状態管理(データ書き込み中)                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：転送中(定期処理終了)       */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：転送完了                   */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：転送中(再実行可能)         */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MoveData_DoMovingRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */

    /* データ書込み中共通処理 */
    u4tResult = Fee_Record_StateWtMvExec( ptstCPUDTFInfo );
    /* 「処理継続中」の場合 */
    if ( u4tResult == FEE_STATUS_EXIT )
    {
        /* 戻り値に「転送中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* 「書込み終了」の場合 */
    else if ( u4tResult == FEE_STATUS_DONE )
    {
        /* データ転送時転送元アドレスを１レコード分デクリメント */
        ptstCPUDTFInfo->u4MoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
        /* サブ状態を「転送元データ検索準備中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMPREPSRCHMDT;
        /* 戻り値に「転送中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* 「書込み失敗」の場合 */
    else
    {
        u4tReturn = Fee_Rebuild_QuitFailure( ptstCPUDTFInfo );
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Rebuild_QuitSuccess                                  */
/* Description   | Function to execute process when rebuilding is quit      */
/*               | successfully.                                            */
/* Preconditions |                                                          */
/* Parameters    | ptstCPUDTFInfo   : Job information.                      */
/* Return Value  | Next status.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitSuccess(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
){
    /* Set the job result. */
    CPUDTFInfo->u1Result = FEE_RSP_OK;

    /* Set next statuses */
    CPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
    CPUDTFInfo->u1SubStatus = FEE_SSTATUSWSWEMOV;
    CPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEIDLE;

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Rebuild_QuitFailure                                  */
/* Description   | Function to execute process when rebuilding is quit      */
/*               | unsuccessfully.                                          */
/* Preconditions |                                                          */
/* Parameters    | ptstCPUDTFInfo   : Job information.                      */
/* Return Value  | Next status.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Rebuild_QuitFailure(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, TYPEDEF ) CPUDTFInfo
){
    /* Initialize the record position table. */
    Fee_RecordPosTbl_ClearPosArea( CPUDTFInfo->u1AreaNum );

    /* Set the job result. */
    CPUDTFInfo->u1Result = FEE_RSP_NG;

    /* Set next statuses */
    CPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
    CPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    CPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSUSD;

    return FEE_STATUS_EXIT;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/15                                              */
/*  2-0-0          :2021/07/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
