/* Gdn_CanTp_Ucfg_c_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | ダイアグCAN通信トランスポート層（コンフィグ）                */
/* Notes       | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2019/12/03   AUBASS   Update                                    */
/*  00_0003   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_Ucfg.h>

#include <GdnWrapper/Gdn_TmrSrv.h>
#include <GdnWrapper/Gdn_CanIf.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_START_SEC_VAR
#include <Gdn_CanTp_MemMap.h>

#define GDN_CANTP_STOP_SEC_VAR
#include <Gdn_CanTp_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_START_SEC_CST
#include <Gdn_CanTp_MemMap.h>

/************************* 受信N_AIコンフィグテーブル *************************/
#if ( GDN_CANTP_MaxRxNAICnt == 0U )
GdnConst Gdn_CanTp_RxNAIInfoType    gdn_cantp_RxNAIInformation[1];
#else
GdnConst Gdn_CanTp_RxNAIInfoType    gdn_cantp_RxNAIInformation[GDN_CANTP_MaxRxNAICnt] = {
    {   /* 受信N_AI0のコンフィグ */
        GDN_CANTP_RxPduId0000              ,/* 受信PDUID           ：0..65535              */
        GDN_CANTP_Physical                 ,/* アドレスタイプ      ：Physical / Functional */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        GDN_TRUE                           ,/* パディング使用有無                          */
        (Gdn_CanTp_ChannelType)0U          ,/* 受信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)0U                      ,/* FCの送信N_AIのインデックス                  */
        (Gdn_CanTp_BlockSizeType)0U        ,/* ブロックサイズ(BS)  ：0..255                */
        (Gdn_CanTp_STminType)0U            ,/* STmin               ：0..127 (ms)           */
        (Gdn_TimeoutValueType)1000U        ,/* N_Arタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)150U         ,/* N_Br(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MIN)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)1000U        ,/* N_Crタイマ          ：1..65534 (ms)         */
        (Gdn_CanTp_WFTMaxType)0U           ,/* FC.WAIT上限(WFTMax) ：0..255                */
        GDN_PDUR_LoTpRxPduId_0_0            /* 受信SDUID（PduRの定義する値を使用する）     */
    },
    {   /* 受信N_AI1のコンフィグ */
        GDN_CANTP_RxPduId0001              ,/* 受信PDUID           ：0..65535              */
        GDN_CANTP_Functional               ,/* アドレスタイプ      ：Physical / Functional */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        GDN_TRUE                           ,/* パディング使用有無                          */
        (Gdn_CanTp_ChannelType)0U          ,/* 受信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)0U                      ,/* FCの送信N_AIのインデックス                  */
        (Gdn_CanTp_BlockSizeType)0U        ,/* ブロックサイズ(BS)  ：0..255                */
        (Gdn_CanTp_STminType)0U            ,/* STmin               ：0..127 (ms)           */
        (Gdn_TimeoutValueType)0U           ,/* N_Arタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MIN)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)1U           ,/* N_Crタイマ          ：1..65534 (ms)         */
        (Gdn_CanTp_WFTMaxType)0U           ,/* FC.WAIT上限(WFTMax) ：0..255                */
        GDN_PDUR_LoTpRxPduId_0_1            /* 受信SDUID（PduRの定義する値を使用する）     */
    },
    {   /* 受信N_AI2のコンフィグ */
        GDN_CANTP_RxPduId0002              ,/* 受信PDUID           ：0..65535              */
        GDN_CANTP_Physical                 ,/* アドレスタイプ      ：Physical / Functional */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        GDN_TRUE                           ,/* パディング使用有無                          */
        (Gdn_CanTp_ChannelType)0U          ,/* 受信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)1U                      ,/* FCの送信N_AIのインデックス                  */
        (Gdn_CanTp_BlockSizeType)0U        ,/* ブロックサイズ(BS)  ：0..255                */
        (Gdn_CanTp_STminType)0U            ,/* STmin               ：0..127 (ms)           */
        (Gdn_TimeoutValueType)1000U        ,/* N_Arタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)150U         ,/* N_Br(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MIN)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)1000U        ,/* N_Crタイマ          ：1..65534 (ms)         */
        (Gdn_CanTp_WFTMaxType)0U           ,/* FC.WAIT上限(WFTMax) ：0..255                */
        GDN_PDUR_LoTpRxPduId_0_2            /* 受信SDUID（PduRの定義する値を使用する）     */
    },
    {   /* 受信N_AI3のコンフィグ */
        GDN_CANTP_RxPduId0003              ,/* 受信PDUID           ：0..65535              */
        GDN_CANTP_Functional               ,/* アドレスタイプ      ：Physical / Functional */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        GDN_TRUE                           ,/* パディング使用有無                          */
        (Gdn_CanTp_ChannelType)0U          ,/* 受信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)0U                      ,/* FCの送信N_AIのインデックス                  */
        (Gdn_CanTp_BlockSizeType)0U        ,/* ブロックサイズ(BS)  ：0..255                */
        (Gdn_CanTp_STminType)0U            ,/* STmin               ：0..127 (ms)           */
        (Gdn_TimeoutValueType)0U           ,/* N_Arタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Br(MIN)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)1U           ,/* N_Crタイマ          ：1..65534 (ms)         */
        (Gdn_CanTp_WFTMaxType)0U           ,/* FC.WAIT上限(WFTMax) ：0..255                */
        GDN_PDUR_LoTpRxPduId_0_3            /* 受信SDUID（PduRの定義する値を使用する）     */
    }
};
#endif

/************************* 送信N_AIコンフィグテーブル *************************/
#if ( GDN_CANTP_MaxTxNAICnt == 0U )
GdnConst Gdn_CanTp_TxNAIInfoType    gdn_cantp_TxNAIInformation[1];
#else
GdnConst Gdn_CanTp_TxNAIInfoType    gdn_cantp_TxNAIInformation[GDN_CANTP_MaxTxNAICnt] = {
    {   /* 送信N_AI0のコンフィグ */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        (Gdn_CanTp_PaddingValueType)0xCCU  ,/* パディングバイトの値（常時有効）            */
        (Gdn_CanTp_ChannelType)0U          ,/* 送信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)0U                      ,/* FCの受信N_AIのインデックス                  */
        (Gdn_TimeoutValueType)1000U        ,/* N_Asタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)1000U        ,/* N_Bsタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)150U         ,/* N_Cs(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Cs(Delay)タイマ   ：0..65534 (ms)         */
        GDN_CANIF_CanTpTxPduId0000          /* 送信PDUID（CanIfの定義する値を使用する）    */
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        ,(Gdn_PduLengthType)32U             /* 送信サイズ(8,12,16,20,24,32,48,64から選択)  */
#endif
    },
    {   /* 送信N_AI1のコンフィグ */
        GDN_CANTP_Normal                   ,/* アドレスフォーマット：Normal / Extended     */
        (Gdn_CanTp_TargetAddressType)0x00U ,/* N_TAの値（Extended選択時のみ有効）          */
        (Gdn_CanTp_PaddingValueType)0xCCU  ,/* パディングバイトの値（常時有効）            */
        (Gdn_CanTp_ChannelType)0U          ,/* 送信チャネル                                */
        (Gdn_CanTp_PriorityType)0U         ,/* N_AIの優先度        ：高 0..255 低          */
        (gdn_uint8)2U                      ,/* FCの受信N_AIのインデックス                  */
        (Gdn_TimeoutValueType)1000U        ,/* N_Asタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)1000U        ,/* N_Bsタイマ          ：1..65534 (ms)         */
        (Gdn_TimeoutValueType)150U         ,/* N_Cs(MAX)タイマ     ：0..65534 (ms)         */
        (Gdn_TimeoutValueType)0U           ,/* N_Cs(Delay)タイマ   ：0..65534 (ms)         */
        GDN_CANIF_CanTpTxPduId0001          /* 送信PDUID（CanIfの定義する値を使用する）    */
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        ,(Gdn_PduLengthType)8U             /* 送信サイズ(8,12,16,20,24,32,48,64から選択)  */
#endif
    }
};
#endif

/************************* タイマIDコンフィグテーブル *************************/
GdnConst Gdn_TimerIdType gdn_cantp_TimerId[GDN_CANTP_MaxChannelCnt][GDN_CANTP_TimerCnt] = {
      /* MaxTimerId */          /* MinTimerId */
    { GDN_TMRSRV_ID_CANTP_1 , GDN_TMRSRV_ID_CANTP_0  }  /* チャネル0のタイマ */
};

#define GDN_CANTP_STOP_SEC_CST
#include <Gdn_CanTp_MemMap.h>

/**** End of File *************************************************************/

