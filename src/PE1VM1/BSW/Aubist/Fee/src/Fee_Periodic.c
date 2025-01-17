/* Fee_Periodic.c v1-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PERIODIC/CODE                                         */
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
#include "../inc/Fee_Periodic_Internal.h"

/* D.F.C.ヘッダ */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 確認用メイン状態 */
#define FEE_MAINSTATUS_IDLE         ((uint8)0x00U)      /* アイドル */
#define FEE_MAINSTATUS_INVALID      ((uint8)0x0FU)      /* 無効値 */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：データFlash定期処理実行命令                                */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：なし                                                       */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC(void, FEE_CODE) Fee_ExecPeriodic( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tStatus;                                  /* 処理状態内部変数 */
    
    /* 処理結果を確認 */
    if ( (ptstCPUDTFInfo->u1Result == FEE_RSP_TIMEOUT)
        || (ptstCPUDTFInfo->u1Result == FEE_RSP_NG_DTF_CTRL))
    {
        u4tStatus = FEE_STATUS_DONE;
    }
    else
    {
        /* 処理結果がタイムアウトでない場合 */
        /* DFC処理確認 */
        u4tStatus = Fee_Periodic_ExecUnderLayer( ptstCPUDTFInfo );
    }

    /* 処理状態内部変数がEXITでない間ループ */
    while ( u4tStatus != FEE_STATUS_EXIT )
    {
        /* 処理状態内部変数で分岐 */
        switch ( u4tStatus )
        {
            case FEE_STATUS_CONT:
                u4tStatus = Fee_Periodic_ExecPeriodicSubCont( ptstCPUDTFInfo );
                break;

            case FEE_STATUS_DONE:
                u4tStatus = Fee_Periodic_ExecPeriodicSubDone( ptstCPUDTFInfo );
                break;

            default: /* others */
                u4tStatus = FEE_STATUS_EXIT;
                break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecPeriodicSubCont                         */
/* Description   | Function to handle the requested jobs and the internal   */
/*               | management operations if the status is CONTINUE.         */
/*               | This function is a sub function for Fee_ExecPeriodic.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/* Return Value  | Next Status                                              */
/*               |   FEE_STATUS_EXIT                                        */
/*               |   FEE_STATUS_DONE                                        */
/*               |   FEE_STATUS_CONT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubCont(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint32 Rtn;
    uint8  ProcessStatus;

    ProcessStatus = CPUDTFInfo->u1ProcessStatus;

    if( ProcessStatus == FEE_STATUSIDREAD )
    {
        Rtn = Fee_ReadMain( CPUDTFInfo );
    }
    else if( ProcessStatus == FEE_STATUSWRITE )
    {
        Rtn = Fee_BWriteMain( CPUDTFInfo );
    }
    else if( ProcessStatus == FEE_STATUSMOVE )
    {
        Rtn = Fee_BWriteMain( CPUDTFInfo );
    }
    else /* ProcessStatus == FEE_STATUSIDLE */
    {
        /* Note : If the process status is an illegal value, this function execute this path.                       */
        /*      : However, the process status value is checked using redundancy RAM before calling this function.   */
        Rtn = FEE_STATUS_DONE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecPeriodicSubDone                         */
/* Description   | Function to finish the requested jobs                    */
/*               | if the status is DONE.                                   */
/*               | This function is a sub function for Fee_ExecPeriodic.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/* Return Value  | Next Status                                              */
/*               |   FEE_STATUS_EXIT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecPeriodicSubDone(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    uint8   ExecResult;

    ExecResult = CPUDTFInfo->u1Result;

    if(( ExecResult == FEE_RSP_TIMEOUT )
    || ( ExecResult == FEE_RSP_NG_DTF_CTRL ))
    {
        if( CPUDTFInfo->u1ProcessStatus != FEE_STATUSIDLE )
        {
            Fee_RecordPosTbl_ClearPosArea( CPUDTFInfo->u1AreaNum );
        }
        Fee_Driver_AbortDfc();
    }

    Fee_RspHook( CPUDTFInfo );

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecUnderLayer                              */
/* Description   | This function handles underlayer jobs, MngDfc or Fls.    */
/* Preconditions | None                                                     */
/* Parameters    | CPUDTFInfo                                               */
/* Return Value  | Status                                                   */
/*               |   FEE_STATUS_EXIT                                        */
/*               |   FEE_STATUS_DONE                                        */
/*               |   FEE_STATUS_CONT                                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecUnderLayer(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
){
    boolean IsWaitingForCancel;
    uint32  RtnStatus;

    IsWaitingForCancel = Fee_Driver_IsWaitingForCancel();
    if( IsWaitingForCancel == (boolean)TRUE )
    {
        RtnStatus = Fee_Periodic_ExecFlsForWaitingCancel();
    }
    else if( CPUDTFInfo->u1Result == FEE_RSP_GARBLED_RAM )
    {
        RtnStatus = Fee_Periodic_ExecFlsForWaitingAbort();
    }
    else
    {
        RtnStatus = Fee_Periodic_ExecMngDfc( CPUDTFInfo );
    }

    return RtnStatus;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecFlsForWaitingCancel                     */
/* Description   | Function to handle FLS jobs while waiting asynchronous   */
/*               | cancel and execute cancel.                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Status. This function returns only FEE_STATUS_EXIT,      */
/*               | because it is not wanted that Fee_ExecPeriodic() does    */
/*               | something.                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingCancel( void )
{
    MemIf_StatusType DfcStatus;

    /* Return value is not checked.                                 */
    /* Instead of using the return value that is a result of FLS,   */
    /* this function uses the status of Fee_Dfc_GetStatus().        */
    (void)Fee_Dfc_ExecFlsMainFunction();

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_IDLE )
    {
        Fee_Driver_AsyncCancel();
    }
    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_ExecFlsForWaitingAbort                      */
/* Description   | Function to handle FLS jobs while waiting asynchronous   */
/*               | abort and execute abort.                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Status. This function returns only FEE_STATUS_EXIT,      */
/*               | because it is not wanted that Fee_ExecPeriodic() does    */
/*               | something.                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecFlsForWaitingAbort( void )
{
    MemIf_StatusType DfcStatus;

    /* Return value is not checked.                                 */
    /* Instead of using the return value that is a result of FLS,   */
    /* this function uses the status of Fee_Dfc_GetStatus().        */
    (void)Fee_Dfc_ExecFlsMainFunction();

    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_IDLE )
    {
        Fee_Driver_AsyncAbort();
    }
    return FEE_STATUS_EXIT;
}

/*関数説明--------------------------------------------------------------------*/
/* 説  明        ：DFC定期処理実行命令                                        */
/* 入  力        ：stCPUDTF *ptstCPUDTFInfo                            */
/*                                           ：MHA[データFlash]管理データ     */
/* 出  力        ：処理状態                                                   */
/*               ：  0x00000002 ：FEE_STATUS_EXIT ：処理中             */
/*               ：  0x00000003 ：FEE_STATUS_DONE ：動作完了           */
/*               ：  0x00000004 ：FEE_STATUS_CONT ：アイドル           */
/* グローバル変数：                                                           */
/* その他        ：                                                           */
/*----------------------------------------------------------------------------*/
FUNC( uint32, FEE_CODE )
Fee_Periodic_ExecMngDfc(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo
){
    uint32          u4tStatus;                                  /* 処理状態内部変数 */
    uint32          u4tMngDFCResult;                            /* 定期処理用データFlash書込み制御処理結果 */
    uint8           u1tLower4BitMainStatus;

    /* 定期処理用データFlash制御管理処理 */
    u4tMngDFCResult = Fee_MngDfcForPrd();
    if ( u4tMngDFCResult == FEE_STATUS_BUSY )
    {
        /* 処理中(STATUS_BUSY)の場合 */
        /* メイン状態確認 */
        u1tLower4BitMainStatus = ptstCPUDTFInfo->u1MainStatus & (uint8)FEE_LOWER4BIT;
        switch ( u1tLower4BitMainStatus )
        {
            case FEE_MAINSTATUS_IDLE:
                /* メイン状態がアイドルの場合 */
                /* 処理結果をデータFlashコントローラ異常に設定 */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_DTF_CTRL;
                /* 処理状態内部変数をDONEに設定 */
                u4tStatus = FEE_STATUS_DONE;
                break;
            case FEE_MAINSTATUS_INVALID:
                /* メイン状態が無効値の場合 */
                /* 処理状態内部変数をCONTに設定 */
                u4tStatus = FEE_STATUS_CONT;
                break;
            default:
                /* メイン状態がアイドル・無効値でない場合 */
                /* 処理状態内部変数をEXITに設定 */
                u4tStatus = FEE_STATUS_EXIT;
                break;
        }
    }
    else
    {
        /* 処理中でない場合 */
        /* 処理状態内部変数をCONTに設定 */
        u4tStatus = FEE_STATUS_CONT;
    }
    
    return u4tStatus;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/09/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
