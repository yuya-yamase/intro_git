/* Gdn_CanIf_h_01_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | CanIfのGUARDIANラッパー（ヘッダー）                          */
/* Notes       | 本ファイルはGUARDIANのCanIf関連処理のWrapperに対して実装の一 */
/*             | 例を示すものである。                                         */
/*             | 製品の機能に合わせて下記ファイルを実装してください。         */
/*             |   Gdn_CanIf.c    Gdn_CanIf.h                                 */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  01_0001   2015/8/31    DN毛     CS結合用テンプレート更新                  */
/*  00_0002   2018/02/13   AUBASS   リプログ対応                              */
/*  01_0003   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_CANIF_H
#define GDN_CANIF_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <CanIf.h>


/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
    /* 送信PDUIDの定義 */
#define GDN_CANIF_CanTpTxPduId0000   ((Gdn_PduIdType)0U)
#define GDN_CANIF_CanTpTxPduId0001   ((Gdn_PduIdType)1U)
#define GDN_CANIF_CanTpTxPduId0002   ((Gdn_PduIdType)2U)
#define GDN_CANIF_CanTpTxPduId0003   ((Gdn_PduIdType)3U)
#define GDN_CANIF_CanTpTxPduId0004   ((Gdn_PduIdType)4U)
#define GDN_CANIF_CanTpTxPduId0005   ((Gdn_PduIdType)5U)
#define GDN_CANIF_CanTpTxPduId0006   ((Gdn_PduIdType)6U)
#define GDN_CANIF_CanTpTxPduId0007   ((Gdn_PduIdType)7U)
#define GDN_CANIF_CanTpTxPduId0008   ((Gdn_PduIdType)8U)
#define GDN_CANIF_CanTpTxPduId0009   ((Gdn_PduIdType)9U)
#define GDN_CANIF_CanTpTxPduId0010   ((Gdn_PduIdType)10U)
#define GDN_CANIF_CanTpTxPduId0011   ((Gdn_PduIdType)11U)
#define GDN_CANIF_CanTpTxPduId0012   ((Gdn_PduIdType)12U)
#define GDN_CANIF_CanTpTxPduId0013   ((Gdn_PduIdType)13U)
#define GDN_CANIF_CanTpTxPduId0014   ((Gdn_PduIdType)14U)
#define GDN_CANIF_CanTpTxPduId0015   ((Gdn_PduIdType)15U)

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
    /* 送信PDUIDの定義 */
/* コンフィグツール生成結果を使用してください */

    /* 上位層の受信PDUID（Gdn_Ucfg.hで定義） */
/* コンフィグツール生成結果を使用してください */

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
/* Function Name | Gdn_CanIf_Transmit                                         */
/* Description   | CanIfの送信要求                                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId    : 送信先の送信PDUID                        */
/*               | (in) PduInfoPtr : 送信Pdu情報（データサイズ、データ）      */
/* Return Value  | 送信要求の処理または受付結果                               */
/*               |   GDN_E_OK / GDN_E_NOT_OK                                  */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CANIF_CODE_SLOW) Gdn_CanIf_Transmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
);

/******************************************************************************/
/* Function Name | Gdn_CanIf_CancelTransmit                                   */
/* Description   | CanIfの送信中止要求                                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TxPduId : 送信中止対象の送信PduId                     */
/* Return Value  | 送信中止要求の処理または受付結果                           */
/*               |   GDN_E_OK / GDN_E_NOT_OK                                  */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CANIF_CODE_SLOW) Gdn_CanIf_CancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTxPduId
);

#if (GDN_PDUR_UsePduR_Nw == GDN_ON)
/******************************************************************************/
/* Function Name | Gdn_CanIf_Gateway                                          */
/* Description   | CanIfのゲートウェイ要求                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) PduId      : 送信先の送信PDUID                        */
/*               | (in) PduInfoPtr : 送信Pdu情報（データサイズ、データ）      */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, GDN_CANIF_CODE_SLOW) Gdn_CanIf_Gateway
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
);
#endif

#endif /* GDN_CANIF_H */
/**** End of File *************************************************************/
