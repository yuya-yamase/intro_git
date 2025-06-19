/* can_rscf2_cfg_ext_h_m10700_v2-2-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/CONFIG_EXT/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF2_CFG_EXT_H
#define     CAN_RSCF2_CFG_EXT_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/********************************/
/* MCU Specific Configuration   */
/********************************/
/*--------------------------------------------------------------*/
/* CAN Baudrate Control Clock Source                            */
/*--------------------------------------------------------------*/
#define CAN_CFG_BAUDRATE_CLK_SOURCE     (CAN_CLK_CLKC)


/*--------------------------------------------------------------*/
/* Cycle Number of CAN RAM Initialization                       */
/*--------------------------------------------------------------*/
#define CAN_CFG_RAM_INIT_CYCLE          (19200UL)


/*--------------------------------------------------------------*/
/* Payload Overflow Mode Select                                 */
/*--------------------------------------------------------------*/
#define CAN_CFG_PAYLOAD_OVERFLOW_MODE   (CAN_PAYLOAD_OVERFLOW_NOTSTORED)


/*--------------------------------------------------------------*/
/* Payload Size of TRX FIFO 0 for TX(Each CAN Controller)       */
/*--------------------------------------------------------------*/
#define CAN_CFG_TX_FIFO_0_PAYLOAD_0     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_1     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_2     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_3     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_4     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_5     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_6     (8U)
#define CAN_CFG_TX_FIFO_0_PAYLOAD_7     (8U)


/*--------------------------------------------------------------*/
/* MBOX Number linked to TRX FIFO 0 for TX(Each CAN Controller) */
/*--------------------------------------------------------------*/
#define CAN_CFG_TX_FIFO_0_LINK_0        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_1        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_2        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_3        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_4        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_5        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_6        (255U)
#define CAN_CFG_TX_FIFO_0_LINK_7        (255U)


/*--------------------------------------------------------------*/
/* Payload Size of TRX FIFO 1 for TX(Each CAN Controller)       */
/*--------------------------------------------------------------*/
#define CAN_CFG_TX_FIFO_1_PAYLOAD_0     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_1     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_2     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_3     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_4     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_5     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_6     (8U)
#define CAN_CFG_TX_FIFO_1_PAYLOAD_7     (8U)


/*--------------------------------------------------------------*/
/* MBOX Number linked to TRX FIFO 1 for TX(Each CAN Controller) */
/*--------------------------------------------------------------*/
#define CAN_CFG_TX_FIFO_1_LINK_0        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_1        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_2        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_3        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_4        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_5        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_6        (255U)
#define CAN_CFG_TX_FIFO_1_LINK_7        (255U)


/*------------------------------------------------------------------*/
/* Payload Size of TRX FIFO 2 for Interrupt RX(Each CAN Controller) */
/*------------------------------------------------------------------*/
#define CAN_CFG_RXINT_FIFO_PAYLOAD_0    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_1    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_2    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_3    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_4    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_5    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_6    (8U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_7    (8U)


/*--------------------------------------------------------------*/
/* Depth of RX FIFO for Polling RX(Each CAN Controller)         */
/*--------------------------------------------------------------*/
#define CAN_CFG_RXPOL_FIFO_SIZE_0       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_1       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_2       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_3       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_4       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_5       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_6       (0U)
#define CAN_CFG_RXPOL_FIFO_SIZE_7       (0U)


/*--------------------------------------------------------------*/
/* Payload Size of RX FIFO for Polling RX(Each CAN Controller)  */
/*--------------------------------------------------------------*/
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_0    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_1    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_2    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_3    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_4    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_5    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_6    (8U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_7    (8U)


#endif  /* CAN_RSCF2_CFG_EXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-2-0         :2020/02/26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
