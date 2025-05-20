/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : Input Caputure Wakeup Factor Detection                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_DRV_WK_C_MAJOR                       (1)
#define ICU_DRV_WK_C_MINOR                       (1)
#define ICU_DRV_WK_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "icu_drv_wk_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ICU_DRV_WK_C_MAJOR != ICU_DRV_WK_H_MAJOR) || \
     (ICU_DRV_WK_C_MINOR != ICU_DRV_WK_H_MINOR) || \
     (ICU_DRV_WK_C_PATCH != ICU_DRV_WK_H_PATCH))
#error "icu_drv_wk.c and icu_drv_wk.h : source and header files are inconsistent!"
#endif

#if ((ICU_DRV_WK_C_MAJOR != ICU_DRV_WK_CFG_H_MAJOR) || \
     (ICU_DRV_WK_C_MINOR != ICU_DRV_WK_CFG_H_MINOR) || \
     (ICU_DRV_WK_C_PATCH != ICU_DRV_WK_CFG_H_PATCH))
#error "icu_drv_wk.c and icu_drv_wk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_WK_RA_BASE                          (0xff98e000U)
#define ICU_WK_RO_REQ                           (0U)
#define ICU_WK_RO_MAS                           (1U)
#define ICU_WK_RO_CLR                           (2U)

#define ICU_WK_WID_WRQ                          (5U)
#define ICU_WK_LSB_WRQ                          (0x1fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_EL_RA_BASE                          (0xffed4600U)

#define ICU_EL_WID_CFG                          (5U)
#define ICU_EL_LSB_CFG                          (0x1fU)

#define ICU_EL_IRQ_BASE                         (544U)      /* Minimum IRQ Channel of INTPn = 544(INTP0) */

#define ICU_WK_LSB_IRQ                          (6U)

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
#define RH850_G4MH_SYNCP_WORD  /* static inline void  vd_s_SYNCP_W(const volatile U4 * const u4_ap_RDBK) */
#define RH850_G4MH_RDBK_BYTE   /* static inline void  vd_s_RDBK_B(const volatile U1 * const u1_ap_RDBK)  */
#define RH850_G4MH_RDBK_WORD   /* static inline void  vd_s_RDBK_W(const volatile U4 * const u4_ap_RDBK)  */
#include "rh850_g4mh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_IcuWkElInit(const ST_ICU_WK_GR * st_ap_GR, const U4 * u4_ap_ELC, const U4 u4_a_CLR);
static U4      u4_s_IcuWkElIRQst(const ST_ICU_WK_GR * st_ap_GR, const U4 u4_a_WRQ, const U1 u1_a_W_CLR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".ICU_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_IcuWkInit(const U1 u1_a_CFGID)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IcuWkInit(const U1 u1_a_CFGID)
{
    const U4 *               u4_tp_CFG;
    const U4 *               u4_tp_CLR;

    volatile U4 *            u4_tp_word;

    U4                       u4_tp_ini[ICU_WK_NUM_GR];
    U4                       u4_t_mask;
    U4                       u4_t_clr;
    U4                       u4_t_ra;
    U4                       u4_t_lpcnt;
    U4                       u4_t_coreid;

    u4_t_coreid = u4_g_GetCoreId();
    if (u4_t_coreid == (U4)BSW_CORE_ID_CORE0) {           /* Mask register only shall be updated in PE0 */
        if(u1_a_CFGID < u1_g_ICU_WK_NUM_CFG){

            u4_tp_CFG = &(st_gp_ICU_WK_CFG[u1_a_CFGID].u4p_elc[0]);
            u4_tp_CLR = &(st_gp_ICU_WK_CFG[u1_a_CFGID].u4p_clr[0]);

            u4_tp_ini[ICU_WK_GR_A0] = u4_s_IcuWkElInit(&st_gp_ICU_WK_GR[ICU_WK_GR_A0],
                                                              u4_tp_CFG,
                                                              u4_tp_CLR[ICU_WK_GR_A0]);
            u4_tp_ini[ICU_WK_GR_A1] = u4_s_IcuWkElInit(&st_gp_ICU_WK_GR[ICU_WK_GR_A1],
                                                              u4_tp_CFG,
                                                              u4_tp_CLR[ICU_WK_GR_A1]);
            u4_tp_ini[ICU_WK_GR_A2] = u4_tp_CLR[ICU_WK_GR_A2];

            u4_tp_CFG = &(st_gp_ICU_WK_CFG[u1_a_CFGID].u4p_ena[0]);
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ICU_WK_NUM_GR; u4_t_lpcnt++){

                u4_t_mask  = (u4_tp_CFG[u4_t_lpcnt] & st_gp_ICU_WK_GR[u4_t_lpcnt].u4_wrqbit) ^ (U4)U4_MAX;
                u4_t_clr   =  u4_tp_ini[u4_t_lpcnt] & st_gp_ICU_WK_GR[u4_t_lpcnt].u4_wrqbit;

                u4_t_ra    = (U4)st_gp_ICU_WK_GR[u4_t_lpcnt].u2_ro + (U4)ICU_WK_RA_BASE;
                u4_tp_word = (volatile U4 *)u4_t_ra; 
                vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_MAS], u4_t_mask);
                vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_CLR], u4_t_clr );
                vd_s_RDBK_W(&u4_tp_word[ICU_WK_RO_REQ]);
            }
        }

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ICU_WK_NUM_INVLD_GR; u4_t_lpcnt++){
            u4_tp_word = (volatile U4 *)st_gp_ICU_WK_INVLD_GR[u4_t_lpcnt].u4_raddr;
            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_MAS], (U4)U4_MAX                             );
            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_CLR], st_gp_ICU_WK_INVLD_GR[u4_t_lpcnt].u4_bit);
            vd_s_RDBK_W(&u4_tp_word[ICU_WK_RO_REQ]);
        }
        vd_s_SYNCP();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_IcuWkSetCh(const U1 u1_a_CH, const U1 u1_a_CFGBIT)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_IcuWkSetCh(const U1 u1_a_CH, const U1 u1_a_CFGBIT)
{
    volatile U4 *            u4_tp_word;
    volatile U1 *            u1_tp_byte;

    volatile U4              u4_t_gli;
    U4                       u4_t_wrqbit;
    U4                       u4_t_mask;
    U4                       u4_t_ra;
    U4                       u4_t_coreid;

    U2                       u2_t_irq_ch;

    U1                       u1_t_el;
    U1                       u1_t_las;
    U1                       u1_t_nex;
    U1                       u1_t_ena;
    U1                       u1_t_clr;
    U1                       u1_t_irq;

    if(u1_a_CH < (U1)ICU_WK_NUM_CH){

        u4_t_wrqbit = (U4)0x00000001U << (u1_a_CH & (U1)ICU_WK_LSB_WRQ);
        u4_t_ra     = (U4)u1_a_CH >> ICU_WK_WID_WRQ;

        u4_t_ra     = (U4)st_gp_ICU_WK_GR[u4_t_ra].u2_ro + (U4)ICU_WK_RA_BASE;
        u4_tp_word  = (volatile U4 *)u4_t_ra; 

        u1_t_ena    = u1_a_CFGBIT & (U1)ICU_WK_CFGBIT_WRQ_ENA;

        u4_t_coreid = u4_g_GetCoreId();
        if (u4_t_coreid == (U4)BSW_CORE_ID_CORE0) {           /* Mask register only shall be updated in PE0 */
            /* ---------------------------------------------------------------------- */
            /* Read/Modify/Write                                                      */
            /* ---------------------------------------------------------------------- */
            u4_t_gli = u4_g_IRQ_DI();

            u4_t_mask = u4_REG_READ(u4_tp_word[ICU_WK_RO_MAS]);
            if(u1_t_ena != (U1)0U){
                u4_t_mask &= ((U4)U4_MAX ^ u4_t_wrqbit);
            }
            else{
                u4_t_mask |= u4_t_wrqbit;
            }
            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_MAS],   u4_t_mask);
            vd_s_RDBK_W(&u4_tp_word[ICU_WK_RO_MAS]);

            vd_g_IRQ_EI(u4_t_gli);
            /* ---------------------------------------------------------------------- */
        }

        u1_t_clr = u1_a_CFGBIT & (U1)ICU_WK_CFGBIT_WRQ_CLR;
        u1_t_el  = u1_gp_ICU_EL_BY_WK[u1_a_CH];
        if(u1_t_el < u1_g_ICU_NUM_EL) {

            u4_t_ra    = (U4)st_gp_ICU_EL[u1_t_el].u2_ro + (U4)ICU_EL_RA_BASE;
            u1_tp_byte = (volatile U1 *)u4_t_ra;

         /* u1_t_irq   = (u1_a_CFGBIT >> ICU_WK_LSB_IRQ) & ((U1)INT_HNDLR_IRQ_CTRL_CH_ENA | INT_HNDLR_IRQ_CTRL_RQ_CLR); QAC warning#2985 */
            u1_t_irq   = (u1_a_CFGBIT >> ICU_WK_LSB_IRQ);
            u1_t_nex   = u1_a_CFGBIT & (U1)ICU_WK_CFGBIT_ELC;

            /* ---------------------------------------------------------------------- */
            /* Read/Modify/Write                                                      */
            /* ---------------------------------------------------------------------- */
            u4_t_gli = u4_g_IRQ_DI();

            u1_t_las = u1_REG_READ(*u1_tp_byte);
            if(u1_t_nex != u1_t_las){

                vd_REG_U1_WRITE(*u1_tp_byte, u1_t_nex);
                vd_s_RDBK_B(u1_tp_byte);

                u1_t_clr  = (U1)ICU_WK_CFGBIT_WRQ_CLR;
                u1_t_irq |= (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR;
            }
            u2_t_irq_ch = (U2)st_gp_ICU_EL[u1_t_el].u1_irq_off + (U2)ICU_EL_IRQ_BASE;
            vd_g_IntHndlrIRQCtrlCh(u2_t_irq_ch, u1_t_irq);

            vd_g_IRQ_EI(u4_t_gli);
            /* ---------------------------------------------------------------------- */
        }

        if(u1_t_clr != (U1)0U){

            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_CLR], u4_t_wrqbit);
            vd_s_SYNCP_W(&u4_tp_word[ICU_WK_RO_REQ]);
        }
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_IcuWkRQst(const U1 u1_a_GR, const U4 u4_a_WRQBIT, const U1 u1_a_W_CLR)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U4      u4_g_IcuWkRQst(const U1 u1_a_GR, const U4 u4_a_WRQBIT, const U1 u1_a_W_CLR)
{
    volatile U4 *            u4_tp_word;

    U4                       u4_t_erqbit;
    U4                       u4_t_wrqbit;
    U4                       u4_t_ra;

    if(u1_a_GR < (U1)ICU_WK_GR_A2){

        u4_t_erqbit = u4_s_IcuWkElIRQst(&st_gp_ICU_WK_GR[u1_a_GR], u4_a_WRQBIT, u1_a_W_CLR);

        u4_t_ra     = (U4)st_gp_ICU_WK_GR[u1_a_GR].u2_ro + (U4)ICU_WK_RA_BASE;
        u4_tp_word  = (volatile U4 *)u4_t_ra; 

        u4_t_wrqbit = u4_REG_READ(u4_tp_word[ICU_WK_RO_REQ]) & u4_a_WRQBIT;
        if(u1_a_W_CLR == (U1)TRUE){

            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_CLR], u4_t_wrqbit);
            vd_s_SYNCP_W(&u4_tp_word[ICU_WK_RO_REQ]);
        }
        u4_t_wrqbit |= u4_t_erqbit;
    }
    else if(u1_a_GR < (U1)ICU_WK_NUM_GR){

        u4_t_ra     = (U4)st_gp_ICU_WK_GR[u1_a_GR].u2_ro + (U4)ICU_WK_RA_BASE;
        u4_tp_word  = (volatile U4 *)u4_t_ra; 

        u4_t_wrqbit = u4_REG_READ(u4_tp_word[ICU_WK_RO_REQ]) & u4_a_WRQBIT;
        if(u1_a_W_CLR == (U1)TRUE){

            vd_REG_U4_WRITE(u4_tp_word[ICU_WK_RO_CLR], u4_t_wrqbit);
            vd_s_SYNCP_W(&u4_tp_word[ICU_WK_RO_REQ]);
        }
    }
    else{
        u4_t_wrqbit = (U4)0U;
    }

    return(u4_t_wrqbit);
}
/*===================================================================================================================================*/
/*  U4      u4_g_IcuWkRQenabled(const U1 u1_a_GR)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_IcuWkRQenabled(const U1 u1_a_GR)
{
    volatile U4 *            u4_tp_word;

    U4                       u4_t_ra;
    U4                       u4_t_ena;

    if(u1_a_GR < (U1)ICU_WK_NUM_GR){

        u4_t_ra    = (U4)st_gp_ICU_WK_GR[u1_a_GR].u2_ro + (U4)ICU_WK_RA_BASE;
        u4_tp_word = (volatile U4 *)u4_t_ra; 
        u4_t_ena   = u4_REG_READ(u4_tp_word[ICU_WK_RO_MAS]);
        u4_t_ena   = (u4_t_ena ^ (U4)U4_MAX) & st_gp_ICU_WK_GR[u1_a_GR].u4_wrqbit;
    }
    else{
        u4_t_ena   = (U4)0U;
    }

    return(u4_t_ena);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_IcuWkElInit(const ST_ICU_WK_GR * st_ap_GR, const U4 * u4_ap_ELC, const U4 u4_a_CLR)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_IcuWkElInit(const ST_ICU_WK_GR * st_ap_GR, const U4 * u4_ap_ELC, const U4 u4_a_CLR)
{
    const ST_ICU_EL *        st_tp_EL;
    volatile U1 *            u1_tp_byte;

    volatile U4              u4_t_gli;

    U4                       u4_t_num_el;
    U4                       u4_t_lpcnt;
    U4                       u4_t_wrqbit;
    U4                       u4_t_ini;
    U4                       u4_t_las;
    U4                       u4_t_nex;
    U4                       u4_t_clr;

    U2                       u2_t_irq_ch;

    U1                       u1_t_idx;
    U1                       u1_t_lsb;
    U2                       u2_t_ro;

    st_tp_EL    = st_ap_GR->stp_EL;
    u4_t_num_el = (U4)st_ap_GR->u2_num_el;
    u1_tp_byte  = (volatile U1 *)ICU_EL_RA_BASE;
    u4_t_ini    = u4_a_CLR;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_el; u4_t_lpcnt++){

        u1_t_idx    = st_tp_EL[u4_t_lpcnt].u1_clsb;
        u1_t_lsb    = u1_t_idx & (U1)ICU_EL_LSB_CFG;
        u1_t_idx    = u1_t_idx >> ICU_EL_WID_CFG;
        u4_t_nex    = (u4_ap_ELC[u1_t_idx] >> u1_t_lsb) & (U4)ICU_WK_CFGBIT_ELC;

        u4_t_wrqbit = st_tp_EL[u4_t_lpcnt].u4_wrqbit;
        u4_t_clr    = u4_t_ini & u4_t_wrqbit;
        u2_t_ro     = st_tp_EL[u4_t_lpcnt].u2_ro;

        /* ---------------------------------------------------------------------- */
        /* Read/Modify/Write                                                      */
        /* ---------------------------------------------------------------------- */
        u4_t_gli = u4_g_IRQ_DI();

        u4_t_las = (U4)u1_REG_READ(u1_tp_byte[u2_t_ro]);
        if(u4_t_las != u4_t_nex){

            vd_REG_U1_WRITE(u1_tp_byte[u2_t_ro], (U1)u4_t_nex);
            vd_s_RDBK_B(&u1_tp_byte[u2_t_ro]);

            u4_t_ini |= u4_t_wrqbit;
            u2_t_irq_ch = (U2)st_tp_EL[u4_t_lpcnt].u1_irq_off + (U2)ICU_EL_IRQ_BASE;
            vd_g_IntHndlrIRQCtrlCh(u2_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        }
        else if(u4_t_clr != (U4)0U){
            u2_t_irq_ch = (U2)st_tp_EL[u4_t_lpcnt].u1_irq_off + (U2)ICU_EL_IRQ_BASE;
            vd_g_IntHndlrIRQCtrlCh(u2_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        }
        else{
            /* do nothing */
        }

        vd_g_IRQ_EI(u4_t_gli);
        /* ---------------------------------------------------------------------- */
    }

    return(u4_t_ini);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_IcuWkElIRQst(const ST_ICU_WK_GR * st_ap_GR, const U4 u4_a_WRQ, const U1 u1_a_W_CLR)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_IcuWkElIRQst(const ST_ICU_WK_GR * st_ap_GR, const U4 u4_a_WRQ, const U1 u1_a_W_CLR)
{
    const ST_ICU_EL *        st_tp_EL;

    U4                       u4_t_num_el;
    U4                       u4_t_erqbit;
    U4                       u4_t_wrqbit;
    U4                       u4_t_lpcnt;
    U4                       u4_t_bit;

    U2                       u2_t_irq_ch;

    U1                       u1_t_irqst;

    st_tp_EL    = st_ap_GR->stp_EL;
    u4_t_num_el = (U4)st_ap_GR->u2_num_el;
    u4_t_erqbit = u4_a_WRQ & st_ap_GR->u4_erqbit;

    u4_t_wrqbit = (U4)0U;
    u4_t_lpcnt  = (U4)0U;
    while((u4_t_erqbit != (U4)0U     ) &&
          (u4_t_lpcnt  <  u4_t_num_el)){

        u4_t_bit = u4_t_erqbit & st_tp_EL[u4_t_lpcnt].u4_wrqbit;
        if(u4_t_bit != (U4)0U){

            u2_t_irq_ch = (U2)st_tp_EL[u4_t_lpcnt].u1_irq_off + (U2)ICU_EL_IRQ_BASE;
            u1_t_irqst = u1_g_IntHndlrIRQst(u2_t_irq_ch, u1_a_W_CLR);
            if(u1_t_irqst == (U1)TRUE){
                u4_t_wrqbit |= u4_t_bit;
            }
            u4_t_erqbit &= ((U4)U4_MAX ^ u4_t_bit);
        }
        u4_t_lpcnt++;
    }
  
    return(u4_t_wrqbit);
}

#pragma ghs section text=default

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/23/2021  TN       New                                                                                                */
/*  1.0.1     3/13/2023  KM       Bug Fix : WUFC. Write the value 0 to the bits to which wake-up factors are not assigned.           */
/*            7/20/2023  KM       QAC warning#2985 was fixed.                                                                        */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, Denso                                                                                                      */
/*  * KM = Kazuyuki Makino, DENSO.                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
