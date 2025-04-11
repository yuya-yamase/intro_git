/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRKHLD                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRKHLD_C_MAJOR                   (5)
#define ALERT_C_BRKHLD_C_MINOR                   (4)
#define ALERT_C_BRKHLD_C_PATCH                   (0)

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
#if (ALERT_C_BRKHLD_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRKHLD.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRKHLD_STBY_NUM_DST              (32U)
#define ALERT_C_BRKHLD_HLD_NUM_DST               (16U)
#define ALERT_C_BRKHLD_WRN_NUM_DST               (32U)
#define ALERT_C_BRKHLD_RW_NUM_DST                (4U)

#define ALERT_C_BRKHLD_NUM_RWSGNL                (2U)
#define ALERT_C_BRKHLD_BHEXIST_BIT               (0x80U)

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
static U4      u4_s_AlertC_brkhldStbySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_brkhldHldSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_brkhldWrnSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_brkhldRwSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_brkhldRwRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_BRKHLD_STBY_DST[ALERT_C_BRKHLD_STBY_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRKHLD_STBY_ON,                                            /* 02 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_C_BRKHLD_HLD_DST[ALERT_C_BRKHLD_HLD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRKHLD_HLD_ON,                                             /* 02 ON                                              */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 03 FLASH                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 08 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 09 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 10 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 11 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 12 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 13 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,                                          /* 14 FLASH                                           */
    (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH                                           /* 15 FLASH                                           */
};
static const U1  u1_sp_ALERT_C_BRKHLD_WRN_DST[ALERT_C_BRKHLD_WRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_MALFNC1,                                        /* 01 MALFNC1                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_MALFNC2,                                        /* 02 MALFNC2                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_WRN1,                                           /* 03 WRN1                                            */
    (U1)ALERT_REQ_C_BRKHLD_WRN_ACT,                                            /* 04 ACT                                             */
    (U1)ALERT_REQ_C_BRKHLD_WRN_WRN2,                                           /* 05 WRN2                                            */
    (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL1,                                        /* 06 UNAVBL1                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL2,                                        /* 07 UNAVBL2                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL3,                                        /* 08 UNAVBL3                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT1,                                         /* 09 MAINT1                                          */
    (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT2,                                         /* 10 MAINT2                                          */
    (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT3,                                         /* 11 MAINT3                                          */
    (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL4,                                        /* 12 UNAVBL4                                         */
    (U1)ALERT_REQ_C_BRKHLD_WRN_DEACT1,                                         /* 13 DEACT1                                          */
    (U1)ALERT_REQ_C_BRKHLD_WRN_DEACT2,                                         /* 14 DEACT2                                          */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_C_BRKHLD_RW_CRIT[ALERT_C_BRKHLD_RW_NUM_DST] = {
    (U4)0x00000041U,                                                           /* 00 AHSW                                            */
    (U4)0x00000042U,                                                           /* 01 AHSW                                            */
    (U4)0x00000070U,                                                           /* 02 AHSWEXIST                                       */
    (U4)0x00000100U                                                            /* 03 AHSWEXIST                                       */
};
static const U4  u4_sp_ALERT_C_BRKHLD_RW_MASK[ALERT_C_BRKHLD_RW_NUM_DST] = {
    (U4)0x000001CFU,                                                           /* 00 AHSW                                            */
    (U4)0x000001CFU,                                                           /* 01 AHSW                                            */
    (U4)0x000001F0U,                                                           /* 02 AHSWEXIST                                       */
    (U4)0x00000100U                                                            /* 03 AHSWEXIST                                       */
};
static const U1  u1_sp_ALERT_C_BRKHLD_RW_DST[ALERT_C_BRKHLD_RW_NUM_DST] = {
    (U1)ALERT_REQ_C_BRKHLD_RW_AHSW,                                            /* 00 AHSW                                            */
    (U1)ALERT_REQ_C_BRKHLD_RW_AHSW,                                            /* 01 AHSW                                            */
    (U1)ALERT_REQ_C_BRKHLD_RW_AHSWEXIST,                                       /* 02 AHSWEXIST                                       */
    (U1)ALERT_REQ_C_BRKHLD_RW_AHSWEXIST                                        /* 03 AHSWEXIST                                       */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRKHLD_MTRX[4] = {
    {
        &u4_s_AlertC_brkhldStbySrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRKHLD_STBY_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_C_BRKHLD_STBY_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_brkhldHldSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRKHLD_HLD_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_BRKHLD_HLD_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_brkhldWrnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRKHLD_WRN_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_BRKHLD_WRN_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_brkhldRwSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_brkhldRwRwTx,                                             /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_BRKHLD_RW_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_C_BRKHLD_RW_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRKHLD_RW_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_C_BRKHLD_RW_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkhldStbySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brkhldStbySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINDC)
    static const U2 u2_s_ALERT_C_BRKHLD_STBY_THR_TO  = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_BRKHLD_STBY_LSB_VSC = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_BRKHLD_STBY_THR_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_BRKHLD_STBY_LSB_VSC);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_DAINDC, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINDC) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkhldHldSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brkhldHldSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINDP)
    static const U2 u2_s_ALERT_C_BRKHLD_HLD_THR_TO  = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_BRKHLD_HLD_LSB_VSC = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_BRKHLD_HLD_THR_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_BRKHLD_HLD_LSB_VSC);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_DAINDP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINDP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkhldWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brkhldWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINFO)
    static const U1 u1_s_ALERT_C_BRKHLD_WRN_LSB_VSC = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_BRKHLD_WRN_LSB_VSC);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_DAINFO, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_DAINFO) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkhldRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brkhldRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_DDRTWV)
    static const U2 u2_s_ALERT_C_BRKHLD_RW_THR_TO    = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
#ifdef ComConf_ComSignal_B_DAINDP
    static const U1 u1_s_ALERT_C_BRKHLD_RW_LSB_NDP   = (U1)4U;
#endif /* ComConf_ComSignal_B_DAINDP */
    static const U1 u1_s_ALERT_C_BRKHLD_RW_LSB_DDRTW = (U1)6U;
    static const U1 u1_s_ALERT_C_BRKHLD_RW_LSB_VSC   = (U1)7U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_BRKHLD_RW_THR_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_BRKHLD_RW_LSB_VSC);

#ifdef ComConf_ComSignal_B_DAINFO
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_DAINFO, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;
#endif /* ComConf_ComSignal_B_DAINFO */
#ifdef ComConf_ComSignal_B_DAINDP
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_DAINDP, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_BRKHLD_RW_LSB_NDP);
#endif /* ComConf_ComSignal_B_DAINDP */
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DDRTWV, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_BRKHLD_RW_LSB_DDRTW);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_DDRTWV) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_brkhldRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_brkhldRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_sp_ALERT_C_BRKHLD_RWTX_CRT[ALERT_C_BRKHLD_NUM_RWSGNL] = {
        ((U1)((U1)1U << ALERT_REQ_C_BRKHLD_RW_AHSWEXIST) | (U1)ALERT_C_BRKHLD_BHEXIST_BIT),
         (U1)((U1)1U << ALERT_REQ_C_BRKHLD_RW_AHSW     )   /* No need BHEXIST */
    };
    U4              u4_t_idx;
    U1              u1_t_sgnl;
    U1              u1_t_rw;
    U1              u1_t_esopt_bh;

    u1_t_esopt_bh = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_BRKHLD_BHEXIST);

    u1_t_rw  = (U1)0U;
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U               ) &&
       (u1_a_DST                          != (U1)ALERT_REQ_UNKNOWN)){
        u1_t_rw = ((U1)1U << u1_a_DST);
        if(u1_t_esopt_bh == (U1)TRUE){
            u1_t_rw |= (U1)ALERT_C_BRKHLD_BHEXIST_BIT;
        }
    }

    u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    for(u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_C_BRKHLD_NUM_RWSGNL; u4_t_idx++){
        if((u1_t_rw & u1_sp_ALERT_C_BRKHLD_RWTX_CRT[u4_t_idx]) == u1_sp_ALERT_C_BRKHLD_RWTX_CRT[u4_t_idx]){
            u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
        }
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_AHSW, &u1_t_sgnl);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 3/2020  MY       New.                                                                                               */
/*  5.1.0     5/19/2020  DS       Fix timeout status for B_DAINDC.                                                                   */
/*  5.2.0     7/22/2020  ZS       Change remote warning logic.                                                                       */
/*  5.3.0     3/19/2021  MO       Communication disruption time change (1000ms->3600ms).                                             */
/*  5.3.1     6/27/2022  YN       Update for 840B#2 1A(Version update).                                                              */
/*  5.3.2     01/22/2024 YR       Update for 19PFv3(Version update)                                                                  */
/*  5.4.0     3/21/2025  KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * YR   = Yhana Regalario, Denso Techno Phil. Inc.                                                                                */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
