/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_PCS1                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_PCS1_C_MAJOR                     (5)
#define ALERT_S_PCS1_C_MINOR                     (5)
#define ALERT_S_PCS1_C_PATCH                     (0)

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
#if (ALERT_S_PCS1_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_PCS1.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_PCS1_BZR_NUM_DST                 (64U)

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
static U4      u4_s_AlertS_pcs1BzrSrcchk    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_PCS1_BZR_DST[ALERT_S_PCS1_BZR_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_PCS1_BZR_NOTICE,                                           /* 01 NOTICE                                          */
    (U1)ALERT_REQ_S_PCS1_BZR_PBA,                                              /* 02 PBA                                             */
    (U1)ALERT_REQ_S_PCS1_BZR_PCS,                                              /* 03 PCS                                             */
    (U1)ALERT_REQ_S_PCS1_BZR_ALM,                                              /* 04 ALM                                             */
    (U1)ALERT_REQ_S_PCS1_BZR_BRK_INSP,                                         /* 05 BRK_INSP                                        */
    (U1)ALERT_REQ_S_PCS1_BZR_RDR_CMP,                                          /* 06 RDR_CMP                                         */
    (U1)ALERT_REQ_S_PCS1_BZR_WRN,                                              /* 07 WRN                                             */
    (U1)ALERT_REQ_S_PCS1_BZR_CMR_CMP,                                          /* 08 CMR_CMP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_PCS1_MTRX[1] = {
    {
        &u4_s_AlertS_pcs1BzrSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_PCS1_BZR_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_S_PCS1_BZR_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#warning "BEVCDCFD-1483"
#if 0 /* BEVCDCFD-1483 */
#else /* BEVCDCFD-1483 */
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1TtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1TtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSINDI)
    static const U1 u1_s_ALERT_S_PCS1_TT_LSB_MSG   = (U1)2U;
    static const U2 u2_s_ALERT_S_PCS1_TT_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_TT_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSINDI, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_TT_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSINDI) */
}
#endif /* BEVCDCFD-1483 */

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1BzrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1BzrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSMTBZ2)
    static const U1 u1_s_ALERT_S_PCS1_BZR_LSB_MSG  = (U1)4U;
    static const U2 u2_s_ALERT_S_PCS1_BZ_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_BZ_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSMTBZ2, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_BZR_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSMTBZ2) */
}

#warning "BEVCDCFD-1483"
#if 0 /* BEVCDCFD-1483 */
#else /* BEVCDCFD-1483 */
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1PcswmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1PcswmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSWM) && defined(ComConf_ComSignal_PCSWDUCT)
    static const U1 u1_s_ALERT_S_PCS1_WM_LSB_MSG   = (U1)3U;
    static const U1 u1_s_ALERT_S_PCS1_WM_LSB_DUCT  = (U1)2U;
    static const U2 u2_s_ALERT_S_PCS1_WM_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_WM_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSWM, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSWDUCT, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_S_PCS1_WM_LSB_DUCT);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_WM_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSWM) && defined(ComConf_ComSignal_PCSWDUCT) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1FssSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1FssSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_FSSINFO)
    static const U1 u1_s_ALERT_S_PCS1_FSS_LSB_MSG   = (U1)3U;
    static const U2 u2_s_ALERT_S_PCS1_FSS_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_FSS_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSSINFO, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_FSS_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_FSSINFO) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1PcsrtwmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1PcsrtwmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSRTWM)
    static const U1 u1_s_ALERT_S_PCS1_RTWM_LSB_MSG   = (U1)2U;
    static const U2 u2_s_ALERT_S_PCS1_RTWM_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_RTWM_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSRTWM, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_RTWM_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSRTWM) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pcs1PcsswmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pcs1PcsswmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if  defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSSWM)
    static const U1 u1_s_ALERT_S_PCS1_SWM_LSB_MSG   = (U1)1U;
    static const U2 u2_s_ALERT_S_PCS1_SWM_THRESH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_PCS1_SWM_THRESH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSSWM, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_PCS1_SWM_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_DS12F02_CH0) && defined(ComConf_ComSignal_PCSSWM) */
}
#endif /* BEVCDCFD-1483 */

/*===================================================================================================================================*/ev
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/25/2020  TH       New.                                                                                               */
/*  5.1.0     8/27/2020  SO       Modify matrix table for PCSWM.                                                                     */
/*  5.2.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.3.0     4/ 8/2021  SO       Add CH for PCSBDM.                                                                                 */
/*  5.3.1     6/30/2021  MO       Update for 050D CV(Version update).                                                                */
/*  5.3.2     8/ 4/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.4.0    11/ 7/2023  PG       Update for 19PFv3.                                                                                 */
/*                                - Updated PCSWM & FSS MID Display Matrix                                                           */
/*                                - Deleted PCSBDM MID Display                                                                       */
/*                                - Added PCSSWM MID Display                                                                         */
/*  5.5.0     6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0,MET-S_ADTT-CSTD-0-02-A-C0)       */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
