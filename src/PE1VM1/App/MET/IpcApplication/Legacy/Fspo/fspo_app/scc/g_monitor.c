/* 3.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-Spo G Monitor                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GMNTR_C_MAJOR                            (3)
#define GMNTR_C_MINOR                            (0)
#define GMNTR_C_PATCH                            (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "g_monitor_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GMNTR_C_MAJOR != GMNTR_H_MAJOR) || \
     (GMNTR_C_MINOR != GMNTR_H_MINOR) || \
     (GMNTR_C_PATCH != GMNTR_H_PATCH))
#error "g_monitor.c and g_monitor.h : source and header files are inconsistent!"
#endif

#if ((GMNTR_C_MAJOR != GMNTR_CFG_H_MAJOR) || \
     (GMNTR_C_MINOR != GMNTR_CFG_H_MINOR) || \
     (GMNTR_C_PATCH != GMNTR_CFG_H_PATCH))
#error "g_monitor.c and g_monitor_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GMNTR_PLUS                               (0U)                   /* Plus                                                      */
#define GMNTR_MINUS                              (1U)                   /* Minus                                                     */

#define GMNTR_NUMINV                             (-1)                   /* S to U conversion factor                                  */

#define GMNTR_OFF                                (0U)                   /* OFF State                                                 */
#define GMNTR_INIT_OR_FAIL                       (1U)                   /* Initial state or Fail state                               */
#define GMNTR_ERR                                (2U)                   /* Invalid definite state                                    */
#define GMNTR_UPDT                               (3U)                   /* Update state                                              */

#define GMNTR_NONRCV                             (0U)                   /* Signal not received                                       */
#define GMNTR_RCV                                (1U)                   /* Normal signal received                                    */

#define GMNTR_PKHLD_NON                          (0U)
#define GMNTR_PKHLD_ACT                          (1U)
#define GMNTR_PKHLD_RTGR                         (2U)
#define GMNTR_PKHLD_LARGE                        (0U)
#define GMNTR_PKHLD_SAME                         (1U)
#define GMNTR_PKHLD_SMALL                        (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2 u2_val;                                                          /* Absolute value                                            */
    U1 u1_signinf;                                                      /* Code information                                          */
}ST_GMNTR_SIGN_U2DAT;

typedef struct {
    U4 u4_val;                                                          /* Absolute value                                            */
    U1 u1_signinf;                                                      /* Code information                                          */
}ST_GMNTR_SIGN_U4DAT;

typedef struct {
    U1 u1_fb_gval;                                                      /* Absolute FB value                                         */
    U1 u1_fb_gvaldrc;                                                   /* Direction of gravity acceleration (front and back)        */
    U1 u1_lr_gval;                                                      /* Absolute LR value                                         */
    U1 u1_lr_gvaldrc;                                                   /* Direction of gravity acceleration (left and right)        */
}ST_GMNTR_COORD_U1DAT;

typedef struct {
    S2 s2_glval;                                                        /* GL Sensor value                                           */
}ST_GMNTR_INCDAT;

typedef struct {
    S4 s4_sub_fb;                                                       /* GL Sensor value - GL Zero value(front and back)           */
    S4 s4_sub_lr;                                                       /* GL Sensor value - GL Zero value(left and right)           */
}ST_GMNTR_SUBDAT;

/* G-Ball Calculation Information */
typedef struct{
    ST_GMNTR_INCDAT st_buf_fb[GMNTR_GRVTY_AVENUM];                      /* Gravity(front and back) average calculation buffer        */
    ST_GMNTR_INCDAT st_buf_lr[GMNTR_GRVTY_AVENUM];                      /* Gravity(left and right) average calculation buffer        */
    U1 u1_dat_adr;                                                      /* Latest data position                                      */
    U1 u1_rcvd;                                                         /* Received state                                            */
    U1 u1_updt_cnt;                                                     /* Calculation update timing counter                         */
    U2 u2_failcnt;                                                      /* G-Ball abnormal signal reception time counter             */
    U1 u1_gb_sts;                                                       /* Gravity acceleration average calculation state            */
}ST_GMNTR_G_VAR;

/* Steering Angle Calculation Information */
typedef struct{
    S4 s4_ave;                                                          /* Weighted average steering angle[LSB:0.1]                  */
}ST_GMNTR_ANGL_VAR;

/* Brake Pressure Calculation Information */
typedef struct{
    S2 s2_vlddat;                                                       /* Brake pedal driver required acceleration                  */
    U2 u2_failcnt;                                                      /* Abnormal signal reception counter                         */
}ST_GMNTR_BRKPRSS_VAR;

/* Accelerator Opening Calculation Information */
typedef struct{
    U2 u2_ave;                                                          /* Weighted average of accelerator opening[LSB:0.1]          */
}ST_GMNTR_ACCEL_VAR;

/* Communication Data between CPUs */
typedef struct{
    U1 u1_fb_gdrc;                                                      /* Direction of gravity acceleration (front and back)        */
    U1 u1_fb_gvaldrc;
    U2 u2_fb_gpos;                                                      /* Gravity acceleration coordinate   (fornt and back)        */
    U1 u1_fb_gval;                                                      /* Gravity acceleration value        (front and back)        */
    U1 u1_lr_gdrc;                                                      /* Direction of gravity acceleration (left and right)        */
    U1 u1_lr_gvaldrc;
    U2 u2_lr_gpos;                                                      /* Gravity acceleration coordinate   (left and right)        */
    U1 u1_lr_gval;                                                      /* Gravity acceleration value        (left and right)        */
    U1 u1_angldrc;                                                      /* Steering angle direction                                  */
    U1 u1_anglval;                                                      /* Steering angle                                            */
    U1 u1_brkprss;                                                      /* Brake pressure                                            */
    U1 u1_accel;                                                        /* Accelerator opening                                       */
}ST_GMNTR_OUTDATA;

/* Gmonitor Disp Status Information */
typedef struct{
    U1 u1_g_sts;                                                        /* Gravity Display Status Information                        */
    U1 u1_angl_sts;                                                     /* Steering Angle Display Status Information                 */
    U1 u1_brkprss_sts;                                                  /* Brake Pressure Display Status Information                 */
    U1 u1_accel_sts;                                                    /* Accelerator Opening Display Status Information            */
}ST_GMNTR_DISP_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_GMNTR_G_VAR       st_s_gmt_g;                                 /* G-Ball Calculation Information                            */
static ST_GMNTR_ANGL_VAR    st_s_gmt_angl;                              /* Steering Angle Calculation Information                    */
static ST_GMNTR_BRKPRSS_VAR st_s_gmt_brk;                               /* Brake Pressure Calculation Information                    */
static ST_GMNTR_ACCEL_VAR   st_s_gmt_accel;                             /* Accelerator Opening Calculation Information               */
static ST_GMNTR_OUTDATA     st_s_comdat;                                /* Communication Data between CPUs                           */
static U1                   u1_s_gmt_brk_updt_cnt;                      /* Brake Pressure Update Counter                             */
static U1                   u1_s_gmt_accel_updt_cnt;                    /* Accelerater Opening Update Counter                        */
static U1                   u1_s_gmt_pkhld_cnt;
static U1                   u1_s_gmt_pkhld_pre_cmpr;
static ST_GMNTR_COORD_U1DAT st_s_gmt_pkhld_pre;                         /* Latest G-monitor value/drc                                */
static ST_GMNTR_DISP_STS    st_s_gmt_dispsts;                           /* G-monitor Display Status  Information                     */
static U1                   u1_s_gmt_angl_fail_cnt;                     /* Angle Fail Counter Information                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void                 vd_s_GmntrClrGballDat(void);
static void                 vd_s_GmntrClrAnglDat(void);
static void                 vd_s_GmntrClrBrkDat(void);
static void                 vd_s_GmntrClrAccelDat(void);
static void                 vd_s_GballInc(const ST_FSPOSNSR_INCARG* stp_a_incarg);
static void                 vd_s_GballBufUpdt(ST_GMNTR_INCDAT st_ap_fbval, ST_GMNTR_INCDAT st_ap_lrval);
static void                 vd_s_BrkprssGetSig(const ST_FSPOSNSR_INCARG* stp_a_incarg);
static void                 vd_s_GmntrBallUpdt(void);
static void                 vd_s_GmntrBallComDtCal(void);
static S2                   s2_s_GmntrGlvlAveCal(const ST_GMNTR_INCDAT* st_ap_buf);
static ST_GMNTR_SIGN_U2DAT  st_s_GmntrS2SizeChg(S2 s2_a_orgval);
static ST_GMNTR_SIGN_U4DAT  st_s_GmntrS4SizeChg(S4 s4_a_orgval);
static U2                   u2_s_GmntrGetComdat(U2 u2_a_ave, U2 u2_a_lsb, U2 u2_a_max);
static void                 vd_s_GmntrAngleUpdt(void);
static void                 vd_s_GmntrBrkprssUpdt(void);
static void                 vd_s_GmntrAccelUpdt(void);
static void                 vd_s_GmntrSetMoveDrct(const U1 u1_a_fb_signinf, const U1 u1_a_lr_signinf);
static U1                   u1_s_GmntrPkhldJdg(U1 u1_a_pre_fb_gval, U1 u1_a_pre_lr_gval,U1 u1_a_latest_fb_gval, U1 u1_a_latest_lr_gval);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GmntrInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GmntrInit(void)
{
    vd_s_GmntrClrGballDat();
    vd_s_GmntrClrAnglDat();
    vd_s_GmntrClrBrkDat();
    vd_s_GmntrClrAccelDat();

    st_s_gmt_g.u1_updt_cnt  = (U1)U1_MAX;
    st_s_gmt_g.u2_failcnt   = (U2)0U;
    st_s_gmt_brk.u2_failcnt = (U2)0U;
    st_s_gmt_g.u1_gb_sts    = (U1)GMNTR_OFF;

    st_s_comdat.u1_fb_gdrc = (U1)GMNTR_FB_DRC_FAIL;
    st_s_comdat.u1_fb_gvaldrc = (U1)GMNTR_FB_DRC_FAIL;
    st_s_comdat.u2_fb_gpos = (U2)GMNTR_POS_FAIL;
    st_s_comdat.u1_fb_gval = (U1)GMNTR_VAL_FAIL;
    st_s_comdat.u1_lr_gdrc = (U1)GMNTR_LR_DRC_FAIL;
    st_s_comdat.u1_lr_gvaldrc = (U1)GMNTR_LR_DRC_FAIL;
    st_s_comdat.u2_lr_gpos = (U2)GMNTR_POS_FAIL;
    st_s_comdat.u1_lr_gval = (U1)GMNTR_VAL_FAIL;
    st_s_comdat.u1_angldrc = (U1)GMNTR_ANGLDRC_FAIL;
    st_s_comdat.u1_anglval = (U1)GMNTR_ANGL_FAIL;
    st_s_comdat.u1_brkprss = (U1)GMNTR_BRKPRS_FAIL;
    st_s_comdat.u1_accel   = (U1)GMNTR_ACCEL_FAIL;
    u1_s_gmt_pkhld_cnt      = (U1)U1_MAX;
    u1_s_gmt_pkhld_pre_cmpr = (U1)GMNTR_PKHLD_SAME;
    st_s_gmt_pkhld_pre.u1_fb_gval = (U1)GMNTR_VAL_FAIL;
    st_s_gmt_pkhld_pre.u1_lr_gval = (U1)GMNTR_VAL_FAIL;
    st_s_gmt_pkhld_pre.u1_fb_gvaldrc = (U1)GMNTR_FB_DRC_FAIL;
    st_s_gmt_pkhld_pre.u1_lr_gvaldrc = (U1)GMNTR_LR_DRC_FAIL;
    st_s_gmt_dispsts.u1_g_sts = (U1)GMNTR_G_VSBL_INIT_FAIL;
    st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_INIT_FAIL;
    st_s_gmt_dispsts.u1_brkprss_sts = (U1)GMNTR_BRKPRS_VSBL_INIT_FAIL;
    st_s_gmt_dispsts.u1_accel_sts = (U1)GMNTR_ACCEL_VSBL_INIT_FAIL;
    u1_s_gmt_angl_fail_cnt = (U1)0U;
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrClrGballDat(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrClrGballDat(void)
{
    U1 u1_t_idx;

    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)GMNTR_GRVTY_AVENUM; u1_t_idx++){
        st_s_gmt_g.st_buf_fb[u1_t_idx].s2_glval   = (S2)GMNTR_POS_CENTER;
        st_s_gmt_g.st_buf_lr[u1_t_idx].s2_glval   = (S2)GMNTR_POS_CENTER;
    }
    st_s_gmt_g.u1_dat_adr = (U1)0U;
    st_s_gmt_g.u1_rcvd    = (U1)GMNTR_NONRCV;
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrClrAnglDat(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrClrAnglDat(void)
{
    st_s_gmt_angl.s4_ave = (S4)0;
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrClrBrkDat(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrClrBrkDat(void)
{
    st_s_gmt_brk.s2_vlddat = (S2)0;

    u1_s_gmt_brk_updt_cnt  = (U1)U1_MAX;
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrClrAccelDat(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrClrAccelDat(void)
{
    st_s_gmt_accel.u2_ave   = (U2)0U;

    u1_s_gmt_accel_updt_cnt = (U1)U1_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_GmntrInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_incarg                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GmntrInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    vd_s_GballInc(stp_a_incarg);
    vd_s_BrkprssGetSig(stp_a_incarg);
}

/*===================================================================================================================================*/
/*  static void vd_s_GballInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_incarg                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GballInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    U2                   u2_t_sig_fail;
    U1                   u1_t_sig_rcv;
    U1                   u1_t_gl_invalid;
    ST_GMNTR_INCDAT      st_t_workval_fb;
    ST_GMNTR_INCDAT      st_t_workval_lr;

    u2_t_sig_fail = stp_a_incarg->u2_sigfail & (U2)GMNTR_GBALL_FAILCHK;
    if(u2_t_sig_fail == (U2)0U){
        u1_t_sig_rcv = stp_a_incarg->u1_rcvd & (U1)GMNTR_GBALL_RCVDCHK;
        if(u1_t_sig_rcv == (U1)GMNTR_GBALL_RCVDCHK){
            u1_t_gl_invalid  = stp_a_incarg->st_inc_vsc1g12.u1_gxf;
            u1_t_gl_invalid |= stp_a_incarg->st_inc_vsc1g12.u1_gyf;
            u1_t_gl_invalid |= stp_a_incarg->st_inc_vsc1g12.u1_gxiv;
            u1_t_gl_invalid |= stp_a_incarg->st_inc_vsc1g12.u1_gyiv;
            if(u1_t_gl_invalid == (U1)0U){
                st_t_workval_fb.s2_glval = stp_a_incarg->st_inc_vsc1g12.s2_gxhr0;
                st_t_workval_lr.s2_glval = stp_a_incarg->st_inc_vsc1g12.s2_gyhr0;

                if(st_s_gmt_g.u1_dat_adr < (U1)GMNTR_GRVTY_AVENUM){
                }
                else{
                    st_s_gmt_g.u1_dat_adr = (U1)0U;
                }
                vd_s_GballBufUpdt(st_t_workval_fb, st_t_workval_lr);
                st_s_gmt_g.u1_rcvd    = (U1)GMNTR_RCV;
                st_s_gmt_g.u2_failcnt = (U2)0U;
            }
            else{
                st_s_gmt_g.u2_failcnt = ((st_s_gmt_g.u2_failcnt < (U2)U2_MAX) ? (st_s_gmt_g.u2_failcnt + (U2)1U) : (U2)U2_MAX);
            }
        }
        else{
            if(st_s_gmt_g.u2_failcnt > (U2)0U){
                st_s_gmt_g.u2_failcnt = ((st_s_gmt_g.u2_failcnt < (U2)U2_MAX) ? (st_s_gmt_g.u2_failcnt + (U2)1U) : (U2)U2_MAX);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GballBufUpdt(ST_GMNTR_INCDAT st_ap_fbval, ST_GMNTR_INCDAT st_ap_lrval)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_GMNTR_INCDAT st_ap_fbval                                                                                      */
/*                  ST_GMNTR_INCDAT st_ap_lrval                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GballBufUpdt(ST_GMNTR_INCDAT st_ap_fbval, ST_GMNTR_INCDAT st_ap_lrval)
{
    U1      u1_t_idx;

    if(st_s_gmt_g.u1_rcvd == (U1)GMNTR_NONRCV){
        for( u1_t_idx = (U1)0U; u1_t_idx < (U1)GMNTR_GRVTY_AVENUM; u1_t_idx++){
            st_s_gmt_g.st_buf_fb[u1_t_idx] = st_ap_fbval;
            st_s_gmt_g.st_buf_lr[u1_t_idx] = st_ap_lrval;
        }
    }
    else{
        if(st_s_gmt_g.u1_dat_adr >= (U1)GMNTR_GRVTY_AVENUM){
            st_s_gmt_g.u1_dat_adr = (U1)0U;
        }
        st_s_gmt_g.st_buf_fb[st_s_gmt_g.u1_dat_adr] = st_ap_fbval;
        st_s_gmt_g.st_buf_lr[st_s_gmt_g.u1_dat_adr] = st_ap_lrval;
        st_s_gmt_g.u1_dat_adr = ((st_s_gmt_g.u1_dat_adr < ((U1)GMNTR_GRVTY_AVENUM - (U1)1U)) ? (st_s_gmt_g.u1_dat_adr + (U1)1U) : (U1)0U);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_BrkprssGetSig(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_incarg                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BrkprssGetSig(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    U2      u2_t_sig_fail;
    U1      u1_t_sig_rcv;
    U1      u1_t_valid;

    u2_t_sig_fail = stp_a_incarg->u2_sigfail & (U2)GMNTR_OILPRSS_FAILCHK;
    if(u2_t_sig_fail == (U2)0U){
        u1_t_sig_rcv = stp_a_incarg->u1_rcvd & (U1)GMNTR_OILPRSS_RCVDCHK;
        if(u1_t_sig_rcv == (U1)GMNTR_OILPRSS_RCVDCHK){
            u1_t_valid  = stp_a_incarg->st_inc_vsc1g30.u1_fbkdrsys;
            if(u1_t_valid == (U1)GMNTR_BRKPRS_BRK_ACCL_VALID){
                st_s_gmt_brk.u2_failcnt = (U2)0U;
                st_s_gmt_brk.s2_vlddat = stp_a_incarg->st_inc_vsc1g30.s2_fbkdr_ax;
            }
            else{
                st_s_gmt_brk.u2_failcnt = ((st_s_gmt_brk.u2_failcnt < (U2)U2_MAX) ? (st_s_gmt_brk.u2_failcnt + (U2)1U) : (U2)U2_MAX);
            }
        }
        else{
            if(st_s_gmt_brk.u2_failcnt > (U2)0U){
                st_s_gmt_brk.u2_failcnt = ((st_s_gmt_brk.u2_failcnt < (U2)U2_MAX) ? (st_s_gmt_brk.u2_failcnt + (U2)1U) : (U2)U2_MAX);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_GmntrTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_evtbit                                                                                                   */
/*                  U2 u2_a_sigfail                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GmntrTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)
{
    U2 u2_t_igon;
    U2 u2_t_fail;

    u2_t_igon = u2_a_evtbit  & (U2)GMNTR_IGON_EVT;
    u2_t_fail = u2_a_sigfail & (U2)GMNTR_GBALL_FAILCHK;
    if(u2_t_igon != (U2)GMNTR_IGON_EVT){
        vd_s_GmntrClrGballDat();
        st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
        st_s_gmt_g.u2_failcnt  = (U2)0U;
        st_s_gmt_g.u1_gb_sts   = (U1)GMNTR_OFF;
    }
    else if(u2_t_fail != (U2)0U){
        vd_s_GmntrClrGballDat();
        st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
        st_s_gmt_g.u1_gb_sts   = (U1)GMNTR_INIT_OR_FAIL;
    }
    else{
        switch(st_s_gmt_g.u1_gb_sts){
            case (U1)GMNTR_OFF:
                if(st_s_gmt_g.u1_rcvd == (U1)GMNTR_RCV){
                    st_s_gmt_g.u1_gb_sts = (U1)GMNTR_UPDT;
                }
                else{
                    st_s_gmt_g.u1_gb_sts = (U1)GMNTR_INIT_OR_FAIL;
                }
                break;
            case (U1)GMNTR_INIT_OR_FAIL:
                if(st_s_gmt_g.u1_rcvd == (U1)GMNTR_RCV){
                    st_s_gmt_g.u1_gb_sts = (U1)GMNTR_UPDT;
                }
                else{
                    if(st_s_gmt_g.u2_failcnt > (U2)GMNTR_GBALL_FAILTIM){
                        vd_s_GmntrClrGballDat();
                        st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
                        st_s_gmt_g.u1_gb_sts   = (U1)GMNTR_ERR;
                    }
                }
                break;
            case (U1)GMNTR_ERR:
                if(st_s_gmt_g.u1_rcvd == (U1)GMNTR_RCV){
                    st_s_gmt_g.u1_gb_sts = (U1)GMNTR_UPDT;
                }
                break;
            case (U1)GMNTR_UPDT:
                if(st_s_gmt_g.u2_failcnt > (U2)GMNTR_GBALL_FAILTIM){
                    vd_s_GmntrClrGballDat();
                    st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
                    st_s_gmt_g.u1_gb_sts   = (U1)GMNTR_ERR;
                }
                else if(st_s_gmt_g.u2_failcnt > (U2)0U){
                    st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
                }
                else{
                    st_s_gmt_g.u1_updt_cnt = (st_s_gmt_g.u1_updt_cnt < (U1)U1_MAX) ? (st_s_gmt_g.u1_updt_cnt + (U1)1U) : (U1)U1_MAX;
                }
                break;
            default:
                vd_s_GmntrClrGballDat();
                st_s_gmt_g.u1_updt_cnt = (U1)U1_MAX;
                st_s_gmt_g.u2_failcnt  = (U2)0U;
                st_s_gmt_g.u1_gb_sts   = (U1)GMNTR_INIT_OR_FAIL;
                break;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_GmntrUpdt(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GmntrUpdt(void)
{
    vd_s_GmntrBallUpdt();
    vd_s_GmntrAngleUpdt();
    vd_s_GmntrBrkprssUpdt();
    vd_s_GmntrAccelUpdt();
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrBallUpdt(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrBallUpdt(void)
{
    switch(st_s_gmt_g.u1_gb_sts){
        case (U1)GMNTR_UPDT:
            if(st_s_gmt_g.u1_updt_cnt >= (U1)GMNTR_UPDTTIM){
                st_s_gmt_dispsts.u1_g_sts = (U1)GMNTR_G_VSBL_VALID;
                vd_s_GmntrBallComDtCal();
                st_s_gmt_g.u1_updt_cnt = (U1)0U;
            }
            break;
        case (U1)GMNTR_ERR:
            st_s_comdat.u1_fb_gdrc = (U1)GMNTR_FB_DRC_FAIL;
            st_s_comdat.u1_lr_gdrc = (U1)GMNTR_LR_DRC_FAIL;
            st_s_comdat.u2_fb_gpos = (U2)GMNTR_POS_FAIL;
            st_s_comdat.u2_lr_gpos = (U2)GMNTR_POS_FAIL;
            st_s_comdat.u1_fb_gval = (U1)GMNTR_VAL_FAIL;
            st_s_comdat.u1_lr_gval = (U1)GMNTR_VAL_FAIL;
            u1_s_gmt_pkhld_cnt      = (U1)U1_MAX;
            u1_s_gmt_pkhld_pre_cmpr = (U1)GMNTR_PKHLD_SAME;
            st_s_gmt_dispsts.u1_g_sts = (U1)GMNTR_G_VSBL_INIT_FAIL;
            break;
        case (U1)GMNTR_OFF:
        case (U1)GMNTR_INIT_OR_FAIL:
        default:
            st_s_comdat.u1_fb_gdrc = (U1)GMNTR_FB_DRC_FAIL;
            st_s_comdat.u1_lr_gdrc = (U1)GMNTR_LR_DRC_FAIL;
            st_s_comdat.u2_fb_gpos = (U2)GMNTR_POS_FAIL;
            st_s_comdat.u2_lr_gpos = (U2)GMNTR_POS_FAIL;
            st_s_comdat.u1_fb_gval = (U1)GMNTR_VAL_FAIL;
            st_s_comdat.u1_lr_gval = (U1)GMNTR_VAL_FAIL;
            u1_s_gmt_pkhld_cnt      = (U1)U1_MAX;
            u1_s_gmt_pkhld_pre_cmpr = (U1)GMNTR_PKHLD_SAME;
            st_s_gmt_dispsts.u1_g_sts = (U1)GMNTR_G_VSBL_INIT_FAIL;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrBallComDtCal(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrBallComDtCal(void)
{
    S2                      s2_t_ave_fb;
    S2                      s2_t_ave_lr;
    ST_GMNTR_SIGN_U2DAT     st_t_dat_fb;
    ST_GMNTR_SIGN_U2DAT     st_t_dat_lr;
    U1                      u1_t_latest_fb_val;
    U1                      u1_t_latest_lr_val;
    U1                      u1_t_latest_fb_valdrc;
    U1                      u1_t_latest_lr_valdrc;
    U1                      u1_t_pre_fb_valdrc;
    U1                      u1_t_pre_lr_valdrc;
    U1                      u1_t_pkhld_sts;

    u1_t_pre_fb_valdrc = st_s_comdat.u1_fb_gvaldrc;
    u1_t_pre_lr_valdrc = st_s_comdat.u1_lr_gvaldrc;
    s2_t_ave_fb = s2_s_GmntrGlvlAveCal(&st_s_gmt_g.st_buf_fb[0]);
    s2_t_ave_lr = s2_s_GmntrGlvlAveCal(&st_s_gmt_g.st_buf_lr[0]);

    st_t_dat_fb = st_s_GmntrS2SizeChg(s2_t_ave_fb);
    st_t_dat_lr = st_s_GmntrS2SizeChg(s2_t_ave_lr);

    vd_s_GmntrSetMoveDrct(st_t_dat_fb.u1_signinf, st_t_dat_lr.u1_signinf);

    st_s_comdat.u2_fb_gpos = u2_s_GmntrGetComdat(st_t_dat_fb.u2_val, (U2)GMNTR_POS_LSB, (U2)GMNTR_POS_MAX);
    st_s_comdat.u2_lr_gpos = u2_s_GmntrGetComdat(st_t_dat_lr.u2_val, (U2)GMNTR_POS_LSB, (U2)GMNTR_POS_MAX);

    st_t_dat_fb.u2_val = (st_t_dat_fb.u2_val < ((U2)U2_MAX - (U2)GMNTR_VAL_RNDOFSET)) ? (st_t_dat_fb.u2_val + (U2)GMNTR_VAL_RNDOFSET) : (U2)U2_MAX;
    st_t_dat_lr.u2_val = (st_t_dat_lr.u2_val < ((U2)U2_MAX - (U2)GMNTR_VAL_RNDOFSET)) ? (st_t_dat_lr.u2_val + (U2)GMNTR_VAL_RNDOFSET) : (U2)U2_MAX;

    u1_t_latest_fb_val = u2_s_GmntrGetComdat(st_t_dat_fb.u2_val, (U2)GMNTR_BALLVAL_LSB, (U2)GMNTR_BALLVAL_MAX);
    u1_t_latest_lr_val = u2_s_GmntrGetComdat(st_t_dat_lr.u2_val, (U2)GMNTR_BALLVAL_LSB, (U2)GMNTR_BALLVAL_MAX);
    u1_t_latest_fb_valdrc = st_s_comdat.u1_fb_gvaldrc;
    u1_t_latest_lr_valdrc = st_s_comdat.u1_lr_gvaldrc;

    u1_t_pkhld_sts = u1_s_GmntrPkhldJdg(st_s_gmt_pkhld_pre.u1_fb_gval, st_s_gmt_pkhld_pre.u1_lr_gval,u1_t_latest_fb_val,u1_t_latest_lr_val);
    if(u1_t_pkhld_sts == (U1)GMNTR_PKHLD_NON){
        st_s_comdat.u1_fb_gval = u1_t_latest_fb_val;
        st_s_comdat.u1_lr_gval = u1_t_latest_lr_val;
    }else if(u1_t_pkhld_sts == (U1)GMNTR_PKHLD_RTGR){
        st_s_comdat.u1_fb_gval = st_s_gmt_pkhld_pre.u1_fb_gval;
        st_s_comdat.u1_lr_gval = st_s_gmt_pkhld_pre.u1_lr_gval;
        st_s_comdat.u1_fb_gvaldrc = st_s_gmt_pkhld_pre.u1_fb_gvaldrc;
        st_s_comdat.u1_lr_gvaldrc = st_s_gmt_pkhld_pre.u1_lr_gvaldrc;
    }else{
        st_s_comdat.u1_fb_gvaldrc = u1_t_pre_fb_valdrc;
        st_s_comdat.u1_lr_gvaldrc = u1_t_pre_lr_valdrc;
    }

    st_s_gmt_pkhld_pre.u1_fb_gval = u1_t_latest_fb_val;
    st_s_gmt_pkhld_pre.u1_lr_gval = u1_t_latest_lr_val;
    st_s_gmt_pkhld_pre.u1_fb_gvaldrc = u1_t_latest_fb_valdrc;
    st_s_gmt_pkhld_pre.u1_lr_gvaldrc = u1_t_latest_lr_valdrc;
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrSetMoveDrct(const U1 u1_a_fb_signinf, const U1 u1_a_lr_signinf)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_fb_signinf                                                                                         */
/*                  const U1 u1_a_lr_signinf                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrSetMoveDrct(const U1 u1_a_fb_signinf, const U1 u1_a_lr_signinf)
{
    U1                      u1_t_snsrstsbit;

    u1_t_snsrstsbit  = (U1)GMNTR_SNSRSTSBIT_ANGLE_90;
    u1_t_snsrstsbit |= (U1)GMNTR_SNSRSTSBIT_DRCT_BACK;

    st_s_comdat.u1_fb_gdrc = u1_sp_GMNTR_SNSRTYP_FB_TBL[u1_t_snsrstsbit][u1_a_fb_signinf];
    st_s_comdat.u1_lr_gdrc = u1_sp_GMNTR_SNSRTYP_LR_TBL[u1_t_snsrstsbit][u1_a_lr_signinf];
    st_s_comdat.u1_fb_gvaldrc = u1_sp_GMNTR_SNSRTYP_FB_TBL[u1_t_snsrstsbit][u1_a_fb_signinf];
    st_s_comdat.u1_lr_gvaldrc = u1_sp_GMNTR_SNSRTYP_LR_TBL[u1_t_snsrstsbit][u1_a_lr_signinf];
}

/*===================================================================================================================================*/
/*  static S2       s2_s_GmntrGlvlAveCal(const ST_GMNTR_INCDAT* st_ap_buf)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_GMNTR_INCDAT* st_ap_buf                                                                                 */
/*  Return:         S2                     s2_t_result                                                                               */
/*===================================================================================================================================*/
static S2       s2_s_GmntrGlvlAveCal(const ST_GMNTR_INCDAT* st_ap_buf)
{
    U1                  u1_t_idx;
    U1                  u1_t_spsig_sts;
    U2                  u2_t_sp;
    S4                  s4_t_glval;
    S2                  s2_t_result;
    S4                  s4_t_work;

    s4_t_glval = (S4)0;

    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)GMNTR_GRVTY_AVENUM; u1_t_idx++){
        s4_t_glval = s4_t_glval + (S4)st_ap_buf[u1_t_idx].s2_glval;
    }

    s4_t_glval = s4_t_glval / (S4)GMNTR_GRVTY_AVENUM;
    if(s4_t_glval < (S4)0){
        s4_t_work = s4_t_glval * (S4)GMNTR_NUMINV;
    }
    else{
        s4_t_work = s4_t_glval;
    }
    u2_t_sp = (U2)0U;
    u1_t_spsig_sts = u1_g_VehspdKmphInst(&u2_t_sp, (U1)TRUE);
    if(u1_t_spsig_sts == (U1)VEHSPD_STSBIT_VALID){
        if(u2_t_sp <= (U2)GMNTR_SPSTOP){
            if(s4_t_work  <= (S4)GMNTR_GRVTY_THRESH){
                s4_t_glval = (S4)0;
            }
        }
    }
    else if(u1_t_spsig_sts == (U1)VEHSPD_STSBIT_UNKNOWN){
        if(s4_t_work  <= (S4)GMNTR_GRVTY_THRESH){
            s4_t_glval = (S4)0;
        }     
    }
    else{
        st_s_gmt_dispsts.u1_g_sts = (U1)GMNTR_G_VSBL_INIT_FAIL;
    }

    s2_t_result = (S2)s4_t_glval;

    return(s2_t_result);
}

/*===================================================================================================================================*/
/*  static U2       u2_s_GmntrGetComdat(U2 u2_a_ave, U2 u2_a_lsb, U2 u2_a_max)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_ave                                                                                                      */
/*                  U2 u2_a_lsb                                                                                                      */
/*                  U1 u2_a_max                                                                                                      */
/*  Return:         U2 u2_t_ret                                                                                                      */
/*===================================================================================================================================*/
static U2       u2_s_GmntrGetComdat(U2 u2_a_ave, U2 u2_a_lsb, U2 u2_a_max)
{
    U2  u2_t_ret;

    u2_t_ret = u2_a_ave / u2_a_lsb;
    if(u2_t_ret > (U2)u2_a_max){
        u2_t_ret = (U2)u2_a_max;
    }
    return(u2_t_ret);
}
/*===================================================================================================================================*/
/*  static U1       u1_s_GmntrPkhldJdg(U1 u1_a_pre_fb_gval, U1 u1_a_pre_lr_gval, U1 u1_a_latest_fb_gval, U1 u1_a_latest_lr_gval)      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_pre_fb_gval                                                                                              */
/*                  U1 u1_a_pre_lr_gval                                                                                              */
/*                  U1 u1_a_latest_fb_gval                                                                                           */
/*                  U1 u1_a_latest_lr_gval                                                                                           */
/*  Return:         U1 u1_t_pkhld_sts                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_GmntrPkhldJdg(U1 u1_a_pre_fb_gval, U1 u1_a_pre_lr_gval, U1 u1_a_latest_fb_gval, U1 u1_a_latest_lr_gval)
{
    U2    u2_t_pre_dst;
    U2    u2_t_dst;
    U1    u1_t_pkhld_cmpr;
    U1    u1_t_pkhld_sts;
    u2_t_pre_dst    = (U2)0U;
    u2_t_dst        = (U2)0U;
    u1_t_pkhld_cmpr = (U1)GMNTR_PKHLD_SAME;
    u1_t_pkhld_sts  = (U1)GMNTR_PKHLD_NON;
    u2_t_pre_dst = ((U2)u1_a_pre_fb_gval * (U2)u1_a_pre_fb_gval) + ((U2)u1_a_pre_lr_gval * (U2)u1_a_pre_lr_gval);
    u2_t_dst = ((U2)u1_a_latest_fb_gval * (U2)u1_a_latest_fb_gval) + ((U2)u1_a_latest_lr_gval * (U2)u1_a_latest_lr_gval);
    if(u2_t_pre_dst > u2_t_dst){
        u1_t_pkhld_cmpr = (U1)GMNTR_PKHLD_LARGE;
    }else if(u2_t_pre_dst == u2_t_dst){
        u1_t_pkhld_cmpr = (U1)GMNTR_PKHLD_SAME;
    }else{
        u1_t_pkhld_cmpr = (U1)GMNTR_PKHLD_SMALL;
    }
    if(
    ((u1_a_pre_fb_gval >= (U1)GMNTR_PKHLD_THRESH) || (u1_a_pre_lr_gval >= (U1)GMNTR_PKHLD_THRESH)) 
    && (u1_t_pkhld_cmpr == (U1)GMNTR_PKHLD_LARGE)
    && (u1_s_gmt_pkhld_pre_cmpr == (U1)GMNTR_PKHLD_SMALL)
    ){
        u1_t_pkhld_sts = (U1)GMNTR_PKHLD_ACT;
        if(u1_s_gmt_pkhld_cnt < (U1)GMNTR_PKHLD_TIM){
            u1_t_pkhld_sts = (U1)GMNTR_PKHLD_RTGR;
        }
        u1_s_gmt_pkhld_cnt = (U1)0U;
    }else if(u1_s_gmt_pkhld_cnt < (U1)GMNTR_PKHLD_TIM){
        u1_s_gmt_pkhld_cnt++;
        u1_t_pkhld_sts = (U1)GMNTR_PKHLD_ACT;
    }else{
        u1_s_gmt_pkhld_cnt = (U1)U1_MAX;
        u1_t_pkhld_sts = (U1)GMNTR_PKHLD_NON;
    }
    if(u1_t_pkhld_cmpr != (U1)GMNTR_PKHLD_SAME){
        u1_s_gmt_pkhld_pre_cmpr = u1_t_pkhld_cmpr;
    }
    return(u1_t_pkhld_sts);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrAngleUpdt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrAngleUpdt(void)
{

    U1                  u1_t_igon;
    U1                  u1_t_msgsts;
    U1                  u1_t_jdg;
    U1                  u1_t_sig;
    S2                  s2_t_ssa;
    S4                  s4_t_angl;
    ST_GMNTR_SIGN_U4DAT st_t_calrslt;
    U1                  u1_t_epssasup;    
    U4                  u4_t_work;

    u1_t_igon = u1_GMNTR_IG_ISON();
    if(u1_t_igon == (U1)TRUE){
        u1_t_sig = (U1)0U;
        s2_t_ssa  = (S2)0;
        u1_t_epssasup = u1_GMNTR_EPSSA_SUP();
        if(u1_t_epssasup != (U1)TRUE){
            u1_t_msgsts  = u1_GMNTR_RXMSG_STR1S01STS();
            vd_GMNTR_RXMSG_STS1(&u1_t_sig);
            vd_GMNTR_RXMSG_SSA(&s2_t_ssa);
        }
        else{
            u1_t_msgsts  = u1_GMNTR_RXMSG_EPS1S11STS();
            vd_GMNTR_RXMSG_EPSTS1(&u1_t_sig);
            vd_GMNTR_RXMSG_EPSSA(&s2_t_ssa);
        }
        u1_t_msgsts &= (U1)(GMNTR_COM_TIMEOUT | GMNTR_COM_NO_RX );

        if(u1_t_msgsts != (U1)0U){
            vd_s_GmntrClrAnglDat();
            st_s_comdat.u1_angldrc = (U1)GMNTR_ANGLDRC_FAIL;
            st_s_comdat.u1_anglval = (U1)GMNTR_ANGL_FAIL;
            st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_INIT_FAIL;
            u1_s_gmt_angl_fail_cnt = (U1)0U;
        }
        else{
            u1_t_jdg = u1_t_sig;

            if(u1_t_jdg == (U1)0U){
                s4_t_angl  = (S4)s2_t_ssa;
                s4_t_angl *= (S4)GMNTR_ANGL_LSB;

                st_s_gmt_angl.s4_ave = ((((S4)st_s_gmt_angl.s4_ave * (S4)GMNTR_ANGL_NUM_A) + (s4_t_angl * (S4)GMNTR_ANGL_NUM_B)) / (S4)GMNTR_ANGL_NUM_C);

                st_t_calrslt  = st_s_GmntrS4SizeChg(st_s_gmt_angl.s4_ave);

                if(st_t_calrslt.u4_val > (U4)GMNTR_ANGL_MAXVAL){
                    st_s_comdat.u1_anglval = (U1)GMNTR_ANGL_MAX;
                    st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_LIGHT;
                }
                else{
                    u4_t_work              = st_t_calrslt.u4_val * (U4)GMNTR_ANGL_MAX;
                    u4_t_work              = u4_t_work + ((U4)GMNTR_RNDOFSET * ((U4)GMNTR_ANGL_MAXVAL / (U4)GMNTR_ANGL_COEFF));
                    st_s_comdat.u1_anglval = (U1)(u4_t_work / (U4)GMNTR_ANGL_MAXVAL);
                    st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_VALID;
                }
                if(st_t_calrslt.u1_signinf == (U1)GMNTR_PLUS){
                    st_s_comdat.u1_angldrc = (U1)GMNTR_LEFT;
                }
                else{
                    st_s_comdat.u1_angldrc = (U1)GMNTR_RGHT;
                }
                u1_s_gmt_angl_fail_cnt = (U1)0U;
            }
            else{
                if(u1_s_gmt_angl_fail_cnt >= (U1)GMNTR_ANGL_FAILTIM){
                    vd_s_GmntrClrAnglDat();
                    st_s_comdat.u1_angldrc = (U1)GMNTR_ANGLDRC_FAIL;
                    st_s_comdat.u1_anglval = (U1)GMNTR_ANGL_FAIL;
                    st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_INIT_FAIL;
                }
                u1_s_gmt_angl_fail_cnt = ((u1_s_gmt_angl_fail_cnt < (U1)U1_MAX) ? (u1_s_gmt_angl_fail_cnt + (U1)1U) : (U1)U1_MAX);
            }
        }
    }
    else{
        vd_s_GmntrClrAnglDat();
        st_s_comdat.u1_angldrc = (U1)GMNTR_ANGLDRC_FAIL;
        st_s_comdat.u1_anglval = (U1)GMNTR_ANGL_FAIL;
        st_s_gmt_dispsts.u1_angl_sts = (U1)GMNTR_ANGL_VSBL_INIT_FAIL;
        u1_s_gmt_angl_fail_cnt = (U1)0U;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrBrkprssUpdt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrBrkprssUpdt(void)
{
    U1              u1_t_igon;
    U2              u2_t_sigfail;
    U2              u2_t_fbkdr_ax;
    U4              u4_t_brk;

    u1_t_igon = u1_GMNTR_IG_ISON();
    if(u1_t_igon == (U1)TRUE){
        if(u1_s_gmt_brk_updt_cnt < (U1)U1_MAX){
            u1_s_gmt_brk_updt_cnt = u1_s_gmt_brk_updt_cnt + (U1)1U;
        }
        else{
            u1_s_gmt_brk_updt_cnt = (U1)U1_MAX;
        }

        if(u1_s_gmt_brk_updt_cnt >= (U1)GMNTR_UPDTTIM){
            u2_t_sigfail = u2_GMNTR_GET_SIGSTS();
            if((u2_t_sigfail & (U2)GMNTR_OILPRSS_FAILCHK ) == (U2)GMNTR_OILPRSS_FAILCHK){
                st_s_comdat.u1_brkprss = (U1)GMNTR_BRKPRS_FAIL;
                vd_s_GmntrClrBrkDat();
                st_s_gmt_dispsts.u1_brkprss_sts = (U1)GMNTR_BRKPRS_VSBL_INIT_FAIL;
            }
            else{
                if(st_s_gmt_brk.u2_failcnt <= (U2)GMNTR_BRKPRS_FAILTIM){
                    if(st_s_gmt_brk.u2_failcnt == (U2)0U){
                        if(st_s_gmt_brk.s2_vlddat > (S2)GMNTR_BRKPRS_BRK_ACCL_LOW_LMT){
                            u2_t_fbkdr_ax = (U2)0U;
                        }
                        else{
                            u2_t_fbkdr_ax = (U2)(st_s_gmt_brk.s2_vlddat * (S2)(-1));
                        }
                        u4_t_brk = (((U4)u2_t_fbkdr_ax * (U4)GMNTR_BRKPRS_MAX) + (U4)GMNTR_BRKPRS_ROUND_VAL)
                                    / (U4)GMNTR_BRKPRS_BRK_ACCL_MAX;
                    }
                    else{
                        u4_t_brk = (U4)st_s_comdat.u1_brkprss;
                    }

                    if(u4_t_brk > (U4)GMNTR_BRKPRS_MAX){
                        st_s_comdat.u1_brkprss = (U1)GMNTR_BRKPRS_MAX;
                    }
                    else{
                        st_s_comdat.u1_brkprss = (U1)u4_t_brk;
                    }
                    st_s_gmt_dispsts.u1_brkprss_sts = (U1)GMNTR_BRKPRS_VSBL_VALID;
                }
                else{
                    st_s_comdat.u1_brkprss = (U1)GMNTR_BRKPRS_FAIL;
                    vd_s_GmntrClrBrkDat();
                    st_s_gmt_dispsts.u1_brkprss_sts = (U1)GMNTR_BRKPRS_VSBL_INIT_FAIL;
                }
            }
            u1_s_gmt_brk_updt_cnt = (U1)0U;
        }

    }
    else{
        st_s_comdat.u1_brkprss  = (U1)GMNTR_BRKPRS_FAIL;
        vd_s_GmntrClrBrkDat();
        st_s_gmt_brk.u2_failcnt = (U2)0U;
        st_s_gmt_dispsts.u1_brkprss_sts = (U1)GMNTR_BRKPRS_VSBL_INIT_FAIL;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_GmntrAccelUpdt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GmntrAccelUpdt(void)
{
    U1  u1_t_igon;
    U1  u1_t_msgsts;
    U2  u2_t_sig;
    U4  u4_t_work;

    u1_t_igon = u1_GMNTR_IG_ISON();
    if(u1_t_igon == (U1)TRUE){
        if(u1_s_gmt_accel_updt_cnt < (U1)U1_MAX){
            u1_s_gmt_accel_updt_cnt = u1_s_gmt_accel_updt_cnt + (U1)1U;
        }
        else{
            u1_s_gmt_accel_updt_cnt = (U1)U1_MAX;
        }

        if(u1_s_gmt_accel_updt_cnt >= (U1)GMNTR_UPDTTIM){
            u1_t_msgsts  = u1_GMNTR_RXMSG_ENG1G03STS();
            u1_t_msgsts &= (U1)(GMNTR_COM_TIMEOUT | GMNTR_COM_NO_RX);

            if(u1_t_msgsts != (U1)0U){
                st_s_comdat.u1_accel = (U1)GMNTR_ACCEL_FAIL;
                vd_s_GmntrClrAccelDat();
                st_s_gmt_dispsts.u1_accel_sts = (U1)GMNTR_ACCEL_VSBL_INIT_FAIL;
            }
            else{
                u2_t_sig  = (U2)0U;
                vd_GMNTR_RXMSG_EACCP_D(&u2_t_sig);
                u2_t_sig *= (U2)GMNTR_ACCEL_LSB;

                st_s_gmt_accel.u2_ave = u2_t_sig;

                if(st_s_gmt_accel.u2_ave > (U2)GMNTR_ACCEL_MAXVAL){
                    st_s_comdat.u1_accel = (U1)GMNTR_ACCEL_MAX;
                }
                else{
                    u4_t_work              = (U4)st_s_gmt_accel.u2_ave * (U4)GMNTR_ACCEL_MAX;
                    u4_t_work              = u4_t_work + ((U4)GMNTR_RNDOFSET * (U4)GMNTR_ACCEL_COEFF);
                    st_s_comdat.u1_accel   = (U1)(u4_t_work / (U4)GMNTR_ACCEL_MAXVAL);
                }
                st_s_gmt_dispsts.u1_accel_sts = (U1)GMNTR_ACCEL_VSBL_VALID;
            }
            u1_s_gmt_accel_updt_cnt = (U1)0U;
        }
    }
    else{
        st_s_comdat.u1_accel = (U1)GMNTR_ACCEL_FAIL;
        vd_s_GmntrClrAccelDat();
        st_s_gmt_dispsts.u1_accel_sts = (U1)GMNTR_ACCEL_VSBL_INIT_FAIL;
    }
}

/*===================================================================================================================================*/
/*  static ST_GMNTR_SIGN_U2DAT      st_s_GmntrS2SizeChg(S2 s2_a_orgval)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2                  s2_a_orgval                                                                                  */
/*  Return:         ST_GMNTR_SIGN_U2DAT st_t_result                                                                                  */
/*===================================================================================================================================*/
static ST_GMNTR_SIGN_U2DAT      st_s_GmntrS2SizeChg(S2 s2_a_orgval)
{
    ST_GMNTR_SIGN_U2DAT     st_t_result;
    S2  s2_t_calcbuf;

    if(s2_a_orgval < (S2)0){
        s2_t_calcbuf = s2_a_orgval * (S2)GMNTR_NUMINV;
        st_t_result.u2_val     = (U2)s2_t_calcbuf;
        st_t_result.u1_signinf = (U1)GMNTR_MINUS;
    }
    else{
        st_t_result.u2_val     = (U2)s2_a_orgval;
        st_t_result.u1_signinf = (U1)GMNTR_PLUS;
    }

    return(st_t_result);
}

/*===================================================================================================================================*/
/*  static ST_GMNTR_SIGN_U4DAT      st_s_GmntrS4SizeChg(S4 s4_a_orgval)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S4                  s4_a_orgval                                                                                  */
/*  Return:         ST_GMNTR_SIGN_U4DAT st_t_result                                                                                  */
/*===================================================================================================================================*/
static ST_GMNTR_SIGN_U4DAT      st_s_GmntrS4SizeChg(S4 s4_a_orgval)
{
    ST_GMNTR_SIGN_U4DAT st_t_result;
    S4  s4_t_calcbuf;

    if(s4_a_orgval < (S4)0){
        s4_t_calcbuf = s4_a_orgval * (S4)GMNTR_NUMINV;
        st_t_result.u4_val     = (U4)s4_t_calcbuf;
        st_t_result.u1_signinf = (U1)GMNTR_MINUS;
    }
    else{
        st_t_result.u4_val     = (U4)s4_a_orgval;
        st_t_result.u1_signinf = (U1)GMNTR_PLUS;
    }

    return(st_t_result);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetdrc(U1 u1_a_drc)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_drc                                                                                                      */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetdrc(U1 u1_a_drc)
{
    U1 u1_t_ret;

    if(u1_a_drc == (U1)GMNTR_FB_INF){
        u1_t_ret = st_s_comdat.u1_fb_gdrc;
    }
    else{
        u1_t_ret = st_s_comdat.u1_lr_gdrc;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetvaldrc(U1 u1_a_drc)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_drc                                                                                                      */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetvaldrc(U1 u1_a_drc)
{
    U1 u1_t_ret;
    if(u1_a_drc == (U1)GMNTR_FB_INF){
        u1_t_ret = st_s_comdat.u1_fb_gvaldrc;
    }
    else{
        u1_t_ret = st_s_comdat.u1_lr_gvaldrc;
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GmntrGetPos(U1 u1_a_drc)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_drc                                                                                                      */
/*  Return:         U2 u2_t_ret                                                                                                      */
/*===================================================================================================================================*/
U2      u2_g_GmntrGetPos(U1 u1_a_drc)
{
    U2 u2_t_ret;

    if(u1_a_drc == (U1)GMNTR_FB_INF){
        u2_t_ret = st_s_comdat.u2_fb_gpos;
    }
    else{
        u2_t_ret = st_s_comdat.u2_lr_gpos;
    }

    return(u2_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetVal(U1 u1_a_drc)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 u1_a_drc                                                                                                      */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetVal(U1 u1_a_drc)
{
    U1 u1_t_ret;

    if(u1_a_drc == (U1)GMNTR_FB_INF){
        u1_t_ret = st_s_comdat.u1_fb_gval;
    }
    else{
        u1_t_ret = st_s_comdat.u1_lr_gval;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetGSts(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 st_s_gmt_dispsts.u1_g_sts                                                                                     */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetGSts(void)
{
    return(st_s_gmt_dispsts.u1_g_sts);
}
/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetAngldrc(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 st_s_comdat.u1_angldrc                                                                                        */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetAngldrc(void)
{
    return(st_s_comdat.u1_angldrc);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetAnglval(U1 *u1p_a_angl)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 *u1p_a_angl                                                                                                   */
/*  Return:         U1 st_s_gmt_dispsts.u1_angl_sts                                                                                  */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetAnglval(U1 *u1p_a_angl)
{
    if (u1p_a_angl != vdp_PTR_NA) {
        (*u1p_a_angl) = st_s_comdat.u1_anglval;
    }
    return(st_s_gmt_dispsts.u1_angl_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetBrkPrss(U1 *u1p_a_brk)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 *u1p_a_brk                                                                                                    */
/*  Return:         U1 st_s_gmt_dispsts.u1_brkprss_sts                                                                               */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetBrkPrss(U1 *u1p_a_brk)
{
    if (u1p_a_brk != vdp_PTR_NA) {
        (*u1p_a_brk) = st_s_comdat.u1_brkprss;
    }
    return(st_s_gmt_dispsts.u1_brkprss_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_GmntrGetAccel(U1 *u1p_a_accel)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 *u1p_a_accel                                                                                                  */
/*  Return:         U1 st_s_gmt_dispsts.u1_accel_sts                                                                                 */
/*===================================================================================================================================*/
U1      u1_g_GmntrGetAccel(U1 *u1p_a_accel)
{
    if (u1p_a_accel != vdp_PTR_NA) {
        (*u1p_a_accel) = st_s_comdat.u1_accel;
    }
    return(st_s_gmt_dispsts.u1_accel_sts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  0.0.1           06/20/2013  TS      New.                                                                                         */
/*  1.0.0           10/01/2013  TS      600A 1A Supported                                                                            */
/*  2.0.0           02/13/2015  TO      945A 1A Supported                                                                            */
/*                                       -frame, signal change : VSC1F06->VSC1S06, PMCF->PBRKF, PMCS->PBRKS,  PMC->PBRK              */
/*                                       -Abnormal state of gravity acceleration :                                                   */
/*                                              The judgment time(GMNTR_FAILTIM_MS) was changed to 3.6s.                             */
/*                                       -The G-Ball/brake hydraulic operation error signal reception counter was changed            */
/*                                              from U1 type to U2 type in order to avoid overflow due to the change.                */
/*  2.1.0           04/15/2015  TO      Effective maximum/minimum values and vehicle type information                                */
/*                                      at HV and CONV were added in accordance with the support of brake hydraulic pressure for HV. */
/*  2.2.0           07/16/2015  MY      945A MPT Supported (Calculation formula changed due to change of G sensor identification)    */
/*  2.2.1           06/07/2017  SM      Delete:#pragma segment                                                                       */
/*  2.2.2           10/03/2017  SM      pixel Range 20step -> 80step                                                                 */
/*  2.3.0           10/22/2018  HT      Update : Variable Sensor Angle/Direction.                                                    */
/*                                      Deal with QAC wrn : Delete unnecessary casts.                                                */
/*  2.3.1           01/09/2019  HN      Deal with QAC wrn : Delete unnecessary casts.                                                */
/*  2.3.2           01/11/2019  HN      BugFix : Data OverFlow when G-Ball coordinates calculate.                                    */
/*  2.4.0           03/19/2019  HN      Update : Change GL-Sensor & GL-ZeroPoint calcuration by Sensor Direction.                    */
/*  2.5.0           06/05/2021  SK      BugFix : Add peakhold disp function                                                          */
/*  2.6.0           04/22/2022  HA      BugFix : peakhold judged by disp prm to num prm                                              */
/*  2.7.0           11/14/2022  HI      850B 1A Supported                                                                            */
/*  3.0.0           01/10/2024  TK      19PFv3 Standard Spec Support (C_GMN-CSTD)                                                    */
/*  3.0.1           07/08/2024  SM(DT)  Bug Fix: G-Monitor Max history info is not hidden when abnormality occurs                    */
/*  3.0.2           07/11/2024  SM(DT)  Update : Brake hydraulic pressure calculation                                                */
/*                                                                                                                                   */
/*  * TS = Takuya Shigemori, NCOS                                                                                                    */
/*  * TO = Takeshi Otoi                                                                                                              */
/*  * MY = Manabu Yamada                                                                                                             */
/*  * SM = Shouhei Matsumoto                                                                                                         */
/*  * HT = Hirotaka Takekoshi, Denso Techno                                                                                          */
/*  * HN = Hiroyuki Noguchi, Denso Techno                                                                                            */
/*  * SK = Shintaro Kanou, Denso Techno                                                                                              */
/*  * HA = Hiroki Asano, PRD                                                                                                         */
/*  * HI = Hidekazu Imai, PRD                                                                                                        */
/*  * TK = Toru Kamishina, Denso Techno                                                                                              */
/*  * SM(DT) = Shota Maegawa, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
