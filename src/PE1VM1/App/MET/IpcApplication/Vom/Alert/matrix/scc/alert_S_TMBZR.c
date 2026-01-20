/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_TMBZR                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_TMBZR_C_MAJOR                         (5)
#define ALERT_S_TMBZR_C_MINOR                         (0)
#define ALERT_S_TMBZR_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_TMBZR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_TMBZR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_TMBZR_BC_AD_NUM_DST              (36U)
#define ALERT_S_TMBZR_BC_DOT_NUM_DST             (8U)

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
static U4     u4_s_AlertS_tmbzrBcAdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4     u4_s_AlertS_tmbzrBcDotSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_S_TMBZR_BC_AD_CRIT[ALERT_S_TMBZR_BC_AD_NUM_DST] = {
    (U4)0x00000200U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000100U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 02 CONT_0                                          */
    (U4)0x00000002U,                                                           /* 03 TEN_0                                           */
    (U4)0x00000005U,                                                           /* 04 RJT_0                                           */
    (U4)0x00000006U,                                                           /* 05 RCV_0                                           */
    (U4)0x00000007U,                                                           /* 06 ANN_0                                           */
    (U4)0x00000011U,                                                           /* 07 CONT_1                                          */
    (U4)0x00000012U,                                                           /* 08 TEN_1                                           */
    (U4)0x00000015U,                                                           /* 09 RJT_1                                           */
    (U4)0x00000016U,                                                           /* 10 RCV_1                                           */
    (U4)0x00000017U,                                                           /* 11 ANN_1                                           */
    (U4)0x00000021U,                                                           /* 12 CONT_2                                          */
    (U4)0x00000022U,                                                           /* 13 TEN_2                                           */
    (U4)0x00000025U,                                                           /* 14 RJT_2                                           */
    (U4)0x00000026U,                                                           /* 15 RCV_2                                           */
    (U4)0x00000027U,                                                           /* 16 ANN_2                                           */
    (U4)0x00000031U,                                                           /* 17 CONT_3                                          */
    (U4)0x00000032U,                                                           /* 18 TEN_3                                           */
    (U4)0x00000035U,                                                           /* 19 RJT_3                                           */
    (U4)0x00000036U,                                                           /* 20 RCV_3                                           */
    (U4)0x00000037U,                                                           /* 21 ANN_3                                           */
    (U4)0x00000041U,                                                           /* 22 CONT_4                                          */
    (U4)0x00000042U,                                                           /* 23 TEN_4                                           */
    (U4)0x00000045U,                                                           /* 24 RJT_4                                           */
    (U4)0x00000046U,                                                           /* 25 RCV_4                                           */
    (U4)0x00000047U,                                                           /* 26 ANN_4                                           */
    (U4)0x00000055U,                                                           /* 27 RJT_4P5                                         */
    (U4)0x00000056U,                                                           /* 28 RCV_4P5                                         */
    (U4)0x00000057U,                                                           /* 29 ANN_4P5                                         */
    (U4)0x00000061U,                                                           /* 30 CONT_5                                          */
    (U4)0x00000063U,                                                           /* 31 TEN_5                                           */
    (U4)0x00000073U,                                                           /* 32 TEN_6                                           */
    (U4)0x00000083U,                                                           /* 33 TEN_6P5                                         */
    (U4)0x00000093U,                                                           /* 34 TEN_7                                           */
    (U4)0x000000A4U                                                            /* 35 TEN_8                                           */
};

static const U4  u4_sp_ALERT_S_TMBZR_BC_AD_MASK[ALERT_S_TMBZR_BC_AD_NUM_DST] = {
    (U4)0x00000200U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000300U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000003FFU,                                                           /* 02 CONT_0                                          */
    (U4)0x000003FFU,                                                           /* 03 TEN_0                                           */
    (U4)0x000003FFU,                                                           /* 04 RJT_0                                           */
    (U4)0x000003FFU,                                                           /* 05 RCV_0                                           */
    (U4)0x000003FFU,                                                           /* 06 ANN_0                                           */
    (U4)0x000003FFU,                                                           /* 07 CONT_1                                          */
    (U4)0x000003FFU,                                                           /* 08 TEN_1                                           */
    (U4)0x000003FFU,                                                           /* 09 RJT_1                                           */
    (U4)0x000003FFU,                                                           /* 10 RCV_1                                           */
    (U4)0x000003FFU,                                                           /* 11 ANN_1                                           */
    (U4)0x000003FFU,                                                           /* 12 CONT_2                                          */
    (U4)0x000003FFU,                                                           /* 13 TEN_2                                           */
    (U4)0x000003FFU,                                                           /* 14 RJT_2                                           */
    (U4)0x000003FFU,                                                           /* 15 RCV_2                                           */
    (U4)0x000003FFU,                                                           /* 16 ANN_2                                           */
    (U4)0x000003FFU,                                                           /* 17 CONT_3                                          */
    (U4)0x000003FFU,                                                           /* 18 TEN_3                                           */
    (U4)0x000003FFU,                                                           /* 19 RJT_3                                           */
    (U4)0x000003FFU,                                                           /* 20 RCV_3                                           */
    (U4)0x000003FFU,                                                           /* 21 ANN_3                                           */
    (U4)0x000003FFU,                                                           /* 22 CONT_4                                          */
    (U4)0x000003FFU,                                                           /* 23 TEN_4                                           */
    (U4)0x000003FFU,                                                           /* 24 RJT_4                                           */
    (U4)0x000003FFU,                                                           /* 25 RCV_4                                           */
    (U4)0x000003FFU,                                                           /* 26 ANN_4                                           */
    (U4)0x000003FFU,                                                           /* 27 RJT_4P5                                         */
    (U4)0x000003FFU,                                                           /* 28 RCV_4P5                                         */
    (U4)0x000003FFU,                                                           /* 29 ANN_4P5                                         */
    (U4)0x000003FFU,                                                           /* 30 CONT_5                                          */
    (U4)0x000003FFU,                                                           /* 31 TEN_5                                           */
    (U4)0x000003FFU,                                                           /* 32 TEN_6                                           */
    (U4)0x000003FFU,                                                           /* 33 TEN_6P5                                         */
    (U4)0x000003FFU,                                                           /* 34 TEN_7                                           */
    (U4)0x000003FFU                                                            /* 35 TEN_8                                           */
};

static const U1  u1_sp_ALERT_S_TMBZR_BC_AD_DST[ALERT_S_TMBZR_BC_AD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_0,                                        /* 02 CONT_0                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_0,                                         /* 03 TEN_0                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_0,                                         /* 04 RJT_0                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_0,                                         /* 05 RCV_0                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_0,                                         /* 06 ANN_0                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_1,                                        /* 07 CONT_1                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_1,                                         /* 08 TEN_1                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_1,                                         /* 09 RJT_1                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_1,                                         /* 10 RCV_1                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_1,                                         /* 11 ANN_1                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_2,                                        /* 12 CONT_2                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_2,                                         /* 13 TEN_2                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_2,                                         /* 14 RJT_2                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_2,                                         /* 15 RCV_2                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_2,                                         /* 16 ANN_2                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_3,                                        /* 17 CONT_3                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_3,                                         /* 18 TEN_3                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_3,                                         /* 19 RJT_3                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_3,                                         /* 20 RCV_3                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_3,                                         /* 21 ANN_3                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_4,                                        /* 22 CONT_4                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_4,                                         /* 23 TEN_4                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_4,                                         /* 24 RJT_4                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_4,                                         /* 25 RCV_4                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_4,                                         /* 26 ANN_4                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RJT_4P5,                                       /* 27 RJT_4P5                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_RCV_4P5,                                       /* 28 RCV_4P5                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_ANN_4P5,                                       /* 29 ANN_4P5                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_CONT_5,                                        /* 30 CONT_5                                          */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_5,                                         /* 31 TEN_5                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_6,                                         /* 32 TEN_6                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_6P5,                                       /* 33 TEN_6P5                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_7,                                         /* 34 TEN_7                                           */
    (U1)ALERT_REQ_S_TMBZR_BC_AD_TEN_8                                          /* 35 TEN_8                                           */
};

static const U1  u1_sp_ALERT_S_TMBZR_BC_DOT_DST[ALERT_S_TMBZR_BC_DOT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_TMBZR_BC_DOT_DOHREQ,                                       /* 01 DOHREQ                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_TMBZR_MTRX[2] = {
    {
        &u4_s_AlertS_tmbzrBcAdSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_TMBZR_BC_AD_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_S_TMBZR_BC_AD_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_TMBZR_BC_AD_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_S_TMBZR_BC_AD_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_tmbzrBcDotSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_TMBZR_BC_DOT_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_S_TMBZR_BC_DOT_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4     u4_s_AlertS_tmbzrBcAdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4     u4_s_AlertS_tmbzrBcAdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1          u1_s_ALERT_S_TMBZR_LSB_MSGSTS = (U1)8U;
    static const U2          u2_s_ALERT_S_TMBZR_THRESH_TO  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1                       u1_t_msgsts;
    U1                       u1_t_sgnl;
    U4                       u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_S_TMBZR_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ADBZRQ, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= (U4)u1_t_msgsts << u1_s_ALERT_S_TMBZR_LSB_MSGSTS;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4     u4_s_AlertS_tmbzrBcDotSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4     u4_s_AlertS_tmbzrBcDotSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1          u1_s_ALERT_S_TMBZR_LSB_MSGSTS = (U1)1U;
    static const U2          u2_s_ALERT_S_TMBZR_THRESH_TO  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1                       u1_t_msgsts;
    U1                       u1_t_sgnl;
    U4                       u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,
                                      (U4)OXCAN_SYS_IGR | (U4)OXCAN_SYS_IGP,
                                      u2_s_ALERT_S_TMBZR_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ADDOTRML, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= (U4)u1_t_msgsts << u1_s_ALERT_S_TMBZR_LSB_MSGSTS;

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
/*  5.0.0    11/28/2025  HL       New.                                                                                               */
/*                                                                                                                                   */
/*  * HL   = Harry Lapiceros, DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
