/* 5.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  alert_S_ADBZR_LTA                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ADBZR_LTA_C_MAJOR                    (5)
#define ALERT_S_ADBZR_LTA_C_MINOR                    (2)
#define ALERT_S_ADBZR_LTA_C_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_ADBZR_LTA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_ADBZR_LTA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ADBZR_LTA_LKA_NUM_DST            (4U)
#define ALERT_S_ADBZR_LTA_LTA_NUM_DST            (16U)

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
static U4      u4_s_AlertS_adbzr_ltaLkaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_adbzr_ltaLtaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_ADBZR_LTA_LKA_DST[ALERT_S_ADBZR_LTA_LKA_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ADBZR_LTA_LKA_DBL,                                         /* 01 DBL                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_S_ADBZR_LTA_LTA_DST[ALERT_S_ADBZR_LTA_LTA_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN1,                                        /* 01 PTN1                                            */
    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN2,                                        /* 02 PTN2                                            */
    (U1)ALERT_REQ_S_ADBZR_LTA_LTA_PTN3,                                        /* 03 PTN3                                            */
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
const ST_ALERT_MTRX st_gp_ALERT_S_ADBZR_LTA_MTRX[2] = {
    {
        &u4_s_AlertS_adbzr_ltaLkaSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ADBZR_LTA_LKA_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_S_ADBZR_LTA_LKA_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_adbzr_ltaLtaSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ADBZR_LTA_LTA_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_S_ADBZR_LTA_LTA_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_adbzr_ltaLkaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_adbzr_ltaLkaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_S_ADBZR_LTA_LKA_LSB = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LKACB, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ADBZR_LTA_LKA_LSB);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_adbzr_ltaLtaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_adbzr_ltaLtaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_S_ADBZR_LTA_BLTA_TO  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);                  /*For THRESH/Judgement time*/
    static const U1 u1_s_ALERT_S_ADBZR_LTA_BLTA_LSB = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_S_ADBZR_LTA_BLTA_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LTABZR, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_ADBZR_LTA_BLTA_LSB);

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
/*  5.0.0    11/08/2023  AA       New.                                                                                               */
/*  5.1.0     6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0,MET-S_ADTT-CSTD-0-02-A-C0)       */
/*  5.2.0    11/13/2025  SH       Configured for BevStep3                                                                            */
/*  5.2.1    12/18/2025  DT       Change for BEV System_Consideration_ADAS.(MET-S_ADBZR-CSTD-0-06-A-C0)                              */
/*                                                                                                                                   */
/*  * AA   = Anna Asuncion, DTJP                                                                                                     */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * DT   = Dj Tutanes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
