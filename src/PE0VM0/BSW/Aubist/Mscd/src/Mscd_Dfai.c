/* Mscd_Dfai.c v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/DFAI/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee_Ext.h>

#include <Mscd_Common.h>
#include "../inc/Mscd_Dfai.h"

#include "../cfg/Mscd_Lcfg.h"
#include "../inc/Mscd_Suspend.h"
#include "../inc/Mscd_Dfai_Internal.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Write （データ書き込み）                       */
/* Description   | メモリ媒体へ書き込み要求する                             */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier  : メモリ媒体ID                       */
/*               |                      ※将来の拡張用。現在は0固定         */
/*               | u4Address           : 書込み要求アドレス                 */
/*               | ptSrcPtr            : 書込みデータの先頭ポインタ         */
/*               | u4Length            : 書込みデータ長                     */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |           MSCD_DFAI_JOB_ACCEPT                           */
/*               |           MSCD_DFAI_JOB_NOT_ACCEPT                       */
/*               |           MSCD_DFAI_JOB_INOPERATIVE_HSM                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Write( uint8 u1MemoryIdentifier, uint32 u4Address, P2CONST(uint8, AUTOMATIC, MSCD_APPL_CONST) ptSrcPtr, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1OpeResult;

    u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;

   /* MSが停止状態のときのみ実施する */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* 要求パラメータが、コンフィグで指定したユーザ用メモリ領域の範囲内かチェック */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1OpeResult = Fee_ExtDirectWrite( u4Address, u4Length, ptSrcPtr );

            if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_ACCEPT )
            {
                u1Result = MSCD_DFAI_JOB_ACCEPT;
            }
            else if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_INOPERATIVE_HSM )
            {
                u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
            }
            else
            {
                u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;
            }
        }
    }
    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Erase （データ消去）                           */
/* Description   | メモリ媒体へ消去要求する                                 */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier  : メモリ媒体ID                       */
/*               |                 ※将来の拡張用。現在は0固定              */
/*               | u4Address           : 消去対象アドレス                   */
/*               |                 ※ セクタの先頭の相対アドレスであること  */
/*               | u4Length            : 消去データ長                       */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |           MSCD_DFAI_JOB_ACCEPT                           */
/*               |           MSCD_DFAI_JOB_NOT_ACCEPT                       */
/*               |           MSCD_DFAI_JOB_INOPERATIVE_HSM                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Erase( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    uint16 u2Req_sector_num;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1OpeResult;

    u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;

    /* MSが停止状態のときのみ実施する */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {

        /* 要求パラメータが、コンフィグで指定したユーザ用メモリ領域の範囲内かチェック */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            /* Calculating the number of sectors to erase from u4Length. */
            u2Req_sector_num = (uint16)( (u4Length + ((uint32)MSCD_DFAI_FLASH_SECTOR_SIZE - (uint32)MSCD_DFAI_1LSB) ) / (uint32)MSCD_DFAI_FLASH_SECTOR_SIZE );

            u1OpeResult = Fee_ExtDirectErase( u4Address, u2Req_sector_num );

            if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_ACCEPT )
            {
                u1Result = MSCD_DFAI_JOB_ACCEPT;
            }
            else if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_INOPERATIVE_HSM )
            {
                u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
            }
            else
            {
                u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;
            }
        }
    }
    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_MainFunction （ドライバ定期処理）           */
/* Description   | 非同期処理を進行させる                                   */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier  : メモリ媒体ID                       */
/*               |                      ※将来の拡張用。現在は0固定         */
/* Return Value  | None                                                     */
/* Notes         | 今後メモリ媒体IDに対してロジックを組むことを考慮し、     */
/*               | 名前置換ではなく関数で実現する                           */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_Dfai_MainFunction( uint8 u1MemoryIdentifier )
{
    uint8 u1Suspend_state;

    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        Fee_ExtDirectMainFunction( );
    }
    return;
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_GetStatus                                      */
/* Description   | Service to return the status of the flash driver.        */
/* Preconditions | None                                                     */
/* Parameters    | u1MemoryIdentifier                                       */
/* Return Value  | Mscd_Dfai_StatusType                                     */
/*               |      MSCD_DFAI_STATE_IDLE                                */
/*               |      MSCD_DFAI_STATE_BUSY                                */
/*               |      MSCD_DFAI_STATE_ERROR                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Mscd_Dfai_StatusType, MSCD_CODE )
Mscd_Dfai_GetStatus(
    uint8 u1MemoryIdentifier
){
    Mscd_Dfai_StatusType    Rtn     = MSCD_DFAI_STATE_ERROR;
    Fee_ExtDirectStatusType FeeStatus;
    uint8                   SuspendState;

    SuspendState = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != SuspendState )
    {
        FeeStatus = Fee_ExtDirectGetStatus();
        
        if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_IDLE )
        {
            Rtn = MSCD_DFAI_STATE_IDLE;
        }
        else if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_BUSY )
        {
            Rtn = MSCD_DFAI_STATE_BUSY;
        }
        else if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_ERROR )
        {
            Rtn = MSCD_DFAI_STATE_ERROR;
        }
        else
        {
            /* RAM garbled. */
            Rtn = MSCD_DFAI_STATE_ERROR;
        }
    }

    return( Rtn );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_GetJobResult                                   */
/* Description   | Service to return the job result of the flash driver     */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier                                       */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD_DFAI_JOB_OK                                    */
/*               |      MSCD_DFAI_JOB_BUSY                                  */
/*               |      MSCD_DFAI_JOB_ERROR                                 */
/*               |      MSCD_DFAI_JOB_CANCELED                              */
/*               |      MSCD_DFAI_JOB_FATALERROR                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_GetJobResult( uint8 u1MemoryIdentifier )
{
    Mscd_Dfai_ReturnType u1Result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Req_result = Fee_ExtGetDirectJobResult();

    /* 返り値の変換 */
    switch( u1Req_result )
    {
        case FEE_EXT_DRCT_JOB_OK:
            u1Result = MSCD_DFAI_JOB_OK;
            break;
        case FEE_EXT_DRCT_JOB_BUSY:
            u1Result = MSCD_DFAI_JOB_BUSY;
            break;
        case FEE_EXT_DRCT_JOB_CANCELED:
            u1Result = MSCD_DFAI_JOB_CANCELED;
            break;
        case FEE_EXT_DRCT_JOB_FATALERROR:
            u1Result = MSCD_DFAI_JOB_FATALERROR;
            break;
        case FEE_EXT_DRCT_JOB_ERROR:
        default: /* 化けている場合は失敗（エラー）として扱う */
            u1Result = MSCD_DFAI_JOB_ERROR;
            break;
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Read （読み出し(同期型)）                      */
/* Description   | メモリ媒体へ同期読み出し要求する                         */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier  : メモリ媒体ID                       */
/*               |                      ※将来の拡張用。現在は0固定         */
/*               | u4Address            : 読み出し要求アドレス              */
/*               | ptSrcPtr             : 読出しデータの先頭ポインタ        */
/*               | u4Length             : 読み出しデータ長                  */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD_DFAI_JOB_OK         : 成功                     */
/*               |      MSCD_DFAI_JOB_ERROR      : 失敗（エラー）           */
/*               |      MSCD_DFAI_JOB_FATALERROR : 失敗（致命的なエラー）   */
/*               |      MSCD_DFAI_JOB_INOPERATIVE_HSM                       */
/*               |      MSCD_DFAI_JOB_INTEGRITY_FAILED                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Read( uint8 u1MemoryIdentifier, uint32 u4Address, P2VAR(uint8, AUTOMATIC, MSCD_APPL_DATA) ptSrcPtr, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Result = MSCD_DFAI_JOB_ERROR;

    /* MSが停止状態のときのみ実施する */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* 要求パラメータが、コンフィグで指定したユーザ用メモリ領域の範囲内かチェック */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1Req_result = Fee_ExtDirectRead( u4Address, u4Length, ptSrcPtr );

            switch( u1Req_result )
            {
                case FEE_EXT_DRCT_JOB_OK:
                    u1Result = MSCD_DFAI_JOB_OK;
                    break;
                case FEE_EXT_DRCT_JOB_FATALERROR:
                    u1Result = MSCD_DFAI_JOB_FATALERROR;
                    break;
                case FEE_EXT_DRCT_JOB_INOPERATIVE_HSM:
                    u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
                    break;
                case FEE_EXT_DRCT_JOB_INTEGRITY_FAILED:
                    u1Result = MSCD_DFAI_JOB_INTEGRITY_FAILED;
                    break;
                case FEE_EXT_DRCT_JOB_ERROR:
                default:
                    u1Result = MSCD_DFAI_JOB_ERROR;
                    break;
            }
        }
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_BlankCheck （ブランクチェック(同期型)）        */
/* Description   | メモリ媒体へ同期ブランクチェック要求する                 */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier  : メモリ媒体ID                       */
/*               |                      ※将来の拡張用。現在は0固定         */
/*               | u4Address            : チェック対象アドレス              */
/*               | u4Length             : チェックするデータ長              */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD_DFAI_JOB_BLANK      : ブランク               */
/*               |      MSCD_DFAI_JOB_NOT_BLANK  : 非ブランク             */
/*               |      MSCD_DFAI_JOB_ERROR      : 失敗（エラー）         */
/*               |      MSCD_DFAI_JOB_FATALERROR : 失敗（致命的なエラー） */
/*               |      MSCD_DFAI_JOB_INOPERATIVE_HSM                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_BlankCheck( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Result = MSCD_DFAI_JOB_ERROR;

    /* MSが停止状態のときのみ実施する */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* 要求パラメータが、コンフィグで指定したユーザ用メモリ領域の範囲内かチェック */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        /* パラメータチェックがOKの場合はDFDAにブランクチェックを要求し、それ以外の場合はE_NOT_OKを返す */
        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1Req_result = Fee_ExtDirectBlankCheck( u4Address, u4Length );

            /* 返り値の変換 */
            switch( u1Req_result )
            {
                case FEE_EXT_DRCT_JOB_BLANK:
                    u1Result = MSCD_DFAI_JOB_BLANK;
                    break;
                /* 非ブランク、かつ読み出せた場合はDFDAからDTF_FEE_RESULT_OKが返るため、 */
                /* MSCD_DFAI_JOB_NOT_BLANKに変換 */
                case FEE_EXT_DRCT_JOB_NOT_BLANK:
                    u1Result = MSCD_DFAI_JOB_NOT_BLANK;
                    break;
                case FEE_EXT_DRCT_JOB_FATALERROR:
                    u1Result = MSCD_DFAI_JOB_FATALERROR;
                    break;
                case FEE_EXT_DRCT_JOB_INOPERATIVE_HSM:
                    u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
                    break;
                case FEE_EXT_DRCT_JOB_ERROR:
                default: /* 化けている場合は失敗（エラー）として扱う */
                    u1Result = MSCD_DFAI_JOB_ERROR;
                    break;
            }
        }
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/02/14                                              */
/*  2-0-0          :2021/05/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
