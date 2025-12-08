/* can_rscf2_st_phy_c_m10700_v3-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/ST/PHYSICAL/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf2/can_rscf2_cfg_ext.h"
#include "../../cfg/rscf2/can_rscf2_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf2/can_rscf2.h>
#include <can/rscf2/can_rscf2_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf2/can_rscf2_tb_phy.h>
#include <can/rscf2/can_rscf2_fs.h>
#include <can/rscf2/can_rscf2_st.h>

#if (CAN_CFG_TRANSMIT == CAN_USE)
#include <can/rscf2/can_rscf2_tx.h>
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_ST_BUF_SND_TOP              (6U)                /* 送信バッファ先頭番号(送信バッファマージモード以外) */
#else /* (CAN_OPEMODE != CAN_OPEMODE_CANFD) */
#define CAN_ST_BUF_SND_TOP              (0U)                /* 送信バッファ先頭番号   */
#endif /* (CAN_OPEMODE) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void  Can_st_GlobalMode_Reset2Stop( void );
static void  Can_st_GlobalMode_Reset2Comm( void );
static void  Can_st_ChannelMode_Any2Reset( uint8 u1Controller );
static void  Can_st_ChannelMode_Reset2Stop( uint8 u1Controller );
static void  Can_st_ChannelMode_Reset2Comm( uint8 u1Controller );
static uint8 Can_st_GlobalRegCheck( uint8 u1Controller );
static void  Can_st_InitGlobalReg( void );
static void  Can_st_InitChannelReg( uint8 u1Controller );
static void  Can_st_SetGlobalReg( void );
static void  Can_st_SetChannelReg( uint8 u1Controller );
static void  Can_st_StopGlobal( void );
static uint8 Can_st_StopChannel( uint8 u1Controller );
static void  Can_st_StartGlobal( void );
static uint8 Can_st_StartChannel( uint8 u1Controller );
static uint8 Can_st_ResetGlobal( void );
static uint8 Can_st_ResetChannel( uint8 u1Controller );
static void  Can_st_SetRxRule( void );
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
static void Can_st_PhyInit( void );
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------*/
/* BRS設定値                                                  */
/* ・内容：                                                   */
/*     BRS設定値を保持する。                                  */
/* ・値域：                                                   */
/*   CAN_ST_BRS_USE   ビットレートスイッチ使用                */
/*   CAN_ST_BRS_NOUSE ビットレートスイッチ未使用              */
/* ・RAM化け対策：                                            */
/*     処置方針の原則として、異常検出と通知に対応する。       */
/*     設定値を上位4bit, 下位4bitを反転させた値とし、和が     */
/*     0xFとなれば正常、ならなければ異常として判断する。      */
/* ・チェックタイミング:                                      */
/*     Can_MainFunction_Fail                                  */
/*     Can_Write                                              */
/*------------------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
uint8 Can_st_u1BRSUse[ CAN_CFG_CONTROLLERNUM_MAX ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Can_st_InitReg                                           */
/* Description   | 初期化時CANレジスタ設定                                  */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | uint8 CANレジスタ設定結果                                */
/*               |   CAN_PROC_OK   : 設定完了                               */
/*               |   CAN_PROC_BUSY : 設定未完了                             */
/* Notes         | ・任意のグローバルモードから呼び出される前提とする。     */
/*               | ・本APIの処理が成功した場合、以下のモードとなる。        */
/*               |   グローバルモード                                       */
/*               |   - グローバルリセットモード                             */
/*               |   チャネルモード                                         */
/*               |   - [使用CAN]   チャネルリセットモード                   */
/*               |   - [未使用CAN] チャネルストップモード                   */
/*               |   - [ユーザCAN] チャネルストップモード                   */
/****************************************************************************/
uint8
Can_st_InitReg( void )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    uint32                              u4GSTS;             /* グローバルステータスレジスタラッチ用         */
    uint32                              u4WaitCount;        /* ループカウンタ                               */
    uint32                              u4InitCycleMax;     /* CAN RAM初期化用カウンタ最大値                */
    uint8                               u1Controller;       /* ループ用コントローラID                       */
    uint8                               u1ControllerUse;    /* コントローラ使用/未使用                      */
    uint8                               u1CtrlNum;          /* コントローラ数                               */
    uint8                               u1Ret;              /* 戻り値                                       */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* 物理層個別のRAM初期化 */
    Can_fs_PhyInit();
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    Can_st_PhyInit();
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* CAN RAM初期化の完了待ち */
    u4GSTS         = CAN_u4GSTS_GRAMINIT;
    u4InitCycleMax = Can_tb_u4RAMInitCycleMax;
    for ( u4WaitCount = 0UL; ( u4WaitCount < u4InitCycleMax ) && ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4GSTS_GRAMINIT ); u4WaitCount++ )
    {
        /* グローバルステータスレジスタの取得 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }

    /* CAN RAM初期化完了確認 */
    if ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4BIT_NONE )
    {   /* CAN RAM初期化完了 */

        /* マイコン制約上、グローバル動作モードから、グローバルストップモードへの遷移は禁止である。               */
        /* 一方、本関数はCan_st_ShutdownRegでのグローバルリセットモード遷移失敗（グローバル動作モード継続）後にも */
        /* 本関数が呼び出されることがありえるため、まずはグローバルリセットモードへ遷移させる。                   */

        /* グローバルリセットモード設定 */
        Can_st_GlobalMode_Any2Reset();

        /* 状態遷移確認 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
        if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
        {   /* グローバルリセットモード遷移成功時 */

            /* グローバルレジスタ初期化 */
            Can_st_InitGlobalReg();

            /* チャネル単位のレジスタ初期化 */
            u1CtrlNum = Can_tb_u1CtrlNum;
            for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
            {
                /* 制御対象CANの初期化 */
                if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
                {
                    /* チャネルリセットモード設定 */
                    /* ※ 既にリセットモードに遷移済みの可能性もあるが、呼び出しても問題なし */
                    Can_st_ChannelMode_Any2Reset( u1Controller );

                    /* 状態遷移確認 */
                    ptChReg = &Can_tb_stChReg[ u1Controller ];
                    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
                    {   /* チャネルリセットモード遷移成功 */

                        /* チャネル単位レジスタの初期化 */
                        Can_st_InitChannelReg( u1Controller );
                    }

                    /* 初期化完了後、使用CAN以外はチャネルストップモードに遷移させる。 */
                    u1ControllerUse = Can_tb_stCtrlInfo[ u1Controller ].u1CtrlUse;
                    if ( u1ControllerUse != (uint8)CAN_USE )
                    {
                        Can_st_ChannelMode_Reset2Stop( u1Controller );
                    }
                }
                /* 非制御対象CANはチャネルストップモードもしくはチャネルリセットモードになっており */
                /* 不要に動作することはないためアクセスしない                                      */
            }

            /* グローバルレジスタ使用設定 */
            /* ※ レジスタの使用値設定は、関数の役割上は Can_st_SetControl で実施するものである。  */
            /*    しかし、本関数以降、上位層はチャネル単位の制御を前提とした呼び出しシーケンスと   */
            /*    なっているため、グローバル要素に関しては本関数で設定を完了させる。               */
            Can_st_SetGlobalReg();

            /* ※ 注意・留意事項                                                                   */
            /*    ソフトウェア仕様書対応のため、本APIでグローバルレジスタの使用値を設定しているが  */
            /*    一方で、レジスタ固着チェック機能を使用する場合、グローバルテストモードと         */
            /*    グローバルリセットモードの行き来が発生するため、設定がクリアされる可能性がある。 */
            /*    よって、若干重複するが、通信開始前にレジスタの使用値設定をやり直す設計とする。   */

            u1Ret = (uint8)CAN_PROC_OK;
        }
        /* グローバルリセットモード遷移失敗の場合、何もしない。   */
        /* UM上規定された最悪時間経過後のため、永続故障と考える。 */
    }
    /* CAN RAM初期化未完了の場合、何もしない。                */
    /* UM上規定された最悪時間経過後のため、永続故障と考える。 */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_SetControl                                        */
/* Description   | コントローラ個別レジスタ設定                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ個別レジスタ設定結果                   */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | ・正常系では、グローバルリセットモード、グローバル動作   */
/*               |   モードから呼び出される。ただし、異常系                 */
/*               |   (Can_CheckStuckRegister失敗)を考慮し、任意の           */
/*               |   グローバルモードから呼び出される想定で設計とする。     */
/****************************************************************************/
uint8
Can_st_SetControl( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    uint32                              u4GSTS;             /* グローバルステータスレジスタラッチ用         */
    uint8                               u1Ret;              /* 戻り値                                       */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* グローバルモード確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    ||   ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM  ) )
    {   /* グローバルリセットモード or グローバル動作モードの場合 */

        /* チャネルモード確認 */
        ptChReg = &Can_tb_stChReg[ u1Controller ];
        if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
        {   /* チャネルリセットモードの場合 */

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
            /* BRS設定値初期化 */
            Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

            /* チャネルレジスタ使用設定 */
            Can_st_SetChannelReg( u1Controller );

            u1Ret = (uint8)CAN_PROC_OK;
        }
        /* チャネルリセットモード以外の場合、HW故障により意図通り状態遷移できていない場合となる。 */
        /* そのため、BUSYを返すのみとする。                                                       */
    }
    /* グローバルストップモード、グローバルテストモードの場合 */
    /* HW故障により意図通り状態遷移できていない場合となる。   */
    /* そのため、BUSYを返すのみとする。                       */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Start                                             */
/* Description   | コントローラ通信開始                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ通信開始結果                           */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 本関数コール時のグローバルモードは以下の状態のいずれか   */
/*               |   ・グローバル動作モード                                 */
/*               |   ・グローバルリセットモード                             */
/****************************************************************************/
uint8
Can_st_Start( uint8 u1Controller )
{
    uint32    u4GSTS;             /* グローバルステータスレジスタラッチ用 */
    uint8     u1Ret;              /* 戻り値                               */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* 本関数呼び出し時のグローバル状態は以下である                              */
    /* ①初期化／再初期化完了後                       ：グローバルリセットモード */
    /* ②初期化／再初期化完了後、かつ                                            */
    /*   通信停止完了後 or 他チャネルの通信開始完了後 ：グローバル動作モード     */

    /* グローバルモードの確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {   /* グローバルリセットモードの場合 */

        /* グローバルレジスタ開始設定 */
        Can_st_StartGlobal();
    }

    /* グローバルモードの再確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM )
    {   /* グローバル動作モードの場合 */

        /* 補足・考え方                                                           */
        /* - 異常が発生し、Stop→Reset→Startの呼び出しシナリオが発生した場合     */
        /* - Reset処理中にグローバルレジスタの異常を検知し、再設定しようとしたが  */
        /*   グローバルリセットモードの遷移も失敗した場合、                       */
        /*   上位層がResetの成功を待たずにStartを要求するため、グローバルレジスタ */
        /*   の復旧をやりきれないまま、本パスに入るシナリオも考えられるが         */
        /*   本ケースは多重故障にあたるため、これ以上のガード処置は含めていない。 */

        /* チャネル通信開始 */
        u1Ret = Can_st_StartChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Stop                                              */
/* Description   | コントローラ通信停止                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ通信停止結果                           */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/*               | 以下のチャネルモードから呼ばれる前提とする。             */
/*               |  - チャネルリセットモード                                */
/*               |  - チャネル待機モード                                    */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
uint8
Can_st_Stop( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ   */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ        */
    CanConst CanTbTxMbBitType *         ptTxMbBit;          /* 送信MBOX種別ビット情報テーブルへのポインタ     */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                              u4CFSTSk_FIFO0;     /* 送受信FIFO0 バッファステータスレジスタラッチ用 */
    uint32                              u4CFSTSk_FIFO1;     /* 送受信FIFO1 バッファステータスレジスタラッチ用 */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                              u2TxMbUseBitMask;   /* 使用MBOXビットマスク                           */
    uint16                              u2TMTRSTSy;         /* 送信バッファ送信要求ステータスレジスタラッチ用 */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint8                               u1Ret;              /* 戻り値                                         */

#if (CAN_CFG_TRANSMIT == CAN_USE)
    /* 送信機能を使用する場合 */

    /* 通信中状態からチャネル停止要求が呼ばれた場合              */
    /* メッセージ送出中にチャネルリセットモードに遷移させると    */
    /* エラーフレームを誘発するため、まずは送信をキャンセルする。*/

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* チャネルモード確認 */
    ptChReg = &Can_tb_stChReg[ u1Controller ];
    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM )
    {
        /* チャネル通信モードの場合 */

        /* Pending中の送信要求があれば全てキャンセル */
        Can_tx_TxAbtAll( u1Controller );

        /*  送信バッファ送信要求ステータスフラグの確認 */
        ptTxMbBit        = &Can_tb_stTxMbBit[ u1Controller ];
        u2TxMbUseBitMask = ( ptTxMbBit->u2TxIntrBit | ptTxMbBit->u2TxPollBit );
        u2TMTRSTSy       = *( ptChReg->ptu2TMTRSTSy );
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /*  送受信FIFOバッファステータスレジスタの確認 */
        u4CFSTSk_FIFO0 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
        u4CFSTSk_FIFO1 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        if ( ( ( u2TMTRSTSy & u2TxMbUseBitMask ) == CAN_u2BIT_NONE )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
          && ( ( u4CFSTSk_FIFO0 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE )
          && ( ( u4CFSTSk_FIFO1 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
           )
        {
            /* 送信要求中のバッファが無い場合（送信中断完了 or 送信要求なし) */
            /* チャネル通信停止 */
            u1Ret = Can_st_StopChannel( u1Controller );
        }
        else
        {
            /* 現在送出中で、送信中断が全て完了しなかった場合は */
            /* 次回モード遷移定期処理でアボート完了を確認し、   */
            /* 完了後に通信停止処理をする。                     */
            /* ただし、できるだけ上位層へ通知を上げないよう、   */
            /* 受信完了割り込みを禁止する。                     */
            /* 送信要求中は送信完了割り込みを禁止できないため、 */
            /* 不正なPduIdで通知が上がることを注意事項とする。  */

            /* 送受信FIFO(割り込み受信用)、および受信FIFO(ポーリング受信用)の停止、割り込み禁止、要因クリアの実施 */

            /* RSCAN設定値テーブルへのポインタ取得 */
            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

            /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk) */
            /* 送受信FIFOバッファ（受信モード）許可ビットを使用しない、割り込み禁止に設定（受信メッセージクリア、割り込み禁止） */
            /* CFEビットを下げる */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFE_NOUSE;
            /* CFRXIEビットを下げる */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE;

            /* 送受信FIFOバッファステータスレジスタ(CFSTSk)のクリア（割り込み受信要因クリア） */
            ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTSK_CLEARALL;              /* 割り込み受信用     */

            /* 受信 FIFO バッファコンフィグレーション／制御レジスタ(RFCCx) */
            /* 受信FIFOバッファ許可ビットを使用しない、割り込み禁止に設定（メッセージクリア、割り込み禁止）*/
            /* RFEビットを下げる */
            Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFE_NOUSE;
            /* RFIEビット下げる */
            Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFIE_DIS & CAN_u4RFCCX_RFE_NOUSE;

            /* 受信 FIFO バッファステータスレジスタ(RFSTSx)のクリア */
            Can_tb_stGlobalReg.ptu4RFSTSx[ u1Controller ] = CAN_u4RFSTSX_CLEARALL;      /* ポーリング受信用   */
        }
    }
    else
    {
        /* チャネルリセットモード、またはチャネル待機モードの場合 */
        /* チャネル通信停止 */
        u1Ret = Can_st_StopChannel( u1Controller );
    }
#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
    /* 送信機能を使用しない場合 */

    /* チャネル通信停止 */
    u1Ret = Can_st_StopChannel( u1Controller );
#endif /* (CAN_CFG_TRANSMIT) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Reset                                             */
/* Description   | コントローラ再初期化                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ再初期化結果                           */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバルテストモード                                */
/*               |  - グローバル動作モード                                  */
/*               | 以下のチャネルモードから呼ばれる前提とする。             */
/*               |  - チャネルリセットモード                                */
/*               |  - チャネル待機モード                                    */
/*               |  - チャネル通信モード                                    */
/*               |  ※ 本APIの呼び出し条件はCan_st_SetControl成功後である為 */
/*               |     グローバルストップモード/チャネルストップモード      */
/*               |      では呼ばれない。                                    */
/****************************************************************************/
uint8
Can_st_Reset( uint8 u1Controller )
{
    uint8    u1Ctrl;             /* ループ用コントローラID */
    uint8    u1CtrlNum;          /* コントローラ数         */
    uint8    u1Result;           /* 関数戻り値             */
    uint8    u1Ret;              /* 戻り値                 */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* グローバルレジスタ化けチェック */
    u1Result = Can_st_GlobalRegCheck( u1Controller );

    if ( u1Result == (uint8)CAN_PROC_OK )
    {   /* グローバルレジスタ正常の場合 */

        /* チャネル再初期化 */
        u1Ret = Can_st_ResetChannel( u1Controller );
    }
    else
    {   /* グローバルレジスタ異常の場合       */
        /* グローバルレジスタの再設定から実施 */

        /* グローバルレジスタ再初期化の際に全チャネルがチャネルリセットモードになり停止するため、 */
        /* コントローラ状態との矛盾が起きないように他のチャネルをSTOP状態にしておく。             */
        /* また、フェール定期処理にてMPU異常を通知し、再初期化されることを期待する。              */
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Ctrl = (uint8)0U; u1Ctrl < u1CtrlNum; u1Ctrl++ )
        {
            if ( u1Ctrl != u1Controller )
            {
                /* コントローラ停止通知 */
                Can_st_StopInd( u1Ctrl );

                /* MPU異常検出通知 */
                Can_fs_MpuFailInd( u1Ctrl );
            }
        }

        /* グローバルレジスタ再初期化 */
        u1Result = Can_st_ResetGlobal();

        if ( u1Result == (uint8)CAN_PROC_OK )
        {
            /* チャネル再初期化 */
            u1Ret = Can_st_ResetChannel( u1Controller );
        }
        /* グローバルリセットモード遷移失敗時(HW故障)   */
        /* 何もせず、次回モード遷移定期処理で再確認する */
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkStart                                          */
/* Description   | コントローラ通信開始チェック                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ通信開始チェック結果                   */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | ・Can_st_Stop、及び、Can_st_Startが連続で呼びだされたが  */
/*               |   CANメッセージをバスに送出中のため、通信停止・開始が    */
/*               |   完了しきれなかった場合に呼び出される。                 */
/****************************************************************************/
uint8
Can_st_ChkStart( uint8 u1Controller )
{
    uint32    u4GSTS;             /* グローバルステータスレジスタラッチ用 */
    uint8     u1Ret;              /* 戻り値                               */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* 本関数呼び出し時のグローバル状態は以下である                              */
    /* ①初期化／再初期化完了後                       ：グローバルリセットモード */
    /* ②初期化／再初期化完了後、かつ                                            */
    /*   通信停止完了後 or 他チャネルの通信開始完了後 ：グローバル動作モード     */

    /* グローバルモードの確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {   /* グローバルリセットモードの場合 */

        /* グローバルレジスタ開始設定 */
        Can_st_StartGlobal();
    }

    /* グローバルモードの再確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM )
    {   /* グローバル動作モードの場合 */

        /* チャネル通信開始 */
        u1Ret = Can_st_StartChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkStop                                           */
/* Description   | コントローラ通信停止チェック                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ通信停止チェック結果                   */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | ・Can_st_Stop時、CANメッセージをバスに送出中のため       */
/*               |   通信停止処理が完了しなかった場合に呼び出される。       */
/****************************************************************************/
uint8
Can_st_ChkStop( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ   */
    CanConst CanTbTxMbBitType *         ptTxMbBit;          /* 送信MBOX種別ビット情報テーブルへのポインタ     */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                              u4CFSTSk_FIFO0;     /* 送受信FIFO0 バッファステータスレジスタラッチ用 */
    uint32                              u4CFSTSk_FIFO1;     /* 送受信FIFO1 バッファステータスレジスタラッチ用 */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                              u2TxMbUseBitMask;   /* 使用MBOXビットマスク                           */
    uint16                              u2TMTRSTSy;         /* 送信バッファ送信要求ステータスレジスタラッチ用 */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint8                               u1Ret;              /* 戻り値                                         */

#if (CAN_CFG_TRANSMIT == CAN_USE)
    /* 送信機能を使用する場合 */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /*  送信バッファ送信要求ステータスフラグの確認 */
    ptTxMbBit        = &Can_tb_stTxMbBit[ u1Controller ];
    u2TxMbUseBitMask = ( ptTxMbBit->u2TxIntrBit | ptTxMbBit->u2TxPollBit );
    ptChReg          = &Can_tb_stChReg[ u1Controller ];
    u2TMTRSTSy       = *( ptChReg->ptu2TMTRSTSy );
    if ( ( u2TMTRSTSy & u2TxMbUseBitMask ) == CAN_u2BIT_NONE )
    {
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /*  送受信FIFOバッファステータスレジスタの確認 */
        u4CFSTSk_FIFO0 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
        u4CFSTSk_FIFO1 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
        if ( ( ( u4CFSTSk_FIFO0 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE )
          && ( ( u4CFSTSk_FIFO1 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        {
            /* 送信要求中のバッファが無い場合（送信中断完了 or 送信要求なし) */
            /* チャネル通信停止 */
            u1Ret = Can_st_StopChannel( u1Controller );
        }
    }
    /* 現在送出中で、送信中断が全て完了しなかった場合は */
    /* 次回モード遷移定期処理でアボート完了を確認し、   */
    /* 完了後に通信停止処理をする。                     */

#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
    /* 送信機能を使用しない場合 */

    /* HW故障時以外では、通信停止は必ず成功するため     */
    /* 本パスで 呼ばれることはない。                    */
    /* 呼ばれた場合は、初めから通信停止処理をやり直す。 */

    /* チャネル通信停止 */
    u1Ret = Can_st_StopChannel( u1Controller );
#endif /* (CAN_CFG_TRANSMIT) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkReset                                          */
/* Description   | コントローラ再初期化チェック                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラ再初期化チェック結果                   */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバルテストモード                                */
/*               |  - グローバル動作モード                                  */
/*               | 以下のチャネルモードから呼ばれる前提とする。             */
/*               |  - チャネルリセットモード                                */
/*               |  - チャネル待機モード                                    */
/*               |  - チャネル通信モード                                    */
/*               |  ※ 本APIの呼び出し条件はCan_st_SetControl成功後である為 */
/*               |     グローバルストップモード/チャネルストップモード      */
/*               |      では呼ばれない。                                    */
/****************************************************************************/
uint8
Can_st_ChkReset( uint8 u1Controller )
{
    uint8    u1Ctrl;             /* ループ用コントローラID */
    uint8    u1CtrlNum;          /* コントローラ数         */
    uint8    u1Result;           /* 関数戻り値             */
    uint8    u1Ret;              /* 戻り値                 */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* 本関数は、HW異常により Can_st_Reset が失敗したケースでのみ呼び出される。 */
    /* HW異常であり、継続動作にリスクがあるため、                               */
    /* グローバルレジスタを含めた再初期化を試みる。                             */

    /* グローバルレジスタ再初期化の際に全チャネルがチャネルリセットモードになり停止するため、 */
    /* コントローラ状態との矛盾が起きないように他のチャネルをSTOP状態にしておく。             */
    /* また、フェール定期処理にてMPU異常を通知し、再初期化されることを期待する。              */
    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Ctrl = (uint8)0U; u1Ctrl < u1CtrlNum; u1Ctrl++ )
    {
        if ( u1Ctrl != u1Controller )
        {
            /* コントローラ停止通知 */
            Can_st_StopInd( u1Ctrl );

            /* MPU異常検出通知 */
            Can_fs_MpuFailInd( u1Ctrl );
        }
    }

    /* グローバルレジスタ再初期化 */
    u1Result = Can_st_ResetGlobal();

    if ( u1Result == (uint8)CAN_PROC_OK )
    {   /* グローバルレジスタ再初期化成功 */
        /* チャネル再初期化 */
        u1Ret = Can_st_ResetChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ShutdownReg                                       */
/* Description   | シャットダウン時CANレジスタ設定                          */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・任意のグローバルモードから呼び出される前提とする。     */
/*               | ・本関数では、CANの機能を停止するためにグローバル        */
/*               |   ストップモードに遷移させる。そのため、ユーザCANも停止  */
/*               |   する事に留意すること。                                 */
/****************************************************************************/
void
Can_st_ShutdownReg( void )
{
    uint32    u4GSTS;             /* グローバルステータスレジスタラッチ用 */
    uint8     u1Controller;       /* ループ用コントローラID               */
    uint8     u1CtrlNum;          /* コントローラ数                       */

    /* CAN RAM初期化完了確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4BIT_NONE )
    {   /* CAN RAM初期化完了 */

        /* グローバルモード確認 */
        if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_STOP )
        {   /* グローバルストップモード以外の場合 */

            /* グローバルリセットモード設定 */
            Can_st_GlobalMode_Any2Reset();

            /* グローバルモード確認 */
            u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
            if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
            {   /* グローバルリセットモード遷移成功時 */

                /* グローバル停止処理割り込み禁止、及び要因クリア */
                Can_st_StopGlobal();

                u1CtrlNum = Can_tb_u1CtrlNum;
                for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
                {
                    if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
                    {
                        /* チャネル通信停止 */
                        (void)Can_st_StopChannel( u1Controller ); /* MISRA DEVIATION: no return check required */
                    }
                }

                /* グローバルストップモード設定 */
                Can_st_GlobalMode_Reset2Stop();
            }
            /* HW故障がない限り、グローバルストップ／チャネルストップモードへの遷移は完了する。   */
            /* また、本API呼び出し以降は、初期化API以外の呼び出しがなく、                         */
            /* 本ソフトとしての追加処置契機がないため、ストップモード遷移完了の確認はしない。     */
            /* ※ 本API呼出し後にHW停止不可をユーザが検知した場合には、                           */
            /*    再度Canの初期化、シャットダウンを順に呼び出し、リトライしてもらう事を期待する。 */
        }
        /* グローバルストップモード時はレジスタ書き込み禁止のため、何もしない。 */
    }
    /* CAN RAM初期化未完了の場合、CANソフトとしては何も設定していないため、何もしない。 */
}


/****************************************************************************/
/* Function Name | Can_st_SetConfigMbox                                     */
/* Description   | MBOXコンフィグ設定                                       */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_st_SetConfigMbox( uint8 u1Controller )
{
    uint32    u4GSTS;             /* グローバルステータスレジスタラッチ用                              */
    uint32    u4GAFLCFG0Conf;     /* 受信ルールコンフィグレーションレジスタ0：コンフィグ値設定ラッチ用 */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    uint32    u4GAFLCFG1Conf;     /* 受信ルールコンフィグレーションレジスタ1：コンフィグ値設定ラッチ用 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */

    /* 当該マイコンにおけるMBOX設定(受信ルール関連レジスタ設定)は             */
    /* グローバルリセットモード（＝マイコン全体の初期化中）にのみ可能である。 */
    /* 一方、本関数はコントローラ個別で呼び出される事が前提である。           */

    /* その為、MBOXコンフィグ設定がされていない状態で本関数が呼ばれた時にのみ */
    /* 全コントローラ分の設定を一括実施する設計とする。                       */

    /* 処理の実施条件                                                         */
    /* - グローバルリセットモードであること                                   */
    /* - 受信ルール関連レジスタが未設定であること                             */
    /*   ※代表でGAFLCFGにコンフィグ設定値が格納されているかにより判別する。  */
    /*     コンフィグ設定値が初期値と同じ値(0)の場合は一度も                  */
    /*     Can_st_SetRxRuleを呼び出さなくなるが、GAFLCFGが0ということは       */
    /*     受信ルール未使用であり呼び出す必要がないため、問題ない。           */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    u4GAFLCFG0Conf = Can_tb_u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    u4GAFLCFG1Conf = Can_tb_u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
    if ( ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK )           == CAN_u4GSTS_GMODE_RESET )
    &&   ( ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] != u4GAFLCFG0Conf         )
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
        || ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] != u4GAFLCFG1Conf         )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
    ) )
    {
        /* 受信ルール関連レジスタ設定 */
        Can_st_SetRxRule();
    }
}


/****************************************************************************/
/* Function Name | Can_st_SetBaudrate                                       */
/* Description   | ボーレートレジスタ設定                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8  u1Controller       : CANコントローラ番号          */
/*               | uint16 u2BaudRateConfigID : ボーレートコンフィグID       */
/* Return Value  | uint8  ボーレート設定結果                                */
/*               |   CAN_PROC_OK   : 設定完了                               */
/*               |   CAN_PROC_BUSY : 設定未完了                             */
/* Notes         | チャネルリセットモードから呼ばれる前提とする。           */
/****************************************************************************/
uint8
Can_st_SetBaudrate( uint8 u1Controller, uint16 u2BaudRateConfigID )
{
    CanConst CanTbChRegType *          ptChReg;          /* チャネルレジスタアドレステーブルへのポインタ        */
    CanConst CanBaudrateSwtCfgType *   ptBaudrateSwtCfg; /* RSCANボーレートコンフィグ設定値テーブルへのポインタ */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanConst CanTbSetRSCANRegType *    ptSetRSCANReg;    /* RSCANレジスタ設定値テーブルへのポインタ             */
    uint32                             u4BRSUse;         /* ビットレートスイッチ使用/未使用設定値               */
    uint32                             u4TDCO;           /* TDCO設定値                                          */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                              u1BRSwtCfgTbl_ARYSIZE;/* ボーレート切り替えコンフィグ情報テーブル要素数  */
    uint8                              u1Ret;            /* 戻り値                                              */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* 引数ボーレートコンフィグIDのダイナミクスチェック */
    u1BRSwtCfgTbl_ARYSIZE = *(Can_tb_ptBRSwtCfgTbl_ARYSIZE);
    if ( u2BaudRateConfigID < u1BRSwtCfgTbl_ARYSIZE )
    {
        ptChReg = &Can_tb_stChReg[ u1Controller ];

        ptBaudrateSwtCfg = &(Can_tb_ptBaudrateSwtCfgTbl[ u2BaudRateConfigID ]);

        /* ボーレート設定 */
        /* クラシカルCANモード：チャネルコンフィグレーションレジスタ(CmCFG)                  */
        /* CAN FDモード       ：チャネル通常ビットレートコンフィグレーションレジスタ(CmNCFG) */
        *(ptChReg->ptu4CmCFG) = ptBaudrateSwtCfg->u4Baudrate;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)

        /* データフェーズボーレート設定 */
        /* チャネルデータビットレートコンフィグレーションレジスタ(CmDCFG) */
        *(ptChReg->ptu4CmDCFG) = ptBaudrateSwtCfg->u4DataBaudrate;

        /* チャネルCAN FDコンフィグレーションレジスタ(CmFDCFG) */
        ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];
        /* 本マイコンではビットレートスイッチ使用/未使用をu4BaudrateInfo_2に格納している */
        u4BRSUse = ptBaudrateSwtCfg->u4BaudrateInfo_2;
        if ( u4BRSUse == (uint32)CAN_USE )
        {   /* ビットレートスイッチ使用の場合 */
            /* 送信遅延補正許可               */
            /* 本マイコンでは送信遅延補正のSSPオフセット設定値をu4BaudrateInfo_1に格納している */
            u4TDCO = ptBaudrateSwtCfg->u4BaudrateInfo_1;
            *(ptChReg->ptu4CmFDCFG) = ( (ptSetRSCANReg->u4CmFDCFGConf & ~CAN_u4CMFDCFG_TDCO_MSK) | (u4TDCO & CAN_u4CMFDCFG_TDCO_MSK) ) | CAN_u4CMFDCFG_TDCE_SET;

            /* BRS設定値保持 */
            Can_st_u1BRSUse[ u1Controller ] = (uint8)CAN_ST_BRS_USE;
        }
        else
        {   /* ビットレートスイッチ未使用の場合 */
            /* 送信遅延補正禁止                 */
            /* 送信遅延補正のSSPオフセット設定値は使用しないためリセット値(0)とする */
            u4TDCO = CAN_u4BIT_NONE;
            *(ptChReg->ptu4CmFDCFG) = ( (ptSetRSCANReg->u4CmFDCFGConf & ~CAN_u4CMFDCFG_TDCO_MSK) | (u4TDCO & CAN_u4CMFDCFG_TDCO_MSK) ) & CAN_u4CMFDCFG_TDCE_CLR;

            /* BRS設定値保持 */
            Can_st_u1BRSUse[ u1Controller ] = (uint8)CAN_ST_BRS_NOUSE;
        }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Test                             */
/* Description   | グローバルモード切替(リセットモード to テストモード)     */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_st_GlobalMode_Reset2Test( void )
{
    volatile uint32     u4GSTS;             /* グローバルステータスレジスタ(条件成立まで複数回リード) */
    uint16              u2WaitCount;        /* ループカウンタ                                         */

    /* 初期値設定 */
    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    /* グローバルテストモード設定 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_TEST_SET;

    /* グローバルテストモード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2TST_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_TEST ); u2WaitCount++ )
    {
        /* グローバルステータスレジスタの取得 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Any2Reset                              */
/* Description   | グローバルモード切替(任意のモード to リセットモード)     */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・任意のグローバルモードからグローバルリセットモードに   */
/*               |   遷移させる。                                           */
/*               |   そのため、本関数内のモード遷移要求後～遷移完了迄の間に */
/*               |   割り込み処理が干渉する可能性がある。                   */
/*               |   割り込み処理側のモード判定処理をシンプルとするため、   */
/*               |   モード遷移要求～確定間は割り込み禁止とする。           */
/*               |                                                          */
/*               | ・グローバルリセットモード遷移の最大遷移時間は           */
/*               |   2CANビット時間(※ 125kbps時、16us)となり、この時間が   */
/*               |   割り込み禁止時間の最大時間となる。                     */
/*               |   ユーザボーレートにて低速なボーレートを使用する場合には */
/*               |   最大プロセッサ割り込み禁止時間(20us)に注意すること。   */
/****************************************************************************/
void
Can_st_GlobalMode_Any2Reset( void )
{
    volatile uint32     u4GSTS;             /* グローバルステータスレジスタ(条件成立まで複数回リード) */
    uint16              u2WaitCount;        /* ループカウンタ                                         */
    uint16              u2ClockCount;       /* モード遷移時間                                         */

    /* 初期値設定 */
    /* ※ 任意のモードからのグローバルリセットモード遷移を想定する    */
    /*    → リセットモード以外の値とするため、反転値で初期化しておく */
    u4GSTS = ~CAN_u4GSTS_GMODE_RESET;

    /* ウェイトカウンタ値取得 */
    u2ClockCount = Can_tb_u2GmodeAny2RstWaitCnt;

    /* ▼▼▼▼▼▼  割り込み禁止  ▼▼▼▼▼▼ */
    Can_DI()

    /* グローバルリセットモード遷移要求 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_RESET_SET;

    /* グローバルリセットモード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_RESET ); u2WaitCount++ )
    {
        /* グローバルステータスレジスタの取得 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }

    Can_EI()
    /* ▲▲▲▲▲▲  割り込み許可  ▲▲▲▲▲▲ */
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Stop                             */
/* Description   | グローバルモード切替(リセットモード to ストップモード)   */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
static void
Can_st_GlobalMode_Reset2Stop( void )
{
    volatile uint32     u4GSTS;             /* グローバルステータスレジスタ(条件成立まで複数回リード) */
    uint16              u2WaitCount;        /* ループカウンタ                                         */

    /* 初期値設定 */
    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    /* グローバルストップモード設定 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GSLPR_STOP_SET | CAN_u4GCTR_GMDC_RESET_SET;

    /* グローバルストップモード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2STP_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != ( CAN_u4GSTS_GMODE_STOP | CAN_u4GSTS_GMODE_RESET ) ); u2WaitCount++ )
    {
        /* グローバルステータスレジスタの取得 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Comm                             */
/* Description   | グローバルモード切替(リセットモード to 動作モード)       */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
static void
Can_st_GlobalMode_Reset2Comm( void )
{
    volatile uint32     u4GSTS;             /* グローバルステータスレジスタ(条件成立まで複数回リード) */
    uint16              u2WaitCount;        /* ループカウンタ                                         */

    /* 初期値設定 */
    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    /* グローバル動作モード設定 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_COMM_SET;

    /* グローバル動作モード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2COM_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_COMM ); u2WaitCount++ )
    {
        /* グローバルステータスレジスタの取得 */
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Any2Reset                             */
/* Description   | チャネルモード切替(任意のモード to リセットモード)       */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・任意のチャネルモードからチャネルリセットモードに       */
/*               |   遷移させる。                                           */
/*               |   そのため、本関数内のモード遷移要求後～遷移完了迄の間に */
/*               |   割り込み処理が干渉する可能性がある。                   */
/*               |   割り込み処理側のモード判定処理をシンプルとするため、   */
/*               |   モード遷移要求～確定間は割り込み禁止とする。           */
/*               |                                                          */
/*               | ・チャネルリセットモード遷移の最大遷移時間は             */
/*               |   2CANビット時間(※ 125kbps時、16us)となり、この時間が   */
/*               |   割り込み禁止時間の最大時間となる。                     */
/*               |   ユーザボーレートにて低速なボーレートを使用する場合には */
/*               |   最大プロセッサ割り込み禁止時間(20us)に注意すること。   */
/****************************************************************************/
static void
Can_st_ChannelMode_Any2Reset( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ         */
    volatile uint32                     u4CmSTS;            /* チャネルステータスレジスタ(条件成立まで複数回リード) */
    uint16                              u2WaitCount;        /* ループカウンタ                                       */
    uint16                              u2ClockCount;       /* モード遷移時間                                       */

    /* 初期値設定 */
    /* ※ 任意のモードからのチャネルリセットモード遷移を想定する      */
    /*    → リセットモード以外の値とするため、反転値で初期化しておく */
    u4CmSTS = ~CAN_u4CMSTS_CMODE_RESET;

    /* チャネル単位レジスタテーブルの取得 */
    ptChReg = &Can_tb_stChReg[ u1Controller ];

    /* ウェイトカウンタ値取得 */
    u2ClockCount = Can_tb_u2CmodeAny2RstWaitCnt;

    /* ▼▼▼▼▼▼  割り込み禁止  ▼▼▼▼▼▼ */
    Can_DI()

    /* チャネルリセットモード遷移要求 */
    *(ptChReg->ptu4CmCTR) = ( *(ptChReg->ptu4CmCTR) & ~CAN_u4CMCTR_MODEALL_MSK ) | CAN_u4CMCTR_CHMDC_RESET_SET;

    /* チャネルリセットモード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != CAN_u4CMSTS_CMODE_RESET ); u2WaitCount++ )
    {
        /* チャネルステータスレジスタの取得 */
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }

    Can_EI()
    /* ▲▲▲▲▲▲  割り込み許可  ▲▲▲▲▲▲ */
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Reset2Stop                            */
/* Description   | チャネルモード切替(リセットモード to ストップモード)     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
static void
Can_st_ChannelMode_Reset2Stop( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ         */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ              */
    volatile uint32                     u4CmSTS;            /* チャネルステータスレジスタ(条件成立まで複数回リード) */
    uint16                              u2WaitCount;        /* ループカウンタ                                       */

    /* 初期値設定 */
    u4CmSTS = CAN_u4CMSTS_CMODE_RESET;

    /* チャネル単位レジスタテーブルの取得 */
    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* チャネルストップモード設定 */
    *(ptChReg->ptu4CmCTR) = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CSLPR_STOP_SET | CAN_u4CMCTR_CHMDC_RESET_SET;

    /* チャネルストップモード遷移完了待ち */
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_CMODE_RST2STP_CYCLE ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != ( CAN_u4CMSTS_CMODE_STOP | CAN_u4CMSTS_CMODE_RESET ) ); u2WaitCount++ )
    {
        /* チャネルステータスレジスタの取得 */
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Reset2Comm                            */
/* Description   | チャネルモード切替(リセットモード to 通信モード)         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
static void
Can_st_ChannelMode_Reset2Comm( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ         */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ              */
    volatile uint32                     u4CmSTS;            /* チャネルステータスレジスタ(条件成立まで複数回リード) */
    uint16                              u2ClockCount;       /* モード遷移時間                                       */
    uint16                              u2WaitCount;        /* ループカウンタ                                       */

    /* 初期値設定 */
    u4CmSTS = CAN_u4CMSTS_CMODE_RESET;

    /* チャネル単位レジスタテーブルの取得 */
    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* チャネル通信モード設定 */
    *(ptChReg->ptu4CmCTR) = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_COMM_SET;

    /* チャネル通信モード遷移完了待ち */
    u2ClockCount = Can_tb_u2CmodeRst2ComWaitCnt;
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != CAN_u4CMSTS_CMODE_COMM ); u2WaitCount++ )
    {
        /* チャネルステータスレジスタの取得 */
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalRegCheck                                    */
/* Description   | グローバルレジスタ化けチェック                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 グローバルレジスタの化けチェック結果               */
/*               |   CAN_PROC_OK : レジスタ正常                             */
/*               |   CAN_PROC_NG : レジスタ異常                             */
/* Notes         | なし                                                     */
/****************************************************************************/
static uint8
Can_st_GlobalRegCheck( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbCtrlInfoType *        ptCtrlCfg;          /* コントローラ管理情報テーブルへのポインタ     */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ      */
    uint32                              u4Page;             /* 受信ルールテーブルページ番号                 */
    uint32                              u4FlMask;           /* 受信フィルタマスク値                         */
    uint32                              u4GCFGConf;         /* グローバルコンフィグレーションレジスタ(GCFG)設定値ラッチ用      */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                              u4GFDCFGConf;       /* グローバルFDコンフィグレーションレジスタ(GFDCFG)設定値ラッチ用  */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint32                              u4GAFLCFG0Conf;     /* 受信ルールコンフィグレーションレジスタ0(GAFLCFG0)設定値ラッチ用 */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    uint32                              u4GAFLCFG1Conf;     /* 受信ルールコンフィグレーションレジスタ1(GAFLCFG1)設定値ラッチ用 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
    uint16                              u2RxRuleNo;         /* 受信ルール番号                               */
    uint16                              u2RxRuleNum;        /* 受信ルール数                                 */
    uint8                               u1Ctrl;             /* コントローラ番号                             */
    uint8                               u1CtrlNum;          /* コントローラ数                               */
    uint8                               u1RuleRegNo;        /* 格納先レジスタ番号                           */
    uint8                               u1MskIdx;           /* 受信マスク値テーブルインデックス             */
    uint8                               u1RxFifo;           /* 受信FIFOバッファ数                           */
    uint8                               u1Ret;              /* 戻り値                                       */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_OK;

    /* チャネル単位レジスタテーブルへのポインタ取得 */
    ptChReg = &Can_tb_stChReg[ u1Controller ];
    /* RSCAN設定値テーブルへのポインタ取得 */
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* グローバルレジスタ化けチェック                                 */
    /* - グローバルインタフェースモード選択レジスタ(GRMCFG)           */
    /* - グローバルコンフィグレーションレジスタ(GCFG)                 */
    /* - グローバル制御レジスタ(GCTR)                                 */
    /* - 受信バッファナンバレジスタ(RMNB)                             */
    /* - 受信ルールエントリ制御レジスタ(GAFLECTR)                     */
    /* - 送受信FIFO バッファコンフィグレーション／制御レジスタ(CFCCk) */
    /*   → チャネル再初期化時に再設定されるビットはチェックしない    */
    /* - グローバルテストコンフィグレーションレジスタ(GTSTCFG)        */
    /* - グローバルテスト制御レジスタ(GTSTCTR)                        */
    /* - グローバルFD コンフィグレーションレジスタ(GFDCFG)            */
    /* - グローバルCRC コンフィグレーションレジスタ(GCRCCFG)          */
    /* - DMA 許可レジスタ(CDTCT)                                      */
    u4GCFGConf = Can_tb_u4GCFGConf;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    u4GFDCFGConf = Can_tb_u4GFDCFGConf;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    if ( ( ( *( Can_tb_stGlobalReg.ptu4GRMCFG )   & CAN_u4GRMCFG_USEDBIT_MSK )   != CAN_u4GRMCFG_INIT         )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GCFG )     & CAN_u4GCFG_USEDBIT_MSK )     != ( u4GCFGConf & CAN_u4GCFG_USEDBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GCTR )     & CAN_u4GCTR_USEDBIT_MSK )     != ( CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_COMM_SET ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4RMNB )     & CAN_u4RMNB_USEDBIT_MSK )     != CAN_u4RMNB_CLEARALL       )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GAFLECTR ) & CAN_u4GAFLECTR_USEDBIT_MSK ) != CAN_u4GAFLECTR_AFLDAE_DIS )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] & CAN_u4CFCCK_GCHKBIT_MSK )    != ( ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_GCHKBIT_MSK ) )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] & CAN_u4CFCCK_GCHKBIT_MSK )    != ( ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_GCHKBIT_MSK ) )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] & CAN_u4CFCCK_GCHKBIT_MSK )    != ( ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_GCHKBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GTSTCFG )  & CAN_u4GTSTCFG_USEDBIT_MSK )  != CAN_u4GTSTCFG_ICBCE_DIS   )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GTSTCTR )  & CAN_u4GTSTCTR_USEDBIT_MSK )  != ( CAN_u4GTSTCTR_RTME_DIS | CAN_u4GTSTCTR_ICBCTME_DIS ) )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GFDCFG )   & CAN_u4GFDCFG_USEDBIT_MSK )   != ( u4GFDCFGConf & CAN_u4GFDCFG_USEDBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GCRCCFG )  & CAN_u4GCRCCFG_USEDBIT_MSK )  != CAN_u4GCRCCFG_INIT        )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4CDTCT )    & CAN_u4CDTCT_USEDBIT_MSK )    != CAN_u4CDTCT_INIT          )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    )
    {
        u1Ret = (uint8)CAN_PROC_NG;
    }

    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        /* 受信FIFOバッファ関連レジスタ化けチェック */
        /* 搭載コントローラの受信FIFOバッファの確認 */
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Ctrl = (uint8)0U; ( u1Ctrl < u1CtrlNum ) && ( u1Ret == (uint8)CAN_PROC_OK ); u1Ctrl++ )
        {
            /* RSCAN設定値テーブルへのポインタ取得 */
            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Ctrl ];
            /* 受信FIFOバッファコンフィグレーション/制御レジスタ化けチェック */
            if ( ( Can_tb_stGlobalReg.ptu4RFCCx[ u1Ctrl ] & CAN_u4RFCCX_GCHKBIT_MSK ) != ( ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_GCHKBIT_MSK ) )
            {
                u1Ret = (uint8)CAN_PROC_NG;
            }
        }

        /* 未使用の受信FIFOバッファの確認 */
        for ( u1RxFifo = u1CtrlNum; ( u1RxFifo < (uint8)CAN_NUM_FIFO_RCV ) && ( u1Ret == (uint8)CAN_PROC_OK ); u1RxFifo++ )
        {
            /* 受信FIFOバッファコンフィグレーション/制御レジスタ化けチェック */
            if ( Can_tb_stGlobalReg.ptu4RFCCx[ u1RxFifo ] != CAN_u4RFCCX_INIT )
            {
                u1Ret = (uint8)CAN_PROC_NG;
            }
        }
    }

    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        /* 受信ルール関連レジスタ化けチェック */

        /* 受信ルールコンフィグレーションレジスタ0化けチェック */
        u4GAFLCFG0Conf = Can_tb_u4GAFLCFG0Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] != u4GAFLCFG0Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }

#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
        /* 受信ルールコンフィグレーションレジスタ1化けチェック */
        u4GAFLCFG1Conf = Can_tb_u4GAFLCFG1Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] != u4GAFLCFG1Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */

        /* 受信ルール数取得 */
        ptCtrlCfg   = &Can_tb_stCtrlInfo[ u1Controller ];
        u2RxRuleNum = ptCtrlCfg->u2RxRuleOffSetId + (uint16)(ptCtrlCfg->u1RxRuleUseNum);

        for ( u2RxRuleNo = (uint16)ptCtrlCfg->u2RxRuleOffSetId; ( u2RxRuleNo < u2RxRuleNum ) && ( u1Ret == (uint8)CAN_PROC_OK ); u2RxRuleNo++ )
        {
            /* 受信ルールテーブルページ番号取得 */
            u4Page = ( (uint32)u2RxRuleNo >> CAN_NUM_RULETABLE_PER_PAGE_SFT ) & CAN_u4GAFLECTR_AFLPN_MSK;

            /* 受信ルール書き込み先レジスタインデックス取得 */
            u1RuleRegNo = (uint8)( u2RxRuleNo & (uint16)CAN_NUM_RULETABLE_PER_PAGE_MSK );

            /* チェック対象ページ設定 */
            *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ( CAN_u4GAFLECTR_AFLDAE_DIS | u4Page );

            /* 受信ルール関連レジスタ化けチェック */
            u1MskIdx = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u1RxMaskRef;
            u4FlMask = Can_tb_u4RxMask[ u1MskIdx ];
            if ( ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLIDj != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLIDjConf )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLMj  != u4FlMask                                           )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0j != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP0jConf )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1j != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP1jConf ) )
            {
                u1Ret = (uint8)CAN_PROC_NG;
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_InitGlobalReg                                     */
/* Description   | グローバルレジスタ初期化                                 */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | グローバルリセットモードでコールすること                 */
/****************************************************************************/
static void
Can_st_InitGlobalReg( void )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    volatile uint32                     u4DummyRead;        /* レジスタのダミーリード用                     */
    uint8                               u1Controller;       /* ループ用コントローラID                       */
    uint8                               u1RxRulePageNum;    /* 受信ルールページ数                           */
    uint8                               u1CtrlNum;          /* コントローラ数                               */
    uint8                               u1PageCnt;          /* 受信ルールテーブルページ数                   */
    uint8                               u1RxFifo;           /* 受信FIFOバッファ数                           */
    uint8                               u1RuleRegNo;        /* 格納先レジスタ番号                           */

    /*----------------------------------*/
    /* インタフェースモード関連レジスタ */
    /*----------------------------------*/
    /* グローバルインタフェースモード選択レジスタ(GRMCFG)                             */
    /* グローバルインタフェースモード選択レジスタは、マイコン制約に従い最初に設定する */
    *(Can_tb_stGlobalReg.ptu4GRMCFG)    = CAN_u4GRMCFG_INIT;

    /* グローバルインタフェースモード選択レジスタへの書き込み反映待ち */
    /* ※ 反映待ちの要否はRH850の中でもマイコン毎に異なるが、         */
    /*    コードを共通化するため実施しておく。                        */
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);

    /*------------------------*/
    /* グローバル関連レジスタ */
    /*------------------------*/
    /* グローバル制御レジスタ(GCTR) */
    /* モード関連のビットに対しては同値書き込みのため、待ち時間不要 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_RESET_SET;

    /* グローバルFD コンフィグレーションレジスタ(GFDCFG) */
    *(Can_tb_stGlobalReg.ptu4GFDCFG) = CAN_u4GFDCFG_INIT;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* グローバルCRC コンフィグレーションレジスタ(GCRCCFG) */
    *(Can_tb_stGlobalReg.ptu4GCRCCFG) = CAN_u4GCRCCFG_INIT;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* グローバルコンフィグレーションレジスタ(GCFG) */
    /* → 受信ルールポインタ0レジスタと関連するため、受信ルール関連レジスタの設定後に初期化 */

    /* グローバルエラーフラグレジスタ(GERFL) */
    /* → グローバルリセットモード遷移時に初期化済み */

    /* グローバルステータスレジスタ(GSTS)                  */
    /* グローバルタイムスタンプカウンタレジスタ(GTSC)      */
    /* グローバルTX 割り込みステータスレジスタ0(GTINTSTS0) */
    /* → リードオンリーのため初期化対象なし */

    /*------------------------*/
    /* 受信ルール関連レジスタ */
    /*------------------------*/
    /* 受信ルールコンフィグレーションレジスタ0(GAFLCFG0) */
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] = CAN_u4GAFLCFG0_INIT;

#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* 受信ルールコンフィグレーションレジスタ1(GAFLCFG1) */
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] = CAN_u4GAFLCFG1_INIT;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */

    u1RxRulePageNum = Can_tb_u1RxRulePageNum;
    for ( u1PageCnt = (uint8)0U; u1PageCnt < u1RxRulePageNum; u1PageCnt++ )
    {
        /* 受信ルールエントリ制御レジスタ(GAFLECTR)               */
        /* 受信ルールテーブル書き込み許可且つ、書き込みページ設定 */
        *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ((uint32)u1PageCnt | CAN_u4GAFLECTR_AFLDAE_ENA);

        for ( u1RuleRegNo = (uint8)0U; u1RuleRegNo < (uint8)CAN_NUM_RULETABLE_PER_PAGE; u1RuleRegNo++ )
        {
            /* 受信ルールID レジスタj(GAFLIDj)        */
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLIDj = CAN_u4GAFLIDJ_INIT;
            /* 受信ルールマスクレジスタj(GAFLMj)      */
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLMj  = CAN_u4GAFLMJ_INIT;
            /* 受信ルールポインタ0 レジスタj(GAFLP0j) */
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0j = CAN_u4GAFLP0J_INIT;
            /* 受信ルールポインタ1 レジスタj(GAFLP1j) */
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1j = CAN_u4GAFLP1J_INIT;
        }
    }
    /* 受信ルールエントリ制御レジスタ(GAFLECTR) 設定後処理 */
    /* 受信ルールテーブル書き込み禁止設定且つ、書き込みページクリア */
    *(Can_tb_stGlobalReg.ptu4GAFLECTR) = CAN_u4GAFLECTR_AFLDAE_DIS;

    /*------------------------*/
    /* グローバル関連レジスタ */
    /*------------------------*/
    /* グローバルコンフィグレーションレジスタ(GCFG) */
    *(Can_tb_stGlobalReg.ptu4GCFG)     = CAN_u4GCFG_INIT;

    /*--------------------------*/
    /* 受信バッファ関連レジスタ */
    /*--------------------------*/
    /* 受信バッファナンバレジスタ(RMNB)      */
    *(Can_tb_stGlobalReg.ptu4RMNB)     = CAN_u4RMNB_INIT;

    /* 受信バッファ新データレジスタ y(RMNDy) */
    /* → グローバルリセットモード遷移時に初期化済み */

    /* 受信バッファIDレジスタ(RMIDq)                                   */
    /* 受信バッファポインタレジスタ(RMPTRq)                            */
    /* 受信バッファCAN FDステータスレジスタ(RMFDSTS)(CAN-FDモードのみ) */
    /* 受信バッファデータフィールドbレジスタ(RMDFb_q)                  */
    /* → リードオンリーのため初期化対象なし */

    /*------------------------------*/
    /* 受信FIFOバッファ関連レジスタ */
    /*------------------------------*/
    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        /* 受信FIFO バッファコンフィグレーション／制御レジスタ(RFCCx) */
        Can_tb_stGlobalReg.ptu4RFCCx[ u1RxFifo ]   = CAN_u4RFCCX_INIT;

        /* 受信FIFO バッファステータスレジスタ(RFSTSx)  */
        /* → グローバルリセットモード遷移時に初期化済み */

        /* 受信FIFO バッファポインタ制御レジスタ(RFPCTRx) */
        /* → ポインタ制御レジスタに関しては、安全値の概念が無いため対象外とする */

        /* 受信 FIFO バッファアクセスIDレジスタ(RFIDx)                            */
        /* 受信 FIFO バッファアクセスポインタレジスタ(RFPTRx)                     */
        /* 受信 FIFO バッファCAN FDステータスレジスタ(RFFDSTSx)(CAN-FDモードのみ) */
        /* 受信 FIFO バッファアクセスデータフィールドdレジスタ(RFDFd_x)           */
        /* → リードオンリーのため初期化対象なし */
    }

    /*--------------------------------*/
    /* 送受信FIFOバッファ関連レジスタ */
    /*--------------------------------*/
    /* ※ 本レジスタはチャネル毎に割り当てて使用するが、リソース自体はグローバル要素に属するため */
    /*    設定可能なタイミングがグローバルモードに依存している。                                 */
    /*    そのため、本関数(グローバルレジスタ設定)にて設定する。                                 */
    /* ※ ただし安全上例外として、割り込みマスクと割り込み要因の設定については、                 */
    /*    グローバルモードを考慮した上で、チャネルの関数でも設定する。                           */
    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        /* 関連チャネルが制御対象CANのもののみを対象とする */
        if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
        {
            ptChReg = &Can_tb_stChReg[ u1Controller ];

            /* 送受信FIFO バッファコンフィグレーション／制御レジスタk(CFCCk) */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = CAN_u4CFCCK_INIT;
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = CAN_u4CFCCK_INIT;
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = CAN_u4CFCCK_INIT;

            /* 送受信FIFO バッファステータスレジスタk(CFSTSk) */
            /*   →：受信モードの場合、グローバルリセットモード遷移時初期化済み */
            /*       送信モードの場合、チャネルリセットモード遷移時に初期化済み */

            /* 送受信FIFO バッファポインタ制御レジスタk(CFPCTRk) */
            /* → ポインタ制御レジスタに関しては、安全値の概念が無いため対象外とする */

            /* 送受信FIFO バッファアクセスID レジスタk(CFIDk)                                                 */
            /* 送受信FIFO バッファアクセスポインタレジスタk(CFPTRk)                                           */
            /* 送受信FIFO バッファCAN FDコンフィグレーション／ステータスレジスタ(CFFDCSTSk)(CAN-FDモードのみ) */
            /* 送受信FIFO バッファアクセスデータフィールドdレジスタk(CFDFd_k)                                 */
            /* → 本設計としては、送受信FIFOバッファは未使用、送信モードまたは受信モードとする。              */
            /*    レジスタのリセット初期値は受信モード。受信モードでは書き込み禁止。                          */
        }
    }

    /*-----------------------------*/
    /* FIFO ステータス関連レジスタ */
    /*-----------------------------*/
    /* FIFO エンプティステータスレジスタ(FESTS)                          */
    /* FIFO フルステータスレジスタ(FFSTS)                                */
    /* FIFO メッセージロストステータスレジスタ(FMSTS)                    */
    /* 受信FIFO バッファ割り込みフラグステータスレジスタ(RFISTS)         */
    /* 送受信FIFO バッファ 受信割り込みフラグステータスレジスタ(CFRISTS) */
    /* 送受信FIFO バッファ 送信割り込みフラグステータスレジスタ(CFTISTS) */
    /* → リードオンリーのため初期化対象なし */

    /*----------------------*/
    /* FIFO DMA関連レジスタ */
    /*----------------------*/
    /* DMA 許可レジスタ(CDTCT)                     */
    /* → グローバルリセットモード遷移時初期化済み */
    /* DMA ステータスレジスタ(CDTSTS)              */
    /* → リードオンリーのため初期化対象なし       */

    /*--------------------*/
    /* テスト関連レジスタ */
    /*--------------------*/
    /* グローバルテストコンフィグレーションレジスタ(GTSTCFG)               */
    /* グローバルテスト制御レジスタ(GTSTCTR)                               */
    /* グローバルロックキーレジスタ(GLOCKK)                                */
    /* RAM テストページアクセスレジスタ(RPGACCr)                           */
    /* → テスト用途でのみ使用するレジスタであり、                         */
    /*    グローバルテストモードのときのみ書き換え可能なため、対象外とする */

    /*----------------------*/
    /* モードリードレジスタ */
    /*----------------------*/
    /* CAN-FD モードリードレジスタ(CANFDMDR) */
    /* → リードオンリーのため初期化対象なし */

}


/****************************************************************************/
/* Function Name | Can_st_InitChannelReg                                    */
/* Description   | チャネルレジスタ初期化                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | 以下のモードから呼ばれる前提とする。                     */
/*               |  - チャネルリセットモード                                */
/****************************************************************************/
static void
Can_st_InitChannelReg( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    uint8                               u1MBox;             /* MBOX数                                       */
    uint8                               u1Data;             /* MB.DATA数                                    */

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    /*----------------------*/
    /* チャネル関連レジスタ */
    /*----------------------*/
    /* クラシカルCANモード：チャネルコンフィグレーションレジスタ(CmCFG)                  */
    /* CAN FDモード       ：チャネル通常ビットレートコンフィグレーションレジスタ(CmNCFG) */
    *(ptChReg->ptu4CmCFG) = CAN_u4CMCFG_INIT;

    /* チャネル制御レジスタ(CmCTR)                                  */
    /* モード関連のビットに対しては同値書き込みのため、待ち時間不要 */
    *(ptChReg->ptu4CmCTR) = CAN_u4CMCTR_INIT;

    /* チャネルステータスレジスタ(CmSTS)           */
    /* チャネルエラーフラグレジスタ(CmERFL)        */
    /* → チャネルリセットモード遷移時に初期化済み */

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* チャネルデータビットレートコンフィグレーションレジスタ(CmDCFG) */
    *(ptChReg->ptu4CmDCFG) = CAN_u4CMDCFG_INIT;

    /* チャネルCAN FDコンフィグレーションレジスタ(CmFDCFG) */
    *(ptChReg->ptu4CmFDCFG) = CAN_u4CMFDCFG_INIT;

    /* チャネルCAN FD制御レジスタ(CmFDCTR)                                                          */
    /* →本レジスタに書き込むことでクリアされるチャネルCAN FDステータスレジスタ(CmFDSTS)のビットは  */
    /*   チャネルリセットモード遷移時にクリアされており、                                           */
    /*   本レジスタに関しては、安全値の概念が無いため対象外とする                                   */

    /* チャネルCAN FDステータスレジスタ(CmFDSTS)   */
    /* → チャネルリセットモード遷移時に初期化済み */

    /* チャネルCAN FD CRCレジスタ(CmFDCRC)   */
    /* → リードオンリーのため初期化対象なし */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /*--------------------------*/
    /* 送信バッファ関連レジスタ */
    /*--------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* マージモード送信バッファ関連レジスタ */
    for ( u1MBox = (uint8)0U; u1MBox < (uint8)CAN_NUM_MERGE_BUF_SND_PER_CH; u1MBox++ )
    {
        /* 送信バッファ制御レジスタ(TMCp)              */
        /* 送信バッファステータスレジスタ(TMSTSp)      */
        /* → チャネルリセットモード遷移時に初期化済み */

        /* 送信バッファIDレジスタ(TMIDp) */
        ptChReg->ptstTM_MERGE[ u1MBox ].u4IDReg = CAN_u4TMIDP_INIT;

        /* 送信バッファポインタレジスタ(TMPTRp) */
        ptChReg->ptstTM_MERGE[ u1MBox ].u4PTRReg = CAN_u4TMPTRP_CLEARALL;

        /* 送信バッファCAN FDコンフィグレーションレジスタ(TMFDCTRp) */
        ptChReg->ptstTM_MERGE[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTRP_CLEARALL;

        for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_TB_TX_MB_DATA_MERGEARYSIZE; u1Data++ )
        {
            /* 送信バッファデータフィールドbレジスタ(TMDFb_p) */
            ptChReg->ptstTM_MERGE[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDFBP_CLEARALL;
        }
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    for ( u1MBox = (uint8)CAN_ST_BUF_SND_TOP; u1MBox < (uint8)CAN_NUM_BUF_SND_PER_CH; u1MBox++ )
    {
        /* 送信バッファ制御レジスタ(TMCp)              */
        /* 送信バッファステータスレジスタ(TMSTSp)      */
        /* → チャネルリセットモード遷移時に初期化済み */

        /* 送信バッファIDレジスタ(TMIDp) */
        ptChReg->ptstTM[ u1MBox ].u4IDReg = CAN_u4TMIDP_INIT;

        /* 送信バッファポインタレジスタ(TMPTRp) */
        ptChReg->ptstTM[ u1MBox ].u4PTRReg = CAN_u4TMPTRP_CLEARALL;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* 送信バッファCAN FDコンフィグレーションレジスタ(TMFDCTRp) */
        ptChReg->ptstTM[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTRP_CLEARALL;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

        for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_TB_TX_MB_DATA_ARYSIZE; u1Data++ )
        {
            /* 送信バッファデータフィールドbレジスタ(TMDFb_p) */
            ptChReg->ptstTM[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDFBP_CLEARALL;
        }
    }

    /* 送信バッファ割り込みイネーブルコンフィグレーションレジスタ(TMIECy) */
    *(ptChReg->ptu2TMIECy)   = CAN_u2TMIECY_INIT;

    /*------------------------------------*/
    /* 送信バッファステータス関連レジスタ */
    /*------------------------------------*/
    /* 送信バッファ送信要求ステータスレジスタ(TMTRSTSy)          */
    /* 送信バッファ送信アボート要求ステータスレジスタ(TMTARSTSy) */
    /* 送信バッファ送信完了ステータスレジスタ(TMTCSTSy)          */
    /* 送信バッファ送信アボートステータスレジスタ(TMTASTSy)      */
    /* → リードオンリーのため初期化対象なし                     */

    /*------------------------*/
    /* 送信キュー関連レジスタ */
    /*------------------------*/
    /* 送信キューコンフィグレーション／制御レジスタm(TXQCCm)                                              */
    /* チャネルリセットモード遷移時にTXQEビットが0に設定されるため、無条件にTXQIEビットへの書き込みを行う */
    *(ptChReg->ptu4TXQCCm)   = CAN_u4TXQCCM_INIT;

    /* 送信キューステータスレジスタ(TXQSTSm)      */
    /* →チャネルリセットモード遷移時に初期化済み */

    /* 送信キューポインタ制御レジスタm(TXQPCTRm)                             */
    /* → ポインタ制御レジスタに関しては、安全値の概念が無いため対象外とする */

    /*----------------------*/
    /* 送信履歴関連レジスタ */
    /*----------------------*/
    /* 送信履歴コンフィグレーション／制御レジスタm(THLCCm) */
    *(ptChReg->ptu4THLCCm)   = CAN_u4THLCCM_INIT;

    /* 送信履歴ステータスレジスタ(THLSTSm)         */
    /* → チャネルリセットモード遷移時に初期化済み */

    /* 送信履歴ポインタ制御レジスタm(THLPCTRm)                               */
    /* → ポインタ制御レジスタに関しては、安全値の概念が無いため対象外とする */

    /* 送信履歴アクセスレジスタm(THLACCm)    */
    /* → リードオンリーのため初期化対象なし */
}


/****************************************************************************/
/* Function Name | Can_st_SetGlobalReg                                      */
/* Description   | グローバルレジスタ使用設定                               */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | グローバルリセットモードから呼ばれる前提とする。         */
/****************************************************************************/
static void
Can_st_SetGlobalReg( void )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ      */
    volatile uint32                     u4DummyRead;        /* レジスタのダミーリード用                     */
    uint8                               u1Controller;       /* ループ用コントローラID                       */
    uint8                               u1CtrlNum;          /* コントローラ数                               */
    uint8                               u1RxFifo;           /* 受信FIFOバッファ数                           */

    /* 本処理は初期化、及びリセット処理から呼び出す                               */
    /* リセット処理からの呼び出しを考慮し、化けた場合に悪影響があるものに関しては */
    /* 再書き込みしておく                                                         */

    /* グローバルインタフェースモード選択レジスタ(GRMCFG) */
    /* マイコン制約に従い最初に設定                       */
    *(Can_tb_stGlobalReg.ptu4GRMCFG) = CAN_u4GRMCFG_INIT;

    /* グローバルインタフェースモード選択レジスタへの書き込み反映待ち */
    /* ※ 反映待ちの要否はRH850の中でもマイコン毎に異なるが、         */
    /*    コードを共通化するため実施しておく。                        */
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);
    u4DummyRead = *(Can_tb_stGlobalReg.ptu4GRMCFG);

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* グローバルCRC コンフィグレーションレジスタ(GCRCCFG) */
    *(Can_tb_stGlobalReg.ptu4GCRCCFG) = CAN_u4GCRCCFG_INIT;

    /* グローバルFD コンフィグレーションレジスタ(GFDCFG) */
    *(Can_tb_stGlobalReg.ptu4GFDCFG) = Can_tb_u4GFDCFGConf;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* グローバルコンフィグレーションレジスタ(GCFG)：CANクロックソース設定 */
    *(Can_tb_stGlobalReg.ptu4GCFG)   = Can_tb_u4GCFGConf;

    /*--------------------*/
    /* 割り込みマスク     */
    /*--------------------*/
    /* グローバルエラー割り込みの再マスク */
    /* モード関連のビットに対しては同値書き込みのため、待ち時間不要 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_RESET_SET;

    /* 送受信FIFOバッファ関連レジスタ、受信FIFOバッファ関連レジスタ */
    /* ※ 本レジスタはチャネル毎に割り当てて使用するが、リソース自体はグローバル要素に属するため */
    /*    設定可能なタイミングがグローバルモードに依存している。                                 */
    /*    そのため、本関数(グローバルレジスタ設定)にて設定する。                                 */
    /* ※ ただし安全上例外として、割り込みマスクと割り込み要因の設定については、                 */
    /*    グローバルモードを考慮した上で、チャネルの関数でも設定する。                           */
    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        /* 関連チャネルが制御対象CANのもののみを対象とする */
        if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
        {
            ptChReg       = &Can_tb_stChReg[ u1Controller ];
            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

            /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)：初期化、割り込み禁止、未使用 */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE; /* 送信用FIFO           */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE; /* 送信用FIFO           */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE; /* 割り込み受信用FIFO   */
        }
    }

    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];
        /* 受信FIFO バッファコンフィグレーション／制御レジスタ(RFCCx)：初期化、割り込み禁止、未使用  */
        Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ] = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFIE_DIS & CAN_u4RFCCX_RFE_NOUSE;  /* ポーリング受信用FIFO */
    }

    /* 未使用リソースの禁止設定を行うため、再書込 */
    for ( u1RxFifo = u1CtrlNum; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        Can_tb_stGlobalReg.ptu4RFCCx[ u1RxFifo ] = CAN_u4RFCCX_INIT;
    }

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* 送受信FIFOバッファステータスレジスタ(CFSTSk) */
    /* → グローバルリセットモード時にクリア済み    */

    /* 受信FIFOバッファステータスレジスタ(RFSTSx)*/
    /* → グローバルリセットモード時にクリア済み */

    /* グローバルエラー */
    /* GERFL.THLESクリア(THLSTSm.THLELTクリア)   */
    /* GERFL.MESクリア(RFSTSx.RFMLTクリア)       */
    /*                (CFSTSk.CFMLTクリア)       */
    /* GERFL.DEFクリア                           */
    /* GERFL.CMPOFクリア(CAN FDモード)           */
    /* → グローバルリセットモード時にクリア済み */

    /*--------------------------------------*/
    /* 未使用機能に対する設定のリフレッシュ */
    /*--------------------------------------*/
    /* 受信バッファナンバレジスタ(RMNB)       */
    /* 未使用機能の禁止設定があるため、再書込 */
    *(Can_tb_stGlobalReg.ptu4RMNB)     = CAN_u4RMNB_INIT;
}


/****************************************************************************/
/* Function Name | Can_st_SetChannelReg                                     */
/* Description   | チャネルレジスタ使用設定                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | チャネルリセットモードから呼ばれる前提とする。           */
/****************************************************************************/
static void
Can_st_SetChannelReg( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ      */
    uint32                              u4GSTS;             /* グローバルステータスレジスタラッチ用         */

    /* GCFGはグローバルレジスタだがパラメータチェック対象であるため、        */
    /* パラメータチェックNGからのリトライを考慮してここで再設定する。        */
    /* ※ すでにグローバル動作モードに遷移している場合設定できないが、       */
    /*    その場合パラメータチェックOKとなったチャネルがあることになるため、 */
    /*    GCFGは正しい値となっており再設定は不要。                           */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {   /* グローバルリセットモードの場合 */
        /* グローバルコンフィグレーションレジスタ(GCFG)：CANクロックソース設定 */
        *(Can_tb_stGlobalReg.ptu4GCFG)   = Can_tb_u4GCFGConf;
    }

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* 本処理は初期化、及びリセット処理から呼び出す                               */
    /* リセット処理からの呼び出しを考慮し、化けた場合に悪影響があるものに関しては */
    /* 再書き込みしておく                                                         */

    /*----------------------------------------------------*/
    /* 割り込み禁止、未使用機能に対する設定のリフレッシュ */
    /*----------------------------------------------------*/
    /* チャネル制御レジスタ(CmCTR) ：バスオフ復帰設定、各種未使用割り込み禁止 */
    *(ptChReg->ptu4CmCTR)    = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_RESET_SET;

    /* 送信バッファ割り込みイネーブルコンフィグレーションレジスタ(TMIECy)：割り込み禁止 */
    *(ptChReg->ptu2TMIECy)   = CAN_u2TMIECY_INIT;

    /* 送信キューコンフィグレーション/制御レジスタ(TXQCCM)：割り込み禁止、未使用機能の無効化 */
    *(ptChReg->ptu4TXQCCm)   = CAN_u4TXQCCM_INIT;

    /* 送信履歴コンフィグレーション/制御レジスタ(THLCCm)： 割り込み禁止、未使用機能の無効化 */
    *(ptChReg->ptu4THLCCm)   = CAN_u4THLCCM_INIT;

    /*----------------*/
    /* ボーレート設定 */
    /*----------------*/
    /* クラシカルCANモード：チャネルコンフィグレーションレジスタ(CmCFG)                  */
    /* CAN FDモード       ：チャネル通常ビットレートコンフィグレーションレジスタ(CmNCFG) */
    *(ptChReg->ptu4CmCFG)    = ptSetRSCANReg->u4CmCFGConf;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* チャネルデータビットレートコンフィグレーションレジスタ(CmDCFG)  */
    *(ptChReg->ptu4CmDCFG)   = ptSetRSCANReg->u4CmDCFGConf;

    /* チャネルCAN FDコンフィグレーションレジスタ(CmFDCFG) */
    *(ptChReg->ptu4CmFDCFG)  = ptSetRSCANReg->u4CmFDCFGConf;

#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* TMSTSp.TMTRF                                     */
    /* TXQSTSm.TXQIF                                    */
    /* THLSTSm.THLIF                                    */
    /* → チャネルリセットモードにすることで自動クリア  */

    /* CFSTSk.CFTXIF, CFRXIF                            */
    /* → ソフトウェアによる“0” 書き込みでクリア可    */
    /*     グローバル動作モードで書き込み可のため       */
    /*     チャネル通信開始直前にクリア                 */

    /* CmERFL.BEF, ALF, BLF, OVLF, BORF, BOEF, EPF, EWF */
    /* CmFDSTS.SOCO, EOCO, TDCVF(CAN FDモード)          */
    /* → チャネルリセットモードにすることで自動クリア  */

    /* グローバルエラーフラグレジスタ(GERFL) EEFmフラグのクリア */
    /* チャネル単位のビットを持つためここでクリアする。         */
    /* ただし全ビット使用しないため、一括で全てクリアする。     */
    *(Can_tb_stGlobalReg.ptu4GERFL) = CAN_u4GERFL_CLEARALL;
}


/****************************************************************************/
/* Function Name | Can_st_StopGlobal                                        */
/* Description   | グローバルレジスタ停止設定                               */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/*               | 以下のチャネルモードから呼ばれる前提とする。             */
/*               |  - チャネルリセットモード                                */
/*               |  - チャネルストップモード                                */
/****************************************************************************/
static void
Can_st_StopGlobal( void )
{
    uint8    u1RxFifo;           /* 受信FIFOバッファ数 */

    /*-------------------------------------------------------*/
    /* 割り込み要因                 要求フラグ  許可ビット   */
    /*-------------------------------------------------------*/
    /* 受信FIFO         受信 FIFO 0 RFSTS0.RFIF RFCC0.RFIE   */
    /*                  :           :           :            */
    /*                  受信 FIFO x RFSTSx.RFIF RFCCx.RFIE   */
    /*-------------------------------------------------------*/
    /* グローバルエラー             GERFL.DEF   GCTR.DEIE    */
    /*                              GERFL.MES   GCTR.MEIE    */
    /*                              GERFL.THLES GCTR.THLEIE  */
    /*-------------------------------------------------------*/

    /* 呼び出し条件のモードに遷移した時点で、シャットダウン機能に期待される       */
    /* 送受信なし、バスに悪影響を与えない、といった機能性は概ね達成されているため */
    /* モード遷移に影響を受けない部分(割り込みマスク、要因クリア)のみ設定する。   */

    /*----------------*/
    /* 割り込みマスク */
    /*----------------*/
    /* グローバルエラー割り込みの再マスク */
    /* モード関連のビットに対しては同値書き込みのため、待ち時間不要 */
    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_TSRST_RESET | CAN_u4GCTR_GMDC_RESET_SET;

    /* 受信FIFO割り込みマスク */
    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        Can_tb_stGlobalReg.ptu4RFCCx[ u1RxFifo ] = CAN_u4RFCCX_INIT;
    }

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* 受信FIFO */
    /* → グローバルリセットモード時にクリア済み */

    /* グローバルエラー */
    /* GERFL.THLESクリア(THLSTSm.THLELTクリア)   */
    /* GERFL.MESクリア(RFSTSx.RFMLTクリア)       */
    /*                (CFSTSk.CFMLTクリア)       */
    /* GERFL.DEFクリア                           */
    /* → グローバルリセットモード時にクリア済み */
}


/****************************************************************************/
/* Function Name | Can_st_StopChannel                                       */
/* Description   | チャネル通信停止                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 通信停止結果                                       */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | なし                                                     */
/****************************************************************************/
static uint8
Can_st_StopChannel( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ      */
    uint8                               u1Ret;              /* 戻り値                                       */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* 送受信FIFO停止、割り込み禁止、要因クリアの実施 */

    /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)                                    */
    /* 送受信FIFOバッファ許可ビットを使用しない、割り込み禁止に設定（メッセージクリア、割り込み禁止）*/
    /* CFEビットを下げる */
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFE_NOUSE;
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFE_NOUSE;
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFE_NOUSE;
    /* CFRXIE,CFTXIEビットを下げる */
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE;
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE;
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFTXRXIE_DIS & CAN_u4CFCCK_CFE_NOUSE;

    /* 送受信FIFOバッファステータスレジスタ(CFSTSk)のクリア（割り込み要因クリア）*/
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTSK_CLEARALL;          /* 送信用FIFO           */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTSK_CLEARALL;          /* 送信用FIFO           */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTSK_CLEARALL;          /* 割り込み受信用FIFO   */

    /* 受信 FIFO バッファコンフィグレーション／制御レジスタ(RFCCx) */
    /* 受信FIFOバッファ許可ビットを使用しない、割り込み禁止に設定（メッセージクリア、割り込み禁止）*/
    /* RFEビットを下げる */
    Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFE_NOUSE;
    /* RFIEビットを下げる */
    Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFIE_DIS & CAN_u4RFCCX_RFE_NOUSE;

    /* 受信 FIFO バッファステータスレジスタ(RFSTSx)のクリア */
    Can_tb_stGlobalReg.ptu4RFSTSx[ u1Controller ] = CAN_u4RFSTSX_CLEARALL;  /* ポーリング受信用FIFO */

    /* チャネルリセットモード遷移要求 */
    Can_st_ChannelMode_Any2Reset( u1Controller );

    /* モード遷移確認 */
    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
    {   /* チャネルリセットモード */

        /* 送信バッファ関連レジスタ */
        /* - 送信バッファ割り込みイネーブルコンフィグレーションレジスタ(TMIECy)：割り込み禁止 */
        *(ptChReg->ptu2TMIECy)   = CAN_u2TMIECY_INIT;

        /* チャネル関連レジスタ */
        /* - チャネルエラーフラグレジスタ(CmERFL)のクリア */
        /*   →チャネルリセットモード遷移時初期化済み     */

        /* 送信キュー関連レジスタ */
        /* - 送信キューコンフィグレーション/制御レジスタ(TXQCCm)：割り込み禁止 */
        *(ptChReg->ptu4TXQCCm)  = CAN_u4TXQCCM_INIT;

        /* - 送信キューステータスレジスタ(TXQSTSm)    */
        /*   →チャネルリセットモード遷移時初期化済み */

        /* 送信履歴関連レジスタ   */
        /* - 送信履歴コンフィグレーション/制御レジスタ(THLCCm)：割り込み禁止 */
        *(ptChReg->ptu4THLCCm)  = CAN_u4THLCCM_INIT;

        /* - 送信履歴ステータスレジスタ(THLSTSm)      */
        /*   →チャネルリセットモード遷移時初期化済み */

        u1Ret = (uint8)CAN_PROC_OK;
    }
    /* モード遷移に失敗した場合、次回モード遷移定期処理にて再確認する */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_StartGlobal                                       */
/* Description   | グローバルレジスタ開始設定                               */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/****************************************************************************/
static void
Can_st_StartGlobal( void )
{
    /* レジスタ固着チェックにより設定がクリアされてしまうため */
    /* 初期化処理と重複するが、再度設定しなおしておく。       */

    /* グローバルレジスタ使用設定 */
    Can_st_SetGlobalReg();

    /* 受信ルール関連レジスタ設定 */
    Can_st_SetRxRule();

    /* グローバル動作モード設定 */
    Can_st_GlobalMode_Reset2Comm();
}


/****************************************************************************/
/* Function Name | Can_st_StartChannel                                      */
/* Description   | チャネル通信開始                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 通信開始結果                                       */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 以下のモードから呼ばれる前提とする。                     */
/*               |   グローバルモード                                       */
/*               |   - グローバル動作モード                                 */
/****************************************************************************/
static uint8
Can_st_StartChannel( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;            /* チャネルレジスタアドレステーブルへのポインタ   */
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;      /* RSCANレジスタ設定値テーブルへのポインタ        */
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbTxMbBitType *         ptTxMbBit;          /* 送信MBOX種別ビット情報テーブルへのポインタ     */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                              u4CFSTSk_FIFO0;     /* 送受信FIFO0 バッファステータスレジスタラッチ用 */
    uint32                              u4CFSTSk_FIFO1;     /* 送受信FIFO1 バッファステータスレジスタラッチ用 */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                              u2TxMbUseBitMask;   /* 使用MBOXビットマスク                           */
    uint16                              u2TMTRSTSy;         /* 送信バッファ送信要求ステータスレジスタラッチ用 */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint8                               u1Fifo0LinkNum;     /* 送受信FIFO0の送信バッファリンク先MBOX番号      */
    uint8                               u1Fifo1LinkNum;     /* 送受信FIFO1の送信バッファリンク先MBOX番号      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint16                              u2TmpTxIntrBit;     /* 割り込み送信MBOXビット                         */
    uint8                               u1MBox;             /* MBOX数                                         */
    uint8                               u1Data;             /* MB.DATA数                                      */
    uint8                               u1Ret;              /* 戻り値                                         */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

#if (CAN_CFG_TRANSMIT == CAN_USE)
    /*  送信バッファ送信要求ステータスフラグの確認 */
    ptTxMbBit        = &Can_tb_stTxMbBit[ u1Controller ];
    u2TxMbUseBitMask = ( ptTxMbBit->u2TxIntrBit | ptTxMbBit->u2TxPollBit );
    u2TMTRSTSy = *( ptChReg->ptu2TMTRSTSy );
    if ( ( u2TMTRSTSy & u2TxMbUseBitMask ) == CAN_u2BIT_NONE )
    {
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /*  送受信FIFOバッファステータスレジスタの確認 */
        u4CFSTSk_FIFO0 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
        u4CFSTSk_FIFO1 = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
        if ( ( ( u4CFSTSk_FIFO0 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE )
          && ( ( u4CFSTSk_FIFO1 & CAN_u4CFSTSK_CFEMP_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        {
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
            /* Stop→Startが連続で呼ばれるシナリオの考慮                                                                                                                    */
            /* ・Stop処理では、メッセージ送出中の強制中断によるエラーフレームを回避するため、まず既存送信をキャンセルし、キャンセル完了を待機してから、Stop処理をしている。 */
            /* ・一方、上位層は、キャンセル完了待ちで、Stop処理が未実施の段階であってもStart要求を呼び出す可能性がある。                                                    */
            /* ⇒ よって、本関数としては、送信要求が空であることを確認してから一旦チャネルリセットモードに遷移させ、Start時の設定を可能とする。                             */

            /* チャネルリセットモード遷移要求 */
            Can_st_ChannelMode_Any2Reset( u1Controller );
#if (CAN_CFG_TRANSMIT == CAN_USE)
        }
    }
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */

    /* チャネルモード確認 */
    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
    {   /* チャネルリセットモードの場合 */

        /* レジスタ固着チェックにより設定がクリアされてしまうため初期化処理と重複するが、再度設定しなおしておく。   */
        /* チャネル制御レジスタ(CmCTR) ：バスオフ復帰設定、各種未使用割り込み禁止                                   */
        *(ptChReg->ptu4CmCTR)    = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_RESET_SET;

        /* クラシカルCANモード：チャネルコンフィグレーションレジスタ(CmCFG)                  */
        /* CAN FDモード       ：チャネル通常ビットレートコンフィグレーションレジスタ(CmNCFG) */
        /* InitController、SetBaudrateでのみ設定し、通信開始時には設定しない */

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* DMA 許可レジスタ(CDTCT)                                                                                                                             */
        /* グローバルレジスタだが、グローバル動作モードでしか設定できないため、チャネル毎に書き込み冗長だがここで設定する。                                    */
        /* CDTCT搭載マイコンではグローバルリセットモード遷移時に初期化されるが、未搭載マイコンの場合同領域が初期化されない可能性を考慮して明示的に初期化する。 */
        *(Can_tb_stGlobalReg.ptu4CDTCT) = CAN_u4CDTCT_INIT;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

        /* 送受信FIFO関連レジスタ：送受信FIFOバッファステータスレジスタ(CFSTSk)のクリア */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTSK_CLEARALL;          /* 送信用FIFO           */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTSK_CLEARALL;          /* 送信用FIFO           */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTSK_CLEARALL;          /* 割り込み受信用FIFO   */

        /* 割り込み受信用設定：送受信FIFOバッファコンフィグレーションレジスタ(CFCCk) */
        /* コンフィグ設定に応じてCFRXIEビットを立てる */
        ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCCK_CFE_NOUSE;
        /* コンフィグ設定に応じてCFEビットを立てる */
        ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf;

        /* 受信FIFOバッファ関連レジスタ：受信 FIFO バッファステータスレジスタ(RFSTSx)のクリア */
        Can_tb_stGlobalReg.ptu4RFSTSx[ u1Controller ] = CAN_u4RFSTSX_CLEARALL;  /* ポーリング受信用FIFO */

        /* ポーリング受信用設定：受信 FIFO バッファコンフィグレーション／制御レジスタ(RFCCx) */
        /* コンフィグ設定に応じてCFIEビットを立てる */
        Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf & CAN_u4RFCCX_RFE_NOUSE;
        /* コンフィグ設定に応じてRFEビットを立てる */
        Can_tb_stGlobalReg.ptu4RFCCx[ u1Controller ]  = ptSetRSCANReg->u4RFCCConf;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* マージモード送信バッファ関連レジスタのクリア */
        for ( u1MBox = (uint8)0U; u1MBox < (uint8)CAN_NUM_MERGE_BUF_SND_PER_CH; u1MBox++ )
        {
            /* 送信バッファ制御レジスタ(TMCp)のクリア         → チャネルリセットモード遷移時初期化済み */
            /* 送信バッファステータスレジスタ(TMSTSp)のクリア → チャネルリセットモード遷移時初期化済み */

            /* 送信バッファIDレジスタ(TMIDp)のクリア */
            /* 送信バッファポインタレジスタ(TMPTRp)のクリア */
            /* 送信バッファCAN FDコンフィグレーションレジスタ(TMFDCTRp)のクリア */
            ptChReg->ptstTM_MERGE[ u1MBox ].u4IDReg    = CAN_u4TMIDP_INIT;
            ptChReg->ptstTM_MERGE[ u1MBox ].u4PTRReg   = CAN_u4TMPTRP_CLEARALL;
            ptChReg->ptstTM_MERGE[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTRP_CLEARALL;

            for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_TB_TX_MB_DATA_MERGEARYSIZE; u1Data++ )
            {
                /* 送信バッファデータフィールドbレジスタ(TMDFb_p)のクリア */
                ptChReg->ptstTM_MERGE[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDFBP_CLEARALL;
            }
        }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

        /* 送信バッファ関連レジスタのクリア */
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* 送受信FIFO0、1のビット位置取得 */
        u1Fifo0LinkNum = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
        u1Fifo1LinkNum = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
        for ( u1MBox = (uint8)CAN_ST_BUF_SND_TOP; u1MBox < (uint8)CAN_NUM_BUF_SND_PER_CH; u1MBox++ )
        {
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
            /* 送受信FIFOバッファにリンクした送信バッファか確認 */
            if ( ( u1Fifo0LinkNum != u1MBox ) && ( u1Fifo1LinkNum != u1MBox ) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
            {
                /* 送信バッファ制御レジスタ(TMCp)のクリア         → チャネルリセットモード遷移時初期化済み */
                /* 送信バッファステータスレジスタ(TMSTSp)のクリア → チャネルリセットモード遷移時初期化済み */

                /* 送信バッファIDレジスタ(TMIDp)のクリア */
                /* 送信バッファポインタレジスタ(TMPTRp)のクリア */
                ptChReg->ptstTM[ u1MBox ].u4IDReg  = CAN_u4TMIDP_INIT;
                ptChReg->ptstTM[ u1MBox ].u4PTRReg = CAN_u4TMPTRP_CLEARALL;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
                /* 送信バッファCAN FDコンフィグレーションレジスタ(TMFDCTRp)のクリア */
                ptChReg->ptstTM[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTRP_CLEARALL;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

                for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_TB_TX_MB_DATA_ARYSIZE; u1Data++ )
                {
                    /* 送信バッファデータフィールドbレジスタ(TMDFb_p)のクリア */
                    ptChReg->ptstTM[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDFBP_CLEARALL;
                }
            }
        }

        /* 送信完了割り込み許可設定 */
        /* - 送信バッファ割り込みイネーブルコンフィグレーションレジスタ(TMIECy) */
        u2TmpTxIntrBit = Can_tb_stTxMbBit[ u1Controller ].u2TxIntrBit;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* 送受信FIFOにリンクされたMBOXは除外する */
        u2TmpTxIntrBit &= Can_tb_u2TxFifoBitMask[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        *(ptChReg->ptu2TMIECy)  = u2TmpTxIntrBit;

        /* 送信キュー関連レジスタ */
        /* - 送信キューコンフィグレーション/制御レジスタ(TXQCCm)のクリア */
        *(ptChReg->ptu4TXQCCm)  = CAN_u4TXQCCM_INIT;

        /* - 送信キューステータスレジスタ(TXQSTSm)のクリア → チャネルリセットモード遷移時初期化済み */

        /* 送信履歴関連レジスタ*/
        /* - 送信履歴コンフィグレーション/制御レジスタ(THLCCm)のクリア   */
        *(ptChReg->ptu4THLCCm)  = CAN_u4THLCCM_INIT;

        /* - 送信履歴ステータスレジスタ(THLSTSm)のクリア → チャネルリセットモード遷移時初期化済み */

        /* チャネルエラーフラグレジスタ(CmERFL)のクリア  → チャネルリセットモード遷移時初期化済み */

        /* ユーザによるボーレート再設定向けの通知 */
        Can_st_PreStart( u1Controller );

        /* チャネル通信モード設定 */
        Can_st_ChannelMode_Reset2Comm( u1Controller );
        if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM )
        {
            /* チャネル通信モード遷移完了 */

            /* 送信用設定：送受信FIFOバッファコンフィグレーションレジスタ(CFCCk) */
            /* コンフィグ設定に応じてCFTXIEビットを立てる */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFE_NOUSE;
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFE_NOUSE;

            /* コンフィグ設定に応じてCFEビットを立てる */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf;
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf;

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ResetGlobal                                       */
/* Description   | グローバルレジスタ再初期化                               */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | uint8 再初期化結果                                       */
/*               |   CAN_PROC_OK   : 設定完了                               */
/*               |   CAN_PROC_BUSY : 設定未完了                             */
/* Notes         | ・任意のグローバルモードから呼び出される前提とする。     */
/*               | ・本APIの処理が成功した場合、以下のモードとなる。        */
/*               |   グローバルモード                                       */
/*               |   - グローバルリセットモード                             */
/****************************************************************************/
static uint8
Can_st_ResetGlobal( void )
{
    uint32    u4GSTS;             /* グローバルステータスレジスタラッチ用 */
    uint8     u1Ret;              /* 戻り値                               */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* DMA 許可レジスタ(CDTCT) */
    /* グローバル動作モードでしか設定できないため */
    /* リセットモードへの変更前に設定する。       */
    *(Can_tb_stGlobalReg.ptu4CDTCT) = CAN_u4CDTCT_INIT;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* グローバルリセットモード設定 */
    Can_st_GlobalMode_Any2Reset();

    /* モード遷移確認 */
    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {   /* グローバルリセットモード遷移完了 */

        /* グローバルレジスタ使用設定 */
        Can_st_SetGlobalReg();

        /* 受信ルール関連レジスタ設定 */
        Can_st_SetRxRule();

        /* グローバルレジスタ再初期化成功 */
        u1Ret = (uint8)CAN_PROC_OK;
    }
    /* グローバルリセットモード遷移失敗時(HW故障)   */
    /* 何もせず、次回モード遷移定期処理で再確認する */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ResetChannel                                      */
/* Description   | チャネル再初期化                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 再初期化結果                                       */
/*               |   CAN_PROC_OK      : 設定完了                            */
/*               |   CAN_PROC_BUSY    : 設定未完了                          */
/* Notes         | 以下のグローバルモードから呼ばれる前提とする。           */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバルテストモード                                */
/*               |  - グローバル動作モード                                  */
/*               | 以下のチャネルモードから呼ばれる前提とする。             */
/*               |  - チャネルリセットモード                                */
/*               |  - チャネル待機モード                                    */
/*               |  - チャネル通信モード                                    */
/*               |  ※ 本APIの呼び出し条件はCan_st_SetControl成功後である為 */
/*               |     グローバルストップモード/チャネルストップモード      */
/*               |      では呼ばれない。                                    */
/****************************************************************************/
static uint8
Can_st_ResetChannel( uint8 u1Controller )
{
    uint8    u1Result;           /* 関数戻り値 */
    uint8    u1Ret;              /* 戻り値     */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_BUSY;

    /* チャネル通信停止 */
    u1Result = Can_st_StopChannel( u1Controller );
    if ( u1Result == (uint8)CAN_PROC_OK )
    {
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* BRS設定値初期化 */
        Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

        /* チャネルレジスタ使用設定 */
        Can_st_SetChannelReg( u1Controller );

        /* 再初期化成功 */
        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_SetRxRule                                         */
/* Description   | 受信ルール関連レジスタ設定                               */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | 以下のモードから呼ばれる前提とする。                     */
/*               |  - グローバルリセットモード                              */
/****************************************************************************/
static void
Can_st_SetRxRule( void )
{
    uint32    u4Page;             /* 受信ルールテーブルページ番号     */
    uint32    u4FlMask;           /* 受信フィルタマスク値             */
    uint16    u2MaxNumRxRule;     /* 受信ルール数                     */
    uint16    u2RxRuleNo;         /* 受信ルール番号                   */
    uint8     u1RuleRegNo;        /* 格納先レジスタ番号               */
    uint8     u1MskIdx;           /* 受信マスク値テーブルインデックス */

    /* 各チャネル毎に使用する受信ルール数の設定 */
    /* 受信ルールコンフィグレーションレジスタ0：コンフィグ値設定 */
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] = Can_tb_u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* 受信ルールコンフィグレーションレジスタ1：コンフィグ値設定 */
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] = Can_tb_u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */

    /* 受信ルール数分処理 */
    u2MaxNumRxRule = Can_tb_u2MaxNumRxRule;
    for ( u2RxRuleNo = (uint16)0U; u2RxRuleNo < u2MaxNumRxRule; u2RxRuleNo++ )
    {
        /* 受信ルールテーブルページ番号取得 */
        u4Page = ( (uint32)( (uint32)u2RxRuleNo >> CAN_NUM_RULETABLE_PER_PAGE_SFT ) & CAN_u4GAFLECTR_AFLPN_MSK );

        /* 受信ルール書き込み先レジスタインデックス取得 */
        u1RuleRegNo = (uint8)( u2RxRuleNo & (uint16)CAN_NUM_RULETABLE_PER_PAGE_MSK );

        /* 受信ルールエントリ制御レジスタへの書き込み許可設定、及び、書き込みページ設定 */
        *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ( CAN_u4GAFLECTR_AFLDAE_ENA | u4Page );

        /* 受信ルールの書き込み */
        u1MskIdx = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u1RxMaskRef;
        u4FlMask = Can_tb_u4RxMask[ u1MskIdx ];
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLIDj = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLIDjConf;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLMj  = u4FlMask;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0j = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP0jConf;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1j = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP1jConf;
    }

    /* 受信ルール書き込み終了後処置 */
    /* 受信ルールエントリ制御レジスタへの書き込み禁止設定、及び、書き込みページ設定のクリア */
    *(Can_tb_stGlobalReg.ptu4GAFLECTR) = CAN_u4GAFLECTR_AFLDAE_DIS;
}


/****************************************************************************/
/* Function Name | Can_st_PhyInit                                           */
/* Description   | 状態管理機能(マイコン依存)初期化                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
static void
Can_st_PhyInit( void )
{
    uint8    u1Controller;       /* ループ用コントローラID */
    uint8    u1CtrlNum;          /* コントローラ数         */

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        /* BRS設定値初期化 */
        Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];
    }
}
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/03/28                                              */
/*  v2-0-2         :2017/04/24                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
