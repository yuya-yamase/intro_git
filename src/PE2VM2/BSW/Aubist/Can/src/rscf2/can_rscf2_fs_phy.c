/* can_rscf2_fs_phy_c_m10700_v2-2-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/FS/PHYSICAL/CODE                                */
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
#include <can/rscf2/can_rscf2_tx.h>
#include <can/rscf2/can_rscf2_rx.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* レジスタ固着チェックパターン */
#define CAN_FS_u4REGCHK_PTN1            (0xAAAAAAAAUL)                      /* レジスタ固着チェックパターン1          */
#define CAN_FS_u4REGCHK_PTN2            (0x55555555UL)                      /* レジスタ固着チェックパターン2          */

/* レジスタ固着チェック実施状態 */
#define CAN_FS_REGCHK_STS_WAIT          (0x5AU)                             /* 固着チェック待機中                     */
#define CAN_FS_REGCHK_STS_OK            (0xA5U)                             /* 固着チェック完了(固着なし)             */
#define CAN_FS_REGCHK_STS_NG            (0x96U)                             /* 固着チェック完了(固着あり)             */
#define CAN_FS_REGCHK_STS_PASS          (0x69U)                             /* 固着チェック無視 ※別Chでチェック      */

/* MPU異常発生有無 */
#define CAN_FS_MPUFAIL_EXIST            (0x5AU)                             /* MPU異常あり                            */
#define CAN_FS_MPUFAIL_NONE             (0xA5U)                             /* MPU異常なし                            */

/* RAMテスト結果 */
#define CAN_FS_RAMTEST_OK               (0x5AU)                             /* RAMテスト異常なし(テスト継続中)        */
#define CAN_FS_RAMTEST_NG               (0xA5U)                             /* RAMテスト異常あり                      */
#define CAN_FS_RAMTEST_FIN              (0x96U)                             /* RAMテスト完了                          */

#define CAN_FS_RAMTEST_DATANUM_MAX      (64U)                               /* RAMテスト1ページ内要素数 最大値        */
#define CAN_FS_RAMTEST_PROTECT_COUNT    (26U)                               /* RAMテスト許可ビット反映待ちカウント    */
                                                                            /* (RSCANの持つ割り込み本数 グローバル2本+チャネル3本*8) */

/* エラー状態取得用パターン */
#define CAN_FS_u4ERRACTIVE              (0x00000000UL)                      /* エラー状態取得 エラーアクティブ        */
#define CAN_FS_u4ERRPASSIVE             (0x00000008UL)                      /* エラー状態取得 エラーパッシブ          */
#define CAN_FS_u4CMSTSCHK_MASK_ERRSTS   (0x00000018UL)                      /* エラー状態取得 CMSTS.BOSTS/EPSTS       */

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_FS_u4PARAMCHK_CMCFG_MASK    (0x037F03FFUL)                      /* 通信パラメータチェック対象マスク(CmCFG)   */
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_FS_u4PARAMCHK_CMCFG_MASK    (0x1F7FFBFFUL)                      /* 通信パラメータチェック対象マスク(CmCFG)   */
#define CAN_FS_u4PARAMCHK_CMDCFG_MASK   (0x077F00FFUL)                      /* 通信パラメータチェック対象マスク(CmDCFG)  */
#define CAN_FS_u4PARAMCHK_CMFDCFG_MASK  (0x007F0300UL)                      /* 通信パラメータチェック対象マスク(CmFDCFG) */
#endif /* (CAN_OPEMODE) */

/* 不正割り込み共通処理の使用/未使用 */
#define CAN_FS_ILLEGALINT_ANYCH_USE \
    ( ( (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) ) ? CAN_USE : CAN_NOUSE )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE)
static void  Can_fs_IllegalInterrupt( uint8 u1Controller );
#endif /* (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) */
static uint8 Can_fs_RAMTest( uint8 u1Time );
static uint8 Can_fs_RAMTestPage( uint8 u1TargetPage, uint8 u1ElmNum );
static uint8 Can_fs_RAMTestEnable( void );
static uint8 Can_fs_RAMTestDisable( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------*/
/* レジスタ固着チェック受付状態                               */
/* ・内容：                                                   */
/*     レジスタ固着チェックの受付状態を記憶する。             */
/* ・値域：                                                   */
/*     CAN_FS_REGCHK_STS_WAIT  固着チェック待機中             */
/*     CAN_FS_REGCHK_STS_OK    固着チェック完了(固着なし)     */
/*     CAN_FS_REGCHK_STS_NG    固着チェック完了(固着あり)     */
/*     CAN_FS_REGCHK_STS_PASS  固着チェック無視               */
/* ・RAM化け対策：                                            */
/*     設定値には、1bit化けで別の値にならないものを設定する。 */
/*------------------------------------------------------------*/
static uint8 Can_fs_u1RegChkStatus[ CAN_CFG_CONTROLLERNUM_MAX ];


/*------------------------------------------------------------*/
/* MPU異常発生有無                                            */
/* ・内容：                                                   */
/*     MPU異常の発生有無を記憶する。                          */
/* ・値域：                                                   */
/*     CAN_FS_MPUFAIL_EXIST  MPU異常あり                      */
/*     CAN_FS_MPUFAIL_NONE   MPU異常なし                      */
/* ・RAM化け対策：                                            */
/*     設定値には、1bit化けで別の値にならないものを設定する。 */
/*     化け時はMPU異常ありとして扱う。                        */
/*------------------------------------------------------------*/
static uint8 Can_fs_u1MpuFail[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_ChkBusOff                                         */
/* Description   | コントローラバスオフ検出チェック                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラバスオフ検出チェック結果               */
/*               |   CAN_NONE      : バスオフなし                           */
/*               |   CAN_EXIST     : バスオフあり                           */
/* Notes         | ・バスオフ復帰方法をMANUALにコンフィグされている場合に   */
/*               |   のみ、呼ばれる前提とする。                             */
/*               | ・中優先度タスクで実施される。                           */
/*               | ・CANIFに対する通知は Can_MainFunction_BusOffで行う。    */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
uint8
Can_fs_ChkBusOff( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;       /* チャネルレジスタアドレステーブルへのポインタ */
    uint8                            u1Ret;         /* 戻り値                                       */

    u1Ret = (uint8)CAN_NONE;

    /* チャネル別レジスタアドレステーブルのラッチ */
    ptChReg = &Can_tb_stChReg[ u1Controller ];

    /* バスオフ発生状態確認 */
    if ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF )
    {
        /* バスオフ開始フラグクリア */
        *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_BOEF_CLR;

        /* バスオフ検出を通知 */
        Can_fs_BusOffInd( u1Controller );

        u1Ret = (uint8)CAN_EXIST;

        /* 以降、本関数の呼び出し元にてコントローラ停止処理が呼び出される */
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_BusOffRecovery                                    */
/* Description   | コントローラバスオフ自動復帰                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・バスオフ復帰方法をAUTOにコンフィグされている場合にのみ */
/*               |   呼ばれる前提とする。                                   */
/*               | ・バスオフ自動復帰機能を持たないマイコンの場合以下を実施 */
/*               |   - バスオフ発生状態を確認                               */
/*               |   - バスオフ検出時に、バスオフ復帰処理の実施             */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
void
Can_fs_BusOffRecovery( uint8 u1Controller )
{
    /* バスオフ自動復帰が可能なCANコントローラのため、本関数は空実装とする。*/
}


/****************************************************************************/
/* Function Name | Can_fs_ChkReg                                            */
/* Description   | MBOXレジスタ固着チェック                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/*               | uint8 u1Time       : 指定回数（n回目のチェック実施）     */
/* Return Value  | uint8 MBOXレジスタ固着チェック結果                       */
/*               |   CAN_FS_REGCHK_NONE      : レジスタ固着なし             */
/*               |   CAN_FS_REGCHK_EXIST     : レジスタ固着検出             */
/*               |   CAN_FS_REGCHK_OPT_EXIST : レジスタ固着検出(未使用MBOX  */
/*               |                             での固着検出)(なし)          */
/* Notes         | 以下のモードから呼ばれる前提とする。                     */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
uint8
Can_fs_ChkReg( uint8 u1Controller, uint8 u1Time )
{
    uint8  u1RAMTestResult;      /* RAMテスト結果        */
    uint8  u1RegChkStatus;       /* 固着チェック受付状態 */
    uint8  u1Idx;                /* ループ用インデックス */
    uint8  u1CtrlNum;            /* コントローラ数       */
    uint8  u1Ret;                /* 戻り値               */

    /* ・本マイコンにはレジスタ固着チェック用の機能である「RAMテスト機能」が搭載     */
    /*   されており、この機能を利用してレジスタ固着チェックを実現する。              */
    /* ・固着チェック範囲は、RAMテスト機能でチェック可能な「CAN用RAM領域」とする。   */
    /* ・CAN用RAM領域 は、マイコングローバル要素であり、かつ、領域の詳細情報         */
    /*   (どのアドレスにどのデータが配置されるか)は、HWで閉じて管理されており        */
    /*   SWからは参照できない。よって、使用領域、未使用領域の区別もできない。        */
    /* ・CanIfを含む上位層、及び、CanのLog層では、レジスタ固着チェックはコントローラ */
    /*   毎に独立で行う前提で定義されているため、本APIもコントローラ毎に独立して     */
    /*   呼び出される。                                                              */
    /*                                                                               */
    /* 上記前提／HW特性を踏まえ、下記設計とする。                                    */
    /* ・チェック結果は、全コントローラで同じ値を返す。                              */
    /* ・チェック実施は、本APIが最初に呼び出された時に指定されたコントローラ(代表Ch) */
    /*   で行う。代表Ch以外で本APIが呼び出された場合は、代表Chの結果を応答する。     */
    /* ・固着検出時の戻り値は、「CAN_FS_REGCHK_EXIST」のみとし、                     */
    /*   「CAN_FS_REGCHK_OPT_EXIST」は使用しない。                                   */
    /*                                                                               */
    /* 例)・コントローラ数2、分割回数2  の呼び出し順序(固着未発生の場合)             */
    /*      ※ 論理Ch:0-物理Ch1 論理Ch:1-物理Ch0でマッピングされていた場合           */
    /*      ①:「u1Controller:1 u1Time:0」 u1Time:0用範囲をチェック 固着なし応答     */
    /*      ②:「u1Controller:0 u1Time:0」 チェックしない           固着なし応答     */
    /*      ③:「u1Controller:1 u1Time:1」 u1Time:1用範囲をチェック 固着なし応答     */
    /*      ④:「u1Controller:0 u1Time:1」 チェックしない           固着なし応答     */
    /*                                                                               */
    /*    ・コントローラ数2、分割回数2 の呼び出し順序(固着発生の場合)                */
    /*      ※ 論理Ch:0-物理Ch1 論理Ch:1-物理Ch0でマッピングされていた場合           */
    /*      ①:「u1Controller:1 u1Time:0」 u1Time:0用範囲をチェック 固着なし応答     */
    /*      ②:「u1Controller:0 u1Time:0」 チェックしない           固着なし応答     */
    /*      ③:「u1Controller:1 u1Time:1」 u1Time:1用範囲をチェック 固着あり応答     */
    /*      ④:「u1Controller:0 u1Time:1」 チェックしない           固着あり応答     */
    /*      レジスタ固着チェックのリトライ発生                                       */
    /*      ⑤:「u1Controller:1 u1Time:0」 u1Time:0用範囲を再チェック 固着なし応答   */
    /*      ⑥:「u1Controller:0 u1Time:0」 チェックしない             固着なし応答   */
    /*      ⑦:「u1Controller:1 u1Time:1」 u1Time:1用範囲を再チェック 固着なし応答   */
    /*      ⑧:「u1Controller:0 u1Time:1」 チェックしない             固着なし応答   */

    /* 戻り値を固着ありで初期化 */
    u1Ret = (uint8)CAN_FS_REGCHK_EXIST;

    /* 固着チェック状態確認 */
    u1RegChkStatus = Can_fs_u1RegChkStatus[ u1Controller ];
    if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_WAIT )
    {   /*========固着チェック待機中の場合========*/

        /* 自分以外のChの固着チェック状態を「固着チェック無視」に変更 */
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_PASS;
        }
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;

        /* RAMテスト実施 */
        u1RAMTestResult = Can_fs_RAMTest( u1Time );
        if ( u1RAMTestResult == (uint8)CAN_FS_RAMTEST_OK )
        {
            /* RAMテスト異常なし(テスト継続中) */
            u1Ret = (uint8)CAN_FS_REGCHK_NONE;
        }
        else if ( u1RAMTestResult == (uint8)CAN_FS_RAMTEST_FIN )
        {
            /* RAMテスト完了 */
            /* 全Chの固着チェック状態を「固着チェック完了(固着なし)」に変更 */
            for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
            {
                Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_OK;
            }
            u1Ret = (uint8)CAN_FS_REGCHK_NONE;
        }
        else
        {
            /* RAMテスト異常あり */
            /* 全Chの固着チェック状態を「固着チェック完了(固着あり)」に変更 */
            /* ※ 以降で代表Ch以外のコントローラに対し本APIが呼ばれた時に、 */
            /*    代表Chと同様に「固着あり」を応答できるようにする。        */
            for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
            {
                Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_NG;
            }
        }
    }
    else if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_PASS )
    {   /*========固着チェック無視の場合========*/
        /* 代表Chにて固着チェック継続中 */
        /* 当該チャネル(非代表Ch)では、固着なしを返す */
        u1Ret = (uint8)CAN_FS_REGCHK_NONE;
    }
    else if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_OK )
    {   /*========固着チェック完了(固着なし)========*/
        u1Ret = (uint8)CAN_FS_REGCHK_NONE;
    }
    else
    {   /*========固着チェック完了(固着あり)========*/
        /* 固着チェック状態のRAM化けが発生した場合を考慮し、            */
        /* 全Chの固着チェック状態を「固着チェック完了(固着あり)」に変更 */
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_NG;
        }
        /* 戻り値は初期値(固着あり)とする */
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_CheckMpu                                          */
/* Description   | コントローラMPU異常チェック                              */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 コントローラMPU異常チェック結果                    */
/*               |   CAN_NONE         : MPU異常なし                         */
/*               |   CAN_EXIST        : MPU異常あり                         */
/* Notes         | ・CANコントローラ内蔵の異常チェック結果を応答する。      */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
uint8
Can_fs_CheckMpu( uint8 u1Controller )
{
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint8  u1BRSUse;           /* BRS設定値                      */
    uint8  u1CheckData;        /* RAM化け確認用データ            */
    uint8  u1CheckDataLo;      /* RAM化け確認用データ下位4ビット */
    uint8  u1CheckDataHi;      /* RAM化け確認用データ上位4ビット */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8  u1Ret;              /* 戻り値                         */

    /* 戻り値の初期化 */
    u1Ret = (uint8)CAN_NONE;

    /* MPU異常発生有無の確認 */
    if ( Can_fs_u1MpuFail[ u1Controller ] != (uint8)CAN_FS_MPUFAIL_NONE )
    {
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_NONE;
        u1Ret = (uint8)CAN_EXIST;
    }

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* RAMチェック */
    /* BRS設定値 */
    u1BRSUse = Can_st_u1BRSUse[ u1Controller ];
    u1CheckDataLo = (uint8)( u1BRSUse & (uint8)CAN_RAMCHK_MASK_LOWERHALFBYTE );
    u1CheckDataHi = (uint8)( u1BRSUse >> CAN_SFT_4 );
    u1CheckData = u1CheckDataLo + u1CheckDataHi;
    if ( u1CheckData != (uint8)CAN_RAMCHK_VALUE_LOWERHALFBYTE )
    {
        u1Ret = (uint8)CAN_EXIST;
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_0                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
void
Can_IllegalInterrupt_0( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_1                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
void
Can_IllegalInterrupt_1( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_2                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
void
Can_IllegalInterrupt_2( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_3                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
void
Can_IllegalInterrupt_3( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_4                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
void
Can_IllegalInterrupt_4( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_5                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
void
Can_IllegalInterrupt_5( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_6                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
void
Can_IllegalInterrupt_6( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_7                                   */
/* Description   | 不正割り込み                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・当該CANコントローラが非制御対象CANにコンフィグ         */
/*               |   されている場合、本APIは提供しない。                    */
/*               | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - チャネル割り込み[未使用コントローラの場合]           */
/*               |     - 全てのチャネル割り込み                             */
/*               |   - チャネル割り込み[使用コントローラの場合]             */
/*               |     - CANm送信割り込み[送信完了割り込みを使わない場合]   */
/*               |     - CANm送受信FIFO受信完了割り込み                     */
/*               |                       [受信完了割り込みを使わない場合]   */
/*               |     - CANmエラー割り込み                                 */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
void
Can_IllegalInterrupt_7( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_Global                              */
/* Description   | 不正割り込み(グローバル)                                 */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・本関数は、下記未使用割り込みベクタに登録され           */
/*               |   対象に応じた不正割り込み抑制処置を実施する。           */
/*               |   - グローバル割り込み                                   */
/*               |     - 受信FIFO                                           */
/*               |     - グローバルエラー                                   */
/*               | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/*               | ・本関数呼び出し後、フェール定期処理にてMPU異常を通知し、*/
/*               |   再初期化されることを期待する。                         */
/****************************************************************************/
void
Can_IllegalInterrupt_Global( void )
{
    volatile uint32 *   ptRFSTSx;      /* RFSTSレジスタの先頭アドレス */
    volatile uint32     u4DummyRead;   /* レジスタのダミーリード用    */
    uint8               u1RxFifo;      /* 受信FIFOバッファ数          */
    uint8               u1Controller;  /* ループ用コントローラID      */
    uint8               u1CtrlNum;     /* コントローラ数              */

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
    /*                (CAN FDモード)GERFL.CMPOF GCTR.CMPOFIE */
    /*-------------------------------------------------------*/

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* 受信FIFO */
    /* 受信FIFOはポーリング受信で使用するため、割り込み要因はクリア固定 */
    ptRFSTSx = Can_tb_stGlobalReg.ptu4RFSTSx;
    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        ptRFSTSx[ u1RxFifo ] = CAN_u4RFSTSX_CLEARALL;
    }

    /* グローバルエラー */
    *(Can_tb_stGlobalReg.ptu4GERFL) = CAN_u4GERFL_CLEARALL;

    /*----------------*/
    /* 割り込みマスク */
    /*----------------*/
    /* 割り込みマスクを再設定するためにはグローバルモード遷移が必要だが、                               */
    /* 割り込み処理からモード遷移させた場合、割り込まれる処理側でモードの前提が崩れる可能性があるため、 */
    /* モード遷移はしない。                                                                             */
    /* → 本設計での割込みの再発の抑制は、全グローバル割り込み要因をクリアするまでとする。              */
    /*    その後、フェール定期処理にて上位層にMPU異常を通知し、再初期化されることを期待する。           */

    /*-------------*/
    /* MPU異常通知 */
    /*-------------*/
    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
    }

    /* パイプライン同期(ダミーリード＋SYNCP) */
    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
    Can_tb_SYNCP();
}

/****************************************************************************/
/* Function Name | Can_fs_ResetInterrupt                                    */
/* Description   | 割り込み再設定                                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・本関数は、コントローラ別の割り込み設定のリフレッシュを */
/*               |   目的とする。                                           */
/*               |   ソフト上使用する割り込みを阻害しない範囲での再設定処置 */
/*               |   (未使用割り込み要因のクリア等)まで実施する。           */
/*               |   但し、割り込み再発防止上必要であれば、                 */
/*               |   使用割り込み要因もクリアする。この場合はフェール定期   */
/*               |   処理にてMPU異常を通知し、再初期化されることを期待する。*/
/*               | ・本関数は、指定されたコントローラで割り込みが起こりえる */
/*               |   状態(チャネル通信モード)でのみ呼び出されることを       */
/*               |   前提とする。                                           */
/*               | ・パイプライン同期は呼び出し元関数で実施する。           */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) )
void
Can_fs_ResetInterrupt( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;       /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbSetRSCANRegType *  ptSetRSCANReg; /* RSCANレジスタテーブルへのポインタ            */
    CanConst CanTbTxMbBitType *      ptTxMbBit;     /* 送信MBOX種別ビット情報テーブルへのポインタ   */
    uint16                           u2TxUseBit;    /* 使用送信MBOXビット                           */
    uint16                           u2TmpTxIntrBit;/* 割り込み送信MBOXビット                       */
    uint8                            u1Idx;         /* ループ用インデックス                         */

    /*------------------------------------------------------------------------------------------------*/
    /* 割り込み要因                     要求フラグ         許可ビット    要求フラグの使用／未使用     */
    /*------------------------------------------------------------------------------------------------*/
    /* CANm送信     送信完了            TMSTSp.TMTRF[1:0]  TMIECy.TMIEp  使用(使用MBのみ)             */
    /*              送信アボート        TMSTSp.TMTRF[1:0]  CmCTR.TAIE    使用(使用MBのみ)             */
    /*              送受信 FIFO送信完了 CFSTSk.CFTXIF      CFCCk.CFTXIE  使用(使用FIFOのみ)           */
    /*              送信キュー          TXQSTSm.TXQIF      TXQCCm.TXQIE  未使用                       */
    /*              送信履歴            THLSTSm.THLIF      THLCCm.THLIE  未使用                       */
    /*------------------------------------------------------------------------------------------------*/
    /* CANm送受信FIFO受信完了           CFSTSk.CFRXIF      CFCCk.CFRXIE  使用(使用FIFOのみ)           */
    /*------------------------------------------------------------------------------------------------*/
    /* CANmエラー                       CmERFL.BEF         CmCTR.BEIE    未使用                       */
    /*                                  CmERFL.ALF         CmCTR.ALIE    未使用                       */
    /*                                  CmERFL.BLF         CmCTR.BLIE    未使用                       */
    /*                                  CmERFL.OVLF        CmCTR.OLIE    未使用                       */
    /*                                  CmERFL.BORF        CmCTR.BORIE   未使用                       */
    /*                                  CmERFL.BOEF        CmCTR.BOEIE   使用(バスオフ検出用)         */
    /*                                  CmERFL.EPF         CmCTR.EPIE    未使用                       */
    /*                                  CmERFL.EWF         CmCTR.EWIE    未使用                       */
    /*                    (CAN FDモード)CmFDSTS.SOCO       CmCTR.SOCOIE  未使用                       */
    /*                    (CAN FDモード)CmFDSTS.EOCO       CmCTR.EOCOIE  未使用                       */
    /*                    (CAN FDモード)CmFDSTS.TDCVF      CmCTR.TDCVFIE 未使用                       */
    /*------------------------------------------------------------------------------------------------*/

    /* チャネル別レジスタアドレステーブルのラッチ */
    ptChReg = &Can_tb_stChReg[ u1Controller ];
    /* チャネル別RSCANレジスタ設定値テーブルのラッチ */
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* TMSTSp.TMTRF(未使用MBOX用) */
    /* 割り込み送信にもポーリング送信にも設定されていない送信MBOXの要因をクリアする */
    ptTxMbBit = &Can_tb_stTxMbBit[ u1Controller ];
    u2TxUseBit = ptTxMbBit->u2TxIntrBit | ptTxMbBit->u2TxPollBit;
    for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
    {
        if( (u2TxUseBit & (uint16)(CAN_u2BIT0 << u1Idx)) == CAN_u2BIT_NONE )
        {
            ptChReg->ptu1TMSTSp[ u1Idx ] = CAN_u1TMSTSP_TMTRF_CLR;
        }
    }

    /* CFSTSk.CFTXIF, CFRXIF */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFSTS0Conf; /* 送信用FIFO        : 送信はコンフィグ依存、受信は未使用 */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFSTS1Conf; /* 送信用FIFO        : 送信はコンフィグ依存、受信は未使用 */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFSTS2Conf; /* 割り込み受信用FIFO: 送信は未使用、受信はコンフィグ依存 */

    /* TXQSTSm.TXQIF */
    *(ptChReg->ptu4TXQSTSm) = CAN_u4TXQSTSM_CLEARALL;

    /* THLSTSm.THLIF */
    *(ptChReg->ptu4THLSTSm) = CAN_u4THLSTSM_CLEARALL;

    /* CmERFL.BEF, ALF, BLF, OVLF, BORF, BOEF, EPF, EWF */
    /* バスオフ要因(BOEF)のみ、バスオフ定期処理、または通信停止要求で処置するため */
    /* ここではクリアしない                                                       */
    *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL | CAN_u4CMERFL_BOEF_MSK;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* CmFDSTS.SOCO, EOCO, TDCVF */
    *(ptChReg->ptu4CmFDSTS) = CAN_u4CMFDSTS_CLEARALL;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /*------------------------*/
    /* 割り込みマスクチェック */
    /*------------------------*/
    /* 割り込みマスクを再設定するためにはチャネルモード遷移が必要だが、                                 */
    /* 割り込み処理からモード遷移させた場合、割り込まれる処理側でモードの前提が崩れる可能性があるため、 */
    /* モード遷移はしない。                                                                             */
    /* → 本設計では設定値の化けをチェックし、異常時は割込みの再発の抑制として                          */
    /*    当該チャネルの全割り込み要因(※)をクリアする。                                                */
    /*    その後、フェール定期処理にて上位層にMPU異常を通知し、再初期化されることを期待する。           */
    /*    ※ 未使用割り込み要因はすでにクリア済みのため、ここでは使用割り込み要因をクリアする。         */
    u2TmpTxIntrBit = Can_tb_stTxMbBit[ u1Controller ].u2TxIntrBit;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* 送受信FIFOにリンクされたMBOXは除外する */
    u2TmpTxIntrBit &= Can_tb_u2TxFifoBitMask[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    if ( ( *(ptChReg->ptu2TMIECy)                                             != u2TmpTxIntrBit )
    ||   ( ( *(ptChReg->ptu4CmCTR) & CAN_u4CMCTR_USEDBIT_MSK )                != ( ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_COMM_SET ) )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] & CAN_u4CFCCK_USEDBIT_MSK ) != ptSetRSCANReg->u4CFCC0Conf )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] & CAN_u4CFCCK_USEDBIT_MSK ) != ptSetRSCANReg->u4CFCC1Conf )
    ||   ( ( ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_2 ] & CAN_u4CFCCK_USEDBIT_MSK ) != ptSetRSCANReg->u4CFCC2Conf )
    ||   ( ( *(ptChReg->ptu4TXQCCm) & CAN_u4TXQCCM_USEDBIT_MSK )              != CAN_u4TXQCCM_INIT )
    ||   ( ( *(ptChReg->ptu4THLCCm) & CAN_u4THLCCM_USEDBIT_MSK )              != CAN_u4THLCCM_INIT ) )
    {   /*======== 割り込みマスク値異常時 ========*/
        /* TMSTSp.TMTRF */
        /* 処理を単純にするため、使用未使用によらず全送信MBOXの要因をクリアする。 */
        for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
        {
            ptChReg->ptu1TMSTSp[ u1Idx ] = CAN_u1TMSTSP_TMTRF_CLR;
        }

        /* CFSTSk.CFRXIF */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTSK_CLEARALL; /* 送信用FIFO         */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTSK_CLEARALL; /* 送信用FIFO         */
        ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTSK_CLEARALL; /* 割り込み受信用FIFO */

        /* CmERFL.BOEF */
        *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL;

        /* MPU異常発生を記憶 */
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
    }
}
#endif /* ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_fs_DisableInterrupt                                  */
/* Description   | 割り込み禁止                                             */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・本関数は、コントローラ別の割り込みが起こりえない状況で */
/*               |   割り込みが発生してしまった場合に対し、可能な限り、     */
/*               |   その再発を抑制するための処置を実施する。               */
/*               |   ※ 平常時であれば使用する割り込み要因もクリアする。    */
/*               | ・本関数は、指定されたコントローラで割り込みが起こりえ   */
/*               |   ない状態で呼び出されることを前提とする。               */
/*               | ・パイプライン同期は呼び出し元関数で実施する。           */
/*               | ・本関数呼び出し後、フェール定期処理にてMPU異常を通知し、*/
/*               |   再初期化されることを期待する。                         */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) || (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) )
void
Can_fs_DisableInterrupt( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;       /* チャネルレジスタアドレステーブルへのポインタ */
    uint8                            u1Idx;         /* ループ用インデックス                         */

    /*------------------------------------------------------------------------------------------------*/
    /* 割り込み要因                     要求フラグ         許可ビット    要求フラグの使用／未使用     */
    /*------------------------------------------------------------------------------------------------*/
    /* CANm送信     送信完了            TMSTSp.TMTRF[1:0]  TMIECy.TMIEp  使用(使用MBのみ)             */
    /*              送信アボート        TMSTSp.TMTRF[1:0]  CmCTR.TAIE    使用(使用MBのみ)             */
    /*              送受信 FIFO送信完了 CFSTSk.CFTXIF      CFCCk.CFTXIE  使用(使用FIFOのみ)           */
    /*              送信キュー          TXQSTSm.TXQIF      TXQCCm.TXQIE  未使用                       */
    /*              送信履歴            THLSTSm.THLIF      THLCCm.THLIE  未使用                       */
    /*------------------------------------------------------------------------------------------------*/
    /* CANm送受信FIFO受信完了           CFSTSk.CFRXIF      CFCCk.CFRXIE  使用(使用FIFOのみ)           */
    /*------------------------------------------------------------------------------------------------*/
    /* CANmエラー                       CmERFL.BEF         CmCTR.BEIE    未使用                       */
    /*                                  CmERFL.ALF         CmCTR.ALIE    未使用                       */
    /*                                  CmERFL.BLF         CmCTR.BLIE    未使用                       */
    /*                                  CmERFL.OVLF        CmCTR.OLIE    未使用                       */
    /*                                  CmERFL.BORF        CmCTR.BORIE   未使用                       */
    /*                                  CmERFL.BOEF        CmCTR.BOEIE   使用(バスオフ検出用)         */
    /*                                  CmERFL.EPF         CmCTR.EPIE    未使用                       */
    /*                                  CmERFL.EWF         CmCTR.EWIE    未使用                       */
    /*                    (CAN FDモード)CmFDSTS.SOCO       CmCTR.SOCOIE  未使用                       */
    /*                    (CAN FDモード)CmFDSTS.EOCO       CmCTR.EOCOIE  未使用                       */
    /*                    (CAN FDモード)CmFDSTS.TDCVF      CmCTR.TDCVFIE 未使用                       */
    /*------------------------------------------------------------------------------------------------*/

    /* チャネル別レジスタアドレステーブルのラッチ */
    ptChReg = &Can_tb_stChReg[ u1Controller ];

    /*--------------------*/
    /* 割り込み要因クリア */
    /*--------------------*/
    /* TMSTSp.TMTRF */
    for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
    {
        ptChReg->ptu1TMSTSp[ u1Idx ] = CAN_u1TMSTSP_TMTRF_CLR;
    }

    /* CFSTSk.CFTXIF, CFRXIF */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTSK_CLEARALL; /* 送信用設定FIFO      */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTSK_CLEARALL; /* 送信用設定FIFO      */
    ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTSK_CLEARALL; /* 割り込み受信用FIFO  */

    /* TXQSTSm.TXQIF */
    *(ptChReg->ptu4TXQSTSm) = CAN_u4TXQSTSM_CLEARALL;

    /* THLSTSm.THLIF */
    *(ptChReg->ptu4THLSTSm) = CAN_u4THLSTSM_CLEARALL;

    /* CmERFL.BEF, ALF, BLF, OVLF, BORF, BOEF, EPF, EWF */
    *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* CmFDSTS.SOCO, EOCO, TDCVF */
    *(ptChReg->ptu4CmFDSTS) = CAN_u4CMFDSTS_CLEARALL;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /*----------------*/
    /* 割り込みマスク */
    /*----------------*/
    /* 割り込みマスクを再設定するためにはチャネルモード遷移が必要だが、                                 */
    /* 割り込み処理からモード遷移させた場合、割り込まれる処理側でモードの前提が崩れる可能性があるため、 */
    /* モード遷移はしない。                                                                             */
    /* → 本設計での割込みの再発の抑制は、当該チャネルの全割り込み要因をクリアするまでとする。          */
    /*    その後、フェール定期処理にて上位層にMPU異常を通知し、再初期化されることを期待する。           */

    /*-------------*/
    /* MPU異常通知 */
    /*-------------*/
    Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
}
#endif /* ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) || (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_fs_GetErrorStatus                                    */
/* Description   | CANプロトコルエラー状態取得                              */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   CANプロトコルエラー状態取得を実施するCANコントローラ   */
/* Return Value  | uint8 CANプロトコルエラー状態取得結果                    */
/*               |   CAN_ERRST_NOT_OK        : エラー状態取得失敗(なし)     */
/*               |   CAN_ERRST_ERROR_ACTIVE  : エラーアクティブ             */
/*               |   CAN_ERRST_ERROR_PASSIVE : エラーパッシブ               */
/*               |   CAN_ERRST_BUS_OFF       : バスオフ                     */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
uint8
Can_fs_GetErrorStatus( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;       /* チャネルレジスタアドレステーブルへのポインタ */
    uint32                         u4CMSTSTmp;    /* CMSTSレジスタラッチ用                        */
    uint8                          u1Ret;         /* 戻り値                                       */

    ptChReg = &Can_tb_stChReg[ u1Controller ];
    u4CMSTSTmp = *(ptChReg->ptu4CmSTS) & CAN_FS_u4CMSTSCHK_MASK_ERRSTS;

    /* CANプロトコルエラー状態取得結果判定 */
    if ( u4CMSTSTmp == CAN_FS_u4ERRACTIVE )
    {
        /* エラーアクティブの場合 */
        u1Ret = (uint8)CAN_ERRST_ERROR_ACTIVE;
    }
    else if ( u4CMSTSTmp == CAN_FS_u4ERRPASSIVE )
    {
        /* エラーパッシブの場合 */
        u1Ret = (uint8)CAN_ERRST_ERROR_PASSIVE;
    }
    else
    {
        /* バスオフの場合 */
        u1Ret = (uint8)CAN_ERRST_BUS_OFF;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PhyInit                                           */
/* Description   | フェールセーフ機能(マイコン依存)初期化                   */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_PhyInit( void )
{
    uint8    u1Controller;       /* ループ用コントローラID */
    uint8    u1CtrlNum;          /* コントローラ数         */

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        /* レジスタ固着チェック受付状態を固着チェック待機中として初期化 */
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;

        /* MPU異常発生有無をMPU異常なしとして初期化 */
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_NONE;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_ChkParameter                                      */
/* Description   | 通信パラメータチェック                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   通信パラメータチェックを実施するCANコントローラ        */
/* Return Value  | uint8 通信パラメータチェック結果                         */
/*               |   CAN_NONE         : パラメータ異常なし                  */
/*               |   CAN_EXIST        : パラメータ異常あり                  */
/* Notes         | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
uint8
Can_fs_ChkParameter( uint8 u1Controller )
{
#if (CAN_CFG_PARAM_CHECK == CAN_USE)
    CanConst CanTbChRegType *        ptChReg;           /* チャネルレジスタアドレステーブルへのポインタ */
    CanConst CanTbSetRSCANRegType *  ptSetRSCANReg;     /* RSCANレジスタテーブルへのポインタ            */
    uint32                           u4DCS;             /* GCFG.DCSレジスタラッチ用                     */
    uint32                           u4DCSConfTmp;      /* GCFG.DCSコンフィグ値ラッチ用                 */
    uint32                           u4CmCFG;           /* CmCFGレジスタラッチ用                        */
    uint32                           u4CmCFGConfTmp;    /* CmCFGレジスタコンフィグ値ラッチ用            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                           u4CmDCFG;          /* CmDCFGレジスタラッチ用                       */
    uint32                           u4CmDCFGConfTmp;   /* CmDCFGレジスタコンフィグ値ラッチ用           */
    uint32                           u4CmFDCFG;         /* CmFDCFGレジスタラッチ用                      */
    uint32                           u4CmFDCFGConfTmp;  /* CmFDCFGレジスタコンフィグ値ラッチ用          */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_PARAM_CHECK == CAN_USE) */
    uint8                            u1Ret;             /* 戻り値                                       */

    u1Ret = (uint8)CAN_NONE;

#if (CAN_CFG_PARAM_CHECK == CAN_USE)

    /* 通信速度設定に関連するレジスタのうち、Canソフト内で    */
    /* 制御対象としているレジスタは、全てチェック対象とする。 */

    /* CANクロック源選択ビットの確認 */
    u4DCS        = *( Can_tb_stGlobalReg.ptu4GCFG ) & CAN_u4GCFG_DCS_MSK;
    u4DCSConfTmp = Can_tb_u4GCFGConf & CAN_u4GCFG_DCS_MSK;
    if ( u4DCS != u4DCSConfTmp )
    {
        /* CANクロック源異常あり                                       */
        /* ※ グローバルレジスタの故障であるため                       */
        /*    別コントローラに対するChkParameterも一律異常ありとなる。 */
        u1Ret = (uint8)CAN_EXIST;
    }

    /* チャネル別レジスタアドレステーブルのラッチ */
    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    /* チャネル別RSCANレジスタ設定値テーブルのラッチ */
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    /* クラシカルCANモード：チャネルコンフィグレーションレジスタ(CmCFG)                  */
    /* CAN FDモード       ：チャネル通常ビットレートコンフィグレーションレジスタ(CmNCFG) */
    u4CmCFG        = *(ptChReg->ptu4CmCFG) & CAN_FS_u4PARAMCHK_CMCFG_MASK;
    u4CmCFGConfTmp = ptSetRSCANReg->u4CmCFGConf & CAN_FS_u4PARAMCHK_CMCFG_MASK;
    if( u4CmCFG != u4CmCFGConfTmp )
    {
        /* 通信パラメータチェック結果が不一致の場合 */
        u1Ret = (uint8)CAN_EXIST;
    }

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* チャネルデータビットレートコンフィグレーションレジスタ(CmDCFG) */
    u4CmDCFG        = *(ptChReg->ptu4CmDCFG) & CAN_FS_u4PARAMCHK_CMDCFG_MASK;
    u4CmDCFGConfTmp = ptSetRSCANReg->u4CmDCFGConf & CAN_FS_u4PARAMCHK_CMDCFG_MASK;

    /* チャネルCAN FDコンフィグレーションレジスタ(CmFDCFG)   */
    /* 送信遅延補償機能に関するビット(TDCO,TDCE,TDCOC)を確認 */
    u4CmFDCFG        = *(ptChReg->ptu4CmFDCFG) & CAN_FS_u4PARAMCHK_CMFDCFG_MASK;
    u4CmFDCFGConfTmp = ptSetRSCANReg->u4CmFDCFGConf & CAN_FS_u4PARAMCHK_CMFDCFG_MASK;

    if( ( u4CmDCFG  != u4CmDCFGConfTmp  )
    ||  ( u4CmFDCFG != u4CmFDCFGConfTmp ) )
    {
        /* 通信パラメータチェック結果が不一致の場合 */
        u1Ret = (uint8)CAN_EXIST;
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_PARAM_CHECK == CAN_USE) */

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PhyPrepChkRegRetry                                */
/* Description   | 物理層レジスタ固着チェックリトライ準備処理               */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller :                                     */
/*               |   レジスタ固着チェックリトライ準備処理を                 */
/*               |   実施するCANコントローラ                                */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_PhyPrepChkRegRetry( uint8 u1Controller )
{
    uint8    u1RegChkStatus;    /* レジスタ固着チェック受付状態 */
    uint8    u1Idx;             /* ループ用インデックス         */
    uint8    u1CtrlNum;         /* コントローラ数               */

    /* 固着チェック完了(固着あり)後最初に呼び出されたチャネル、もしくは */
    /* リトライ前のチェックが完了していない場合はリトライ前の代表Chを   */
    /* リトライ後の代表Chとする。                                       */
    /* それ以降は本関数が呼び出されても何もしない。                     */
    /* 状態が化けていた場合はリトライせずにCan_fs_ChkRegでNGを返し続け  */
    /* 初期化異常扱いとなることを期待する。                             */
    u1RegChkStatus = Can_fs_u1RegChkStatus[ u1Controller ];
    if ( ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_WAIT )
    ||   ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_NG   ) )
    {
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_PASS;
        }
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_MpuFailInd                                        */
/* Description   | MPU異常検出通知                                          */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | なし                                                     */
/****************************************************************************/
void
Can_fs_MpuFailInd( uint8 u1Controller )
{
    Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_IllegalInterrupt                                  */
/* Description   | 不正割り込み共通処理                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・グローバルストップモードで本関数が呼び出される事は     */
/*               |   ない前提とし、それ以外のグローバル状態で割り込みが     */
/*               |   生じた場合の割り込み抑制処置を実施する。               */
/*               |   ※ 本ソフトの設計上、グローバルストップモードは電源ON  */
/*               |      リセット直後、またはシャットダウン後の状態である。  */
/*               |      電源ON直後の場合、HW初期値上割り込みは起こりえず、  */
/*               |      シャットダウン後であれば、ソフト上可能な割り込み抑制*/
/*               |      処置は実施済みであるため。                          */
/****************************************************************************/
#if (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE)
static void
Can_fs_IllegalInterrupt( uint8 u1Controller )
{
    volatile uint32                      u4DummyRead;   /* レジスタのダミーリード用 */

    /* 割り込みを禁止する */
    Can_fs_DisableInterrupt( u1Controller );

    /* パイプライン同期(ダミーリード＋SYNCP) */
    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
    Can_tb_SYNCP();
}
#endif /* (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_fs_RAMTest                                           */
/* Description   | RAMテスト                                                */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Time        : 指定回数（n回目のチェック実施）    */
/* Return Value  | uint8 RAMテスト結果                                      */
/*               |   CAN_FS_RAMTEST_OK :RAMテスト異常なし(テスト継続中)     */
/*               |   CAN_FS_RAMTEST_NG :RAMテスト異常あり                   */
/*               |   CAN_FS_RAMTEST_FIN:RAMテスト完了                       */
/* Notes         | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/*               | ・本APIは、レジスタ固着チェックの代表Chに指定されたCh    */
/*               |   からのみ呼び出される。                                 */
/*               |   代表Chとは、Canの初期化後「Can_CheckStuckRegister」が  */
/*               |   最初に呼び出された時に指定されたCANコントローラを指す。*/
/****************************************************************************/
static uint8
Can_fs_RAMTest( uint8 u1Time )
{
    uint8  u1TargetPage;         /* 固着チェック対象ページ */
    uint8  u1StartPage;          /* 固着チェック開始ページ */
    uint8  u1ChkPage;            /* 固着チェックページ数   */
    uint8  u1LastPage;           /* 固着チェック最終ページ */
    uint8  u1RAMTestModeChgRet;  /* RAMテスト許可成否      */
    uint8  u1Cnt;                /* ループ用カウンタ       */
    uint8  u1Ret;                /* 戻り値                 */

    /* 戻り値をRAMテスト異常なしで初期化 */
    u1Ret = (uint8)CAN_FS_RAMTEST_OK;

    /* RAMテスト許可設定 */
    u1RAMTestModeChgRet = Can_fs_RAMTestEnable();
    if ( u1RAMTestModeChgRet == (uint8)CAN_PROC_OK )
    {
        /* RAMテスト許可成功 */

        /* u1Timeに応じた固着チェック開始ページ、チェックページ数の取り出し */
        u1StartPage = Can_tb_stCheckStuckPara[ u1Time ].u1StChkStart;
        u1ChkPage   = Can_tb_stCheckStuckPara[ u1Time ].u1StChkPage;

        /* RAMテスト実施#1(指定ページの全領域テスト) */
        for ( u1Cnt = (uint8)0U; ( ( u1Cnt < u1ChkPage ) && ( u1Ret == (uint8)CAN_FS_RAMTEST_OK ) ); u1Cnt++ )
        {
            u1TargetPage = (uint8)( u1StartPage + u1Cnt );
            u1Ret        = Can_fs_RAMTestPage( u1TargetPage, (uint8)CAN_FS_RAMTEST_DATANUM_MAX );
        }

        /* RAMテスト実施#2(指定ページ内の有効領域分テスト)(※最終ページの場合のみ発生) */
        u1TargetPage = (uint8)( u1StartPage + u1ChkPage );
        u1LastPage   = Can_tb_u1LastTestpage;
        if ( u1TargetPage == u1LastPage )
        {
            if ( u1Ret == (uint8)CAN_FS_RAMTEST_OK )
            {
                u1Ret = Can_fs_RAMTestPage( u1TargetPage, Can_tb_u1LastTestpageRegNum );
                if ( u1Ret == (uint8)CAN_FS_RAMTEST_OK )
                {
                    /* RAMテスト完了(成功) */
                    u1Ret = (uint8)CAN_FS_RAMTEST_FIN;
                }
            }
        }
    }
    else
    {
        /* RAMテスト許可失敗時: 固着発生と同様に失敗扱いとする */
        u1Ret = (uint8)CAN_FS_RAMTEST_NG;
    }

    /* RAMテスト禁止設定 */
    u1RAMTestModeChgRet = Can_fs_RAMTestDisable();
    if ( u1RAMTestModeChgRet != (uint8)CAN_PROC_OK )
    {
        /* RAMテスト禁止失敗時(テスト前の状態に戻せなかった場合) : 固着発生と同様に失敗扱いとする */
        u1Ret = (uint8)CAN_FS_RAMTEST_NG;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestPage                                       */
/* Description   | ページ指定RAMテスト                                      */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1TargetPage   : RAMテスト対象ページ               */
/*               | uint8 u1ElmNum       : テスト対象要素数                  */
/* Return Value  | uint8 RAMテスト結果                                      */
/*               |   CAN_FS_RAMTEST_OK  :RAMテスト異常なし(テスト継続中)    */
/*               |   CAN_FS_RAMTEST_NG  :RAMテスト異常あり                  */
/* Notes         | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルテストモード                                */
/****************************************************************************/
static uint8
Can_fs_RAMTestPage( uint8 u1TargetPage, uint8 u1ElmNum )
{
    volatile uint32 *   ptRDATA;        /* RAMデータへのアクセスポインタ(テスト対象) */
    uint8               u1Idx;          /* ループ用インデックス                      */
    uint8               u1Ret;          /* 戻り値                                    */

    /* RAMテスト対象ページ指定 */
    *(Can_tb_stGlobalReg.ptu4GTSTCFG) = (uint32)( ( (uint32)u1TargetPage << CAN_SFT_16 ) & CAN_u4GTSTCFG_RTMPS_MSK );

    /* 戻り値をRAMテスト異常なしで初期化 */
    /* ※ テスト範囲がなかった場合もOKとする */
    u1Ret = (uint8)CAN_FS_RAMTEST_OK;

    /* 指定終了位置まで繰り返し */
    /* 異常検出時は処理終了     */
    for ( u1Idx = (uint8)0U; ( ( u1Idx < u1ElmNum ) && ( u1Ret == (uint8)CAN_FS_RAMTEST_OK ) ); u1Idx++ )
    {
        /* テスト対象RAMデータのアドレスを取得 */
        ptRDATA = &(Can_tb_stGlobalReg.ptu4RPGACCr[ u1Idx ]);

        /* チェックパターン1 : AAAAAAAAH */
        /* チェックパターン1書き込み */
        *ptRDATA = CAN_FS_u4REGCHK_PTN1;

        /* レジスタ固着の確認 */
        if ( *ptRDATA != CAN_FS_u4REGCHK_PTN1 )
        {
            u1Ret = (uint8)CAN_FS_RAMTEST_NG;
        }
        else
        {
            /* チェックパターン2 : 55555555H */
            /* チェックパターン2書き込み */
            *ptRDATA = CAN_FS_u4REGCHK_PTN2;

            /* レジスタ固着の確認 */
            if ( *ptRDATA != CAN_FS_u4REGCHK_PTN2 )
            {
                u1Ret = (uint8)CAN_FS_RAMTEST_NG;
            }
            else
            {
                /* ゼロクリア(異常なし時)                              */
                /* マイコン制約に従いRAMテスト終了前にゼロクリアする。 */
                /* ただし、異常検出時は故障解析のため書き戻ししない。  */
                *ptRDATA = CAN_u4BIT_NONE;
            }
        }
    }
    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestEnable                                     */
/* Description   | RAMテスト許可設定                                        */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | uint8 RAMテスト許可の成否                                */
/*               |   CAN_PROC_OK      : RAMテスト許可成功                   */
/*               |   CAN_PROC_NG      : RAMテスト許可失敗                   */
/* Notes         | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルリセットモード                              */
/*               |  - グローバル動作モード                                  */
/****************************************************************************/
static uint8
Can_fs_RAMTestEnable( void )
{
    uint8  u1CheckCount;          /* プロテクト解除 リトライ回数 */
    uint8  u1Ret;                 /* 戻り値                      */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_NG;

    /* グローバルリセットモード遷移 */
    /* RAM化け発生時、既に他chが通信開始している可能性を考慮し、一度リセットモードへ遷移させる。  */
    /* その場合、既に通信開始しているchは通信が停止するため、上位層の送信ロック検出～復旧を期待。 */
    Can_st_GlobalMode_Any2Reset();

    /* グローバルテストモード遷移 */
    Can_st_GlobalMode_Reset2Test();

    if ( ( *(Can_tb_stGlobalReg.ptu4GSTS) & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_TEST )
    {
        /* グローバルテストモードに遷移できた場合 */

        /* RAMテスト許可 */
        /* 許可ビット設定処理後、設定反映されるまでリトライ */
        for ( u1CheckCount = (uint8)0U; ( ( u1CheckCount < (uint8)CAN_FS_RAMTEST_PROTECT_COUNT ) && ( u1Ret != (uint8)CAN_PROC_OK ) ); u1CheckCount++ )
        {
            /* RAMテスト許可ビットのプロテクト解除 */
            *(Can_tb_stGlobalReg.ptu4GLOCKK) = CAN_u4GLOCKK_LOCK_RELKEY1;
            *(Can_tb_stGlobalReg.ptu4GLOCKK) = CAN_u4GLOCKK_LOCK_RELKEY2;

            /* RAMテスト許可ビット設定 */
            *(Can_tb_stGlobalReg.ptu4GTSTCTR) = CAN_u4GTSTCTR_RTME_ENA;

            /* 設定結果確認 */
            if ( ( *( Can_tb_stGlobalReg.ptu4GTSTCTR ) & CAN_u4GTSTCTR_RTME_MSK ) == CAN_u4GTSTCTR_RTME_ENA )
            {
                /* RAMテスト許可成功 */
                u1Ret = (uint8)CAN_PROC_OK;
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestDisable                                    */
/* Description   | RAMテスト禁止設定                                        */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | uint8 RAMテスト禁止の成否                                */
/*               |   CAN_PROC_OK      : RAMテスト禁止成功                   */
/*               |   CAN_PROC_NG      : RAMテスト禁止失敗                   */
/* Notes         | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバルテストモード                                */
/*               |  - グローバル動作モード(テストモード遷移失敗時のみ)      */
/*               |  - グローバルリセットモード(テストモード遷移失敗時のみ)  */
/****************************************************************************/
static uint8
Can_fs_RAMTestDisable( void )
{
    uint8  u1Ret;                 /* 戻り値 */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_NG;

    /* RAMテスト禁止 */
    /* ※ 以降のグローバルリセットモード遷移によっても */
    /*    RAMテスト禁止となるが、明示的に実施しておく  */
    *(Can_tb_stGlobalReg.ptu4GTSTCTR) = ( CAN_u4GTSTCTR_RTME_DIS | CAN_u4GTSTCTR_ICBCTME_DIS );

    /* グローバルリセットモード遷移 */
    Can_st_GlobalMode_Any2Reset();

    /* モード遷移確認 */
    if ( ( *(Can_tb_stGlobalReg.ptu4GSTS) & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        /* RAMテスト禁止成功 */
        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
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
