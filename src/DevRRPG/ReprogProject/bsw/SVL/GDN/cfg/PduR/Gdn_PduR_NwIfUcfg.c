/* Gdn_PduR_NwIfUcfg_c_00_0002 */
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
#include "Gdn_PduR_NwIfUcfg.h"

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
/* Function Name | Gdn_PduR_<Lo>RxIndication                                  */
/* Description   | Network層受信通知                                          */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoNw_0 != 0U ) )
void GDN_PDUR_LoRxIndication(0) ( Gdn_PduIdType RxPduId, const Gdn_PduInfoType* PduInfoPtr )
{
    Gdn_PduR_LoRxIndication( RxPduId, PduInfoPtr, &gdn_pdur_LoNwRxRoutingTbl_0[0], (gdn_uint16)GDN_PDUR_MaxRxPduIdCnt_LoNw_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Lo>TxConfirmation                                */
/* Description   | Network層送信完了通知                                      */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_TxConfirmation_LoNw_0 == GDN_ON) )
void GDN_PDUR_LoTxConfirmation(0) ( Gdn_PduIdType TxPduId )
{
    Gdn_PduR_LoTxConfirmation( TxPduId, &gdn_pdur_LoNwTxRoutingTbl_0[0], (gdn_uint16)GDN_PDUR_MaxTxPduIdCnt_LoNw_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Lo>TriggerTransmit                               */
/* Description   | Network層送信要求トリガー                                  */
/******************************************************************************/
    /* コンポーネント#0 */
#if ( ( GDN_PDUR_UsePduR_Nw == GDN_ON ) && ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_TriggerTransmit_LoNw_0 == GDN_ON) )
Gdn_Std_ReturnType GDN_PDUR_LoTriggerTransmit(0) ( Gdn_PduIdType TxPduId, Gdn_PduInfoType* PduInfoPtr )
{
    return Gdn_PduR_LoTriggerTransmit( TxPduId, PduInfoPtr, &gdn_pdur_LoNwTxRoutingTbl_0[0], (gdn_uint16)GDN_PDUR_MaxTxPduIdCnt_LoNw_0 );
}
#endif

/******************************************************************************/
/* Function Name | Gdn_PduR_<Up>Transmit                                      */
/* Description   | Network層送信要求                                          */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_PduR_<Up>CancelTransmit                                */
/* Description   | Network層送信中止要求                                      */
/******************************************************************************/

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define GDN_PDUR_STOP_SEC_CODE
#include <Gdn_PduR_MemMap.h>

/**** End of File *************************************************************/

