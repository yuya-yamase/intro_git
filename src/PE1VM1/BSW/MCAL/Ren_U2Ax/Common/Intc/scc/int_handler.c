/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : Interrupt Handler                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INT_HNDLR_C_MAJOR                        (1)
#define INT_HNDLR_C_MINOR                        (0)
#define INT_HNDLR_C_PATCH                        (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "int_handler_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((INT_HNDLR_C_MAJOR != INT_HNDLR_H_MAJOR) || \
     (INT_HNDLR_C_MINOR != INT_HNDLR_H_MINOR) || \
     (INT_HNDLR_C_PATCH != INT_HNDLR_H_PATCH))
#error "int_handler.c and int_handler.h : source and header files are inconsistent!"
#endif

#if ((INT_HNDLR_C_MAJOR != INT_HNDLR_CFG_H_MAJOR) || \
     (INT_HNDLR_C_MINOR != INT_HNDLR_CFG_H_MINOR) || \
     (INT_HNDLR_C_PATCH != INT_HNDLR_CFG_H_PATCH))
#error "int_handler.c and int_handler_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* EEICn Higher half-word */
#define INT_HNDLR_EICX_BIT_EICT                  (0x8000U)
#define INT_HNDLR_EICX_BIT_EIRF                  (0x1000U)
#define INT_HNDLR_EICX_BIT_EIMK                  (0x0080U)
#define INT_HNDLR_EICX_BIT_EITB                  (0x0040U)

#define INT_HNDLR_EICX_LSB_EIRF                  (12U)
#define INT_HNDLR_EICX_LSB_EIMK                  (7U)

/* EEICn Higher half-word, haigher byte */
#define INT_HNDLR_EICX_BYTE_BIT_EICT             (0x80U)
#define INT_HNDLR_EICX_BYTE_BIT_EIRF             (0x10U)

/* EEICn Lower half-word */
/* #define INT_HNDLR_EICX_BIT_EIOV               (0x8000U) */   /* not access */
/* #define INT_HNDLR_EICX_BIT_EIPX               (0x003fU) */   /* not access */

#if ((TRUE != 0x0001) || (FALSE != 0x0000))
#error "int_handler.c : TRUE/FALSE are NOT equal to TRUE(0x0001)/FALSE(0x0000)."
#endif

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
#define RH850_G4MH_SYNCP_WORD  /* static inline void  vd_s_SYNCP_W(const volatile U4 * const u4_ap_RDBK) */
#include "rh850_g4mh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_IntHndlrIRQCUpdt__D(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK);
static void    vd_s_IntHndlrIRQCUpdt__E(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK);
static void    vd_s_IntHndlrIRQCUpdt_CD(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK);
static void    vd_s_IntHndlrIRQCUpdt_CE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK);
static void    vd_s_IntHndlrIRQCUpdt_SE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*===================================================================================================================================*/

#pragma ghs section rodata=default

/*===================================================================================================================================*/
#define INT_HNDLR_INTC_1                         (0U)
#define INT_HNDLR_INTC_1_NUM_CH                  (32U)
#define INT_HNDLR_INTC_2                         (1U)
#define INT_HNDLR_INTC_2_NUM_CH                  (768U)

#define INT_HNDLR_EIC_HALF_LO                    (0U)
#define INT_HNDLR_EIC_HALF_HI                    (1U)

#define INT_HNDLR_EIC_BYTE_LO                    (0U)
#define INT_HNDLR_EIC_BYTE_HI                    (1U)
static volatile U4 * const u4p_sp_INT_HNDLR_RADDR_EEIC[] = {
    (volatile U4 *)0xfffc0200U,  /* INTC1 SELF : 00 -  31 ch. */
    (volatile U4 *)0xfff84000U   /* INTC2      : 32 - 767 ch. */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_IntHndlrIRQCtrlCh(const U2 u2_a_IRQ_CH, const U1 u1_a_CTRL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IntHndlrIRQCtrlCh(const U2 u2_a_IRQ_CH, const U1 u1_a_CTRL)
{
    static void ( * const       fp_sp_vd_INT_HNDLR_IRQC_UPDT[])(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK) = {
        &vd_s_IntHndlrIRQCUpdt__D, /* 000b */
        &vd_s_IntHndlrIRQCUpdt__E, /* 001b */
        &vd_s_IntHndlrIRQCUpdt_CD, /* 010b */
        &vd_s_IntHndlrIRQCUpdt_CE, /* 011b */
        &vd_s_IntHndlrIRQCUpdt__D, /* 100b */
        &vd_s_IntHndlrIRQCUpdt_SE, /* 101b */
        &vd_s_IntHndlrIRQCUpdt__D, /* 110b */
        &vd_s_IntHndlrIRQCUpdt__E  /* 111b */
    };

    volatile U4 *               u4_tp_eic_word;
    volatile U2 *               u2_tp_eic_ch;

    U2                          u2_t_back;
    U1                          u1_t_ctrl;

    if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_1_NUM_CH){
        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_1];
    }
    else if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_2_NUM_CH){
        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_2];
    }
    else{
        u4_tp_eic_word = (volatile U4 *)0U;
    }

    if(u4_tp_eic_word != (volatile U4 *)0U){

        /*----------------------------------------------------------*/
        /* Note:                                                    */
        /*                                                          */
        /* Write back the previous value of EEIC.EICT/EITB,         */
        /* because constant values are written in the interrupt     */
        /* initialization by the RTOS.                              */
        /*----------------------------------------------------------*/
        u2_tp_eic_ch = (volatile U2 *)(&u4_tp_eic_word[u2_a_IRQ_CH]);
        u2_t_back    = u2_REG_READ(u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI]);
        u1_t_ctrl    = u1_a_CTRL & ((U1)INT_HNDLR_IRQ_CTRL_CH_ENA |
                                    (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR |
                                    (U1)INT_HNDLR_IRQ_CTRL_RQ_SET);
        (*fp_sp_vd_INT_HNDLR_IRQC_UPDT[u1_t_ctrl])(&u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI], u2_t_back);
        vd_s_SYNCP_W(&u4_tp_eic_word[u2_a_IRQ_CH]);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_IntHndlrIRQst(const U2 u2_a_IRQ_CH, const U1 u1_a_W_CLR)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IntHndlrIRQst(const U2 u2_a_IRQ_CH, const U1 u1_a_W_CLR)
{
    volatile U4 *               u4_tp_eic_word;
    volatile U2 *               u2_tp_eic_ch;
    volatile U1 *               u1_tp_eic_byte;

    U2                          u2_t_irqst;
    U1                          u1_t_eict;

    if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_1_NUM_CH){

        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_1];
        u2_tp_eic_ch   = (volatile U2 *)(&u4_tp_eic_word[u2_a_IRQ_CH]);
        u2_t_irqst     = u2_REG_READ(u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI]) & (U2)INT_HNDLR_EICX_BIT_EIRF;
        if((u1_a_W_CLR == (U1)TRUE) &&
           (u2_t_irqst != (U2)0U  )){

            u1_tp_eic_byte = (volatile U1 *)&u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI];
            /*----------------------------------------------------------*/
            /* Note:                                                    */
            /*                                                          */
            /* Write back previous value of EEIC.EICT,                  */
            /* because initial values need to be written after reset.   */
            /*----------------------------------------------------------*/
            u1_t_eict = u1_REG_READ(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_HI]) & (U1)INT_HNDLR_EICX_BYTE_BIT_EICT;
            vd_REG_U1_WRITE(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_HI], u1_t_eict); /* EICx.EIRF is cleared */
            vd_s_SYNCP_W(&u4_tp_eic_word[u2_a_IRQ_CH]);
        }
        u2_t_irqst >>= INT_HNDLR_EICX_LSB_EIRF;
   }
    else if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_2_NUM_CH){

        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_2];
        u2_tp_eic_ch = (volatile U2 *)(&u4_tp_eic_word[u2_a_IRQ_CH]);
        u2_t_irqst     = u2_REG_READ(u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI]) & (U2)INT_HNDLR_EICX_BIT_EIRF;
        if((u1_a_W_CLR == (U1)TRUE) &&
           (u2_t_irqst != (U2)0U  )){

            u1_tp_eic_byte = (volatile U1 *)&u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI];

            /*----------------------------------------------------------*/
            /* Note:                                                    */
            /*                                                          */
            /* Write back previous value of EEIC.EICT,                  */
            /* because initial values need to be written after reset.   */
            /*----------------------------------------------------------*/
            u1_t_eict = u1_REG_READ(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_HI]) & (U1)INT_HNDLR_EICX_BYTE_BIT_EICT;
            vd_REG_U1_WRITE(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_HI], u1_t_eict); /* EICx.EIRF is cleared */
            vd_s_SYNCP_W(&u4_tp_eic_word[u2_a_IRQ_CH]);
        }
        u2_t_irqst >>= INT_HNDLR_EICX_LSB_EIRF;
    }
    else{
        u2_t_irqst = (U2)FALSE;
    }

    return((U1)u2_t_irqst);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IntHndlrIRQenabled(const U2 u2_a_IRQ_CH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IntHndlrIRQenabled(const U2 u2_a_IRQ_CH)
{
    volatile U4 *               u4_tp_eic_word;
    volatile U2 *               u2_tp_eic_ch;
    U2                          u2_t_ei;

    if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_1_NUM_CH){

        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_1];
        u2_tp_eic_ch   = (volatile U2 *)(&u4_tp_eic_word[u2_a_IRQ_CH]);
        u2_t_ei        = (u2_REG_READ(u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI]) ^ (U2)INT_HNDLR_EICX_BIT_EIMK);
        u2_t_ei        = (u2_t_ei & (U2)INT_HNDLR_EICX_BIT_EIMK) >> INT_HNDLR_EICX_LSB_EIMK;
    }
    else if(u2_a_IRQ_CH < (U2)INT_HNDLR_INTC_2_NUM_CH){

        u4_tp_eic_word = u4p_sp_INT_HNDLR_RADDR_EEIC[INT_HNDLR_INTC_2];
        u2_tp_eic_ch   = (volatile U2 *)(&u4_tp_eic_word[u2_a_IRQ_CH]);
        u2_t_ei        = (u2_REG_READ(u2_tp_eic_ch[INT_HNDLR_EIC_HALF_HI]) ^ (U2)INT_HNDLR_EICX_BIT_EIMK);
        u2_t_ei        = (u2_t_ei & (U2)INT_HNDLR_EICX_BIT_EIMK) >> INT_HNDLR_EICX_LSB_EIMK;
    }
    else{
        u2_t_ei        = (U2)FALSE;
    }

    return((U1)u2_t_ei);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IntHndlrIRQCUpdt__D(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IntHndlrIRQCUpdt__D(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)
{
    volatile U1 *               u1_tp_eic_byte;
    U1                          u1_t_eic_lo;

    u1_tp_eic_byte = (volatile U1 *)u2_ap_eic_half_ch;
    u1_t_eic_lo    = ((U1)u2_a_EIC_BACK & (U1)INT_HNDLR_EICX_BIT_EITB) | (U1)INT_HNDLR_EICX_BIT_EIMK;
    vd_REG_U1_WRITE(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_LO], u1_t_eic_lo);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IntHndlrIRQCUpdt__E(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IntHndlrIRQCUpdt__E(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)
{
    volatile U1 *               u1_tp_eic_byte;
    U1                          u1_t_eic_lo;

    u1_tp_eic_byte = (volatile U1 *)u2_ap_eic_half_ch;
    u1_t_eic_lo    = (U1)u2_a_EIC_BACK & (U1)INT_HNDLR_EICX_BIT_EITB;
    vd_REG_U1_WRITE(u1_tp_eic_byte[INT_HNDLR_EIC_BYTE_LO], u1_t_eic_lo);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IntHndlrIRQCUpdt_CD(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IntHndlrIRQCUpdt_CD(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)
{
    U2                          u2_t_eic;

    u2_t_eic = (u2_a_EIC_BACK & (U2)(INT_HNDLR_EICX_BIT_EICT | INT_HNDLR_EICX_BIT_EITB)) | (U2)INT_HNDLR_EICX_BIT_EIMK;
    vd_REG_U2_WRITE((*u2_ap_eic_half_ch), u2_t_eic);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IntHndlrIRQCUpdt_CE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IntHndlrIRQCUpdt_CE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)
{
    U2                          u2_t_eic;

    u2_t_eic = u2_a_EIC_BACK & (U2)(INT_HNDLR_EICX_BIT_EICT | INT_HNDLR_EICX_BIT_EITB);
    vd_REG_U2_WRITE((*u2_ap_eic_half_ch), u2_t_eic);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IntHndlrIRQCUpdt_SE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IntHndlrIRQCUpdt_SE(volatile U2 * u2_ap_eic_half_ch, const U2 u2_a_EIC_BACK)
{
    U2                          u2_t_eic;

    u2_t_eic = (u2_a_EIC_BACK & (U2)(INT_HNDLR_EICX_BIT_EICT | INT_HNDLR_EICX_BIT_EITB)) | (U2)INT_HNDLR_EICX_BIT_EIRF;
    vd_REG_U2_WRITE((*u2_ap_eic_half_ch), u2_t_eic);
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
/*  1.0.1     9/28/2023  YI       Bug Fix :  Unexpected access to reserved channels in vd_g_IntHndlrIRQInit/vd_g_IntHndlrIRQDeInit.  */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YI   = Yusuke Ichikawa, Denso Create                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
