/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_EPB                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_EPB_C_MAJOR                      (5)
#define ALERT_C_EPB_C_MINOR                      (3)
#define ALERT_C_EPB_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_EPB_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_EPB.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_EPB_TT_PKB_NUM_DST               (32U)
#define ALERT_C_EPB_WRN_IG_NUM_DST               (8U)
#define ALERT_C_EPB_WRN_BAT_NUM_DST              (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) /* _235D_CAN_ */
static U1      u1_s_alert_epb_msgsts_pkblp;
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) */
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) /* _235D_CAN_ */
static U1      u1_s_alert_epb_msgsts_wrnbat;
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_epbTtPkbSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_epbWrnIgSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_epbWrnBatSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_epbWrnIgRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_EPB_TT_PKB_DST[ALERT_C_EPB_TT_PKB_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
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
    (U1)ALERT_REQ_C_EPB_TT_PKB_TT_ON,                                          /* 17 TT_ON                                           */
    (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_1HZ,                                      /* 18 FLASH_1HZ                                       */
    (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_2HZ,                                      /* 19 FLASH_2HZ                                       */
    (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_4HZ,                                      /* 20 FLASH_4HZ                                       */
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
static const U4  u4_sp_ALERT_C_EPB_WRN_IG_CRIT[ALERT_C_EPB_WRN_IG_NUM_DST] = {
    (U4)0x00000040U,                                                           /* 00 MALFUNC                                         */
    (U4)0x00000003U,                                                           /* 01 LOCK                                            */
    (U4)0x00000004U,                                                           /* 02 ADVICE1                                         */
    (U4)0x00000005U,                                                           /* 03 ACTIVE                                          */
    (U4)0x00000006U,                                                           /* 04 DEACTIVE                                        */
    (U4)0x00000007U,                                                           /* 05 ADVICE2                                         */
    (U4)0x0000000BU,                                                           /* 06 MALFUNC                                         */
    (U4)0x0000000DU                                                            /* 07 UNRELABLE                                       */
};
static const U4  u4_sp_ALERT_C_EPB_WRN_IG_MASK[ALERT_C_EPB_WRN_IG_NUM_DST] = {
    (U4)0x00000040U,                                                           /* 00 MALFUNC                                         */
    (U4)0x0000007FU,                                                           /* 01 LOCK                                            */
    (U4)0x0000007FU,                                                           /* 02 ADVICE1                                         */
    (U4)0x0000007FU,                                                           /* 03 ACTIVE                                          */
    (U4)0x0000007FU,                                                           /* 04 DEACTIVE                                        */
    (U4)0x0000007FU,                                                           /* 05 ADVICE2                                         */
    (U4)0x0000007FU,                                                           /* 06 MALFUNC                                         */
    (U4)0x0000007FU                                                            /* 07 UNRELABLE                                       */
};
static const U1  u1_sp_ALERT_C_EPB_WRN_IG_DST[ALERT_C_EPB_WRN_IG_NUM_DST] = {
    (U1)ALERT_REQ_C_EPB_WRN_IG_MALFUNC,                                        /* 00 MALFUNC                                         */
    (U1)ALERT_REQ_C_EPB_WRN_IG_LOCK,                                           /* 01 LOCK                                            */
    (U1)ALERT_REQ_C_EPB_WRN_IG_ADVICE1,                                        /* 02 ADVICE1                                         */
    (U1)ALERT_REQ_C_EPB_WRN_IG_ACTIVE,                                         /* 03 ACTIVE                                          */
    (U1)ALERT_REQ_C_EPB_WRN_IG_DEACTIVE,                                       /* 04 DEACTIVE                                        */
    (U1)ALERT_REQ_C_EPB_WRN_IG_ADVICE2,                                        /* 05 ADVICE2                                         */
    (U1)ALERT_REQ_C_EPB_WRN_IG_MALFUNC,                                        /* 06 MALFUNC                                         */
    (U1)ALERT_REQ_C_EPB_WRN_IG_UNRELABLE                                       /* 07 UNRELABLE                                       */
};
static const U4  u4_sp_ALERT_C_EPB_WRN_BAT_CRIT[ALERT_C_EPB_WRN_BAT_NUM_DST] = {
    (U4)0x02000001U,                                                           /* 00 ADVICE1                                         */
    (U4)0x02000002U,                                                           /* 01 AUTOLOCK                                        */
    (U4)0x02000008U,                                                           /* 02 ADVICE2                                         */
    (U4)0x02000009U,                                                           /* 03 NOTUSE1                                         */
    (U4)0x0200000AU,                                                           /* 04 NOTUSE2                                         */
    (U4)0x0200000CU                                                            /* 05 STOPPED                                         */
};
static const U4  u4_sp_ALERT_C_EPB_WRN_BAT_MASK[ALERT_C_EPB_WRN_BAT_NUM_DST] = {
    (U4)0x0200007FU,                                                           /* 00 ADVICE1                                         */
    (U4)0x0200007FU,                                                           /* 01 AUTOLOCK                                        */
    (U4)0x0200007FU,                                                           /* 02 ADVICE2                                         */
    (U4)0x0200007FU,                                                           /* 03 NOTUSE1                                         */
    (U4)0x0200007FU,                                                           /* 04 NOTUSE2                                         */
    (U4)0x0200007FU                                                            /* 05 STOPPED                                         */
};
static const U1  u1_sp_ALERT_C_EPB_WRN_BAT_DST[ALERT_C_EPB_WRN_BAT_NUM_DST] = {
    (U1)ALERT_REQ_C_EPB_WRN_BAT_ADVICE1,                                       /* 00 ADVICE1                                         */
    (U1)ALERT_REQ_C_EPB_WRN_BAT_AUTOLOCK,                                      /* 01 AUTOLOCK                                        */
    (U1)ALERT_REQ_C_EPB_WRN_BAT_ADVICE2,                                       /* 02 ADVICE2                                         */
    (U1)ALERT_REQ_C_EPB_WRN_BAT_NOTUSE1,                                       /* 03 NOTUSE1                                         */
    (U1)ALERT_REQ_C_EPB_WRN_BAT_NOTUSE2,                                       /* 04 NOTUSE2                                         */
    (U1)ALERT_REQ_C_EPB_WRN_BAT_STOPPED                                        /* 05 STOPPED                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_EPB_MTRX[3] = {
    {
        &u4_s_AlertC_epbTtPkbSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_EPB_TT_PKB_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_EPB_TT_PKB_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_epbWrnIgSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_epbWrnIgRwTx,                                             /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_EPB_WRN_IG_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_C_EPB_WRN_IG_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_EPB_WRN_IG_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_EPB_WRN_IG_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_epbWrnBatSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_EPB_WRN_BAT_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_C_EPB_WRN_BAT_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_EPB_WRN_BAT_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_C_EPB_WRN_BAT_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_epbInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_epbInit(void)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) /* _235D_CAN_ */
    u1_s_alert_epb_msgsts_pkblp  = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) */
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) /* _235D_CAN_ */
    u1_s_alert_epb_msgsts_wrnbat = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_epbTtPkbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_epbTtPkbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) /* _235D_CAN_ */
    static const U2 u2_s_ALERT_C_EPB_PKB_TO_THRESH  = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_EPB_PKB_LSB_MSG    = (U1)3U;
    static const U4 u4_s_ALERT_C_EPB_PKB_BIT_BAT_WT = (U4)0x00000010U;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                           (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                           u2_s_ALERT_C_EPB_PKB_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_epb_msgsts_pkblp, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
#ifdef ComConf_ComSignal_B_PKBLP
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_PKBLP, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_PKBLP */ /* 345D_CAN */
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= ((U4)u1_s_alert_epb_msgsts_pkblp << u1_s_ALERT_C_EPB_PKB_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_C_EPB_PKB_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_PKBLP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_epbWrnIgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_epbWrnIgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && (defined(ComConf_ComSignal_B_EPBMID)) /* _235D_CAN_ */
    static const U2 u2_s_ALERT_C_EPB_WRNIG_TO_THRESH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_EPB_WRNIG_LSB_MSG   = (U1)5U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_EPB_WRNIG_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_B_EPBMID
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EPBMID, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_EPBMID */ /* 345D_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_EPB_WRNIG_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && (defined(ComConf_ComSignal_B_EPBMID)) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_epbWrnBatSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_epbWrnBatSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) /* _235D_CAN_ */
    static const U2 u2_s_ALERT_C_EPB_WRNBAT_TO_TRSH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_EPB_WRNBAT_LSB_MSG = (U1)5U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                          u2_s_ALERT_C_EPB_WRNBAT_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_epb_msgsts_wrnbat, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_B_EPBMID
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EPBMID, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_EPBMID */ /* 345D_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_epb_msgsts_wrnbat << u1_s_ALERT_C_EPB_WRNBAT_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_DDM1S17_RXCH0) && defined(ComConf_ComSignal_B_EPBMID) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_epbWrnIgRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_epbWrnIgRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_C_EPB_RWTX_CRT = (U4)(((U4)1U << ALERT_REQ_C_EPB_WRN_IG_MALFUNC ));
    static const U1 u1_s_ALERT_C_EPB_RWTX_MSK = (U1)0x1FU;
    U1              u1_t_sgnl;
    U4              u4_t_rw;

    u4_t_rw    = ((U4)1U << (u1_a_DST & u1_s_ALERT_C_EPB_RWTX_MSK));

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)      != (U1)0U  ) &&
       ((u4_t_rw  & u4_s_ALERT_C_EPB_RWTX_CRT) != (U4)0U  )){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_EPBW, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/24/2020  ZS       New.                                                                                               */
/*  5.1.0     8/28/2020  KT       Deleted the judgment of communication interruption.                                                */
/*  5.2.0     6/24/2021  MO       Add Req for PD.                                                                                    */
/*  5.2.1     1/19/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*  5.2.2     5/30/2022  KK       Add B_ATLP control.                                                                                */
/*  5.3.0     11/25/2024 KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
