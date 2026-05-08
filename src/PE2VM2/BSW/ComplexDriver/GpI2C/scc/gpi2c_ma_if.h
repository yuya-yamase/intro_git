/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  General Purpose I2C Communication / Master                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef GP_I2C_MA_IF_H
#define GP_I2C_MA_IF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_IF_H_MAJOR                     (1)
#define GP_I2C_MA_IF_H_MINOR                     (1)
#define GP_I2C_MA_IF_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_frt.h"

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
#include "DMA.h"
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_g_GpI2cMaIfFrt()                      ((U2)((*u4p_g_GPT_FRT_RA) >> 10U))

#define vd_g_GpI2cMaIfTRxStart(ch)               ((void)u1_g_I2cMasReqSrscTx((ch)->u1_i2c_ch, (U1)I2C_MA_REQ_SRSC_STAR))
#define vd_g_GpI2cMaIfTRxRepeat(ch)              ((void)u1_g_I2cMasReqSrscTx((ch)->u1_i2c_ch, (U1)I2C_MA_REQ_SRSC_REST))
#define vd_g_GpI2cMaIfTRxFinish(ch)              ((void)u1_g_I2cMasReqSrscTx((ch)->u1_i2c_ch, (U1)I2C_MA_REQ_SRSC_STOP))

#define vd_g_GpI2cMaIfWriTx(ch, tx)              ((void)u1_g_I2cWriteTxByte((ch)->u1_i2c_ch, (tx), (U1)1U))
#define vd_g_GpI2cMaIfReaRx(ch, rx)              ((void)u1_g_I2cReadRxByte((ch)->u1_i2c_ch, (rx), (U1)1U))
#define vd_g_GpI2cMaIfResp_Ack(ch)               (vd_g_I2cSetRxAck((ch)->u1_i2c_ch, (U4)I2C_RXA_ACKBT_BIT__ACK))
#define vd_g_GpI2cMaIfRespNack(ch)               (vd_g_I2cSetRxAck((ch)->u1_i2c_ch, (U4)I2C_RXA_ACKBT_BIT_NACK))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_IF_SEQ_EI                      (0x00005e00U)      /* I2C_IRQEN_BIT_ALOS (0x00000200U) */
                                                                    /* I2C_IRQEN_BIT_STAR (0x00000400U) */
                                                                    /* I2C_IRQEN_BIT_STOP (0x00000800U) */
                                                                    /* I2C_IRQEN_BIT_NACK (0x00001000U) */
                                                                    /* I2C_IRQEN_BIT_RDRF               */
                                                                    /* I2C_IRQEN_BIT_TEND (0x00004000U) */
                                                                    /* I2C_IRQEN_BIT_TDRE               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_IF_REA_EI                      (0x00007e00U)      /* I2C_IRQEN_BIT_ALOS (0x00000200U) */
                                                                    /* I2C_IRQEN_BIT_STAR (0x00000400U) */
                                                                    /* I2C_IRQEN_BIT_STOP (0x00000800U) */
                                                                    /* I2C_IRQEN_BIT_NACK (0x00001000U) */
                                                                    /* I2C_IRQEN_BIT_RDRF (0x00002000U) */
                                                                    /* I2C_IRQEN_BIT_TEND (0x00004000U) */
                                                                    /* I2C_IRQEN_BIT_TDRE               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_IF_WRI_EI                      (0x0000de00U)      /* I2C_IRQEN_BIT_ALOS (0x00000200U) */
                                                                    /* I2C_IRQEN_BIT_STAR (0x00000400U) */
                                                                    /* I2C_IRQEN_BIT_STOP (0x00000800U) */
                                                                    /* I2C_IRQEN_BIT_NACK (0x00001000U) */
                                                                    /* I2C_IRQEN_BIT_RDRF               */
                                                                    /* I2C_IRQEN_BIT_TEND (0x00004000U) */
                                                                    /* I2C_IRQEN_BIT_TDRE (0x00008000U) */
#define vd_g_GpI2cMaIfIRQ_SeqEI(ch)              (vd_g_I2cEI((ch)->u1_i2c_ch, (U4)GP_I2C_MA_IF_SEQ_EI))
#define vd_g_GpI2cMaIfIRQ_ReaEI(ch)              (vd_g_I2cEI((ch)->u1_i2c_ch, (U4)GP_I2C_MA_IF_REA_EI))
#define vd_g_GpI2cMaIfIRQ_WriEI(ch)              (vd_g_I2cEI((ch)->u1_i2c_ch, (U4)GP_I2C_MA_IF_WRI_EI))
#define vd_g_GpI2cMaIfIRQ_DI(ch)                 (vd_g_I2cDI((ch)->u1_i2c_ch))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
#define vd_g_GpI2cMaIfDmaDeAct(ch)               (Dma_DisableTrans(st_ap_CH->u1_dma_ch))
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* U2      u2_g_GpI2cMaIfFrt(void); */

void    vd_g_GpI2cMaIfEnaCh(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 u1_a_RES_EN);
void    vd_g_GpI2cMaIfDisCh(const ST_GP_I2C_MA_CH * st_ap_CH);
void    vd_g_GpI2cMaIfResbyFrT(const ST_GP_I2C_MA_CH * st_ap_CH);                                    /* Reset by FrT : Frame Timeout */

/* void    vd_g_GpI2cMaIfStaTRx(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* void    vd_g_GpI2cMaIfWriTx(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 * u1_ap_BYTE_TX); */
/* void    vd_g_GpI2cMaIfReaRx(const ST_GP_I2C_MA_CH * st_ap_CH, U1 * u1_ap_byte_rx); */
/* void    vd_g_GpI2cMaIfFinTRx(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* void    vd_g_GpI2cMaIfResp_Ack(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* void    vd_g_GpI2cMaIfRespNack(const ST_GP_I2C_MA_CH * st_ap_CH); */

/* void    vd_g_GpI2cMaIfIRQ_SeqEI(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* void    vd_g_GpI2cMaIfIRQ_RwoEI(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* void    vd_g_GpI2cMaIfIRQ_DI(const ST_GP_I2C_MA_CH * st_ap_CH); */
U4      u4_g_GpI2cMaIfIRQst(const ST_GP_I2C_MA_CH * st_ap_CH, const U2 u2_a_SEQ);

#if (GP_I2C_MA_RWC_DMA_WRI >= 2U)
void    vd_g_GpI2cMaIfDmaTxAct(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 * u1p_a_PDU_TX, const U2 u2_a_NBYTE);
#endif /* #if (GP_I2C_MA_RWC_DMA_WRI >= 2U) */
#if (GP_I2C_MA_RWC_DMA_REA >= 4U)
void    vd_g_GpI2cMaIfDmaRxAct(const ST_GP_I2C_MA_CH * st_ap_CH, U1 * u1p_a_pdu_rx, const U2 u2_a_NBYTE);
U4      u4_g_GpI2cMaIfDmaRxchk(const ST_GP_I2C_MA_CH * st_ap_CH);
#endif /* #if (GP_I2C_MA_RWC_DMA_REA >= 4U) */

/* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */
/* void    vd_g_GpI2cMaIfDmaDeAct(const ST_GP_I2C_MA_CH * st_ap_CH); */
/* #endif */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* GP_I2C_MA_IF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  gpi2c_ma.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
