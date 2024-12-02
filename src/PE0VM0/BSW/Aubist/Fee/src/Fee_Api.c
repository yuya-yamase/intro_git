/* Fee_Api.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/API/CODE                                              */
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

#include "../inc/Fee_Ram.h"

#include "../inc/Fee_FreeSpace.h"
#include "../inc/Fee_Record_Pos_Tbl.h"

#include "../inc/Fee_Api.h"
#include "../inc/Fee_Api_Internal.h"
#include <NvM_Ext.h>
#include <Mscd_Common.h>

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
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* 動作状態取得用テーブル */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_Legacy_GetStatusTBL[FEE_STATUSMAX] = 
{
    FEE_IDLING,     /* アイドル             ：待機中 */
    FEE_WRITING,    /* 書込み中             ：書込み中 */
    FEE_REBUILDING, /* 再編中               ：データ再編中 */
    FEE_ID_READING, /* ID指定データ読出し中 ：ID指定読出し中 */
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
/* 説  明        ：データ書込み要求                                           */
/* 入  力        ：uint16 data_id             ：書込みデータのID                  */
/*               ：const uint8  *data_address ：書込みデータの先頭アドレス */
/*               ：uint8 No                  ：書込みエリアの番号                */
/* 出  力        ：書込み要求受付結果                                         */
/*               ：  0x00 ：FEE_REQUEST_ACCEPT  ：要求受付            */
/*               ：  0x01 ：FEE_REQUEST_DECLINE ：要求拒否            */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint8, FEE_CODE) Fee_Legacy_WriteData( uint16 data_id, P2CONST(uint8, AUTOMATIC, TYPEDEF) data_address, uint8 No )
{
    uint8           u1tReturn;                          /* 戻り値 */
    uint16          DataLength;
    Std_ReturnType      DataLenResult;

    u1tReturn = FEE_REQUEST_DECLINE;

    if ( data_address != NULL_PTR )
    {
        /* 先頭アドレスがNULL以外 */
        /* データ書込み要求は受付可能? */
        if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
        {
            /* 動作状態がアイドルの場合は受付可能 */
            DataLength = FEE_LENGTH_00;
            DataLenResult = Fee_Legacy_GetDataLength( data_id, &DataLength);
            if( DataLenResult == (Std_ReturnType) E_OK )
            {
                /* MHA[データFlash]管理データ初期化 */
                Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
                /* エリア番号を保存 */
                Fee_CpuDtfInfo.u1AreaNum = No;
                /* 使用エリア選択処理 */
                Fee_SelectUseArea( &Fee_CpuDtfInfo );
                /* DATA-IDを保存 */
                Fee_CpuDtfInfo.u2DATA_ID = data_id;

                /* 要求データの保存 */
                Fee_CpuDtfInfo.ptu1ReqWriteAddr = data_address;
                Fee_CpuDtfInfo.u2ReqDataLen     = DataLength;

                /* メインタイマカウンタ設定 */
                Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtWriteTime;
                /* 動作状態を書込み中(STATUS_WRITE)に設定 */
                Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSWRITE;
                /* メイン状態をアイドル(MAIN_STATUS_WBIDLE)に設定 */
                Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSWBIDLE;
                /* 最終書込みレコード位置読出し処理 */
                /* Return value is not checked. */
                (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

                /* Set the sub of RAMs. */
                Fee_Block_SetUseBlockInfoSub();
                Fee_Lib_SetCpuDtfDataSub();

                /* 戻り値用変数に要求受付を設定 */
                u1tReturn = FEE_REQUEST_ACCEPT;
            }
        }
    }
    
    /* 上位層に要求受付結果を返す */
    return u1tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ読出し要求（ID指定読出し）                           */
/* 入  力        ：uint16 data_id ：読出データのID                                */
/*               ：uint8 No      ：読出しエリアの番号                            */
/* 出  力        ：ID指定読出し要求受付結果                                   */
/*               ：  0x00 ：FEE_REQUEST_ACCEPT  ：要求受付            */
/*               ：  0x01 ：FEE_REQUEST_DECLINE ：要求拒否            */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint8, FEE_CODE) Fee_Legacy_ReadData( uint16 data_id, uint8 No, P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr )
{
    uint8           u1tReturn;                          /* 戻り値 */
    uint16          DataLength;
    Std_ReturnType  DataLenResult;

    u1tReturn = FEE_REQUEST_DECLINE;

    if ( DataBufferPtr != NULL_PTR )
    {
        /* データ読出し要求（ID指定読出し）は受付可能? */
        if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
        {
            /* 動作状態がアイドルの場合は受付可能 */
            DataLength = FEE_LENGTH_00;
            DataLenResult = Fee_Legacy_GetDataLength( data_id, &DataLength);
            if( DataLenResult == (Std_ReturnType) E_OK )
            {
                /* MHA[データFlash]管理データ初期化 */
                Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
                /* エリア番号を保存 */
                Fee_CpuDtfInfo.u1AreaNum = No;
                /* 使用エリア選択処理 */
                Fee_SelectUseArea( &Fee_CpuDtfInfo );
                /* DATA-IDを保存 */
                Fee_CpuDtfInfo.u2DATA_ID = data_id;

                /* 要求データの保存 */
                Fee_CpuDtfInfo.u2ReqDataLen     = DataLength;
                Fee_CpuDtfInfo.ptu1ReqReadAddr  = DataBufferPtr;

                /* メインタイマカウンタ設定 */
                Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtIdReadTime;
                /* 動作状態をID指定データ読出し中(STATUS_IDREAD)に設定 */
                Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSIDREAD;
                /* メイン状態をアイドル(MAIN_STATUS_RIDLE)に設定 */
                Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSRIDLE;
                /* 最終書込みレコード位置読出し処理 */
                /* Return value is not checked. */
                (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

                /* Set the sub of RAMs. */
                Fee_Block_SetUseBlockInfoSub();
                Fee_Lib_SetCpuDtfDataSub();

                /* 戻り値用変数に要求受付を設定 */
                u1tReturn = FEE_REQUEST_ACCEPT;
            }
        }
    }

    /* 上位層に要求受付結果を返す */
    return u1tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データ再編要求                                             */
/* 入  力        ：uint8 No ：再編エリアの番号                                   */
/* 出  力        ：再編要求受付結果                                           */
/*               ：  0x00 ：FEE_REQUEST_ACCEPT  ：要求受付            */
/*               ：  0x01 ：FEE_REQUEST_DECLINE ：要求拒否            */
/*               ：  0x02 ：FEE_REQUEST_IRBLD_CNFM_NOT_OK                     */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint8, FEE_CODE) Fee_Legacy_Rebuild( uint8 No )
{
    uint8           u1tReturn;                          /* 戻り値 */
    Std_ReturnType  ChkIntentRbld;

    /* 戻り値用変数を要求拒否で初期化 */
    u1tReturn = FEE_REQUEST_DECLINE;
    
    /* データ再編要求は受付可能? */
    if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
    {
        /* 強制再編実施可否の問い合わせ */
        ChkIntentRbld = Mscd_Cnfm_CheckIntentRbld( No );
        if( ChkIntentRbld == (Std_ReturnType)E_OK )
        {
            /* 動作状態がアイドルの場合は受付可能 */
            /* MHA[データFlash]管理データ初期化 */
            Fee_InitCpuDtfData( &Fee_CpuDtfInfo );

            /* エリア番号を保存 */
            Fee_CpuDtfInfo.u1AreaNum = No;
            /* 使用エリア選択処理 */
            Fee_SelectUseArea( &Fee_CpuDtfInfo );

            /* メインタイマカウンタ設定 */
            Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtRebuildTime;
            /* 動作状態をデータ再編中(STATUS_MOVE)に設定 */
            Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSMOVE;
            /* メイン状態をアイドル(MAIN_STATUS_WBIDLE)に設定 */
            Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSWBIDLE;
            /* 最終書込みレコード位置読出し処理 */
            /* Return value is not checked. */
            (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

            /* Set the sub of RAMs. */
            Fee_Block_SetUseBlockInfoSub();
            Fee_Lib_SetCpuDtfDataSub();

            /* 戻り値用変数に要求受付を設定 */
            u1tReturn = FEE_REQUEST_ACCEPT;
        }
        else
        {
            u1tReturn = FEE_REQUEST_IRBLD_CNFM_NOT_OK;
        }
    }

    /* 上位層に要求受付結果を返す */
    return u1tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_GetFreeSpace                                  */
/* Description   | Function to get free spaces sizes on data flash.         */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LimitSearchDataArea                                      */
/*               | FreeSpaceInfoPtr                                         */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/*               | FEE_EXT_E_FRSP_AREA_FAULT                                */
/*               | FEE_EXT_E_FRSP_INTERNAL_ERROR                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_Legacy_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceReturnType  Rtn;
    MemIf_StatusType            DfcStatus;
    Fee_ExtFreeSpaceInfoType    TmpFreeSpaceInfo;
    Std_ReturnType              CheckCpuDtfDataResult;
    uint8                       ProcessStatus;

    CheckCpuDtfDataResult = Fee_Lib_CheckCpuDtfData();
    if( CheckCpuDtfDataResult == (Std_ReturnType)E_OK )
    {
        ProcessStatus = Fee_CpuDtfInfo.u1ProcessStatus;
        if(( ProcessStatus == FEE_STATUSIDLE )
        || ( ProcessStatus == FEE_STATUSIDREAD ))
        {
            DfcStatus = Fee_Dfc_GetStatus();
            if( DfcStatus == MEMIF_IDLE )
            {
                Rtn = Fee_FreeSpace_GetFreeSpace( AreaNo, LimitSearchMngArea, LimitSearchDataArea, &TmpFreeSpaceInfo );
            }
            else
            {
                Rtn = FEE_EXT_E_FRSP_BUSY;
            }
        }
        else
        {
            Rtn = FEE_EXT_E_FRSP_BUSY;
        }
    }
    else
    {
        Rtn = FEE_EXT_E_FRSP_INTERNAL_ERROR;
    }

    if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
    {
        FreeSpaceInfoPtr->Result       = TmpFreeSpaceInfo.Result;
        FreeSpaceInfoPtr->RcrdNum      = TmpFreeSpaceInfo.RcrdNum;
        FreeSpaceInfoPtr->DataAreaByte = TmpFreeSpaceInfo.DataAreaByte;
    }

    return Rtn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlashドライバ初期化要求（リセット時）                */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_Legacy_PwonInit( void )
{
    Fee_Driver_Init();

    /* リセット時初期化タイミングを通知する */
    Fee_ResetInitHook();

     Fee_Legacy_SetRAMAllSub();

   /* 関数コール元に戻る */
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlashドライバ強制初期化                              */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_Legacy_Abort( void )
{
    Std_ReturnType CancelResult;

    CancelResult = Fee_Driver_Cancel();
    if( CancelResult == (Std_ReturnType)E_OK )
    {
        Fee_Legacy_SetRAMAllSub();
    }

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash動作状態取得要求                                */
/* 入  力        ：なし                                                       */
/* 出  力        ：データFlash動作状態                                        */
/*               ：  0x00 ：FEE_IDLING      ：待機中                          */
/*               ：  0x01 ：FEE_WRITING     ：書込み中                        */
/*               ：  0x02 ：FEE_ID_READING  ：ID指定読出し中                  */
/*               ：  0x06 ：FEE_REBUILDING  ：データ再編中                    */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(uint8, FEE_CODE) Fee_Legacy_GetStatus( void )
{
    uint8               u1tReturn;                      /* 戻り値 */
    uint8               u1tStateInfo;                   /* 動作状態格納用 */
    MemIf_StatusType    DfcStatus;                      /* DFC動作状態格納用 */
    

    /* 戻り値用変数を待機中で初期化 */
    u1tReturn = FEE_IDLING;
    /* 動作状態取り出し */
    u1tStateInfo = Fee_CpuDtfInfo.u1ProcessStatus;

    if ( u1tStateInfo < FEE_STATUSMAX )
    {
        /* 状態が正常範囲内の場合 */
        /* データFlash動作状態を取得する */
        u1tReturn = Fee_Legacy_GetStatusTBL[u1tStateInfo];
    }

    if ( u1tReturn == FEE_IDLING )
    {
        /* 戻り値が待機中の場合、DFCが動作していないか確認 */
        DfcStatus = Fee_Dfc_GetStatus();
        
        if( DfcStatus != MEMIF_IDLE )
        {
            u1tReturn = FEE_DFC_ERROR;
        }
        else
        {
            /* No process to keep Idling status */
        }
    }

    /* 関数コール元にデータFlash動作状態を返す */
    return u1tReturn;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash定期処理                                        */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_Legacy_PeriodicFunc( void )
{
    Std_ReturnType CheckResult;

    /* Check RAMs. */
    CheckResult = Fee_Legacy_CheckRAMAll();
    if( CheckResult != (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u1Result = FEE_RSP_GARBLED_RAM;
    }

    /* メインタイマカウント値を確認 */
    if ( Fee_CpuDtfInfo.u4MainTimerCnt != (uint32)FEE_TM_COUNT_ZERO )
    {
        /* メインタイマ起動中 */
        /* タイマカウントデクリメント */
        Fee_CpuDtfInfo.u4MainTimerCnt--;
    }
    else
    {
        /* タイムアウト */
        /* 処理結果をタイムアウト(RSP_TIMEOUT)に設定 */
        Fee_CpuDtfInfo.u1Result = FEE_RSP_TIMEOUT;
    }
    /* D.F.C.タイマカウント値を確認 */
    if ( Fee_CpuDtfInfo.u4DFCTimerCnt != (uint32)FEE_TM_COUNT_ZERO )
    {
        /* D.F.C.タイマ起動中 */
        /* タイマカウントデクリメント */
        Fee_CpuDtfInfo.u4DFCTimerCnt--;
    }
    else
    {
        /* タイムアウト */
        /* 処理結果をタイムアウト(RSP_TIMEOUT)に設定 */
        Fee_CpuDtfInfo.u1Result = FEE_RSP_TIMEOUT;
    }

    /* データFlash定期処理(共通) */
    Fee_Periodic_FuncCommon();

    /* Set the sub RAMs. */
    Fee_Legacy_SetRAMAllSub();

    /* 関数コール元に戻る */
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash不定期処理                                      */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_Legacy_NonPeriodicFunc( void )
{
    Std_ReturnType CheckResult;

    /* Check RAMs. */
    CheckResult = Fee_Legacy_CheckRAMAll();
    if( CheckResult != (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u1Result = FEE_RSP_GARBLED_RAM;
    }

    /* データFlash定期処理(共通) */
    Fee_Periodic_FuncCommon();

    /* Set the sub RAMs. */
    Fee_Legacy_SetRAMAllSub();

    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash定期処理(共通)                                  */
/* 入  力        ：なし                                                       */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_Periodic_FuncCommon( void )
{
    /* Flashアクセス可否判定 */
    Fee_FlashAccessCheck();
    
    /* AreaNumは初期化でありえない値にしているので動作状態を確認する */
    if ( Fee_CpuDtfInfo.u1ProcessStatus != FEE_STATUSIDLE )
    {
        /* 検索処理可能回数を初期化 */
        Fee_CpuDtfInfo.u4SrchRemainCount = Fee_CpuDtfInfo.ptstAreaInf->u2MaxReadNum;
    }
    /* データFlash定期処理実行命令 */
    Fee_ExecPeriodic( &Fee_CpuDtfInfo );

    /* 関数コール元に戻る */
    return;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：指定データIDおよび指定エリアのデータ長を取得する           */
/* 入  力        ：データID                                                   */
/*               ：エリア番号                                                 */
/* 出  力        ：指定されたデータIDおよび指定エリアのデータ長               */
/*               ：データ長取得結果                                           */
/* グローバル変数：ID情報テーブル                                             */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, FEE_CODE) Fee_Legacy_GetDataLength( uint16 data_id , P2VAR(uint16, AUTOMATIC, TYPEDEF) DataLength )
{
    NvM_BlockIdType NvRamBlockId;
    Std_ReturnType  Rtn = E_NOT_OK;
    Std_ReturnType  BlockLenResult;

    /* ブロックIdを算出 */
    NvRamBlockId = (NvM_BlockIdType)( data_id >> Fee_DatasetSelectionBits );

    BlockLenResult = NvM_ExtGetNvBlockLength( NvRamBlockId , DataLength );

    if( BlockLenResult == (Std_ReturnType) E_OK )
    {
        /* Check a range of length */
        if( *DataLength < (uint16)FEE_DATA_LENGTH_MAX )
        {
            if( *DataLength > (uint16)FEE_LENGTH_00 )
            {
                Rtn = E_OK;
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FlashAccessCheck （Flashアクセス可否判定）       */
/* Description   | Flashへのアクセスが可能かどうか判定する                  */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_FlashAccessCheck( void )
{
    uint8               CheckResult = FEE_RSP_OK;
    MemIf_StatusType    DfcStatus;
    uint32              u4FlashAccessState;   /* Flashアクセス可否判定結果 */

    /* Check the Fls module status */
    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_UNINIT )
    {
        CheckResult = FEE_RSP_NG_DTF_CTRL;
    }
    else if( DfcStatus == MEMIF_BUSY_INTERNAL )
    {
        CheckResult = FEE_RSP_NG_DTF_CTRL;
    }
    else
    {
        /* No process */
    }

    /* Flashアクセス可否判定 */
    u4FlashAccessState = Fee_FlashAccessCheckHook();

    switch ( u4FlashAccessState )
    {
        case FEE_FLASH_ACCESS_DISABLE:
            /* Flashアクセス不可能の場合、処理結果をデータFlashコントローラ異常に設定 */
            CheckResult = FEE_RSP_NG_DTF_CTRL;
            break;
        case FEE_FLASH_ACCESS_WRITE_DISABLE:
            if ((FEE_STATUSWRITE == Fee_CpuDtfInfo.u1ProcessStatus)
             || (FEE_STATUSMOVE == Fee_CpuDtfInfo.u1ProcessStatus))
            {
                /* 書き込み不可能、かつ書き込みを実行する処理(書き込み/再編/初期化)の場合、*/
                /* 処理結果をデータFlashコントローラ異常に設定                             */
                CheckResult = FEE_RSP_NG_DTF_CTRL;
            }
            break;
        case FEE_FLASH_ACCESS_READ_DISABLE:
        case FEE_FLASH_ACCESS_ENABLE:
        default:
            /* No process */
            break;
    }

    if( CheckResult != FEE_RSP_OK )
    {
        Fee_CpuDtfInfo.u1Result = CheckResult;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_CheckRAMAll                                   */
/* Description   | Function to check RAMs of all units.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Legacy_CheckRAMAll( void )
{
    Std_ReturnType Rtn;

    Rtn = Fee_Dfc_CheckRAM();
    if( Rtn == (Std_ReturnType)E_OK )
    {
        Rtn = Fee_MngDfc_CheckRAM();
        if( Rtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_Record_CheckRAM();
            if( Rtn == (Std_ReturnType)E_OK )
            {
                Rtn = Fee_Block_CheckUseBlockInfo();
                if( Rtn == (Std_ReturnType)E_OK )
                {
                    Rtn = Fee_Lib_CheckCpuDtfData();
                }
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_SetRAMAllSub                                  */
/* Description   | Function to set value to sub RAMs of all units.          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Legacy_SetRAMAllSub( void )
{
    Fee_Dfc_SetRAMSub();
    Fee_MngDfc_SetRAMSub();
    Fee_Record_SetRAMSub();
    Fee_Block_SetUseBlockInfoSub();
    Fee_Lib_SetCpuDtfDataSub();

    return;
}

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
