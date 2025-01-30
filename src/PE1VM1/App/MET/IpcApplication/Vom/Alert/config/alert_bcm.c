/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert Bulb Check Mask                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_BCM_C_MAJOR                        (5)
#define ALERT_BCM_C_MINOR                        (5)
#define ALERT_BCM_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_bcm.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "iohw_diflt.h"
#if 0   /* BEV BSW provisionally */
#else
#include "iohw_adc_channel_STUB.h"
#include "iohw_diflt_sgnl_STUB.h"
#endif
#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ALERT_BCM_C_MAJOR != ALERT_BCM_H_MAJOR) || \
     (ALERT_BCM_C_MINOR != ALERT_BCM_H_MINOR) || \
     (ALERT_BCM_C_PATCH != ALERT_BCM_H_PATCH))
#error "alert_bcm.c and alert_bcm.h : source and header files are inconsistent!"
#endif

#if ((ALERT_BCM_C_MAJOR != ALERT_CFG_H_MAJOR) || \
     (ALERT_BCM_C_MINOR != ALERT_CFG_H_MINOR) || \
     (ALERT_BCM_C_PATCH != ALERT_CFG_H_PATCH))
#error "alert_bcm.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Project Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#if (__PRJ_LIB_ALERT_D1L1_330D_HEV__ != 1)
#error "alert_bcm.c : Target project is inactive!"
#endif
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_BCM_NUM_TM                         (4U)

#define ALERT_BCM_SRC_IGN_10V                    (0x0100U)
#define ALERT_BCM_SRC_RDY_ON                     (0x0200U)
#define ALERT_BCM_SRC_PTS_ON                     (0x0400U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2       u2_bcm_bit;
    U2       u2_bcm_tout;

    U2       u2_tmc_act;
    U2       u2_tmc_run;
}ST_ALERT_BCM_CHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2    u2_sp_alert_bcm_tmcnt[ALERT_BCM_NUM_TM];
static U2    u2_s_alert_bcm_act;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_AlertBcmActChk(const U2 u2_a_SRC);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertBcmInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_AlertBcmInit(void)
{
    U4                       u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ALERT_BCM_NUM_TM; u4_t_lpcnt++){
        u2_sp_alert_bcm_tmcnt[u4_t_lpcnt]  = (U2)U2_MAX;
    }

    u2_s_alert_bcm_act = (U2)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertBcmTask(const U1 u1_a_VOM)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_AlertBcmTask(const U1 u1_a_VOM)
{
    U2                       u2_t_bcm_act;
    U2                       u2_t_src_chk;
    U2                       u2_t_ign_on;
    U2                       u2_t_vcs_on;

    U1                       u1_t_ign_10v;
    U1                       u1_t_rdyind;
    U1                       u1_t_pts;
    U1                       u1_t_msgsts;

    u2_t_src_chk  = (U2)u1_a_VOM;

    u2_t_bcm_act  = (U2)0U;
    u2_t_ign_on   = u2_t_src_chk & (U2)ALERT_VOM_IGN_ON;
    if(u2_t_ign_on != (U2)0U){

        u2_t_vcs_on = u2_t_src_chk & (U2)ALERT_VOM_VDC_ON;
        if(u2_t_vcs_on == (U2)0U){
            u2_t_bcm_act = (U2)ALERT_BCM_VDC;
        }

        u1_t_ign_10v = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN_10P5V);
        if(u1_t_ign_10v == (U1)IOHW_DIFLT_SWITCH_ACT){
            u2_t_src_chk |= (U2)ALERT_BCM_SRC_IGN_10V;
        }

        u1_t_rdyind = (U1)0U;
        u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G90_RXCH0,
                                            (U2)OXCAN_RX_SYS_NRX_IGR,
                                            (U2)U2_MAX) & (U1)COM_NO_RX;
        if(u1_t_msgsts != (U1)COM_NO_RX){
            (void)Com_ReceiveSignal(ComConf_ComSignal_RDYIND, &u1_t_rdyind);
        }
        if(u1_t_rdyind != (U1)0U){
            u2_t_src_chk |= (U2)ALERT_BCM_SRC_RDY_ON;
        }

#if 0   /* BEV BSW provisionally */
        u1_t_pts = u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_ON);
#else
        u1_t_pts = (U1)FALSE;
#endif
        if(u1_t_pts != (U1)TRUE){
            u2_t_bcm_act |= (U2)ALERT_BCM_PTS;
        }
        else{
            u2_t_src_chk |= (U2)ALERT_BCM_SRC_PTS_ON;
        }
    }

    u2_t_bcm_act |= u2_s_AlertBcmActChk(u2_t_src_chk);

    u2_s_alert_bcm_act = u2_t_bcm_act;
}
/*===================================================================================================================================*/
/*  U2      u2_g_AlertBcmAct(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2          u2_g_AlertBcmAct(void)
{
    return(u2_s_alert_bcm_act);
}
/*===================================================================================================================================*/
/*  static U2   u2_s_AlertBcmActChk(const U2 u2_a_SRC)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_AlertBcmActChk(const U2 u2_a_SRC)
{
    static const ST_ALERT_BCM_CHK      st_sp_ALERT_BCM_CHK[ALERT_BCM_NUM_TM] = {
        {
            (U2)ALERT_BCM_VDC,                                                         /* u2_bcm_bit  */
            (U2)5000U / (U2)ALERT_MAIN_TICK,                                           /* u2_bcm_tout */
            (U2)ALERT_VOM_VDC_ON,                                                      /* u2_tmc_act  */
            (U2)ALERT_VOM_VDC_ON     | (U2)ALERT_BCM_SRC_IGN_10V                       /* u2_tmc_run  */
        },
        {
            (U2)ALERT_BCM_VDC,                                                         /* u2_bcm_bit  */
            (U2)5000U / (U2)ALERT_MAIN_TICK,                                           /* u2_bcm_tout */
            (U2)ALERT_BCM_SRC_RDY_ON,                                                  /* u2_tmc_act  */
            (U2)ALERT_BCM_SRC_RDY_ON | (U2)ALERT_BCM_SRC_IGN_10V                       /* u2_tmc_run  */
        },
        {
            (U2)ALERT_BCM_PTS,                                                         /* u2_bcm_bit  */
            (U2)1000U / (U2)ALERT_MAIN_TICK,                                           /* u2_bcm_tout */
            (U2)ALERT_BCM_SRC_PTS_ON,                                                  /* u2_tmc_act  */
            (U2)ALERT_BCM_SRC_PTS_ON                                                   /* u2_tmc_run  */
        },
        {
            (U2)ALERT_BCM_PTS_5S,                                                      /* u2_bcm_bit  */
            (U2)5000U / (U2)ALERT_MAIN_TICK,                                           /* u2_bcm_tout */
            (U2)ALERT_BCM_SRC_PTS_ON,                                                  /* u2_tmc_act  */
            (U2)ALERT_BCM_SRC_PTS_ON                                                   /* u2_tmc_run  */
        }
    };

    U4                       u4_t_lpcnt;

    U2                       u2_t_bcm_act;
    U2                       u2_t_bcm_bit;
    U2                       u2_t_bcm_tout;
    U2                       u2_t_tmc_act;
    U2                       u2_t_tmc_run;

    U2                       u2_t_act;
    U2                       u2_t_run;

    u2_t_bcm_act = (U2)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ALERT_BCM_NUM_TM; u4_t_lpcnt++){

        u2_t_bcm_bit  = st_sp_ALERT_BCM_CHK[u4_t_lpcnt].u2_bcm_bit;
        u2_t_bcm_tout = st_sp_ALERT_BCM_CHK[u4_t_lpcnt].u2_bcm_tout;
        u2_t_tmc_act  = st_sp_ALERT_BCM_CHK[u4_t_lpcnt].u2_tmc_act;
        u2_t_tmc_run  = st_sp_ALERT_BCM_CHK[u4_t_lpcnt].u2_tmc_run;

        u2_t_act      = u2_a_SRC & u2_t_tmc_act;
        u2_t_run      = u2_a_SRC & u2_t_tmc_run;

        if(u2_t_act != u2_t_tmc_act){
            u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] = (U2)U2_MAX;
        }
        else if(u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] >= (U2)U2_MAX){
            u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] = (U2)0U;
        }
        else if(u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] >= u2_t_bcm_tout){
            u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] = u2_t_bcm_tout;
        }
        else if(u2_t_run != u2_t_tmc_run){
            u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] = (U2)0U;
        }
        else{
            u2_sp_alert_bcm_tmcnt[u4_t_lpcnt]++;
        }

        if(u2_sp_alert_bcm_tmcnt[u4_t_lpcnt] < u2_t_bcm_tout){
            u2_t_bcm_act |= u2_t_bcm_bit;
        }
    }

    return(u2_t_bcm_act);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     1/17/2019  TN       New.                                                                                               */
/*  5.1.0     3/26/2019  TN       alert v5.0.0 -> v5.1.0.                                                                            */
/*            4/04/2019  SN       Add PTS MASK                                                                                       */
/*  5.2.0     4/17/2019  YI       alert v5.1.0 -> v5.2.0.                                                                            */
/*  5.3.0     5/10/2019  YI       alert v5.2.0 -> v5.3.0.                                                                            */
/*  5.4.0     9/20/2019  YI       alert v5.3.0 -> v5.4.0.                                                                            */
/*  5.5.0    10/31/2019  DS       alert v5.4.0 -> v5.5.0.                                                                            */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  001      11/29/2019  SN       Modify RDY MASK processing                                                                         */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
