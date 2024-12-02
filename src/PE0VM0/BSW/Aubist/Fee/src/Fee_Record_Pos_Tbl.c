/* Fee_Record_Pos_Tbl.c v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/POS/TBL/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Const.h"
#include "../inc/Fee_Mpu_Dev_Const.h"

#include "../inc/Fee_Record_Pos_Tbl.h"
#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Record_Pos_Tbl_Internal.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Pif.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_DfcMpu.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
/* 有効レコード位置TBL有効フラグ */
#define FEE_RPTBLFIXED          ((uint8)0x03U)      /* TBL作成済み */
#define FEE_RPTBLERASED         ((uint8)0x0CU)      /* TBL未作成 */
#define FEE_RPTBLMAKING         ((uint8)0x30U)      /* TBL作成中 */

/* 有効レコード位置TBL有効フラグ(ミラー) */
#define FEE_RPTBL_MRR_FIXED         ((uint8)0xFCU)         /* TBL作成済み(ミラー) */
#define FEE_RPTBL_MRR_ERASED        ((uint8)0xF3U)        /* TBL未作成(ミラー) */
#define FEE_RPTBL_MRR_MAKING        ((uint8)0xCFU)        /* TBL作成中(ミラー) */

#define FEE_RPTBL_VALID_FLAG_COMPARE_MATCH    ((uint8)0xFFU)    /* TBL作成状態一致判定 */

/* 有効レコード位置TBL状態 */
#define FEE_RPSTATUS_VALID      ((uint32)0x00000000UL)  /* TBL有効状態 */
#define FEE_RPSTATUS_INVALID    ((uint32)0x00000001UL)  /* TBL無効状態 */
#define FEE_RPSTATUS_ERROR      ((uint32)0x00000002UL)  /* TBL異常状態 */

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

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

#if ( FEE_RECORDPOSTBL_ENABLE == STD_ON )

VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddress;
VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddressMrr;

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：有効レコード位置TBL初期化                                  */
/* 入  力        ：uint8 u1AreaNum ：初期化するエリアの番号                   */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosArea(
    uint8 u1AreaNum
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint16          u2tTableIndex;                      /* TBLインデックス */
    uint16          u2tInitDataSize;                    /* 初期化サイズ */

    /* 有効レコード位置TBL有効フラグを「未作成」に設定 */
    Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLERASED;
    Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_ERASED;
    
    /* 引数エリア先頭IDのインデックスを取得 */
    u2tTableIndex = Fee_OffsetPos[u1AreaNum];
    /* 引数エリアのDATA-ID数を取得 */
    u2tInitDataSize = Fee_AreaInfTBL[u1AreaNum].u2UseDataIdNum;
    
    /* メイン初期化 */
    Fee_RecordPosTbl_SetMemoryU2( &Fee_RecordPosTBL[u2tTableIndex],    FEE_IDNONE,      u2tInitDataSize );
    /* サブ初期化 */
    Fee_RecordPosTbl_SetMemoryU2( &Fee_RecordPosTBLMrr[u2tTableIndex], FEE_ID_MRR_NONE, u2tInitDataSize );

    /* TBL作成検索アドレス初期化 */
    Fee_TBLMakeSrcAddress    = FEE_ADDRESS_INVALID;
    Fee_TBLMakeSrcAddressMrr = (uint32)(~Fee_TBLMakeSrcAddress);
#endif /* FEE_RECORDPOSTBL_ENABLE == ON */

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：全エリア有効レコード位置TBL初期化処理                      */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosAll( void )
{
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

    uint8 AreaCounter;
    uint8 TotalAreaNum;

    TotalAreaNum = Fee_AreaNumber;

    for ( AreaCounter = 0U; AreaCounter < TotalAreaNum; AreaCounter++ )
    {
        Fee_RecordPosTbl_ClearPosArea( AreaCounter );
    }

    return;

#else
    return;
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_ReadyPosArea                            */
/* Description   | Function to get ready to use a record position table.    */
/*               | READY means checking status of a record                  */
/*               | position table and making a record position table        */
/*               | as necessary.                                            */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum                                                */
/*               | u1BlockNum                                               */
/*               | u4SrchAddress                                            */
/* Return Value  | The activation result.                                   */
/*               |      FEE_STATUS_OK   : To activate a table has been      */
/*               |                        finished successfully.            */
/*               |      FEE_STATUS_NG   : To activate a table was failure.  */
/*               |                        RECORDPOSTBL is disabled.         */
/*               |      FEE_STATUS_BUSY : To activate a table has not been  */
/*               |                        finished yet.                     */
/* Notes         | 1. Only when FEE_RECORDPOSTBL_ENABLE is STD_ON,          */
/*               |    FEE_STATUS_OK/BUSY are returned.                      */
/*               | 2. Only when FEE_RECORDPOSTBL_ENABLE is STD_OFF,         */
/*               |    FEE_STATUS_NG is returned.                            */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_ReadyPosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
){
    uint32          u4tReturn;                          /* 戻り値 */
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint32          u4tValidityResult;                  /* 有効性チェック結果 */
    uint32          u4tMakeRecordPosTblResult;          /* 有効レコード位置TBL作成結果 */

    /* 有効レコード位置TBLの有効性確認 */
    u4tValidityResult = Fee_RecordPosTbl_GetStatusArea( u1AreaNum );
    if ( u4tValidityResult == FEE_RPSTATUS_VALID )
    {
        /* 有効レコード位置TBLが「有効」の場合、有効レコード位置TBL作成不要 */
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        if( u4tValidityResult == FEE_RPSTATUS_INVALID )
        {
            /* 有効レコード位置TBLが「無効」の場合、有効レコード位置TBL作成 */
            u4tMakeRecordPosTblResult = Fee_RecordPosTbl_MakePosArea( u1AreaNum, u1BlockNum, u4SrchAddress );
        }
        else
        {
            /* 有効レコード位置TBLが「異常」の場合、有効レコード位置TBLを初期化して作成 */
            Fee_RecordPosTbl_ClearPosArea( u1AreaNum );
            u4tMakeRecordPosTblResult = Fee_RecordPosTbl_MakePosArea( u1AreaNum, u1BlockNum, u4SrchAddress );
        }

        /* 有効レコード位置TBL作成完了の場合 */
        if ( u4tMakeRecordPosTblResult == FEE_STATUS_OK )
        {
            u4tReturn = FEE_STATUS_OK;
        }
        /* 有効レコード位置TBL作成未完了の場合 */
        else
        {
            u4tReturn = FEE_STATUS_BUSY;
        }
    }

#else /* FEE_RECORDPOSTBL_ENABLE == STD_OFF */
    u4tReturn = FEE_STATUS_NG;
#endif/* FEE_RECORDPOSTBL_ENABLE == *** */

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_GetPos                                  */
/* Description   | Function to get a record position from a record          */
/*               | position table.                                          */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum                                                */
/*               | u2DataNum                                                */
/*               | ptu2RecordPos : Output argument. A record position.      */
/* Return Value  | The result of getting a record position.                 */
/*               |  FEE_STATUS_OK     : A record position is registered.    */
/*               |  FEE_STATUS_NODATA : A record position is unregistered.  */
/*               |  FEE_STATUS_NG     : A record position data is broken.   */
/*               |                    Or This function has been turned off. */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    P2VAR(uint16, AUTOMATIC, TYPEDEF) ptu2RecordPos
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint32          u4tReturn;                          /* 戻り値 */
    uint16          u2tTableIndex;                      /* TBLインデックス */
    uint16          u2tRecordPos;                       /* 有効レコード位置*/
    uint16          u2tRecordPosMrr;                    /* 有効レコード位置(ミラー) */
    Std_ReturnType  GetTblIdxResult;
    
    u4tReturn = FEE_STATUS_NG;

    /* TBLインデックスを算出 */
    GetTblIdxResult = Fee_RecordPosTbl_GetTblIdx( u1AreaNum, u2DataNum, &u2tTableIndex );

    if ( GetTblIdxResult == (Std_ReturnType)E_OK )
    {
        /* 有効レコード位置を取得 */
        u2tRecordPos    = Fee_RecordPosTBL[u2tTableIndex];
        u2tRecordPosMrr = Fee_RecordPosTBLMrr[u2tTableIndex];
        /* 取得データの一致確認 */
        if ( u2tRecordPos == (uint16)(~u2tRecordPosMrr) )
        {
            /* 取得データが未登録でないか確認(未登録の場合はデータなしを返す) */
            if ( u2tRecordPos != FEE_IDNONE )
            {
                u4tReturn = FEE_STATUS_OK;
                *ptu2RecordPos = u2tRecordPos;
            }
            else
            {
                u4tReturn = FEE_STATUS_NODATA;
            }
        }
    }

    return u4tReturn;
#else /* FEE_RECORDPOSTBL_ENABLE == STD_OFF */
    return FEE_STATUS_NG;
#endif /* FEE_RECORDPOSTBL_ENABLE */
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：有効レコード位置設定                                       */
/* 入  力        ：u1AreaNum          ：エリア番号                            */
/*               ：u2DataNum          ：ID番号                                */
/*               ：u2RecordPos        ：有効レコード位置                      */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    uint16 u2RecordPos
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint16          u2tTableIndex;                      /* TBLインデックス */
    Std_ReturnType  GetTblIdxResult;

    /* TBLインデックスを算出 */
    GetTblIdxResult = Fee_RecordPosTbl_GetTblIdx( u1AreaNum, u2DataNum, &u2tTableIndex );

    if ( GetTblIdxResult == (Std_ReturnType)E_OK )
    {
        /*  有効レコード位置TBLに設定 */
        Fee_RecordPosTBL[u2tTableIndex]    = u2RecordPos;
        Fee_RecordPosTBLMrr[u2tTableIndex] = (uint16)(~u2RecordPos);
    }
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

    return;
}

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：有効レコード位置TBL作成                                    */
/* 入  力        ：u1AreaNum                ：エリア番号                      */
/*               ：u1BlockNum               ：ブロック番号番号                */
/*               ：u4SrchAddress           ：検索アドレス                     */
/*               ：stCPUDTF  *ptstCPUDTFInfo                                  */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：有効レコード位置TBL作成結果                                */
/*               ：  0x00000000 ： FEE_STATUS_OK   ：作成完了                 */
/*               ：  0x00000001 ： FEE_STATUS_NG   ：作成未完了               */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_MakePosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
){
    uint32          u4tReturn;                          /* 戻り値 */
    uint32          u4tSearchEndAddress;                /* 検索終了アドレス */
    uint32          u4tGetRecordPosResult;              /* 有効レコード位置取得結果 */
    uint32          u4tLocalSrchAddress;                /* 検索アドレス */
    uint32          SrchRemainCount;                    /* 検索処理可能回数 */
    uint16          u2tDataNum;                         /* ID番号 */
    uint16          u2tRecordPos;                       /* 有効レコード位置 */
    uint8           u1tValidFlag;                       /* 有効フラグ */
    uint8           u1tCompareResult;                   /* result of comparision of Write-CHECK */

    /* ローカル変数(レジスタ変数)にロード */
    SrchRemainCount = Fee_CpuDtfInfo.u4SrchRemainCount;
    u4tReturn = FEE_STATUS_NG;

    /* ブロック先頭レコードアドレス算出 */
    u4tSearchEndAddress = FEE_BLKSTARTADDRTBL[u1BlockNum] + FEE_STARTRECORDPOS;

    /* 有効レコード位置TBL有効フラグが「作成中」の場合 */
    u1tValidFlag = Fee_RecordPosTBLValidFlag[u1AreaNum];

    if ( u1tValidFlag == FEE_RPTBLMAKING )
    {
        if(( Fee_TBLMakeSrcAddress ^ Fee_TBLMakeSrcAddressMrr ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
        {
            /* 前回中断時の最終検索アドレスを今回検索の開始アドレスとして設定 */
            u4tLocalSrchAddress = Fee_TBLMakeSrcAddress;
        }
        else
        {
            /* Note : This case is that Fee_TBLMakeSrcAddress has become garbled.                       */
            /*        So this function resets an address of initiating a search to u4SrchAddress.       */
            /*        However this function does not initialize record position data,                   */
            /*        because it checks that the latest position data has already been set using        */
            /*        Fee_RecordPosTbl_GetPos().                                                        */
            u4tLocalSrchAddress = u4SrchAddress;
        }
    }
    else
    {
        /* 有効レコード位置TBL有効フラグを「作成中」に設定 */
        Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLMAKING;
        Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_MAKING;

        /* 検索アドレスを「末尾レコードアドレス」に設定 */
        u4tLocalSrchAddress = u4SrchAddress;
    }
    
    /* 検索開始アドレスからレコード長分デクリメントしながらブロック先頭レコードアドレス以下の間ループ */
    while ( ( u4tSearchEndAddress <= u4tLocalSrchAddress )
                && ( (uint32)FEE_SRCH_REMAIN_COUNT_ZERO <  SrchRemainCount ) )
    {
        /* 検索処理可能回数をデクリメント */
        SrchRemainCount--;
        
        /* Check Write-CHECK. */
        u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( ( u4tLocalSrchAddress + (uint32)FEE_WRITECHECKPOS ), &Fee_FixWCData[0] );
        if ( u1tCompareResult == FEE_DFCMPU_RESULT_OK )
        {
            /* In case of Write-CHECK is valid. */
            /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncReadUint16( ( u4tLocalSrchAddress + FEE_RECORD_FORMAT_OFFSET_ID ), &u2tDataNum );
#else
        (void)Fee_DfcMpu_SyncReadUint16( u4tLocalSrchAddress, &u2tDataNum );
#endif
            /* 有効レコード位置取得 */
            u4tGetRecordPosResult = Fee_RecordPosTbl_GetPos( u1AreaNum, u2tDataNum, &u2tRecordPos );
            if ( u4tGetRecordPosResult == FEE_STATUS_NODATA )
            {
                /* 有効レコード位置取得失敗の場合、有効レコード位置設定 */
                Fee_RecordPosTbl_SetPos( u1AreaNum, u2tDataNum, 
                                            (uint16)( ( u4tLocalSrchAddress - u4tSearchEndAddress ) / (uint32)FEE_RECORDMNGINFOLEN ) );
            }
            else /* u4tGetRecordPosResult == FEE_STATUS_OK, FEE_STATUS_NG */
            {
                /* No process. This reason is below.                                            */
                /*      If FEE_STATUS_OK was returned, the latest data has already been set.    */
                /*      If FEE_STATUS_NG was returned, the record position has been broken.     */
                /*      In this case, this function doesn't change its position and             */
                /*      restoration activity will be executed when its position will be gotten.   */
            }
        }
        else
        {
            /* No process, in case of Write-CHECK error */
        }
        
        /* 検索アドレスをレコード長分デクリメント */
        u4tLocalSrchAddress -= (uint32)FEE_RECORDMNGINFOLEN;
    }
    

    /* 検索アドレスを書き戻し */
    if ( u4tSearchEndAddress > u4tLocalSrchAddress )
    {
        /* 全レコード検索したとき */
        /* TBL作成検索アドレスを初期化 */
        Fee_TBLMakeSrcAddress = FEE_ADDRESS_INVALID;
        /* 有効レコード位置TBLフラグを「作成済み」に設定 */
        Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLFIXED;
        Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_FIXED;
        /* 戻り値を作成完了(STATUS_OK)に設定 */
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        /* １定期処理あたりの検索数に到達した場合 */
        /* 今回の最終検索アドレスを保持 */
        Fee_TBLMakeSrcAddress = u4tLocalSrchAddress;
    }
    
    /* 検索処理可能回数を書き戻し */
    Fee_CpuDtfInfo.u4SrchRemainCount = SrchRemainCount;

    Fee_TBLMakeSrcAddressMrr = (uint32)(~Fee_TBLMakeSrcAddress);

    return u4tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：有効レコード位置TBLの有効性取得                            */
/* 入  力        ：uint8 u1AreaNum ：エリアの番号                             */
/* 出  力        ：有効性取得結果                                             */
/*               ：  0x00000000 ：FEE_RPSTATUS_VALID   ：有効                 */
/*               ：  0x00000001 ：FEE_RPSTATUS_INVALID ：無効                 */
/*               ：  0x00000002 ：FEE_RPSTATUS_ERROR   ：異常                 */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetStatusArea(
    uint8 u1AreaNum
){
    uint32          u4tReturn;                  /* 戻り値 */
    uint8           u1tValidFlag;               /* 有効フラグ */
    uint8           u1tValidFlagMrr;            /* 有効フラグミラー */

    u1tValidFlag = Fee_RecordPosTBLValidFlag[u1AreaNum];
    u1tValidFlagMrr = Fee_RecordPosTBLValidFlagMrr[u1AreaNum];
    if ( (u1tValidFlag ^ u1tValidFlagMrr) == FEE_RPTBL_VALID_FLAG_COMPARE_MATCH )
    {
        if ( u1tValidFlag == FEE_RPTBLFIXED )
        {
            /* 有効フラグが「作成済み」の場合 */
            u4tReturn = FEE_RPSTATUS_VALID;
        }
        else
        {
            /* 有有効フラグが「未作成」、「作成中」の場合 */
            u4tReturn = FEE_RPSTATUS_INVALID;
        }
    }
    else
    {
        u4tReturn = FEE_RPSTATUS_ERROR;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_GetTblIdx                               */
/* Description   | Function to get an index of the record position table.   */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo      : An area number.                            */
/*               | BlockNumber : A block number.                            */
/*               | RecPosTblIdx: An output parameter.                       */
/*               |               An index of the record position table.     */
/* Return Value  | Getting result.                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_RecordPosTbl_GetTblIdx(
    uint8  AreaNo,
    uint16 BlockNumber,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) RecPosTblIdx
){
    Std_ReturnType Rtn = E_NOT_OK;
    Std_ReturnType GetCfgTblIndexResult;

    uint16         CfgTblIdx;
    uint16         DatasetIdx;
    uint16         TmpRecPosTblIdx;
    uint16         RecPosTblSize;
    uint16         OffsetPos;

    GetCfgTblIndexResult = Fee_Pif_GetCfgTblIdxFromBlockNumber( BlockNumber, &CfgTblIdx );
    if( GetCfgTblIndexResult == (Std_ReturnType)E_OK )
    {
        Fee_Pif_GetDatasetIdxFromBlockNumber( BlockNumber, &DatasetIdx );

        OffsetPos = Fee_OffsetPos[AreaNo];
        TmpRecPosTblIdx = ( FeeRecPosTblIdx[CfgTblIdx] + DatasetIdx ) + OffsetPos;
        RecPosTblSize = Fee_RecordPosTBLSize;
        if ( TmpRecPosTblIdx < RecPosTblSize )
        {
            *RecPosTblIdx = TmpRecPosTblIdx;
            Rtn = E_OK;
        }
    }

    return Rtn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データのセット処理                                         */
/* 入  力        ：ptu2Dst           ：セット先アドレス                       */
/*               ：u2Data            ：セットするデータ                       */
/*               ：u2SetLen          ：セットサイズ                           */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetMemoryU2(
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) ptu2Dst,
    uint16 u2Data,
    uint16 u2SetLen
){
    uint16 Index;

    for( Index = 0U; Index < u2SetLen; Index++ )
    {
        ptu2Dst[Index] = u2Data;
    }

    return;
}
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
