/* can_cv_cbk_h_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/CV/CBK/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_CV_CBK_H
#define     CAN_CV_CBK_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void Can_cv_IP0_CntrlMdInd( uint8 Controller, CanIf_ControllerModeType ControllerMode );
void Can_cv_IP0_TxConfirmation( PduIdType CanTxPduId );
void Can_cv_IP0_RxIndication( Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, CanConstR uint8 CanSduPtr[] );
void Can_cv_IP0_ControllerBusOff( uint8 Controller );
void Can_cv_IP0_ControllerFail( uint8 Controller );

void Can_cv_IP1_CntrlMdInd( uint8 Controller, CanIf_ControllerModeType ControllerMode );
void Can_cv_IP1_TxConfirmation( PduIdType CanTxPduId );
void Can_cv_IP1_RxIndication( Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, CanConstR uint8 CanSduPtr[] );
void Can_cv_IP1_ControllerBusOff( uint8 Controller );
void Can_cv_IP1_ControllerFail( uint8 Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_CV_CBK_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2018/04/04                                              */
/*  v2-0-2         :2021/12/01                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
