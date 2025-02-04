/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Eelectric Vehicle System Charging                                                                                                */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_C_MAJOR                      (1)
#define EVSCHG_C_MINOR                      (0)
#define EVSCHG_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "evschg_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVSCHG_C_MAJOR != EVSCHG_H_MAJOR) ||\
     (EVSCHG_C_MINOR != EVSCHG_H_MINOR) ||\
     (EVSCHG_C_PATCH != EVSCHG_H_PATCH))
#error "evschg.c and evschg.h : source and header files are inconsistent!"
#endif

#if ((EVSCHG_C_MAJOR != EVSCHG_CFG_H_MAJOR) ||\
     (EVSCHG_C_MINOR != EVSCHG_CFG_H_MINOR) ||\
     (EVSCHG_C_PATCH != EVSCHG_CFG_H_PATCH))
#error "evschg.c and evschg_cfg_private.h : source and parameter files are inconsistent!"
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
static  U2                          u2_sp_evschg_rx_value[EVSCHG_ID_RX_NUM];
static  ST_EVSCHG_TMCHG_SCHDINFO    st_sp_evschg_schdinfo[EVSCHG_TIMCHG_SCHDINFO_SIZE];

static  U4                          u4_s_evschg_hold_cnt[EVSCHG_ID_TX_NUM];
static  U2                          u2_s_evschg_reqtx[EVSCHG_ID_TX_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void                 vd_s_EvschgBonSchdInfoInit(void);
static void                 vd_s_EvschgRstwkSchdInfoInit(void);
static void                 vd_s_EvschgUpdateRx(ST_EVSCHG_SGNL * st_ap_rx_value);
static void                 vd_s_EvschgUpdateSchdInfo(ST_EVSCHG_SGNL * st_ap_schdinfo);
static void                 vd_s_EvschgInitRam(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2             u2_sp_EVSCHG_RX_INIT[EVSCHG_ID_RX_NUM] = {
/* TIMCHG-CSTD */
    (U2)EVSCHG_P_NCTYP_INIT,
    (U2)EVSCHG_P_NCWKD_INIT,
    (U2)EVSCHG_P_NCSTM_INIT,
    (U2)EVSCHG_P_NCFTM_INIT,
    (U2)EVSCHG_P_ADDDSP_INIT,
    (U2)EVSCHG_PCNOWDSP_INIT,
    (U2)EVSCHG_P_NCDSP_INIT,
    (U2)EVSCHG_P_TMPID_INIT,
    (U2)EVSCHG_P_TMPTYP_INIT,
    (U2)EVSCHG_P_TMPACD_INIT,
    (U2)EVSCHG_P_TMPACN_INIT,
    (U2)EVSCHG_P_TMPSTM_INIT,
    (U2)EVSCHG_P_TMPFTM_INIT,
    (U2)EVSCHG_P_TMPSWK_INIT,
    (U2)EVSCHG_P_TMPNWK_INIT,
    (U2)EVSCHG_PARK_S_INIT,
/* SWQUICHA-CSTD */
    (U2)EVSCHG_P_CURDSP_INIT,
    (U2)EVSCHG_P_CUR200_INIT,
    (U2)EVSCHG_P_CURSEL_INIT,
    (U2)EVSCHG_CBLC_AVA_INIT,
    (U2)EVSCHG_CBLOCKSU_INIT,
    (U2)EVSCHG_P_LMTDSP_INIT,
    (U2)EVSCHG_P_CURAVA_INIT,
    (U2)EVSCHG_P_CLCAVA_INIT,
    (U2)EVSCHG_P_LMTAVA_INIT,
    (U2)EVSCHG_P_LMTNOW_INIT,
    (U2)EVSCHG_P_LMTSEL_INIT,
    (U2)EVSCHG_P_DPWAVA_INIT,
    (U2)EVSCHG_P_DPW_INIT,
    (U2)EVSCHG_P_DPWSL0_INIT,
    (U2)EVSCHG_P_DPWSL1_INIT,
    (U2)EVSCHG_P_DPWSL2_INIT,
    (U2)EVSCHG_P_DPWSL3_INIT,
    (U2)EVSCHG_P_DPWSL4_INIT,
    (U2)EVSCHG_P_DPWSL5_INIT,
    (U2)EVSCHG_P_DPWSL6_INIT,
    (U2)EVSCHG_P_DPWSL7_INIT,
    (U2)EVSCHG_P_DPWSL8_INIT,
    (U2)EVSCHG_P_DPWSL9_INIT,
    (U2)EVSCHG_P_TMRAVA_INIT,
    (U2)EVSCHG_P_SLMAVA_INIT,
    (U2)EVSCHG_P_CURSL1_INIT,
    (U2)EVSCHG_P_CURSL2_INIT,
    (U2)EVSCHG_P_CURSL3_INIT,
    (U2)EVSCHG_P_CURSL4_INIT
};

static const U2             u2_sp_EVSCHG_SCHDSGNL_INIT[EVSCHG_TIMCHG_SCHDSGNL_NUM] = {
    (U2)EVSCHG_P_SETID_INIT,
    (U2)EVSCHG_P_SETON_INIT,
    (U2)EVSCHG_P_SETTYP_INIT,
    (U2)EVSCHG_P_SETSTM_INIT,
    (U2)EVSCHG_P_SETFTM_INIT,
    (U2)EVSCHG_P_SETWKD_INIT,
    (U2)EVSCHG_P_SETNXT_INIT
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void                        vd_g_EvschgBonInit(void)                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                        vd_g_EvschgBonInit(void)
{
    const ST_EVSCHG_RX *        stp_t_RX;
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_RX_NUM; u4_t_loop++) {
        stp_t_RX = &st_gp_EVSCHG_RX_CFG[u4_t_loop];

        u2_sp_evschg_rx_value[u4_t_loop] = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
        if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U1) {
            vd_g_Evschg_RimU1Write(stp_t_RX->u2_memoryid, (U1)u2_sp_EVSCHG_RX_INIT[u4_t_loop]);
        }
        else if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U2) {
            vd_g_Evschg_RimU2Write(stp_t_RX->u2_memoryid, u2_sp_EVSCHG_RX_INIT[u4_t_loop]);
        } 
        else{
            /* Do Nothing */
        }
    }

    vd_s_EvschgBonSchdInfoInit();
    vd_s_EvschgInitRam();

    vd_g_EvschgCfgBonInit();
    vd_g_EvschgCfgBonTxInit();
}

/*===================================================================================================================================*/
/*  void                        vd_g_EvschgRstwkInit(void)                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                        vd_g_EvschgRstwkInit(void)
{
    const ST_EVSCHG_RX *        stp_t_RX;
    U1                          u1_t_rimsts;
    U2                          u2_t_value;
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_RX_NUM; u4_t_loop++) {
        stp_t_RX = &st_gp_EVSCHG_RX_CFG[u4_t_loop];

        u2_t_value                       = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
        u2_sp_evschg_rx_value[u4_t_loop] = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
        if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U1) {
            u1_t_rimsts = u1_g_Evschg_RimU1Read(stp_t_RX->u2_memoryid, (U1*)&u2_t_value);
        }
        else if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U2) {
            u1_t_rimsts = u1_g_Evschg_RimU2Read(stp_t_RX->u2_memoryid, &u2_t_value);
        }
        else {
            u1_t_rimsts = (U1)RIM_RESULT_KIND_NG;
        }

        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) {
            u2_sp_evschg_rx_value[u4_t_loop] = u2_t_value;
        }
    }

    vd_s_EvschgRstwkSchdInfoInit();
    vd_s_EvschgInitRam();

    vd_g_EvschgCfgRstwkInit();
}

/*===================================================================================================================================*/
/*  void                        vd_g_EvschgMainTask(void)                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                        vd_g_EvschgMainTask(void)
{
    ST_EVSCHG_SGNL              st_tp_rx_value[EVSCHG_ID_RX_NUM];
    ST_EVSCHG_SGNL              st_tp_schdinfo[EVSCHG_TIMCHG_SCHDSGNL_NUM];
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_RX_NUM; u4_t_loop++) {
        st_tp_rx_value[u4_t_loop].u1_sts = (U1)EVSCHG_STSBIT_UNKNOWN;
        st_tp_rx_value[u4_t_loop].u2_sig = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_TIMCHG_SCHDSGNL_NUM; u4_t_loop++) {
        st_tp_schdinfo[u4_t_loop].u1_sts = (U1)EVSCHG_STSBIT_UNKNOWN;
        st_tp_schdinfo[u4_t_loop].u2_sig = u2_sp_EVSCHG_SCHDSGNL_INIT[u4_t_loop];
    }

    vd_g_EvschgCfgSgnlInst(&st_tp_rx_value[0], &st_tp_schdinfo[0]);

    vd_s_EvschgUpdateRx(&st_tp_rx_value[0]);
    vd_s_EvschgUpdateSchdInfo(&st_tp_schdinfo[0]);

    vd_g_EvschgCfgMainTask();
}

/*===================================================================================================================================*/
/*  U2                          u2_g_EvschgGetSignal(const U1 u1_a_EVSCHG_ID_RX)                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
U2                          u2_g_EvschgGetSignal(const U1 u1_a_EVSCHG_ID_RX)
{
    U2                          u2_t_ret;

    u2_t_ret = (U2)0U;
    if (u1_a_EVSCHG_ID_RX < (U1)EVSCHG_ID_RX_NUM) {
        u2_t_ret = u2_sp_evschg_rx_value[u1_a_EVSCHG_ID_RX];
    }

    return (u2_t_ret);
}

/*===================================================================================================================================*/
/*  ST_EVSCHG_TMCHG_SCHDINFO    st_g_EvschgGetSchdInfo(const U1 u1_a_SCHDINFO_ID)                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
ST_EVSCHG_TMCHG_SCHDINFO    st_g_EvschgGetSchdInfo(const U1 u1_a_SCHDINFO_ID)
{
    ST_EVSCHG_TMCHG_SCHDINFO    st_t_set;          /* Schedule data     */

    st_t_set.u1_id         = (U1)EVSCHG_P_SETID_INIT;
    st_t_set.u1_onoff      = (U1)EVSCHG_P_SETON_INIT;
    st_t_set.u1_type       = (U1)EVSCHG_P_SETTYP_INIT;
    st_t_set.u2_start_tim  = (U2)EVSCHG_P_SETSTM_INIT;
    st_t_set.u2_finish_tim = (U2)EVSCHG_P_SETFTM_INIT;
    st_t_set.u1_wkd_bit    = (U1)EVSCHG_P_SETWKD_INIT;
    st_t_set.u1_nxt_id     = (U1)EVSCHG_P_SETNXT_INIT;

    if (u1_a_SCHDINFO_ID < (U1)EVSCHG_TIMCHG_SCHDINFO_SIZE) {
        st_t_set.u1_id         = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u1_id;
        st_t_set.u1_onoff      = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u1_onoff;
        st_t_set.u1_type       = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u1_type;
        st_t_set.u2_start_tim  = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u2_start_tim;
        st_t_set.u2_finish_tim = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u2_finish_tim;
        st_t_set.u1_wkd_bit    = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u1_wkd_bit;
        st_t_set.u1_nxt_id     = st_sp_evschg_schdinfo[u1_a_SCHDINFO_ID].u1_nxt_id;
    }

    return (st_t_set);
}

/*===================================================================================================================================*/
/*  void                        vd_g_Evschg10msTask(void)                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                        vd_g_Evschg10msTask(void)
{
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_TX_NUM; u4_t_loop++) {
        if (u4_s_evschg_hold_cnt[u4_t_loop] >= (U4)EVSCHG_HOLD_TIME) {
            if (fp_gp_vd_EVSCHG_TX[u4_t_loop] != vdp_PTR_NA) {
                fp_gp_vd_EVSCHG_TX[u4_t_loop](u2_s_evschg_reqtx[u4_t_loop]);
            }
         }

        if (u4_s_evschg_hold_cnt[u4_t_loop] < (U4)U4_MAX){
            u4_s_evschg_hold_cnt[u4_t_loop]++;
        }
    }
}

/*===================================================================================================================================*/
/*  void                        vd_g_EvschgSendSignal(const U1 u1_a_ID, const U2 u2_a_RXDATA)                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                        vd_g_EvschgSendSignal(const U1 u1_a_ID, const U2 u2_a_RXDATA)
{
    if (u1_a_ID < (U1)EVSCHG_ID_TX_NUM){
        if (u2_a_RXDATA != u2_s_evschg_reqtx[u1_a_ID]){
            if (u4_s_evschg_hold_cnt[u1_a_ID] >= (U4)EVSCHG_HOLD_TIME) {
                if (fp_gp_vd_EVSCHG_TX[u1_a_ID] != vdp_PTR_NA) {
                    fp_gp_vd_EVSCHG_TX[u1_a_ID](u2_a_RXDATA);
                    u4_s_evschg_hold_cnt[u1_a_ID] = (U4)0U;
                }
            }
        }
        u2_s_evschg_reqtx[u1_a_ID] = u2_a_RXDATA;
    }
}

/*===================================================================================================================================*/
/*  static void                 vd_s_EvschgBonSchdInfoInit(void)                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void                 vd_s_EvschgBonSchdInfoInit(void)
{
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_TIMCHG_SCHDINFO_SIZE; u4_t_loop++) {
        st_sp_evschg_schdinfo[u4_t_loop].u1_id         = (U1)EVSCHG_P_SETID_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u1_onoff      = (U1)EVSCHG_P_SETON_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u1_type       = (U1)EVSCHG_P_SETTYP_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u2_start_tim  = (U2)EVSCHG_P_SETSTM_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u2_finish_tim = (U2)EVSCHG_P_SETFTM_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u1_wkd_bit    = (U1)EVSCHG_P_SETWKD_INIT;
        st_sp_evschg_schdinfo[u4_t_loop].u1_nxt_id     = (U1)EVSCHG_P_SETNXT_INIT;

        vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETID[u4_t_loop],  (U1)EVSCHG_P_SETID_INIT );
        vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETON[u4_t_loop],  (U1)EVSCHG_P_SETON_INIT );
        vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETTYP[u4_t_loop], (U1)EVSCHG_P_SETTYP_INIT);
        vd_g_Evschg_RimU2Write(u2_gp_EVSCHG_RIMID_P_SETSTM[u4_t_loop], (U2)EVSCHG_P_SETSTM_INIT);
        vd_g_Evschg_RimU2Write(u2_gp_EVSCHG_RIMID_P_SETFTM[u4_t_loop], (U2)EVSCHG_P_SETFTM_INIT);
        vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETWKD[u4_t_loop], (U1)EVSCHG_P_SETWKD_INIT);
        vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETNXT[u4_t_loop], (U1)EVSCHG_P_SETNXT_INIT);
    }
}

/*===================================================================================================================================*/
/*  static void                 vd_s_EvschgRstwkSchdInfoInit(void)                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void                 vd_s_EvschgRstwkSchdInfoInit(void)
{
    U1                          u1_t_rimsts;
    U2                          u2_t_value;
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_TIMCHG_SCHDINFO_SIZE; u4_t_loop++) {
        u2_t_value = (U2)EVSCHG_P_SETID_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU1Read(u2_gp_EVSCHG_RIMID_P_SETID[u4_t_loop],  (U1*)&u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETID_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u1_id = (U1)u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETON_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU1Read(u2_gp_EVSCHG_RIMID_P_SETON[u4_t_loop],  (U1*)&u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETON_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u1_onoff = (U1)u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETTYP_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU1Read(u2_gp_EVSCHG_RIMID_P_SETTYP[u4_t_loop], (U1*)&u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETTYP_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u1_type = (U1)u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETSTM_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU2Read(u2_gp_EVSCHG_RIMID_P_SETSTM[u4_t_loop], &u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETSTM_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u2_start_tim = u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETFTM_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU2Read(u2_gp_EVSCHG_RIMID_P_SETFTM[u4_t_loop], &u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETFTM_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u2_finish_tim = u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETWKD_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU1Read(u2_gp_EVSCHG_RIMID_P_SETWKD[u4_t_loop], (U1*)&u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETWKD_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u1_wkd_bit = (U1)u2_t_value;

        u2_t_value = (U2)EVSCHG_P_SETNXT_INIT;
        u1_t_rimsts = u1_g_Evschg_RimU1Read(u2_gp_EVSCHG_RIMID_P_SETNXT[u4_t_loop], (U1*)&u2_t_value);
        if ((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK) {
            u2_t_value = (U2)EVSCHG_P_SETNXT_INIT;
        }
        st_sp_evschg_schdinfo[u4_t_loop].u1_nxt_id = (U1)u2_t_value;
    }
}

/*===================================================================================================================================*/
/*  static void                 vd_s_EvschgUpdateRx(ST_EVSCHG_SGNL * st_ap_rx_value)                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void                 vd_s_EvschgUpdateRx(ST_EVSCHG_SGNL * st_ap_rx_value)
{
    U2                          u2_t_value;
    U4                          u4_t_loop;
    const ST_EVSCHG_RX *        stp_t_RX;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_RX_NUM; u4_t_loop++) {
        stp_t_RX = &st_gp_EVSCHG_RX_CFG[u4_t_loop];

        if (st_ap_rx_value[u4_t_loop].u1_sts == (U1)EVSCHG_STSBIT_VALID){
            if (st_ap_rx_value[u4_t_loop].u2_sig != u2_sp_evschg_rx_value[u4_t_loop]) {
                if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U1) {
                    vd_g_Evschg_RimU1Write(stp_t_RX->u2_memoryid, (U1)st_ap_rx_value[u4_t_loop].u2_sig);
                    u2_sp_evschg_rx_value[u4_t_loop] = st_ap_rx_value[u4_t_loop].u2_sig;
                }
                else if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U2) {
                    vd_g_Evschg_RimU2Write(stp_t_RX->u2_memoryid, st_ap_rx_value[u4_t_loop].u2_sig);
                    u2_sp_evschg_rx_value[u4_t_loop] = st_ap_rx_value[u4_t_loop].u2_sig;
                }
                else{
                    /* Do Nothing */
                }
            }
        }
        else if((st_ap_rx_value[u4_t_loop].u1_sts & (U1)EVSCHG_STSBIT_INVALID) != (U1)0U) {
            if (stp_t_RX->u1_on_tout == (U1)EVSCHG_TOUT_INIT) {
                if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U1) {
                    vd_g_Evschg_RimU1Write(stp_t_RX->u2_memoryid, (U1)u2_sp_EVSCHG_RX_INIT[u4_t_loop]);
                    u2_sp_evschg_rx_value[u4_t_loop] = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
                }
                else if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U2) {
                    vd_g_Evschg_RimU2Write(stp_t_RX->u2_memoryid, u2_sp_EVSCHG_RX_INIT[u4_t_loop]);
                    u2_sp_evschg_rx_value[u4_t_loop] = u2_sp_EVSCHG_RX_INIT[u4_t_loop];
                }
                else{
                    /* Do Nothing */
                }
            }
            else if (stp_t_RX->u1_on_tout == (U1)EVSCHG_TOUT_SP) {
                u2_t_value = u2_g_EvschgCfgToutSp(u4_t_loop, u2_sp_evschg_rx_value[u4_t_loop]);

                if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U1) {
                    vd_g_Evschg_RimU1Write(stp_t_RX->u2_memoryid, (U1)u2_t_value);
                    u2_sp_evschg_rx_value[u4_t_loop] = u2_t_value;
                }
                else if (stp_t_RX->u1_rimsize == (U1)EVSCHG_RIMSIZE_U2) {
                    vd_g_Evschg_RimU2Write(stp_t_RX->u2_memoryid, u2_t_value);
                    u2_sp_evschg_rx_value[u4_t_loop] = u2_t_value;
                }
                else{
                    /* Do Nothing */
                }
            }
            else {
                /* HOLD */
            }
        }
        else {
            /* Do Nothing*/
        }
    }
}

/*===================================================================================================================================*/
/*  static void                 vd_s_EvschgUpdateSchdInfo(ST_EVSCHG_SGNL * st_ap_schdinfo)                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void                 vd_s_EvschgUpdateSchdInfo(ST_EVSCHG_SGNL * st_ap_schdinfo)
{
    U1                          u1_t_msgsts;
    U2                          u2_t_setid;

    u1_t_msgsts = st_ap_schdinfo[EVSCHG_ID_P_SETID].u1_sts;
    u2_t_setid  = st_ap_schdinfo[EVSCHG_ID_P_SETID].u2_sig;

    if (u1_t_msgsts == (U1)EVSCHG_STSBIT_VALID) {
        if (u2_t_setid < (U2)EVSCHG_TIMCHG_SCHDINFO_SIZE) {
            st_sp_evschg_schdinfo[u2_t_setid].u1_id         = (U1)st_ap_schdinfo[EVSCHG_ID_P_SETID].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u1_onoff      = (U1)st_ap_schdinfo[EVSCHG_ID_P_SETON].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u1_type       = (U1)st_ap_schdinfo[EVSCHG_ID_P_SETTYP].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u2_start_tim  = (U2)st_ap_schdinfo[EVSCHG_ID_P_SETSTM].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u2_finish_tim = (U2)st_ap_schdinfo[EVSCHG_ID_P_SETFTM].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u1_wkd_bit    = (U1)st_ap_schdinfo[EVSCHG_ID_P_SETWKD].u2_sig;
            st_sp_evschg_schdinfo[u2_t_setid].u1_nxt_id     = (U1)st_ap_schdinfo[EVSCHG_ID_P_SETNXT].u2_sig;

            vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETID[u2_t_setid],  (U1)st_ap_schdinfo[EVSCHG_ID_P_SETID].u2_sig );
            vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETON[u2_t_setid],  (U1)st_ap_schdinfo[EVSCHG_ID_P_SETON].u2_sig );
            vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETTYP[u2_t_setid], (U1)st_ap_schdinfo[EVSCHG_ID_P_SETTYP].u2_sig);
            vd_g_Evschg_RimU2Write(u2_gp_EVSCHG_RIMID_P_SETSTM[u2_t_setid], (U2)st_ap_schdinfo[EVSCHG_ID_P_SETSTM].u2_sig);
            vd_g_Evschg_RimU2Write(u2_gp_EVSCHG_RIMID_P_SETFTM[u2_t_setid], (U2)st_ap_schdinfo[EVSCHG_ID_P_SETFTM].u2_sig);
            vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETWKD[u2_t_setid], (U1)st_ap_schdinfo[EVSCHG_ID_P_SETWKD].u2_sig);
            vd_g_Evschg_RimU1Write(u2_gp_EVSCHG_RIMID_P_SETNXT[u2_t_setid], (U1)st_ap_schdinfo[EVSCHG_ID_P_SETNXT].u2_sig);
        }
    }
}

/*===================================================================================================================================*/
/*  static void                        vd_s_EvschgInitRam(void)                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void                 vd_s_EvschgInitRam(void)
{
    static const   U2           u2_sp_EVSCHG_TX_INIT[EVSCHG_ID_TX_NUM] = {
        (U2)EVSCHG_M_SETACN_INIT,
        (U2)EVSCHG_M_SETSTM_INIT,
        (U2)EVSCHG_M_SETFTM_INIT
    };
    U4                          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)EVSCHG_ID_TX_NUM; u4_t_loop++) {
        u4_s_evschg_hold_cnt[u4_t_loop] = (U4)U4_MAX;
        u2_s_evschg_reqtx[u4_t_loop]    = u2_sp_EVSCHG_TX_INIT[u4_t_loop];
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  ---------------------------------------------------------------------------------------------*/
/*  1.0.0           2022.11.15  ToK     New                                                                                          */
/*                                                                                                                                   */
/*  * ToK = Toru Kamishina, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
