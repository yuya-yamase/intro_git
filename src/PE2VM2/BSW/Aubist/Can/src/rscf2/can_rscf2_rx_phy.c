/* can_rscf2_rx_phy_c_m10700_v2-2-1                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/RX/PHYSICAL/CODE                                */
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
#if (CAN_CFG_RECEIVE == CAN_USE)
#include <can/rscf2/can_rscf2_tb_phy.h>
#include <can/rscf2/can_rscf2_rx.h>
#include <can/rscf2/can_rscf2_fs.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_RX_DLC_NUM                  ( 16U )            /* DLCパターン数             */
#define CAN_RX_ID_FDF_CANFD             ( 0x40000000UL )   /* CAN IDのFDFビットがCAN FD */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE)
static void Can_rx_RxFinish( uint8 u1Controller );
#endif /* (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) */
static uint8 Can_rx_ChkRxFinMboxInt( uint8 u1Controller );
static uint8 Can_rx_ChkRxFinMboxPol( uint8 u1Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* データ長への変換用テーブル */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
static CanConst uint8 Can_rx_u1DataLengthVal[CAN_RX_DLC_NUM] = { (uint8)0U ,(uint8)1U  ,(uint8)2U  ,(uint8)3U  ,(uint8)4U  ,(uint8)5U  ,(uint8)6U  ,(uint8)7U
                                                                ,(uint8)8U ,(uint8)12U ,(uint8)16U ,(uint8)20U ,(uint8)24U ,(uint8)32U ,(uint8)48U ,(uint8)64U };
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_RxFinish_0                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_0 == CAN_USE)
void
Can_RxFinish_0( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_0 );
}
#endif /* (CAN_RX_RXFINISH_USE_0 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_1                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_1 == CAN_USE)
void
Can_RxFinish_1( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_1 );
}
#endif /* (CAN_RX_RXFINISH_USE_1 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_2                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_2 == CAN_USE)
void
Can_RxFinish_2( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_2 );
}
#endif /* (CAN_RX_RXFINISH_USE_2 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_3                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_3 == CAN_USE)
void
Can_RxFinish_3( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_3 );
}
#endif /* (CAN_RX_RXFINISH_USE_3 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_4                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_4 == CAN_USE)
void
Can_RxFinish_4( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_4 );
}
#endif /* (CAN_RX_RXFINISH_USE_4 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_5                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_5 == CAN_USE)
void
Can_RxFinish_5( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_5 );
}
#endif /* (CAN_RX_RXFINISH_USE_5 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_6                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_6 == CAN_USE)
void
Can_RxFinish_6( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_6 );
}
#endif /* (CAN_RX_RXFINISH_USE_6 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_7                                           */
/* Description   | 受信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる受信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_7 == CAN_USE)
void
Can_RxFinish_7( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_7 );
}
#endif /* (CAN_RX_RXFINISH_USE_7 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_rx_ChkRxFinMbox                                      */
/* Description   | MBOX受信完了確認                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/*               | uint8 u1Kind       : 検索対象種別(INTR/POLL）            */
/* Return Value  | uint8 MBOX受信完了確認結果                               */
/*               |   CAN_EXIST        : 受信完了あり                        */
/*               |   CAN_NONE         : 受信完了なし                        */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
uint8
Can_rx_ChkRxFinMbox( uint8 u1Controller, uint8 u1Kind )
{
    uint8 u1Ret; /* 戻り値 */

    if ( u1Kind == (uint8)CAN_INTERRUPT )
    {   /* 検索対象メッセージが割り込み受信の場合 */
        u1Ret = Can_rx_ChkRxFinMboxInt( u1Controller );
    }
    else
    {   /* 検索対象メッセージがポーリング受信の場合 */
        u1Ret = Can_rx_ChkRxFinMboxPol( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_rx_RxFinish                                          */
/* Description   | 受信完了割り込み共通処理                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/****************************************************************************/
#if (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE)
static void
Can_rx_RxFinish( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;     /* チャネルレジスタアドレステーブルへのポインタ   */
    volatile uint32                u4DummyRead; /* レジスタのダミーリード用                       */
    uint32                         u4CmSTS;     /* チャネルステータスレジスタ(CmSTS)ラッチ用      */
    uint8                          u1RxResult;  /* 受信完了確認の戻り値                           */

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* チャネルステータスレジスタ(CmSTS)の値を取得 */
    u4CmSTS = *( ptChReg->ptu4CmSTS );

    /* チャネル通信モードかチェック */
    /* チャネル通信モードの場合、必ずグローバル動作モードのためグローバルモードはチェックしない */
    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {   /*=================== チャネル通信モード ===================*/

       /* FIFOを使用しているため、本受信処理中に発生した新規受信の取りこぼしの心配はない */
       /* Can_rx_ChkRxFinMbox内で受信割り込み要求フラグのクリアは実施する                */

        /* 受信完了割り込み確認 */
        u1RxResult = Can_rx_ChkRxFinMbox( u1Controller, (uint8)CAN_INTERRUPT );

        /* 受信完了の有無チェック */
        if ( u1RxResult != (uint8)CAN_EXIST )
        {
            /* 受信完了したデータが存在しなかった場合、割り込み設定をリフレッシュする */
            Can_fs_ResetInterrupt( u1Controller );
        }
    }
    else
    {   /*========== チャネル待機/リセット/ストップモード ==========*/

        /* チャネル通信モード以外の場合、不正割り込みと判断 */
        Can_fs_DisableInterrupt( u1Controller );
    }

    /* パイプライン同期(ダミーリード＋SYNCP) */
    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
    Can_tb_SYNCP();
}
#endif /* (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_rx_ChkRxFinMboxInt                                   */
/* Description   | MBOX割り込み受信完了確認                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 MBOX割り込み受信完了確認結果                       */
/*               |   CAN_EXIST        : 受信完了あり                        */
/*               |   CAN_NONE         : 受信完了なし                        */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
static uint8
Can_rx_ChkRxFinMboxInt( uint8 u1Controller )
{
    CanMsgType                      stMsg;               /* 受信メッセージ格納用一時バッファ             */
    volatile CanTbRegCANCFType *    ptMb;                /* MBOXへのポインタ                             */
    CanConst CanTbChRegType*        ptChReg;             /* チャネルレジスタアドレステーブルへのポインタ */
    uint32                          u4Data[ CAN_TB_RX_MB_DATA_ARYSIZE ]; /* 受信データ取得用             */
    uint32                          u4IdVal;             /* CAN ID                                       */
    uint32                          u4CFSTSk;            /* 送受信FIFO バッファステータスレジスタ(CFSTSk)ラッチ用                        */
    uint32                          u4CFIDk;             /* 送受信FIFO バッファアクセスID レジスタ(CFIDk)ラッチ用                        */
    uint32                          u4CFPTRk;            /* 送受信FIFO バッファアクセスポインタレジスタ(CFPTRk)ラッチ用                  */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                          u4FDCSTSk;           /* 送受信FIFO CAN FD コンフィグレーション／ステータスレジスタ(CFFDCSTS)ラッチ用 */
    uint8                           u1Dlc;               /* DLC                                          */
    uint8                           u1DataReadSize;      /* データの読み出しサイズ                       */
    uint8                           u1Idx;               /* ループ用インデックス                         */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                           u1DataLength;        /* データ長                                     */
    uint8                           u1MsgNum;            /* 受信メッセージ数ラッチ用                     */
    uint8                           u1Count;             /* 送受信FIFOループ用カウンタ                   */
    uint8                           u1Mbox;              /* MBOX番号                                     */
    uint8                           u1Ret;               /* 戻り値                                       */

    /* 戻り値をCAN_NONEに初期化 */
    u1Ret = (uint8)CAN_NONE;

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &(Can_tb_stChReg[ u1Controller ]);

    /* 送受信FIFO 受信割り込み要求フラグのクリア */
    ptChReg->ptu4CFSTSk[ CAN_CFTYPE_RX_INT ] = CAN_u4CFSTSK_CFRXIF_CLR;

    /* 送受信FIFO バッファステータスレジスタ(CFSTSk)の値を取得 */
    u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_CFTYPE_RX_INT ];

    /* 受信メッセージ数を取得 */
    u1MsgNum = (uint8)( ( u4CFSTSk & CAN_u4CFSTSK_CFMC_MSK ) >> CAN_SFT_8 );

    /* 受信メッセージのアドレス取得 */
    ptMb = &( ptChReg->ptstCF[ CAN_CFTYPE_RX_INT ] );

    /* 処理速度向上のためポインタのキャストを使用 */
    stMsg.ptData = (uint8 *)&( u4Data[ CAN_IDX0 ] ); /* アラインメント、及びエンディアンの不整合がない事を確認済み */

    /* 受信完了メッセージ検索 */
    for ( u1Count = (uint8)0U; u1Count < u1MsgNum; u1Count++ )
    {
        /* 受信メッセージ格納(送受信FIFO バッファ関連レジスタ) */
        u4CFIDk   = ptMb->u4IDReg;
        u4CFPTRk  = ptMb->u4PTRReg;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        u4FDCSTSk = ptMb->u4FDCSTSReg;

        if ( ( u4FDCSTSk & CAN_u4CFFDCSTSK_CFFDF_MSK ) == CAN_u4CFFDCSTSK_CFFDF_CANFD )
        {   /* CAN FDフレームの場合    */
            /* データフィールドの読み出し回数を設定 */
            u1DataReadSize = Can_tb_u1FifoReadSizeInt[ u1Controller ];

            /* 受信データを格納 */
            for ( u1Idx = (uint8)0U; u1Idx < u1DataReadSize; u1Idx++ )
            {
                u4Data[ u1Idx ] = ptMb->u4DFReg[ u1Idx ];
            }

            /* 送受信FIFO バッファポインタ制御レジスタ(CFPCTRk)を制御しリードポインタを移動 */
            /* 取得処理中にFIFOがフルにならないようにデータを取得後に即座に更新する         */
            ptChReg->ptu4CFPCTRk[ CAN_CFTYPE_RX_INT ] = CAN_u4CFPCTRK_CFPC_SET;

            /* 送受信FIFO バッファアクセスID レジスタ(CFIDk)から読みだした値をIDに整形 */
            /* CAN FDフレームはメッセージIDのLSBから30bit目にCAN FDフレームの情報付与  */
            u4IdVal      = ( ( u4CFIDk & CAN_u4CFIDK_EID_MSK ) | CAN_RX_ID_FDF_CANFD );

            /* 送受信FIFO バッファアクセスポインタレジスタ(CFPTRk)から読みだした値をDLCに整形 */
            u1Dlc        = (uint8)( ( u4CFPTRk & CAN_u4CFPTRK_CFDLC_MSK ) >> CAN_SFT_28 );

            /* DLCをデータ長に変換 */
            u1DataLength = Can_rx_u1DataLengthVal[ u1Dlc ];
        }
        else
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        {   /* CANフレームの場合       */
            /* 受信データ 00-07 を格納 */
            u4Data[ CAN_IDX0 ] = ptMb->u4DFReg[ CAN_IDX0 ];
            u4Data[ CAN_IDX1 ] = ptMb->u4DFReg[ CAN_IDX1 ];

            /* 送受信FIFO バッファポインタ制御レジスタ(CFPCTRk)を制御しリードポインタを移動 */
            /* 取得処理中にFIFOがフルにならないようにデータを取得後に即座に更新する         */
            ptChReg->ptu4CFPCTRk[ CAN_CFTYPE_RX_INT ] = CAN_u4CFPCTRK_CFPC_SET;

            /* 送受信FIFO バッファアクセスID レジスタ(CFIDk)から読みだした値をIDに整形 */
            u4IdVal      = u4CFIDk & CAN_u4CFIDK_EID_MSK;

            /* 送受信FIFO バッファアクセスポインタレジスタ(CFPTRk)から読みだした値をDLCに整形 */
            /* クラシカルCANフレームはDLCをデータ長として扱う                                 */
            u1DataLength = (uint8)( ( u4CFPTRk & CAN_u4CFPTRK_CFDLC_MSK ) >> CAN_SFT_28 );
        }

        /* 受信メッセージ格納用一時バッファへID,データ長を格納 */
        stMsg.u4Id     = u4IdVal;
        stMsg.u1Length = u1DataLength;

        /* 通過フィルタよりMBOXを算出 */
        u1Mbox = (uint8)( ( u4CFPTRk & CAN_u4CFPTRK_CFPTR_MSK ) >> CAN_SFT_16 );

        /* 取得メッセージをCAN共通部へ通知 */
        Can_rx_RxIndMbox( u1Controller, u1Mbox, &stMsg );

        u1Ret = (uint8)CAN_EXIST;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_rx_ChkRxFinMboxPol                                   */
/* Description   | MBOXポーリング受信完了確認                               */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | uint8 MBOXポーリング受信完了確認結果                     */
/*               |   CAN_EXIST        : 受信完了あり                        */
/*               |   CAN_NONE         : 受信完了なし                        */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
static uint8
Can_rx_ChkRxFinMboxPol( uint8 u1Controller )
{
    CanMsgType                      stMsg;               /* 受信メッセージ格納用一時バッファ             */
    volatile CanTbRegCANRFType *    ptMb;                /* MBOXへのポインタ                             */
    uint32                          u4Data[ CAN_TB_RX_MB_DATA_ARYSIZE ]; /* 受信データ取得用             */
    uint32                          u4IdVal;             /* CAN ID                                       */
    uint32                          u4RFSTSx;            /* 受信FIFO バッファステータスレジスタ(RFSTSx)ラッチ用       */
    uint32                          u4RFIDx;             /* 受信FIFO バッファアクセスID レジスタ(RFIDx)ラッチ用       */
    uint32                          u4RFPTRx;            /* 受信FIFO バッファアクセスポインタレジスタ(RFPTRx)ラッチ用 */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                          u4FDSTSx;            /* 受信FIFO CAN FD ステータスレジスタ(RFFDSTSx)ラッチ用      */
    uint8                           u1Dlc;               /* DLC                                          */
    uint8                           u1DataReadSize;      /* データの読み出しサイズ                       */
    uint8                           u1Idx;               /* ループ用インデックス                         */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                           u1DataLength;        /* データ長                                     */
    uint8                           u1MsgNum;            /* 受信メッセージ数ラッチ用                     */
    uint8                           u1Count;             /* 受信FIFOループ用カウンタ                     */
    uint8                           u1Mbox;              /* MBOX番号                                     */
    uint8                           u1Ret;               /* 戻り値                                       */

    /* 戻り値をCAN_NONEに初期化 */
    u1Ret = (uint8)CAN_NONE;

    /* 受信FIFO 受信割り込み要求フラグのクリア */
    Can_tb_stGlobalReg.ptu4RFSTSx[ u1Controller ] = CAN_u4RFSTSX_RFIF_CLR;

    /* 受信FIFO バッファステータスレジスタ(RFSTSx)の値を取得 */
    u4RFSTSx = Can_tb_stGlobalReg.ptu4RFSTSx[ u1Controller ];

    /* 受信メッセージ数を取得 */
    u1MsgNum = (uint8)( ( u4RFSTSx & CAN_u4RFSTSX_RFMC_MSK ) >> CAN_SFT_8 );

    /* 受信メッセージのアドレス取得 */
    ptMb = &( Can_tb_stGlobalReg.ptstRF[ u1Controller ] );

    /* 処理速度向上のためポインタのキャストを使用 */
    stMsg.ptData = (uint8 *)&( u4Data[ CAN_IDX0 ] ); /* MISRA DEVIATION: アラインメント、及びエンディアンの不整合がない事を確認済み */

    /* 受信完了メッセージ検索 */
    for ( u1Count = (uint8)0U; u1Count < u1MsgNum; u1Count++ )
    {
        /* 受信メッセージ格納(受信FIFO バッファ関連レジスタ) */
        u4RFIDx  = ptMb->u4IDReg;
        u4RFPTRx = ptMb->u4PTRReg;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        u4FDSTSx = ptMb->u4FDSTSReg;

        if ( ( u4FDSTSx & CAN_u4RFFDSTSX_RFFDF_MSK ) == CAN_u4RFFDSTSX_RFFDF_CANFD )
        {   /* CAN FDフレームの場合    */
            /* データフィールドの読み出し回数を設定 */
            u1DataReadSize = Can_tb_u1FifoReadSizePol[ u1Controller ];

            /* 受信データを格納 */
            for ( u1Idx = (uint8)0U; u1Idx < u1DataReadSize; u1Idx++ )
            {
                u4Data[ u1Idx ] = ptMb->u4DFReg[ u1Idx ];
            }

            /* 受信FIFO バッファポインタ制御レジスタ(RFPCTRx)を制御しリードポインタを移動 */
            /* 取得処理中にFIFOがフルにならないようにデータを取得後に即座に更新する       */
            Can_tb_stGlobalReg.ptu4RFPCTRx[ u1Controller ] = CAN_u4RFPCTRX_RFPC_SET;

            /* 受信FIFO バッファアクセスID レジスタ(RFIDx)から読みだした値をIDに整形  */
            /* CAN FDフレームはメッセージIDのLSBから30bit目にCAN FDフレームの情報付与 */
            u4IdVal      = ( ( u4RFIDx & CAN_u4RFIDX_ID_MSK ) | CAN_RX_ID_FDF_CANFD );

            /* 受信FIFO バッファアクセスポインタレジスタ(RFPTRx)から読みだした値をDLCに整形 */
            u1Dlc        = (uint8)( ( u4RFPTRx & CAN_u4RFPTRX_RFDLC_MSK ) >> CAN_SFT_28 );

            /* DLCをデータ長に変換 */
            u1DataLength = Can_rx_u1DataLengthVal[ u1Dlc ];
        }
        else
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        {   /* CANフレームの場合       */
            /* 受信データ 00-07 を格納 */
            u4Data[ CAN_IDX0 ] = ptMb->u4DFReg[ CAN_IDX0 ];
            u4Data[ CAN_IDX1 ] = ptMb->u4DFReg[ CAN_IDX1 ];

            /* 受信FIFO バッファポインタ制御レジスタ(RFPCTRx)を制御しリードポインタを移動 */
            /* 取得処理中にFIFOがフルにならないようにデータを取得後に即座に更新する       */
            Can_tb_stGlobalReg.ptu4RFPCTRx[ u1Controller ] = CAN_u4RFPCTRX_RFPC_SET;

            /* 受信FIFO バッファアクセスID レジスタ(RFIDx)から読みだした値をIDに整形 */
            u4IdVal      = u4RFIDx & CAN_u4RFIDX_ID_MSK;

            /* 受信FIFO バッファアクセスポインタレジスタ(RFPTRx)から読みだした値をDLCに整形 */
            /* クラシカルCANフレームはDLCをデータ長として扱う                               */
            u1DataLength = (uint8)( ( u4RFPTRx & CAN_u4RFPTRX_RFDLC_MSK ) >> CAN_SFT_28 );
        }

        /* 受信メッセージ格納用一時バッファへID,データ長を格納 */
        stMsg.u4Id     = u4IdVal;
        stMsg.u1Length = u1DataLength;

        /* 通過フィルタよりMBOXを算出 */
        u1Mbox = (uint8)( ( u4RFPTRx & CAN_u4RFPTRX_RFPTR_MSK ) >> CAN_SFT_16 );

        /* 取得メッセージをCAN共通部へ通知 */
        Can_rx_RxIndMbox( u1Controller, u1Mbox, &stMsg );

        u1Ret = (uint8)CAN_EXIST;
    }

    return ( u1Ret );
}


#endif /* (CAN_CFG_RECEIVE == CAN_USE) */
#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v2-2-1         :2022/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
