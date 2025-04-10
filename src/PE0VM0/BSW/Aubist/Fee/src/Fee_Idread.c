/* Fee_Idread.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/IDREAD/CODE                                           */
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
#include "../inc/Fee_Idread_Internal.h"

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
/* 説  明        ：ID指定データ読出し状態管理                                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：読出し中                   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：処理終了                   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_ReadMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* 戻り値を処理継続に設定 */
    u4tReturn = FEE_STATUS_CONT;
    while ( u4tReturn == FEE_STATUS_CONT )
    {
        /* 処理継続の間は処理を続ける */
        /* メイン状態により分岐 */
        switch ( ptstCPUDTFInfo->u1MainStatus )
        {
            case FEE_MSTATUSRIDLE:                  /* メイン状態がアイドル(MAIN_STATUS_R_IDLE)の場合 */
                u4tReturn = Fee_ReadMainSelectReadBlock( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRBSRCH:                 /* メイン状態が空き領域検索中(MAIN_STATUS_R_BSRCH)の場合 */
                u4tReturn = Fee_ReadMainSrchFreeSpace( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRPREPISRCH:             /* メイン状態がID指定データ読出し準備中の場合 */
                u4tReturn = Fee_ReadMainPrepSrchReadData( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRISRCH:                 /* メイン状態がID指定データ読出し中(MAIN_STATUS_R_ISRCH)の場合 */
                u4tReturn = Fee_ReadMainSrchReadData( ptstCPUDTFInfo );
                break;

            default:                                            /* メイン状態がそれ以外の場合 */
                /* 処理結果を該当データなし(RSP_NODATA)に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
                /* 戻り値を処理終了に設定 */
                u4tReturn = FEE_STATUS_DONE;
                break;
        }
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ID指定データ読出し状態管理(アイドル)                       */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：読出し中                   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：処理終了                   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_ReadMainSelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tSelResult;                               /* 読出しブロック選択処理結果 */
    uint32          u4tRcrdDataAreaStartAbsAddr;
    uint32          u4tBlockStartAddr;

    /* 読出しブロック選択処理 */
    u4tSelResult = Fee_SelectReadBlock( ptstCPUDTFInfo );
    if ( u4tSelResult == FEE_STATUS_OK )
    {
        /* 選択成功の場合 */
        /* 最終書込みレコード位置は有効か？*/
        if ( ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr != FEE_ADDRESS_INVALID )
        {
            /* 最終書込みレコード位置が有効の場合 */
            /* 読出し検索開始アドレスを最終書込みレコード位置に設定 */
            ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;

            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRPREPISRCH;
        }
        else
        {
            /* 最終書込みレコード位置が無効の場合 */
            /* 読出し検索開始アドレスをブロックの最終レコードに設定 */
            u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
            u4tRcrdDataAreaStartAbsAddr = u4tBlockStartAddr
                                          + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr );
            ptstCPUDTFInfo->u4ReadSrchAddress = u4tRcrdDataAreaStartAbsAddr - (uint32)FEE_RECORDMNGINFOLEN;

            /* メイン状態を空き領域検索中(MAIN_STATUS_R_BSRCH)に設定 */
            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRBSRCH;
        }
        /* 戻り値を処理継続に設定 */
        u4tReturn = FEE_STATUS_CONT;
    }
    else if ( u4tSelResult == FEE_STATUS_NODATA )
    {
        /* 全ブロック未使用の場合 */
        /* 処理結果をブロック未使用(RSP_UNUSED)に設定 */
        ptstCPUDTFInfo->u1Result = FEE_RSP_UNUSED;
        /* 戻り値を処理終了に設定 */
        u4tReturn = FEE_STATUS_DONE;
    }
    else
    {
        /* それ以外：選択失敗の場合 */
        /* 処理結果を該当データなし(RSP_NODATA)に設定 */
        ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
        /* 戻り値を処理終了に設定 */
        u4tReturn = FEE_STATUS_DONE;
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ID指定データ読出し状態管理(空き領域検索中)                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：読出し中                   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：処理終了                   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tSrchFSResult;                            /* 空き領域検索結果 */

    /* 空き領域検索処理 */
    u4tSrchFSResult = Fee_SrchFreeSpace( ptstCPUDTFInfo );
    /* 戻り値により分岐 */
    switch ( u4tSrchFSResult )
    {
        case FEE_STATUS_OK:             /* 戻り値が使用中(STATUS_OK)の場合 */
            /* 末尾レコード保持データ更新許可フラグを許可(FLAG_ON)に設定 */
            ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
            /* データ書込み時・転送時書込み先アドレスに検索結果アドレスを設定 */
            ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;

            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRPREPISRCH;
            /* 戻り値を処理継続に設定 */
            u4tReturn = FEE_STATUS_CONT;
            break;

        case FEE_STATUS_NG:             /* 戻り値が未使用(STATUS_NG)の場合 */
            /* 末尾レコード保持データ更新許可フラグを許可(FLAG_ON)に設定 */
            ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
            /* データ書込み時・転送時書込み先アドレスに検索結果アドレスを設定 */
            ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;
            /* 処理結果を該当データなし(RSP_NODATA)に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
            /* 戻り値を処理終了に設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;

        case FEE_STATUS_BUSY:           /* 戻り値が処理継続中(STATUS_BUSY)の場合 */
            /* 戻り値を読出し中(STATUS_EXIT)に設定 */
            u4tReturn = FEE_STATUS_EXIT;
            break;

        default:                                    /* それ以外 */
            /* 処理結果を該当データなし(RSP_NODATA)に設定 */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
            /* 戻り値を処理終了に設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ReadMainPrepSrchReadData                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMainPrepSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    Fee_Record_StateScRdStart();
    /* メイン状態をID指定データ読出し中(MAIN_STATUS_R_ISRCH)に設定 */
    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRISRCH;

    return FEE_STATUS_CONT;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ID指定データ読出し状態管理(ID指定データ読出し中)           */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：読出し中                   */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：処理終了                   */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tReadActStatus;
    uint32          u4tReadExecResult;

    u4tReadActStatus = Fee_Record_StateScRdExec( ptstCPUDTFInfo, &u4tReadExecResult );
    switch ( u4tReadActStatus )
    {
        case FEE_STATUS_EXIT:
            u4tReturn = FEE_STATUS_EXIT;
            break;

        case FEE_STATUS_DONE:
            switch ( u4tReadExecResult )
            {
                case FEE_STATUS_OK:
                    ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
                    break;
                case FEE_STATUS_INVALID:
                case FEE_STATUS_NG:
                default:
                    ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
                    break;
            }
            u4tReturn = FEE_STATUS_DONE;
            break;

        case FEE_STATUS_NG:
        default:
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
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
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2021/07/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

