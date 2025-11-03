/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Warning Chime                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_ARB_C_MAJOR                      (2)
#define WCHIME_ARB_C_MINOR                      (1)
#define WCHIME_ARB_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "wchime_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((WCHIME_ARB_C_MAJOR != WCHIME_H_MAJOR) || \
     (WCHIME_ARB_C_MINOR != WCHIME_H_MINOR) || \
     (WCHIME_ARB_C_PATCH != WCHIME_H_PATCH))
#error "wchime_arb.c and wchime.h : source and header files are inconsistent!"
#endif

#if ((WCHIME_ARB_C_MAJOR != WCHIME_CFG_H_MAJOR) || \
     (WCHIME_ARB_C_MINOR != WCHIME_CFG_H_MINOR) || \
     (WCHIME_ARB_C_PATCH != WCHIME_CFG_H_PATCH))
#error "wchime_arb.c and wchime_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WCHIME_ARB_NUM_STS                      (3U)                                    /* Number of operating status.               */
#define WCHIME_ARB_REQ_SEL                      (0U)                                    /* Request is selected.                      */
#define WCHIME_ARB_SW_WAIT                      (1U)                                    /* Switching Wait.                           */
#define WCHIME_ARB_NOT_SEL                      (2U)                                    /* Nothing is selected.                      */

#define WCHIME_NUM_STSCHK                       (16U)                                   /* Number of status check.                   */
#define WCHIME_STSCHK_REQSW_ENA                 (0x01U)                                 /* Switching Enable.                         */
#define WCHIME_STSCHK_SW_WAIT                   (0x02U)                                 /* Switching wait time.                      */
#define WCHIME_STSCHK_WAI_EXPRD                 (0x04U)                                 /* Elapsed waiting time.                     */
#define WCHIME_STSCHK_REQ_DTCT                  (0x08U)                                 /* Sound request detection.                  */

#define WCHIME_ARB_ACT_TO_REQ_SEL               (0U)                                    /* Transition to request detection.          */
#define WCHIME_ARB_ACT_REQ_SEL                  (1U)                                    /* Continue request detection.               */
#define WCHIME_ARB_ACT_TO_SW_WAIT               (2U)                                    /* Transition to switching wait time.        */
#define WCHIME_ARB_ACT_SW_WAIT                  (3U)                                    /* Continue switching wait time.             */
#define WCHIME_ARB_ACT_TO_NOT_SEL               (4U)                                    /* Transition to no request.                 */

#define WCHIME_REQ_TO_BUF_IDX                   (5U)                                    /* For index operation in buffers.           */
#define WCHIME_REQ_TO_BIT_POS                   ((0x01U << WCHIME_REQ_TO_BUF_IDX) - 1U) /* For bit position operation in buffers.    */

#define WCHIME_MM_BUZ_LV_NUM                    (10U)                                   /* Number of buzzer priority level for MM    */
#define WCHIME_MM_BUZ_LVOFF                     (0x0FU)                                 /* Buzzer priority level OFF for MM.         */
#define WCHIME_MM_BUZ_LV1                       (0x01U)                                 /* Buzzer priority level 1 for MM.           */
#define WCHIME_MM_BUZ_LV2                       (0x02U)                                 /* Buzzer priority level 2 for MM.           */
#define WCHIME_MM_BUZ_LV3                       (0x03U)                                 /* Buzzer priority level 3 for MM.           */
#define WCHIME_MM_BUZ_LV4                       (0x04U)                                 /* Buzzer priority level 4 for MM.           */
#define WCHIME_MM_BUZ_LV5                       (0x05U)                                 /* Buzzer priority level 5 for MM.           */
#define WCHIME_MM_BUZ_LV6                       (0x06U)                                 /* Buzzer priority level 6 for MM.           */
#define WCHIME_MM_BUZ_LV7                       (0x07U)                                 /* Buzzer priority level 7 for MM.           */
#define WCHIME_MM_BUZ_LV8                       (0x08U)                                 /* Buzzer priority level 8 for MM.           */
#define WCHIME_MM_BUZ_LV9                       (0x09U)                                 /* Buzzer priority level 9 for MM.           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1     u1_s_wchime_emg;            /* ON/OFF of emergency buzzer for MM     (WCHIME_BUZ_EMON/WCHIME_BUZ_EMOFF)                */
static U1     u1_s_wchime_longtone;       /* Lengh of meter buzzer for MM          (WCHIME_BUZ_LONG/WCHIME_BUZ_SHORT)                */
static U1     u1_s_wchime_highpri;        /* Level of meter buzzer priority for MM (WCHIME_MM_BUZ_LVOFF,WCHIME_MM_BUZ_LV1-LV9)       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_wChimeReqmaskClr(const U4 * u4_ap_REQBIT, const U1 u1_a_CYC_CHK, const U1 u1_a_REQ_SEL, const U4 * u4_ap_CHBIT);
static void    vd_s_wChimeReqEvtchk(U4 * u4_ap_reqbit, const U4 * u4_ap_MDMSK);

static U1      u1_s_wChimeReqNext(const U4 * u4_ap_REQBIT, const U4 * u4_ap_CHBIT, const U4 * u4_ap_SELMSK);
static U1      u1_s_wChimeSwReqchk(const U1 u1_a_REQ_SEL, const U1 u1_a_BFRWAIT_SEL, const U1 u1_a_REQ_NEXT,
                                   const U1 u1_a_CYC_CHK, const U4 * u4_ap_MDMSK, U2 * u2p_a_wait_time);
static void    vd_s_wChimeReqSelUpdt(const U1 u1_a_STSCHK, const U1 u1_a_REQ_NEXT, ST_WCHIME_ARB_CH * st_ap_ch);
static void    vd_s_wChimeReqmaskUpdt(U4 * u4_ap_selmsk, const U4 * u4_ap_CHBIT, const U1 u1_a_REQ_SEL);
static void    vd_s_wChimeEvtmskUpdt(const U4 * u4_ap_SELMSK, const U4 * u4_ap_CHBIT, const U4 u4_a_POS, const U4 u4_a_MASK);

static void    vd_s_wChimeMMInfo(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_wChimeInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeInit(void)
{
    U4                    u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
        u4_gp_wchime_reqbit[u4_t_lpcnt] = (U4)0U;
        u4_gp_wchime_evtbit[u4_t_lpcnt] = (U4)0U;
        u4_gp_wchime_evtmsk[u4_t_lpcnt] = u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt];
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_NUM_CH; u4_t_lpcnt++){
        st_gp_wchime_arb_ch[u4_t_lpcnt].u2_tmelpsd     = (U2)U2_MAX;
        st_gp_wchime_arb_ch[u4_t_lpcnt].u1_arb         = (U1)WCHIME_ARB_NOT_SEL;
        st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_vol     = (U1)U1_MAX;
        st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_sel     = (U1)U1_MAX;
        st_gp_wchime_arb_ch[u4_t_lpcnt].u1_bfrwait_sel = (U1)U1_MAX;
        st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_mm      = (U1)U1_MAX;

        u2_gp_wchime_wt_tim[u4_t_lpcnt]                = (U2)WCHIME_WT_TIM_CMN;
    }

    u1_s_wchime_emg      = (U1)WCHIME_BUZ_EMOFF;
    u1_s_wchime_longtone = (U1)WCHIME_BUZ_SHORT;
    u1_s_wchime_highpri  = (U1)WCHIME_MM_BUZ_LVOFF;

    vd_g_wChimeCfgInit();
    vd_g_wChimeReqCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_wChimeMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeMainTask(void)
{
    static const U4       u4_sp_WCHIME_MDMSK_UNK[WCHIME_REQBIT_NWORD_MAX] = {
        (U4)U4_MAX,  /* 0 */
        (U4)U4_MAX,  /* 1 */
        (U4)U4_MAX,  /* 2 */
        (U4)U4_MAX,  /* 3 */
        (U4)U4_MAX,  /* 4 */
        (U4)U4_MAX,  /* 5 */
        (U4)U4_MAX   /* 6 */
    };

    const U4 *            u4_tp_CHBIT;
    const U4 *            u4_tp_MDMSK;

    U4                    u4_t_lpcnt;

    U4                    u4_tp_reqbit[WCHIME_REQBIT_NWORD_MAX];
    U4                    u4_tp_selmsk[WCHIME_REQBIT_NWORD_MAX];

    U1                    u1_t_opemd;
    U1                    u1_t_req_next;
    U1                    u1_t_stschk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)WCHIME_REQBIT_NWORD_MAX; u4_t_lpcnt++){
        u4_tp_reqbit[u4_t_lpcnt] = (U4)0U;
        u4_tp_selmsk[u4_t_lpcnt] = (U4)U4_MAX;
    }

    vd_g_wChimeCfgPreTask();

    u1_t_opemd = u1_g_wChimeCfgOpemdchk();
    if(u1_t_opemd < u1_g_WCHIME_NUM_OPEMD){
        u4_tp_MDMSK = u4p_gp_WCHIME_REQBIT_BY_OPEMD[u1_t_opemd];
    }
    else{
        u4_tp_MDMSK = &u4_sp_WCHIME_MDMSK_UNK[0];
    }

    vd_g_wChimeCfgReqchk(&u4_tp_reqbit[0]);

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_NUM_CH; u4_t_lpcnt++){
        u4_tp_CHBIT                      = u4p_gp_WCHIME_REQBIT_BY_CH[u4_t_lpcnt];
        u1_gp_wchime_cyclchk[u4_t_lpcnt] = u1_g_wChimeCfgWavCycled((U1)u4_t_lpcnt);

        vd_s_wChimeReqmaskClr(&u4_tp_reqbit[0], u1_gp_wchime_cyclchk[u4_t_lpcnt], st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_sel, u4_tp_CHBIT);
    }
    vd_s_wChimeReqEvtchk(&u4_tp_reqbit[0], u4_tp_MDMSK);

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_NUM_CH; u4_t_lpcnt++){
        u4_tp_CHBIT   = u4p_gp_WCHIME_REQBIT_BY_CH[u4_t_lpcnt];
        u1_t_req_next = u1_s_wChimeReqNext(&u4_tp_reqbit[0], u4_tp_CHBIT, &u4_tp_selmsk[0]);

        u1_t_stschk   = u1_s_wChimeSwReqchk(st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_sel, st_gp_wchime_arb_ch[u4_t_lpcnt].u1_bfrwait_sel,
                                            u1_t_req_next, u1_gp_wchime_cyclchk[u4_t_lpcnt], u4_tp_MDMSK, &u2_gp_wchime_wt_tim[u4_t_lpcnt]);
        if(st_gp_wchime_arb_ch[u4_t_lpcnt].u2_tmelpsd < (U2)U2_MAX){
            st_gp_wchime_arb_ch[u4_t_lpcnt].u2_tmelpsd++;
        }
        if(st_gp_wchime_arb_ch[u4_t_lpcnt].u2_tmelpsd >= u2_gp_wchime_wt_tim[u4_t_lpcnt]){
            u1_t_stschk |= (U1)WCHIME_STSCHK_WAI_EXPRD;
        }

        vd_s_wChimeReqSelUpdt(u1_t_stschk, u1_t_req_next, &st_gp_wchime_arb_ch[u4_t_lpcnt]);
        vd_s_wChimeReqmaskUpdt(&u4_tp_selmsk[0], u4_tp_CHBIT, st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_sel);
    }

    vd_s_wChimeMMInfo();
    vd_g_wChimeCfgPostTask();
}
/*===================================================================================================================================*/
/*  U1      u1_g_wChimeReqSel(const U1 u1_a_WC_CH, U1 * u1p_a_reqvol)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_wChimeReqSel(const U1 u1_a_WC_CH, U1 * u1p_a_reqvol)
{
    U1                    u1_t_sel;

    u1_t_sel = (U1)U1_MAX;

    if(u1_a_WC_CH < u1_g_WCHIME_NUM_CH){
        u1_t_sel = st_gp_wchime_arb_ch[u1_a_WC_CH].u1_req_sel;
        if(u1p_a_reqvol != vdp_PTR_NA){
            (*u1p_a_reqvol) = st_gp_wchime_arb_ch[u1_a_WC_CH].u1_req_vol;
        }
    }

    return(u1_t_sel);
}
/*===================================================================================================================================*/
/*  void    vd_g_wChimeMetBuzzInfo(U1 * u1p_a_level, U1 * u1p_a_length, U1 * u1p_a_emergency)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimeMetBuzzInfo(U1 * u1p_a_level, U1 * u1p_a_length, U1 * u1p_a_emergency)
{
    *u1p_a_level     = u1_s_wchime_highpri;
    *u1p_a_length    = u1_s_wchime_longtone;
    *u1p_a_emergency = u1_s_wchime_emg;
}
#if 0   /* BEV Rebase provisionally */
#else   /* BEV Rebase provisionally */
/*===================================================================================================================================*/
/*  void    vd_g_wChimePutMWVCope(U1 u1_a_mwvcope)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_mwvcope : Meter warning volume Cstm value                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_wChimePutMWVCope(U1 u1_a_mwvcope)
{
    if(u1_a_mwvcope <= (U1)2U)
    {
        u1_g_wchime_metcstmvol = u1_a_mwvcope;
    }
}
/*===================================================================================================================================*/
/*  void    u1_g_wChimeGetMWVCope(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_g_wchime_metcstmvol : Meter warning volume Cstm value                                                         */
/*===================================================================================================================================*/
U1      u1_g_wChimeGetMWVCope(void)
{
    return(u1_g_wchime_metcstmvol);
}
#endif   /* BEV Rebase provisionally */
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeReqmaskClr(const U4 * u4_ap_REQBIT, const U1 u1_a_CYC_CHK, const U1 u1_a_REQ_SEL,                      */
/*                                       const U4 * u4_ap_CHBIT)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeReqmaskClr(const U4 * u4_ap_REQBIT, const U1 u1_a_CYC_CHK, const U1 u1_a_REQ_SEL, const U4 * u4_ap_CHBIT)
{
    U4 u4_t_lpcnt;
    U4 u4_t_bit_mask;
    U1 u1_t_bz_req;
    U1 u1_t_sw_ctrl;
    U1 u1_t_chk;

    if(u1_a_REQ_SEL < u1_g_WCHIME_NUM_REQ){
        u1_t_bz_req  = u1_g_wChimeCfgReqRead(u4_ap_REQBIT, u1_a_REQ_SEL);
        u1_t_sw_ctrl = u1_g_wChimeReqSwCtrl(u1_a_REQ_SEL);

        u1_t_chk     = u1_t_sw_ctrl & (U1)WCHIME_REQ_SWC_WAV_CYCL;

        if((u1_t_bz_req == (U1)FALSE                     ) &&
           ((u1_a_CYC_CHK == (U1)TRUE                   )  ||
            (u1_t_chk     != (U1)WCHIME_REQ_SWC_WAV_CYCL))){

            /* The current buzzer will be stop at this cycle.Therefore, clear the evtmsk for target CH. */
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
                u4_t_bit_mask                    = (u4_ap_CHBIT[u4_t_lpcnt] & u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt]);
                u4_gp_wchime_evtmsk[u4_t_lpcnt] |= u4_t_bit_mask;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeReqEvtchk(U4 * u4_ap_reqbit, const U4 * u4_ap_MDMSK)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeReqEvtchk(U4 * u4_ap_reqbit, const U4 * u4_ap_MDMSK)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_evtbit;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){

        u4_ap_reqbit[u4_t_lpcnt] &= u4_ap_MDMSK[u4_t_lpcnt];

        u4_t_evtbit  = (u4_ap_reqbit[u4_t_lpcnt] ^ u4_gp_wchime_reqbit[u4_t_lpcnt]) & u4_ap_reqbit[u4_t_lpcnt];
        u4_t_evtbit &= u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt];

        u4_gp_wchime_reqbit[u4_t_lpcnt]  = u4_ap_reqbit[u4_t_lpcnt];

        u4_gp_wchime_evtbit[u4_t_lpcnt] |= u4_t_evtbit;
        u4_gp_wchime_evtbit[u4_t_lpcnt] &= (u4_gp_wchime_evtmsk[u4_t_lpcnt] & u4_ap_MDMSK[u4_t_lpcnt]);
        u4_gp_wchime_evtmsk[u4_t_lpcnt]  = (U4)0U;

        u4_ap_reqbit[u4_t_lpcnt] &= ((U4)U4_MAX ^ u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt]);
        u4_ap_reqbit[u4_t_lpcnt] |= u4_gp_wchime_evtbit[u4_t_lpcnt];
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_wChimeReqNext(const U4 * u4_ap_REQBIT, const U4 * u4_ap_CHBIT, const U4 * u4_ap_SELMSK)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_wChimeReqNext(const U4 * u4_ap_REQBIT, const U4 * u4_ap_CHBIT, const U4 * u4_ap_SELMSK)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_chkbit;
    U4                    u4_t_req_next;

    u4_t_lpcnt = (U4)0U;
    do{
        u4_t_chkbit = (u4_ap_REQBIT[u4_t_lpcnt] & u4_ap_CHBIT[u4_t_lpcnt]) & u4_ap_SELMSK[u4_t_lpcnt];
        u4_t_lpcnt++; /* QAC over-detection */
    }
    while((u4_t_chkbit == (U4)0U                         ) &&
          (u4_t_lpcnt  <  (U4)u1_g_WCHIME_REQBIT_NUM_WORD));

    if(u4_t_chkbit != (U4)0U){

        u4_t_req_next = (U4)u1_g_wChimeLsbSrch(u4_t_chkbit) + ((u4_t_lpcnt - (U4)1U) << WCHIME_REQ_TO_BUF_IDX);
        /* The type of u1_g_wChimeLsbSrch is U1, so max value of u1_g_wChimeLsbSrch is 255.                                          */
        /* The max value of u4_t_lpcnt is u1_g_WCHIME_REQBIT_NUM_WORD, so max value of u4_t_lpcnt is 255.                            */
        /* The min value of u4_t_lpcnt is 1, because u4_t_lpcnt ++ is always executed after u4_t_lpcnt is initialized with 0         */
        /* The max value of ((u4_t_lpcnt - (U4)1U) << WCHIME_REQ_TO_BUF_IDX) is always lower than 0x00001FE0(0xFF<< 5)               */
        /* Therefore (U4) u1_g_wChimeLsbSrch (u4_t_chkbit) + ((u4_t_lpcnt-(U4) 1U) << WCHIME_REQ_TO_BUF_IDX) can never be greater than U4_MAX */
        if(u4_t_req_next > (U4)U1_MAX){
            u4_t_req_next = (U4)U1_MAX;
        }
    }
    else{
        u4_t_req_next = (U4)U1_MAX;
    }

    return((U1)u4_t_req_next);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_wChimeSwReqchk(const U1 u1_a_REQ_SEL, const U1 u1_a_BFRWAIT_SEL, const U1 u1_a_REQ_NEXT,                     */
/*                                     const U1 u1_a_CYC_CHK, const U4 * u4_ap_MDMSK, U2 * u2p_a_wait_time)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_wChimeSwReqchk(const U1 u1_a_REQ_SEL, const U1 u1_a_BFRWAIT_SEL, const U1 u1_a_REQ_NEXT,
                                   const U1 u1_a_CYC_CHK, const U4 * u4_ap_MDMSK, U2 * u2p_a_wait_time)
{
    static const U1       u1_s_WCHIME_STSCHK_SW_DIS = ((U1)WCHIME_REQ_SWC_WAV_CYCL |
                                                       (U1)WCHIME_REQ_SWC_OPEMD    |
                                                       (U1)WCHIME_REQ_SWC_PRI_HI);

    U4                    u4_t_bit;
    U1                    u1_t_pos;

    U1                    u1_t_stschk;

    U1                    u1_t_sw_ctrl;
    U1                    u1_t_sw_chk;
    U1                    u1_t_chk;
    U1                    u1_t_chk_next;

    if(u1_a_REQ_NEXT < u1_g_WCHIME_NUM_REQ){
        u1_t_stschk  = (U1)WCHIME_STSCHK_REQ_DTCT;
    }
    else{
        u1_t_stschk  = (U1)0x00U;
    }

    if((u1_a_REQ_SEL >= u1_g_WCHIME_NUM_REQ) ||
       (u1_a_CYC_CHK == (U1)TRUE           )){

        u1_t_stschk |= (U1)WCHIME_STSCHK_REQSW_ENA;
    }
    else{

        u1_t_sw_ctrl = u1_g_wChimeReqSwCtrl(u1_a_REQ_SEL);

        u1_t_sw_chk  = u1_t_sw_ctrl & (U1)WCHIME_REQ_SWC_WAV_CYCL;

        u1_t_chk = u1_t_sw_ctrl & (U1)WCHIME_REQ_SWC_OPEMD;
        if(u1_t_chk != (U1)0U){

            u1_t_pos  = u1_a_REQ_SEL >> (U1)WCHIME_REQ_TO_BUF_IDX;
            u4_t_bit  = (U4)0x00000001U << (u1_a_REQ_SEL & (U1)WCHIME_REQ_TO_BIT_POS);
            u4_t_bit &= u4_ap_MDMSK[u1_t_pos];
            if(u4_t_bit != (U4)0U){
                u1_t_sw_chk |= (U1)WCHIME_REQ_SWC_OPEMD;
            }
        }
        else{
            u1_t_sw_chk |= (U1)WCHIME_REQ_SWC_OPEMD;
        }

        u1_t_chk = u1_t_sw_ctrl & (U1)WCHIME_REQ_SWC_PRI_HI;
        if(u1_a_REQ_NEXT < u1_g_WCHIME_NUM_REQ){
            u1_t_pos      = u1_a_REQ_NEXT >> (U1)WCHIME_REQ_TO_BUF_IDX;
            u4_t_bit      = (U4)0x00000001U << (u1_a_REQ_NEXT & (U1)WCHIME_REQ_TO_BIT_POS);
            u4_t_bit     &= u4_gp_WCHIME_REQBIT_PRIFREE[u1_t_pos];
            u1_t_sw_ctrl  = u1_g_wChimeReqSwCtrl(u1_a_REQ_NEXT);
        }
        else{
            u4_t_bit     = (U4)0U;
            u1_t_sw_ctrl = (U1)0U;
        }
        u1_t_chk_next = u1_t_sw_ctrl & (U1)WCHIME_REQ_SWC_PRI_HI_CNCL;
        if(((u1_t_chk      == (U1)0U      )  &&
            (u1_t_chk_next == (U1)0U      )) ||
           ((u1_a_REQ_NEXT >= u1_a_REQ_SEL)  &&
            (u4_t_bit      == (U4)0U      ))){
            u1_t_sw_chk |= (U1)WCHIME_REQ_SWC_PRI_HI;
        }
        u1_t_chk = u1_g_wChimeCfgIntermSplCnd(u1_a_REQ_SEL, u1_a_REQ_NEXT);
        if(u1_t_chk == (U1)TRUE){
            u1_t_sw_chk |= (U1)WCHIME_REQ_SWC_PRI_HI;
        }

        if(u1_t_sw_chk != u1_s_WCHIME_STSCHK_SW_DIS){
            u1_t_stschk |= (U1)WCHIME_STSCHK_REQSW_ENA;
        }
    }

    u1_t_chk = u1_g_wChimeCfgSwWaitInsert(u1_a_BFRWAIT_SEL, u1_a_REQ_NEXT, u2p_a_wait_time);
    if(u1_t_chk == (U1)TRUE){
        u1_t_stschk |= (U1)WCHIME_STSCHK_SW_WAIT;
    }

    return(u1_t_stschk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeReqSelUpdt(const U1 u1_a_STSCHK, const U1 u1_a_REQ_NEXT, ST_WCHIME_ARB_CH * st_ap_ch)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeReqSelUpdt(const U1 u1_a_STSCHK, const U1 u1_a_REQ_NEXT, ST_WCHIME_ARB_CH * st_ap_ch)
{
    static const U1       u1_sp_WCHIME_ARB_STM[] = {
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_TO_SW_WAIT, (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_TO_SW_WAIT, (U1)WCHIME_ARB_ACT_TO_NOT_SEL, (U1)WCHIME_ARB_ACT_TO_NOT_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_TO_SW_WAIT, (U1)WCHIME_ARB_ACT_SW_WAIT,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_REQ_SEL,    (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_TO_REQ_SEL,
        (U1)WCHIME_ARB_ACT_TO_SW_WAIT, (U1)WCHIME_ARB_ACT_TO_REQ_SEL, (U1)WCHIME_ARB_ACT_TO_REQ_SEL
    };

    U4                    u4_t_bit;
    U2                    u2_t_idx;
    U1                    u1_t_act;
    U1                    u1_t_pos;

    if(st_ap_ch->u1_arb < (U1)WCHIME_ARB_NUM_STS){
        u2_t_idx = ((U2)u1_a_STSCHK * (U2)WCHIME_ARB_NUM_STS) + (U2)st_ap_ch->u1_arb;
        u1_t_act = u1_sp_WCHIME_ARB_STM[u2_t_idx];
    }
    else{
        u1_t_act = (U1)WCHIME_ARB_ACT_TO_NOT_SEL;
    }

    switch(u1_t_act){
        case (U1)WCHIME_ARB_ACT_TO_REQ_SEL:
            st_ap_ch->u2_tmelpsd     = (U2)U2_MAX;
            st_ap_ch->u1_arb         = (U1)WCHIME_ARB_REQ_SEL;
            st_ap_ch->u1_req_vol     = u1_g_wChimeCfgVolGet(u1_a_REQ_NEXT);
            st_ap_ch->u1_req_sel     = u1_a_REQ_NEXT;
            st_ap_ch->u1_bfrwait_sel = u1_a_REQ_NEXT;
            st_ap_ch->u1_req_mm      = u1_a_REQ_NEXT;

            u4_t_bit = (U4)0x00000001U << (u1_a_REQ_NEXT & (U1)WCHIME_REQ_TO_BIT_POS);
            u1_t_pos = u1_a_REQ_NEXT >> WCHIME_REQ_TO_BUF_IDX;
            u4_gp_wchime_evtbit[u1_t_pos] &= ((U4)U4_MAX ^ u4_t_bit);
            break;
        case (U1)WCHIME_ARB_ACT_REQ_SEL:
            st_ap_ch->u2_tmelpsd = (U2)U2_MAX;
            st_ap_ch->u1_arb     = (U1)WCHIME_ARB_REQ_SEL;
            st_ap_ch->u1_req_vol = u1_g_wChimeCfgVolGet(st_ap_ch->u1_req_sel);
            break;
        case (U1)WCHIME_ARB_ACT_TO_SW_WAIT:
            st_ap_ch->u2_tmelpsd = (U2)0U;
            st_ap_ch->u1_arb     = (U1)WCHIME_ARB_SW_WAIT;
            st_ap_ch->u1_req_vol = (U1)U1_MAX;
            st_ap_ch->u1_req_sel = (U1)U1_MAX;
            break;
        case (U1)WCHIME_ARB_ACT_SW_WAIT:
            st_ap_ch->u1_arb     = (U1)WCHIME_ARB_SW_WAIT;
            st_ap_ch->u1_req_mm  = u1_a_REQ_NEXT;
            break;
     /* case (U1)WCHIME_ARB_ACT_TO_NOT_SEL: */
        default:
            st_ap_ch->u2_tmelpsd     = (U2)U2_MAX;
            st_ap_ch->u1_arb         = (U1)WCHIME_ARB_NOT_SEL;
            st_ap_ch->u1_req_vol     = (U1)U1_MAX;
            st_ap_ch->u1_req_sel     = (U1)U1_MAX;
            st_ap_ch->u1_bfrwait_sel = (U1)U1_MAX;
            st_ap_ch->u1_req_mm      = (U1)U1_MAX;
            break;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeReqmaskUpdt(U4 * u4_ap_selmsk, const U4 * u4_ap_CHBIT, const U1 u1_a_REQ_SEL)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeReqmaskUpdt(U4 * u4_ap_selmsk, const U4 * u4_ap_CHBIT, const U1 u1_a_REQ_SEL)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_pos_sel;
    U4                    u4_t_bit_sel;
    U4                    u4_t_pos_mask;
    U4                    u4_t_bit_mask;
    U1                    u1_t_req_hi;

    U1                    u1_t_sw_ctrl;

    if(u1_a_REQ_SEL < u1_g_WCHIME_NUM_REQ){

        u4_t_pos_sel = (U4)u1_a_REQ_SEL >> WCHIME_REQ_TO_BUF_IDX;
        u4_t_bit_sel = (U4)u1_a_REQ_SEL & (U4)WCHIME_REQ_TO_BIT_POS;

        u1_t_sw_ctrl  = u1_g_wChimeReqSwCtrl(u1_a_REQ_SEL);
        u1_t_sw_ctrl &= (U1)WCHIME_REQ_SWC_SIN_RET;
        if(u1_t_sw_ctrl != (U1)0U){
            u4_t_pos_mask = u4_t_pos_sel;
            u4_t_bit_mask = (U4)U4_MAX >> ((U4)WCHIME_REQ_TO_BIT_POS - u4_t_bit_sel);
            /* The value of WCHIME_REQ_TO_BIT_POS is 0x1F(=31).                                                         */
            /* The value of u4_t_bit_sel is less than WCHIME_REQ_TO_BIT_POS,                                            */
            /* because u4_t_bit_sel is masked by WCHIME_REQ_TO_BIT_POS(=0x1F)                                           */
            /* Therefore (U4) WCHIME_REQ_TO_BIT_POS is greater than or equal to u4_t_bit_sel and cannot be negative.    */
        }
        else if(u1_a_REQ_SEL > (U1)0U){
            u1_t_req_hi   = u1_a_REQ_SEL - (U1)1U;
            u4_t_pos_mask = (U4)u1_t_req_hi >> WCHIME_REQ_TO_BUF_IDX;
            u4_t_bit_mask = (U4)U4_MAX >> ((U4)WCHIME_REQ_TO_BIT_POS - ((U4)u1_t_req_hi & (U4)WCHIME_REQ_TO_BIT_POS));
            /* The value of WCHIME_REQ_TO_BIT_POS is 0x1F(=31).                                                                      */
            /* The value of (U4)u1_t_req_hi & (U4)WCHIME_REQ_TO_BIT_POS is less than WCHIME_REQ_TO_BIT_POS,                          */
            /* because (U4)u1_t_req_hi & (U4)WCHIME_REQ_TO_BIT_POS is masked by WCHIME_REQ_TO_BIT_POS(=0x1F)                         */
            /* Therefore (U4) WCHIME_REQ_TO_BIT_POS is greater than or equal to (U4)u1_t_req_hi & (U4)WCHIME_REQ_TO_BIT_POS and cannot be negative.    */
        }
        else{
            u4_t_pos_mask = (U4)0U;
            u4_t_bit_mask = (U4)0x00000000U;
        }
        vd_s_wChimeEvtmskUpdt(u4_ap_selmsk, u4_ap_CHBIT, u4_t_pos_mask, u4_t_bit_mask);

        u4_t_bit_mask = ((U4)0x00000001U << u4_t_bit_sel) ^ (U4)U4_MAX;
        u4_ap_selmsk[u4_t_pos_sel] &= u4_t_bit_mask;
    }
    else{
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
            u4_t_bit_mask = (u4_ap_CHBIT[u4_t_lpcnt] & u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt]) & u4_ap_selmsk[u4_t_lpcnt];
            u4_gp_wchime_evtmsk[u4_t_lpcnt] |= u4_t_bit_mask;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeEvtmskUpdt(const U4 * u4_ap_SELMSK, const U4 * u4_ap_CHBIT, const U4 u4_a_POS, const U4 u4_a_MASK)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeEvtmskUpdt(const U4 * u4_ap_SELMSK, const U4 * u4_ap_CHBIT, const U4 u4_a_POS, const U4 u4_a_MASK)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_mask;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_REQBIT_NUM_WORD; u4_t_lpcnt++){
        u4_t_mask = u4_gp_WCHIME_REQBIT_PRIFREE[u4_t_lpcnt];
        if(u4_t_lpcnt < u4_a_POS){
            u4_t_mask |= u4_gp_WCHIME_REQBIT_SIN[u4_t_lpcnt];
        }
        u4_gp_wchime_evtmsk[u4_t_lpcnt] |= (u4_ap_CHBIT[u4_t_lpcnt] & u4_t_mask) & u4_ap_SELMSK[u4_t_lpcnt];
    }

    u4_t_mask  = (u4_ap_CHBIT[u4_a_POS] & u4_gp_WCHIME_REQBIT_SIN[u4_a_POS]) & u4_ap_SELMSK[u4_a_POS];
    u4_t_mask &= u4_a_MASK;
    u4_gp_wchime_evtmsk[u4_a_POS] |= u4_t_mask;
}
/*===================================================================================================================================*/
/*  static void    vd_s_wChimeMMInfo(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_wChimeMMInfo(void)
{
    /* Conversion table of BUZZER_LV value to inform to the multimedia device */
    static const U1       u1_sp_WCHIME_BUZ_LV_CNV_TBL[WCHIME_MM_BUZ_LV_NUM] = {
        (U1)WCHIME_MM_BUZ_LVOFF, /* For the Priority level other than Lv1-9 */
        (U1)WCHIME_MM_BUZ_LV1,   /* WCHIME_BUZ_LV1                          */
        (U1)WCHIME_MM_BUZ_LV2,   /* WCHIME_BUZ_LV2                          */
        (U1)WCHIME_MM_BUZ_LV3,   /* WCHIME_BUZ_LV3                          */
        (U1)WCHIME_MM_BUZ_LV4,   /* WCHIME_BUZ_LV4                          */
        (U1)WCHIME_MM_BUZ_LV5,   /* WCHIME_BUZ_LV5                          */
        (U1)WCHIME_MM_BUZ_LV6,   /* WCHIME_BUZ_LV6                          */
        (U1)WCHIME_MM_BUZ_LV7,   /* WCHIME_BUZ_LV7                          */
        (U1)WCHIME_MM_BUZ_LV8,   /* WCHIME_BUZ_LV8                          */
        (U1)WCHIME_MM_BUZ_LV9    /* WCHIME_BUZ_LV9                          */
    };

    const ST_WCHIME_MM_INFO *   stp_t_info;
    U4                          u4_t_lpcnt;
    U1                          u1_t_emg;
    U1                          u1_t_longtone;
    U1                          u1_t_highpri;

    u1_t_emg      = (U1)WCHIME_BUZ_EMOFF;
    u1_t_longtone = (U1)WCHIME_BUZ_SHORT;
    u1_t_highpri  = (U1)WCHIME_BUZ_LV0;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_WCHIME_NUM_CH; u4_t_lpcnt++){
        if(st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_mm < u1_g_WCHIME_NUM_REQ){
            stp_t_info = &st_gp_WCHIME_BUZ_OUTPUT_INFO[st_gp_wchime_arb_ch[u4_t_lpcnt].u1_req_mm];
            if(stp_t_info->u1_emergency == (U1)WCHIME_BUZ_EMON){
                u1_t_emg = (U1)WCHIME_BUZ_EMON;
            }

            if(stp_t_info->u1_length == (U1)WCHIME_BUZ_LONG){
                u1_t_longtone = (U1)WCHIME_BUZ_LONG;
            }

            if(stp_t_info->u1_level > u1_t_highpri){
                u1_t_highpri = (U1)stp_t_info->u1_level;
            }
        }
    }
    u1_s_wchime_emg      = u1_t_emg;
    u1_s_wchime_longtone = u1_t_longtone;
    u1_s_wchime_highpri  = u1_sp_WCHIME_BUZ_LV_CNV_TBL[u1_t_highpri];

}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 2/2018  TN       New.                                                                                               */
/*  1.1.0     3/27/2018  TN       QAC Function metrics was improved.                                                                 */
/*  1.2.0    11/19/2018  TN       Improvement : WCHIME_REQ_IDX_UPLMT was replaced with u1_g_WCHIME_NUM_REQ in order to prevent       */
/*                                potential out of bound array.                                                                      */
/*  1.3.0     3/31/2020  ToN      Apply 800B CV spec.                                                                                */
/*  1.4.0     7/21/2020  SK       Correct the QAC metrics(STMIF), and change how the playing volume is specified.                    */
/*                                Correct the silent duration control to meet the specification of APP buzzer.                       */
/*                                Correct the buzzer level setting for MM volume suppression.                                        */
/*  1.4.1    11/24/2020  TF       Correction to avoid the discard of the single shot buzzer request when previous buzzer             */
/*                                will be finished in the same cycle.                                                                */
/*  1.5.0    12/23/2020  YK       Add the function to judge whether to buzzer until the end of 1 cycle or not,                       */
/*                                depend on the buzzer condition.                                                                    */
/*                                Improvement : u1_gp_WCHIME_REQ_SW_CTRL[] -> u1_g_wChimeReqSwCtrl(...)                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    11/12/2024  GM       Add function call for special condition switching to high priority from intermittent buzzer items  */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * ToN  = Toshiharu Nagata, Denso Techno                                                                                          */
/*  * SK   = Sakae Kitamura, Denso Techno                                                                                            */
/*  * TF   = Tomohiro Furuichi, Denso Techno                                                                                         */
/*  * YK   = Yuki Kawai, Denso Techno                                                                                                */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * GM   = Glen Monteposo, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
