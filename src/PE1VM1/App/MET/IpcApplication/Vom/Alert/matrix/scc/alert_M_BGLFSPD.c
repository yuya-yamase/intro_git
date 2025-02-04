/* 5.3.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert M_BGLFSPD                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_BGLFSPD_C_MAJOR                  (5)
#define ALERT_M_BGLFSPD_C_MINOR                  (3)
#define ALERT_M_BGLFSPD_C_PATCH                  (2)

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
#if (ALERT_M_BGLFSPD_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_M_BGLFSPD.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_BGLFSPD_NUM_DST                  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_m_bglfspd_tm_on_elpsd;
static U4      u4_s_alert_m_bglfspd_tm_of_elpsd;
static U1      u1_s_alert_m_bglfspd_tm_re_flg;
static U1      u1_s_alert_m_bglfspd_last_req;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertM_bglfspdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_M_BGLFSPD_CRIT[ALERT_M_BGLFSPD_NUM_DST] = {
    (U4)0x10000016U,                                                           /* 00 ON                                              */
    (U4)0x10000028U,                                                           /* 01 ON                                              */
    (U4)0x10000026U,                                                           /* 02 ON                                              */
    (U4)0x10000022U                                                            /* 03 ON                                              */
};
static const U4  u4_sp_ALERT_M_BGLFSPD_MASK[ALERT_M_BGLFSPD_NUM_DST] = {
    (U4)0x10000076U,                                                           /* 00 ON                                              */
    (U4)0x1000007DU,                                                           /* 01 ON                                              */
    (U4)0x10000076U,                                                           /* 02 ON                                              */
    (U4)0x1000007FU                                                            /* 03 ON                                              */
};
static const U1  u1_sp_ALERT_M_BGLFSPD_DST[ALERT_M_BGLFSPD_NUM_DST] = {
    (U1)ALERT_REQ_M_BGLFSPD_ON,                                                /* 00 ON                                              */
    (U1)ALERT_REQ_M_BGLFSPD_ON,                                                /* 01 ON                                              */
    (U1)ALERT_REQ_M_BGLFSPD_ON,                                                /* 02 ON                                              */
    (U1)ALERT_REQ_M_BGLFSPD_ON                                                 /* 03 ON                                              */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_M_BGLFSPD_MTRX[1] = {
    {
        &u4_s_AlertM_bglfspdSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_M_BGLFSPD_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_M_BGLFSPD_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_M_BGLFSPD_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_M_BGLFSPD_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertM_bglfspdInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertM_bglfspdInit(void)
{
    u4_s_alert_m_bglfspd_tm_on_elpsd = (U4)U4_MAX;
    u4_s_alert_m_bglfspd_tm_of_elpsd = (U4)U4_MAX;
    u1_s_alert_m_bglfspd_tm_re_flg   = (U1)TRUE;
    u1_s_alert_m_bglfspd_last_req    = (U1)ALERT_REQ_UNKNOWN;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertM_bglfspdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertM_bglfspdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_M_BGLFSPD_THRSH_LOWER = (U2)11950U;
    static const U2 u2_s_ALERT_M_BGLFSPD_THRSH_UPPER = (U2)12050U;
    static const U4 u4_s_ALERT_M_BGLFSPD_OF_ELPS_LMT = ((U4)6000U / (U4)ALERT_CH_TICK);
    static const U4 u4_s_ALERT_M_BGLFSPD_ON_ELPS_LMT = ((U4)6000U / (U4)ALERT_CH_TICK);

    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_LESS_OF = (U4)0x00000001U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_LESS_ON = (U4)0x00000002U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_ON_PREV = (U4)0x00000004U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_RE_BUZZ = (U4)0x00000008U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_SPD_MID = (U4)0x00000010U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_SPD_HI  = (U4)0x00000020U;
    static const U4 u4_s_ALERT_M_BGLFSPD_BIT_SPD_INV = (U4)0x00000040U;

    U4              u4_t_src_chk;
    U2              u2_t_vehspd;
    U1              u1_t_vehspd_sts;

    u4_t_src_chk                  = (U4)0U;
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        if(u1_a_LAS == (U1)ALERT_REQ_M_BGLFSPD_ON){
            if((u1_s_alert_m_bglfspd_last_req == (U1)ALERT_REQ_UNKNOWN)){
                u1_s_alert_m_bglfspd_tm_re_flg = (U1)FALSE;
            }
            u4_t_src_chk                    |= u4_s_ALERT_M_BGLFSPD_BIT_ON_PREV;
            u4_s_alert_m_bglfspd_tm_of_elpsd = (U4)1U;
            if(u4_s_ALERT_M_BGLFSPD_ON_ELPS_LMT > u4_s_alert_m_bglfspd_tm_on_elpsd){
                u4_t_src_chk                  |= u4_s_ALERT_M_BGLFSPD_BIT_LESS_ON;
                u4_s_alert_m_bglfspd_tm_on_elpsd++;
            }
        }
        else{
            u4_s_alert_m_bglfspd_tm_on_elpsd = (U4)1U;
            if(u4_s_ALERT_M_BGLFSPD_OF_ELPS_LMT > u4_s_alert_m_bglfspd_tm_of_elpsd){
                u4_t_src_chk                  |= u4_s_ALERT_M_BGLFSPD_BIT_LESS_OF;
                u4_s_alert_m_bglfspd_tm_of_elpsd++;
            }
        }
    }
    else{
        u4_s_alert_m_bglfspd_tm_on_elpsd = (U4)U4_MAX;
        u4_s_alert_m_bglfspd_tm_of_elpsd = (U4)U4_MAX;
        u1_s_alert_m_bglfspd_tm_re_flg   = (U1)TRUE;
    }

    u2_t_vehspd                   = (U2)0U;
    u1_t_vehspd_sts               = u1_g_AlertSpdKmphBiased(&u2_t_vehspd, (U1)FALSE);

    if(u1_t_vehspd_sts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_s_ALERT_M_BGLFSPD_THRSH_UPPER      <= u2_t_vehspd){
            u4_t_src_chk                  |= u4_s_ALERT_M_BGLFSPD_BIT_SPD_HI;
        }
        else if(u2_s_ALERT_M_BGLFSPD_THRSH_LOWER < u2_t_vehspd){
            u4_t_src_chk                  |= u4_s_ALERT_M_BGLFSPD_BIT_SPD_MID;
        }
        else{
            u1_s_alert_m_bglfspd_tm_re_flg = (U1)TRUE;
        }
    }
    else{
        u4_t_src_chk                    |= u4_s_ALERT_M_BGLFSPD_BIT_SPD_INV;
        u1_s_alert_m_bglfspd_tm_re_flg   = (U1)TRUE;
    }

    if(u1_s_alert_m_bglfspd_tm_re_flg == (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_M_BGLFSPD_BIT_RE_BUZZ;
    }
    u1_s_alert_m_bglfspd_last_req = u1_a_LAS;
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
/*  5.0.0     3/10/2020  SK       New.                                                                                               */
/*  5.1.0     5/22/2020  ZS       Fix the initial timing and start timing of the buzzer end timer.                                   */
/*  5.2.0     6/ 1/2020  ZS       Fix timer spec and timer bit on timing.                                                            */
/*  5.3.0     9/15/2020  TM       Fix re-buzzer conditions.                                                                          */
/*  5.3.1     3/26/2021  SO       Update for 840B CV(Version update).                                                                */
/*  5.3.2     1/19/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
