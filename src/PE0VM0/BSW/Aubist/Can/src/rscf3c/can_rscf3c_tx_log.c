/* can_rscf3c_tx_log_c_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/TX/LOGICAL/CODE                                */
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
#include "../../cfg/rscf3c/can_rscf3c_cfg_ext.h"
#include "../../cfg/rscf3c/can_rscf3c_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>
#include <can/rscf3c/can_rscf3c.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf3c/can_rscf3c_tb_log.h>
#include <can/rscf3c/can_rscf3c_st.h>
#include <can/rscf3c/can_rscf3c_tx.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TX_PDUID_INIT               ( 0xFFFFU )         /* 送信PDU ID初期値                    */
#define CAN_TX_DL_MAX_CAN               ( 15U )             /* クラシカルCANフレームの最大データ長 */
#define CAN_TX_DL_MAX_CANFD             ( 64U )             /* CAN FDフレームの最大データ長        */
#define CAN_TX_ID_FDF_MSK               ( 0x40000000UL )    /* CAN IDのFDFビットマスク             */
#define CAN_TX_ID_FDF_CANFD             ( 0x40000000UL )    /* CAN IDのFDFビットがCAN FD           */


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
/* 送信要求PDU ID                                             */
/* ・内容：                                                   */
/*     上位層からHTHに対して送信要求を受けた際に、            */
/*     指定されたPDU IDを記憶する。                           */
/*     記憶したPDU IDは、HTHの送信完了を検出後、上位層に      */
/*     送信完了を通知する際に使用する。                       */
/*     インデックスは、記憶するHTH の位置(HTH先頭からの連番)  */
/*     となる。                                               */
/* ・値域：                                                   */
/*     0x0000 - 0xFFFE                                        */
/*       送信要求として受付可能な値域。                       */
/*       送信要求受付後、送信完了を通知するまで保持する値。   */
/*     0xFFFF                                                 */
/*       初期値、及び送信完了通知後から次回送信要求を受け     */
/*       付けるまで保持する値。                               */
/* ・RAM化け対策：                                            */
/*     送信要求受付時、及び送信完了通知時にリフレッシュする。 */
/*------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
static PduIdType Can_tx_u2TxPduId[ CAN_TB_HTHNUM_MAX ];
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_Init                                              */
/* Description   | 送信機能初期化                                           */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   空関数とする。                                         */
/****************************************************************************/
void
Can_tx_Init( void )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    uint16  u2HthIdx;           /* 送信要求PDU ID情報のインデクス */
    uint16  u2HthNumMax;        /* 総HTH数                        */

    /* 送信要求PDU IDの初期化 */
    u2HthNumMax = Can_tb_u2HthNumMax;
    for ( u2HthIdx = (uint16)0U; u2HthIdx < u2HthNumMax; u2HthIdx++ )
    {
        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;
    }
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_tx_ClearTxInf                                        */
/* Description   | 送信情報クリア                                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   空関数とする。                                         */
/****************************************************************************/
void
Can_tx_ClearTxInf( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;   /* HOH-MBOX配置情報テーブルへのポインタ     */
    uint16                          u2HthIdx;       /* 送信要求PDU ID情報のインデクス           */
    uint16                          u2HthStart;     /* コントローラ毎HTH開始位置(HTHインデクス) */
    uint16                          u2HthEnd;       /* コントローラ毎HTH終了位置(HTHインデクス) */

    /* HOH配置情報取得 */
    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HthStart   = ptHohMbAlloc->u2HthOffset - Can_tb_u2HrhNumMax;
    u2HthEnd     = u2HthStart + (uint16)ptHohMbAlloc->u1HthNum;

    /* 送信要求PDU IDの初期化                               */
    /* 当該CANコントローラで使用するHTH領域のみ初期化する。 */
    for ( u2HthIdx = u2HthStart; u2HthIdx < u2HthEnd; u2HthIdx++ )
    {
        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;
    }
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_Write                                                */
/* Description   | 送信要求                                                 */
/* Preconditions | -                                                        */
/* Parameters    | Can_HwHandleType Hth :                                   */
/*               |   送信を要求するMBOXに対応したHardware Transmit Handle   */
/*               | CanConstR Can_PduType* PduInfo : PDU                     */
/*               |   PduIdType  swPduHandle       : PDU ID                  */
/*               |   uint8      length            : データ長                */
/*               |   Can_IdType id                : CAN ID                  */
/*               |   uint8*     sdu               : 送信データへのポインタ  */
/* Return Value  | Can_ReturnType 要求受付結果                              */
/*               |   CAN_OK     : 要求が受け付けられた                      */
/*               |   CAN_NOT_OK : 要求が受け付けられなかった                */
/*               |   CAN_BUSY   : 他の要求を実行中                          */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・本関数はCanIf_TxConfirmationの発行中に呼び出される     */
/*               |   可能性があるため、変数やレジスタのアクセスが干渉しない */
/*               |   よう注意すること。                                     */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・送信要求されたデータ長がCANに設定可能なデータ長の上限  */
/*               |   を超えていた場合、フレーム種別に合わせ丸めて設定する。 */
/*               |   本設定がMPU仕様に違反していないか確認すること。        */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
Can_ReturnType
Can_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo )
{
    CanConst CanHohCfgType *  ptHohTbl;           /* HOHコンフィグ情報テーブルへのポインタ */
    CanMsgType                stMsg;              /* 送信メッセージ                        */
    uint32                    u4IdVal;            /* CAN ID                                */
    uint16                    u2ControllerStatus; /* コントローラ状態                      */
    uint16                    u2HthIdx;           /* 送信要求PDU ID情報のインデクス        */
    uint8                     u1Controller;       /* コントローラID                        */
    uint8                     u1Mbox;             /* MBOX番号                              */
    uint8                     u1DataLength;       /* データ長                              */
    uint8                     u1TxRet;            /* 送信処理結果                          */
    uint8                     u1Ret;              /* 戻り値                                */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    /* HTHに対応するコントローラの特定 */
    ptHohTbl = &( Can_tb_ptHohCfgTbl[ CAN_IDX0 ] );
    u1Controller = ptHohTbl[ Hth ].u1ControllerID;

    /* CANコントローラの開始チェック */
    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        /* ▼▼▼▼▼▼  割り込み禁止  ▼▼▼▼▼▼ */
        /* 送信要求～PDUIDセット～送信完了の順序を守るために割り込み禁止とする。 */
        /* DI状態でマイコン依存部をコールするため処理時間に留意する。            */
        Can_DI()

        /* 送信データのラッチ */
        u1DataLength = PduInfo->length;
        u4IdVal      = PduInfo->id;
        stMsg.ptData = PduInfo->sdu;

        /* フレーム種別の判定 */
        if ( ( u4IdVal & CAN_TX_ID_FDF_MSK ) == CAN_TX_ID_FDF_CANFD )
        {   /* CAN FDフレームの場合 */
            /* データ長の最大値チェック */
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CANFD )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CANFD;
            }
            stMsg.u1Length = u1DataLength;
            stMsg.u4Id     = u4IdVal;

            /* HTH→MBOX変換 */
            u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

            /* 送信要求 */
            u1TxRet = Can_tx_TxReq_CanFdFrame( u1Controller, u1Mbox, &stMsg );
        }
        else
        {   /* クラシカルCANフレームの場合 */
            /* データ長の最大値チェック */
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CAN )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CAN;
            }
            stMsg.u1Length = u1DataLength;
            stMsg.u4Id     = u4IdVal;

            /* HTH→MBOX変換 */
            u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

            /* 送信要求 */
            u1TxRet = Can_tx_TxReq_CanFrame( u1Controller, u1Mbox, &stMsg );
        }

        if ( u1TxRet == (uint8)CAN_PROC_OK )
        {
            /* 送信処理成功時 */
            /* 送信要求を受けたPDU IDの記憶 */
            /* HRH数を除いたHTH先頭からの連番を取得 */
            u2HthIdx  = (uint16)( Hth - Can_tb_u2HrhNumMax );
            Can_tx_u2TxPduId[ u2HthIdx ] = PduInfo->swPduHandle;
            u1Ret = (uint8)CAN_OK;
        }
        else if ( u1TxRet == (uint8)CAN_PROC_BUSY )
        {
            u1Ret = (uint8)CAN_BUSY;
        }
        else /* MISRA DEVIATION: no process */
        {   /* u1TxRet == (uint8)CAN_PROC_NG */
            /* CAN_NOT_OKを返却する */
        }

        Can_EI()
        /* ▲▲▲▲▲▲  割り込み許可  ▲▲▲▲▲▲ */
    }

    return (u1Ret);
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_MainFunction_Write                                   */
/* Description   | 送信定期処理                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・本APIはCANIFから呼び出されるため、CANIFの状態によって  */
/*               |   必ずしも定期的に呼び出されない。そのため、厳密な時間   */
/*               |   監視処理は実施しない。                                 */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_MainFunction_Write( void )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1Controller;           /* コントローラID   */
    uint8   u1ControllerNumMax;     /* コントローラ数   */

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* CANコントローラの開始チェック */
        /* CANコントローラが開始していない場合、受付しない。                */
        /* ※ 非制御対象CANに割当てられたコントローラも含め状態変数を持つ。 */
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* 制御対象CAN かつ 使用するコントローラに対し                  */
            /* 送信完了をチェックする。                                     */

            /* 制御対象CAN かつ 使用するコントローラか否かは                */
            /* コントローラ状態変数から判断する。                           */
            /* ※ 非制御対象CANの場合、Can_Init後 CAN_ST_CTRL_UNINIT で固定 */
            /*    制御対象CAN かつ 使用しないコントローラの場合は           */
            /*    Can_Init後、CAN_ST_CTRL_INIT で固定されるため             */
            /*    コンフィグ設定のチェックは不要。                          */

            /* 送信完了の確認実施 */
            /* ・コントローラに紐づくMBOXの内、ポーリングで処理する   */
            /*   ものに対し、送信完了発生を確認する。                 */
            /*   送信完了が発生していた場合、本関数内で               */
            /*   CanIf_TxConfirmationを発行し、CANIFに通知する。      */
            /* ・戻り値は不正割り込み確認用であり、ポーリング処理     */
            /*   では使用しない。                                     */
            (void)Can_tx_ChkTxFinMbox( u1Controller, (uint8)CAN_POLLING ); /* MISRA DEVIATION: no return check required */

#if (CAN_CFG_ABORTSEND == CAN_USE)
            /* 送信中断完了の確認                                     */
            /* ・コントローラに紐づくMBOX(割り込み、ポーリング共に)   */
            /*   に対する送信中断完了を確認する。                     */
            /*   送信中断完了が発生していた場合、本関数内で           */
            /*   CanIf_TxConfirmationを発行し、CANIFに通知する。      */
            /*   ※ なお、マイコンによって、同一のMBOXに対して        */
            /*      送信完了と送信中断完了が 同時に成立する、または   */
            /*      区別できないケースでは、CANIFに対する通知は       */
            /*      どちらか一方でのみ通知する。                      */
            Can_tx_ChkTxAbtMbox( u1Controller );

#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */
        }
    }
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_AbortSend                                            */
/* Description   | 送信中断要求                                             */
/* Preconditions | -                                                        */
/* Parameters    | Can_HwHandleType Hth :                                   */
/*               |   送信中断を要求するMBOXに対応した                       */
/*               |   Hardware Transmit Handle                               */
/* Return Value  | Can_ReturnType 要求受付結果                              */
/*               |  CAN_OK     : 要求受付                                   */
/*               |  CAN_NOT_OK : 要求不受理                                 */
/* Notes         | ・以下の場合、本APIは提供しない。                        */
/*               |   - 送信機能が未使用にコンフィグされている場合           */
/*               | ・以下の場合、本APIは空関数とし、要求不受理を応答する。  */
/*               |   - 送信中断機能が未使用にコンフィグされている場合       */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               | ・送信要求中のHTHに対してのみ処理要求される前提とする。  */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
Can_ReturnType
Can_AbortSend( Can_HwHandleType Hth )
{
#if (CAN_CFG_ABORTSEND == CAN_USE)
    CanConst CanHohCfgType *  ptHohTbl;           /* HOHコンフィグ情報テーブルへのポインタ */
    uint16                    u2ControllerStatus; /* コントローラ状態                      */
    uint16                    u2HthIdx;           /* 送信要求PDU ID情報のインデクス        */
    uint16                    u2TxPduId;          /* 送信完了したPDU ID                    */
    uint8                     u1AbtRet;           /* 送信中断実施結果                      */
    uint8                     u1Controller;       /* コントローラID                        */
    uint8                     u1Mbox;             /* MBOX番号                              */
    uint8                     u1Ret;              /* 戻り値                                */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_NOT_OK;

    /* HTHに対応するコントローラの特定 */
    ptHohTbl = &( Can_tb_ptHohCfgTbl[ CAN_IDX0 ] );
    u1Controller = ptHohTbl[ Hth ].u1ControllerID;

    /* CANコントローラの開始チェック */
    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        /* HTH→MBOX変換 */
        u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

        /* 送信中断実施 */
        u1AbtRet = Can_tx_TxAbt( u1Controller, u1Mbox );
        if ( u1AbtRet == (uint8)CAN_PROC_OK )
        {
            /* HRH数を除いたHTH先頭からの連番を取得 */
            u2HthIdx  = (uint16)( Hth - Can_tb_u2HrhNumMax );

            /* 送信完了したPDU IDのラッチ */
            u2TxPduId = Can_tx_u2TxPduId[ u2HthIdx ];

            /* Can_Writeは送信完了通知内で呼び出される可能性があるため               */
            /* CanIf_TxConfirmationを発行する前にRAMを初期値(無効値)に設定しておく。 */
            Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;

            /* 送信完了通知の発行 */
            CanIf_TxConfirmation( u2TxPduId );
        }

        /* 送信中断要求受付を応答 */
        u1Ret = (uint8)CAN_OK;
    }

    return ( u1Ret );
#else /* (CAN_CFG_ABORTSEND != CAN_USE) */
    return ( (uint8)CAN_NOT_OK );
#endif /* (CAN_CFG_ABORTSEND) */
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxReq                                                */
/* Description   | ユーザ送信要求                                           */
/* Preconditions | -                                                        */
/* Parameters    | uint8  u1Controller : 送信を要求するコントローラ         */
/*               | uint8  u1MsgBuffer  : 送信を要求するメッセージバッファ   */
/*               | CanMsgType* ptMsg   : 送信メッセージ                     */
/*               |   uint8* ptData     : 送信データへのポインタ             */
/*               |   uint32 u4Id       : CAN ID                             */
/*               |   uint8  u1Length   : データ長                           */
/* Return Value  | uint8 要求受付結果                                       */
/*               |   CAN_PROC_OK       : 要求が受け付けられた               */
/*               |   CAN_PROC_NG       : 要求が受け付けられなかった         */
/*               |   CAN_PROC_BUSY     : 他の要求を実行中                   */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/*               | ・ユーザ送信機能が未使用にコンフィグされている場合、     */
/*               |   本APIは提供しない。                                    */
/*               | ・本関数はCan_UTxConfirmationの発行中に呼び出される      */
/*               |   可能性があるため、変数やレジスタのアクセスが干渉しない */
/*               |   よう注意すること。                                     */
/*               | ・引数チェックは関数呼び出し元で実施するものとし、本関数 */
/*               |   内では実施しない。                                     */
/*               |   ただし、送信要求されたデータ長がCANに設定可能なデータ長*/
/*               |   の上限を超えていた場合、フレーム種別に合わせ丸めて     */
/*               |   設定する。本設定がMPU仕様に違反していないか確認する    */
/*               |   こと。                                                 */
/*               | ・引数で渡されるメッセージの内容は本処理が終了するまで   */
/*               |   更新されない前提とする。                               */
/*               | ・対象のメッセージバッファについては、複数のタスクから   */
/*               |   同時に要求されない前提とする。                         */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
uint8
Can_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg )
{
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1DataLength;           /* データ長         */
    uint8   u1Ret;                  /* 戻り値           */

    /* 戻り値初期化 */
    u1Ret = (uint8)CAN_PROC_NG;

    /* CANコントローラの開始チェック */
    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        /* データ長のラッチ */
        u1DataLength = ptMsg->u1Length;

        /* フレーム種別の判定 */
        if ( ( ptMsg->u4Id & CAN_TX_ID_FDF_MSK ) == CAN_TX_ID_FDF_CANFD )
        {   /* CAN FDフレームの場合 */
            /* データ長の最大値チェック */
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CANFD )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CANFD;
            }
            ptMsg->u1Length = u1DataLength;

             /* 送信要求 */
            u1Ret = Can_tx_TxReq_CanFdFrame( u1Controller, u1MsgBuffer, ptMsg );
        }
        else
        {   /* クラシカルCANフレームの場合 */
            /* データ長の最大値チェック */
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CAN )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CAN;
            }
            ptMsg->u1Length = u1DataLength;

             /* 送信要求 */
            u1Ret = Can_tx_TxReq_CanFrame( u1Controller, u1MsgBuffer, ptMsg );
        }
    }

    return ( u1Ret );
}
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_TxConfMbox                                        */
/* Description   | MBOX送信完了通知                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller : CANコントローラ番号                 */
/*               | uint8 u1Mbox       : 送信完了MBOX番号                    */
/* Return Value  | なし                                                     */
/* Notes         | ・送信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない。                                           */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_tx_TxConfMbox( uint8 u1Controller, uint8 u1Mbox )
{
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;       /* HOH-MBOX配置情報テーブルへのポインタ         */
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    CanConst CanTbUTxMbAllocType *  ptUTxMbAlloc;       /* ユーザ送信用MBOX配置情報テーブルへのポインタ */
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
    uint16                          u2Hoh;              /* HOH番号                                      */
    uint16                          u2HthOfs;           /* コントローラ毎HTH開始位置(HOH番号)           */
    uint16                          u2HthIdx;           /* 送信要求PDU ID情報のインデクス               */
    uint16                          u2TxPduId;          /* 送信完了したPDU ID                           */
    uint8                           u1HthMbOfs;         /* HTH用MBOX開始位置(MBOX番号)                  */
    uint8                           u1HthMbEnd;         /* HTH用MBOX終了位置(MBOX番号)                  */
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    uint8                           u1UTxMbOfs;         /* ユーザ送信用MBOX開始位置(MBOX番号)           */
    uint8                           u1UTxMbEnd;         /* ユーザ送信用MBOX終了位置(MBOX番号)           */
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */

    /* 送信完了メッセージがある場合は         */
    /* コントローラモード状態によらず通知する */

    /* HOH配置情報取得 */
    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HthOfs     = ptHohMbAlloc->u2HthOffset;
    u1HthMbOfs   = ptHohMbAlloc->u1HthMbOffset;
    u1HthMbEnd   = u1HthMbOfs + ptHohMbAlloc->u1HthNum;

#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    /* ユーザ送信用MBOX配置情報取得 */
    ptUTxMbAlloc = &( Can_tb_stUTxMbAlloc[ u1Controller ] );
    u1UTxMbOfs   = ptUTxMbAlloc->u1UTxMbOffset;
    u1UTxMbEnd   = u1UTxMbOfs + ptUTxMbAlloc->u1UTxMbNum;
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */

    if ( ( u1Mbox >= u1HthMbOfs ) && ( u1Mbox < u1HthMbEnd ) )
    {   /* HTH送信完了処理 */

        /* MBOX→HOH変換 */
        u2Hoh = ( ((uint16)u1Mbox - (uint16)u1HthMbOfs) + u2HthOfs );

        /* HRH数を除いたHTH先頭からの連番を取得 */
        u2HthIdx  = (uint16)( u2Hoh - Can_tb_u2HrhNumMax );

        /* 送信完了したPDU IDのラッチ */
        u2TxPduId = Can_tx_u2TxPduId[ u2HthIdx ];

        /* Can_Writeは送信完了通知内で呼び出される可能性があるため               */
        /* CanIf_TxConfirmationを発行する前にRAMを初期値(無効値)に設定しておく。 */
        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;

        /* 送信完了通知の発行 */
        CanIf_TxConfirmation( u2TxPduId );
    }
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    else if ( ( u1Mbox >= u1UTxMbOfs ) && ( u1Mbox < u1UTxMbEnd ) )
    {   /* ユーザ送信完了処理 */

        /* ユーザ送信完了通知 */
        Can_UTxConfirmation( u1Controller, u1Mbox );
    }
    else /* MISRA DEVIATION: no process */
    {
        /* 意図しない送信完了通知 */
        /* 破棄(処置なし)         */
    }
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/03/03                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
