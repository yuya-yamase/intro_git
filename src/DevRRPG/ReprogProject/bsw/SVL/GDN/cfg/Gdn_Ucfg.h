/* Gdn_Ucfg_h_01_0006 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | GUARDIAN ユーザコンフィグ                                    */
/* Notes       | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/30   DN 毛    テンプレート新規作成                      */
/*  00_0001   2014/08/22   DN 毛    サービス27追加要件対応                    */
/*  00_0002   2014/09/25   DT       サービス11/14/19_06追加                   */
/*  00_0003   2015/08/31   DC       DataId動的サポート判定対応                */
/*  00_0004   2015/10/02   DN 野田  DTR用ラベル名にUaSId追加                  */
/*                                  FIM用GroupIdのラベル情報生成              */
/*  01_0000   2016/01/07   DN 野田  マルチコア用ラベル追加                    */
/*                                  Service23メモリアドレス5byte以上設定追加  */
/*                         DC       アプリクリア失敗の否定応答対応            */
/*                                  標準フリーズの法規外対応                  */
/*  01_0001   2016/01/14   DN 野田  各DataIdサポート情報用ラベル追加          */
/*                                  各DataIdデータサイズ用ラベル追加          */
/*  01_0002   2016/02/18   DN 野田  MSとの結合対応                            */
/*  01_0003   2018/02/13   AUBASS   リプログ対応                              */
/*  01_0004   2018/12/11   AUBASS   Update                                    */
/*  01_0005   2019/12/03   AUBASS   Update                                    */
/*  01_0006   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_UCFG_H
#define GDN_UCFG_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/


/************************ GUARDIAN COMPONENT SELECTION ************************/
#define GDN_CMPSELECT_PDUR      (GDN_ON)
#define GDN_CMPSELECT_CANTP     (GDN_ON)
#define GDN_CMPSELECT_DCM_DSP   (GDN_ON)

/*************************** BSW FUNCTION CONFIG *******************************/
#define GDN_DEQUEUENUM_TIMEOUT              (0U)

/***************************** CANTP CONFIG START *****************************/
    /* CANTP機能設定 */
#define GDN_CANTP_MaxChannelCnt        (1U)        /* 送受信で使用するチャネル数 */
#define GDN_CANTP_ChangeParameterApi   (GDN_ON)    /* パラメータ変更機能のサポート有無 */
#define GDN_CANTP_FullDuplexSupport    (GDN_OFF)   /* 全2重通信のサポート有無はOFF固定 */
#define GDN_CANTP_CanFDSupport         (GDN_ON)    /* CanFD送受信のサポート有無 */

#define GDN_CANTP_FixedPar             (1)         /* FC受信時に、固定のBSとSTminを使用する */
#define GDN_CANTP_FirstPar             (2)         /* FC受信時に、最初のBSとSTminを使用する */
#define GDN_CANTP_LatestPar            (3)         /* FC受信時に、最新のBSとSTminを使用する */
#define GDN_CANTP_ParameterPattern     (GDN_CANTP_FirstPar)
#define GDN_CANTP_BSFixedValue         (0U)        /* Fixed選択時のみ有効 */
#define GDN_CANTP_STminFixedValue      (0U)        /* Fixed選択時のみ有効 */

#define GDN_CANTP_FailSafeMax          (1)         /* μsオーダーのSTminを最大値とみなす */
#define GDN_CANTP_FailSafeMin          (2)         /* μsオーダーのSTminを最小値とみなす */
#define GDN_CANTP_STminFailPattern     (GDN_CANTP_FailSafeMin)

    /* 受信PDUID定義（CANIFへ公開） */
#define GDN_CANTP_RxPduId0000          ((Gdn_PduIdType)0x0000U)
#define GDN_CANTP_RxPduId0001          ((Gdn_PduIdType)0x0001U)
#define GDN_CANTP_RxPduId0002          ((Gdn_PduIdType)0x0002U)
#define GDN_CANTP_RxPduId0003          ((Gdn_PduIdType)0x0003U)
#define GDN_CANTP_MaxRxPduIdCnt        (4U)        /* 受信PduId数 */

    /* 送信SDUID定義（PDURへ公開） */
#define GDN_CANTP_TxSduId0000          ((Gdn_PduIdType)0x0000U)
#define GDN_CANTP_TxSduId0001          ((Gdn_PduIdType)0x0001U)
#define GDN_CANTP_MaxTxSduIdCnt        (2U)        /* 送信SduId数 */

    /* 受信N_AI数 */
#define GDN_CANTP_MaxRxNAICnt          (GDN_CANTP_MaxRxPduIdCnt)

    /* 送信N_AI数 */
#define GDN_CANTP_MaxTxNAICnt          (GDN_CANTP_MaxTxSduIdCnt)
/****************************** CANTP CONFIG END ******************************/


/*************************** PDUROUTER CONFIG START ***************************/
    /*----------------------------------*/
    /*      PDUR_Network層機能設定      */
    /*----------------------------------*/
#define GDN_PDUR_UsePduR_Nw              (GDN_OFF)   /* PduRネットワーク層機能のサポート有無 */
#define GDN_PDUR_OnlyZeroCost_Nw         (GDN_OFF)   /* PduRネットワーク層機能のゼロコストコードサポート有無 */
      /* 以下の設定はZeroCost使用時にOFFとする */
#define GDN_PDUR_LoLayerReceive_Nw       (GDN_OFF)   /* 下位ネットワーク層の受信通知サポート有無 */
#define GDN_PDUR_UpLayerTransmit_Nw      (GDN_OFF)   /* 上位ネットワーク層の送信要求サポート有無 */
#define GDN_PDUR_CancelTransmitApi_Nw    (GDN_OFF)   /* 上位ネットワーク層の送信中止要求サポート有無 */
#define GDN_PDUR_TriggerTransmitApi_Nw   (GDN_OFF)   /* 下位ネットワーク層の送信要求トリガーサポート有無 */
#define GDN_PDUR_TxConfirmationApi_Nw    (GDN_OFF)   /* 下位ネットワーク層の送信完了通知サポート有無 */

    /*----------------------------------*/
    /*     PDUR_Transport層機能設定     */
    /*----------------------------------*/
#define GDN_PDUR_UsePduR_Tp              (GDN_ON)    /* PduRトランスポート層機能のサポート有無 */
#define GDN_PDUR_OnlyZeroCost_Tp         (GDN_ON)    /* PduRトランスポート層機能のゼロコストコードサポート有無 */
#define GDN_PDUR_MaxLoLayerCnt_Tp        (1U)        /* トランスポート層の下位コンポーネント数 */
      /* 以下の設定はZeroCost使用時にOFFとする */
#define GDN_PDUR_LoLayerReceive_Tp       (GDN_OFF)   /* 下位トランスポート層の受信通知サポート有無 */
#define GDN_PDUR_LoLayerGateway_Tp       (GDN_OFF)   /* 下位トランスポート層のゲートウェイサポート有無 */
#define GDN_PDUR_UpLayerTransmit_Tp      (GDN_OFF)   /* 上位トランスポート層の送信サポート有無 */
#define GDN_PDUR_CancelTransmitApi_Tp    (GDN_OFF)   /* 上位トランスポート層の送信中止要求サポート有無 */
#define GDN_PDUR_CancelReceiveApi_Tp     (GDN_OFF)   /* 上位トランスポート層の受信中止要求サポート有無 */
#define GDN_PDUR_ChangeParameterApi_Tp   (GDN_OFF)   /* 上位トランスポート層のパラメータ変更要求サポート有無 */

    /*----------------------------------*/
    /*  PDUR_下位Network層のコンフィグ  */
    /*----------------------------------*/
        /********************/
        /* コンポーネント#0 */
        /********************/
#define GDN_PDUR_UseZeroCost_LoNw_0       (GDN_OFF)  /* 下位ネットワーク層のゼロコストコードサポート有無 */
#define GDN_PDUR_MaxRxPduIdCnt_LoNw_0     (0U)       /* 下位ネットワーク層の受信PduId数 */
#define GDN_PDUR_MaxTxPduIdCnt_LoNw_0     (0U)       /* 下位ネットワーク層の送信PduId数 */
#define GDN_PDUR_ComponentName_LoNw_0     CanIf      /* 下位ネットワーク層のコンポーネント名 */
#define GDN_PDUR_TriggerTransmit_LoNw_0   (GDN_OFF)  /* 下位ネットワーク層の送信要求トリガー有無 */
#define GDN_PDUR_TxConfirmation_LoNw_0    (GDN_OFF)  /* 下位ネットワーク層の送信完了通知サポート有無 */

        /* 受信PduId定義（下位Network層へ公開） */
/* #define GDN_PDUR_LoNwRxPduId_##_##          ((Gdn_PduIdType)0x0000U) */

  #if ( GDN_PDUR_UseZeroCost_LoNw_0 == GDN_ON ) /* ゼロコスト使用時 */

  #else                                         /* ゼロコスト不使用 */
        /* 以下 MaxRxPduIdCntが1以上の場合のみ有効 */

        /* 以下 MaxTxPduIdCntが1以上の場合のみ有効 */

  #endif

    /*----------------------------------*/
    /*  PDUR_上位Network層のコンフィグ  */
    /*----------------------------------*/

    /*----------------------------------*/
    /* PDUR_下位Transport層のコンフィグ */
    /*----------------------------------*/
        /********************/
        /* コンポーネント#0 */
        /********************/
#define GDN_PDUR_UseZeroCost_LoTp_0      (GDN_ON)    /* 下位トランスポート層のゼロコストコードサポート有無 */

  #if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON ) /* サブマイコン使用(サブマイコン) */

#define GDN_PDUR_MaxRxPduIdCnt_LoTp_0    (1U)        /* 下位トランスポート層の受信PduId数 */
#define GDN_PDUR_MaxTxPduIdCnt_LoTp_0    (1U)        /* 下位トランスポート層の送信PduId数 */
#define GDN_PDUR_ComponentName_LoTp_0    SubMinconIf /* 下位トランスポート層のコンポーネント名 */

        /* 受信PduId定義（下位Transport層へ公開） */
#define GDN_PDUR_LoTpRxPduId_0_0         (GDN_DCM_DCP_RXPDUID_0)
#define GDN_PDUR_LoTpRxPduId_0_1         (GDN_DCM_DCP_RXPDUID_1)

  #else                                         /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

#define GDN_PDUR_MaxRxPduIdCnt_LoTp_0    (4U)        /* 下位トランスポート層の受信PduId数 */
#define GDN_PDUR_MaxTxPduIdCnt_LoTp_0    (2U)        /* 下位トランスポート層の送信PduId数 */
#define GDN_PDUR_ComponentName_LoTp_0    CanTp       /* 下位トランスポート層のコンポーネント名 */

        /* 受信PduId定義（下位Transport層へ公開） */
#define GDN_PDUR_LoTpRxPduId_0_0         (GDN_DCM_DCP_RXPDUID_0)
#define GDN_PDUR_LoTpRxPduId_0_1         (GDN_DCM_DCP_RXPDUID_1)
#define GDN_PDUR_LoTpRxPduId_0_2         (GDN_DCM_DCP_RXPDUID_2)
#define GDN_PDUR_LoTpRxPduId_0_3         (GDN_DCM_DCP_RXPDUID_3)

  #endif

  #if ( GDN_PDUR_UseZeroCost_LoTp_0 == GDN_ON ) /* ゼロコスト使用時 */

    #if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )   /* サブマイコン使用(サブマイコン) */

    /* 受信開始通知 */
#define Gdn_PduR_SubMiconIfStartOfReception (Gdn_Dcm_StartOfReception)
    /* 受信データコピー要求 */
#define Gdn_PduR_SubMiconIfCopyRxData       (Gdn_Dcm_CopyRxData)
    /* 受信完了通知 */
#define Gdn_PduR_SubMiconIfRxIndication     (Gdn_Dcm_TpRxIndication)
    /* 送信データコピー要求 */
#define Gdn_PduR_SubMiconIfCopyTxData       (Gdn_Dcm_CopyTxData)
    /* 送信完了通知 */
#define Gdn_PduR_SubMiconIfTxConfirmation   (Gdn_Dcm_TpTxConfirmation)

#define Gdn_PduR_CanTpStartOfReception      (Gdn_Dcm_StartOfReception)
#define Gdn_PduR_CanTpCopyRxData            (Gdn_Dcm_CopyRxData)
#define Gdn_PduR_CanTpRxIndication          (Gdn_Dcm_TpRxIndication)
#define Gdn_PduR_CanTpCopyTxData            (Gdn_Dcm_CopyTxData)
#define Gdn_PduR_CanTpTxConfirmation        (Gdn_Dcm_TpTxConfirmation)

    #else                                           /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

    /* 受信開始通知 */
#define Gdn_PduR_CanTpStartOfReception   (Gdn_Dcm_StartOfReception)
    /* 受信データコピー要求 */
#define Gdn_PduR_CanTpCopyRxData         (Gdn_Dcm_CopyRxData)
    /* 受信完了通知 */
#define Gdn_PduR_CanTpRxIndication       (Gdn_Dcm_TpRxIndication)
    /* 送信データコピー要求 */
#define Gdn_PduR_CanTpCopyTxData         (Gdn_Dcm_CopyTxData)
    /* 送信完了通知 */
#define Gdn_PduR_CanTpTxConfirmation     (Gdn_Dcm_TpTxConfirmation)

    #endif

  #else                                         /* ゼロコスト不使用 */

        /* 以下 MaxRxPduIdCntが1以上の場合のみ有効 */
          /* LoTpRxPduId0のルーティング情報 */
#define GDN_PDUR_GwDstCnt_LoTp_0_0       (0U)   /* ゲートウェイによる下位トランスポート層受信情報の転送数 */
#define GDN_PDUR_GwBufSize_LoTp_0_0      (0U)   /* 下位トランスポート層受信情報のゲートウェイバッファサイズ */
            /* 上位Transport層受信の転送先 */
#define GDN_PDUR_UpStartIF_LoTp_0_0      (Gdn_Dcm_StartOfReception)
#define GDN_PDUR_UpCopyRxIF_LoTp_0_0     (Gdn_Dcm_CopyRxData)
#define GDN_PDUR_UpRxIndIF_LoTp_0_0      (Gdn_Dcm_TpRxIndication)
            /* 下位トランスポート層受信情報の上位転送PduId */
#define GDN_PDUR_UpRxPduId_LoTp_0_0      (GDN_DCM_DCP_RXPDUID_0)

    #if ( (REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) )   /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

            /* 下位Transport層送信の転送先 */
              /* GwDstCntが1以上の場合のみ有効 */
          /* LoTpRxPduId1のルーティング情報 */
#define GDN_PDUR_GwDstCnt_LoTp_0_1       (0U)   /* ゲートウェイによる下位トランスポート層受信情報の転送数 */
#define GDN_PDUR_GwBufSize_LoTp_0_1      (0U)   /* 下位トランスポート層受信情報のゲートウェイバッファサイズ */
            /* 上位Transport層受信の転送先 */
#define GDN_PDUR_UpStartIF_LoTp_0_1      (Gdn_Dcm_StartOfReception)
#define GDN_PDUR_UpCopyRxIF_LoTp_0_1     (Gdn_Dcm_CopyRxData)
#define GDN_PDUR_UpRxIndIF_LoTp_0_1      (Gdn_Dcm_TpRxIndication)
            /* 下位トランスポート層受信情報の上位転送PduId */
#define GDN_PDUR_UpRxPduId_LoTp_0_1      (GDN_DCM_DCP_RXPDUID_1)

    #endif

        /* 以下 MaxTxPduIdCntが1以上の場合のみ有効 */
          /* LoTpTxPduId0のルーティング情報 */
#define GDN_PDUR_LoTxPduId_LoTp_0_0      (GDN_CANTP_TxSduId0000)
#define GDN_PDUR_UpCopyTxIF_LoTp_0_0     (Gdn_Dcm_CopyTxData)
#define GDN_PDUR_UpTxConIF_LoTp_0_0      (Gdn_Dcm_TpTxConfirmation)
#define GDN_PDUR_UpTxPduId_LoTp_0_0      (GDN_PDUR_UpTpTxPduId_0_0)
#define GDN_PDUR_LoSrcCmpId_LoTp_0_0     (0U)
#define GDN_PDUR_LoSrcPduId_LoTp_0_0     ((Gdn_PduIdType)0U)
#define GDN_PDUR_LoSrcGwIdx_LoTp_0_0     ((Gdn_PduIdType)0U)

  #endif

    /*----------------------------------*/
    /* PDUR_上位Transport層のコンフィグ */
    /*----------------------------------*/
        /********************/
        /* コンポーネント#0 */
        /********************/
#define GDN_PDUR_UseZeroCost_UpTp_0       (GDN_ON)  /* 上位トランスポート層のゼロコストコードサポート有無 */
#define GDN_PDUR_MaxRxPduIdCnt_UpTp_0     (4U)      /* 上位トランスポート層の受信PduId数 */
#define GDN_PDUR_MaxTxPduIdCnt_UpTp_0     (2U)      /* 上位トランスポート層の送信PduId数 */
#define GDN_PDUR_ComponentName_UpTp_0     Dcm       /* 上位トランスポート層のコンポーネント名 */
#define GDN_PDUR_CancelReceive_UpTp_0     (GDN_OFF)  /* 上位トランスポート層の受信中止要求サポート有無 */
#define GDN_PDUR_ChangeParameter_UpTp_0   (GDN_OFF) /* 上位トランスポート層のパラメータ変更要求サポート有無 */
#define GDN_PDUR_CancelTransmit_UpTp_0    (GDN_OFF)  /* 上位トランスポート層の送信中止要求サポート有無 */

        /* 送信PduId定義（上位Transport層へ公開） */
#define GDN_PDUR_UpTpTxPduId_0_0          (GDN_CANTP_TxSduId0000)
#define GDN_PDUR_UpTpTxPduId_0_1          (GDN_CANTP_TxSduId0000)
#define GDN_PDUR_UpTpTxPduId_0_2          (GDN_CANTP_TxSduId0001)
#define GDN_PDUR_UpTpTxPduId_0_3          (GDN_CANTP_TxSduId0001)

  #if ( GDN_PDUR_UseZeroCost_UpTp_0 == GDN_ON ) /* ゼロコスト使用時 */

    #if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )   /* サブマイコン使用(サブマイコン) */

    /* 受信中止要求 */
#define Gdn_PduR_DcmCancelReceive(RxSduId)  (PduR_CancelReceive((RxSduId)))
    /* 送信要求 */
#define Gdn_PduR_DcmTransmit(Id, TxInfoPtr) (SubMiconIf_Sub_Transmit((Id), (TxInfoPtr)))
    /* 送信中止要求 */
#define Gdn_PduR_DcmCancelTransmit(TxSduId) (PduR_CancelTransmit((TxSduId)))

    #else                                           /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

    /* 受信中止要求 */
#define Gdn_PduR_DcmCancelReceive         (Gdn_CanTp_CancelReceive)
    /* 送信要求 */
#define Gdn_PduR_DcmTransmit              (Gdn_CanTp_Transmit)
    /* 送信中止要求 */
#define Gdn_PduR_DcmCancelTransmit        (Gdn_CanTp_CancelTransmit)
    /* 受信パラメータ変更要求 */
#define Gdn_PduR_DcmChangeParameter       (Gdn_CanTp_ChangeParameter)

    #endif

  #else                                         /* ゼロコスト不使用 */

        /* 以下 MaxRxPduIdCntが1以上の場合のみ有効 */
        /* UpTpRxPduId0のルーティング情報 */
#define GDN_PDUR_UpRxPduId_UpTp_0_0       (GDN_DCM_DCP_RXPDUID_0)
#define GDN_PDUR_LoCancelRxIF_UpTp_0_0    (GDN_NULL_PTR)
#define GDN_PDUR_LoChgParaIF_UpTp_0_0     (GDN_NULL_PTR)
#define GDN_PDUR_LoRxPduId_UpTp_0_0       (GDN_PDUR_LoTpRxPduId_0_0)

    #if ( (REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) )   /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

        /* UpTpRxPduId1のルーティング情報 */
#define GDN_PDUR_UpRxPduId_UpTp_0_1       (GDN_DCM_DCP_RXPDUID_1)
#define GDN_PDUR_LoCancelRxIF_UpTp_0_1    (GDN_NULL_PTR)
#define GDN_PDUR_LoChgParaIF_UpTp_0_1     (GDN_NULL_PTR)
#define GDN_PDUR_LoRxPduId_UpTp_0_1       (GDN_PDUR_LoTpRxPduId_0_1)

    #endif

    #if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )   /* サブマイコン使用(サブマイコン) */

        /* 以下 MaxTxPduIdCntが1以上の場合のみ有効 */
          /* UpTpTxPduId0のルーティング情報 */
#define GDN_PDUR_LoTransIF_UpTp_0_0       (SubMiconIf_Sub_Transmit)
#define GDN_PDUR_LoCancelTxIF_UpTp_0_0    (GDN_NULL_PTR)
#define GDN_PDUR_LoTxPduId_UpTp_0_0       (GDN_SUBMICONIF_TxSduId0000)

    #else                                           /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

        /* 以下 MaxTxPduIdCntが1以上の場合のみ有効 */
          /* UpTpTxPduId0のルーティング情報 */
#define GDN_PDUR_LoTransIF_UpTp_0_0       (Gdn_CanTp_Transmit)
#define GDN_PDUR_LoCancelTxIF_UpTp_0_0    (GDN_NULL_PTR)
#define GDN_PDUR_LoTxPduId_UpTp_0_0       (GDN_CANTP_TxSduId0000)

    #endif

  #endif


/**************************** PDUROUTER CONFIG END ****************************/


/****************************** DCM CONFIG START ******************************/
/*--------------------------------------*/
/* セッションコンフィグレーション       */
/*--------------------------------------*/

/* セッション数の設定 */
#define GDN_DCM_SESSIONCTRL_SUPPORT_NUM        (2U)

/* セッション BS/STmin切替機能の設定 */

  #if ( (REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) )    /* サブマイコン未使用又はサブマイコン使用(メインマイコン) */

#define GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE   (GDN_ON)

  #else    /* サブマイコン使用(サブマイコン) */

#define GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE   (GDN_OFF)

  #endif

/* セッション_## */                                                                           /* 【制約】デフォルトセッションは0固定 */
#define GDN_DCM_SESSIONCTRL_0                  (GDN_DCM_DEFAULT_SESSION)    /* defaultSession(0x01)                */
#define GDN_DCM_SESSIONCTRL_1                  (GDN_DCM_REPROG_SESSION)     /* programmingSession(0x02)            */
#define GDN_DCM_SESSIONCTRL_KIND_0             (GDN_DCM_ChangeSesCtrl)      /* セッション状態種別                  */
#define GDN_DCM_SESSIONCTRL_KIND_1             (GDN_DCM_ChangeSesCtrl)      /* セッション状態種別                  */
#define GDN_DCM_P2MAX_TIMECNT_0                (2U)                         /* P2MAX時間 (LSB:1ms)                 */
#define GDN_DCM_P2MAX_TIMECNT_1                (2U)                         /* P2MAX時間 (LSB:1ms)                 */
#define GDN_DCM_P2MAX_ASTER_EX_TIMECNT_0       (2000U/GDN_DCM_P2MAXASTER_LSB)   /* P2*EX時間 (NRC0x78-NRC0x78間隔) (LSB:10ms) */
#define GDN_DCM_P2MAX_ASTER_EX_TIMECNT_1       (2000U/GDN_DCM_P2MAXASTER_LSB)   /* P2*EX時間 (NRC0x78-NRC0x78間隔) (LSB:10ms) */
#define GDN_DCM_S3TIMER_ENABLE_0               (GDN_FALSE)                  /* S3タイマ動作                        */
#define GDN_DCM_S3TIMER_ENABLE_1               (GDN_TRUE)                   /* S3タイマ動作                        */
#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
/* セッション毎のBS値 */
#define GDN_DCM_BS_VALUE_PER_SESSION_0         (0x00U)
#define GDN_DCM_BS_VALUE_PER_SESSION_1         (0x00U)
/* セッション毎のSTmin値 */
#define GDN_DCM_STMIN_VALUE_PER_SESSION_0      (0x00U)
#define GDN_DCM_STMIN_VALUE_PER_SESSION_1      (0x00U)
#endif

/******************************* DCM CONFIG END *******************************/


/****************************** DCP CONFIG START ******************************/
/*--------------------------------------*/
/* SID共通コンフィグレーション          */
/*--------------------------------------*/

/* 実行時間フェールセーフタイプの設定 */
#define GDN_DCM_DCP_PROCESS_FAILSAFE_NRC78CNT                 (0U)
#define GDN_DCM_DCP_PROCESS_FAILSAFE_P4                       (1U)
#define GDN_DCM_DCP_PROCESS_FAILSAFE_NON                      (2U)
#define GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE                     (GDN_DCM_DCP_PROCESS_FAILSAFE_NRC78CNT)
#define GDN_DCM_DCP_PROCESS_FAILSAFE_OBDRESPONSE_ENABLE       (GDN_OFF)

/* タイマの設定 */
#define GDN_DCM_DCP_S3_TIMER_ID                               (GDN_TMRSRV_ID_DCP_0)   /* S3serverタイマID                 */
#define GDN_DCM_DCP_S3_TIMECNT                                (5000U)                 /* S3serverタイマ値 (LSB:1ms)       */
#define GDN_DCM_DCP_P4_TIMER_ID                               (GDN_TMRSRV_ID_DCP_1)   /* P4serverタイマID                 */
#define GDN_DCM_DCP_P4_TIMECNT                                (180000U)               /* P4serverタイマ値 (LSB:1ms)       */
#define GDN_DCM_DCP_P2_TIMER_ID                               (GDN_TMRSRV_ID_DCP_2)   /* P2serverタイマID                 */
#define GDN_DCM_DCP_P2_ADJUST_TIMERCNT                        (0U)                    /* P2,P2*Exタイマ調整時間 (LSB:1ms) */
#if ( GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_NRC78CNT )
#define GDN_DCM_DCP_RESP_MAX_NUM_RESP_PENDING                 (90U)                   /* NRC0x78最大回数(MAX:255回)       */
#endif

/* 応答有無の設定 */
#define GDN_DCM_DCP_SUPPRESS_RES_FUNC_EX                      (GDN_OFF)               /* 機能アドレス要求時の応答有無     */

/* バッファサイズの設定 */
#define GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE                     (4096U + 16U)

/* 送受信面数の設定 */
#if ( REPROG_CFG_PARALLEL_ENABLE == STD_ON )
#define GDN_DCM_DCP_RXTX_AREA_NUM                     (2U)
#else
#define GDN_DCM_DCP_RXTX_AREA_NUM                     (1U)
#endif

/*--------------------------------------*/
/* 調停コンフィグレーション             */
/*--------------------------------------*/

/* 調停共通設定 */
#define GDN_DCM_DCP_PRIORITY_BEFORE                         (0U)
#define GDN_DCM_DCP_PRIORITY_AFTER                          (1U)
#define GDN_DCM_DCP_SAME_CONNECTION_PRIORITY_ACTION         (GDN_DCM_DCP_PRIORITY_BEFORE)  /* 同優先度Connectionの判定(前優先/後優先)                          */
#define GDN_DCM_DCP_PRIORITY_JUDGE_ENABLE_BY_SID            (GDN_OFF)                      /* OBDSID,Non-OBDSIDによる優先度判定（する/しない）                 */
#define GDN_DCM_DCP_DEFAULTSESSION_TRANS_ON_CLIENT_CHANGE   (GDN_OFF)                      /* Client切り替わり時にデフォルトセッション遷移（する/しない）      */

/*--------------------------------------*/
/* コネクションコンフィグレーション     */
/*--------------------------------------*/
#define GDN_DCM_DCP_ALL_CONNECTION_NUM                 (4U)     /* DcmDcpConnection数 */
#define GDN_DCM_DCP_ALL_RXPDUID_NUM                    (4U)     /* 全DcmRxPduId数     */

/* DcmRxPduId定義 */
#define GDN_DCM_DCP_RXPDUID_0                          ((Gdn_PduIdType)0U)
#define GDN_DCM_DCP_RXPDUID_1                          ((Gdn_PduIdType)1U)
#define GDN_DCM_DCP_RXPDUID_2                          ((Gdn_PduIdType)2U)
#define GDN_DCM_DCP_RXPDUID_3                          ((Gdn_PduIdType)3U)

/* DcmTxConfPduId定義 */
#define GDN_DCM_DCP_TXCONFPDUID_0                      (GDN_PDUR_UpTpTxPduId_0_0)
#define GDN_DCM_DCP_TXCONFPDUID_1                      (GDN_PDUR_UpTpTxPduId_0_1)
#define GDN_DCM_DCP_TXCONFPDUID_2                      (GDN_PDUR_UpTpTxPduId_0_2)
#define GDN_DCM_DCP_TXCONFPDUID_3                      (GDN_PDUR_UpTpTxPduId_0_3)

/* DcmTxPduIdRef定義 */
#define GDN_DCM_DCP_TXPDUID_REF_0                      (GDN_PDUR_UpTpTxPduId_0_0)
#define GDN_DCM_DCP_TXPDUID_REF_1                      (GDN_PDUR_UpTpTxPduId_0_1)
#define GDN_DCM_DCP_TXPDUID_REF_2                      (GDN_PDUR_UpTpTxPduId_0_2)
#define GDN_DCM_DCP_TXPDUID_REF_3                      (GDN_PDUR_UpTpTxPduId_0_3)

/* DcmDcpConnectionId_## */
#define GDN_DCM_DCP_CONNECTION_0_PRIORITY              (0U)
#define GDN_DCM_DCP_CONNECTION_1_PRIORITY              (0U)
#define GDN_DCM_DCP_CONNECTION_2_PRIORITY              (0U)
#define GDN_DCM_DCP_CONNECTION_3_PRIORITY              (0U)
#define GDN_DCM_DCP_CONNECTION_0_TXCONF_ID             (GDN_DCM_DCP_TXCONFPDUID_0)
#define GDN_DCM_DCP_CONNECTION_1_TXCONF_ID             (GDN_DCM_DCP_TXCONFPDUID_1)
#define GDN_DCM_DCP_CONNECTION_2_TXCONF_ID             (GDN_DCM_DCP_TXCONFPDUID_2)
#define GDN_DCM_DCP_CONNECTION_3_TXCONF_ID             (GDN_DCM_DCP_TXCONFPDUID_3)
#define GDN_DCM_DCP_CONNECTION_0_TXREF_ID              (GDN_DCM_DCP_TXPDUID_REF_0)
#define GDN_DCM_DCP_CONNECTION_1_TXREF_ID              (GDN_DCM_DCP_TXPDUID_REF_1)
#define GDN_DCM_DCP_CONNECTION_2_TXREF_ID              (GDN_DCM_DCP_TXPDUID_REF_2)
#define GDN_DCM_DCP_CONNECTION_3_TXREF_ID              (GDN_DCM_DCP_TXPDUID_REF_3)

/* DcmRxPduId_## */
#define GDN_DCM_DCP_RXPDUID_0_ID                       (GDN_DCM_DCP_RXPDUID_0)
#define GDN_DCM_DCP_RXPDUID_1_ID                       (GDN_DCM_DCP_RXPDUID_1)
#define GDN_DCM_DCP_RXPDUID_2_ID                       (GDN_DCM_DCP_RXPDUID_2)
#define GDN_DCM_DCP_RXPDUID_3_ID                       (GDN_DCM_DCP_RXPDUID_3)
#define GDN_DCM_DCP_RXPDUID_0_RXTYPE                   (GDN_DCM_AddressKindPhysical)
#define GDN_DCM_DCP_RXPDUID_1_RXTYPE                   (GDN_DCM_AddressKindFunctional)
#define GDN_DCM_DCP_RXPDUID_2_RXTYPE                   (GDN_DCM_AddressKindPhysical)
#define GDN_DCM_DCP_RXPDUID_3_RXTYPE                   (GDN_DCM_AddressKindFunctional)
#define GDN_DCM_DCP_RXPDUID_0_CONNECTIONID             (0U)
#define GDN_DCM_DCP_RXPDUID_1_CONNECTIONID             (1U)
#define GDN_DCM_DCP_RXPDUID_2_CONNECTIONID             (2U)
#define GDN_DCM_DCP_RXPDUID_3_CONNECTIONID             (3U)

/****************************** DCP CONFIG END ********************************/

#endif /* GDN_UCFG_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

