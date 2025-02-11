/* 5.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_4WDSYS                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_4WDSYS_C_MAJOR                   (5)
#define ALERT_D_4WDSYS_C_MINOR                   (6)
#define ALERT_D_4WDSYS_C_PATCH                   (0)

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
#if (ALERT_D_4WDSYS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_4WDSYS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_4WDSYS_TT_NUM_DST                (9U)
#define ALERT_D_4WDSYS_PD_B4_NUM_DST             (8U)
#define ALERT_D_4WDSYS_PD_H4_NUM_DST             (8U)

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
static U4      u4_s_AlertD_4wdsysTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_4wdsysPdB4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_4wdsysPdH4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_D_4WDSYS_TT_DST[ALERT_D_4WDSYS_TT_NUM_DST] = {
    (U1)ALERT_REQ_D_4WDSYS_TT_OVRHEAT,                                         /* 00 OVRHEAT                                         */
    (U1)ALERT_REQ_D_4WDSYS_TT_PREWRN,                                          /* 01 PREWRN                                          */
    (U1)ALERT_REQ_D_4WDSYS_TT_MALFUNC,                                         /* 02 MALFUNC                                         */
    (U1)ALERT_REQ_D_4WDSYS_TT_OVRHEAT,                                         /* 03 OVRHEAT                                         */
    (U1)ALERT_REQ_D_4WDSYS_TT_ACTTEST,                                         /* 04 ACTTEST                                         */
    (U1)ALERT_REQ_D_4WDSYS_TT_TSTMODE,                                         /* 05 TSTMODE                                         */
    (U1)ALERT_REQ_D_4WDSYS_TT_PREWRN,                                          /* 06 PREWRN                                          */
    (U1)ALERT_REQ_D_4WDSYS_TT_INICHK,                                          /* 07 INICHK                                          */
    (U1)ALERT_REQ_D_4WDSYS_TT_MALFUNC                                          /* 08 MALFUNC                                         */
};
static const U4  u4_sp_ALERT_D_4WDSYS_TT_CRIT[ALERT_D_4WDSYS_TT_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 OVRHEAT                                         */
    (U4)0x00000005U,                                                           /* 01 PREWRN                                          */
    (U4)0x00000007U,                                                           /* 02 MALFUNC                                         */
    (U4)0x00000010U,                                                           /* 03 OVRHEAT                                         */
    (U4)0x00000030U,                                                           /* 04 ACTTEST                                         */
    (U4)0x00000040U,                                                           /* 05 TSTMODE                                         */
    (U4)0x00000050U,                                                           /* 06 PREWRN                                          */
    (U4)0x00000060U,                                                           /* 07 INICHK                                          */
    (U4)0x00000070U                                                            /* 08 MALFUNC                                         */
};
static const U4  u4_sp_ALERT_D_4WDSYS_TT_MASK[ALERT_D_4WDSYS_TT_NUM_DST] = {
    (U4)0x0000000FU,                                                           /* 00 OVRHEAT                                         */
    (U4)0x0000000FU,                                                           /* 01 PREWRN                                          */
    (U4)0x0000000FU,                                                           /* 02 MALFUNC                                         */
    (U4)0x000000F0U,                                                           /* 03 OVRHEAT                                         */
    (U4)0x000000F0U,                                                           /* 04 ACTTEST                                         */
    (U4)0x000000F0U,                                                           /* 05 TSTMODE                                         */
    (U4)0x000000F0U,                                                           /* 06 PREWRN                                          */
    (U4)0x000000F0U,                                                           /* 07 INICHK                                          */
    (U4)0x000000F0U                                                            /* 08 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_D_4WDSYS_PD_B4_DST[ALERT_D_4WDSYS_PD_B4_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_B4_OVRHEAT,                                      /* 01 OVRHEAT                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_B4_MALFUNC,                                      /* 03 MALFUNC                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_B4_TSTMODE,                                      /* 04 TSTMODE                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_B4_PREWRN,                                       /* 05 PREWRN                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_B4_MALFUNC                                       /* 07 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_D_4WDSYS_PD_H4_DST[ALERT_D_4WDSYS_PD_H4_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_H4_OVRHEAT,                                      /* 01 OVRHEAT                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_H4_PREWRN,                                       /* 05 PREWRN                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_D_4WDSYS_PD_H4_MALFUNC                                       /* 07 MALFUNC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_4WDSYS_MTRX[3] = {
    {
        &u4_s_AlertD_4wdsysTtSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_4WDSYS_TT_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_D_4WDSYS_TT_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_4WDSYS_TT_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_D_4WDSYS_TT_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_4wdsysPdB4Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_4WDSYS_PD_B4_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_D_4WDSYS_PD_B4_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_4wdsysPdH4Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_4WDSYS_PD_H4_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_D_4WDSYS_PD_H4_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_4wdsysTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_4wdsysTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_4WDSYS_LSB_EHV1S26 = (U1)3U;
    static const U1 u1_s_ALERT_D_4WDSYS_LSB_B_4WD   = (U1)4U;
    static const U1 u1_s_ALERT_D_4WDSYS_LSB_FWD1S90 = (U1)7U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_4WDSYS_LSB_EHV1S26);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HV4WNG, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FWD1S90,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_4WDSYS_LSB_FWD1S90);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_4WD, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_D_4WDSYS_LSB_B_4WD);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_4wdsysPdB4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_4wdsysPdB4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_4WDSYS_LSB_FWD1S90 = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FWD1S90,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_4WDSYS_LSB_FWD1S90);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_4WD, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_4wdsysPdH4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_4wdsysPdH4Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_4WDSYS_LSB_EHV1S26 = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_4WDSYS_LSB_EHV1S26);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HV4WNG, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

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
/*  5.0.0     3/ 9/2020  TH       New.                                                                                               */
/*  5.0.1     4/22/2020  DS       Devide module for power train.                                                                     */
/*  5.0.2     9/ 2/2020  MO       Renamed file.                                                                                      */
/*  5.1.0    12/15/2020  KT       Update for 032D CV(Version update).                                                                */
/*  5.1.1     7/ 1/2021  SO       Update for 050D CV(Version update).                                                                */
/*  5.1.2     7/12/2022  KK       Update for 840B #2 1A(Version update).                                                             */
/*  5.2.0    12/25/2023  RO       Update for 19PFv3(Version update).                                                                 */
/*  5.3.0     3/12/2024  RO       Update for 19PFv3 CV.                                                                              */
/*  5.4.0     3/27/2024  AA       Applied remote warning of FWW                                                                      */
/*  5.5.0     4/17/2024  AA       Removed remote warning                                                                             */
/*  5.6.0     6/18/2024  RO       Add warning correction                                                                             */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
