/* Gdn_PduR_NwIfUcfg_h_00_0001 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | PDUルータのNetwork層インターフェース                         */
/* Notes       | 本モジュールはコンフィグツールにより自動生成される           */
/*             | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_PDUR_NWIFUCFG_H
#define GDN_PDUR_NWIFUCFG_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
    /* 下位Network層のコンポーネント名取得 */
#define GDN_PDUR_NwIfGetName_Lo( comp )       GDN_PDUR_ComponentName_LoNw_ ##comp
    /* 下位Network層の受信通知のI/F名の生成マクロ */
#define GDN_PDUR_NwIfRxIndName_Lo( name )     Gdn_PduR_ ## name ## RxIndication
#define GDN_PDUR_NwIfRxInd_Lo( name )         GDN_PDUR_NwIfRxIndName_Lo( name )
#define GDN_PDUR_LoRxIndication( comp )       GDN_PDUR_NwIfRxInd_Lo(GDN_PDUR_NwIfGetName_Lo( comp ))
    /* 下位Network層の送信完了通知のI/F名の生成マクロ */
#define GDN_PDUR_NwIfTxConName_Lo( name )     Gdn_PduR_ ## name ## TxConfirmation
#define GDN_PDUR_NwIfTxCon_Lo( name )         GDN_PDUR_NwIfTxConName_Lo( name )
#define GDN_PDUR_LoTxConfirmation( comp )     GDN_PDUR_NwIfTxCon_Lo(GDN_PDUR_NwIfGetName_Lo( comp ))
    /* 下位Network層の送信要求トリガーのI/F名の生成マクロ */
#define GDN_PDUR_NwIfTxTrgName_Lo( name )     Gdn_PduR_ ## name ## TriggerTransmit
#define GDN_PDUR_NwIfTxTrg_Lo( name )         GDN_PDUR_NwIfTxTrgName_Lo( name )
#define GDN_PDUR_LoTriggerTransmit( comp )    GDN_PDUR_NwIfTxTrg_Lo(GDN_PDUR_NwIfGetName_Lo( comp ))
    /* 上位Network層のコンポーネント名取得 */
#define GDN_PDUR_NwIfGetName_Up( comp )       GDN_PDUR_ComponentName_UpNw_ ##comp
    /* 上位Network層の送信要求のI/F名の生成マクロ */
#define GDN_PDUR_NwIfTxReqName_Up( name )     Gdn_PduR_ ## name ## Transmit
#define GDN_PDUR_NwIfTxReq_Up( name )         GDN_PDUR_NwIfTxReqName_Up( name )
#define GDN_PDUR_UpTransmit( comp )           GDN_PDUR_NwIfTxReq_Up(GDN_PDUR_NwIfGetName_Up( comp ))
    /* 上位Network層の送信中止要求のI/F名の生成マクロ */
#define GDN_PDUR_NwIfTxCanclName_Up( name )   Gdn_PduR_ ## name ## CancelTransmit
#define GDN_PDUR_NwIfTxCancl_Up( name )       GDN_PDUR_NwIfTxCanclName_Up( name )
#define GDN_PDUR_UpCancelTransmit( comp )     GDN_PDUR_NwIfTxCancl_Up(GDN_PDUR_NwIfGetName_Up( comp ))

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
/* Function Name | Gdn_PduR_<Lo>RxIndication                                  */
/* Description   | Network層受信通知                                          */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RxPduId    : 受信PduId                                */
/*               | (in) PduInfoPtr : 受信Pdu情報（データサイズ、データ）      */
/* Return Value  | なし                                                       */
/* Notes         | 下位Network層毎に自動生成する                              */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoNw_0 != 0U ) )
void GDN_PDUR_LoRxIndication(0) ( Gdn_PduIdType RxPduId, const Gdn_PduInfoType* PduInfoPtr );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Lo>TxConfirmation                                */
/* Description   | Network層送信完了通知                                      */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId    : 送信PduId                                */
/* Return Value  | なし                                                       */
/* Notes         | 下位Network層毎に自動生成する                              */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_TxConfirmation_LoNw_0 == GDN_ON) )
void GDN_PDUR_LoTxConfirmation(0) ( Gdn_PduIdType TxPduId );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Lo>TriggerTransmit                               */
/* Description   | Network層送信要求トリガー                                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  TxPduId    : 送信PduId                               */
/*               | (out) PduInfoPtr : 送信Pdu情報（データサイズ、データ）     */
/* Return Value  | 送信要求トリガーの処理結果                                 */
/*               |  GDN_E_OK     : 送信データ取得                             */
/*               |  GDN_E_NOT_OK : 送信データ取得失敗またはルーティング未実施 */
/* Notes         | 下位Network層毎に自動生成する                              */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_TriggerTransmit_LoNw_0 == GDN_ON) )
Gdn_Std_ReturnType GDN_PDUR_LoTriggerTransmit(0) ( Gdn_PduIdType TxPduId, Gdn_PduInfoType* PduInfoPtr );
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Up>Transmit                                      */
/* Description   | Network層送信要求                                          */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId    : 送信PduId                                */
/*               | (in) PduInfoPtr : 送信Pdu情報（データサイズ、データ）      */
/* Return Value  | 送信要求の処理結果                                         */
/*               |  GDN_E_OK     : 送信成功                                   */
/*               |  GDN_E_NOT_OK : 送信失敗またはルーティング未実施           */
/* Notes         | 上位Network層毎に自動生成する                              */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_PduR_<Up>CancelTransmit                                */
/* Description   | Network層送信中止要求                                      */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : 送信PduId                                   */
/* Return Value  | 送信キャンセルの処理結果                                   */
/*               |  GDN_E_OK     : 送信キャンセル実施完了                     */
/*               |  GDN_E_NOT_OK : 送信キャンセルまたはルーティング未実施     */
/* Notes         | 上位Network層毎に自動生成する                              */
/******************************************************************************/

#endif /* GDN_PDUR_NWIFUCFG_H */
/**** End of File *************************************************************/

