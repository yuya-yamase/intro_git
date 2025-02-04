/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HMI communication I/F control G monitor peak hold processing                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIGMON_C_MAJOR                          (1)
#define HMIGMON_C_MINOR                          (0)
#define HMIGMON_C_PATCH                          (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmigmon_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIGMON_C_MAJOR != HMIGMON_H_MAJOR) || \
     (HMIGMON_C_MINOR != HMIGMON_H_MINOR) || \
     (HMIGMON_C_PATCH != HMIGMON_H_PATCH))
#error "hmigmon.c and hmigmon.h : source and header files are inconsistent!"
#endif

#if ((HMIGMON_C_MAJOR != HMIGMON_CFG_H_MAJOR) || \
     (HMIGMON_C_MINOR != HMIGMON_CFG_H_MINOR) || \
     (HMIGMON_C_PATCH != HMIGMON_CFG_H_PATCH))
#error "hmigmon.c and hmigmon_cfg_private.h : source and parameter files are inconsistent!"
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
static ST_GMONINFO  st_s_hmigmon_peakhold_peak[HMIGMON_NUM_ANGLE];      /* Peak hold maximum XY information per area                 */
static ST_GMONINFO  st_s_hmigmon_ball;                                  /* gravitational acceleration ball information               */
static ST_GMONINFO  st_s_hmigmon_val;                                   /* gravitational acceleration val information                */
                                                                        /* Do not use .u1_visible (FALSE Fixed)                      */
static ST_GMONINFO  st_s_hmigmon_peakhold[HMIGMON_NUM_ANGLE][HMIGMON_NUM_LINEPOINT];    /* peak hold information                     */

static U1           u1_s_reset_flag;                                    /* reset flag                                                */

static U1           u1_s_gmon_his_ava;                                  /* History of gravity is available or not                    */

static ST_GMONINFO  st_s_hmigmon_maxguard[HMIGMON_NUM_ANGLE];           /* MAX Guard Retraction Location Lookup Table                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_HmiGmonVisibleJdg(U1 u1_a_visible);
static void     vd_s_HmiGmonDupliDel(U1 u1_a_area_org_idx);
static U1       u1_s_HmiGmonMakeBall(void);
static void     vd_s_HmiGmonMakeVal(void);
static U1       u1_s_HmiGmonPhInfoCheck(void);
static void     vd_s_HmiGmonMakePhDiagram(void);
static U1       u1_s_HmiGmonJudgeArea(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft);
static void     vd_s_HmiGmonCalcArea(U1 *u1_ap_area, U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft);
static U1       u1_s_HmiGmonMaxQuadrant(U1 u1_a_move_frtbk);
static U4       u4_s_HmiGmonOldDistGetInfo(U1 u1_a_now_angle);
static U4       u4_s_HmiGmonDistGetInfo(U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft);
static void     vd_s_HmiGmonInfoUpdate(ST_GMONINFO *stp_a_gmon, U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft);
static U2       u2_s_HmiGmonABS(S2 s2_a_data1, S2 s2_a_data2, S2 *s2_a_siged);
static void     vd_s_HmiGmonHeakHoldInfoClear(void);
static U1       u1_s_HmiGmonDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft);
static U1       u1_s_HmiGmonValDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U1 u1_a_val_frtbk, U1 u1_a_val_rgtlft);
static void     vd_s_HmiGmonPhInfoGuard(void);
static void     vd_s_HmiGmonSetMaxGuardTable(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void    vd_g_HmiGmonBonInitial(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiGmonBonInitial(void)
{
    U1 u1_t_area_idx;
    U1 u1_t_plot_idx;

    st_s_hmigmon_ball = st_HMIGMON_INVISIBLE_GMONINFO;
    st_s_hmigmon_val  = st_HMIGMON_INVISIBLE_GMONINFO;

    for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
        for(u1_t_plot_idx = (U1)0U; u1_t_plot_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_idx++){
            st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
        }
        st_s_hmigmon_peakhold_peak[u1_t_area_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
        vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_Y],
                                     (U2)st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_frtbk);
        vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_X],
                                     (U2)st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_rgtlft);
    }
    u1_s_reset_flag = (U1)HMIGMON_PEAKHOLD_RESET_HOLD;
    
    u1_s_gmon_his_ava = (U1)TRUE;
    vd_HMIGMON_GMONHISWRT_U1(u1_s_gmon_his_ava);
    vd_s_HmiGmonSetMaxGuardTable();
}

/*===================================================================================================================================*/
/* void    vd_g_HmiGmonWkupInitial(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiGmonWkupInitial(void)
{
    U1 u1_t_area_idx;
    U1 u1_t_plot_idx;
    U1 u1_t_rimsts;
    U2 u2_t_gcdn_frtbk;
    U2 u2_t_gcdn_rgtlft;

    st_s_hmigmon_ball = st_HMIGMON_INVISIBLE_GMONINFO;
    st_s_hmigmon_val  = st_HMIGMON_INVISIBLE_GMONINFO;

    for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
        for(u1_t_plot_idx = (U1)0U; u1_t_plot_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_idx++){
            st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
        }
        st_s_hmigmon_peakhold_peak[u1_t_area_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
        u2_t_gcdn_frtbk  = (U2)0U;
        u1_t_rimsts = u1_HMIGMON_GMONGCDN_HIS_READ(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_Y],&u2_t_gcdn_frtbk);
        if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_frtbk = (S2)u2_t_gcdn_frtbk;
        }
        u2_t_gcdn_rgtlft = (U2)0U;
        u1_t_rimsts = u1_HMIGMON_GMONGCDN_HIS_READ(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_X],&u2_t_gcdn_rgtlft);
        if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_rgtlft = (S2)u2_t_gcdn_rgtlft;
        }
    }
    u1_s_reset_flag = (U1)HMIGMON_PEAKHOLD_RESET_HOLD;

    u1_t_rimsts = u1_HMIGMON_GMONHISREAD(&u1_s_gmon_his_ava);
    if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
        u1_s_gmon_his_ava = (U1)TRUE;
    }
    u1_s_gmon_his_ava = u1_s_gmon_his_ava & (U1)TRUE;

    vd_HMIGMON_GMONHISWRT_U1(u1_s_gmon_his_ava);
    vd_s_HmiGmonSetMaxGuardTable();
}

/*===================================================================================================================================*/
/*  ST_GMONINFO     st_g_HmiGmonGetBallInfo(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         ST_GMONINFO st_s_hmigmon_ball                                                                                    */
/*===================================================================================================================================*/
ST_GMONINFO     st_g_HmiGmonGetBallInfo(void)
{
    /* Not Use Literal Define for Compiler constraints(sign conversion) */
    if((st_s_hmigmon_ball.s2_gcdn_frtbk  > (S2)((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT))
    || (st_s_hmigmon_ball.s2_gcdn_frtbk  < (S2)(((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * (-1)))
    || (st_s_hmigmon_ball.s2_gcdn_rgtlft > (S2)((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT))
    || (st_s_hmigmon_ball.s2_gcdn_rgtlft < (S2)(((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * (-1)))){
        st_s_hmigmon_ball.s2_gcdn_frtbk  = (S2)0;
        st_s_hmigmon_ball.s2_gcdn_rgtlft = (S2)0;
        st_s_hmigmon_ball.u1_visible     = (U1)FALSE;
    }

    return(st_s_hmigmon_ball);
}

/*===================================================================================================================================*/
/*  ST_GMONINFO     st_g_HmiGmonGetValInfo(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         ST_GMONINFO st_s_hmigmon_val                                                                                    */
/*===================================================================================================================================*/
ST_GMONINFO     st_g_HmiGmonGetValInfo(void)
{
    if((st_s_hmigmon_val.s2_gcdn_frtbk  > (S2)HMIGMON_VAL_FRTBK_MAX )
    || (st_s_hmigmon_val.s2_gcdn_frtbk  < (S2)HMIGMON_VAL_FRTBK_MIN )
    || (st_s_hmigmon_val.s2_gcdn_rgtlft > (S2)HMIGMON_VAL_RGTLFT_MAX)
    || (st_s_hmigmon_val.s2_gcdn_rgtlft < (S2)HMIGMON_VAL_RGTLFT_MIN)){
        st_s_hmigmon_val.s2_gcdn_frtbk  = (S2)0;
        st_s_hmigmon_val.s2_gcdn_rgtlft = (S2)0;
        st_s_hmigmon_val.u1_visible     = (U1)FALSE;
    }

    return(st_s_hmigmon_val);
}

/*===================================================================================================================================*/
/*  const ST_GMONINFO*      st_g_HmiGetPeakHoldInfo(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         const ST_GMONINFO* st_s_hmigmon_peakhold_peak                                                                    */
/*===================================================================================================================================*/
const ST_GMONINFO*      st_g_HmiGetPeakHoldInfo(void)
{
    vd_s_HmiGmonPhInfoGuard();

    return((const ST_GMONINFO*)st_s_hmigmon_peakhold_peak);
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiGmonPeakHoldMainTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiGmonPeakHoldMainTask(void)
{
    U1 u1_t_ok;
    U1 u1_t_igon;

    u1_t_igon = u1_HMIGMON_IG_ISON();

    if(u1_t_igon == (U1)TRUE){
        vd_s_HmiGmonMakeVal();
        vd_s_HmiGmonPhInfoGuard();

        u1_t_ok  = u1_s_HmiGmonMakeBall();
        u1_t_ok &= u1_s_HmiGmonPhInfoCheck();
        u1_t_ok &= u1_g_GmntrGetGSts();

        if(u1_t_ok == (U1)TRUE){
            vd_s_HmiGmonMakePhDiagram();
            vd_s_HmiGmonVisibleJdg((U1)HMIGMON_VISIBLE_TRUE);
            vd_s_HmiGmonDupliDel((U1)HMIGMON_TAN_ANGLE_90);
            vd_s_HmiGmonDupliDel((U1)HMIGMON_TAN_ANGLE_270);
        }
        else{
            vd_s_HmiGmonVisibleJdg((U1)HMIGMON_VISIBLE_FALSE);
        }
    }
    else{
        vd_g_HmiGmonWkupInitial();
    }
    u1_s_reset_flag = (U1)HMIGMON_PEAKHOLD_RESET_HOLD;
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonVisibleJdg(U1 u1_a_visible)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_visible                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonVisibleJdg(U1 u1_a_visible)
{
    U1 u1_t_area_idx;
    U1 u1_t_plot_idx;

    if(u1_a_visible == (U1)HMIGMON_VISIBLE_TRUE){
        st_s_hmigmon_ball.u1_visible = (U1)TRUE;
        for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
            st_s_hmigmon_peakhold_peak[u1_t_area_idx].u1_visible = (U1)TRUE;
        }
    }
    else{
        st_s_hmigmon_ball.u1_visible = (U1)FALSE;
            for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
                st_s_hmigmon_peakhold_peak[u1_t_area_idx].u1_visible = (U1)FALSE;
            }
    }

    if(u1_a_visible == (U1)HMIGMON_VISIBLE_FALSE){
        for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
            for(u1_t_plot_idx = (U1)0U; u1_t_plot_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_idx++){
                st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx].u1_visible = (U1)FALSE;
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonDupliDel(U1 u1_a_area_org_idx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_area_org_idx                                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonDupliDel(U1 u1_a_area_org_idx)
{
    U1 u1_t_area_enm_idx;
    U1 u1_t_plot_org_idx;
    U1 u1_t_plot_enm_idx;

    if(u1_a_area_org_idx != (U1)HMIGMON_TAN_ANGLE_0){
        u1_t_area_enm_idx = u1_a_area_org_idx - (U1)1U;
    }
    else{
        u1_t_area_enm_idx = (U1)HMIGMON_TAN_ANGLE_360 - (U1)1U;
    }

    for(u1_t_plot_org_idx = (U1)0U; u1_t_plot_org_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_org_idx++){
        if(st_s_hmigmon_peakhold[u1_a_area_org_idx][u1_t_plot_org_idx].u1_visible == (U1)TRUE){
            for(u1_t_plot_enm_idx = (U1)0U; u1_t_plot_enm_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_enm_idx++){
                if(st_s_hmigmon_peakhold[u1_t_area_enm_idx][u1_t_plot_enm_idx].u1_visible == (U1)TRUE){
                    if((st_s_hmigmon_peakhold[u1_a_area_org_idx][u1_t_plot_org_idx].s2_gcdn_frtbk  == st_s_hmigmon_peakhold[u1_t_area_enm_idx][u1_t_plot_enm_idx].s2_gcdn_frtbk )
                    && (st_s_hmigmon_peakhold[u1_a_area_org_idx][u1_t_plot_org_idx].s2_gcdn_rgtlft == st_s_hmigmon_peakhold[u1_t_area_enm_idx][u1_t_plot_enm_idx].s2_gcdn_rgtlft)){
                        st_s_hmigmon_peakhold[u1_t_area_enm_idx][u1_t_plot_enm_idx].u1_visible = (U1)FALSE;
                    }
                }
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonMakeBall(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_datachk                                                                                                  */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonMakeBall(void)
{
    ST_GMONINFO st_t_gmon_ball;
    U4          u4_t_now_dist;
    U1          u1_t_move_frtbk;
    U1          u1_t_move_rgtlft;
    U2          u2_t_gcdn_frtbk;
    U2          u2_t_gcdn_rgtlft;
    U1          u1_t_area_idx;
    U1          u1_t_datachk;

    st_t_gmon_ball.s2_gcdn_frtbk  = (S2)0;
    st_t_gmon_ball.s2_gcdn_rgtlft = (S2)0;
    st_t_gmon_ball.u1_visible     = (U1)FALSE;

    u1_t_move_frtbk  = u1_HMIGMON_MOVE_FRTBK();
    u1_t_move_rgtlft = u1_HMIGMON_MOVE_RGTLFT();
    u2_t_gcdn_frtbk  = u2_HMIGMON_GCDN_FRTBK();
    u2_t_gcdn_rgtlft = u2_HMIGMON_GCDN_RGTLFT();

    u1_t_datachk = u1_s_HmiGmonDataisOK(u1_t_move_frtbk, u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);

    if(u1_t_datachk == (U1)TRUE){
        st_t_gmon_ball.u1_visible = (U1)TRUE;

        u4_t_now_dist = u4_s_HmiGmonDistGetInfo(u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
        if(u4_t_now_dist <= (U4)HMIGMON_GCDN_DIST_MAX){
            vd_s_HmiGmonInfoUpdate(&st_t_gmon_ball, u1_t_move_frtbk, u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
        }
        else{
            u1_t_area_idx  = u1_s_HmiGmonJudgeArea(u1_t_move_frtbk, u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
            st_t_gmon_ball = st_s_hmigmon_maxguard[u1_t_area_idx];
        }
    }
    st_s_hmigmon_ball = st_t_gmon_ball;

    return(u1_t_datachk);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonMakeVal(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_datachk                                                                                                  */
/*===================================================================================================================================*/
static void       vd_s_HmiGmonMakeVal(void)
{
    ST_GMONINFO st_t_gmon_val;
    U1          u1_t_move_frtbk;
    U1          u1_t_move_rgtlft;
    U1          u1_t_val_frtbk;
    U1          u1_t_val_rgtlft;
    U1          u1_t_datachk;

    st_t_gmon_val.s2_gcdn_frtbk  = (S2)0;
    st_t_gmon_val.s2_gcdn_rgtlft = (S2)0;
    st_t_gmon_val.u1_visible     = (U1)FALSE;

    u1_t_move_frtbk  = u1_HMIGMON_MOVE_VAL_FRTBK();
    u1_t_move_rgtlft = u1_HMIGMON_MOVE_VAL_RGTLFT();
    u1_t_val_frtbk = u1_HMIGMON_VAL_FRTBK();
    u1_t_val_rgtlft = u1_HMIGMON_VAL_RGTLFT();
    
    u1_t_datachk = u1_s_HmiGmonValDataisOK(u1_t_move_frtbk, u1_t_move_rgtlft, u1_t_val_frtbk, u1_t_val_rgtlft);

    if(u1_t_datachk == (U1)TRUE){
        vd_s_HmiGmonInfoUpdate(&st_t_gmon_val, u1_t_move_frtbk, u1_t_move_rgtlft, (U2)u1_t_val_frtbk, (U2)u1_t_val_rgtlft);
    }

    st_s_hmigmon_val = st_t_gmon_val;

}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonPhInfoCheck(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_datachk                                                                                                  */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonPhInfoCheck(void)
{
    U4 u4_t_now_dist;
    U4 u4_t_old_dist;
    U1 u1_t_ph_resetreq;
    U1 u1_t_move_frtbk;
    U1 u1_t_move_rgtlft;
    U2 u2_t_gcdn_frtbk;
    U2 u2_t_gcdn_rgtlft;
    U1 u1_t_area_idx;
    U1 u1_t_datachk;
    U1 u1_t_loop;

    u1_t_ph_resetreq = u1_s_reset_flag;
    u1_t_move_frtbk  = u1_HMIGMON_MOVE_FRTBK();
    u1_t_move_rgtlft = u1_HMIGMON_MOVE_RGTLFT();
    u2_t_gcdn_frtbk  = u2_HMIGMON_GCDN_FRTBK();
    u2_t_gcdn_rgtlft = u2_HMIGMON_GCDN_RGTLFT();

    u1_t_datachk = u1_s_HmiGmonDataisOK(u1_t_move_frtbk, u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);

    switch(u1_t_ph_resetreq){
        case (U1)HMIGMON_PEAKHOLD_RESET_RESET:
            vd_s_HmiGmonHeakHoldInfoClear();
            for(u1_t_loop = (U1)0U; u1_t_loop < (U1)HMIGMON_NUM_ANGLE; u1_t_loop++){
                vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_loop][HMIGMON_GCDN_Y],
                                             (U2)st_s_hmigmon_peakhold_peak[u1_t_loop].s2_gcdn_frtbk);
                vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_loop][HMIGMON_GCDN_X],
                                             (U2)st_s_hmigmon_peakhold_peak[u1_t_loop].s2_gcdn_rgtlft);
            }
            break;
        case (U1)HMIGMON_PEAKHOLD_RESET_HOLD:
        default:
            if(u1_t_datachk == (U1)TRUE){
                u1_t_area_idx = u1_s_HmiGmonJudgeArea(u1_t_move_frtbk, u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
                u4_t_now_dist = u4_s_HmiGmonDistGetInfo(u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
                u4_t_old_dist = u4_s_HmiGmonOldDistGetInfo(u1_t_area_idx);
                if(u4_t_now_dist > u4_t_old_dist){
                    if(u4_t_now_dist <= (U4)HMIGMON_GCDN_DIST_MAX){
                        vd_s_HmiGmonInfoUpdate(&st_s_hmigmon_peakhold_peak[u1_t_area_idx],
                                                u1_t_move_frtbk,  u1_t_move_rgtlft, u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
                    }
                    else{
                        st_s_hmigmon_peakhold_peak[u1_t_area_idx] = st_s_hmigmon_maxguard[u1_t_area_idx];
                    }
                    vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_Y],
                                                 (U2)st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_frtbk);
                    vd_HMIGMON_GMONGCDN_HIS_WRITE(u2_HMIGMON_MAXHIST_RIM[u1_t_area_idx][HMIGMON_GCDN_X],
                                                 (U2)st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_rgtlft);
                }
            }
            break;
    }
    return(u1_t_datachk);
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonMakePhDiagram(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonMakePhDiagram(void)
{
    ST_PEAKINFO st_t_pt0;
    ST_PEAKINFO st_t_pt1;
    S4          s4_t_x_calc;
    S4          s4_t_y_calc;
    S2          s2_t_x_signed;
    S2          s2_t_y_signed;
    S2          s2_t_x;
    S2          s2_t_y;
    U1          u1_t_area_next_id;
    U2          u2_t_x_dist;
    U2          u2_t_y_dist;
    U1          u1_t_area_idx;
    U1          u1_t_plot_idx;

    for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
        u1_t_area_next_id = u1_t_area_idx + (U1)1U;
        if(u1_t_area_next_id >= (U1)HMIGMON_NUM_ANGLE){
            u1_t_area_next_id = (U1)0U;
        }

        st_t_pt0.s2_x = st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_rgtlft;
        st_t_pt0.s2_y = st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_frtbk;

        st_t_pt1.s2_x = st_s_hmigmon_peakhold_peak[u1_t_area_next_id].s2_gcdn_rgtlft;
        st_t_pt1.s2_y = st_s_hmigmon_peakhold_peak[u1_t_area_next_id].s2_gcdn_frtbk;

        u2_t_x_dist = u2_s_HmiGmonABS(st_t_pt1.s2_x, st_t_pt0.s2_x, &s2_t_x_signed);
        u2_t_y_dist = u2_s_HmiGmonABS(st_t_pt1.s2_y, st_t_pt0.s2_y, &s2_t_y_signed);

        if(u2_t_x_dist > u2_t_y_dist){
            st_t_pt0.u2_point = (u2_t_x_dist + (U2)HMIGMON_PT_HALFSIZE) / (U2)HMIGMON_PT_SIZE;
        }
        else{
            st_t_pt0.u2_point = (u2_t_y_dist + (U2)HMIGMON_PT_HALFSIZE) / (U2)HMIGMON_PT_SIZE;
        }
        s2_t_x = st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_rgtlft;
        s2_t_y = st_s_hmigmon_peakhold_peak[u1_t_area_idx].s2_gcdn_frtbk;

        st_s_hmigmon_peakhold[u1_t_area_idx][0].s2_gcdn_rgtlft = s2_t_x;
        st_s_hmigmon_peakhold[u1_t_area_idx][0].s2_gcdn_frtbk  = s2_t_y;
        st_s_hmigmon_peakhold[u1_t_area_idx][0].u1_visible     = (U1)TRUE;

        for(u1_t_plot_idx = (U1)1U; u1_t_plot_idx < (U1)HMIGMON_NUM_LINEPOINT; u1_t_plot_idx++){
            if(u1_t_plot_idx < st_t_pt0.u2_point){
                s4_t_x_calc = (S4)u2_t_x_dist * (S4)HMIGMON_DIS_ACCURACY * (S4)u1_t_plot_idx;
                s2_t_x      = (S2)(((s4_t_x_calc / (S4)st_t_pt0.u2_point) / (S4)HMIGMON_DIS_ACCURACY) * (S4)s2_t_x_signed);
                s2_t_x      = st_t_pt0.s2_x + s2_t_x;

                s4_t_y_calc = (S4)u2_t_y_dist * (S4)HMIGMON_DIS_ACCURACY * (S4)u1_t_plot_idx;
                s2_t_y      = (S2)(((s4_t_y_calc / (S2)st_t_pt0.u2_point) / (S2)HMIGMON_DIS_ACCURACY) * (S4)s2_t_y_signed);
                s2_t_y      = st_t_pt0.s2_y + s2_t_y;

                st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx].s2_gcdn_rgtlft = s2_t_x;
                st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx].s2_gcdn_frtbk  = s2_t_y;
                st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx].u1_visible     = (U1)TRUE;
            }
            else{
                st_s_hmigmon_peakhold[u1_t_area_idx][u1_t_plot_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonJudgeArea(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_move_frtbk                                                                                               */
/*                  U1 u1_a_move_rgtlft                                                                                              */
/*                  U2 u2_a_gcdn_frtbk                                                                                               */
/*                  U2 u2_a_gcdn_rgtlft                                                                                              */
/*  Return:         U1 u1_t_now_tan                                                                                                  */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonJudgeArea(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)
{
    U4 u4_t_work_tan;
    U1 u1_t_cnt_tan;
    U1 u1_t_get_tan;
    U1 u1_t_now_tan;

    u1_t_get_tan = (U1)FALSE;
    u1_t_now_tan = (U1)HMIGMON_TAN_NON;

    if(u2_a_gcdn_rgtlft != (U2)0U){
        u4_t_work_tan = ((U4)HMIGMON_TAN_ACCURACY * (U4)u2_a_gcdn_frtbk) / (U4)u2_a_gcdn_rgtlft;

        u1_t_now_tan = (U1)HMIGMON_TANSEAECH_NUM;
        for(u1_t_cnt_tan = (U1)0U; (u1_t_cnt_tan < (U1)HMIGMON_TANSEAECH_NUM) && (u1_t_get_tan == (U1)FALSE); u1_t_cnt_tan++){
            if(u4_t_work_tan < (U4)u2_HMIGMON_TANGENT_TBL[u1_t_cnt_tan]){
                u1_t_get_tan = (U1)TRUE;
                u1_t_now_tan = u1_t_cnt_tan;
            }
        }
        vd_s_HmiGmonCalcArea(&u1_t_now_tan, u1_a_move_frtbk, u1_a_move_rgtlft);
    }
    else{
        u1_t_now_tan = u1_s_HmiGmonMaxQuadrant(u1_a_move_frtbk);
    }

    return(u1_t_now_tan);
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonCalcArea(U1 *u1_ap_area, U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 *u1_ap_area                                                                                                   */
/*                  U1 u1_a_move_frtbk                                                                                               */
/*                  U1 u1_a_move_rgtlft                                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonCalcArea(U1 *u1_ap_area, U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft)
{
    U1 u1_t_now_gmove;

    u1_t_now_gmove = u1_HMIGMON_MOVEGET[u1_a_move_frtbk][u1_a_move_rgtlft];

    switch(u1_t_now_gmove){
        case (U1)HMIGMON_MOVE_2ND:
            *u1_ap_area = (U1)HMIGMON_TAN_ANGLE_180 - *u1_ap_area;
            break;
        case (U1)HMIGMON_MOVE_3RD:
            *u1_ap_area = (U1)HMIGMON_TAN_ANGLE_180 + *u1_ap_area;
            break;
        case (U1)HMIGMON_MOVE_4TH:
            if(*u1_ap_area != (U1)HMIGMON_TAN_NON){
                *u1_ap_area = (U1)HMIGMON_TAN_ANGLE_360 - *u1_ap_area;
            }
            break;
        case (U1)HMIGMON_MOVE_1ST:
        default:
            /* Do Nothing */
            break;
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonMaxQuadrant(U1 u1_a_move_frtbk)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_move_frtbk                                                                                               */
/*  Return:         U1 u1_t_tan                                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonMaxQuadrant(U1 u1_a_move_frtbk)
{
    U1 u1_t_tan;

    u1_t_tan = (U1)HMIGMON_TAN_ANGLE_90;

    if(u1_a_move_frtbk == (U1)HMIGMON_MOVE_BACK){
        u1_t_tan = (U1)HMIGMON_TAN_ANGLE_270;
    }

    return(u1_t_tan);
}

/*===================================================================================================================================*/
/*  static U4       u4_s_HmiGmonOldDistGetInfo(U1 u1_a_now_angle)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_now_angle                                                                                                */
/*  Return:         U4 u4_t_dist                                                                                                     */
/*===================================================================================================================================*/
static U4       u4_s_HmiGmonOldDistGetInfo(U1 u1_a_now_angle)
{
    S2 s2_t_calc_singed;
    U4 u4_t_dist;
    U2 u2_t_gcdn_frtbk;
    U2 u2_t_gcdn_rgtlft;

    u4_t_dist = (U4)HMIGMON_PEAKHOLD_DIST_DEF;

    u2_t_gcdn_frtbk = u2_s_HmiGmonABS(st_s_hmigmon_peakhold_peak[u1_a_now_angle].s2_gcdn_frtbk, (S2)0, &s2_t_calc_singed);
    u2_t_gcdn_frtbk = u2_t_gcdn_frtbk / (U2)HMIGMON_LSBCHNG_CANTOTFT;

    u2_t_gcdn_rgtlft = u2_s_HmiGmonABS(st_s_hmigmon_peakhold_peak[u1_a_now_angle].s2_gcdn_rgtlft, (S2)0, &s2_t_calc_singed);
    u2_t_gcdn_rgtlft = u2_t_gcdn_rgtlft / (U2)HMIGMON_LSBCHNG_CANTOTFT;

    if((u2_t_gcdn_frtbk  <= (U2)HMIGMON_GCDN_MAX)
    && (u2_t_gcdn_rgtlft <= (U2)HMIGMON_GCDN_MAX)){
        u4_t_dist = u4_s_HmiGmonDistGetInfo(u2_t_gcdn_frtbk, u2_t_gcdn_rgtlft);
    }

    return(u4_t_dist);
}

/*===================================================================================================================================*/
/*  static U4       u4_s_HmiGmonDistGetInfo(U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_gcdn_frtbk                                                                                               */
/*                  U1 u1_a_gcdn_rgtlft                                                                                              */
/*  Return:         U4 u4_t_dist                                                                                                     */
/*===================================================================================================================================*/
static U4       u4_s_HmiGmonDistGetInfo(U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)
{
    U4 u4_t_dist;

    u4_t_dist = ((U4)u2_a_gcdn_frtbk * (U4)u2_a_gcdn_frtbk) + ((U4)u2_a_gcdn_rgtlft * (U4)u2_a_gcdn_rgtlft);

    return(u4_t_dist);
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonInfoUpdate(ST_GMONINFO *stp_a_gmon, U1 u1_a_move_frtbk,                                              */
/*                                         U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_GMONINFO *   stp_a_gmon                                                                                       */
/*                  U1              u1_a_move_frtbk                                                                                  */
/*                  U1              u1_a_move_rgtlft                                                                                 */
/*                  U2              u2_a_gcdn_frtbk                                                                                  */
/*                  U2              u2_a_gcdn_rgtlft                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonInfoUpdate(ST_GMONINFO *stp_a_gmon, U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)
{
    switch(u1_a_move_frtbk){
        case (U1)HMIGMON_MOVE_BACK:
            stp_a_gmon->s2_gcdn_frtbk = (S2)HMIGMON_LSBCHNG_CANTOTFT * ((S2)0 - (S2)u2_a_gcdn_frtbk);
            break;
        case (U1)HMIGMON_MOVE_FRONT:
            stp_a_gmon->s2_gcdn_frtbk = (S2)HMIGMON_LSBCHNG_CANTOTFT * (S2)u2_a_gcdn_frtbk;
            break;
        default:
            /* Do Nothing */
            break;
    }

    switch(u1_a_move_rgtlft){
        case (U1)HMIGMON_MOVE_LEFT:
            stp_a_gmon->s2_gcdn_rgtlft = (S2)HMIGMON_LSBCHNG_CANTOTFT * ((S2)0 - (S2)u2_a_gcdn_rgtlft);
            break;
        case (U1)HMIGMON_MOVE_RIGHT:
            stp_a_gmon->s2_gcdn_rgtlft = (S2)HMIGMON_LSBCHNG_CANTOTFT * (S2)u2_a_gcdn_rgtlft;
            break;
        default:
            /* Do Nothing */
            break;
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_HmiGmonABS(S2 s2_a_data1, S2 s2_a_data2, S2 *s2_a_siged)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2      s2_a_data1                                                                                               */
/*                  S2      s2_a_data2                                                                                               */
/*                  S2 *    s2_a_siged                                                                                               */
/*  Return:         U2      u2_ret                                                                                                   */
/*===================================================================================================================================*/
static U2       u2_s_HmiGmonABS(S2 s2_a_data1, S2 s2_a_data2, S2 *s2_a_siged)
{
    U2 u2_ret;
    S2 s2_t_calcbuf;

    if(s2_a_data1 > s2_a_data2){
        s2_t_calcbuf = s2_a_data1 - s2_a_data2;
        u2_ret = (U2)s2_t_calcbuf;
        *s2_a_siged = (S2)1;
    }
    else{
        s2_t_calcbuf = s2_a_data2 - s2_a_data1;
        u2_ret = (U2)s2_t_calcbuf;
        *s2_a_siged = (S2)(-1);
    }

    return(u2_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_HmiGmonHeakHoldInfoClear(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonHeakHoldInfoClear(void)
{
    U1 u1_t_area_idx;

    for(u1_t_area_idx = (U1)0U; u1_t_area_idx < (U1)HMIGMON_NUM_ANGLE; u1_t_area_idx++){
        st_s_hmigmon_peakhold_peak[u1_t_area_idx] = st_HMIGMON_INVISIBLE_GMONINFO;
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_move_frtbk                                                                                               */
/*                  U1 u1_a_move_rgtlft                                                                                              */
/*                  U2 u2_a_gcdn_frtbk                                                                                               */
/*                  U2 u2_a_gcdn_rgtlft                                                                                              */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U2 u2_a_gcdn_frtbk, U2 u2_a_gcdn_rgtlft)
{
    U1 u1_t_ret;

    u1_t_ret = (U1)TRUE;
    if((u1_a_move_frtbk  >= (U1)HMIGMON_MOVE_NUM)
    || (u1_a_move_rgtlft >= (U1)HMIGMON_MOVE_NUM)
    || (u2_a_gcdn_frtbk  >  (U2)HMIGMON_GCDN_MAX)
    || (u2_a_gcdn_rgtlft >  (U2)HMIGMON_GCDN_MAX)){
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_HmiGmonValDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U1 u1_a_gcdn_frtbk, U1 u1_a_gcdn_rgtlft)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_move_frtbk                                                                                               */
/*                  U1 u1_a_move_rgtlft                                                                                              */
/*                  U1 u1_a_gcdn_frtbk                                                                                               */
/*                  U1 u1_a_gcdn_rgtlft                                                                                              */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_HmiGmonValDataisOK(U1 u1_a_move_frtbk, U1 u1_a_move_rgtlft, U1 u1_a_val_frtbk, U1 u1_a_val_rgtlft)
{
    U1 u1_t_ret;

    u1_t_ret = (U1)TRUE;
    if((u1_a_move_frtbk  >= (U1)HMIGMON_MOVE_NUM)
    || (u1_a_move_rgtlft >= (U1)HMIGMON_MOVE_NUM)
    || (u1_a_val_frtbk   >  (U1)HMIGMON_VAL_MAX)
    || (u1_a_val_rgtlft  >  (U1)HMIGMON_VAL_MAX)){
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static void     vd_s_HmiGmonPhInfoGuard(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonPhInfoGuard(void)
{
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)HMIGMON_NUM_ANGLE; u1_t_cnt++){
        /* Not Use Literal Define for Compiler constraints(sign conversion) */
        if((st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_frtbk  > (S2)((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT))
        || (st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_frtbk  < (S2)(((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * (-1)) )
        || (st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_rgtlft > (S2)((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT))
        || (st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_rgtlft < (S2)(((S2)HMIGMON_GCDN_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * (-1)))){
            st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_frtbk  = (S2)0;
            st_s_hmigmon_peakhold_peak[u1_t_cnt].s2_gcdn_rgtlft = (S2)0;
            st_s_hmigmon_peakhold_peak[u1_t_cnt].u1_visible     = (U1)FALSE;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiGmonPeakHoldReset(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiGmonPeakHoldReset(void)
{
    u1_s_reset_flag = (U1)HMIGMON_PEAKHOLD_RESET_RESET;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiGmonPeakHoldRelesRst(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiGmonPeakHoldRelesRst(void)
{
    u1_s_reset_flag = (U1)HMIGMON_PEAKHOLD_RESET_HOLD;
}

/*===================================================================================================================================*/
/*  U1      u1_g_HmiGmonGetHis(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_his                                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_HmiGmonGetHis(void)
{
    return(u1_s_gmon_his_ava);
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiGmonSetHis(const U1 u1_a_HIS)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_HIS                                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_HmiGmonSetHis(const U1 u1_a_HIS)
{
    u1_s_gmon_his_ava = u1_a_HIS;
    u1_s_gmon_his_ava = u1_s_gmon_his_ava & (U1)TRUE;

    vd_HMIGMON_GMONHISWRT_U1(u1_s_gmon_his_ava);
}

/*===================================================================================================================================*/
/* static void     vd_s_HmiGmonSetMaxGuardTable(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_HmiGmonSetMaxGuardTable(void)
{
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)HMIGMON_NUM_ANGLE; u1_t_cnt++){
            st_s_hmigmon_maxguard[u1_t_cnt].s2_gcdn_frtbk  = 
                (S2)(((S4)HMIGMON_GCDN_MAX * (S4)st_HMIGMON_MAXGUARD[u1_t_cnt].s2_gcdn_frtbk) / (S4)HMIGMON_MAXGUARD_DIV);
            st_s_hmigmon_maxguard[u1_t_cnt].s2_gcdn_rgtlft = 
                (S2)(((S4)HMIGMON_GCDN_MAX * (S4)st_HMIGMON_MAXGUARD[u1_t_cnt].s2_gcdn_rgtlft) / (S4)HMIGMON_MAXGUARD_DIV);
            st_s_hmigmon_maxguard[u1_t_cnt].u1_visible     = st_HMIGMON_MAXGUARD[u1_t_cnt].u1_visible;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  P0.0.0-600A-1   05/20/2013  YI      New.                                                                                         */
/*  P0.0.0-600A-2   11/08/2013  YS      Peak hold 30 degree division Step 2 correspondence, MAX Guard Compatible.                    */
/*  P0.0.0-740A-1   03/28/2014  MK      MMAS Add Peak Hold Information Guard.                                                        */
/*  P0.0.0-740A-2   10/14/2014  TO      Ported to the Next side to retain the peak hold value during Sleep.                          */
/*                                      The address provided in the G monitor peak hold value providing process is                   */
/*                                          changed to the peak hold maximum value information top address for each area.            */
/*                                      Change initialization for peak hold information guard processing to macro setting.           */
/*  P0.0.1          06/07/2017  SM      Delete:#pragma segment                                                                       */
/*  0.0.2           06/13/2017  SM      Add:Reset & Reles Reset. Change for BSW3G & 310B-CV.                                         */
/*  0.0.3           10/03/2017  SM      pixel Range 20step -> 80step                                                                 */
/*  0.0.4           11/09/2017  SM      Change:DrvModeSelect=SPORT -> Move                                                           */
/*  0.0.5           10/22/2018  HT      Correct:u1_s_reset_flag R/W Labels.                                                          */
/*                                      Update:Judge Display/Reset in All DriveMode.                                                 */
/*  0.1.0           12/14/2020  SK      Add:G-ball Disp Numerical notice function                                                    */
/*  0.2.0           06/05/2021  SK      BugFix:Add peakhold function. Change G-ball Disp Numerical notice function IF                */
/*  0.3.0           05/19/2022  HA      Update:History of grav is recorded in RIM and default of that is ON                          */
/*  1.0.0           01/10/2024  TK      19PFv3 Standard Spec Support (C_GMN-CSTD)                                                    */
/*  1.0.1           07/08/2024  SM(DT)  Bug Fix: G-Monitor Max history info is not hidden when abnormality occurs                    */
/*                                                                                                                                   */
/*  YI = Yuusuke Iwano                                                                                                               */
/*  YS = Yuta Suzuki                                                                                                                 */
/*  MK = Makoto Kumon                                                                                                                */
/*  TO = Takeshi Otoi                                                                                                                */
/*  SM = Shouhei Matsumoto                                                                                                           */
/*  HT = Hirotaka Takekoshi, Denso Techno                                                                                            */
/*  SK = Shintaro Kanou, Denso Techno                                                                                                */
/*  HA = Hiroki Asano, PRD                                                                                                           */
/*  TK = Toru Kamishina, Denso Techno                                                                                                */
/*  SM(DT) = Shota Maegawa, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
