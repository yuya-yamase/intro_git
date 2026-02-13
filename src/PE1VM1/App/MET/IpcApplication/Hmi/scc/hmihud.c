/* 1.2.0 */
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
#define HMIHUD_C_MINOR                         (2)
#define HMIHUD_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmihud.h"

#include "mcst.h"
#include "vardef.h"
#include "veh_opemd.h"
#include "himgadj.h"
#include "hdimmgr_if.h"
#include "calibration.h"

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

#define HMIHUD_DTA_NUM                         (5U)
#define HMIHUD_SOC_DTA_NUM                     (1U)
#define HMIHUD_GVIF_DTA_NUM                    (4U)

#define HMIHUD_GVIF_DTA_OFFSET                 (HMIHUD_SOC_DTA_NUM)

#define HMIHUD_SIG_NUM                         (7U)
#define HMIHUD_SIG_HUD_ILL_STEP_IND            (0U)
#define HMIHUD_SIG_CSTM_HUD_ONOFF_ACT          (1U)
#define HMIHUD_SIG_HUD_ROT_SW                  (2U)
#define HMIHUD_SIG_MOVPOS                      (3U)
#define HMIHUD_SIG_ADJMINPOS                   (4U)
#define HMIHUD_SIG_ADJTEPPOS                   (5U)
#define HMIHUD_SIG_ADJMAXPOS                   (6U)

#define HMIHUD_VAL_HUD_ONOFF_ACT_NON           (0U)
#define HMIHUD_VAL_HUD_ONOFF_ACT_ON            (1U)
#define HMIHUD_VAL_HUD_ONOFF_ACT_OFF           (2U)
#define HMIHUD_VAL_HUD_ONOFF_ACT_UNDEF         (3U)

#define HMIHUD_VAL_ROT_SW_NON                  (0U)
#define HMIHUD_VAL_ROT_SW_CW                   (1U)
#define HMIHUD_VAL_ROT_SW_CCW                  (2U)
#define HMIHUD_VAL_ROT_SW_UNDEF                (3U)

#define HMIHUD_VAL_ROT_STEP_UP                 (0U)
#define HMIHUD_VAL_ROT_STEP_DOWN               (1U)

#define HMIHUD_VAL_ROT_STEP_ONE                (1U)

#define HMIHUD_VAL_ROT_STS_ENABLE              (0U)
#define HMIHUD_VAL_ROT_STS_CW_DISABLE          (1U)
#define HMIHUD_VAL_ROT_STS_CCW_DISABLE         (2U)
#define HMIHUD_VAL_ROT_STS_UNDEF               (3U)

#define HMIHUD_VAL_POS_STS_ENABLE              (0U)
#define HMIHUD_VAL_POS_STS_UP_DISABLE          (1U)
#define HMIHUD_VAL_POS_STS_DW_DISABLE          (2U)
#define HMIHUD_VAL_POS_STS_UNDEF               (3U)

#define HMIHUD_STS_POS_MOVPOS_UNK              (0xFFFFU)
#define HMIHUD_STS_POS_ADJMINPOS_UNK           (0xFFFFU)
#define HMIHUD_STS_POS_ADJMAXPOS_UNK           (0xFFFFU)

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
static U1   u1_s_hmihud_hud_onoff_act_pre;
static U1   u1_s_hmihud_hud_rot_sw_pre;
static S1   s1_s_hmihud_hud_rot;
static S1   s1_s_hmihud_hud_rot_pre;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_s_HmiHudReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ);

static void vd_s_HmiHudSetIllStep(void);
static void vd_s_HmiHudSetHudOnOffAct(void);
static void vd_s_HmiHudSetHudRot(void);
static void vd_s_HmiHudCalcHudRot(const U1 u1_a_DIRECTION);
static void vd_s_HmiHudChkHudRotLimit(S1 * s1_ap_lmt_ccw, S1 * s1_ap_lmt_cw);
static inline U1 u1_s_HmihudCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF);
static void vd_s_HmiHudSetMovpos(void);
static void vd_s_HmiHudSetAdjminpos(void);
static void vd_s_HmiHudSetAdjteppos(void);
static void vd_s_HmiHudSetAdjmaxpos(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_HMIHUD_SIGCONVERT st_sp_HMIHUD_SIGCONVERT[HMIHUD_SIG_NUM] = {
/*  u4_buf      u1_bitpos    u4_bitmask                              */
    {(U4)0U,    (U1)0U,      (U4)0xFFU  },    /* HUD_ILL_STEP_IND    */
    {(U4)0U,    (U1)13U,     (U4)0x03U  },    /* CSTM_HUD_ONOFF_ACT  */
    {(U4)0U,    (U1)8U,      (U4)0x03U  },    /* HUD_ROT_SW          */
    {(U4)3U,    (U1)0U,      (U4)0xFFFFU},    /* HUD_VIPOS_MOVPOS    */
    {(U4)3U,    (U1)16U,     (U4)0xFFFFU},    /* HUD_VIPOS_ADJMINPOS */
    {(U4)4U,    (U1)0U,      (U4)0xFFFFU},    /* HUD_VIPOS_ADJTEPPOS */
    {(U4)4U,    (U1)16U,     (U4)0xFFFFU}     /* HUD_VIPOS_ADJMAXPOS */
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
    U1  u1_t_hud_rot;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIHUD_DTA_NUM ; u4_t_loop++){
        u4_sp_hmihud_dtabuf[u4_t_loop] = (U4)0xFFFFFFFFU;
    }
    u1_s_hmihud_hud_onoff_act_pre = (U1)HMIHUD_VAL_HUD_ONOFF_ACT_UNDEF;
    u1_s_hmihud_hud_rot_sw_pre    = (U1)HMIHUD_VAL_ROT_SW_UNDEF;
    u1_t_hud_rot                  = (U1)u4_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_s_hmihud_hud_rot           = (S1)u1_t_hud_rot;
    s1_s_hmihud_hud_rot_pre       = s1_s_hmihud_hud_rot;
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiHudMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudMainTask(void)
{
    vd_s_HmiHudSetIllStep();
    vd_s_HmiHudSetHudOnOffAct();
    vd_s_HmiHudSetHudRot();
    vd_s_HmiHudSetMovpos();
    vd_s_HmiHudSetAdjminpos();
    vd_s_HmiHudSetAdjteppos();
    vd_s_HmiHudSetAdjmaxpos();
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiHudSocDataPut(const U4 * u4_ap_REQ)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : soc first address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudSocDataPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIHUD_SOC_DTA_NUM ; u4_t_loop++){
            u4_sp_hmihud_dtabuf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiHudGvifDataPut(const U4 * u4_ap_REQ)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : gvif first address                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudGvifDataPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIHUD_GVIF_DTA_NUM ; u4_t_loop++){
            u4_sp_hmihud_dtabuf[u4_t_loop + (U4)HMIHUD_GVIF_DTA_OFFSET] = u4_ap_REQ[u4_t_loop];
        }
    }
}
/*===================================================================================================================================*/
/* void    vd_g_HmiHudMcstHook(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiHudMcstHook(void)
{
    U1  u1_t_hud_rot;

    u1_t_hud_rot            = (U1)u4_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_s_hmihud_hud_rot     = (S1)u1_t_hud_rot;
    s1_s_hmihud_hud_rot_pre = s1_s_hmihud_hud_rot;
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
/*  static void    vd_s_HmiHudSetIllStep(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetIllStep(void)
{
    U1 u1_t_step;

    u1_t_step = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_HUD_ILL_STEP_IND, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    vd_g_HdimmgrIfSetIllStepVal(u1_t_step);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetHudOnOffAct(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetHudOnOffAct(void)
{
    U1 u1_t_gvif;
    U1 u1_t_igon;
    U1 u1_t_act;

    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    u1_t_igon = u1_g_VehopemdIgnOn();
    u1_t_act = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_CSTM_HUD_ONOFF_ACT, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    if((u1_t_gvif == (U1)TRUE) &&
       (u1_t_igon == (U1)TRUE)) {
        if(u1_t_act != u1_s_hmihud_hud_onoff_act_pre) {
            if(u1_t_act == (U1)HMIHUD_VAL_HUD_ONOFF_ACT_ON) {
                vd_g_McstBfPut((U1)MCST_BFI_HUD, (U4)MCST_HUD_ON);
            }
            else if(u1_t_act == (U1)HMIHUD_VAL_HUD_ONOFF_ACT_OFF) {
                vd_g_McstBfPut((U1)MCST_BFI_HUD, (U4)MCST_HUD_OFF);
            }
            else{
                /* Do Nothing */
            }
        }
    }

    u1_s_hmihud_hud_onoff_act_pre = u1_t_act;
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetHudRot(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetHudRot(void)
{
    U1 u1_t_gvif;
    U1 u1_t_sw;

    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    u1_t_sw   = (U1)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_HUD_ROT_SW, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    if(u1_t_gvif == (U1)TRUE) {
        if(u1_t_sw != u1_s_hmihud_hud_rot_sw_pre) {
            if(u1_t_sw == (U1)HMIHUD_VAL_ROT_SW_CW) {
                vd_s_HmiHudCalcHudRot((U1)HMIHUD_VAL_ROT_STEP_UP);
            }
            else if(u1_t_sw == (U1)HMIHUD_VAL_ROT_SW_CCW) {
                vd_s_HmiHudCalcHudRot((U1)HMIHUD_VAL_ROT_STEP_DOWN);
            }
            else{
                /* Do Nothing */
            }
        }
    }

    if(s1_s_hmihud_hud_rot != s1_s_hmihud_hud_rot_pre){
        vd_g_McstBfPut((U1)MCST_BFI_HUD_ROT, (U4)((U1)s1_s_hmihud_hud_rot));
    }

    u1_s_hmihud_hud_rot_sw_pre = u1_t_sw;
    s1_s_hmihud_hud_rot_pre    = s1_s_hmihud_hud_rot;
}
/*===================================================================================================================================*/
/* static  void    vd_s_HmiHudCalcHudRot                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_DIRECTION : step up/down                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiHudCalcHudRot(const U1 u1_a_DIRECTION)
{
    S1  s1_t_lmt_ccw;
    S1  s1_t_lmt_cw;
    U1  u1_t_now;
    S1  s1_t_now;

    vd_s_HmiHudChkHudRotLimit(&s1_t_lmt_ccw, &s1_t_lmt_cw);

    u1_t_now = (U1)u4_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_t_now = (S1)u1_t_now;

    if (u1_a_DIRECTION == (U1)HMIHUD_VAL_ROT_STEP_DOWN){
        if (s1_t_now > s1_t_lmt_ccw){
            s1_s_hmihud_hud_rot = s1_t_now - (S1)HMIHUD_VAL_ROT_STEP_ONE;
        }
    } else {
        if (s1_t_now < s1_t_lmt_cw){
            s1_s_hmihud_hud_rot = s1_t_now + (S1)HMIHUD_VAL_ROT_STEP_ONE;
        }
    }
}
/*===================================================================================================================================*/
/* static  void    vd_s_HmiHudChkHudRotLimit                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      s1_ap_lmt_ccw : ccw limit                                                                                        */
/*                  s1_ap_lmt_cw : cw limit                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiHudChkHudRotLimit(S1 * s1_ap_lmt_ccw, S1 * s1_ap_lmt_cw)
{
    static const S2 s2_s_HMIHUD_HUDDEGSTEPLSB = (S2)10;

    U1  u1_t_lsb;
    S2  s2_t_lmt_tmp;

    u1_t_lsb = u1_s_HmihudCalibU1MinChk(u1_CALIB_MCUID0578_DEG_RTSTEP, (U1)CALIB_MCUID0578_MIN, (U1)CALIB_MCUID0578_DEF);

    if(s1_ap_lmt_ccw != vdp_PTR_NA) {
        s2_t_lmt_tmp = (((S2)((U2)u1_CALIB_MCUID0577_DEGCCW) - (S2)((U2)U1_MAX)) * s2_s_HMIHUD_HUDDEGSTEPLSB) / (S2)((U2)u1_t_lsb);
        /* ((Min:0 Max:255) - 255) * 10 / (Min:1 Max:255) */
        if(s2_t_lmt_tmp < (S2)((S1)MCST_HUDROT_CCW_LMT)){
            (*s1_ap_lmt_ccw) = (S1)MCST_HUDROT_CCW_LMT;
        }
        else{
            (*s1_ap_lmt_ccw) = (S1)s2_t_lmt_tmp;
        }
    }

    if(s1_ap_lmt_cw != vdp_PTR_NA) {
        s2_t_lmt_tmp = ((S2)((U2)u1_CALIB_MCUID0576_DEGCW) * s2_s_HMIHUD_HUDDEGSTEPLSB) / (S2)((U2)u1_t_lsb);
        /* (Min:0 Max:255)         * 10 / (Min:1 Max:255) */
        if(s2_t_lmt_tmp > (S2)MCST_HUDROT_CW_LMT){
            (*s1_ap_lmt_cw)  = (S1)MCST_HUDROT_CW_LMT;
        }
        else{
            (*s1_ap_lmt_cw)  = (S1)s2_t_lmt_tmp;
        }
    }
}
/*===================================================================================================================================*/
/*  static inline U1    u1_s_HmihudCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MIN                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1    u1_s_HmihudCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret < u1_a_MIN){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetMovpos(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetMovpos(void){
    U2 u2_t_movpos;

    u2_t_movpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_MOVPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    vd_g_HudImgAdjSet_GV_VIPOS_MOVPOS(u2_t_movpos);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjminpos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjminpos(void){
    U2 u2_t_adjminpos;

    u2_t_adjminpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMINPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    vd_g_HudImgAdjSet_GV_VIPOS_ADJMINPOS(u2_t_adjminpos);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjteppos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjteppos(void){
    U2 u2_t_adjteppos;

    u2_t_adjteppos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJTEPPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    vd_g_HudImgAdjSet_GV_VIPOS_ADJTEPPOS(u2_t_adjteppos);
}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiHudSetAdjmaxpos(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiHudSetAdjmaxpos(void){
    U2 u2_t_adjmaxpos;

    u2_t_adjmaxpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMAXPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    vd_g_HudImgAdjSet_GV_VIPOS_ADJMAXPOS(u2_t_adjmaxpos);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HmiHudGetHudOnoff(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_onoff    :  hud on/off                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_HmiHudGetHudOnoff(void)
{
    U1 u1_t_onoff;

    u1_t_onoff = (U1)(u4_g_McstBf((U1)MCST_BFI_HUD));

    return(u1_t_onoff);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HmiHudGetHudRot                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_hud_rot : hud rot                                                                                           */
/*===================================================================================================================================*/
U1      u1_g_HmiHudGetHudRot(void)
{
    U1 u1_t_hud_rot;

    u1_t_hud_rot = (U1)u4_g_McstBf((U1)MCST_BFI_HUD_ROT);

    return(u1_t_hud_rot);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HmiHudGetHudRotSwSts                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sw_sts : sw sts                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_HmiHudGetHudRotSwSts(void)
{
    U1 u1_t_sw_sts;
    S1 s1_t_lmt_ccw;
    S1 s1_t_lmt_cw;
    U1 u1_t_now;
    S1 s1_t_now;

    vd_s_HmiHudChkHudRotLimit(&s1_t_lmt_ccw, &s1_t_lmt_cw);

    u1_t_now = (U1)u4_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_t_now = (S1)u1_t_now;

    if(s1_t_now <= s1_t_lmt_ccw){
        u1_t_sw_sts = (U1)HMIHUD_VAL_ROT_STS_CCW_DISABLE;
    }
    else if(s1_t_now >= s1_t_lmt_cw){
        u1_t_sw_sts = (U1)HMIHUD_VAL_ROT_STS_CW_DISABLE;
    }
    else{
        u1_t_sw_sts = (U1)HMIHUD_VAL_ROT_STS_ENABLE;
    }

    return(u1_t_sw_sts);
}
/*===================================================================================================================================*/
/*  U1      u1_g_HmiHudGetHudViposSwSts                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sw_sts : sw sts                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_HmiHudGetHudViposSwSts(void)
{
    U1 u1_t_sw_sts;
    U2 u2_t_movpos;
    U2 u2_t_adjminpos;
    U2 u2_t_adjmaxpos;

    u1_t_sw_sts    = (U1)HMIHUD_VAL_POS_STS_ENABLE;
    u2_t_movpos    = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_MOVPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u2_t_adjminpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMINPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);
    u2_t_adjmaxpos = (U2)u4_s_HmiHudReadSig((U1)HMIHUD_SIG_ADJMAXPOS, &u4_sp_hmihud_dtabuf[HMIHUD_FIRST_DTA]);

    if((u2_t_movpos    != (U2)HMIHUD_STS_POS_MOVPOS_UNK)    &&
       (u2_t_adjminpos != (U2)HMIHUD_STS_POS_ADJMINPOS_UNK) &&
       (u2_t_adjmaxpos != (U2)HMIHUD_STS_POS_ADJMAXPOS_UNK)){
        if(u2_t_movpos >= u2_t_adjmaxpos){
            u1_t_sw_sts = (U1)HMIHUD_VAL_POS_STS_UP_DISABLE;
        }
        else if(u2_t_movpos <= u2_t_adjminpos){
            u1_t_sw_sts = (U1)HMIHUD_VAL_POS_STS_DW_DISABLE;
        }
        else{
            u1_t_sw_sts = (U1)HMIHUD_VAL_POS_STS_ENABLE;
        }
    }

    return(u1_t_sw_sts);
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
/*  1.2.0    02/02/2026  TS       Change for BEV FF2.(MET-M_HUDILL-CSTD-1)                                                           */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    02/03/2026  TS       Change for BEV FF2.(MET-M_HUDONOFF-CSTD-1)                                                         */
/*  BEV-2    02/12/2026  KN       Add function for HUD rotation.                                                                     */
/*  BEV-3    02/13/2026  HH       Add function for HUD position.                                                                     */
/*                                                                                                                                   */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * TS   = Takuo Suganuma,  Denso Techno                                                                                           */
/*  * KN   = Kazuo Nishigaki, Denso Techno                                                                                           */
/*  * HH   = Hiroki Hara,     Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
