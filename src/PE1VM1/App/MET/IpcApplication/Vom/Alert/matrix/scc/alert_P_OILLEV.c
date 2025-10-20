/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_OILLEV                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILLEV_C_MAJOR                   (5)
#define ALERT_P_OILLEV_C_MINOR                   (5)
#define ALERT_P_OILLEV_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_OILLEV_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_OILLEV.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILLEV_NUM_DST                   (64U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_p_oillev_locnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertP_oillevSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_oillevRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static U4      u4_s_AlertP_oillevJdgOillv(const U1 u1_a_VOM, const U1 u1_a_CTRL_JDG, const U2 u2_a_LMT_RPM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_OILLEV_DST[ALERT_P_OILLEV_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 09 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 11 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 12 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 13 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 15 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 16 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 17 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 18 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 19 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 20 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 21 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 22 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 23 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 24 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 25 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 26 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 27 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 28 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 29 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 30 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 31 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 41 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 43 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 44 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 45 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 47 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 57 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 59 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 60 OILLVLO                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO,                                            /* 61 OILLVLO                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLEV_OILLVLO                                             /* 63 OILLVLO                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_OILLEV_MTRX[1] = {
    {
        &u4_s_AlertP_oillevSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_oillevRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILLEV_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_P_OILLEV_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertP_oillevInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertP_oillevInit(void)
{
    u4_s_alert_p_oillev_locnt = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oillevSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oillevSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_P_OILLEV_LSB_MSGSTS = (U1)5U;
    static const U1 u1_s_ALERT_P_OILLEV_LSB_OILLV  = (U1)4U;
    static const U4 u4_s_ALERT_P_OILLEV_LAS        = (U4)0x00000001U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_ctrl_jdg;
    U2              u2_t_lmt_rpm;

    u2_t_lmt_rpm  = (U2)0U;
    u1_t_ctrl_jdg = u1_g_AlertCfgOilrpm(&u2_t_lmt_rpm);

    u1_t_sgnl     = (U1)0U;
    u1_t_msgsts   = (U1)COM_NO_RX;
    if((u1_t_ctrl_jdg & (U1)ALERT_ENGTYPE_CAN_VALID) != (U1)0U){
        u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                       (U2)OXCAN_RX_SYS_NRX_IGR,
                                       (U2)U2_MAX) & (U1)COM_NO_RX;

        (void)Com_ReceiveSignal(ComConf_ComSignal_B_OILLV, &u1_t_sgnl);
    }
    u4_t_src_chk  = ((U4)u1_t_sgnl   << u1_s_ALERT_P_OILLEV_LSB_OILLV );
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_OILLEV_LSB_MSGSTS);

    u4_t_src_chk |= u4_s_AlertP_oillevJdgOillv(u1_a_VOM, u1_t_ctrl_jdg, u2_t_lmt_rpm);

    if(u1_a_LAS == (U1)ALERT_REQ_P_OILLEV_OILLVLO){
        u4_t_src_chk |= u4_s_ALERT_P_OILLEV_LAS;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oillevJdgOillv(const U1 u1_a_VOM, const U1 u1_a_CTRL_JDG, const U2 u2_a_LMT_RPM)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oillevJdgOillv(const U1 u1_a_VOM, const U1 u1_a_CTRL_JDG, const U2 u2_a_LMT_RPM)
{
#if 0   /* BEV Rebase provisionally */
    static const U4 u4_s_ALERT_P_OILLEV_DLY_TIME     = (U4)(40000U / ALERT_CH_TICK);  /* 40[s] */
    static const U2 u2_s_ALERT_P_OILLEV_TMP_THRESH   = (U2)8000U;                     /* 80[degree] */
    static const U4 u4_s_ALERT_P_OILLEV_OLLV_STS_HI  = (U4)0x00000000U;
    static const U4 u4_s_ALERT_P_OILLEV_OLLV_STS_CNT = (U4)0x00000002U;
    static const U4 u4_s_ALERT_P_OILLEV_OLLV_STS_LO  = (U4)0x00000004U;
    static const U4 u4_s_ALERT_P_OILLEV_OILW_STS_ACT = (U4)0x00000008U;
    static const U2 u2_s_ALERT_P_OILLEV_OILRPM_ZERO  = (U2)0U;
    U4              u4_t_oillv;
    U2              u2_t_tmp;
    U2              u2_t_rpm;
    U1              u1_t_oilw;
    U1              u1_t_tmpsts;
    U1              u1_t_engsts;
    U1              u1_t_oilsw;

    u4_t_oillv  = u4_s_ALERT_P_OILLEV_OLLV_STS_HI;

    if((u1_a_CTRL_JDG & (U1)ALERT_ENGTYPE_IOHW_VALID) != (U1)0U){
        u1_t_oilsw                = u1_g_AlertOillvSw();

        if((u1_t_oilsw   == (U1)TRUE                       ) &&
           (u2_a_LMT_RPM != u2_s_ALERT_P_OILLEV_OILRPM_ZERO)){
            u1_t_oilw = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_P_OILLEV_OIL_W);
        }
        else{
            u1_t_oilw = (U1)IOHW_DIFLT_SWITCH_INACT;
        }

        if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                   ) &&
           (u1_t_oilw                         == (U1)IOHW_DIFLT_SWITCH_ACT)){

            u2_t_tmp    = (U2)0U;
            u1_t_tmpsts = (u1_g_AlertCfgPtsctmpCelInst(&u2_t_tmp) & ((U1)ALERT_PTSCTMP_STSBIT_UNKNOWN | (U1)ALERT_PTSCTMP_STSBIT_INVALID));

            u2_t_rpm    = (U2)0U;
            u1_t_engsts = (u1_g_AlertEngspdRpmInst(&u2_t_rpm)  & ((U1)ALERT_RPM_STSBIT_UNKNOWN | (U1)ALERT_RPM_STSBIT_INVALID));
            if((u1_t_engsts & (U1)ALERT_RPM_STSBIT_INVALID)      != (U1)0U){
                u2_t_rpm = (U2)U2_MAX;
            }
            else if((u1_t_engsts & (U1)ALERT_RPM_STSBIT_UNKNOWN) != (U1)0U){
                u2_t_rpm = (U2)0U;
            }
            else{
                /* Nothing to do */
            }

            if(u4_s_alert_p_oillev_locnt >= u4_s_ALERT_P_OILLEV_DLY_TIME){
                u4_s_alert_p_oillev_locnt = u4_s_ALERT_P_OILLEV_DLY_TIME;
                u4_t_oillv                = (u4_s_ALERT_P_OILLEV_OLLV_STS_LO  | u4_s_ALERT_P_OILLEV_OILW_STS_ACT);
            }
            else if((u1_t_tmpsts         == (U1)ALERT_PTSCTMP_STSBIT_VALID) &&
                    (u2_t_tmp            >= u2_s_ALERT_P_OILLEV_TMP_THRESH) &&
                    (u2_t_rpm            <= u2_a_LMT_RPM                  )){
                u4_s_alert_p_oillev_locnt++;
                u4_t_oillv                = (u4_s_ALERT_P_OILLEV_OLLV_STS_CNT | u4_s_ALERT_P_OILLEV_OILW_STS_ACT);
            }
            else{
                u4_s_alert_p_oillev_locnt = (U4)0U;
                u4_t_oillv                = u4_s_ALERT_P_OILLEV_OILW_STS_ACT;
            }
        }
        else{
            u4_s_alert_p_oillev_locnt = (U4)0U;
        }
    }
    else{
        u4_s_alert_p_oillev_locnt = (U4)0U;
    }

    return(u4_t_oillv);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_oillevRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_oillevRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
#ifdef ComConf_ComSignal_OLW
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                        ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_P_OILLEV_OILLVLO)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_OLW, &u1_t_sgnl);
#endif /* ComConf_ComSignal_OLW */
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/26/2020  TH       New.                                                                                               */
/*  5.1.0     4/28/2020  DS       Modify ptsctmp handling(Add offset).                                                               */
/*  5.2.0     8/25/2020  KT       Update CV-R.                                                                                       */
/*  5.2.1     9/16/2020  ZS       Add ConfigIF for get ptsctmp and remove handling to offset.                                        */
/*  5.2.2    12/ 8/2020  ZS       Add Compile switch.                                                                                */
/*  5.2.3    12/22/2020  TM       Change ConfigIF for get Engine rpm threshold.                                                      */
/*  5.2.4     3/ 2/2021  ZS       Fix PCS3-2 Warning.                                                                                */
/*  5.2.5     3/25/2021  KT       Update how to get the Message Label.                                                               */
/*  5.3.0    11/11/2021  YN       Add ConfigIF for OIL_W.                                                                            */
/*  5.4.0     1/21/2022  KT       Modify Conditional expression for judge which signal to use, B_OILLV or OIL_W.                     */
/*  5.4.1     8/ 8/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.5.0     4/ 3/2024  SR       Update for 19PFv3 (removed engine type)                                                            */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
