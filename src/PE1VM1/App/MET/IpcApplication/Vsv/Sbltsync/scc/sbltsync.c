/* 2.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Synchronizer of Seatbelt WarningChime with Telltale                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTSYNC_C_MAJOR                         (2)
#define SBLTSYNC_C_MINOR                         (6)
#define SBLTSYNC_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sbltsync_cfg_private.h"
#include "memfill_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SBLTSYNC_C_MAJOR != SBLTSYNC_H_MAJOR) || \
     (SBLTSYNC_C_MINOR != SBLTSYNC_H_MINOR) || \
     (SBLTSYNC_C_PATCH != SBLTSYNC_H_PATCH))
#error "sbltsync.c and sbltsync.h : source and header files are inconsistent!"
#endif

#if ((SBLTSYNC_C_MAJOR != SBLTSYNC_CFG_H_MAJOR) || \
     (SBLTSYNC_C_MINOR != SBLTSYNC_CFG_H_MINOR) || \
     (SBLTSYNC_C_PATCH != SBLTSYNC_CFG_H_PATCH))
#error "sbltsync.c and sbltsync_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTSYNC_OUT_OFF                        (0U)
#define SBLTSYNC_OUT_PRD                        (1U)
#define SBLTSYNC_OUT_ON_TRM                     (2U)

#define SBLTSYNC_NUM_FRSEAT                     (SBLTWRN_NUM_COL)

#define SBLTSYNC_RTRG                           (0x60U)      /* Internal counter Retrigger bit */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4           u4_s_sbltsync_lgltm_elpsd;
static U4           u4_s_sbltsync_lv2tm_elpsd;
static U4           u4_s_sbltsync_lv1tm_elpsd;
static U2           u2_s_sbltsync_req_tt;
static U2           u2_s_sbltsync_chm_prev;
static U1           u1_s_sbltsync_act_tt;
static U1           u1_s_sbltsync_act_fr_tt;
static U1           u1_s_sbltsync_req_chm;
static U1           u1_s_sbltsync_lv2cmp_chm;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Sbltsync(void);
static void vd_s_Sbltsync_FM(void);
static U1   u1_s_SbltsyncTrgt(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS);
static U1   u1_s_SbltsyncTrgt_FM(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS);
static void vd_s_SbltsyncChk(U1 * u1_ap_sync_tt, U1 * u1_ap_sync_chm, const U1 u1_a_SYNCBIT);
static U1   u1_s_SbltsyncPeriodSts(const U4 u4_a_PRD, const U4 u4_a_CNG, const U4 u4_a_TM_ELPSD);
static void vd_s_SbltsyncChmReqUpdt(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT);
static void vd_s_SbltsyncChmReqUpdt_FM(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT);
static U1   u1_s_SbltsyncFrTtSts(void);
static U2   u2_s_SbltsyncChmSts(void);
static U2   u2_s_SbltsyncChmSts_FM(void);
static U1   u1_s_SbltsyncTtReqUpdt(const U1 u1_a_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req);
static U1   u1_s_SbltsyncTtReqUpdt_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req, const U1 u1_a_SEATID);
static U1   u1_s_SbltsyncRearTtChk_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 u1_a_SEATID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
    const ST_SBLTSYNC_PRM st_gp_SBLTSYNC_PRM[CALIB_MCUID0024_NUM][SBLTSYNC_NUM_KND] = {
            /* u4_sync_tt_prd               u4_sync_tt_cng               u4_sync_chm_prd              u4_sync_chm_cng */
    {
        {  (U4)(1200U / SBLTSYNC_TICK), (U4)( 600U / SBLTSYNC_TICK), (U4)(1200U / SBLTSYNC_TICK), (U4)( 600U / SBLTSYNC_TICK)  },
        {  (U4)( 400U / SBLTSYNC_TICK), (U4)( 200U / SBLTSYNC_TICK), (U4)( 400U / SBLTSYNC_TICK), (U4)( 200U / SBLTSYNC_TICK)  },
        {  (U4)(1200U / SBLTSYNC_TICK), (U4)( 600U / SBLTSYNC_TICK), (U4)(1200U / SBLTSYNC_TICK), (U4)( 600U / SBLTSYNC_TICK)  }
    },
    {
        {  (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK), (U4)(2000U / SBLTSYNC_TICK), (U4)(1000U / SBLTSYNC_TICK)  },
        {  (U4)( 360U / SBLTSYNC_TICK), (U4)( 180U / SBLTSYNC_TICK), (U4)(1440U / SBLTSYNC_TICK), (U4)( 720U / SBLTSYNC_TICK)  },
        {  (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK), (U4)(2000U / SBLTSYNC_TICK), (U4)(1000U / SBLTSYNC_TICK)  }
    },
    {
        {  (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK), (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK)  },
        {  (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK), (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK)  },
        {  (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK), (U4)(1000U / SBLTSYNC_TICK), (U4)( 500U / SBLTSYNC_TICK)  }
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void        vd_g_SbltsyncInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_SbltsyncInit(void)
{
    u4_s_sbltsync_lgltm_elpsd = (U4)U4_MAX;
    u4_s_sbltsync_lv2tm_elpsd = (U4)U4_MAX;
    u4_s_sbltsync_lv1tm_elpsd = (U4)U4_MAX;

    u2_s_sbltsync_req_tt      = (U2)0U;
    u1_s_sbltsync_act_tt      = (U1)FALSE;
    u1_s_sbltsync_act_fr_tt   = (U1)FALSE;
    u2_s_sbltsync_chm_prev    = (U2)0U;
    u1_s_sbltsync_req_chm     = (U1)0U;
    u1_s_sbltsync_lv2cmp_chm  = (U1)FALSE;

    vd_g_SbltsyncCfgInit();
}
/*===================================================================================================================================*/
/*  void        vd_g_SbltsyncMainTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_SbltsyncMainTask(void)
{
    U1              u1_t_dest_judge;

    u1_t_dest_judge = u1_g_SbltsyncCfgJdg_FM();
    if((U1)SBLTSYNC_DEST_OTHER_FM == u1_t_dest_judge) {
        vd_s_Sbltsync();
    } else {
        vd_s_Sbltsync_FM();
    }

    vd_g_SbltsyncCfgPostTask();
}
/*===================================================================================================================================*/
/* static void vd_s_Sbltsync(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Sbltsync(void)
{
    static  void  ( * const   fp_sp_u1_SBLTSYNC_CXPI[SBLTWRN_NUM_ALLSEAT])(const U1 u1_a_SIG) = {
        vdp_PTR_NA,                 vdp_PTR_NA,                 vdp_PTR_NA,
        &vd_g_SbltsyncCfgTxRLTT,    &vd_g_SbltsyncCfgTxRCTT,    &vd_g_SbltsyncCfgTxRRTT,
        &vd_g_SbltsyncCfgTxRL2TT,   &vd_g_SbltsyncCfgTxRC2TT,   &vd_g_SbltsyncCfgTxRR2TT,
        &vd_g_SbltsyncCfgTxRL3TT,   &vd_g_SbltsyncCfgTxRC3TT,   &vd_g_SbltsyncCfgTxRR3TT
    };

    U4              u4_t_lpcnt;
    U4              u4_t_tt_sts;
    U2              u2_t_chm_sts;
    U2              u2_t_tt_onoff;
    U2              u2_t_tt_req;
    U1              u1_tp_sync_tt[SBLTSYNC_NUM_KND];
    U1              u1_tp_sync_chm[SBLTSYNC_NUM_KND];
    U1              u1_t_syncbit;
    U1              u1_t_seat_sts;
    U1              u1_t_tt_act;
    U1              u1_t_txchg;

    vd_g_MemfillU1(u1_tp_sync_tt,  (U1)SBLTSYNC_OUT_OFF, (U4)SBLTSYNC_NUM_KND);
    vd_g_MemfillU1(u1_tp_sync_chm, (U1)SBLTSYNC_OUT_OFF, (U4)SBLTSYNC_NUM_KND);

    u4_t_tt_sts  = u4_g_SbltwrnTtSts();
    u2_t_chm_sts = u2_s_SbltsyncChmSts();
    u1_t_syncbit = u1_s_SbltsyncTrgt(u4_t_tt_sts, u2_t_chm_sts);
    vd_s_SbltsyncChk(&u1_tp_sync_tt[0], &u1_tp_sync_chm[0], u1_t_syncbit);

    vd_s_SbltsyncChmReqUpdt(&u1_tp_sync_chm[0], u2_t_chm_sts);

    u1_t_seat_sts = u1_s_SbltsyncFrTtSts();
    u2_t_tt_req   = (U2)FALSE;
    (void)u1_s_SbltsyncTtReqUpdt(u1_t_seat_sts, &u1_tp_sync_tt[0], &u2_t_tt_req);
    if((U2)FALSE != u2_t_tt_req){
        u2_t_tt_req = (U2)SBLTSYNC_TT_REQ_FR;
    }
    u1_t_tt_act   = (U1)FALSE;
    u1_t_txchg    = (U1)FALSE;
    for(u4_t_lpcnt = (U4)SBLTSYNC_NUM_FRSEAT; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++){
        u1_t_seat_sts = u1_g_SbltwrnTtStsBySeat((U1)u4_t_lpcnt);
        u1_t_tt_act  |= u1_s_SbltsyncTtReqUpdt(u1_t_seat_sts, &u1_tp_sync_tt[0], &u2_t_tt_onoff);
        u2_t_tt_req  |= (U2)(u2_t_tt_onoff << u4_t_lpcnt);
        if((fp_sp_u1_SBLTSYNC_CXPI[u4_t_lpcnt] != vdp_PTR_NA)
        && (((u2_t_tt_req ^ u2_s_sbltsync_req_tt) & ((U2)1U << u4_t_lpcnt)) != (U2)0U)){
            fp_sp_u1_SBLTSYNC_CXPI[u4_t_lpcnt]((U1)u2_t_tt_onoff);
            u1_t_txchg |= (U1)TRUE;
        }
    }
    if(u1_t_tt_act != u1_s_sbltsync_act_tt){
        vd_g_SbltsyncCfgTxREARINDI(u1_t_tt_act);
        u1_t_txchg |= (U1)TRUE;
    }
    if(u1_t_txchg == (U1)TRUE){
        vd_g_SbltsyncCfgTxCXMET1S02();
    }

    u2_s_sbltsync_req_tt = u2_t_tt_req;
    u1_s_sbltsync_act_tt = u1_t_tt_act;
}
/*===================================================================================================================================*/
/*  void        vd_s_Sbltsync_FM(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Sbltsync_FM(void)
{
    static  void  ( * const   fp_sp_u1_SBLTSYNC_CXPI[SBLTWRN_NUM_ALLSEAT])(const U1 u1_a_SIG) = {
        vdp_PTR_NA,                 vdp_PTR_NA,                 vdp_PTR_NA,
        &vd_g_SbltsyncCfgTxRLTT,    &vd_g_SbltsyncCfgTxRCTT,    &vd_g_SbltsyncCfgTxRRTT,
        &vd_g_SbltsyncCfgTxRL2TT,   &vd_g_SbltsyncCfgTxRC2TT,   &vd_g_SbltsyncCfgTxRR2TT,
        &vd_g_SbltsyncCfgTxRL3TT,   &vd_g_SbltsyncCfgTxRC3TT,   &vd_g_SbltsyncCfgTxRR3TT
    };

    U4              u4_t_lpcnt;
    U4              u4_t_tt_sts;
    U2              u2_t_chm_sts;
    U2              u2_t_tt_onoff;
    U2              u2_t_tt_req;
    U1              u1_tp_sync_tt[SBLTSYNC_NUM_KND];
    U1              u1_tp_sync_chm[SBLTSYNC_NUM_KND];
    U1              u1_t_syncbit;
    U1              u1_t_tt_act;
    U1              u1_t_tt_act_front;
    U1              u1_tp_all_seat_sts[SBLTWRN_NUM_ALLSEAT];
    U1              u1_t_tt_fr_act;
    U1              u1_t_tt_rr_act;
    U1              u1_t_tt_work_act;
    U1              u1_t_mid_typ;
    U1              u1_t_txchg;

    vd_g_MemfillU1(u1_tp_sync_tt,  (U1)SBLTSYNC_OUT_OFF, (U4)SBLTSYNC_NUM_KND);
    vd_g_MemfillU1(u1_tp_sync_chm, (U1)SBLTSYNC_OUT_OFF, (U4)SBLTSYNC_NUM_KND);

    u4_t_tt_sts  = u4_g_SbltwrnTtSts_FM();
    u2_t_chm_sts = u2_s_SbltsyncChmSts_FM();
    u1_t_syncbit = u1_s_SbltsyncTrgt_FM(u4_t_tt_sts, u2_t_chm_sts);
    vd_s_SbltsyncChk(&u1_tp_sync_tt[0], &u1_tp_sync_chm[0], u1_t_syncbit);

    vd_s_SbltsyncChmReqUpdt_FM(&u1_tp_sync_chm[0], u2_t_chm_sts);

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++){
        u1_tp_all_seat_sts[u4_t_lpcnt] = u1_g_SbltwrnTtStsBySeat_FM((U1)u4_t_lpcnt);
    }
    u2_t_tt_req       = (U2)FALSE;
    u1_t_tt_act       = (U1)FALSE;
    u1_t_tt_act_front = (U1)FALSE;
    u1_t_tt_fr_act    = (U1)FALSE;
    u1_t_tt_rr_act    = (U1)FALSE;
    u1_t_tt_work_act  = (U1)FALSE;
    u1_t_txchg        = (U1)FALSE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++){
        u1_t_tt_work_act = u1_s_SbltsyncTtReqUpdt_FM(&u1_tp_all_seat_sts[0], &u1_tp_sync_tt[0], &u2_t_tt_onoff, (U1)u4_t_lpcnt);
        u2_t_tt_req     |= (U2)(u2_t_tt_onoff << u4_t_lpcnt);
        if((U4)SBLTSYNC_NUM_FRSEAT > u4_t_lpcnt) {
            u1_t_tt_fr_act  |= u1_t_tt_work_act;
        } else {
            u1_t_tt_rr_act  |= u1_t_tt_work_act;
        }
        if((fp_sp_u1_SBLTSYNC_CXPI[u4_t_lpcnt] != vdp_PTR_NA)
        && (((u2_t_tt_req ^ u2_s_sbltsync_req_tt) & (U2)((U2)1U << u4_t_lpcnt)) != (U2)0U)){
            fp_sp_u1_SBLTSYNC_CXPI[u4_t_lpcnt]((U1)u2_t_tt_onoff);
            u1_t_txchg |= (U1)TRUE;
        }
    }

    u1_t_mid_typ = u1_g_SbltsyncCfgSelMidTyp_FM();
    switch(u1_t_mid_typ) {
        case (U1)SBLTSYNC_MIDTYP_D_P_REAR:
            u1_t_tt_act = (u1_t_tt_fr_act | u1_t_tt_rr_act);
            break;
        case (U1)SBLTSYNC_MIDTYP_D_P:
            u1_t_tt_act_front = u1_t_tt_fr_act;
            break;
        default:
            /* Do nothing: the output is OFF */
            break;
    }

    if(u1_t_tt_act != u1_s_sbltsync_act_tt) {
        vd_g_SbltsyncCfgTxREARINDI(u1_t_tt_act);
        u1_t_txchg |= (U1)TRUE;
    }
    if(u1_t_txchg == (U1)TRUE) {
        vd_g_SbltsyncCfgTxCXMET1S02();
    }

    u2_s_sbltsync_req_tt = u2_t_tt_req;
    u1_s_sbltsync_act_tt = u1_t_tt_act;
    u1_s_sbltsync_act_fr_tt = u1_t_tt_act_front;
}
/*===================================================================================================================================*/
/*  U1          u1_g_SbltsyncReqChm(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1          u1_g_SbltsyncReqChm(void)
{
    return(u1_s_sbltsync_req_chm);
}
/*===================================================================================================================================*/
/*  U2          u2_g_SbltsyncReqTt(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2          u2_g_SbltsyncReqTt(void)
{
    return(u2_s_sbltsync_req_tt);
}
/*===================================================================================================================================*/
/*  U1          u1_g_SbltsyncActTt(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1          u1_g_SbltsyncActTt(void)
{
    return(u1_s_sbltsync_act_tt);
}
/*===================================================================================================================================*/
/*  U1          u1_g_SbltsyncActFrTt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1          u1_g_SbltsyncActFrTt(void)
{
    return(u1_s_sbltsync_act_fr_tt);
}
/*===================================================================================================================================*/
/*  U1          u1_g_SbltsyncLv2Cmp(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1          u1_g_SbltsyncLv2Cmp(void)
{
    return(u1_s_sbltsync_lv2cmp_chm);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_SbltsyncTrgt(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_SbltsyncTrgt(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS)
{
    static const U2 u2_s_CHMRTRG_MSK  = (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1) | ((U2)1U << SBLTWRN_CHMSTS_LV2) | ((U2)1U << SBLTWRN_CHMSTS_UNBKNT));
    static const U2 u2_s_CHMWRN_MSK   = (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1) | ((U2)1U << SBLTWRN_CHMSTS_LV2) | ((U2)1U << SBLTWRN_CHMSTS_LEGAL));
    static const U2 u2_s_CHMINACT_MSK = (U2)(((U2)1U << SBLTWRN_CHMSTS_OFF) | ((U2)1U << SBLTWRN_CHMSTS_LGLCMP));
    static const U2 u2_s_CHMCMP_MSK   = (U2)((U2)1U << SBLTWRN_CHMSTS_L2CMP);
    static const U4 u4_s_TTACT_LGL    = (U4)((U4)1U << SBLTWRN_TTSTS_LGLPR);
    static const U4 u4_s_TTACT_LV2    = (U4)(((U4)1U << SBLTWRN_TTSTS_FR_LV2) | ((U4)1U << SBLTWRN_TTSTS_RR_LV2));
    static const U4 u4_s_TTACT_LV1    = (U4)(((U4)1U << SBLTWRN_TTSTS_FR_LV1) | ((U4)1U << SBLTWRN_TTSTS_RR_LV1) | ((U4)1U << SBLTWRN_TTSTS_FR_LWSP) | ((U4)1U << SBLTWRN_TTSTS_RR_LWSP));

    U2              u2_t_chm_onedg;
    U1              u1_t_trgt;

    u1_t_trgt = (U1)0U;

    if((u4_a_TT_STS & u4_s_TTACT_LV2) != (U4)0U){
        u1_t_trgt  = (U1)(1U << SBLTSYNC_KND_LV2);
    }
    if((u4_a_TT_STS & u4_s_TTACT_LV1) != (U4)0U){
        u1_t_trgt |= (U1)(1U << SBLTSYNC_KND_LV1);
    }
    if((u4_a_TT_STS & u4_s_TTACT_LGL) == (U4)0U){
        u1_t_trgt |= (U1)(1U << SBLTSYNC_KND_LGL);
    }

    u2_t_chm_onedg  = (u2_s_sbltsync_chm_prev ^ u2_a_CHM_STS) & u2_a_CHM_STS;
    u2_t_chm_onedg &= u2_s_CHMRTRG_MSK;
    if ((u2_t_chm_onedg != (U2)0U) && ((u2_s_sbltsync_chm_prev & u2_s_CHMWRN_MSK) == (U2)0U)) {
        u1_t_trgt |= (U1)SBLTSYNC_RTRG;
    }
    u2_s_sbltsync_chm_prev = u2_a_CHM_STS;

    if ((u2_a_CHM_STS & ((U2)U2_MAX ^ u2_s_CHMINACT_MSK)) == u2_s_CHMCMP_MSK) {
        u1_s_sbltsync_lv2cmp_chm = (U1)TRUE;
    } else {
        u1_s_sbltsync_lv2cmp_chm = (U1)FALSE;
    }

    return(u1_t_trgt);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_SbltsyncTrgt_FM(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_SbltsyncTrgt_FM(const U4 u4_a_TT_STS, const U2 u2_a_CHM_STS)
{
    static const U2 u2_s_CHMRTRG_MSK  = (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1_FM) | ((U2)1U << SBLTWRN_CHMSTS_LV2_FM) | ((U2)1U << SBLTWRN_CHMSTS_INITIAL_FM) | ((U2)1U << SBLTWRN_CHMSTS_UNBKNT_FM));
    static const U2 u2_s_CHMWRN_MSK   = (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1_FM) | ((U2)1U << SBLTWRN_CHMSTS_LV2_FM) | ((U2)1U << SBLTWRN_CHMSTS_INITIAL_FM) | ((U2)1U << SBLTWRN_CHMSTS_UNBKNT_FM));
    static const U2 u2_s_CHMINACT_MSK = (U2)(((U2)1U << SBLTWRN_CHMSTS_OFF_FM) | ((U2)1U << SBLTWRN_CHMSTS_INICMP_FM) | ((U2)1U << SBLTWRN_CHMSTS_UNBKCMP_FM));
    static const U2 u2_s_CHMCMP_MSK   = (U2)((U2)1U << SBLTWRN_CHMSTS_L2CMP_FM);
    static const U4 u4_s_TTACT_LV2    = (U4)((U4)1U << SBLTWRN_TTSTS_LV2_FM);
    static const U4 u4_s_TTACT_LV1    = (U4)(((U4)1U << SBLTWRN_TTSTS_INITIAL_FM) | ((U4)1U << SBLTWRN_TTSTS_INICMP_FM) | ((U4)1U << SBLTWRN_TTSTS_UNBKNT_FM) | ((U4)1U << SBLTWRN_TTSTS_LV1_FM));

    U2              u2_t_chm_onedg;
    U1              u1_t_trgt;

    u1_t_trgt = (U1)0U;

    if((u4_a_TT_STS & u4_s_TTACT_LV2) != (U4)0U){
        u1_t_trgt  = (U1)(1U << SBLTSYNC_KND_LV2);
    }
    if((u4_a_TT_STS & u4_s_TTACT_LV1) != (U4)0U){
        u1_t_trgt |= (U1)(1U << SBLTSYNC_KND_LV1);
    }

    u2_t_chm_onedg  = (u2_s_sbltsync_chm_prev ^ u2_a_CHM_STS) & u2_a_CHM_STS;
    u2_t_chm_onedg &= u2_s_CHMRTRG_MSK;
    if ((u2_t_chm_onedg != (U2)0U) && ((u2_s_sbltsync_chm_prev & u2_s_CHMWRN_MSK) == (U2)0U)) {
        u1_t_trgt |= (U1)SBLTSYNC_RTRG;
    }
    u2_s_sbltsync_chm_prev = u2_a_CHM_STS;

    if ((u2_a_CHM_STS & ((U2)U2_MAX ^ u2_s_CHMINACT_MSK)) == u2_s_CHMCMP_MSK) {
        u1_s_sbltsync_lv2cmp_chm = (U1)TRUE;
    } else {
        u1_s_sbltsync_lv2cmp_chm = (U1)FALSE;
    }

    return(u1_t_trgt);
}
/*===================================================================================================================================*/
/* static void vd_s_SbltsyncChk(U1 * u1_ap_sync_tt, U1 * u1_ap_sync_chm, const U1 u1_a_SYNCBIT)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_SbltsyncChk(U1 * u1_ap_sync_tt, U1 * u1_ap_sync_chm, const U1 u1_a_SYNCBIT)
{
    static  U4 * const u4_sp_SBLTSYNC_TM_ELPSD[SBLTSYNC_NUM_KND] = {
        &u4_s_sbltsync_lgltm_elpsd,
        &u4_s_sbltsync_lv2tm_elpsd,
        &u4_s_sbltsync_lv1tm_elpsd 
    };
    static const U4 u4_s_SBLTSYNC_TM_MAX = (U4)0xFFFFFFFEU;
    static const U1 u1_s_SBLTSYNC_RTRG_SFT = (U1)4U;

    U4                    * u4p_t_tm_elpsd;
    U4                      u4_t_lpcnt;
    U4                      u4_t_sync_tt_prd;
    U4                      u4_t_sync_tt_cng;
    U4                      u4_t_sync_chm_prd;
    U4                      u4_t_sync_chm_cng;
    U1                      u1_t_sync_act;
    U1                      u1_t_rtrg_trgt;
    U1                      u1_t_brand;

    u1_t_brand = u1_g_VardefOmusMCUID0024();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTSYNC_NUM_KND; u4_t_lpcnt++){
        u4_t_sync_tt_prd   = st_gp_SBLTSYNC_PRM[u1_t_brand][u4_t_lpcnt].u4_sync_tt_prd;
        u4_t_sync_tt_cng   = st_gp_SBLTSYNC_PRM[u1_t_brand][u4_t_lpcnt].u4_sync_tt_cng;
        u4_t_sync_chm_prd  = st_gp_SBLTSYNC_PRM[u1_t_brand][u4_t_lpcnt].u4_sync_chm_prd;
        u4_t_sync_chm_cng  = st_gp_SBLTSYNC_PRM[u1_t_brand][u4_t_lpcnt].u4_sync_chm_cng;
        u4p_t_tm_elpsd     = u4_sp_SBLTSYNC_TM_ELPSD[u4_t_lpcnt];
        u1_t_sync_act  = (U1)(1U << u4_t_lpcnt);
        u1_t_rtrg_trgt = (U1)(u1_t_sync_act << u1_s_SBLTSYNC_RTRG_SFT);
        if((u1_a_SYNCBIT & u1_t_sync_act) == (U1)0U){
            (*u4p_t_tm_elpsd) = (U4)U4_MAX;
        }
        else if((*u4p_t_tm_elpsd == (U4)U4_MAX) || ((u1_a_SYNCBIT & u1_t_rtrg_trgt) != (U1)0U)) {
            (*u4p_t_tm_elpsd) = (U4)0U;
        }
        else if(*u4p_t_tm_elpsd <  u4_s_SBLTSYNC_TM_MAX){
            (*u4p_t_tm_elpsd)++;
        }
        else{
            /* Do nothing */
        }
        u1_ap_sync_tt[u4_t_lpcnt]  = u1_s_SbltsyncPeriodSts(u4_t_sync_tt_prd,  u4_t_sync_tt_cng,  *u4p_t_tm_elpsd);
        u1_ap_sync_chm[u4_t_lpcnt] = u1_s_SbltsyncPeriodSts(u4_t_sync_chm_prd, u4_t_sync_chm_cng, *u4p_t_tm_elpsd);
    }
}
/*===================================================================================================================================*/
/* static U1   u1_s_SbltsyncPeriodSts(const U4 u4_a_PRD, const U4 u4_a_CNG, const U4 u4_a_TM_ELPSD)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_SbltsyncPeriodSts(const U4 u4_a_PRD, const U4 u4_a_CNG, const U4 u4_a_TM_ELPSD)
{
    U1  u1_t_sync;

    if((u4_a_TM_ELPSD % u4_a_PRD) == (U4)0U){
        u1_t_sync = (U1)SBLTSYNC_OUT_PRD;
    }
    else if((u4_a_TM_ELPSD % u4_a_PRD) < u4_a_CNG){
        u1_t_sync = (U1)SBLTSYNC_OUT_ON_TRM;
    }
    else{
        u1_t_sync = (U1)SBLTSYNC_OUT_OFF;
    }
    return (u1_t_sync);
}
/*===================================================================================================================================*/
/* static U2   u2_s_SbltsyncChmSts(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_SbltsyncChmSts(void)
{
    static const U2 u2_s_CHM_ACT_LGLPR = (U2)((U2)1U << SBLTWRN_CHMSTS_LGLPR);
    static const U2 u2_s_CHM_ACT_LEGAL = (U2)((U2)1U << SBLTWRN_CHMSTS_LEGAL);
    U4              u4_t_lpcnt;
    U2              u2_t_chm_bit;
    U2              u2_t_chm_stsbit;
    U2              u2_t_chm_msk;
    U1              u1_t_chm_sts;

    u2_t_chm_bit = (U2)0U;
    u2_t_chm_msk = u2_g_SbltsyncCfgChmMask();

    for (u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++) {
        u1_t_chm_sts = u1_g_SbltwrnChmStsBySeat((U1)u4_t_lpcnt);
        u2_t_chm_stsbit = (U2)((U2)1U << u1_t_chm_sts);

        /* Diag Customize Check */
        if ((u2_t_chm_msk & (U2)((U2)1U << u4_t_lpcnt)) == (U2)0U) {
            /* Remove a request bit except legal warning */
            u2_t_chm_stsbit &= (U2)(u2_s_CHM_ACT_LGLPR | u2_s_CHM_ACT_LEGAL);
        }
        u2_t_chm_bit |= u2_t_chm_stsbit;
    }

    return (u2_t_chm_bit);
}
/*===================================================================================================================================*/
/* static U2   u2_s_SbltsyncChmSts_FM(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_SbltsyncChmSts_FM(void)
{
    U4              u4_t_lpcnt;
    U2              u2_t_chm_bit;
    U2              u2_t_chm_stsbit;
    U1              u1_t_chm_sts;

    u2_t_chm_bit = (U2)0U;
    /* u2_t_chm_msk = u2_g_SbltsyncCfgChmMask(); */ 
    /* CAUTION: */
    /* This function is called only when the destination is USA and the new FMVSS208 is applied (MCUID1137=1), */
    /* so u2_g_SbltsyncCfgChmMask is not executed. */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++) {
        u1_t_chm_sts = u1_g_SbltwrnChmStsBySeat_FM((U1)u4_t_lpcnt);
        u2_t_chm_stsbit = (U2)((U2)1U << u1_t_chm_sts);

        u2_t_chm_bit |= u2_t_chm_stsbit;
    }

    return(u2_t_chm_bit);
}
/*===================================================================================================================================*/
/* static void vd_s_SbltsyncChmReqUpdt(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_SbltsyncChmReqUpdt(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT)
{
    static const U2 u2_sp_CHM_ACT_INT[SBLTSYNC_NUM_KND] = {
        (U2)((U2)1U << SBLTWRN_CHMSTS_LEGAL),
        (U2)((U2)1U << SBLTWRN_CHMSTS_LV2),
        (U2)((U2)1U << SBLTWRN_CHMSTS_LV1)
    };

    static const U2 u2_s_CHM_ACT_LGLPR  = (U2)((U2)1U << SBLTWRN_CHMSTS_LGLPR);
    static const U2 u2_s_CHM_ACT_UNBKNT = (U2)((U2)1U << SBLTWRN_CHMSTS_UNBKNT);
    static const U2 u2_s_CHM_ACT_WRN    = (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1) | ((U2)1U << SBLTWRN_CHMSTS_LV2));

    U4              u4_t_lpcnt;
    U1              u1_t_chm_req;
    U1              u1_t_ringknd;

    u1_t_chm_req = (U1)0U;

    if((u2_a_CHM_BIT & u2_s_CHM_ACT_LGLPR) == (U2)0U){
        /* CAUTION: */
        /* The unbuckle notification is performed only if other seat(s) are not in Lv1/Lv2. */
        /* This special procedure MUST BE also MODIFIED when "MET-M_CONTBUZZ-" is modified  */
        /*  because this procedure depends on buzzer priority between "Unbuckle notificaton" and "Seatbelt Lv1/Lv2". */
        if(((u2_a_CHM_BIT & u2_s_CHM_ACT_UNBKNT) != (U2)0U) &&
           ((u2_a_CHM_BIT & u2_s_CHM_ACT_WRN)    == (U2)0U)){
            u1_t_chm_req = (U1)SBLTSYNC_CHM_REQ_UNBKL;
        }

        u1_t_ringknd = u1_g_SbltsyncCfgChmRingKnd();
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTSYNC_NUM_KND; u4_t_lpcnt++){
            if(((u2_a_CHM_BIT & u2_sp_CHM_ACT_INT[u4_t_lpcnt]) != (U2)0U                   ) &&
               ((u1_ap_SYNC[u4_t_lpcnt] == (U1)SBLTSYNC_OUT_PRD) || (u1_t_ringknd == (U1)u4_t_lpcnt))){
                u1_t_chm_req |= (U1)(1U << u4_t_lpcnt);
            }
        }
    }
    u1_s_sbltsync_req_chm = u1_t_chm_req;
}
/*===================================================================================================================================*/
/* static void vd_s_SbltsyncChmReqUpdt_FM(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_SbltsyncChmReqUpdt_FM(const U1 * u1_ap_SYNC, const U2 u2_a_CHM_BIT)
{
    static const U2 u2_sp_CHM_ACT_INT[SBLTSYNC_NUM_KND] = {
        (U2)0U,
        (U2)((U2)1U << SBLTWRN_CHMSTS_LV2_FM),
        (U2)(((U2)1U << SBLTWRN_CHMSTS_LV1_FM) | ((U2)1U << SBLTWRN_CHMSTS_INITIAL_FM) | ((U2)1U << SBLTWRN_CHMSTS_UNBKNT_FM))
    };

    U4              u4_t_lpcnt;
    U1              u1_t_chm_req;
    U1              u1_t_ringknd;

    u1_t_chm_req = (U1)0U;

    u1_t_ringknd = u1_g_SbltsyncCfgChmRingKnd();
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTSYNC_NUM_KND; u4_t_lpcnt++){
        if((U4)SBLTSYNC_KND_LGL != u4_t_lpcnt) {
            if(((u2_a_CHM_BIT & u2_sp_CHM_ACT_INT[u4_t_lpcnt]) != (U2)0U) &&
               ((u1_ap_SYNC[u4_t_lpcnt] == (U1)SBLTSYNC_OUT_PRD) || (u1_t_ringknd == (U1)u4_t_lpcnt))){
                u1_t_chm_req |= (U1)(1U << u4_t_lpcnt);
            }
        }
    }
    u1_s_sbltsync_req_chm = u1_t_chm_req;
}
/*===================================================================================================================================*/
/* static U1   u1_s_SbltsyncFrTtSts(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_SbltsyncFrTtSts(void)
{
    static const U1 u1_s_SBLTSYNC_FR_PRTY_TBL[SBLTWRN_NUM_TTSTS] = {
        (U1)9U,
        (U1)0U,
        (U1)1U,
        (U1)7U,
        (U1)8U,
        (U1)3U,
        (U1)2U,
        (U1)6U,
        (U1)5U,
        (U1)4U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U,
        (U1)10U
    };

    U4              u4_t_lpcnt;
    U1              u1_t_prty;
    U1              u1_t_sts;
    U1              u1_t_fr_sts;

    u1_t_prty   = (U1)U1_MAX;
    u1_t_fr_sts = (U1)SBLTWRN_TTSTS_OFF;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)SBLTSYNC_NUM_FRSEAT; u4_t_lpcnt++){
        u1_t_sts = u1_g_SbltwrnTtStsBySeat((U1)u4_t_lpcnt);
        if(u1_t_sts < (U1)SBLTWRN_NUM_TTSTS){
           	if(u1_s_SBLTSYNC_FR_PRTY_TBL[u1_t_sts] < u1_t_prty){
            	u1_t_prty   = u1_s_SBLTSYNC_FR_PRTY_TBL[u1_t_sts];
            	u1_t_fr_sts = u1_t_sts;
			}
        }
    }

    return(u1_t_fr_sts);
}
/*===================================================================================================================================*/
/* static U1   u1_s_SbltsyncTtReqUpdt(const U1 u1_a_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_SbltsyncTtReqUpdt(const U1 u1_a_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req)
{
    U2              u2_t_out;
    U1              u1_t_act;

    u2_t_out = (U2)FALSE;
    u1_t_act = (U1)FALSE;
    switch(u1_a_SEAT_STS) {
        case SBLTWRN_TTSTS_LEGAL:
            if((u1_ap_SYNC[SBLTSYNC_KND_LGL] == (U1)SBLTSYNC_OUT_PRD   ) ||
               (u1_ap_SYNC[SBLTSYNC_KND_LGL] == (U1)SBLTSYNC_OUT_ON_TRM)){
                u2_t_out = (U2)TRUE;
            }
            u1_t_act     = (U1)TRUE;
            break;
        case SBLTWRN_TTSTS_FR_LV2:
        case SBLTWRN_TTSTS_RR_LV2:
            if((u1_ap_SYNC[SBLTSYNC_KND_LV2] == (U1)SBLTSYNC_OUT_PRD   ) ||
               (u1_ap_SYNC[SBLTSYNC_KND_LV2] == (U1)SBLTSYNC_OUT_ON_TRM)){
                u2_t_out = (U2)TRUE;
            }
            u1_t_act     = (U1)TRUE;
            break;
        case SBLTWRN_TTSTS_FR_LV1:
        case SBLTWRN_TTSTS_RR_LV1:
        case SBLTWRN_TTSTS_FR_LWSP:
        case SBLTWRN_TTSTS_RR_LWSP:
            if((u1_ap_SYNC[SBLTSYNC_KND_LV1] == (U1)SBLTSYNC_OUT_PRD   ) ||
               (u1_ap_SYNC[SBLTSYNC_KND_LV1] == (U1)SBLTSYNC_OUT_ON_TRM)){
                u2_t_out = (U2)TRUE;
            }
            u1_t_act     = (U1)TRUE;
            break;
        case SBLTWRN_TTSTS_IGON:
        case SBLTWRN_TTSTS_DOOR:
        case SBLTWRN_TTSTS_FR_PARK:
        case SBLTWRN_TTSTS_RR_PARK:
        case SBLTWRN_TTSTS_SYNC:
        case SBLTWRN_TTSTS_FR_L2CMP:
        case SBLTWRN_TTSTS_RR_L2CMP_ON:
            u2_t_out     = (U2)TRUE;
            u1_t_act     = (U1)TRUE;
            break;
        default:
            /* Do nothing: the output is OFF */
            break;
    }
    *u2p_a_req = u2_t_out;

    return(u1_t_act);
}
/*==========================================================================================================================================*/
/* static U1   u1_s_SbltsyncTtReqUpdt_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req, const U1 u1_a_SEATID)        */
/* ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                       */
/*  Return:         -                                                                                                                       */
/*==========================================================================================================================================*/
static U1   u1_s_SbltsyncTtReqUpdt_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 * u1_ap_SYNC, U2 * u2p_a_req, const U1 u1_a_SEATID)
{
    U2              u2_t_out;
    U1              u1_t_act;
    U1              u1_t_lit;
    U1              u1_t_bkl;

    u2_t_out = (U2)FALSE;
    u1_t_act = (U1)FALSE;
    switch(u1_ap_ALL_SEAT_STS[u1_a_SEATID]) {
        case (U1)SBLTWRN_TTSTS_LV2_FM:
            if((u1_ap_SYNC[SBLTSYNC_KND_LV2] == (U1)SBLTSYNC_OUT_PRD   ) ||
                (u1_ap_SYNC[SBLTSYNC_KND_LV2] == (U1)SBLTSYNC_OUT_ON_TRM)){
                u2_t_out = (U2)TRUE;
            }
            u1_t_act     = (U1)TRUE;
            break;
        case (U1)SBLTWRN_TTSTS_LV1_FM:
        case (U1)SBLTWRN_TTSTS_INITIAL_FM:
        case (U1)SBLTWRN_TTSTS_UNBKNT_FM:
        case (U1)SBLTWRN_TTSTS_INICMP_FM:
            if((u1_ap_SYNC[SBLTSYNC_KND_LV1] == (U1)SBLTSYNC_OUT_PRD   ) ||
                (u1_ap_SYNC[SBLTSYNC_KND_LV1] == (U1)SBLTSYNC_OUT_ON_TRM)){
                u2_t_out = (U2)TRUE;
            }
            u1_t_act     = (U1)TRUE;
            break;
        case (U1)SBLTWRN_TTSTS_L2INT_FM:
        case (U1)SBLTWRN_TTSTS_DOOR_FM:
        case (U1)SBLTWRN_TTSTS_IGON_FM:
            u2_t_out     = (U2)TRUE;
            u1_t_act     = (U1)TRUE;
            break;
        case (U1)SBLTWRN_TTSTS_L2CMP_FM:
        case (U1)SBLTWRN_TTSTS_OFF_FM:
            if(((U1)SBLTSYNC_NUM_FRSEAT <= u1_a_SEATID) && ((U1)SBLTWRN_NUM_ALLSEAT > u1_a_SEATID)){
                u1_t_lit = u1_s_SbltsyncRearTtChk_FM(u1_ap_ALL_SEAT_STS, u1_a_SEATID);
                u1_t_bkl = u1_g_SbltSeatBklStsBySeat(u1_a_SEATID);
                if(((U1)TRUE == u1_t_lit) && (((U1)SBLTWRN_BKLSTS_UNBCKL & u1_t_bkl) != (U1)0U)){
                    u2_t_out     = (U2)TRUE;
                    u1_t_act     = (U1)TRUE;
                }
            }
            break;
        default:
            /* Do nothing: the output is OFF */
            break;
    }
    *u2p_a_req = u2_t_out;

    return(u1_t_act);
}
/*==========================================================================================================================================*/
/* static U1   u1_s_SbltsyncRearTtChk_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 u1_a_SEATID)                                               */
/* ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                       */
/*  Return:         -                                                                                                                       */
/*==========================================================================================================================================*/
static U1   u1_s_SbltsyncRearTtChk_FM(const U1 * u1_ap_ALL_SEAT_STS, const U1 u1_a_SEATID)
{
    U4              u4_t_lpcnt;
    U1              u1_t_lit;

    u1_t_lit = (U1)FALSE;

    for(u4_t_lpcnt = (U4)SBLTSYNC_NUM_FRSEAT; u4_t_lpcnt < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_lpcnt++){
        if(u1_a_SEATID != (U1)u4_t_lpcnt){
            if(((U1)SBLTWRN_TTSTS_OFF_FM != u1_ap_ALL_SEAT_STS[u4_t_lpcnt]) &&
               ((U1)SBLTWRN_TTSTS_L2CMP_FM != u1_ap_ALL_SEAT_STS[u4_t_lpcnt])){
                u1_t_lit = (U1)TRUE;
            }
        }
    }

    return(u1_t_lit);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    05/31/2019  YI       New.                                                                                               */
/*  1.1.0    01/23/2020  YI       Add telltale request over white IF.                                                                */
/*  1.2.0    05/14/2020  YI       Delete telltale request over white IF.                                                             */
/*  1.3.0    07/22/2020  KK       Add the support of the different period between telltale and chime                                 */
/*  2.0.0    10/08/2020  KK       MET-B_SEAREM-CSTD-1-03-A-C2                                                                        */
/*  2.1.0    02/23/2021  TN       Move cycle table to sbltsync_cfg.c                                                                 */
/*  2.1.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.2    04/05/2022  YI(M)    Add range check refer to u1_s_SBLTSYNC_FR_PRTY_TBL.                                                */
/*  2.2.0    04/06/2022  YI(M)    Move cycle table to sbltsync.c.                                                                    */
/*  2.3.0    01/29/2024  TH       for 19PFv3                    .                                                                    */
/*  2.4.0    09/08/2025  ST       Legal compliance.(FMVSS208_2025 SBR regulations)                                                   */
/*  2.5.0    01/22/2026  ST       Delete buzzer deterrence process in FMVSS operation                                                */
/*  2.6.0    03/23/2026  SN       Change config for BEV Full_Function_2.                                                             */
/*                                MET-B_OPTMON-CSTD-0-00-A-C0                                                                        */
/*                                Add an interface to switch the OPTMON TT request (steady/blink) using seatbelt Lv1 TT timing.      */
/*                                Expose the blink/buzzer period table externally.                                                   */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * KK   = Kohei Kato,    Denso Techno                                                                                             */
/*  * TN   = Tetsu Naruse,  Denso Techno                                                                                             */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * YI(M)= Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * ST   = Shoma Taki,    PXT                                                                                                      */
/*  * SN   = Shizuka Nakajima, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
