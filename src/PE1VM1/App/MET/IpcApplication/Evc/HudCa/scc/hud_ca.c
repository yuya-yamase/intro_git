/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* HUD Calibration                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HUD_CA_C_MAJOR                           (1)
#define HUD_CA_C_MINOR                           (0)
#define HUD_CA_C_PATCH                           (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hud_ca_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HUD_CA_C_MAJOR != HUD_CA_H_MAJOR) || \
     (HUD_CA_C_MINOR != HUD_CA_H_MINOR) || \
     (HUD_CA_C_PATCH != HUD_CA_H_PATCH))
#error "hud_ca.c and hud_ca.h : source and header files are inconsistent!"
#endif

#if ((HUD_CA_C_MAJOR != HUD_CA_CFG_H_MAJOR) || \
     (HUD_CA_C_MINOR != HUD_CA_CFG_H_MINOR) || \
     (HUD_CA_C_PATCH != HUD_CA_CFG_H_PATCH))
#error "hud_ca.c and hud_ca_cfg_private.h : source and header files are inconsistent!"
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
static S1      s1_sp_hud_ca_prm[HUD_CA_NUM_PRM];
static U1      u1_sp_hud_ca_dsr[HUD_CA_NUM_PRM];
static U1      u1_sp_hud_ca_syn[HUD_CA_NUM_PRM];

static U1      u1_s_hud_ca_prm_next;
static U1      u1_s_hud_ca_nvm_synen;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_HudCaSynNext(const U2 u2_a_NID, const S1 s1_a_NEXT);
static U1      u1_s_HudCaSynLast(const ST_HUD_CA * st_ap_CA, S1 * s1_ap_prm);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HudCaInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudCaInit(void)
{
    U4                   u4_t_lpcnt;
    U4                   u4_t_nvm_ca;

    U2                   u2_t_nid;

    S1                   s1_t_min;
    S1                   s1_t_max;
    S1                   s1_t_cal;

    U1                   u1_t_nvm_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)HUD_CA_NUM_PRM; u4_t_lpcnt++){

        u2_t_nid     = st_gp_HUD_CA[u4_t_lpcnt].u2_nid;
        s1_t_min     = st_gp_HUD_CA[u4_t_lpcnt].s1_min;
        s1_t_max     = st_gp_HUD_CA[u4_t_lpcnt].s1_max;

        u4_t_nvm_ca  = (U4)U4_MAX;
        u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_t_nid, &u4_t_nvm_ca);
        s1_t_cal     = (S1)((U1)u4_t_nvm_ca);
        if((u1_t_nvm_chk == (U1)NVMC_STATUS_KIND_OK) &&
           (u4_t_nvm_ca  <= (U4)U1_MAX             ) &&
           (s1_t_cal     >= s1_t_min               ) &&
           (s1_t_cal     <= s1_t_max               )){

            s1_sp_hud_ca_prm[u4_t_lpcnt] = s1_t_cal;
        }
        else{
            s1_sp_hud_ca_prm[u4_t_lpcnt] = (S1)0;
        }

        u1_sp_hud_ca_dsr[u4_t_lpcnt] = (U1)HUD_CA_DSR_INI;
        u1_sp_hud_ca_syn[u4_t_lpcnt] = (U1)HUD_CA_SYN_UNK;
    }
    u1_s_hud_ca_prm_next  = (U1)HUD_CA_NUM_PRM;
    u1_s_hud_ca_nvm_synen = (U1)TRUE;
}
/*===================================================================================================================================*/
/*  void    vd_g_HudCaMainTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HudCaMainTask(void)
{
    U4                   u4_t_lpcnt;
    U4                   u4_t_lpend;
    U4                   u4_t_next;

    U1                   u1_t_esi_chk;
    U1                   u1_t_syn;

    u1_t_esi_chk = u1_g_HudCaCfgEsichk() & ((U1)HUD_CA_ESI_SI_ACT | (U1)HUD_CA_ESI_NUO_DI);
    if(u1_t_esi_chk == (U1)0U){
        u1_s_hud_ca_nvm_synen = (U1)TRUE;
    }
    else{
        u1_s_hud_ca_nvm_synen = (U1)FALSE;
    }

    u4_t_lpcnt = (U4)u1_s_hud_ca_prm_next;
    if(u4_t_lpcnt >= (U4)U1_MAX){
        u4_t_lpcnt = (U4)HUD_CA_PRM_ROT;
        u4_t_lpend = (U4)HUD_CA_NUM_PRM;
    }
    else if(u4_t_lpcnt >= (U4)HUD_CA_NUM_PRM){
        u4_t_lpcnt = (U4)HUD_CA_PRM_ROT;
        u4_t_lpend = (U4)HUD_CA_PRM_TRA;
    }
    else{
        u4_t_lpend = u4_t_lpcnt + (U4)1U;
    }

    u4_t_next = u4_t_lpend;
    while(u4_t_lpcnt < u4_t_lpend){

        u1_t_syn = u1_sp_hud_ca_syn[u4_t_lpcnt];
        if(u1_t_syn == (U1)HUD_CA_SYN_REQ){

            u1_sp_hud_ca_syn[u4_t_lpcnt] = u1_s_HudCaSynNext(st_gp_HUD_CA[u4_t_lpcnt].u2_nid,
                                                             s1_sp_hud_ca_prm[u4_t_lpcnt]);
            u4_t_next                    = (U4)U1_MAX;
        }
        else if(u1_t_syn == (U1)HUD_CA_SYN_RUN){

            u1_sp_hud_ca_syn[u4_t_lpcnt] = u1_s_HudCaSynLast(&st_gp_HUD_CA[u4_t_lpcnt],
                                                             &s1_sp_hud_ca_prm[u4_t_lpcnt]);
            u4_t_next                    = (U4)U1_MAX;
        }
        else if(u1_s_hud_ca_nvm_synen != (U1)FALSE){

            (void)u1_s_HudCaSynLast(&st_gp_HUD_CA[u4_t_lpcnt], &s1_sp_hud_ca_prm[u4_t_lpcnt]);
        }
        else{
            /* Do nothing */
        }

        u4_t_lpcnt++;
    }

    u1_s_hud_ca_prm_next = (U1)u4_t_next;
}
/*===================================================================================================================================*/
/*  U1      u1_g_HudCaPrmSynchk(const U1 u1_a_PRM)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudCaPrmSynchk(const U1 u1_a_PRM)
{
    U1                   u1_t_syn;

    if(u1_a_PRM < (U1)HUD_CA_NUM_PRM){
        u1_t_syn = u1_sp_hud_ca_syn[u1_a_PRM];
    }
    else{
        u1_t_syn = (U1)HUD_CA_SYN_UNK;
    }

    return(u1_t_syn);
}
/*===================================================================================================================================*/
/*  S1      s1_g_HudCaPrmLast(const U1 u1_a_PRM, const U1 u1_a_DSR_RX)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
S1      s1_g_HudCaPrmLast(const U1 u1_a_PRM, const U1 u1_a_DSR_RX)
{
    S1                   s1_t_las;

    if(u1_a_PRM < (U1)HUD_CA_NUM_PRM){
        s1_t_las                   = s1_sp_hud_ca_prm[u1_a_PRM];
        u1_sp_hud_ca_dsr[u1_a_PRM] = u1_sp_hud_ca_dsr[u1_a_PRM] + (u1_a_DSR_RX & (U1)1U);  /* intentional wrap around */
    }
    else{
        s1_t_las = (S1)0;
    }

    return(s1_t_las);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HudCaDsrRxcnt(const U1 u1_a_PRM)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudCaDsrRxcnt(const U1 u1_a_PRM)
{
    U1                   u1_t_dsr;

    if(u1_a_PRM < (U1)HUD_CA_NUM_PRM){
        u1_t_dsr = u1_sp_hud_ca_dsr[u1_a_PRM] & (U1)HUD_CA_DSR_MAX;
    }
    else{
        u1_t_dsr = (U1)HUD_CA_DSR_INA;
    }

    return(u1_t_dsr);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HudCaPrmNext(const U1 u1_a_PRM, const S1 s1_a_NEXT, const U1 u1_a_DSR_RX)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_HudCaPrmNext(const U1 u1_a_PRM, const S1 s1_a_NEXT, const U1 u1_a_DSR_RX)
{
    S1                   s1_t_min;
    S1                   s1_t_max;
    S1                   s1_t_las;

    U1                   u1_t_ena;
    U1                   u1_t_syn;

    u1_t_syn = (U1)HUD_CA_SYN_FAI;
    if(u1_a_PRM < (U1)HUD_CA_NUM_PRM){

        s1_t_las = s1_sp_hud_ca_prm[u1_a_PRM];
        s1_t_min = st_gp_HUD_CA[u1_a_PRM].s1_min;
        s1_t_max = st_gp_HUD_CA[u1_a_PRM].s1_max;

        u1_t_ena = u1_s_hud_ca_nvm_synen | u1_a_DSR_RX;

        if((s1_a_NEXT < s1_t_min) ||
           (s1_a_NEXT > s1_t_max)){

         /* u1_t_syn = (U1)HUD_CA_SYN_FAI; */
        }
        else if(s1_a_NEXT == s1_t_las){

            u1_t_syn = (U1)HUD_CA_SYN_SUC;

            u1_sp_hud_ca_dsr[u1_a_PRM] = u1_sp_hud_ca_dsr[u1_a_PRM] + (u1_a_DSR_RX & (U1)1U);  /* intentional wrap around */
        }
        else if(u1_t_ena != (U1)0U){

            u1_t_syn = (U1)HUD_CA_SYN_REQ;

            s1_sp_hud_ca_prm[u1_a_PRM] = s1_a_NEXT;
            u1_sp_hud_ca_dsr[u1_a_PRM] = u1_sp_hud_ca_dsr[u1_a_PRM] + (u1_a_DSR_RX & (U1)1U);  /* intentional wrap around */
            u1_sp_hud_ca_syn[u1_a_PRM] = u1_t_syn;
            u1_s_hud_ca_prm_next       = (U1)U1_MAX;
        }
        else if(u1_sp_hud_ca_syn[u1_a_PRM] > (U1)HUD_CA_SYN_RUN){

            u1_t_syn = (U1)HUD_CA_SYN_SUC;

            s1_sp_hud_ca_prm[u1_a_PRM] = s1_a_NEXT;
        }
        else{

         /* u1_t_syn = (U1)HUD_CA_SYN_FAI; */
        }
    }

    return(u1_t_syn);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_HudCaSynNext(const U2 u2_a_NID, const S1 s1_a_NEXT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_HudCaSynNext(const U2 u2_a_NID, const S1 s1_a_NEXT)
{
    U4                   u4_t_nvm_ca;

    U1                   u1_t_nvm_chk;
    U1                   u1_t_syn;
    S1                   s1_t_cal;

    u4_t_nvm_ca  = (U4)U4_MAX;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_a_NID, &u4_t_nvm_ca);
    s1_t_cal     = (S1)((U1)u4_t_nvm_ca);
    if((u1_t_nvm_chk == (U1)NVMC_STATUS_KIND_OK) &&
       (u4_t_nvm_ca  <= (U4)U1_MAX             ) &&
       (s1_t_cal     == s1_a_NEXT              )){

        u1_t_syn = (U1)HUD_CA_SYN_SUC;
    }
    else{

        u4_t_nvm_ca = (U4)((U1)s1_a_NEXT);
        vd_g_Nvmc_WriteU4(u2_a_NID, u4_t_nvm_ca);
        u1_t_syn = (U1)HUD_CA_SYN_RUN;
    }

    return(u1_t_syn);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_HudCaSynLast(const ST_HUD_CA * st_ap_CA, S1 * s1_ap_prm)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_HudCaSynLast(const ST_HUD_CA * st_ap_CA, S1 * s1_ap_prm)
{
    U4                   u4_t_nvm_ca;

    U1                   u1_t_nvm_chk;
    U1                   u1_t_syn;

    S1                   s1_t_min;
    S1                   s1_t_max;
    S1                   s1_t_cal;

    s1_t_min     = st_ap_CA->s1_min;
    s1_t_max     = st_ap_CA->s1_max;
    u4_t_nvm_ca  = (U4)U4_MAX;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(st_ap_CA->u2_nid, &u4_t_nvm_ca);
    s1_t_cal     = (S1)((U1)u4_t_nvm_ca);
    if((u1_t_nvm_chk == (U1)NVMC_STATUS_KIND_OK) &&
       (u4_t_nvm_ca  <= (U4)U1_MAX             ) &&
       (s1_t_cal     >= s1_t_min               ) &&
       (s1_t_cal     <= s1_t_max               )){

        (*s1_ap_prm) = s1_t_cal;
        u1_t_syn     = (U1)HUD_CA_SYN_SUC;
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_syn = (U1)HUD_CA_SYN_RUN;
    }
    else{
        (*s1_ap_prm) = (S1)0;
        u1_t_syn = (U1)HUD_CA_SYN_FAI;
    }

    return(u1_t_syn);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/30/2020  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
