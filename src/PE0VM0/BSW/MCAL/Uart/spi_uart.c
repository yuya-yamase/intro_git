/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : SPI UART Interface                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_C_MAJOR                         (1)
#define SPI_UART_C_MINOR                         (0)
#define SPI_UART_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "spi_uart_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SPI_UART_C_MAJOR != SPI_UART_H_MAJOR) || \
     (SPI_UART_C_MINOR != SPI_UART_H_MINOR) || \
     (SPI_UART_C_PATCH != SPI_UART_H_PATCH))
#error "spi_uart.c and spi_uart.h : source and header files are inconsistent!"
#endif

#if ((SPI_UART_C_MAJOR != SPI_UART_CFG_H_MAJOR) || \
     (SPI_UART_C_MINOR != SPI_UART_CFG_H_MINOR) || \
     (SPI_UART_C_PATCH != SPI_UART_CFG_H_PATCH))
#error "spi_uart.c and spi_uart_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_RO_BYTE_LWBR                    (0x0001U)      /* Addr Offset : 0x0001 */

#define SPI_UART_RO_HALF_LBRP                    (0x0002U >> 1) /* Addr Offset : 0x0002 */

#define SPI_UART_RO_BYTE_LMD                     (0x0008U)      /* Addr Offset : 0x0008 */
#define SPI_UART_RO_BYTE_LBFC                    (0x0009U)      /* Addr Offset : 0x0009 */
#define SPI_UART_RO_BYTE_LSC                     (0x000aU)      /* Addr Offset : 0x000A */
#define SPI_UART_RO_BYTE_LEDE                    (0x000dU)      /* Addr Offset : 0x000D */
#define SPI_UART_RO_BYTE_LCUC                    (0x000eU)      /* Addr Offset : 0x000E */
#define SPI_UART_RO_BYTE_LTRC                    (0x0010U)      /* Addr Offset : 0x0010 */
#define SPI_UART_RO_BYTE_LMST                    (0x0011U)      /* Addr Offset : 0x0011 */
#define SPI_UART_RO_BYTE_LST                     (0x0012U)      /* Addr Offset : 0x0012 */
#define SPI_UART_RO_BYTE_LEST                    (0x0013U)      /* Addr Offset : 0x0013 */
#define SPI_UART_RO_BYTE_LDFC                    (0x0014U)      /* Addr Offset : 0x0014 */
#define SPI_UART_RO_BYTE_LIDB                    (0x0015U)      /* Addr Offset : 0x0015 */
#define SPI_UART_RO_BYTE_LUDB0                   (0x0017U)      /* Addr Offset : 0x0017 */
#define SPI_UART_RO_BYTE_LDBR1                   (0x0018U)      /* Addr Offset : 0x0018 */
#define SPI_UART_RO_BYTE_LUOER                   (0x0020U)      /* Addr Offset : 0x0020 */
#define SPI_UART_RO_BYTE_LUOR1                   (0x0021U)      /* Addr Offset : 0x0021 */

#define SPI_UART_RO_HALF_LUTDR                   (0x0024U >> 1) /* Addr Offset : 0x0024 */

#define SPI_UART_RO_BYTE_LUTDR_LO                (0x0024U)      /* Addr Offset : 0x0024 */
#define SPI_UART_RO_BYTE_LUTDR_HI                (0x0025U)      /* Addr Offset : 0x0025 */

#define SPI_UART_RO_HALF_LURDR                   (0x0026U >> 1) /* Addr Offset : 0x0026 */
#define SPI_UART_RO_BYTE_LURDR_LO                (0x0026U)      /* Addr Offset : 0x0026 */
#define SPI_UART_RO_BYTE_LURDR_HI                (0x0027U)      /* Addr Offset : 0x0027 */

#define SPI_UART_RO_HALF_LUWTDR                  (0x0028U >> 1) /* Addr Offset : 0x0028 */
#define SPI_UART_RO_BYTE_LUWTDR_LO               (0x0028U)      /* Addr Offset : 0x0028 */
#define SPI_UART_RO_BYTE_LUWTDR_HI               (0x0029U)      /* Addr Offset : 0x0029 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LCUC_LINRST_ACT                 (0x00U)
#define SPI_UART_LCUC_LINRST_INACT               (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LST_BIT_IRQST                   (0x39U)
#define SPI_UART_LST_BIT_FTC                     (0x01U)
#define SPI_UART_LST_BIT_UTS                     (0x10U)

#define SPI_UART_LTRC_BIT_IRQST                  (0x02U)
#define SPI_UART_LTRC_BIT_RTS                    (0x02U)

#define SPI_UART_LEST_BIT_IRQST                  (0x4cU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_LDFC_MDL_MAX                    (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_IRQST_LSB_LST                   (8U)     /* UART_LST_BIT_IRQST(0x39)     -> (0x00003900)     */
#define SPI_UART_IRQST_LSB_LTRC                  (16U)    /* UART_LTRC_BIT_IRQST(0x02)    -> (0x00020000)     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SPI_UART_IRQ_LSB_ST                      (31U)
#define SPI_UART_IRQ_LSB_RX                      (30U)
#define SPI_UART_IRQ_LSB_TX                      (29U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1     u1_st;
    U1     u1_rx;
    U1     u1_tx;
}ST_SPI_UART_IRQEN;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U1    u1_s_SpiUartBufferTx(volatile U1 * const u1_ap_RBASE, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SpiUartInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SpiUartInit(void)
{
    const ST_SPI_UART_CH *     st_tp_CH;

    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    U4                         u4_t_ch;
    volatile U1                u1_t_rdbk;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_SPI_UART_NUM_CH; u4_t_ch++){

        st_tp_CH   = &st_gp_SPI_UART_CH_CFG[u4_t_ch];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LCUC], (U1)SPI_UART_LCUC_LINRST_ACT);
        u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LCUC]);
        __SYNCP();

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)0U);

        vd_g_IRQ_EI(u4_t_gli);

        vd_g_Gpt_BusyWait((U2)SPI_UART_MDSW_WAIT); /* Mode switching wait time */

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_SpiUartStart(const U1 u1_a_SPI_UART_CH, const U4  u4_a_START)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SpiUartStart(const U1 u1_a_SPI_UART_CH, const U4 u4_a_START)
{
    static const ST_SPI_UART_IRQEN    st_sp_SPI_UART_IRQ_STA[] = {
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR                                  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR                                  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR                                  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR,                                 /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR                                  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        }
    };

    const ST_SPI_UART_CH *     st_tp_CH;
    const ST_SPI_UART_IRQEN *  st_tp_EI;

    volatile U2 *              u2_tp_half;
    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    U4                         u4_t_irqen;
    U4                         u4_t_luoer;

    U2                         u2_t_cfg;

    volatile U1                u1_t_rdbk;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH   = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];

        u2_tp_half = (volatile U2 *)st_tp_CH->u4p_rbase;
        u1_tp_byte = (volatile U1 *)u2_tp_half;

        u4_t_gli = u4_g_IRQ_DI();

        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LCUC], (U1)SPI_UART_LCUC_LINRST_ACT);
        u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LCUC]);
        __SYNCP();

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

        vd_g_IRQ_EI(u4_t_gli);

        vd_g_Gpt_BusyWait((U2)SPI_UART_MDSW_WAIT);        /* Mode switching wait time */

        u2_t_cfg = (U2)st_tp_CH->u1_lwbr & (U2)SPI_UART_LWBR_BIT_CONST;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LWBR],  (U1)u2_t_cfg                  );

        vd_REG_U2_WRITE(u2_tp_half[SPI_UART_RO_HALF_LBRP], st_tp_CH->u2_lbrp);

        u2_t_cfg = (U2)st_tp_CH->u1_lbfc & (U2)SPI_UART_LBFC_BIT_CONST;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LBFC],  (U1)u2_t_cfg                  );

        u2_t_cfg = (U2)st_tp_CH->u1_lede & (U2)SPI_UART_LEDE_BIT_CONST;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LEDE],  (U1)u2_t_cfg                  );

        u2_t_cfg = (U2)st_tp_CH->u1_lmd_luor1 & (U2)SPI_UART_LUOR1_BIT_CONST;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LUOR1], (U1)u2_t_cfg                  );

        u2_t_cfg = (U2)u4_a_START & (U2)SPI_UART_START_BIT_IBS;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LSC],   (U1)u2_t_cfg                  );

        u2_t_cfg = ((U2)st_tp_CH->u1_lmd_luor1 & (U2)SPI_UART_LMD_BIT_CONST) | (U2)SPI_UART_LMD_BIT_UART;
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LMD],   (U1)u2_t_cfg                  );

        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LCUC],  (U1)SPI_UART_LCUC_LINRST_INACT);
        u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LCUC]);
        __SYNCP();

        vd_g_Gpt_BusyWait((U2)SPI_UART_MDSW_WAIT);         /* Mode switching wait time */

        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LIDB], (U1)0U);

        u4_t_irqen = u4_a_START >> SPI_UART_IRQ_LSB_TX;
        st_tp_EI   = &st_sp_SPI_UART_IRQ_STA[u4_t_irqen];
        u4_t_luoer = u4_a_START & (U4)SPI_UART_LUOER_BIT_PARAM;

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  st_tp_EI->u1_st);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  st_tp_EI->u1_rx);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  st_tp_EI->u1_tx);

        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LUOER], (U1)u4_t_luoer);
        u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LUOER]);
        __SYNCP();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_SpiUartStop(const U1 u1_a_SPI_UART_CH)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SpiUartStop(const U1 u1_a_SPI_UART_CH)
{
    const ST_SPI_UART_CH *     st_tp_CH;

    volatile U1 *              u1_tp_byte;
    volatile U4                u4_t_gli;

    volatile U1                u1_t_rdbk;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH   = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];
        u1_tp_byte = (volatile U1 *)st_tp_CH->u4p_rbase;

        u4_t_gli = u4_g_IRQ_DI();

        /* ------------------------------------------------------------------------------------ */
        /* LCUC.OM0 change from 1 to 0(LIN reset mode). will cause following effect.            */
        /*  1. LTRC.RTS   = 0b                                                                  */
        /*  2. LST.FTC    = 0b                                                                  */
        /*  3. LST.ERR    = 0b                                                                  */
        /*  4. LST.UTS    = 0b                                                                  */
        /*  5. LST.URS    = 0b                                                                  */
        /*  6. LEST.BER   = 0b                                                                  */
        /*  7. LEST.OER   = 0b                                                                  */
        /*  8. LEST.FER   = 0b                                                                  */
        /*  9. LEST.EXBT  = 0b                                                                  */
        /* 10. LEST.IDMT  = 0b                                                                  */
        /* 11. LEST.UPER  = 0b                                                                  */
        /* 12. LEST.UTOE  = 0b                                                                  */
        /* 13. LEST.UROE  = 0b                                                                  */
        /* ------------------------------------------------------------------------------------ */
        vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LCUC], (U1)SPI_UART_LCUC_LINRST_ACT);
        u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LCUC]);
        __SYNCP();

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)0U);

        vd_g_IRQ_EI(u4_t_gli);

        vd_g_Gpt_BusyWait((U2)SPI_UART_MDSW_WAIT);        /* Mode switching wait time */
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_SpiUartWriteTxByte(const U1 u1_a_SPI_UART_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SpiUartWriteTxByte(const U1 u1_a_SPI_UART_CH, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)
{
    volatile U1 *              u1_tp_byte;

    U1                         u1_t_ibs;
    U1                         u1_t_num_tx;
    volatile U1                u1_t_rdbk;

    if((u1_a_SPI_UART_CH <  u1_g_SPI_UART_NUM_CH) &&
       (u1_ap_TX         != vdp_PTR_NA          ) &&
       (u1_a_NUM_TX      >  (U1)0U              )){

        u1_tp_byte = (volatile U1 *)st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH].u4p_rbase;
        u1_t_ibs   = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LSC]) & (U1)SPI_UART_LSC_BIT_IBS;
        if(u1_t_ibs != (U1)SPI_UART_IBS_BIT_TB_0){
            u1_t_num_tx = u1_s_SpiUartBufferTx(u1_tp_byte, u1_ap_TX, u1_a_NUM_TX);
        }
        else{

            vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LUTDR_LO], *u1_ap_TX);
            u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LUTDR_LO]);
            __SYNCP();

            u1_t_num_tx = (U1)1U;
        }
    }
    else{
        u1_t_num_tx = (U1)0U;
    }

    return(u1_t_num_tx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_SpiUartReadRxByte(const U1 u1_a_SPI_UART_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX);                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SpiUartReadRxByte(const U1 u1_a_SPI_UART_CH, U1 * u1_ap_rx, const U1 u1_a_NUM_RX)
{
    volatile U1 *              u1_tp_byte;
    U1                         u1_t_num_rx;

    if((u1_a_SPI_UART_CH <  u1_g_SPI_UART_NUM_CH) &&
       (u1_ap_rx         != vdp_PTR_NA          ) &&
       (u1_a_NUM_RX      >  (U1)0U              )){

        u1_tp_byte  = (volatile U1 *)st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH].u4p_rbase;
        (*u1_ap_rx) = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LURDR_LO]);
        u1_t_num_rx = (U1)1U;
    }
    else{
        u1_t_num_rx = (U1)0U;
    }

    return(u1_t_num_rx);
}
/*===================================================================================================================================*/
/*  U4      u4_g_SpiUartIRQst(const U1 u1_a_SPI_UART_CH, const U4 u4_a_W_CLRBIT)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_SpiUartIRQst(const U1 u1_a_SPI_UART_CH, const U4 u4_a_W_CLRBIT)
{
    const ST_SPI_UART_CH *     st_tp_CH;

    volatile U1 *              u1_tp_byte;

    U4                         u4_t_irqbit;
    U4                         u4_t_irqclr;

    U1                         u1_t_lest;
    U1                         u1_t_lst;
    U1                         u1_t_ltrc;

    U1                         u1_t_irq_st;
    U1                         u1_t_irq_rx;
    U1                         u1_t_irq_tx;

    U1                         u1_t_sts_cr;
    volatile U1                u1_t_rdbk;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH    = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];
        u1_tp_byte  = (volatile U1 *)st_tp_CH->u4p_rbase;

     /* u4_t_irqclr = (u4_a_W_CLRBIT >> SPI_UART_IRQ_LSB_ST) & (U4)TRUE; QAC warning#2985 */
        u4_t_irqclr = u4_a_W_CLRBIT >> SPI_UART_IRQ_LSB_ST;
        u1_t_irq_st = u1_g_IntHndlrIRQst(st_tp_CH->u2_irq_er, (U1)u4_t_irqclr);

        u4_t_irqclr = (u4_a_W_CLRBIT >> SPI_UART_IRQ_LSB_RX) & (U4)TRUE;
        u1_t_irq_rx = u1_g_IntHndlrIRQst(st_tp_CH->u2_irq_rx, (U1)u4_t_irqclr);

        u4_t_irqclr = (u4_a_W_CLRBIT >> SPI_UART_IRQ_LSB_TX) & (U4)TRUE;
        u1_t_irq_tx = u1_g_IntHndlrIRQst(st_tp_CH->u2_irq_tx, (U1)u4_t_irqclr);

        u1_t_lest   = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LEST]) & (U1)SPI_UART_LEST_BIT_IRQST;
        u1_t_lst    = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LST])  & (U1)SPI_UART_LST_BIT_IRQST;
        u1_t_ltrc   = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LTRC]) & (U1)SPI_UART_LTRC_BIT_IRQST;

        u4_t_irqclr = u4_a_W_CLRBIT & (U4)SPI_UART_LEST_BIT_IRQST;
        if(u4_t_irqclr != (U4)0U){
            u1_t_sts_cr = (u1_t_lest & (U1)u4_t_irqclr) ^ (U1)SPI_UART_LEST_BIT_IRQST;
            vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LEST], u1_t_sts_cr);
            u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LEST]);
        }

        u4_t_irqclr = u4_a_W_CLRBIT & (U4)SPI_UART_IRQST_BIT_FTC;
        if(u4_t_irqclr != (U4)0U){
            u1_t_sts_cr = (u1_t_lst ^ (U1)U1_MAX) & (U1)SPI_UART_LST_BIT_FTC;
            vd_REG_U1_WRITE(u1_tp_byte[SPI_UART_RO_BYTE_LST], u1_t_sts_cr);
            u1_t_rdbk = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LST]);
        }
        __SYNCP();

        u4_t_irqbit  = (U4)u1_t_lest;
        u4_t_irqbit |= ((U4)u1_t_lst    << SPI_UART_IRQST_LSB_LST);
        u4_t_irqbit |= ((U4)u1_t_ltrc   << SPI_UART_IRQST_LSB_LTRC);
        u4_t_irqbit |= ((U4)u1_t_irq_st << SPI_UART_IRQ_LSB_ST);
        u4_t_irqbit |= ((U4)u1_t_irq_rx << SPI_UART_IRQ_LSB_RX);
        u4_t_irqbit |= ((U4)u1_t_irq_tx << SPI_UART_IRQ_LSB_TX);
    }
    else{
        u4_t_irqbit = (U4)0U;
    }

    return(u4_t_irqbit);
}
/*===================================================================================================================================*/
/*  U4      u4_g_SpiUartIRQenabled(const U1 u1_a_SPI_UART_CH)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_SpiUartIRQenabled(const U1 u1_a_SPI_UART_CH)
{
    const ST_SPI_UART_CH *     st_tp_CH;

    volatile U4                u4_t_gli;
    volatile U1 *              u1_tp_byte;

    U4                         u4_t_enabit;

    U1                         u1_t_irq_st;
    U1                         u1_t_irq_rx;
    U1                         u1_t_irq_tx;
    U1                         u1_t_urtoe;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH     = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];
        u1_tp_byte   = (volatile U1 *)st_tp_CH->u4p_rbase;

        u1_t_urtoe   = u1_REG_READ(u1_tp_byte[SPI_UART_RO_BYTE_LUOER]) & (U1)SPI_UART_LUOER_BIT_PARAM;
        u1_t_irq_st  = u1_g_IntHndlrIRQenabled(st_tp_CH->u2_irq_er);
        u1_t_irq_rx  = u1_g_IntHndlrIRQenabled(st_tp_CH->u2_irq_rx);
        u1_t_irq_tx  = u1_g_IntHndlrIRQenabled(st_tp_CH->u2_irq_tx);

        u4_t_enabit  = (U4)u1_t_urtoe;
        u4_t_enabit |= ((U4)u1_t_irq_st << SPI_UART_IRQ_LSB_ST);
        u4_t_enabit |= ((U4)u1_t_irq_rx << SPI_UART_IRQ_LSB_RX);
        u4_t_enabit |= ((U4)u1_t_irq_tx << SPI_UART_IRQ_LSB_TX);
    }
    else{
        u4_t_enabit = (U4)0U;
    }

    return(u4_t_enabit);
}
/*===================================================================================================================================*/
/*  void    vd_g_SpiUartEI(const U1 u1_a_SPI_UART_CH, const U4 u4_a_IRQEN)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SpiUartEI(const U1 u1_a_SPI_UART_CH, const U4 u4_a_IRQEN)
{
    static const ST_SPI_UART_IRQEN    st_sp_SPI_UART_IRQ_EI[] = {
        {
            (U1)0x00U,                     /* u1_st */
            (U1)0x00U,                     /* u1_rx */
            (U1)0x00U                      /* u1_tx */
        },
        {
            (U1)0x00U,                     /* u1_st */
            (U1)0x00U,                     /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)0x00U,                     /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)0x00U                      /* u1_tx */
        },
        {
            (U1)0x00U,                     /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)0x00U,                     /* u1_rx */
            (U1)0x00U                      /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)0x00U,                     /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)0x00U                      /* u1_tx */
        },
        {
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_st */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA, /* u1_rx */
            (U1)INT_HNDLR_IRQ_CTRL_CH_ENA  /* u1_tx */
        }
    };

    const ST_SPI_UART_CH *     st_tp_CH;
    const ST_SPI_UART_IRQEN *  st_tp_EI;

    volatile U4                u4_t_gli;
    U4                         u4_t_irqen;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH   = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];
        u4_t_irqen = u4_a_IRQEN >> SPI_UART_IRQ_LSB_TX;
        st_tp_EI   = &st_sp_SPI_UART_IRQ_EI[u4_t_irqen];

        u4_t_gli = u4_g_IRQ_DI();

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  st_tp_EI->u1_st);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  st_tp_EI->u1_rx);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  st_tp_EI->u1_tx);

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_SpiUartDI(const U1 u1_a_SPI_UART_CH)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SpiUartDI(const U1 u1_a_SPI_UART_CH)
{
    const ST_SPI_UART_CH *     st_tp_CH;
    volatile U4                u4_t_gli;

    if(u1_a_SPI_UART_CH < u1_g_SPI_UART_NUM_CH){

        st_tp_CH = &st_gp_SPI_UART_CH_CFG[u1_a_SPI_UART_CH];

        u4_t_gli = u4_g_IRQ_DI();

        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_er,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_rx,  (U1)0U);
        vd_g_IntHndlrIRQCtrlCh(st_tp_CH->u2_irq_tx,  (U1)0U);

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  static inline U1    u1_s_SpiUartBufferTx(volatile U1 * const u1_ap_RBASE, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1    u1_s_SpiUartBufferTx(volatile U1 * const u1_ap_RBASE, const U1 * u1_ap_TX, const U1 u1_a_NUM_TX)
{
    volatile U1 *               u1_tp_tx_byte;

    U4                          u4_t_txcnt;
    U4                          u4_t_num_tx;

    U1                          u1_t_rts;
    volatile U1                 u1_t_rdbk;

    u1_t_rts = u1_REG_READ(u1_ap_RBASE[SPI_UART_RO_BYTE_LTRC]) & (U1)SPI_UART_LTRC_BIT_RTS;
    if(u1_t_rts == (U1)0U){

        if(u1_a_NUM_TX >= (U1)SPI_UART_LDFC_MDL_MAX){
            u1_tp_tx_byte = &u1_ap_RBASE[SPI_UART_RO_BYTE_LUDB0];
            u4_t_num_tx   = (U4)SPI_UART_LDFC_MDL_MAX;
        }
        else{
            u1_tp_tx_byte = &u1_ap_RBASE[SPI_UART_RO_BYTE_LDBR1];
            u4_t_num_tx   = (U4)u1_a_NUM_TX;
        }

        u4_t_txcnt = (U4)0U;
        do{
            vd_REG_U1_WRITE(u1_tp_tx_byte[u4_t_txcnt], u1_ap_TX[u4_t_txcnt]);
            u4_t_txcnt++;
        }
        while(u4_t_txcnt < u4_t_num_tx);

        vd_REG_U1_WRITE(u1_ap_RBASE[SPI_UART_RO_BYTE_LDFC], (U1)u4_t_num_tx          );
        vd_REG_U1_WRITE(u1_ap_RBASE[SPI_UART_RO_BYTE_LTRC], (U1)SPI_UART_LTRC_BIT_RTS);
        u1_t_rdbk = u1_REG_READ(u1_ap_RBASE[SPI_UART_RO_BYTE_LTRC]);
        __SYNCP();
    }
    else{
        u4_t_num_tx = (U4)0U;
    }

    return((U1)u4_t_num_tx);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/20/2021  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO.                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
