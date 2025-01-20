/* Gdn_Dcm_Dcp_h_01_0006 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | Gdn_Dcm_Dcp.h                                                */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/03/dd   DN矢加部 新規作成                                  */
/*  00_0001   2014/11/12   DN矢加部 Dcpのスリープ禁止状態取得関数追加         */
/*  00_0002   2015/03/09   DN 毛    優先度調停の不具合修正                    */
/*  01_0000   2015/11/23   DC       マルチコア対応(RAM干渉対策)               */
/*  01_0001   2016/01/07   DC       送信完了通知のコールバック対応            */
/*  01_0002   2018/06/19   AUBASS   リプログ対応                              */
/*  01_0003   2019/02/12   AUBASS   Update                                    */
/*  01_0004   2019/07/16   AUBASS   Update                                    */
/*  01_0005   2019/12/03   AUBASS   Update                                    */
/*  01_0006   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/
#ifndef DCM_DCP_H
#define DCM_DCP_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/* セッション遷移要因の定義（ユーザ公開用） */
#define GDN_DCM_SESSION_FACTOR_INIT                     (0x00U)
#define GDN_DCM_SESSION_FACTOR_S3TIMEOUT                (0x01U)
#define GDN_DCM_SESSION_FACTOR_SID10                    (0x02U)
#define GDN_DCM_SESSION_FACTOR_OTHER                    (0xFFU)

/* セッションインデックスの定義（ユーザ未使用） */
#define GDN_DCM_DEFAULT_SESSION_INDEX                   ((gdn_uint8)0x00U)                          /* セッション状態初期値(デフォルトセッション)           */
#define GDN_DCM_EXTENDED_SESSION_INDEX                  ((gdn_uint8)0x02U)                          /* セッション状態(拡張セッション)                       */
#define GDN_DCM_REPROG_SESSION_INDEX                    ((gdn_uint8)0x01U)                          /* セッション状態(プログラミングセッション)             */

/* セキュリティ状態の定義（ユーザ公開用） */
#define GDN_DCM_DCP_SECURITY_ALL_LOCK                   ((gdn_uint8)0x00U)                          /* セキュリティ状態初期値(全セキュリティレベルロック)   */

/* DCM通信状態 */
#define GDN_DCM_DCP_COM_IDLE                            ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_COM_BUSY                            ((gdn_uint8)0x01U)

/* レスポンスペンディング送信状態 */
#define GDN_DCM_DCP_PENDRESP_NOT_SENT                   ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_PENDRESP_SENT                       ((gdn_uint8)0x11U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/

typedef struct {
    gdn_uint8                           SecurityLevelBitPattern;                                    /*  セキュリティレベル(BitPattarn)      */
} Gdn_Dcm_Dcp_SecurityLevelAttrType;

typedef struct {
    gdn_uint8                           SessionCtrlIndex;                                           /*  セッション状態インデックス          */
    gdn_uint8                           OldSessionCtrlIndex;                                        /*  前回のセッション状態インデックス    */
} Gdn_Dcm_Dcp_SessionCtrlAttrType;

typedef struct {
    Gdn_Dcm_NegativeResponseCodeType    Nrc;                                                        /* 否定応答コード                       */
    Gdn_Dcm_MsgAddInfoSuppressResponseType    SuppressResInfoLegal[ GDN_DCM_AddressKindNum ];       /* 法規サービス否定応答抑制情報         */
                                                                                                    /* (配列0=機能アドレス時)               */
                                                                                                    /* (配列1=物理アドレス時)               */
    Gdn_Dcm_MsgAddInfoSuppressResponseType    SuppressResInfoExtend[ GDN_DCM_AddressKindNum ];      /* 非法規サービス否定応答抑制情報       */
                                                                                                    /* (配列0=機能アドレス時)               */
                                                                                                    /* (配列1=物理アドレス時)               */
} Gdn_Dcm_Dcp_NegativeResponseInfoType;

/*--------------------------------*/
/* コンフィグレーション構造体定義 */
/*--------------------------------*/

/* RXPDUコンフィグレーション項目 */
typedef struct {
    Gdn_PduIdType                           RxPduId;                                                /* 受信PduId                            */
    Gdn_Dcm_MsgAddInfoReqTypeType           AddressType;                                            /* アドレスタイプ                       */
    gdn_uint8                               ConnectionId;                                           /* ConnectionId                         */
} Gdn_Dcm_Dcp_RxPduConfigType;

/* Connectionコンフィグレーション項目 */
typedef struct {
    gdn_uint8                               PriorityValue;                                          /* Connectionの優先順位                 */
    Gdn_PduIdType                           TxConfPduId;                                            /* 送信完了用TxPduId                    */
    Gdn_PduIdType                           TxPduId_Ref;                                            /* 送信用TxPduId                        */
} Gdn_Dcm_Dcp_ConnectionConfigType;

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

extern GdnConst Gdn_Dcm_Dcp_ConnectionConfigType    Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_ALL_CONNECTION_NUM];
extern GdnConst Gdn_Dcm_Dcp_RxPduConfigType         Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_ALL_RXPDUID_NUM];
extern GdnConst Gdn_Dcm_SessionCtrlConfigType       Gdn_Dcm_SessionCtrlConfig[GDN_DCM_SESSIONCTRL_SUPPORT_NUM];

#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_MainFunction                                   */
/* Description   | DCM_DCPメイン関数（定期周期コール）                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_MainFunction (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_Init                                           */
/* Description   | DCM_DCP初期化                                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_Init (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetRxPduId                                     */
/* Description   | 実行中のRxPduIdを取得                                      */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (out) RxPduId                                              */
/* Return Value  | Gdn_Std_ReturnType                                         */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_Dcp_GetRxPduId
(
    P2VAR(Gdn_PduIdType, AUTOMATIC, DCM_APPL_DATA) RxPduId
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SetNegativeResponse                            */
/* Description   | NRCをセット                                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  ErrorCode        : NRC                               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SetNegativeResponse
(
    VAR(Gdn_Dcm_NegativeResponseCodeType, AUTOMATIC) t_Nrc
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ProcessingDone                                 */
/* Description   | 応答要求                                                   */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (-)   pMsgContext->ReqData    : 未使用                     */
/*               | (-)   pMsgContext->ReqDataLen : 未使用                     */
/*               | (in)  pMsgContext->ResData    : 肯定応答データ(SIDを除く)  */
/*               | (in)  pMsgContext->ResDataLen : ResDataのデータ長          */
/*               | (in)  pMsgContext->ReqType    : 未使用                     */
/*               | (in)  pMsgContext->SuppressResponse : 応答抑制情報         */
/*               | (-)   pMsgContext->ResMaxDataLen    : 未使用               */
/*               | (in)  ProcessingDoneStatus  : 応答状態（通常/キャンセルNG）*/
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ProcessingDone
(
    P2CONST(Gdn_Dcm_MsgContextType, AUTOMATIC, DCM_APPL_CONST) t_MsgContext,
    VAR(Gdn_Dcm_ProcessingDoneStatusType, AUTOMATIC) t_ProcessingStatus
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_StartOfReception                               */
/* Description   | 受信開始通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  info->SduDataPtr : PduDataのポインタ                 */
/*               | (in)  info->SduLength  : PduData長                         */
/*               | (in)  TpPduLength      : Pduの全Data長                     */
/*               | (out) RxBufferSizePtr  : 残りの受信バッファ長              */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 受信開始OK                        */
/*               |  GDN_BUFREQ_E_NOT_OK   : 受信開始NG                        */
/*               |  GDN_BUFREQ_E_OVFL     : 受信バッファオーバー              */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_Dcp_StartOfReception
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) t_pPduInfo,
    VAR(Gdn_PduLengthType, AUTOMATIC) t_TpPduLength,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) t_pRxBufferSizePtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_CopyRxData                                     */
/* Description   | 受信データコピー                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  PduInfoPtr->SduDataPtr : コピーするPduData           */
/*               | (in)  PduInfoPtr->SduLength  : コピーするPduData長         */
/*               | (out) RxBufferSizePtr  : 残りの受信バッファ長              */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 受信データコピー結果OK            */
/*               |  GDN_BUFREQ_E_NOT_OK   : 受信データコピー結果NG            */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_Dcp_CopyRxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmRxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) t_pPduInfo,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) t_pRxBufferSizePtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_RxIndication                                   */
/* Description   | 受信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmRxPduId       : DcmのRxPduId                      */
/*               | (in)  Result           : 下位層の受信結果                  */
/*               |  GDN_NTFRSLT_OK        : 受信正常完了                      */
/*               |  other                 : 受信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_RxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmRxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) t_Result
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_CopyTxData                                     */
/* Description   | 送信データコピー                                           */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  DcmTxPduId       : DcmのTxPduId                      */
/*               | (in)  PduInfoPtr       : PduDataコピー先のアドレス         */
/*               | (in)  RetryInfoPtr     : リトライ関連情報                  */
/*               | (out) TxDataCntPtr     : 残りの送信TpPduデータ長           */
/* Return Value  | Gdn_BufReq_ReturnType                                      */
/*               |  GDN_BUFREQ_OK         : 送信データコピー結果OK            */
/*               |  GDN_BUFREQ_E_NOT_OK   : 送信データコピー結果NG            */
/* Notes         |  ・RetryInfoPtrは、NULL_PTR固定で指定すること。            */
/*               |  （Dcmにコピーのリトライのニーズがなく非対応のため。）     */
/*               |  ・Sタスクでコールすること。(タスク抜け/タスク干渉防止)    */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_Dcp_CopyTxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmTxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) t_PduInfoPtr,
    P2CONST(Gdn_RetryInfoType, AUTOMATIC, DCM_APPL_CONST) t_RetryInfoPtr,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) t_TxDataCntPtr
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_TxConfirmation                                 */
/* Description   | 送信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DcmTxPduId       : DcmのTxPduId                      */
/*               | (in)  Result           : 下位層の送信結果                  */
/*               |  GDN_NTFRSLT_OK        : 送信正常完了                      */
/*               |  other                 : 送信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_TxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmTxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) t_Result
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetSesCtrlTypeBitPattern                       */
/* Description   | 現在のセッション状態のIndexのBitPatternを取得              */
/* Parameter(s)  | None                                                       */
/* Return Value  | gdn_uint8                                                  */
/*               | SessionIndexBitPattern : SessionIndexのビットパターン      */
/* Notes         | Dspが使用する。                                            */
/******************************************************************************/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

extern Gdn_Dcm_Dcp_SessionCtrlAttrType      Gdn_Dcm_Dcp_SessionCtrlAttr;

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

#define Gdn_Dcm_Dcp_GetSesCtrlTypeBitPattern()    \
            ((gdn_uint8)GDN_BIT0 << (Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex))

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_SetSesCtrlTypeBitPattern                       */
/* Description   | セッション状態のIndexのBitPatternを設定                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  SesCtrlType : 新しいセッションのIndexのBitPattern    */
/*               | (in)    TransitionFactor                                   */
/* Return Value  | None                                                       */
/* Notes         | Dspが使用する。Sタスクでコールすること。                   */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dsl_SetSesCtrlTypeBitPattern
(
    VAR(gdn_uint8, AUTOMATIC) SesCtrlTypeIdxBitPtrn,
    VAR(gdn_uint8, AUTOMATIC) TransitionFactor
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetSecurityLevelBitPattern                     */
/* Description   | SecurityLevelを取得                                        */
/* Parameter(s)  | None                                                       */
/* Return Value  | gdn_uint8                                                  */
/*               | SecurityLevelBitPattern : SecurityLevelのビットパターン    */
/* Notes         |                                                            */
/******************************************************************************/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

extern Gdn_Dcm_Dcp_SecurityLevelAttrType    Gdn_Dcm_Dcp_SecurityLevelAttr;

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

#define Gdn_Dcm_Dcp_GetSecurityLevelBitPattern()    \
            (Gdn_Dcm_Dcp_SecurityLevelAttr.SecurityLevelBitPattern)

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SetSecurityLevelBitPattern                     */
/* Description   | SecurityLevelの設定                                        */
/* Parameters    | (in) t_SecurityLevel:新しいセキュリティのIndexのBitPattern */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SetSecurityLevelBitPattern
(
    VAR(gdn_uint8, AUTOMATIC) t_SecurityLevel
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_TimeoutIndication                              */
/* Description   | タイムアウト通知                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TimerId      : タイマのID                             */
/*               | (in) Synchronizer : タイマ同期用カウンタ                   */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_TimeoutIndication
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
);
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SessionTransitionFuncTask                      */
/* Description   | セッション遷移時タスク起床関数                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) Parameter    : OSから渡されるパラメータ               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SessionTransitionFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ServiceProcessingFuncTask                      */
/* Description   | サービス実行要求時タスク起床関数                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) Parameter    : OSから渡されるパラメータ               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ServiceProcessingFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask              */
/* Description   | サブマイコンゲートウェイ実行要求時タスク起床関数           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) Parameter    : OSから渡されるパラメータ               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
);
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ProcessingDoneFuncTask                         */
/* Description   | サービス応答要求時タスク起床関数                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) Parameter    : OSから渡されるパラメータ               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ProcessingDoneFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_Time                                           */
/* Description   | Dcm の定周期[1ms]実行関数                                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_Time (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_NotifySessionChange                            */
/* Description   | DCM_DCPのセッション遷移通知                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) t_NewSession : 遷移するセッション                     */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_NotifyChangeSession
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) t_NewSession
);
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_NotifySecurityChange                           */
/* Description   | DCM_DCPのセキュリティ変更通知                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) t_NewSecurity ： 設定するセキュリティ                 */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_NotifyChangeSecurity
(
    VAR(gdn_uint8, AUTOMATIC) t_NewSecurity
);
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetComStatus                                   */
/* Description   | DCMの通信状態を取得する                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | gdn_uint8                                                  */
/*               |      GDN_DCM_DCP_COM_IDLE : 非通信中                       */
/*               |      GDN_DCM_DCP_COM_BUSY : 通信中                         */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(gdn_uint8, DCM_CODE_SLOW) Gdn_Dcm_Dcp_GetComStatus (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetPendRespStatus                              */
/* Description   | レスポンスペンディング送信状態を取得する                   */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | gdn_uint8                                                  */
/*               |      GDN_DCM_DCP_PENDRESP_NOT_SENT : 未送信                */
/*               |      GDN_DCM_DCP_PENDRESP_SENT     : 送信済み              */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(gdn_uint8, DCM_CODE_SLOW) Gdn_Dcm_Dcp_GetPendRespStatus (void);

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SetServiceDiscard                              */
/* Description   | サービス破棄設定                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  Flag  : サービス破棄設定                             */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SetServiceDiscard
(
    VAR(gdn_uint8, AUTOMATIC) Flag
);

/*-- End Of File -------------------------------------------------------*/
#endif
