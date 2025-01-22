/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : I2C Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef I2C_DRV_H
#define I2C_DRV_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_DRV_H_MAJOR                          (1)
#define I2C_DRV_H_MINOR                          (3)
#define I2C_DRV_H_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "i2c_drv_channel.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U1      u1_g_I2cMaReqSrscTx(const U1 u1_a_I2C_CH,const U1 u1_a_REQ)                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_MA_REQ_SRSC_STAR                     (0U)                       /* Master/Start Condition Tx                             */
#define I2C_MA_REQ_SRSC_REST                     (1U)                       /* Master/Restart Condition Tx                           */
#define I2C_MA_REQ_SRSC_STOP                     (2U)                       /* Master/Stop Condition Tx                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_I2cStart(const U1 u1_a_I2C_CH, const U4  u4_a_CTRL)                                                          */
/*  void    vd_g_I2cSetRxAck(const U1 u1_a_I2C_CH, const U1 u1_a_RXA)                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_RXA_ACKBT_BIT__ACK                   (0x00000000U)              /* MR3.ACKBT : 0b = ACK Tx                               */
#define I2C_RXA_ACKBT_BIT_NACK                   (0x00000008U)              /* MR3.ACKBT : 1b = NACK Tx                              */
#define I2C_RXA_RDRFS_BIT_CYC_9TH                (0x00000000U)              /* MR3.RDRFS : 0b = RDRF is set at rising edge of ninth  */
                                                                            /*                  cycle and SCL is NOT held low        */
#define I2C_RXA_RDRFS_BIT_CYC_8TH                (0x00000020U)              /* MR3.RDRFS : 1b = RDRF is set at rising edge of eigth  */
                                                                            /*                  cycle and SCL is held low            */

#define I2C_CTRL_BIT_RXA                         (0x00000028U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_I2cStart(const U1 u1_a_I2C_CH, const U4  u4_a_CTRL)                                                                 */
/*  void    vd_g_I2cEI(const U1 u1_a_I2C_CH, const U4 u4_a_IRQEN)                                                                    */
/*  U4      u4_g_I2cIRQenabled(const U1 u1_a_I2C_CH)                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_IRQEN_BIT_TOUT                       (0x00000100U)              /* RIICnIER.TMOIE                                        */
#define I2C_IRQEN_BIT_ALOS                       (0x00000200U)              /* RIICnIER.ALIE                                         */
#define I2C_IRQEN_BIT_STAR                       (0x00000400U)              /* RIICnIER.STIE                                         */
#define I2C_IRQEN_BIT_STOP                       (0x00000800U)              /* RIICnIER.SPIE                                         */
#define I2C_IRQEN_BIT_NACK                       (0x00001000U)              /* RIICnIER.NAKIE                                        */
#define I2C_IRQEN_BIT_RDRF                       (0x00002000U)              /* RIICnIER.RIE                                          */
#define I2C_IRQEN_BIT_TEND                       (0x00004000U)              /* RIICnIER.TEIE                                         */
#define I2C_IRQEN_BIT_TDRE                       (0x00008000U)              /* RIICnIER.TIE                                          */

#define I2C_CTRL_BIT_IRQEN                       (0x0000ff00U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U4        u4_g_I2cIRQst(const U1 u1_a_I2C_CH, const U4 u4_a_W_CLRBIT)                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_IRQST_BIT_AAS0                       (0x00000001U)              /* RIICnSR1.AAS0                                         */
#define I2C_IRQST_BIT_AAS1                       (0x00000002U)              /* RIICnSR1.AAS1                                         */
#define I2C_IRQST_BIT_AAS2                       (0x00000004U)              /* RIICnSR1.AAS2                                         */
#define I2C_IRQST_BIT_GCA                        (0x00000008U)              /* RIICnSR1.GCA                                          */
#define I2C_IRQST_BIT_DID                        (0x00000020U)              /* RIICnSR1.DID                                          */

#define I2C_IRQST_BIT_TOUT                       (0x00000100U)              /* RIICnSR2.TMOF                              : w/ CLR   */
#define I2C_IRQST_BIT_ALOS                       (0x00000200U)              /* RIICnSR2.AL                                : w/ CLR   */
#define I2C_IRQST_BIT_STAR                       (0x00000400U)              /* RIICnSR2.START                             : w/ CLR   */
#define I2C_IRQST_BIT_STOP                       (0x00000800U)              /* RIICnSR2.STOP                              : w/ CLR   */
#define I2C_IRQST_BIT_NACK                       (0x00001000U)              /* RIICnSR2.NACKF                             : w/ CLR   */
#define I2C_IRQST_BIT_RDRF                       (0x00002000U)              /* RIICnSR2.RDRF                                         */
#define I2C_IRQST_BIT_TEND                       (0x00004000U)              /* RIICnSR2.TEND                              : w/ CLR   */
#define I2C_IRQST_BIT_TDRE                       (0x00008000U)              /* RIICnSR2.TDRE                                         */

#define I2C_IRQST_BIT_RXFI                       (0x00010000U)              /* INTRIIC0RI/Rx Buffer Full  Interrupt       : w/ CLR   */
#define I2C_IRQST_BIT_TXEI                       (0x00020000U)              /* INTRIIC0TI/Tx Buffer Empty Interrupt       : w/ CLR   */

#define I2C_IRQST_BIT_TRS                        (0x00200000U)              /* RIICnCR2.TRS                                          */
#define I2C_IRQST_BIT_MST                        (0x00400000U)              /* RIICnCR2.MST                                          */
#define I2C_IRQST_BIT_BBSY                       (0x00800000U)              /* RIICnCR2.BBSY                                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define vd_g_I2cDeInit()                         (vd_g_I2cInit())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_I2cInit(void);
/* void    vd_g_I2cDeInit(void); */

void    vd_g_I2cStart(const U1 u1_a_I2C_CH, const U4 u4_a_CTRL);
void    vd_g_I2cStop(const U1 u1_a_I2C_CH);
                                                                               /* TRUE : request is accepted else Not      */
void    vd_g_I2cSetRxAck(const U1 u1_a_I2C_CH, const U4 u4_a_RXA);

U1      u1_g_I2cWriteTxByte(const U1 u1_a_I2C_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX);
U1      u1_g_I2cReadRxByte(const U1 u1_a_I2C_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX);

U4      u4_g_I2cIRQst(const U1 u1_a_I2C_CH, const U4 u4_a_W_CLRBIT);
U4      u4_g_I2cIRQenabled(const U1 u1_a_I2C_CH);

void    vd_g_I2cEI(const U1 u1_a_I2C_CH, const U4 u4_a_IRQEN);
void    vd_g_I2cDI(const U1 u1_a_I2C_CH);

/* ------------------------------------------------------------------------------------*/
/* Attention :                                                                         */
/* ------------------------------------------------------------------------------------*/
/* u1_g_I2cMaSynLost shall NOT be invoked/used ONLY IF I2C TRx timeout/bus lock is     */
/* detected.                                                                           */
/*                                                                                     */
/* If the return value of u1_g_I2cMaSynLost is equal to "TRUE", I2C controller reset   */
/* is being performed in it. Therefore, vd_g_I2cStart shall be invoked to restart I2C  */
/* TRx.                                                                                */
/* ------------------------------------------------------------------------------------*/
U1      u1_g_I2cMasReqSrscTx(const U1 u1_a_I2C_CH, const U1 u1_a_REQ);         /* Return = TRUE/FALSE                      */
U1      u1_g_I2cMasSynLost(const U1 u1_a_I2C_CH, const U1 u1_a_CLO_MAX);       /* Return = TRUE/FALSE                      */
                                                                               /* TRUE : SCL Synchronization Lost else Not */

/* ------------------------------------------------------------------------------------*/
/* Attention :                                                                         */
/* ------------------------------------------------------------------------------------*/
/* RH850/U2A-EVA Group UserÅfs Manual:                                                  */
/* Hardware Renesas microcontroller RH850 Family Rev.1.40 Aug. 2023                    */
/*                                                                                     */
/* 22.4.2.5 Slave Transmit Operation                                                   */
/*                                                                                     */
/* (5) When the RIICnSR2.NACKF flag or the RIICnSR2.TEND flag is 1, dummy read         */
/*     RIICnDRR to complete the processing. This releases the SCL line.                */
/*                                                                                     */
/* ------------------------------------------------------------------------------------*/
void    vd_g_I2cSlaFinTx(const U1 u1_a_I2C_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* I2C_DRV_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see i2c_drv.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
