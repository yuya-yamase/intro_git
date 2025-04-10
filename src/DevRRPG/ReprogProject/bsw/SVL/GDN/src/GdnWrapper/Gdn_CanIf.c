/* Gdn_CanIf_c_01_0004 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | CANインターフェース                                          */
/* Notes       | 本ファイルはGUARDIANのCANインターフェース関連処理のWrapperに */
/*             | 対して実装の一例を示すものである。                           */
/*             | 製品の機能に合わせて下記ファイルの実装を変更してください。   */
/*             |   Gdn_CanIf.c    Gdn_CanIf.h                                 */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  01_0001   2015/8/31    DN毛     CS結合用テンプレート更新                  */
/*  01_0002   2018/02/13   AUBASS   リプログ対応                              */
/*  01_0003   2020/03/10   AUBASS   Update                                    */
/*  01_0004   2022/03/01   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include    <Gdn.h>
#include    <ComStack_Types.h>
#include    <CanIf.h>
#include    <ReprogOpt.h>
#include    "Gdn_CanIf.h"

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
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

#define GDN_WRAPPER_STOP_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_WRAPPER_START_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_CanIf_Transmit                                         */
/* Description   | CanIfの送信要求（戻り値の値が一致する前提）                */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CANIF_CODE_SLOW) Gdn_CanIf_Transmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
)
{
    Gdn_Std_ReturnType Ret;
    PduInfoType tmp;

    Ret = GDN_E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        tmp.SduDataPtr = PduInfoPtr->SduDataPtr;
        tmp.SduLength = (PduLengthType)PduInfoPtr->SduLength;
        Ret = CanIf_Transmit( (PduIdType)CanTxPduId, &tmp );
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Gdn_CanIf_CancelTransmit                                   */
/* Description   | CanIfの送信中止要求                                        */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, GDN_CANIF_CODE_SLOW) Gdn_CanIf_CancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTxPduId
)
{
    Gdn_Std_ReturnType Ret;

    Ret = GDN_E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        Ret = CanIf_CancelTransmit( (PduIdType)CanTxPduId );
    }

    return Ret;
}

#if (GDN_PDUR_UsePduR_Nw == GDN_ON)
/******************************************************************************/
/* Function Name | Gdn_CanIf_Gateway                                          */
/* Description   | CanIfのゲートウェイ要求                                    */
/******************************************************************************/
FUNC(void, GDN_CANIF_CODE_SLOW) Gdn_CanIf_Gateway
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
)
{
    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        /* 他の手段で異常検出するため戻り値を確認しない */
        (void)Gdn_CanIf_Transmit( PduId, PduInfoPtr );
    }

    return;
}
#endif

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define GDN_WRAPPER_STOP_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/**** End of File *************************************************************/
