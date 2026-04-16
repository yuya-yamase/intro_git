/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_ABS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_ABS_C_MAJOR                      (5)
#define ALERT_C_ABS_C_MINOR                      (4)
#define ALERT_C_ABS_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_ABS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_ABS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_ABS_TT_NUM_DST                   (32U)
#define ALERT_C_ABS_PD_NUM_DST                   (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_absTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_absPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_ABS_TT_DST[ALERT_C_ABS_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ABS_TT_FLASH_4HZ,                                          /* 02 FLASH_4HZ                                       */
    (U1)ALERT_REQ_C_ABS_TT_ON,                                                 /* 03 ON                                              */
    (U1)ALERT_REQ_C_ABS_TT_FLASH_1HZ,                                          /* 04 FLASH_1HZ                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 07 ASIL_ON                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 16 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 17 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 18 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 19 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 20 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 21 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 22 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 23 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 24 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 25 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 26 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 27 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 28 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 29 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON,                                            /* 30 ASIL_ON                                         */
    (U1)ALERT_REQ_C_ABS_TT_ASIL_ON                                             /* 31 ASIL_ON                                         */
};
static const U1  u1_sp_ALERT_C_ABS_PD_DST[ALERT_C_ABS_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ABS_PD_MALFUNC,                                            /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_ABS_PD_MALFUNC,                                            /* 04 MALFUNC                                         */
    (U1)ALERT_REQ_C_ABS_PD_MALFUNC,                                            /* 05 MALFUNC                                         */
    (U1)ALERT_REQ_C_ABS_PD_MALFUNC,                                            /* 06 MALFUNC                                         */
    (U1)ALERT_REQ_C_ABS_PD_MALFUNC                                             /* 07 MALFUNC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_ABS_MTRX[2] = {
    {
        &u4_s_AlertC_absTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_ABS_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_ABS_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_absPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_ABS_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_ABS_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_absTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_absTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_ABS_TT_THRSH_TO   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_ABS_TT_LSB_COMSTS = (U1)3U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_C_ABS_TT_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ABS, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_ABS_TT_LSB_COMSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_absPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_absPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_ABS_PD_THRSH_TO   = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_ABS_PD_LSB_COMSTS = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_C_ABS_PD_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ABS_MID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_ABS_PD_LSB_COMSTS);

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
/*  5.0.0     3/24/2020  MY       New.                                                                                               */
/*  5.1.0     8/24/2020  TI       Delete Low-voltage Jugdment.                                                                       */
/*  5.2.0     1/13/2026  HT       Change for Full_function2 (MET-M_REMWAR-CSTD-2-04-A-C0)                                            */
/*                                Removed "ALERT_REQ" in order to transfer signal transmission control from the MCU to the SoC       */
/*  5.3.0     4/ 6/2026  HY       Change for Electronic CV (MET-M_REMWAR-CSTD-2-05-A-C0)                                             */
/*                                Remove the remote warning signal receiving process.                                                */
/*  5.4.0     4/13/2026  KO       Change for BEV Electronic CV. (Add TT abnormality monitoring)                                      */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
