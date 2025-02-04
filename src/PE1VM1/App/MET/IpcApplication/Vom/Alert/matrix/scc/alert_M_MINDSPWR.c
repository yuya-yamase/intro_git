/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert M_MINDSPWR                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_MINDSPWR_C_MAJOR                 (5)
#define ALERT_M_MINDSPWR_C_MINOR                 (3)
#define ALERT_M_MINDSPWR_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_M_MINDSPWR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_M_MINDSPWR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_MINDSPWR_NUM_DST                 (16U)

#define ALERT_M_MINDSPWR_BZSTS_OFF               (0U)
#define ALERT_M_MINDSPWR_BZSTS_LVL1              (1U)
#define ALERT_M_MINDSPWR_BZSTS_OFFTOLVL1         (2U)
#define ALERT_M_MINDSPWR_BZSTS_LVL2              (3U)
#define ALERT_M_MINDSPWR_BZSTS_NUM               (4U)
#define ALERT_M_MINDSPWR_SPDSTS_NUM              (5U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_m_mindspwr_bzsts_last;
static U4      u4_s_alert_m_mindspwr_lvl1_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertM_mindspwrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_M_MINDSPWR_DST[ALERT_M_MINDSPWR_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_M_MINDSPWR_SINGLE,                                           /* 10 SINGLE                                          */
    (U1)ALERT_REQ_M_MINDSPWR_CYCLE,                                            /* 11 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_M_MINDSPWR_SINGLE,                                           /* 13 SINGLE                                          */
    (U1)ALERT_REQ_M_MINDSPWR_SINGLE,                                           /* 14 SINGLE                                          */
    (U1)ALERT_REQ_M_MINDSPWR_CYCLE                                             /* 15 CYCLE                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_M_MINDSPWR_MTRX[1] = {
    {
        &u4_s_AlertM_mindspwrSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_M_MINDSPWR_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_M_MINDSPWR_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertM_mindspwrInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertM_mindspwrInit(void)
{
    u1_s_alert_m_mindspwr_bzsts_last = (U1)0U;
    u4_s_alert_m_mindspwr_lvl1_cnt   = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertM_mindspwrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertM_mindspwrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2  u2_s_ALERT_M_MINDSPWR_L1_LOTHRSH = (U2)7900U;
    static const U2  u2_s_ALERT_M_MINDSPWR_L1_UPTHRSH = (U2)8000U;
    static const U2  u2_s_ALERT_M_MINDSPWR_L2_LOTHRSH = (U2)11900U;
    static const U2  u2_s_ALERT_M_MINDSPWR_L2_UPTHRSH = (U2)12000U;
    static const U4  u4_s_ALERT_M_MINDSPWR_L1_RETHRSH = ((U4)115000U / (U4)ALERT_CH_TICK);
    static const U4  u4_s_ALERT_M_MINDSPWR_L1_REELPS  = (U4)0x00000004U;
    static const U4  u4_s_ALERT_M_MINDSPWR_IGN_ON     = (U4)0x00000008U;
    static const U1  u1_s_ALERT_M_MINDSPWR_BZSTS_MSK  = (U1)0x03U;
    static const U1  u1_s_ALERT_M_MINDSPWR_SPD_OFF    = (U1)0U;
    static const U1  u1_s_ALERT_M_MINDSPWR_SPD_HYS_L1 = (U1)1U;
    static const U1  u1_s_ALERT_M_MINDSPWR_SPD_OVR_L1 = (U1)2U;
    static const U1  u1_s_ALERT_M_MINDSPWR_SPD_HYS_L2 = (U1)3U;
    static const U1  u1_s_ALERT_M_MINDSPWR_SPD_OVR_L2 = (U1)4U;

    static const U1  u1_sp2_ALERT_M_MINDSPWR_BZSTS[ALERT_M_MINDSPWR_SPDSTS_NUM][ALERT_M_MINDSPWR_BZSTS_NUM] = {
        {(U1)ALERT_M_MINDSPWR_BZSTS_OFF,         (U1)ALERT_M_MINDSPWR_BZSTS_OFF,   (U1)ALERT_M_MINDSPWR_BZSTS_OFF,   (U1)ALERT_M_MINDSPWR_BZSTS_OFF },
        {(U1)ALERT_M_MINDSPWR_BZSTS_OFF,         (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL1},
        {(U1)ALERT_M_MINDSPWR_BZSTS_OFFTOLVL1,   (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL1},
        {(U1)ALERT_M_MINDSPWR_BZSTS_OFFTOLVL1,   (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL1,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL2},
        {(U1)ALERT_M_MINDSPWR_BZSTS_LVL2,        (U1)ALERT_M_MINDSPWR_BZSTS_LVL2,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL2,  (U1)ALERT_M_MINDSPWR_BZSTS_LVL2}
    };

    U4               u4_t_src_chk;
    U2               u2_t_vehspd;
    U1               u1_t_vehspd_sts;
    U1               u1_t_spd_sts;
    U1               u1_t_bzsts;

    u2_t_vehspd     = (U2)0U;
    u1_t_vehspd_sts = u1_g_AlertSpdKmphBiased(&u2_t_vehspd, (U1)FALSE);

    u1_t_spd_sts    = u1_s_ALERT_M_MINDSPWR_SPD_OFF;
    if(u1_t_vehspd_sts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_s_ALERT_M_MINDSPWR_L2_UPTHRSH <= u2_t_vehspd){
            u1_t_spd_sts = u1_s_ALERT_M_MINDSPWR_SPD_OVR_L2;
        }
        else if(u2_s_ALERT_M_MINDSPWR_L2_LOTHRSH <= u2_t_vehspd){
            u1_t_spd_sts = u1_s_ALERT_M_MINDSPWR_SPD_HYS_L2;
        }
        else if(u2_s_ALERT_M_MINDSPWR_L1_UPTHRSH <= u2_t_vehspd){
            u1_t_spd_sts = u1_s_ALERT_M_MINDSPWR_SPD_OVR_L1;
        }
        else if(u2_s_ALERT_M_MINDSPWR_L1_LOTHRSH <= u2_t_vehspd){
            u1_t_spd_sts = u1_s_ALERT_M_MINDSPWR_SPD_HYS_L1;
        }
        else{
            /* LESS THAN LVL1 */
        }
    }
    u1_s_alert_m_mindspwr_bzsts_last &= u1_s_ALERT_M_MINDSPWR_BZSTS_MSK;
    u1_t_bzsts                        = u1_sp2_ALERT_M_MINDSPWR_BZSTS[u1_t_spd_sts][u1_s_alert_m_mindspwr_bzsts_last];
    u4_t_src_chk                      = (U4)u1_t_bzsts;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        if(u1_t_bzsts == (U1)ALERT_M_MINDSPWR_BZSTS_LVL1){
            u4_s_alert_m_mindspwr_lvl1_cnt++;
        }
        else{
            u4_s_alert_m_mindspwr_lvl1_cnt = (U4)0U;
        }
        u4_t_src_chk |= u4_s_ALERT_M_MINDSPWR_IGN_ON;
    }
    else{
        u4_s_alert_m_mindspwr_lvl1_cnt = (U4)0U;
    }

    if(u4_s_alert_m_mindspwr_lvl1_cnt >= u4_s_ALERT_M_MINDSPWR_L1_RETHRSH){
        u4_t_src_chk                  |= u4_s_ALERT_M_MINDSPWR_L1_REELPS;
        u4_s_alert_m_mindspwr_lvl1_cnt = (U4)0U;
    }

    u1_s_alert_m_mindspwr_bzsts_last  = u1_t_bzsts;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/19/2020  FN       New.                                                                                               */
/*  5.1.0     6/10/2020  ZS       Fix u4_s_ALERT_M_MINDSPWR_L1_RETHRSH value.                                                        */
/*  5.2.0     8/26/2020  KT       Modify the condition to sound the buzzer.                                                          */
/*  5.2.1     5/14/2021  KT       Fix 800B Bug.                                                                                      */
/*  5.2.2     1/19/2022  KAT      Update for 840B#2 CV(Version update).                                                              */
/*  5.3.0     2/08/2024  SW       Update for 19PFv3(Version update).                                                                 */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * KAT  = Katsushi Takahashi, NTTD MSE                                                                                            */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
