/* CanIf_Local_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/Local/HEADER                                          */
/******************************************************************************/
#ifndef CANIF_LOCAL_H
#define CANIF_LOCAL_H


/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Rte.h>
#include "CanIf_Ucfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANIF_CS_UNINIT                       ((uint8)0x00U)
#define CANIF_CS_INIT                         ((uint8)0x01U)

#define CANIF_API_ID_INIT                     (0x00U)
#define CANIF_API_ID_SETCONTROLLERMODE        (0x01U)
#define CANIF_API_ID_TRANSMIT                 (0x02U)
#define CANIF_API_ID_CANCELTRANSMIT           (0x03U)
#define CANIF_API_ID_SETBAUDRATE              (0x04U)
#define CANIF_API_ID_CHECKBAUDRATE            (0x05U)
#define CANIF_API_ID_TXCONFIRMATION           (0x06U)
#define CANIF_API_ID_RXINDICATION             (0x07U)
#define CANIF_API_ID_CONTROLLERMODEINDICATION (0x08U)

#define CANIF_E_UNINIT                        (0x00U)
#define CANIF_E_PARAM_POINTER                 (0x01U)

#define CANIF_STANDARD_CAN                    ((uint8)0x00U)
#define CANIF_EXTENDED_CAN                    ((uint8)0x02U)
#if (CANIF_UCFG_CANFD_SUPPORT == STD_ON)
#define CANIF_STANDARD_FD_CAN                 ((uint8)0x01U)
#define CANIF_EXTENDED_FD_CAN                 ((uint8)0x03U)
#endif
#define CANIF_STANDARD_CANID_MASK             (0x000007FFUL)
#define CANIF_EXTENDED_CANID_MASK             (0x1FFFFFFFUL)
#define CANIF_CANIDTYPE_SHIFTBIT              (30U)

#if (CANIF_UCFG_CANFD_SUPPORT == STD_ON)
#define CANIF_SDUMAXLENGTH                    ((uint8)0x40U)
#else
#define CANIF_SDUMAXLENGTH                    ((uint8)0x08U)
#endif

#define CANIF_CANTP_RXINDICATION              (&Gdn_CanTp_RxIndication)
#define CANIF_CANTP_TXCONFIRMATION            (&Gdn_CanTp_TxConfirmation)
#define CANIF_PDUR_RXINDICATION               (&Gdn_PduR_CanIfRxIndication)
#define CANIF_PDUR_TXCONFIRMATION             (&Gdn_PduR_CanIfTxConfirmation)
#if 0   /* Nbr1503(CtrlFrame) */
#define CANIF_RPGLIB_RXINDICATION             (&Rte_RpgLib_CtrlFrameRxIndication)
#define CANIF_RPGLIB_TXCONFIRMATION           (&Rte_RpgLib_CtrlFrameTxConfirmation)
#endif


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


#endif /* CANIF_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

