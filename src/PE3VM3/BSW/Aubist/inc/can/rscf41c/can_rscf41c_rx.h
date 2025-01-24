/* can_rscf41c_rx_h_m10700_v2-2-1                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41C/RX/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF41C_RX_H
#define     CAN_RSCF41C_RX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_RX_RXFINISH_USE_0 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_0 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_1 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_1 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_2 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_2 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_3 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_3 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_4 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_4 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_5 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_5 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_6 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_6 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_USE_7 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_7 == CAN_USE )         \
     && ( CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_RX_RXFINISH_ANYCH_USE \
    ( ( ( CAN_RX_RXFINISH_USE_0 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_1 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_2 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_3 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_4 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_5 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_6 == CAN_USE ) \
     || ( CAN_RX_RXFINISH_USE_7 == CAN_USE ) ) ? CAN_USE : CAN_NOUSE )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  Can_rx_RxIndMbox( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg );

uint8 Can_rx_ChkRxFinMbox( uint8 u1Controller, uint8 u1Kind );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_RSCF41C_RX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/03/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
