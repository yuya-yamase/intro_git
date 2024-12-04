/* Fee_Hook.c v1-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/HOOK/CODE                                             */
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
#include "../inc/Fee_Hook_Internal.h"

/* D.F.C.ヘッダ */
#include "../inc/Fee_Dfc.h"

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
/* 説  明        ：応答Hook呼び出し共通処理                                   */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_RspHook( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo)
{
    uint8   u1tProcessStatus;   /* 動作状態 */
    uint8   u1tResult;          /* 処理成否 */
    uint16  u2tDATA_ID;         /* DATA-ID */
    uint8   u1tAreaNum;         /* エリア番号 */

    /* 動作状態取り出し */
    u1tProcessStatus = ptstCPUDTFInfo->u1ProcessStatus;
    /* 処理結果取り出し */
    u1tResult = ptstCPUDTFInfo->u1Result;
    /* DATA-ID取り出し */
    u2tDATA_ID = ptstCPUDTFInfo->u2DATA_ID;
    /* エリア番号取り出し */
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    /* 最終書込みレコード位置 */
    if ( ptstCPUDTFInfo->u1LastWritePosFlag == FEE_FLAG_ON )
    {
        /* 最終書込みレコード位置更新許可フラグが更新可 */
        /* 最終書込みレコード位置保存処理 */
        /* Return value is not checked. */
        (void)Fee_SetLastWritePos( ptstCPUDTFInfo );
    }

    /* MHA[データFlash]管理データ初期化 */
    Fee_InitCpuDtfData( ptstCPUDTFInfo );

    /* 動作状態別の応答Hook呼び出し */
    Fee_CallRspHook( u1tProcessStatus, u1tResult, u2tDATA_ID, u1tAreaNum );
    
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：応答Hook呼び出し                                           */
/* 入  力        ：uint8 u1tProcessStatus   ：動作状態                        */
/*               ：uint8 u1tResult          ：処理成否                        */
/*               ：uint16 u2tDATA_ID        ：DATA-ID                         */
/*               ：uint8 u1tAreaNum         ：エリア番号                      */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_CallRspHook(
    uint8   u1tProcessStatus,
    uint8   u1tResult,
    uint16  u2tDATA_ID,
    uint8   u1tAreaNum
){
    switch( u1tProcessStatus )
    {
        case FEE_STATUSWRITE:   /* 書込み中(STATUS_WRITE) */
            /* データ書込み応答Hook */
            Fee_Write_Rsp_Hook( u1tResult, u2tDATA_ID, u1tAreaNum );
            break;

        case FEE_STATUSIDREAD:  /* ID指定データ読出し中(STATUS_IDREAD) */
            /* データ読出し応答Hook(ID指定) */
            Fee_Read_Rsp_Hook( u1tResult, u2tDATA_ID, u1tAreaNum );
            break;

        case FEE_STATUSMOVE:    /* データ再編中(STATUS_MOVE) */
            /* データ再編応答Hook */
            Fee_Rebuild_Rsp_Hook( u1tResult, u1tAreaNum );
            break;

        default:                /* 動作状態がそれ以外(ありえない) */
            /* No process */
            break;
    }

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
