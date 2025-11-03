/* 5.3.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_GPF                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_GPF_C_MAJOR                      (5)
#define ALERT_P_GPF_C_MINOR                      (3)
#define ALERT_P_GPF_C_PATCH                      (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_GPF_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_GPF.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_GPF_WRN_NUM_DST                  (38U)
#define ALERT_P_GPF_BC_NUM_DST                   (4U)

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
static U4      u4_s_AlertP_gpfWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_gpfBcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_gpfWrnRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_P_GPF_WRN_CRIT[ALERT_P_GPF_WRN_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 ON                                              */
    (U4)0x00000002U,                                                           /* 01 FLASH1_RW                                       */
    (U4)0x00000003U,                                                           /* 02 FLASH2                                          */
    (U4)0x00000008U,                                                           /* 03 CAUTION                                         */
    (U4)0x00000009U,                                                           /* 04 ON_CAUTION                                      */
    (U4)0x0000000AU,                                                           /* 05 FLSH1_CAU_RW                                    */
    (U4)0x0000000BU,                                                           /* 06 FLASH2_CAU                                      */
    (U4)0x0000000CU,                                                           /* 07 CAUTION                                         */
    (U4)0x00000010U,                                                           /* 08 WARNING_RW                                      */
    (U4)0x00000011U,                                                           /* 09 ON_WRN_RW                                       */
    (U4)0x00000012U,                                                           /* 10 FLSH1_WRN_RW                                    */
    (U4)0x00000013U,                                                           /* 11 FLSH2_WRN_RW                                    */
    (U4)0x00000014U,                                                           /* 12 WARNING_RW                                      */
    (U4)0x00000018U,                                                           /* 13 REGENERATION                                    */
    (U4)0x00000019U,                                                           /* 14 ON_REGEN                                        */
    (U4)0x0000001AU,                                                           /* 15 FLSH1_REG_RW                                    */
    (U4)0x0000001BU,                                                           /* 16 FLASH2_REGEN                                    */
    (U4)0x0000001CU,                                                           /* 17 REGENERATION                                    */
    (U4)0x00000020U,                                                           /* 18 ALERT                                           */
    (U4)0x00000021U,                                                           /* 19 ON_ALT                                          */
    (U4)0x00000022U,                                                           /* 20 FLSH1_ALT_RW                                    */
    (U4)0x00000023U,                                                           /* 21 FLSH2_ALT                                       */
    (U4)0x00000024U,                                                           /* 22 ALERT                                           */
    (U4)0x00000028U,                                                           /* 23 FINISH                                          */
    (U4)0x00000029U,                                                           /* 24 ON_FIN                                          */
    (U4)0x0000002AU,                                                           /* 25 FLSH1_FIN_RW                                    */
    (U4)0x0000002BU,                                                           /* 26 FLSH2_FIN                                       */
    (U4)0x0000002CU,                                                           /* 27 FINISH                                          */
    (U4)0x00000030U,                                                           /* 28 LOW                                             */
    (U4)0x00000031U,                                                           /* 29 ON_LOW                                          */
    (U4)0x00000032U,                                                           /* 30 FLSH1_LOW_RW                                    */
    (U4)0x00000033U,                                                           /* 31 FLSH2_LOW                                       */
    (U4)0x00000034U,                                                           /* 32 LOW                                             */
    (U4)0x00000038U,                                                           /* 33 CAUTION_LVL                                     */
    (U4)0x00000039U,                                                           /* 34 ON_CLVL                                         */
    (U4)0x0000003AU,                                                           /* 35 FLH1_CLVL_RW                                    */
    (U4)0x0000003BU,                                                           /* 36 FLH2_CLVL                                       */
    (U4)0x0000003CU                                                            /* 37 CAUTION_LVL                                     */
};
static const U4  u4_sp_ALERT_P_GPF_WRN_MASK[ALERT_P_GPF_WRN_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 ON                                              */
    (U4)0x0000007FU,                                                           /* 01 FLASH1_RW                                       */
    (U4)0x0000007FU,                                                           /* 02 FLASH2                                          */
    (U4)0x0000007FU,                                                           /* 03 CAUTION                                         */
    (U4)0x0000007FU,                                                           /* 04 ON_CAUTION                                      */
    (U4)0x0000007FU,                                                           /* 05 FLSH1_CAU_RW                                    */
    (U4)0x0000007FU,                                                           /* 06 FLASH2_CAU                                      */
    (U4)0x0000007CU,                                                           /* 07 CAUTION                                         */
    (U4)0x0000007FU,                                                           /* 08 WARNING_RW                                      */
    (U4)0x0000007FU,                                                           /* 09 ON_WRN_RW                                       */
    (U4)0x0000007FU,                                                           /* 10 FLSH1_WRN_RW                                    */
    (U4)0x0000007FU,                                                           /* 11 FLSH2_WRN_RW                                    */
    (U4)0x0000007CU,                                                           /* 12 WARNING_RW                                      */
    (U4)0x0000007FU,                                                           /* 13 REGENERATION                                    */
    (U4)0x0000007FU,                                                           /* 14 ON_REGEN                                        */
    (U4)0x0000007FU,                                                           /* 15 FLSH1_REG_RW                                    */
    (U4)0x0000007FU,                                                           /* 16 FLASH2_REGEN                                    */
    (U4)0x0000007CU,                                                           /* 17 REGENERATION                                    */
    (U4)0x0000007FU,                                                           /* 18 ALERT                                           */
    (U4)0x0000007FU,                                                           /* 19 ON_ALT                                          */
    (U4)0x0000007FU,                                                           /* 20 FLSH1_ALT_RW                                    */
    (U4)0x0000007FU,                                                           /* 21 FLSH2_ALT                                       */
    (U4)0x0000007CU,                                                           /* 22 ALERT                                           */
    (U4)0x0000007FU,                                                           /* 23 FINISH                                          */
    (U4)0x0000007FU,                                                           /* 24 ON_FIN                                          */
    (U4)0x0000007FU,                                                           /* 25 FLSH1_FIN_RW                                    */
    (U4)0x0000007FU,                                                           /* 26 FLSH2_FIN                                       */
    (U4)0x0000007CU,                                                           /* 27 FINISH                                          */
    (U4)0x0000007FU,                                                           /* 28 LOW                                             */
    (U4)0x0000007FU,                                                           /* 29 ON_LOW                                          */
    (U4)0x0000007FU,                                                           /* 30 FLSH1_LOW_RW                                    */
    (U4)0x0000007FU,                                                           /* 31 FLSH2_LOW                                       */
    (U4)0x0000007CU,                                                           /* 32 LOW                                             */
    (U4)0x0000007FU,                                                           /* 33 CAUTION_LVL                                     */
    (U4)0x0000007FU,                                                           /* 34 ON_CLVL                                         */
    (U4)0x0000007FU,                                                           /* 35 FLH1_CLVL_RW                                    */
    (U4)0x0000007FU,                                                           /* 36 FLH2_CLVL                                       */
    (U4)0x0000007CU                                                            /* 37 CAUTION_LVL                                     */
};
static const U1  u1_sp_ALERT_P_GPF_WRN_DST[ALERT_P_GPF_WRN_NUM_DST] = {
    (U1)ALERT_REQ_P_GPF_WRN_ON,                                                /* 00 ON                                              */
    (U1)ALERT_REQ_P_GPF_WRN_FLASH1_RW,                                         /* 01 FLASH1_RW                                       */
    (U1)ALERT_REQ_P_GPF_WRN_FLASH2,                                            /* 02 FLASH2                                          */
    (U1)ALERT_REQ_P_GPF_WRN_CAUTION,                                           /* 03 CAUTION                                         */
    (U1)ALERT_REQ_P_GPF_WRN_ON_CAUTION,                                        /* 04 ON_CAUTION                                      */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_CAU_RW,                                      /* 05 FLSH1_CAU_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLASH2_CAU,                                        /* 06 FLASH2_CAU                                      */
    (U1)ALERT_REQ_P_GPF_WRN_CAUTION,                                           /* 07 CAUTION                                         */
    (U1)ALERT_REQ_P_GPF_WRN_WARNING_RW,                                        /* 08 WARNING_RW                                      */
    (U1)ALERT_REQ_P_GPF_WRN_ON_WRN_RW,                                         /* 09 ON_WRN_RW                                       */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_WRN_RW,                                      /* 10 FLSH1_WRN_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH2_WRN_RW,                                      /* 11 FLSH2_WRN_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_WARNING_RW,                                        /* 12 WARNING_RW                                      */
    (U1)ALERT_REQ_P_GPF_WRN_REGENERATION,                                      /* 13 REGENERATION                                    */
    (U1)ALERT_REQ_P_GPF_WRN_ON_REGEN,                                          /* 14 ON_REGEN                                        */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_REG_RW,                                      /* 15 FLSH1_REG_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLASH2_REGEN,                                      /* 16 FLASH2_REGEN                                    */
    (U1)ALERT_REQ_P_GPF_WRN_REGENERATION,                                      /* 17 REGENERATION                                    */
    (U1)ALERT_REQ_P_GPF_WRN_ALERT,                                             /* 18 ALERT                                           */
    (U1)ALERT_REQ_P_GPF_WRN_ON_ALT,                                            /* 19 ON_ALT                                          */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_ALT_RW,                                      /* 20 FLSH1_ALT_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH2_ALT,                                         /* 21 FLSH2_ALT                                       */
    (U1)ALERT_REQ_P_GPF_WRN_ALERT,                                             /* 22 ALERT                                           */
    (U1)ALERT_REQ_P_GPF_WRN_FINISH,                                            /* 23 FINISH                                          */
    (U1)ALERT_REQ_P_GPF_WRN_ON_FIN,                                            /* 24 ON_FIN                                          */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_FIN_RW,                                      /* 25 FLSH1_FIN_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH2_FIN,                                         /* 26 FLSH2_FIN                                       */
    (U1)ALERT_REQ_P_GPF_WRN_FINISH,                                            /* 27 FINISH                                          */
    (U1)ALERT_REQ_P_GPF_WRN_LOW,                                               /* 28 LOW                                             */
    (U1)ALERT_REQ_P_GPF_WRN_ON_LOW,                                            /* 29 ON_LOW                                          */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH1_LOW_RW,                                      /* 30 FLSH1_LOW_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLSH2_LOW,                                         /* 31 FLSH2_LOW                                       */
    (U1)ALERT_REQ_P_GPF_WRN_LOW,                                               /* 32 LOW                                             */
    (U1)ALERT_REQ_P_GPF_WRN_CAUTION_LVL,                                       /* 33 CAUTION_LVL                                     */
    (U1)ALERT_REQ_P_GPF_WRN_ON_CLVL,                                           /* 34 ON_CLVL                                         */
    (U1)ALERT_REQ_P_GPF_WRN_FLH1_CLVL_RW,                                      /* 35 FLH1_CLVL_RW                                    */
    (U1)ALERT_REQ_P_GPF_WRN_FLH2_CLVL,                                         /* 36 FLH2_CLVL                                       */
    (U1)ALERT_REQ_P_GPF_WRN_CAUTION_LVL                                        /* 37 CAUTION_LVL                                     */
};
static const U1  u1_sp_ALERT_P_GPF_BC_DST[ALERT_P_GPF_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_GPF_BC_SINGLE,                                             /* 01 SINGLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_GPF_MTRX[2] = {
    {
        &u4_s_AlertP_gpfWrnSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_gpfWrnRwTx,                                               /* fp_vd_XDST                                         */

        &u4_sp_ALERT_P_GPF_WRN_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_P_GPF_WRN_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_GPF_WRN_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_P_GPF_WRN_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_gpfBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_GPF_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_P_GPF_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_gpfWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_gpfWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_B_GPFTT) || defined(ComConf_ComSignal_B_GPFMID)
#ifdef ComConf_ComSignal_B_GPFMID
    static const U1 u1_s_ALERT_P_GPFWRN_LSB_B_GPFMID = (U1)3U;
#endif
    static const U1 u1_s_ALERT_P_GPFWRN_LSB_MSGSTS   = (U1)6U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_PDU_RX_CAN_ENG1G97)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#endif /* OXCAN_PDU_RX_CAN_ENG1G97 */

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_GPFWRN_LSB_MSGSTS);

#ifdef ComConf_ComSignal_B_GPFMID
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_GPFMID, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_P_GPFWRN_LSB_B_GPFMID);
#endif /* ComConf_ComSignal_B_GPFMID */

#ifdef ComConf_ComSignal_B_GPFTT
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_GPFTT, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;
#endif /* ComConf_ComSignal_B_GPFTT */

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(ComConf_ComSignal_B_GPFTT) || defined(ComConf_ComSignal_B_GPFMID) */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_gpfBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_gpfBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_B_GPFBZR)
    static const U1 u1_s_ALERT_P_GPFBC_LSB_MSGSTS = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_PDU_RX_CAN_ENG1G97)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#endif /* OXCAN_PDU_RX_CAN_ENG1G97 */

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_GPFBC_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_GPFBZR, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* ComConf_ComSignal_B_GPFBZR */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_gpfWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_gpfWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    static const U4 u4_s_ALERT_P_GPFWRN_CRT      = ((U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLASH1_RW   )
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_CAU_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_WARNING_RW  )
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_ON_WRN_RW   )
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_WRN_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH2_WRN_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_REG_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_ALT_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_FIN_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLSH1_LOW_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLH1_CLVL_RW));
#ifdef ComConf_ComSignal_GPMW /* 460B_CAN */
    static const U4 u4_s_ALERT_P_GPFWRN_CRT_GPMW = ((U4)((U4)1U << ALERT_REQ_P_GPF_WRN_CAUTION_LVL )
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_ON_CLVL     )
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLH1_CLVL_RW)
                                                 |  (U4)((U4)1U << ALERT_REQ_P_GPF_WRN_FLH2_CLVL   ));
    static const U4 u4_s_ALERT_P_GPF_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
#endif /* ComConf_ComSignal_GPMW */
    static const U1 u1_s_ALERT_P_GPFWRN_MSK      = (U1)0x1FU;
    U4              u4_t_rw;
    U1              u1_t_sgnl_gpfw;
#ifdef ComConf_ComSignal_GPMW /* 460B_CAN */
    U1              u1_t_sgnl_gpmw;
#endif /* ComConf_ComSignal_GPMW */

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_P_GPFWRN_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN   ) != (U1)0U) &&
       ((u4_t_rw  & u4_s_ALERT_P_GPFWRN_CRT) != (U4)0U)){
        u1_t_sgnl_gpfw = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl_gpfw = (U1)ALERT_RW_SGNL_OFF;
    }

#ifdef ComConf_ComSignal_GPMW /* 460B_CAN */
    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON)        != (U1)0U                      ) &&
       (u4_a_IGN_TM                              >= u4_s_ALERT_P_GPF_TIM_RW_ENBL) &&
       ((u4_t_rw & u4_s_ALERT_P_GPFWRN_CRT_GPMW) != (U4)0U                      )){
        u1_t_sgnl_gpmw = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl_gpmw = (U1)ALERT_RW_SGNL_OFF;
    }
#endif /* ComConf_ComSignal_GPMW */

    (void)Com_SendSignal(ComConf_ComSignal_GPFW, &u1_t_sgnl_gpfw);
#ifdef ComConf_ComSignal_GPMW /* 460B_CAN */
    (void)Com_SendSignal(ComConf_ComSignal_GPMW, &u1_t_sgnl_gpmw);
#endif /* ComConf_ComSignal_GPMW */
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
/*  5.0.0     3/ 9/2020  MY       New.                                                                                               */
/*  5.1.0     3/19/2021  TN       Change WRN Ch matrix table.                                                                        */
/*  5.2.0     9/ 6/2021  TM       Fix Primary compile switch to ENG1G97.                                                             */
/*  5.3.0    10/25/2021  KT       Add remote warning of GPMW.                                                                        */
/*  5.3.1     1/19/2022  KAT      Update for 840B#2 CV(Version update).                                                              */
/*  5.3.2     7/12/2022  KK       Update for 840B#2 1A(Version update).                                                              */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * KAT  = Katsushi Takahashi, NTTD MSE                                                                                            */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
