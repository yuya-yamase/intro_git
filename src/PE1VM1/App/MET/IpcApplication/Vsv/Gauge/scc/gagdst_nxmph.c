/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Gauge Digital Vehicle Speed - Numerical Xmph                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_NXMPH_C_MAJOR                     (2)
#define GAGDST_NXMPH_C_MINOR                     (0)
#define GAGDST_NXMPH_C_PATCH                     (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_nxmph_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_NXMPH_C_MAJOR != GAGDST_NXMPH_H_MAJOR) || \
     (GAGDST_NXMPH_C_MINOR != GAGDST_NXMPH_H_MINOR) || \
     (GAGDST_NXMPH_C_PATCH != GAGDST_NXMPH_H_PATCH))
#error "gagdst_nxmph.c and gagdst_nxmph.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_NXMPH_C_MAJOR != GAGDST_NXMPH_CFG_H_MAJOR) || \
     (GAGDST_NXMPH_C_MINOR != GAGDST_NXMPH_CFG_H_MINOR) || \
     (GAGDST_NXMPH_C_PATCH != GAGDST_NXMPH_CFG_H_PATCH))
#error "gagdst_nxmph.c and gagdst_nxmph_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_NXMPH_TIM_MAX                     (0xfffeU)

#define GAGDST_NXMPH_KM_TO_MI_MLT                (1000U)
#define GAGDST_NXMPH_KM_TO_MI_DIV                (1609U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_NXMPH_0P01_TO_0P5                 (50U)
#define GAGDST_NXMPH_0P5_UPDT                    (2U)     /* 1 xmph     */
#define GAGDST_NXMPH_1_XPMH                      (100U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_NXMPH_NUM_CD_STS                  (3U)
#define GAGDST_NXMPH_CD_0                        (0U)
#define GAGDST_NXMPH_CD_1                        (1U)
#define GAGDST_NXMPH_CD_2                        (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2      u2_xmph_0p5;
    U2      u2_fltrd;
    U2      u2_dsplyd;
}ST_GAGDST_NXMPH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                   u4_s_gagdst_nxmph_at_lvsum;
static U1                   u1_s_gagdst_nxmph_at_smplcnt;

static U4                   u4_s_gagdst_nxmph_kmphsum;
static U2                   u2_s_gagdst_nxmph_tmcnt;
static U2                   u2_s_gagdst_nxmph_tmidx;

static ST_GAGDST_NXMPH      st_sp_gagdst_nxmph[GAGDST_NXMPH_NUM_UNIT];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_GagdstNxmphTmupdt(void);
static void    vd_s_GagdstNxmphAct(void);
static void    vd_s_GagdstNxmphDeAct(void);
static U2      u2_s_GagdstNxmphTrgt(const U2 u2_a_XMPH, const U1 u1_a_UNIT);
static void    vd_s_GagdstNxmphCntdwn(const U2 u2_a_XMPH_TRGT, const U2 u2_a_TMUPDT, const U1 u1_a_UNIT);

static void    vd_s_GagdstNxmphOwDsplyd(const U2 u2_a_OW);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GagdstNxmphInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstNxmphInit(void)
{
    U4                       u4_t_lpcnt;

    u4_s_gagdst_nxmph_at_lvsum   = (U4)0U;
    u1_s_gagdst_nxmph_at_smplcnt = (U1)0U;

    u4_s_gagdst_nxmph_kmphsum    = (U4)0U;
    u2_s_gagdst_nxmph_tmcnt      = (U2)U2_MAX;
    u2_s_gagdst_nxmph_tmidx      = (U2)U2_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GAGDST_NXMPH_NUM_UNIT; u4_t_lpcnt++){
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_xmph_0p5 = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_fltrd    = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_dsplyd   = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstNxmphUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstNxmphUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)
{
    U4                       u4_t_xmph;

    U2                       u2_t_tmupdt;
    U2                       u2_t_kmph_0p01;
    U2                       u2_t_xmph_0p5;
    U2                       u2_t_xmph_trgt;

    U2                       u2_t_src_chk;

    u2_t_tmupdt = u2_s_GagdstNxmphTmupdt();

    if((u4_s_gagdst_nxmph_kmphsum < ((U4)U4_MAX - (U4)U2_MAX)) &&
       (u2_s_gagdst_nxmph_tmcnt   < (U2)GAGDST_NXMPH_TIM_MAX)){

        u2_t_src_chk = u2_a_SRC_CHK & u2_g_GAGDST_NXMPH_SRC_CHK;
        if(u2_t_src_chk == u2_g_GAGDST_NXMPH_SRC_VAL){
            u4_s_gagdst_nxmph_kmphsum += (U4)u2_a_TRGT;
            /* The maximum value of u4_s_gaggdst_nxmph_kmphsum is (U4_MAX - U2_MAX - 1).        */
            /* The maximum value of u2_a_TRGT is U2_MAX,                                        */
            /* so (u4_s_ gaggdst_nxmph_kmphsum += (U4)u2_a_TRGT) is always less than U4_MAX.    */
        }
        u2_s_gagdst_nxmph_tmcnt++;
    }

    u2_t_src_chk = u2_a_SRC_CHK & (U2)GAUGE_SRC_CHK_IGN_ON;
    if(u2_t_src_chk == (U2)0U){
        vd_s_GagdstNxmphDeAct();
    }
    else if(u2_s_gagdst_nxmph_tmcnt >= (U2)U2_MAX){

        vd_s_GagdstNxmphAct();
        vd_g_GagdstNxmphCfgComTx(u2_a_SRC_CHK, (U2)0U, (U2)0U);
    }
    else if(u2_s_gagdst_nxmph_tmcnt >= u2_t_tmupdt){

        u4_t_xmph = u4_s_gagdst_nxmph_kmphsum / (U4)u2_s_gagdst_nxmph_tmcnt;

        if(u4_t_xmph > (U4)U2_MAX){
            u2_t_kmph_0p01 = (U2)U2_MAX;
        }
        else{
            u2_t_kmph_0p01 = (U2)u4_t_xmph;
        }

        u4_s_gagdst_nxmph_kmphsum = (U4)0U;
        u2_s_gagdst_nxmph_tmcnt   = (U2)0U;

        /* Kmph */
        u2_t_xmph_0p5  = u2_t_kmph_0p01 / (U2)GAGDST_NXMPH_0P01_TO_0P5;
        u2_t_xmph_trgt = u2_s_GagdstNxmphTrgt(u2_t_xmph_0p5, (U1)GAGDST_NXMPH_KMPH);
        vd_s_GagdstNxmphCntdwn(u2_t_xmph_trgt, u2_t_tmupdt, (U1)GAGDST_NXMPH_KMPH);

        /* Mph  */
        if(((U4)U4_MAX / (U4)GAGDST_NXMPH_KM_TO_MI_MLT) > (U4)u2_t_kmph_0p01){
            u4_t_xmph = ((U4)u2_t_kmph_0p01 * (U4)GAGDST_NXMPH_KM_TO_MI_MLT) / (U4)GAGDST_NXMPH_KM_TO_MI_DIV;
        }
        else{
            u4_t_xmph = (U4)U4_MAX / (U4)GAGDST_NXMPH_KM_TO_MI_DIV;
        }
        u2_t_xmph_0p5  = (U2)u4_t_xmph / (U2)GAGDST_NXMPH_0P01_TO_0P5;
        u2_t_xmph_trgt = u2_s_GagdstNxmphTrgt(u2_t_xmph_0p5, (U1)GAGDST_NXMPH__MPH);
        vd_s_GagdstNxmphCntdwn(u2_t_xmph_trgt, u2_t_tmupdt, (U1)GAGDST_NXMPH__MPH);

        vd_g_GagdstNxmphCfgComTx(u2_a_SRC_CHK ,
                                 st_sp_gagdst_nxmph[GAGDST_NXMPH_KMPH].u2_fltrd,
                                 st_sp_gagdst_nxmph[GAGDST_NXMPH__MPH].u2_fltrd);
    }
    else{
        /* Nothing */
    }

    vd_s_GagdstNxmphOwDsplyd(u2_a_OW);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GagdstNxmphDsplyd(const U1 u1_a_UNIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_GagdstNxmphDsplyd(const U1 u1_a_UNIT)
{
    U2                       u2_t_dsplyd;

    if(u1_a_UNIT < (U1)GAGDST_NXMPH_NUM_UNIT){
        u2_t_dsplyd = st_sp_gagdst_nxmph[u1_a_UNIT].u2_dsplyd;
    }
    else{
        u2_t_dsplyd = (U2)0U;
    }

    return(u2_t_dsplyd);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_GagdstNxmphTmupdt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_GagdstNxmphTmupdt(void)
{
    U4                       u4_t_at;     /* ambient temperature */
    U2                       u2_t_tmupdt;

    u4_t_at = (U4)u2_g_GagdstNxmphCfgAtlv();
    if((u4_s_gagdst_nxmph_at_lvsum   < ((U4)U4_MAX - (U4)U2_MAX)) &&
       (u1_s_gagdst_nxmph_at_smplcnt < (U1)U1_MAX               )){

        u4_s_gagdst_nxmph_at_lvsum += u4_t_at;
        /* The maximum value of u4_s_gagdst_nxmph_at_lvsum is (U4_MAX - U2_MAX - 1).        */
        /* The maximum value of u4_t_at is U2_MAX.                                          */
        /* so (u4_s_gagdst_nxmph_at_lvsum += u4_t_at) is always less than U4_MAX.           */
        u1_s_gagdst_nxmph_at_smplcnt++;
    }

    if(u1_s_gagdst_nxmph_at_smplcnt >= (U1)GAGDST_NXMPH_AT_NUM_SMPL){

        u4_t_at = u4_s_gagdst_nxmph_at_lvsum >> GAGDST_NXMPH_AT_AVE_SFT;

        u4_s_gagdst_nxmph_at_lvsum   = (U4)0U;
        u1_s_gagdst_nxmph_at_smplcnt = (U1)0U;

        u2_s_gagdst_nxmph_tmidx = u2_g_GagdstNxmphRngCmprU2(u2_s_gagdst_nxmph_tmidx, (U2)u4_t_at);
    }

    if(u2_s_gagdst_nxmph_tmidx >= u2_g_GAGDST_NXMPH_NUM_TMIDX){
        u2_t_tmupdt = u2_g_GAGDST_NXMPH_TMUPDT_MIN;
    }
    else{
        u2_t_tmupdt = u2_gp_GAGDST_NXMPH_TMUPDT[u2_s_gagdst_nxmph_tmidx];
        if(u2_t_tmupdt < u2_g_GAGDST_NXMPH_TMUPDT_MIN){
            u2_t_tmupdt = u2_g_GAGDST_NXMPH_TMUPDT_MIN;
        }
    }

    return(u2_t_tmupdt);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GagdstNxmphAct(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GagdstNxmphAct(void)
{
    U4                       u4_t_lpcnt;

    u4_s_gagdst_nxmph_kmphsum = (U4)0U;
    u2_s_gagdst_nxmph_tmcnt   = (U2)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GAGDST_NXMPH_NUM_UNIT; u4_t_lpcnt++){
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_xmph_0p5 = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_fltrd    = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_dsplyd   = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GagdstNxmphDeAct(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GagdstNxmphDeAct(void)
{
    U4                       u4_t_lpcnt;

    u4_s_gagdst_nxmph_kmphsum = (U4)0U;
    u2_s_gagdst_nxmph_tmcnt   = (U2)U2_MAX;
    u2_s_gagdst_nxmph_tmidx   = (U2)U2_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GAGDST_NXMPH_NUM_UNIT; u4_t_lpcnt++){
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_xmph_0p5 = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_fltrd    = (U2)0U;
        st_sp_gagdst_nxmph[u4_t_lpcnt].u2_dsplyd   = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  static U2      u2_s_GagdstNxmphTrgt(const U2 u2_a_XMPH, const U1 u1_a_UNIT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_GagdstNxmphTrgt(const U2 u2_a_XMPH, const U1 u1_a_UNIT)
{
    U2                       u2_t_trgt;
    U2                       u2_t_dist;

    u2_t_trgt = st_sp_gagdst_nxmph[u1_a_UNIT].u2_xmph_0p5;
    if(u2_a_XMPH >= u2_t_trgt){
        u2_t_dist = u2_a_XMPH - u2_t_trgt;
    }
    else{
        u2_t_dist = u2_t_trgt - u2_a_XMPH;
    }

    if(u2_t_dist >= (U2)GAGDST_NXMPH_0P5_UPDT){
        u2_t_trgt = u2_a_XMPH;
        st_sp_gagdst_nxmph[u1_a_UNIT].u2_xmph_0p5 = u2_a_XMPH;
    }

    /* ------------------------------------------------------------------------------ */
    /* Attention :                                                                    */
    /* ------------------------------------------------------------------------------ */
    /* u2_t_trgt is set to zero intentionally if u2_a_XMPH is equal to zero in order  */
    /* to follow the customer specification fully.                                    */
    /* ------------------------------------------------------------------------------ */
    if(u2_a_XMPH == (U2)0U){
        u2_t_trgt = (U2)0U;
    }

    u2_t_trgt = (u2_t_trgt + (U2)1U) >> 1U;  /* round half : 0.5 xmph -> 1 xmph */

    return(u2_t_trgt);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GagdstNxmphCntdwn(const U2 u2_a_XMPH_TRGT, const U2 u2_a_TMUPDT, const U1 u1_a_UNIT)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GagdstNxmphCntdwn(const U2 u2_a_XMPH_TRGT, const U2 u2_a_TMUPDT, const U1 u1_a_UNIT)
{
    static const U1          u1_sp_GAGDST_NXMPH_CD_NEXT[GAGDST_NXMPH_NUM_CD_STS * GAGDST_NXMPH_NUM_CD_STS] = {
        (U1)GAGDST_NXMPH_CD_0, (U1)GAGDST_NXMPH_CD_0, (U1)GAGDST_NXMPH_CD_1,
        (U1)GAGDST_NXMPH_CD_1, (U1)GAGDST_NXMPH_CD_1, (U1)GAGDST_NXMPH_CD_1,
        (U1)GAGDST_NXMPH_CD_2, (U1)GAGDST_NXMPH_CD_2, (U1)GAGDST_NXMPH_CD_2
    };

    U2                       u2_t_fltrd;
    U2                       u2_t_max;
    U2                       u2_t_next;

    u2_t_fltrd = st_sp_gagdst_nxmph[u1_a_UNIT].u2_dsplyd;
    u2_t_max    = u2_g_GagdstNxmphCfgDsplyMax(u1_a_UNIT);
    if(u2_a_XMPH_TRGT > u2_t_max){
        u2_t_fltrd = u2_t_max;
    }
    else if((u2_a_XMPH_TRGT > (U2)GAGDST_NXMPH_CD_2       ) ||
            (u2_a_TMUPDT    > u2_g_GAGDST_NXMPH_TMUPDT_MIN)){
        u2_t_fltrd = u2_a_XMPH_TRGT;
    }
    else if(u2_t_fltrd > (U2)GAGDST_NXMPH_CD_2){
        u2_t_fltrd = (U2)GAGDST_NXMPH_CD_2;
    }
    else{
        u2_t_next   = (u2_a_XMPH_TRGT * (U2)GAGDST_NXMPH_NUM_CD_STS) + u2_t_fltrd;
        u2_t_fltrd = (U2)u1_sp_GAGDST_NXMPH_CD_NEXT[u2_t_next];
    }
    st_sp_gagdst_nxmph[u1_a_UNIT].u2_fltrd = u2_t_fltrd;
}
/*===================================================================================================================================*/
/*  static void    vd_s_GagdstNxmphOwDsplyd(const U2 u2_a_OW)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GagdstNxmphOwDsplyd(const U2 u2_a_OW)
{
    U4                       u4_t_xmph;

    if(u2_a_OW < (U2)GAUGE_OW_INA){

        u4_t_xmph  = (U4)u2_a_OW + (U4)GAGDST_NXMPH_0P01_TO_0P5;
        /* The maximum value of u2_a_OW is 65534 and the value of GAGDST_NXMPH_0P01_TO_0P5 is 50.                           */
        /* so ((U4)u2_a_OW + (U4)GAGDST_NXMPH_0P01_TO_0P5) is always less than U4_MAX.                                      */
        u4_t_xmph /= (U4)GAGDST_NXMPH_1_XPMH;
        st_sp_gagdst_nxmph[GAGDST_NXMPH_KMPH].u2_dsplyd = (U2)u4_t_xmph;

        u4_t_xmph  = ((U4)u2_a_OW * (U4)GAGDST_NXMPH_KM_TO_MI_MLT) / (U4)GAGDST_NXMPH_KM_TO_MI_DIV;
        /* The maximum value of u2_a_OW is 65534 and the value of GAGDST_NXMPH_KM_TO_MI_MLT is 2548.                        */
        /* The value of GAGDST_NXMPH_KM_TO_MI_DIV is 4100.                                                                  */
        /* so (((U4)u2_a_OW * (U4)GAGDST_NXMPH_KM_TO_MI_MLT) / (U4)GAGDST_NXMPH_KM_TO_MI_DIV) is always less than U4_MAX.   */
        u4_t_xmph += (U4)GAGDST_NXMPH_0P01_TO_0P5;
        /* The maximum value of (((U4)u2_a_OW * (U4)GAGDST_NXMPH_KM_TO_MI_MLT) / (U4)GAGDST_NXMPH_KM_TO_MI_DIV) is 40726.   */
        /* The value of GAGDST_NXMPH_0P01_TO_0P5 is 50.                                                                     */
        /* so (u4_t_xmph += (U4)GAGDST_NXMPH_0P01_TO_0P5) is always less than U4_MAX.                                       */
        u4_t_xmph /= (U4)GAGDST_NXMPH_1_XPMH;
        st_sp_gagdst_nxmph[GAGDST_NXMPH__MPH].u2_dsplyd = (U2)u4_t_xmph;
    }
    else{
        st_sp_gagdst_nxmph[GAGDST_NXMPH_KMPH].u2_dsplyd = st_sp_gagdst_nxmph[GAGDST_NXMPH_KMPH].u2_fltrd;
        st_sp_gagdst_nxmph[GAGDST_NXMPH__MPH].u2_dsplyd = st_sp_gagdst_nxmph[GAGDST_NXMPH__MPH].u2_fltrd;
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
/*  1.0.0     3/ 7/2018  TN       New.                                                                                               */
/*  1.1.0     6/ 3/2019  TN       The design and implementation were optimized.                                                      */
/*  2.0.0     6/ 9/2021  TA       u2_g_GagdstNxmphTmupdt -> u2_s_GagdstNxmphTmupdt.                                                  */
/*  2.0.1    10/25/2021  TK       QAC supported.                                                                                     */
/*  2.0.2    12/13/2022  TA(M)    Change GAGDST_NXMPH_KM_TO_MI_MLT 2548 to 1000, GAGDST_NXMPH_KM_TO_MI_DIV 4100 to 1609              */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * TA(M) = Teruyuki Anjima, NTT Data MSE                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
