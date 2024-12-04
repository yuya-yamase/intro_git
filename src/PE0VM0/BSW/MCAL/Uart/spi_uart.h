/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : SPI UART Interface                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SPI_UART_H
#define SPI_UART_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_H_MAJOR                         (1)
#define SPI_UART_H_MINOR                         (0)
#define SPI_UART_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "spi_uart_channel.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LUOER_BIT_UTOE                  (0x00000001U)               /* Tx Enable                   */
#define SPI_UART_LUOER_BIT_UROE                  (0x00000002U)               /* Rx Enable                   */
#define SPI_UART_LUOER_BIT_PARAM                 (0x00000003U)

#define SPI_UART_LSC_BIT_IBS                     (0x00000030U)
#define SPI_UART_IBS_BIT_TB_0                    (0x00000000U)
#define SPI_UART_IBS_BIT_TB_1                    (0x00000010U)
#define SPI_UART_IBS_BIT_TB_2                    (0x00000020U)
#define SPI_UART_IBS_BIT_TB_3                    (0x00000030U)
#define SPI_UART_LSC_BIT_PARAM                   (0x00000030U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_SpiUartStart(const U1 u1_a_SPI_UART_CH, const U4 u4_a_START)                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_START_BIT_TXE                   (SPI_UART_LUOER_BIT_UTOE)   /* Tx Enable                   */
#define SPI_UART_START_BIT_RXE                   (SPI_UART_LUOER_BIT_UROE)   /* Rx Enable                   */

#define SPI_UART_START_BIT_IBS                   (SPI_UART_LSC_BIT_IBS)      /* Inter-Byte Space Select     */
#define SPI_UART_START_IBS_TB_0                  (SPI_UART_IBS_BIT_TB_0)
#define SPI_UART_START_IBS_TB_1                  (SPI_UART_IBS_BIT_TB_1)
#define SPI_UART_START_IBS_TB_2                  (SPI_UART_IBS_BIT_TB_2)
#define SPI_UART_START_IBS_TB_3                  (SPI_UART_IBS_BIT_TB_3)

#define SPI_UART_START_BIT_TXI                   (0x20000000U)               /* Transmission Interrupt      */
#define SPI_UART_START_BIT_RXI                   (0x40000000U)               /* Reception Interrupt         */
#define SPI_UART_START_BIT_STI                   (0x80000000U)               /* Status Interrupt            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_SpiUartEI(const U1 u1_a_SPI_UART_CH, const U4 u4_a_IRQEN)                                                           */
/*  U4      u4_g_SpiUartIRQenabled(const U1 u1_a_SPI_UART_CH)                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_IRQEN_BIT_TXE                   (SPI_UART_LUOER_BIT_UTOE)   /* Tx Enable                   */
#define SPI_UART_IRQEN_BIT_RXE                   (SPI_UART_LUOER_BIT_UROE)   /* Rx Enable                   */

#define SPI_UART_IRQEN_BIT_TXI                   (SPI_UART_START_BIT_TXI)    /* Transmission Interrupt      */
#define SPI_UART_IRQEN_BIT_RXI                   (SPI_UART_START_BIT_RXI)    /* Reception Interrupt         */
#define SPI_UART_IRQEN_BIT_STI                   (SPI_UART_START_BIT_STI)    /* Status Interrupt            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U4        u4_g_SpiUartIRQst(const U1 u1_a_SPI_UART_CH, const U4 u4_a_W_CLRBIT)                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_IRQST_BIT_OER                   (0x00000004U)               /* RLN3nLEST.OER               */

#define SPI_UART_IRQST_BIT_FER                   (0x00000008U)               /* RLN3nLEST.FER               */
#define SPI_UART_IRQST_BIT_UPER                  (0x00000040U)               /* RLN3nLEST.UPER              */

#define SPI_UART_IRQST_BIT_FTC                   (0x00000100U)               /* RLN3nLST.FTC                */
#define SPI_UART_IRQST_BIT_ERR                   (0x00000800U)               /* RLN3nLST.ERR                */
#define SPI_UART_IRQST_BIT_UTS                   (0x00001000U)               /* RLN3nLST.UTS                */
#define SPI_UART_IRQST_BIT_URS                   (0x00002000U)               /* RLN3nLST.URS                */

#define SPI_UART_IRQST_BIT_RTS                   (0x00020000U)               /* RLN3nLTRC.RTS               */

#define SPI_UART_IRQST_BIT_TXI                   (SPI_UART_IRQEN_BIT_TXI)    /* Transmission Interrupt      */
#define SPI_UART_IRQST_BIT_RXI                   (SPI_UART_IRQEN_BIT_RXI)    /* Reception Interrupt         */
#define SPI_UART_IRQST_BIT_STI                   (SPI_UART_IRQEN_BIT_STI)    /* Status Interrupt            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define vd_g_SpiUartDeInit()                     (vd_g_SpiUartInit())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_SpiUartInit(void);
/* void    vd_g_SpiUartDeInit(void); */

void    vd_g_SpiUartStart(const U1 u1_a_SPI_UART_CH, const U4 u4_a_START);
void    vd_g_SpiUartStop(const U1 u1_a_SPI_UART_CH);

U1      u1_g_SpiUartWriteTxByte(const U1 u1_a_SPI_UART_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX);
U1      u1_g_SpiUartReadRxByte(const U1 u1_a_SPI_UART_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX);

U4      u4_g_SpiUartIRQst(const U1 u1_a_SPI_UART_CH, const U4 u4_a_W_CLRBIT);
U4      u4_g_SpiUartIRQenabled(const U1 u1_a_SPI_UART_CH);

void    vd_g_SpiUartEI(const U1 u1_a_SPI_UART_CH, const U4 u4_a_IRQEN);
void    vd_g_SpiUartDI(const U1 u1_a_SPI_UART_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* SPI_UART_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see spi_uart.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
