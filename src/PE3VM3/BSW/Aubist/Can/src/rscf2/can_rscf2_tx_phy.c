/* can_rscf2_tx_phy_c_m10700_v2-2-1                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/TX/PHYSICAL/CODE                                */
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
#if (CAN_CFG_TRANSMIT == CAN_USE)
#include <can/rscf2/can_rscf2_tb_phy.h>
#include <can/rscf2/can_rscf2_tx.h>
#include <can/rscf2/can_rscf2_fs.h>
#include <can/rscf2/can_rscf2_st.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TX_DATA_ARYSIZE_4BYTE       ( 16U )            /* CAN DATA格納用領域の要素数(4byteアクセス用)       */
#define CAN_TX_DATA_ARYSIZE_1BYTE       ( 64U )            /* CAN DATA格納用領域の要素数(1byteアクセス用)       */
#define CAN_TX_CAN_DATA_SIZE            (  8U )            /* クラシカルCANフレームのデータフィールドへ書き込み */
                                                           /* 可能なデータ長(8byte)                             */
#define CAN_TX_CAN_DATA_WR_SIZE         (  2U )            /* クラシカルCANフレームのデータフィールドへ書き込み */
                                                           /* 可能な回数（最大データ長(8byte)÷4)               */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TX_MERGE_BUF_NUM            (  6U )            /* 送信バッファマージモード対象の送信バッファ数      */
#define CAN_TX_NOMERGE_DATA_WR_SIZE     (  5U )            /* 送信バッファマージモード対象外の送信バッファへ    */
                                                           /* 書き込み可能な回数（最大データ長(20byte)÷4)      */
#define CAN_TX_DLC_TBL_NUM              ( 65U )            /* CAN FDフレームのDLC変換用テーブルの要素数         */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* CAN送信メッセージ情報型 */
typedef struct
{
    uint32* ptTxData;                                      /* 送信データへのポインタ    */
    uint32  u4Id;                                          /* CAN ID                    */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32  u4FrameInfo;                                   /* FDF,BRS,ESIビット設定値   */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8   u1Dlc;                                         /* DLC                       */
} CanTxMsgInfoType;

/* CAN DATA格納用共用体 */
typedef union
{
    uint32 u4Data[CAN_TX_DATA_ARYSIZE_4BYTE];              /* CAN DATA(4byteアクセス用) */
    uint8  u1Data[CAN_TX_DATA_ARYSIZE_1BYTE];              /* CAN DATA(1byteアクセス用) */
} CanTxDataType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static uint8 Can_tx_SetTxReg( uint8 u1Controller, uint8 u1Mbox, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo );
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
static uint8 Can_tx_SetTxFifoReg( uint8 u1Controller, uint8 u1TxFifoIdx, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo );
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#if (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE)
static void Can_tx_TxFinish( uint8 u1Controller );
#endif /* (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
/* MBOX番号変換用(送信バッファアクセスレジスタ用)テーブル         */
/*   配列のインデックス：MBOX番号                                 */
/*   配列の要素        ：送信バッファマージモード使用時のMBOX番号 */
static CanConst uint8 Can_tx_u1MergeMBNo[ CAN_TX_MERGE_BUF_NUM ] = { (uint8)0U  ,(uint8)0U  ,(uint8)0U  ,(uint8)1U  ,(uint8)1U  ,(uint8)1U };

/* データ長からDLCへの変換用テーブル */
/*   配列のインデックス：データ長    */
/*   配列の要素        ：DLC         */
static CanConst uint8 Can_tx_u1DlcVal[ CAN_TX_DLC_TBL_NUM ]      = { (uint8)0x00U
                                                                    ,(uint8)0x01U ,(uint8)0x02U ,(uint8)0x03U ,(uint8)0x04U ,(uint8)0x05U ,(uint8)0x06U ,(uint8)0x07U ,(uint8)0x08U
                                                                    ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x0AU ,(uint8)0x0AU ,(uint8)0x0AU ,(uint8)0x0AU
                                                                    ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0CU ,(uint8)0x0CU ,(uint8)0x0CU ,(uint8)0x0CU
                                                                    ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU
                                                                    ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU
                                                                    ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU
                                                                    ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU
                                                                    ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU };

/* DLC丸めこみ後のデータフィールドへの書き込み回数用テーブル                    */
/*   配列のインデックス：データ長                                               */
/*   配列の要素        ：渡されたデータをラッチするサイズ(丸め込み後のデータ長) */
static CanConst uint8 Can_tx_u1DataSize[ CAN_TX_DLC_TBL_NUM ]    = { (uint8)0U
                                                                    ,(uint8)4U    ,(uint8)4U    ,(uint8)4U    ,(uint8)4U    ,(uint8)8U    ,(uint8)8U    ,(uint8)8U    ,(uint8)8U
                                                                    ,(uint8)12U   ,(uint8)12U   ,(uint8)12U   ,(uint8)12U   ,(uint8)16U   ,(uint8)16U   ,(uint8)16U   ,(uint8)16U
                                                                    ,(uint8)20U   ,(uint8)20U   ,(uint8)20U   ,(uint8)20U   ,(uint8)24U   ,(uint8)24U   ,(uint8)24U   ,(uint8)24U
                                                                    ,(uint8)28U   ,(uint8)28U   ,(uint8)28U   ,(uint8)28U   ,(uint8)32U   ,(uint8)32U   ,(uint8)32U   ,(uint8)32U
                                                                    ,(uint8)36U   ,(uint8)36U   ,(uint8)36U   ,(uint8)36U   ,(uint8)40U   ,(uint8)40U   ,(uint8)40U   ,(uint8)40U
                                                                    ,(uint8)44U   ,(uint8)44U   ,(uint8)44U   ,(uint8)44U   ,(uint8)48U   ,(uint8)48U   ,(uint8)48U   ,(uint8)48U
                                                                    ,(uint8)52U   ,(uint8)52U   ,(uint8)52U   ,(uint8)52U   ,(uint8)56U   ,(uint8)56U   ,(uint8)56U   ,(uint8)56U
                                                                    ,(uint8)60U   ,(uint8)60U   ,(uint8)60U   ,(uint8)60U   ,(uint8)64U   ,(uint8)64U   ,(uint8)64U   ,(uint8)64U   };
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_TxReq_CanFrame                                    */
/* Description   | クラシカルCANフレーム送信要求                            */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller          : CANコントローラ番号        */
/*               | uint8 u1Mbox                : MBOX番号                   */
/*               | CanConstR CanMsgType* ptMsg : メッセージ                 */
/*               |   uint8* ptData             : 送信データへのポインタ     */
/*               |   uint32 u4Id;              : CAN ID                     */
/*               |   uint8  u1Length           : データ長                   */
/* Return Value  | uint8 MBOX送信要求結果                                   */
/*               |   CAN_PROC_OK               : 要求受理                   */
/*               |   CAN_PROC_BUSY             : 他の要求を実行中           */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・割り込み禁止状態で実施されるため処理時間に留意する     */
/*               |   こと。                                                 */
/****************************************************************************/
uint8
Can_tx_TxReq_CanFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
    CanTxMsgInfoType                  stTxMsgInfo;     /* 送信メッセージ情報                             */
    CanConst CanTbChRegType *         ptChReg;         /* チャネルレジスタアドレステーブルへのポインタ   */
    CanTxDataType                     unDataAry;       /* 送信データ                                     */
    uint32                            u4IdVal;         /* CAN ID(標準/拡張)                              */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint32                            u4FrameInfoVal;  /* FDF,BRS,ESIビット設定値                        */
    uint32                            u4CFCCk;         /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)ラッチ用 */
    uint32                            u4CFSTSk;        /* 送受信FIFOバッファステータスレジスタ(CFSTSk)ラッチ用               */
    uint8                             u1TxFifo0Mbox;   /* 送受信FIFO0に接続されたMBOX番号                */
    uint8                             u1TxFifo1Mbox;   /* 送受信FIFO1に接続されたMBOX番号                */
    uint8                             u1TxFifoIdx;     /* 送受信FIFO番号                                 */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                             u1DataWriteSize; /* データへの書き込みサイズ                       */
    uint8                             u1DataSize;      /* 渡されたデータをラッチするサイズ               */
    uint8                             u1TMSTSp;        /* 送信バッファステータスレジスタ(TMSTSp)ラッチ用 */
    uint8                             u1DataIdx;       /* データ参照用インデックス                       */
    uint8                             u1Ret;           /* 戻り値                                         */

    u1Ret = (uint8)CAN_PROC_BUSY;

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* 送受信FIFO引き当て情報確認 */
    u1TxFifo0Mbox = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
    u1TxFifo1Mbox = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
    if ( u1Mbox == u1TxFifo0Mbox )
    {
        u1TxFifoIdx = (uint8)CAN_TRX_FIFO_0;
    }
    else if ( u1Mbox == u1TxFifo1Mbox )
    {
        u1TxFifoIdx = (uint8)CAN_TRX_FIFO_1;
    }
    else
    {
        u1TxFifoIdx = (uint8)CAN_TRX_FIFO_INVALID;
    }

    if ( u1TxFifoIdx <= (uint8)CAN_TRX_FIFO_1 )
    {   /* 送受信FIFO0もしくは1にリンクされたMBOXの場合 */
        u4CFCCk = ptChReg->ptu4CFCCk[ u1TxFifoIdx ];
        u4CFSTSk = ptChReg->ptu4CFSTSk[ u1TxFifoIdx ];
        if ( ( ( u4CFCCk & CAN_u4CFCCK_CFE_MSK ) != CAN_u4BIT_NONE ) && ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
        {   /* 送信要求なし,送信アボート要求なし,送信完了なし,送信アボート完了なし */
            /* 送信要求中のMBOXには再度送信要求はしない                            */

            /* ID,IDE値整形 */
            /* メッセージIDのLSBから31ビット目の値で標準IDか拡張IDを設定するため、マスク設定のみ実施 */
            u4IdVal = ptMsg->u4Id;
            if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
            {   /* 標準CAN ID */
                u4IdVal &= CAN_u4CFIDK_SID_MSK;
            }
            else
            {   /* 拡張CAN ID */
                u4IdVal &= CAN_u4CFIDK_EID_MSK;
            }

            /* 送信データを書き込み用データ領域に格納 */
            u1DataSize = (uint8)CAN_TX_CAN_DATA_SIZE;
            for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
            {
                unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
            }

            /* FDF,BRS,ESI値整形 */
            /* ※クラシカルCANモードでは使用されない設定値だがCan_tx_SetTxFifoRegの */
            /*   引数統一化のためにクラシカルCANモード時でも設定値を生成する。      */
            /* FDF:クラシカルCANフレーム                                            */
            /* BRS:データ領域のビットレートは変わらない                             */
            /* ESI:エラーアクティブノード                                           */
            u4FrameInfoVal = CAN_u4CFFDCSTSK_CFFDF_CAN | CAN_u4CFFDCSTSK_CFBRS_OFF | CAN_u4CFFDCSTSK_CFESI_E_ACT;

            /* データフィールドへの書き込みサイズを設定 */
            u1DataWriteSize = (uint8)CAN_TX_CAN_DATA_WR_SIZE;

            /* 送信メッセージ情報を設定                       */
            /* クラシカルCANフレームはデータ長をDLCとして扱う */
            stTxMsgInfo.ptTxData    = &(unDataAry.u4Data[ CAN_IDX0 ]);
            stTxMsgInfo.u4Id        = u4IdVal;
            stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
            stTxMsgInfo.u1Dlc       = ptMsg->u1Length;

            /* 戻り値はCAN-FDフレーム用のため使用しない */
            (void)Can_tx_SetTxFifoReg( u1Controller, u1TxFifoIdx, u1DataWriteSize ,&stTxMsgInfo ); /* MISRA DEVIATION: no return check required */

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }
    else
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    {   /* 送受信FIFOにリンクされていないMBOXの場合 */
        /* 送信バッファステータスレジスタ(TMSTSp)の値を取得 */
        u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

        if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_TXFREE )
        {   /* 送信要求なし,送信アボート要求なし,送信完了なし,送信アボート完了なし */
            /* 送信要求中のMBOXには再度送信要求はしない                            */

            /* ID,IDE値整形 */
            /* メッセージIDのLSBから31ビット目の値で標準IDか拡張IDを設定するため、マスク設定のみ実施 */
            u4IdVal = ptMsg->u4Id;
            if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
            {   /* 標準CAN ID */
                u4IdVal &= CAN_u4TMIDP_SID_MSK;
            }
            else
            {   /* 拡張CAN ID */
                u4IdVal &= CAN_u4TMIDP_EID_MSK;
            }

            /* 送信データを書き込み用データ領域に格納 */
            u1DataSize = (uint8)CAN_TX_CAN_DATA_SIZE;
            for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
            {
                unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
            }

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
            /* FDF,BRS,ESI値整形 */
            /* ※クラシカルCANモードでは使用されない設定値だがCan_tx_SetTxRegの */
            /*   引数統一化のためにクラシカルCANモード時でも設定値を生成する。  */
            /* FDF:クラシカルCANフレーム                                        */
            /* BRS:データ領域のビットレートは変わらない                         */
            /* ESI:エラーアクティブノード                                       */
            u4FrameInfoVal = CAN_u4TMFDCTR_FDF_CAN | CAN_u4TMFDCTR_BRS_OFF | CAN_u4TMFDCTR_ESI_E_ACT;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

            /* データフィールドへの書き込みサイズを設定 */
            u1DataWriteSize = (uint8)CAN_TX_CAN_DATA_WR_SIZE;

            /* 送信メッセージ情報を設定                       */
            /* クラシカルCANフレームはデータ長をDLCとして扱う */
            stTxMsgInfo.ptTxData    = &(unDataAry.u4Data[ CAN_IDX0 ]);
            stTxMsgInfo.u4Id        = u4IdVal;
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
            stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
            stTxMsgInfo.u1Dlc       = ptMsg->u1Length;

            /* 戻り値はCAN-FDフレーム用のため使用しない */
            (void)Can_tx_SetTxReg( u1Controller, u1Mbox, u1DataWriteSize ,&stTxMsgInfo ); /* MISRA DEVIATION: no return check required */

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_TxReq_CanFdFrame                                  */
/* Description   | CAN FDフレーム送信要求                                   */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller          : CANコントローラ番号        */
/*               | uint8 u1Mbox                : MBOX番号                   */
/*               | CanConstR CanMsgType* ptMsg : メッセージ                 */
/*               |   uint8* ptData             : 送信データへのポインタ     */
/*               |   uint32 u4Id;              : CAN ID                     */
/*               |   uint8  u1Length           : データ長                   */
/* Return Value  | uint8 MBOX送信要求結果                                   */
/*               |   CAN_PROC_OK               : 要求受理                   */
/*               |   CAN_PROC_NG               : 要求棄却                   */
/*               |   CAN_PROC_BUSY             : 他の要求を実行中           */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・割り込み禁止状態で実施されるため処理時間に留意する     */
/*               |   こと。                                                 */
/****************************************************************************/
uint8
Can_tx_TxReq_CanFdFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanTxMsgInfoType                  stTxMsgInfo;     /* 送信メッセージ情報                             */
    CanConst CanTbChRegType *         ptChReg;         /* チャネルレジスタアドレステーブルへのポインタ   */
    CanTxDataType                     unDataAry;       /* 送信データ                                     */
    uint32                            u4IdVal;         /* CAN ID(標準/拡張)                              */
    uint32                            u4FrameInfoVal;  /* FDF,BRS,ESIビット設定値                        */
    uint32                            u4CFCCk;         /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)ラッチ用 */
    uint32                            u4CFSTSk;        /* 送受信FIFOバッファステータスレジスタ(CFSTSk)ラッチ用               */
    uint8                             u1TxFifo0Mbox;   /* 送受信FIFO0に接続されたMBOX番号                */
    uint8                             u1TxFifo1Mbox;   /* 送受信FIFO1に接続されたMBOX番号                */
    uint8                             u1TxFifoIdx;     /* 送受信FIFO番号                                 */
    uint8                             u1DlcVal;        /* DLCサイズ                                      */
    uint8                             u1CheckData;     /* RAM化け確認用データ                            */
    uint8                             u1CheckDataLo;   /* RAM化け確認用データ下位4ビット                 */
    uint8                             u1CheckDataHi;   /* RAM化け確認用データ上位4ビット                 */
    uint8                             u1BRSUse;        /* BRS設定値                                      */
    uint8                             u1DataLength;    /* データ長ラッチ用                               */
    uint8                             u1DataWriteSize; /* データへの書き込みサイズ                       */
    uint8                             u1DataSize;      /* 渡されたデータをラッチするサイズ               */
    uint8                             u1TMSTSp;        /* 送信バッファステータスレジスタ(TMSTSp)ラッチ用 */
    uint8                             u1DataIdx;       /* データ参照用インデックス                       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                             u1Ret;           /* 戻り値                                         */

    /* CAN_PROC_NGは以下の2ケースで返却される                          */
    /* - CAN FDモードでBRS設定値がRAM化けしていた場合                  */
    /* - クラシカルCANモードのチャネルでCAN FDフレームが指定された場合 */
    u1Ret = (uint8)CAN_PROC_NG;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* BRS設定値のRAMチェック(上位4bitと下位4bitの和を算出) */
    u1BRSUse    = Can_st_u1BRSUse[ u1Controller ];
    u1CheckDataLo = (uint8)( u1BRSUse & (uint8)CAN_RAMCHK_MASK_LOWERHALFBYTE );
    u1CheckDataHi = (uint8)( u1BRSUse >> CAN_SFT_4 );
    u1CheckData = u1CheckDataLo + u1CheckDataHi;
    if( u1CheckData == (uint8)CAN_RAMCHK_VALUE_LOWERHALFBYTE )
    {   /* RAM化けが発生していない場合 */

        u1Ret = (uint8)CAN_PROC_BUSY;

        /* 送受信FIFO引き当て情報確認 */
        u1TxFifo0Mbox = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
        u1TxFifo1Mbox = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
        if ( u1Mbox == u1TxFifo0Mbox )
        {
            u1TxFifoIdx = (uint8)CAN_TRX_FIFO_0;
        }
        else if ( u1Mbox == u1TxFifo1Mbox )
        {
            u1TxFifoIdx = (uint8)CAN_TRX_FIFO_1;
        }
        else
        {
            u1TxFifoIdx = (uint8)CAN_TRX_FIFO_INVALID;
        }

        if ( u1TxFifoIdx <= (uint8)CAN_TRX_FIFO_1 )
        {   /* 送受信FIFO0もしくは1にリンクされたMBOXの場合 */
            u4CFCCk = ptChReg->ptu4CFCCk[ u1TxFifoIdx ];
            u4CFSTSk = ptChReg->ptu4CFSTSk[ u1TxFifoIdx ];
            if ( ( ( u4CFCCk & CAN_u4CFCCK_CFE_MSK ) != CAN_u4BIT_NONE ) && ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
            {   /* 送信要求なし,送信アボート要求なし,送信完了なし,送信アボート完了なし */
                /* 送信要求中のMBOXには再度送信要求はしない                            */

                /* ID,IDE値整形 */ 
                /* メッセージIDのLSBから31ビット目の値で標準IDか拡張IDを設定するため、マスク設定のみ実施 */
                u4IdVal = ptMsg->u4Id;
                if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
                {   /* 標準CAN ID */
                    u4IdVal &= CAN_u4CFIDK_SID_MSK;
                }
                else
                {   /* 拡張CAN ID */
                    u4IdVal &= CAN_u4CFIDK_EID_MSK;
                }

                /* データ長のラッチ */
                u1DataLength = ptMsg->u1Length;

                /* CAN FDフレームの時はデータ長からDLCに変換する */
                u1DlcVal = Can_tx_u1DlcVal[ u1DataLength ];

                /* 送信データを書き込み用データ領域に格納 */
                u1DataSize = Can_tx_u1DataSize[ u1DataLength ];
                for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
                {
                    unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
                }

                /* FDF,BRS,ESI値整形 */
                if ( u1BRSUse == (uint8)CAN_ST_BRS_USE )
                {
                    /* FDF:CAN FDフレーム                       */
                    /* BRS:データ領域のビットレートは変わる     */
                    /* ESI:コンフィグに合わせて設定             */
                    u4FrameInfoVal = CAN_u4CFFDCSTSK_CFFDF_CANFD | CAN_u4CFFDCSTSK_CFBRS_ON | Can_tb_stSetRSCANReg[ u1Controller ].u4CFFDCSTSkConf;
                }
                else
                {
                    /* FDF:CAN FDフレーム                       */
                    /* BRS:データ領域のビットレートは変わらない */
                    /* ESI:コンフィグに合わせて設定             */
                    u4FrameInfoVal = CAN_u4CFFDCSTSK_CFFDF_CANFD | CAN_u4CFFDCSTSK_CFBRS_OFF | Can_tb_stSetRSCANReg[ u1Controller ].u4CFFDCSTSkConf;
                }

                /* データフィールドへの書き込み回数をデータ長に合わせて設定                      */
                /* ■前提                                                                        */
                /* ・呼び出し元により8byte単位でデータ領域が確保されている。                     */
                /* ・呼び出し元によりプロトコルで規定されたデータ長(0～8,12,16,20,24,32,48,64)に */
                /*   切り上げられた不足領域はパディングされている。                              */
                u1DataWriteSize = u1DataSize >> CAN_SFT_2;

                /* 送信メッセージ情報を設定 */
                stTxMsgInfo.ptTxData    = &( unDataAry.u4Data[ CAN_IDX0 ] );
                stTxMsgInfo.u4Id        = u4IdVal;
                stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
                stTxMsgInfo.u1Dlc       = u1DlcVal;

                u1Ret = Can_tx_SetTxFifoReg( u1Controller, u1TxFifoIdx, u1DataWriteSize ,&stTxMsgInfo );
            }
        }
        else
        {   /* 送受信FIFOにリンクされていないMBOXの場合 */
            /* 送信バッファステータスレジスタ(TMSTSp)の値を取得 */
            u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

            if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_TXFREE )
            {   /* 送信要求なし,送信アボート要求なし,送信完了なし,送信アボート完了なし */
                /* 送信要求中のMBOXには再度送信要求はしない                            */

                /* ID,IDE値整形 */ 
                /* メッセージIDのLSBから31ビット目の値で標準IDか拡張IDを設定するため、マスク設定のみ実施 */
                u4IdVal = ptMsg->u4Id;
                if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
                {   /* 標準CAN ID */
                    u4IdVal &= CAN_u4TMIDP_SID_MSK;
                }
                else
                {   /* 拡張CAN ID */
                    u4IdVal &= CAN_u4TMIDP_EID_MSK;
                }

                /* データ長のラッチ */
                u1DataLength = ptMsg->u1Length;

                /* CAN FDフレームの時はデータ長からDLCに変換する */
                u1DlcVal = Can_tx_u1DlcVal[ u1DataLength ];

                /* 送信データを書き込み用データ領域に格納 */
                u1DataSize = Can_tx_u1DataSize[ u1DataLength ];
                for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
                {
                    unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
                }

                /* FDF,BRS,ESI値整形 */
                if ( u1BRSUse == (uint8)CAN_ST_BRS_USE )
                {
                    /* FDF:CAN FDフレーム                       */
                    /* BRS:データ領域のビットレートは変わる     */
                    /* ESI:コンフィグに合わせて設定             */
                    u4FrameInfoVal = CAN_u4TMFDCTR_FDF_CANFD | CAN_u4TMFDCTR_BRS_ON | Can_tb_stSetRSCANReg[ u1Controller ].u4TMFDCTRpConf;
                }
                else
                {
                    /* FDF:CAN FDフレーム                       */
                    /* BRS:データ領域のビットレートは変わらない */
                    /* ESI:コンフィグに合わせて設定             */
                    u4FrameInfoVal = CAN_u4TMFDCTR_FDF_CANFD | CAN_u4TMFDCTR_BRS_OFF | Can_tb_stSetRSCANReg[ u1Controller ].u4TMFDCTRpConf;
                }

                /* データフィールドへの書き込み回数をデータ長に合わせて設定                      */
                /* ■前提                                                                        */
                /* ・呼び出し元により8byte単位でデータ領域が確保されている。                     */
                /* ・呼び出し元によりプロトコルで規定されたデータ長(0～8,12,16,20,24,32,48,64)に */
                /*   切り上げられた不足領域はパディングされている。                              */
                u1DataWriteSize = u1DataSize >> CAN_SFT_2;

                /* 送信メッセージ情報を設定 */
                stTxMsgInfo.ptTxData    = &( unDataAry.u4Data[ CAN_IDX0 ] );
                stTxMsgInfo.u4Id        = u4IdVal;
                stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
                stTxMsgInfo.u1Dlc       = u1DlcVal;

                u1Ret = Can_tx_SetTxReg( u1Controller, u1Mbox, u1DataWriteSize ,&stTxMsgInfo );
            }
        }
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_TxAbt                                             */
/* Description   | MBOX送信中断要求                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/*               | uint8 u1Mbox       : MBOX番号                            */
/* Return Value  | uint8 MBOX送信中断要求結果                               */
/*               |   CAN_PROC_OK      : 中断完了                            */
/*               |   CAN_PROC_BUSY    : 中断未完了                          */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・送信中断機能が未使用にコンフィグされている場合、       */
/*               |   本APIは提供しない。                                    */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・送信要求後かつ送信完了処理前のMBOXで呼ばれる前提と     */
/*               |   する。                                                 */
/*               | ・割り込み禁止状態で実施されるため処理時間に留意する     */
/*               |   こと。                                                 */
/*               | ・MBOX0,1,2と3,4,5がマージされている場合、MBOX1,2,4,5の  */
/*               |   設定はCAN_MB_NOUSE固定を前提とする。                   */
/****************************************************************************/
#if (CAN_CFG_ABORTSEND == CAN_USE)
uint8
Can_tx_TxAbt( uint8 u1Controller, uint8 u1Mbox )
{
    CanConst CanTbChRegType *       ptChReg;        /* チャネルレジスタアドレステーブルへのポインタ         */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanConst CanTbSetRSCANRegType * ptSetRSCANReg;  /* RSCANレジスタ設定値テーブルへのポインタ              */
    uint32                          u4CFSTSk;       /* 送受信FIFOバッファステータスレジスタ(CFSTSk)ラッチ用 */
    uint8                           u1TxFifo0Mbox;  /* 送受信FIFO0に接続されたMBOX番号                      */
    uint8                           u1TxFifo1Mbox;  /* 送受信FIFO1に接続されたMBOX番号                      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                           u1TMSTSp;       /* 送信バッファステータスレジスタ(TMSTSp)ラッチ用       */
    uint8                           u1Ret;          /* 戻り値                                               */

    u1Ret = (uint8)CAN_PROC_BUSY;

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* 送受信FIFO引き当て情報確認 */
    u1TxFifo0Mbox = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
    u1TxFifo1Mbox = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
    if ( u1Mbox == u1TxFifo0Mbox )
    {   /* 送受信FIFO0にリンクされたMBOXの場合 */

        /* RSCAN設定値テーブルへのポインタ取得 */
        ptSetRSCANReg = &(Can_tb_stSetRSCANReg[ u1Controller ]);

        /* 送信中断要求 */
        /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)の送受信FIFO バッファ許可ビット(CFE)を */
        /* 「送受信FIFO バッファを使用しない」にすることで送信中断要求相当の動作となる                      */
        ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFE_NOUSE;

        /* 完了判定 */
        u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
        if ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE )
        {
            /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)の送受信FIFO バッファ許可ビット(CFE)を */
            /* もとに戻すことで、中断完了処理が終わっていることを示す                                           */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf;

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }
    else if ( u1Mbox == u1TxFifo1Mbox )
    {   /* 送受信FIFO1にリンクされたMBOXの場合 */

        /* RSCAN設定値テーブルへのポインタ取得 */
        ptSetRSCANReg = &(Can_tb_stSetRSCANReg[ u1Controller ]);

        /* 送信中断要求 */
        /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)の送受信FIFO バッファ許可ビット(CFE)を */
        /* 「送受信FIFO バッファを使用しない」にすることで送信中断要求相当の動作となる                      */
        ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFE_NOUSE;

        /* 完了判定 */
        u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
        if ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE )
        {
            /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)の送受信FIFO バッファ許可ビット(CFE)を */
            /* もとに戻すことで、中断完了処理が終わっていることを示す                                           */
            ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf;

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }
    else
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    {   /* 送受信FIFOにリンクされていないMBOXの場合 */

        /* 送信中断要求 */
        /* 本関数は送信要求後かつ送信完了処理前で呼ばれ、                     */
        /* 必ず送信要求中の区間であるため、中断要求実施要否の判定は実施しない */
        /* 送信バッファ制御レジスタ(TMCp)に送信アボート要求を設定             */
        ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTAR_SET;

        /* 完了判定 */
        /* (マイコン個別制約)                                            */
        /* 送信完了および中断完了処理は以下で実施する。                  */
        /*   割り込み送信用MBOXの場合                                    */
        /*     送信完了(通常)       Can_tx_ChkTxFinMbox(割り込み処理時)  */
        /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(割り込み処理時)  */
        /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(割り込み処理時)  */
        /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
        /*     中断完了(未送信)     Can_tx_TxAbt                         */
        /*   ポーリング送信用MBOXの場合                                  */
        /*     送信完了(通常)       Can_tx_ChkTxFinMbox(定期処理時)      */
        /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(定期処理時)      */
        /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(定期処理時)      */
        /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
        /*     中断完了(未送信)     Can_tx_TxAbt                         */
        /* ※中断完了時に割り込みが発生しないように設定している。        */
        /* ※RSCANでは中断完了(未送信)の場合は即時結果確認が可能。       */

        /* 送信バッファステータスレジスタ(TMSTSp)の値を取得 */
        u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

        if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_ABORTED )
        {   /* 中断完了(未送信) */

            /* 送信バッファステータスレジスタ(TMSTSp)の送信アボート完了フラグクリア */
            ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}
#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_TxAbtAll                                          */
/* Description   | 全MBOX送信中断要求                                       */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・MBOX0,1,2と3,4,5がマージされている場合、MBOX1,2,4,5の  */
/*               |   設定はCAN_MB_NOUSE固定を前提とする。                   */
/****************************************************************************/
void
Can_tx_TxAbtAll( uint8 u1Controller )
{
    CanConst CanTbChRegType *       ptChReg;             /* チャネルレジスタアドレステーブルへのポインタ  */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanConst CanTbSetRSCANRegType * ptSetRSCANReg;       /* RSCANレジスタ設定値テーブルへのポインタ       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                          u2TmpTxAbtReqFlag;   /* 中断要求の対象とするMBOX一覧                  */
    uint16                          u2MboxBit;           /* MBOXビット位置                                */
    uint8                           u1MboxNum;           /* 送信用のMBOX数ラッチ用                        */
    uint8                           u1Mbox;              /* MBOX番号                                      */

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &Can_tb_stChReg[ u1Controller ];

    /* 送信中断要求の対象メッセージの情報取得 */
    u2TmpTxAbtReqFlag = ( Can_tb_stTxMbBit[ u1Controller ].u2TxIntrBit
                        | Can_tb_stTxMbBit[ u1Controller ].u2TxPollBit );

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* RSCAN設定値テーブルへのポインタ取得 */
    ptSetRSCANReg = &(Can_tb_stSetRSCANReg[ u1Controller ]);

    /* 送受信FIFOの送信中断要求 */
    /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)の送受信FIFO バッファ許可ビット(CFE)を */
    /* 「送受信FIFO バッファを使用しない」にすることで送信中断要求相当の動作となる                      */
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCCK_CFE_NOUSE;
    ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCCK_CFE_NOUSE;

    /* 送受信FIFOにリンクされたMBOXは除外する */
    u2TmpTxAbtReqFlag &= Can_tb_u2TxFifoBitMask[ u1Controller ];
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* 送信用のMBOX数取得 */
    u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

    /* 送信バッファの送信中断要求(送信要求クリア) */
    for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
    {
        /* MBOX番号を16bit列に変換 */
        u2MboxBit = (uint16)(CAN_u2BIT0 << ( u1Mbox & (uint8)CAN_MBSFT_MSK ));

        /* MBOX毎の中断要求の対象か判定 */
        if ( ( u2TmpTxAbtReqFlag & u2MboxBit ) != CAN_u2BIT_NONE )
        {
            /* 送信中断要求 */
            /* 送信バッファ制御レジスタ(TMCp)に送信アボート要求を設定 */
            ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTAR_SET;
        }
    }
}


/****************************************************************************/
/* Function Name | Can_TxFinish_0                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_0 == CAN_USE)
void
Can_TxFinish_0( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_0 );
}
#endif /* (CAN_TX_TXFINISH_USE_0 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_1                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_1 == CAN_USE)
void
Can_TxFinish_1( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_1 );
}
#endif /* (CAN_TX_TXFINISH_USE_1 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_2                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_2 == CAN_USE)
void
Can_TxFinish_2( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_2 );
}
#endif /* (CAN_TX_TXFINISH_USE_2 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_3                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_3 == CAN_USE)
void
Can_TxFinish_3( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_3 );
}
#endif /* (CAN_TX_TXFINISH_USE_3 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_4                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_4 == CAN_USE)
void
Can_TxFinish_4( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_4 );
}
#endif /* (CAN_TX_TXFINISH_USE_4 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_5                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_5 == CAN_USE)
void
Can_TxFinish_5( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_5 );
}
#endif /* (CAN_TX_TXFINISH_USE_5 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_6                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_6 == CAN_USE)
void
Can_TxFinish_6( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_6 );
}
#endif /* (CAN_TX_TXFINISH_USE_6 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_7                                           */
/* Description   | 送信完了割り込み                                         */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・当該CANコントローラが以下のいずれかに該当する場合、    */
/*               |   本APIは提供しない。                                    */
/*               |   - 割り込みによる送信処理を実施しない場合               */
/*               |   - 非制御対象CANにコンフィグされている場合              */
/*               |   - 未使用にコンフィグされている場合                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_7 == CAN_USE)
void
Can_TxFinish_7( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_7 );
}
#endif /* (CAN_TX_TXFINISH_USE_7 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_ChkTxFinMbox                                      */
/* Description   | MBOX送信完了確認                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/*               | uint8 u1Kind       : 検索対象種別(INTR/POLL)             */
/* Return Value  | uint8 MBOX送信完了確認結果                               */
/*               |   CAN_EXIST        : 送信完了あり                        */
/*               |   CAN_NONE         : 送信完了なし                        */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
uint8
Can_tx_ChkTxFinMbox( uint8 u1Controller, uint8 u1Kind )
{
    CanConst CanTbChRegType *       ptChReg;          /* チャネルレジスタアドレステーブルへのポインタ             */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanConst CanTbSetRSCANRegType * ptSetRSCANReg;    /* RSCANレジスタ設定値テーブルへのポインタ                  */
    uint32                          u4CFSTSk;         /* 送受信FIFOバッファステータスレジスタ(CFSTSk)ラッチ用     */
    uint16                          u2TxFifo0MboxBit; /* 送受信FIFO0に接続されたMBOXビット位置                    */
    uint16                          u2TxFifo1MboxBit; /* 送受信FIFO1に接続されたMBOXビット位置                    */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                          u2TMTCSTSy;       /* 送信バッファ送信完了ステータスレジスタ(TMTCSTSy)ラッチ用 */
    uint16                          u2TmpTxFinFlag;   /* 送信完了済みのMBOX一覧                                   */
    uint16                          u2MboxBit;        /* MBOXビット位置                                           */
    uint16                          u2TxBit;          /* 送信MBOXビット                                           */
    uint8                           u1MboxNum;        /* 送信用のMBOX数ラッチ用                                   */
    uint8                           u1Mbox;           /* MBOX番号                                                 */
    uint8                           u1Ret;            /* 戻り値                                                   */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint8                           u1TxFifo0Mbox;    /* 送受信FIFO0に接続されたMBOX番号                          */
    uint8                           u1TxFifo1Mbox;    /* 送受信FIFO1に接続されたMBOX番号                          */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    u1Ret = (uint8)CAN_NONE;

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* 検索対象メッセージの情報取得 */
    if ( u1Kind == (uint8)CAN_INTERRUPT )
    {   /* 検索対象メッセージが割り込み送信の場合 */
        u2TxBit = Can_tb_stTxMbBit[ u1Controller ].u2TxIntrBit;
    }
    else
    {   /* 検索対象メッセージがポーリング送信の場合 */
        u2TxBit = Can_tb_stTxMbBit[ u1Controller ].u2TxPollBit;
    }

    /* 送信用のMBOX数取得 */
    u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* RSCAN設定値テーブルへのポインタ取得 */
    ptSetRSCANReg = &(Can_tb_stSetRSCANReg[ u1Controller ]);

    /* 送受信FIFOの送信完了確認 */
    u1TxFifo0Mbox = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
    if ( u1TxFifo0Mbox < u1MboxNum )
    {
        u2TxFifo0MboxBit = (uint16)( CAN_u2BIT0 << u1TxFifo0Mbox );
        if ( ( u2TxBit & u2TxFifo0MboxBit ) != CAN_u2BIT_NONE )
        {
            u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
            if ( ( u4CFSTSk & CAN_u4CFSTSK_CFTXIF_MSK ) != CAN_u4BIT_NONE )
            {
                /* 送信済みかつ完了処理前MBOXが存在している場合 */
                /* 戻り値は送信完了ありとする。                 */
                u1Ret = (uint8)CAN_EXIST;

                /* 送信完了割り込み要因のクリア */
                ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTSK_CLEARALL;

                /* 中断要求をかけている場合、CFFCk.CFEビットが「送受信FIFO バッファを使用しない」になっているため、 */
                /* 完了処理時に再度送信要求可能なように「送受信FIFO バッファを使用する」に再設定する                */
                ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1TxFifo0Mbox );
            }
        }
    }
    u1TxFifo1Mbox = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
    if ( u1TxFifo1Mbox < u1MboxNum )
    {
        u2TxFifo1MboxBit = (uint16)( CAN_u2BIT0 << u1TxFifo1Mbox );
        if ( ( u2TxBit & u2TxFifo1MboxBit ) != CAN_u2BIT_NONE )
        {
            u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
            if ( ( u4CFSTSk & CAN_u4CFSTSK_CFTXIF_MSK ) != CAN_u4BIT_NONE )
            {
                /* 送信済みかつ完了処理前MBOXが存在している場合 */
                /* 戻り値は送信完了ありとする。                 */
                u1Ret = (uint8)CAN_EXIST;

                /* 送信完了割り込み要因のクリア */
                ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTSK_CLEARALL;

                /* 中断要求をかけている場合、CFFCk.CFEビットが「送受信FIFO バッファを使用しない」になっているため、 */
                /* 完了処理時に再度送信要求可能なように「送受信FIFO バッファを使用する」に再設定する                */
                ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1TxFifo1Mbox );
            }
        }
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    /* 送信バッファの送信完了確認 */

    /* 送信バッファ送信完了ステータスレジスタ(TMTCSTSy)の値を取得 */
    u2TMTCSTSy = *( ptChReg->ptu2TMTCSTSy );

    /* 送信完了したメッセージ */
    u2TmpTxFinFlag = u2TMTCSTSy & u2TxBit;

    /* 送信済みかつ完了処理前MBOXの有無を一括確認     */
    /* 存在した場合のみ、MBOX個別の送信完了を確認する */
    if ( u2TmpTxFinFlag != CAN_u2BIT_NONE )
    {
        /* 送信済みかつ完了処理前MBOXが存在している場合 */
        /* 戻り値は送信完了ありとする。                 */
        u1Ret = (uint8)CAN_EXIST;

        /* MBOX別の送信完了検索 */
        for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
        {
            /* 完了判定 */
            /* (マイコン個別制約)                                            */
            /* 送信完了および中断完了処理は以下で実施する。                  */
            /*   割り込み送信用MBOXの場合                                    */
            /*     送信完了(通常)       Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
            /*     中断完了(未送信)     Can_tx_TxAbt                         */
            /*   ポーリング送信用MBOXの場合                                  */
            /*     送信完了(通常)       Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
            /*     中断完了(未送信)     Can_tx_TxAbt                         */
            /* ※中断完了時に割り込みが発生しないように設定している。        */
            /* ※RSCANでは中断完了(未送信)の場合は即時結果確認が可能。       */

            /* MBOX番号を16bit列に変換 */
            u2MboxBit = (uint16)(CAN_u2BIT0 << ( u1Mbox & (uint8)CAN_MBSFT_MSK ));

            /* MBOX毎の送信完了判定 */
            if ( ( u2TmpTxFinFlag & u2MboxBit ) != CAN_u2BIT_NONE )
            {
                /* 送信バッファステータスレジスタ(TMSTSp)の送信完了フラグクリア */
                ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1Mbox );
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_ChkTxAbtMbox                                      */
/* Description   | MBOX送信中断完了確認                                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・送信中断機能が未使用にコンフィグされている場合、       */
/*               |   本APIは提供しない。                                    */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/****************************************************************************/
#if (CAN_CFG_ABORTSEND == CAN_USE)
void
Can_tx_ChkTxAbtMbox( uint8 u1Controller )
{
    CanConst CanTbChRegType *       ptChReg;          /* チャネルレジスタアドレステーブルへのポインタ                       */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    CanConst CanTbSetRSCANRegType * ptSetRSCANReg;    /* RSCANレジスタ設定値テーブルへのポインタ                            */
    uint32                          u4CFCCk;          /* 送受信FIFOバッファコンフィグレーション/制御レジスタ(CFCCk)ラッチ用 */
    uint32                          u4CFSTSk;         /* 送受信FIFOバッファステータスレジスタ(CFSTSk)ラッチ用               */
    uint16                          u2TxFifo0MboxBit; /* 送受信FIFO0に接続されたMBOXビット位置                              */
    uint16                          u2TxFifo1MboxBit; /* 送受信FIFO1に接続されたMBOXビット位置                              */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint16                          u2TMTASTSy;       /* 送信バッファ送信アボートステータスレジスタ(TMTASTSy)ラッチ用       */
    uint16                          u2TmpTxAbtFlag;   /* 中断完了済みのMBOX一覧                                             */
    uint16                          u2MboxBit;        /* MBOXビット位置                                                     */
    uint16                          u2TxBit;          /* 送信MBOXビット                                                     */
    uint8                           u1MboxNum;        /* 送信用のMBOX数ラッチ用                                             */
    uint8                           u1Mbox;           /* MBOX番号                                                           */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    uint8                           u1TxFifo0Mbox;    /* 送受信FIFO0に接続されたMBOX番号                                    */
    uint8                           u1TxFifo1Mbox;    /* 送受信FIFO1に接続されたMBOX番号                                    */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

    /* 本関数では、送信MBOXの種別(INTR or POLL)によらず送信中断を確認する */

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* 検索対象メッセージの情報取得 */
    u2TxBit = ( Can_tb_stTxMbBit[ u1Controller ].u2TxIntrBit
              | Can_tb_stTxMbBit[ u1Controller ].u2TxPollBit );

    /* 送信用のMBOX数取得 */
    u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    /* RSCAN設定値テーブルへのポインタ取得 */
    ptSetRSCANReg = &(Can_tb_stSetRSCANReg[ u1Controller ]);

    /* 送受信FIFOの送信中断完了確認 */
    u1TxFifo0Mbox = Can_tb_u1TxFifo0LinkConf[ u1Controller ];
    if ( u1TxFifo0Mbox < u1MboxNum )
    {
        u2TxFifo0MboxBit = (uint16)( CAN_u2BIT0 << u1TxFifo0Mbox );
        if ( ( u2TxBit & u2TxFifo0MboxBit ) != CAN_u2BIT_NONE )
        {
            u4CFCCk = ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ];
            u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_0 ];
            if ( ( ( u4CFCCk & CAN_u4CFCCK_CFE_MSK ) == CAN_u4BIT_NONE ) && ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
            {
                /* 中断要求をかけている場合、CFFCk.CFEビットが「送受信FIFO バッファを使用しない」になっているため、 */
                /* 完了処理時に再度送信要求可能なように「送受信FIFO バッファを使用する」に再設定する                */
                ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1TxFifo0Mbox );
            }
        }
    }
    u1TxFifo1Mbox = Can_tb_u1TxFifo1LinkConf[ u1Controller ];
    if ( u1TxFifo1Mbox < u1MboxNum )
    {
        u2TxFifo1MboxBit = (uint16)( CAN_u2BIT0 << u1TxFifo1Mbox );
        if ( ( u2TxBit & u2TxFifo1MboxBit ) != CAN_u2BIT_NONE )
        {
            u4CFCCk = ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ];
            u4CFSTSk = ptChReg->ptu4CFSTSk[ CAN_TRX_FIFO_1 ];
            if ( ( ( u4CFCCk & CAN_u4CFCCK_CFE_MSK ) == CAN_u4BIT_NONE ) && ( ( u4CFSTSk & CAN_u4CFSTSK_TXIDLE_MSK ) == CAN_u4CFSTSK_TXIDLE ) )
            {
                /* 中断要求をかけている場合、CFFCk.CFEビットが「送受信FIFO バッファを使用しない」になっているため、 */
                /* 完了処理時に再度送信要求可能なように「送受信FIFO バッファを使用する」に再設定する                */
                ptChReg->ptu4CFCCk[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1TxFifo1Mbox );
            }
        }
    }
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    /* 送信バッファの送信中断完了確認 */

    /* 送信バッファ送信アボートステータスレジスタ(TMTASTSy)の値を取得 */
    u2TMTASTSy = *( ptChReg->ptu2TMTASTSy );

    /* 送信中断完了したメッセージ */
    u2TmpTxAbtFlag = u2TMTASTSy & u2TxBit;

    /* 中断済みかつ中断完了処理前MBOXの有無を一括確認 */
    /* 存在した場合のみ、MBOX個別の中断完了を確認する */
    if ( u2TmpTxAbtFlag != CAN_u2BIT_NONE )
    {
        /* MBOX別の中断完了検索 */
        for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
        {
            /* 完了判定 */
            /* (マイコン個別制約)                                            */
            /* 送信完了および中断完了処理は以下で実施する。                  */
            /*   割り込み送信用MBOXの場合                                    */
            /*     送信完了(通常)       Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(割り込み処理時)  */
            /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
            /*     中断完了(未送信)     Can_tx_TxAbt                         */
            /*   ポーリング送信用MBOXの場合                                  */
            /*     送信完了(通常)       Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     送信完了(中断要求後) Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     送信完了後中断要求   Can_tx_ChkTxFinMbox(定期処理時)      */
            /*     中断完了(送信開始後) Can_tx_ChkTxAbtMbox                  */
            /*     中断完了(未送信)     Can_tx_TxAbt                         */
            /* ※中断完了時に割り込みが発生しないように設定している。        */
            /* ※RSCANでは中断完了(未送信)の場合は即時結果確認が可能。       */

            /* MBOX番号を16bit列に変換 */
            u2MboxBit = (uint16)(CAN_u2BIT0 << ( u1Mbox & (uint8)CAN_MBSFT_MSK ));

            /* MBOX毎の中断完了判定 */
            if ( ( u2TmpTxAbtFlag & u2MboxBit ) != CAN_u2BIT_NONE )
            {
                /* 送信バッファステータスレジスタ(TMSTSp)の送信アボート完了フラグクリア */
                ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

                /* CAN共通部へ通知 */
                Can_tx_TxConfMbox( u1Controller, u1Mbox );
            }
        }
    }
}
#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_SetTxReg                                          */
/* Description   | 送信バッファレジスタ設定                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller           : CANコントローラ番号       */
/*               | uint8 u1Mbox                 : MBOX番号                  */
/*               | uint8 u1DataWriteSize        : データ書き込みサイズ      */
/*               | CanConstR CanTxMsgInfoType* ptTxMsgInfo :                */
/*               |                                送信メッセージ情報        */
/*               |   uint32* ptTxData           : 送信データへのポインタ    */
/*               |   uint32  u4Id;              : CAN ID                    */
/*               |   uint32  u4FrameInfo        : FDF,BRS,ESIビット設定値   */
/*               |   uint8   u1Dlc;             : DLC                       */
/* Return Value  |   uint8 MBOX送信設定結果                                 */
/*               |     CAN_PROC_OK              : 送信設定完了              */
/*               |     CAN_PROC_NG              : 送信設定棄却              */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・割り込み禁止状態で実施されるため処理時間に留意する     */
/*               |   こと。                                                 */
/****************************************************************************/
static uint8
Can_tx_SetTxReg( uint8 u1Controller, uint8 u1Mbox, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo )
{
    CanConst CanTbChRegType *         ptChReg;         /* チャネルレジスタアドレステーブルへのポインタ */
    volatile CanTbRegCANTMType *      ptMb;            /* MBOXへのポインタ                             */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    volatile CanTbRegCANTMMRGType *   ptMergeMb;       /* MBOXへのポインタ(送信バッファマージモード)   */
    uint8                             u1MergeMbox;     /* 送信バッファマージモード用MBOX番号           */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    uint8                             u1Idx;           /* ループ用インデックス                         */
    uint8                             u1Ret;           /* 戻り値                                       */

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    u1Ret = (uint8)CAN_PROC_NG;

    if( u1Mbox < (uint8)CAN_TX_MERGE_BUF_NUM )
    {   /* 送信バッファマージモード対象MBOXの場合 */

        /* MBOX番号を取得 */
        u1MergeMbox = Can_tx_u1MergeMBNo[ u1Mbox ];

        /* MBOXのアドレス取得 */
        ptMergeMb   = &( ptChReg->ptstTM_MERGE[ u1MergeMbox ] );

        /* メッセージ書き込み */
        /* 送信バッファIDレジスタ(TMIDp)の設定(ID,IDE値設定) */
        ptMergeMb->u4IDReg    = ptTxMsgInfo->u4Id;

        /* 送信バッファポインタレジスタ(TMPTRp)の設定           */
        /* DLCは0～15の範囲で指定されるため、マスク処理は不要。 */
        ptMergeMb->u4PTRReg   = (uint32)ptTxMsgInfo->u1Dlc << CAN_SFT_28;

        /* 送信バッファポインタレジスタ(TMFDCTRp)の設定(FDF,BRS,ESI値設定) */
        ptMergeMb->u4FDCTRReg = ptTxMsgInfo->u4FrameInfo;

        /* 送信バッファデータフィールドbレジスタ(TMDFb_p)の設定 */
        for ( u1Idx = (uint8)0U; u1Idx < u1DataWriteSize; u1Idx++ )
        {
            ptMergeMb->u4DFReg[ u1Idx ] = ptTxMsgInfo->ptTxData[ u1Idx ];
        }

        /* 送信バッファ制御レジスタ(TMCp)に送信要求を設定 */
        ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTR_SET;

        u1Ret = (uint8)CAN_PROC_OK;
    }
    else
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    {
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        /* 送信バッファマージモード対象外MBOXの場合         */
        /* データフィールドへの書き込み回数の最大値チェック */
        if( u1DataWriteSize <= (uint8)CAN_TX_NOMERGE_DATA_WR_SIZE )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        {   /* 書き込み回数が5回以下の場合(送信データ長が20byte以下の場合) */

            /* MBOXのアドレス取得 */
            ptMb = &( ptChReg->ptstTM[ u1Mbox ] );

            /* メッセージ書き込み */
            /* 送信バッファIDレジスタ(TMIDp)の設定(ID,IDE値設定) */
            ptMb->u4IDReg    = ptTxMsgInfo->u4Id;

            /* 送信バッファポインタレジスタ(TMPTRp)の設定           */
            /* DLCは0～15の範囲で指定されるため、マスク処理は不要。 */
            ptMb->u4PTRReg   = (uint32)ptTxMsgInfo->u1Dlc << CAN_SFT_28;

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
            /* 送信バッファポインタレジスタ(TMFDCTRp)の設定(FDF,BRS,ESI値設定) */
            ptMb->u4FDCTRReg = ptTxMsgInfo->u4FrameInfo;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

            /* 送信バッファデータフィールドbレジスタ(TMDFb_p)の設定 */
            for ( u1Idx = (uint8)0U; u1Idx < u1DataWriteSize; u1Idx++ )
            {
                ptMb->u4DFReg[ u1Idx ] = ptTxMsgInfo->ptTxData[ u1Idx ];
            }

            /* 送信バッファ制御レジスタ(TMCp)に送信要求を設定 */
            ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTR_SET;

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_SetTxFifoReg                                      */
/* Description   | 送信用送受信FIFOバッファレジスタ設定                     */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller           : CANコントローラ番号       */
/*               | uint8 u1TxFifoIdx            : 送受信FIFO番号            */
/*               | uint8 u1DataWriteSize        : データ書き込みサイズ      */
/*               | CanConstR CanTxMsgInfoType* ptTxMsgInfo :                */
/*               |                                送信メッセージ情報        */
/*               |   uint32* ptTxData           : 送信データへのポインタ    */
/*               |   uint32  u4Id;              : CAN ID                    */
/*               |   uint32  u4FrameInfo        : FDF,BRS,ESIビット設定値   */
/*               |   uint8   u1Dlc;             : DLC                       */
/* Return Value  |   uint8 MBOX送信設定結果                                 */
/*               |     CAN_PROC_OK              : 送信設定完了              */
/*               |     CAN_PROC_NG              : 送信設定棄却              */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・以下のモードから呼ばれる前提とする。                   */
/*               |  - グローバル動作モード                                  */
/*               |  - チャネル通信モード                                    */
/*               | ・割り込み禁止状態で実施されるため処理時間に留意する     */
/*               |   こと。                                                 */
/****************************************************************************/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
static uint8
Can_tx_SetTxFifoReg( uint8 u1Controller, uint8 u1TxFifoIdx, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo )
{
    CanConst CanTbChRegType *         ptChReg;         /* チャネルレジスタアドレステーブルへのポインタ */
    volatile CanTbRegCANCFType *      ptMb;            /* MBOXへのポインタ                             */
    uint8                             u1FifoWriteSize; /* 送受信FIFO書き込み回数の最大値               */
    uint8                             u1Idx;           /* ループ用インデックス                         */
    uint8                             u1Ret;           /* 戻り値                                       */

    u1Ret = (uint8)CAN_PROC_NG;

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* データフィールドへの書き込み回数の最大値チェック */
    u1FifoWriteSize = Can_tb_u1FifoWriteSize[ u1Controller ][ u1TxFifoIdx ];
    if( u1DataWriteSize <= u1FifoWriteSize )
    {   /* 書き込み回数がFIFOのペイロードサイズに対応する書き込み回数に収まる場合 */

        /* MBOXのアドレス取得 */
        ptMb = &( ptChReg->ptstCF[ u1TxFifoIdx ] );

        /* メッセージ書き込み */
        /* 送受信FIFOバッファアクセスIDレジスタ(CFIDk)の設定(ID,IDE値設定) */
        ptMb->u4IDReg    = ptTxMsgInfo->u4Id;

        /* 送受信FIFOバッファアクセスポインタレジスタ(CFPTRk)の設定           */
        /* DLCは0～15の範囲で指定されるため、マスク処理は不要。 */
        ptMb->u4PTRReg   = (uint32)ptTxMsgInfo->u1Dlc << CAN_SFT_28;

        /* 送受信FIFO CAN FD コンフィグレーション／ステータスレジスタ(CFFDCSTSk)の設定(FDF,BRS,ESI値設定) */
        ptMb->u4FDCSTSReg = ptTxMsgInfo->u4FrameInfo;

        /* 送受信FIFOバッファアクセスデータフィールドdレジスタ(CFDFd_k)の設定 */
        for ( u1Idx = (uint8)0U; u1Idx < u1DataWriteSize; u1Idx++ )
        {
            ptMb->u4DFReg[ u1Idx ] = ptTxMsgInfo->ptTxData[ u1Idx ];
        }

        /* 送受信FIFO バッファポインタ制御レジスタ(CFPCTRk)に書き込むことで送信要求を設定 */
        ptChReg->ptu4CFPCTRk[ u1TxFifoIdx ] = CAN_u4CFPCTRK_CFPC_SET;

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/****************************************************************************/
/* Function Name | Can_tx_TxFinish                                          */
/* Description   | 送信完了割り込み共通処理                                 */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/****************************************************************************/
#if (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE)
static void
Can_tx_TxFinish( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;     /* チャネルレジスタアドレステーブルへのポインタ */
    volatile uint32                u4DummyRead; /* レジスタのダミーリード用                     */
    uint32                         u4CmSTS;     /* チャネルステータスレジスタ(CmSTS)ラッチ用    */
    uint8                          u1TxResult;  /* 送信完了確認の戻り値                         */

    /* チャネルレジスタアドレステーブルのアドレス取得 */
    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    /* チャネルステータスレジスタ(CmSTS)の値を取得 */
    u4CmSTS = *( ptChReg->ptu4CmSTS );

    /* チャネル通信モードかチェック */
    /* チャネル通信モードの場合、必ずグローバル動作モードのためグローバルモードはチェックしない */
    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {   /*=================== チャネル通信モード ===================*/

        /* 通信停止遷移中、通信停止中に本処理を実施した場合、                 */
        /* 不要な送信完了通知をする可能性があるが、上位で破棄する前提とする。 */

        /* 送信完了割り込み確認 */
        u1TxResult = Can_tx_ChkTxFinMbox( u1Controller, (uint8)CAN_INTERRUPT );

        /* 送信完了の有無チェック */
        if ( u1TxResult != (uint8)CAN_EXIST )
        {
            /* 送信完了したデータが存在しなかった場合、割り込み設定をリフレッシュする */
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
#endif /* (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) */


#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
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
