/* Gdn_Dcm_Dcp_c_01_0007 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | Gdn_Dcm_Dcp.c                                                */
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
/*  01_0006   2022/03/01   AUBASS   Update                                    */
/*  01_0007   2022/12/06   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include    <SchM_Dcm.h>
#include    <Rte.h>
#include    <ReprogOpt.h>
#include    <Sys.h>
#include    <SubMiconIf.h>
#include    <DiagCmn.h>
#include    <DiagLib.h>
#include    <DiagSrv.h>
#include    <Gdn_Types.h>
#include    <Gdn_Ucfg.h>
#include    <Gdn_LocalNotification.h>
#include    <GdnWrapper/Gdn_TmrSrv.h>
#include    <PduR.h>
#include    <PduR/Gdn_PduR.h>
#include    <Dcm/Gdn_Dcm.h>
#include    "Dcm/Dcp/Gdn_Dcm_Dcp.h"
#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#include    <SchM.h>
#endif

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/* DCM状態 */
#define GDN_DCM_DCP_IDLE_INACTIVE                       ((gdn_uint8)0x00U)     /* アイドル(INACTIVE)                       */
#define GDN_DCM_DCP_IDLE_ACTIVE                         ((gdn_uint8)0x01U)     /* アイドル(ACTIVE)                         */
#define GDN_DCM_DCP_RX_NORMAL                           ((gdn_uint8)0x10U)     /* 受信中                                   */
#define GDN_DCM_DCP_PROCESS_NORMAL                      ((gdn_uint8)0x20U)     /* 実行中                                   */
#define GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX               ((gdn_uint8)0x21U)     /* 実行中(1stキャンセル中 && 2nd受信中)     */
#define GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND              ((gdn_uint8)0x22U)     /* 実行中(1stキャンセル中 && 2nd受信完了)   */
#define GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO               ((gdn_uint8)0x23U)     /* 実行中(1stキャンセル中 && 2nd受信なし)   */
#define GDN_DCM_DCP_TX_NORMAL                           ((gdn_uint8)0x30U)     /* 送信中                                   */
#define GDN_DCM_DCP_TX_WAIT_CONF                        ((gdn_uint8)0x31U)     /* NRC0x78送信完了待ち                      */

/* バッファサイズ */
#define GDN_DCM_DCP_SUB_RX_BUFFER_SIZE                  (8)         /* MultiClinet用の受信バッファサイズ */

/* サービスIDバイトサイズ */
#define GDN_DCM_DCP_SERVICE_ID_LENGTH                   ((gdn_uint8)1U)

/* キープアライブメッセージ */
#define GDN_DCM_DCP_KEEPALIVEMSG_LENGTH                 ((gdn_uint16)0x0002U)
#define GDN_DCM_DCP_KEEPALIVEMSG_BYTE1                  ((gdn_uint8)DIAG_SID_TP)
#define GDN_DCM_DCP_KEEPALIVEMSG_BYTE2                  ((gdn_uint8)0x80U)

/* 肯定応答サービスID */
#define GDN_DCM_DCP_POSITIVE_RESPONSE_SERVICE_ID        ((gdn_uint8)0x40U)

/* 否定応答サービスID */
#define GDN_DCM_DCP_NEGATIVE_RESPONSE_SERVICE_ID        ((gdn_uint8)0x7FU)

/* 否定応答メッセージ長 */
#define GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH            ((gdn_uint8)3U)

/* 否定応答コードの初期値 */
#define GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT      ((Gdn_Dcm_NegativeResponseCodeType)DIAG_NRC_PR)

/* 否定応答コード（ペンディング） */
#define GDN_DCM_DCP_PENDING_RESPONSE_NRC                ((gdn_uint8)DIAG_NRC_RCRRP)
#define GDN_DCM_DCP_COUNTER_MAX_GUARD                   ((gdn_uint8)0xFFU)

/* 否定応答コード（P2上限回数、P4タイムアウト） */
#define GDN_DCM_DCP_GENERAL_REJECT_NRC                  (DIAG_NRC_GR)
#define GDN_DCM_DCP_TimeoutValueType_MaxValue           (0xFFFFU)

/* レスポンス種別 */
#define GDN_DCM_DCP_RESPONSE_KIND_POSITIVE              ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE              ((gdn_uint8)0x01U)

/* レスポンス要因 */
#define GDN_DCM_DCP_RESPONSE_FACTOR_NRC78               ((gdn_uint8)0x01U)
#define GDN_DCM_DCP_RESPONSE_FACTOR_DSDFAILSAFE         ((gdn_uint8)0x02U)
#define GDN_DCM_DCP_RESPONSE_FACTOR_MSGERR              ((gdn_uint8)0x04U)
#define GDN_DCM_DCP_RESPONSE_FACTOR_DSP                 ((gdn_uint8)0x05U)

/* レスポンス予約 */
#define GDN_DCM_DCP_RESPONSE_RESERVE_NONE               ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_RESPONSE_RESERVE_DSP                ((gdn_uint8)0x01U)
#define GDN_DCM_DCP_RESPONSE_RESERVE_NRC78MAXNUM        ((gdn_uint8)0x02U)
#define GDN_DCM_DCP_RESPONSE_RESERVE_P4TIMEOUT          ((gdn_uint8)0x03U)
#define GDN_DCM_DCP_RESPONSE_RESERVE_NRC78PENDING       ((gdn_uint8)0x04U)

/* 拡張サービスIDの最小値 */
#define GDN_DCM_DCP_UDS_SERVICE_ID_MIN                  ((gdn_uint8)0x10U)

/* 優先度チェック関数の戻り値 */
#define GDN_DCM_DCP_PRIORITY_CHECK_BEFORE               ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_PRIORITY_CHECK_AFTER                ((gdn_uint8)0x01U)

/* セッション状態算出 */
#define GDN_DCM_DSL_UINT8_BIT_WIDTH                     (8U)

/* セッション状態取得 */
#define GDN_DCM_DSL_GetSesCtrlTypeIndex()               (Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex)
#define GDN_DCM_DSL_GetOldSesCtrlTypeIndex()            (Gdn_Dcm_Dcp_SessionCtrlAttr.OldSessionCtrlIndex)

/* 内部状態 取得マクロ */
#define GDN_DCM_DCP_GetMainRxPduId()                    (Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex)
#define GDN_DCM_DCP_GetMainConnectionId()               (Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].ConnectionId)
#define GDN_DCM_DCP_GetMainTxPduId_Ref()                (Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_GetMainConnectionId()].TxPduId_Ref)
#define GDN_DCM_DCP_GetMainTxConfPduId()                (Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_GetMainConnectionId()].TxConfPduId)

#define GDN_DCM_DCP_GetSubRxPduId()                     (Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex)
#define GDN_DCM_DCP_GetSubRxConnectionId()              (Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetSubRxPduId()].ConnectionId)

/* 演算用マクロ */
#define GDN_DCM_DCP_Index2                              (2U)
#define GDN_DCM_DCP_Index3                              (3U)

/* イベント実行用マクロ */
#define GDN_DCM_DCP_SESSIONTRANSITION_PARAM_NUM         (3UL)

/* NRC */
#define GDN_DCM_DCP_GeneralRejectNrc                    ((gdn_uint8)DIAG_NRC_GR)

#define GDN_DCM_DCP_CHECK_SECURITY_LOCK_BIT_PATTERN     ((gdn_uint8)0x00U)

/* サービス実行対象マイコン */
#define GDN_DCM_DCP_TARGET_MICON_NONE                   ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_TARGET_MICON_MAIN                   ((gdn_uint8)0x11U)
#define GDN_DCM_DCP_TARGET_MICON_SUB                    ((gdn_uint8)0x22U)

/* サブマイコンゲートウェイ実行中サービスID */
#define GDN_DCM_DCP_SUMBICONGATEWAY_SID_NONE            ((gdn_uint8)0x00U)

/* サブマイコン通信レスポンスデータチェック結果 */
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_POSITIVE       ((gdn_uint8)0x00U)
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NEGATIVE       ((gdn_uint8)0x01U)
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_INVALID        ((gdn_uint8)0x02U)

/* サブマイコン通信レスポンスデータチェック用マクロ */
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_SID_POS        (0U)
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_REQSID_POS     (1U)
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NRC_POS        (2U)
#define GDN_DCM_DCP_SUBMICONGATEWAY_RESP_MIN_LEN        ((gdn_uint8)1U)

#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#define GDN_DCM_DCP_STAYINBOOT_SUBFUNC_MASK             ((gdn_uint8)0x7FU)
#endif

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/* 受信オブジェクト変数(1stClient) */
typedef struct {
    Gdn_Dcm_MsgContextType              MsgContext;                                         /*  Msgコンテキスト                     */
    gdn_uint8                           RxPduIdIndex;                                       /*  受信RxPduIdインデックス             */
} Gdn_Dcm_Dcp_MainRxCtrlAttrType;

/* 受信オブジェクト変数(2ndClient) */
typedef struct {
    Gdn_Dcm_MsgContextType              MsgContext;                                         /*  Msgコンテキスト                     */
    gdn_uint8                           RxPduIdIndex;                                       /*  受信RxPduIdインデックス             */
} Gdn_Dcm_Dcp_SubRxCtrlAttrType;

/* 実行サービスオブジェクト変数    */
typedef struct {
    Gdn_Dcm_NegativeResponseCodeType    Nrc;                                                /*  否定応答コード(NRC)                 */
} Gdn_Dcm_Dcp_ServiceCtrlAttrType;

/* 送信オブジェクト変数            */
typedef struct {
    gdn_uint16                          RemainingTxDataLen;                                 /*  残送信データ長                      */
    gdn_uint8                           PendingResponseTxNum;                               /*  NRC78送信送信回数                   */
    gdn_uint8                           ResponseKind;                                       /*  応答種別（肯定or否定）              */
    gdn_uint8                           ResponseFactor;                                     /*  応答要因識別(Dsd or Dsp)            */
    gdn_uint8                           ResponseReserve;                                    /*  応答予約                            */
    gdn_bool                            PendingResponseTxFlg;                               /*  NRC78送信中フラグ                   */
} Gdn_Dcm_Dcp_TxCtrlAttrType;

#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
/* BS/STmin変更オブジェクト変数    */
typedef struct {
    Gdn_Std_ReturnType                  BsStminSettingErr;                                  /*  BS/STminの設定エラー検出            */
} Gdn_Dcm_Dcp_BsSTminCtrlAttrType;
#endif

typedef struct {
    uint16                              SchMValue;
    gdn_uint8                           GdnValue;
} Gdn_Dcm_Dcp_SecLevelMatrixType;

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*  Local functions(セッション)                                               */
static void Gdn_Dcm_Dsl_SessionTransition( gdn_uint8 t_NewSessionIndex, gdn_uint8 t_TransitionFactor );

/*  Local functions(優先判定)                                                 */
static gdn_uint8 Gdn_Dcm_Dsl_PriorityCheck( gdn_uint8 t_NewRxPduIdIndex, const Gdn_PduInfoType* t_pPduInfo );
static void Gdn_Dcm_Dsl_PreemptProcessing( gdn_uint8 t_NewRxPduIdIndex, Gdn_PduLengthType* t_BufLength );

#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
/*  Local functions(タイマ開始)                                               */
static void Gdn_Dcm_Dsl_StartP2Timer( void );
static void Gdn_Dcm_Dsl_StartS3Timer( void );
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_StartP4Timer( void );
#endif

/*  Local functions(タイマ停止)                                               */
static void Gdn_Dcm_Dsl_StopP2Timer( void );
static void Gdn_Dcm_Dsl_StopS3Timer( void );
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_StopP4Timer( void );
#endif

/*  Local functions(タイムアウト)                                             */
static void Gdn_Dcm_Dsl_P2MaxTimeout( void );
static void Gdn_Dcm_Dsl_PendingResponseMessageTransmit( void );
static void Gdn_Dcm_Dsl_S3Timeout( void );
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_P4Timeout( void );
static void Gdn_Dcm_Dsl_P4TimeoutConfirmed( void );
#endif
#endif

/*  Local functions(サービス実行)                                             */
static void Gdn_Dcm_Dsl_PreServiceIndication( gdn_uint8 t_DcmRxPduIdIndex );
static void Gdn_Dcm_Dsd_ServiceIndication( void );
static Gdn_Dcm_NegativeResponseCodeType Gdn_Dcm_Dsd_SidCheck( void );
static Gdn_Std_ReturnType Gdn_Dcm_Dsd_ServiceCancel( void );
static gdn_bool Gdn_Dcm_Dsl_KeepAliveMsgCheck( void );

/*  Local functions(サービス応答)                                             */
static void Gdn_Dcm_Dsl_ResponseTransmit( const Gdn_PduInfoType* t_ResponseInfo, Gdn_Dcm_MsgAddInfoSuppressResponseType t_SuppressInfo );
static void Gdn_Dcm_Dsd_Confirmation( Gdn_NotifResultType t_Result_low );

/*  Local functions(応答Msg生成)                                              */
static void Gdn_Dcm_Dsl_PositiveResponseMessageTransmit( const Gdn_Dcm_MsgContextType* t_pMsgContext, gdn_uint8 t_Factor );
static void Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( gdn_uint8 t_ServiceId, Gdn_Dcm_MsgAddInfoSuppressResponseType t_SuppressInfo, gdn_uint8 t_Factor, Gdn_Dcm_NegativeResponseCodeType t_Nrc );
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_P4TimeoutMessageTransmit( void );
#endif

/*  Local functions(BS/STmin変更)                                             */
#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
static void Gdn_Dcm_Dsl_BsSTminChange( gdn_uint8 t_SesCtlIndex);
#endif

/*  Local functions(2nd受信データを1st受信データにコピー)                     */
static void Gdn_Dcm_Dsl_CopyRxDataSubToMain( void );

/*  Local functions(アイドル状態遷移時のEntry処理)                            */
static void Gdn_Dcm_Dcp_EntryIdleState( void );

/* Local functions[実行中サービスIDの取得] */
static gdn_uint8 Gdn_Dcm_Dcp_GetMainServiceId( void );

/* Local functions[否定応答情報の取得] */
static void Gdn_Dcm_Dcp_GetNegativeResponseInfo( Gdn_Dcm_NegativeResponseCodeType t_Nrc, Gdn_Dcm_NegativeResponseInfoType* t_pNegativeResponseInfo );

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing( Gdn_Dcm_OpStatusType t_OpStatus );
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing_Execute( Gdn_Dcm_OpStatusType t_OpStatus );
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing_Cancel( void );
static gdn_uint8 Gdn_Dcm_Dcp_SubMiconGateway_CheckResponse( const gdn_uint8* t_RespData, gdn_uint16 t_RespDataSize );
static void Gdn_Dcm_Dcp_SubMiconGateway_TransmitPositiveResponse( void );
static void Gdn_Dcm_Dcp_SubMiconGateway_TransmitNegativeResponse( Gdn_Dcm_NegativeResponseCodeType t_Nrc );
#endif

#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
static Gdn_Std_ReturnType Gdn_Dcm_Dsd_CheckStayInBootMsg( void );
#endif

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

/* DCM制御状態 */
static gdn_uint8                        Gdn_Dcm_Dcp_State;

static Gdn_Dcm_Dcp_MainRxCtrlAttrType   Gdn_Dcm_Dcp_MainRxCtrlAttr[ GDN_DCM_DCP_RXTX_AREA_NUM ];
static Gdn_Dcm_Dcp_SubRxCtrlAttrType    Gdn_Dcm_Dcp_SubRxCtrlAttr;
static Gdn_Dcm_Dcp_ServiceCtrlAttrType  Gdn_Dcm_Dcp_ServiceCtrlAttr;
static Gdn_Dcm_Dcp_TxCtrlAttrType       Gdn_Dcm_Dcp_TxCtrlAttr;
#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
static Gdn_Dcm_Dcp_BsSTminCtrlAttrType  Gdn_Dcm_Dcp_BsSTminCtrlAttr;
#endif
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static gdn_uint32   Gdn_Dcm_Dcp_RemainedP4Timeout;
#endif
#endif
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static gdn_uint8                            Gdn_Dcm_Dcp_TargetMicon;
static gdn_uint8                            Gdn_Dcm_Dcp_SubMiconGateway_ServiceId;
#endif

/* レスポンスペンディング送信状態 */
static gdn_uint8                            Gdn_Dcm_Dcp_PendRespStatus;

/* サービス破棄設定 */
static gdn_uint8                            Gdn_Dcm_Dcp_ServiceDiscard;

/* 現在使用中の送受信面を示すIndex値 */
static gdn_uint8                            Gdn_Dcm_Dcp_SwitchBufferFlag;
static gdn_uint8                            Gdn_Dcm_Dcp_CurrentRxTxAreaIndex;
static Gdn_Dcm_Dcp_MainRxCtrlAttrType       *Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr;
static gdn_uint8                            *Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

#define GDN_DCM_START_SEC_VAR_LARGE
#include <Gdn_Dcm_MemMap.h>

static gdn_uint8    Gdn_Dcm_Dcp_MainRxTxBuff[ GDN_DCM_DCP_RXTX_AREA_NUM ][ GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE ];  /*  送受信バッファ */
static gdn_uint8    Gdn_Dcm_Dcp_NegativeResBuff[ GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH ];    /*  否定応答送信バッファ */
static gdn_uint8    Gdn_Dcm_Dcp_SubRxBuff[ GDN_DCM_DCP_SUB_RX_BUFFER_SIZE ];                /*  受信専用バッファ */

#define GDN_DCM_STOP_SEC_VAR_LARGE
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* extern Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

Gdn_Dcm_Dcp_SecurityLevelAttrType    Gdn_Dcm_Dcp_SecurityLevelAttr;
Gdn_Dcm_Dcp_SessionCtrlAttrType      Gdn_Dcm_Dcp_SessionCtrlAttr;

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

static GdnConst Gdn_Dcm_Dcp_SecLevelMatrixType Gdn_Dcm_Dcp_SecLevelMatrix[] = {
    { SCHM_BSWM_SECURITY_UNLOCK_LV1,    GDN_DCM_SECURITY_UNLOCK_LV1 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV2,    GDN_DCM_SECURITY_UNLOCK_LV2 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV3,    GDN_DCM_SECURITY_UNLOCK_LV3 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV4,    GDN_DCM_SECURITY_UNLOCK_LV4 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV5,    GDN_DCM_SECURITY_UNLOCK_LV5 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV6,    GDN_DCM_SECURITY_UNLOCK_LV6 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV7,    GDN_DCM_SECURITY_UNLOCK_LV7 },
    { SCHM_BSWM_SECURITY_UNLOCK_LV8,    GDN_DCM_SECURITY_UNLOCK_LV8 }
};
static GdnConst gdn_uint8 Gdn_Dcm_Dcp_SecLevelMatrixNum = (sizeof(Gdn_Dcm_Dcp_SecLevelMatrix) / sizeof(Gdn_Dcm_Dcp_SecLevelMatrix[0]));
#if ( GDN_DCM_DCP_RXTX_AREA_NUM > 1U )
static GdnConst gdn_uint8 Gdn_Dcm_Dcp_RxTxAreaNum = GDN_DCM_DCP_RXTX_AREA_NUM;
#endif

#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* External Function                                                          */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CODE
#include <Gdn_Dcm_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_MainFunction                                   */
/* Description   | DCM_DCPメイン関数（定期周期コール）                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_Init                                           */
/* Description   | DCM_DCP初期化                                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | None                                                       */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_Init (void)
{
    /* Dcm制御状態 初期化 */
    Gdn_Dcm_Dcp_State = GDN_DCM_DCP_IDLE_INACTIVE;

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    /* サービス実行対象マイコン 初期化 */
    Gdn_Dcm_Dcp_TargetMicon = GDN_DCM_DCP_TARGET_MICON_NONE;
    /* サブマイコンゲートウェイ実行中サービスID 初期化 */
    Gdn_Dcm_Dcp_SubMiconGateway_ServiceId = GDN_DCM_DCP_SUMBICONGATEWAY_SID_NONE;
#endif

    Gdn_Dcm_Dcp_PendRespStatus = GDN_DCM_DCP_PENDRESP_NOT_SENT;

    /* セキュリティオブジェクト変数 初期化 */
    Gdn_Dcm_Dcp_SecurityLevelAttr.SecurityLevelBitPattern = GDN_DCM_DCP_SECURITY_ALL_LOCK;

    /* セッションオブジェクト変数 初期化 */
    Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex = GDN_DCM_DEFAULT_SESSION_INDEX;

    /* 現在使用中の送受信面を示すIndex値 初期化 */
    Gdn_Dcm_Dcp_SwitchBufferFlag = GDN_OFF;
    Gdn_Dcm_Dcp_CurrentRxTxAreaIndex = 0U;
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr = &Gdn_Dcm_Dcp_MainRxCtrlAttr[Gdn_Dcm_Dcp_CurrentRxTxAreaIndex];
    Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr = &Gdn_Dcm_Dcp_MainRxTxBuff[Gdn_Dcm_Dcp_CurrentRxTxAreaIndex][0];

#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
    /* BS STmin変更オブジェクト変数 初期化 */
    Gdn_Dcm_Dcp_BsSTminCtrlAttr.BsStminSettingErr = GDN_E_OK;
#endif

    Gdn_Dcm_Dcp_SetServiceDiscard( GDN_OFF );

    /* 前回のセッション状態インデックス 初期化不要 */
    /* 受信オブジェクト変数(1stClient)  初期化不要 */
    /* 受信オブジェクト変数(2ndClient)  初期化不要 */
    /* 実行サービスオブジェクト変数     初期化不要 */
    /* 送信オブジェクト変数             初期化不要 */
    /* 残P4タイマ時間                   初期化不要 */
    /* 送受信バッファ                   初期化不要 */
    /* 否定応答送信バッファ             初期化不要 */
    /* 受信専用バッファ                 初期化不要 */

    DiagLib_Init();

    DiagSrv_Init();

    return;
}

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
)
{
    Gdn_Std_ReturnType      t_RetVal;

    t_RetVal = GDN_E_NOT_OK;

    if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL         ) ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX  ) ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND ) ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO  )) {

        *RxPduId = Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].RxPduId;
        t_RetVal = GDN_E_OK;

    } else { /* 実行中以外のためNGを返す。 */
    }
    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_StartOfReception                               */
/* Description   | 受信開始通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_RxPduId              : DcmのRxPduId                */
/*               | (in)  t_pPduInfo->SduDataPtr : PduDataのポインタ           */
/*               | (in)  t_pPduInfo->SduLength  : PduData長                   */
/*               | (in)  t_TpPduLength          : Pduの全Data長               */
/*               | (out) t_pRxBufferSizePtr     : 残りの受信バッファ長        */
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
)
{
    Gdn_BufReq_ReturnType                   t_RetVal;
    gdn_uint8                               t_PduIdCnt;
    gdn_uint8                               t_RetPriorityCheck;

    t_RetVal = GDN_BUFREQ_E_NOT_OK;

    /* 受信PDU ID検索 */
    for ( t_PduIdCnt=0U; t_PduIdCnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_PduIdCnt++ ) {
        if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].RxPduId == t_RxPduId ) {

            /*----------------------------------------------------------------*/
            /* TpPduLengthチェック                                            */
            /* TpPduLengthが受信バッファ長以下であるかを確認する。            */
            /* Dsdは、応答SID1Byte分の送信バッファを確保しておく。            */
            /* Dspは、サービス毎にバッファオーバチェックする必要あり。        */
            /*----------------------------------------------------------------*/

            /*----------------------------------------------------------------*/
            /* 1stClientキャンセル後は、2ndClinetもMainBufferを使用するため、 */
            /* TpPduLengthチェックの対象は、MainBufferの長さとする。          */
            /*----------------------------------------------------------------*/

            /* チェック結果OK(バッファ長以下)の場合 */
            if ( t_TpPduLength <= ((gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH) ) {

                *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;

                /* "アイドル中"の場合 */
                if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_IDLE_INACTIVE ) ||
                    ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_IDLE_ACTIVE )){

                    if( Gdn_Dcm_Dcp_ServiceDiscard != (gdn_uint8)GDN_ON ) {
                        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_RX_NORMAL;
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
                        Gdn_Dcm_Dsl_StopS3Timer();
#endif
                        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;   /* 受信情報初期化 */
                        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen = 0x0000u;                     /* 受信情報初期化 */
                        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex = t_PduIdCnt;                           /* 受信情報記憶   */
                        t_RetVal = GDN_BUFREQ_OK;
                    }

                /* "アイドル中"以外の場合 */
                } else {

                    t_RetPriorityCheck = Gdn_Dcm_Dsl_PriorityCheck( t_PduIdCnt, t_pPduInfo);
                    /* 前優先の場合 */
                    if ( GDN_DCM_DCP_PRIORITY_CHECK_AFTER != t_RetPriorityCheck ) {
                        if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].AddressType != Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType ) {
                            t_RetVal = GDN_BUFREQ_OK;
                        } else {
                            t_RetVal = GDN_BUFREQ_E_NOT_OK;
                        }
                    /* 後優先の場合 */
                    } else {
                        Gdn_Dcm_Dsl_PreemptProcessing( t_PduIdCnt, t_pRxBufferSizePtr);
                        t_RetVal = GDN_BUFREQ_OK;
                    }
                }
            /* チェック結果NG（バッファ長オーバー）の場合 */
            } else {
                t_RetVal = GDN_BUFREQ_E_OVFL;
            }
            break;
        }
    }
    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_CopyRxData                                     */
/* Description   | 受信データコピー                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_DcmRxPduId           : DcmのRxPduId                */
/*               | (in)  t_pPduInfo->SduDataPtr : コピーするPduData           */
/*               | (in)  t_pPduInfo->SduLength  : コピーするPduData長         */
/*               | (out) t_pRxBufferSizePtr     : 残りの受信バッファ長        */
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
)
{
    Gdn_BufReq_ReturnType   t_RetVal;
    gdn_uint16              t_CurrentBufferCnt;
    Gdn_PduLengthType       t_BuffSizeCnt;
    Gdn_PduIdType           t_RxPduId;
    gdn_uint8               t_PduIdCnt;

    t_RetVal = GDN_BUFREQ_E_NOT_OK;

    /* 1stClient受信中の場合 */
    if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_RX_NORMAL ) {

        /* 1stClientのRxPduIdと一致 */
        t_RxPduId = Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].RxPduId;
        if ( t_DcmRxPduId == t_RxPduId ) {
            t_CurrentBufferCnt = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen;

            /* 受信データコピー実施 */
            if ( t_pPduInfo->SduLength == (Gdn_PduLengthType)0U ) {
                *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE
                                      - Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen
                                      - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;
                t_RetVal = GDN_BUFREQ_OK;
            } else {
                if ( (Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen + t_pPduInfo->SduLength) <=
                     ((gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH) ) {
                    /* 受信データコピー */
                    for ( t_BuffSizeCnt = 0U; t_BuffSizeCnt < t_pPduInfo->SduLength ; t_BuffSizeCnt++ ){
                        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData[t_CurrentBufferCnt + t_BuffSizeCnt] = t_pPduInfo->SduDataPtr[t_BuffSizeCnt];
                    }
                    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen += t_pPduInfo->SduLength;   /* no wrap around */
                    *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE
                                          - Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen
                                          - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;
                    t_RetVal = GDN_BUFREQ_OK;
                } else { /* 受信データコピー拒否: 受信バッファオーバー */
                }
            }
        } else { /* 受信データコピー拒否: RxPduId不一致 */
            for ( t_PduIdCnt=0U; t_PduIdCnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_PduIdCnt++ ) {
                if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].RxPduId == t_DcmRxPduId ) {
                    if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].AddressType != Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType ) {
                        *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;
                        t_RetVal = GDN_BUFREQ_OK;
                    }
                    break;
                }
            }
        }

    /* 2ndClient受信中の場合 */
    } else if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX ) {

        /* 2ndClientのRxPduIdと一致 */
        t_RxPduId = Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetSubRxPduId()].RxPduId;
        if ( t_DcmRxPduId == t_RxPduId ) {
            t_CurrentBufferCnt = Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen;
            /* 受信データコピー実施 */
            if ( t_pPduInfo->SduLength == (Gdn_PduLengthType)0U ) {
                *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE - Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen;
                t_RetVal = GDN_BUFREQ_OK;
            } else {
                if ( (Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen + t_pPduInfo->SduLength) <=
                     ((gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE) ) {
                    /* 受信データコピー */
                    for ( t_BuffSizeCnt = 0U; t_BuffSizeCnt < t_pPduInfo->SduLength ; t_BuffSizeCnt++ ){
                        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqData[t_CurrentBufferCnt + t_BuffSizeCnt] = t_pPduInfo->SduDataPtr[t_BuffSizeCnt];
                    }
                    Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen += t_pPduInfo->SduLength;   /* no wrap around */
                    *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE - Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen;
                    t_RetVal = GDN_BUFREQ_OK;
                } else { /* 受信データコピー拒否: 受信バッファオーバー */
                }
            }
        } else { /* 受信データコピー拒否: RxPduId不一致 */
        }
    } else if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_IDLE_INACTIVE ) || ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_IDLE_ACTIVE )) {
        *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;
        t_RetVal = GDN_BUFREQ_OK;
    } else {  /* 受信データコピー拒否: 状態不一致 */
        for ( t_PduIdCnt=0U; t_PduIdCnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_PduIdCnt++ ) {
            if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].RxPduId == t_DcmRxPduId ) {
                if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].AddressType != Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType ) {
                    *t_pRxBufferSizePtr = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - (gdn_uint16)GDN_DCM_DCP_SERVICE_ID_LENGTH;
                    t_RetVal = GDN_BUFREQ_OK;
                }
                break;
            }
        }
    }
    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_RxIndication                                   */
/* Description   | 受信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_DcmRxPduId     : DcmのRxPduId                      */
/*               | (in)  t_Result         : 下位層の受信結果                  */
/*               |  GDN_NTFRSLT_OK        : 受信正常完了                      */
/*               |  other                 : 受信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_RxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmRxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) t_Result
)
{
    gdn_uint8                               t_PduIdCnt;

    /* BS,STmin設定リトライ */
    #if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
    if ( Gdn_Dcm_Dcp_BsSTminCtrlAttr.BsStminSettingErr != GDN_E_OK ) {
        Gdn_Dcm_Dsl_BsSTminChange( GDN_DCM_DSL_GetSesCtrlTypeIndex() );
    } else { /* BS/STmin正常設定時はリトライ不要 */
    }
    #endif

    /* 受信PDU IDインデックス検索 */
    for ( t_PduIdCnt=0U; t_PduIdCnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_PduIdCnt++ ) {
        if ( Gdn_Dcm_Dcp_RxPduIdConfig[t_PduIdCnt].RxPduId == t_DcmRxPduId ) {
            break;
        }
    }

    /* 1stClient受信中の場合 */
    if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_RX_NORMAL ) {
        if ( t_PduIdCnt == GDN_DCM_DCP_GetMainRxPduId() ) {
            if ( t_Result == GDN_NTFRSLT_OK ) {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_NORMAL;                     /* 実行中に遷移        */
                Gdn_Dcm_Dsl_PreServiceIndication( GDN_DCM_DCP_GetMainRxPduId() );   /* DSDに渡す前処理     */
                Gdn_Dcm_Dsd_ServiceIndication();                                    /* SIDディスパッチ処理 */
            } else {
                Gdn_Dcm_Dcp_EntryIdleState();
            }
        } else { /* 受信完了無視: RxPduId不一致 */
        }

    /* 2ndClient受信中(1stClient実行キャンセル中)の場合 */
    } else if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX ) {
        if ( t_PduIdCnt == GDN_DCM_DCP_GetSubRxPduId() ) {
            if ( t_Result == GDN_NTFRSLT_OK ) {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND;
            } else {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO;
            }
        } else { /* 受信完了無視: RxPduId不一致 */
        }
    } else { /* 受信完了無視: 状態不一致 */
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SetNegativeResponse                            */
/* Description   | NRCをセット                                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_Nrc            : NRC                               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SetNegativeResponse
(
    VAR(Gdn_Dcm_NegativeResponseCodeType, AUTOMATIC) t_Nrc
)
{
    if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL           )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX    )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND   )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO    ))  {
            Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc = t_Nrc;
    } else { /* NRC設定要求無視: 状態不一致 */
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ProcessingDone                                 */
/* Description   | 応答要求                                                   */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (-)   t_MsgContext->ReqData    : 未使用                    */
/*               | (-)   t_MsgContext->ReqDataLen : 未使用                    */
/*               | (in)  t_MsgContext->ResData    : 肯定応答データ(SIDを除く) */
/*               | (in)  t_MsgContext->ResDataLen : ResDataのデータ長         */
/*               | (in)  t_MsgContext->ReqType    : 未使用                    */
/*               | (in)  t_MsgContext->SuppressResponse : 応答抑制情報        */
/*               | (-)   t_MsgContext->ResMaxDataLen    : 未使用              */
/*               | (in)  t_ProcessingStatus    : 応答状態（通常/キャンセルNG）*/
/* Return Value  | None                                                       */
/* Notes         | Dcpとタスクレベルを合わせた後、ProcessingDoneを実行。      */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ProcessingDone
(
    P2CONST(Gdn_Dcm_MsgContextType, AUTOMATIC, DCM_APPL_CONST) t_MsgContext,
    VAR(Gdn_Dcm_ProcessingDoneStatusType, AUTOMATIC) t_ProcessingStatus
)
{
    Gdn_Std_ReturnType  t_EvtRetVal;
    gdn_uint32          t_EvtParameter;

    t_EvtParameter = (gdn_uint32)t_ProcessingStatus;
    t_EvtRetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SERVICE_DONE, 1UL, &t_EvtParameter );

    if ( t_EvtRetVal != GDN_E_OK ) {
        /* タスク起床失敗時は、フェールセーフ（P4タイマ or NRC78上限到達）により復帰する。 */
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_CopyTxData                                     */
/* Description   | 送信データコピー                                           */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  t_DcmTxPduId       : DcmのTxPduId                    */
/*               | (in)  t_PduInfoPtr       : PduDataコピー先のアドレス       */
/*               | (in)  t_RetryInfoPtr     : リトライ関連情報                */
/*               | (out) t_TxDataCntPtr     : 残りの送信TpPduデータ長         */
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
)
{
    Gdn_BufReq_ReturnType       t_RetVal;
    gdn_uint16                  t_CurrentBufferCnt;     /* 現在の送信データ位置 */
    gdn_uint16                  t_RemainingTxDataLen;   /* 残送信データ長       */
    Gdn_PduLengthType           t_BuffSizeCnt;          /* 検索カウンタ         */
    const gdn_uint8*            t_BuffPtr;

    t_RetVal = GDN_BUFREQ_E_NOT_OK;

    /* 1stClient送信中の場合 */
    if ((( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL          ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
        (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX   ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
        (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND  ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
        (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO   ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
        (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_WAIT_CONF            ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
        (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_NORMAL               ) &&
            (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_FALSE ))) {

        /* 1stClientのTxConfPduIdと一致 */
        if ( t_DcmTxPduId == GDN_DCM_DCP_GetMainTxConfPduId() ) {
            t_RemainingTxDataLen = Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen;

            /* 送信データ0であれば、コピー実施しない */
            if ( t_PduInfoPtr->SduLength  == (gdn_uint16)0U ) {
                *t_TxDataCntPtr = t_RemainingTxDataLen;
                t_RetVal = GDN_BUFREQ_OK;
            } else {
                /* コピー要求されたデータ長が、残送信データ長を超えていないかチェック */
                if ( t_RemainingTxDataLen >= t_PduInfoPtr->SduLength ){

                    /* 送信データ開始位置 */
                    t_BuffPtr = GDN_NULL_PTR;
                    if ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind == GDN_DCM_DCP_RESPONSE_KIND_POSITIVE ) {
                        t_CurrentBufferCnt = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResDataLen - t_RemainingTxDataLen;
                        t_BuffPtr = &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResData[t_CurrentBufferCnt];
                    } else {    /* GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE */
                        if ( t_RemainingTxDataLen == GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH ) {
                            t_BuffPtr = &Gdn_Dcm_Dcp_NegativeResBuff[0];
                        }
                    }

                    if ( t_BuffPtr != GDN_NULL_PTR ) {
                        /* 送信データコピー実施 */
                        for ( t_BuffSizeCnt=0U; t_BuffSizeCnt < t_PduInfoPtr->SduLength; t_BuffSizeCnt++ ) {
                            t_PduInfoPtr->SduDataPtr[t_BuffSizeCnt] = t_BuffPtr[t_BuffSizeCnt];
                        }
                        Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen = t_RemainingTxDataLen - t_PduInfoPtr->SduLength;
                        *t_TxDataCntPtr = Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen;
                        t_RetVal = GDN_BUFREQ_OK;
                    } else { /* 送信データコピー拒否: オーバーフロー */
                    }
                } else { /* 送信データコピー拒否: オーバーフロー */
                }
            }
        } else { /* 送信データコピー拒否：TxConfPduId不一致 */
        }
    } else { /* 送信データコピー拒否：状態不一致 */
    }

    /* リトライ情報がNULL_PTRであることをチェックする。リトライ機能非サポートのため。 */
    if ( t_RetryInfoPtr != GDN_NULL_PTR ) {
        t_RetVal = GDN_BUFREQ_E_NOT_OK;
    }
    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_TxConfirmation                                 */
/* Description   | 送信完了通知                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_DcmTxPduId     : DcmのTxPduId                      */
/*               | (in)  t_Result         : 下位層の送信結果                  */
/*               |  GDN_NTFRSLT_OK        : 送信正常完了                      */
/*               |  other                 : 送信失敗                          */
/* Return Value  | None                                                       */
/* Notes         | Sタスクでコールすること。(タスク抜け/タスク干渉防止)       */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_TxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) t_DcmTxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) t_Result
)
{

    /* 1stClientのTxConfPduIdと一致した場合 */
    if ( t_DcmTxPduId == GDN_DCM_DCP_GetMainTxConfPduId() ) {

#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
        if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_NORMAL        ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_FALSE )) {
            Gdn_Dcm_Dsd_Confirmation( t_Result );
            Gdn_Dcm_Dcp_EntryIdleState();
#else
        /* NRC78送信中（待機Msgなし）  */
        if ((( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL          ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
            (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX   ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
            (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND  ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) ||
            (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO   ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  ))) {
            Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg = GDN_FALSE;
            if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum < GDN_DCM_DCP_COUNTER_MAX_GUARD ) {
                Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum++;
            }

            Gdn_Dcm_Dcp_PendRespStatus = GDN_DCM_DCP_PENDRESP_SENT;

            DiagLib_PendingRspSentHook();

            Gdn_Dcm_Dsl_StartP2Timer();

        /* 最終応答Msg送信中            */
        } else if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_NORMAL        ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_FALSE )) {
            Gdn_Dcm_Dcp_PendRespStatus = GDN_DCM_DCP_PENDRESP_NOT_SENT;

            Gdn_Dcm_Dsd_Confirmation( t_Result );

            Gdn_Dcm_Dcp_EntryIdleState();

        /* NRC78送信中（待機Msgあり）  */
        } else if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_WAIT_CONF       ) &&
                (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE  )) {
            Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg = GDN_FALSE;

            Gdn_Dcm_Dcp_PendRespStatus = GDN_DCM_DCP_PENDRESP_SENT;

            if  (Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve == GDN_DCM_DCP_RESPONSE_RESERVE_DSP  ) {
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NONE;
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_NORMAL;
                Gdn_Dcm_Dcp_ProcessingDone( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext, GDN_DCM_NormalDone );   /* DSPの応答MSG送信 */
            } else { /* P4タイムアウト, NRC78上限回数到達, RAM化け時 */
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_NORMAL;
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NONE;
                Gdn_Dcm_Dsl_P4TimeoutMessageTransmit();
            }
#endif
        } else { /* 送信完了通知を無視: 状態不一致 */
        }
    } else { /* 送信完了通知を無視: TxConfPduId不一致 */
    }

    return;
}

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
)
{
    gdn_uint8  t_CurrentLevel;
    gdn_uint8  t_MatrixNum;
    gdn_uint8  t_Cnt;
    uint16     t_SchMValue;

    t_CurrentLevel = (gdn_uint8)Gdn_Dcm_Dcp_GetSecurityLevelBitPattern();

    if ( (gdn_uint8)(t_CurrentLevel & (gdn_uint8)~t_SecurityLevel) != GDN_DCM_DCP_CHECK_SECURITY_LOCK_BIT_PATTERN ) {
        /* As the result of this function is always OK, there is no need to check the return value. */
        (void)SchM_Switch_DcmSecurityControl( SCHM_BSWM_SECURITY_LOCK );
    }

    /* セキュリティ状態変更 */
    Gdn_Dcm_Dcp_SecurityLevelAttr.SecurityLevelBitPattern = t_SecurityLevel;

    /* セキュリティ状態通知 */
    t_MatrixNum = Gdn_Dcm_Dcp_SecLevelMatrixNum;
    for ( t_Cnt = 0U; t_Cnt < t_MatrixNum; t_Cnt++ ) {
        if ( (gdn_uint8)(t_SecurityLevel & Gdn_Dcm_Dcp_SecLevelMatrix[t_Cnt].GdnValue) == Gdn_Dcm_Dcp_SecLevelMatrix[t_Cnt].GdnValue ) {
            t_SchMValue = Gdn_Dcm_Dcp_SecLevelMatrix[t_Cnt].SchMValue;
            /* As the result of this function is always OK, there is no need to check the return value. */
            (void)SchM_Switch_DcmSecurityControl( t_SchMValue );
        }
    }

    return;
}

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
)
{
    /* GdnTimerServiceでDcpのタスクレベルに変更済み */

    switch ( TimerId ) {

        case ( GDN_DCM_DCP_S3_TIMER_ID ):
            Gdn_Dcm_Dsl_S3Timeout();
            break;
    #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
        case ( GDN_DCM_DCP_P4_TIMER_ID ):
            Gdn_Dcm_Dsl_P4Timeout();
            break;
    #endif
        case ( GDN_DCM_DCP_P2_TIMER_ID ):
            Gdn_Dcm_Dsl_P2MaxTimeout();
            break;
        default:
            /* 処理なし */
            break;
    }
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ServiceProcessingFuncTask                      */
/* Description   | サービス実行要求タスク                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Parameter[0]     : サービス実行要求種別            */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ServiceProcessingFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
)
{
    uint8 Diag_Op;

    Diag_Op = (uint8)t_Parameter[0];

    DiagSrv_Processing( Diag_Op, &(Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext) );

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask              */
/* Description   | サブマイコンゲートウェイ実行要求タスク                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) t_Parameter  : オペレーションステータス               */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
)
{
    Gdn_Dcm_OpStatusType                    t_OpStatus;

    t_OpStatus = (Gdn_Dcm_OpStatusType)t_Parameter[0];
    Gdn_Dcm_Dcp_SubMiconGateway_Processing( t_OpStatus );

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_ProcessingDoneFuncTask                         */
/* Description   | サービス応答要求タスク                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Parameter[0]     : サービス応答要求状態            */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_ProcessingDoneFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
)
{
    const Gdn_Dcm_MsgContextType*           t_pMsgContext;
    Gdn_Dcm_ProcessingDoneStatusType        t_ProcessingStatus;
    gdn_uint8                               t_ServiceId;

    t_pMsgContext = &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext;
    t_ProcessingStatus = (Gdn_Dcm_ProcessingDoneStatusType)t_Parameter[0];

    /* 1stClient実行中の場合 */
    if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL ) {
        /* 応答要求の場合 */
        if ( t_ProcessingStatus != GDN_DCM_CancelNotAllowed ) {
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
            Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_NORMAL;

            /* 肯定応答の場合 */
            if ( Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc == GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT ) {
                Gdn_Dcm_Dsl_PositiveResponseMessageTransmit( t_pMsgContext, GDN_DCM_DCP_RESPONSE_FACTOR_DSP );

            /* 否定応答の場合 */
            } else {
                t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
                Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( t_ServiceId,
                                                             t_pMsgContext->SuppressResponse,
                                                             GDN_DCM_DCP_RESPONSE_FACTOR_DSP,
                                                             Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc );
            }
#else
            /* NRC78送信中 */
            if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE ) {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_WAIT_CONF;
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_DSP;
                #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
                Gdn_Dcm_Dsl_StopP4Timer();
                #endif
            /* NRC78送信中でない */
            } else {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_NORMAL;
                Gdn_Dcm_Dsl_StopP2Timer();
                #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
                Gdn_Dcm_Dsl_StopP4Timer();
                #endif

                /* 肯定応答の場合 */
                if ( Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc == GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT ) {
                    Gdn_Dcm_Dsl_PositiveResponseMessageTransmit( t_pMsgContext, GDN_DCM_DCP_RESPONSE_FACTOR_DSP );

                /* 否定応答の場合 */
                } else {
                    t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
                    Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( t_ServiceId,
                                                                 t_pMsgContext->SuppressResponse,
                                                                 GDN_DCM_DCP_RESPONSE_FACTOR_DSP,
                                                                 Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc );
                }
            }
#endif
        } else { /* 状態化けorDSPエラー */
        }
    /* 1stClientキャンセル待ちの場合 */
    } else if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX  )  ||
               ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND )) {

        /* キャンセルOKの場合 */
        if ( t_ProcessingStatus != GDN_DCM_CancelNotAllowed ) {
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
            Gdn_Dcm_Dsl_StopP2Timer();
            #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
            Gdn_Dcm_Dsl_StopP4Timer();
            #endif
#endif
            Gdn_Dcm_Dsl_CopyRxDataSubToMain();
            if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX ){
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_RX_NORMAL;
            } else {
                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_NORMAL;
                /* 2ndClient実行開始 */
                #if ( GDN_DCM_DCP_DEFAULTSESSION_TRANS_ON_CLIENT_CHANGE == GDN_ON )
                Gdn_Dcm_Dsl_SessionTransition( GDN_DCM_DEFAULT_SESSION_INDEX, GDN_DCM_SESSION_FACTOR_PRIORITY_PREEMPT );
                #endif
                Gdn_Dcm_Dsl_PreServiceIndication( GDN_DCM_DCP_GetMainRxPduId() );
                Gdn_Dcm_Dsd_ServiceIndication();
            }

        } else { /* キャンセルNG */
            Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_NORMAL;
        }
    } else if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO ) {

        /* キャンセルOKの場合 */
        if ( t_ProcessingStatus != GDN_DCM_CancelNotAllowed ) {
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
            Gdn_Dcm_Dcp_EntryIdleState();
#else
            if (( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve == GDN_DCM_DCP_RESPONSE_RESERVE_NRC78MAXNUM )  ||
                ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve == GDN_DCM_DCP_RESPONSE_RESERVE_P4TIMEOUT   )) {
                Gdn_Dcm_Dsl_StopP2Timer();
                #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
                Gdn_Dcm_Dsl_StopP4Timer();
                #endif
                /* NRC78送信中 */
                if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE ) {
                    Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_WAIT_CONF;
                /* NRC78送信中でない */
                } else {
                    t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
                    Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_NORMAL;
                    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NONE;
                    Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( t_ServiceId,
                                                                 GDN_FALSE,
                                                                 GDN_DCM_DCP_RESPONSE_FACTOR_DSDFAILSAFE,
                                                                 GDN_DCM_DCP_GENERAL_REJECT_NRC );
                }
            } else {
                Gdn_Dcm_Dsl_StopP2Timer();
                #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
                Gdn_Dcm_Dsl_StopP4Timer();
                #endif
                Gdn_Dcm_Dcp_EntryIdleState();
            }
#endif
        } else { /* キャンセルNG */
            Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_NORMAL;
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
            if (( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve == GDN_DCM_DCP_RESPONSE_RESERVE_NRC78MAXNUM  )  ||
                ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve == GDN_DCM_DCP_RESPONSE_RESERVE_NRC78PENDING )) {
                /* NRC78上限回数到達時は、P2MaxTimeout()でNRC78未送信のため、NRC78送信する。 */
                Gdn_Dcm_Dsl_PendingResponseMessageTransmit();
            } else {
                /* P4タイムアウト時は、P2MaxTimeout()でNRC78送信済み。 */
            }
#endif
        }
    }else { /* 状態化けorDSPエラー */
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SessionTransitionFuncTask                      */
/* Description   | Session遷移通知タスク                                      */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Parameter[0] : 旧Session状態                       */
/*               | (in)  t_Parameter[1] : 新Session状態                       */
/*               | (in)  t_Parameter[2] : Session遷移要因                     */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_SessionTransitionFuncTask
(
    CONST(gdn_uint32, DCM_CONST) t_Parameter[]
)
{
    uint8 OldSession;
    uint8 NewSession;
    uint8 Factor;
    uint16 SchMMode;

    OldSession = (uint8)t_Parameter[0];
    NewSession = (uint8)t_Parameter[1];
    Factor = (uint8)t_Parameter[GDN_DCM_DCP_Index2];

    SchMMode = SCHM_BSWM_SESSION_DEF;
    if ( NewSession == GDN_DCM_REPROG_SESSION ) {
        SchMMode = SCHM_BSWM_SESSION_PRG;
    } else if ( NewSession == GDN_DCM_EXTENDED_SESSION ) {
        SchMMode = SCHM_BSWM_SESSION_EXT;
    } else {
        /* No process */
    }

    /* As the result of this function is always OK, there is no need to check the return value. */
    (void)SchM_Switch_DcmDiagnosticSessionControl( SchMMode );

    DiagSrv_NotifyChangeSession( OldSession, NewSession, Factor );

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_SetSesCtrlTypeBitPattern                       */
/* Description   | 新しいセッション状態のIndexのBitPatternを設定              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  SesCtrlTypeIdxBitPtrn :セッションIndexのBitPattern   */
/*               | (in)  TransitionFactor      :セッション遷移の要因          */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dsl_SetSesCtrlTypeBitPattern
(
    VAR(gdn_uint8, AUTOMATIC) SesCtrlTypeIdxBitPtrn,
    VAR(gdn_uint8, AUTOMATIC) TransitionFactor
)
{
    gdn_uint8   t_cnt;
    gdn_uint8   t_SesCtrlBitPtrn;

    t_SesCtrlBitPtrn = SesCtrlTypeIdxBitPtrn;

    for ( t_cnt = 0U; t_cnt < (gdn_uint8)GDN_DCM_DSL_UINT8_BIT_WIDTH; t_cnt++ ) {
        if ( t_SesCtrlBitPtrn == (gdn_uint8)GDN_BIT0 ) {
            Gdn_Dcm_Dsl_SessionTransition( t_cnt, TransitionFactor );
            break;
        }

        t_SesCtrlBitPtrn >>= 1U;
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_Time                                           */
/* Description   | Dcm の定周期[1ms]実行関数                                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_Time (void)
{
    DiagLib_Time();

    DiagSrv_Time();

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    if ( ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL ) && ( Gdn_Dcm_Dcp_TargetMicon == GDN_DCM_DCP_TARGET_MICON_SUB ) ) {
        Gdn_Dcm_Dcp_SubMiconGateway_Processing( GDN_DCM_PENDING );
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_NotifyChangeSession                            */
/* Description   | DCM_DCPのセッション遷移通知                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)   t_NewSession  : 遷移するセッション                  */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_NotifyChangeSession
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) t_NewSession
)
{
    gdn_uint8 t_NewSessionIndex;

    /* セッションをセッションインデックスに変換 */
    t_NewSessionIndex = GDN_DCM_DEFAULT_SESSION_INDEX;
    if ( t_NewSession == GDN_DCM_DEFAULT_SESSION ) {
        /* 処理無し */
    } else if ( t_NewSession == GDN_DCM_REPROG_SESSION ) {
        t_NewSessionIndex = GDN_DCM_REPROG_SESSION_INDEX;
#ifdef GDN_DCM_SESSIONCTRL_2
    } else if ( t_NewSession == GDN_DCM_EXTENDED_SESSION ) {
        t_NewSessionIndex = GDN_DCM_EXTENDED_SESSION_INDEX;
#endif
    } else {
        /* 処理無し */
    }

    Gdn_Dcm_Dsl_SessionTransition( t_NewSessionIndex, GDN_DCM_SESSION_FACTOR_OTHER );

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_NotifyChangeSecurity                           */
/* Description   | DCM_DCPのセキュリティ変更通知                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  t_NewSecurity  : 設定するセキュリティ                */
/* Return Value  | None                                                       */
/* Notes         |                                                            */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Dcp_NotifyChangeSecurity
(
    VAR(gdn_uint8, AUTOMATIC) t_NewSecurity
)
{
    gdn_uint8 t_CurrentSecLevel;
    gdn_uint8 t_NewSecLevel;

    t_NewSecLevel = t_NewSecurity;

    if ( t_NewSecurity != GDN_DCM_SECURITY_LOCK ) {
        t_CurrentSecLevel = Gdn_Dcm_Dcp_GetSecurityLevelBitPattern();
        t_NewSecLevel =(gdn_uint8)( t_NewSecurity | t_CurrentSecLevel );
    }

    Gdn_Dcm_Dcp_SetSecurityLevelBitPattern( t_NewSecLevel );

    return;
}
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
FUNC(gdn_uint8, DCM_CODE_SLOW) Gdn_Dcm_Dcp_GetComStatus (void)
{
    gdn_uint8 t_RetVal;

    t_RetVal = GDN_DCM_DCP_COM_IDLE;

    if ( (Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE) ||
         (Gdn_Dcm_Dcp_State == GDN_DCM_DCP_RX_NORMAL) ||
         (Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_NORMAL) )
    {
        t_RetVal = GDN_DCM_DCP_COM_BUSY;
    }

    return t_RetVal;
}

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
FUNC(gdn_uint8, DCM_CODE_SLOW) Gdn_Dcm_Dcp_GetPendRespStatus (void)
{
    return Gdn_Dcm_Dcp_PendRespStatus;
}

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
)
{
    Gdn_Dcm_Dcp_ServiceDiscard = Flag;

    return;
}

/*----------------------------------------------------------------------------*/
/* Internal Function                                                          */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_PriorityCheck                                  */
/* Description   | 優先度判定                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_NewRxPduIdIndex      : 新規受信したRxPduIdのIndex  */
/*               | (in)  t_pPduInfo->SduDataPtr : PduDataのポインタ           */
/*               | (in)  t_pPduInfo->SduLength  : PduData長                   */
/* Return Value  | gdn_uint8                                                  */
/*               |      GDN_DCM_DCP_PRIORITY_CHECK_BEFORE : 前優先            */
/*               |      GDN_DCM_DCP_PRIORITY_CHECK_AFTER  : 後優先            */
/* Notes         | -                                                          */
/******************************************************************************/
static gdn_uint8 Gdn_Dcm_Dsl_PriorityCheck( gdn_uint8 t_NewRxPduIdIndex, const Gdn_PduInfoType* t_pPduInfo )
{
    gdn_uint8                               t_RetVal;
    gdn_uint8                               t_NewConnectionId;
    gdn_uint8                               t_NewConnectionPrio;
    gdn_uint8                               t_OldConnectionPrio;
    #if ( GDN_DCM_DCP_PRIORITY_JUDGE_ENABLE_BY_SID == GDN_ON )
    gdn_uint8                               t_Sid;
    #endif

    t_RetVal = GDN_DCM_DCP_PRIORITY_CHECK_BEFORE;

    t_NewConnectionId = Gdn_Dcm_Dcp_RxPduIdConfig[t_NewRxPduIdIndex].ConnectionId;
    t_NewConnectionPrio = Gdn_Dcm_Dcp_ConnectionConfig[t_NewConnectionId].PriorityValue;

    /* 2ndClient保留中 */
    if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX  )  ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND )) {
        t_OldConnectionPrio = Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_GetSubRxConnectionId()].PriorityValue;
        #if ( GDN_DCM_DCP_PRIORITY_JUDGE_ENABLE_BY_SID == GDN_ON )
        t_Sid = Gdn_Dcm_Dcp_SubRxBuff[0];
        #endif
    /* 1stClient実行中 */
    } else {
        t_OldConnectionPrio = Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_GetMainConnectionId()].PriorityValue;
        #if ( GDN_DCM_DCP_PRIORITY_JUDGE_ENABLE_BY_SID == GDN_ON )
        t_Sid = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0];
        #endif
    }

    /*----------------------------------------------------------------*/
    /* 優先度判定                                                     */
    /* (優先度高) 0..255 (優先度低)                                   */
    /*----------------------------------------------------------------*/

    /* 高優先度 */
    if ( t_NewConnectionPrio < t_OldConnectionPrio ) {
        t_RetVal = GDN_DCM_DCP_PRIORITY_CHECK_AFTER;
    /* 同優先度 */
    } else if ( t_NewConnectionPrio == t_OldConnectionPrio ) {
        if ( t_pPduInfo->SduLength > (Gdn_PduLengthType)0U ) {
            #if ( GDN_DCM_DCP_PRIORITY_JUDGE_ENABLE_BY_SID == GDN_ON )
            /* 法規SID→非法規SID */
            if        (( t_pPduInfo->SduDataPtr[0] >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) &&
                       ( t_Sid <  GDN_DCM_DCP_UDS_SERVICE_ID_MIN )) {
            /* 非法規SID→法規SID */
            } else if (( t_pPduInfo->SduDataPtr[0] <  GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) &&
                       ( t_Sid >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN )) {
                t_RetVal = GDN_DCM_DCP_PRIORITY_CHECK_AFTER;
            /* 法規SID→法規SID  or  非法規SID→非法規SID */
            } else
            #else
            #endif
            {
            /* 同優先度時のコンフィグ"後優先" */
            #if ( GDN_DCM_DCP_SAME_CONNECTION_PRIORITY_ACTION == GDN_DCM_DCP_PRIORITY_AFTER )
                t_RetVal = GDN_DCM_DCP_PRIORITY_CHECK_AFTER;
            #else
            #endif
            }
        } else { /* MsgにSIDが含まれていないので"前優先" */
        }
    /* 低優先度 */
    } else { /* "前優先" */
    }
    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_PreemptProcessing                              */
/* Description   | 後優先時の切替処理                                         */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_NewRxPduIdIndex     : 新RxPduIdのIndex             */
/*               | (out) t_BufLength           : 受信バッファサイズ           */
/* Return Value  | None                                                       */
/* Notes         | 受信バッファサイズは、サブバッファ使用時のみ更新する。     */
/******************************************************************************/
static void Gdn_Dcm_Dsl_PreemptProcessing( gdn_uint8 t_NewRxPduIdIndex, Gdn_PduLengthType* t_BufLength )
{
    Gdn_Std_ReturnType  t_RetVal;
    Gdn_PduIdType       t_RxPduId;
    Gdn_PduIdType       t_TxPduId_Ref;

    t_RetVal = GDN_E_OK;

    /* 受信中の場合 */
    switch ( Gdn_Dcm_Dcp_State ) {
    case GDN_DCM_DCP_RX_NORMAL:
        t_RxPduId = Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].RxPduId;
        t_RetVal = Gdn_PduR_DcmCancelReceive( t_RxPduId );                              /* 受信キャンセル     */
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_RX_NORMAL;                                      /* 状態遷移           */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;  /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen = 0x0000U;          /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex = t_NewRxPduIdIndex;         /* 受信情報設定       */
                                                                                        /* メインバッファ使用 */
        break;
    /* 実行中の場合 */
    case GDN_DCM_DCP_PROCESS_NORMAL:
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX;                          /* 状態遷移           */
        t_RetVal = Gdn_Dcm_Dsd_ServiceCancel();                                         /* サービスキャンセル */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqData = &Gdn_Dcm_Dcp_SubRxBuff[0];       /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen = 0x0000U;                      /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex = t_NewRxPduIdIndex;                     /* 受信情報設定       */
        *t_BufLength = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE;                      /* サブバッファ使用   */
        break;
    /* 実行中(1stキャンセル中 && 2nd受信中)の場合 */
    case GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX:
        t_RxPduId = Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetSubRxPduId()].RxPduId;
        t_RetVal = Gdn_PduR_DcmCancelReceive( t_RxPduId );                              /* 受信キャンセル     */
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX;                          /* 状態遷移           */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqData = &Gdn_Dcm_Dcp_SubRxBuff[0];       /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen = 0x0000U;                      /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex = t_NewRxPduIdIndex;                     /* 受信情報設定       */
        *t_BufLength = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE;                      /* サブバッファ使用   */
        break;
    /* 実行中(1stキャンセル中 && 2nd受信完了)の場合 */
    case GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND:
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX;                          /* 状態遷移           */
                                                                                        /* キャンセル処理なし */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqData = &Gdn_Dcm_Dcp_SubRxBuff[0];       /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen = 0x0000U;                      /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex = t_NewRxPduIdIndex;                     /* 受信情報設定       */
        *t_BufLength = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE;                      /* サブバッファ使用   */
        break;
    /* 実行中(1stキャンセル中 && 2nd受信なし)の場合 */
    case GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO:
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX;                          /* 状態遷移           */
                                                                                        /* キャンセル処理なし */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqData = &Gdn_Dcm_Dcp_SubRxBuff[0];       /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen = 0x0000U;                      /* 受信情報設定       */
        Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex = t_NewRxPduIdIndex;                     /* 受信情報設定       */
        *t_BufLength = (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE;                      /* サブバッファ使用   */
        break;
    /* 送信中の場合 */
    case GDN_DCM_DCP_TX_NORMAL:
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_RX_NORMAL;                                      /* 状態遷移           */
        t_TxPduId_Ref = GDN_DCM_DCP_GetMainTxPduId_Ref();
        t_RetVal = Gdn_PduR_DcmCancelTransmit( t_TxPduId_Ref );                         /* 送信キャンセル     */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;  /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen = 0x0000U;          /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex = t_NewRxPduIdIndex;         /* 受信情報設定       */
                                                                                        /* メインバッファ使用 */
        break;
    /* NRC0x78送信完了待ちの場合 */
    case GDN_DCM_DCP_TX_WAIT_CONF:
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_RX_NORMAL;                                      /* 状態遷移           */
        t_TxPduId_Ref = GDN_DCM_DCP_GetMainTxPduId_Ref();
        t_RetVal = Gdn_PduR_DcmCancelTransmit( t_TxPduId_Ref );                         /* 送信キャンセル     */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;  /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen = 0x0000U;          /* 受信情報設定       */
        Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex = t_NewRxPduIdIndex;         /* 受信情報設定       */
                                                                                        /* メインバッファ使用 */
        break;
    default: /* 上記以外の状態の場合は無視する。 */
        break;
    }
    if ( t_RetVal != GDN_E_OK ) {
        /* 下位層キャンセルの場合: 下位層状態が受信/送信処理完了済みのため処置不要          */
        /* 上位層キャンセルの場合: NRC0x78上限回数/P4で状態ロック監視を継続しており処置不要 */
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_CopyRxDataSubToMain                            */
/* Description   | サブオブジェクトの受信データをメインオブジェクトにコピー   */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsl_CopyRxDataSubToMain( void )
{
    gdn_uint16  t_Cnt;

    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->RxPduIdIndex = Gdn_Dcm_Dcp_SubRxCtrlAttr.RxPduIdIndex;
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen = Gdn_Dcm_Dcp_SubRxCtrlAttr.MsgContext.ReqDataLen;
    for ( t_Cnt=0U; t_Cnt < (gdn_uint16)GDN_DCM_DCP_SUB_RX_BUFFER_SIZE; t_Cnt++ ) {
        Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[t_Cnt] = Gdn_Dcm_Dcp_SubRxBuff[t_Cnt];
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_KeepAliveMsgCheck                              */
/* Description   | キープアライブメッセージ判定                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | gdn_bool                                                   */
/*               |      GDN_TRUE  : キープアライブメッセージ                  */
/*               |      GDN_FALSE : キープアライブメッセージ以外              */
/* Notes         | Gdn_Dcm_Dsl_PreServiceIndication()コール後に使用する。     */
/******************************************************************************/
static gdn_bool Gdn_Dcm_Dsl_KeepAliveMsgCheck( void )
{
    gdn_bool    retVal;

    retVal = GDN_FALSE;

    if (( Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData[0] == GDN_DCM_DCP_KEEPALIVEMSG_BYTE1  ) &&
        ( Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData[1] == GDN_DCM_DCP_KEEPALIVEMSG_BYTE2  ) &&
        ( Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen == GDN_DCM_DCP_KEEPALIVEMSG_LENGTH ) &&
        ( Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqType    == GDN_DCM_AddressKindFunctional   )) {
        retVal = GDN_TRUE;
    }
    return retVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_PreServiceIndication                           */
/* Description   | DSDにサービス実行処理する前処理                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) t_DcmRxPduIdIndex : DcmRxPduIdのインデックス          */
/* Return Value  | None                                                       */
/* Notes         | MsgContextをDsdに渡す形に変更                              */
/******************************************************************************/
static void Gdn_Dcm_Dsl_PreServiceIndication( gdn_uint8 t_DcmRxPduIdIndex )
{
    gdn_uint16      t_RequestMsgLength;

    t_RequestMsgLength = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen;

    /* Msgコンテキストの受信情報設定 */
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;

    /* Msgコンテキストの送信情報設定 */
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResData = &Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[t_RequestMsgLength];
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResDataLen = 0x0000U;

    /* Msgコンテキストのアドレスタイプ設定 */
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqType = Gdn_Dcm_Dcp_RxPduIdConfig[t_DcmRxPduIdIndex].AddressType;

    /* Msgコンテキストの応答有無情報設定 */
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.SuppressResponse = GDN_FALSE;

    /* Msgコンテキストの最大応答データ長設定                         */
    /* 最大応答データ長 = バッファサイズ - 受信データ長 */
    Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResMaxDataLen = (gdn_uint16)GDN_DCM_DCP_MAIN_RXTX_BUFFER_SIZE - t_RequestMsgLength;

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StartP2Timer                                   */
/* Description   | P2タイマ開始要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | P2タイマの制約：MAX65535ms                                 */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_StartP2Timer( void )
{
    Gdn_TimeoutValueType    t_P2TimeoutValue;

    if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum == (gdn_uint8)0x00U ) {
        t_P2TimeoutValue = Gdn_Dcm_SessionCtrlConfig[GDN_DCM_DSL_GetSesCtrlTypeIndex()].P2MaxTime - (Gdn_TimeoutValueType)GDN_DCM_DCP_P2_ADJUST_TIMERCNT;
    } else {
        t_P2TimeoutValue = ( (Gdn_Dcm_SessionCtrlConfig[GDN_DCM_DSL_GetSesCtrlTypeIndex()].P2MaxAsterExTime * (Gdn_TimeoutValueType)GDN_DCM_P2MAXASTER_LSB)
            - (Gdn_TimeoutValueType)GDN_DCM_DCP_P2_ADJUST_TIMERCNT );
    }
    Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P2_TIMER_ID, t_P2TimeoutValue, (gdn_uint16)0U );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StartP4Timer                                   */
/* Description   | P4タイマ開始要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_StartP4Timer( void )
{
#if ( GDN_DCM_DCP_P4_TIMECNT > GDN_DCM_DCP_TimeoutValueType_MaxValue )
        Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P4_TIMER_ID, (Gdn_TimeoutValueType)GDN_DCM_DCP_TimeoutValueType_MaxValue, (gdn_uint16)0U );
        Gdn_Dcm_Dcp_RemainedP4Timeout = (gdn_uint32)GDN_DCM_DCP_P4_TIMECNT - (gdn_uint32)GDN_DCM_DCP_TimeoutValueType_MaxValue;
#else
        Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P4_TIMER_ID, (Gdn_TimeoutValueType)GDN_DCM_DCP_P4_TIMECNT, (gdn_uint16)0U );
        Gdn_Dcm_Dcp_RemainedP4Timeout = (gdn_uint32)0U;
#endif
}
#endif
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StartS3Timer                                   */
/* Description   | S3タイマ開始要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | 現在セッションでS3サポート時のみタイマ開始する。           */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_StartS3Timer( void )
{
    Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_S3_TIMER_ID, (Gdn_TimeoutValueType)GDN_DCM_DCP_S3_TIMECNT, (gdn_uint16)0U );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StopP2Timer                                    */
/* Description   | P2タイマ停止要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_StopP2Timer( void )
{
    Gdn_TmrSrv_ReleaseTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P2_TIMER_ID );

    DiagLib_PendingRspStopHook();

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StopP4Timer                                    */
/* Description   | P4タイマ停止要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_StopP4Timer( void )
{
    Gdn_Dcm_Dcp_RemainedP4Timeout = (gdn_uint32)0U;
    Gdn_TmrSrv_ReleaseTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P4_TIMER_ID );
}
#endif
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_StopS3Timer                                    */
/* Description   | S3タイマ停止要求                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_StopS3Timer( void )
{
    Gdn_TmrSrv_ReleaseTimer( (Gdn_TimerIdType)GDN_DCM_DCP_S3_TIMER_ID );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_P2MaxTimeout                                   */
/* Description   | P2MAXタイムアウト                                          */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_P2MaxTimeout( void )
{
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_NRC78CNT)
    gdn_uint8 t_ServiceId;
#endif

    /*----------------------------------------------------------------*/
    /* P2タイマ                                                       */
    /* 1stToolキャンセル中もP2タイマカウントしている。                */
    /* 2ndToolに対するP2タイマは開始していない。                      */
    /*----------------------------------------------------------------*/

    if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL         )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX  )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO  ))  {

        /* NRC78送信上限回数を超えている場合、否定応答を送信する。 */
        #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_NRC78CNT)
        if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum >= (gdn_uint8)GDN_DCM_DCP_RESP_MAX_NUM_RESP_PENDING ) {

            Gdn_Dcm_Dsl_StartP2Timer();

            if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL ) {
                t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
                if ( t_ServiceId >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) {
                    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NRC78MAXNUM;
                }
                /* 法規SIDでフェールセーフによる最終応答を許可する場合 */
                #if ( GDN_DCM_DCP_PROCESS_FAILSAFE_OBDRESPONSE_ENABLE == GDN_ON )
                else {
                    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NRC78MAXNUM;
                }
                /* 法規SIDでフェールセーフによる最終応答を許可しない場合 */
                #else
                else {
                    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NRC78PENDING;
                }
                #endif

                Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO;
                (void)Gdn_Dcm_Dsd_ServiceCancel();  /* No need to check return value */

            } else { /* 既にキャンセル中のため、キャンセル通知しない。 */
            }

        /* NRC78送信上限回数を超えていない場合、NRC78を送信する。 */
        } else
        #endif
        {
            Gdn_Dcm_Dsl_PendingResponseMessageTransmit();
        }
    } else {    /* No process */
    }
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_P4Timeout                                      */
/* Description   | P4タイムアウト                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | 65535ms(LSB:1ms)までしか計測しないタイマを考慮し分割計測。 */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_P4Timeout( void )
{
    if ( Gdn_Dcm_Dcp_RemainedP4Timeout == (gdn_uint32)0U ) {
        Gdn_Dcm_Dsl_P4TimeoutConfirmed();
    } else if ( Gdn_Dcm_Dcp_RemainedP4Timeout < (gdn_uint32)GDN_DCM_DCP_TimeoutValueType_MaxValue ) {
        Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P4_TIMER_ID, (Gdn_TimeoutValueType)Gdn_Dcm_Dcp_RemainedP4Timeout, (gdn_uint16)0U );
        Gdn_Dcm_Dcp_RemainedP4Timeout = (gdn_uint32)0U;
    } else {
        Gdn_TmrSrv_SetTimer( (Gdn_TimerIdType)GDN_DCM_DCP_P4_TIMER_ID, (Gdn_TimeoutValueType)GDN_DCM_DCP_TimeoutValueType_MaxValue, (gdn_uint16)0U );
        Gdn_Dcm_Dcp_RemainedP4Timeout -= (gdn_uint32)GDN_DCM_DCP_TimeoutValueType_MaxValue;
    }
}
#endif
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_P4TimeoutConfirmed                             */
/* Description   | P4タイムアウト                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | P4タイムアウト発生。                                       */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
#if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
static void Gdn_Dcm_Dsl_P4TimeoutConfirmed( void )
{
    gdn_uint8 t_ServiceId;

    if (( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL         )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_RX  )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_IND )   ||
        ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO  ))  {

        Gdn_Dcm_Dsl_StartP4Timer();

        if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_PROCESS_NORMAL ) {
            t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
            if ( t_ServiceId >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) {
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_P4TIMEOUT;
            }
            /* 法規SIDでフェールセーフによる最終応答を許可する場合 */
            #if ( GDN_DCM_DCP_PROCESS_FAILSAFE_OBDRESPONSE_ENABLE == GDN_ON )
            else {
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_P4TIMEOUT;
            }
            /* 法規SIDでフェールセーフによる最終応答を許可しない場合 */
            #else
            else {
                Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NONE;
            }
            #endif

            Gdn_Dcm_Dcp_State = GDN_DCM_DCP_PROCESS_CANCEL_2ND_NO;
            (void)Gdn_Dcm_Dsd_ServiceCancel();  /* No need to check return value */

        } else { /* 既にキャンセル中のため、キャンセル通知しない。 */
        }
    } else {    /* No process */
    }
}
#endif
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_S3Timeout                                      */
/* Description   | S3タイムアウト                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_S3Timeout( void )
{
    Gdn_Dcm_Dcp_State = GDN_DCM_DCP_IDLE_INACTIVE;
    Gdn_Dcm_Dsl_SessionTransition( GDN_DCM_DEFAULT_SESSION_INDEX, GDN_DCM_SESSION_FACTOR_S3TIMEOUT );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_SessionTransition                              */
/* Description   | Session遷移処理                                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_NewSessionIndex   : 新SessionのIndex               */
/*               | (in)  t_TransitionFactor  : Session遷移の要因              */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsl_SessionTransition( gdn_uint8 t_NewSessionIndex, gdn_uint8 t_TransitionFactor )
{
    gdn_uint32              t_EvtParameter[GDN_DCM_DCP_Index3];
    Gdn_Std_ReturnType      t_EvtRetVal;

    /* Session状態変更 */
    Gdn_Dcm_Dcp_SessionCtrlAttr.OldSessionCtrlIndex = Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex;
    Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex = t_NewSessionIndex;

    /* BS/STmin設定変更 */
    #if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
    if ( GDN_DCM_DSL_GetSesCtrlTypeIndex() != GDN_DCM_DSL_GetOldSesCtrlTypeIndex() ) {
        Gdn_Dcm_Dsl_BsSTminChange( GDN_DCM_DSL_GetSesCtrlTypeIndex() );
    }
    #endif

    /* Session遷移通知タスク起床 */
    t_EvtParameter[0] = (gdn_uint32)(Gdn_Dcm_SessionCtrlConfig[Gdn_Dcm_Dcp_SessionCtrlAttr.OldSessionCtrlIndex].SessionCtrl);
    t_EvtParameter[1] = (gdn_uint32)(Gdn_Dcm_SessionCtrlConfig[Gdn_Dcm_Dcp_SessionCtrlAttr.SessionCtrlIndex].SessionCtrl);
    t_EvtParameter[GDN_DCM_DCP_Index2] = (gdn_uint32)t_TransitionFactor;
    t_EvtRetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SESSION_TRANSITION, GDN_DCM_DCP_SESSIONTRANSITION_PARAM_NUM, &t_EvtParameter[0] );

    if ( t_EvtRetVal != GDN_E_OK ) {
        /* タスク起床失敗 */
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_BsSTminChange                                  */
/* Description   | BS/STmin変更                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_SesCtlIndex      : Session状態インデックス         */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
static void Gdn_Dcm_Dsl_BsSTminChange( gdn_uint8 t_SesCtlIndex)
{
    Gdn_Std_ReturnType      t_retVal;
    gdn_uint8               t_Cnt;
    gdn_uint16              t_BsValue;
    gdn_uint16              t_StminValue;

    Gdn_Dcm_Dcp_BsSTminCtrlAttr.BsStminSettingErr = GDN_E_OK;

    /* BS */
    for ( t_Cnt=0U; t_Cnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_Cnt++ ) {
        t_BsValue = (gdn_uint16)Gdn_Dcm_SessionCtrlConfig[t_SesCtlIndex].BsValue;
        t_retVal = Gdn_PduR_DcmChangeParameter( (Gdn_PduIdType)t_Cnt,
                                                (Gdn_TPParameterType)GDN_TP_BS,
                                                t_BsValue );
        if ( t_retVal != GDN_E_OK ) {
            Gdn_Dcm_Dcp_BsSTminCtrlAttr.BsStminSettingErr = t_retVal;
        } else {    /* No process */
        }
    }
    /* STmin */
    for ( t_Cnt=0U; t_Cnt < (gdn_uint8)GDN_DCM_DCP_ALL_RXPDUID_NUM; t_Cnt++ ) {
        t_StminValue = (gdn_uint16)Gdn_Dcm_SessionCtrlConfig[t_SesCtlIndex].StminValue;
        t_retVal = Gdn_PduR_DcmChangeParameter( (Gdn_PduIdType)t_Cnt,
                                                (Gdn_TPParameterType)GDN_TP_STMIN,
                                                t_StminValue);
        if ( t_retVal != GDN_E_OK ) {
            Gdn_Dcm_Dcp_BsSTminCtrlAttr.BsStminSettingErr = t_retVal;
        } else {    /* No process */
        }
    }
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_PendingResponseMessageTransmit                 */
/* Description   | NRC78メッセージ送信                                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_PendingResponseMessageTransmit( void )
{
    Gdn_PduInfoType     t_ResponseFormat;
    gdn_uint8           t_ServiceId;

    t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();

    Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg = GDN_TRUE;
    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind = GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE;
    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseFactor = GDN_DCM_DCP_RESPONSE_FACTOR_NRC78;

    t_ResponseFormat.SduDataPtr = &Gdn_Dcm_Dcp_NegativeResBuff[0];
    t_ResponseFormat.SduLength = (gdn_uint16)GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH;

    t_ResponseFormat.SduDataPtr[0] = GDN_DCM_DCP_NEGATIVE_RESPONSE_SERVICE_ID;
    t_ResponseFormat.SduDataPtr[1] = t_ServiceId;
    t_ResponseFormat.SduDataPtr[GDN_DCM_DCP_Index2] = GDN_DCM_DCP_PENDING_RESPONSE_NRC;

    Rte_RpgEvtHk_SendPendingResponse( t_ServiceId,
                                    t_ResponseFormat.SduDataPtr,
                                    t_ResponseFormat.SduLength );

    Gdn_Dcm_Dsl_ResponseTransmit( &t_ResponseFormat, GDN_FALSE );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_PositiveResponseMessageTransmit                */
/* Description   | 肯定応答メッセージ送信                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_pMsgContext->SuppressResponse  : 応答有無          */
/*               | (in)  t_Factor                         : 応答要因          */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsl_PositiveResponseMessageTransmit( const Gdn_Dcm_MsgContextType* t_pMsgContext, gdn_uint8 t_Factor )
{
    Gdn_PduInfoType     t_ResponseFormat;
    gdn_uint8           t_ServiceId;

    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind = GDN_DCM_DCP_RESPONSE_KIND_POSITIVE;
    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseFactor = t_Factor;

    t_ResponseFormat.SduDataPtr = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResData;
    t_ResponseFormat.SduLength = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResDataLen;

    t_ServiceId = t_ResponseFormat.SduDataPtr[0] - GDN_DCM_DCP_POSITIVE_RESPONSE_SERVICE_ID;

    Rte_RpgEvtHk_SendPositiveResponse( t_ServiceId,
                                    t_ResponseFormat.SduDataPtr,
                                    t_ResponseFormat.SduLength );

    Gdn_Dcm_Dsl_ResponseTransmit( &t_ResponseFormat, t_pMsgContext->SuppressResponse );

    if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
    {
        if( t_ServiceId == (gdn_uint8)DIAG_SID_TD )
        {
            /* Switch buffer when SID 0x36(TranferData) positive response */
            Gdn_Dcm_Dcp_SwitchBufferFlag = GDN_ON;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_NegativeResponseMessageTransmit                */
/* Description   | 否定応答メッセージ送信                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_ServiceId                      : サービスID        */
/*               | (in)  t_SuppressInfo                   : 応答有無          */
/*               | (in)  t_Factor                         : 応答要因          */
/*               | (in)  t_Nrc                            : NRC               */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( gdn_uint8 t_ServiceId,
                                                         Gdn_Dcm_MsgAddInfoSuppressResponseType t_SuppressInfo,
                                                         gdn_uint8 t_Factor,
                                                         Gdn_Dcm_NegativeResponseCodeType t_Nrc )
{
    Gdn_PduInfoType     t_ResponseFormat;

    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind = GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE;
    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseFactor = t_Factor;

    t_ResponseFormat.SduDataPtr = &Gdn_Dcm_Dcp_NegativeResBuff[0];
    t_ResponseFormat.SduLength = (Gdn_PduLengthType)GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH;

    t_ResponseFormat.SduDataPtr[0] = GDN_DCM_DCP_NEGATIVE_RESPONSE_SERVICE_ID;
    t_ResponseFormat.SduDataPtr[1] = t_ServiceId;
    t_ResponseFormat.SduDataPtr[GDN_DCM_DCP_Index2] = t_Nrc;

    Rte_RpgEvtHk_SendNegativeResponse( t_ServiceId,
                                    t_ResponseFormat.SduDataPtr,
                                    t_ResponseFormat.SduLength );

    Gdn_Dcm_Dsl_ResponseTransmit( &t_ResponseFormat, t_SuppressInfo );
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_ResponseTransmit                               */
/* Description   | 応答Msg送信要求受付                                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_ResponseInfo      : 応答情報                       */
/*               | (in)  t_SuppressInfo      : 応答抑制情報                   */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsl_ResponseTransmit( const Gdn_PduInfoType* t_ResponseInfo, Gdn_Dcm_MsgAddInfoSuppressResponseType t_SuppressInfo )
{
#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
    Gdn_Std_ReturnType                      t_ReqResult;
    Gdn_PduIdType                           t_TxPduId_Ref;
    Gdn_PduIdType                           t_TxConfPduId;

    /* サブマイコン使用(サブマイコン側) 時は、応答抑制を行わない */
    Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen = t_ResponseInfo->SduLength;
    t_TxPduId_Ref = GDN_DCM_DCP_GetMainTxPduId_Ref();
    t_ReqResult = Gdn_PduR_DcmTransmit( t_TxPduId_Ref, t_ResponseInfo );
    if ( t_ReqResult != GDN_E_OK ) {
        /* サブマイコン使用(サブマイコン)側 では、全ての送信要求が最終応答 */
        t_TxConfPduId = GDN_DCM_DCP_GetMainTxConfPduId();
        Gdn_Dcm_Dcp_TxConfirmation( t_TxConfPduId, GDN_NTFRSLT_E_NOT_OK );
    }
#else
    Gdn_Std_ReturnType                      t_ReqResult;
    Gdn_Dcm_MsgAddInfoSuppressResponseType  t_SuppressRes;
    Gdn_PduIdType                           t_TxPduId_Ref;
    Gdn_PduIdType                           t_TxConfPduId;

    t_SuppressRes = t_SuppressInfo;

    /* NRC78送信履歴有の時は、応答抑制しない */
    if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum != (gdn_uint8)0x00U ) {
        t_SuppressRes = GDN_FALSE;
    }

    /* 機能アドレス, 非法規SIDの時は、応答抑制する */
    #if ( GDN_DCM_DCP_SUPPRESS_RES_FUNC_EX == GDN_ON )
    if (( Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0] >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) &&
        ( Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType == GDN_DCM_AddressKindFunctional )) {
        t_SuppressRes = GDN_TRUE;
    }
    #endif

#if ( REPROG_CFG_CXPI_USE == STD_ON )
    if ( Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType == GDN_DCM_AddressKindFunctional ) {
        t_SuppressRes = GDN_TRUE;
    }
#endif

    /* 応答抑制しない */
    if ( t_SuppressRes != GDN_TRUE ) {
        Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen = t_ResponseInfo->SduLength;
        t_TxPduId_Ref = GDN_DCM_DCP_GetMainTxPduId_Ref();
        t_ReqResult = Gdn_PduR_DcmTransmit( t_TxPduId_Ref, t_ResponseInfo );
        if ( t_ReqResult != GDN_E_OK ) {
            /* NRC78送信中 */
            if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg == GDN_TRUE ) {
                Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg = GDN_FALSE;
                if ( Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum < GDN_DCM_DCP_COUNTER_MAX_GUARD ) {
                    Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum++;
                }
                Gdn_Dcm_Dsl_StartP2Timer();
            /* 最終応答Msg */
            } else {
                t_TxConfPduId = GDN_DCM_DCP_GetMainTxConfPduId();
                Gdn_Dcm_Dcp_TxConfirmation( t_TxConfPduId, GDN_NTFRSLT_E_NOT_OK );
                /* Gdn_Dcm_Dcp_EntryIdleState(); */ /* TxConfirmation内にて実施 */
            }
        } else { /* 送信要求OK */
        }
    /* 応答抑制する */
    } else {
        t_TxConfPduId = GDN_DCM_DCP_GetMainTxConfPduId();
        if ( Gdn_Dcm_Dcp_State == GDN_DCM_DCP_TX_NORMAL ) {
            Gdn_Dcm_Dcp_TxConfirmation( t_TxConfPduId, GDN_NTFRSLT_OK );
            /* Gdn_Dcm_Dcp_EntryIdleState(); */ /* TxConfirmation内にて実施 */
        } else { /* NRC78送信中のみ */
            Gdn_Dcm_Dcp_TxConfirmation( t_TxConfPduId, GDN_NTFRSLT_OK );
        }
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsl_P4TimeoutMessageTransmit                       */
/* Description   | P4タイムアウト否定応答メッセージ送信                       */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
static void Gdn_Dcm_Dsl_P4TimeoutMessageTransmit( void )
{
    Gdn_PduInfoType                         t_ResponseFormat;
    Gdn_Std_ReturnType                      t_ReqResult;
    Gdn_PduIdType                           t_TxPduId_Ref;

    /* 機能アドレス, 非法規SIDの時は、応答抑制する */
    #if ( GDN_DCM_DCP_SUPPRESS_RES_FUNC_EX == GDN_ON )
    if (( Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0] >= GDN_DCM_DCP_UDS_SERVICE_ID_MIN ) &&
        ( Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_GetMainRxPduId()].AddressType == GDN_DCM_AddressKindFunctional )) {
        /* 応答抑制する */
        /* Gdn_Dcm_Dsd_Confirmation( GDN_NTFRSLT_OK ); */ /* Cancel完了のためConirm通知不要 */
        Gdn_Dcm_Dcp_EntryIdleState();
    } else
    #endif
        /* 応答抑制しない */
    {
        t_ResponseFormat.SduDataPtr = &Gdn_Dcm_Dcp_NegativeResBuff[0];
        t_ResponseFormat.SduLength = (Gdn_PduLengthType)GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH;

        t_ResponseFormat.SduDataPtr[0] = GDN_DCM_DCP_NEGATIVE_RESPONSE_SERVICE_ID;
        t_ResponseFormat.SduDataPtr[1] = Gdn_Dcm_Dcp_GetMainServiceId();
        t_ResponseFormat.SduDataPtr[GDN_DCM_DCP_Index2] = GDN_DCM_DCP_GENERAL_REJECT_NRC;

        Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind = GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE;
        Gdn_Dcm_Dcp_TxCtrlAttr.ResponseFactor = GDN_DCM_DCP_RESPONSE_FACTOR_DSDFAILSAFE;
        Gdn_Dcm_Dcp_TxCtrlAttr.RemainingTxDataLen = t_ResponseFormat.SduLength;
        t_TxPduId_Ref = GDN_DCM_DCP_GetMainTxPduId_Ref();
        t_ReqResult = Gdn_PduR_DcmTransmit( t_TxPduId_Ref, &t_ResponseFormat );
        if ( t_ReqResult != GDN_E_OK ) {
            /* Gdn_Dcm_Dsd_Confirmation( GDN_NTFRSLT_E_NOT_OK ); */ /* Cancel完了のためConirm通知不要 */
            Gdn_Dcm_Dcp_EntryIdleState();
        } else { /* 送信要求OK */
        }
    }

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsd_ServiceCancel                                  */
/* Description   | サービスキャンセルのディスパッチ処理                       */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | Gdn_Std_ReturnType                                         */
/*               |      GDN_E_OK                   : キャンセル通知OK         */
/*               |      GDN_E_NOT_OK               : キャンセル通知NG         */
/* Notes         | -                                                          */
/******************************************************************************/
static Gdn_Std_ReturnType Gdn_Dcm_Dsd_ServiceCancel( void )
{
    gdn_uint32              t_EvtParameter;
    Gdn_Std_ReturnType      t_RetVal;

    t_EvtParameter = (gdn_uint32)DIAG_CANCEL;

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    t_RetVal = GDN_E_NOT_OK;

    if ( Gdn_Dcm_Dcp_TargetMicon == GDN_DCM_DCP_TARGET_MICON_MAIN ) {
        t_RetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SERVICE_PROCESSING, 1UL, &t_EvtParameter );
    } else if ( Gdn_Dcm_Dcp_TargetMicon == GDN_DCM_DCP_TARGET_MICON_SUB ) {
        t_RetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SUB_SERVICE_GW, 1UL, &t_EvtParameter );
    } else { /* No Process */
    }
#else
    /* 上位層へサービスキャンセル通知 */
    t_RetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SERVICE_PROCESSING, 1UL, &t_EvtParameter );
#endif

    return t_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsd_ServiceIndication                              */
/* Description   | サービス実行のディスパッチ処理                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsd_ServiceIndication( void )
{
    Gdn_Std_ReturnType                              t_RetVal;
    gdn_uint8                                       t_ServiceId;
    gdn_uint32                                      t_EvtParameter;
    Gdn_Dcm_NegativeResponseCodeType                t_AppNegativeResponseCode;
    Gdn_Dcm_MsgAddInfoReqTypeType                   t_MsgAddInfoReqType;
    gdn_bool                                        t_RetKeepAliveMsgCheck;
    Gdn_Dcm_NegativeResponseInfoType                t_AppNegativeResponseInfo;
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    uint8                                           t_MiconId;
#endif

    Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxNum = 0x00u;
    Gdn_Dcm_Dcp_TxCtrlAttr.PendingResponseTxFlg = GDN_FALSE;
    Gdn_Dcm_Dcp_TxCtrlAttr.ResponseReserve = GDN_DCM_DCP_RESPONSE_RESERVE_NONE;
    Gdn_Dcm_Dcp_PendRespStatus = GDN_DCM_DCP_PENDRESP_NOT_SENT;

#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    t_RetVal = Gdn_Dcm_Dsd_CheckStayInBootMsg();
    if( t_RetVal == GDN_E_OK )
    {
#endif
    /* SIDサポートチェック */
    t_AppNegativeResponseCode = Gdn_Dcm_Dsd_SidCheck();

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    /* サブマイコンGWチェック */
    if ( t_AppNegativeResponseCode == GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT ) {
        t_MiconId = DIAGSRV_SUBM_ID_MAIN;
        t_AppNegativeResponseCode = (Gdn_Dcm_NegativeResponseCodeType)DiagSrv_SubM_JudgeGw( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext, &t_MiconId );
    }
#endif

    if ( t_AppNegativeResponseCode == GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT ) {
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
        if ( t_MiconId != DIAGSRV_SUBM_ID_MAIN ) {

            Gdn_Dcm_Dsl_StartP2Timer();
            #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
            Gdn_Dcm_Dsl_StartP4Timer();
            #endif

            Gdn_Dcm_Dcp_TargetMicon = GDN_DCM_DCP_TARGET_MICON_SUB;
            Gdn_Dcm_Dcp_SubMiconGateway_ServiceId = DIAG_GET_SID( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext );

            /* サブマイコンへのGW */
            t_EvtParameter = (gdn_uint32)GDN_DCM_INITIAL;
            t_RetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SUB_SERVICE_GW, 1UL, &t_EvtParameter );

            if ( t_RetVal != GDN_E_OK ) {
                /* タスク起床失敗時は、フェールセーフ（P4タイマ or NRC78上限到達）により復帰する。 */
            }
        }
        else
#endif
        {
            /* KeepAliveチェック */
            t_RetKeepAliveMsgCheck = Gdn_Dcm_Dsl_KeepAliveMsgCheck();
            if ( t_RetKeepAliveMsgCheck == GDN_FALSE ) {

                Gdn_Dcm_Dcp_ServiceCtrlAttr.Nrc = GDN_DCM_DCP_NEGATIVE_RESPONSE_CODE_DEFAULT;

#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
                Gdn_Dcm_Dsl_StartP2Timer();
                #if (GDN_DCM_DCP_PROCESS_FAILSAFE_TYPE == GDN_DCM_DCP_PROCESS_FAILSAFE_P4)
                Gdn_Dcm_Dsl_StartP4Timer();
                #endif

  #if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
                Gdn_Dcm_Dcp_TargetMicon = GDN_DCM_DCP_TARGET_MICON_MAIN;
  #endif
#endif

                /* 上位層へサービス実行通知 */
                t_EvtParameter = (gdn_uint32)DIAG_INITIAL;
                t_RetVal = Gdn_Rte_SendEvent( GDN_DCM_DCP_EVENTID_SERVICE_PROCESSING, 1UL, &t_EvtParameter );

                if ( t_RetVal != GDN_E_OK ) {
                    /* タスク起床失敗時は、フェールセーフ（P4タイマ or NRC78上限到達）により復帰する。 */
                }
            } else {
                Gdn_Dcm_Dcp_EntryIdleState(); /* KeepAliveMsgは上位層に通知しない。 */
            }
        }
    } else {
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_TX_NORMAL;

        t_ServiceId = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0];
        t_MsgAddInfoReqType = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqType;

        Gdn_Dcm_Dcp_GetNegativeResponseInfo( t_AppNegativeResponseCode, &t_AppNegativeResponseInfo );
        Gdn_Dcm_Dsl_NegativeResponseMessageTransmit( t_ServiceId,
                                                     t_AppNegativeResponseInfo.ResponseSuppressInfo[t_MsgAddInfoReqType],
                                                     GDN_DCM_DCP_RESPONSE_FACTOR_MSGERR,
                                                     t_AppNegativeResponseCode );
    }
#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
    } else {
        Gdn_Dcm_Dcp_EntryIdleState();
    }
#endif
    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsd_SidCheck                                       */
/* Description   | SIDチェック                                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | Nrc                                                        */
/* Notes         | -                                                          */
/******************************************************************************/
static Gdn_Dcm_NegativeResponseCodeType Gdn_Dcm_Dsd_SidCheck( void )
{
    uint8 ApNrc;

    ApNrc = Rte_RpgMfr_CommonCheckCondition();
    if ( ApNrc == DIAG_NRC_PR )
    {
        ApNrc = DiagLib_CheckSidSupport( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext );
        if ( ApNrc == DIAG_NRC_PR )
        {
            ApNrc = Rte_RpgSpp_SidCheckCondition( Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0] );
        }
    }

    return (Gdn_Dcm_NegativeResponseCodeType)ApNrc;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsd_Confirmation                                   */
/* Description   | サービス応答完了のディスパッチ処理                         */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Result_low      : 下位層の送信結果                 */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dsd_Confirmation( Gdn_NotifResultType t_Result_low )
{
    uint8 t_Result_up;
#if ( GDN_DCM_DCP_RXTX_AREA_NUM > 1U )
    gdn_uint8   t_RxTxAreaNum;
#endif

    if ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseFactor == GDN_DCM_DCP_RESPONSE_FACTOR_DSP ) {
        /* DiagSrvに渡す結果通知の型に変換 */
        if        (( t_Result_low == GDN_NTFRSLT_OK ) && ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind == GDN_DCM_DCP_RESPONSE_KIND_POSITIVE )) {
            t_Result_up = DIAG_POSRSP_OK;
        } else if (( t_Result_low == GDN_NTFRSLT_OK ) && ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind == GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE )) {
            t_Result_up = DIAG_NEGRSP_OK;
        } else if (( t_Result_low != GDN_NTFRSLT_OK ) && ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind == GDN_DCM_DCP_RESPONSE_KIND_POSITIVE )) {
            t_Result_up = DIAG_POSRSP_NG;
        } else if (( t_Result_low != GDN_NTFRSLT_OK ) && ( Gdn_Dcm_Dcp_TxCtrlAttr.ResponseKind == GDN_DCM_DCP_RESPONSE_KIND_NEGATIVE )) {
            t_Result_up = DIAG_NEGRSP_NG;
        } else { /* 該当条件なし */
            t_Result_up = DIAG_NEGRSP_NG;
        }

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
        if ( Gdn_Dcm_Dcp_TargetMicon == GDN_DCM_DCP_TARGET_MICON_MAIN )
#endif
        {
            DiagSrv_Confirmation( t_Result_up );

            if( Gdn_Dcm_Dcp_SwitchBufferFlag == (gdn_uint8)GDN_ON )
            {
                /* Switch buffer when SID 0x36(TransferData) positive response */
#if ( GDN_DCM_DCP_RXTX_AREA_NUM > 1U )
                t_RxTxAreaNum = Gdn_Dcm_Dcp_RxTxAreaNum;
                if( Gdn_Dcm_Dcp_CurrentRxTxAreaIndex < ( t_RxTxAreaNum - (gdn_uint8)1U ) )
                {
                    Gdn_Dcm_Dcp_CurrentRxTxAreaIndex++;
                }
                else
#endif
                {
                    Gdn_Dcm_Dcp_CurrentRxTxAreaIndex = 0U;
                }

                Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr = &Gdn_Dcm_Dcp_MainRxCtrlAttr[Gdn_Dcm_Dcp_CurrentRxTxAreaIndex];
                Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr = &Gdn_Dcm_Dcp_MainRxTxBuff[Gdn_Dcm_Dcp_CurrentRxTxAreaIndex][0];
                Gdn_Dcm_Dcp_SwitchBufferFlag = GDN_OFF;
            }
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_EntryIdleState                                 */
/* Description   | アイドル状態遷移処理                                       */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dcp_EntryIdleState( void )
{
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    Gdn_Dcm_Dcp_TargetMicon = GDN_DCM_DCP_TARGET_MICON_NONE;
#endif

#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
    Gdn_Dcm_Dcp_State = GDN_DCM_DCP_IDLE_INACTIVE;
#else
    if ( Gdn_Dcm_SessionCtrlConfig[GDN_DCM_DSL_GetSesCtrlTypeIndex()].S3TimerEnable == GDN_TRUE ) {
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_IDLE_ACTIVE;
        Gdn_Dcm_Dsl_StartS3Timer();
    } else {
        Gdn_Dcm_Dcp_State = GDN_DCM_DCP_IDLE_INACTIVE;
    }
#endif
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetMainServiceId                               */
/* Description   | 実行中サービスIDの取得                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | gdn_uint8                                                  */
/*               |      実行中サービスID                                      */
/* Notes         | -                                                          */
/******************************************************************************/
static gdn_uint8 Gdn_Dcm_Dcp_GetMainServiceId( void )
{
    gdn_uint8 Sid;

#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
    if ( Gdn_Dcm_Dcp_TargetMicon == GDN_DCM_DCP_TARGET_MICON_SUB )
    {
        Sid = Gdn_Dcm_Dcp_SubMiconGateway_ServiceId;
    }
    else
#endif
    {
        Sid = (gdn_uint8)DiagSrv_GetMainServiceId();
    }

    return Sid;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_GetNegativeResponseInfo                        */
/* Description   | 否定応答情報の取得                                         */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Nrc                   : NRC                        */
/*               | (out) t_pNegativeResponseInfo : 否定応答情報               */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
static void Gdn_Dcm_Dcp_GetNegativeResponseInfo( Gdn_Dcm_NegativeResponseCodeType t_Nrc, Gdn_Dcm_NegativeResponseInfoType* t_pNegativeResponseInfo )
{
    t_pNegativeResponseInfo->Nrc = t_Nrc;
    t_pNegativeResponseInfo->ResponseSuppressInfo[GDN_DCM_AddressKindPhysical] = GDN_FALSE;

    DiagLib_SetFuncAddressSuppressByNrc(t_pNegativeResponseInfo);

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_Processing                     */
/* Description   | Processing SubMicon-Gateway                                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_OpStatus     : Operation status                    */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing( Gdn_Dcm_OpStatusType t_OpStatus )
{
    if ( ( t_OpStatus == GDN_DCM_INITIAL ) || ( t_OpStatus == GDN_DCM_PENDING ) ) {
        Gdn_Dcm_Dcp_SubMiconGateway_Processing_Execute( t_OpStatus );
    } else {
        Gdn_Dcm_Dcp_SubMiconGateway_Processing_Cancel();
    }

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_Processing_Execute             */
/* Description   | Execution of SubMicon-Gateway                              */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_OpStatus     : Operation status                    */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing_Execute( Gdn_Dcm_OpStatusType t_OpStatus )
{
    SubMiconIf_ReqInfoType              t_ReqInfo;
    SubMiconIf_RespInfoType             t_RespInfo;
    SubMiconIf_OpStatusType             t_SubMiconIf_OpStatus;
    Std_ReturnType                      t_SubMiconIf_Result;
    gdn_uint8                           t_CheckResp_Result;
    Gdn_Std_ReturnType                  t_Result;
    Gdn_Dcm_NegativeResponseCodeType    t_Nrc;
    uint8                               t_MiconId;

    t_SubMiconIf_OpStatus = SUBMICONIF_INITIAL;
    if ( t_OpStatus != GDN_DCM_INITIAL ) {
        t_SubMiconIf_OpStatus = SUBMICONIF_PENDING;
    }

    t_Result = GDN_E_NOT_OK;
    t_Nrc = GDN_DCM_DCP_GeneralRejectNrc;

    t_ReqInfo.ReqData = Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr;
    t_ReqInfo.ReqDataSize = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ReqDataLen;
    t_RespInfo.RespData = &Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[t_ReqInfo.ReqDataSize];
    t_RespInfo.RespDataSize = Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResMaxDataLen;

    t_MiconId = DiagSrv_SubM_GetSequenceMiconId();

    t_SubMiconIf_Result = SubMiconIf_Main_RequestService( t_MiconId, &t_ReqInfo, &t_RespInfo, t_SubMiconIf_OpStatus );
    if ( t_SubMiconIf_Result == SUBMICONIF_E_PENDING ) {
        t_Result = GDN_E_PENDING;
    } else if ( t_SubMiconIf_Result == (Std_ReturnType)E_OK ) {
        t_CheckResp_Result = Gdn_Dcm_Dcp_SubMiconGateway_CheckResponse( t_RespInfo.RespData, t_RespInfo.RespDataSize );
        if ( t_CheckResp_Result == GDN_DCM_DCP_SUBMICONGATEWAY_RESP_POSITIVE ) {
            Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResDataLen = t_RespInfo.RespDataSize;
            t_Result = GDN_E_OK;
        } else if ( t_CheckResp_Result == GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NEGATIVE ) {
            t_Nrc = t_RespInfo.RespData[GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NRC_POS];
        } else {
            /* No Process */
        }
    } else {
        /* No Process */
    }

    if ( t_Result == GDN_E_PENDING ) {
        /* No Process */
    } else if ( t_Result == GDN_E_OK ) {
        Gdn_Dcm_Dcp_SubMiconGateway_TransmitPositiveResponse();
    } else {
        DiagSrv_SubM_SetGwStatus( DIAGSRV_SUBM_GW_STAT_IDLE );
        Gdn_Dcm_Dcp_SubMiconGateway_TransmitNegativeResponse( t_Nrc );
    }

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_Processing_Cancel              */
/* Description   | Cancel SubMicon-Gateway                                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_Processing_Cancel( void )
{
    Gdn_Dcm_Dcp_ProcessingDone( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext, GDN_DCM_NormalDone );

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_CheckResponse                  */
/* Description   | Checking SubMicon-Gateway ResponseData                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_RespData     : Response Data (Including SID)       */
/*               | (in)  t_RespDataSize : Size of RespData                    */
/* Return Value  | GDN_DCM_DCP_SUBMICONGATEWAY_RESP_POSITIVE : 肯定応答       */
/*               | GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NEGATIVE : 否定応答       */
/*               | GDN_DCM_DCP_SUBMICONGATEWAY_RESP_INVALID  : 異常応答       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static gdn_uint8 Gdn_Dcm_Dcp_SubMiconGateway_CheckResponse( const gdn_uint8* t_RespData, gdn_uint16 t_RespDataSize )
{
    gdn_uint8 t_ServiceId;
    gdn_uint8 t_Result;

    t_Result = GDN_DCM_DCP_SUBMICONGATEWAY_RESP_INVALID;

    if ( ( t_RespDataSize >= GDN_DCM_DCP_SUBMICONGATEWAY_RESP_MIN_LEN ) &&
         ( t_RespDataSize <= Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext.ResMaxDataLen ) ) {
        t_ServiceId = Gdn_Dcm_Dcp_GetMainServiceId();
        if ( t_RespData[GDN_DCM_DCP_SUBMICONGATEWAY_RESP_SID_POS] == ( t_ServiceId | GDN_DCM_DCP_POSITIVE_RESPONSE_SERVICE_ID ) ) {
            /* Transmit Positive Response */
            t_Result = GDN_DCM_DCP_SUBMICONGATEWAY_RESP_POSITIVE;
        } else if ( t_RespData[GDN_DCM_DCP_SUBMICONGATEWAY_RESP_SID_POS] == GDN_DCM_DCP_NEGATIVE_RESPONSE_SERVICE_ID ) {
            if ( t_RespDataSize == GDN_DCM_DCP_NEGATIVE_RESPONSE_LENGTH ) {
                if ( t_RespData[GDN_DCM_DCP_SUBMICONGATEWAY_RESP_REQSID_POS] == t_ServiceId ) {
                    /* Transmit Negative Response */
                    t_Result = GDN_DCM_DCP_SUBMICONGATEWAY_RESP_NEGATIVE;
                }
            }
        } else {
            /* No Process */
        }
    }

    return t_Result;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_TransmitPositiveResponse       */
/* Description   | Positive response transmission for SubMicon-Gateway        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_TransmitPositiveResponse( void )
{
    DiagLib_SetSuppressResponseBySid( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext );
    Gdn_Dcm_Dcp_ProcessingDone( &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext, GDN_DCM_NormalDone );

    return;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_Dcm_Dcp_SubMiconGateway_TransmitNegativeResponse       */
/* Description   | Negative response transmission for SubMicon-Gateway        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in)  t_Nrc    : NRC                                       */
/* Return Value  | None                                                       */
/* Notes         | -                                                          */
/******************************************************************************/
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
static void Gdn_Dcm_Dcp_SubMiconGateway_TransmitNegativeResponse( Gdn_Dcm_NegativeResponseCodeType t_Nrc )
{
    Gdn_Dcm_NegativeResponseInfoType t_NegativeResponseInfo;

    t_NegativeResponseInfo.Nrc = GDN_DCM_DCP_GeneralRejectNrc;
    t_NegativeResponseInfo.ResponseSuppressInfo[GDN_DCM_AddressKindFunctional] = GDN_FALSE;
    t_NegativeResponseInfo.ResponseSuppressInfo[GDN_DCM_AddressKindPhysical] = GDN_FALSE;

    Gdn_Dcm_Dcp_GetNegativeResponseInfo( t_Nrc, &t_NegativeResponseInfo );
    Gdn_Dcm_TransmitNegativeResponse( &t_NegativeResponseInfo, &Gdn_Dcm_Dcp_CurrentMainRxCtrlAttrPtr->MsgContext );

    return;
}
#endif

#if ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
/******************************************************************************/
/* Function Name | Gdn_Dcm_Dsd_CheckStayInBootMsg                             */
/* Description   | Check if message should be discarded or not.               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  GDN_E_OK                   : message is valid             */
/*               |  GDN_E_REQUEST_NOT_ACCEPTED : message is discarded         */
/* Notes         | This function can be used when                             */
/*               | REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                    */
/******************************************************************************/
static Gdn_Std_ReturnType Gdn_Dcm_Dsd_CheckStayInBootMsg( void )
{
    Gdn_Std_ReturnType  t_Result;
    gdn_uint8           t_StayInBootState;

    t_Result = GDN_E_REQUEST_NOT_ACCEPTED;

    t_StayInBootState = SchM_GetStayInBootState();
    if ( t_StayInBootState == SCHM_STATE_STAYINBOOT_WAIT ) {
        if ( ( Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[0] == DIAG_SID_DSC ) &&
             ( ( Gdn_Dcm_Dcp_CurrentMainRxTxBuffPtr[1] & GDN_DCM_DCP_STAYINBOOT_SUBFUNC_MASK ) == DIAG_SESSION_PRG ) ) {
            t_Result = GDN_E_OK;
        }
    } else if ( t_StayInBootState == SCHM_STATE_STAYINBOOT_TMO ) {
        /* No Process */
    } else {
        t_Result = GDN_E_OK;
    }

    return t_Result;
}
#endif /* ( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON ) */

#define GDN_DCM_STOP_SEC_CODE
#include <Gdn_Dcm_MemMap.h>

/*-- End Of File -------------------------------------------------------*/
