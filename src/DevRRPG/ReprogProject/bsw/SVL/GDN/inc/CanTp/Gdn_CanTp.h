/* Gdn_CanTp_h_00_0002 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | ダイアグCAN通信トランスポート層（コンポーネントヘッダ）      */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     新規作成                                  */
/*  00_0001   2019/12/03   AUBASS   Update                                    */
/*  00_0002   2022/03/01   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_CANTP_H
#define GDN_CANTP_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_Physical      ((Gdn_CanTp_NTATypeType)1U)
#define GDN_CANTP_Functional    ((Gdn_CanTp_NTATypeType)2U)
#define GDN_CANTP_Normal        ((Gdn_CanTp_AddressFormatType)3U)
#define GDN_CANTP_Extended      ((Gdn_CanTp_AddressFormatType)4U)

#define GDN_CANTP_TimerCnt      (2)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef gdn_uint8   Gdn_CanTp_NTATypeType;
typedef gdn_uint8   Gdn_CanTp_AddressFormatType;
typedef gdn_uint8   Gdn_CanTp_TargetAddressType;
typedef gdn_uint8   Gdn_CanTp_ChannelType;
typedef gdn_uint8   Gdn_CanTp_PriorityType;
typedef gdn_uint8   Gdn_CanTp_BlockSizeType;
typedef gdn_uint8   Gdn_CanTp_STminType;
typedef gdn_uint8   Gdn_CanTp_WFTMaxType;
typedef gdn_uint8   Gdn_CanTp_PaddingValueType;

    /* 受信N_AIコンフィグ項目 */
typedef struct {
    Gdn_PduIdType                   PduId;
    Gdn_CanTp_NTATypeType           N_TaType;
    Gdn_CanTp_AddressFormatType     AddressFormat;
    Gdn_CanTp_TargetAddressType     TargetAddress;
    gdn_bool                        IsPadding;
    Gdn_CanTp_ChannelType           Channel;
    Gdn_CanTp_PriorityType          Priority;
    gdn_uint8                       TxN_AIidx;
    Gdn_CanTp_BlockSizeType         BlockSize;
    Gdn_CanTp_STminType             STmin;
    Gdn_TimeoutValueType            N_Ar;
    Gdn_TimeoutValueType            N_Br;
    Gdn_TimeoutValueType            N_Br_min;
    Gdn_TimeoutValueType            N_Cr;
    Gdn_CanTp_WFTMaxType            WFTMax;
    Gdn_PduIdType                   SduId;
} Gdn_CanTp_RxNAIInfoType;

    /* 送信N_AIコンフィグ項目 */
typedef struct {
    Gdn_CanTp_AddressFormatType     AddressFormat;
    Gdn_CanTp_TargetAddressType     TargetAddress;
    Gdn_CanTp_PaddingValueType      PaddingValue;
    Gdn_CanTp_ChannelType           Channel;
    Gdn_CanTp_PriorityType          Priority;
    gdn_uint8                       RxN_AIidx;
    Gdn_TimeoutValueType            N_As;
    Gdn_TimeoutValueType            N_Bs;
    Gdn_TimeoutValueType            N_Cs;
    Gdn_TimeoutValueType            N_Cs_min;
    Gdn_PduIdType                   PduId;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    Gdn_PduLengthType               SendSize;
#endif
} Gdn_CanTp_TxNAIInfoType;

/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_START_SEC_CST
#include <Gdn_CanTp_MemMap.h>

#if ( GDN_CANTP_MaxRxNAICnt == 0U )
extern GdnConst Gdn_CanTp_RxNAIInfoType gdn_cantp_RxNAIInformation[1];
#else
extern GdnConst Gdn_CanTp_RxNAIInfoType gdn_cantp_RxNAIInformation[GDN_CANTP_MaxRxNAICnt];
#endif

#if ( GDN_CANTP_MaxTxNAICnt == 0U )
extern GdnConst Gdn_CanTp_TxNAIInfoType gdn_cantp_TxNAIInformation[1];
#else
extern GdnConst Gdn_CanTp_TxNAIInfoType gdn_cantp_TxNAIInformation[GDN_CANTP_MaxTxNAICnt];
#endif

extern GdnConst Gdn_TimerIdType gdn_cantp_TimerId[GDN_CANTP_MaxChannelCnt][GDN_CANTP_TimerCnt];

#define GDN_CANTP_STOP_SEC_CST
#include <Gdn_CanTp_MemMap.h>

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_CanTp_Init                                             */
/* Description   | CanTpの初期化処理                                          */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | なし                                                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_Init (void);

/******************************************************************************/
/* Function Name | Gdn_CanTp_Shutdown                                         */
/* Description   | CanTpの終了処理                                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | なし                                                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_Shutdown (void);

/******************************************************************************/
/* Function Name | Gdn_CanTp_MainFunction                                     */
/* Description   | CanTpの送受信リトライ処理                                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | なし                                                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_MainFunction (void);

/******************************************************************************/
/* Function Name | Gdn_CanTp_RxIndication                                     */
/* Description   | 受信通知（L_Data.indication）                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId    : CanTpの受信PduId                         */
/*               | (in) PduInfoPtr : 受信Pdu情報（データサイズ、データ）      */
/* Return Value  | なし                                                       */
/* Notes         | PduInfoPtr及びPDUデータへのポインタの有効性(NULLではない)  */
/*               | を判定しないため、このインターフェースを使用する時に、無効 */
/*               | なアドレスを渡してはいけない。                             */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_RxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANTP_APPL_CONST) PduInfoPtr
);

#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
/******************************************************************************/
/* Function Name | Gdn_CanTp_Transmit                                         */
/* Description   | 送信要求（N_USData.request）                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) CanTpTxSduId   : CanTpの送信SduId                     */
/*               | (in) CanTpTxInfoPtr : 送信Sdu情報（データサイズ、データ）  */
/* Return Value  | 送信処理の結果                                             */
/*               |  GDN_E_OK     : SFまたはFF送信要求を実施した               */
/*               |  GDN_E_NOT_OK : 送信要求を実施できない                     */
/* Notes         | ・CanTpTxInfoPtrの有効性(NULLではない)を判定しないため、こ */
/*               |   のインターフェースを使用する時に、無効なアドレスを渡して */
/*               |   はいけない。                                             */
/*               | ・このインターフェースでは、送信Sdu情報の「データ」を使用  */
/*               |   しない。送信データは、上位層のCopyTxDataインターフェース */
/*               |   を使って取得する。                                       */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_Transmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpTxSduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr
);
#endif

/******************************************************************************/
/* Function Name | Gdn_CanTp_TxConfirmation                                   */
/* Description   | 送信完了通知（L_Data.confirmation）                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : CanTpが参照する下位層の送信PduId            */
/* Return Value  | なし                                                       */
/* Notes         | 同じ送信PduIdを使用する異なる送信N_AIは、必ず同じチャネル  */
/*               | で送信すること。                                           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_TxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId
);

/******************************************************************************/
/* Function Name | Gdn_CanTp_TimeoutIndication                                */
/* Description   | タイムアウト通知                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TimerId      : タイマのID                             */
/*               | (in) Synchronizer : タイマ同期用カウンタ                   */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_TimeoutIndication
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
);

#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
  #if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
/******************************************************************************/
/* Function Name | Gdn_CanTp_ChangeParameter                                  */
/* Description   | 受信パラメータ変更要求（N_ChangeParameter.request）        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) id        : CanTpが参照する上位層の受信SduId          */
/*               | (in) parameter : パラメータ種類（BSまたはSTmin）           */
/*               | (in) value     : 変更後の値                                */
/* Return Value  | 変更処理の結果                                             */
/*               |  GDN_E_OK     : 変更完了                                   */
/*               |  GDN_E_NOT_OK : 変更要求を実施できない                     */
/* Notes         | ・このインターフェースは、コンフィグで有効/無効を切り換え  */
/*               |   られる。                                                 */
/*               | ・変更後の値は、次の変更またはRAMの初期化まで保存する。    */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_ChangeParameter
(
    VAR(Gdn_PduIdType, AUTOMATIC) id,
    VAR(Gdn_TPParameterType, AUTOMATIC) parameter,
    VAR(gdn_uint16, AUTOMATIC) value
);
  #endif

/******************************************************************************/
/* Function Name | Gdn_CanTp_CancelTransmit                                   */
/* Description   | 送信中止要求                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) CanTpTxSduId : 中止対象の送信SduId                    */
/* Return Value  | StatusType                                                 */
/*               |  GDN_E_OK     : 中止要求を実施した                         */
/*               |  GDN_E_NOT_OK : 中止要求を実施できなかった                 */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_CancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpTxSduId
);

/******************************************************************************/
/* Function Name | Gdn_CanTp_CancelReceive                                    */
/* Description   | 受信中止要求                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) CanTpRxSduId : 中止対象の受信SduId                    */
/* Return Value  | StatusType                                                 */
/*               |  GDN_E_OK     : 中止要求を実施した                         */
/*               |  GDN_E_NOT_OK : 中止要求を実施できなかった                 */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_CancelReceive
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpRxSduId
);
#endif  /* REPROG_CFG_SUBMICON_USE_SUB != STD_ON */

#endif /* GDN_CANTP_H */
/**** End of File *************************************************************/
