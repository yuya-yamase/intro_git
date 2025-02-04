/* Fee_Write.c v1-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/WRITE/CODE                                            */
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
/* 説  明        ：データ書込み状態管理（ブロック管理機能あり）               */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：データ書込み中・継続不可   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：データ書込み終了           */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：データ書込み中・継続可     */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_BWriteMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */

    /* メイン状態により分岐 */
    switch ( ptstCPUDTFInfo->u1MainStatus )
    {
        case FEE_MSTATUSWBIDLE:                 /* メイン状態がアイドル(MAIN_STATUS_W_B_IDLE)の場合 */
            /* メイン状態をブロック選択中(MAIN_STATUS_W_B_SEL)に設定 */
            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
            /* ブロックカウンタクリア */
            ptstCPUDTFInfo->u4BlockCount = 0U;
            /* サブ状態を「ブロックステータスデータ確定中」に設定 */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFIX;
            /* ブロックステータスデータ確定中にはサブサブ状態がないため、設定しない */
            /* 戻り値をデータ書込み中・継続可に設定 */
            u4tReturn = FEE_STATUS_CONT;
            break;

        case FEE_MSTATUSWBSEL:                  /* メイン状態が書込みブロック選択中(MAIN_STATUS_W_B_SEL)の場合 */
            /* 書込みブロック選択状態管理処理 */
            u4tReturn = Fee_SelectWriteBlock( ptstCPUDTFInfo );
            break;

        case FEE_MSTATUSWBWRITE:                    /* メイン状態がレコード書き込み中(MAIN_STATUS_W_B_WRITE)の場合 */
            /* レコード書込み状態管理処理 */
            u4tReturn = Fee_WriteRecord( ptstCPUDTFInfo );
            break;

        case FEE_MSTATUSWBMOVE:                 /* メイン状態がデータ転送中(MAIN_STATUS_W_B_MOVE)の場合 */
            /* データ転送状態管理処理 */
            u4tReturn = Fee_MoveData( ptstCPUDTFInfo );
            break;

        default:                                            /* メイン状態がそれ以外の場合 */
            /* 有効レコード位置TBL初期化 */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
            {
                /* 動作状態が書込み(STATUS_WRITE)の場合 */
                /* 処理結果を書込み失敗(RSP_NG_WRITE_DATA)に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_WRITE_DATA;
            }
            else
            {
                /* 動作状態がそれ以外：再編の場合 */
                /* 処理結果を再編失敗(RSP_NG)に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            }
            /* 戻り値をデータ書込み終了に設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
