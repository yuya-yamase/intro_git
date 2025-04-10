/* Gdn_PduR_Core_h_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | PDUルータのルーティング処理の本体（ZeroCost不使用時）        */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     新規作成                                  */
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2019/02/12   AUBASS   Update                                    */
/*  00_0003   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_PDUR_CORE_H
#define GDN_PDUR_CORE_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoRxIndication                                    */
/* Description   | Network層受信通知の本体                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId        : PduRの受信PduId                      */
/*               | (in) PduInfo        : Network層受信Pdu情報                 */
/*               | (in) RxRoutingTable : Network層受信ルーティングテーブル    */
/*               | (in) TableSize      : テーブルの項目数                     */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_LoNwRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_TxConfirmationApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTxConfirmation                                  */
/* Description   | Network層送信完了通知の本体                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId        :下位Network層の送信PduId              */
/*               | (in) TxRoutingTable :下位Network層送信ルーティングテーブル */
/*               | (in) TableSize      :テーブルの項目数                      */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_LoNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_TriggerTransmitApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTriggerTransmit                                 */
/* Description   | Network層送信要求トリガーの本体                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  TxPduId       :下位Network層の送信PduId              */
/*               | (out) PduInfo       :送信情報を格納するためのPdu情報       */
/*               | (in)  TxRoutingTable:下位Network層送信ルーティングテーブル */
/*               | (in)  TableSize     :テーブルの項目数                      */
/* Return Value  | 送信トリガー要求の実施結果                                 */
/*               |  GDN_E_OK     : 送信データ取得                             */
/*               |  GDN_E_NOT_OK : 送信データ未取得またはルーティング未実施   */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTriggerTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2VAR(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfo,
    CONST(volatile Gdn_PduR_LoNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UpLayerTransmit_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTransmit                                        */
/* Description   | Network層送信要求の本体                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId        :送信PduId                             */
/*               | (in) PduInfo        :送信Pdu情報（データサイズ、データ）   */
/*               | (in) TxRoutingTable :上位Network層送信ルーティングテーブル */
/*               | (in) TableSize      :テーブルの項目数                      */
/* Return Value  | 送信要求の処理結果                                         */
/*               |  GDN_E_OK     : 送信成功                                   */
/*               |  GDN_E_NOT_OK : 送信失敗またはルーティング未実施           */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_UpNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_CancelTransmitApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpCancelTransmit                                  */
/* Description   | Network層送信中止要求の本体                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId        :送信PduId                             */
/*               | (in) TxRoutingTable :上位Network層送信ルーティングテーブル */
/*               | (in) TableSize      :テーブルの項目数                      */
/* Return Value  | 送信キャンセルの処理結果                                   */
/*               |  GDN_E_OK     : 送信キャンセル実施完了                     */
/*               |  GDN_E_NOT_OK : 送信キャンセルまたはルーティング未実施     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpCancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_UpNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpStartOfReception                              */
/* Description   | Transport層受信開始通知の本体                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId        : 受信PduId                           */
/*               | (in)  PduInfo        : 受信Pdu情報（データサイズ、データ） */
/*               | (in)  TpSduLength    : 受信Sduサイズ                       */
/*               | (out) BufferSize     : 受信バッファのサイズ                */
/*               | (in)  RxBufferIdx    : 受信バッファの現在位置              */
/*               | (in)  RxRoutingTable :                                     */
/*               |                  下位Transport層受信ルーティングテーブル   */
/*               | (in)  TableSize      : テーブルの項目数                    */
/* Return Value  | 受信開始通知/受信バッファ取得の結果                        */
/*               |   GDN_BUFREQ_OK       : 受信可能                           */
/*               |   GDN_BUFREQ_E_NOT_OK : 受信不可                           */
/*               |   GDN_BUFREQ_E_OVFL   : バッファ不足                       */
/* Notes         | ・ゲートウェイ送受信中の受信開始通知を無視する。ただし、   */
/*               | 受信開始後データをまだコピーしていない場合は再受信する。   */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTpStartOfReception
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    VAR(Gdn_PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSize,
    VAR(Gdn_PduLengthType, AUTOMATIC) RxBufferIdx[],
    CONST(volatile Gdn_PduR_LoTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpCopyRxData                                    */
/* Description   | Transport層受信データコピー処理の本体                      */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId        : 受信PduId                           */
/*               | (in)  PduInfo        : 受信Pdu情報（データサイズ、データ） */
/*               | (out) BufferSize     : 残バッファサイズ                    */
/*               | (in)  RxBufferIdx    : 受信バッファの現在位置              */
/*               | (in)  RxRoutingTable :                                     */
/*               |                  下位Transport層受信ルーティングテーブル   */
/*               | (in)  TableSize      : テーブルの項目数                    */
/* Return Value  | 受信データコピー処理の結果                                 */
/*               |   GDN_BUFREQ_OK       : コピー完了                         */
/*               |   GDN_BUFREQ_E_NOT_OK : コピー未実施                       */
/*               |   GDN_BUFREQ_E_OVFL   : バッファ不足                       */
/* Notes         | リソース削減のため、ゲートウェイ使用時の受信処理に対して、 */
/*               | PduRは予期せぬデータのコピー要求をガードしない。           */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTpCopyRxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSize,
    VAR(Gdn_PduLengthType, AUTOMATIC) RxBufferIdx[],
    CONST(volatile Gdn_PduR_LoTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpRxIndication                                  */
/* Description   | Transport層受信完了通知の本体                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId        : 受信PduId                           */
/*               | (in)  Result         : 受信結果                            */
/*               | (in)  RxBufferIdx    : 受信バッファの現在位置              */
/*               | (in)  RxRoutingTable :                                     */
/*               |                  下位Transport層受信ルーティングテーブル   */
/*               | (in)  TableSize      : テーブルの項目数                    */
/* Return Value  | なし                                                       */
/* Notes         | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ送信中に、StartOfReception→CopyRxDataの受信処 */
/*               | 理手順を守らず、いきなりRxIndicationをPduRに通知すると、送 */
/*               | 信の情報がリセットされ送信データが乱れてしまう。           */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTpRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result,
    VAR(Gdn_PduLengthType, AUTOMATIC) RxBufferIdx[],
    CONST(volatile Gdn_PduR_LoTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpCopyTxData                                    */
/* Description   | Transport層送信データコピー処理の本体                      */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  TxPduId        : 下位層送信PduId                     */
/*               | (in)  PduInfo        : 送信Pdu情報（データサイズ、データ） */
/*               | (in)  Retry          : データコピーのリトライ情報          */
/*               | (out) AvailableData  : 送信データの残バイト数              */
/*               | (in)  TxRoutingTable :                                     */
/*               |                  下位Transport層送信ルーティングテーブル   */
/*               | (in)  TableSize      : テーブルの項目数                    */
/*               | (in)  RxTableList    : GW時、ルーティングテーブルのリスト  */
/* Return Value  | バッファコピーの結果                                       */
/*               |   GDN_BUFREQ_OK       : コピー完了                         */
/*               |   GDN_BUFREQ_E_NOT_OK : コピー未実施                       */
/*               |   GDN_BUFREQ_E_BUSY   : 送信データ不足                     */
/* Notes         | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ受信中に、送受信処理の手順を守らず、いきなり   */
/*               | CopyTxDataをPduRに通知すると、受信中のデータを出力してしま */
/*               | ことがある。                                               */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTpCopyTxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    P2CONST(Gdn_RetryInfoType, AUTOMATIC, PDUR_APPL_CONST) Retry,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableData,
    CONST(volatile Gdn_PduR_LoTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize,
    CONST(volatile Gdn_PduR_LoTpRxTableListType, PDUR_CONST) RxTableList[]
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpTxConfirmation                                */
/* Description   | Transport層送信完了通知の本体                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  TxPduId        : 下位層送信PduId                     */
/*               | (in)  Result         : 送信処理の結果                      */
/*               | (in)  TxRoutingTable :                                     */
/*               |                  下位Transport層送信ルーティングテーブル   */
/*               | (in)  TableSize      : テーブルの項目数                    */
/*               | (in)  RxTableList    : GW時、ルーティングテーブルのリスト  */
/* Return Value  | なし                                                       */
/* Notes         | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ受信中に、送受信処理の手順を守らず、いきなり   */
/*               | TxConfirmationをPduRに通知すると、受信中のデータを消してし */
/*               | しまうことがある。                                         */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTpTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result,
    CONST(volatile Gdn_PduR_LoTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize,
    CONST(volatile Gdn_PduR_LoTpRxTableListType, PDUR_CONST) RxTableList[]
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_CancelReceiveApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpCancelReceive                                 */
/* Description   | Transport層受信中止要求の本体                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId       :上位層受信PduId                        */
/*               | (in) RxRoutingTable:上位Transport層受信ルーティングテーブル*/
/*               | (in) TableSize     :テーブルの項目数                       */
/* Return Value  | 受信中止の処理結果                                         */
/*               |  GDN_E_OK     : 受信中止処理実施完了                       */
/*               |  GDN_E_NOT_OK : 受信中止処理未実施またはルーティング未実施 */
/* Notes         | ・ゲートウェイ用の受信PduIdはシングルフレームのみサポート  */
/*               | するため、受信中止要求をサポートしない。                   */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpCancelReceive
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    CONST(volatile Gdn_PduR_UpTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_ChangeParameterApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpChangeParameter                               */
/* Description   | Transport層パラメータ変更要求の本体                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId       :上位層受信PduId                        */
/*               | (in) Parameter     :変更対象パラメータ                     */
/*               | (in) Value         :設定値                                 */
/*               | (in) RxRoutingTable:上位Transport層受信ルーティングテーブル*/
/*               | (in) TableSize     :テーブルの項目数                       */
/* Return Value  | パラメータ変更処理の結果                                   */
/*               |  GDN_E_OK     : 変更処理実施完了                           */
/*               |  GDN_E_NOT_OK : 変更処理未実施またはルーティング未実施     */
/* Notes         | ・ゲートウェイ用の受信PduIdはシングルフレームのみサポート  */
/*               | するため、パラメータ変更要求をサポートしない。             */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpChangeParameter
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    VAR(Gdn_TPParameterType, AUTOMATIC) Parameter,
    VAR(gdn_uint16, AUTOMATIC) Value,
    CONST(volatile Gdn_PduR_UpTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpTransmit                                      */
/* Description   | Transport層送信要求の本体                                  */
/* Parameter(s)  | (in) TxPduId       :送信PduId                              */
/*               | (in) PduInfo       :送信Pdu情報（データサイズ、データ）    */
/*               | (in) TxRoutingTable:上位Transport層送信ルーティングテーブル*/
/*               | (in) TableSize     :テーブルの項目数                       */
/* Return Value  | 送信要求の処理結果                                         */
/*               |  GDN_E_OK     : 送信要求処理完了                           */
/*               |  GDN_E_NOT_OK : 送信要求未実施またはルーティング未実施     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_UpTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_CancelTransmitApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpCancelTransmit                                */
/* Description   | Transport層送信中止要求の本体                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId       :送信PduId                              */
/*               | (in) TxRoutingTable:上位Transport層送信ルーティングテーブル*/
/*               | (in) TableSize     :テーブルの項目数                       */
/* Return Value  | 送信キャンセルの処理結果                                   */
/*               |  GDN_E_OK     : 送信キャンセル実施完了                     */
/*               |  GDN_E_NOT_OK : 送信キャンセルまたはルーティング未実施     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpCancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_UpTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
);
#endif

#endif /* GDN_PDUR_CORE_H */
/**** End of File *************************************************************/
