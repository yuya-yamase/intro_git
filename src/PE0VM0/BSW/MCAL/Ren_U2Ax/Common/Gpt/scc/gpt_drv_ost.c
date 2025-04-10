/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : OS Timer                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_DRV_OST_C_MAJOR                      (1)
#define GPT_DRV_OST_C_MINOR                      (0)
#define GPT_DRV_OST_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_ost_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GPT_DRV_OST_C_MAJOR != GPT_DRV_OST_H_MAJOR) || \
     (GPT_DRV_OST_C_MINOR != GPT_DRV_OST_H_MINOR) || \
     (GPT_DRV_OST_C_PATCH != GPT_DRV_OST_H_PATCH))
#error "gpt_drv_ost.c and gpt_drv_ost.h : source and header files are inconsistent!"
#endif

#if ((GPT_DRV_OST_C_MAJOR != GPT_DRV_OST_CFG_H_MAJOR) || \
     (GPT_DRV_OST_C_MINOR != GPT_DRV_OST_CFG_H_MINOR) || \
     (GPT_DRV_OST_C_PATCH != GPT_DRV_OST_CFG_H_PATCH))
#error "gpt_drv_ost.c and gpt_drv_ost_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TRUE != 1) || (FALSE != 0))
#error "gpt_drv_ost.c : TRUE shall be "1" and FALSE shall be "0"."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_OST_RA_WORD_CMPR                     (0U)
#define GPT_OST_RA_WORD_CNTR                     (1U)

#define GPT_OST_RA_BYTE_TO                       (8U)
#define GPT_OST_RA_BYTE_TOE                      (12U)
#define GPT_OST_RA_BYTE_TE                       (16U)
#define GPT_OST_RA_BYTE_TS                       (20U)
#define GPT_OST_RA_BYTE_TT                       (24U)
#define GPT_OST_RA_BYTE_CTRL                     (32U)

#define GPT_OST_RA_HALF_SEL                      (96U)

#define GPT_OST_CTRL_BIT_FIELDS                  (0x87U)

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
#define RH850_G4MH_SYNCP       /* static inline void  vd_s_SYNCP(void)                                   */
#define RH850_G4MH_SYNCP_BYTE  /* static inline void  vd_s_SYNCP_B(const volatile U1 * const u1_ap_RDBK) */
#define RH850_G4MH_SYNCP_WORD  /* static inline void  vd_s_SYNCP_W(const volatile U4 * const u4_ap_RDBK) */
#define RH850_G4MH_RDBK_BYTE   /* static inline void  vd_s_RDBK_B(const volatile U1 * const u1_ap_RDBK)  */
#define RH850_G4MH_RDBK_WORD   /* static inline void  vd_s_RDBK_W(const volatile U4 * const u4_ap_RDBK)  */
#include "rh850_g4mh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline void    vd_s_Gpt_OstSetPeriod(volatile U4 * u4_ap_base, const U4 * u4_ap_START, const U4 u4_a_FRT_MD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstInit(void)
{
    volatile U4 *       u4_tp_word;
    volatile U2 *       u2_tp_half;
    volatile U1 *       u1_tp_byte;
    U4                  u4_t_ch;
    U4                  u4_t_tmr_ctrl;
    U4                  u4_t_select;
    U4                  u4_t_bit;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GPT_OST_NUM_CH; u4_t_ch++){

        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u4_t_ch].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

        u4_tp_word  = st_gp_GPT_OST_CFG[u4_t_ch].u4p_base;
        u1_tp_byte  = (volatile U1 *)u4_tp_word;

        u4_t_tmr_ctrl = (U4)st_gp_GPT_OST_CFG[u4_t_ch].u2_tmr_ctrl;
        u4_t_select   = (U4)st_gp_GPT_OST_CFG[u4_t_ch].u4_select;

        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TT],     (U1)TRUE                  );

        vd_REG_U4_WRITE(u4_tp_word[GPT_OST_RA_WORD_CMPR],   (U4)U4_MAX                );

        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TO],     (U1)FALSE                 );

        u4_t_bit = (u4_t_tmr_ctrl >> GPT_OST_TMR_CTRL_LSB_OUT_EN) & (U4)TRUE;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TOE],    (U1)u4_t_bit              );

        if(u4_t_select != (U4)U4_MAX){
            u2_tp_half  = (volatile U2 *)u4_tp_word;
            vd_REG_U2_WRITE(u2_tp_half[GPT_OST_RA_HALF_SEL],    (U2)u4_t_select       );
        }

        u4_t_bit = u4_t_tmr_ctrl & (U4)GPT_OST_CTRL_BIT_FIELDS;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_CTRL],   (U1)u4_t_bit              );
        vd_s_RDBK_B(&u1_tp_byte[GPT_OST_RA_BYTE_CTRL]);
    }
    vd_s_SYNCP();
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstDeInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstDeInit(void)
{
    volatile U1 *       u1_tp_byte;
    U4                  u4_t_ch;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GPT_OST_NUM_CH; u4_t_ch++){

        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u4_t_ch].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

        u1_tp_byte = (volatile U1 *)st_gp_GPT_OST_CFG[u4_t_ch].u4p_base;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TT],     (U1)TRUE    );
        vd_s_RDBK_B(&u1_tp_byte[GPT_OST_RA_BYTE_TE]);
    }
    vd_s_SYNCP();
}
/*===================================================================================================================================*/
/*  U4      u4_g_Gpt_OstGetTimeElapsed(const U1 u1_a_OST_CH, U4 * u4_ap_oststamp)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_Gpt_OstGetTimeElapsed(const U1 u1_a_OST_CH, U4 * u4_ap_oststamp)
{
    volatile U4 *       u4_tp_word;
    U4                  u4_t_elapsed;

    u4_t_elapsed = (U4)U4_MAX;
    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){

        u4_tp_word  = st_gp_GPT_OST_CFG[u1_a_OST_CH].u4p_base;
        u4_t_elapsed = u4_REG_READ(u4_tp_word[GPT_OST_RA_WORD_CNTR]);

        if(u4_ap_oststamp != vdp_PTR_NA){
            u4_ap_oststamp[GPT_OST_TMELPSD_CRRNT] = u4_t_elapsed;
            u4_t_elapsed -= u4_ap_oststamp[GPT_OST_TMELPSD_BASE];
        }
    }

    return(u4_t_elapsed);
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstStart(const U1 u1_a_OST_CH, const U4 * u4_ap_START)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstStart(const U1 u1_a_OST_CH, const U4 * u4_ap_START)
{
    volatile U4 *       u4_tp_word;
    volatile U1 *       u1_tp_byte;
    U4                  u4_t_period;
    U4                  u4_t_bit;
    U4                  u4_t_tmr_ctrl;
    volatile U1         u1_t_run;

    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){

        u4_tp_word = st_gp_GPT_OST_CFG[u1_a_OST_CH].u4p_base;
        u1_tp_byte = (volatile U1 *)u4_tp_word;

        u4_t_tmr_ctrl = (U4)st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_tmr_ctrl;

        u4_t_bit      = (U4)u1_REG_READ(u1_tp_byte[GPT_OST_RA_BYTE_CTRL]);
        u4_t_bit      = (u4_t_bit ^ u4_t_tmr_ctrl) & (U4)GPT_OST_TMR_CTRL_BIT_MD_FRT;
        u4_t_bit     |= (u4_ap_START[GPT_OST_START_CTRL] & (U4)GPT_OST_START_CTRL_BIT_TRG_ST);

        u1_t_run   = u1_REG_READ(u1_tp_byte[GPT_OST_RA_BYTE_TE]);
        if((u1_t_run == (U1)0U) ||
           (u4_t_bit != (U4)0U)){

            vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

            vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TT],     (U1)TRUE    );
            vd_s_SYNCP_B(&u1_tp_byte[GPT_OST_RA_BYTE_TE]);

            u4_t_bit = u4_t_tmr_ctrl & (U4)GPT_OST_TMR_CTRL_BIT_MD_FRT;
            if(u4_t_bit != (U4)0){
                u4_t_period = u4_ap_START[GPT_OST_START_PERIOD];
            }
            else{
                u4_t_period = u4_ap_START[GPT_OST_START_PERIOD] - (U4)1U;
            }

            vd_REG_U4_WRITE(u4_tp_word[GPT_OST_RA_WORD_CMPR],   u4_t_period);

            u4_t_bit = u4_t_tmr_ctrl & (U4)GPT_OST_CTRL_BIT_FIELDS;
            vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_CTRL],   (U1)u4_t_bit);

            u4_t_bit = u4_ap_START[GPT_OST_START_CTRL] & (U4)GPT_OST_START_CTRL_BIT_IRQ_EN;
            if(u4_t_bit != (U4)0U){
                vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch,
                                       (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }

            vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TS],     (U1)TRUE    );
            vd_s_SYNCP_B(&u1_tp_byte[GPT_OST_RA_BYTE_TE]);
        }
        else{

            u4_t_bit = u4_t_tmr_ctrl & (U4)GPT_OST_TMR_CTRL_BIT_MD_FRT;
            vd_s_Gpt_OstSetPeriod(u4_tp_word, u4_ap_START, u4_t_bit);

            u4_t_bit = u4_ap_START[GPT_OST_START_CTRL] & ((U4)GPT_OST_START_CTRL_BIT_IRQ_EN | (U4)GPT_OST_START_CTRL_BIT_IRQ_CL);
            if(u4_t_bit == ((U4)GPT_OST_START_CTRL_BIT_IRQ_EN | (U4)GPT_OST_START_CTRL_BIT_IRQ_CL)){
                vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch,
                                       (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else if(u4_t_bit == (U4)GPT_OST_START_CTRL_BIT_IRQ_EN){
                vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstStop(const U1 u1_a_OST_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstStop(const U1 u1_a_OST_CH)
{
    volatile U1 *       u1_tp_byte;
    volatile U1         u1_t_run;

    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){

        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)0x00U);

        u1_tp_byte = (volatile U1 *)st_gp_GPT_OST_CFG[u1_a_OST_CH].u4p_base;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_OST_RA_BYTE_TT],     (U1)TRUE    );
        vd_s_SYNCP_B(&u1_tp_byte[GPT_OST_RA_BYTE_TE]);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstEI(const U1 u1_a_OST_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstEI(const U1 u1_a_OST_CH)
{
    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){
        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_OstDI(const U1 u1_a_OST_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_OstDI(const U1 u1_a_OST_CH)
{
    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){
        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, (U1)0x00U);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_OstIRQst(const U1 u1_a_OST_CH, const U1 u1_a_W_CLR)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_OstIRQst(const U1 u1_a_OST_CH, const U1 u1_a_W_CLR)
{
    U1                  u1_t_irqst;

    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){
        u1_t_irqst = u1_g_IntHndlrIRQst(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch, u1_a_W_CLR);
    }
    else{
        u1_t_irqst = (U1)FALSE;
    }

    return(u1_t_irqst);
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_OstIRQenabled(const U1 u1_a_OST_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_OstIRQenabled(const U1 u1_a_OST_CH)
{
    volatile U1 *       u1_tp_byte;
    U1                  u1_t_irqen;

    if(u1_a_OST_CH < u1_g_GPT_OST_NUM_CH){

        u1_tp_byte = (volatile U1 *)st_gp_GPT_OST_CFG[u1_a_OST_CH].u4p_base;

        u1_t_irqen  = u1_g_IntHndlrIRQenabled(st_gp_GPT_OST_CFG[u1_a_OST_CH].u2_irq_ch);
        u1_t_irqen |= (U1)(u1_REG_READ(u1_tp_byte[GPT_OST_RA_BYTE_TE]) << 1);
    }
    else{
        u1_t_irqen = (U1)0x00U;
    }

    return(u1_t_irqen);
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_Gpt_OstSetPeriod(volatile U4 * u4_ap_base, const U4 * u4_ap_START, const U4 u4_a_FRT_MD)              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_Gpt_OstSetPeriod(volatile U4 * u4_ap_base, const U4 * u4_ap_START, const U4 u4_a_FRT_MD)
{
    volatile U4         u4_t_gli;
    U4                  u4_t_period;
    U4                  u4_t_ps;

    u4_t_ps = u4_ap_START[GPT_OST_START_CTRL] & (U4)GPT_OST_START_CTRL_BIT_PS;
    if(u4_a_FRT_MD == (U4)0U){

        u4_t_period = u4_ap_START[GPT_OST_START_PERIOD] - (U4)1U;
        vd_REG_U4_WRITE(u4_ap_base[GPT_OST_RA_WORD_CMPR],   u4_t_period);
        vd_s_SYNCP_W(&u4_ap_base[GPT_OST_RA_WORD_CMPR]);
    }
    else if(u4_t_ps == (U4)GPT_OST_START_CTRL_PS_CURR){

        u4_t_gli = u4_g_IRQ_DI();

        u4_t_period = u4_REG_READ(u4_ap_base[GPT_OST_RA_WORD_CNTR]) + u4_ap_START[GPT_OST_START_PERIOD];
        vd_REG_U4_WRITE(u4_ap_base[GPT_OST_RA_WORD_CMPR],   u4_t_period);
        vd_s_RDBK_W(&u4_ap_base[GPT_OST_RA_WORD_CMPR]);

        vd_g_IRQ_EI(u4_t_gli);
    }
    else if(u4_t_ps == (U4)GPT_OST_START_CTRL_PS_PREV){

        u4_t_gli = u4_g_IRQ_DI();

        u4_t_period = u4_REG_READ(u4_ap_base[GPT_OST_RA_WORD_CMPR]) + u4_ap_START[GPT_OST_START_PERIOD];
        vd_REG_U4_WRITE(u4_ap_base[GPT_OST_RA_WORD_CMPR],   u4_t_period);
        vd_s_RDBK_W(&u4_ap_base[GPT_OST_RA_WORD_CMPR]);

        vd_g_IRQ_EI(u4_t_gli);
    }
    else if(u4_t_ps == (U4)GPT_OST_START_CTRL_PS_ZERO){

        vd_REG_U4_WRITE(u4_ap_base[GPT_OST_RA_WORD_CMPR],   u4_ap_START[GPT_OST_START_PERIOD]);
        vd_s_SYNCP_W(&u4_ap_base[GPT_OST_RA_WORD_CMPR]);
    }
    else{
        /* do nothing */
    }
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
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
