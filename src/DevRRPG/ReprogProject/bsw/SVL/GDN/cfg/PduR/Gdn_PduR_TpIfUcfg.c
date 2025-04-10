/* Gdn_PduR_TpIfUcfg_c_00_0002 */
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
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>
#include <Gdn_Ucfg.h>
#include "Gdn_PduR_Ucfg.h"
#include "Gdn_PduR_Core.h"
#include "Gdn_PduR_TpIfUcfg.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

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

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_PDUR_START_SEC_CODE
#include <Gdn_PduR_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>StartOfReception                            */
/* Description   | Transport層受信開始通知                                    */
/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>CopyRxData                                  */
/* Description   | Transport層受信データコピー処理                            */
/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>RxIndication                                */
/* Description   | Transport層受信完了通知                                    */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
Gdn_BufReq_ReturnType GDN_PDUR_LoTpStartOfReception(0) ( Gdn_PduIdType      RxPduId,
                                                   const Gdn_PduInfoType*   PduInfoPtr,
                                                         Gdn_PduLengthType  TpSduLength,
                                                         Gdn_PduLengthType* BufferSizePtr )
{
    return Gdn_PduR_LoTpStartOfReception( RxPduId, PduInfoPtr, TpSduLength, BufferSizePtr,
                                          &Gdn_PduR_LoTpRxDataPtr_0[0], &gdn_pdur_LoTpRxRoutingTbl_0[0],
                                          (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_LoTp_0 );
}

Gdn_BufReq_ReturnType GDN_PDUR_LoTpCopyRxData(0) ( Gdn_PduIdType      RxPduId,
                                             const Gdn_PduInfoType*   PduInfoPtr,
                                                   Gdn_PduLengthType* BufferSizePtr )
{
    return Gdn_PduR_LoTpCopyRxData( RxPduId, PduInfoPtr, BufferSizePtr,
                                    &Gdn_PduR_LoTpRxDataPtr_0[0], &gdn_pdur_LoTpRxRoutingTbl_0[0],
                                    (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_LoTp_0 );
}

void GDN_PDUR_LoTpRxIndication(0) ( Gdn_PduIdType RxPduId, Gdn_NotifResultType Result )
{
    Gdn_PduR_LoTpRxIndication( RxPduId, Result,
                               &Gdn_PduR_LoTpRxDataPtr_0[0], &gdn_pdur_LoTpRxRoutingTbl_0[0],
                               (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_LoTp_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>CopyTxData                                  */
/* Description   | Transport層送信データコピー処理                            */
/******************************************************************************/
/* Function Name | Gdn_PduR_<LoTp>TxConfirmation                              */
/* Description   | Transport層送信完了通知の本体                              */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoTp_0 != 0U ) )
Gdn_BufReq_ReturnType GDN_PDUR_LoTpCopyTxData(0) ( Gdn_PduIdType      TxPduId,
                                             const Gdn_PduInfoType*   PduInfo,
                                             const Gdn_RetryInfoType* Retry,
                                                   Gdn_PduLengthType* AvailableData )
{
    return Gdn_PduR_LoTpCopyTxData( TxPduId, PduInfo, Retry, AvailableData, &gdn_pdur_LoTpTxRoutingTbl_0[0],
                                    (gdn_uint8)GDN_PDUR_MaxTxPduIdCnt_LoTp_0,
                                    &gdn_pdur_LoTpRxRoutingTableList[0] );
}

void GDN_PDUR_LoTpTxConfirmation(0) ( Gdn_PduIdType TxPduId, Gdn_NotifResultType Result )
{
    Gdn_PduR_LoTpTxConfirmation( TxPduId, Result, &gdn_pdur_LoTpTxRoutingTbl_0[0],
                                 (gdn_uint8)GDN_PDUR_MaxTxPduIdCnt_LoTp_0,
                                 &gdn_pdur_LoTpRxRoutingTableList[0] );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>CancelReceive                               */
/* Description   | Transport層受信中止要求                                    */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_CancelReceive_UpTp_0 == GDN_ON ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpCancelReceive(0) ( Gdn_PduIdType RxPduId )
{
    return Gdn_PduR_UpTpCancelReceive( RxPduId, &gdn_pdur_UpTpRxRoutingTbl_0[0], (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_UpTp_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>ChangeParameter                             */
/* Description   | Transport層パラメータ変更要求                              */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_ChangeParameter_UpTp_0 == GDN_ON ) )
Gdn_Std_ReturnType GDN_PDUR_UpTpChangeParameter(0) ( Gdn_PduIdType RxPduId, Gdn_TPParameterType Parameter,
                                                     gdn_uint16    Value )
{
    return Gdn_PduR_UpTpChangeParameter( RxPduId, Parameter, Value, &gdn_pdur_UpTpRxRoutingTbl_0[0],
                                         (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_UpTp_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>Transmit                                    */
/* Description   | Transport層送信要求                                        */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_UpTp_0 != 0U ) )

#define GDN_PDUR_START_SEC_CST
#include <Gdn_PduR_MemMap.h>
extern GdnConst Gdn_PduR_UpTpTxRoutingTblType gdn_pdur_UpTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_UpTp_0];
#define GDN_PDUR_STOP_SEC_CST
#include <Gdn_PduR_MemMap.h>

Gdn_Std_ReturnType GDN_PDUR_UpTpTransmit(0) ( Gdn_PduIdType TxPduId, const Gdn_PduInfoType* PduInfo )
{
    return Gdn_PduR_UpTpTransmit( TxPduId, PduInfo, &gdn_pdur_UpTpTxRoutingTbl_0[0], (gdn_uint8)GDN_PDUR_MaxTxPduIdCnt_UpTp_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<UpTp>CancelTransmit                              */
/* Description   | Transport層送信中止要求                                    */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_CancelTransmit_UpTp_0 == GDN_ON ) )

#define GDN_PDUR_START_SEC_CST
#include <Gdn_PduR_MemMap.h>
extern GdnConst Gdn_PduR_UpTpTxRoutingTblType gdn_pdur_UpTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_UpTp_0];
#define GDN_PDUR_STOP_SEC_CST
#include <Gdn_PduR_MemMap.h>

Gdn_Std_ReturnType GDN_PDUR_UpTpCancelTransmit(0) ( Gdn_PduIdType TxPduId )
{
    return Gdn_PduR_UpTpCancelTransmit( TxPduId, &gdn_pdur_UpTpTxRoutingTbl_0[0], GDN_PDUR_MaxTxPduIdCnt_UpTp_0 );
}
#endif


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define GDN_PDUR_STOP_SEC_CODE
#include <Gdn_PduR_MemMap.h>

/**** End of File *************************************************************/

