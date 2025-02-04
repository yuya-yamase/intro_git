/* Gdn_Dcm_h_00_0007 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | DCM共通処理（コンポーネントヘッダ）                          */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/02/dd   DN長谷川 新規作成                                  */
/*  00_0000   2014/02/dd   DN矢加部 追加                                      */
/*  00_0001   2014/09/25   DT       DTCKindのセッションサポート判定を追加     */
/*  00_0002   2014/11/12   DN矢加部 Dcmのスリープ禁止状態取得関数追加         */
/*  00_0003   2018/06/19   AUBASS   リプログ対応                              */
/*  00_0004   2019/02/12   AUBASS   Update                                    */
/*  00_0005   2019/07/16   AUBASS   Update                                    */
/*  00_0006   2019/12/03   AUBASS   Update                                    */
/*  00_0007   2022/03/01   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_DCM_H
#define GDN_DCM_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>
#include <ComStack_Types.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
typedef gdn_uint8       Gdn_Dcm_MsgAddInfoReqTypeType;
#define GDN_DCM_AddressKindFunctional ((Gdn_Dcm_MsgAddInfoReqTypeType)0U)
#define GDN_DCM_AddressKindPhysical   ((Gdn_Dcm_MsgAddInfoReqTypeType)1U)
#define GDN_DCM_AddressKindNum        (2)

typedef gdn_uint8       Gdn_Dcm_ProcessingDoneStatusType;
#define GDN_DCM_NormalDone             ((Gdn_Dcm_ProcessingDoneStatusType)0U)
#define GDN_DCM_CancelNotAllowed       ((Gdn_Dcm_ProcessingDoneStatusType)1U)

typedef gdn_uint8       Gdn_Dcm_OpStatusType;
#define GDN_DCM_INITIAL                 ((Gdn_Dcm_OpStatusType)0U)
#define GDN_DCM_PENDING                 ((Gdn_Dcm_OpStatusType)1U)
#define GDN_DCM_CANCEL                  ((Gdn_Dcm_OpStatusType)2U)
#define GDN_DCM_FORCE_RCRRP_OK          ((Gdn_Dcm_OpStatusType)3U)

typedef gdn_uint8       Gdn_Dcm_SesCtrlKindType;
#define GDN_DCM_ChangeSesCtrl           ((Gdn_Dcm_SesCtrlKindType)0U)
#define GDN_DCM_ReprogEntry             ((Gdn_Dcm_SesCtrlKindType)1U)
#define GDN_DCM_ReadSesCtrl             ((Gdn_Dcm_SesCtrlKindType)2U)

#define GDN_DCM_P2MAXASTER_LSB          (10U)

/* セッション状態の定義（ラベル） */
#define GDN_DCM_DEFAULT_SESSION             ((Gdn_Dcm_SesCtrlType)0x01U)
#define GDN_DCM_EXTENDED_SESSION            ((Gdn_Dcm_SesCtrlType)0x03U)
#define GDN_DCM_REPROG_SESSION              ((Gdn_Dcm_SesCtrlType)0x02U)

/* アドレス種別 */
#define GDN_DCM_ADDRESSKIND_FUNC            ((gdn_uint8)(GDN_BIT0 << GDN_DCM_AddressKindFunctional))
#define GDN_DCM_ADDRESSKIND_PHYS            ((gdn_uint8)(GDN_BIT0 << GDN_DCM_AddressKindPhysical))
#define GDN_DCM_ADDRESSKIND_FUNC_PHYS       ((gdn_uint8)(GDN_DCM_ADDRESSKIND_FUNC | GDN_DCM_ADDRESSKIND_PHYS))

/* アプリ要求起動時のセキュリティ状態定義 */
#define GDN_DCM_SECURITY_LOCK               ((gdn_uint8)0x00U)
#define GDN_DCM_SECURITY_UNLOCK_LV1         ((gdn_uint8)0x01U)
#define GDN_DCM_SECURITY_UNLOCK_LV2         ((gdn_uint8)0x02U)
#define GDN_DCM_SECURITY_UNLOCK_LV3         ((gdn_uint8)0x04U)
#define GDN_DCM_SECURITY_UNLOCK_LV4         ((gdn_uint8)0x08U)
#define GDN_DCM_SECURITY_UNLOCK_LV5         ((gdn_uint8)0x10U)
#define GDN_DCM_SECURITY_UNLOCK_LV6         ((gdn_uint8)0x20U)
#define GDN_DCM_SECURITY_UNLOCK_LV7         ((gdn_uint8)0x40U)
#define GDN_DCM_SECURITY_UNLOCK_LV8         ((gdn_uint8)0x80U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef gdn_uint8       Gdn_Dcm_SesCtrlType;
typedef gdn_uint8       Gdn_Dcm_NegativeResponseCodeType;
typedef gdn_bool        Gdn_Dcm_MsgAddInfoSuppressResponseType;

typedef struct {
    gdn_uint8*                             ReqData;
    gdn_uint16                             ReqDataLen;
    gdn_uint8*                             ResData;
    gdn_uint16                             ResDataLen;
    Gdn_Dcm_MsgAddInfoReqTypeType          ReqType;
    Gdn_Dcm_MsgAddInfoSuppressResponseType SuppressResponse;
    gdn_uint16                             ResMaxDataLen;
} Gdn_Dcm_MsgContextType;

typedef struct {
    Gdn_Dcm_NegativeResponseCodeType       Nrc;
    Gdn_Dcm_MsgAddInfoSuppressResponseType ResponseSuppressInfo[ GDN_DCM_AddressKindNum ];
} Gdn_Dcm_NegativeResponseInfoType;

#if ( GDN_CMPSELECT_DCM_DSP == GDN_ON )
/* セッション状態関連コンフィグレーション項目 */
typedef struct {
    Gdn_Dcm_SesCtrlType                     SessionCtrl;                                /*  セッション状態                      */
    Gdn_TimeoutValueType                    P2MaxTime;                                  /*  P2MAX時間                           */
    Gdn_TimeoutValueType                    P2MaxAsterExTime;                           /*  P2*EX時間 (NRC0x78-NRC0x78間隔)     */
    gdn_bool                                S3TimerEnable;                              /*  S3タイマ起動許可                    */
#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
    gdn_uint8                               BsValue;                                    /*  セッション毎のBS値                  */
    gdn_uint8                               StminValue;                                 /*  セッション毎のSTmin値               */
#endif
} Gdn_Dcm_SessionCtrlConfigType;
#endif

/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/
/******************************************************************************/
/* Function Name | Gdn_Dcm_TransmitNegativeResponse                           */
/* Description   |                                                            */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  NegativeResponseInfo->Nrc : 否定応答コード           */
/*               | (in)  NegativeResponseInfo->ResponseSuppressInfo[] :       */
/*               |                                              応答抑制情報  */
/*               | (-)   MsgContext->ReqData : 未使用                         */
/*               | (-)   MsgContext->ReqDataLen : 未使用                      */
/*               | (-)   MsgContext->ResData : 未使用                         */
/*               | (-)   MsgContext->ResDataLen : 未使用                      */
/*               | (in)  MsgContext->ReqType : アドレス種別                   */
/*               | (out) MsgContext->SuppressResponse : 応答抑制情報          */
/*               | (-)   MsgContext->ResMaxDataLen : 未使用                   */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TransmitNegativeResponse
(
    P2CONST(Gdn_Dcm_NegativeResponseInfoType, AUTOMATIC, DCM_APPL_CONST) NegativeResponseInfo,
    P2VAR(Gdn_Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) MsgContext
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_StartOfReception                                   */
/* Description   | 受信開始通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  info->SduDataPtr : SduDataのポインタ                 */
/*               | (in)  info->SduLength  : SduData長                         */
/*               | (in)  TpSduLength      : Sduの全Data長                     */
/*               | (out) RxBufferSizePtr  : 残りの受信バッファ長              */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 受信開始OK                        */
/*               |  GDN_BUFREQ_E_NOT_OK   : 受信開始NG                        */
/*               |  GDN_BUFREQ_E_OVFL     : 受信バッファオーバー              */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_StartOfReception
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) info,
    VAR(Gdn_PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_CopyRxData                                         */
/* Description   | 受信データコピー                                           */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  PduInfoPtr->SduDataPtr : コピーするSduData           */
/*               | (in)  PduInfoPtr->SduLength  : コピーするSduData長         */
/*               | (out) RxBufferSizePtr  : 残りの受信バッファ長              */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 受信データコピー結果OK            */
/*               |  GDN_BUFREQ_E_NOT_OK   : 受信データコピー結果NG            */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_CopyRxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_TpRxIndication                                     */
/* Description   | 受信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  Result           : 下位層の受信結果                  */
/*               |  GDN_NTFRSLT_OK        : 受信正常完了                      */
/*               |  other                 : 受信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TpRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_CopyTxData                                         */
/* Description   | 送信データコピー                                           */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  DcmTxPduId       : DcmのTxPduId                      */
/*               | (in)  PduInfoPtr       : SduDataコピー先のアドレス         */
/*               | (in)  RetryInfoPtr     : リトライ関連情報                  */
/*               | (out) TxDataCntPtr     : 残りの送信TpSduデータ長           */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 送信データコピー結果OK            */
/*               |  GDN_BUFREQ_E_NOT_OK   : 送信データコピー結果NG            */
/* Notes         |  ・RetryInfoPtrは、NULL_PTR固定で指定すること。            */
/*               |  （Dcmにコピーのリトライのニーズがなく非対応のため。）     */
/*               |  ・Sタスクでコールすること。(タスク抜け/タスク干渉防止)    */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_CopyTxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmTxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
    P2CONST(Gdn_RetryInfoType, AUTOMATIC, DCM_APPL_CONST) RetryInfoPtr,
    P2VAR(gdn_uint16, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_TpTxConfirmation                                   */
/* Description   | 送信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmTxPduId       : DcmのTxPduId                      */
/*               | (in)  Result           : 下位層の送信結果                  */
/*               |  GDN_NTFRSLT_OK        : 送信正常完了                      */
/*               |  other                 : 送信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TpTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmTxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_MainFunction                                       */
/* Description   | DCMメイン関数（定期周期コール）                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_MainFunction (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Init                                               */
/* Description   | DCM初期化                                                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Init (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Shutdown                                           */
/* Description   | Dcmの通信終了処理                                          */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | なし                                                       */
/* Return Value  | なし                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Shutdown (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_TimeoutIndication                                  */
/* Description   | Dcm(Dcp)タイムアウト通知                                   */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TimerId      : タイマのID                             */
/*               | (in) Synchronizer : タイマ同期用カウンタ                   */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TimeoutIndication
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Time                                               */
/* Description   | 1msタイム処理関数コール処理を行う。                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Time (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyBaudrateSettingResult                        */
/* Description   |  ボーレート変更の成否を通知する                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) Network      : Networkハンドル                        */
/*               | (in) Dcm_Result   : 処理結果                               */
/* Return Value  | なし                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyBaudrateSettingResult
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    P2CONST(Gdn_Std_ReturnType, AUTOMATIC, DCM_APPL_CONST) Dcm_Result
);

#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyChangeSession                                */
/* Description   | セッション遷移を通知する                                   */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) NewSession   : 遷移するセッション                     */
/* Return Value  | なし                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyChangeSession
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) NewSession
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyChangeSecurity                               */
/* Description   | セキュリティ変更を通知する                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) NewSecurity : 設定するセキュリティ                    */
/* Return Value  | なし                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyChangeSecurity
(
    VAR(gdn_uint8, AUTOMATIC) NewSecurity
);
#endif

#endif /* GDN_DCM_H */
/**** End of File *************************************************************/
