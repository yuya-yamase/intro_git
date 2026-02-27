/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  General Purpose I2C Communication / Master                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_IF_C_MAJOR                     (1)
#define GP_I2C_MA_IF_C_MINOR                     (1)
#define GP_I2C_MA_IF_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma_cfg_private.h"
#include "gpi2c_ma_if.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GP_I2C_MA_IF_C_MAJOR != GP_I2C_MA_IF_H_MAJOR) || \
     (GP_I2C_MA_IF_C_MINOR != GP_I2C_MA_IF_H_MINOR) || \
     (GP_I2C_MA_IF_C_PATCH != GP_I2C_MA_IF_H_PATCH))
#error "gpi2c_ma_if.c and gpi2c_ma_if.h : source and header files are inconsistent!"
#endif

#if ((GP_I2C_MA_IF_C_MAJOR != GP_I2C_MA_CFG_H_MAJOR) || \
     (GP_I2C_MA_IF_C_MINOR != GP_I2C_MA_CFG_H_MINOR) || \
     (GP_I2C_MA_IF_C_PATCH != GP_I2C_MA_CFG_H_PATCH))
#error "gpi2c_ma_if.c and gpi2c_ma_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
static inline U4      u4_s_GpI2cMaIfDmaErrchk(const U1 u1_a_DMA_CH);
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4    u4_sp_GP_I2C_MA_IRQ_MASK[] = {
    (U4)0x00e0ff00U,        /* GP_I2C_MA_SEQ_STA (0U) */
    (U4)0x00e0bf00U,        /* GP_I2C_MA_SEQ_WRI (1U) */
    (U4)0x00e0ff00U,        /* GP_I2C_MA_SEQ_WEN (2U) */
    (U4)0x00e03f00U,        /* GP_I2C_MA_SEQ_REA (3U) */
    (U4)0x00e03f00U,        /* GP_I2C_MA_SEQ_RLA (4U) */
    (U4)0x00600800U         /* GP_I2C_MA_SEQ_FIN (5U) */
};
static const U4    u4_sp_GP_I2C_MA_IRQ_CRIT[] = {
    (U4)0x00e08400U,        /* GP_I2C_MA_SEQ_STA (0U) */
    (U4)0x00e08000U,        /* GP_I2C_MA_SEQ_WRI (1U) */
    (U4)0x00e0c000U,        /* GP_I2C_MA_SEQ_WEN (2U) */
    (U4)0x00c02000U,        /* GP_I2C_MA_SEQ_REA (3U) */
    (U4)0x00c02000U,        /* GP_I2C_MA_SEQ_RLA (4U) */
    (U4)0x00000800U         /* GP_I2C_MA_SEQ_FIN (5U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIfEnaCh(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 u1_a_PIN_ACT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIfEnaCh(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 u1_a_PIN_ACT)
{
    const ST_GP_I2C_MA_PIN *      st_tp_PIN;

    st_tp_PIN = st_ap_CH->stp_PIN;
    if((u1_a_PIN_ACT != (U1)FALSE ) &&
       (st_tp_PIN    != vdp_PTR_NA)){

        Port_SetPinMode(st_tp_PIN->u2_scl_pin, st_tp_PIN->u4_scl_ina);
        Port_SetPinMode(st_tp_PIN->u2_sda_pin, st_tp_PIN->u4_sda_ina);

        Port_SetPinMode(st_tp_PIN->u2_scl_pin, st_tp_PIN->u4_scl_act);
        Port_SetPinMode(st_tp_PIN->u2_sda_pin, st_tp_PIN->u4_sda_act);
    }

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        Dma_DisableTrans(st_ap_CH->u1_dma_ch);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    vd_g_I2cStart(st_ap_CH->u1_i2c_ch, (U4)I2C_RXA_ACKBT_BIT__ACK);
}
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIfDisCh(const ST_GP_I2C_MA_CH * st_ap_CH)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIfDisCh(const ST_GP_I2C_MA_CH * st_ap_CH)
{
    const ST_GP_I2C_MA_PIN *      st_tp_PIN;

    vd_g_I2cStop(st_ap_CH->u1_i2c_ch);

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        Dma_DisableTrans(st_ap_CH->u1_dma_ch);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    st_tp_PIN = st_ap_CH->stp_PIN;
    if(st_tp_PIN != vdp_PTR_NA){

        Port_SetPinMode(st_tp_PIN->u2_scl_pin, st_tp_PIN->u4_scl_ina);
        Port_SetPinMode(st_tp_PIN->u2_sda_pin, st_tp_PIN->u4_sda_ina);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIfResbyFrT(const ST_GP_I2C_MA_CH * st_ap_CH)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIfResbyFrT(const ST_GP_I2C_MA_CH * st_ap_CH)
{
    static const U1               u1_s_GP_I2C_MA_CLO_MAX = (U1)18U;    /* 18 bits, 2 bytes TRx             */

    const ST_GP_I2C_MA_PIN *      st_tp_PIN;

    vd_g_I2cDI(st_ap_CH->u1_i2c_ch);

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        Dma_DisableTrans(st_ap_CH->u1_dma_ch);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* ------------------------------------------------------------------------------------- */
    /* u1_g_I2cMasSynLost shall be always invoked pior to vd_g_I2cStart since I2C controller */
    /* reset is performed in vd_g_I2cStart and SCL synchronization lost can not be detected  */
    /* in u1_g_I2cMasSynLost.                                                                */
    /* ------------------------------------------------------------------------------------- */
    (void)u1_g_I2cMasSynLost(st_ap_CH->u1_i2c_ch, u1_s_GP_I2C_MA_CLO_MAX);

    st_tp_PIN = st_ap_CH->stp_PIN;
    if(st_tp_PIN != vdp_PTR_NA){

        Port_SetPinMode(st_tp_PIN->u2_scl_pin, st_tp_PIN->u4_scl_ina);
        Port_SetPinMode(st_tp_PIN->u2_sda_pin, st_tp_PIN->u4_sda_ina);

        Port_SetPinMode(st_tp_PIN->u2_scl_pin, st_tp_PIN->u4_scl_act);
        Port_SetPinMode(st_tp_PIN->u2_sda_pin, st_tp_PIN->u4_sda_act);
    }

    vd_g_I2cStart(st_ap_CH->u1_i2c_ch, (U4)I2C_RXA_ACKBT_BIT__ACK);
}
/*===================================================================================================================================*/
/*  U4      u4_g_GpI2cMaIfIRQst(const ST_GP_I2C_MA_CH * st_ap_CH, const U2 u2_a_SEQ)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_GpI2cMaIfIRQst(const ST_GP_I2C_MA_CH * st_ap_CH, const U2 u2_a_SEQ)
{
    U4                            u4_t_irq;
    U4                            u4_t_eas;

    u4_t_irq = u4_g_I2cIRQst(st_ap_CH->u1_i2c_ch, (U4)U4_MAX) & u4_sp_GP_I2C_MA_IRQ_MASK[u2_a_SEQ];
    if(u4_t_irq != u4_sp_GP_I2C_MA_IRQ_CRIT[u2_a_SEQ]){
        u4_t_eas = (U4)GP_I2C_MA_ERR_IRQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
    }
#if (GP_I2C_MA_RWC_DMA_WRI >= 2U)
    else if(u2_a_SEQ == (U2)GP_I2C_MA_SEQ_WEN){
        u4_t_eas = u4_s_GpI2cMaIfDmaErrchk(st_ap_CH->u1_dma_ch);
    }
#endif /* #if (GP_I2C_MA_RWC_DMA_WRI >= 2U) */
#if (GP_I2C_MA_RWC_DMA_REA >= 4U)
    else if(u2_a_SEQ == (U2)GP_I2C_MA_SEQ_REA){
        u4_t_eas = u4_s_GpI2cMaIfDmaErrchk(st_ap_CH->u1_dma_ch);
    }
#endif /* #if (GP_I2C_MA_RWC_DMA_REA >= 4U) */
    else{
        u4_t_eas = (U4)0U;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
#if (GP_I2C_MA_RWC_DMA_WRI >= 2U)
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIfDmaTxAct(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 * u1p_a_PDU_TX, const U2 u2_a_NBYTE)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIfDmaTxAct(const ST_GP_I2C_MA_CH * st_ap_CH, const U1 * u1p_a_PDU_TX, const U2 u2_a_NBYTE)
{
    static volatile U1 * const    u1p_sp_GP_I2C_MA_IF_DMA_TX[] = {
        (volatile U1 *)0xfff2203cU,      /* <RIIC0_base> FFF2 2000H P-Bus Group 7 / RIICnDRT: <RIICn_base> + 003CH */
        (volatile U1 *)0xfff2303cU       /* <RIIC1_base> FFF2 3000H P-Bus Group 7 / RIICnDRT: <RIICn_base> + 003CH */
    };

    Dma_SetTransMode(st_ap_CH->u1_dma_ch,                                                         /* t_u1ChDataID  */
                     u1DMA_TRANSSIZE_1,                                                           /* t_u1TransSize */
                     (U1)DMA_DMAMODE2,                                                            /* t_u1DmaMode   */
                     (volatile const void * )u1p_a_PDU_TX,                                        /* t_pcvdSrcAdr  */
                     (volatile const void * )u1p_sp_GP_I2C_MA_IF_DMA_TX[st_ap_CH->u1_i2c_ch],     /* t_pcvdDestAdr */
                     u2_a_NBYTE);                                                                 /* t_u2TransNum  */
    Dma_SetInterrupt(st_ap_CH->u1_dma_ch,
                     (U1)DMA_OFF,                                /* interrupt disabled */         /* t_u1HalfIe    */
                     (U1)DMA_OFF);                               /* interrupt disabled */         /* t_u1EndIe     */
    Dma_EnableTrans(st_ap_CH->u1_dma_ch);
}
#endif /* #if (GP_I2C_MA_RWC_DMA_WRI >= 2U) */
/*===================================================================================================================================*/
#if (GP_I2C_MA_RWC_DMA_REA >= 4U)
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIfDmaRxAct(const ST_GP_I2C_MA_CH * st_ap_CH, U1 * u1p_a_pdu_rx, const U2 u2_a_NBYTE)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIfDmaRxAct(const ST_GP_I2C_MA_CH * st_ap_CH, U1 * u1p_a_pdu_rx, const U2 u2_a_NBYTE)
{
    static volatile U1 * const    u1p_sp_GP_I2C_MA_IF_DMA_RX[] = {
        (volatile U1 *)0xfff22040U,      /* <RIIC0_base> FFF2 2000H P-Bus Group 7 / RIICnDRR: <RIICn_base> + 0040H */
        (volatile U1 *)0xfff23040U       /* <RIIC1_base> FFF2 3000H P-Bus Group 7 / RIICnDRR: <RIICn_base> + 0040H */
    };

    Dma_SetTransMode(st_ap_CH->u1_dma_ch,                                                         /* t_u1ChDataID  */
                     u1DMA_TRANSSIZE_1,                                                           /* t_u1TransSize */
                     (U1)DMA_DMAMODE1,                                                            /* t_u1DmaMode   */
                     (volatile const void * )u1p_sp_GP_I2C_MA_IF_DMA_RX[st_ap_CH->u1_i2c_ch],     /* t_pcvdSrcAdr  */
                     (volatile const void * )u1p_a_pdu_rx,                                        /* t_pcvdDestAdr */
                     u2_a_NBYTE);                                                                 /* t_u2TransNum  */
    Dma_SetInterrupt(st_ap_CH->u1_dma_ch,
                     (U1)DMA_OFF,                                /* interrupt disabled */         /* t_u1HalfIe    */
                     (U1)DMA_ON);                                /* interrupt enabled  */         /* t_u1EndIe     */
    Dma_EnableTrans(st_ap_CH->u1_dma_ch);
}
/*===================================================================================================================================*/
/*  U4      u4_g_GpI2cMaIfDmaRxchk(const ST_GP_I2C_MA_CH * st_ap_CH)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_GpI2cMaIfDmaRxchk(const ST_GP_I2C_MA_CH * st_ap_CH)
{
    static const U4               u4_s_GP_I2C_MA_DMA_CRIT = (U4)0x00c00000U;
    U4                            u4_t_irq;
    U4                            u4_t_eas;

    u4_t_irq = u4_g_I2cIRQst(st_ap_CH->u1_i2c_ch, (U4)U4_MAX) & u4_sp_GP_I2C_MA_IRQ_MASK[GP_I2C_MA_SEQ_REA];
    if(u4_t_irq == u4_s_GP_I2C_MA_DMA_CRIT){
        u4_t_eas = (U4)GP_I2C_MA_EAS_REA_RUN;
    }
    else if(u4_t_irq == u4_sp_GP_I2C_MA_IRQ_CRIT[GP_I2C_MA_SEQ_REA]){
        u4_t_eas = u4_s_GpI2cMaIfDmaErrchk(st_ap_CH->u1_dma_ch);
    }
    else{
        u4_t_eas = (U4)GP_I2C_MA_ERR_IRQ_UNK;
    }

    return(u4_t_eas);
}
#endif /* #if (GP_I2C_MA_RWC_DMA_REA >= 4U) */
/*===================================================================================================================================*/
#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
/*===================================================================================================================================*/
/*  static inline U4      u4_s_GpI2cMaIfDmaErrchk(const U1 u1_a_DMA_CH)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U4      u4_s_GpI2cMaIfDmaErrchk(const U1 u1_a_DMA_CH)
{
    U4                            u4_t_eas;
    U4                            u4_t_dma;

    if(u1_a_DMA_CH < u1_g_GP_I2C_MA_DMA_NUM_CH){

        u4_t_dma  = (U4)Dma_IsTransferCompleted(u1_a_DMA_CH) ^ (U4)TRUE;
        u4_t_dma |= (U4)Dma_CheckDmaError(u1_a_DMA_CH);
        Dma_ClearDmaError(u1_a_DMA_CH);
        if(u4_t_dma != (U4)0U){
            u4_t_eas = (U4)GP_I2C_MA_ERR_IRQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
        }
        else{
            u4_t_eas = (U4)0U;
        }
    }
    else{
        u4_t_eas = (U4)0U;
    }

    return(u4_t_eas);
}
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.1.0    10/10/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
