/* can_rsc_fs_log_c_v2-2-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSC/FS/LOGICAL/CODE                                   */
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
#include <can/rsc/can_rsc_st.h>
#include <can/rsc/can_rsc_fs.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* ビットマスク */
#define CAN_FS_MASK_LOWERBYTE           (0x00FFU)

/* ビットシフト */
#define CAN_FS_BITSHIFT_8               (8U)

/* レジスタ固着チェック実施履歴 */
#define CAN_FS_REGCHK_HIST_NONE         (0x5AU)   /* レジスタ固着チェック実施履歴なし                     */
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
#define CAN_FS_REGCHK_HIST_OPT_NOT_BUSY (0xA5U)   /* レジスタ固着チェック中      (未使用MBOXでの固着検出) */
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
#define CAN_FS_REGCHK_HIST_OK           (0x96U)   /* レジスタ固着チェック結果成功                         */
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
#define CAN_FS_REGCHK_HIST_OPT_NOT_OK   (0x69U)   /* レジスタ固着チェック結果成功(未使用MBOXでの固着検出) */
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
#define CAN_FS_REGCHK_HIST_NG           (0x3CU)   /* レジスタ固着チェック結果失敗                         */

/* バスオフ発生状態 */
#define CAN_FS_BUSOFF_NONE              (0x3CU)   /* バスオフ未発生 */
#define CAN_FS_BUSOFF_EXIST             (0x5AU)   /* バスオフ発生   */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static uint8   Can_fs_CheckRamU2( uint16 u2Value );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------*/
/* バスオフ発生情報                                           */
/* ・内容：                                                   */
/*     バスオフ発生の有無を記憶する。                         */
/* ・値域：                                                   */
/*     CAN_FS_BUSOFF_NONE                                     */
/*       バスオフ未発生                                       */
/*     CAN_FS_BUSOFF_EXIST                                    */
/*       バスオフ発生                                         */
/* ・RAM化け対策：                                            */
/*     本パラメータはCan_MainFunction_BusOffにて毎周期        */
/*     チェックする。                                         */
/*     チェックの判定文として、                               */
/*     「バスオフ発生情報 != バスオフ未発生」(１点判定)とし   */
/*     化け発生時にバスオフ発生側に倒し、CANIFにバスオフ通知  */
/*     してもらう事で復旧させる。                             */
/*------------------------------------------------------------*/
static uint8 Can_fs_u1BusOffStatus[ CAN_CFG_CONTROLLERNUM_MAX ];


/*------------------------------------------------------------*/
/* レジスタ固着チェック未完了応答回数                         */
/* ・内容：                                                   */
/*     レジスタ固着チェックの分割実施中における、分割実施済み */
/*     の処理回数（固着チェック結果未完了を応答した回数）を   */
/*     保持する。                                             */
/*     レジスタ固着チェックの要求時、最大分割回数を超えて     */
/*     "BUSY"を応答しないようにガードする。                   */
/* ・値域：                                                   */
/*     0 - CAN_CFG_CHKSTKREG_LIMIT                            */
/* ・RAM化け対策：                                            */
/*     初期化直後にのみ提供する機能で使用するパラメータであり */
/*     かつ、RAM化け発生はCANIF側で検出でき、再初期化される   */
/*     ため、CANとしては処置しない。                          */
/*------------------------------------------------------------*/
static uint8 Can_fs_u1RegChkWaitCnt[ CAN_CFG_CONTROLLERNUM_MAX ];


/*------------------------------------------------------------*/
/* レジスタ固着チェック実施履歴                               */
/* ・内容：                                                   */
/*     レジスタ固着チェックの実施履歴を保持する。             */
/*     レジスタ固着チェック完了後に再度レジスタ固着チェックが */
/*     呼び出された場合に、チェック完了時点の応答結果を       */
/*     再度提供する。                                         */
/* ・値域：                                                   */
/*     CAN_FS_REGCHK_HIST_NONE                                */
/*       レジスタ固着チェック実施履歴なし                     */
/*     CAN_FS_REGCHK_HIST_OK                                  */
/*       レジスタ固着チェック結果成功                         */
/*     CAN_FS_REGCHK_HIST_NG                                  */
/*       レジスタ固着チェック結果失敗                         */
/*     CAN_FS_REGCHK_HIST_OPT_NOT_BUSY                        */
/*       レジスタ固着チェック中(未使用MBOXでの固着検出)       */
/*     CAN_FS_REGCHK_HIST_OPT_NOT_OK                          */
/*       レジスタ固着チェック結果成功(未使用MBOXでの固着検出) */
/* ・RAM化け対策：                                            */
/*     処置方針の原則として、レジスタ固着異常検出に対応する。 */
/*     設定値を上位4bit, 下位4bitを反転させた値とする。       */
/*     設定値には、1bit化けで別の値にならないものを設定する。 */
/*------------------------------------------------------------*/
static uint8 Can_fs_u1RegChkHist[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_Init                                              */
/* Description   | フェールセーフ機能初期化                                 */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_Init( void )
{
    uint8  u1Controller;           /* コントローラID */
    uint8  u1ControllerNumMax;     /* コントローラ数 */

    /* フェールセーフ機能が保持するRAMの初期化を実施 */
    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        Can_fs_u1BusOffStatus[ u1Controller ]  = (uint8)CAN_FS_BUSOFF_NONE;
        Can_fs_u1RegChkWaitCnt[ u1Controller ] = (uint8)0U;
        Can_fs_u1RegChkHist[ u1Controller ]    = (uint8)CAN_FS_REGCHK_HIST_NONE;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_ClearBusOffStatus                                 */
/* Description   | バスオフ発生情報クリア                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_ClearBusOffStatus( uint8 u1Controller )
{
    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_NONE;
}


/****************************************************************************/
/* Function Name | Can_MainFunction_BusOff                                  */
/* Description   | バスオフ定期処理                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・本APIはCANIFから呼び出されるため、CANIFの状態によって  */
/*               |   必ずしも定期的に呼び出されない。そのため、厳密な時間   */
/*               |   監視処理は実施しない。                                 */
/****************************************************************************/
void
Can_MainFunction_BusOff( void )
{
    CanConst CanTbControllerConfigType *    ptCtrCfgTbl;           /* コントローラ設定テーブルへのポインタ */
    uint16                                  u2ControllerStatus;    /* コントローラ状態                     */
    uint8                                   u1Controller;          /* コントローラID                       */
    uint8                                   u1ControllerNumMax;    /* コントローラ数                       */

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* 制御対象 かつ 使用コントローラを対象とする。 */
        ptCtrCfgTbl = &(Can_tb_stControllerCfgTbl[ u1Controller ]);
        if (( ptCtrCfgTbl->u1ControllerActivation == (uint8)CAN_TRUE )
        &&  ( ptCtrCfgTbl->u1ControllerUse        == (uint8)CAN_USE ) )
        {
            /* コントローラ別バスオフ復帰方法の確認 */
            if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffRecovery == (uint8)CAN_MANUAL )
            {
                /* コントローラ別バスオフ復帰方法を手動で実施する場合 */

                /* 制御対象CAN かつ 使用するコントローラに対し                    */
                /* バスオフが発生しているかをチェックする。                       */

                /* バスオフのチェックは、バスオフが発生しうるコントローラ状態の   */
                /* 場合のみ行う。                                                 */

                /* CAN_ST_CTRL_UNINIT, CAN_ST_CTRL_INIT, CAN_ST_CTRL_STOPPED      */
                /*   : 受付しない                                                 */
                /*     コントローラが開始していないためバスオフは発生しない。     */
                /* CAN_ST_CTRL_TO_STOPPED_NML                                     */
                /*   : 受付                                                       */
                /*     コントローラ開始後、停止前のためバスオフ発生の可能性あり。 */
                /* CAN_ST_CTRL_TO_STOPPED_RST                                     */
                /*   : 受付しない                                                 */
                /*     本ケースは、バスオフ発生、またはフェール発生時の復旧過程   */
                /*     のため、復旧完了まではバスオフ検出・通知は実施しない。     */
                /* CAN_ST_CTRL_STARTED                                            */
                /*   : 受付                                                       */
                /* CAN_ST_CTRL_TO_STARTED                                         */
                /*   : 受付                                                       */
                /*     CAN_ST_CTRL_STOPPED→CAN_ST_CTRL_TO_STARTED のパスでは     */
                /*     バスオフは発生しないが、上位からのモード遷移要求が連続で   */
                /*     発行され、CAN_ST_CTRL_STARTED→CAN_ST_CTRL_TO_STOPPED_NML  */
                /*      →CAN_ST_CTRL_TO_STARTEDと動いた場合を考慮し、受付する。  */

                /* バスオフ検出方法がポーリングの場合 */
                /* 最新のバスオフ発生情報を取得       */
                if ( Can_tb_stControllerCfgTbl[ u1Controller ].u1BusoffProcessing == (uint8)CAN_POLLING )
                {
                    /* CANコントローラの状態チェック */
                    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
                    if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
                    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED )
                    ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STOPPED_NML ))
                    {
                        /* バスオフ発生情報を更新。戻り値は割り込み用のため使用しない。 */
                        (void)Can_fs_ChkBusOff( u1Controller ); /* MISRA DEVIATION: no return check required */
                    }
                }

                /* バスオフ発生情報のチェック */
                if ( Can_fs_u1BusOffStatus[ u1Controller ] != (uint8)CAN_FS_BUSOFF_NONE )
                {
                    /* バスオフが未発生ではない場合 */
                    /* (RAM化けを考慮し、異常値もバスオフ側で処置) */

                    /* CANIF通知前にバスオフ発生情報をクリア               */
                    /* バスオフ検出後、毎周期CANIFに通知することを防ぐため */
                    /* バスオフ通知が確定した本タイミングでクリアする。    */
                    /* ※ 割り込みでバスオフを検出する場合は               */
                    /*    クリア後に再度更新される可能性もあるが、         */
                    /*    取りこぼしではないため問題なし。                 */
                    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_NONE;

                    /* コントローラの停止 */
                    Can_st_ControllerStop( u1Controller );

                    /* CANIFにバスオフ発生を通知 */
                    CanIf_ControllerBusOff( u1Controller );
                }
            }
            else
            {
                /* コントローラ別バスオフ復帰方法を自動で実施する場合 */

                /* 制御対象CAN かつ 使用するコントローラに対し                    */
                /* バスオフからの自動復帰を行う。                                 */

                /* バスオフのチェックは、バスオフが発生しうるコントローラ状態の   */
                /* 場合のみ行う。                                                 */

                /* CAN_ST_CTRL_UNINIT, CAN_ST_CTRL_INIT, CAN_ST_CTRL_STOPPED      */
                /*   : 受付しない                                                 */
                /*     コントローラが開始していないためバスオフは発生しない。     */
                /* CAN_ST_CTRL_TO_STOPPED_NML                                     */
                /*   : 受付しない                                                 */
                /*     コントローラ開始後、停止前のためバスオフ発生の可能性あり。 */
                /*     コントローラ停止に遷移するため、自動復帰させない。         */
                /* CAN_ST_CTRL_TO_STOPPED_RST                                     */
                /*   : 受付しない                                                 */
                /*     本ケースは、バスオフ発生、またはフェール発生時の復旧過程   */
                /*     のため、復旧完了まではバスオフ検出・通知は実施しない。     */
                /* CAN_ST_CTRL_STARTED                                            */
                /*   : 受付                                                       */
                /* CAN_ST_CTRL_TO_STARTED                                         */
                /*   : 受付                                                       */
                /*     CAN_ST_CTRL_STOPPED→CAN_ST_CTRL_TO_STARTED のパスでは     */
                /*     バスオフは発生しないが、上位からのモード遷移要求が連続で   */
                /*     発行され、CAN_ST_CTRL_STARTED→CAN_ST_CTRL_TO_STOPPED_NML  */
                /*      →CAN_ST_CTRL_TO_STARTEDと動いた場合を想定。              */
                /*     この場合、通信開始に遷移するが、バスオフ復帰処理と通信開始 */
                /*     処理の処理内容が異なるマイコンも想定されるため、受付する。 */

                /* CANコントローラの状態チェック */
                u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
                if (( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
                ||  ( u2ControllerStatus == (uint16)CAN_ST_CTRL_TO_STARTED ))
                {
                    /* バスオフからの自動復帰 */
                    Can_fs_BusOffRecovery( u1Controller );
                }
            }
        }

        /*==== 非制御対象コントローラ ====*/
        /* ユーザCANとして使用する場合、ユーザにて処置。 */

    }
}


/****************************************************************************/
/* Function Name | Can_fs_BusOffInd                                         */
/* Description   | コントローラバスオフ検出通知                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_BusOffInd( uint8 u1Controller )
{
    /* バスオフがある場合は                   */
    /* コントローラモード状態によらず保持する */

    Can_fs_u1BusOffStatus[ u1Controller ] = (uint8)CAN_FS_BUSOFF_EXIST;
}


/****************************************************************************/
/* Function Name | Can_CheckStuckRegister                                   */
/* Description   | レジスタ固着チェック                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   レジスタ固着チェックを実施するCANコントローラ          */
/* Return Value  | Can_ReturnType レジスタ固着チェック結果                  */
/*               |   CAN_OK         : レジスタ固着異常未検出                */
/*               |   CAN_NOT_OK     : レジスタ固着異常検出                  */
/*               |   CAN_BUSY       : レジスタ固着チェック未完了            */
/*               |   CAN_OPT_NOT_OK : レジスタ固着異常検出(未使用MBOX)      */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・レジスタ固着チェック完了時(CAN_OK ,CAN_NOT_OK,         */
/*               |   CAN_OPT_NOT_OKを応答時)に、実施結果をレジスタ固着      */
/*               |   チェック実施履歴に保持する。レジスタ固着チェック実施   */
/*               |   履歴が初期化される前に再度本関数が呼び出された場合には */
/*               |   記憶した実施結果を応答する。                           */
/****************************************************************************/
Can_ReturnType
Can_CheckStuckRegister( uint8 Controller )
{
    uint16  u2ControllerStatus;     /* コントローラ状態                   */
    uint8   u1Ret;                  /* 戻り値                             */
    uint8   u1ChkResult;            /* レジスタ固着チェック結果           */
    uint8   u1RegChkWaitCnt;        /* レジスタ固着チェック未完了応答回数 */
    uint8   u1RegChkHist;           /* レジスタ固着チェック実施履歴       */
    uint8   u1RegChkNum;            /* レジスタ固着チェック分割回数       */

    /*  指定コントローラのMBOXレジスタ固着状態を確認し、結果を応答 */
    /*  する。本機能の対象はMBOXの ID, DLC, DATA領域のレジスタ     */
    /*  とする。                                                   */

    /* レジスタ固着チェック実施方法について                        */
    /* 本APIは、コンフィグレーションである最大分割回数で           */
    /* 指定された回数でレジスタ固着チェックの処理を実施する        */
    /*（指定された回数より少ない回数で処理が完了することはない）。 */
    /* 例)CAN_CFG_CHKSTKREG_LIMIT = 12 とした場合                  */
    /*    本APIを12回発行し、その間レジスタ固着チェック実施が全て  */
    /*    成功した場合、12回目の呼び出し時にレジスタ固着異常未検出 */
    /*    を応答する。                                             */

    /* 戻り値をレジスタ固着チェック失敗で初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    /* コントローラ状態の確認 */
    u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STOPPED )
    {
        /* レジスタ固着チェック実施履歴の確認 */
        u1RegChkHist = Can_fs_u1RegChkHist[ Controller ];
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
        if ( (u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_NONE) || (u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY) )
#else /* (CAN_CFG_CHKSTKREG_RESP != CAN_RESP_OPT_NOT_OK) */
        if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_NONE )
#endif /* (CAN_CFG_CHKSTKREG_RESP) */
        {
            /* 実施履歴がない場合 */
            /* レジスタ固着チェック未完了応答回数のRAM化けチェック       */
            /* ※ マイコン依存部のAPI引数に、異常値を渡さないための確認。*/
            /*    正常系（RAM化け未発生)であれば                         */
            /*    u1RegChkWaitCnt < Can_tb_u1RegChkNum は必ず真となる。  */
            u1RegChkWaitCnt = Can_fs_u1RegChkWaitCnt[ Controller ];
            u1RegChkNum = Can_tb_u1RegChkNum;
            if ( u1RegChkWaitCnt < u1RegChkNum )
            {
                /* 最大分割回数まで実施していない場合 */
                /* レジスタ固着チェック実施 */
                u1ChkResult = Can_fs_ChkReg( Controller, u1RegChkWaitCnt );
                if ( u1ChkResult == (uint8)CAN_FS_REGCHK_EXIST )
                {
                    /* レジスタ固着異常ありの場合 */
                    /* レジスタ固着チェック実施履歴として失敗を記録 */
                    Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_NG;

                    /* 戻り値として失敗(ローカル変数初期値)を応答 */
                }
                else
                {
                    /* レジスタ固着異常なしの場合 */
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
                    /* 未使用MBOXでレジスタ固着を検出した場合、レジスタ固着チェック実施履歴を更新する */
                    if ( u1ChkResult == (uint8)CAN_FS_REGCHK_OPT_EXIST )
                    {
                        Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY;
                    }
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */

                    /* レジスタ固着チェック未完了応答回数の更新 */
                    u1RegChkWaitCnt++;
                    Can_fs_u1RegChkWaitCnt[ Controller ] = u1RegChkWaitCnt;

                    /* 最大分割回数に到達したか、否かをチェック */
                    if ( u1RegChkWaitCnt < u1RegChkNum )
                    {
                        /* 最大分割回数到達前の場合 */
                        /* チェック未完了を応答     */
                        u1Ret = (uint8)CAN_BUSY;
                    }
                    else
                    {
                        /* MBOXコンフィグの再設定を実施 */
                        Can_st_SetConfigMbox( Controller );

                        /* 最大分割回数到達時 */
                        /* チェック完了       */
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
                        if ( Can_fs_u1RegChkHist[ Controller ] == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_BUSY )
                        {
                            /* 未使用MBOXでのレジスタ固着検出履歴がある場合 */

                            /* レジスタ固着チェック実施履歴として成功(未使用MBOXでの固着検出)を記録 */
                            Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_OK;
                            /* レジスタ固着異常未検出(OPT_NOT_OK)を応答 */
                            u1Ret = (uint8)CAN_OPT_NOT_OK;

                        }
                        else
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
                        {
                            /* 未使用MBOXでのレジスタ固着検出履歴がない場合 */

                            /* レジスタ固着チェック実施履歴として成功を記録 */
                            Can_fs_u1RegChkHist[ Controller ] = (uint8)CAN_FS_REGCHK_HIST_OK;
                            /* レジスタ固着異常未検出(OK)を応答 */
                            u1Ret = (uint8)CAN_OK;
                        }
                    }
                }
            }
        }
        else if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OK )
        {
            /* 成功の履歴がある場合 */
            /* 戻り値を成功で更新   */
            u1Ret = (uint8)CAN_OK;
        }
#if (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK)
        else if ( u1RegChkHist == (uint8)CAN_FS_REGCHK_HIST_OPT_NOT_OK )
        {
            /* 成功(未使用MBOXでの固着検出)の履歴がある場合 */
            /* 戻り値を成功(未使用MBOXでの固着検出)で更新   */
            u1Ret = (uint8)CAN_OPT_NOT_OK;
        }
#endif /* (CAN_CFG_CHKSTKREG_RESP == CAN_RESP_OPT_NOT_OK) */
        else /* MISRA DEVIATION: no process */
        {
            /* 失敗履歴がある場合（または、RAM化けによる異常値の場合）は失敗を応答 */
        }
    }
    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_RefreshRegister                                      */
/* Description   | レジスタリフレッシュ                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   レジスタリフレッシュを実施するCANコントローラ          */
/* Return Value  | なし                                                     */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない                                       */
/****************************************************************************/
void
Can_RefreshRegister( uint8 Controller )
{
    /* ユーザ実装関数によるレジスタリフレッシュの実施 */
    Can_URefreshRegister( Controller );
}


/****************************************************************************/
/* Function Name | Can_MainFunction_Fail                                    */
/* Description   | フェール定期処理                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_MainFunction_Fail( void )
{
    CanConst CanTbControllerConfigType *    ptCtrCfgTbl;        /* コントローラ設定テーブルへのポインタ */
    uint16                                  u2ControllerStatus; /* コントローラ状態                     */
    uint8                                   u1Controller;       /* コントローラID                       */
    uint8                                   u1ControllerNumMax; /* コントローラ数                       */
    uint8                                   u1ChkRamResult;     /* コントローラ状態チェック結果         */
    uint8                                   u1ChkMpuResult;     /* マイコン依存部MPU異常チェック結果    */

    /* フェール発生の有無を確認し、フェール有りを確認した */
    /* CANコントローラ番号をCANIFに通知する。             */

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* 制御対象 かつ 使用コントローラを対象とする。 */
        ptCtrCfgTbl = &(Can_tb_stControllerCfgTbl[ u1Controller ]);
        if (( ptCtrCfgTbl->u1ControllerActivation == (uint8)CAN_TRUE )
        &&  ( ptCtrCfgTbl->u1ControllerUse        == (uint8)CAN_USE ) )
        {
            /* コントローラ状態のRAM化けチェック */
            u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
            u1ChkRamResult = Can_fs_CheckRamU2( u2ControllerStatus );

            /* マイコン依存部のMPU異常チェック */
            u1ChkMpuResult = Can_fs_CheckMpu( u1Controller );

            if (( u1ChkRamResult != (uint8)CAN_PROC_OK )
            ||  ( u1ChkMpuResult != (uint8)CAN_NONE ))
            {
                /* 異常検出時処置 */
                /* コントローラの停止 */
                Can_st_ControllerStop( u1Controller );

                /* CANIFにフェール発生を通知 */
                CanIf_ControllerFail( u1Controller );

                /* フェール処理による処理負荷を分散するため、                               */
                /* フェール定期処理の呼び出し一回につき、フェール発生通知は一回のみとする。 */
                break;
            }
        }

        /* 非制御対象 または 未使用コントローラはチェック不要            */
        /* 状態ガード(==状態判定)によりRAM化けしても不定動作とならない。 */
    }
}


/****************************************************************************/
/* Function Name | Can_GetErrorStatus                                       */
/* Description   | エラー状態取得                                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8 Controller :                                       */
/*               |   エラー状態取得を実施するCANコントローラ                */
/* Return Value  | Can_ErrStType エラー状態取得結果                         */
/*               |   CAN_ERRST_NOT_OK        : エラー状態取得失敗           */
/*               |   CAN_ERRST_ERROR_ACTIVE  : エラーアクティブ             */
/*               |   CAN_ERRST_ERROR_PASSIVE : エラーパッシブ               */
/*               |   CAN_ERRST_BUS_OFF       : バスオフ                     */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/****************************************************************************/
Can_ErrStType
Can_GetErrorStatus( uint8 Controller )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1Ret;                  /* 戻り値           */

    u1Ret = (uint8)CAN_ERRST_NOT_OK;

    /* コントローラ別バスオフ復帰方法の確認 */
    if ( Can_tb_stControllerCfgTbl[ Controller ].u1BusoffRecovery == (uint8)CAN_AUTO )
    {
        /* コントローラ別バスオフ復帰方法が自動の場合 */

        /* CANコントローラの状態チェック */
        u2ControllerStatus = Can_st_u2ControllerStatus[ Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* CANコントローラ状態が通信中の場合 */
            /* CANプロトコルエラー状態取得 */
            u1Ret = Can_fs_GetErrorStatus( Controller );
        }
        /* CANコントローラ状態が通信中以外の場合、エラー状態取得失敗を応答する */
    }
    /* コントローラ別バスオフ復帰方法の確認が手動の場合、エラー状態取得失敗を応答する */

    /* Can_ErrStTypeのサイズはuint8のため、Can_ErrStTypeへのキャストを行わず応答する */
    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PrepChkRegRetry                                   */
/* Description   | レジスタ固着チェックリトライ準備処理                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   レジスタ固着チェックリトライ準備処理を                 */
/*               |   実施するCANコントローラ                                */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_PrepChkRegRetry( uint8 u1Controller )
{

    if( Can_fs_u1RegChkHist[ u1Controller ] != (uint8)CAN_FS_REGCHK_HIST_OK )
    {
        Can_fs_u1RegChkHist[ u1Controller ]    = (uint8)CAN_FS_REGCHK_HIST_NONE;
        Can_fs_u1RegChkWaitCnt[ u1Controller ] = (uint8)0U;
    }

    /* 物理層レジスタ固着チェックリトライ準備処理 */
    Can_fs_PhyPrepChkRegRetry( u1Controller );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_CheckRamU2                                        */
/* Description   | 符号なし2バイト型RAM化けチェック                         */
/* Preconditions | -                                                        */
/* Parameters    | uint16 u2Value    : チェック対象符号なし2バイト型RAM値   */
/* Return Value  | uint8  RAM化けチェック結果                               */
/*               |   CAN_PROC_OK : 正常(RAM化け未発生)                      */
/*               |   CAN_PROC_NG : 異常(RAM化け発生)                        */
/* Notes         | なし                                                     */
/****************************************************************************/
static uint8
Can_fs_CheckRamU2( uint16 u2Value )
{
    uint16  u2HiByte;               /* 上位8bit */
    uint16  u2LoByte;               /* 下位8bit */
    uint16  u2Sum;                  /* 合算値   */
    uint8   u1Ret;                  /* 戻り値   */

    /* 上位8bitと下位8bitを反転保持する符号なし2バイト型RAMに対して */
    /* RAM化けが発生していないかを検証する。                        */

    u1Ret = (uint8)CAN_PROC_OK;

    u2HiByte = (uint16)(u2Value >> CAN_FS_BITSHIFT_8);
    u2LoByte = u2Value  & (uint16)CAN_FS_MASK_LOWERBYTE;

    /* 上位8bitと下位8bitの和を算出              */
    /* 0xFFとなれば正常、ならなければRAM化け発生 */
    u2Sum = (uint16)(u2HiByte + u2LoByte);
    if ( u2Sum != (uint16)CAN_FS_MASK_LOWERBYTE )
    {
        u1Ret = (uint8)CAN_PROC_NG;
    }

    return (u1Ret);
}


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-2-0         :2020/02/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
