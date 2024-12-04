/* Fee_Mngdfc.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MNGDFC/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Mngdfc_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_PifExt.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* データFlash制御管理データ関連定義 */
/* データFlash制御状態 */
#define FEE_MNGDFCIDLE      ((uint8)0x00U)      /* アイドル */
#define FEE_MNGDFCWRITE     ((uint8)0x01U)      /* 書込み中 */
#define FEE_MNGDFCERASE     ((uint8)0x02U)      /* 消去中 */
#define FEE_MNGDFCBLANKCHK  ((uint8)0x03U)      /* ブランクチェック中 */
/* 連続書込み用フラグ設定値(エラー発生フラグ) */
#define FEE_CWFLG_DFCERRSTS ((uint16)0x0080U)   /* DFCエラー発生 */
#define FEE_CWFLG_VRFYERRSTS    ((uint16)0x0040U)   /* ベリファイエラー発生 */
/* バッファインデックス値0(ブランクチェック・消去用) */
#define FEE_CWINDEXINIT     ((uint8)0x00U)      /* インデックス0 */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_CWFLG_INIT       ((uint16)0x0000U)  /* フラグ初期値   */
#define FEE_CWNUMINIT        ((uint8)0x00U)    /* データ個数初期値 */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_MngDfc_CheckRAM                                      */
/* Description   | Function to check RAMs.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_MngDfc_CheckRAM( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;
    uint32         Counter;

    if((( Fee_MngDfcInfo.u1MngDFCStatus ^ Fee_MngDfcInfoSub.u1MngDFCStatus ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1CWriteIndex  ^ Fee_MngDfcInfoSub.u1CWriteIndex  ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1CWriteNum    ^ Fee_MngDfcInfoSub.u1CWriteNum    ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1RetryFlag    ^ Fee_MngDfcInfoSub.u1RetryFlag    ) == (uint8)FEE_MIRROR_CHECK_UINT8 ))
    {
        Rtn = E_OK;
        for ( Counter = 0U; Counter < (uint32)FEE_CWRITE_MAX; Counter++ )
        {
            if((( Fee_MngDfcInfo.u2CWriteDataLength[Counter]         ^ Fee_MngDfcInfoSub.u2CWriteDataLength[Counter]         ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u2CWriteAddrOffset[Counter]         ^ Fee_MngDfcInfoSub.u2CWriteAddrOffset[Counter]         ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u2CWriteFlag[Counter]               ^ Fee_MngDfcInfoSub.u2CWriteFlag[Counter]               ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u4CWriteAddrBuf[Counter]            ^ Fee_MngDfcInfoSub.u4CWriteAddrBuf[Counter]            ) != (uint32)FEE_MIRROR_CHECK_UINT32 )
            || (  Fee_MngDfcInfo.ptu1CWriteDataAddr[Counter]        != Fee_MngDfcInfoSub.ptu1CWriteDataAddr[Counter] ))
            {
                Rtn = E_NOT_OK;
                break;
            }
        }
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_SetRAMSub                                     */
/* Description   | Function to set value to sub RAMs from main RAMs.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_MngDfc_SetRAMSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    uint32 Counter;

    Fee_MngDfcInfoSub.u1MngDFCStatus = (uint8)(~Fee_MngDfcInfo.u1MngDFCStatus);
    Fee_MngDfcInfoSub.u1CWriteIndex  = (uint8)(~Fee_MngDfcInfo.u1CWriteIndex);
    Fee_MngDfcInfoSub.u1CWriteNum    = (uint8)(~Fee_MngDfcInfo.u1CWriteNum);
    Fee_MngDfcInfoSub.u1RetryFlag    = (uint8)(~Fee_MngDfcInfo.u1RetryFlag);
    for ( Counter = 0U; Counter < (uint32)FEE_CWRITE_MAX; Counter++ )
    {
        Fee_MngDfcInfoSub.u2CWriteDataLength[Counter] = (uint16)(~Fee_MngDfcInfo.u2CWriteDataLength[Counter]);
        Fee_MngDfcInfoSub.u2CWriteAddrOffset[Counter] = (uint16)(~Fee_MngDfcInfo.u2CWriteAddrOffset[Counter]);
        Fee_MngDfcInfoSub.u2CWriteFlag[Counter]       = (uint16)(~Fee_MngDfcInfo.u2CWriteFlag[Counter]);
        Fee_MngDfcInfoSub.u4CWriteAddrBuf[Counter]    = (uint32)(~Fee_MngDfcInfo.u4CWriteAddrBuf[Counter]);
        Fee_MngDfcInfoSub.ptu1CWriteDataAddr[Counter] = Fee_MngDfcInfo.ptu1CWriteDataAddr[Counter];
    }
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：定期処理用データFlash制御管理                              */
/* 入  力        ：なし                                                       */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000005 ：FEE_STATUS_BUSY ：処理中             */
/*               ：  0x00000003 ：FEE_STATUS_DONE ：動作完了           */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MngDfcForPrd( void )
{
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tMngDFCResult;                    /* データFlash制御管理共通処理結果 */

    /* データFlash制御管理共通処理呼び出し */
    u4tMngDFCResult = Fee_MngDfcCom();
    if ( u4tMngDFCResult == FEE_STATUS_DONE )
    {
        /* データFlash制御管理共通処理結果が動作完了 */
        if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCWRITE )
        {
            /* データFlash制御状態が書込み中 */
            Fee_MngDfcEndWriteProcess();
            /* 戻り値を動作完了に設定 */
            u4tReturn = FEE_STATUS_DONE;
        }
        else if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCBLANKCHK )
        {
            /* データFlash制御状態がブランクチェック中 */
            Fee_MngDfcEndBlanckCheckProcess();
            /* 戻り値を動作完了に設定 */
            u4tReturn = FEE_STATUS_DONE;
        }
        else
        {
            /* データFlash制御状態がその他(消去) */
            Fee_MngDfcEndEraseProcess();
            /* 戻り値を動作完了に設定 */
            u4tReturn = FEE_STATUS_DONE;
        }
    }
    else if ( u4tMngDFCResult == FEE_STATUS_EXIT )
    {
        /* データFlash制御管理共通処理結果が処理中 */
        /* 戻り値を処理中に設定 */
        u4tReturn = FEE_STATUS_BUSY;
    }
    else
    {
        /* データFlash制御管理共通処理結果がその他(アイドル) */
        /* 戻り値を動作完了に設定 */
        u4tReturn = FEE_STATUS_DONE;
    }

    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash制御管理書き込み終了処理                        */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_MngDfcEndWriteProcess( void )
{
    uint32          u4tCounter;                         /* カウンタ */
    uint32          u4tCWriteNum;                       /* 連続書込みデータ数 */
    uint32          u4tCWriteAddress;                   /* 連続書込みアドレス */
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1WriteDataAddr;                       /* データ比較用ポインタ */
    uint8           u1tCompareResult;

    /* データFlash制御状態が書込み中 */
    /* Flash操作終了(この後ベリファイをするため、Flash操作終了を先に行う) */
    Fee_Dfc_End();
    /* 連続書込みデータ数を取り出す */
    u4tCWriteNum = (uint32)Fee_MngDfcInfo.u1CWriteNum;
    for ( u4tCounter = 0U; u4tCounter < u4tCWriteNum; u4tCounter++ )
    {
        if ( ( Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] & FEE_CWFLG_VRFYERRCHK ) == FEE_CWFLG_VRFYERRCHK )
        {
            /* ベリファイ要求がある場合、ベリファイ実施 */
            u4tCWriteAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCounter] );
            ptu1WriteDataAddr = Fee_MngDfcInfo.ptu1CWriteDataAddr[u4tCounter];
            u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( u4tCWriteAddress, ptu1WriteDataAddr );
            if( u1tCompareResult != FEE_DFCMPU_RESULT_OK )
            {
                /* ベリファイエラーの場合、ベリファイエラーフラグ設定 */
                Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] |= FEE_CWFLG_VRFYERRSTS;
                Fee_PifExt_WriteVerifyFailedNotification();
            }
        }
    }
    /* データFlash制御状態をアイドルに設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash制御管理ブランクチェック終了処理                */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_MngDfcEndBlanckCheckProcess( void )
{
    uint32          u4tBlankchkAddress;                 /* ブランクチェックで検出した非ブランクアドレス */

    /* データFlash制御状態がブランクチェック中 */
    /* エラー確認 */
    if ( ( Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] & FEE_CWFLG_DFCERRSTS ) == FEE_CWFLG_DFCERRSTS )
    {
        /* エラー発生時 */
        /* FLAP取得関数 */
        u4tBlankchkAddress = Fee_Dfc_GetFLAP();
        /* 連続書込み用アドレスバッファに設定 */
        Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] = Fee_ConvAddr_AbsToBaseRelative( u4tBlankchkAddress );
    }
    /* Flash操作終了 */
    Fee_Dfc_End();
    /* データFlash制御状態をアイドルに設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash制御管理消去終了処理                            */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_MngDfcEndEraseProcess( void )
{
    /* データFlash制御状態がその他(消去) */
    /* Flash操作終了 */
    Fee_Dfc_End();
    /* データFlash制御状態をアイドルに設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;
    
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash制御管理共通処理                                */
/* 入  力        ：なし                                                       */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000002 ：FEE_STATUS_EXIT ：処理中             */
/*               ：  0x00000003 ：FEE_STATUS_DONE ：動作完了           */
/*               ：  0x00000004 ：FEE_STATUS_CONT ：アイドル           */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_MngDfcCom( void )
{
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tDFCResult;                       /* ステータスチェック結果 */
    
    /* ステータスチェック */
    u4tDFCResult = Fee_MngDfc_ExecDfcAndCheckStatus();
    if ( u4tDFCResult == FEE_DFC_STATUS_BUSY )
    {
        /* BUSYの場合 */
        /* 戻り値を処理中に設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else
    {
        if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCIDLE )
        {
            /* データFlash制御状態がアイドル */
            /* 戻り値をアイドルに設定 */
            u4tReturn = FEE_STATUS_CONT;
        }
        else
        {
            if ( u4tDFCResult != FEE_DFC_STATUS_OK )
            {
                /* チェック結果が正常終了でない場合 */
                /* D.F.C.エラー発生フラグを設定 */
                Fee_MngDfcInfo.u2CWriteFlag[Fee_MngDfcInfo.u1CWriteIndex] |= FEE_CWFLG_DFCERRSTS;
            }
            if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCWRITE )
            {
                if( Fee_MngDfcInfo.u1RetryFlag == FEE_FLAG_ON )
                {
                    u4tReturn = Fee_MngDfcComRetry();
                }
                else
                {
                    if ( ( Fee_MngDfcInfo.u1CWriteIndex + (uint8)FEE_NEXT_CWRITENUM_OFFSET ) < Fee_MngDfcInfo.u1CWriteNum )
                    {
                        u4tReturn = Fee_MngDfcComCWrite( u4tDFCResult );
                    }
                    else
                    {
                        u4tReturn = FEE_STATUS_DONE;
                    }
                }
            }
            else
            {
                /* データFlash制御状態がその他(消去中かブランクチェック中) */
                /* 戻り値を動作完了に設定 */
                u4tReturn = FEE_STATUS_DONE;
            }
        }
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcComCWrite                                      */
/* Description   | Function to write continuity.                            */
/* Preconditions | None                                                     */
/* Parameters    | u4tDFCResult                                             */
/* Return Value  | FEE_STATUS_EXIT : On the way to execution                */
/*               | FEE_STATUS_DONE : The write was complete                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcComCWrite(
    uint32 u4tDFCResult
){
    uint32          u4tReturn;

    /* Next data exist  */
    if ( ( u4tDFCResult != FEE_DFC_STATUS_OK )
      && ( ( Fee_MngDfcInfo.u2CWriteFlag[Fee_MngDfcInfo.u1CWriteIndex] & FEE_CWFLG_ERRSTOP ) == FEE_CWFLG_ERRSTOP ) )
    {
        u4tReturn = FEE_STATUS_DONE;
    }
    else
    {
        Fee_MngDfcInfo.u1CWriteIndex++;
        Fee_MngDfcReqWrite();

        u4tReturn = FEE_STATUS_EXIT;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcComRetry                                       */
/* Description   | Function to retry to write.                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | FEE_STATUS_EXIT : On the way to execution                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcComRetry( void )
{
    Fee_MngDfcReqWrite();

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcReqWrite                                       */
/* Description   | Function to request writing.                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_MngDfcReqWrite( void )
{
    uint32          u4tAddress;
    P2CONST( uint8, AUTOMATIC, TYPEDEF )    ptu1Data;
    uint16          u2tLength;
    uint16          u2tOffset;
    uint16          u2tFlag;
    uint8           u1tIndex;

    u1tIndex = Fee_MngDfcInfo.u1CWriteIndex;
    u2tLength = Fee_MngDfcInfo.u2CWriteDataLength[u1tIndex];
    u2tOffset = Fee_MngDfcInfo.u2CWriteAddrOffset[u1tIndex];
    u4tAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u1tIndex] );
    u4tAddress += (uint32)u2tOffset;

    ptu1Data = &Fee_MngDfcInfo.ptu1CWriteDataAddr[u1tIndex][u2tOffset];
    u2tFlag = Fee_MngDfcInfo.u2CWriteFlag[u1tIndex];

    Fee_MngDfc_VolChkWrite( u4tAddress, ptu1Data, u2tLength, u2tFlag );

    return;
}


/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：連続書込み用バッファ追加処理                               */
/* 入  力        ：uint32 u4Address ：データFlash書込み先アドレス             */
/*               ：uint32 u4Data    ：書込みデータ                            */
/*               ：uint16 u2Length  ：書き込むデータ長                        */
/*               ：uint16 u2OffSet  ：u4Dataの先頭からのオフセット            */
/*               ：                   オフセットからu2Length分データを書き込む*/
/*               ：uint16 u2Flg     ：連続書込み用フラグ設定値                */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_AddCWriteBuf( uint32 u4Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Src, uint16 u2Length, uint16 u2OffSet, uint16 u2Flg )
{
    uint8           u1tIndex;                           /* 書込み位置 */
    
    /* 連続書込みデータ数を書込み位置とする */
    u1tIndex = Fee_MngDfcInfo.u1CWriteNum;
    
    /* 連続書込み用アドレスバッファ設定 */
    Fee_MngDfcInfo.u4CWriteAddrBuf[u1tIndex] = Fee_ConvAddr_AbsToBaseRelative( u4Address );

    /* 連続書込み用データアドレス設定 */
    Fee_MngDfcInfo.ptu1CWriteDataAddr[u1tIndex] = ptu1Src;

    /* Set Write Data length */
    Fee_MngDfcInfo.u2CWriteDataLength[u1tIndex] = u2Length;
    /* Set Write Addr Offset */
    Fee_MngDfcInfo.u2CWriteAddrOffset[u1tIndex] = u2OffSet;

    /* 連続書込み用フラグ設定 */
    Fee_MngDfcInfo.u2CWriteFlag[u1tIndex] = u2Flg;
    /* 連続書込みデータ数をインクリメント */
    Fee_MngDfcInfo.u1CWriteNum++;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：連続書込み開始処理                                         */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_StartCWrite( void )
{
    uint32          u4tAddress;                         /* アドレス */
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptu1Src;                            /* データポインタ */
    uint16          u2tLength;                          /* Data Length */
    uint16          u2tOffset;                          /* Addr Offset */

    u2tLength = Fee_MngDfcInfo.u2CWriteDataLength[FEE_CWINDEXINIT];
    u2tOffset = Fee_MngDfcInfo.u2CWriteAddrOffset[FEE_CWINDEXINIT];
    /* データFlash制御管理データから書込みデータを取り出す(インデックス=0) */
    /* 連続書込み用アドレス[0] */
    u4tAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] );
    u4tAddress += (uint32)u2tOffset;

    /* 連続書込み用データ */
    ptu1Src = &Fee_MngDfcInfo.ptu1CWriteDataAddr[FEE_CWINDEXINIT][u2tOffset];

    Fee_MngDfc_VolChkWrite( u4tAddress, ptu1Src, u2tLength, Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] );
    /* データFlash制御状態を書込み中に設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCWRITE;

    return;
}
/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：消去開始処理                                               */
/* 入  力        ：uint8 u1BlockNo ：消去ブロック番号                            */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_StartErase( uint8 u1BlockNo )
{
    uint32          u4tAddress;                         /* アドレス */

    /* アドレス計算 */
    u4tAddress = FEE_BLKSTARTADDRTBL[u1BlockNo];

    /* 連続書込み用バッファ初期化処理 */
    Fee_ClearCWriteBuf();
    /* 消去関数呼び出し */
    Fee_Dfc_Erase( u4tAddress );
    /* データFlash制御状態を消去中に設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCERASE;

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：ブランクチェック開始処理                                   */
/*  引数        : uint32 StartTailAddress : ブランクチェック開始アドレス      */
/*              : uint32 EndTopAddress    : ブランクチェック終了アドレス      */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_StartBlankCheck( uint32 u4StartTailAddress, uint32 u4EndTopAddress )
{
    /* 連続書込み用バッファ初期化処理 */
    Fee_ClearCWriteBuf();
    /* ブランクチェック関数呼び出し */
    Fee_Dfc_BlankCheck( u4StartTailAddress, u4EndTopAddress, Fee_MaxBlankCheckNumber );
    /* データFlash制御状態をブランクチェック中に設定 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCBLANKCHK;

    return;
}
/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：連続書込み用バッファ初期化処理                             */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_ClearCWriteBuf( void )
{
    uint32          u4tCounter;                         /* カウンタ */

    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_CWRITE_MAX; u4tCounter++ )
    {
        /* 連続書込み用アドレスバッファ初期化 */
        Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCounter] = FEE_ADDRESS_INVALID;

        /* 連続書込み用データアドレス初期化 */
        Fee_MngDfcInfo.ptu1CWriteDataAddr[u4tCounter]= NULL_PTR;
        /* 連続書込み用フラグ初期化 */
        Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] = FEE_CWFLG_INIT; /* 0x00U で初期化 */
        Fee_MngDfcInfo.u2CWriteDataLength[u4tCounter] = FEE_LENGTH_INVALID;   /* DataLength Initialize */
        Fee_MngDfcInfo.u2CWriteAddrOffset[u4tCounter] = FEE_CWOFFSET_INVALID; /* Address Offset Initialize */
    }

    /* データFlash制御状態初期化 */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;
     
    /* 連続書込み用バッファのインデックス初期化 */
    Fee_MngDfcInfo.u1CWriteIndex = FEE_CWINDEXINIT;
    /* 連続書込みデータ数初期化 */
    Fee_MngDfcInfo.u1CWriteNum = FEE_CWNUMINIT;

    Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_OFF;

    return;
}
/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash制御結果取得処理                                */
/* 入  力        ：uint32 *ptu4Address  ：書込み最終/ブランクエラーアドレス*/
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000000 ：FEE_STATUS_OK ：エラーなし       */
/*               ：  0x00000001 ：FEE_STATUS_NG ：エラーあり       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_GetMngDfcResult( P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4Address )
{
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tCounter;                         /* カウンタ */
    uint32          u4tCWriteNum;                       /* 連続書込みデータ数 */
    uint16          u2tCWriteFlag;                      /* 連続書込み用フラグ */

    /* 戻り値をエラーなしで初期化 */
    u4tReturn = FEE_STATUS_OK;
    /* 連続書込みデータ数を取り出す */
    u4tCWriteNum = Fee_MngDfcInfo.u1CWriteNum;

    if ( u4tCWriteNum == (uint32)FEE_CWRITENUM_ZERO )
    {
        /* 連続書込み数=0：消去・ブランクチェック中の場合 */
        if ( (Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] & FEE_CWFLG_DFCERRSTS ) == FEE_CWFLG_DFCERRSTS )
        {
            /* エラーフラグONの場合 */
            /* 戻り値をエラーありに設定 */
            u4tReturn = FEE_STATUS_NG;
            /* ブランクチェックアドレスを取り出す */
            if ( ptu4Address != NULL_PTR )
            {
                *ptu4Address = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] );
            }
        }
        else
        {
            /* 無効アドレス設定 */
            if ( ptu4Address != NULL_PTR )
            {
                *ptu4Address = FEE_ADDRESS_INVALID;
            }
        }
    }
    else
    {
        /* 書込み中の場合 */
        for ( u4tCounter = 0U; ( u4tCounter < u4tCWriteNum ) && ( u4tReturn == FEE_STATUS_OK ); u4tCounter++ )
        {
            /* 連続書込み用フラグ取得 */
            u2tCWriteFlag = Fee_MngDfcInfo.u2CWriteFlag[u4tCounter];
            if ( ( ( u2tCWriteFlag & FEE_CWFLG_VRFYERRSTS ) == FEE_CWFLG_VRFYERRSTS )
              || ( ( u2tCWriteFlag & ( FEE_CWFLG_DFCERRCHK | FEE_CWFLG_DFCERRSTS ) )
                == ( FEE_CWFLG_DFCERRCHK | FEE_CWFLG_DFCERRSTS ) ) )
            {
                /* 確認が必要なエラー種別がエラーの場合 */
                /* ベリファイチェックの結果は確認が必要なときのみ設定されている */
                /* 戻り値をエラーありに設定 */
                u4tReturn = FEE_STATUS_NG;
            }
        }
        /* 最終書込みアドレスを取り出す */
        if ( ptu4Address != NULL_PTR )
        {
            *ptu4Address = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCWriteNum - (uint32)FEE_CWRITE_LAST_INDEX_OFFSET] );
        }
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_ExecDfcAndCheckStatus                         */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  |                                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_MngDfc_ExecDfcAndCheckStatus( void )
{
    uint32 Rtn;

    Rtn = Fee_Dfc_ExecFlsMainFunction();

    if( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCBLANKCHK )
    {
        Rtn = Fee_Dfc_ExecBlankCheck();
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_VolChkWrite                                   */
/* Description   | Function to check voltage and write.                     */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | ptu1Data                                                 */
/*               | u2Len                                                    */
/*               | u2Flag                                                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_MngDfc_VolChkWrite(
    const uint32 u4Address,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data,
    const uint16 u2Len,
    const uint16 u2Flag
){
    Std_ReturnType srVolChkResult = E_OK;

    if(( u2Flag & FEE_CWFLG_VOLMINCHK ) == FEE_CWFLG_VOLMINCHK )
    {
        srVolChkResult = Mscd_Cnfm_CheckWcWriteHook();
    }

    if( srVolChkResult == (Std_ReturnType)E_OK )
    {
        Fee_Dfc_Write( u4Address, ptu1Data, u2Len );

        Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_OFF;
    }
    else
    {
        Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_ON;
    }

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
