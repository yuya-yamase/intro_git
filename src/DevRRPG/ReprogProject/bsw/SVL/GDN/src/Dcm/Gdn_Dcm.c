/* Gdn_Dcm_c_00_0007 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | DCM共通処理                                                  */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/02/dd   DN長谷川 新規作成                                  */
/*  00_0000   2014/03/dd   DN矢加部 追加                                      */
/*  00_0001   2014/09/25   DT       DTCKindのセッションサポート判定を追加     */
/*  00_0002   2014/11/12   DN矢加部 Dcmのスリープ禁止状態取得関数追加         */
/*  00_0003   2018/06/19   AUBASS   リプログ対応                              */
/*  00_0004   2019/02/12   AUBASS   Update                                    */
/*  00_0005   2019/07/16   AUBASS   Update                                    */
/*  00_0006   2019/12/03   AUBASS   Update                                    */
/*  00_0007   2022/03/01   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Rte.h>

#include <Gdn_Types.h>
#include <Gdn_Ucfg.h>
#include "Dcm/Gdn_Dcm.h"
#include "Dcm/Dcp/Gdn_Dcm_Dcp.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_ShutDown      ((gdn_uint8)0x00U)
#define GDN_DCM_Active        ((gdn_uint8)0xA5U)

#define GDN_DCM_Index2 (2)
#define GDN_DCM_Index3 (3)

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

static gdn_uint8 Gdn_Dcm_InitStatus;                    /* Dcm有効化状態      */

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_DCM_START_SEC_CODE
#include <Gdn_Dcm_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_Dcm_TransmitNegativeResponse                           */
/* Description   | 否定応答送信                                               */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TransmitNegativeResponse
(
    P2CONST(Gdn_Dcm_NegativeResponseInfoType, AUTOMATIC, DCM_APPL_CONST) NegativeResponseInfo,
    P2VAR(Gdn_Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) MsgContext
)
{
    MsgContext->SuppressResponse = NegativeResponseInfo->ResponseSuppressInfo[ MsgContext->ReqType ];

    Gdn_Dcm_Dcp_SetNegativeResponse( NegativeResponseInfo->Nrc );

    Gdn_Dcm_Dcp_ProcessingDone( MsgContext, GDN_DCM_NormalDone );

}

/******************************************************************************/
/* Function Name | Gdn_Dcm_StartOfReception                                   */
/* Description   | 受信開始通知                                               */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_StartOfReception
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) info,
    VAR(Gdn_PduLengthType, AUTOMATIC) TpSduLength,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
)
{
    Gdn_BufReq_ReturnType   Gdn_Dcm_RetVal;

    Gdn_Dcm_RetVal = GDN_BUFREQ_E_NOT_OK;

    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_RetVal = Gdn_Dcm_Dcp_StartOfReception( DcmRxPduId, info, TpSduLength, RxBufferSizePtr );
    }
    return Gdn_Dcm_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_CopyRxData                                         */
/* Description   | 受信データコピー                                           */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_CopyRxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
)
{
    Gdn_BufReq_ReturnType   Gdn_Dcm_RetVal;

    Gdn_Dcm_RetVal = GDN_BUFREQ_E_NOT_OK;

    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_RetVal = Gdn_Dcm_Dcp_CopyRxData( DcmRxPduId, PduInfoPtr, RxBufferSizePtr );
    }
    return Gdn_Dcm_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_TpRxIndication                                     */
/* Description   | 受信完了通知                                               */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TpRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmRxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
)
{
    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_Dcp_RxIndication( DcmRxPduId, Result );
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_CopyTxData                                         */
/* Description   | 送信データコピー                                           */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, DCM_CODE_SLOW) Gdn_Dcm_CopyTxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmTxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, DCM_APPL_CONST) PduInfoPtr,
    P2CONST(Gdn_RetryInfoType, AUTOMATIC, DCM_APPL_CONST) RetryInfoPtr,
    P2VAR(gdn_uint16, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr
)
{
    Gdn_BufReq_ReturnType   Gdn_Dcm_RetVal;

    Gdn_Dcm_RetVal = GDN_BUFREQ_E_NOT_OK;

    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_RetVal = Gdn_Dcm_Dcp_CopyTxData( DcmTxPduId, PduInfoPtr, RetryInfoPtr, TxDataCntPtr );
    }
    return Gdn_Dcm_RetVal;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_TpTxConfirmation                                   */
/* Description   | 送信完了通知                                               */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TpTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) DcmTxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result
)
{
    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_Dcp_TxConfirmation( DcmTxPduId, Result );
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_MainFunction                                       */
/* Description   | DCMメイン関数（定期周期コール）                            */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_MainFunction (void)
{
    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_Dcp_MainFunction();
    }
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Init                                               */
/* Description   | DCM初期化                                                  */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Init (void)
{
    Gdn_Dcm_Dcp_Init();
    Gdn_Dcm_InitStatus = GDN_DCM_Active;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Shutdown                                           */
/* Description   | Dcmの通信終了処理                                          */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Shutdown (void)
{
    Gdn_Dcm_InitStatus = GDN_DCM_ShutDown;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_TimeoutIndication                                  */
/* Description   | Dcm(Dcp)タイムアウト通知                                   */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_TimeoutIndication
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
)
{
#if ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) )
    if ( Gdn_Dcm_InitStatus != GDN_DCM_ShutDown ) {
        Gdn_Dcm_Dcp_TimeoutIndication( TimerId, Synchronizer );
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_Time                                               */
/* Description   | 1msタイム処理関数コール処理を行う。                        */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_Time (void)
{
    if ( Gdn_Dcm_InitStatus == GDN_DCM_Active ) {
        /* Dcm の定周期[1ms]実行関数 */
        Gdn_Dcm_Dcp_Time();
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyBaudrateSettingResult                        */
/* Description   | ボーレート変更の成否を通知する                             */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyBaudrateSettingResult
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    P2CONST(Gdn_Std_ReturnType, AUTOMATIC, DCM_APPL_CONST) Dcm_Result
)
{
    uint8 ChangeResult;

    ChangeResult = RTE_RPGLIB_CHANGEBAUDRATE_NG;

    if( *Dcm_Result == GDN_E_OK ) {
        ChangeResult = RTE_RPGLIB_CHANGEBAUDRATE_OK;
    }

    Rte_RpgLib_NotifyChangeBaudrate( ChangeResult );

    return;
}

#if ( REPROG_CFG_SUBMICON_USE_SUB == STD_ON )
/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyChangeSession                                */
/* Description   | セッション遷移を通知する                                   */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyChangeSession
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) NewSession
)
{
    if ( Gdn_Dcm_InitStatus == GDN_DCM_Active ) {
        Gdn_Dcm_Dcp_NotifyChangeSession( NewSession );
    }

    return;
}

/******************************************************************************/
/* Function Name | Gdn_Dcm_NotifyChangeSecurity                               */
/* Description   | セキュリティ変更を通知する                                 */
/******************************************************************************/
FUNC(void, DCM_CODE_SLOW) Gdn_Dcm_NotifyChangeSecurity
(
    VAR(gdn_uint8, AUTOMATIC) NewSecurity
)
{
    if ( Gdn_Dcm_InitStatus == GDN_DCM_Active ) {
        Gdn_Dcm_Dcp_NotifyChangeSecurity( NewSecurity );
    }

    return;
}
#endif

#define GDN_DCM_STOP_SEC_CODE
#include <Gdn_Dcm_MemMap.h>

/*-- End Of File -------------------------------------------------------*/
