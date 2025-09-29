/* can_rsc_st_log_c_v3-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSC/ST/LOGICAL/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include <CanIf_Cbk.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rsc/can_rsc_cfg_ext.h"
#include "../../cfg/rsc/can_rsc_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>
#include <can/rsc/can_rsc.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rsc/can_rsc_tb_log.h>
#include <can/rsc/can_rsc_tx.h>
#include <can/rsc/can_rsc_fs.h>
#include <can/rsc/can_rsc_st.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------*/
/* CANコントローラ状態                                        */
/* ・内容：                                                   */
/*     CANコントローラの状態を保持する。                      */
/* ・値域：                                                   */
/*   CAN_ST_CTRL_UNINIT         未初期化                      */
/*   CAN_ST_CTRL_INIT           初期化済                      */
/*   CAN_ST_CTRL_STOPPED        通信停止                      */
/*   CAN_ST_CTRL_STARTED        通信中                        */
/*   CAN_ST_CTRL_TO_STOPPED_NML 通信停止待ち                  */
/*   CAN_ST_CTRL_TO_STOPPED_RST 再初期化待ち                  */
/*   CAN_ST_CTRL_TO_STARTED     通信開始待ち                  */
/* ・RAM化け対策：                                            */
/*     処置方針の原則として、異常検出と通知に対応する。       */
/*     設定値を上位8bit, 下位8bitを反転させた値とし、和が     */
/*      0xFFとなれば正常、ならなければ異常として判断する。    */
/*     設定値には、1bit化けで別の値にならないものを設定する。 */
/* ・チェックタイミング:                                      */
/*     Can_MainFunction_Fail                                  */
/*------------------------------------------------------------*/
uint16 Can_st_u2ControllerStatus[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Can_Init                                                 */
/* Description   | CANモジュール初期化                                      */
/* Preconditions | -                                                        */
/* Parameters    | uint8 CanConfigSet : コンフィグセット番号(使用しない)    */
/* Return Value  | なし                                                     */
/* Notes         | ・power-on/reset/wakeup直後のCANへの要求は、本関数から   */
/*               |   開始することを制約とする。                             */
/*               | ・ソフトPFでは、非制御対象CANの領域に影響を与えないことを*/
/*               |   原則とするが、全コントローラ共通領域については         */
/*               |   ソフトPFにより初期化する。                             */
/*               | ・コンフィグセット番号は将来拡張用(0固定)であり、        */
/*               |   本ソフトでは使用しない。                               */
/****************************************************************************/
void
Can_Init( uint8 CanConfigSet )
{
    uint8  u1Controller;           /* コントローラID     */
    uint8  u1ControllerNumMax;     /* コントローラ数     */
    uint8  u1InitRegRet;           /* レジスタ初期化結果 */

    /* 引数で指定したコンフィグセットを用いて */
    /* CANモジュールを初期化する              */

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* コントローラ状態の初期化前設定                              */
        /* 全てのCANコントローラ状態について、予め未初期化に設定する。 */
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_UNINIT;
    }

    /* 送信機能の保持するRAMの初期化 */
    Can_tx_Init();

    /* フェールセーフ機能の保持するRAMの初期化 */
    Can_fs_Init();

    /* レジスタ初期化                           */
    /* CAN共通で使用するレジスタの設定、及び    */
    /* コントローラ別、MBOX別レジスタに対する   */
    /* 外部に悪影響を及ぼさないための安全値設定 */
    u1InitRegRet = Can_st_InitReg();

    if ( u1InitRegRet == (uint8)CAN_PROC_OK )
    {
        /* 状態管理機能の保持するRAMの初期化 */
        for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
        {
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1ControllerActivation == (uint8)CAN_TRUE )
            {
                /* 制御対象CANの場合                     */
                /* CANコントローラ状態を初期化済みに設定 */
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_INIT;

                /* CANコントローラ状態は本関数が正常に終了した場合、以下となる。 */
                /* - 非制御対象CAN                    : 未初期化                 */
                /* - 制御対象CAN && 未使用コントローラ: 初期化済                 */
                /* - 制御対象CAN && 使用コントローラ  : 初期化済                 */
            }
        }
    }
}


/****************************************************************************/
/* Function Name | Can_InitController                                       */
/* Description   | CANコントローラ初期化                                    */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   初期化を実施するCANコントローラ                        */
/*               | uint8 CanControllerBaudrateConfigSet :                   */
/*               |   コントローラボーレートコンフィグセット番号(使用しない) */
/* Return Value  | Can_ReturnType CANコントローラ初期化結果                 */
/*               |   CAN_OK     : 初期化完了                                */
/*               |   CAN_NOT_OK : 初期化失敗                                */
/*               |   CAN_BUSY   : 初期化未完了                              */
/* Notes         | ・ボーレートコンフィグセット番号は将来拡張用(0固定)であり*/
/*               |   本ソフトでは使用しない。                               */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・CAN_OK、CAN_BUSY応答後でも、再度本APIが要求される      */
/*               |   ケースを想定する。                                     */
/*               | ・CAN_BUSY応答後に要求された場合は初期化処理を実施する。 */
/*               | ・CAN_OK応答後に要求された場合はCAN_OKを応答する。       */
/****************************************************************************/
Can_ReturnType
Can_InitController( uint8 Controller, uint8 CanControllerBaudrateConfigSet )
{
    uint16  u2ControllerStatus;     /* コントローラ状態               */
    uint8   u1Ret;                  /* 戻り値                         */
    uint8   u1ModeChgRet;           /* レジスタ初期化結果             */
    uint8   u1ChkParam;             /* 通信パラメータチェックの戻り値 */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    /* CANコントローラの動作状態確認 */
    /* Can_Init発行後、初期化済のみ受け付け */
    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_INIT )
    {
        /* レジスタ初期化 */
        u1ModeChgRet = Can_st_SetControl( Controller );
        if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
        {
            /* コントローラ関連レジスタ初期化完了時 */

            /* 通信パラメータチェック */
            u1ChkParam = Can_fs_ChkParameter( Controller );
            if ( u1ChkParam == (uint8)CAN_NONE )
            {
                /* バスオフ発生情報のクリア */
                Can_fs_ClearBusOffStatus( Controller );

                /* MBOXコンフィグ設定 */
                Can_st_SetConfigMbox( Controller );

                /* CANコントローラ状態を通信停止に設定 */
                /* ※レジスタ固着チェック or Can_SetControllerMode(CAN_T_START)受付可能 */
                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                u1Ret = (uint8)CAN_OK;
            }
        }
        else    /* u1ModeChgRet == (uint8)CAN_PROC_BUSY */
        {
            u1Ret = (uint8)CAN_BUSY;
        }
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        /* コントローラの初期化完了後、再度呼ばれた場合 */
        Can_fs_PrepChkRegRetry( Controller );
        u1Ret = (uint8)CAN_OK;
    }
    else /* MISRA DEVIATION: no process */
    {
        /* 上記以外の状態で呼ばれた場合 */
        /* NOT_OKを応答 */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_SetControllerMode                                    */
/* Description   | CANコントローラモード設定                                */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   モード設定を実施するCANコントローラ                    */
/*               | Can_StateTransitionType Transition :                     */
/*               |   要求するコントローラ状態                               */
/* Return Value  | Can_ReturnType 要求受付結果                              */
/*               |   CAN_OK     : 要求受付                                  */
/*               |   CAN_NOT_OK : 要求不受理                                */
/* Notes         | ・本関数は、下記コールバック関数の発行中に呼び出される   */
/*               |   可能性があるため、変数やレジスタのアクセスが干渉しない */
/*               |   よう注意すること。                                     */
/*               |   - CanIf_ControllerBusOff                               */
/*               |   - CanIf_ControllerFail                                 */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/****************************************************************************/
Can_ReturnType
Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1ModeChgRet;           /* モード遷移結果   */
    uint8   u1Ret;                  /* 戻り値           */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    if ( Transition == (uint8)CAN_T_START )
    {
        /* CAN_T_START時 */

        /* モード遷移前に、送受信関連レジスタ（送信要求、送信完了、受信完了等）、  */
        /* 割り込み要因、エラー情報などをクリアすることで、想定外の動作を防止する。*/
        /* モード遷移確定後には以下の状態となる。                                  */
        /* ・CAN関連割り込み許可（コンフィグで使用しているもののみ）               */
        /* ・CAN関連割り込み要因なし                                               */
        /* ただし、レジスタの操作可否タイミング等の問題で                          */
        /* 本関数のみでモード遷移が確定しない場合は、                              */
        /* Can_MainFunction_Modeで処置する。                                       */

        /* CANコントローラ状態の確認 */
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
        {
            /* CANコントローラが停止状態、または停止状態への遷移中の場合 */

            /* コントローラ通信開始処理の要求前に      */
            /* CANコントローラ状態を通信開始待ちに設定 */
            Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STARTED;

            /* バスオフ発生情報のクリア */
            Can_fs_ClearBusOffStatus( Controller );

            /* コントローラ通信開始処理の実行 */
            u1ModeChgRet = Can_st_Start( Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                /* コントローラ通信開始処理が完了した場合 */
                /* CANコントローラ状態を通信中に設定      */
                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STARTED;

                /* 通信中への遷移完了を通知 */
                CanIf_ControllerModeIndication( Controller, (uint8)CANIF_CS_STARTED );
            }
            /* コントローラ通信開始処理が完了しなかった場合 */
            /* CANコントローラ状態は通信開始待ちのまま      */
            /* 以降、Can_MainFunctionModeにて遷移する。     */

            /* 要求の受付成功   */
            /* 戻り値をOKに更新 */
            u1Ret = (uint8)CAN_OK;
        }
        /* 上記以外の状態の場合、 NOT_OKを応答する。                         */
        /* 動作中の状態に影響させないため、既にSTARTモードへの遷移要求が実行 */
        /* されている場合も要求は受け付けずNOT_OKを応答する。                */
    }
    else if ( Transition == (uint8)CAN_T_STOP )
    {
        /* CAN_T_STOP時 */

        /* モード遷移後に、送受信関連レジスタ（送信要求、送信完了、受信完了等）、            */
        /* 割り込み要因などをクリアすることで、想定外の動作を防止する。                      */
        /* (エラー情報のクリアは)実施しない。                                                */
        /* モード遷移要求前に、以下の状態にする。                                            */
        /* ・CAN関連割り込み禁止（割り込み許可はCan_SetControllerMode(CAN_T_START）時に実施) */
        /* ・CAN関連割り込み要因なし                                                         */
        /* ※ 割り込み禁止処理はネスト構造を持たないこと                                     */

        /* ただし、モード遷移確定後にしか操作できないレジスタが存在するMPUにおいて、         */
        /* 本関数でモード遷移が確定しない場合は、Can_MainFunction_Modeにて                   */
        /* 上記の処理を実施する。                                                            */

        /* CANコントローラ状態の確認 */
        /* CANコントローラ状態が未初期化、または異常値の場合は受付しない。 */
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
        ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED ))
        {
            /* コントローラ通信停止処理の要求前に      */
            /* CANコントローラ状態を通信停止待ちに設定 */
            Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_NML;

            /* コントローラ別バスオフ復帰方法の確認 */
            if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                /* コントローラ別バスオフ復帰方法を手動で実施する場合 */

                /* バスオフ検出をポーリングで行う場合                                           */
                /*   バスオフ検出区間は、コントローラ停止状態への遷移完了までとするため、       */
                /*   本タイミングでバスオフ発生情報を更新する。                                 */
                /*   ※ 本タイミングで、通信停止状態への遷移が完了しなかった場合は、            */
                /*      遷移が確定するまでCan_MainFunction_Modeにてバスオフ発生情報を更新する。 */
                if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffProcessing == (uint8)CAN_POLLING )
                {
                    /* バスオフ発生情報を更新。戻り値は割り込み用のため使用しない。 */
                    (void)Can_fs_ChkBusOff( Controller ); /* MISRA DEVIATION: no return check required */
                }
            }

            /* コントローラ通信停止処理の実行 */
            u1ModeChgRet = Can_st_Stop( Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                /* コントローラ通信停止処理が完了した場合 */
                /* CANコントローラ状態を通信停止に設定    */
                Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                /* 通信停止への遷移完了を通知 */
                CanIf_ControllerModeIndication( Controller, (uint8)CANIF_CS_STOPPED );
            }
            /* コントローラ通信停止処理が完了しなかった場合 */
            /* CANコントローラ状態は通信停止待ちのまま      */
            /* 以降、Can_MainFunctionModeにて遷移する。     */

            /* 要求の受付成功   */
            /* 戻り値をOKに更新 */
            u1Ret = (uint8)CAN_OK;
        }
        else if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
             ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
             ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
        {
            /* 要求の受付成功  */
            /* 既にSTOPモードへの遷移処理が実行されているため、OKのみ応答する。      */
            /* 同一タスクのMainFunctionModeで確認するため、モード確定の確認はしない。*/
            u1Ret = (uint8)CAN_OK;
        }
        else /* MISRA DEVIATION: no process */
        {
            /* 上記以外の状態の場合 */
            /* NOT_OKを応答 */
        }
    }
    else /* MISRA DEVIATION: no process */
    {
        /* CAN_T_START、 CAN_T_STOP以外の無効な状態が要求された場合 */
        /* NOT_OKを応答 */
    }
    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Mode                                    */
/* Description   | モード確認定期処理                                       */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・本APIはCANIFから呼び出されるため、CANIFの状態によって  */
/*               |   必ずしも定期的に呼び出されない。そのため、厳密な時間   */
/*               |   監視処理は実施しない。                                 */
/****************************************************************************/
void
Can_MainFunction_Mode( void )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1Controller;           /* コントローラID   */
    uint8   u1ControllerNumMax;     /* コントローラ数   */
    uint8   u1ModeChgRet;           /* モード遷移結果   */

    /* コントローラ別モード確認処理を実施 */
    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* 制御対象CAN かつ 使用するコントローラに対し                  */
        /* モード遷移をチェックする。                                   */

        /* 制御対象CAN かつ 使用するコントローラか否かは                */
        /* コントローラ状態変数から判断する。                           */
        /* ※ 非制御対象CANの場合、Can_Init後 CAN_ST_CTRL_UNINIT で固定 */
        /*    制御対象CAN かつ 使用しないコントローラの場合は           */
        /*    Can_Init後、CAN_ST_CTRL_INIT で固定されるため             */
        /*    コンフィグ設定のチェックは不要。                          */

        /* コントローラの動作モードチェック                 */
        /* コントローラの動作モードが遷移中か否かのチェック */
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
        {
            /* Can_SetControllerMode(CAN_T_START)発行後に                */
            /* Can_SetControllerMode内でモード遷移が確定しない場合の処置 */
            /*   モード遷移前に、送受信関連レジスタ                      */
            /*   （送信要求、送信完了、受信完了等）、割り込み要因、      */
            /*   エラー情報などをクリアすることで、想定外の動作を        */
            /*   しないようにする。                                      */
            /*   モード遷移確定後には以下の状態となる。                  */
            /*   ・CAN関連割り込み許可                                   */
            /*   ・CAN関連割り込み要因なし                               */

            /* 通信開始待ちの場合           */
            /* コントローラ通信開始チェック */
            u1ModeChgRet = Can_st_ChkStart( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                /* 通信開始処理が完了した場合        */
                /* CANコントローラ状態を通信中に設定 */
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STARTED;

                /* CANIFへのモード遷移完了通知 */
                CanIf_ControllerModeIndication( u1Controller, (uint8)CANIF_CS_STARTED );

            }

            /* 通信開始処理に失敗し続けるケースの考慮              */
            /* 本仕様としては何もせず、次回定期処理でリトライする。*/
            /* 前提：CANIF側での送信ロック検出機能が提供されること */
            /*       前提条件が満たされない場合、遷移の失敗回数を  */
            /*       カウントし、フェールを通知するなどの設計を    */
            /*       追加する。                                    */
        }
        else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
        {
            /* 通信停止待ちの場合 */

            /* コントローラ別バスオフ復帰方法の確認 */
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                /* コントローラ別バスオフ復帰方法を手動で実施する場合 */

                /* コントローラ停止確定までバスオフが発生しうるため、最新の     */
                /* バスオフ発生情報に更新。戻り値は割り込み用のため使用しない。 */
                (void)Can_fs_ChkBusOff( u1Controller ); /* MISRA DEVIATION: no return check required */
            }

            /* コントローラ通信停止チェック */
            u1ModeChgRet = Can_st_ChkStop( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                /* 通信停止処理が完了した場合          */
                /* CANコントローラ状態を通信停止に設定 */
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;

                /* CANIFへのモード遷移完了通知 */
                CanIf_ControllerModeIndication( u1Controller, (uint8)CANIF_CS_STOPPED );
            }
            /* 通信停止処理に失敗し続けるケースの考慮について */
            /* CANとしては、通信停止処理の施行を継続する。    */
        }
        else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST )
        {
            /* 再初期化待ちの場合 */

            /* 本パスは、上位層のソフトの設計によっては呼び出されない可能性がある  */
            /* ※ Can_ResetController, Can_SetControllerModeを連続発行する場合     */

            /* コントローラ再初期化チェック */
            u1ModeChgRet = Can_st_ChkReset( u1Controller );
            if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
            {
                /* バスオフ発生情報のクリア                                      */
                /* ※ リセットが完了していない場合は、バスからコントローラが     */
                /*    切断されておらず、バスオフが継続発生している可能性がある。 */
                /*    その場合、バスオフ発生情報がクリアできないため             */
                /*    リセット成功後(コントローラ停止確定後)に実施する。         */
                Can_fs_ClearBusOffStatus( u1Controller );

                /* MBOXコンフィグ設定 */
                Can_st_SetConfigMbox( u1Controller );

                /* STOPモードへの遷移(再初期化)が完了した場合 */
                /* CANコントローラ状態を通信停止に設定        */
                Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
            }
            /* 再初期化処理に失敗し続けるケースの考慮について */
            /* CANとしては、再初期化処理の施行を継続する。    */
        }
        else /* MISRA DEVIATION: no process */
        {
            /* 通信開始待ち、通信停止待ち、再初期化待ち以外の状態では何もしない。 */
        }
    }
}


/****************************************************************************/
/* Function Name | Can_Shutdown                                             */
/* Description   | シャットダウン                                           */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | シャットダウンのためのモード遷移の完了確認が必要な       */
/*               | マイコンの場合は、タイムアウト時間を設けて待機する。     */
/*               | 時間内に完了しない場合は、CANコンポーネントのソフト上は  */
/*               | 遷移完了と同等の状態とし、起動時の失敗でのフェール検出を */
/*               | 期待する。                                               */
/****************************************************************************/
void
Can_Shutdown( void )
{
    uint8  u1Controller;           /* コントローラID */
    uint8  u1ControllerNumMax;     /* コントローラ数 */

    /* ▼▼▼▼▼▼  割り込み禁止  ▼▼▼▼▼▼ */
    /* シャットダウン要求直後、全てのコントローラに対して         */
    /* 一律に新規要求を受付不可とするため、割り込み禁止を掛ける。 */
    Can_DI()
    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* モード遷移中に送受信機能要求が実施された場合に */
        /* 誤ったメッセージの送受信などが発生しないよう   */
        /* はじめに未使用を含む全CANコントローラを        */
        /* 停止状態(未初期化)にする。                     */
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_UNINIT;
    }
    Can_EI()
    /* ▲▲▲▲▲▲  割り込み許可  ▲▲▲▲▲▲ */

    /* シャットダウン用レジスタ設定を実施 */
    Can_st_ShutdownReg();

    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* バスオフ発生情報のクリア */
        Can_fs_ClearBusOffStatus( u1Controller );
    }
}


/****************************************************************************/
/* Function Name | Can_ResetController                                      */
/* Description   | CANコントローラ再初期化                                  */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   再初期化を実施するCANコントローラ                      */
/*               | uint8 CanControllerBaudrateConfigSet :                   */
/*               |   コントローラボーレートコンフィグセット番号(使用しない) */
/* Return Value  | なし                                                     */
/* Notes         | ・ボーレートコンフィグセット番号は将来拡張用(0固定)であり*/
/*               |   本ソフトでは使用しない。                               */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・CANコントローラ初期化処理が完了したコントローラでのみ  */
/*               |   実施される前提とする。                                 */
/****************************************************************************/
void
Can_ResetController( uint8 Controller, uint8 CanControllerBaudrateConfigSet )
{
    uint8  u1Ret;     /* 再初期化実施状態 */

    /* コントローラに対するフェールが検出された場合に         */
    /* コントローラを再初期化する。                           */
    /* 本処理要求時はコントローラ状態によらず処理を実施する。 */

    /* コントローラ再初期化処理の要求前に            */
    /* CANコントローラ状態を再初期化待ちに設定する。 */
    Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_RST;

    /* 送信情報クリア */
    Can_tx_ClearTxInf( Controller );

    /* コントローラ関連レジスタリセット */
    u1Ret = Can_st_Reset( Controller );
    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        /* リセット成功時 */

        /* MBOXコンフィグ設定 */
        Can_st_SetConfigMbox( Controller );

        /* CANコントローラ状態を通信停止に設定 */
        Can_st_u2ControllerStatus[ Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }

    /* バスオフ発生情報のクリア                                      */
    /* ※ リセットが完了していない場合は、バスからコントローラが     */
    /*    切断されておらず、バスオフが継続発生している可能性がある。 */
    /*    その場合、バスオフ発生情報がクリアできないため             */
    /*    リセット成功後(コントローラ停止確定後)に実施する。         */
    /* ※ リセット要求前に発生していたバスオフ情報はクリアしておく   */
    /*    必要があるため、コントローラ再初期化処理の完了/未完了に    */
    /*    かかわらずクリア処理を実施する。                           */
    /* ※ バスオフ情報の参照はMainFunctionBusOff(中優先度処理)のみ   */
    /*    のためコントローラ状態更新後のクリアでも問題なし。         */
    Can_fs_ClearBusOffStatus( Controller );
}


/****************************************************************************/
/* Function Name | Can_SetBaudrate                                          */
/* Description   | ボーレート設定                                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   ボーレート設定を実施するCANコントローラ                */
/*               | uint16 BaudRateConfigID :                                */
/*               |   ボーレートコンフィグID                                 */
/* Return Value  | Can_ReturnType ボーレート設定結果                        */
/*               |   CAN_OK     : 設定完了                                  */
/*               |   CAN_NOT_OK : 設定失敗                                  */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・コントローラ開始前通知からのみ呼び出される前提とする。 */
/****************************************************************************/
Can_ReturnType
Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
    uint8  u1BRChgRet;             /* ボーレート設定結果 */
    uint8  u1Ret;                  /* 戻り値             */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    /* ボーレート設定 */
    u1BRChgRet = Can_st_SetBaudrate( Controller, BaudRateConfigID );
    if ( u1BRChgRet == (uint8)CAN_PROC_OK )
    {
        u1Ret = (uint8)CAN_OK;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_CheckStopCompletion                                  */
/* Description   | 通信停止完了確認                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   通信停止完了を確認するCANコントローラ                  */
/* Return Value  | Can_ReturnType 通信停止完了状態                          */
/*               |   CAN_OK     : 停止完了                                  */
/*               |   CAN_NOT_OK : 停止未完了                                */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/****************************************************************************/
Can_ReturnType
Can_CheckStopCompletion( uint8 Controller )
{
    uint16  u2ControllerStatus;     /* CANコントローラ状態 */
    uint8   u1Ret;                  /* 通信停止完了状態    */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if (( u2ControllerStatus != (uint16)CAN_ST_CTRL_INIT    )
    &&  ( u2ControllerStatus != (uint16)CAN_ST_CTRL_STOPPED ))
    {
        /* 使用CANで初期化済、通信停止のどちらの状態でもない場合、停止未完了とする */
        u1Ret = (uint8)CAN_NOT_OK;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_GetControllerStatus                                  */
/* Description   | CANコントローラ状態取得                                  */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   CANコントローラ状態を取得するCANコントローラ           */
/* Return Value  | Can_CtrlStType CANコントローラ状態取得結果               */
/*               |   CAN_CTRLST_NOT_OK         : CANコントローラ状態取得失敗*/
/*               |   CAN_CTRLST_UNINIT         : 未初期化                   */
/*               |   CAN_CTRLST_INIT           : 初期化済                   */
/*               |   CAN_CTRLST_STOPPED        : 通信停止                   */
/*               |   CAN_CTRLST_STARTED        : 通信中                     */
/*               |   CAN_CTRLST_TO_STOPPED_NML : 通信停止待ち               */
/*               |   CAN_CTRLST_TO_STOPPED_RST : 再初期化待ち               */
/*               |   CAN_CTRLST_TO_STARTED     : 通信開始待ち               */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/****************************************************************************/
Can_CtrlStType
Can_GetControllerStatus( uint8 Controller )
{
    uint16  u2ControllerStatus;     /* CANコントローラ状態 */
    uint8   u1Ret;                  /* 戻り値              */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_CTRLST_NOT_OK;

    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];

    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        u1Ret = (uint8)CAN_CTRLST_STOPPED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        u1Ret = (uint8)CAN_CTRLST_STARTED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STOPPED_NML;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STOPPED_RST;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
    {
        u1Ret = (uint8)CAN_CTRLST_TO_STARTED;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_INIT )
    {
        u1Ret = (uint8)CAN_CTRLST_INIT;
    }
    else if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_UNINIT )
    {
        u1Ret = (uint8)CAN_CTRLST_UNINIT;
    }
    else /* MISRA DEVIATION: no process */
    {
        /* CANコントローラ状態が化けた場合はNOT_OKを応答 */
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_st_ControllerStop                                    */
/* Description   | コントローラ停止指示                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_st_ControllerStop( uint8 u1Controller )
{
    uint8  u1ModeChgRet;     /* モード遷移結果 */

    /* フェール検出時の通信停止処理を実施する。 */

    /* コントローラ通信停止処理の要求前に            */
    /* CANコントローラ状態を通信停止待ちに設定する。 */
    Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_TO_STOPPED_NML;

    /* コントローラ通信停止処理の実行 */
    u1ModeChgRet = Can_st_Stop( u1Controller );
    if ( u1ModeChgRet == (uint8)CAN_PROC_OK )
    {
        /* 通信停止成功時 */

        /* CANコントローラ状態を通信停止に設定 */
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }
    /* コントローラ通信停止処理が完了しなかった場合 */
    /* CANコントローラ状態は通信停止待ちのまま      */
    /* 以降、Can_MainFunctionModeにて遷移する。     */

    /* フェール検出時は状態によらず停止処理を実施する。                             */
    /* なお、フェール通知により、本処理後に再初期化が要求される前提とする。         */

    /* UNINIT状態中は定期処理が実施されないため本機能は実施されない前提とする。     */
    /* INIT状態中のフェール検出(状態RAM異常を含む)の場合、                          */
    /* 初期化未完了でSTOP状態に遷移するが、フェール通知にて上位が初期化異常判定し、 */
    /* 以降シャットダウンまでCANへの通信開始要求は発生しない前提とする。            */
    /* TO_STOPPED_RST状態中のフェール検出の場合、再初期化処理が完了しないまま       */
    /* STOP状態に遷移する可能性があるが、フェール通知により、本処理後に再初期化が   */
    /* 再度要求されるため状態の不整合は継続しない。                                 */
}


/****************************************************************************/
/* Function Name | Can_st_StopInd                                           */
/* Description   | コントローラ停止通知                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | phy層の動作によりCANコントローラが停止してしまう場合に、 */
/*               | コントローラ状態との矛盾を解消するため本関数を呼び出す。 */
/****************************************************************************/
void
Can_st_StopInd( uint8 u1Controller )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */

    /* コントローラ初期化が完了している場合のみ、STOP状態に遷移する。 */
    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML )
    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_RST ))
    {
        Can_st_u2ControllerStatus[ u1Controller ] = (uint16)CAN_ST_CTRL_STOPPED;
    }
}


/****************************************************************************/
/* Function Name | Can_st_PreStart                                          */
/* Description   | コントローラ開始前処理                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_st_PreStart( uint8 u1Controller )
{
    Can_UPreStart( u1Controller );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
