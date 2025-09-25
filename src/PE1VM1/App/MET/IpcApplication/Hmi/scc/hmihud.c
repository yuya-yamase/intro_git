/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Hmihud                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIHUD_C_MAJOR                         (1)
#define HMIHUD_C_MINOR                         (1)
#define HMIHUD_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmihud.h"
#include "vardef.h"

#if 0   /* BEV Rebase provisionally */
#include "himgadj.h"
#include "hdimmgr_if.h"
#endif   /* BEV Rebase provisionally */

#include "rim_ctl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIHUD_C_MAJOR != HMIHUD_H_MAJOR) || \
     (HMIHUD_C_MINOR != HMIHUD_H_MINOR) || \
     (HMIHUD_C_PATCH != HMIHUD_H_PATCH))
#error "hmihud.c and hmihud.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIHUD_FIRST_DTA                       (0U)

#define HMIHUD_DTA_NUM                         (7U)

#define HMIHUD_SIG_NUM                         (16U)
#define HMIHUD_SIG_RESID                       (0U)
#define HMIHUD_SIG_HUD_ST                      (1U)
#define HMIHUD_SIG_VIPOS_UPSW                  (2U)
#define HMIHUD_SIG_VIPOS_DNSW                  (3U)
#define HMIHUD_SIG_VIPOS_UP                    (4U)
#define HMIHUD_SIG_VIPOS_DN                    (5U)
#define HMIHUD_SIG_ILL_UPSW                    (6U)
#define HMIHUD_SIG_ILL_DNSW                    (7U)
#define HMIHUD_SIG_BLDUTY_OUT                  (8U)
#define HMIHUD_SIG_ADJMAXPOS                   (9U)
#define HMIHUD_SIG_RESPOS                      (10U)
#define HMIHUD_SIG_MOVPOS                      (11U)
#define HMIHUD_SIG_ADJMINPOS                   (12U)
#define HMIHUD_SIG_ADJTEPPOS                   (13U)
#define HMIHUD_SIG_GBUS_STS                    (14U)
#define HMIHUD_SIG_GVIF_STS                    (15U)

#define HMIHUD_STS_NORMAL                      (0U)
#define HMIHUD_SW_OPE                          (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4          u4_buf;
    U1          u1_bitpos;
    U4          u4_bitmask;
}ST_HMIHUD_SIGCONVERT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_sp_hmihud_dtabuf[HMIHUD_DTA_NUM];
static U1   u1_s_hmihud_viposdn_sig;
static U1   u1_s_hmihud_viposup_sig;
static U1   u1_s_hmihud_illupsw_presig;
static U1   u1_s_hmihud_illdnsw_presig;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_s_HmiHudReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ);

static void vd_s_HmiHudSetResid(void);
static void vd_s_HmiHudSetHudst(void);
static void vd_s_HmiHudSetHudbrns(void);
static void vd_s_HmiHudSetViposSw(void);
static void vd_s_HmiHudSetViposUpdn(void);
static void vd_s_HmiHudSetIllSw(void);
static void vd_s_HmiHudSetBldutyout(void);
static void vd_s_HmiHudSetAdjmaxpos(void);
static void vd_s_HmiHudSetRespos(void);
static void vd_s_HmiHudSetMovpos(void);
static void vd_s_HmiHudSetAdjminpos(void);
static void vd_s_HmiHudSetAdjteppos(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_HMIHUD_SIGCONVERT st_sp_HMIHUD_SIGCONVERT[HMIHUD_SIG_NUM] = {
/*  u4_buf      u1_bitpos    u4_bitmask                            */
    {(U4)6U,    (U1)0U,      (U4)0xFFU  },    /* HUD_VIPOS_RESID */
    {(U4)6U,    (U1)8U,      (U4)0xFFU  },    /* HUD_VIPOS_HUD_ST */
    {(U4)0U,    (U1)0U,      (U4)0x01U  },    /* HUD_VIPOS_UPSW */
    {(U4)0U,    (U1)1U,      (U4)0x01U  },    /* HUD_VIPOS_DNSW */
    {(U4)0U,    (U1)2U,      (U4)0x01U  },    /* HUD_L_VIPOS_UP */
    {(U4)0U,    (U1)3U,      (U4)0x01U  },    /* HUD_L_VIPOS_DN */
    {(U4)1U,    (U1)0U,      (U4)0x01U  },    /* HUD_ILL_UPSW */
    {(U4)1U,    (U1)1U,      (U4)0x01U  },    /* HUD_ILL_DNSW */
    {(U4)3U,    (U1)0U,      (U4)0xFFFFU},    /* HUD_BLDUTY_OUT */
    {(U4)3U,    (U1)16U,     (U4)0xFFFFU},    /* HUD_VIPOS_ADJMAXPOS */
    {(U4)4U,    (U1)0U,      (U4)0xFFFFU},    /* HUD_VIPOS_RESPOS */
    {(U4)4U,    (U1)16U,     (U4)0xFFFFU},    /* HUD_VIPOS_MOVPOS */
    {(U4)5U,    (U1)0U,      (U4)0xFFFFU},    /* HUD_VIPOS_ADJMINPOS */
    {(U4)5U,    (U1)16U,     (U4)0xFFFFU},    /* HUD_VIPOS_ADJTEPPOS */
    {(U4)1U,    (U1)24U,     (U4)0xFFU  },    /* HUD_GBUS_STS */
    {(U4)2U,    (U1)24U,     (U4)0xFFU  }     /* HUD_GVIF_STS */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiHudInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudInit(void)
{
    U4  u4_t_loop;    /* loop counter */

    u1_s_hmihud_viposdn_sig = (U1)0U;
    u1_s_hmihud_viposup_sig = (U1)0U;
    u1_s_hmihud_illupsw_presig = (U1)0U;
    u1_s_hmihud_illdnsw_presig = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIHUD_DTA_NUM ; u4_t_loop++){
        u4_sp_hmihud_dtabuf[u4_t_loop] = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiHudMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudMainTask(void)
{
    U1 u1_t_gbus_sts;    /* HUD_GBUS_STS */
    U1 u1_t_gvif_sts;    /* HUD_GVIF_STS */

    u1_t_gbus_sts = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_GBUS_STS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u1_t_gvif_sts = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_GVIF_STS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    if(u1_t_gbus_sts == (U1)HMIHUD_STS_NORMAL){
        vd_s_HmiHudSetViposSw();
        vd_s_HmiHudSetIllSw();
    }

    if(u1_t_gvif_sts == (U1)HMIHUD_STS_NORMAL){
        vd_s_HmiHudSetResid();
        vd_s_HmiHudSetHudst();
        vd_s_HmiHudSetBldutyout();
        vd_s_HmiHudSetAdjmaxpos();
        vd_s_HmiHudSetRespos();
        vd_s_HmiHudSetMovpos();
        vd_s_HmiHudSetAdjminpos();
        vd_s_HmiHudSetAdjteppos();
    }

    /* Ethernet */
    vd_s_HmiHudSetViposUpdn();
    vd_s_HmiHudSetHudbrns();
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiHudDataPut(U4 * u4_ap_REQ)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : hud first address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudDataPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIHUD_DTA_NUM ; u4_t_loop++){
            u4_sp_hmihud_dtabuf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/*  static U4 u4_s_HmiHudReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG_IDX  :  signal index number                                                                             */
/*                  u4_ap_REQ     :  hud data buffer                                                                                 */
/*  Return:         u4_t_sig      :  recieve signal                                                                                  */
/*===================================================================================================================================*/
static U4 u4_s_HmiHudReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ)
{
    U4    u4_t_sig;       /* recieve signal */
    U4    u4_t_buf;       /* MM Sub-Bus buffer */
    U1    u1_t_bitpos;    /* bit position */
    U4    u4_t_bitmask;   /* bit mask */

    u4_t_buf      = u4_ap_REQ[st_sp_HMIHUD_SIGCONVERT[u1_a_SIG_IDX].u4_buf];
    u1_t_bitpos   = st_sp_HMIHUD_SIGCONVERT[u1_a_SIG_IDX].u1_bitpos;
    u4_t_bitmask  = st_sp_HMIHUD_SIGCONVERT[u1_a_SIG_IDX].u4_bitmask;

    u4_t_sig      = (u4_t_buf >> u1_t_bitpos) & u4_t_bitmask;

    return(u4_t_sig);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetResid(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetResid(void){
    U1 u1_t_resid;    /* recieve signal */

    u1_t_resid = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_RESID, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_RESID(u1_t_resid);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetHudst(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetHudst(void){
    U1 u1_t_hudst;    /* recieve signal */

    u1_t_hudst = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_HUD_ST, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_HUD_ST(u1_t_hudst);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetHudbrns(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetHudbrns(void){
    U1 u1_t_ill_upsw;   /* recieve signal */
    U1 u1_t_ill_dnsw;   /* recieve signal */
    
    u1_t_ill_upsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ILL_UPSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u1_t_ill_dnsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ILL_DNSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetViposSw(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetViposSw(void){
    U1 u1_t_vpos_upsw;    /* recieve signal */
    U1 u1_t_vpos_dnsw;    /* recieve signal */

    u1_t_vpos_upsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_VIPOS_UPSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u1_t_vpos_dnsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_VIPOS_DNSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    
#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSetUpDwSw(u1_t_vpos_upsw, u1_t_vpos_dnsw);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetViposUpdn(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetViposUpdn(void){
    U1 u1_t_vpos_up;    /* recieve signal */
    U1 u1_t_vpos_dn;    /* recieve signal */

    u1_t_vpos_up = u1_s_hmihud_viposup_sig;
    u1_t_vpos_dn = u1_s_hmihud_viposdn_sig;

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_L_VIPOS_UPDW(u1_t_vpos_up, u1_t_vpos_dn);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetIllSw(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetIllSw(void){
    U1 u1_t_ill_upsw;    /* recieve signal */
    U1 u1_t_ill_dnsw;    /* recieve signal */
    U1 u1_t_sts;
    U1 u1_t_kind;
    U2 u2_t_swcnt;

#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_HMIHUD_ID_HUDDIM = (U2)RIMID_U2_DS_22_10A7_HUD_DIM;
#else   /* BEV Rebase provisionally */
    static const U2 u2_s_HMIHUD_ID_HUDDIM = (U2)U2_MAX;
#endif   /* BEV Rebase provisionally */
    u1_t_ill_upsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ILL_UPSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u1_t_ill_dnsw = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ILL_DNSW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u2_t_swcnt    = (U2)0U;

#if 0   /* BEV Rebase provisionally */
    u1_t_sts  = u1_g_Rim_ReadU2withStatus(u2_s_HMIHUD_ID_HUDDIM , &u2_t_swcnt);
#else   /* BEV Rebase provisionally */
    u1_t_sts  = (U1)RIM_RESULT_KIND_NG;
#endif   /* BEV Rebase provisionally */
    u1_t_kind = u1_t_sts & (U1)RIM_RESULT_KIND_MASK;

    if ((u1_t_kind == (U1)RIM_RESULT_KIND_OK) &&
        (u2_t_swcnt < (U2)U2_MAX            ))  {
        if((u1_t_ill_upsw == (U1)HMIHUD_SW_OPE) &&
           (u1_t_ill_dnsw == (U1)HMIHUD_SW_OPE)) {
            /* Do Nothing */
        }
        else if ((u1_t_ill_upsw != u1_s_hmihud_illupsw_presig) &&
           (u1_t_ill_upsw == (U1)HMIHUD_SW_OPE         ))  {
            u2_t_swcnt++;
#if 0   /* BEV Rebase provisionally */
            vd_g_Rim_WriteU2(u2_s_HMIHUD_ID_HUDDIM, u2_t_swcnt);
#endif   /* BEV Rebase provisionally */
        }
        else if ((u1_t_ill_dnsw != u1_s_hmihud_illdnsw_presig) &&
                 (u1_t_ill_dnsw == (U1)HMIHUD_SW_OPE         ))  {
            u2_t_swcnt++;
#if 0   /* BEV Rebase provisionally */
            vd_g_Rim_WriteU2(u2_s_HMIHUD_ID_HUDDIM, u2_t_swcnt);
#endif   /* BEV Rebase provisionally */
        }
        else {
            /* Do Nothing */
        }
    }
    else {
        /* Do Nothing */
    }

    u1_s_hmihud_illupsw_presig = u1_t_ill_upsw;
    u1_s_hmihud_illdnsw_presig = u1_t_ill_dnsw;

#if 0   /* BEV Rebase provisionally */
    vd_g_HdimmgrIfSetUpDwSw(u1_t_ill_upsw, u1_t_ill_dnsw);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetBldutyout(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetBldutyout(void){
    U2 u2_t_bldutyout;    /* recieve signal */

    u2_t_bldutyout = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_BLDUTY_OUT, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HdimmgrIfSetOutduty(u2_t_bldutyout);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjmaxpos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjmaxpos(void){
    U2 u2_t_adjmaxpos;    /* recieve signal */

    u2_t_adjmaxpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMAXPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_ADJMAXPOS(u2_t_adjmaxpos);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetRespos(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetRespos(void){
    U2 u2_t_respos;    /* recieve signal */

    u2_t_respos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_RESPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_RESPOS(u2_t_respos);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetMovpos(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetMovpos(void){
    U2 u2_t_movpos;    /* recieve signal */

    u2_t_movpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_MOVPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_MOVPOS(u2_t_movpos);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjminpos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjminpos(void){
    U2 u2_t_adjmaxpos;    /* recieve signal */

    u2_t_adjmaxpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMINPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_ADJMINPOS(u2_t_adjmaxpos);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjteppos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjteppos(void){
    U2 u2_t_adjteppos;    /* recieve signal */

    u2_t_adjteppos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJTEPPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

#if 0   /* BEV Rebase provisionally */
    vd_g_HudImgAdjSet_GV_VIPOS_ADJTEPPOS(u2_t_adjteppos);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/13/2020  TH       New.                                                                                               */
/*  1.1.0    10/07/2020  TH       Fix HudSetViposUpdn.                                                                               */
/*                                                                                                                                   */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
