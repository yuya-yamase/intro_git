/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_PKBWAR                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_PKBWAR_C_MAJOR                   (5)
#define ALERT_C_PKBWAR_C_MINOR                   (2)
#define ALERT_C_PKBWAR_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_PKBWAR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_PKBWAR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_PKBWAR_BC_NUM_DST                (3U)
#define ALERT_C_PKBWAR_PD_NUM_DST                (3U)

#define ALERT_C_PKBWAR_JDGSPD_NUM                (8U)
#define ALERT_C_PKBWAR_JDGSPD_OFF                (0U)
#define ALERT_C_PKBWAR_JDGSPD_ON                 (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_pkbwar_spdjdg_rslt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_pkbwarBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_pkbwarPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_pkbwarJdgSpd  (void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_C_PKBWAR_BC_CRIT[ALERT_C_PKBWAR_BC_NUM_DST] = {
    (U4)0x00000103U,                                                           /* 00 ON                                              */
    (U4)0x00000109U,                                                           /* 03 ON                                              */
    (U4)0x00000105U                                                            /* 02 ON                                              */
};
static const U4  u4_sp_ALERT_C_PKBWAR_BC_MASK[ALERT_C_PKBWAR_BC_NUM_DST] = {
    (U4)0x00000103U,                                                           /* 00 ON                                              */
    (U4)0x000001C9U,                                                           /* 01 ON                                              */
    (U4)0x00000135U                                                            /* 02 ON                                              */
};
static const U1  u1_sp_ALERT_C_PKBWAR_BC_DST[ALERT_C_PKBWAR_BC_NUM_DST] = {
    (U1)ALERT_REQ_C_PKBWAR_BC_ON,                                              /* 00 ON                                              */
    (U1)ALERT_REQ_C_PKBWAR_BC_ON,                                              /* 01 ON                                              */
    (U1)ALERT_REQ_C_PKBWAR_BC_ON                                               /* 33 ON                                              */
};
static const U4  u4_sp_ALERT_C_PKBWAR_PD_CRIT[ALERT_C_PKBWAR_PD_NUM_DST] = {
    (U4)0x00000043U,                                                           /* 00 ON                                              */
    (U4)0x00000049U,                                                           /* 02 ON                                              */
    (U4)0x00000045U                                                            /* 02 ON                                              */
};
static const U4  u4_sp_ALERT_C_PKBWAR_PD_MASK[ALERT_C_PKBWAR_PD_NUM_DST] = {
    (U4)0x00000043U,                                                           /* 00 ON                                              */
    (U4)0x00000069U,                                                           /* 01 ON                                              */
    (U4)0x00000055U                                                            /* 02 ON                                              */
};
static const U1  u1_sp_ALERT_C_PKBWAR_PD_DST[ALERT_C_PKBWAR_PD_NUM_DST] = {
    (U1)ALERT_REQ_C_PKBWAR_PD_ON,                                              /* 03 ON                                              */
    (U1)ALERT_REQ_C_PKBWAR_PD_ON,                                              /* 05 ON                                              */
    (U1)ALERT_REQ_C_PKBWAR_PD_ON                                               /* 63 ON                                              */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_PKBWAR_MTRX[2] = {
    {
        &u4_s_AlertC_pkbwarBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_PKBWAR_BC_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_C_PKBWAR_BC_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_PKBWAR_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_C_PKBWAR_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_pkbwarPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_PKBWAR_PD_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_C_PKBWAR_PD_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_PKBWAR_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_C_PKBWAR_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_pkbwarInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_pkbwarInit(void)
{
    u1_s_alert_pkbwar_spdjdg_rslt = (U1)ALERT_C_PKBWAR_JDGSPD_OFF;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_pkbwarBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_pkbwarBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_PKBWAR_BC_TO_THRS_VSC = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_PKBWAR_BC_TO_THRS_BDB = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_PKBWAR_BC_LSB_VSC1S95 = (U1)6U;
    static const U1 u1_s_ALERT_PKBWAR_BC_LSB_BDB1S01 = (U1)4U;
    static const U1 u1_s_ALERT_PKBWAR_BC_LSB_B_CPKB  = (U1)3U;
    static const U1 u1_s_ALERT_PKBWAR_BC_LSB_PKB_BDB = (U1)2U;
    static const U4 u4_s_ALERT_PKBWAR_BC_BIT_PKB_SW  = (U4)0x00000002U;
    static const U4 u4_s_ALERT_PKBWAR_BC_BIT_IGN_ON  = (U4)0x00000100U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;
    U1              u1_t_pkbsw_act;
    U4              u4_t_jdgspd;

    u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                      (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                      u2_s_ALERT_PKBWAR_BC_TO_THRS_VSC) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl      = (U1)0U;
#ifdef ComConf_ComSignal_B_CPKB
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_CPKB, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_CPKB */ /* 235D_CAN */
    u4_t_src_chk   = ((U4)u1_t_sgnl    << u1_s_ALERT_PKBWAR_BC_LSB_B_CPKB);
    u4_t_src_chk  |= ((U4)u1_t_msgsts  << u1_s_ALERT_PKBWAR_BC_LSB_VSC1S95);

    u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01,
                                      (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                      u2_s_ALERT_PKBWAR_BC_TO_THRS_BDB) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PKB_BDB, &u1_t_sgnl);
    u4_t_src_chk  |= ((U4)u1_t_sgnl    << u1_s_ALERT_PKBWAR_BC_LSB_PKB_BDB);
    u4_t_src_chk  |= ((U4)u1_t_msgsts  << u1_s_ALERT_PKBWAR_BC_LSB_BDB1S01);

    u1_t_pkbsw_act = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_C_PKBWAR_PKB);
    if(u1_t_pkbsw_act == (U1)IOHW_DIFLT_SWITCH_ACT){
        u4_t_src_chk |= u4_s_ALERT_PKBWAR_BC_BIT_PKB_SW;
    }

    u4_t_jdgspd    = u4_s_AlertC_pkbwarJdgSpd();
    u4_t_src_chk  |= u4_t_jdgspd;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_PKBWAR_BC_BIT_IGN_ON;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_pkbwarPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_pkbwarPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_PKBWAR_PD_LSB_VSC1S95 = (U1)5U;
    static const U1 u1_s_ALERT_PKBWAR_PD_LSB_BDB1S01 = (U1)4U;
    static const U1 u1_s_ALERT_PKBWAR_PD_LSB_B_CPKB  = (U1)3U;
    static const U1 u1_s_ALERT_PKBWAR_PD_LSB_PKB_BDB = (U1)2U;
    static const U4 u4_s_ALERT_PKBWAR_PD_BIT_PKB_SW  = (U4)0x00000002U;
    static const U4 u4_s_ALERT_PKBWAR_PD_BIT_IGN_ON  = (U4)0x00000040U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;
    U1              u1_t_pkbsw_act;

    u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                      (U2)OXCAN_RX_SYS_NRX_IGR,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl      = (U1)0U;
#ifdef ComConf_ComSignal_B_CPKB
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_CPKB, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_CPKB */ /* 345D_CAN */
    u4_t_src_chk   = ((U4)u1_t_sgnl   << u1_s_ALERT_PKBWAR_PD_LSB_B_CPKB);
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_PKBWAR_PD_LSB_VSC1S95);

    u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01,
                                      (U2)OXCAN_RX_SYS_NRX_IGR,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PKB_BDB, &u1_t_sgnl);
    u4_t_src_chk  |= ((U4)u1_t_sgnl   << u1_s_ALERT_PKBWAR_PD_LSB_PKB_BDB);
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_PKBWAR_PD_LSB_BDB1S01);

    u1_t_pkbsw_act = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_C_PKBWAR_PKB);
    if(u1_t_pkbsw_act == (U1)IOHW_DIFLT_SWITCH_ACT){
        u4_t_src_chk |= u4_s_ALERT_PKBWAR_PD_BIT_PKB_SW;
    }

    u4_t_src_chk  |= (U4)u1_s_alert_pkbwar_spdjdg_rslt;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_PKBWAR_PD_BIT_IGN_ON;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_pkbwarJdgSpd(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4 u4_s_AlertC_pkbwarJdgSpd(void)
{
    static const U1 u1_sp_ALERT_C_PKBWAR_JDGSPD[ALERT_C_PKBWAR_JDGSPD_NUM] = {
        (U1)ALERT_C_PKBWAR_JDGSPD_OFF,                                         /* 00 OFF                                             */
        (U1)ALERT_C_PKBWAR_JDGSPD_OFF,                                         /* 01 OFF                                             */
        (U1)ALERT_C_PKBWAR_JDGSPD_OFF,                                         /* 02 OFF                                             */
        (U1)ALERT_C_PKBWAR_JDGSPD_ON,                                          /* 03 ON                                              */
        (U1)ALERT_C_PKBWAR_JDGSPD_ON,                                          /* 04 ON                                              */
        (U1)ALERT_C_PKBWAR_JDGSPD_ON,                                          /* 05 ON                                              */
        (U1)ALERT_C_PKBWAR_JDGSPD_ON,                                          /* 06 ON                                              */
        (U1)ALERT_C_PKBWAR_JDGSPD_ON                                           /* 07 ON                                              */
    };

    static const U2 u2_s_ALERT_PKBWAR_SPD_HI_THRESH = (U2)1000U;
    static const U2 u2_s_ALERT_PKBWAR_SPD_MD_THRESH = (U2)500U;
    static const U2 u2_s_ALERT_PKBWAR_SPD_LO_THRESH = (U2)400U;
    static const U1 u1_s_ALERT_PKBWAR_BIT_SPD_LO    = (U1)0x02U;
    static const U1 u1_s_ALERT_PKBWAR_BIT_SPD_MD    = (U1)0x04U;
    static const U1 u1_s_ALERT_PKBWAR_BIT_SPD_HI    = (U1)0x06U;
    U2              u2_t_vehspd;
    U1              u1_t_spdsts;
    U1              u1_t_pkb_jdg;

    u2_t_vehspd  = (U2)0U;
    u1_t_spdsts  = u1_g_AlertSpdKmphInst(&u2_t_vehspd, (U1)TRUE);

    u1_t_pkb_jdg = u1_s_alert_pkbwar_spdjdg_rslt;

    if(u2_t_vehspd   > u2_s_ALERT_PKBWAR_SPD_HI_THRESH){
        u1_t_pkb_jdg |= u1_s_ALERT_PKBWAR_BIT_SPD_HI;
    }
    else if(u2_t_vehspd >= u2_s_ALERT_PKBWAR_SPD_MD_THRESH){
        u1_t_pkb_jdg |= u1_s_ALERT_PKBWAR_BIT_SPD_MD;
    }
    else if(u2_t_vehspd >= u2_s_ALERT_PKBWAR_SPD_LO_THRESH){
        u1_t_pkb_jdg |= u1_s_ALERT_PKBWAR_BIT_SPD_LO;
    }
    else{
        /* Do Nothing */
    }

    if((u1_t_spdsts  == (U1)ALERT_SPD_STSBIT_VALID   ) &&
       (u1_t_pkb_jdg <  (U1)ALERT_C_PKBWAR_JDGSPD_NUM)){
        u1_s_alert_pkbwar_spdjdg_rslt = u1_sp_ALERT_C_PKBWAR_JDGSPD[u1_t_pkb_jdg];
    }
    else{
        u1_s_alert_pkbwar_spdjdg_rslt = (U1)ALERT_C_PKBWAR_JDGSPD_OFF;
    }

    return((U4)u1_s_alert_pkbwar_spdjdg_rslt);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/19/2021  SO       New.                                                                                               */
/*  5.1.0     8/26/2021  RI       Change counter thresh.                                                                             */
/*  5.2.0    10/17/2022  SM       Update for 345D CV(Remove 1 second judgment).                                                      */
/*                                                                                                                                   */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
