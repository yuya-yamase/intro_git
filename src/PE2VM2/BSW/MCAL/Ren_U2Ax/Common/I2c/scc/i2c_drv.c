/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : I2C Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_DRV_C_MAJOR                          (1)
#define I2C_DRV_C_MINOR                          (4)
#define I2C_DRV_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "i2c_drv_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((I2C_DRV_C_MAJOR != I2C_DRV_H_MAJOR) || \
     (I2C_DRV_C_MINOR != I2C_DRV_H_MINOR) || \
     (I2C_DRV_C_PATCH != I2C_DRV_H_PATCH))
#error "i2c_drv.c and i2c_drv.h : source and header files are inconsistent!"
#endif

#if ((I2C_DRV_C_MAJOR != I2C_DRV_CFG_H_MAJOR) || \
     (I2C_DRV_C_MINOR != I2C_DRV_CFG_H_MINOR) || \
     (I2C_DRV_C_PATCH != I2C_DRV_CFG_H_PATCH))
#error "i2c_drv.c and i2c_drv_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/**+**  RIICn registers  *****/
#define I2C_RO_BYTE_CR1                          (0x0000U)      /* RIICn I2C Bus Control Register 1                    */
#define I2C_RO_BYTE_CR2                          (0x0004U)      /* RIICn I2C Bus Control Register 2                    */
#define I2C_RO_BYTE_MR1                          (0x0008U)      /* RIICn I2C Bus Mode Register 1                       */
#define I2C_RO_BYTE_MR2                          (0x000cU)      /* RIICn I2C Bus Mode Register 2                       */
#define I2C_RO_BYTE_MR3                          (0x0010U)      /* RIICn I2C Bus Mode Register 3                       */
#define I2C_RO_BYTE_FER                          (0x0014U)      /* RIICn I2C Bus Function Enable Register              */
#define I2C_RO_BYTE_SER                          (0x0018U)      /* RIICn I2C Bus Status Enable Register                */
#define I2C_RO_BYTE_IER                          (0x001cU)      /* RIICn I2C Bus Interrupt Enable Register             */
#define I2C_RO_BYTE_SR1                          (0x0020U)      /* RIICn I2C Bus Status Register 1 RIICnSR1            */
#define I2C_RO_BYTE_SR2                          (0x0024U)      /* RIICn I2C Bus Status Register 2                     */
#define I2C_RO_HALF_SAR0                         (0x0028U >> 1) /* RIICn I2C Slave Address Register 0                  */
#define I2C_RO_HALF_SAR1                         (0x002cU >> 1) /* RIICn I2C Slave Address Register 1                  */
#define I2C_RO_HALF_SAR2                         (0x0030U >> 1) /* RIICn I2C Slave Address Register 2                  */
#define I2C_RO_BYTE_BRL                          (0x0034U)      /* RIICn I2C Bus Bit Rate Low-Level Register           */
#define I2C_RO_BYTE_BRH                          (0x0038U)      /* RIICn I2C Bus Bit Rate High-Level Register          */
#define I2C_RO_BYTE_DRT                          (0x003cU)      /* RIICn I2C Bus Transmit Data Register                */
#define I2C_RO_BYTE_DRR                          (0x0040U)      /* RIICn I2C Bus Receive Data Register for word access */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_CR1_BIT_SDAI                         (0x01U)
#define I2C_CR1_BIT_SCLI                         (0x02U)
#define I2C_CR1_BIT_SDAO                         (0x04U)       /* 0b = low, 1b = released                              */
#define I2C_CR1_BIT_SCLO                         (0x08U)       /* 0b = low, 1b = released                              */
#define I2C_CR1_BIT_SOWP                         (0x10U)       /* 0b = SCLO/SDAO can be set, 1b = not                  */
#define I2C_CR1_BIT_CLO                          (0x20U)
#define I2C_CR1_BIT_IICRST                       (0x40U)       /* 0b = reset is inactive,    1b = reset is active      */
#define I2C_CR1_BIT_ICE                          (0x80U)       /* 0b = I2C is disabled,      1b = enabled              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* I2C is ENable or DIsable and ReSeT is ACTive or INActive */
#define I2C_CR1_DI_RST_ACT                       (0x50U)       /* ICE = 0b and IICRST = 1b and SOWP = 1b               */
#define I2C_CR1_EN_RST_ACT                       (0xd0U)       /* ICE = 1b and IICRST = 1b and SOWP = 1b               */
#define I2C_CR1_EN_RST_INA                       (0x90U)       /* ICE = 1b and IICRST = 0b and SOWP = 1b               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_CR1_CLO_RUN                          (0xb0U)       /* ICE = 1b and CLO    = 1b and SOWP = 1b               */
#define I2C_CR1_CL_LO_DA_LO                      (0x80U)       /* ICE = 1b and SOWP   = 0b and SCLO = 0b and SDAO = 0b */
#define I2C_CR1_CL_HI_DA_HI                      (0x8cU)       /* ICE = 1b and SOWP   = 0b and SCLO = 1b and SDAO = 1b */
#define I2C_CR1_CL_LO_DA_HI                      (0x84U)       /* ICE = 1b and SOWP   = 0b and SCLO = 0b and SDAO = 1b */
#define I2C_CR1_CL_HI_DA_LO                      (0x88U)       /* ICE = 1b and SOWP   = 0b and SCLO = 1b and SDAO = 0b */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_CR2_BIT_ST                           (0x02U)
#define I2C_CR2_BIT_RS                           (0x04U)
#define I2C_CR2_BIT_SP                           (0x08U)
#define I2C_CR2_BIT_TRS                          (0x20U)
#define I2C_CR2_BIT_MST                          (0x40U)
#define I2C_CR2_BIT_BBSY                         (0x80U)

#define I2C_CR2_LSB_MST                          (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_CR2_MD_CHK                           (0xe0U)      /* CR2.bit.BBSY, CR2.bit.MST, CR2.bit.TRS              */
#define I2C_CR2_SLA_TX                           (0xa0U)      /* CR2.bit.BBSY = 1, CR2.bit.MST = 0, CR2.bit.TRS = 1  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_MR1_BIT_MTWP                         (0x80U)
#define I2C_MR1_BIT_BCWP                         (0x08U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define I2C_MR3_BIT_ACKBT                        (0x08U) */
#define I2C_MR3_BIT_ACKWP                        (0x10U)
/* #define I2C_MR3_BIT_RDRFS                        (0x20U) */
#define I2C_MR3_BIT_WAIT                         (0x40U)

#define I2C_BRL_BIT_W1                           (0xe0U)
#define I2C_BRH_BIT_W1                           (0xe0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_SR2_BIT_TDRE                         (0x80U)
#define I2C_SR2_BIT_TEND                         (0x40U)
#define I2C_SR2_BIT_RDRF                         (0x20U)
#define I2C_SR2_BIT_NACK                         (0x10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_FER_BIT_NACKE                        (0x10U)
#define I2C_FER_BIT_AL_DI                        (0x70U)  /* Master/Slave Arbitration Lost are disabled    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_CR2_BIT_IRQST                        (0xe0U)
#define I2C_SR1_BIT_IRQST                        (0x2fU)
#define I2C_SR2_BIT_IRQST                        (0xffU)
#define I2C_SR2_BIT_W_CLR                        (0x5fU)
#define I2C_SR2_BIT_W_XOR                        (0x7fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_IRQST_LSB_SR2                        (8U)      /* I2C_SR2_BIT_IRQST (0xfe) -> (0x0000fe00)     */
#define I2C_IRQEN_LSB_IER                        (8U)
#define I2C_IRQST_LSB_CR2                        (16U)     /* I2C_CR2_BIT_IRQST (0xee) -> (0x00ee0000)     */
#define I2C_IRQEN_LSB_RDRF                       (13U)
#define I2C_IRQEN_LSB_TDRE                       (15U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_IRQST_LSB_RXFI                       (16U)
#define I2C_IRQST_LSB_TXEI                       (17U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_MA_SRSC_NUM_CR2                      (4U)      /* CR2.bit.BBSY, CR2.bit.MST                                          */
#define I2C_MA_SRSC_LSB_REQ                      (2U)
#define I2C_MA_SRSC_NUM_REQ                      (3U)      /* I2C_MA_REQ_SRSC_STAR (0U)                                          */
                                                           /* I2C_MA_REQ_SRSC_REST (1U)                                          */
                                                           /* I2C_MA_REQ_SRSC_STOP (2U)                                          */

#define I2C_MA_SRSC_BBSY_WA                      (0x02U)   /* I2C_MA_REQ_SRSC_STAR (0U) and CR2.bit.BBSY = 1 and CR2.bit.MST = 0 */

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
#define RH850_G4MH_SYNCP_BYTE  /* static inline void  vd_s_SYNCP_B(const volatile U1 * const u1_ap_RDBK) */
#define RH850_G4MH_RDBK_BYTE   /* static inline void  vd_s_RDBK_B(const volatile U1 * const u1_ap_RDBK)  */
#include "rh850_g4mh.h"

static void    vd_s_I2cMasResSla(volatile U1 * u1_ap_cr1, const U2 u2_a_BW_SCL);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".I2C_TEXT_CODE"
#pragma ghs section rodata=".I2C_RODATA_CONST"

/*===================================================================================================================================*/
/*  void    vd_g_I2cInit(void)                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cInit(void)
{
    const ST_I2C_CH *          st_tp_CH;

    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    U4                         u4_t_ch;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_I2C_NUM_CH; u4_t_ch++){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u4_t_ch];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_DI_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        /* ------------------------------------------------------------------------------------*/
        /* Attention :                                                                         */
        /* ------------------------------------------------------------------------------------*/
        /* Following IRQs factors are level type, not edge. Therefore, no need to clear IRQ    */
        /* Receive error/event interrupt (INTRIIC0LEE)                                         */
        /* Data transmitted interrupt (INTRIIC0TEI)                                            */
        /* ------------------------------------------------------------------------------------*/
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_ee,  (U1)0x00U                    );
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_te,  (U1)0x00U                    );

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cStart(const U1 u1_a_I2C_CH, const U4  u4_a_CTRL)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cStart(const U1 u1_a_I2C_CH, const U4 u4_a_CTRL)
{
    const ST_I2C_CH *          st_tp_CH;

    volatile U2 *              u2_tp_half;
    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    U4                         u4_t_irqen;

    U1                         u1_t_cfg;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];

        u2_tp_half = (volatile U2 *)st_tp_CH->u4p_rbase;
        u1_tp_byte = (volatile U1 *)u2_tp_half;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_DI_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        /* ------------------------------------------------------------------------------------*/
        /* Attention :                                                                         */
        /* ------------------------------------------------------------------------------------*/
        /* The interrupt requests INTRIICnTI and INTRIICnRI could not be synchronously and     */
        /* immidiately disabled with RIICnIER - I2C Bus Interrupt Enable Register = 0x00.      */
        /* Thus INTRIICnTI and INTRIICnRI are disabld with global DI/EI.                       */
        /* ------------------------------------------------------------------------------------*/
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_EN_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR0], st_tp_CH->u2_sar0 & (U2)I2C_SAR_BIT_CONST);
        vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR1], st_tp_CH->u2_sar1 & (U2)I2C_SAR_BIT_CONST);
        vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR2], st_tp_CH->u2_sar2 & (U2)I2C_SAR_BIT_CONST);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_SER],  st_tp_CH->u1_ser  & (U1)I2C_SER_BIT_CONST);

        u1_t_cfg  = (st_tp_CH->u1_mr1 & (U1)I2C_MR1_BIT_CONST) | (U1)I2C_MR1_BIT_BCWP;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR1],  u1_t_cfg);

        u1_t_cfg  = (st_tp_CH->u1_brl & (U1)I2C_BRL_BIT_CONST) | (U1)I2C_BRL_BIT_W1;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_BRL],  u1_t_cfg);

        u1_t_cfg  = (st_tp_CH->u1_brh & (U1)I2C_BRH_BIT_CONST) | (U1)I2C_BRH_BIT_W1;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_BRH],  u1_t_cfg);

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR2],  st_tp_CH->u1_mr2 & (U1)I2C_MR2_BIT_CONST);

        /* ------------------------------------------------------------------------------------*/
        /* Attention :                                                                         */
        /* ------------------------------------------------------------------------------------*/
        /* If it is attempted to write 1 to both ACKWP and ACKBT bits, the ACKBT bit cannot be */
        /* set to 1. Therefore, MR3 is written twice.                                          */
        /* ------------------------------------------------------------------------------------*/
        u1_t_cfg  = (st_tp_CH->u1_mr3 & (U1)I2C_MR3_BIT_CONST) | ((U1)I2C_MR3_BIT_ACKWP | (U1)I2C_MR3_BIT_WAIT);
        u1_t_cfg |= ((U1)u4_a_CTRL & (U1)I2C_CTRL_BIT_RXA);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR3],  u1_t_cfg);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR3],  u1_t_cfg);

        u1_t_cfg  = (st_tp_CH->u1_fer & (U1)I2C_FER_BIT_CONST) | (U1)I2C_FER_BIT_NACKE;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_FER],  u1_t_cfg);

        u1_t_cfg  = (U1)(u4_a_CTRL >> I2C_IRQEN_LSB_IER);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_IER],  u1_t_cfg);

#if (INT_HNDLR_IRQ_CTRL_CH_ENA != 0x01U)
#error "spi_i2c.c : INT_HNDLR_IRQ_CTRL_CH_ENA shall be equal to 0x01."
#endif
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_ee,  (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
        u4_t_irqen = (u4_a_CTRL >> I2C_IRQEN_LSB_RDRF) | (U4)INT_HNDLR_IRQ_CTRL_RQ_CLR;
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)u4_t_irqen);
        u4_t_irqen = (u4_a_CTRL >> I2C_IRQEN_LSB_TDRE) | (U4)INT_HNDLR_IRQ_CTRL_RQ_CLR;
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)u4_t_irqen);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_te,  (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_EN_RST_INA);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cStop(const U1 u1_a_I2C_CH)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cStop(const U1 u1_a_I2C_CH)
{
    const ST_I2C_CH *          st_tp_CH;

    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli = u4_g_IRQ_DI();
        /* ------------------------------------------------------------------------------------*/
        /* CR1.IICRST change from 0 to 1(Reset mode). will cause following effect.             */
        /*  1. RIICnCR1  = 0x5f                                                                */
        /*  2. RIICnCR2  = 0x00                                                                */
        /*  3. RIICnMR1  = 0x08                                                                */
        /*  4. RIICnMR2  = 0x06                                                                */
        /*  5. RIICnMR3  = 0x00                                                                */
        /*  6. RIICnFER  = 0x72                                                                */
        /*  7. RIICnSER  = 0x09                                                                */
        /*  8. RIICnIER  = 0x00                                                                */
        /*  9. RIICnSR1  = 0x00                                                                */
        /* 10. RIICnSR2  = 0x00                                                                */
        /* 11. RIICnSAR0 = 0x00                                                                */
        /* 12. RIICnSAR1 = 0x00                                                                */
        /* 13. RIICnSAR2 = 0x00                                                                */
        /* 14. RIICnBRH  = 0xff                                                                */
        /* 15. RIICnBRL  = 0xff                                                                */
        /* 16. RIICnDRT  = 0xff                                                                */
        /* 17. RIICnDRR  = 0x00                                                                */
        /* 18. RIICnDRS  = 0xff                                                                */
        /* ------------------------------------------------------------------------------------*/
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_DI_RST_ACT);
        vd_s_RDBK_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)0U);

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */
    }
}
/*===================================================================================================================================*/
/* void    vd_g_I2cSetRxAck(const U1 u1_a_I2C_CH, const U4 u4_a_RXA)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cSetRxAck(const U1 u1_a_I2C_CH, const U4 u4_a_RXA)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    U1                         u1_t_mr3;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH    = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte  = (volatile U1 *)st_tp_CH->u4p_rbase;

        u1_t_mr3    = (st_tp_CH->u1_mr3 & (U1)I2C_MR3_BIT_CONST) | ((U1)I2C_MR3_BIT_ACKWP | (U1)I2C_MR3_BIT_WAIT);
        u1_t_mr3   |= ((U1)u4_a_RXA & (U1)I2C_CTRL_BIT_RXA);

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR3],  u1_t_mr3);
        /* ------------------------------------------------------------------------------------*/
        /* Attention :                                                                         */
        /* ------------------------------------------------------------------------------------*/
        /* If it is attempted to write 1 to both ACKWP and ACKBT bits, the ACKBT bit cannot be */
        /* set to 1. Therefore, MR3 is written twice.                                          */
        /* ------------------------------------------------------------------------------------*/
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR3],  u1_t_mr3);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_MR3]);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_I2cWriteTxByte(const U1 u1_a_I2C_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_I2cWriteTxByte(const U1 u1_a_I2C_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)
{
    volatile U1 *              u1_tp_byte;

    U1                         u1_t_tdre;
    U1                         u1_t_num_tx;

    u1_t_num_tx = (U1)0U;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        u1_tp_byte = (volatile U1 *)st_gp_I2C_CH_CFG[u1_a_I2C_CH].u4p_rbase;

        u1_t_tdre  = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_SR2]) & (U1)I2C_SR2_BIT_TDRE;
        if(u1_t_tdre == (U1)0U){
         /* u1_t_num_tx = (U1)0U; */
        }
        else if(u1_ap_TX == vdp_PTR_NA){
            u1_t_num_tx = (U1)1U;
        }
        else if(u1_a_NUM_TX > (U1)0U){
            vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_DRT], *u1_ap_TX);
            u1_t_num_tx = (U1)1U;
        }
        else{
         /* u1_t_num_tx = (U1)0U; */
        }
    }

    return(u1_t_num_tx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_I2cReadRxByte(const U1 u1_a_I2C_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX);                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_I2cReadRxByte(const U1 u1_a_I2C_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    U1                         u1_t_num_rx;
    U1                         u1_t_rdrf;

    u1_t_num_rx = (U1)0U;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u1_t_rdrf  = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_SR2]) & (U1)I2C_SR2_BIT_RDRF;
        if(u1_t_rdrf == (U1)0U){
         /* u1_t_num_rx = (U1)0U; */
        }
        else if(u1_ap_rx == vdp_PTR_NA){
            u1_t_num_rx = (U1)1U;
        }
        else if(u1_a_NUM_RX > (U1)0U){
            *u1_ap_rx = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_DRR]);
            u1_t_num_rx = (U1)1U;
        }
        else{
         /* u1_t_num_rx = (U1)0U; */
        }
    }

    return(u1_t_num_rx);
}
/*===================================================================================================================================*/
/*  U4      u4_g_I2cIRQst(const U1 u1_a_I2C_CH, const U4 u4_a_W_CLRBIT)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_I2cIRQst(const U1 u1_a_I2C_CH, const U4 u4_a_W_CLRBIT)
{
    const ST_I2C_CH *          st_tp_CH;

    volatile U1 *              u1_tp_byte;

    U4                         u4_t_irqbit;
    U4                         u4_t_irqclr;

    U1                         u1_t_cr2;
    U1                         u1_t_sr1;
    U1                         u1_t_sr2;

    U1                         u1_t_irq_ti;
    U1                         u1_t_irq_ri;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH      = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte    = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_irqclr  = (u4_a_W_CLRBIT >> I2C_IRQST_LSB_TXEI) & (U4)TRUE;
        u1_t_irq_ti  = u1_g_IntHndlrIRQst(st_tp_CH->u2_irq_tx,  (U1)u4_t_irqclr);

        u4_t_irqclr  = (u4_a_W_CLRBIT >> I2C_IRQST_LSB_RXFI) & (U4)TRUE;
        u1_t_irq_ri  = u1_g_IntHndlrIRQst(st_tp_CH->u2_irq_rx,  (U1)u4_t_irqclr);

        u1_t_cr2     = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR2]) & (U1)I2C_CR2_BIT_IRQST;
        u1_t_sr1     = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_SR1]) & (U1)I2C_SR1_BIT_IRQST;
        u1_t_sr2     = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_SR2]) & (U1)I2C_SR2_BIT_IRQST;

        u4_t_irqclr  = (u4_a_W_CLRBIT >> I2C_IRQST_LSB_SR2) & (U4)I2C_SR2_BIT_W_CLR;
        u4_t_irqclr &= (U4)u1_t_sr2;
        if(u4_t_irqclr != (U4)0U){

            u4_t_irqclr ^= (U4)I2C_SR2_BIT_W_XOR;
            vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_SR2], (U1)u4_t_irqclr);
            vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_SR2]);
        }

        u4_t_irqbit  = (U4)u1_t_sr1;
        u4_t_irqbit |= ((U4)u1_t_sr2     << I2C_IRQST_LSB_SR2 );
        u4_t_irqbit |= ((U4)u1_t_cr2     << I2C_IRQST_LSB_CR2 );
        u4_t_irqbit |= ((U4)u1_t_irq_ri  << I2C_IRQST_LSB_RXFI);
        u4_t_irqbit |= ((U4)u1_t_irq_ti  << I2C_IRQST_LSB_TXEI);
    }
    else{
        u4_t_irqbit = (U4)0U;
    }

    return(u4_t_irqbit);
}
/*===================================================================================================================================*/
/*  U4      u4_g_I2cIRQenabled(const U1 u1_a_I2C_CH)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_I2cIRQenabled(const U1 u1_a_I2C_CH)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    U4                         u4_t_ena;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_ena   = (U4)u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_IER]) << I2C_IRQEN_LSB_IER;
    }
    else{
        u4_t_ena   = (U4)0U;
    }

    return(u4_t_ena);
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cEI(const U1 u1_a_I2C_CH, const U4 u4_a_IRQEN)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cEI(const U1 u1_a_I2C_CH, const U4 u4_a_IRQEN)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    volatile U4                u4_t_gli;
    U4                         u4_t_rec;
    U4                         u4_t_tra;
    U1                         u1_t_cfg;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

#if (INT_HNDLR_IRQ_CTRL_CH_ENA != 0x01U)
#error "spi_i2c.c : INT_HNDLR_IRQ_CTRL_CH_ENA shall be equal to 0x01."
#endif
        u1_t_cfg   = (U1)(u4_a_IRQEN >> I2C_IRQEN_LSB_IER);
        u4_t_rec   = (u4_a_IRQEN >> I2C_IRQEN_LSB_RDRF) & (U4)INT_HNDLR_IRQ_CTRL_CH_ENA;
        u4_t_tra   = (u4_a_IRQEN >> I2C_IRQEN_LSB_TDRE) & (U4)INT_HNDLR_IRQ_CTRL_CH_ENA;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_IER],  u1_t_cfg);
        vd_s_RDBK_B(&u1_tp_byte[I2C_RO_BYTE_IER]);

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)u4_t_rec);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)u4_t_tra);

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cDI(const U1 u1_a_I2C_CH)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cDI(const U1 u1_a_I2C_CH)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    volatile U4                u4_t_gli;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli   = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_IER],  (U1)0U);
        vd_s_RDBK_B(&u1_tp_byte[I2C_RO_BYTE_IER]);

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)0U);

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_I2cMasReqSrscTx(const U1 u1_a_I2C_CH, const U1 u1_a_REQ)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_I2cMasReqSrscTx(const U1 u1_a_I2C_CH, const U1 u1_a_REQ)
{
    static const U1            u1_sp_I2C_MA_SRSC_TX[I2C_MA_SRSC_NUM_REQ * I2C_MA_SRSC_NUM_CR2] = {
        /* I2C_MA_REQ_SRSC_STAR (0U) */
        (U1)I2C_CR2_BIT_ST,                   /* BBSY = 0, MST = 0 */
        (U1)I2C_CR2_BIT_ST,                   /* BBSY = 0, MST = 1 */
        (U1)0x00U,                            /* BBSY = 1, MST = 0 */
        (U1)0x00U,                            /* BBSY = 1, MST = 1 */

        /* I2C_MA_REQ_SRSC_REST (1U) */
        (U1)0x00U,                            /* BBSY = 0, MST = 0 */
        (U1)0x00U,                            /* BBSY = 0, MST = 1 */
        (U1)0x00U,                            /* BBSY = 1, MST = 0 */
        (U1)I2C_CR2_BIT_RS,                   /* BBSY = 1, MST = 1 */ /* CR2.bit.MST is protected since MR1.bit.MTWP is fixed with zero */

        /* I2C_MA_REQ_SRSC_STOP (2U) */
        (U1)0x00U,                            /* BBSY = 0, MST = 0 */
        (U1)0x00U,                            /* BBSY = 0, MST = 1 */
        (U1)0x00U,                            /* BBSY = 1, MST = 0 */
        (U1)I2C_CR2_BIT_SP                    /* BBSY = 1, MST = 1 */ /* CR2.bit.MST is protected since MR1.bit.MTWP is fixed with zero */
    };

    volatile U1 *              u1_tp_byte;

    U1                         u1_t_accpt;
    U1                         u1_t_req;
    U1                         u1_t_srsc;

    u1_t_accpt = (U1)FALSE;

    if((u1_a_I2C_CH < u1_g_I2C_NUM_CH        ) &&
       (u1_a_REQ    < (U1)I2C_MA_SRSC_NUM_REQ)){

        u1_tp_byte = (volatile U1 *)st_gp_I2C_CH_CFG[u1_a_I2C_CH].u4p_rbase;

        u1_t_req   = (U1)(u1_a_REQ << I2C_MA_SRSC_LSB_REQ);
        u1_t_srsc  = (u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR2]) >> I2C_CR2_LSB_MST) | u1_t_req;
        /* I2C_MA_REQ_SRSC_STAR (0U) and CR2.bit.BBSY = 1 and CR2.bit.MST = 0 */
        if(u1_t_req == (U1)I2C_MA_SRSC_BBSY_WA){

            /* ------------------------------------------------------------------------------------*/
            /* Attention :                                                                         */
            /* ------------------------------------------------------------------------------------*/
            /* RH850/U2A-EVA Group User's Manual: Hardware Renesas microcontroller RH850 Family    */
            /* 22.3.3 RIICnCR2 - I2C Bus Control Register 2                                        */
            /*                                                                                     */
            /* BBSY Flag (Bus Busy Detection)                                                      */
            /* [Clearing conditions]                                                               */
            /*  When the bus free time (specified in RIICnBRL) start condition is not detected     */
            /*  after detecting a Stop condition.                                                  */
            /*                                                                                     */
            /* BBSY = 1b->0b Senario:                                                              */
            /*  Start condition has NOT been detected during free-bus time which is specified by   */
            /*  RIICnBRL, since stop condition was detected.                                       */
            /*                                                                                     */
            /* Thus, vd_g_Gpt_BusyWait is being performed at here in order to wait BBSY = 1b->0b   */
            /* ------------------------------------------------------------------------------------*/
            vd_g_Gpt_BusyWait(st_gp_I2C_CH_CFG[u1_a_I2C_CH].u2_bw_scl);
            u1_t_srsc = (u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR2]) >> I2C_CR2_LSB_MST) | u1_t_req;
        }

        u1_t_srsc = u1_sp_I2C_MA_SRSC_TX[u1_t_srsc];
        if(u1_t_srsc == (U1)0x00U){
         /* u1_t_accpt = (U1)FALSE; */
        }
        else if(u1_t_srsc == (U1)I2C_CR2_BIT_SP){
            vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR2], u1_t_srsc);
            vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR2]);
            u1_t_accpt = (U1)TRUE;
        }
        else{
            vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_SR2], (U1)0x00U);
            vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR2], u1_t_srsc);
            vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR2]);
            u1_t_accpt = (U1)TRUE;
        }
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cMasReset(const U1 u1_a_I2C_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cMasReset(const U1 u1_a_I2C_CH)
{
    const ST_I2C_CH *          st_tp_CH;
    volatile U1 *              u1_tp_byte;

    volatile U4                u4_t_gli;
    U4                         u4_t_clo_cnt;
    U4                         u4_t_clo_max;
    U2                         u2_t_bw_scl;

    U1                         u1_t_sda;
    U1                         u1_t_cfg;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        st_tp_CH   = &st_gp_I2C_CH_CFG[u1_a_I2C_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_DI_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        /* ------------------------------------------------------------------------------------*/
        /* Attention :                                                                         */
        /* ------------------------------------------------------------------------------------*/
        /* The interrupt requests INTRIICnTI and INTRIICnRI could not be synchronously and     */
        /* immidiately disabled with RIICnIER - I2C Bus Interrupt Enable Register = 0x00.      */
        /* Thus INTRIICnTI and INTRIICnRI are disabld with global DI/EI.                       */
        /* ------------------------------------------------------------------------------------*/
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

        vd_g_IRQ_EI(u4_t_gli);                                    /* syncp insruction is performed at here           */

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_EN_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

     /* vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR0], st_tp_CH->u2_sar0 & (U2)I2C_SAR_BIT_CONST);  sar0 = 0x00 */
     /* vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR1], st_tp_CH->u2_sar1 & (U2)I2C_SAR_BIT_CONST);  sar1 = 0x00 */
     /* vd_REG_U2_WRITE(u2_tp_half[I2C_RO_HALF_SAR2], st_tp_CH->u2_sar2 & (U2)I2C_SAR_BIT_CONST);  sar2 = 0x00 */
     /* vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_SER],  st_tp_CH->u1_ser  & (U1)I2C_SER_BIT_CONST);  ser  = 0x09 */

        u1_t_cfg  = (st_tp_CH->u1_mr1 & (U1)I2C_MR1_BIT_CONST) | ((U1)I2C_MR1_BIT_BCWP | (U1)I2C_MR1_BIT_MTWP);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR1],  u1_t_cfg);

        u1_t_cfg  = (st_tp_CH->u1_brl & (U1)I2C_BRL_BIT_CONST) | (U1)I2C_BRL_BIT_W1;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_BRL],  u1_t_cfg);

        u1_t_cfg  = (st_tp_CH->u1_brh & (U1)I2C_BRH_BIT_CONST) | (U1)I2C_BRH_BIT_W1;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_BRH],  u1_t_cfg);

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR2],  st_tp_CH->u1_mr2 & (U1)I2C_MR2_BIT_CONST);

        u1_t_cfg  = st_tp_CH->u1_mr3 & (U1)I2C_MR3_BIT_CONST;
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_MR3],  u1_t_cfg);

     /* u1_t_cfg  = (st_tp_CH->u1_fer & (U1)I2C_FER_BIT_CONST) | (U1)I2C_FER_BIT_NACKE; */
     /* vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_FER],  u1_t_cfg); fer = 0x72             */
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_FER],  (U1)I2C_FER_BIT_AL_DI);

     /* u1_t_cfg  = (U1)(u4_a_CTRL >> I2C_IRQEN_LSB_IER); */
     /* vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_IER],  u1_t_cfg); ier = 0x00             */

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1],  (U1)I2C_CR1_EN_RST_INA);
        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR2],  (U1)I2C_CR2_BIT_MST);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

        u2_t_bw_scl = st_tp_CH->u2_bw_scl;
        u1_t_sda    = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR1]) & (U1)I2C_CR1_BIT_SDAI;
        if(u1_t_sda == (U1)I2C_CR1_BIT_SDAI){
            /* SCL = High/Low, SDA = High */
            /* If SCL is held low by a slave device, the master can do nothing to   */
            /* recover the bus. It must be considered to issue a reset or turn off  */
            /* then turn on the device by a physical pin.                           */ 
            /* If SCL is high, there is a possibility that a slave device is still  */
            /* in the process of sending data to the master. Such a condition will  */
            /* be reset by the next start condition, therefore no action is         */
            /* required at here.                                                    */
        }
        else{
            /* SCL = High/Low, SDA = Low */
            /* A slave device might be holding the SDA line low.    */
            /* Try to get a slave release SDA.                      */
            /* Note that this bus clear mechanism DOES NOT support  */
            /* the clock stretching.                                */
            u4_t_clo_cnt = (U4)0U;
            u4_t_clo_max = (U4)st_tp_CH->u1_clo_max;
            do{
                u4_t_clo_cnt++;

                /* SCL high -> low */
                /* Note: CR1.bit.CLO is NOT used intentionally.                     */
                /* It's because stop condition might NOT be generated since SCL     */
                /* is released and becomes high once BBSY becomes idle state(=0b).  */
                vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1],  (U1)I2C_CR1_CL_LO_DA_HI);
                vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);
                vd_g_Gpt_BusyWait(u2_t_bw_scl);

                /* Check whether SDA has been released (high) */
                u1_t_sda = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR1]) & (U1)I2C_CR1_BIT_SDAI;
                if(u1_t_sda == (U1)I2C_CR1_BIT_SDAI){
                    vd_s_I2cMasResSla(&u1_tp_byte[I2C_RO_BYTE_CR1], u2_t_bw_scl);
                    break;
                }
                else{
                    /* SCL low -> high */
                    vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1],  (U1)I2C_CR1_CL_HI_DA_HI);
                    vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);
                    vd_g_Gpt_BusyWait(u2_t_bw_scl);
                }
            }
            while(u4_t_clo_cnt < u4_t_clo_max);
        }

        vd_REG_U1_WRITE(u1_tp_byte[I2C_RO_BYTE_CR1], (U1)I2C_CR1_DI_RST_ACT);
        vd_s_SYNCP_B(&u1_tp_byte[I2C_RO_BYTE_CR1]);

    } /* if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){ */
}
/*===================================================================================================================================*/
/*  void    vd_g_I2cSlaFinTx(const U1 u1_a_I2C_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_I2cSlaFinTx(const U1 u1_a_I2C_CH)
{
    volatile U1 *              u1_tp_byte;
    U1                         u1_t_cr2;

    if(u1_a_I2C_CH < u1_g_I2C_NUM_CH){

        u1_tp_byte = (volatile U1 *)st_gp_I2C_CH_CFG[u1_a_I2C_CH].u4p_rbase;
        u1_t_cr2   = u1_REG_READ(u1_tp_byte[I2C_RO_BYTE_CR2]) & (U1)I2C_CR2_MD_CHK;
        if(u1_t_cr2 == (U1)I2C_CR2_SLA_TX){
            vd_s_RDBK_B(&u1_tp_byte[I2C_RO_BYTE_DRR]); /* DDR dummy read */
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_I2cMasResSla(volatile U1 * u1_ap_cr1, const U2 u2_a_BW_SCL)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_I2cMasResSla(volatile U1 * u1_ap_cr1, const U2 u2_a_BW_SCL)
{
    volatile U4                u4_t_gli;

    u4_t_gli = u4_g_IRQ_DI();

    /* Here SDA/SCL must be SDA=high, SCL=low */
    /* Stop Condition Tx */
    vd_REG_U1_WRITE((*u1_ap_cr1),  (U1)I2C_CR1_CL_LO_DA_LO);
    vd_s_SYNCP_B(u1_ap_cr1);

    vd_g_Gpt_BusyWait(u2_a_BW_SCL);

    vd_REG_U1_WRITE((*u1_ap_cr1),  (U1)I2C_CR1_CL_HI_DA_LO);
    vd_s_SYNCP_B(u1_ap_cr1);

    vd_g_Gpt_BusyWait(u2_a_BW_SCL);

    vd_REG_U1_WRITE((*u1_ap_cr1),  (U1)I2C_CR1_CL_HI_DA_HI);
    vd_s_SYNCP_B(u1_ap_cr1);

    vd_g_Gpt_BusyWait(u2_a_BW_SCL);

    vd_g_IRQ_EI(u4_t_gli);
}

#pragma ghs section rodata=default
#pragma ghs section text=default

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/17/2022  TN       New.                                                                                               */
/*  1.1.0    10/13/2022  TN       SPI_I2C_FER_BIT_TMOE and SPI_I2C_IER_BIT_TMOE were NOT configurabled.                              */
/*  1.1.1    30/ 1/2023  KM       QAC warning#2985 was fixed.                                                                        */
/*  1.2.0     4/ 7/2023  KM       vd_g_SpiI2cCloStart was implemented.                                                               */
/*                                u1_g_SpiI2cCloCheck was implemented.                                                               */
/*  1.3.0    10/11/2024  TN       vd_g_SpiI2cStart, vd_g_SpiI2cEI/DI was modified in order that IER can be configured.               */
/*                                The component name was changed from spi_i2c to i2c.                                                */
/*  1.4.0     2/ 5/2026  TN       u1_g_I2cMasSynLost -> vd_g_I2cMasReset.                                                            */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * KM   = Kazuyuki Makino, DENSO                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
