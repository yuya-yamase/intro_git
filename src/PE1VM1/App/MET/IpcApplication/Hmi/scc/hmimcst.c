/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Hmiodo                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMCST_C_MAJOR                         (2)
#define HMIMCST_C_MINOR                         (4)
#define HMIMCST_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmimcst.h"

#include "mcst.h"
#include "vardef.h"
#include "oxcan.h"
#include "calibration.h"
#include "hdimmgr.h"
#include "veh_opemd.h"
#include "rim_ctl.h"
#include "iohw_diflt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIMCST_C_MAJOR != HMIMCST_H_MAJOR) || \
     (HMIMCST_C_MINOR != HMIMCST_H_MINOR) || \
     (HMIMCST_C_PATCH != HMIMCST_H_PATCH))
#error "hmimcst.c and hmimcst.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    HMIMCST_MAIN_TICK                    (20U)        /* 20 milliseconds */

#define    HMIMCST_ON_EDG_NUM                   (6U)
#define    HMIMCST_NO_OPE_NUM                   (3U)

#define    HMIMCST_SW_NO_OPE                    (0U)
#define    HMIMCST_SW_OPE                       (1U)

#define    HMIMCST_VAL_ON                       (1U)
#define    HMIMCST_VAL_OFF                      (0U)

#define    HMIMCST_CMND_NON                     (0U)
#define    HMIMCST_CMND_SWITCH                  (1U)

#define    HMIMCST_DRVMODE_ARRYPOS              (1U)
#define    HMIMCST_DRVMODE_BITPOS               (18U)
#define    HMIMCST_DRVMODE_SIG_MASK             (0x01FC0000U)
#define    HMIMCST_DRVMODE_JDG_MASK             (0x1FU)
#define    HMIMCST_DRVMODE3                     (0x13U)
#define    HMIMCST_DRVMODE4                     (0x1DU)

#define    HMIMCST_HUDROT_NO_OPE                (0U)
#define    HMIMCST_HUDROT_CW                    (1U)
#define    HMIMCST_HUDROT_CW_HLD                (2U)
#define    HMIMCST_HUDROT_CCW                   (3U)
#define    HMIMCST_HUDROT_CCW_HLD               (4U)

#define    HMIMCST_HUDROT_STEP_UP               (0U)
#define    HMIMCST_HUDROT_STEP_DOWN             (1U)

#define    HMIMCST_HUDROT_STEP_ONE              (1U)

#define    HMIMCST_USERBUF_FSTDAT               (0U)
#define    HMIMCST_USERBUF_TXTDAT               (1U)

#define    HMIMCST_USERBUF_INIVAL               (0U)

#define    HMIMCST_UPDATENUM_MIN                (0x01U)
#define    HMIMCST_UPDATENUM_MAX                (0x0EU)
#define    HMIMCST_UPDATENUM_INIVAL             (0x0FU)

#define    HMIMCST_L_STSW_UD_VALID_VAL          ( 9U)
#define    HMIMCST_L_STSW_LR_VALID_VAL          (10U)
#define    HMIMCST_R_STSW_UD_VALID_VAL          ( 8U)
#define    HMIMCST_R_STSW_LR_VALID_VAL          ( 9U)

#define    HMIMCST_EL_SENS_OFF                  ( 3U)
#define    HMIMCST_EL_SENS_ON                   ( 5U)

#define    HMIMCST_STRING_MAX                   (VDF_HDSIDE_RHD)
#define    HMIMCST_SL_ACST_MAX                  (32U)

#define    HMIMCST_REVLMT_5700RPM               (14U)
#define    HMIMCST_REVLMT_6000RPM               (20U)
#define    HMIMCST_REVLMT_6200RPM               (24U)
#define    HMIMCST_REVLMT_6800RPM               (36U)

/* User Name (Ether/MM-SUB-BUS)                                                 */
#define    HMIMCST_USRNAME_NUM_MASK             (0x0000000FU)

/* User Name(MM-SUB-BUS)                                                        */
#define    HMIMCST_MM_USRNAME_LSB               (16U)
#define    HMIMCST_MM_USRNAME_CNVT_LO_MASK      (0x00FFU)
#define    HMIMCST_MM_USRNAME_CNVT_HI_MASK      (0xFF00U)
#define    HMIMCST_MM_USRNAME_CNVT_SFT          (8U)

/* NickName                                                                     */
#define    HMIMCST_NICKNAME_NUM_MASK            (0x0000FFFFU)
#define    HMIMCST_NICKNAME_LSB                 (16U)
#define    HMIMCST_NICKNAME_TXT_MAX             (0xFFFFU)
#define    HMIMCST_NICKNAME_U4_FSTDAT           (0U)
#define    HMIMCST_NICKNAME_U2_FSTDAT           (0U)

#define    HMIMCST_CAL_ONE                      (1U)    /* calculate as number 1 */
#define    HMIMCST_CAL_TWO                      (2U)    /* calculate as number 2 */

#define    HMIMCST_HUD_STS_NORMAL               (0U)
#define    HMIMCST_HUD_STS_FAIL                 (1U)

/* CSTM Count                                                                   */
#define    HMIMCST_CSTM_CNT_NUM                     (73U)

#define    HMIMCST_CSTM_CNT_HUD                     (0U)
#define    HMIMCST_CSTM_CNT_HUD_ST                  (1U)
#define    HMIMCST_CSTM_CNT_ECO_IND                 (2U)
#define    HMIMCST_CSTM_CNT_EV_IND                  (3U)
#define    HMIMCST_CSTM_CNT_REV_IND                 (4U)
#define    HMIMCST_CSTM_CNT_REV_ST                  (5U)
#define    HMIMCST_CSTM_CNT_REV_PK                  (6U)
#define    HMIMCST_CSTM_CNT_FUEL_CO_GRH             (7U)
#define    HMIMCST_CSTM_CNT_DRVINF_UP               (8U)
#define    HMIMCST_CSTM_CNT_DRVINF_DN               (9U)
#define    HMIMCST_CSTM_CNT_CROSS_ADV               (10U)
#define    HMIMCST_CSTM_CNT_TEL                     (11U)
#define    HMIMCST_CSTM_CNT_AUDIO_OPE               (12U)
#define    HMIMCST_CSTM_CNT_VOL_OPE                 (13U)
#define    HMIMCST_CSTM_CNT_VRCTRL                  (14U)
#define    HMIMCST_CSTM_CNT_ILLUMI_ADJ              (15U)
#define    HMIMCST_CSTM_CNT_HVIND                   (16U)
#define    HMIMCST_CSTM_CNT_TRIP_A_UP               (17U)
#define    HMIMCST_CSTM_CNT_TRIP_A_DN               (18U)
#define    HMIMCST_CSTM_CNT_TRIP_B_UP               (19U)
#define    HMIMCST_CSTM_CNT_TRIP_B_DN               (20U)
#define    HMIMCST_CSTM_CNT_EV_DRINFO               (21U)
#define    HMIMCST_CSTM_CNT_HUD_ANALOG              (22U)
#define    HMIMCST_CSTM_CNT_VIEW_EYE0               (23U)
#define    HMIMCST_CSTM_CNT_WDG_EYE0                (24U)
#define    HMIMCST_CSTM_CNT_VIEW_EYE1               (25U)
#define    HMIMCST_CSTM_CNT_ANALOG_EYE1             (26U)
#define    HMIMCST_CSTM_CNT_WDG_EYE1                (27U)
#define    HMIMCST_CSTM_CNT_VIEW_EYE2               (28U)
#define    HMIMCST_CSTM_CNT_ANALOG_EYE2             (29U)
#define    HMIMCST_CSTM_CNT_VIEW_NAVI               (30U)
#define    HMIMCST_CSTM_CNT_WDG_NAVI                (31U)
#define    HMIMCST_CSTM_CNT_VIEW_ADAS               (32U)
#define    HMIMCST_CSTM_CNT_WDG_ADAS                (33U)
#define    HMIMCST_CSTM_CNT_VIEW_ECO                (34U)
#define    HMIMCST_CSTM_CNT_WDG_ECO                 (35U)
#define    HMIMCST_CSTM_CNT_VIEW_TRACK              (36U)
#define    HMIMCST_CSTM_CNT_VIEW_SHIFT              (37U)
#define    HMIMCST_CSTM_CNT_VIEW_OFFROAD            (38U)
#define    HMIMCST_CSTM_CNT_VIEW_EYE6               (39U)
#define    HMIMCST_CSTM_CNT_FUEL_CO_HIS             (40U)
#define    HMIMCST_CSTM_CNT_ELE_CO_HIS              (41U)
#define    HMIMCST_CSTM_CNT_LEFT_FU_ECO_NP          (42U)
#define    HMIMCST_CSTM_CNT_LEFT_FU_ECO_PHV         (43U)
#define    HMIMCST_CSTM_CNT_LEFT_EL_ECO             (44U)
#define    HMIMCST_CSTM_CNT_LEFT_CONSUMP            (45U)
#define    HMIMCST_CSTM_CNT_LEFT_ECO_IND            (46U)
#define    HMIMCST_CSTM_CNT_LEFT_ECO_JDG            (47U)
#define    HMIMCST_CSTM_CNT_LEFT_EV_RATIO           (48U)
#define    HMIMCST_CSTM_CNT_LEFT_NAVI               (49U)
#define    HMIMCST_CSTM_CNT_LEFT_AUDIO              (50U)
#define    HMIMCST_CSTM_CNT_LEFT_DRV_INFO           (51U)
#define    HMIMCST_CSTM_CNT_LEFT_TRIP_A             (52U)
#define    HMIMCST_CSTM_CNT_LEFT_TRIP_B             (53U)
#define    HMIMCST_CSTM_CNT_LEFT_ENE_MON            (54U)
#define    HMIMCST_CSTM_CNT_LEFT_TPMS               (55U)
#define    HMIMCST_CSTM_CNT_LEFT_4WD                (56U)
#define    HMIMCST_CSTM_CNT_LEFT_TRAC               (57U)
#define    HMIMCST_CSTM_CNT_LEFT_ANGEL              (58U)
#define    HMIMCST_CSTM_CNT_LEFT_PITCH              (59U)
#define    HMIMCST_CSTM_CNT_LEFT_TR_BRAKE           (60U)
#define    HMIMCST_CSTM_CNT_LEFT_TR_BSM             (61U)
#define    HMIMCST_CSTM_CNT_LEFT_VOLT               (62U)
#define    HMIMCST_CSTM_CNT_LEFT_OIL_VOLT           (63U)
#define    HMIMCST_CSTM_CNT_LEFT_ENG_AT             (64U)
#define    HMIMCST_CSTM_CNT_LEFT_ENGINE             (65U)
#define    HMIMCST_CSTM_CNT_LEFT_AT                 (66U)
#define    HMIMCST_CSTM_CNT_LEFT_TURBO              (67U)
#define    HMIMCST_CSTM_CNT_LEFT_BOOST              (68U)
#define    HMIMCST_CSTM_CNT_LEFT_MOTOR              (69U)
#define    HMIMCST_CSTM_CNT_LEFT_SPORTS             (70U)
#define    HMIMCST_CSTM_CNT_LEFT_G_FORCE            (71U)
#define    HMIMCST_CSTM_CNT_LEFT_ADBLUE             (72U)

/* SW Count                                                                     */
#define    HMIMCST_SW_CNT_NUM                   (3U)

#define    HMIMCST_SW_CNT_IDX_HUD_ROT_CW        (0U)
#define    HMIMCST_SW_CNT_IDX_HUD_ROT_CCW       (1U)
#define    HMIMCST_SW_CNT_IDX_DIM               (2U)

/* Operation                                                                    */
#define    HMIMCST_CSTM_CNT_NO_OPE              (0xFFU)
#define    HMIMCST_SW_CNT_NO_OPE                (0x00U)

#define    HMIMCST_SW_CNT_HUD_ROT_MAX           (1U)
#define    HMIMCST_SW_CNT_DIM_MAX               (2U)

/* ChargeMode                                                                    */
#define    HMIMCST_CSTM_CHGMD_MASK              (0x00000003U)
#define    HMIMCST_CSTM_CHGMD_ON                (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    u1_HMIMCST_READ__BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1         u1_mcstid;      /* Meter Cutomize ID   */
    U1         u1_hmimcstid;   /* Local CAN Signal ID */
}ST_HMIMCST_SIG;

typedef struct {
    U1         u1_max;         /* Max Data                 */
    U2         u2_rimid;       /* RIM ID                   */
}ST_HMIMCST_SW_CNT;

typedef struct{
    U2                          u2_lcomid;
    U1                          u1_length;
    U1                          u1_bitpos;
    U1                          u1_max;
    U1                          u1_mcstid;
    U1                          u1_cntid;
}ST_HMIMCST_READDATA;

typedef struct{
    U2                          u2_lcomid;
    U4                          u4_mask;
    U1                          u1_bitpos;
    U4                          u4_max;
    U1                          u1_mcstid;
}ST_HMITFTCNTTS_READDATA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_sp_hmimcst_sigdata[HMIMCST_ID_NUM];

/* Hud Rot RAM                                                                  */
static S1   s1_s_hmimcst_hud_rot;
static S1   s1_s_hmimcst_hud_rot_pre;
static U2   u2_s_hmimcst_timer;
static U1   u1_s_hmimcst_hud_rot_sts;

/* User Name RAM (Ether)                                                        */
static U4   u4_sp_hmimcst_user1dat_buf[HMIMCST_USER_DTA_NUM];
static U4   u4_sp_hmimcst_user2dat_buf[HMIMCST_USER_DTA_NUM];
static U4   u4_sp_hmimcst_user3dat_buf[HMIMCST_USER_DTA_NUM];
static U4   u4_s_hmimcst_user1_updatenum_old;
static U4   u4_s_hmimcst_user2_updatenum_old;
static U4   u4_s_hmimcst_user3_updatenum_old;

/* User Name RAM (MM-SUB-BUS)                                                   */
static U4   u4_sp_hmimcst_mm_user1dat_buf[HMIMCST_USER_DTA_NUM];
static U4   u4_sp_hmimcst_mm_user2dat_buf[HMIMCST_USER_DTA_NUM];
static U4   u4_sp_hmimcst_mm_user3dat_buf[HMIMCST_USER_DTA_NUM];

static U4   u4_s_hmimcst_mm_user1_updatenum_old;
static U4   u4_s_hmimcst_mm_user2_updatenum_old;
static U4   u4_s_hmimcst_mm_user3_updatenum_old;

/* SW Count                                                                     */
static U1   u1_sp_hmimcst_cstm_cnt[HMIMCST_CSTM_CNT_NUM];
static U1   u1_sp_hmimcst_pre_val_cstm_cnt[HMIMCST_CSTM_CNT_NUM];
static U1   u1_sp_hmimcst_sw_cnt[HMIMCST_SW_CNT_NUM];
static U1   u1_sp_hmimcst_pre_val_sw_cnt[HMIMCST_SW_CNT_NUM];

/* NickName RAM                                                                 */
static U2   u2_sp_hmimcst_nickname1dat_buf[HMIMCST_NICKNAME_U2_DTA_NUM];
static U2   u2_sp_hmimcst_nickname2dat_buf[HMIMCST_NICKNAME_U2_DTA_NUM];
static U2   u2_sp_hmimcst_nickname3dat_buf[HMIMCST_NICKNAME_U2_DTA_NUM];

/* Customize  RAM                                                               */
static U1   u1_s_hmimcst_reset_req_pre;
static U2   u2_s_hmimcst_to;
static U1   u1_s_hmimcst_mwvc_ope;

/* HUDONOFFSW  HardSW INPUT RAM                                                 */
static U1   u1_s_hmimcst_hud_hwsw_pre;

/* HUD Cstm RAM                                                                 */
static U1   u1_s_hmimcst_hud_cstm_pre;

/* DID-10B3  RAM                                                                */
static U1   u1_s_hmimcst_chg_md_on;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void      vd_s_HmiMcstHUDRotCtr(const U1 u1_a_HUDCW , const U1 u1_a_HUDCCW);
static void      vd_s_HmiMcstHUDRotCW(void);
static void      vd_s_HmiMcstHUDRotCCW(void);
static void      vd_s_HmiMcstHUDRotCalc(const U1 u1_a_DIRECTION);
static void      vd_s_HmiMcstHUDONOFFCtr(void);
static U1        u1_s_HmiMcstJdgHwSwHUD(void);
static U1        u1_s_HmimcstCstmPtChk(const U1 u1_a_ID, const U1 u1_a_RDATA);
static void      vd_s_HmiMcstSetUserName(void);
static void      vd_s_HmiMcstSetMMUserName(void);
static void      vd_s_HmiMcstSetNickName(void);
static void      vd_s_HmiMcstSWCount(const U2 u2_a_RIMID);
static void      vd_s_HmiMcstSWCountMgr(void);
static U1        u1_s_HmimcstHudChk(void);
static inline U1 u1_s_HmimcstCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstInit(void)
{
    U4 u4_t_loop;   /* loop counter */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_ID_NUM ; u4_t_loop++){
        u1_sp_hmimcst_sigdata[u4_t_loop] = (U1)HMIMCST_SW_NO_OPE;
    }

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_CSTM_CNT_NUM ; u4_t_loop++){
        u1_sp_hmimcst_cstm_cnt[u4_t_loop] = (U1)HMIMCST_CSTM_CNT_NO_OPE;
        u1_sp_hmimcst_pre_val_cstm_cnt[u4_t_loop] = (U1)HMIMCST_CSTM_CNT_NO_OPE;
    }

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_SW_CNT_NUM ; u4_t_loop++){
        u1_sp_hmimcst_sw_cnt[u4_t_loop] = (U1)HMIMCST_SW_CNT_NO_OPE;
        u1_sp_hmimcst_pre_val_sw_cnt[u4_t_loop] = (U1)HMIMCST_SW_CNT_NO_OPE;
    }

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_USER_DTA_NUM ; u4_t_loop++){
        u4_sp_hmimcst_user1dat_buf[u4_t_loop]    = (U4)HMIMCST_USERBUF_INIVAL;
        u4_sp_hmimcst_user2dat_buf[u4_t_loop]    = (U4)HMIMCST_USERBUF_INIVAL;
        u4_sp_hmimcst_user3dat_buf[u4_t_loop]    = (U4)HMIMCST_USERBUF_INIVAL;
        u4_sp_hmimcst_mm_user1dat_buf[u4_t_loop] = (U4)HMIMCST_USERBUF_INIVAL;
        u4_sp_hmimcst_mm_user2dat_buf[u4_t_loop] = (U4)HMIMCST_USERBUF_INIVAL;
        u4_sp_hmimcst_mm_user3dat_buf[u4_t_loop] = (U4)HMIMCST_USERBUF_INIVAL;
    }
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_NICKNAME_U2_DTA_NUM; u4_t_loop++){
        u2_sp_hmimcst_nickname1dat_buf[u4_t_loop] = (U2)HMIMCST_NICKNAME_TXT_MAX;
        u2_sp_hmimcst_nickname2dat_buf[u4_t_loop] = (U2)HMIMCST_NICKNAME_TXT_MAX;
        u2_sp_hmimcst_nickname3dat_buf[u4_t_loop] = (U2)HMIMCST_NICKNAME_TXT_MAX;
    }
    s1_s_hmimcst_hud_rot                = (S1)u1_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_s_hmimcst_hud_rot_pre            = s1_s_hmimcst_hud_rot;

    u2_s_hmimcst_timer                  = (U2)0U;
    u1_s_hmimcst_hud_rot_sts            = (U1)HMIMCST_HUDROT_NO_OPE;

    u4_s_hmimcst_user1_updatenum_old    = (U4)HMIMCST_UPDATENUM_INIVAL;
    u4_s_hmimcst_user2_updatenum_old    = (U4)HMIMCST_UPDATENUM_INIVAL;
    u4_s_hmimcst_user3_updatenum_old    = (U4)HMIMCST_UPDATENUM_INIVAL;

    u4_s_hmimcst_mm_user1_updatenum_old = (U4)HMIMCST_UPDATENUM_INIVAL;
    u4_s_hmimcst_mm_user2_updatenum_old = (U4)HMIMCST_UPDATENUM_INIVAL;
    u4_s_hmimcst_mm_user3_updatenum_old = (U4)HMIMCST_UPDATENUM_INIVAL;

    u1_s_hmimcst_reset_req_pre          = (U1)HMIMCST_SW_NO_OPE;

    u2_s_hmimcst_to                     = (U2)HMIPROXY_TOC_MAX;

    u1_s_hmimcst_mwvc_ope               = (U1)HMIMCST_MWVC_OPE_INIT;

    u1_s_hmimcst_hud_hwsw_pre           = (U1)IOHW_DIFLT_SWITCH_UNKNWN;

    u1_s_hmimcst_hud_cstm_pre           = u1_g_McstBf((U1)MCST_BFI_HUD);

    u1_s_hmimcst_chg_md_on              = (U1)FALSE;

}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstMainTask(void)
{
    static const U2 u2_s_HMIMCST_TO = (U2)1000U / (U2)20U;
    U1           u1_t_igon;
    U1           u1_t_to;
    U1           u1_t_gvif;
    U1           u1_t_mmcnnct_comsys;

    u1_t_to = u1_g_HmiProxyToc(&u2_s_hmimcst_to, u2_s_HMIMCST_TO);
    u1_t_igon = u1_g_VehopemdIgnOn();
    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);

    /* "MET-M_METCSTM-" Not applicable */

    if(u1_t_to   == (U1)FALSE){
        if(u1_t_igon == (U1)TRUE ){

            /* Judge SW ON Edge */
            /* vd_s_HmiMcstOnEdgeCtr(); */

            /* Judge SW No Operation */
            /* vd_s_HmiMcstSWNoOpeCtr(); */

            /* STSW Assigned Arbitration */
            /* vd_s_HmiMcstStsw(); */

            /* Judge STSW RIGHT Preset Group */
            /* vd_s_HmiMcstSTSWRHSetJdg(u1_sp_hmimcst_sigdata[HMIMCST_L_STSWRH_A]); */

            /* Judge STSW Left Preset Group */
            /* vd_s_HmiMcstSTSWLHSetJdg(u1_sp_hmimcst_sigdata[HMIMCST_L_STSWLH_A]); */

            if(u1_t_gvif == (U1)TRUE ){
                /* HUD Rot */
                vd_s_HmiMcstHUDRotCtr(u1_sp_hmimcst_sigdata[HMIMCST_CSTM_HUDRTCW] , u1_sp_hmimcst_sigdata[HMIMCST_CSTM_HUDRTCCW]);

                /* HUD ON/OFF */
                vd_s_HmiMcstHUDONOFFCtr();

                /* HUD MODE */
                /* vd_s_HmiMcstHUDModeCtr(); */
            }

            /* REV Limit */
            /* vd_s_HmiMcstSetRevLimit(); */

            /* Ending */
            /* vd_g_McstBfPut((U1)MCST_BFI_ENDING, (U1)HMIMCST_VAL_ON); */      /* Fixed value */

            /* Customize Reset */
            /* vd_s_HmiMcstReset(); */

            /* SW Operation Count */
            vd_s_HmiMcstSWCountMgr();
        }

        /* Set UserName */
        u1_t_mmcnnct_comsys = u1_g_VardefMmMthd();
        if(u1_t_mmcnnct_comsys == (U1)VDF_MM_MTHD_ETHER){
            vd_s_HmiMcstSetUserName();
        }
        else{
            vd_s_HmiMcstSetMMUserName();
        }

        /* Set NickName */
        vd_s_HmiMcstSetNickName();
    }

}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiMcstHUDRotCtr                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstHUDRotCtr(const U1 u1_a_HUDCW , const U1 u1_a_HUDCCW){

    U2    u2_t_hud_light;
    U1    u1_t_func;

    u2_t_hud_light = (U2)0U;

    (void)u1_g_HdimmgrGetPrcnt((U1)HDIMMGR_OTPTSIG_OTPTDUTY, &u2_t_hud_light);

    if(u2_t_hud_light != (U2)0U){
        u1_t_func = (U1)TRUE;
    }
    else {
        u1_t_func = (U1)FALSE;
    }

    if(u1_t_func == (U1)TRUE){
        if((u1_a_HUDCW == (U1)TRUE) && (u1_a_HUDCCW  == (U1)FALSE)){
            vd_s_HmiMcstHUDRotCW();
        }
        else if((u1_a_HUDCCW  == (U1)TRUE) && (u1_a_HUDCW == (U1)FALSE)){
            vd_s_HmiMcstHUDRotCCW();
        }
        else{
            u2_s_hmimcst_timer = (U2)0U;
            u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_NO_OPE;
        }
    }
    else{
        u2_s_hmimcst_timer = (U2)0U;
        u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_NO_OPE;
    }

    if(s1_s_hmimcst_hud_rot != s1_s_hmimcst_hud_rot_pre){
        vd_g_McstBfPut((U1)MCST_BFI_HUD_ROT, (U1)s1_s_hmimcst_hud_rot);
    }

    s1_s_hmimcst_hud_rot_pre = s1_s_hmimcst_hud_rot;

}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstHUDRotCW                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstHUDRotCW(void){

    static const U2     u2_s_HMIMCST_HLD_INIT = (U2)800U / (U2)HMIMCST_MAIN_TICK;   /* 800ms */
    static const U2     u2_s_HMIMCST_HLD      = (U2)500U / (U2)HMIMCST_MAIN_TICK;   /* 500ms */

    switch(u1_s_hmimcst_hud_rot_sts){
        case (U1)HMIMCST_HUDROT_NO_OPE:
        case (U1)HMIMCST_HUDROT_CCW:
        case (U1)HMIMCST_HUDROT_CCW_HLD:
            vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_UP);
            u2_s_hmimcst_timer = (U2)0U;
            u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CW;
            break;
        case (U1)HMIMCST_HUDROT_CW:
            if(u2_s_hmimcst_timer >= u2_s_HMIMCST_HLD_INIT){
                vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_UP);
                u2_s_hmimcst_timer = (U2)0U;
                u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CW_HLD;
            }
            break;
        case (U1)HMIMCST_HUDROT_CW_HLD:
            if(u2_s_hmimcst_timer >= u2_s_HMIMCST_HLD){
                vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_UP);
                u2_s_hmimcst_timer = (U2)0U;
                u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CW_HLD;
            }
            break;
        default:
            u2_s_hmimcst_timer = (U2)0U;
            u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_NO_OPE;
            break;
    }

    if(u2_s_hmimcst_timer < (U2)U2_MAX){
        u2_s_hmimcst_timer++;
    }
}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstHUDRotCCW                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstHUDRotCCW(void){

    static const U2     u2_s_HMIMCST_HLD_INIT = (U2)800U / (U2)HMIMCST_MAIN_TICK;   /* 800ms */
    static const U2     u2_s_HMIMCST_HLD      = (U2)500U / (U2)HMIMCST_MAIN_TICK;   /* 500ms */

    switch(u1_s_hmimcst_hud_rot_sts){
        case (U1)HMIMCST_HUDROT_NO_OPE:
        case (U1)HMIMCST_HUDROT_CW:
        case (U1)HMIMCST_HUDROT_CW_HLD:
            vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_DOWN);
            u2_s_hmimcst_timer = (U2)0U;
            u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CCW;
            break;
        case (U1)HMIMCST_HUDROT_CCW:
            if(u2_s_hmimcst_timer >= u2_s_HMIMCST_HLD_INIT){
                vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_DOWN);
                u2_s_hmimcst_timer = (U2)0U;
                u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CCW_HLD;
            }
            break;
        case (U1)HMIMCST_HUDROT_CCW_HLD:
            if(u2_s_hmimcst_timer >= u2_s_HMIMCST_HLD){
                vd_s_HmiMcstHUDRotCalc((U1)HMIMCST_HUDROT_STEP_DOWN);
                u2_s_hmimcst_timer = (U2)0U;
                u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_CCW_HLD;
            }
            break;
        default:
            u2_s_hmimcst_timer = (U2)0U;
            u1_s_hmimcst_hud_rot_sts = (U1)HMIMCST_HUDROT_NO_OPE;
            break;
    }

    if(u2_s_hmimcst_timer < (U2)U2_MAX){
        u2_s_hmimcst_timer++;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_HmiMcstHUDRotCalc                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstHUDRotCalc(const U1 u1_a_DIRECTION){

    static const S2 s2_s_HMIMCST_HUDDEGSTEPLSB = (S2)10;

    S1  s1_t_lmt_ccw;
    S1  s1_t_lmt_cw;
    U1  u1_t_lsb;
    S2  s2_t_lmt_tmp;
    S1  s1_t_now;

    u1_t_lsb = u1_s_HmimcstCalibU1MinChk(u1_CALIB_MCUID0578_DEG_RTSTEP, (U1)CALIB_MCUID0578_MIN, (U1)CALIB_MCUID0578_DEF);

    s2_t_lmt_tmp = (((S2)((U2)u1_CALIB_MCUID0577_DEGCCW) - (S2)((U2)U1_MAX)) * s2_s_HMIMCST_HUDDEGSTEPLSB) / (S2)((U2)u1_t_lsb);
    /* ((Min:0 Max:255) - 255) * 10 / (Min:1 Max:255) */
    if(s2_t_lmt_tmp < (S2)((S1)MCST_HUDROT_CCW_LMT)){
        s1_t_lmt_ccw = (S1)MCST_HUDROT_CCW_LMT;
    }
    else{
        s1_t_lmt_ccw = (S1)s2_t_lmt_tmp;
    }

    s2_t_lmt_tmp = ((S2)((U2)u1_CALIB_MCUID0576_DEGCW) * s2_s_HMIMCST_HUDDEGSTEPLSB) / (S2)((U2)u1_t_lsb);
    /* (Min:0 Max:255)         * 10 / (Min:1 Max:255) */
    if(s2_t_lmt_tmp > (S2)MCST_HUDROT_CW_LMT){
        s1_t_lmt_cw  = (S1)MCST_HUDROT_CW_LMT;
    }
    else{
        s1_t_lmt_cw  = (S1)s2_t_lmt_tmp;
    }

    s1_t_now = (S1)u1_g_McstBf((U1)MCST_BFI_HUD_ROT);

    if (u1_a_DIRECTION == (U1)HMIMCST_HUDROT_STEP_DOWN){
        if (s1_t_now > s1_t_lmt_ccw){
            s1_s_hmimcst_hud_rot = s1_t_now - (S1)HMIMCST_HUDROT_STEP_ONE;
        }
    } else {
        if (s1_t_now < s1_t_lmt_cw){
            s1_s_hmimcst_hud_rot = s1_t_now + (S1)HMIMCST_HUDROT_STEP_ONE;
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_HmiMcstHUDONOFFCtr                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstHUDONOFFCtr(void)
{
    U1 u1_t_hud_now;
    U1 u1_t_result_hwsw;

    u1_t_hud_now               = u1_g_McstBf((U1)MCST_BFI_HUD);

    /* HardSW */
    u1_t_result_hwsw           = u1_s_HmiMcstJdgHwSwHUD();

    if(u1_t_hud_now != u1_s_hmimcst_hud_cstm_pre){
        /* MetCstm Update */
    }
    else if(u1_t_result_hwsw == (U1)HMIMCST_CMND_SWITCH){
        if(u1_t_hud_now != (U1)HMIMCST_VAL_ON){
            u1_t_hud_now = (U1)HMIMCST_VAL_ON;
        }
        else{
            u1_t_hud_now = (U1)HMIMCST_VAL_OFF;
        }
        vd_g_McstBfPut((U1)MCST_BFI_HUD, u1_t_hud_now);
    }
    else{
        /*do nothing*/
    }
    u1_s_hmimcst_hud_cstm_pre  = u1_t_hud_now;
}

/*===================================================================================================================================*/
/* static  U1    u1_s_HmiMcstJdgHwSwHUD                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_HmiMcstJdgHwSwHUD(void)
{
    U1  u1_t_hud_cstm;
    U1  u1_t_hud_hwsw;

    u1_t_hud_cstm                  = (U1)HMIMCST_CMND_NON;
    u1_t_hud_hwsw                  = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_HUD_MAIN_SW_IN);

    if((u1_s_hmimcst_hud_hwsw_pre == (U1)IOHW_DIFLT_SWITCH_INACT) && (u1_t_hud_hwsw == (U1)IOHW_DIFLT_SWITCH_ACT)){
        u1_t_hud_cstm = (U1)HMIMCST_CMND_SWITCH;
    }
    u1_s_hmimcst_hud_hwsw_pre      = u1_t_hud_hwsw;
    return(u1_t_hud_cstm);
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiCstmPut(    const U4 * u4_ap_PDU_RX)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 * u4_ap_PDU_RX                                                                                          */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiCstmPut(const U4 * u4_ap_PDU_RX)
{
    static const ST_HMIMCST_READDATA st_sp_HMIMCST_SPI_METCSTMZ[] = {
        /*u2_lcomid,u1_length,  u1_bitpos,  u1_max,                         u1_mcstid,                      u1_cntid    */
        {(U2)1U,    (U1)2U,     (U1)26U,    (U1)MCST_HUD_MAX,               (U1)MCST_BFI_HUD,               (U1)HMIMCST_CSTM_CNT_HUD                },
        {(U2)1U,    (U1)3U,     (U1)18U,    (U1)MCST_HUD_ST_MAX,            (U1)MCST_BFI_HUD_ST,            (U1)HMIMCST_CSTM_CNT_HUD_ST             },
        {(U2)1U,    (U1)2U,     (U1)10U,    (U1)MCST_ECO_IND_MAX,           (U1)MCST_BFI_ECO_IND,           (U1)HMIMCST_CSTM_CNT_ECO_IND            },
        {(U2)1U,    (U1)2U,     (U1)12U,    (U1)MCST_EV_IND_MAX,            (U1)MCST_BFI_EV_IND,            (U1)HMIMCST_CSTM_CNT_EV_IND             },
        {(U2)1U,    (U1)2U,     (U1)30U,    (U1)MCST_CROSS_ADV_MAX,         (U1)MCST_BFI_CROSS_ADV,         (U1)HMIMCST_CSTM_CNT_CROSS_ADV          },
        {(U2)1U,    (U1)2U,     (U1)22U,    (U1)MCST_DRVINF_UP_MAX,         (U1)MCST_BFI_DRVINF_UP,         (U1)HMIMCST_CSTM_CNT_DRVINF_UP          },
        {(U2)1U,    (U1)2U,     (U1)24U,    (U1)MCST_DRVINF_DN_MAX,         (U1)MCST_BFI_DRVINF_DN,         (U1)HMIMCST_CSTM_CNT_DRVINF_DN          },
        {(U2)2U,    (U1)2U,     (U1)2U,     (U1)MCST_AUDIO_OPE_MAX,         (U1)MCST_BFI_AUDIO_OPE,         (U1)HMIMCST_CSTM_CNT_AUDIO_OPE          },
        {(U2)1U,    (U1)2U,     (U1)16U,    (U1)MCST_HVIND_MAX,             (U1)MCST_BFI_HVIND,             (U1)HMIMCST_CSTM_CNT_HVIND              },
        {(U2)1U,    (U1)2U,     (U1)28U,    (U1)HMIMCST_VAL_ON,             (U1)MCST_BFI_NOW_RUN,           (U1)U1_MAX                              },
        {(U2)2U,    (U1)2U,     (U1)0U,     (U1)MCST_TEL_MAX,               (U1)MCST_BFI_TEL,               (U1)HMIMCST_CSTM_CNT_TEL                },
        {(U2)2U,    (U1)2U,     (U1)4U,     (U1)MCST_VOL_OPE_MAX,           (U1)MCST_BFI_VOL_OPE,           (U1)HMIMCST_CSTM_CNT_VOL_OPE            },
        {(U2)2U,    (U1)2U,     (U1)6U,     (U1)MCST_VRCTRL_MAX,            (U1)MCST_BFI_VRCTRL,            (U1)HMIMCST_CSTM_CNT_VRCTRL             },
        {(U2)2U,    (U1)2U,     (U1)10U,    (U1)HMIMCST_VAL_ON,             (U1)MCST_BFI_STS_ACT,           (U1)U1_MAX                              },
        {(U2)2U,    (U1)8U,     (U1)16U,    (U1)MCST_REV_ST_MAX,            (U1)MCST_BFI_REV_ST,            (U1)HMIMCST_CSTM_CNT_REV_ST             },
        {(U2)2U,    (U1)2U,     (U1)24U,    (U1)MCST_REV_IND_MAX,           (U1)MCST_BFI_REV_IND,           (U1)HMIMCST_CSTM_CNT_REV_IND            },
        {(U2)2U,    (U1)2U,     (U1)26U,    (U1)MCST_REV_PK_MAX,            (U1)MCST_BFI_REV_PK,            (U1)HMIMCST_CSTM_CNT_REV_PK             },
        {(U2)2U,    (U1)2U,     (U1)28U,    (U1)MCST_ILLUMI_ADJ_MAX,        (U1)MCST_BFI_ILLUMI_ADJ,        (U1)HMIMCST_CSTM_CNT_ILLUMI_ADJ         },
        {(U2)3U,    (U1)2U,     (U1)8U,     (U1)MCST_EV_DRINFO_MAX,         (U1)MCST_BFI_EV_DRINFO,         (U1)HMIMCST_CSTM_CNT_EV_DRINFO          },
        {(U2)3U,    (U1)2U,     (U1)0U,     (U1)MCST_TRIP_A_UP_MAX,         (U1)MCST_BFI_TRIP_A_UP,         (U1)HMIMCST_CSTM_CNT_TRIP_A_UP          },
        {(U2)3U,    (U1)2U,     (U1)2U,     (U1)MCST_TRIP_A_DN_MAX,         (U1)MCST_BFI_TRIP_A_DN,         (U1)HMIMCST_CSTM_CNT_TRIP_A_DN          },
        {(U2)3U,    (U1)2U,     (U1)4U,     (U1)MCST_TRIP_B_UP_MAX,         (U1)MCST_BFI_TRIP_B_UP,         (U1)HMIMCST_CSTM_CNT_TRIP_B_UP          },
        {(U2)3U,    (U1)2U,     (U1)6U,     (U1)MCST_TRIP_B_DN_MAX,         (U1)MCST_BFI_TRIP_B_DN,         (U1)HMIMCST_CSTM_CNT_TRIP_B_DN          },
        {(U2)3U,    (U1)3U,     (U1)10U,    (U1)MCST_ANALOG_EYE1_MAX,       (U1)MCST_BFI_ANALOG_EYE1,       (U1)HMIMCST_CSTM_CNT_ANALOG_EYE1        },
        {(U2)3U,    (U1)3U,     (U1)13U,    (U1)MCST_ANALOG_EYE2_MAX,       (U1)MCST_BFI_ANALOG_EYE2,       (U1)HMIMCST_CSTM_CNT_ANALOG_EYE2        },
        {(U2)3U,    (U1)3U,     (U1)19U,    (U1)MCST_METWRNCSTM_MAX,        (U1)MCST_BFI_METWRNCSTM,        (U1)U1_MAX                              },
        {(U2)4U,    (U1)2U,     (U1)0U,     (U1)MCST_NAME_MAX,              (U1)MCST_BFI_NAME_DRV1,         (U1)U1_MAX                              },
        {(U2)4U,    (U1)2U,     (U1)2U,     (U1)MCST_NAME_MAX,              (U1)MCST_BFI_NAME_DRV2,         (U1)U1_MAX                              },
        {(U2)4U,    (U1)2U,     (U1)4U,     (U1)MCST_NAME_MAX,              (U1)MCST_BFI_NAME_DRV3,         (U1)U1_MAX                              },
        {(U2)6U,    (U1)2U,     (U1)4U,     (U1)MCST_VIEW_EYE0_MAX,         (U1)MCST_BFI_VIEW_EYE0,         (U1)HMIMCST_CSTM_CNT_VIEW_EYE0          },
        {(U2)6U,    (U1)2U,     (U1)6U,     (U1)MCST_WDG_EYE0_MAX,          (U1)MCST_BFI_WDG_EYE0,          (U1)HMIMCST_CSTM_CNT_WDG_EYE0           },
        {(U2)6U,    (U1)2U,     (U1)8U,     (U1)MCST_VIEW_EYE1_MAX,         (U1)MCST_BFI_VIEW_EYE1,         (U1)HMIMCST_CSTM_CNT_VIEW_EYE1          },
        {(U2)6U,    (U1)2U,     (U1)10U,    (U1)MCST_WDG_EYE1_MAX,          (U1)MCST_BFI_WDG_EYE1,          (U1)HMIMCST_CSTM_CNT_WDG_EYE1           },
        {(U2)6U,    (U1)2U,     (U1)12U,    (U1)MCST_VIEW_EYE2_MAX,         (U1)MCST_BFI_VIEW_EYE2,         (U1)HMIMCST_CSTM_CNT_VIEW_EYE2          },
        {(U2)6U,    (U1)2U,     (U1)14U,    (U1)MCST_VIEW_NAVI_MAX,         (U1)MCST_BFI_VIEW_NAVI,         (U1)HMIMCST_CSTM_CNT_VIEW_NAVI          },
        {(U2)6U,    (U1)2U,     (U1)16U,    (U1)MCST_WDG_NAVI_MAX,          (U1)MCST_BFI_WDG_NAVI,          (U1)HMIMCST_CSTM_CNT_WDG_NAVI           },
        {(U2)6U,    (U1)2U,     (U1)18U,    (U1)MCST_VIEW_ADAS_MAX,         (U1)MCST_BFI_VIEW_ADAS,         (U1)HMIMCST_CSTM_CNT_VIEW_ADAS          },
        {(U2)6U,    (U1)2U,     (U1)20U,    (U1)MCST_WDG_ADAS_MAX,          (U1)MCST_BFI_WDG_ADAS,          (U1)HMIMCST_CSTM_CNT_WDG_ADAS           },
        {(U2)6U,    (U1)2U,     (U1)22U,    (U1)MCST_VIEW_ECO_MAX,          (U1)MCST_BFI_VIEW_ECO,          (U1)HMIMCST_CSTM_CNT_VIEW_ECO           },
        {(U2)6U,    (U1)2U,     (U1)24U,    (U1)MCST_WDG_ECO_MAX,           (U1)MCST_BFI_WDG_ECO,           (U1)HMIMCST_CSTM_CNT_WDG_ECO            },
        {(U2)6U,    (U1)2U,     (U1)26U,    (U1)MCST_VIEW_TRACK_MAX,        (U1)MCST_BFI_VIEW_TRACK,        (U1)HMIMCST_CSTM_CNT_VIEW_TRACK         },
        {(U2)6U,    (U1)2U,     (U1)28U,    (U1)MCST_VIEW_SHIFT_MAX,        (U1)MCST_BFI_VIEW_SHIFT,        (U1)HMIMCST_CSTM_CNT_VIEW_SHIFT         },
        {(U2)6U,    (U1)2U,     (U1)30U,    (U1)MCST_VIEW_OFFROAD_MAX,      (U1)MCST_BFI_VIEW_OFFROAD,      (U1)HMIMCST_CSTM_CNT_VIEW_OFFROAD       },
        {(U2)7U,    (U1)2U,     (U1)0U,     (U1)MCST_VIEW_EYE6_MAX,         (U1)MCST_BFI_VIEW_EYE6,         (U1)HMIMCST_CSTM_CNT_VIEW_EYE6          },
        {(U2)7U,    (U1)2U,     (U1)2U,     (U1)MCST_LEFT_FU_ECO_NP_MAX,    (U1)MCST_BFI_LEFT_FU_ECO_NP,    (U1)HMIMCST_CSTM_CNT_LEFT_FU_ECO_NP     },
        {(U2)7U,    (U1)2U,     (U1)4U,     (U1)MCST_LEFT_EL_ECO_MAX,       (U1)MCST_BFI_LEFT_EL_ECO,       (U1)HMIMCST_CSTM_CNT_LEFT_EL_ECO        },
        {(U2)7U,    (U1)2U,     (U1)6U,     (U1)MCST_LEFT_CONSUMP_MAX,      (U1)MCST_BFI_LEFT_CONSUMP,      (U1)HMIMCST_CSTM_CNT_LEFT_CONSUMP       },
        {(U2)7U,    (U1)2U,     (U1)8U,     (U1)MCST_LEFT_ECO_IND_MAX,      (U1)MCST_BFI_LEFT_ECO_IND,      (U1)HMIMCST_CSTM_CNT_LEFT_ECO_IND       },
        {(U2)7U,    (U1)2U,     (U1)10U,    (U1)MCST_LEFT_ECO_JDG_MAX,      (U1)MCST_BFI_LEFT_ECO_JDG,      (U1)HMIMCST_CSTM_CNT_LEFT_ECO_JDG       },
        {(U2)7U,    (U1)2U,     (U1)12U,    (U1)MCST_LEFT_EV_RATIO_MAX,     (U1)MCST_BFI_LEFT_EV_RATIO,     (U1)HMIMCST_CSTM_CNT_LEFT_EV_RATIO      },
        {(U2)7U,    (U1)2U,     (U1)14U,    (U1)MCST_LEFT_NAVI_MAX,         (U1)MCST_BFI_LEFT_NAVI,         (U1)HMIMCST_CSTM_CNT_LEFT_NAVI          },
        {(U2)7U,    (U1)2U,     (U1)16U,    (U1)MCST_LEFT_AUDIO_MAX,        (U1)MCST_BFI_LEFT_AUDIO,        (U1)HMIMCST_CSTM_CNT_LEFT_AUDIO         },
        {(U2)7U,    (U1)2U,     (U1)18U,    (U1)MCST_LEFT_DRV_INFO_MAX,     (U1)MCST_BFI_LEFT_DRV_INFO,     (U1)HMIMCST_CSTM_CNT_LEFT_DRV_INFO      },
        {(U2)7U,    (U1)2U,     (U1)20U,    (U1)MCST_LEFT_TRIP_A_MAX,       (U1)MCST_BFI_LEFT_TRIP_A,       (U1)HMIMCST_CSTM_CNT_LEFT_TRIP_A        },
        {(U2)7U,    (U1)2U,     (U1)22U,    (U1)MCST_LEFT_TRIP_B_MAX,       (U1)MCST_BFI_LEFT_TRIP_B,       (U1)HMIMCST_CSTM_CNT_LEFT_TRIP_B        },
        {(U2)7U,    (U1)2U,     (U1)24U,    (U1)MCST_LEFT_ENE_MON_MAX,      (U1)MCST_BFI_LEFT_ENE_MON,      (U1)HMIMCST_CSTM_CNT_LEFT_ENE_MON       },
        {(U2)7U,    (U1)2U,     (U1)26U,    (U1)MCST_LEFT_4WD_MAX,          (U1)MCST_BFI_LEFT_4WD,          (U1)HMIMCST_CSTM_CNT_LEFT_4WD           },
        {(U2)7U,    (U1)2U,     (U1)28U,    (U1)MCST_LEFT_TRAC_MAX,         (U1)MCST_BFI_LEFT_TRAC,         (U1)HMIMCST_CSTM_CNT_LEFT_TRAC          },
        {(U2)7U,    (U1)2U,     (U1)30U,    (U1)MCST_LEFT_ANGEL_MAX,        (U1)MCST_BFI_LEFT_ANGEL,        (U1)HMIMCST_CSTM_CNT_LEFT_ANGEL         },
        {(U2)8U,    (U1)2U,     (U1)0U,     (U1)MCST_LEFT_PITCH_MAX,        (U1)MCST_BFI_LEFT_PITCH,        (U1)HMIMCST_CSTM_CNT_LEFT_PITCH         },
        {(U2)8U,    (U1)2U,     (U1)2U,     (U1)MCST_LEFT_TR_BRAKE_MAX,     (U1)MCST_BFI_LEFT_TR_BRAKE,     (U1)HMIMCST_CSTM_CNT_LEFT_TR_BRAKE      },
        {(U2)8U,    (U1)2U,     (U1)4U,     (U1)MCST_LEFT_TR_BSM_MAX,       (U1)MCST_BFI_LEFT_TR_BSM,       (U1)HMIMCST_CSTM_CNT_LEFT_TR_BSM        },
        {(U2)8U,    (U1)2U,     (U1)6U,     (U1)MCST_LEFT_VOLT_MAX,         (U1)MCST_BFI_LEFT_VOLT,         (U1)HMIMCST_CSTM_CNT_LEFT_VOLT          },
        {(U2)8U,    (U1)2U,     (U1)8U,     (U1)MCST_LEFT_OIL_VOLT_MAX,     (U1)MCST_BFI_LEFT_OIL_VOLT,     (U1)HMIMCST_CSTM_CNT_LEFT_OIL_VOLT      },
        {(U2)8U,    (U1)2U,     (U1)10U,    (U1)MCST_LEFT_ENG_AT_MAX,       (U1)MCST_BFI_LEFT_ENG_AT,       (U1)HMIMCST_CSTM_CNT_LEFT_ENG_AT        },
        {(U2)8U,    (U1)2U,     (U1)12U,    (U1)MCST_LEFT_ENGINE_MAX,       (U1)MCST_BFI_LEFT_ENGINE,       (U1)HMIMCST_CSTM_CNT_LEFT_ENGINE        },
        {(U2)8U,    (U1)2U,     (U1)14U,    (U1)MCST_LEFT_AT_MAX,           (U1)MCST_BFI_LEFT_AT,           (U1)HMIMCST_CSTM_CNT_LEFT_AT            },
        {(U2)8U,    (U1)2U,     (U1)16U,    (U1)MCST_LEFT_TURBO_MAX,        (U1)MCST_BFI_LEFT_TURBO,        (U1)HMIMCST_CSTM_CNT_LEFT_TURBO         },
        {(U2)8U,    (U1)2U,     (U1)18U,    (U1)MCST_LEFT_BOOST_MAX,        (U1)MCST_BFI_LEFT_BOOST,        (U1)HMIMCST_CSTM_CNT_LEFT_BOOST         },
        {(U2)8U,    (U1)2U,     (U1)20U,    (U1)MCST_LEFT_MOTOR_MAX,        (U1)MCST_BFI_LEFT_MOTOR,        (U1)HMIMCST_CSTM_CNT_LEFT_MOTOR         },
        {(U2)8U,    (U1)2U,     (U1)22U,    (U1)MCST_LEFT_SPORTS_MAX,       (U1)MCST_BFI_LEFT_SPORTS,       (U1)HMIMCST_CSTM_CNT_LEFT_SPORTS        },
        {(U2)8U,    (U1)2U,     (U1)24U,    (U1)MCST_LEFT_G_FORCE_MAX,      (U1)MCST_BFI_LEFT_G_FORCE,      (U1)HMIMCST_CSTM_CNT_LEFT_G_FORCE       },
        {(U2)8U,    (U1)2U,     (U1)26U,    (U1)MCST_LEFT_ADBLUE_MAX,       (U1)MCST_BFI_LEFT_ADBLUE,       (U1)HMIMCST_CSTM_CNT_LEFT_ADBLUE        },
        {(U2)8U,    (U1)3U,     (U1)28U,    (U1)MCST_HUD_ANALOG_MAX,        (U1)MCST_BFI_HUD_ANALOG,        (U1)HMIMCST_CSTM_CNT_HUD_ANALOG         },
        {(U2)9U,    (U1)2U,     (U1)0U,     (U1)MCST_FUEL_CO_HIS_MAX,       (U1)MCST_BFI_FUEL_CO_HIS,       (U1)HMIMCST_CSTM_CNT_FUEL_CO_HIS        },
        {(U2)9U,    (U1)2U,     (U1)2U,     (U1)MCST_ELE_CO_HIS_MAX,        (U1)MCST_BFI_ELE_CO_HIS,        (U1)HMIMCST_CSTM_CNT_ELE_CO_HIS         },
        {(U2)9U,    (U1)3U,     (U1)4U,     (U1)MCST_FUEL_CO_GRH_MAX,       (U1)MCST_BFI_FUEL_CO_GRH,       (U1)HMIMCST_CSTM_CNT_FUEL_CO_GRH        },
        {(U2)9U,    (U1)2U,     (U1)8U,     (U1)MCST_ELE_CO_GRH_MAX,        (U1)MCST_BFI_ELE_CO_GRH,        (U1)U1_MAX                              },
        {(U2)9U,    (U1)2U,     (U1)10U,    (U1)MCST_LEFT_TPMS_MAX,         (U1)MCST_BFI_LEFT_TPMS,         (U1)HMIMCST_CSTM_CNT_LEFT_TPMS          },
        {(U2)9U,    (U1)2U,     (U1)12U,    (U1)MCST_LEFT_OILLVL_MAX,       (U1)MCST_BFI_LEFT_OILLVL,       (U1)U1_MAX                              },
        {(U2)9U,    (U1)2U,     (U1)16U,    (U1)MCST_LEFT_FU_ECO_PHV_MAX,   (U1)MCST_BFI_LEFT_FU_ECO_PHV,   (U1)HMIMCST_CSTM_CNT_LEFT_FU_ECO_PHV    },
        {(U2)9U,    (U1)2U,     (U1)20U,    (U1)MCST_WDG_OFR_MAX,           (U1)MCST_BFI_WDG_OFR,           (U1)U1_MAX                              }
    };

    static const ST_HMIMCST_READDATA st_sp_HMIMCST_SPI_HMIMCST[] = {
        /* u2_lcomid,  u1_length,  u1_bitpos,  u1_max,    u1_mcstid,                 u1_cntid                           */
           {(U2)0U,    (U1)2U,    (U1)26U,     (U1)1U,    (U1)HMIMCST_CSTM_HUDRTCW  ,(U1)HMIMCST_SW_CNT_IDX_HUD_ROT_CW  },
           {(U2)0U,    (U1)2U,    (U1)28U,     (U1)1U,    (U1)HMIMCST_CSTM_HUDRTCCW ,(U1)HMIMCST_SW_CNT_IDX_HUD_ROT_CCW },
           {(U2)0U,    (U1)2U,    (U1)24U,     (U1)2U,    (U1)HMIMCST_CSTM_DIMSW    ,(U1)HMIMCST_SW_CNT_IDX_DIM         }
    };

    U1 u1_t_rxdata;
    U1 u1_t_mcstid;
    U1 u1_t_cntid;
    U1 u1_t_ptchk;
    U4 u4_t_cstmsize;
    U4 u4_t_hmimcstsize;
    U4 u4_t_loop;

    u4_t_cstmsize    = (U4)sizeof(st_sp_HMIMCST_SPI_METCSTMZ) / (U4)sizeof(st_sp_HMIMCST_SPI_METCSTMZ[0]);
    u4_t_hmimcstsize = (U4)sizeof(st_sp_HMIMCST_SPI_HMIMCST) / (U4)sizeof(st_sp_HMIMCST_SPI_HMIMCST[0]);

    /*customize(Mcst)*/
    for(u4_t_loop = (U4)0U; u4_t_loop < u4_t_cstmsize; u4_t_loop++){
        u1_t_rxdata = u1_HMIMCST_READ__BIT(u4_ap_PDU_RX[st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u2_lcomid]
            , st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u1_bitpos
            , st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u1_length);
        u1_t_mcstid = st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u1_mcstid;
        u1_t_cntid = st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u1_cntid;

        u1_t_ptchk = u1_s_HmimcstCstmPtChk(u1_t_mcstid, u1_t_rxdata);

        if((u1_t_rxdata <= st_sp_HMIMCST_SPI_METCSTMZ[u4_t_loop].u1_max) &&
           (u1_t_ptchk == (U1)TRUE                                     )){
            vd_g_McstBfPut(u1_t_mcstid, u1_t_rxdata);
        }

        if(u1_t_cntid < (U1)HMIMCST_CSTM_CNT_NUM){
            u1_sp_hmimcst_cstm_cnt[u1_t_cntid] = u1_t_rxdata;
        }

        if(u1_t_mcstid == (U1)MCST_BFI_METWRNCSTM){
            u1_s_hmimcst_mwvc_ope = u1_t_rxdata;
        }
    }

    /*customize(Hmimcst)*/
    for(u4_t_loop = (U4)0U; u4_t_loop < u4_t_hmimcstsize; u4_t_loop++){
        u1_t_rxdata = u1_HMIMCST_READ__BIT(u4_ap_PDU_RX[st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u2_lcomid]
            , st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u1_bitpos
            , st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u1_length);
        u1_t_cntid = st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u1_cntid;

        if(u1_t_rxdata <= st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u1_max){
            vd_g_HmiMcstPut(st_sp_HMIMCST_SPI_HMIMCST[u4_t_loop].u1_mcstid, u1_t_rxdata);
        }
        if(u1_t_cntid < (U1)HMIMCST_SW_CNT_NUM){
            u1_sp_hmimcst_sw_cnt[u1_t_cntid] = u1_t_rxdata;
        }
    }

    /*reset*/
    u1_t_rxdata = u1_HMIMCST_READ__BIT(u4_ap_PDU_RX[3], (U1)22U, (U1)2U);
    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_hmimcst_reset_req_pre)){
        (void)u1_g_McstReset((U1)TRUE);
        vd_s_HmiMcstSWCount((U2)RIMID_U2_DS_22_10A7_FACT_INIT);
    }
    u1_s_hmimcst_reset_req_pre = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static U1    u1_s_HmiCstmPutCheck(const U1 u1_a_ID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_ID                                                                                                 */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_HmimcstCstmPtChk(const U1 u1_a_ID, const U1 u1_a_RDATA)
{
    U1 u1_t_result;

    u1_t_result = (U1)TRUE;

    if((u1_a_ID == (U1)MCST_BFI_HUD   ) ||
       (u1_a_ID == (U1)MCST_BFI_HUD_ST)){
        u1_t_result = u1_s_HmimcstHudChk();
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTftcnttsPut(const U4 * u4_ap_PDU_RX)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 * u4_ap_PDU_RX                                                                                          */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTftcnttsPut(const U4 * u4_ap_PDU_RX)
{
    static const ST_HMITFTCNTTS_READDATA st_sp_TFTCNTTS_SPI_CNTTS[] = {
         /* u2_lcomid, u4_mask,          u1_bitpos,  u4_max,            u1_mcstid                       */
           {(U2)7U,    (U4)0x0000003FU,  (U1) 0U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_EYE0          },
           {(U2)7U,    (U4)0x0000003FU,  (U1) 6U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_EYE1          },
           {(U2)7U,    (U4)0x0000003FU,  (U1)12U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_EYE2          },
           {(U2)7U,    (U4)0x0000003FU,  (U1)18U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_MAP           },
           {(U2)7U,    (U4)0x0000003FU,  (U1)24U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_ADAS          },
           {(U2)8U,    (U4)0x0000003FU,  (U1) 0U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_ECO           },
           {(U2)8U,    (U4)0x0000003FU,  (U1) 6U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_TRACK         },
           {(U2)8U,    (U4)0x0000003FU,  (U1)12U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_SHIFT         },
           {(U2)8U,    (U4)0x0000003FU,  (U1)18U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_OFFROAD       },
           {(U2)8U,    (U4)0x0000003FU,  (U1)24U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_EYE6          },
           {(U2)9U,    (U4)0x0000000FU,  (U1) 0U,    (U4)0x00000009U,   (U1)MCST_BFI_DISP_VIEW          },
           {(U2)9U,    (U4)0x0000003FU,  (U1)24U,    (U4)0x00000026U,   (U1)MCST_BFI_DISP_CHARGEMODE    }
    };

    U4  u4_t_rxdata;
    U4  u4_t_contsize;
    U4  u4_t_loop;
    U1  u1_t_special_mode;

    u4_t_contsize = (U4)sizeof(st_sp_TFTCNTTS_SPI_CNTTS) / (U4)sizeof(st_sp_TFTCNTTS_SPI_CNTTS[0]);
    u1_t_special_mode = (U1)FALSE;

    for(u4_t_loop = (U4)0U; u4_t_loop < u4_t_contsize; u4_t_loop++){
        u4_t_rxdata = ((U4)(u4_ap_PDU_RX[st_sp_TFTCNTTS_SPI_CNTTS[u4_t_loop].u2_lcomid]
            >> st_sp_TFTCNTTS_SPI_CNTTS[u4_t_loop].u1_bitpos)
            &  st_sp_TFTCNTTS_SPI_CNTTS[u4_t_loop].u4_mask);
        if(u4_t_rxdata <= st_sp_TFTCNTTS_SPI_CNTTS[u4_t_loop].u4_max){
            vd_g_McstBfPutU4(st_sp_TFTCNTTS_SPI_CNTTS[u4_t_loop].u1_mcstid, u4_t_rxdata);
        }
    }

    u1_t_special_mode = (U1)(u4_ap_PDU_RX[1] & (U4)HMIMCST_CSTM_CHGMD_MASK);
    if(u1_t_special_mode <= (U1)HMIMCST_CSTM_CHGMD_ON){
        u1_s_hmimcst_chg_md_on = u1_t_special_mode;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstPut(const U1 u1_a_ID, const U1 u1_a_SIG)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_ID   :  recieve signal id                                                                                   */
/*                  u1_a_SIG  :  recieve signal value                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstPut(const U1 u1_a_ID, const U1 u1_a_SIG)
{
    U4 u4_t_loop;   /* loop counter */

    u2_s_hmimcst_to = (U2)HMIPROXY_TOC_INI;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_ID_NUM ; u4_t_loop++){
        if (u4_t_loop == (U4)u1_a_ID) {
            u1_sp_hmimcst_sigdata[u4_t_loop] = u1_a_SIG;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser1Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstUser1Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {

        for(u4_t_loop = (U4)HMIMCST_USERBUF_FSTDAT ; u4_t_loop < (U4)HMIMCST_USER_DTA_NUM ; u4_t_loop++){
            u4_sp_hmimcst_user1dat_buf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser2Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstUser2Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {

        for(u4_t_loop = (U4)HMIMCST_USERBUF_FSTDAT ; u4_t_loop < (U4)HMIMCST_USER_DTA_NUM ; u4_t_loop++){
            u4_sp_hmimcst_user2dat_buf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser3Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstUser3Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {

        for(u4_t_loop = (U4)HMIMCST_USERBUF_FSTDAT ; u4_t_loop < (U4)HMIMCST_USER_DTA_NUM ; u4_t_loop++){
            u4_sp_hmimcst_user3dat_buf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstSetUserName(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstSetUserName(void)
{
    U4          u4_t_user_updtnum;

    u4_t_user_updtnum = (U4)0U;

    u4_t_user_updtnum = (u4_sp_hmimcst_user1dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_user1_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_user1dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER1);
            u4_s_hmimcst_user1_updatenum_old = u4_t_user_updtnum;
        }
    }

    u4_t_user_updtnum = (u4_sp_hmimcst_user2dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_user2_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_user2dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER2);
            u4_s_hmimcst_user2_updatenum_old = u4_t_user_updtnum;
        }
    }

    u4_t_user_updtnum = (u4_sp_hmimcst_user3dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_user3_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_user3dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER3);
            u4_s_hmimcst_user3_updatenum_old = u4_t_user_updtnum;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstMMUserPut(const U2 * u2_ap_USRDAT,const U1 u1_a_SYNCID, const U1 u1_a_USRNUM)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstMMUserPut(const U2 * u2_ap_USRDAT,const U1 u1_a_SYNCID, const U1 u1_a_USRNUM)
{
    U4      u4_t_loop;    /* loop counter */
    U4 *    u4_tp_datbuf;
    U4      u4_t_idx_lo;
    U4      u4_t_idx_hi;
    U4      u4_t_txt_lo;
    U4      u4_t_txt_hi;

    if(u1_a_USRNUM == (U1)MCST_USR_USER1){
        u4_tp_datbuf = &u4_sp_hmimcst_mm_user1dat_buf[HMIMCST_USERBUF_FSTDAT];
    }
    else if(u1_a_USRNUM == (U1)MCST_USR_USER2){
        u4_tp_datbuf = &u4_sp_hmimcst_mm_user2dat_buf[HMIMCST_USERBUF_FSTDAT];
    }
    else if(u1_a_USRNUM == (U1)MCST_USR_USER3){
        u4_tp_datbuf = &u4_sp_hmimcst_mm_user3dat_buf[HMIMCST_USERBUF_FSTDAT];
    }
    else{
        u4_tp_datbuf = vdp_PTR_NA;
    }

    if(u4_tp_datbuf != vdp_PTR_NA) {
        /* Set updatenum in first index */
        u4_tp_datbuf[HMIMCST_USERBUF_FSTDAT] = (U4)u1_a_SYNCID;
        /* Convert U2 to U4             */
        for(u4_t_loop = (U4)HMIMCST_USERBUF_TXTDAT; u4_t_loop < (U4)HMIMCST_USER_DTA_NUM; u4_t_loop++){

            u4_t_idx_lo = (u4_t_loop - (U4)HMIMCST_CAL_ONE) * (U4)HMIMCST_CAL_TWO;
            u4_t_idx_hi = ((u4_t_loop - (U4)HMIMCST_CAL_ONE) * (U4)HMIMCST_CAL_TWO) + (U4)HMIMCST_CAL_ONE;
            u4_t_txt_lo = (U4)u2_ap_USRDAT[u4_t_idx_lo];
            u4_t_txt_hi = (U4)u2_ap_USRDAT[u4_t_idx_hi];

            u4_tp_datbuf[u4_t_loop]  = u4_t_txt_lo;
            u4_tp_datbuf[u4_t_loop] |= u4_t_txt_hi << HMIMCST_MM_USRNAME_LSB;
        }
    }
}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstSetMMUserName(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstSetMMUserName(void)
{
    U4          u4_t_user_updtnum;

    u4_t_user_updtnum = (U4)0U;

    u4_t_user_updtnum = (u4_sp_hmimcst_mm_user1dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_mm_user1_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_mm_user1dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER1);
            u4_s_hmimcst_mm_user1_updatenum_old = u4_t_user_updtnum;
        }
    }

    u4_t_user_updtnum = (u4_sp_hmimcst_mm_user2dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_mm_user2_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_mm_user2dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER2);
            u4_s_hmimcst_mm_user2_updatenum_old = u4_t_user_updtnum;
        }
    }

    u4_t_user_updtnum = (u4_sp_hmimcst_mm_user3dat_buf[HMIMCST_USERBUF_FSTDAT] & (U4)HMIMCST_USRNAME_NUM_MASK);
    if(u4_t_user_updtnum !=  u4_s_hmimcst_mm_user3_updatenum_old){
        if((u4_t_user_updtnum >= (U4)HMIMCST_UPDATENUM_MIN) &&
           (u4_t_user_updtnum <= (U4)HMIMCST_UPDATENUM_MAX)   ){
            vd_g_McstUsrNamePut(&u4_sp_hmimcst_mm_user3dat_buf[HMIMCST_USERBUF_FSTDAT], (U1)MCST_USR_USER3);
            u4_s_hmimcst_mm_user3_updatenum_old = u4_t_user_updtnum;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser1Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstNickname1Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)HMIMCST_NICKNAME_U4_FSTDAT ; u4_t_loop < (U4)HMIMCST_NICKNAME_U4_DTA_NUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMIMCST_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMIMCST_CAL_TWO) + (U4)HMIMCST_CAL_ONE;

            u2_t_txt_lo                                     = (U2)(u4_ap_REQ[u4_t_loop]
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname1dat_buf[u4_t_idx_lo]     = u2_t_txt_lo;

            u2_t_txt_hi                                     = (U2)((u4_ap_REQ[u4_t_loop] >> HMIMCST_NICKNAME_LSB)
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname1dat_buf[u4_t_idx_hi]     = u2_t_txt_hi;

        }
    }
}


/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser2Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstNickname2Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)HMIMCST_NICKNAME_U4_FSTDAT ; u4_t_loop < (U4)HMIMCST_NICKNAME_U4_DTA_NUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMIMCST_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMIMCST_CAL_TWO) + (U4)HMIMCST_CAL_ONE;

            u2_t_txt_lo                                     = (U2)(u4_ap_REQ[u4_t_loop]
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname2dat_buf[u4_t_idx_lo]     = u2_t_txt_lo;

            u2_t_txt_hi                                     = (U2)((u4_ap_REQ[u4_t_loop] >> HMIMCST_NICKNAME_LSB)
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname2dat_buf[u4_t_idx_hi]     = u2_t_txt_hi;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiMcstUser3Put(const U4 * u4_ap_REQ)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : User name address                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstNickname3Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)HMIMCST_NICKNAME_U4_FSTDAT ; u4_t_loop < (U4)HMIMCST_NICKNAME_U4_DTA_NUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMIMCST_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMIMCST_CAL_TWO) + (U4)HMIMCST_CAL_ONE;

            u2_t_txt_lo                                     = (U2)(u4_ap_REQ[u4_t_loop]
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname3dat_buf[u4_t_idx_lo]     = u2_t_txt_lo;

            u2_t_txt_hi                                     = (U2)((u4_ap_REQ[u4_t_loop] >> HMIMCST_NICKNAME_LSB)
                                                              & (U2)HMIMCST_NICKNAME_NUM_MASK);
            u2_sp_hmimcst_nickname3dat_buf[u4_t_idx_hi]     = u2_t_txt_hi;
        }
    }
}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstSetUserName(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstSetNickName(void)
{
    U4 u4_t_loop;    /* loop counter */
    U2 u2_tp_nickname1[HMIMCST_NICKNAME_U2_DTA_NUM];
    U2 u2_tp_nickname2[HMIMCST_NICKNAME_U2_DTA_NUM];
    U2 u2_tp_nickname3[HMIMCST_NICKNAME_U2_DTA_NUM];

    (void)u1_g_McstReadNickName(&u2_tp_nickname1[HMIMCST_NICKNAME_U2_FSTDAT],(U1)MCST_USR_USER1);
    (void)u1_g_McstReadNickName(&u2_tp_nickname2[HMIMCST_NICKNAME_U2_FSTDAT],(U1)MCST_USR_USER2);
    (void)u1_g_McstReadNickName(&u2_tp_nickname3[HMIMCST_NICKNAME_U2_FSTDAT],(U1)MCST_USR_USER3);

    for(u4_t_loop = (U4)HMIMCST_NICKNAME_U2_FSTDAT ; u4_t_loop < (U4)HMIMCST_NICKNAME_U2_DTA_NUM ; u4_t_loop++){
        if(u2_sp_hmimcst_nickname1dat_buf[u4_t_loop] < (U2)HMIMCST_NICKNAME_TXT_MAX){
            u2_tp_nickname1[u4_t_loop] = u2_sp_hmimcst_nickname1dat_buf[u4_t_loop];
        }
        if(u2_sp_hmimcst_nickname2dat_buf[u4_t_loop] < (U2)HMIMCST_NICKNAME_TXT_MAX){
            u2_tp_nickname2[u4_t_loop] = u2_sp_hmimcst_nickname2dat_buf[u4_t_loop];
        }
        if(u2_sp_hmimcst_nickname3dat_buf[u4_t_loop] < (U2)HMIMCST_NICKNAME_TXT_MAX){
            u2_tp_nickname3[u4_t_loop] = u2_sp_hmimcst_nickname3dat_buf[u4_t_loop];
        }
    }

    vd_g_McstNickNamePut(&u2_tp_nickname1[HMIMCST_NICKNAME_U2_FSTDAT], (U1)MCST_USR_USER1);
    vd_g_McstNickNamePut(&u2_tp_nickname2[HMIMCST_NICKNAME_U2_FSTDAT], (U1)MCST_USR_USER2);
    vd_g_McstNickNamePut(&u2_tp_nickname3[HMIMCST_NICKNAME_U2_FSTDAT], (U1)MCST_USR_USER3);
}

/*===================================================================================================================================*/
/* U1    u1_g_HmiMcstJdgHUDFail(const U1 u1_a_NOW)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1        u1_g_HmiMcstJdgHUDFail(const U1 u1_a_NOW)
{
    U1      u1_t_return;
    U1      u1_t_gvif;

    u1_t_return = u1_a_NOW;
    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);

    if((u1_sp_hmimcst_sigdata[HMIMCST_GV_SYS_HW_ERR] == (U1)HMIMCST_HUD_STS_FAIL) ||
       (u1_sp_hmimcst_sigdata[HMIMCST_GVIF_LINKDOWN] == (U1)HMIMCST_HUD_STS_FAIL) ||
       (u1_t_gvif                                    == (U1)FALSE)){
        u1_t_return = (U1)HMIMCST_VAL_OFF;
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstSWCount(const U2 u2_a_RIMID)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstSWCount(const U2 u2_a_RIMID)
{

    U2  u2_t_count;
    U1  u1_t_sts;

    u2_t_count = (U2)0U;

    u1_t_sts = u1_g_Rim_ReadU2withStatus(u2_a_RIMID, &u2_t_count);

    if(((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) &&
       (u2_t_count                            <  (U2)U2_MAX            )){
        u2_t_count++;
        vd_g_Rim_WriteU2(u2_a_RIMID, u2_t_count);
    }

}

/*===================================================================================================================================*/
/* static void    vd_s_HmiMcstSWCountMgr(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiMcstSWCountMgr(void)
{
    static const ST_HMIMCST_SW_CNT st_sp_HMIMCST_CSTM_CNT[HMIMCST_CSTM_CNT_NUM] = {
        /* u1_max,                      u1_rimid                               */
        {(U1)MCST_HUD_MAX,              (U2)RIMID_U2_DS_22_10A7_HUD_ONOFF               },   /* HMIMCST_CSTM_CNT_HUD             */
        {(U1)MCST_HUD_ST_MAX,           (U2)RIMID_U2_DS_22_10A7_HUD_DSP                 },   /* HMIMCST_CSTM_CNT_HUD_ST          */
        {(U1)MCST_ECO_IND_MAX,          (U2)RIMID_U2_DS_22_10A7_IND_ECO                 },   /* HMIMCST_CSTM_CNT_ECO_IND         */
        {(U1)MCST_EV_IND_MAX,           (U2)RIMID_U2_DS_22_10A7_IND_EV                  },   /* HMIMCST_CSTM_CNT_EV_IND          */
        {(U1)MCST_REV_IND_MAX,          (U2)RIMID_U2_DS_22_10A7_IND_REVIND              },   /* HMIMCST_CSTM_CNT_REV_IND         */
        {(U1)MCST_REV_ST_MAX,           (U2)RIMID_U2_DS_22_10A7_IND_REVSET              },   /* HMIMCST_CSTM_CNT_REV_ST          */
        {(U1)MCST_REV_PK_MAX,           (U2)RIMID_U2_DS_22_10A7_IND_REVPEK              },   /* HMIMCST_CSTM_CNT_REV_PK          */
        {(U1)MCST_FUEL_CO_GRH_MAX,      (U2)RIMID_U2_DS_22_10A7_FUEL_FLG                },   /* HMIMCST_CSTM_CNT_FUEL_CO_GRH     */
        {(U1)MCST_DRVINF_UP_MAX,        (U2)RIMID_U2_DS_22_10A7_DRVINF_ITEM             },   /* HMIMCST_CSTM_CNT_DRVINF_UP       */
        {(U1)MCST_DRVINF_DN_MAX,        (U2)RIMID_U2_DS_22_10A7_DRVINF_ITEM             },   /* HMIMCST_CSTM_CNT_DRVINF_DN       */
        {(U1)MCST_CROSS_ADV_MAX,        (U2)RIMID_U2_DS_22_10A7_POP_CROSS               },   /* HMIMCST_CSTM_CNT_CROSS_ADV       */
        {(U1)MCST_TEL_MAX,              (U2)RIMID_U2_DS_22_10A7_POP_TEL                 },   /* HMIMCST_CSTM_CNT_TEL             */
        {(U1)MCST_AUDIO_OPE_MAX,        (U2)RIMID_U2_DS_22_10A7_POP_AUDIO               },   /* HMIMCST_CSTM_CNT_AUDIO_OPE       */
        {(U1)MCST_VOL_OPE_MAX,          (U2)RIMID_U2_DS_22_10A7_POP_VOLUME              },   /* HMIMCST_CSTM_CNT_VOL_OPE         */
        {(U1)MCST_VRCTRL_MAX,           (U2)RIMID_U2_DS_22_10A7_POP_VOICE               },   /* HMIMCST_CSTM_CNT_VRCTRL          */
        {(U1)MCST_ILLUMI_ADJ_MAX,       (U2)RIMID_U2_DS_22_10A7_POP_DIM                 },   /* HMIMCST_CSTM_CNT_ILLUMI_ADJ      */
        {(U1)MCST_HVIND_MAX,            (U2)RIMID_U2_DS_22_10A7_HV_IND                  },   /* HMIMCST_CSTM_CNT_HVIND           */
        {(U1)MCST_TRIP_A_UP_MAX,        (U2)RIMID_U2_DS_22_10A7_MET_TRIP_A              },   /* HMIMCST_CSTM_CNT_TRIP_A_UP       */
        {(U1)MCST_TRIP_A_DN_MAX,        (U2)RIMID_U2_DS_22_10A7_MET_TRIP_A              },   /* HMIMCST_CSTM_CNT_TRIP_A_DN       */
        {(U1)MCST_TRIP_B_UP_MAX,        (U2)RIMID_U2_DS_22_10A7_MET_TRIP_B              },   /* HMIMCST_CSTM_CNT_TRIP_B_UP       */
        {(U1)MCST_TRIP_B_DN_MAX,        (U2)RIMID_U2_DS_22_10A7_MET_TRIP_B              },   /* HMIMCST_CSTM_CNT_TRIP_B_DN       */
        {(U1)MCST_EV_DRINFO_MAX,        (U2)RIMID_U2_DS_22_10A7_EV_DRVINF               },   /* HMIMCST_CSTM_CNT_EV_DRINFO       */
        {(U1)MCST_HUD_ANALOG_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_HUD_MET            },   /* HMIMCST_CSTM_CNT_HUD_ANALOG      */
        {(U1)MCST_VIEW_EYE0_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_0DIAL          },   /* HMIMCST_CSTM_CNT_VIEW_EYE0       */
        {(U1)MCST_WDG_EYE0_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_MET_0DIALWDG       },   /* HMIMCST_CSTM_CNT_WDG_EYE0        */
        {(U1)MCST_VIEW_EYE1_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_1DIAL          },   /* HMIMCST_CSTM_CNT_VIEW_EYE1       */
        {(U1)MCST_ANALOG_EYE1_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_ANLG_CHG_1DIAL     },   /* HMIMCST_CSTM_CNT_ANALOG_EYE1     */
        {(U1)MCST_WDG_EYE1_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_MET_1DIALWDG       },   /* HMIMCST_CSTM_CNT_WDG_EYE1        */
        {(U1)MCST_VIEW_EYE2_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_2DIAL          },   /* HMIMCST_CSTM_CNT_VIEW_EYE2       */
        {(U1)MCST_ANALOG_EYE2_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_ANLG_CHG_2DIAL     },   /* HMIMCST_CSTM_CNT_ANALOG_EYE2     */
        {(U1)MCST_VIEW_NAVI_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_MAP            },   /* HMIMCST_CSTM_CNT_VIEW_NAVI       */
        {(U1)MCST_WDG_NAVI_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_MET_MAPWDG         },   /* HMIMCST_CSTM_CNT_WDG_NAVI        */
        {(U1)MCST_VIEW_ADAS_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_ADAS           },   /* HMIMCST_CSTM_CNT_VIEW_ADAS       */
        {(U1)MCST_WDG_ADAS_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_MET_ADASWDG        },   /* HMIMCST_CSTM_CNT_WDG_ADAS        */
        {(U1)MCST_VIEW_ECO_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_MET_ECO            },   /* HMIMCST_CSTM_CNT_VIEW_ECO        */
        {(U1)MCST_WDG_ECO_MAX,          (U2)RIMID_U2_DS_22_10B2_CSTM_MET_ECOWDG         },   /* HMIMCST_CSTM_CNT_WDG_ECO         */
        {(U1)MCST_VIEW_TRACK_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_MET_1DIALTRACK     },   /* HMIMCST_CSTM_CNT_VIEW_TRACK      */
        {(U1)MCST_VIEW_SHIFT_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_MET_SHIFTUPIND     },   /* HMIMCST_CSTM_CNT_VIEW_SHIFT      */
        {(U1)MCST_VIEW_OFFROAD_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_MET_OFFROAD        },   /* HMIMCST_CSTM_CNT_VIEW_OFFROAD    */
        {(U1)MCST_VIEW_EYE6_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_MET_6DIAL          },   /* HMIMCST_CSTM_CNT_VIEW_EYE6       */
        {(U1)MCST_FUEL_CO_HIS_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_FE_GRPH            },   /* HMIMCST_CSTM_CNT_FUEL_CO_HIS     */
        {(U1)MCST_ELE_CO_HIS_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_EE_GRPH            },   /* HMIMCST_CSTM_CNT_ELE_CO_HIS      */
        {(U1)MCST_LEFT_FU_ECO_NP_MAX,   (U2)RIMID_U2_DS_22_10B2_CSTM_INF_FE_GRPH        },   /* HMIMCST_CSTM_CNT_LEFT_FU_ECO_NP  */
        {(U1)MCST_LEFT_FU_ECO_PHV_MAX,  (U2)RIMID_U2_DS_22_10B2_CSTM_INF_FE_GRPH        },   /* HMIMCST_CSTM_CNT_LEFT_FU_ECO_PHV */
        {(U1)MCST_LEFT_EL_ECO_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ELEC           },   /* HMIMCST_CSTM_CNT_LEFT_EL_ECO     */
        {(U1)MCST_LEFT_CONSUMP_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_INF_CONSUMP        },   /* HMIMCST_CSTM_CNT_LEFT_CONSUMP    */
        {(U1)MCST_LEFT_ECO_IND_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ECOIND         },   /* HMIMCST_CSTM_CNT_LEFT_ECO_IND    */
        {(U1)MCST_LEFT_ECO_JDG_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ECOJDG         },   /* HMIMCST_CSTM_CNT_LEFT_ECO_JDG    */
        {(U1)MCST_LEFT_EV_RATIO_MAX,    (U2)RIMID_U2_DS_22_10B2_CSTM_INF_EV             },   /* HMIMCST_CSTM_CNT_LEFT_EV_RATIO   */
        {(U1)MCST_LEFT_NAVI_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_INF_NAVI           },   /* HMIMCST_CSTM_CNT_LEFT_NAVI       */
        {(U1)MCST_LEFT_AUDIO_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_AUDIO          },   /* HMIMCST_CSTM_CNT_LEFT_AUDIO      */
        {(U1)MCST_LEFT_DRV_INFO_MAX,    (U2)RIMID_U2_DS_22_10B2_CSTM_INF_DRVINFO        },   /* HMIMCST_CSTM_CNT_LEFT_DRV_INFO   */
        {(U1)MCST_LEFT_TRIP_A_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_TRIPA          },   /* HMIMCST_CSTM_CNT_LEFT_TRIP_A     */
        {(U1)MCST_LEFT_TRIP_B_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_TRIPB          },   /* HMIMCST_CSTM_CNT_LEFT_TRIP_B     */
        {(U1)MCST_LEFT_ENE_MON_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ENERGY         },   /* HMIMCST_CSTM_CNT_LEFT_ENE_MON    */
        {(U1)MCST_LEFT_TPMS_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_INF_TPMS           },   /* HMIMCST_CSTM_CNT_LEFT_TPMS       */
        {(U1)MCST_LEFT_4WD_MAX,         (U2)RIMID_U2_DS_22_10B2_CSTM_INF_4WD_AWD        },   /* HMIMCST_CSTM_CNT_LEFT_4WD        */
        {(U1)MCST_LEFT_TRAC_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_INF_TRACTION       },   /* HMIMCST_CSTM_CNT_LEFT_TRAC       */
        {(U1)MCST_LEFT_ANGEL_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ANGEL          },   /* HMIMCST_CSTM_CNT_LEFT_ANGEL      */
        {(U1)MCST_LEFT_PITCH_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_PITCH_ROLL     },   /* HMIMCST_CSTM_CNT_LEFT_PITCH      */
        {(U1)MCST_LEFT_TR_BRAKE_MAX,    (U2)RIMID_U2_DS_22_10B2_CSTM_INF_BRAKE          },   /* HMIMCST_CSTM_CNT_LEFT_TR_BRAKE   */
        {(U1)MCST_LEFT_TR_BSM_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_BSM            },   /* HMIMCST_CSTM_CNT_LEFT_TR_BSM     */
        {(U1)MCST_LEFT_VOLT_MAX,        (U2)RIMID_U2_DS_22_10B2_CSTM_INF_VOLT           },   /* HMIMCST_CSTM_CNT_LEFT_VOLT       */
        {(U1)MCST_LEFT_OIL_VOLT_MAX,    (U2)RIMID_U2_DS_22_10B2_CSTM_INF_OIL_VOLT       },   /* HMIMCST_CSTM_CNT_LEFT_OIL_VOLT   */
        {(U1)MCST_LEFT_ENG_AT_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ENGINE_AT      },   /* HMIMCST_CSTM_CNT_LEFT_ENG_AT     */
        {(U1)MCST_LEFT_ENGINE_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ENGINE         },   /* HMIMCST_CSTM_CNT_LEFT_ENGINE     */
        {(U1)MCST_LEFT_AT_MAX,          (U2)RIMID_U2_DS_22_10B2_CSTM_INF_AT             },   /* HMIMCST_CSTM_CNT_LEFT_AT         */
        {(U1)MCST_LEFT_TURBO_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_TURBO          },   /* HMIMCST_CSTM_CNT_LEFT_TURBO      */
        {(U1)MCST_LEFT_BOOST_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_BOOST          },   /* HMIMCST_CSTM_CNT_LEFT_BOOST      */
        {(U1)MCST_LEFT_MOTOR_MAX,       (U2)RIMID_U2_DS_22_10B2_CSTM_INF_MOTOR          },   /* HMIMCST_CSTM_CNT_LEFT_MOTOR      */
        {(U1)MCST_LEFT_SPORTS_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_SPORTS         },   /* HMIMCST_CSTM_CNT_LEFT_SPORTS     */
        {(U1)MCST_LEFT_G_FORCE_MAX,     (U2)RIMID_U2_DS_22_10B2_CSTM_INF_GFORCE         },   /* HMIMCST_CSTM_CNT_LEFT_G_FORCE    */
        {(U1)MCST_LEFT_ADBLUE_MAX,      (U2)RIMID_U2_DS_22_10B2_CSTM_INF_ADBLUE         }    /* HMIMCST_CSTM_CNT_LEFT_ADBLUE     */
    };

    static const ST_HMIMCST_SW_CNT st_sp_HMIMCST_SW_CNT[HMIMCST_SW_CNT_NUM] = {
        /* u1_max,                         u1_rimid                               */
        {(U1)HMIMCST_SW_CNT_HUD_ROT_MAX,   (U2)RIMID_U2_DS_22_10A7_HUD_ROT    },
        {(U1)HMIMCST_SW_CNT_HUD_ROT_MAX,   (U2)RIMID_U2_DS_22_10A7_HUD_ROT    },
        {(U1)HMIMCST_SW_CNT_DIM_MAX,       (U2)RIMID_U2_DS_22_10A7_MET_DIM    }
    };

    U1  u1_t_max;
    U2  u2_t_rimid;
    U4  u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_CSTM_CNT_NUM ; u4_t_loop++){
        u1_t_max   = st_sp_HMIMCST_CSTM_CNT[u4_t_loop].u1_max;
        u2_t_rimid = st_sp_HMIMCST_CSTM_CNT[u4_t_loop].u2_rimid;
        if((u1_sp_hmimcst_pre_val_cstm_cnt[u4_t_loop] != u1_sp_hmimcst_cstm_cnt[u4_t_loop]) &&
           (u1_sp_hmimcst_cstm_cnt[u4_t_loop]         != (U1)HMIMCST_CSTM_CNT_NO_OPE      ) &&
           (u1_sp_hmimcst_cstm_cnt[u4_t_loop]         <= u1_t_max                        )){
            vd_s_HmiMcstSWCount(u2_t_rimid);
        }
        u1_sp_hmimcst_pre_val_cstm_cnt[u4_t_loop] = u1_sp_hmimcst_cstm_cnt[u4_t_loop];
    }

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMCST_SW_CNT_NUM ; u4_t_loop++){
        u1_t_max   = st_sp_HMIMCST_SW_CNT[u4_t_loop].u1_max;
        u2_t_rimid = st_sp_HMIMCST_SW_CNT[u4_t_loop].u2_rimid;
        if((u1_sp_hmimcst_pre_val_sw_cnt[u4_t_loop] != u1_sp_hmimcst_sw_cnt[u4_t_loop]    ) &&
           (u1_sp_hmimcst_sw_cnt[u4_t_loop]         != (U1)HMIMCST_SW_CNT_NO_OPE          ) &&
           (u1_sp_hmimcst_sw_cnt[u4_t_loop]         <= u1_t_max                          )){
            vd_s_HmiMcstSWCount(u2_t_rimid);
        }
        u1_sp_hmimcst_pre_val_sw_cnt[u4_t_loop] = u1_sp_hmimcst_sw_cnt[u4_t_loop];

    }

}

/*===================================================================================================================================*/
/* void    vd_g_HmiMcstRefHook(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMcstRefHook(void)
{

    s1_s_hmimcst_hud_rot     = (S1)u1_g_McstBf((U1)MCST_BFI_HUD_ROT);
    s1_s_hmimcst_hud_rot_pre = s1_s_hmimcst_hud_rot;

}

/*===================================================================================================================================*/
/*  static U1    u1_s_HmimcstHudChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_ID                                                                                                 */
/*                                                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_HmimcstHudChk(void)
{
    U1 u1_t_result;
    U1 u1_t_gvif;

    u1_t_result = (U1)TRUE;
    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);

    if((u1_sp_hmimcst_sigdata[HMIMCST_GV_SYS_HW_ERR] == (U1)HMIMCST_HUD_STS_FAIL) ||
       (u1_sp_hmimcst_sigdata[HMIMCST_GVIF_LINKDOWN] == (U1)HMIMCST_HUD_STS_FAIL) ||
       (u1_t_gvif                                    == (U1)FALSE               )){
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* U1    u1_g_HmiMcstGetMWVCOpe(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_HmiMcstGetMWVCOpe(void)
{
    return(u1_s_hmimcst_mwvc_ope);
}

/*===================================================================================================================================*/
/*  static inline U1    u1_s_HmimcstCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MIN                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1    u1_s_HmimcstCalibU1MinChk(const U1 u1_a_CALIBID, const U1 u1_a_MIN, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret < u1_a_MIN){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1    u1_g_HmiMcstGetChargeMode(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_hmimcst_chg_md_on                                                                                           */
/*===================================================================================================================================*/
U1    u1_g_HmiMcstGetChargeMode(void)
{
    return(u1_s_hmimcst_chg_md_on);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2017  TA       New.                                                                                               */
/*  1.1.0    04/21/2020  TH       Setting for 800B CV.                                                                               */
/*  2.0.0    10/06/2020  TM       Re-designed.                                                                                       */
/*  2.1.0     1/13/2021  TM       Setting for 800B 1A.                                                                               */
/*  2.2.0     4/23/2021  TM       Fixed METHUD800B-16508 and METHUD800B-16509.                                                       */
/*  2.3.0    11/16/2021  SI       Setting for 22-24FGM 1A                                                                            */
/*  2.4.0    09/23/2022  TX       Add Trailer Setting                                                                                */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 12/27/2023  SI       Correspond to MET-M_MWVCUS-                                                                        */
/*  19PFv3-2 03/15/2024  SN       Add HudOnOff hard sw                                                                               */
/*  19PFv3-3 04/04/2024  KH       Delete VRCTRL function                                                                             */
/*  19PFv3-4 04/25/2024  SW       Change parameter of st_sp_TFTCNTTS_SPI_CNTTS for G_T_SCREEN                                        */
/*  19PFv3-5 07/01/2024  SN       Change function arguments                                                                          */
/*  19PFv3-5 07/03/2024  SN       Change MCST_BFI_REV_ST Max Value                                                                   */
/*  19PFv3-7 07/12/2024  SW       Add parameter for MCST_BFP_DISP_CHARGEMODE                                                         */
/*                                Change Max Value of MCST_BFI_DISP_EYE0/EYE1/MAP/ADAS                                               */
/*                                Add process for don't save IG-ON ChargeMode                                                        */
/*  19PFv3-8 08/26/2024  SW       Add parameter for MCST_BFI_LEFT_FU_ECO_PHV                                                         */
/*  19PFv3-9 09/24/2024  SI       Update Parameters for 10A7                                                                         */
/*                                Add Parameter for 10B2                                                                             */
/*  19PFv3-10 01/21/2025  SI      Add IF to provide ChargeMode for 10B3                                                              */
/*  19PFv3-11 03/26/2025  SI      Change logic to update u1_s_hmimcst_chg_md_on                                                      */
/*                                Delete u1_s_HmimcstViewSpModeChk                                                                   */
/*  19PFv3-12 04/24/2025  SW      Add parameter for MCST_BFI_WDG_OFR                                                                 */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * TM   = Takuya   Mitsui, Denso Techno                                                                                           */
/*  * SI   = Shugo  Ichinose, Denso Techno                                                                                           */
/*  * TX   = Tong Xinyuan   , DNST                                                                                                   */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
