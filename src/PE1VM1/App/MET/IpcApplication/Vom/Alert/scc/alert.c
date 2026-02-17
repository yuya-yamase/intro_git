/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert                                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_MAJOR                            (5)
#define ALERT_C_MINOR                            (7)
#define ALERT_C_PATCH                            (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "veh_opemd.h"
#include "oxcan.h"

#include "mtrxsrch.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ALERT_C_MAJOR != ALERT_H_MAJOR) || \
     (ALERT_C_MINOR != ALERT_H_MINOR) || \
     (ALERT_C_PATCH != ALERT_H_PATCH))
#error "alert.c and alert.h : source and header files are inconsistent!"
#endif

#if ((ALERT_C_MAJOR != ALERT_CFG_H_MAJOR) || \
     (ALERT_C_MINOR != ALERT_CFG_H_MINOR) || \
     (ALERT_C_PATCH != ALERT_CFG_H_PATCH))
#error "alert.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Package Version Check                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  VOM Index Check                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ALERT_VOM_BAT_AO     != 0x01U) || \
     (ALERT_VOM_BAT_WT     != 0x02U) || \
     (ALERT_VOM_IGN_OFF    != 0x04U) || \
     (ALERT_VOM_IGN_OFF_WT != 0x08U) || \
     (ALERT_VOM_IGN_ON     != 0x10U) || \
     (ALERT_VOM_VDC_ON     != 0x20U) || \
     (ALERT_VOM_RWT_EN     != 0x80U))
#error "alert.h or alert_cfg_private.h : VOM Index is updated!"
#endif


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_TO_TM_MAX                          (0xfffffffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                         u1_req;                            /* ALERT_REQ_XXXXX. see alert_mtrx.h                               */
    U1                         u1_vom;                            /* ALERT_VOM_XXXXX.                                                */
}ST_ALERT_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_ALERT_CH  st_sp_alert_ch[ALERT_NUM_CH];
static U4           u4_s_alert_ign_tm_elpsd;
static U4           u4_s_alert_bslp_tm_elpsd;
static U1           u1_s_alert_vom_chk;

static U2           u2_s_alert_task_idx;
static U1           u1_s_alert_task_slot;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1           u1_s_AlertVomchk(void);
static U1           u1_s_AlertToutchk(void);
static U1           u1_s_AlertPowerChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertInit(void)
{
    U4                       u4_t_lpcnt;

    u4_s_alert_ign_tm_elpsd                = (U4)ALERT_IGN_TM_MAX;
    u4_s_alert_bslp_tm_elpsd               = (U4)U4_MAX;

    u1_s_alert_vom_chk                     = (U1)ALERT_VOM_BAT_AO;

    u2_s_alert_task_idx                    = (U2)U2_MAX;
    u1_s_alert_task_slot                   = (U1)U1_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ALERT_NUM_CH; u4_t_lpcnt++){
        st_sp_alert_ch[u4_t_lpcnt].u1_req  = (U1)ALERT_REQ_UNKNOWN;
        st_sp_alert_ch[u4_t_lpcnt].u1_vom  = (U1)0U;
    }

    vd_g_AlertMtrxInit();
    vd_g_AlertCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U4                       u4_t_evt;
    U1                       u1_t_vom_chk;

    u1_t_vom_chk = u1_s_AlertPowerChk();
    u4_t_evt     = u4_a_EVTBIT & ((U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF | (U4)VEH_OPEMD_EVBIT_IG_R_TO_ON);
    if(u4_t_evt == (U4)VEH_OPEMD_EVBIT_IG_R_TO_ON){
        u4_s_alert_ign_tm_elpsd  = (U4)U4_MAX;
        u1_t_vom_chk            |= (U1)ALERT_VOM_BAT_WT;
    }
    else if(u4_t_evt == (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF){
        u4_s_alert_ign_tm_elpsd  = (U4)U4_MAX;
        u4_s_alert_bslp_tm_elpsd = (U4)U4_MAX;
        u1_t_vom_chk            |= ((U1)ALERT_VOM_BAT_WT | (U1)ALERT_VOM_IGN_OFF_WT);
    }
    else{
        u1_t_vom_chk            |= (u1_s_alert_vom_chk & ((U1)ALERT_VOM_BAT_WT | (U1)ALERT_VOM_IGN_OFF_WT));
    }

    u1_s_alert_vom_chk = u1_t_vom_chk;
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertMainTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertMainTask(void)
{
    const ST_ALERT_MTRX *             st_tp_MTRX;
    const U1 *                        u1_tp_DST;

    ST_MTRX_SRCH                      st_t_srch;

    U4                                u4_t_lpcnt;
    U4                                u4_t_src_vom;
    U4                                u4_t_src_chk;
    U4                                u4_t_ch;
    U4                                u4_t_num_mtrx;

    U1                                u1_t_vom_chk;
    U1                                u1_t_dst;

    u1_t_vom_chk    = u1_s_AlertVomchk();

    vd_g_AlertCfgMainStart(u1_t_vom_chk);

    if((u1_s_alert_task_slot >= (U1)ALERT_TASK_NUM_SLOT) ||
       (u2_s_alert_task_idx  >= u2_g_ALERT_NUM_TASK    )){

        u1_s_alert_task_slot = (U1)0U;
        u2_s_alert_task_idx  = (U2)0U;
    }

    u4_t_src_vom = ((U4)u1_t_vom_chk << ALERT_SRC_CHK_LSB_VOM);
    while((u2_s_alert_task_idx                               <  u2_g_ALERT_NUM_TASK) &&
          (st_gp_ALERT_TASK_CFG[u2_s_alert_task_idx].u1_slot == u1_s_alert_task_slot)){

        st_tp_MTRX    = st_gp_ALERT_TASK_CFG[u2_s_alert_task_idx].stp_MTRX;
        u4_t_ch       = (U4)st_gp_ALERT_TASK_CFG[u2_s_alert_task_idx].u2_ch_begin;
        u4_t_num_mtrx = (U4)st_gp_ALERT_TASK_CFG[u2_s_alert_task_idx].u1_num_mtrx;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_mtrx; u4_t_lpcnt++){

            u4_t_src_chk  = (st_tp_MTRX[u4_t_lpcnt].fp_u4_SRC_CHK)(u1_t_vom_chk,
                                                                   u4_s_alert_ign_tm_elpsd,
                                                                   st_sp_alert_ch[u4_t_ch].u1_req);
            u4_t_src_chk &= (U4)ALERT_SRC_CHK_MAX;

            st_t_srch.u4p_MASK    = st_tp_MTRX[u4_t_lpcnt].u4p_SRC_MASK;
            st_t_srch.u4p_CRIT    = st_tp_MTRX[u4_t_lpcnt].u4p_SRC_CRIT;
            st_t_srch.u2_len_inst = (U2)1U;
            st_t_srch.u2_num_srch = st_tp_MTRX[u4_t_lpcnt].u2_num_dst;

            if((st_t_srch.u4p_MASK    != (const U4 *)vdp_PTR_NA) &&
               (st_t_srch.u4p_CRIT    != (const U4 *)vdp_PTR_NA) &&
               (st_t_srch.u2_num_srch >  (U2)0U                )){

                u4_t_src_chk |= u4_t_src_vom;
                u4_t_src_chk  = (U4)u2_g_MtrxSrch((U2)0U, &u4_t_src_chk, &st_t_srch);
            }

            u1_tp_DST = st_tp_MTRX[u4_t_lpcnt].u1p_DST;
            if(u4_t_src_chk >= (U4)st_t_srch.u2_num_srch){
                u1_t_dst = (U1)ALERT_REQ_UNKNOWN;
            }
            else if(u1_tp_DST != (const U1 *)vdp_PTR_NA){
                u1_t_dst = u1_tp_DST[u4_t_src_chk];
            }
            else if(u4_t_src_chk < (U4)ALERT_REQ_UNKNOWN){
                u1_t_dst = (U1)u4_t_src_chk;
            }
            else{
                u1_t_dst = (U1)ALERT_REQ_UNKNOWN;
            }

            st_sp_alert_ch[u4_t_ch].u1_req  = u1_t_dst;
            st_sp_alert_ch[u4_t_ch].u1_vom  = st_tp_MTRX[u4_t_lpcnt].u1_vom_act;

            if(st_tp_MTRX[u4_t_lpcnt].fp_vd_XDST != vdp_PTR_NA){
                (st_tp_MTRX[u4_t_lpcnt].fp_vd_XDST)(u1_t_vom_chk,
                                                    u4_s_alert_ign_tm_elpsd,
                                                    u1_t_dst);
            }

            u4_t_ch++;
        }

        u2_s_alert_task_idx++;
    }

    u1_s_alert_task_slot++;

    vd_g_AlertCfgMainFinish();
}
/*===================================================================================================================================*/
/*  U1      u1_g_AlertReqByCh(const U2 u2_a_CH)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AlertReqByCh(const U2 u2_a_CH)
{
    U1                       u1_t_act;
    U1                       u1_t_req;

    u1_t_req = (U1)ALERT_REQ_UNKNOWN;
    if(u2_a_CH < (U2)ALERT_NUM_CH){

        u1_t_act = u1_s_alert_vom_chk & st_sp_alert_ch[u2_a_CH].u1_vom;
        if(u1_t_act != (U1)0U){
            u1_t_req = st_sp_alert_ch[u2_a_CH].u1_req;
        }
    }

    return(u1_t_req);
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertReqToBit(const ST_ALERT_REQBIT * st_ap_REQBIT, const U2 u2_a_NUM_REQBIT,                                       */
/*                             U4 * u4_ap_reqbit, const U1 u1_a_NUM_WORD)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertReqToBit(const ST_ALERT_REQBIT * st_ap_REQBIT, const U2 u2_a_NUM_REQBIT,
                           U4 * u4_ap_reqbit, const U1 u1_a_NUM_WORD)
{
    U4                       u4_t_lpcnt;
    U2                       u2_t_src_ch;

    U1                       u1_t_dst_idx;

    U1                       u1_t_act;
    U1                       u1_t_req;
    U1                       u1_t_vom;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_a_NUM_REQBIT; u4_t_lpcnt++){

        u2_t_src_ch  = st_ap_REQBIT[u4_t_lpcnt].u2_src_ch;
        u1_t_dst_idx = st_ap_REQBIT[u4_t_lpcnt].u1_dst_idx;
        if((u2_t_src_ch  < (U2)ALERT_NUM_CH) &&
           (u1_t_dst_idx < u1_a_NUM_WORD    )){

            u1_t_act = st_ap_REQBIT[u4_t_lpcnt].u1_src_act;
            u1_t_req = st_sp_alert_ch[u2_t_src_ch].u1_req;
            u1_t_vom = u1_s_alert_vom_chk & st_sp_alert_ch[u2_t_src_ch].u1_vom;
            if((u1_t_req == u1_t_act) &&
               (u1_t_vom != (U1)0U)){
                u4_ap_reqbit[u1_t_dst_idx] |= st_ap_REQBIT[u4_t_lpcnt].u4_dst_bit;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_AlertVomchk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertVomchk(void)
{
    U1                       u1_t_vom_chk;
    U1                       u1_t_ign_on;

    if(u4_s_alert_ign_tm_elpsd >= (U4)U4_MAX){
        u4_s_alert_ign_tm_elpsd = (U4)0U;
    }
    else if(u4_s_alert_ign_tm_elpsd >= (U4)ALERT_IGN_TM_MAX){
        u4_s_alert_ign_tm_elpsd = (U4)ALERT_IGN_TM_MAX;
    }
    else{
        u4_s_alert_ign_tm_elpsd++;
    }

    u1_t_vom_chk = u1_s_AlertPowerChk();
    u1_t_ign_on  = u1_t_vom_chk & (U1)ALERT_VOM_IGN_ON;
    if(u1_t_ign_on != (U1)0U){

        u4_s_alert_bslp_tm_elpsd = (U4)U4_MAX;
        u1_t_vom_chk            |= (U1)ALERT_VOM_BAT_WT;
    }
    else{

        u1_t_vom_chk            |= u1_s_AlertToutchk();
    }

    u1_s_alert_vom_chk = u1_t_vom_chk;

    return(u1_t_vom_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_AlertToutchk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertToutchk(void)
{
    U1                       u1_t_chk;
    U4                       u4_t_wk;

    u4_t_wk = u4_g_oXCANSysActvtd() & u4_g_ALERT_BUS_CH_MSK;
    if(u4_t_wk != (U4)0U){
        u4_s_alert_bslp_tm_elpsd = (U4)U4_MAX;
    }
    else if(u4_s_alert_bslp_tm_elpsd >= (U4)U4_MAX){
        u4_s_alert_bslp_tm_elpsd = (U4)0U;
    }
    else if(u4_s_alert_bslp_tm_elpsd >= (U4)ALERT_TO_TM_MAX){
        u4_s_alert_bslp_tm_elpsd = (U4)ALERT_TO_TM_MAX;
    }
    else{
        u4_s_alert_bslp_tm_elpsd++;
    }

    if((u4_s_alert_bslp_tm_elpsd >= u4_g_ALERT_IGN_OFF_TOUT) &&
       (u4_s_alert_bslp_tm_elpsd <  (U4)U4_MAX             )){
        u1_t_chk = (U1)0U;
    }
    else{
        u1_t_chk = ((U1)ALERT_VOM_BAT_WT | (U1)ALERT_VOM_IGN_OFF_WT);
    }

    return(u1_t_chk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_AlertGetReqSlot(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_alert_task_slot                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_AlertGetReqSlot(void)
{
    return(u1_s_alert_task_slot);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_AlertPowerChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_vom_chk                                                                                                     */
/*===================================================================================================================================*/
static U1      u1_s_AlertPowerChk(void)
{
    U1          u1_t_igr_on;
    U1          u1_t_vom_chk;

    u1_t_vom_chk = (U1)ALERT_VOM_BAT_AO;

    u1_t_igr_on = u1_g_VehopemdIgnOn();
    if (u1_t_igr_on == (U1)TRUE) {
        u1_t_vom_chk |= ((U1)ALERT_VOM_IGN_ON | (U1)ALERT_VOM_VDC_ON);
        /* Attention: VDC_OFF during IGN_ON is not supported. */
    }
    else {
        u1_t_vom_chk |= (U1)ALERT_VOM_IGN_OFF;
    }

    return(u1_t_vom_chk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/ 5/2019  TN       New.                                                                                               */
/*  5.1.0     3/26/2019  TN       u1_g_AlertReqByVehopemd was implemented.                                                           */
/*  5.2.0     4/17/2019  YI       u1_s_AlertToutchk was implemented.                                                                 */
/*  5.3.0     5/10/2019  YI       alert.c compile timing was changed to lib_alert build.                                             */
/*  5.4.0     9/20/2019  YI       u1_g_AlertReqByVehopemd was updated.                                                               */
/*  5.5.0    10/31/2019  DS       u1_g_AlertReqByVehopemd was removed.                                                               */
/*  5.6.0     6/30/2025  SF       BSW Update:u1_s_AlertToutchk was modified for Toyota BEVStep3.                                     */
/*  5.7.0     1/28/2026  TH(K)    Change for BEV Full_function_2                               .                                     */
/*                                Delete u1_s_AlertJudgeStartEngine                                                                  */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/*  19PFv3-1 08/06/2024  TH       Add function(u1_g_AlertGetReqSlot).                                                                */
/*  19PFv3-2 11/04/2024  HY       Renaming ipc_tycan.h -> ipc_mainline.h                                                             */
/*  19PFv3-3 12/24/2024  SN       Add function(u1_s_AlertJudgeStartEngine).                                                          */
/*  BEV-1    10/30/2025  SH       Configured for BEVstep3_Rebase                                                                     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * HY   = Hiroki You, Denso Techno                                                                                                */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * SF   = Seiya Fukutome, Denso Techno                                                                                            */
/*  * TH(K)= Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
