/* 5.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_CLESON                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_CLESON_C_MAJOR                   (5)
#define ALERT_S_CLESON_C_MINOR                   (2)
#define ALERT_S_CLESON_C_PATCH                   (4)

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
#if (ALERT_S_CLESON_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_CLESON.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_CLESON_TT_NUM_DST                (16U)
#define ALERT_S_CLESON_BZ_NUM_DST                (64U)
#define ALERT_S_CLESON_VOL_NUM_DST               (16U)
#define ALERT_S_CLESON_CUTIN_NUM_DST             (8U)

#define ALERT_S_CLESON_CI_NUM_CSR1S07            (10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1        (* const fp_u1_SGNL)(void);
    U1        u1_crit;
    U1        u1_mask;
}ST_ALERT_S_CLESON_SGNLCFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_sp_alert_s_cleson_csr1s07[ALERT_S_CLESON_CI_NUM_CSR1S07];
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertS_clesonTtSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_clesonBzSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_clesonVolSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_clesonCutinSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonDispChg    (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonCSRDISP3   (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonFLC_POS    (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonFRC_POS    (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonFL_POS     (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonFR_POS     (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonRLC_POS    (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonRRC_POS    (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonRL_POS     (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonRR_POS     (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonCSMUTESW   (void);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_CLESON_TT_DST[ALERT_S_CLESON_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 01 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_FLASH,                                           /* 02 FLASH                                           */
    (U1)ALERT_REQ_S_CLESON_TT_INDI_ON,                                         /* 03 INDI_ON                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 08 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 09 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 10 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 11 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 12 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 13 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON,                                              /* 14 ON                                              */
    (U1)ALERT_REQ_S_CLESON_TT_ON                                               /* 15 ON                                              */
};
static const U1  u1_sp_ALERT_S_CLESON_BZ_DST[ALERT_S_CLESON_BZ_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CLESON_BZ_RCTA,                                            /* 01 RCTA                                            */
    (U1)ALERT_REQ_S_CLESON_BZ_FR_CAD,                                          /* 02 FR_CAD                                          */
    (U1)ALERT_REQ_S_CLESON_BZ_FR_SD,                                           /* 03 FR_SD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_FR_MD,                                           /* 04 FR_MD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_FR_LD,                                           /* 05 FR_LD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_RR_CAD,                                          /* 06 RR_CAD                                          */
    (U1)ALERT_REQ_S_CLESON_BZ_RR_SD,                                           /* 07 RR_SD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_RR_MD,                                           /* 08 RR_MD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_RR_LD,                                           /* 09 RR_LD                                           */
    (U1)ALERT_REQ_S_CLESON_BZ_CAD,                                             /* 10 CAD                                             */
    (U1)ALERT_REQ_S_CLESON_BZ_SD,                                              /* 11 SD                                              */
    (U1)ALERT_REQ_S_CLESON_BZ_MD,                                              /* 12 MD                                              */
    (U1)ALERT_REQ_S_CLESON_BZ_LD,                                              /* 13 LD                                              */
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
static const U1  u1_sp_ALERT_S_CLESON_VOL_DST[ALERT_S_CLESON_VOL_NUM_DST] = {
    (U1)ALERT_REQ_S_CLESON_VOL_VOL0,                                           /* 00 VOL0                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL1,                                           /* 01 VOL1                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL2,                                           /* 02 VOL2                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL3,                                           /* 03 VOL3                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL4,                                           /* 04 VOL4                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL5,                                           /* 05 VOL5                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL6,                                           /* 06 VOL6                                            */
    (U1)ALERT_REQ_S_CLESON_VOL_VOL7,                                           /* 07 VOL7                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_CLESON_CUTIN_DST[ALERT_S_CLESON_CUTIN_NUM_DST] = {
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPA_V,                                      /* 00 DISPA_V                                         */
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPB_V,                                      /* 01 DISPB_V                                         */
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPB_V,                                      /* 02 DISPB_V                                         */
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPA_V,                                      /* 03 DISPA_V                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPA_V,                                      /* 05 DISPA_V                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_S_CLESON_CUTIN_DISPA_V                                       /* 07 DISPA_V                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_CLESON_MTRX[4] = {
    {
        &u4_s_AlertS_clesonTtSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_CLESON_TT_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_S_CLESON_TT_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_clesonBzSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_CLESON_BZ_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_S_CLESON_BZ_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_clesonVolSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_CLESON_VOL_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_CLESON_VOL_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_clesonCutinSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_CLESON_CUTIN_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_S_CLESON_CUTIN_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertS_clesonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertS_clesonInit(void)
{
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
    U4              u4_t_loop;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ALERT_S_CLESON_CI_NUM_CSR1S07; u4_t_loop++){
        u1_sp_alert_s_cleson_csr1s07[u4_t_loop] = (U1)0U;
    }
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_clesonTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_clesonTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) && defined(ComConf_ComSignal_CS_LAMP)
    static const U2 u2_s_ALERT_S_CLESON_TT_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_CLESON_TT_LSB_STS  = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_CSR1S07_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_CLESON_TT_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CS_LAMP, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_CLESON_TT_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) && defined(ComConf_ComSignal_CS_LAMP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_clesonBzSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_clesonBzSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_CSR1S08_CH0) && defined(ComConf_ComSignal_CSR_BUZ)
    static const U2 u2_s_ALERT_S_CLESON_BZ_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_CLESON_BZ_LSB_STS  = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_CSR1S08_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_CLESON_BZ_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSR_BUZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_CLESON_BZ_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S08_CH0) && defined(ComConf_ComSignal_CSR_BUZ) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_clesonVolSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_clesonVolSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_CSR1S08_CH0) && defined(ComConf_ComSignal_CSR_VOL)
    static const U1 u1_s_ALERT_S_CLESON_VOL_LSB_STS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_CSR1S08_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSR_VOL, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_CLESON_VOL_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0x00000008U); /* UNKNOWN */
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S08_CH0) && defined(ComConf_ComSignal_CSR_VOL) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_clesonCutinSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_clesonCutinSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
    static const U4 u4_s_ALERT_S_CLESON_CI_BIT_NODSP = (U4)0x00000004U;
    static const U1 u1_s_ALERT_S_CLESON_CI_LSB_LSTST = (U1)1U;
    static const U1 u1_s_ALERT_S_CLESON_CI_MSK_REQ   = (U1)0x03U;
    U4              u4_t_src_chk;
    U1              u1_t_lastreq;

    u4_t_src_chk = (U4)u1_s_AlertS_clesonDispChg();

    u1_t_lastreq = u1_a_LAS;
    if(u1_t_lastreq == (U1)ALERT_REQ_UNKNOWN){
        u4_t_src_chk |= u4_s_ALERT_S_CLESON_CI_BIT_NODSP;
    }
    else{
        u1_t_lastreq &= u1_s_ALERT_S_CLESON_CI_MSK_REQ;
        u4_t_src_chk |= ((U4)u1_t_lastreq << u1_s_ALERT_S_CLESON_CI_LSB_LSTST);
    }

    return(u4_t_src_chk);
#else
    return((U4)0x00000004U); /* UNKNOWN */
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertS_clesonDispChg(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static U1      u1_s_AlertS_clesonDispChg(void)
{
    static const ST_ALERT_S_CLESON_SGNLCFG st_sp_ALERT_S_CLESON_CSR1S07[ALERT_S_CLESON_CI_NUM_CSR1S07] = {
        /*  fp_u1_SGNL                    u1_crit     u1_mask     */
        {   &u1_s_AlertS_clesonCSRDISP3,  (U1)0x02U,  (U1)0x01U   },    /* 1b                             */
        {   &u1_s_AlertS_clesonFLC_POS,   (U1)0x7EU,  (U1)0x07U   },    /* 001b-110b                      */
        {   &u1_s_AlertS_clesonFRC_POS,   (U1)0x7EU,  (U1)0x07U   },    /* 001b-110b                      */
        {   &u1_s_AlertS_clesonFL_POS,    (U1)0x3EU,  (U1)0x07U   },    /* 001b-101b                      */
        {   &u1_s_AlertS_clesonFR_POS,    (U1)0x3EU,  (U1)0x07U   },    /* 001b-101b                      */
        {   &u1_s_AlertS_clesonRL_POS,    (U1)0x3EU,  (U1)0x07U   },    /* 001b-101b                      */
        {   &u1_s_AlertS_clesonRR_POS,    (U1)0x3EU,  (U1)0x07U   },    /* 001b-101b                      */
        {   &u1_s_AlertS_clesonRLC_POS,   (U1)0x7EU,  (U1)0x07U   },    /* 001b-110b                      */
        {   &u1_s_AlertS_clesonRRC_POS,   (U1)0x7EU,  (U1)0x07U   },    /* 001b-110b                      */
        {   &u1_s_AlertS_clesonCSMUTESW,  (U1)0x06U,  (U1)0x03U   }     /* 01b,10b                        */
    };

    static const U2 u2_s_ALERT_S_CLESON_CI_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_CLESON_CI_BIT_DISP = (U1)0x01U;
    U1              u1_t_change;
    U1              u1_t_msg_csr1s07;
    U1              u1_t_sgnl;
    U1              u1_t_bitpos;
    U4              u4_t_loop;

    u1_t_change      = (U1)0U;

    u1_t_msg_csr1s07 = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_CSR1S07_CH0,
                                             (U4)OXCAN_SYS_IGR,
                                             u2_s_ALERT_S_CLESON_CI_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ALERT_S_CLESON_CI_NUM_CSR1S07; u4_t_loop++){
        u1_t_sgnl = (U1)0U;
        if((u1_t_msg_csr1s07                                   == (U1)0U     ) &&
           (st_sp_ALERT_S_CLESON_CSR1S07[u4_t_loop].fp_u1_SGNL != vdp_PTR_NA )){
            u1_t_sgnl   = (st_sp_ALERT_S_CLESON_CSR1S07[u4_t_loop].fp_u1_SGNL)();
            u1_t_bitpos = ((U1)1U << (u1_t_sgnl & st_sp_ALERT_S_CLESON_CSR1S07[u4_t_loop].u1_mask));
            if(((u1_t_bitpos & st_sp_ALERT_S_CLESON_CSR1S07[u4_t_loop].u1_crit) != (U1)0U   ) &&
               (u1_sp_alert_s_cleson_csr1s07[u4_t_loop]                         != u1_t_sgnl)){
                u1_t_change = u1_s_ALERT_S_CLESON_CI_BIT_DISP;
            }
        }
        u1_sp_alert_s_cleson_csr1s07[u4_t_loop] = u1_t_sgnl;
    }

    return(u1_t_change);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonCSRDISP3(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonCSRDISP3(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_CSRDISP3)
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSRDISP3, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_CSRDISP3) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonFLC_POS(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonFLC_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_FLC_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_FLC_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_FLC_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonFRC_POS(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonFRC_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_FRC_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_FRC_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_FRC_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonFL_POS(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonFL_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_FL_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_FL_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_FL_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonFR_POS(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonFR_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_FR_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_FR_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_FR_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonRL_POS(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonRL_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_RL_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_RL_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_RL_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonRR_POS(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonRR_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_RR_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_RR_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_RR_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonRLC_POS(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonRLC_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_RLC_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_RLC_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_RLC_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonRRC_POS(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonRRC_POS(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_RRC_POS)
    (void)Com_ReceiveSignal(ComConf_ComSignal_RRC_POS, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_RRC_POS) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/* static  U1      u1_s_AlertS_clesonCSMUTESW(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0)
static  U1      u1_s_AlertS_clesonCSMUTESW(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0;
#if defined(ComConf_ComSignal_CSMUTESW)
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSMUTESW, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_CSMUTESW) */
    return (u1_t_sgnl);
}
#endif /* defined(OXCAN_RXD_PDU_CAN_CSR1S07_CH0) */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/25/2020  DS       New.                                                                                               */
/*  5.1.0     5/18/2020  DS       Fix VOL status for IG-OFF.                                                                         */
/*  5.1.1     8/28/2020  RI       Change module name to 800B CV-R.                                                                   */
/*  5.1.2     9/16/2020  MY       Fix missing type cast.                                                                             */
/*  5.1.3     9/24/2020  TH       Fix QAC Warning.                                                                                   */
/*  5.2.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.2.1     3/25/2021  KT       Update for 840B CV(Version update).                                                                */
/*  5.2.2     5/14/2021  TN       Fix 800B Bug.                                                                                      */
/*  5.2.3    11/16/2021  TM       Fix QAC Warning.                                                                                   */
/*  5.2.4     2/ 3/2022  TM       Add Control of ON TT.                                                                              */
/*                                                                                                                                   */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
