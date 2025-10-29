/* can_rscf3c_cfg_ext_h_m10700_v3-0-0                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/CONFIG_EXT/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3C_CFG_EXT_H
#define     CAN_RSCF3C_CFG_EXT_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/********************************/
/* MCU Specific Configuration   */
/********************************/
/*------------------------------------------------------------------*/
/* CAN Baudrate Control Clock Source                                */
/*------------------------------------------------------------------*/
#define CAN_CFG_BAUDRATE_CLK_SOURCE     (CAN_CLK_CLKC)


/*------------------------------------------------------------------*/
/* Cycle Number of CAN RAM Initialization                           */
/*------------------------------------------------------------------*/
#define CAN_CFG_RAM_INIT_CYCLE          (19200UL)


/*------------------------------------------------------------------*/
/* Payload Overflow Mode Select                                     */
/*------------------------------------------------------------------*/
#define CAN_CFG_PAYLOAD_OVERFLOW_MODE   (CAN_PAYLOAD_OVERFLOW_NOTSTORED)


/*------------------------------------------------------------------*/
/* Payload Size of TRX FIFO 0 for Interrupt RX(Each CAN Controller) */
/*------------------------------------------------------------------*/
#define CAN_CFG_RXINT_FIFO_PAYLOAD_0    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_1    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_2    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_3    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_4    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_5    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_6    (64U)
#define CAN_CFG_RXINT_FIFO_PAYLOAD_7    (64U)


/*------------------------------------------------------------------*/
/* Depth of TRX FIFO 1 for Polling RX(Each CAN Controller)          */
/*------------------------------------------------------------------*/
#define CAN_CFG_RXPOL_FIFO_SIZE_0       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_1       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_2       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_3       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_4       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_5       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_6       (32U)
#define CAN_CFG_RXPOL_FIFO_SIZE_7       (32U)


/*------------------------------------------------------------------*/
/* Payload Size of TRX FIFO 1 for Polling RX(Each CAN Controller)   */
/*------------------------------------------------------------------*/
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_0    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_1    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_2    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_3    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_4    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_5    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_6    (64U)
#define CAN_CFG_RXPOL_FIFO_PAYLOAD_7    (64U)


#endif  /* CAN_RSCF3C_CFG_EXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
