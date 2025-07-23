/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_PEXI                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_PEXI_C_MAJOR                     (5)
#define ALERT_H_PEXI_C_MINOR                     (4)
#define ALERT_H_PEXI_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_PEXI_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_PEXI.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_PEXI_TT_NUM_DST                  (64U)
#define ALERT_H_PEXI_WARN_NUM_DST                (8U)

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
static U4      u4_s_AlertH_pexiTtSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_pexiWarnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_PEXI_TT_DST[ALERT_H_PEXI_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_TT_PRMRYCHK,                                          /* 05 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 08 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 09 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 10 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 11 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 12 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 13 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 14 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 15 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 24 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 25 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 26 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 27 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 28 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 29 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 30 MALFUNC                                         */
    (U1)ALERT_REQ_H_PEXI_TT_MALFUNC,                                           /* 31 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_TT_PRMRYCHK,                                          /* 37 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_TT_PRMRYCHK,                                          /* 45 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 57 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_PEXI_WARN_DST[ALERT_H_PEXI_WARN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_PEXI_WARN_MALFUNC,                                         /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_PEXI_MTRX[2] = {
    {
        &u4_s_AlertH_pexiTtSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_PEXI_TT_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_H_PEXI_TT_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_pexiWarnSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_PEXI_WARN_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_PEXI_WARN_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_pexiTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_pexiTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_PEXI_TT_LSB_NDBW    = (U1)3U;
    static const U1 u1_s_ALERT_H_PEXI_TT_LSB_EHV1S90 = (U1)5U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_SOCLOWID)
    static const U1 u1_s_ALERT_H_PEXI_TT_LSB_EHV1S94 = (U1)4U;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_SOCLOWID) */
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_NDBW
    (void)Com_ReceiveSignal(ComConf_ComSignal_NDBW, &u1_t_sgnl);
#endif /* ComConf_ComSignal_NDBW */ /* 840B_CAN */
    u4_t_src_chk  = ((U4)u1_t_sgnl   << u1_s_ALERT_H_PEXI_TT_LSB_NDBW);

#if defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S90_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0) */ /* 840B_CAN */
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_PEXI_TT_LSB_EHV1S90);

#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_SOCLOWID)
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_SOCLOWID, &u1_t_sgnl);
#endif
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
                                          (U4)OXCAN_SYS_IGP,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_PEXI_TT_LSB_EHV1S94);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_SOCLOWID) */

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_pexiWarnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_pexiWarnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_PEXI_WARN_LSB_MSG   = (U1)1U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0)
    static const U2 u2_s_ALERT_H_PEXI_WARN_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0) */ /* 840B_CAN */
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_NDBW
    (void)Com_ReceiveSignal(ComConf_ComSignal_NDBW, &u1_t_sgnl);
#endif /* ComConf_ComSignal_NDBW */ /* 840B_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S90_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_H_PEXI_WARN_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S90_CH0) */ /* 840B_CAN */
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_PEXI_WARN_LSB_MSG);

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
/*  5.0.0     2/21/2019  SN       New.                                                                                               */
/*  5.0.1    10/08/2019  DS       Add compile switch.                                                                                */
/*  5.1.0     2/ 6/2020  MY       Fix WARN matrix table.                                                                             */
/*  5.2.0     4/ 1/2020  ZS       Change module name to 800B spec.                                                                   */
/*  5.3.0     6/ 1/2020  ZS       Fix WARN matrix table.                                                                             */
/*  5.4.0     3/16/2021  SO       Change CH name.                                                                                    */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
