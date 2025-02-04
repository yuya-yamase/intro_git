/* CanIf_Types_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/Types/HEADER                                          */
/******************************************************************************/
#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H


/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <Can.h>
#include <Gdn_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 CanIf_ControllerModeType;

typedef P2FUNC(void, CANIF_CALLOUT_CODE, CanIf_RxIndicationFuncType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
);

typedef P2FUNC(void, CANIF_CALLOUT_CODE, CanIf_TxConfirmationFuncType)
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId
);

typedef struct {
    CanIf_TxConfirmationFuncType TxConfirmationFunc;
    uint32 TxPduCanId;
    PduIdType TxPduId;
    Can_HwHandleType HthIndx;
    uint8 TxPduCanIdType;
}CanIf_TxPduSettingConfigType;

typedef struct {
    CanIf_RxIndicationFuncType RxIndicationFunc;
    uint32 RxPduCanId;
    PduIdType RxPduId;
    Can_HwHandleType HrhIndx;
    uint8 RxPduCanIdType;
}CanIf_RxPduSettingConfigType;

typedef struct {
    P2CONST(CanIf_RxPduSettingConfigType, TYPEDEF, CANIF_APPL_CONST) RxPduSettingTbl;
    P2CONST(CanIf_TxPduSettingConfigType, TYPEDEF, CANIF_APPL_CONST) TxPduSettingTbl;
    uint8 RxPduSettingNum;
    uint8 TxPduSettingNum;
}CanIf_TxRxInfoConfigType;

typedef struct {
    uint8 CanControllerId;
}CanIf_ControllerSettingConfigType;

typedef struct {
    P2CONST(CanIf_ControllerSettingConfigType, TYPEDEF, CANIF_APPL_CONST) ControllerSettingTbl;
    uint8 ControllerSettingNum;
}CanIf_ControllerConfigType;

typedef struct {
    P2CONST(CanIf_ControllerConfigType, TYPEDEF, CANIF_APPL_CONST) ControllerInfoTbl;
    P2CONST(CanIf_TxRxInfoConfigType, TYPEDEF, CANIF_APPL_CONST) TxRxInfoTbl;
}CanIf_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* CANIF_TYPES_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

