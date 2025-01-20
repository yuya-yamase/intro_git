/* Gdn_PduR_Core_c_00_0003 */
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

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>
#include <Gdn_Ucfg.h>
#include "Gdn_PduR.h"
#include "Gdn_PduR_Ucfg.h"
#include "Gdn_PduR_Core.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_Num0           ((gdn_uint8)0)
#define GDN_PDUR_Num7           ((gdn_uint8)7)
#define GDN_PDUR_Num6           ((gdn_uint8)6)
#define GDN_PDUR_Num5           ((gdn_uint8)5)
#define GDN_PDUR_Num4           ((gdn_uint8)4)
#define GDN_PDUR_Num3           ((gdn_uint8)3)
#define GDN_PDUR_Num2           ((gdn_uint8)2)

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Nw == GDN_ON ) )
static void Gdn_PduR_LoRxLoop( const Gdn_PduInfoType* PduInfo, GdnConst Gdn_PduR_LoNwRxDstInfoType RxDstTable[], gdn_uint16 TableSize );
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
static void Gdn_PduR_DataCopy( const gdn_uint8 SrcBuf[], Gdn_PduLengthType SrcOffset, gdn_uint8 DstBuf[], Gdn_PduLengthType DstOffset, Gdn_PduLengthType Size );
static void Gdn_PduR_InitBuffer( gdn_uint8 Buffer[], Gdn_PduLengthType Size );
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
static void Gdn_PduR_ReceiveToUpTp( GdnConst Gdn_PduR_LoTpRxRoutingTblType* RoutingInfo, const Gdn_PduInfoType* RxPduInfo );
static Gdn_Std_ReturnType Gdn_PduR_GatewayToLoTp( gdn_uint8 GatewayCnt, GdnConst Gdn_PduR_LoTpGatewayInfoType GatewayInfo[], const Gdn_PduInfoType* PduInfo );
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
static GdnConst Gdn_PduR_LoTpGatewayInfoType* Gdn_PduR_GetRxInfoOfTx( Gdn_PduIdType RxPduId, GdnConst Gdn_PduR_LoTpRxRoutingTblType RxRoutingInfo[],
                                                                      GdnConst Gdn_PduR_LoTpRxRoutingTblType** RxRoutingInfoOut,
                                                                      Gdn_PduLengthType RxBufferInfo[], Gdn_PduLengthType** RxBufferInfoOut );
static Gdn_BufReq_ReturnType Gdn_PduR_LoTpCopyGwData( const Gdn_PduInfoType* PduInfo, const Gdn_RetryInfoType* Retry, Gdn_PduLengthType* AvailableData,
                                                      const gdn_uint8* RxBuffer, GdnConst Gdn_PduR_LoTpGatewayInfoType RxGatewayInfo[],
                                                      gdn_uint8 GatewayIndex, Gdn_PduLengthType RxBufPtr );
static void Gdn_PduR_LoTpGwConfirm( gdn_uint8 DestCnt, GdnConst Gdn_PduR_LoTpGatewayInfoType RxGatewayInfo[], gdn_uint8 GatewayIndex, Gdn_PduLengthType* RxBufPtr );
#endif

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_VAR
#include <Gdn_PduR_MemMap.h>

#define GDN_PDUR_STOP_SEC_VAR
#include <Gdn_PduR_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_CST
#include <Gdn_PduR_MemMap.h>

#define GDN_PDUR_STOP_SEC_CST
#include <Gdn_PduR_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_PDUR_START_SEC_CODE
#include <Gdn_PduR_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_PduR_Init                                              */
/* Description   | PduRの初期化処理                                           */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_Init (void)
{
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
             gdn_uint8                      Cnt;
             gdn_uint8                      Cnt2;
             gdn_uint8                      Cnt3;
             gdn_uint8                      RxPduCnt;
    GdnConst Gdn_PduR_LoTpRxRoutingTblType* RxTable;

    for ( Cnt = (gdn_uint8)0; Cnt < (gdn_uint8)GDN_PDUR_MaxLoLayerCnt_Tp; Cnt++ ) {

        RxPduCnt = gdn_pdur_LoTpRxRoutingTableList[Cnt].PduIdCnt;
        RxTable  = gdn_pdur_LoTpRxRoutingTableList[Cnt].RxRoutingTbl;

        if ( ( RxPduCnt != (gdn_uint8)0 ) &&
             ( RxTable != GDN_NULL_PTR ) ) {
            for ( Cnt2 = (gdn_uint8)0; Cnt2 < RxPduCnt; Cnt2++ ) {

                /* 受信バッファ位置情報の初期化 */
                gdn_pdur_LoTpRxRoutingTableList[Cnt].BufPosition[Cnt2] = (Gdn_PduLengthType)0;

                /* 受信バッファの初期化 */
                if ( RxTable[Cnt2].BufferSize != (Gdn_PduLengthType)0 ) {
                    Gdn_PduR_InitBuffer( RxTable[Cnt2].GatewayBuffer, RxTable[Cnt2].BufferSize );
                }

                /* 送信バッファ位置情報の初期化 */
                for ( Cnt3 = (gdn_uint8)0; Cnt3 < RxTable[Cnt2].GatewayCnt; Cnt3++ ) {
                    *RxTable[Cnt2].GatewayInfo[Cnt3].TxDataPtr = (Gdn_PduLengthType)0;
                }
            }
        }
    }
#endif
}

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoRxIndication                                    */
/* Description   | Network層受信通知の本体                                    */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_LoNwRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
)
{
    if ( RxPduId < (Gdn_PduIdType)TableSize ) {
        Gdn_PduR_LoRxLoop( PduInfo,
                           RxRoutingTable[RxPduId].DestinationInfo,
                           RxRoutingTable[RxPduId].DestinationCnt );
    }
}
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_TxConfirmationApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTxConfirmation                                  */
/* Description   | Network層送信完了通知の本体                                */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_LoNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
)
{
    gdn_uint16 Cnt;

    for ( Cnt = (gdn_uint16)0; Cnt < TableSize; Cnt++ ) {
        if ( TxRoutingTable[Cnt].PduId == TxPduId ) {
            if ( TxRoutingTable[Cnt].TxConfirmIf != GDN_NULL_PTR ) {
                TxRoutingTable[Cnt].TxConfirmIf( TxRoutingTable[Cnt].SduId );
            }
            break;
        }
    }
}
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_TriggerTransmitApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTriggerTransmit                                 */
/* Description   | Network層送信要求トリガーの本体                            */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTriggerTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2VAR(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfo,
    CONST(volatile Gdn_PduR_LoNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;
    gdn_uint16         Cnt;

    t_Result = GDN_E_NOT_OK;

    for ( Cnt = (gdn_uint16)0; Cnt < TableSize; Cnt++ ) {
        if ( TxRoutingTable[Cnt].PduId == TxPduId ) {
            if ( TxRoutingTable[Cnt].TxTriggerIf != GDN_NULL_PTR ) {
                t_Result = TxRoutingTable[Cnt].TxTriggerIf( TxRoutingTable[Cnt].SduId, PduInfo );
            }
            break;
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UpLayerTransmit_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTransmit                                        */
/* Description   | Network層送信要求の本体                                    */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_UpNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;

    t_Result = GDN_E_NOT_OK;
    if ( TxPduId < (Gdn_PduIdType)TableSize ) {
        t_Result = TxRoutingTable[TxPduId].TxTransmit( TxRoutingTable[TxPduId].PduId, PduInfo );
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_CancelTransmitApi_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpCancelTransmit                                  */
/* Description   | Network層送信中止要求の本体                                */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpCancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_UpNwTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint16, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;

    t_Result = GDN_E_NOT_OK;
    if ( TxPduId < (Gdn_PduIdType)TableSize ) {
        t_Result = TxRoutingTable[TxPduId].TxCancel( TxRoutingTable[TxPduId].PduId );
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpStartOfReception                              */
/* Description   | Transport層受信開始通知の本体                              */
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
)
{
    Gdn_BufReq_ReturnType t_Result;

    t_Result = GDN_BUFREQ_E_NOT_OK;
    if ( RxPduId < (Gdn_PduIdType)TableSize ) {

        if ( RxRoutingTable[RxPduId].GatewayCnt == (gdn_uint8)0 ) {     /* ゲートウェイしない */
            t_Result = RxRoutingTable[RxPduId].StartOfReception( RxRoutingTable[RxPduId].PduId, PduInfo, TpSduLength, BufferSize );

        } else if ( TpSduLength > RxRoutingTable[RxPduId].BufferSize ) {    /* バッファ不足 */
            t_Result = GDN_BUFREQ_E_OVFL;

        } else if ( ( RxBufferIdx[RxPduId] == (Gdn_PduLengthType)0 ) ||
                    ( RxBufferIdx[RxPduId] > RxRoutingTable[RxPduId].BufferSize ) ) {   /* 受信可能 */
            RxBufferIdx[RxPduId] = (Gdn_PduLengthType)0;        /* 受信開始の準備 */
            *BufferSize = RxRoutingTable[RxPduId].BufferSize;   /* バッファサイズ出力 */
            t_Result = GDN_BUFREQ_OK;

        } else {    /* 送受信中 */
            /* 受信通知を無視する */
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpCopyRxData                                    */
/* Description   | Transport層受信データコピー処理の本体                      */
/******************************************************************************/
FUNC(Gdn_BufReq_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_LoTpCopyRxData
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    P2VAR(Gdn_PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSize,
    VAR(Gdn_PduLengthType, AUTOMATIC) RxBufferIdx[],
    CONST(volatile Gdn_PduR_LoTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    Gdn_BufReq_ReturnType t_Result;
    Gdn_PduLengthType     BufPtr;
    Gdn_PduLengthType     BufRemained;
    Gdn_PduLengthType     ReceivedSize;

    t_Result = GDN_BUFREQ_E_NOT_OK;
    if ( RxPduId < (Gdn_PduIdType)TableSize ) {

        if ( RxRoutingTable[RxPduId].GatewayCnt == (gdn_uint8)0 ) {     /* ゲートウェイしない */
            t_Result = RxRoutingTable[RxPduId].CopyRxData( RxRoutingTable[RxPduId].PduId, PduInfo, BufferSize );

        } else {    /* 受信データのバッファリング処理 */
            /* 残バッファサイズ算出 */
            BufPtr       = RxBufferIdx[RxPduId];
            BufRemained  = RxRoutingTable[RxPduId].BufferSize - BufPtr;
            ReceivedSize = PduInfo->SduLength;

            if ( ReceivedSize > BufRemained ) {     /* バッファ不足 */
                t_Result = GDN_BUFREQ_E_NOT_OK;

            } else {    /* データコピー */
                Gdn_PduR_DataCopy( PduInfo->SduDataPtr, (Gdn_PduLengthType)0, RxRoutingTable[RxPduId].GatewayBuffer, BufPtr, ReceivedSize );
                RxBufferIdx[RxPduId] = BufPtr + ReceivedSize;   /* バッファ情報更新 */
                *BufferSize = BufRemained - ReceivedSize;       /* 残バッファサイズの出力 */
                t_Result = GDN_BUFREQ_OK;
            }
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpRxIndication                                  */
/* Description   | Transport層受信完了通知の本体                              */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTpRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result,
    VAR(Gdn_PduLengthType, AUTOMATIC) RxBufferIdx[],
    CONST(volatile Gdn_PduR_LoTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    GdnConst Gdn_PduR_LoTpRxRoutingTblType* RoutingInfo;
             Gdn_PduLengthType              MessageSize;
             Gdn_PduInfoType                PduInfo;
             Gdn_Std_ReturnType             GatewayResult;

    if ( RxPduId < (Gdn_PduIdType)TableSize ) {
        RoutingInfo = &RxRoutingTable[RxPduId];
        MessageSize = RxBufferIdx[RxPduId];

        if ( RoutingInfo->GatewayCnt == (gdn_uint8)0 ) {    /* ゲートウェイしない */
            RoutingInfo->RxIndication( RoutingInfo->PduId, Result );

        } else if ( Result != GDN_NTFRSLT_OK ) {    /* 受信失敗通知 */
            RxBufferIdx[RxPduId] = (Gdn_PduLengthType)0;    /* 受信データを破棄 */

        } else if ( ( MessageSize > (Gdn_PduLengthType)0 ) &&
                    ( MessageSize <= RoutingInfo->BufferSize ) ) { /* 受信データあり */

            PduInfo.SduDataPtr = RoutingInfo->GatewayBuffer;
            PduInfo.SduLength  = MessageSize;

            /* 上位層への受信通知 */
            if ( RoutingInfo->StartOfReception != GDN_NULL_PTR ) {
                Gdn_PduR_ReceiveToUpTp( RoutingInfo, &PduInfo );
            }

            /* Gateway処理 */
            GatewayResult = Gdn_PduR_GatewayToLoTp( RoutingInfo->GatewayCnt, RoutingInfo->GatewayInfo, &PduInfo );
            if ( GatewayResult == GDN_E_NOT_OK ) {  /* ゲートウェイ送信失敗 */
                RxBufferIdx[RxPduId] = (Gdn_PduLengthType)0;    /* 受信データ破棄 */
            }
        } else {
            /* 受信データがないため、何もしない */
        }
    }
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpCopyTxData                                    */
/* Description   | Transport層送信データコピー処理の本体                      */
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
)
{
             Gdn_BufReq_ReturnType          t_Result;
             gdn_uint8                      Cnt;
    GdnConst Gdn_PduR_LoTpRxRoutingTblType* RxRoutingInfo;
             Gdn_PduLengthType*             RxBufferInfo;
    GdnConst Gdn_PduR_LoTpGatewayInfoType*  GwInformation;

    t_Result = GDN_BUFREQ_E_NOT_OK;

    for ( Cnt = (gdn_uint8)0; Cnt < TableSize; Cnt++ ) {

        if ( TxRoutingTable[Cnt].PduId == TxPduId ) {

            if ( TxRoutingTable[Cnt].CopyTxData != GDN_NULL_PTR ) { /* 上層へルーティング */
                t_Result = TxRoutingTable[Cnt].CopyTxData( TxRoutingTable[Cnt].SduId, PduInfo, Retry, AvailableData );

            } else {    /* ゲートウェイのデータコピー処理 */
                RxRoutingInfo = RxTableList[TxRoutingTable[Cnt].ComponentIdx].RxRoutingTbl;
                RxBufferInfo  = RxTableList[TxRoutingTable[Cnt].ComponentIdx].BufPosition;
                GwInformation = Gdn_PduR_GetRxInfoOfTx( TxRoutingTable[Cnt].RxPduId,
                                                        RxRoutingInfo, &RxRoutingInfo, RxBufferInfo, &RxBufferInfo );

                t_Result = Gdn_PduR_LoTpCopyGwData( PduInfo, Retry, AvailableData, RxRoutingInfo->GatewayBuffer,
                                                  GwInformation, TxRoutingTable[Cnt].GatewayIdx, *RxBufferInfo );
            }

            break;
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpTxConfirmation                                */
/* Description   | Transport層送信完了通知の本体                              */
/******************************************************************************/
FUNC(void, PDUR_CODE_SLOW) Gdn_PduR_LoTpTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    VAR(Gdn_NotifResultType, AUTOMATIC) Result,
    CONST(volatile Gdn_PduR_LoTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize,
    CONST(volatile Gdn_PduR_LoTpRxTableListType, PDUR_CONST) RxTableList[]
)
{
             gdn_uint8                      Cnt;
    GdnConst Gdn_PduR_LoTpRxRoutingTblType* RxRoutingInfo;
             Gdn_PduLengthType*             RxBufferInfo;
    GdnConst Gdn_PduR_LoTpGatewayInfoType*  GwInformation;

    for ( Cnt = (gdn_uint8)0; Cnt < TableSize; Cnt++ ) {

        if ( TxRoutingTable[Cnt].PduId == TxPduId ) {

            if ( TxRoutingTable[Cnt].TxConfirmation != GDN_NULL_PTR ) { /* 上層へルーティング */
                TxRoutingTable[Cnt].TxConfirmation( TxRoutingTable[Cnt].SduId, Result );

            } else {    /* ゲートウェイの送信完了通知 */
                RxRoutingInfo = RxTableList[TxRoutingTable[Cnt].ComponentIdx].RxRoutingTbl;
                RxBufferInfo  = RxTableList[TxRoutingTable[Cnt].ComponentIdx].BufPosition;
                GwInformation = Gdn_PduR_GetRxInfoOfTx( TxRoutingTable[Cnt].RxPduId,
                                                        RxRoutingInfo, &RxRoutingInfo, RxBufferInfo, &RxBufferInfo );

                Gdn_PduR_LoTpGwConfirm( RxRoutingInfo->GatewayCnt, GwInformation, TxRoutingTable[Cnt].GatewayIdx, RxBufferInfo );
            }

            break;
        }
    }
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_CancelReceiveApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpCancelReceive                                 */
/* Description   | Transport層受信中止要求の本体                              */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpCancelReceive
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    CONST(volatile Gdn_PduR_UpTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;
    gdn_uint8          Cnt;

    t_Result = GDN_E_NOT_OK;

    for ( Cnt = (gdn_uint8)0; Cnt < TableSize; Cnt++ ) {
        if ( RxRoutingTable[Cnt].SduId == RxPduId ) {
            t_Result = RxRoutingTable[Cnt].RxCancel( RxRoutingTable[Cnt].PduId );
            break;
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_ChangeParameterApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpChangeParameter                               */
/* Description   | Transport層パラメータ変更要求の本体                        */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpChangeParameter
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    VAR(Gdn_TPParameterType, AUTOMATIC) Parameter,
    VAR(gdn_uint16, AUTOMATIC) Value,
    CONST(volatile Gdn_PduR_UpTpRxRoutingTblType, PDUR_CONST) RxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;
    gdn_uint8          Cnt;

    t_Result = GDN_E_NOT_OK;

    for ( Cnt = (gdn_uint8)0; Cnt < TableSize; Cnt++ ) {
        if ( RxRoutingTable[Cnt].SduId == RxPduId ) {
            t_Result = RxRoutingTable[Cnt].ChangeParam( RxRoutingTable[Cnt].PduId, Parameter, Value );
            break;
        }
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpTransmit                                      */
/* Description   | Transport層送信要求の本体                                  */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfo,
    CONST(volatile Gdn_PduR_UpTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;

    t_Result = GDN_E_NOT_OK;
    if ( TxPduId < (Gdn_PduIdType)TableSize ) {
        t_Result = TxRoutingTable[TxPduId].TxTransmit( TxRoutingTable[TxPduId].PduId, PduInfo );
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_CancelTransmitApi_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_UpTpCancelTransmit                                */
/* Description   | Transport層送信中止要求の本体                              */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, PDUR_CODE_SLOW) Gdn_PduR_UpTpCancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId,
    CONST(volatile Gdn_PduR_UpTpTxRoutingTblType, PDUR_CONST) TxRoutingTable[],
    VAR(gdn_uint8, AUTOMATIC) TableSize
)
{
    Gdn_Std_ReturnType t_Result;

    t_Result = GDN_E_NOT_OK;
    if ( TxPduId < (Gdn_PduIdType)TableSize ) {
        t_Result = TxRoutingTable[TxPduId].TxCancel( TxRoutingTable[TxPduId].PduId );
    }

    return t_Result;
}
#endif


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Nw == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoRxLoop                                          */
/* Description   | 受信通知のマルチキャスト処理（受信andゲートウェイ）        */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in) PduInfo    : Network層受信Pdu情報                     */
/*               | (in) RxDstTable : Network層受信PduIdの転送先リスト         */
/*               | (in) TableSize  : テーブルの項目数                         */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_PduR_LoRxLoop( const    Gdn_PduInfoType*           PduInfo,
                               GdnConst Gdn_PduR_LoNwRxDstInfoType RxDstTable[],
                                        gdn_uint16                 TableSize )
{
    gdn_uint16 Cnt;

    for ( Cnt = (gdn_uint16)0; Cnt < TableSize; Cnt++ ) {
        RxDstTable[Cnt].DstInterface( RxDstTable[Cnt].PduId, PduInfo );
    }
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_DataCopy                                          */
/* Description   | データコピー処理                                           */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in) SrcBuf    : コピー元のデータ                          */
/*               | (in) SrcOffset : コピー元のバッファの開始位置              */
/*               | (in) DstBuf    : コピー先のバッファ                        */
/*               | (in) DstOffset : コピー先のバッファの開始位置              */
/*               | (in) Size      : コピー対象のバイト数                      */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_PduR_DataCopy( const gdn_uint8 SrcBuf[], Gdn_PduLengthType SrcOffset,
                                     gdn_uint8 DstBuf[], Gdn_PduLengthType DstOffset, Gdn_PduLengthType Size )
{
    gdn_uint8 Cnt;

    Cnt = (gdn_uint8)(Size & (Gdn_PduLengthType)GDN_PDUR_Num7); /* Cnt = Size % 8 */
    Size += SrcOffset;
    while ( Size > SrcOffset ) {    /* Sizeが0の場合はコピーしない */
        switch ( Cnt ) {
            case GDN_PDUR_Num0: /* Size % 8 == 0 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num7: /* Size % 8 == 7 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num6: /* Size % 8 == 6 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num5: /* Size % 8 == 5 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num4: /* Size % 8 == 4 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num3: /* Size % 8 == 3 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            case GDN_PDUR_Num2: /* Size % 8 == 2 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;    /* break不要 */
            default:            /* Size % 8 == 1 */
                DstBuf[DstOffset] = SrcBuf[SrcOffset];
                DstOffset++;
                SrcOffset++;
                break;
        }
        Cnt = GDN_PDUR_Num0;
    }
}
#endif


#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_InitBuffer                                        */
/* Description   | バッファの初期化処理                                       */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in) Buffer : 初期化対象バッファ                           */
/*               | (in) Size   : バッファサイズ                               */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_PduR_InitBuffer( gdn_uint8 Buffer[], Gdn_PduLengthType Size )
{
    gdn_uint8 Cnt;

    Cnt = (gdn_uint8)(Size & (Gdn_PduLengthType)GDN_PDUR_Num7); /* Cnt = Size % 8 */
    while ( Size > (Gdn_PduLengthType)0 ) { /* Sizeが0の場合は処理しない */
        switch ( Cnt ) {
            case GDN_PDUR_Num0: /* Size % 8 == 0 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num7: /* Size % 8 == 7 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num6: /* Size % 8 == 6 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num5: /* Size % 8 == 5 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num4: /* Size % 8 == 4 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num3: /* Size % 8 == 3 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            case GDN_PDUR_Num2: /* Size % 8 == 2 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
            default:            /* Size % 8 == 1 */
                Size--;
                Buffer[Size] = (gdn_uint8)0;    /* break不要 */
                break;
        }
        Cnt = GDN_PDUR_Num0;
    }
}
#endif


#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_ReceiveToUpTp                                     */
/* Description   | 上位TP層受信通知                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) RoutingInfo:下位Transport層の受信ルーティングテーブル */
/*               | (in) RxPduInfo  :受信Sdu情報（メッセージサイズ、データ）   */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_PduR_ReceiveToUpTp( GdnConst Gdn_PduR_LoTpRxRoutingTblType* RoutingInfo,
                                    const    Gdn_PduInfoType*               RxPduInfo )
{
    Gdn_PduLengthType     UpBufferSize;
    Gdn_BufReq_ReturnType GetBufferResult;

    UpBufferSize = (Gdn_PduLengthType)0;

    GetBufferResult  = RoutingInfo->StartOfReception( RoutingInfo->PduId, RxPduInfo, RxPduInfo->SduLength, &UpBufferSize );
    if ( GetBufferResult == GDN_BUFREQ_OK ) {
        if ( UpBufferSize >= RxPduInfo->SduLength ) {   /* 受信可能 */
            /* 受信データコピー */
            GetBufferResult = RoutingInfo->CopyRxData( RoutingInfo->PduId, RxPduInfo, &UpBufferSize );

            if ( GetBufferResult == GDN_BUFREQ_OK ) {
                RoutingInfo->RxIndication( RoutingInfo->PduId, GDN_NTFRSLT_OK );

            } else {
                RoutingInfo->RxIndication( RoutingInfo->PduId, GDN_NTFRSLT_E_NOT_OK );
            }

        } else {    /* バッファサイズ不足 */
            RoutingInfo->RxIndication( RoutingInfo->PduId, GDN_NTFRSLT_E_NO_BUFFER );
        }
    }
    /* else 上位層の転送を中止する */
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_LoLayerReceive_Tp == GDN_ON ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_GatewayToLoTp                                     */
/* Description   | 下位TP層ゲートウェイ処理（送信要求）                       */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) GatewayCnt  : ゲートウェイの転送先数                  */
/*               | (in) GatewayInfo : ゲートウェイ情報のテーブル              */
/*               | (in) PduInfo     : 受信Sdu情報（メッセージサイズ、データ） */
/* Return Value  | ゲートウェイ処理の結果                                     */
/*               |  GDN_E_OK     : ゲートウェイ処理が一つでも転送成功した     */
/*               |  GDN_E_NOT_OK : すべてのゲートウェイ送信処理が失敗した     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static Gdn_Std_ReturnType Gdn_PduR_GatewayToLoTp( gdn_uint8                    GatewayCnt,
                                         GdnConst Gdn_PduR_LoTpGatewayInfoType GatewayInfo[],
                                         const    Gdn_PduInfoType*             PduInfo )
{
    Gdn_Std_ReturnType TotalResult;
    gdn_uint8          GwCnt;
    Gdn_Std_ReturnType TransmitResult;

    TotalResult = GDN_E_NOT_OK;

    for ( GwCnt = (gdn_uint8)0; GwCnt < GatewayCnt; GwCnt++ ) {
        *(GatewayInfo[GwCnt].TxDataPtr) = (Gdn_PduLengthType)0;
        TransmitResult = GatewayInfo[GwCnt].TxTransmit( GatewayInfo[GwCnt].PduId, PduInfo );
        if ( TransmitResult == GDN_E_OK ) {
            /* 転送成功のコンポーネントのCopyTxData処理を実施するため、   */
            /* 一つでも転送成功のコンポーネントがあったら、転送成功とする */
            TotalResult = GDN_E_OK;
        }
    }

    return TotalResult;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_GetRxInfoOfTx                                     */
/* Description   | Transport層送信ゲートウェイ時の受信情報取得                */
/* Re-entrancy   | Reentrant                                                  */
/* Parameter(s)  | (in)  RxPduId          : 受信PDUID                         */
/*               | (in)  RxRoutingInfo    : 受信ルーティングテーブル          */
/*               | (out) RxRoutingInfoOut : 指定の受信PDUIDのルーティング情報 */
/*               | (in)  RxBufferInfo     : 受信データ位置情報の配列          */
/*               | (out) RxBufferInfoOut  : 指定の受信PDUIDの位置情報         */
/* Return Value  | 受信PDUIDのゲートウェイ情報へのポインタ                    */
/* Notes         | MISRA-C対応のため、ポインタの直接演算を回避する処置        */
/******************************************************************************/
static GdnConst Gdn_PduR_LoTpGatewayInfoType* Gdn_PduR_GetRxInfoOfTx( Gdn_PduIdType                   RxPduId,
                                                             GdnConst Gdn_PduR_LoTpRxRoutingTblType   RxRoutingInfo[],
                                                             GdnConst Gdn_PduR_LoTpRxRoutingTblType** RxRoutingInfoOut,
                                                                      Gdn_PduLengthType               RxBufferInfo[],
                                                                      Gdn_PduLengthType**             RxBufferInfoOut )
{
    *RxRoutingInfoOut = &RxRoutingInfo[RxPduId];
    *RxBufferInfoOut  = &RxBufferInfo[RxPduId];
    return RxRoutingInfo[RxPduId].GatewayInfo;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpCopyGwData                                    */
/* Description   | Transport層送信ゲートウェイ時のデータコピー処理            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  PduInfo       : 送信データのPDU情報（サイズ、データ）*/
/*               | (in)  Retry         : データ取得のリトライ情報             */
/*               | (out) AvailableData : コピー処理後の残メッセージサイズ     */
/*               | (in)  RxBuffer      : 受信メッセージのバッファ（コピー元） */
/*               | (in)  RxGatewayInfo : 転送先情報テーブル                   */
/*               | (in)  GatewayIndex  : 転送先情報のインデックス             */
/*               | (in)  RxBufPtr      : 受信メッセージの位置情報             */
/* Return Value  | 送信データ取得処理の結果                                   */
/*               |  GDN_BUFREQ_OK       : 正常取得                            */
/*               |  GDN_BUFREQ_E_BUSY   : 送信データ不足                      */
/*               |  GDN_BUFREQ_E_NOT_OK : データ取得異常                      */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static Gdn_BufReq_ReturnType Gdn_PduR_LoTpCopyGwData( const    Gdn_PduInfoType*             PduInfo,
                                                      const    Gdn_RetryInfoType*           Retry,
                                                               Gdn_PduLengthType*           AvailableData,
                                                      const    gdn_uint8*                   RxBuffer,
                                                      GdnConst Gdn_PduR_LoTpGatewayInfoType RxGatewayInfo[],
                                                               gdn_uint8                    GatewayIndex,
                                                               Gdn_PduLengthType            RxBufPtr )
{
    Gdn_BufReq_ReturnType t_Result;
    Gdn_PduLengthType     TxBufPtr;
    Gdn_PduLengthType     t_ReqData;
    Gdn_PduLengthType     RemainedData;

    t_Result   = GDN_BUFREQ_OK;
    TxBufPtr = *RxGatewayInfo[GatewayIndex].TxDataPtr;
    t_ReqData  = PduInfo->SduLength;
    RemainedData = (Gdn_PduLengthType)0;
    if ( RxBufPtr > TxBufPtr ) {    /* 未送信データあり */
        RemainedData = RxBufPtr - TxBufPtr;
    }

    if ( ( Retry == GDN_NULL_PTR ) ||   /* Retry情報不使用 */
         ( Retry->TpDataState == GDN_TP_DATACONF ) ||
         ( Retry->TpDataState == GDN_TP_DATAPENDING ) ) {
        /* バッファの動的割り当てをサポートしないため、CONFとPENDINGを区別しない */
        if ( RemainedData >= t_ReqData ) {    /* データあり */
            /* 出力データコピー */
            Gdn_PduR_DataCopy( RxBuffer, TxBufPtr, PduInfo->SduDataPtr, (Gdn_PduLengthType)0, t_ReqData );
            /* データ取得位置の更新 */
            *RxGatewayInfo[GatewayIndex].TxDataPtr = TxBufPtr + t_ReqData;
            /* 残データ数出力 */
            *AvailableData = RemainedData - t_ReqData;

        } else {
            t_Result = GDN_BUFREQ_E_BUSY;
        }

    } else if ( ( Retry->TpDataState == GDN_TP_DATARETRY ) &&   /* データの再取得 */
                ( Retry->TxTpDataCnt <= TxBufPtr ) ) {
        /* 取得位置の後退 */
        TxBufPtr     -= Retry->TxTpDataCnt;
        RemainedData += Retry->TxTpDataCnt;

        if ( RemainedData >= t_ReqData ) {    /* データあり */
            /* 出力データコピー */
            Gdn_PduR_DataCopy( RxBuffer, TxBufPtr, PduInfo->SduDataPtr, (Gdn_PduLengthType)0, t_ReqData );
            /* データ取得位置の更新 */
            *RxGatewayInfo[GatewayIndex].TxDataPtr = TxBufPtr + t_ReqData;
            /* 残データ数出力 */
            *AvailableData = RemainedData - t_ReqData;

        } else {
            *RxGatewayInfo[GatewayIndex].TxDataPtr = TxBufPtr;  /* データ取得位置の更新 */
            t_Result = GDN_BUFREQ_E_BUSY;
        }

    } else {
        t_Result = GDN_BUFREQ_E_NOT_OK;
    }

    return t_Result;
}
#endif

#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( ( GDN_PDUR_LoLayerGateway_Tp == GDN_ON ) || ( GDN_PDUR_UpLayerTransmit_Tp == GDN_ON ) ) )
/******************************************************************************/
/* Function Name | Gdn_PduR_LoTpGwConfirm                                     */
/* Description   | Transport層送信ゲートウェイ時の送信完了通知                */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in)  DestCnt       : ゲートウェイの転送先数               */
/*               | (in)  RxGatewayInfo : 転送先情報テーブル                   */
/*               | (in)  GatewayIndex  : 転送先情報のインデックス             */
/*               | (in)  RxBufPtr      : 受信メッセージの位置情報             */
/* Return Value  | 送信データ取得処理の結果                                   */
/*               |  GDN_BUFREQ_OK       : 正常取得                            */
/*               |  GDN_BUFREQ_E_BUSY   : 送信データ不足                      */
/*               |  GDN_BUFREQ_E_NOT_OK : データ取得異常                      */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_PduR_LoTpGwConfirm( gdn_uint8                    DestCnt,
                           GdnConst Gdn_PduR_LoTpGatewayInfoType RxGatewayInfo[],
                                    gdn_uint8                    GatewayIndex,
                                    Gdn_PduLengthType*           RxBufPtr )
{
    gdn_uint8   Cnt;

    /* 送信位置をリセット */
    *RxGatewayInfo[GatewayIndex].TxDataPtr = (Gdn_PduLengthType)0;

    /* G/W完了チェック */
    for ( Cnt = (gdn_uint8)0; Cnt < DestCnt; Cnt++ ) {
        if ( *RxGatewayInfo[Cnt].TxDataPtr != (Gdn_PduLengthType)0 ) {  /* G/W未完了 */
            break;
        }
    }

    if ( Cnt >= DestCnt ) { /* G/W完了 */
        /* 受信位置をリセット */
        *RxBufPtr = (Gdn_PduLengthType)0;
    }
}
#endif

#define GDN_PDUR_STOP_SEC_CODE
#include <Gdn_PduR_MemMap.h>

/**** End of File *************************************************************/
