/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : SPI UART Interface                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SPI_UART_CFG_H
#define SPI_UART_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_CFG_H_MAJOR                     (1)
#define SPI_UART_CFG_H_MINOR                     (0)
#define SPI_UART_CFG_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

/* #include "mem_bar.h" */
#include "int_drv.h"
#include "int_handler.h"
#include "gpt_busywait.h"

#include "spi_uart.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LWBR_BIT_NSPB                   (0xf0U)  /* const                */
#define SPI_UART_LWBR_BIT_LPRS                   (0x0eU)  /* const                */
#define SPI_UART_LWBR_BIT_CONST                  (0xfeU)  /* const                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LMD_BIT_LRDNFS                  (0x20U)  /* const                */
#define SPI_UART_LMD_BIT_LMD                     (0x03U)
#define SPI_UART_LMD_BIT_UART                    (0x01U)
#define SPI_UART_LMD_BIT_CONST                   (0x20U)  /* const                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LBFC_BIT_UTPS                   (0x40U)  /* const                */
#define SPI_UART_LBFC_BIT_URPS                   (0x20U)  /* const                */
#define SPI_UART_LBFC_BIT_UPS                    (0x18U)  /* const                */
#define SPI_UART_LBFC_BIT_USBLS                  (0x04U)  /* const                */
#define SPI_UART_LBFC_BIT_UBOS                   (0x02U)  /* const                */
#define SPI_UART_LBFC_BIT_UBLS                   (0x01U)  /* const                */
#define SPI_UART_LBFC_BIT_CONST                  (0x7fU)  /* const                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LUOR1_BIT_UECD                  (0x10U)  /* const                */
#define SPI_UART_LUOR1_BIT_UTIGTS                (0x08U)  /* const                */
#define SPI_UART_LUOR1_BIT_UEBDCE                (0x04U)  /* const                */
#define SPI_UART_LUOR1_BIT_UEBDL                 (0x02U)  /* const                */
#define SPI_UART_LUOR1_BIT_UEBE                  (0x01U)  /* const                */
#define SPI_UART_LUOR1_BIT_CONST                 (0x08U)  /* const                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LEDE_BIT_FERE                   (0x08U)  /* const                */
#define SPI_UART_LEDE_BIT_OERE                   (0x04U)  /* const                */
#define SPI_UART_LEDE_BIT_BERE                   (0x01U)  /* const                */
#define SPI_UART_LEDE_BIT_CONST                  (0x0cU)  /* const                */

/* ----------------------------------------------------------------------------------------------------------------------------------*/
/* Attention :                                                                                                                       */
/* ----------------------------------------------------------------------------------------------------------------------------------*/
/* In order to stop and/or restart the operation, RLN3nLMST.bit.OMM0 shall be set to 0b(The module is in LIN reset mode) and         */
/* reset to 1b (The module is not in LIN reset mode). The duration, which RLN3nLMST.bit.OMM0 is switched 0b->1b vice versa, are      */
/* defined as following formula.                                                                                                     */
/*                                                                                                                                   */
/* 7 * LIN communication clock sources(CLK_RLIN)                                                                                     */
/*                                                                                                                                   */
/* The duration 500 [ns] is being designed considering on slowest clock configuration (MOSC = 16MHz,  CLK_RLIN = 2MHz)               */
/* Therefore, no need to change SPI_UART_MDSW_WAIT if clock configuration is equal or faster than above.                             */
/*                                                                                                                                   */
/* ----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_MDSW_WAIT                       (GPT_BUSY_WAIT_1_US * 4)  /* 4 [us] */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    volatile U4 *       u4p_rbase;

    U2                  u2_irq_er;      /* IRQ channel # of INTRLIN3nUR2/Status interrupt   */ 
    U2                  u2_irq_rx;      /* IRQ channel # of INTRLIN3nUR1/Rx interrupt       */ 
    U2                  u2_irq_tx;      /* IRQ channel # of INTRLIN3nUR0/Tx interrupt       */ 

    U2                  u2_lbrp;        /* RLN3nLBRP01 UART Baud Rate Prescaler 01 Register */

    U1                  u1_lwbr;        /* RLN3nLWBR   Wake-Up Baud Rate Select Register    */
    U1                  u1_lbfc;        /* RLN3nLBFC   UART Configuration Register          */
    U1                  u1_lmd_luor1;   /* RLN3nLMD    UART Mode Register                   */
                                        /* RLN3nLUOR1  UART Option Register 1               */
    U1                  u1_lede;        /* RLN3nLEDE   UART Error Detection Enable Register */
}ST_SPI_UART_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_SPI_UART_CH        st_gp_SPI_UART_CH_CFG[];
extern const U1                    u1_g_SPI_UART_NUM_CH;

#endif      /* SPI_UART_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see spi_uart.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
