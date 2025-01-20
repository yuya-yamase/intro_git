/* Gdn_PduR_TpIfUcfg_h_00_0001 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | PDUルータのTransport層インターフェース                       */
/* Notes       | 本モジュールはコンフィグツールにより自動生成される           */
/*             | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_PDUR_TPIFUCFG_H
#define GDN_PDUR_TPIFUCFG_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
    /* 下位Transport層のコンポーネント名取得 */
#define GDN_PDUR_TpIfGetName_Lo( comp )         GDN_PDUR_ComponentName_LoTp_ ##comp
    /* 下位Transport層の受信開始通知のI/F名の生成マクロ */
#define GDN_PDUR_TpIfRxSorName_Lo( name )       Gdn_PduR_ ## name ## StartOfReception
#define GDN_PDUR_TpIfRxSor_Lo( name )           GDN_PDUR_TpIfRxSorName_Lo( name )
#define GDN_PDUR_LoTpStartOfReception( comp )   GDN_PDUR_TpIfRxSor_Lo(GDN_PDUR_TpIfGetName_Lo( comp ))
    /* 下位Transport層の受信データコピー処理のI/F名の生成マクロ */
#define GDN_PDUR_TpIfRxCpyName_Lo( name )       Gdn_PduR_ ## name ## CopyRxData
#define GDN_PDUR_TpIfRxCpy_Lo( name )           GDN_PDUR_TpIfRxCpyName_Lo( name )
#define GDN_PDUR_LoTpCopyRxData( comp )         GDN_PDUR_TpIfRxCpy_Lo(GDN_PDUR_TpIfGetName_Lo( comp ))
    /* 下位Transport層の受信完了通知のI/F名の生成マクロ */
#define GDN_PDUR_TpIfRxIndName_Lo( name )       Gdn_PduR_ ## name ## RxIndication
#define GDN_PDUR_TpIfRxInd_Lo( name )           GDN_PDUR_TpIfRxIndName_Lo( name )
#define GDN_PDUR_LoTpRxIndication( comp )       GDN_PDUR_TpIfRxInd_Lo(GDN_PDUR_TpIfGetName_Lo( comp ))
    /* 下位Transport層の送信データコピー処理のI/F名の生成マクロ */
#define GDN_PDUR_TpIfTxCpyName_Lo( name )       Gdn_PduR_ ## name ## CopyTxData
#define GDN_PDUR_TpIfTxCpy_Lo( name )           GDN_PDUR_TpIfTxCpyName_Lo( name )
#define GDN_PDUR_LoTpCopyTxData( comp )         GDN_PDUR_TpIfTxCpy_Lo(GDN_PDUR_TpIfGetName_Lo( comp ))
    /* 下位Transport層の送信完了通知のI/F名の生成マクロ */
#define GDN_PDUR_TpIfTxConName_Lo( name )       Gdn_PduR_ ## name ## TxConfirmation
#define GDN_PDUR_TpIfTxCon_Lo( name )           GDN_PDUR_TpIfTxConName_Lo( name )
#define GDN_PDUR_LoTpTxConfirmation( comp )     GDN_PDUR_TpIfTxCon_Lo(GDN_PDUR_TpIfGetName_Lo( comp ))
    /* 上位Transport層のコンポーネント名取得 */
#define GDN_PDUR_TpIfGetName_Up( comp )         GDN_PDUR_ComponentName_UpTp_ ##comp
    /* 上位Transport層の送信中止通知のI/F名の生成マクロ */
#define GDN_PDUR_TpIfRxCancelName_Up( name )    Gdn_PduR_ ## name ## CancelReceive
#define GDN_PDUR_TpIfRxCancel_Up( name )        GDN_PDUR_TpIfRxCancelName_Up( name )
#define GDN_PDUR_UpTpCancelReceive( comp )      GDN_PDUR_TpIfRxCancel_Up(GDN_PDUR_TpIfGetName_Up( comp ))
    /* 上位Transport層のパラメータ変更要求のI/F名の生成マクロ */
#define GDN_PDUR_TpIfRxChgParName_Up( name )    Gdn_PduR_ ## name ## ChangeParameter
#define GDN_PDUR_TpIfRxChgPar_Up( name )        GDN_PDUR_TpIfRxChgParName_Up( name )
#define GDN_PDUR_UpTpChangeParameter( comp )    GDN_PDUR_TpIfRxChgPar_Up(GDN_PDUR_TpIfGetName_Up( comp ))
    /* 上位Transport層の送信要求のI/F名の生成マクロ */
#define GDN_PDUR_TpIfTxTransName_Up( name )     Gdn_PduR_ ## name ## Transmit
#define GDN_PDUR_TpIfTxTrans_Up( name )         GDN_PDUR_TpIfTxTransName_Up( name )
#define GDN_PDUR_UpTpTransmit( comp )           GDN_PDUR_TpIfTxTrans_Up(GDN_PDUR_TpIfGetName_Up( comp ))
    /* 上位Transport層の送信中止要求のI/F名の生成マクロ */
#define GDN_PDUR_TpIfTxCancelName_Up( name )    Gdn_PduR_ ## name ## CancelTransmit
#define GDN_PDUR_TpIfTxCancel_Up( name )        GDN_PDUR_TpIfTxCancelName_Up( name )
#define GDN_PDUR_UpTpCancelTransmit( comp )     GDN_PDUR_TpIfTxCancel_Up(GDN_PDUR_TpIfGetName_Up( comp ))


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

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>StartOfReception                            */
/* Description   | Transport層受信開始通知                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId       : 受信PduId                            */
/*               | (in)  PduInfoPtr    : 受信Pdu情報（データサイズ、データ）  */
/*               | (in)  TpSduLength   : 受信Sduサイズ                        */
/*               | (out) BufferSizePtr : 受信バッファのサイズ                 */
/* Return Value  | 受信開始通知/受信バッファ取得の結果                        */
/*               |   GDN_BUFREQ_OK       : 受信可能                           */
/*               |   GDN_BUFREQ_E_NOT_OK : 受信不可                           */
/*               |   GDN_BUFREQ_E_OVFL   : バッファ不足                       */
/* Notes         | 下位Transport層毎に自動生成する                            */
/*               | ・ゲートウェイ送受信中の受信開始通知を無視する。ただし、   */
/*               | 受信開始後データをまだコピーしていない場合は再受信する。   */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
Gdn_BufReq_ReturnType GDN_PDUR_LoTpStartOfReception(0) ( Gdn_PduIdType      RxPduId,     const Gdn_PduInfoType*   PduInfoPtr,
                                                         Gdn_PduLengthType  TpSduLength,       Gdn_PduLengthType* BufferSizePtr );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>CopyRxData                                  */
/* Description   | Transport層受信データコピー処理                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId       : 受信PduId                            */
/*               | (in)  PduInfoPtr    : 受信Pdu情報（データサイズ、データ）  */
/*               | (out) BufferSizePtr : 残バッファサイズ                     */
/* Return Value  | 受信データコピー処理の結果                                 */
/*               |   GDN_BUFREQ_OK       : コピー完了                         */
/*               |   GDN_BUFREQ_E_NOT_OK : コピー未実施                       */
/*               |   GDN_BUFREQ_E_OVFL   : バッファ不足                       */
/* Notes         | 下位Transport層毎に自動生成する                            */
/*               | ・リソース削減のため、ゲートウェイ使用時の受信処理に対して */
/*               | PduRは予期せぬデータのコピー要求をガードしない。           */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
Gdn_BufReq_ReturnType GDN_PDUR_LoTpCopyRxData(0) ( Gdn_PduIdType      RxPduId,
                                             const Gdn_PduInfoType*   PduInfoPtr,
                                                   Gdn_PduLengthType* BufferSizePtr );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>RxIndication                                */
/* Description   | Transport層受信完了通知                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  RxPduId : 受信PduId                                  */
/*               | (in)  Result  : 受信結果                                   */
/* Return Value  | なし                                                       */
/* Notes         | 下位Transport層毎に自動生成する                            */
/*               | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ送信中に、StartOfReception→CopyRxDataの受信処 */
/*               | 理手順を守らず、いきなりRxIndicationをPduRに通知すると、送 */
/*               | 信の情報がリセットされ送信データが乱れてしまう。           */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
void GDN_PDUR_LoTpRxIndication(0) ( Gdn_PduIdType RxPduId, Gdn_NotifResultType Result );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>CopyTxData                                  */
/* Description   | Transport層送信データコピー処理                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  TxPduId        : 下位層送信PduId                     */
/*               | (in)  PduInfo        : 送信Pdu情報（データサイズ、データ） */
/*               | (in)  Retry          : データコピーのリトライ情報          */
/*               | (out) AvailableData  : 送信データの残バイト数              */
/* Return Value  | バッファコピーの結果                                       */
/*               |   GDN_BUFREQ_OK       : コピー完了                         */
/*               |   GDN_BUFREQ_E_NOT_OK : コピー未実施                       */
/*               |   GDN_BUFREQ_E_BUSY   : 送信データ不足                     */
/* Notes         | 下位Transport層毎に自動生成する                            */
/*               | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ受信中に、送受信処理の手順を守らず、いきなり   */
/*               | CopyTxDataをPduRに通知すると、受信中のデータを出力してしま */
/*               | ことがある。                                               */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoTp_0 != 0U ) )
Gdn_BufReq_ReturnType GDN_PDUR_LoTpCopyTxData(0) ( Gdn_PduIdType      TxPduId, const Gdn_PduInfoType*   PduInfo,
                                             const Gdn_RetryInfoType* Retry,         Gdn_PduLengthType* AvailableData );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>TxConfirmation                              */
/* Description   | Transport層送信完了通知                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : 下位層送信PduId                             */
/*               | (in) Result  : 送信処理の結果                              */
/* Return Value  | なし                                                       */
/* Notes         | 下位Transport層毎に自動生成する                            */
/*               | ・リソース削減のため、PduRは状態を管理していない。もし、   */
/*               | ゲートウェイ受信中に、送受信処理の手順を守らず、いきなり   */
/*               | TxConfirmationをPduRに通知すると、受信中のデータを消してし */
/*               | しまうことがある。                                         */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoTp_0 != 0U ) )
void GDN_PDUR_LoTpTxConfirmation(0) ( Gdn_PduIdType TxPduId, Gdn_NotifResultType Result );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>CancelReceive                               */
/* Description   | Transport層受信中止要求                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId : 上位層受信PduId                             */
/* Return Value  | 受信中止の処理結果                                         */
/*               |  GDN_E_OK     : 受信中止処理実施完了                       */
/*               |  GDN_E_NOT_OK : 受信中止処理未実施またはルーティング未実施 */
/* Notes         | 上位Transport層毎に自動生成する                            */
/*               | ・ゲートウェイ用の受信PduIdはシングルフレームのみサポート  */
/*               | するため、受信中止要求をサポートしない。                   */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_CancelReceive_UpTp_0 == GDN_ON ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpCancelReceive(0) ( Gdn_PduIdType RxPduId );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>ChangeParameter                             */
/* Description   | Transport層パラメータ変更要求                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId   : 上位層受信PduId                           */
/*               | (in) Parameter : 変更対象パラメータ                        */
/*               | (in) Value     : 設定値                                    */
/* Return Value  | パラメータ変更処理の結果                                   */
/*               |  GDN_E_OK     : 変更処理実施完了                           */
/*               |  GDN_E_NOT_OK : 変更処理未実施またはルーティング未実施     */
/* Notes         | 上位Transport層毎に自動生成する                            */
/*               | ・ゲートウェイ用の受信PduIdはシングルフレームのみサポート  */
/*               | するため、パラメータ変更要求をサポートしない。             */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_ChangeParameter_UpTp_0 == GDN_ON ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpChangeParameter(0) ( Gdn_PduIdType RxPduId, Gdn_TPParameterType Parameter, gdn_uint16 Value );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>Transmit                                    */
/* Description   | Transport層送信要求                                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : 送信PduId                                   */
/*               | (in) PduInfo : 送信Pdu情報（データサイズ、データ）         */
/* Return Value  | 送信要求の処理結果                                         */
/*               |  GDN_E_OK     : 送信要求処理完了                           */
/*               |  GDN_E_NOT_OK : 送信要求未実施またはルーティング未実施     */
/* Notes         | 上位Transport層毎に自動生成する                            */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_UpTp_0 != 0U ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpTransmit(0) ( Gdn_PduIdType TxPduId, const Gdn_PduInfoType* PduInfo );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>CancelTransmit                              */
/* Description   | Transport層送信中止要求                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : 送信PduId                                   */
/* Return Value  | 送信キャンセルの処理結果                                   */
/*               |  GDN_E_OK     : 送信キャンセル実施完了                     */
/*               |  GDN_E_NOT_OK : 送信キャンセルまたはルーティング未実施     */
/* Notes         | 上位Transport層毎に自動生成する                            */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_CancelTransmit_UpTp_0 == GDN_ON ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpCancelTransmit(0) ( Gdn_PduIdType TxPduId );
#endif


#endif /* GDN_PDUR_TPIFUCFG_H */
/**** End of File *************************************************************/

