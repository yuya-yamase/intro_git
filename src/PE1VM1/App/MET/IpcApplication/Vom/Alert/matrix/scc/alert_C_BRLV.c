/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRLV                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRLV_2_C_MAJOR                   (5)
#define ALERT_C_BRLV_2_C_MINOR                   (4)
#define ALERT_C_BRLV_2_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_BRLV_2_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRLV.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRLV_2_WRN_NUM_DST               (4U)
#define ALERT_C_BRLV_2_BC_NUM_DST                (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_brlv_spdjdg_rslt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_brlv_2WrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_brlv_2BcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_brlvJdgSpd     (void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_BRLV_2_WRN_DST[ALERT_C_BRLV_2_WRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRLV_2_WRN_MALFUNC,                                        /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_C_BRLV_2_BC_DST[ALERT_C_BRLV_2_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRLV_2_BC_MALFUNC,                                         /* 03 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRLV_2_MTRX[2] = {
    {
        &u4_s_AlertC_brlv_2WrnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRLV_2_WRN_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_BRLV_2_WRN_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_brlv_2BcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRLV_2_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_C_BRLV_2_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_brlv_2Init(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_brlv_2Init(void)
{
    u4_s_alert_brlv_spdjdg_rslt = (U4)FALSE;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brlv_2WrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brlv_2WrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_BRLV_WRN_LSB_DDM1S17 = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl_brlv;
    U4              u4_t_src_chk;

    u1_t_msgsts       = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                          (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl_brlv    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_BRLV, &u1_t_sgnl_brlv);
    u4_t_src_chk      = (U4)u1_t_sgnl_brlv;
    u4_t_src_chk     |= ((U4)u1_t_msgsts    << u1_s_ALERT_BRLV_WRN_LSB_DDM1S17);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brlv_2BcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brlv_2BcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_BRLV_BC_TO_THRESH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_BRLV_BC_LSB_DDM1S17 = (U1)2U;
    static const U1 u1_s_ALERT_BRLV_BC_LSB_B_BRLV  = (U1)1U;
    U1              u1_t_msg;
    U1              u1_t_sgnl_brlv;
    U4              u4_t_src_chk;

    u4_t_src_chk    = u4_s_AlertC_brlvJdgSpd();

    u1_t_msg        = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                        (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                        u2_s_ALERT_BRLV_BC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl_brlv  = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_BRLV, &u1_t_sgnl_brlv);
    u4_t_src_chk   |= ((U4)u1_t_sgnl_brlv  << u1_s_ALERT_BRLV_BC_LSB_B_BRLV);
    u4_t_src_chk   |= ((U4)u1_t_msg        << u1_s_ALERT_BRLV_BC_LSB_DDM1S17);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4 u4_s_AlertC_brlvJdgSpd(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      void                                                                                                             */
/*  Return:         u4_t_jdgrslt        Vehcle Speed Status                                                                          */
/*                                      LSB     : u4_s_ALERT_BRLV_BIT_JDGSPD(5kmph Over)/0U(Under 4kmph) [1kmph hysteresis]          */
/*                                      RANGE   : [0U,u4_s_ALERT_BRLV_BIT_JDGSPD]                                                    */
/*===================================================================================================================================*/
static U4 u4_s_AlertC_brlvJdgSpd(void)
{
    static const U2 u2_s_ALERT_BRLV_SPD_HI_THRESH = (U2)500U;
    static const U2 u2_s_ALERT_BRLV_SPD_LO_THRESH = (U2)400U;
    static const U4 u4_s_ALERT_BRLV_BIT_JDGSPD    = (U4)0x00000001U;

    U2              u2_t_vehspd;
    U1              u1_t_spdsts;
    U4              u4_t_jdgrslt;

    u4_t_jdgrslt = (U4)0U;
    u2_t_vehspd  = (U2)0U;

    u1_t_spdsts  = u1_g_AlertSpdKmphInst(&u2_t_vehspd, (U1)TRUE);

    if(u1_t_spdsts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_t_vehspd >= u2_s_ALERT_BRLV_SPD_HI_THRESH){
            u4_t_jdgrslt = u4_s_ALERT_BRLV_BIT_JDGSPD;
        }
        else if((u2_t_vehspd                 >= u2_s_ALERT_BRLV_SPD_LO_THRESH) &&
                (u4_s_alert_brlv_spdjdg_rslt == u4_s_ALERT_BRLV_BIT_JDGSPD   )){
            u4_t_jdgrslt = u4_s_ALERT_BRLV_BIT_JDGSPD;
        }
        else{
            /* Do Nothing */
        }
    }

    u4_s_alert_brlv_spdjdg_rslt = u4_t_jdgrslt;

    return(u4_t_jdgrslt);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/23/2020  FN       New.                                                                                               */
/*  5.0.1     4/22/2020  DS       Rename module name.                                                                                */
/*  5.1.0     5/26/2020  ZS       Change remote warning logic.                                                                       */
/*  5.2.0     8/24/2020  TN       Delete judgment low voltage logic.                                                                 */
/*  5.3.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.3.1     3/16/2021  SO       Update for 840B CV(Version update).                                                                */
/*  5.3.2     5/14/2021  TN       Fix 800B Bug.                                                                                      */
/*  5.4.0    11/12/2024  KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
