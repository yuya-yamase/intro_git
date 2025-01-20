/* CanIf_Ucfg_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/Ucfg/HEADER                                           */
/******************************************************************************/
#ifndef CANIF_UCFG_H
#define CANIF_UCFG_H


/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANIF_UCFG_CONTROLLERNUM        (1U)

#define CANIF_UCFG_CANCONTROLLERID_0    (5U)

#define CANIF_UCFG_CANFD_SUPPORT        (STD_ON)

#define CANIF_UCFG_RXPDUNUM             (4U)                        /* ^^^ */
#define CANIF_UCFG_TXPDUNUM             (2U)                        /* ^^^ */

#define CANIF_UCFG_RXINDICATIONFUNC_0   (CANIF_CANTP_RXINDICATION)
#define CANIF_UCFG_RXPDUCANID_0         (0x18DA17E0UL)              /* ^^^ */
#define CANIF_UCFG_RXPDUCANIDTYPE_0     (CANIF_EXTENDED_FD_CAN)
#define CANIF_UCFG_HRHINDX_0            (0U)
#define CANIF_UCFG_RXINDICATIONFUNC_1   (CANIF_CANTP_RXINDICATION)
#define CANIF_UCFG_RXPDUCANID_1         (0x18DBEFE0UL)              /* ^^^ */
#define CANIF_UCFG_RXPDUCANIDTYPE_1     (CANIF_EXTENDED_FD_CAN)
#define CANIF_UCFG_HRHINDX_1            (1U)
#define CANIF_UCFG_RXINDICATIONFUNC_2   (CANIF_CANTP_RXINDICATION)  /* ^^^ */
#define CANIF_UCFG_RXPDUCANID_2         (0x18DA17E0UL)              /* ^^^ */
#define CANIF_UCFG_RXPDUCANIDTYPE_2     (CANIF_EXTENDED_CAN)        /* ^^^ */
#define CANIF_UCFG_HRHINDX_2            (0U)                        /* ^^^ */
#define CANIF_UCFG_RXINDICATIONFUNC_3   (CANIF_CANTP_RXINDICATION)  /* ^^^ */
#define CANIF_UCFG_RXPDUCANID_3         (0x18DBEFE0UL)              /* ^^^ */
#define CANIF_UCFG_RXPDUCANIDTYPE_3     (CANIF_EXTENDED_CAN)        /* ^^^ */
#define CANIF_UCFG_HRHINDX_3            (1U)                        /* ^^^ */

#define CANIF_UCFG_TXCONFIRMATIONFUNC_0 (CANIF_CANTP_TXCONFIRMATION)
#define CANIF_UCFG_TXPDUCANID_0         (0x18DAE017UL)              /* ^^^ */
#define CANIF_UCFG_TXPDUCANIDTYPE_0     (CANIF_EXTENDED_FD_CAN)
#define CANIF_UCFG_HTHINDX_0            (2U)
#define CANIF_UCFG_TXCONFIRMATIONFUNC_1 (CANIF_CANTP_TXCONFIRMATION)/* ^^^ */
#define CANIF_UCFG_TXPDUCANID_1         (0x18DAE017UL)              /* ^^^ */
#define CANIF_UCFG_TXPDUCANIDTYPE_1     (CANIF_EXTENDED_CAN)        /* ^^^ */
#define CANIF_UCFG_HTHINDX_1            (3U)                        /* ^^^ */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

#define CANIF_START_SEC_CST
#include <CanIf_MemMap.h>

extern CONST(CanIf_ControllerSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_ControllerSetting_Data[CANIF_UCFG_CONTROLLERNUM];
extern CONST(CanIf_RxPduSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_RxPduSetting_Data[CANIF_UCFG_RXPDUNUM];
extern CONST(CanIf_TxPduSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_TxPduSetting_Data[CANIF_UCFG_TXPDUNUM];

#define CANIF_STOP_SEC_CST
#include <CanIf_MemMap.h>


#endif /* CANIF_UCFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

