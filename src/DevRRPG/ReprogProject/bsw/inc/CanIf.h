/* CanIf_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/HEADER                                                */
/******************************************************************************/
#ifndef CANIF_H
#define CANIF_H


/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanIf_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANIF_CS_STOPPED ((uint8)0x00U)
#define CANIF_CS_STARTED ((uint8)0x01U)

#define CANIF_RXPDUID_0   (0U)
#define CANIF_RXPDUID_1   (1U)
#define CANIF_RXPDUID_2   (2U)
#define CANIF_RXPDUID_3   (3U)
#define CANIF_RXPDUID_4   (4U)
#define CANIF_RXPDUID_5   (5U)
#define CANIF_RXPDUID_6   (6U)
#define CANIF_RXPDUID_7   (7U)
#define CANIF_RXPDUID_8   (8U)
#define CANIF_RXPDUID_9   (9U)
#define CANIF_RXPDUID_10  (10U)
#define CANIF_RXPDUID_11  (11U)
#define CANIF_RXPDUID_12  (12U)
#define CANIF_RXPDUID_13  (13U)
#define CANIF_RXPDUID_14  (14U)
#define CANIF_RXPDUID_15  (15U)
#define CANIF_RXPDUID_16  (16U)
#define CANIF_RXPDUID_17  (17U)
#define CANIF_RXPDUID_18  (18U)
#define CANIF_RXPDUID_19  (19U)
#define CANIF_RXPDUID_20  (20U)
#define CANIF_RXPDUID_21  (21U)
#define CANIF_RXPDUID_22  (22U)
#define CANIF_RXPDUID_23  (23U)
#define CANIF_RXPDUID_24  (24U)
#define CANIF_RXPDUID_25  (25U)
#define CANIF_RXPDUID_26  (26U)
#define CANIF_RXPDUID_27  (27U)
#define CANIF_RXPDUID_28  (28U)
#define CANIF_RXPDUID_29  (29U)
#define CANIF_RXPDUID_30  (30U)
#define CANIF_RXPDUID_31  (31U)

#define CANIF_RXPDUID_100 (100U)
#define CANIF_RXPDUID_101 (101U)
#define CANIF_RXPDUID_102 (102U)
#define CANIF_RXPDUID_103 (103U)
#define CANIF_RXPDUID_104 (104U)
#define CANIF_RXPDUID_105 (105U)
#define CANIF_RXPDUID_106 (106U)
#define CANIF_RXPDUID_107 (107U)

#define CANIF_TXPDUID_0   (0U)
#define CANIF_TXPDUID_1   (1U)
#define CANIF_TXPDUID_2   (2U)
#define CANIF_TXPDUID_3   (3U)
#define CANIF_TXPDUID_4   (4U)
#define CANIF_TXPDUID_5   (5U)
#define CANIF_TXPDUID_6   (6U)
#define CANIF_TXPDUID_7   (7U)
#define CANIF_TXPDUID_8   (8U)
#define CANIF_TXPDUID_9   (9U)
#define CANIF_TXPDUID_10  (10U)
#define CANIF_TXPDUID_11  (11U)
#define CANIF_TXPDUID_12  (12U)
#define CANIF_TXPDUID_13  (13U)
#define CANIF_TXPDUID_14  (14U)
#define CANIF_TXPDUID_15  (15U)

#define CANIF_TXPDUID_100 (100U)
#define CANIF_TXPDUID_101 (101U)
#define CANIF_TXPDUID_102 (102U)
#define CANIF_TXPDUID_103 (103U)
#define CANIF_TXPDUID_104 (104U)
#define CANIF_TXPDUID_105 (105U)
#define CANIF_TXPDUID_106 (106U)
#define CANIF_TXPDUID_107 (107U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* See CanIf_Types.h */


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, CANIF_CODE_SLOW) CanIf_Init
(
    P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr
);

FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_SetControllerMode
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
);

FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_Transmit
(
    VAR(PduIdType, AUTOMATIC) CanIfTxSduId,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr
);

FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_CancelTransmit
(
    VAR(PduIdType, AUTOMATIC) CanIfTxSduId
);

FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_SetBaudrate
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
);
#if 0   /* Nbr1503(ChangeBaudrate) */
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_CheckBaudrate
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
);
#endif
FUNC(void, CANIF_CODE_SLOW) CanIf_TxConfirmation
(
    VAR(PduIdType, AUTOMATIC) CanTxPduId
);

FUNC(void, CANIF_CODE_SLOW) CanIf_RxIndication
(
    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
);

FUNC(void, CANIF_CODE_SLOW) CanIf_ControllerModeIndication
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANIF_START_SEC_CST
#include <CanIf_MemMap.h>

extern CONST(CanIf_ConfigType, CANIF_CONFIG_DATA) CanIf_Cfg_Data;

#define CANIF_STOP_SEC_CST
#include <CanIf_MemMap.h>


#endif /* CANIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

