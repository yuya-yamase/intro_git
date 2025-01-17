/* Fee_Record.c v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Record_Internal.h"

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_Dfc_Ram.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Mpu_Const.h"
#include "../inc/Fee_Mpu_Const_Ext.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Pif.h"
#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_RECORD_SYNC_READ_MAX_SIZE ((uint16)FEE_DATA_FLASH_READ_SIZE)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

VAR( uint8,  FEE_VAR_NO_INIT ) Fee_Record_DataMatchResult;
VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_State;
VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_CompleteLen;

/* The following variables may wraparound at the point of operation */
/* Variable | Fee_Record_CheckSumVal                                */
/* Location | Fee_Record_StateWtCmAsubWtDatCs_INT30_01              */
/*          | Fee_Record_StateScOdAsubCalCSChkDat_INT30_02          */
/*          | Fee_Record_StateScRdAsubCalCSCpyDat_INT30_02          */
/*          | Fee_Record_StateScMsAsubCalCS_INT30_02                */
VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_CheckSumVal;

VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_ReadOldRcrdResult;
VAR( Fee_Record_DFlashAccessDataType, FEE_VAR_NO_INIT ) Fee_Record_Buffer;
VAR( Fee_Record_RecordInfoType,       FEE_VAR_NO_INIT ) Fee_Record_RecordInfo;

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
/* Redundancy Data */
VAR( uint8,  FEE_VAR_NO_INIT ) Fee_Record_DataMatchResultSub;
VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_StateSub;
VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_CompleteLenSub;
VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_CheckSumValSub;
VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_ReadOldRcrdResultSub;
VAR( Fee_Record_DFlashAccessDataType, FEE_VAR_NO_INIT ) Fee_Record_BufferSub;
VAR( Fee_Record_RecordInfoType,       FEE_VAR_NO_INIT ) Fee_Record_RecordInfoSub;
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Record_Init                                          */
/* Description   | Function for resetting this unit.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_Init( void )
{
    Fee_Record_State                        = FEE_RECORD_STATE_INVALID;
    Fee_Record_DataMatchResult              = FEE_RECORD_DATA_CMP_INI_MISMATCH;
    Fee_Record_CompleteLen                  = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO;
    Fee_Record_CheckSumVal                  = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    Fee_Record_RecordInfo.DataAddr          = FEE_ADDRESS_INVALID;
    Fee_Record_RecordInfo.XFlagAddr         = FEE_ADDRESS_INVALID;
    Fee_Record_RecordInfo.DataRecordLen     = FEE_LENGTH_INVALID;
    Fee_Lib_SetMemory( Fee_Record_Buffer.au1RecordData, (uint8)FEE_RECORD_PADDING_VAL, (uint32)FEE_DFLASH_ONE_TIME_WRITE_SIZE );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_CheckRAM                                      */
/* Description   | Function to check RAMs.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Record_CheckRAM( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;
    uint8          Counter;

    if((( Fee_Record_State                    ^ Fee_Record_StateSub                    ) == (uint16)FEE_MIRROR_CHECK_UINT16 )
    && (( Fee_Record_DataMatchResult          ^ Fee_Record_DataMatchResultSub          ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_Record_CompleteLen              ^ Fee_Record_CompleteLenSub              ) == (uint16)FEE_MIRROR_CHECK_UINT16 )
    && (( Fee_Record_CheckSumVal              ^ Fee_Record_CheckSumValSub              ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Record_ReadOldRcrdResult        ^ Fee_Record_ReadOldRcrdResultSub        ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Record_RecordInfo.DataAddr      ^ Fee_Record_RecordInfoSub.DataAddr      ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Record_RecordInfo.XFlagAddr     ^ Fee_Record_RecordInfoSub.XFlagAddr     ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Record_RecordInfo.DataRecordLen ^ Fee_Record_RecordInfoSub.DataRecordLen ) == (uint32)FEE_MIRROR_CHECK_UINT32 ))
    {
        Rtn = E_OK;
        for( Counter = 0U; Counter < (uint8)FEE_DFLASH_ONE_TIME_WRITE_SIZE; Counter++ )
        {
            if(( Fee_Record_Buffer.au1RecordData[Counter] ^ Fee_Record_BufferSub.au1RecordData[Counter] ) != (uint8)FEE_MIRROR_CHECK_UINT8 )
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
/* Function Name | Fee_Record_SetRAMSub                                     */
/* Description   | Function to set value to sub RAMs from main RAMs.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_SetRAMSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    uint8 Counter;

    Fee_Record_StateSub                    = (uint16)(~Fee_Record_State);
    Fee_Record_DataMatchResultSub          = (uint8)(~Fee_Record_DataMatchResult);
    Fee_Record_CompleteLenSub              = (uint16)(~Fee_Record_CompleteLen);
    Fee_Record_CheckSumValSub              = (uint32)(~Fee_Record_CheckSumVal);
    Fee_Record_ReadOldRcrdResultSub        = (uint32)(~Fee_Record_ReadOldRcrdResult);
    Fee_Record_RecordInfoSub.DataAddr      = (uint32)(~Fee_Record_RecordInfo.DataAddr);
    Fee_Record_RecordInfoSub.XFlagAddr     = (uint32)(~Fee_Record_RecordInfo.XFlagAddr);
    Fee_Record_RecordInfoSub.DataRecordLen = (uint32)(~Fee_Record_RecordInfo.DataRecordLen);

    for( Counter = 0U; Counter < (uint8)FEE_DFLASH_ONE_TIME_WRITE_SIZE; Counter++ )
    {
        Fee_Record_BufferSub.au1RecordData[Counter] = (uint8)(~Fee_Record_Buffer.au1RecordData[Counter]);
    }
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ書込み用空き領域検索                                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/*               ：uint32 *ptu4WriteLastRecMngAbsAddr                         */
/*                                      :検索結果を格納するアドレス           */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：最終書込みレコード先頭アドレスが返却されます               */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_Record_SrchSpcMngArea(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( uint32,         AUTOMATIC, TYPEDEF         ) ptu4WriteLastRecMngAbsAddr
){
    uint32          u4tBlockRecordAddress;                      /* ブロック先頭レコードアドレス */
    uint32          u4tLastRecordAddress;                       /* ブロック最終レコードアドレス */
    uint32          u4tDFCResult;                               /* ブランクチェック結果 */
    uint32          u4tBlankErrAddress;                         /* ブランクエラー発生アドレス */
    uint8           u1tBlockNo;                                 /* ブロック番号 */
    uint32          u4tBlockStartAddr;

    /* ブロック番号取り出し */
    u1tBlockNo = ptstCPUDTFInfo->u1MainBlockNo;
    /* 検索開始アドレス（レコード管理領域の先頭）を計算 */
    u4tBlockStartAddr     = FEE_BLKSTARTADDRTBL[u1tBlockNo];
    u4tBlockRecordAddress = u4tBlockStartAddr + FEE_STARTRECORDPOS;
    /* 検索終了アドレス（レコード管理領域とデータ領域の境界 に配置される最後のレコードの先頭）を計算 */
    u4tLastRecordAddress = ( u4tBlockStartAddr
                           + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr ))
                           - (uint32)FEE_RECORDMNGINFOLEN;

    /* ブランクチェック結果取得 */
    u4tDFCResult = Fee_GetMngDfcResult( &u4tBlankErrAddress );
    if ( u4tDFCResult != FEE_STATUS_OK )
    {
        /* ブランクエラーが発生した場合 */
        if ( u4tBlankErrAddress < u4tBlockRecordAddress )
        {
            /* ブランクエラーアドレスがブロック先頭レコードアドレス未満の場合 */
            /* 検索結果をブロック先頭レコードアドレス-レコード長に設定 */
            *ptu4WriteLastRecMngAbsAddr = u4tBlockRecordAddress - (uint32)FEE_RECORDMNGINFOLEN;
        }
        else if ( u4tLastRecordAddress <= u4tBlankErrAddress )
        {
            /* ブランクエラーアドレスがブロック最終レコードアドレス以上の場合 */
            /* 検索結果をブロック最終レコードアドレスに設定 */
            *ptu4WriteLastRecMngAbsAddr = u4tLastRecordAddress;
        }
        else
        {
            /* ブランクエラーアドレスがブロック先頭レコードアドレス以上の場合 */
            /* ブランクエラーとなったレコードの先頭アドレスに変換する */
            *ptu4WriteLastRecMngAbsAddr = u4tBlankErrAddress
                                - ( ( u4tBlankErrAddress - u4tBlockRecordAddress ) % (uint32)FEE_RECORDMNGINFOLEN );
        }
    }
    else
    {
        /* ブランクエラーが発生していない場合 */
        /* 検索結果をブロック先頭レコードアドレス-レコード長に設定 */
        *ptu4WriteLastRecMngAbsAddr = u4tBlockRecordAddress - (uint32)FEE_RECORDMNGINFOLEN;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_SrchSpcDatArea                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_SrchSpcDatArea(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( uint32,         AUTOMATIC, TYPEDEF )         ptu4WriteLastRecDatAbsAddr
){
    uint32          u4tDataAreaTopAddress;
    uint32          u4tDataAreaTailAddress;
    uint32          u4tDFCResult;                               /* ブランクチェック結果 */
    uint32          u4tBlankErrAddress;                         /* ブランクエラー発生アドレス */
    uint8           u1tBlockNo;                                 /* ブロック番号 */
    uint32          u4tBlockStartAddr;

    u1tBlockNo = ptstCPUDTFInfo->u1MainBlockNo;
    u4tBlockStartAddr      = FEE_BLKSTARTADDRTBL[u1tBlockNo];
    u4tDataAreaTopAddress  = u4tBlockStartAddr + (uint32)(ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr);
    u4tDataAreaTailAddress = ( u4tBlockStartAddr
                           + (uint32)FEE_DATA_FLASH_SECTOR_SIZE )
                           - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;

    /* ブランクチェック結果取得 */
    u4tDFCResult = Fee_GetMngDfcResult( &u4tBlankErrAddress );
    if ( u4tDFCResult != FEE_STATUS_OK )
    {
        /* ブランクエラーが発生した場合 */
        if ( u4tBlankErrAddress < u4tDataAreaTopAddress )
        {
            /* ブランクエラーアドレスが探索領域先頭アドレス未満の場合 */
            *ptu4WriteLastRecDatAbsAddr = u4tDataAreaTopAddress - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
        }
        else if ( u4tDataAreaTailAddress <= u4tBlankErrAddress )
        {
            /* ブランクエラーアドレスが探索領域末尾アドレス以上の場合 */
            *ptu4WriteLastRecDatAbsAddr = u4tDataAreaTailAddress;
        }
        else
        {
            *ptu4WriteLastRecDatAbsAddr = ( u4tBlankErrAddress + (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE ) - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
        }
    }
    else
    {
        /* ブランクエラーが発生していない場合 */
        *ptu4WriteLastRecDatAbsAddr = u4tDataAreaTopAddress - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
    }

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：空き領域検索                                               */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：検索結果                                                   */
/*               ：  0x00000000 ：FEE_STATUS_OK   ：使用中         */
/*               ：  0x00000001 ：FEE_STATUS_NG   ：未使用         */
/*               ：  0x00000005 ：FEE_STATUS_BUSY ：処理継続中     */
/* グローバル変数：                                                           */
/* その他        ：検索はReadSrchAddressから開始し、結果アドレスで更新します  */
/*               ：使用中の場合：非ブランクのレコードのアドレス               */
/*               ：未使用の場合：ブロックの先頭レコードアドレス－レコード長   */
/*               ：処理継続中の場合：次に検索するアドレス                     */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_SrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tSearchEndAddress;                /* 検索終了アドレス */
    uint32          u4tReadSrchAddress;                 /* 検索アドレス */
    uint32          u4tSrchRemainCount;                 /* 検索処理可能回数 */
    uint32          u4tBlockRecordAddress;              /* ブロック先頭レコードアドレス */
    uint8           u1tBlankCheckResult;

    /* ローカル変数(レジスタ変数)にロード */
    u4tReadSrchAddress = ptstCPUDTFInfo->u4ReadSrchAddress;
    u4tSrchRemainCount = ptstCPUDTFInfo->u4SrchRemainCount;
    u4tBlockRecordAddress = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo] + FEE_STARTRECORDPOS;

    /* 戻り値を未使用に設定 */
    u4tReturn = FEE_STATUS_NG;
    /* 検索処理可能回数から検索終了アドレスを計算 */
    u4tSearchEndAddress = u4tReadSrchAddress - ( ( u4tSrchRemainCount - (uint32)FEE_SRCH_REMAIN_CNT_OFFSET ) * (uint32)FEE_RECORDMNGINFOLEN );
    if ( u4tSearchEndAddress < u4tBlockRecordAddress )
    {
        /* 検索終了アドレスがブロック先頭レコードアドレスより小さい場合 */
        /* 検索終了アドレスをブロック先頭レコードアドレスとする */
        u4tSearchEndAddress = u4tBlockRecordAddress;
    }

    /* 検索開始アドレスからレコード長分デクリメントしながらブロック先頭アドレス以下になるまでループ */
    while ( ( u4tSearchEndAddress <= u4tReadSrchAddress ) && ( u4tReturn == FEE_STATUS_NG ) )
    {
        u1tBlankCheckResult = Fee_DfcMpu_SyncBlankCheck( u4tReadSrchAddress, (uint32)FEE_RECORDMNGINFOLEN );
        if ( u1tBlankCheckResult != FEE_DFCMPU_RESULT_OK )
        {
            /* In case of a record is not blank. */
            /* 戻り値を使用中(STATUS_OK)に設定 */
            u4tReturn = FEE_STATUS_OK;
        }
        else
        {
            /* 検索可能回数をデクリメント */
            u4tSrchRemainCount--;
            /* 検索アドレスをレコード長分デクリメント */
            u4tReadSrchAddress -= (uint32)FEE_RECORDMNGINFOLEN;
        }
    }

    if ( ( u4tReturn == FEE_STATUS_NG ) && ( u4tBlockRecordAddress <= u4tReadSrchAddress ) )
    {
        /* 最終データ位置が見つからず、かつ、検索アドレスがブロック先頭レコードアドレス以上のとき */
        /* 戻り値を処理継続中(STATUS_BUSY)に設定 */
        u4tReturn = FEE_STATUS_BUSY;
    }
    /* 検索アドレスを書き戻し */
    ptstCPUDTFInfo->u4ReadSrchAddress = u4tReadSrchAddress;
    /* 検索処理可能回数を書き戻し */
    ptstCPUDTFInfo->u4SrchRemainCount = u4tSrchRemainCount;

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：レコード書込み状態管理                                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込み中(定期処理終了)     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込み完了                 */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込み中(再実行可能)       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_WriteRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    
    /* サブ状態により分岐 */
    switch ( ptstCPUDTFInfo->u1SubStatus )
    {
        case FEE_SSTATUSWWIDLE:         /* 「アイドル」の場合 */
            u4tReturn = Fee_WriteRecord_DoIdle( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWSRCHPOSMNG:       /* 「書込みレコード位置(管理情報)検索中」の場合 */
            u4tReturn = Fee_WriteRecord_DoSrchWritePosMng( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWSTARTSRCHPOSDAT:      /* 「書込みレコード位置(データ)検索開始」の場合 */
            u4tReturn = Fee_WriteRecord_DoStartSrchPosDat( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWSRCHPOSDAT:           /* 「書込みレコード位置(データ)検索中」の場合 */
            u4tReturn = Fee_WriteRecord_DoSrchWritePosDat( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWPREPSRCHOLD:          /* 「旧データ検索準備中」の場合 */
            u4tReturn = Fee_WriteRecord_DoPrepSrchOldRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWSRCHOLD:      /* 「旧データ検索中」の場合 */
            u4tReturn = Fee_WriteRecord_DoSrchOldRecord( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWWWRITE:            /* 「データ書き込み中」の場合 */
            u4tReturn = Fee_WriteRecord_DoWriteNewRecord( ptstCPUDTFInfo );
            break;
        default:                                    /* 上記以外の場合 */
            /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
            if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
            {
                /* 処理結果を「書込み失敗」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_WRITE_DATA;
            }
            /* 処理結果が「書込み成功・対象ブロックなし」の場合 */
            else
            {
                /* 処理結果を「書込み失敗・対象ブロックなし」に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
            }
            /* 戻り値に「書込み完了」を設定 */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* 戻り値返却 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：レコード書込み状態管理(アイドル)                           */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込み中(定期処理終了)     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込み完了                 */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込み中(再実行可能)       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoIdle( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tBCStartTailAddress;
    uint32          u4tBCEndTopAddress;
    uint32          u4tBlockStartAddr;
    
    /* 末尾レコードを保持している場合 */
    if (( ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr != FEE_ADDRESS_INVALID ) &&
        ( ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr != FEE_ADDRESS_INVALID ))
    {
        /* ID指定データ読出し先アドレスに末尾レコードを設定 */
        ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
        /* サブ状態を「旧データ検索準備中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWPREPSRCHOLD;
        /* 戻り値に「書込み中(再実行可能)」を設定 */
        u4tReturn = FEE_STATUS_CONT;
    }
    /* 末尾レコードを保持していない場合 */
    else
    {
        /* ID指定データ読出し先アドレスに無効値を設定 */
        ptstCPUDTFInfo->u4ReadSrchAddress = FEE_ADDRESS_INVALID;

        /* Calculate blank check target address. */
        /* The blank check target is a record management information area. */
        u4tBlockStartAddr     = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
        u4tBCEndTopAddress    = u4tBlockStartAddr + FEE_STARTRECORDPOS;
        u4tBCStartTailAddress = u4tBlockStartAddr + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr );

        /* Start blank check. */
        Fee_StartBlankCheck( u4tBCStartTailAddress, u4tBCEndTopAddress );
        /* サブ状態を「書込み位置検索中」に設定 */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWSRCHPOSMNG;
        /* 戻り値に「書込み中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：レコード書込み状態管理(書込み位置検索中)                   */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：STATUS_EXIT ：書込み中(定期処理終了)        */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchWritePosMng( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    /* データ書込み用空き領域検索 */
    Fee_Record_SrchSpcMngArea( ptstCPUDTFInfo, &(ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr) );
    /* ID指定データ読出し先アドレスにデータ書込み時・転送時書込み先アドレスを設定 */
    ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
    /* サブ状態を「書込みレコード位置(データ)検索開始」に設定 */
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWSTARTSRCHPOSDAT;

    /* 戻り値に「書込み中(定期処理終了)」を設定 */
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_WriteRecord_DoStartSrchPosDat                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoStartSrchPosDat( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    uint32              u4tBCStartTailAddress;
    uint32              u4tBCEndTopAddress;
    uint32              u4tBlockStartAddr;

    /* Calculate blank check target address. */
    /* The blank check target is a record data area. */
    u4tBlockStartAddr     = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
    u4tBCEndTopAddress    = u4tBlockStartAddr + (uint32)(ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr);
    u4tBCStartTailAddress = u4tBlockStartAddr + (uint32)FEE_DATA_FLASH_SECTOR_SIZE;

    /* Start blank check. */
    Fee_StartBlankCheck( u4tBCStartTailAddress, u4tBCEndTopAddress );

    /* サブ状態を「書込みレコード位置(データ)検索中」に設定 */
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWSRCHPOSDAT;

    /* 戻り値に「書込み中(定期処理終了)」を設定 */
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_WriteRecord_DoSrchWritePosDat                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchWritePosDat( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    /* データ書込み用空き領域検索 */
    Fee_Record_SrchSpcDatArea( ptstCPUDTFInfo, &(ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr) );
    /* サブ状態を「旧データ検索準備中」に設定 */
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWPREPSRCHOLD;
    
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_WriteRecord_DoPrepSrchOldRecord                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoPrepSrchOldRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    Fee_Record_StateScOdStart();
    /* サブ状態を「旧データ検索中」に設定 */
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWSRCHOLD;
    
    return FEE_STATUS_CONT;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：レコード書込み状態管理(旧データ検索中)                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込み中(定期処理終了)     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込み完了                 */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込み中(再実行可能)       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchOldRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tReadActStatus;                           /* 結果 */
    uint32          u4tReadExecResult;
    boolean         btCheckDiffDataResult;
    boolean         btCheckWriteSpaceResult;

    /* データ読み出し用データ検索 */
    u4tReadActStatus = Fee_Record_StateScOdExec( ptstCPUDTFInfo, &u4tReadExecResult, &btCheckDiffDataResult );
    if ( u4tReadActStatus == FEE_STATUS_EXIT )
    {
        u4tReturn = FEE_STATUS_EXIT;
    }
    else if( u4tReadActStatus == FEE_STATUS_DONE )
    {
        /* 旧データ比較結果が「旧データあり」の場合 */
        if (( u4tReadExecResult == FEE_STATUS_OK ) && ( btCheckDiffDataResult == (boolean)FALSE ))
        {
            u4tReturn = Fee_QuitWriteProcessSuccess( ptstCPUDTFInfo );
        }
        /* 旧データ比較結果が「旧データなし」の場合 */
        else
        {
            btCheckWriteSpaceResult = Fee_Record_CheckWriteSpace( ptstCPUDTFInfo->u2ReqDataLen,
                                                                  (uint16)(ptstCPUDTFInfo->u1MainBlockNo),
                                                                  ptstCPUDTFInfo );
            /* 書込み位置の空きがある場合 */
            if ( btCheckWriteSpaceResult == (boolean)TRUE )
            {
                Fee_Record_StateWtWtStart( ptstCPUDTFInfo, u4tReadExecResult );

                /* サブ状態を「データ書き込み中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWWRITE;
                /* 戻り値に「書込み中(定期処理終了)」を設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* 書込み位置の空きがない場合 */
            else
            {
                /* メイン状態を「ブロック選択中」に設定 */
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
                /* サブ状態を「転送中ブロック作成中」に設定 */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSMOV;
                /* サブサブ状態を「転送中ブロック作成中－転送中設定待ち」に設定 */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMWMOVE;
                /* 戻り値にEXITを設定 */
                u4tReturn = FEE_STATUS_EXIT;
            }
        }
    }
    else /* u4tReadActStatus == FEE_STATUS_NG */
    {
        u4tReturn = Fee_QuitWriteProcessFailure( ptstCPUDTFInfo );
    }

    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：レコード書込み状態管理(データ書き込み中)                   */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込み中(定期処理終了)     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込み完了                 */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込み中(再実行可能)       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoWriteNewRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* 戻り値 */
    uint32          u4tResult;                                  /* 結果 */

    /* データ書込み中共通処理 */
    u4tResult = Fee_Record_StateWtWtExec( ptstCPUDTFInfo );
    /* 「処理継続中」の場合 */
    if ( u4tResult == FEE_STATUS_EXIT )
    {
        /* 戻り値に「書込み中(定期処理終了)」を設定 */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* 「書込み終了」の場合 */
    else if ( u4tResult == FEE_STATUS_DONE )
    {
        u4tReturn = Fee_QuitWriteProcessSuccess( ptstCPUDTFInfo );
    }
    /* 「書込み失敗」の場合 */
    else
    {
        u4tReturn = Fee_QuitWriteProcessFailure( ptstCPUDTFInfo );
    }
    
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：書き込み成功時終了処理                                     */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                                   */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：u4gSTATUS_EXIT ：書込み中(定期処理終了)     */
/*               ：  0x00000003 ：u4gSTATUS_DONE ：書込み完了                 */
/*               ：  0x00000004 ：u4gSTATUS_CONT ：書込み中(再実行可能)       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_QuitWriteProcessSuccess(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo
){
    uint32          u4tReturn;                                  /* 戻り値 */

    /* 最終書込みレコード位置更新許可フラグを「許可」に設定 */
    ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
    /* 処理結果が「書込み成功・対象ブロックなし」以外の場合 */
    if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
    {
        /* 処理結果を「書込み成功」に設定 */
        ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
    }
    /* 処理結果が「書込み成功・対象ブロックなし」の場合 */
    else
    {
        /* No process */
    }
    /* 戻り値に「書込み完了」を設定 */
    u4tReturn = FEE_STATUS_DONE;
    
    return u4tReturn;

}

/****************************************************************************/
/* Function Name | Fee_QuitWriteProcessFailure                              */
/* Description   | Function to execute process when writing job is quit     */
/*               | unsuccessfully.                                          */
/* Preconditions |                                                          */
/* Parameters    | ptstCPUDTFInfo   : Job information.                      */
/* Return Value  | Next status.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_QuitWriteProcessFailure(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo
){
    ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;

    if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
    {
        ptstCPUDTFInfo->u1Result = FEE_RSP_NG_WRITE_DATA;
    }
    else
    {
        ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
    }

    return FEE_STATUS_DONE;

}

/****************************************************************************/
/* Function Name | Fee_Record_GetRoundUpLen                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint16, FEE_CODE )
Fee_Record_GetRoundUpLen(
    uint16  InputDataLen, 
    uint8   RoundUpNum
){
    uint16 RtnDataLen;
    uint16 AddNum       = (uint16)RoundUpNum - (uint16)FEE_RECORD_ROUNDUP_CALC_ADDNUM_VAL;
    uint16 ShiftNum     = (uint16)FEE_RECORD_ROUNDUP_CALC_MASKNUM_VAL - AddNum;

    RtnDataLen = InputDataLen + AddNum;
    RtnDataLen = RtnDataLen & ShiftNum;

    return RtnDataLen;
}

/****************************************************************************/
/* Function Name | Fee_Record_GetDataAreaRcrdLen                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint16, FEE_CODE )
Fee_Record_GetDataAreaRcrdLen(
    uint16  InputDataLen
){
    uint16 DataCsLen;
    uint16 DataPadCsLen;
    uint16 Rtn;

    DataCsLen    = InputDataLen + (uint16)FEE_RECORD_SIZE_CHECKSUM;
    DataPadCsLen = Fee_Record_GetRoundUpLen( DataCsLen, (uint8)FEE_DFLASH_ONE_TIME_WRITE_SIZE );
    Rtn          = DataPadCsLen + (uint16)FEE_DFLASH_FORMAT_XFLAG_SIZE;

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_CheckWriteSpace                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  | Check result.                                            */
/*               |  TRUE  : It is able to write the next data.              */
/*               |  FALSE : It is not able to write. The sector is full.    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, FEE_CODE )
Fee_Record_CheckWriteSpace(
    uint16 WriteDataLen,
    uint16 TargetSector,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    boolean Rtn;

    uint32  StartSectorAbsAddr;
    uint32  TargetRecordMngPos;
    uint32  TargetRecordDatPos;
    uint32  MaxNextRecordMngPos;
    uint32  MaxNextRecordDatPos;
    uint32  RecordMngBorderPos;
    uint32  RecordDatBorderPos;
    uint32  MaxWriteRecordMngSize;
    uint32  MaxWriteRecordDatSize;
    uint16  DataPadCsFlagLen;
    uint8   RetryNum;

    Rtn = FALSE;

    StartSectorAbsAddr = FEE_BLKSTARTADDRTBL[TargetSector];
    RetryNum           = CPUDTFInfo->ptstAreaInf->u1RcrdRetryNum;

    TargetRecordMngPos = ( CPUDTFInfo->u4WriteLastRecMngAbsAddr - StartSectorAbsAddr ) + (uint32)FEE_RECORDMNGINFOLEN;
    MaxWriteRecordMngSize = ( (uint32)RetryNum * (uint32)FEE_RECORDMNGINFOLEN ) + (uint32)FEE_RECORDMNGINFOLEN;
    MaxNextRecordMngPos = TargetRecordMngPos + MaxWriteRecordMngSize;
    RecordMngBorderPos = CPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr;

    /* Check the record management information area. */
    if( MaxNextRecordMngPos <= RecordMngBorderPos )
    {
        TargetRecordDatPos = ( CPUDTFInfo->u4WriteLastRecDatAbsAddr - StartSectorAbsAddr ) + (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;

        DataPadCsFlagLen = Fee_Record_GetDataAreaRcrdLen( WriteDataLen );
        MaxWriteRecordDatSize = ( (uint32)RetryNum * (uint32)DataPadCsFlagLen ) + (uint32)DataPadCsFlagLen;

        MaxNextRecordDatPos = TargetRecordDatPos + MaxWriteRecordDatSize;
        RecordDatBorderPos = (uint32)FEE_DATA_FLASH_SECTOR_SIZE;

        /* Check the record data area. */
        if( MaxNextRecordDatPos <= RecordDatBorderPos )
        {
            Rtn = TRUE;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtWtStart(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    uint32 SrcReadOldRecordResult
){

    CPUDTFInfo->u4FailCount = 0U;

    Fee_Record_StateWtCmActShiftRec( CPUDTFInfo->u2ReqDataLen, CPUDTFInfo );

#if( FEE_USE_KEEPING_OLD_RCRD == STD_ON )
    Fee_Record_ReadOldRcrdResult = SrcReadOldRecordResult;
    Fee_Record_StateWtWtActWtIdAddr( CPUDTFInfo );
    Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;
#else /* FEE_USE_KEEPING_OLD_RCRD == STD_OFF */
    if ( SrcReadOldRecordResult == FEE_STATUS_OK )
    {
        Fee_Record_StateWtCmActWtDS( CPUDTFInfo->u4ReadSrchAddress );
        Fee_Record_State = FEE_RECORD_STATE_WWAITDS;
    }
    else
    {
        Fee_Record_StateWtWtActWtIdAddr( CPUDTFInfo );
        Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;
    }
#endif /* FEE_USE_KEEPING_OLD_RCRD */

    return;

}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  | The executed result.                                     */
/*               |  FEE_STATUS_EXIT : On the way to execution.              */
/*               |  FEE_STATUS_DONE : The write was complete.               */
/*               |  FEE_STATUS_NG   : Error occurred.                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32         Rtn = FEE_STATUS_EXIT;
    uint32         MngDfcResult;
    uint32         DummyLastWriteAddr;

    MngDfcResult = Fee_GetMngDfcResult( &DummyLastWriteAddr );

    if( FEE_STATUS_OK == MngDfcResult )
    {
        switch ( Fee_Record_State )
        {
            case FEE_RECORD_STATE_WWAITDS:
                Rtn = Fee_Record_StateWtWtEsubWaitDS( CPUDTFInfo );
                break;

            case FEE_RECORD_STATE_WWAITIDADDR:
                Fee_Record_StateWtCmActWtXFlag();
                Fee_Record_State = FEE_RECORD_STATE_WWAITXFLAG;
                break;

            case FEE_RECORD_STATE_WWAITXFLAG:
                Fee_Record_CompleteLen = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */
                Fee_Record_StateWtWtActWtDatCs( CPUDTFInfo );
                Fee_Record_State = FEE_RECORD_STATE_WWAITDATACS;
                break;

            case FEE_RECORD_STATE_WWAITDATACS:
                if( Fee_Record_CompleteLen < ( CPUDTFInfo->u2ReqDataLen + (uint16)FEE_RECORD_SIZE_CHECKSUM ))
                {
                    Fee_Record_StateWtWtActWtDatCs( CPUDTFInfo );
                    Fee_Record_State = FEE_RECORD_STATE_WWAITDATACS;
                }
                else
                {
                    Rtn = Fee_Record_StateWtWtEsubWaitDataCs( CPUDTFInfo );
                }
                break;

            case FEE_RECORD_STATE_WWAITHALFWC:
                Rtn = Fee_Record_StateWtWtEsubWaitHalfWC( CPUDTFInfo );
                break;

            case FEE_RECORD_STATE_WWAITWC:
                Rtn = Fee_Record_StateWtWtEsubWaitWC( CPUDTFInfo );
                break;

            case FEE_RECORD_STATE_WWAITDSFAIL:
                if( CPUDTFInfo->u4FailCount <= (uint32)CPUDTFInfo->ptstAreaInf->u1RcrdRetryNum)
                {
                    Fee_Record_StateWtCmActShiftRec( CPUDTFInfo->u2ReqDataLen, CPUDTFInfo );
                    Fee_Record_StateWtWtActWtIdAddr( CPUDTFInfo );
                    Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;
                }
                else
                {
                    Rtn = FEE_STATUS_NG;
                }
                break;

            case FEE_RECORD_STATE_INVALID:
            default:
                Rtn = FEE_STATUS_NG;
                break;
        }
    }
    else
    {
        CPUDTFInfo->u4FailCount++;
        Fee_Record_StateWtCmActWtDS( CPUDTFInfo->u4WriteLastRecMngAbsAddr );
        Fee_Record_State = FEE_RECORD_STATE_WWAITDSFAIL;
    }

    if( Rtn != FEE_STATUS_EXIT )
    {
        /* When any action result is end( Rtn is FEE_STATUS_DONE or FEE_STATUS_NG ), */
        /* here executes end process for this state transition control.              */
        Fee_Record_StateWtCmActQuit();
    }
    if( Rtn ==  FEE_STATUS_DONE )
    {
        Fee_Record_StateCmCmAsubSetRecPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u1MainBlockNo, CPUDTFInfo->u2DATA_ID, CPUDTFInfo->u4WriteLastRecMngAbsAddr );
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtMvStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtMvStart(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){

    CPUDTFInfo->u4FailCount = 0U;

    Fee_Record_StateWtCmActShiftRec( CPUDTFInfo->u2MovDataLen, CPUDTFInfo );

    Fee_Record_StateWtMvActWtIdAddr( CPUDTFInfo );
    Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;

    return;

}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtMvExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  | The executed result.                                     */
/*               |  FEE_STATUS_EXIT : On the way to execution.              */
/*               |  FEE_STATUS_DONE : The write was complete.               */
/*               |  FEE_STATUS_NG   : Error occurred.                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtMvExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32 Rtn = FEE_STATUS_EXIT;
    uint32 MngDfcResult;
    uint32 DummyLastWriteAddr;

    MngDfcResult = Fee_GetMngDfcResult( &DummyLastWriteAddr );

    if( FEE_STATUS_OK == MngDfcResult )
    {
        switch ( Fee_Record_State )
        {
            case FEE_RECORD_STATE_WWAITIDADDR:
                Fee_Record_StateWtCmActWtXFlag();
                Fee_Record_State = FEE_RECORD_STATE_WWAITXFLAG;
                break;

            case FEE_RECORD_STATE_WWAITXFLAG:
                Fee_Record_CompleteLen = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */
                Fee_Record_StateWtMvActWtDatCs( CPUDTFInfo );
                Fee_Record_State = FEE_RECORD_STATE_WWAITDATACS;
                break;

            case FEE_RECORD_STATE_WWAITDATACS:
                if( Fee_Record_CompleteLen < ( CPUDTFInfo->u2MovDataLen + (uint16)FEE_RECORD_SIZE_CHECKSUM ))
                {
                    Fee_Record_StateWtMvActWtDatCs( CPUDTFInfo );
                    Fee_Record_State = FEE_RECORD_STATE_WWAITDATACS;
                }
                else
                {
                    Fee_Record_StateWtCmActWtWc( CPUDTFInfo, FEE_RECORD_MNGDFC_WFLAG_BASIC );
                    Fee_Record_State = FEE_RECORD_STATE_WWAITWC;
                }
                break;

            case FEE_RECORD_STATE_WWAITWC:
                Rtn = FEE_STATUS_DONE;
                break;

            case FEE_RECORD_STATE_WWAITDSFAIL:
                if( CPUDTFInfo->u4FailCount <= (uint32)CPUDTFInfo->ptstAreaInf->u1RcrdRetryNum)
                {
                    Fee_Record_StateWtCmActShiftRec( CPUDTFInfo->u2MovDataLen, CPUDTFInfo );
                    Fee_Record_StateWtMvActWtIdAddr( CPUDTFInfo );
                    Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;
                }
                else
                {
                    Rtn = FEE_STATUS_NG;
                }
                break;

            case FEE_RECORD_STATE_INVALID:
            default:
                Rtn = FEE_STATUS_NG;
                break;
        }
    }
    else
    {
        CPUDTFInfo->u4FailCount++;
        Fee_Record_StateWtCmActWtDS( CPUDTFInfo->u4WriteLastRecMngAbsAddr );
        Fee_Record_State = FEE_RECORD_STATE_WWAITDSFAIL;
    }

    if( Rtn != FEE_STATUS_EXIT )
    {
        /* When any action result is end( Rtn is FEE_STATUS_DONE or FEE_STATUS_NG ), */
        /* here executes end process for this state transition control.              */
        Fee_Record_StateWtCmActQuit();
    }
    if( Rtn ==  FEE_STATUS_DONE )
    {
        /* Set RecPosTbl */
        Fee_Record_StateCmCmAsubSetRecPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u1SubBlockNo, CPUDTFInfo->u2MovDataId, CPUDTFInfo->u4WriteLastRecMngAbsAddr );
    }
    
    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateScOdStart( void )
{
    Fee_Record_DataMatchResult  = FEE_RECORD_DATA_CMP_INI_MISMATCH;
    Fee_Record_State            = FEE_RECORD_STATE_SWAITRECPOSTBL;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | CPUDTFInfo : Fee management data.                        */
/*               | DstSrchResult :                                          */
/*               |      The result of searching. The condition, which this  */
/*               |      parameter is changed, is the return value is DONE.  */
/*               |          FEE_STATUS_OK      :                            */
/*               |              A valid old data exist.                     */
/*               |          FEE_STATUS_INVALID :                            */
/*               |              An invalid old data exist.                  */
/*               |          FEE_STATUS_NG      :                            */
/*               |              Not found any old data.                     */
/*               | DstChkDiffData :                                         */
/*               |      The result of comparing write request data and      */
/*               |      flash ROM data with the same ID.                    */
/*               |          TRUE  : The two data are not same data.         */
/*               |          FALSE : The two data are same data.             */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to execution.          */
/*               |      FEE_STATUS_DONE : The search was complete.          */
/*               |      FEE_STATUS_NG   : Error occurred.                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult, 
    P2VAR( boolean,        AUTOMATIC, TYPEDEF )         DstChkDiffData
){
    uint32 Rtn        = FEE_STATUS_NG;
    uint32 SrchResult = FEE_STATUS_NG;

    switch ( Fee_Record_State )
    {
        case FEE_RECORD_STATE_SWAITRECPOSTBL:
            Rtn = Fee_Record_StateScOdActRecPosTbl( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITCALCSTBL:
            Rtn = Fee_Record_StateScOdActCalCSTbl ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITSRCHDAT:
            Rtn = Fee_Record_StateScOdActSrchDat  ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITCALCSSRCH:
            Rtn = Fee_Record_StateScOdActCalCSSrch( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_INVALID:
        default:
            /* Unlikely case. */
            break;
    }

    if( Rtn == FEE_STATUS_DONE )
    {
        *DstSrchResult  = SrchResult;
        if( Fee_Record_DataMatchResult == (uint8)FEE_RECORD_DATA_CMP_MATCH )
        {
            *DstChkDiffData = FALSE;
        }
        else
        {
            *DstChkDiffData = TRUE;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateScRdStart( void )
{
    Fee_Record_State        = FEE_RECORD_STATE_SWAITRECPOSTBL;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | CPUDTFInfo : Fee management data.                        */
/*               | DstSrchResult :                                          */
/*               |      The result of searching. The condition, which this  */
/*               |      parameter is changed, is the return value is DONE.  */
/*               |          FEE_STATUS_OK      :                            */
/*               |              A valid old data exist.                     */
/*               |          FEE_STATUS_INVALID :                            */
/*               |              An invalid old data exist.                  */
/*               |          FEE_STATUS_NG      :                            */
/*               |              Not found any old data.                     */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to execution.          */
/*               |      FEE_STATUS_DONE : The search was complete.          */
/*               |      FEE_STATUS_NG   : Error occurred.                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn        = FEE_STATUS_NG;
    uint32 SrchResult = FEE_STATUS_NG;

    switch ( Fee_Record_State )
    {
        case FEE_RECORD_STATE_SWAITRECPOSTBL:
            Rtn = Fee_Record_StateScRdActRecPosTbl( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITCALCSTBL:
            Rtn = Fee_Record_StateScRdActCalCSTbl ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITSRCHDAT:
            Rtn = Fee_Record_StateScRdActSrchDat  ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITCALCSSRCH:
            Rtn = Fee_Record_StateScRdActCalCSSrch( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_INVALID:
        default:
            /* Unlikely case. */
            break;
    }

    if( Rtn == FEE_STATUS_DONE )
    {
        *DstSrchResult  = SrchResult;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMsStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateScMsStart( void )
{
    Fee_Record_State        = FEE_RECORD_STATE_SWAITSRCHDAT;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMsExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | CPUDTFInfo : Fee management data.                        */
/*               | DstSrchResult :                                          */
/*               |      The result of searching. The condition, which this  */
/*               |      parameter is changed, is the return value is DONE.  */
/*               |          FEE_STATUS_OK :                                 */
/*               |              A valid data exist.                         */
/*               |          FEE_STATUS_NG :                                 */
/*               |              Not found any valid data.                   */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to execution.          */
/*               |      FEE_STATUS_DONE : The search was complete.          */
/*               |      FEE_STATUS_NG   : Error occurred.                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn        = FEE_STATUS_NG;
    uint32 SrchResult = FEE_STATUS_NG;

    switch ( Fee_Record_State )
    {
        case FEE_RECORD_STATE_SWAITSRCHDAT:
            Rtn = Fee_Record_StateScMsActSrchDat ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITCALCSSRCH:
            Rtn = Fee_Record_StateScMsActCalCS   ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_INVALID:
        default:
            /* Unlikely case. */
            break;
    }

    if( Rtn == FEE_STATUS_DONE )
    {
        *DstSrchResult  = SrchResult;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMdStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateScMdStart( void )
{
    Fee_Record_State        = FEE_RECORD_STATE_SWAITRECPOSTBL;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMdExec                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | CPUDTFInfo : Fee management data.                        */
/*               | DstSrchResult :                                          */
/*               |      The result of searching. The condition, which this  */
/*               |      parameter is changed, is the return value is DONE.  */
/*               |          FEE_STATUS_OK :                                 */
/*               |              A valid old data exist.                     */
/*               |          FEE_STATUS_INVALID :                            */
/*               |              An invalid old data exist.                  */
/*               |          FEE_STATUS_NG   :                               */
/*               |              Not found any old data.                     */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to execution.          */
/*               |      FEE_STATUS_DONE : The search was complete.          */
/*               |      FEE_STATUS_NG   : Error occurred.                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn        = FEE_STATUS_NG;
    uint32 SrchResult = FEE_STATUS_NG;

    switch ( Fee_Record_State )
    {
        case FEE_RECORD_STATE_SWAITRECPOSTBL:
            Rtn = Fee_Record_StateScMdActRecPosTbl( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_SWAITSRCHDAT:
            Rtn = Fee_Record_StateScMdActSrchDat  ( CPUDTFInfo, &SrchResult );
            break;
        case FEE_RECORD_STATE_INVALID:
        default:
            /* Unlikely case. */
            break;
    }

    if( Rtn == FEE_STATUS_DONE )
    {
        *DstSrchResult  = SrchResult;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtEsubWaitDS                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitDS(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32 Rtn;

#if( FEE_USE_KEEPING_OLD_RCRD == STD_ON )
    Rtn = FEE_STATUS_DONE;
#else /* FEE_USE_KEEPING_OLD_RCRD == STD_OFF */
    Fee_Record_StateWtWtActWtIdAddr( CPUDTFInfo );
    Fee_Record_State = FEE_RECORD_STATE_WWAITIDADDR;
    Rtn = FEE_STATUS_EXIT;
#endif /* FEE_USE_KEEPING_OLD_RCRD */

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtEsubWaitDataCs                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitDataCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32           Rtn = FEE_STATUS_EXIT;

#if ( FEE_HALFWORD_WRITE_USE == STD_ON )
    Fee_Record_StateWtCmActWtWc1st( CPUDTFInfo );
    Fee_Record_State = FEE_RECORD_STATE_WWAITHALFWC;

#else /* FEE_HALFWORD_WRITE_USE == STD_OFF */

    Fee_Record_StateWtCmActWtWc( CPUDTFInfo, FEE_RECORD_MNGDFC_WFLAG_WC );
    Fee_Record_State = FEE_RECORD_STATE_WWAITWC;

#endif /* FEE_HALFWORD_WRITE_USE */

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtEsubWaitHalfWC                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitHalfWC(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32          Rtn = FEE_STATUS_NG;
#if ( FEE_HALFWORD_WRITE_USE == STD_ON )

    Fee_Record_StateWtCmActWtWc2nd( CPUDTFInfo );
    Fee_Record_State = FEE_RECORD_STATE_WWAITWC;
    Rtn = FEE_STATUS_EXIT;
#endif /* FEE_HALFWORD_WRITE_USE == STD_ON */

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtEsubWaitWC                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitWC(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32 Rtn;

#if( FEE_USE_KEEPING_OLD_RCRD == STD_ON )
    if( Fee_Record_ReadOldRcrdResult == FEE_STATUS_OK )
    {
        Fee_Record_StateWtCmActWtDS( CPUDTFInfo->u4ReadSrchAddress );
        Fee_Record_State = FEE_RECORD_STATE_WWAITDS;
        Rtn = FEE_STATUS_EXIT;
    }
    else
    {
        Rtn = FEE_STATUS_DONE;
    }
#else /* FEE_USE_KEEPING_OLD_RCRD == STD_OFF */
    Rtn = FEE_STATUS_DONE;
#endif /* FEE_USE_KEEPING_OLD_RCRD */

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActWtDS                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtDS(
    uint32 TgtRcrdMngInfoAddr
){
    uint32 TargetAbsAddr;

    TargetAbsAddr = TgtRcrdMngInfoAddr + (uint32)FEE_DATASTATUSPOS;
    Fee_Record_StateWtCmAsubWtCom( TargetAbsAddr, &Fee_FixDSData[0], FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, FEE_RECORD_MNGDFC_WFLAG_DS );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtActWtIdAddr                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtWtActWtIdAddr(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint16 DataRelAddr;

    DataRelAddr = (uint16)( Fee_Record_RecordInfo.DataAddr - FEE_BLKSTARTADDRTBL[CPUDTFInfo->u1MainBlockNo] );
    Fee_Record_StateWtCmAsubWtIdAddr( CPUDTFInfo->u2DATA_ID, DataRelAddr, CPUDTFInfo->u4WriteLastRecMngAbsAddr );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtMvActWtIdAddr                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtMvActWtIdAddr(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint16 DataRelAddr;

    DataRelAddr = (uint16)( Fee_Record_RecordInfo.DataAddr - FEE_BLKSTARTADDRTBL[CPUDTFInfo->u1SubBlockNo] );
    Fee_Record_StateWtCmAsubWtIdAddr( CPUDTFInfo->u2MovDataId, DataRelAddr, CPUDTFInfo->u4WriteLastRecMngAbsAddr );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActWtXFlag                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtXFlag( void )
{
    Fee_Record_StateWtCmAsubWtCom( Fee_Record_RecordInfo.XFlagAddr, &Fee_FixXFlagData[0], FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, FEE_RECORD_MNGDFC_WFLAG_BASIC );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtWtActWtDatCs                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtWtActWtDatCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    Fee_Record_StateWtCmAsubWtDatCs( CPUDTFInfo->u2ReqDataLen, &CPUDTFInfo->ptu1ReqWriteAddr[Fee_Record_CompleteLen] );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtMvActWtDatCs                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtMvActWtDatCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint16 SrcDataRelTopAddr;
    uint32 SrcDataAbsTopAddr;
    uint32 SrcDataBuffer[FEE_DFLASH_ONE_TIME_WRITE_SIZE / FEE_BYTE_NUM_04];

    /* Return value is not checked. */
    (void)Fee_DfcMpu_SyncReadUint16( ( CPUDTFInfo->u4MoveSrcAddress + (uint32)FEE_RECORD_FORMAT_OFFSET_DATAADDR ), &SrcDataRelTopAddr );
    SrcDataAbsTopAddr = FEE_BLKSTARTADDRTBL[CPUDTFInfo->u1MainBlockNo] + SrcDataRelTopAddr;

    /* Return value is not checked. */
    (void)Fee_DfcMpu_SyncRead( ( SrcDataAbsTopAddr + (uint32)Fee_Record_CompleteLen ), (uint8 *)SrcDataBuffer, (uint32)FEE_DFLASH_ONE_TIME_WRITE_SIZE );
    Fee_Record_StateWtCmAsubWtDatCs( CPUDTFInfo->u2MovDataLen, (uint8 *)SrcDataBuffer );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActWtWc                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    uint16 WriteOptFlag
){
    uint32           TargetAbsAddr;

    TargetAbsAddr = CPUDTFInfo->u4WriteLastRecMngAbsAddr + (uint32)FEE_WRITECHECKPOS;
    Fee_Record_StateWtCmAsubWtCom( TargetAbsAddr, &Fee_FixWCData[0], FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, WriteOptFlag );

    return;
}

#if ( FEE_HALFWORD_WRITE_USE == STD_ON ) 
/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActWtWc1st                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc1st(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32           TargetAbsAddr;

    TargetAbsAddr   = CPUDTFInfo->u4WriteLastRecMngAbsAddr + (uint32)FEE_WRITECHECKPOS;
    Fee_Record_StateWtCmAsubWtCom( TargetAbsAddr, &Fee_FixWCData[0], (uint16)FEE_DATA_FLASH_HALF_WRITE_SIZE, FEE_CWOFFSET_ZERO, FEE_RECORD_MNGDFC_WFLAG_WC_1ST );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActWtWc2nd                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc2nd(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32           TargetAbsAddr;

    TargetAbsAddr   = CPUDTFInfo->u4WriteLastRecMngAbsAddr + (uint32)FEE_WRITECHECKPOS;
    Fee_Record_StateWtCmAsubWtCom( TargetAbsAddr, &Fee_FixWCData[0], (uint16)FEE_DATA_FLASH_HALF_WRITE_SIZE, (uint16)FEE_CWOFFSET_HALFWORD, FEE_RECORD_MNGDFC_WFLAG_WC );

    return;
}
#endif /* FEE_HALFWORD_WRITE_USE */ 

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActShiftRec                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActShiftRec(
    uint16 WriteDataLen,
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    Fee_Record_StateWtCmAsubMkRecInfo( WriteDataLen, CPUDTFInfo->u4WriteLastRecDatAbsAddr );

    /* Set next record position to a global variable */
    CPUDTFInfo->u4WriteLastRecMngAbsAddr = CPUDTFInfo->u4WriteLastRecMngAbsAddr + (uint32)FEE_RECORDMNGINFOLEN;
    CPUDTFInfo->u4WriteLastRecDatAbsAddr = CPUDTFInfo->u4WriteLastRecDatAbsAddr + Fee_Record_RecordInfo.DataRecordLen;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmActQuit                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActQuit( void ){
    /* Initialize global variables */
    Fee_Record_State = FEE_RECORD_STATE_INVALID;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmAsubWtIdAddr                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtIdAddr(
    uint16  BlockNumber,
    uint16  DataAddress,
    uint32  TargetAddress
){
    uint8  Counter;
    uint8  CheckSumTargetPos;
    uint32 IdAddrCheckSum;

    /* Init buffer, and make to write data, block number and data address. */
    Fee_Lib_SetMemory( Fee_Record_Buffer.au1RecordData, (uint8)FEE_RECORD_PADDING_VAL, (uint32)FEE_DFLASH_ONE_TIME_WRITE_SIZE );

    Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_ID_MSBYTE] = (uint8)(BlockNumber >> (uint16)FEE_NUM_OF_BITS_IN_1BYTE);
    Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_ID_LSBYTE] = (uint8)BlockNumber;
    Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_DATAADDR_MSBYTE] = (uint8)(DataAddress >> (uint16)FEE_NUM_OF_BITS_IN_1BYTE);
    Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_DATAADDR_LSBYTE] = (uint8)DataAddress;


    /* Request to write. */
    Fee_Record_StateWtCmAsubWtCom( TargetAddress, Fee_Record_Buffer.au1RecordData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, FEE_RECORD_MNGDFC_WFLAG_BASIC );

    /* Calculate check sum. */
    IdAddrCheckSum = FEE_CHECKSUM_UNLOCK_VAL;
    for ( Counter = 0U; Counter < (uint8)FEE_RECORD_SIZE_BLOCKNUM_DATAADDR; Counter++ )
    {
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        CheckSumTargetPos = (uint8)FEE_RECORD_FORMAT_OFFSET_ID + Counter;
#else
        CheckSumTargetPos = Counter;
#endif
        IdAddrCheckSum += Fee_Record_Buffer.au1RecordData[CheckSumTargetPos];
    }
    IdAddrCheckSum += Fee_Record_StateCmCmAsubCalcMngAddrCS( TargetAddress );

    Fee_Record_CheckSumVal = IdAddrCheckSum; /* The point of initializing Fee_Record_CheckSumVal. */

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmAsubWtDatCs                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         | This function uses global variables of the following     */
/*               | as input and output values.                              */
/*               |      Fee_Record_CompleteLen                              */
/*               |      Fee_Record_CheckSumVal                              */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtDatCs(
    uint16 TargetLen,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataAddr
){
    uint8  WriteData;
    uint16 Counter;
    uint16 WriteDataLen;
    uint16 ResidualLen;
    uint16 CompleteWriteLen;
    uint32 TargetAbsAddr;
    uint32 TmpCheckSum;

    Fee_Lib_SetMemory( Fee_Record_Buffer.au1RecordData, (uint8)FEE_RECORD_PADDING_VAL, (uint32)FEE_DFLASH_ONE_TIME_WRITE_SIZE );
    CompleteWriteLen = Fee_Record_CompleteLen;

    WriteDataLen = Fee_Record_StateWtCmAsubCalWtDatLen( TargetLen, CompleteWriteLen );

    /* Set data, and calculate check sum with data. */
    TmpCheckSum = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    for( Counter = 0U; Counter < WriteDataLen; Counter++ )
    {
        WriteData = DataAddr[Counter];
        TmpCheckSum += WriteData;
        Fee_Record_Buffer.au1RecordData[Counter] = WriteData;
    }
    /* Fee_Record_StateWtCmAsubWtDatCs_INT30_01 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Fee_Record_CheckSumVal += TmpCheckSum;

    /* Set check sum. */
    ResidualLen = (uint16)FEE_DFLASH_ONE_TIME_WRITE_SIZE - WriteDataLen;
    if( ResidualLen >= (uint16)FEE_RECORD_SIZE_CHECKSUM )
    {
        Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_0] = (uint8)(Fee_Record_CheckSumVal >> (uint32)FEE_NUM_OF_BITS_IN_3BYTE);
        Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_1] = (uint8)(Fee_Record_CheckSumVal >> (uint32)FEE_NUM_OF_BITS_IN_2BYTE);
        Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_2] = (uint8)(Fee_Record_CheckSumVal >> (uint32)FEE_NUM_OF_BITS_IN_1BYTE);
        Fee_Record_Buffer.au1RecordData[FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_3] = (uint8)Fee_Record_CheckSumVal;
    }

    /* Request to write the buffer data. */
    TargetAbsAddr = Fee_Record_RecordInfo.DataAddr + CompleteWriteLen;
    Fee_Record_StateWtCmAsubWtCom( TargetAbsAddr, Fee_Record_Buffer.au1RecordData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, FEE_RECORD_MNGDFC_WFLAG_BASIC );
    Fee_Record_CompleteLen += (uint16)FEE_DFLASH_ONE_TIME_WRITE_SIZE;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmAsubCalWtDatLen                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint16, FEE_CODE )
Fee_Record_StateWtCmAsubCalWtDatLen(
    uint16 TargetLen,
    uint16 CompleteWriteLen
){
    uint16 RtnWriteDataLen;

    RtnWriteDataLen = FEE_RECORD_WRITEDATALEN_VAL_ZERO;
    if( CompleteWriteLen < TargetLen )
    {
        RtnWriteDataLen = TargetLen - CompleteWriteLen;
        if( RtnWriteDataLen > (uint16)FEE_DFLASH_ONE_TIME_WRITE_SIZE )
        {
            RtnWriteDataLen = FEE_DFLASH_ONE_TIME_WRITE_SIZE;
        }
        /* Else case : If the residual writhing data length is smaller than the writing size at one time,   */
        /*             the return value is the residual writhing data length.                               */
    }
    /* Else case : If writing all data is completed,    */
    /*             the return value is zero.            */

    return RtnWriteDataLen;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmAsubWtCom                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtCom(
    uint32                                  TargetAbsAddr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF )    WriteDataAddr,
    uint16                                  WriteLength,
    uint16                                  WriteOffset,
    uint16                                  WriteOptFlag
){
    Fee_ClearCWriteBuf();
    Fee_AddCWriteBuf( TargetAbsAddr, WriteDataAddr, WriteLength, WriteOffset, WriteOptFlag );
    Fee_StartCWrite();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateWtCmAsubMkRecInfo                        */
/* Description   | Function to make the record information.                 */
/* Preconditions | None                                                     */
/* Parameters    | DataLen              : Next writing record size.         */
/*               | LastRecordDataAddr   : Last record data address.         */
/* Return Value  | None                                                     */
/* Notes         | The output is the global variable, Fee_Record_RecordInfo.*/
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubMkRecInfo(
    uint16 DataLen,
    uint32 LastRecordDataAddr
){
    uint32 StartRecordDataAddr;
    uint16 DataPadCsFlagLen;

    StartRecordDataAddr = LastRecordDataAddr + (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
    DataPadCsFlagLen = Fee_Record_GetDataAreaRcrdLen( DataLen );

    Fee_Record_RecordInfo.DataAddr      = StartRecordDataAddr;
    Fee_Record_RecordInfo.XFlagAddr     = StartRecordDataAddr + ( DataPadCsFlagLen - (uint32)FEE_DFLASH_FORMAT_XFLAG_SIZE );
    Fee_Record_RecordInfo.DataRecordLen = DataPadCsFlagLen;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdActRecPosTbl                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    uint32 Rtn;
    uint32 ActivateResult;
    uint32 CheckRecordPosResult;
    uint8  SectorNo = CPUDTFInfo->u1MainBlockNo;

    /* Do Action. */
    ActivateResult = Fee_RecordPosTbl_ReadyPosArea( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u4WriteLastRecMngAbsAddr );

    /* Exit action and state change. */
    if( ActivateResult == FEE_STATUS_OK )
    {
        CheckRecordPosResult = Fee_Record_StateScCmAsubGetRecPos( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u2DATA_ID, CPUDTFInfo->u2ReqDataLen, &(CPUDTFInfo->u4ReadSrchAddress) );
        if( CheckRecordPosResult == FEE_STATUS_OK )
        {
            /* Initialize sum value and calculate sum using block number and data address. */
            Fee_Record_CheckSumVal = Fee_Record_StateScCmAsubCalCSIdAddr( CPUDTFInfo->u4ReadSrchAddress );/* The point of initializing Fee_Record_CheckSumVal. */

            Fee_Record_CompleteLen     = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */
            Fee_Record_DataMatchResult = FEE_RECORD_DATA_CMP_MATCH;

            Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSTBL;
            Rtn = Fee_Record_StateScOdActCalCSTbl( CPUDTFInfo, DstSrchResult );
        }
        else if( CheckRecordPosResult == FEE_STATUS_NODATA )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = FEE_STATUS_NG;
            Rtn = FEE_STATUS_DONE;
        }
        else /* CheckRecordPosResult == FEE_STATUS_NG */
        {
            CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = Fee_Record_StateScOdActSrchDat( CPUDTFInfo, DstSrchResult );
        }
    }
    else if( ActivateResult == FEE_STATUS_NG )
    {
        CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = Fee_Record_StateScOdActSrchDat( CPUDTFInfo, DstSrchResult );
    }
    else /* ActivateResult == FEE_STATUS_BUSY */
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITRECPOSTBL;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdActCalCSTbl                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActCalCSTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    boolean ChkCSResult;
    uint32  CalCsResult;
    uint32  Rtn;

    /* Do Action. Calculate check sum of data. And check if request data and old record data match. */
    CalCsResult = Fee_Record_StateScOdAsubCalCSChkDat( CPUDTFInfo, &ChkCSResult );

    /* Exit action and state change. */
    if( CalCsResult == FEE_STATUS_DONE )
    {
        if ( ChkCSResult == (boolean)TRUE )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( CPUDTFInfo->u4ReadSrchAddress );
            Rtn = FEE_STATUS_DONE;
        }
        else
        {
            Fee_Record_DataMatchResult = FEE_RECORD_DATA_CMP_INI_MISMATCH;
            CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = FEE_STATUS_EXIT;
        }
    }
    else
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSTBL;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdActSrchDat                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    uint32 Rtn;
    uint32 SrchResult;

    SrchResult = Fee_Record_StateScCmAsubSrchId( CPUDTFInfo->u2DATA_ID, CPUDTFInfo->u2ReqDataLen, CPUDTFInfo->u1MainBlockNo, CPUDTFInfo );

    if( SrchResult == FEE_STATUS_BUSY )
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = FEE_STATUS_EXIT;
    }
    else if( SrchResult == FEE_STATUS_OK )
    {
        Fee_Record_CheckSumVal = Fee_Record_StateScCmAsubCalCSIdAddr( CPUDTFInfo->u4ReadSrchAddress );/* The point of initializing Fee_Record_CheckSumVal. */
        Fee_Record_CompleteLen = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */
        Fee_Record_DataMatchResult = FEE_RECORD_DATA_CMP_MATCH;

        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = Fee_Record_StateScOdActCalCSSrch( CPUDTFInfo, DstSrchResult );
    }
    else /* SrchResult == FEE_STATUS_NG */
    {
        Fee_RecordPosTbl_SetPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u2DATA_ID, FEE_IDNONE );
        Fee_Record_State = FEE_RECORD_STATE_INVALID;
        *DstSrchResult = SrchResult;
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdActCalCSSrch                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActCalCSSrch(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    boolean ChkCSResult;
    uint32  CalCsResult;
    uint32  ReadSrchAddress;
    uint32  Rtn;

    /* Do Action. Calculate check sum of data. And check if request data and old record data match. */
    CalCsResult = Fee_Record_StateScOdAsubCalCSChkDat( CPUDTFInfo, &ChkCSResult );

    /* Exit action and state change. */
    if( CalCsResult == FEE_STATUS_DONE )
    {
        ReadSrchAddress = CPUDTFInfo->u4ReadSrchAddress;
        if ( ChkCSResult == (boolean)TRUE )
        {
            Fee_Record_StateCmCmAsubSetRecPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u1MainBlockNo, CPUDTFInfo->u2DATA_ID, ReadSrchAddress );
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( ReadSrchAddress );
            Rtn = FEE_STATUS_DONE;
        }
        else
        {
            Fee_Record_DataMatchResult = FEE_RECORD_DATA_CMP_INI_MISMATCH;
            CPUDTFInfo->u4ReadSrchAddress = ReadSrchAddress - (uint32)FEE_RECORDMNGINFOLEN;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = FEE_STATUS_EXIT;
        }
    }
    else
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdActRecPosTbl                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    uint32 Rtn;
    uint32 ActivateResult;
    uint32 CheckRecordPosResult;
    uint8  SectorNo = CPUDTFInfo->u1MainBlockNo;

    /* Do Action. */
    ActivateResult = Fee_RecordPosTbl_ReadyPosArea( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u4WriteLastRecMngAbsAddr );

    /* Exit action and state change. */
    if( ActivateResult == FEE_STATUS_OK )
    {
        CheckRecordPosResult = Fee_Record_StateScCmAsubGetRecPos( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u2DATA_ID, CPUDTFInfo->u2ReqDataLen, &(CPUDTFInfo->u4ReadSrchAddress) );
        if( CheckRecordPosResult == FEE_STATUS_OK )
        {
            /* Initialize sum value and calculate sum using block number and data address. */
            Fee_Record_CheckSumVal = Fee_Record_StateScCmAsubCalCSIdAddr( CPUDTFInfo->u4ReadSrchAddress );/* The point of initializing Fee_Record_CheckSumVal. */
            Fee_Record_CompleteLen     = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */

            Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSTBL;
            Rtn = Fee_Record_StateScRdActCalCSTbl( CPUDTFInfo, DstSrchResult );
        }
        else if( CheckRecordPosResult == FEE_STATUS_NODATA )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = FEE_STATUS_NG;
            Rtn = FEE_STATUS_DONE;
        }
        else /* CheckRecordPosResult == FEE_STATUS_NG */
        {
            CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = Fee_Record_StateScRdActSrchDat( CPUDTFInfo, DstSrchResult );
        }
    }
    else if( ActivateResult == FEE_STATUS_NG )
    {
        CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = Fee_Record_StateScRdActSrchDat( CPUDTFInfo, DstSrchResult );
    }
    else /* ActivateResult == FEE_STATUS_BUSY */
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITRECPOSTBL;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdActCalCSTbl                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActCalCSTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    boolean ChkCSResult;
    uint32  CalCsResult;
    uint32  Rtn;

    /* Do Action. Calculate check sum of data. And copy flash data to request address. */
    CalCsResult = Fee_Record_StateScRdAsubCalCSCpyDat( CPUDTFInfo, &ChkCSResult );

    /* Exit action and state change. */
    if( CalCsResult == FEE_STATUS_DONE )
    {
        if ( ChkCSResult == (boolean)TRUE )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( CPUDTFInfo->u4ReadSrchAddress );
            Rtn = FEE_STATUS_DONE;
        }
        else
        {
            CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = FEE_STATUS_EXIT;
        }
    }
    else
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSTBL;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdActSrchDat                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn;
    uint32 SrchResult;

    SrchResult = Fee_Record_StateScCmAsubSrchId( CPUDTFInfo->u2DATA_ID, CPUDTFInfo->u2ReqDataLen, CPUDTFInfo->u1MainBlockNo, CPUDTFInfo );

    if( SrchResult == FEE_STATUS_BUSY )
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = FEE_STATUS_EXIT;
    }
    else if( SrchResult == FEE_STATUS_OK )
    {
        Fee_Record_CheckSumVal = Fee_Record_StateScCmAsubCalCSIdAddr( CPUDTFInfo->u4ReadSrchAddress );/* The point of initializing Fee_Record_CheckSumVal. */
        Fee_Record_CompleteLen = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */

        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = Fee_Record_StateScRdActCalCSSrch( CPUDTFInfo, DstSrchResult );
    }
    else /* SrchResult == FEE_STATUS_NG */
    {
        Fee_RecordPosTbl_SetPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u2DATA_ID, FEE_IDNONE );
        Fee_Record_State = FEE_RECORD_STATE_INVALID;
        *DstSrchResult = SrchResult;
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdActCalCSSrch                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActCalCSSrch(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    boolean ChkCSResult;
    uint32  CalCsResult;
    uint32  ReadSrchAddress;
    uint32  Rtn;

    /* Do Action. Calculate check sum of data. And copy flash data to request address. */
    CalCsResult = Fee_Record_StateScRdAsubCalCSCpyDat( CPUDTFInfo, &ChkCSResult );

    /* Exit action and state change. */
    if( CalCsResult == FEE_STATUS_DONE )
    {
        ReadSrchAddress = CPUDTFInfo->u4ReadSrchAddress;
        if ( ChkCSResult == (boolean)TRUE )
        {
            Fee_Record_StateCmCmAsubSetRecPos( CPUDTFInfo->u1AreaNum, CPUDTFInfo->u1MainBlockNo, CPUDTFInfo->u2DATA_ID, ReadSrchAddress );
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( ReadSrchAddress );
            Rtn = FEE_STATUS_DONE;
        }
        else
        {
            CPUDTFInfo->u4ReadSrchAddress = ReadSrchAddress - (uint32)FEE_RECORDMNGINFOLEN;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = FEE_STATUS_EXIT;
        }
    }
    else
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMsActSrchDat                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn;
    uint32 SrchResult;

    SrchResult = Fee_Record_StateScCmAsubSrchValid( CPUDTFInfo );

    if( SrchResult == FEE_STATUS_BUSY )
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = FEE_STATUS_EXIT;
    }
    else if( SrchResult == FEE_STATUS_OK )
    {
        Fee_Record_CheckSumVal = Fee_Record_StateScCmAsubCalCSIdAddr( CPUDTFInfo->u4MoveSrcAddress );/* The point of initializing Fee_Record_CheckSumVal. */
        Fee_Record_CompleteLen = FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO; /* The point of initializing Fee_Record_CompleteLen. */

        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = Fee_Record_StateScMsActCalCS( CPUDTFInfo, DstSrchResult );
    }
    else /* SrchResult == FEE_STATUS_NG */
    {
        Fee_Record_State = FEE_RECORD_STATE_INVALID;
        *DstSrchResult = SrchResult;
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMsActCalCS                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsActCalCS(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    boolean ChkCSResult;
    uint32  CalCsResult;
    uint32  Rtn;

    /* Do Action. Calculate check sum of data. */
    CalCsResult = Fee_Record_StateScMsAsubCalCS( CPUDTFInfo, &ChkCSResult );

    /* Exit action and state change. */
    if( CalCsResult == FEE_STATUS_DONE )
    {
        if ( ChkCSResult == (boolean)TRUE )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = FEE_STATUS_OK;
            Rtn = FEE_STATUS_DONE;
        }
        else
        {
            CPUDTFInfo->u4MoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = FEE_STATUS_EXIT;
        }
    }
    else
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITCALCSSRCH;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMdActRecPosTbl                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
){
    uint32  Rtn;
    uint32  ActivateResult;
    uint32  CheckRecordPosResult;
    uint8   SectorNo = CPUDTFInfo->u1SubBlockNo;

    /* Do Action. */
    ActivateResult = Fee_RecordPosTbl_ReadyPosArea( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u4WriteLastRecMngAbsAddr );

    /* Exit action and state change. */
    if( ActivateResult == FEE_STATUS_OK )
    {
        CheckRecordPosResult = Fee_Record_StateScCmAsubGetRecPos( CPUDTFInfo->u1AreaNum, SectorNo, CPUDTFInfo->u2MovDataId, CPUDTFInfo->u2MovDataLen, &(CPUDTFInfo->u4ReadSrchAddress) );
        if( CheckRecordPosResult == FEE_STATUS_OK )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( CPUDTFInfo->u4ReadSrchAddress );
            Rtn = FEE_STATUS_DONE;
        }
        else if( CheckRecordPosResult == FEE_STATUS_NODATA )
        {
            Fee_Record_State = FEE_RECORD_STATE_INVALID;
            *DstSrchResult = FEE_STATUS_NG;
            Rtn = FEE_STATUS_DONE;
        }
        else /* CheckRecordPosResult == FEE_STATUS_NG */
        {
            CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
            Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
            Rtn = Fee_Record_StateScMdActSrchDat( CPUDTFInfo, DstSrchResult );
        }
    }
    else if( ActivateResult == FEE_STATUS_NG )
    {
        CPUDTFInfo->u4ReadSrchAddress = CPUDTFInfo->u4WriteLastRecMngAbsAddr;
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = Fee_Record_StateScMdActSrchDat( CPUDTFInfo, DstSrchResult );
    }
    else /* ActivateResult == FEE_STATUS_BUSY */
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITRECPOSTBL;
        Rtn = FEE_STATUS_EXIT;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMdActSrchDat                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
){
    uint32 Rtn;
    uint32 SrchResult;
    uint8  SubBlockNo;
    uint16 MovDataId;
    uint32 ReadSrchAddress;

    SubBlockNo = CPUDTFInfo->u1SubBlockNo;
    MovDataId  = CPUDTFInfo->u2MovDataId;
    SrchResult = Fee_Record_StateScCmAsubSrchId( MovDataId, CPUDTFInfo->u2MovDataLen, SubBlockNo, CPUDTFInfo );

    if( SrchResult == FEE_STATUS_BUSY )
    {
        Fee_Record_State = FEE_RECORD_STATE_SWAITSRCHDAT;
        Rtn = FEE_STATUS_EXIT;
    }
    else if( SrchResult == FEE_STATUS_OK )
    {
        ReadSrchAddress = CPUDTFInfo->u4ReadSrchAddress;
        Fee_Record_StateCmCmAsubSetRecPos( CPUDTFInfo->u1AreaNum, SubBlockNo, MovDataId, ReadSrchAddress );
        Fee_Record_State = FEE_RECORD_STATE_INVALID;
        *DstSrchResult = Fee_Record_StateScCmAsubRdChkDS( ReadSrchAddress );
        Rtn = FEE_STATUS_DONE;
    }
    else /* SrchResult == FEE_STATUS_NG */
    {
        Fee_RecordPosTbl_SetPos( CPUDTFInfo->u1AreaNum, MovDataId, FEE_IDNONE );
        Fee_Record_State = FEE_RECORD_STATE_INVALID;
        *DstSrchResult = FEE_STATUS_NG;
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScOdAsubCalCSChkDat                      */
/* Description   | Function to calculate the check sum of old record data   */
/*               | with data flash. And checks if request data and data     */
/*               | old record data match.                                   */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/*               | DstCheckResult                                           */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to calculate.          */
/*               |      FEE_STATUS_DONE : The calculation was complete.     */
/* Notes         | This function uses global variables of the following     */
/*               | as input and output values.                              */
/*               |      Fee_Record_CompleteLen                              */
/*               |      Fee_Record_CheckSumVal                              */
/*               |      Fee_Record_DataMatchResult                          */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdAsubCalCSChkDat(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
){
    uint8   DataMatchResult = Fee_Record_DataMatchResult;
    uint8   CompareResult;
    uint16  ReqDataLen;
    uint16  ExecCounter;
    uint16  ReadDataLen;
    uint16  ExecTargetPos   = Fee_Record_CompleteLen;
    uint16  ExecLimit;
    /* Fee_Record_StateScOdAsubCalCSChkDat_INT30_01 */
    /* Wraparound may occur */
    uint32  TmpCheckSumData = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    uint32  Rtn             = FEE_STATUS_EXIT;
    uint32  FlashDataAreaAbsAddr;
    uint32  ReadBuffer[FEE_RECORD_SYNC_READ_MAX_SIZE / (uint16)FEE_BYTE_NUM_04];
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ReqWriteDataAddr;

    ReqDataLen = CPUDTFInfo->u2ReqDataLen;
    ReqWriteDataAddr = CPUDTFInfo->ptu1ReqWriteAddr;
    FlashDataAreaAbsAddr = Fee_Record_StateCmCmAsubGetDatRecFromMngRec( CPUDTFInfo->u4ReadSrchAddress, CPUDTFInfo->u1MainBlockNo );

    /* Calculate check sum of data. */
    ExecLimit = Fee_Record_StateScCmAsubCalOneTimeCSSize( Fee_Record_CompleteLen, ReqDataLen );

    for( ExecCounter = 0U; ExecCounter < ExecLimit; ExecCounter += FEE_RECORD_SYNC_READ_MAX_SIZE )
    {
        ReadDataLen = ExecLimit - ExecCounter;
        if( ReadDataLen > FEE_RECORD_SYNC_READ_MAX_SIZE )
        {
            ReadDataLen = FEE_RECORD_SYNC_READ_MAX_SIZE;
        }

        /* Return value is not checked. */
        (void)Fee_DfcMpu_SyncRead( ( FlashDataAreaAbsAddr + ExecTargetPos ), (uint8 *)ReadBuffer, (uint32)ReadDataLen );
        /* Fee_Record_StateScOdAsubCalCSChkDat_INT30_01 */
        /* Wraparound may occur due to CS calculations. */
        /* No problem because CS calculation causes wraparound as intended. */
        TmpCheckSumData += Fee_Record_StateScCmAsubCalcCS( (uint8 *)ReadBuffer, ReadDataLen );

        /* Check if request data and old record data match. */
        if( DataMatchResult == (uint8)FEE_RECORD_DATA_CMP_MATCH )
        {
            CompareResult = Fee_Lib_CompareMemory( &ReqWriteDataAddr[ExecTargetPos], (uint8 *)ReadBuffer, (uint32)ReadDataLen );
            if( CompareResult != FEE_LIB_EQUAL )
            {
                DataMatchResult = FEE_RECORD_DATA_CMP_INI_MISMATCH;
            }
        }

        ExecTargetPos += ReadDataLen;
    }

    /* Update global variables for calculating check sum. */
    Fee_Record_CompleteLen  = ExecTargetPos;
    /* Fee_Record_StateScOdAsubCalCSChkDat_INT30_02 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Fee_Record_CheckSumVal += TmpCheckSumData;

    /* Update global variables for checking if request data and data old record data match. */
    Fee_Record_DataMatchResult = DataMatchResult;

    /* Check that calculating a check sum have been completed. */
    if( ReqDataLen <= ExecTargetPos )
    {
        *DstCheckResult = Fee_Record_StateScCmAsubCmpCS( Fee_Record_CheckSumVal, FlashDataAreaAbsAddr, ReqDataLen );
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScRdAsubCalCSCpyDat                      */
/* Description   | Function to calculate the check sum of old record data   */
/*               | with data flash. copy flash data to request address.     */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/*               | DstCheckResult                                           */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to calculate.          */
/*               |      FEE_STATUS_DONE : The calculation was complete.     */
/* Notes         | This function uses global variables of the following     */
/*               | as input and output values.                              */
/*               |      Fee_Record_CompleteLen                              */
/*               |      Fee_Record_CheckSumVal                              */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdAsubCalCSCpyDat(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
){
    uint16  ReqDataLen;
    uint16  ExecCounter;
    uint16  ReadDataLen;
    uint16  ExecTargetPos   = Fee_Record_CompleteLen;
    uint16  ExecLimit;
    /* Fee_Record_StateScRdAsubCalCSCpyDat_INT30_01 */
    /* Wraparound may occur */
    uint32  TmpCheckSumData = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    uint32  Rtn             = FEE_STATUS_EXIT;
    uint32  FlashDataAreaAbsAddr;
    uint32  ReadBuffer[FEE_RECORD_SYNC_READ_MAX_SIZE / (uint16)FEE_BYTE_NUM_04];
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ReqReadAddr;

    ReqDataLen = CPUDTFInfo->u2ReqDataLen;
    ReqReadAddr = CPUDTFInfo->ptu1ReqReadAddr;
    FlashDataAreaAbsAddr = Fee_Record_StateCmCmAsubGetDatRecFromMngRec( CPUDTFInfo->u4ReadSrchAddress, CPUDTFInfo->u1MainBlockNo );
    ExecLimit = Fee_Record_StateScCmAsubCalOneTimeCSSize( Fee_Record_CompleteLen, ReqDataLen );


    for( ExecCounter = 0U; ExecCounter < ExecLimit; ExecCounter += FEE_RECORD_SYNC_READ_MAX_SIZE )
    {
        ReadDataLen = ExecLimit - ExecCounter;
        if( ReadDataLen > FEE_RECORD_SYNC_READ_MAX_SIZE )
        {
            ReadDataLen = FEE_RECORD_SYNC_READ_MAX_SIZE;
        }

        /* Use 4-byte aligned buffer to read from data flash. */
        /* Return value is not checked. */
        (void)Fee_DfcMpu_SyncRead( ( FlashDataAreaAbsAddr + ExecTargetPos ), (uint8 *)ReadBuffer, (uint32)ReadDataLen );

        /* Copy flash data to request address. */
        Fee_Lib_CopyMemory( &ReqReadAddr[ExecTargetPos], (uint8 *)ReadBuffer, (uint32)ReadDataLen );

        /* Calculate check sum of data. */
        /* Fee_Record_StateScRdAsubCalCSCpyDat_INT30_01 */
        /* Wraparound may occur due to CS calculations. */
        /* No problem because CS calculation causes wraparound as intended. */
        TmpCheckSumData += Fee_Record_StateScCmAsubCalcCS( (uint8 *)ReadBuffer, ReadDataLen );

        ExecTargetPos += ReadDataLen;
    }

    /* Update global variables for calculating check sum. */
    Fee_Record_CompleteLen  = ExecTargetPos;
    /* Fee_Record_StateScRdAsubCalCSCpyDat_INT30_02 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Fee_Record_CheckSumVal += TmpCheckSumData;

    /* Check that calculating a check sum have been completed. */
    if( ReqDataLen <= ExecTargetPos )
    {
        *DstCheckResult = Fee_Record_StateScCmAsubCmpCS( Fee_Record_CheckSumVal, FlashDataAreaAbsAddr, ReqDataLen );
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScMsAsubCalCS                            */
/* Description   | Function to calculate the check sum of old record data   */
/*               | with data flash.                                         */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/*               | DstCheckResult                                           */
/* Return Value  | The executed result.                                     */
/*               |      FEE_STATUS_EXIT : On the way to calculate.          */
/*               |      FEE_STATUS_DONE : The calculation was complete.     */
/* Notes         | This function uses global variables of the following     */
/*               | as input and output values.                              */
/*               |      Fee_Record_CompleteLen                              */
/*               |      Fee_Record_CheckSumVal                              */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsAsubCalCS(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
){
    uint16  ReqDataLen;
    uint16  ExecCounter;
    uint16  ReadDataLen;
    uint16  ExecTargetPos   = Fee_Record_CompleteLen;
    uint16  ExecLimit;
    /* Fee_Record_StateScMsAsubCalCS_INT30_01 */
    /* Wraparound may occur */
    uint32  TmpCheckSumData = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    uint32  Rtn             = FEE_STATUS_EXIT;
    uint32  FlashDataAreaAbsAddr;
    uint32  ReadBuffer[FEE_RECORD_SYNC_READ_MAX_SIZE / (uint16)FEE_BYTE_NUM_04];

    ReqDataLen = CPUDTFInfo->u2MovDataLen;
    FlashDataAreaAbsAddr = Fee_Record_StateCmCmAsubGetDatRecFromMngRec( CPUDTFInfo->u4MoveSrcAddress, CPUDTFInfo->u1MainBlockNo );

    /* Calculate check sum of data. */
    ExecLimit = Fee_Record_StateScCmAsubCalOneTimeCSSize( Fee_Record_CompleteLen, ReqDataLen );

    for( ExecCounter = 0U; ExecCounter < ExecLimit; ExecCounter += FEE_RECORD_SYNC_READ_MAX_SIZE )
    {
        ReadDataLen = ExecLimit - ExecCounter;
        if( ReadDataLen > FEE_RECORD_SYNC_READ_MAX_SIZE )
        {
            ReadDataLen = FEE_RECORD_SYNC_READ_MAX_SIZE;
        }

        /* Return value is not checked. */
        (void)Fee_DfcMpu_SyncRead( ( FlashDataAreaAbsAddr + ExecTargetPos ), (uint8 *)ReadBuffer, (uint32)ReadDataLen );
        /* Fee_Record_StateScMsAsubCalCS_INT30_01 */
        /* Wraparound may occur due to CS calculations. */
        /* No problem because CS calculation causes wraparound as intended. */
        TmpCheckSumData += Fee_Record_StateScCmAsubCalcCS( (uint8 *)ReadBuffer, ReadDataLen );
        ExecTargetPos += ReadDataLen;
    }

    /* Update global variables for calculating check sum. */
    Fee_Record_CompleteLen  = ExecTargetPos;
    /* Fee_Record_StateScMsAsubCalCS_INT30_02 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Fee_Record_CheckSumVal += TmpCheckSumData;

    /* Check that calculating a check sum have been completed. */
    if( ReqDataLen <= ExecTargetPos )
    {
        *DstCheckResult = Fee_Record_StateScCmAsubCmpCS( Fee_Record_CheckSumVal, FlashDataAreaAbsAddr, ReqDataLen );
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubSrchId                           */
/* Description   | Function to search a record by ID from a data flash.     */
/* Preconditions | None                                                     */
/* Parameters    | TargetId                                                 */
/*               | DataLength                                               */
/*               | TargetSector                                             */
/*               | ptstCPUDTFInfo                                           */
/* Return Value  | Searched result.                                         */
/*               |  FEE_STATUS_OK      TargetId is found.                   */
/*               |  FEE_STATUS_NG      TargetId is not found.               */
/*               |  FEE_STATUS_BUSY    Search in progress                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubSrchId(
    uint16 TargetId,
    uint16 DataLength,
    uint8  TargetSector,
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo
){
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tReadSrchAddress;                 /* 検索アドレス */
    sint32          s4tSrchRemainCount;                 /* 検索処理可能回数 */
    uint32          u4tSearchEndAddress;                /* 検索終了アドレス */
    uint16          u2tReadDataID;                      /* データFlash読出しデータ、DATA-ID */
    uint8           u1tCompareResult;

    /* ローカル変数(レジスタ変数)にロード */
    u4tReadSrchAddress = ptstCPUDTFInfo->u4ReadSrchAddress;
    s4tSrchRemainCount = (sint32)ptstCPUDTFInfo->u4SrchRemainCount;
    u4tSearchEndAddress = FEE_BLKSTARTADDRTBL[TargetSector] + FEE_STARTRECORDPOS;

    /* 戻り値をデータなし(STATUS_NG)に設定 */
    u4tReturn = FEE_STATUS_NG;

    /* 検索開始アドレスからレコード長分デクリメントしながらブロック先頭レコードアドレス以下の間ループ */
    while ( ( u4tSearchEndAddress <= u4tReadSrchAddress )
                && ( u4tReturn == FEE_STATUS_NG )
                && ( (sint32)FEE_SRCH_REMAIN_COUNT_ZERO < s4tSrchRemainCount ) )
    {
        /* 検索処理可能回数をデクリメント */
        s4tSrchRemainCount--;
        /* Check DATA-ID. */
        /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncReadUint16( ( u4tReadSrchAddress + (uint32)FEE_RECORD_FORMAT_OFFSET_ID ), &u2tReadDataID );
#else
        (void)Fee_DfcMpu_SyncReadUint16( u4tReadSrchAddress, &u2tReadDataID );
#endif
        if ( u2tReadDataID == TargetId )
        {
            /* 一致した場合 */
            /* Check Write-CHECK. */
            u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( ( u4tReadSrchAddress + (uint32)FEE_WRITECHECKPOS ), &Fee_FixWCData[0] );
            if ( u1tCompareResult == FEE_DFCMPU_RESULT_OK )
            {
                /* Write-CHECKが有効だった場合 */
                u4tReturn = Fee_Record_StateScCmAsubChkAddr( u4tReadSrchAddress, DataLength );
            }
        }
        /* 検索アドレスをレコード長分デクリメント */
        u4tReadSrchAddress -= (uint32)FEE_RECORDMNGINFOLEN;
    }
    if ( ( u4tReturn == FEE_STATUS_NG ) && ( u4tSearchEndAddress <= u4tReadSrchAddress ) )
    {
        /* 指定データが見つからず、かつ、検索アドレスがブロック先頭レコードアドレス以上のとき */
        /* 戻り値を処理継続中(STATUS_BUSY)に設定 */
        u4tReturn = FEE_STATUS_BUSY;
    }
    /* 検索アドレスを書き戻し */
    if ( ( u4tReturn == FEE_STATUS_NG) || (u4tReturn == FEE_STATUS_BUSY ) )
    {
        /* 指定データが見つからない場合 */
        ptstCPUDTFInfo->u4ReadSrchAddress = u4tReadSrchAddress;
    }
    else
    {
        /* 指定データ(WC有効)が見つかった場合 */
        /* 検索アドレスをレコード長分インクリメント */
        ptstCPUDTFInfo->u4ReadSrchAddress = u4tReadSrchAddress + (uint32)FEE_RECORDMNGINFOLEN;
    }
    /* 検索処理可能回数を書き戻し */
    if ( s4tSrchRemainCount < (sint32)FEE_SRCH_REMAIN_COUNT_ZERO )
    {
        /* 検索処理可能回数がマイナスの場合 */
        /* 検索処理可能回数を0に設定 */
        ptstCPUDTFInfo->u4SrchRemainCount = 0UL;
    }
    else
    {
        /* 検索処理可能回数を書き戻し */
        ptstCPUDTFInfo->u4SrchRemainCount = (uint32)s4tSrchRemainCount;
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ転送用有効データ検索                                 */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理結果                                                   */
/*               ：  0x00000000 ：FEE_STATUS_OK   ：データあり     */
/*               ：  0x00000001 ：FEE_STATUS_NG   ：データなし     */
/*               ：  0x00000005 ：FEE_STATUS_BUSY ：検索中         */
/* グローバル変数：                                                           */
/* その他        ：検索はMoveSrcAddressから開始し、結果アドレスで更新します   */
/*               ：データありの場合：見つかったレコードのアドレス             */
/*               ：データなしの場合：ブロックの先頭レコードアドレス－レコード長 */
/*               ：検索中の場合：次に検索するアドレス                         */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubSrchValid(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo
){
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tSearchEndAddress;                /* 検索終了アドレス */
    uint32          u4tMoveSrcAddress;                  /* 検索アドレス */
    sint32          s4tSrchRemainCount;                 /* 検索処理可能回数 */
    uint16          u2tDataLen;
    uint16          u2tReadBlockNumber;
    uint8           u1tAreaNo;
    uint8           u1tBlankCheckResult;
    uint8           u1tCompareResult;
    boolean         bCheckIdResult;
    Std_ReturnType  rtGetLenResult;

    /* ローカル変数(レジスタ変数)にロード */
    u4tMoveSrcAddress = ptstCPUDTFInfo->u4MoveSrcAddress;
    s4tSrchRemainCount = (sint32)ptstCPUDTFInfo->u4SrchRemainCount;
    u1tAreaNo = ptstCPUDTFInfo->u1AreaNum;
    /* ブロック先頭レコードアドレス算出 */
    u4tSearchEndAddress = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo] + FEE_STARTRECORDPOS;
    
    /* 戻り値をデータなし(STATUS_NG)に設定 */
    u4tReturn = FEE_STATUS_NG;

    /* 検索開始アドレスからレコード長分デクリメントしながらブロック先頭レコードアドレス以下の間ループ */
    while ( ( u4tSearchEndAddress <= u4tMoveSrcAddress )
                && ( u4tReturn == FEE_STATUS_NG )
                && ( (sint32)FEE_SRCH_REMAIN_COUNT_ZERO <  s4tSrchRemainCount ) )
    {
        /* 検索処理可能回数をデクリメント */
        s4tSrchRemainCount--;

        u1tBlankCheckResult = Fee_DfcMpu_SyncBlankCheck( ( u4tMoveSrcAddress + (uint32)FEE_DATASTATUSPOS ), (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
        if ( u1tBlankCheckResult == FEE_DFCMPU_RESULT_OK )
        {
            /* DATA-STATUSが有効だった場合 */
            /* Check Write-CHECK. */
            u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( ( u4tMoveSrcAddress + (uint32)FEE_WRITECHECKPOS ), &Fee_FixWCData[0] );
            if ( u1tCompareResult == FEE_DFCMPU_RESULT_OK )
            {
                /* Write-CHECKが有効だった場合 */
                /* Check a block number. */
                /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncReadUint16( ( u4tMoveSrcAddress + (uint32)FEE_RECORD_FORMAT_OFFSET_ID ), &u2tReadBlockNumber );
#else
        (void)Fee_DfcMpu_SyncReadUint16( u4tMoveSrcAddress, &u2tReadBlockNumber );
#endif
                bCheckIdResult = Fee_Record_StateScCmAsubChkId( u2tReadBlockNumber, u1tAreaNo );
                if( bCheckIdResult == (boolean)TRUE )
                {
                    /* Get the data length from the block number written data flash. */
                    rtGetLenResult = Fee_Legacy_GetDataLength( u2tReadBlockNumber, &u2tDataLen );
                    if( rtGetLenResult == (Std_ReturnType)E_OK )
                    {
                        u4tReturn = Fee_Record_StateScCmAsubChkAddr( u4tMoveSrcAddress, u2tDataLen );
                    }
                }
            }
        }

        /* 検索アドレスをレコード長分デクリメント */
        u4tMoveSrcAddress -= (uint32)FEE_RECORDMNGINFOLEN;
    }
    if ( ( u4tReturn == FEE_STATUS_NG ) && ( u4tSearchEndAddress <= u4tMoveSrcAddress ) )
    {
        /* 最終データ位置が見つからず、かつ、検索アドレスがブロック先頭レコードアドレス以上のとき */
        /* 戻り値を処理継続中(STATUS_BUSY)に設定 */
        u4tReturn = FEE_STATUS_BUSY;
    }
    /* 検索アドレスを書き戻し */
    if ( u4tReturn == FEE_STATUS_OK )
    {
        /* 最終データ位置が見つかった場合 */
        /* 検索アドレスをレコード長分インクリメント */
        ptstCPUDTFInfo->u4MoveSrcAddress = u4tMoveSrcAddress + (uint32)FEE_RECORDMNGINFOLEN;
        ptstCPUDTFInfo->u2MovDataId  = u2tReadBlockNumber;
        ptstCPUDTFInfo->u2MovDataLen = u2tDataLen;
    }
    else
    {
        /* 最終データ位置が見つからない場合 */
        ptstCPUDTFInfo->u4MoveSrcAddress = u4tMoveSrcAddress;
    }
    /* 検索処理可能回数を書き戻し */
    if ( s4tSrchRemainCount < (sint32)FEE_SRCH_REMAIN_COUNT_ZERO )
    {
        /* 検索処理可能回数がマイナスの場合 */
        /* 検索処理可能回数を0に設定 */
        ptstCPUDTFInfo->u4SrchRemainCount = 0UL;
    }
    else
    {
        /* 検索処理可能回数を書き戻し */
        ptstCPUDTFInfo->u4SrchRemainCount = (uint32)s4tSrchRemainCount;
    }

    /* 戻り値を返却して処理終了 */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubChkAddr                          */
/* Description   | Function to check an address element of a record.        */
/* Preconditions | None                                                     */
/* Parameters    | TgtRcrdMngInfoAddr                                       */
/*               | DataLength                                               */
/* Return Value  | Check result.                                            */
/*               |      FEE_STATUS_OK                                       */
/*               |      FEE_STATUS_NG                                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubChkAddr(
    uint32 TgtRcrdMngInfoAddr,
    uint16 DataLength
){
    uint32 Rtn                          = FEE_STATUS_NG;
    uint32 RelativeNextDataRcrdAddress;
    uint32 DataAreaRcrdLength;
    uint16 DataAreaRelativeAddress;

    /* Return value is not checked. */
    (void)Fee_DfcMpu_SyncReadUint16( ( TgtRcrdMngInfoAddr + (uint32)FEE_RECORD_FORMAT_OFFSET_DATAADDR ), &DataAreaRelativeAddress );
    DataAreaRcrdLength = Fee_Record_GetDataAreaRcrdLen( DataLength );
    RelativeNextDataRcrdAddress = DataAreaRelativeAddress + DataAreaRcrdLength;

    if( (uint32)FEE_DATA_FLASH_SECTOR_SIZE >= RelativeNextDataRcrdAddress )
    {
        if(( DataAreaRelativeAddress % (uint16)FEE_DATA_FLASH_READ_SIZE ) == (uint16)FEE_RECORD_VAL_ZERO_FOR_CHECK_MULTIPLE )
        {
            Rtn = FEE_STATUS_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubRdChkDS                          */
/* Description   | Function to read DS from a data flash, and check that    */
/*               | DS value is valid or invalid.                            */
/* Preconditions | None                                                     */
/* Parameters    | TgtRcrdMngInfoAddr                                       */
/* Return Value  | Check result.                                            */
/*               |      FEE_STATUS_OK      : DS value is valid.             */
/*               |                           DS area is blank.              */
/*               |      FEE_STATUS_INVALID : DS value is invalid.           */
/*               |                           DS area is not blank.          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubRdChkDS(
    uint32 TgtRcrdMngInfoAddr
){
    uint32 RtnResult = FEE_STATUS_INVALID;
    uint8  BlankCheckResult;

    BlankCheckResult = Fee_DfcMpu_SyncBlankCheck( ( TgtRcrdMngInfoAddr + (uint32)FEE_DATASTATUSPOS ), (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
    if( BlankCheckResult == FEE_DFCMPU_RESULT_OK )
    {
        RtnResult = FEE_STATUS_OK;
    }

    return RtnResult;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubCalOneTimeCSSize                 */
/* Description   | This function to calculate the size to calculate         */
/*               | check sum in one time.                                   */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint16, FEE_CODE )
Fee_Record_StateScCmAsubCalOneTimeCSSize (
    uint16 CompleteLen,
    uint16 DataLen
){
    uint16 RtnCalcCSSize = Fee_MaxCalcCheckSumBytes;
    uint16 RemainLen     = DataLen - CompleteLen;

    if( RtnCalcCSSize > RemainLen )
    {
        RtnCalcCSSize = RemainLen;
    }

    return RtnCalcCSSize;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubCalCSIdAddr                      */
/* Description   | Function to calculate the check sum with the following.  */
/*               |     The unlock value.                                    */
/*               |     The blocknumber of the record with flash data.       */
/*               |     The data address of the record with flash data.      */
/*               |     The management record address                        */
/* Preconditions | None                                                     */
/* Parameters    | MngRecAddr                                               */
/* Return Value  | Check sum value.                                         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubCalCSIdAddr(
    uint32 MngRecAddr
){
    uint32 DataIdData[FEE_RECORD_SIZE_BLOCKNUM_DATAADDR / FEE_BYTE_NUM_04];
    /* Fee_Record_StateScCmAsubCalCSIdAddr_INT30_01 */
    /* Fee_Record_StateScCmAsubCalCSIdAddr_INT30_02 */
    /* Wraparound may occur */
    uint32 Rtn;

    Rtn = FEE_CHECKSUM_UNLOCK_VAL;

    /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncRead( ( MngRecAddr + (uint32)FEE_RECORD_FORMAT_OFFSET_ID ), (uint8 *)DataIdData, (uint32)FEE_RECORD_SIZE_BLOCKNUM_DATAADDR );
#else
        (void)Fee_DfcMpu_SyncRead( MngRecAddr, (uint8 *)DataIdData, (uint32)FEE_RECORD_SIZE_BLOCKNUM_DATAADDR );
#endif
    /* Fee_Record_StateScCmAsubCalCSIdAddr_INT30_01 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Rtn += Fee_Record_StateScCmAsubCalcCS( (uint8 *)DataIdData, FEE_RECORD_SIZE_BLOCKNUM_DATAADDR );

    /* Fee_Record_StateScCmAsubCalCSIdAddr_INT30_02 */
    /* Wraparound may occur due to CS calculations. */
    /* No problem because CS calculation causes wraparound as intended. */
    Rtn += Fee_Record_StateCmCmAsubCalcMngAddrCS( MngRecAddr );

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubCmpCS                            */
/* Description   | This function to compare two check sum values as follow. */
/*               |      1. An expectation check sum value.                  */
/*               |      2. A written check sum value on the flash.          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, FEE_CODE )
Fee_Record_StateScCmAsubCmpCS (
    uint32 ExpectValue,
    uint32 RecordDataAreaAbsAddr,
    uint16 DataLen
){
    boolean Rtn = FALSE;
    uint16  DataPadCsFlagLen;
    uint16  DataPadLen;
    uint32  ReadFlashUint32;

    DataPadCsFlagLen = Fee_Record_GetDataAreaRcrdLen( DataLen );
    DataPadLen   = DataPadCsFlagLen - ( (uint16)FEE_RECORD_SIZE_CHECKSUM + (uint16)FEE_DFLASH_FORMAT_XFLAG_SIZE );
    /* Return value is not checked. */
    (void)Fee_DfcMpu_SyncReadUint32( ( RecordDataAreaAbsAddr + (uint32)DataPadLen ), &ReadFlashUint32 );

    if ( ExpectValue == ReadFlashUint32 )
    {
        Rtn = TRUE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubChkId                            */
/* Description   | Function to check that a block number is inside of the   */
/*               | valid range.                                             */
/* Preconditions | None                                                     */
/* Parameters    | BlockNumber                                              */
/*               | AreaNo                                                   */
/* Return Value  | Check result.                                            */
/*               |  TRUE  : A block number is inside of the valid range.    */
/*               |  FALSE : A block number is outside of the valid range.   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, FEE_CODE )
Fee_Record_StateScCmAsubChkId(
    uint16 BlockNumber,
    uint8  AreaNo
){
    boolean         Rtn = FALSE;
    Std_ReturnType  GetAreaResult;
    uint8           AreaNoFromCfg;

    GetAreaResult = Fee_Pif_GetAreaNoFromBlockNumber( BlockNumber, &AreaNoFromCfg );
    if( GetAreaResult == (Std_ReturnType)E_OK )
    {
        if( AreaNoFromCfg == AreaNo )
        {
            Rtn = TRUE;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubGetRecPos                        */
/* Description   | Function to get a record position from RECORDPOSTBL.     */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | TargetSector                                             */
/*               | BlockNumber                                              */
/*               | DataLength                                               */
/*               | DstRecordPos : Output argument. A record position .      */
/* Return Value  | The result of getting a record position.                 */
/*               |  FEE_STATUS_OK     : A record position is registered.    */
/*               |  FEE_STATUS_NODATA : A record position is unregistered.  */
/*               |  FEE_STATUS_NG     : A record position data is broken.   */
/*               |                     Or RECORDPOSTBL has been turned off. */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubGetRecPos(
    uint8  AreaNo,
    uint8  TargetSector,
    uint16 BlockNumber,
    uint16 DataLength,
    P2VAR( uint32, AUTOMATIC, TYPEDEF ) DstRecordPos
){
    uint32          Rtn;
    uint32          CheckDataResult;
    uint32          TopMngRecordAddress;
    uint32          TargetMngRecordAddress;
    uint16          RecordPos;

    /* Gets a record position and checks it. */
    Rtn = Fee_RecordPosTbl_GetPos( AreaNo, BlockNumber, &RecordPos );
    if( Rtn == FEE_STATUS_OK )
    {
        TopMngRecordAddress = FEE_BLKSTARTADDRTBL[TargetSector] + FEE_STARTRECORDPOS;
        TargetMngRecordAddress = ( (uint32)RecordPos * (uint32)FEE_RECORDMNGINFOLEN ) + TopMngRecordAddress;
        CheckDataResult = Fee_Record_StateScCmAsubChkFlash( TargetMngRecordAddress, BlockNumber, DataLength );
        if( CheckDataResult == FEE_STATUS_NG )
        {
            Rtn = FEE_STATUS_NG;
        }
    }

    /* Sets output values */
    if( Rtn == FEE_STATUS_OK )
    {
        *DstRecordPos = TargetMngRecordAddress;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubChkFlash                         */
/* Description   | Function to check a record in a data flash.              */
/*               | Check target is the following.                           */
/*               |      ID, D.ADDR, WC                                      */
/* Preconditions | None                                                     */
/* Parameters    | RecMngAbsAddr                                            */
/*               | BlockNumber                                              */
/*               | DataLength                                               */
/* Return Value  | The result of getting a record position.                 */
/*               |  FEE_STATUS_OK : The record is valid.                    */
/*               |  FEE_STATUS_NG : The record is invalid or error.         */
/* Notes         | This function doesn't check other than listed above.     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubChkFlash(
    uint32 RecMngAbsAddr,
    uint16 BlockNumber,
    uint16 DataLength
){
    uint32          Rtn                 = FEE_STATUS_NG;
    uint16          ReadFlashUint16;
    uint8           CompareResult;

    /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncReadUint16( ( RecMngAbsAddr + (uint32)FEE_RECORD_FORMAT_OFFSET_ID ), &ReadFlashUint16 );
#else
        (void)Fee_DfcMpu_SyncReadUint16( RecMngAbsAddr, &ReadFlashUint16 );
#endif
    if ( ReadFlashUint16 == BlockNumber )
    {
        CompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( ( RecMngAbsAddr + (uint32)FEE_WRITECHECKPOS ), &Fee_FixWCData[0] );
        if ( CompareResult == FEE_DFCMPU_RESULT_OK )
        {
            Rtn = Fee_Record_StateScCmAsubChkAddr( RecMngAbsAddr, DataLength );
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateScCmAsubCalcCS                           */
/* Description   | Function to calculate check sum of data                  */
/* Preconditions | None                                                     */
/* Parameters    | TargetAddressPtr : Pointer to target data buffer         */
/*               | Length           : Number of bytes of data               */
/* Return Value  | Check sum                                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubCalcCS(
    P2CONST(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint16                             Length
){
    uint16 Counter;
    uint32 Rtn;

    Rtn = FEE_RECORD_CHECKSUM_INIT_VAL_ZERO;
    for( Counter = 0U; Counter < Length; Counter++ )
    {
        Rtn += (uint32)TargetAddressPtr[Counter];
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateCmCmAsubCalcMngAddrCS                    */
/* Description   | Function to calculate a check sum with a record          */
/*               | address of a management area.                            */
/* Preconditions | None                                                     */
/* Parameters    | MngRecAddr                                               */
/* Return Value  | Check sum.                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateCmCmAsubCalcMngAddrCS(
    uint32 MngRecAddr
){
    uint32 Rtn;
    uint32 RelAddr;
    uint32 MngAddrVal00To07;
    uint32 MngAddrVal08To15;

    RelAddr = Fee_ConvAddr_AbsToSectorTopRelative( MngRecAddr );

    MngAddrVal00To07 = RelAddr & (uint32)FEE_RECORD_MASKNUM_00_TO_07_BIT;

    MngAddrVal08To15 = RelAddr & (uint32)FEE_RECORD_MASKNUM_08_TO_15_BIT;
    MngAddrVal08To15 = MngAddrVal08To15 >> FEE_RECORD_SHIFTNUM_8_BIT;

    Rtn = MngAddrVal08To15 + MngAddrVal00To07;

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateCmCmAsubGetDatRecFromMngRec              */
/* Description   | Function to get an absolute address of a record          */
/*               | in a data area from a record in a management area.       */
/* Preconditions | None                                                     */
/* Parameters    | MngRecAddr                                               */
/*               | SectorNo                                                 */
/* Return Value  | An absolute address of a record in a data area.          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Record_StateCmCmAsubGetDatRecFromMngRec(
    uint32 MngRecAddr,
    uint8  SectorNo
){

    uint16  DataAreaRelativeAddress;
    uint32  DataAreaAbsoluteAddress;

    /* Return value is not checked. */
    (void)Fee_DfcMpu_SyncReadUint16( ( MngRecAddr + (uint32)FEE_RECORD_FORMAT_OFFSET_DATAADDR ), &DataAreaRelativeAddress );
    DataAreaAbsoluteAddress = FEE_BLKSTARTADDRTBL[SectorNo] + (uint32)DataAreaRelativeAddress;

    return DataAreaAbsoluteAddress;
}

/****************************************************************************/
/* Function Name | Fee_Record_StateCmCmAsubSetRecPos                        */
/* Description   | Function to set a record position to RECORDPOSTBL.       */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | SectorNo                                                 */
/*               | BlockNumber                                              */
/*               | MngAbsAddr                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Record_StateCmCmAsubSetRecPos(
    uint8  AreaNo,
    uint8  SectorNo,
    uint16 BlockNumber,
    uint32 MngAbsAddr
){
    uint32 RecMngAbsTopAddr; 
    uint16 RecordPos;

    RecMngAbsTopAddr = FEE_BLKSTARTADDRTBL[SectorNo] + FEE_STARTRECORDPOS;
    RecordPos        = (uint16)( ( MngAbsAddr - RecMngAbsTopAddr ) / (uint32)FEE_RECORDMNGINFOLEN );

    Fee_RecordPosTbl_SetPos( AreaNo, BlockNumber, RecordPos );

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/11/18                                              */
/*  2-0-0          :2023/01/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
