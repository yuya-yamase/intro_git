/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_TDOOR                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TDOOR_C_MAJOR                    (5)
#define ALERT_B_TDOOR_C_MINOR                    (7)
#define ALERT_B_TDOOR_C_PATCH                    (0)

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
#if (ALERT_B_TDOOR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_TDOOR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Configuration Check                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if !defined(u1_ALERT_CFG_B_TDOOR_RRCY)
#error "alert_cfg_private.h : u1_ALERT_CFG_B_TDOOR_RRCY is undefined!"
#endif
#if !defined(u1_ALERT_CFG_B_TDOOR_RLCY)
#error "alert_cfg_private.h : u1_ALERT_CFG_B_TDOOR_RLCY is undefined!"
#endif
#if !defined(u1_ALERT_CFG_B_TDOOR_BCTY)
#error "alert_cfg_private.h : u1_ALERT_CFG_B_TDOOR_BCTY is undefined!"
#endif
#if !defined(u1_ALERT_CFG_B_TDOOR_LGCY)
#error "alert_cfg_private.h : u1_ALERT_CFG_B_TDOOR_LGCY is undefined!"
#endif
#if !defined(u1_ALERT_CFG_B_TDOOR_HDCY_BDB)
#error "alert_cfg_private.h : u1_ALERT_CFG_B_TDOOR_HDCY_BDB is undefined!"
#endif
#if !defined(ALERT_CFG_B_TDOOR_RPSDWARN)
#error "alert_cfg_private.h : ALERT_CFG_B_TDOOR_RPSDWARN is undefined!"
#endif
#if !defined(ALERT_CFG_B_TDOOR_LPSDWARN)
#error "alert_cfg_private.h : ALERT_CFG_B_TDOOR_LPSDWARN is undefined!"
#endif
#if !defined(ALERT_CFG_B_TDOOR_SLP_POS)
#error "alert_cfg_private.h : ALERT_CFG_B_TDOOR_SLP_POS is undefined!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TDOOR_NUM_DST                    (15U)

#define ALERT_B_TDOOR_STS_STOP                   (0x00U)
#define ALERT_B_TDOOR_STS_RUN                    (0x02U)

#define ALERT_B_TDOOR_SLP_TBL_NUM                (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_b_tdoor_igoff_dspcnt;
static U2      u2_s_alert_b_tdoor_laststs;
static U1      u1_s_alert_b_tdoor_bdb1s01_sts;
static U1      u1_s_alert_b_tdoor_bdb1f01_sts;
#if (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE)
static U1      u1_s_alert_b_tdoor_drl1s03_sts;
#endif /* (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) */
#if (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)
static U1      u1_s_alert_b_tdoor_drr1s03_sts;
#endif /* (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE) */
static U1      u1_s_alert_b_tdoor_runsts;
#if (ALERT_CFG_B_TDOOR_SLP_POS == TRUE)
static U1      u1_s_alert_b_tdoor_slp1s01_sts;
#endif /* (ALERT_CFG_B_TDOOR_SLP_POS == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U4      u4_s_AlertB_tdoorSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static        U1      u1_s_AlertB_tdoorSgnl    (const U1 u1_a_FACT);
static        U1      u1_s_AlertB_tdoorPsdSgnl (const U1 u1_a_FACT);
static        U1      u1_s_AlertB_tdoorSlpSgnl (const U1 u1_a_FACT);
static        U4      u4_s_AlertB_tdoorIgOffDsp(const U1 u1_a_VOM, const U2 u2_a_DOOR_STS);
static        U1      u1_s_AlertB_tdoorRunSts  (void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_B_TDOOR_CRIT[ALERT_B_TDOOR_NUM_DST] = {
    (U4)0x08000004U,                                                           /* 00 IG_OFF                                          */
    (U4)0x08000010U,                                                           /* 01 IG_OFF                                          */
    (U4)0x08000008U,                                                           /* 02 IG_OFF_ON                                       */
    (U4)0x08000009U,                                                           /* 03 ON                                              */
    (U4)0x08000020U,                                                           /* 04 IG_OFF                                          */
    (U4)0x08000028U,                                                           /* 05 IG_OFF_ON                                       */
    (U4)0x08000029U,                                                           /* 06 ON                                              */
    (U4)0x10000004U,                                                           /* 07 STOP                                            */
    (U4)0x10000006U,                                                           /* 08 RUN                                             */
    (U4)0x10000010U,                                                           /* 09 STOP                                            */
    (U4)0x10000012U,                                                           /* 10 RUN                                             */
    (U4)0x10000020U,                                                           /* 11 STOP                                            */
    (U4)0x10000022U,                                                           /* 12 RUN                                             */
    (U4)0x10000008U,                                                           /* 13 STOP_ON                                         */
    (U4)0x1000000AU                                                            /* 14 RUN_ON                                          */
};
static const U4  u4_sp_ALERT_B_TDOOR_MASK[ALERT_B_TDOOR_NUM_DST] = {
    (U4)0x1800003DU,                                                           /* 00 IG_OFF                                          */
    (U4)0x18000039U,                                                           /* 01 IG_OFF                                          */
    (U4)0x18000029U,                                                           /* 02 IG_OFF_ON                                       */
    (U4)0x18000029U,                                                           /* 03 ON                                              */
    (U4)0x18000029U,                                                           /* 04 IG_OFF                                          */
    (U4)0x18000029U,                                                           /* 05 IG_OFF_ON                                       */
    (U4)0x18000029U,                                                           /* 06 ON                                              */
    (U4)0x1000003EU,                                                           /* 07 STOP                                            */
    (U4)0x1000003EU,                                                           /* 08 RUN                                             */
    (U4)0x1000003AU,                                                           /* 09 STOP                                            */
    (U4)0x1000003AU,                                                           /* 10 RUN                                             */
    (U4)0x1000002AU,                                                           /* 11 STOP                                            */
    (U4)0x1000002AU,                                                           /* 12 RUN                                             */
    (U4)0x1000000AU,                                                           /* 13 STOP_ON                                         */
    (U4)0x1000000AU                                                            /* 14 RUN_ON                                          */
};
static const U1  u1_sp_ALERT_B_TDOOR_DST[ALERT_B_TDOOR_NUM_DST] = {
    (U1)ALERT_REQ_B_TDOOR_IG_OFF,                                              /* 00 IG_OFF                                          */
    (U1)ALERT_REQ_B_TDOOR_IG_OFF,                                              /* 01 IG_OFF                                          */
    (U1)ALERT_REQ_B_TDOOR_IG_OFF_ON,                                           /* 02 IG_OFF_ON                                       */
    (U1)ALERT_REQ_B_TDOOR_ON,                                                  /* 03 ON                                              */
    (U1)ALERT_REQ_B_TDOOR_IG_OFF,                                              /* 04 IG_OFF                                          */
    (U1)ALERT_REQ_B_TDOOR_IG_OFF_ON,                                           /* 05 IG_OFF_ON                                       */
    (U1)ALERT_REQ_B_TDOOR_ON,                                                  /* 06 ON                                              */
    (U1)ALERT_REQ_B_TDOOR_STOP,                                                /* 07 STOP                                            */
    (U1)ALERT_REQ_B_TDOOR_RUN,                                                 /* 08 RUN                                             */
    (U1)ALERT_REQ_B_TDOOR_STOP,                                                /* 09 STOP                                            */
    (U1)ALERT_REQ_B_TDOOR_RUN,                                                 /* 10 RUN                                             */
    (U1)ALERT_REQ_B_TDOOR_STOP,                                                /* 11 STOP                                            */
    (U1)ALERT_REQ_B_TDOOR_RUN,                                                 /* 12 RUN                                             */
    (U1)ALERT_REQ_B_TDOOR_STOP_ON,                                             /* 13 STOP_ON                                         */
    (U1)ALERT_REQ_B_TDOOR_RUN_ON                                               /* 14 RUN_ON                                          */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_TDOOR_MTRX[1] = {
    {
        &u4_s_AlertB_tdoorSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_B_TDOOR_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_B_TDOOR_CRIT[0],                                          /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TDOOR_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_B_TDOOR_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_tdoorInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_tdoorInit(void)
{
    u2_s_alert_b_tdoor_laststs      = (U2)0U;
    u4_s_alert_b_tdoor_igoff_dspcnt = (U4)0U;
    u1_s_alert_b_tdoor_runsts       = (U1)ALERT_B_TDOOR_STS_STOP;
    u1_s_alert_b_tdoor_bdb1s01_sts  = (U1)COM_NO_RX;
    u1_s_alert_b_tdoor_bdb1f01_sts  = (U1)COM_NO_RX;
#if (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE)
    u1_s_alert_b_tdoor_drl1s03_sts  = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) */
#if (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)
    u1_s_alert_b_tdoor_drr1s03_sts  = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE) */
#if (ALERT_CFG_B_TDOOR_SLP_POS == TRUE)
    u1_s_alert_b_tdoor_slp1s01_sts  = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_TDOOR_SLP_POS == TRUE) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_tdoorSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_tdoorSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_B_TDOOR_BIT_SLP_OPN  = (U4)0x00000020U;
    static const U4 u4_s_ALERT_B_TDOOR_BIT_HDCY_OPN = (U4)0x00000010U;
    static const U4 u4_s_ALERT_B_TDOOR_BIT_DOOR_OPN = (U4)0x00000008U;
    static const U4 u4_s_ALERT_B_TDOOR_BIT_PSD_WRN  = (U4)0x00000004U;
    static const U1 u1_s_ALERT_B_TDOOR_MSK_HDCY_OPN = (U1)0x40U;
    static const U1 u1_s_ALERT_B_TDOOR_MSK_DOOR_OPN = (U1)0x3FU;
    static const U1 u1_s_ALERT_B_TDOOR_MSK_PSD_WRN  = (U1)0x03U;
    static const U1 u1_s_ALERT_B_TDOOR_LSB_SLP_STS  = (U1)9U;
    static const U1 u1_s_ALERT_B_TDOOR_LSB_PSD_STS  = (U1)7U;
    static const U1 u1_s_ALERT_B_TDOOR_STS_SLP_OPN  = (U1)TRUE;
    U4              u4_t_src_chk;
    U2              u2_t_alldoor_sts;
    U1              u1_t_door_sts;
    U1              u1_t_psd_sts;
    U1              u1_t_slp_sts;
    U1              u1_t_fact;

    u1_t_fact         = (U1)0U;
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_OFF_WT) != (U1)0U){
        u1_t_fact = (U1)ALERT_BRX_FACT_NO_RX;
    }

    u1_t_door_sts     = u1_s_AlertB_tdoorSgnl(u1_t_fact);
    u1_t_psd_sts      = u1_s_AlertB_tdoorPsdSgnl(u1_t_fact);
    u1_t_slp_sts      = u1_s_AlertB_tdoorSlpSgnl(u1_t_fact);
    u2_t_alldoor_sts  = (U2)u1_t_door_sts | (U2)((U2)u1_t_psd_sts << u1_s_ALERT_B_TDOOR_LSB_PSD_STS);
    u2_t_alldoor_sts |= (U2)((U2)u1_t_slp_sts << u1_s_ALERT_B_TDOOR_LSB_SLP_STS);
    u4_t_src_chk      = u4_s_AlertB_tdoorIgOffDsp(u1_a_VOM, u2_t_alldoor_sts);

    u4_t_src_chk     |= (U4)u1_s_AlertB_tdoorRunSts();

    if((u1_t_door_sts & u1_s_ALERT_B_TDOOR_MSK_HDCY_OPN) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TDOOR_BIT_HDCY_OPN;
    }

    if((u1_t_door_sts & u1_s_ALERT_B_TDOOR_MSK_DOOR_OPN) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TDOOR_BIT_DOOR_OPN;
    }

    if((u1_t_psd_sts  & u1_s_ALERT_B_TDOOR_MSK_PSD_WRN) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_TDOOR_BIT_PSD_WRN;
    }

    if(u1_t_slp_sts  == u1_s_ALERT_B_TDOOR_STS_SLP_OPN){
        u4_t_src_chk |= u4_s_ALERT_B_TDOOR_BIT_SLP_OPN;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_tdoorSgnl(const U1 u1_a_FACT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_tdoorSgnl(const U1 u1_a_FACT)
{
    static const U2 u2_s_ALERT_B_TDOOR_TO_BDB1S01    = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_B_TDOOR_TO_BDB1F01    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_PCTY = (U1)1U;
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_RRCY = (U1)2U;
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_RLCY = (U1)3U;
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_BCTY = (U1)4U;
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_LGCY = (U1)5U;
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_HDCY = (U1)6U;
    U1              u1_t_sgnl;
    U1              u1_t_retval;
    U1              u1_t_fact_bdb1s01;
    U1              u1_t_fact_bdb1f01;
    U1              u1_t_rrcy;
    U1              u1_t_rlcy;
    U1              u1_t_bcty;
    U1              u1_t_lgcy;
    U1              u1_t_hdcy_bdb;

    u1_t_fact_bdb1s01  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01_RXCH0,
                                               (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                               u2_s_ALERT_B_TDOOR_TO_BDB1S01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_fact_bdb1f01  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1F01_RXCH0,
                                               (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                               u2_s_ALERT_B_TDOOR_TO_BDB1F01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_fact_bdb1s01 |= u1_a_FACT;
    u1_t_fact_bdb1f01 |= u1_a_FACT;

    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tdoor_bdb1s01_sts, u1_t_fact_bdb1s01);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tdoor_bdb1f01_sts, u1_t_fact_bdb1f01);

    u1_t_retval        = (U1)0U;

    u1_t_rrcy        = u1_ALERT_CFG_B_TDOOR_RRCY;
    u1_t_rlcy        = u1_ALERT_CFG_B_TDOOR_RLCY;
    u1_t_bcty        = u1_ALERT_CFG_B_TDOOR_BCTY;
    u1_t_lgcy        = u1_ALERT_CFG_B_TDOOR_LGCY;
    u1_t_hdcy_bdb    = u1_ALERT_CFG_B_TDOOR_HDCY_BDB;

    if((u1_s_alert_b_tdoor_bdb1s01_sts & (U1)COM_NO_RX) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_DCTY, &u1_t_retval);

        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_PCTY, &u1_t_sgnl);
        u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_PCTY);

        if(u1_t_rrcy == (U1)TRUE){
            u1_t_sgnl    = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_RRCY, &u1_t_sgnl);
            u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_RRCY);
        }

        if(u1_t_rlcy == (U1)TRUE){
            u1_t_sgnl    = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_RLCY, &u1_t_sgnl);
            u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_RLCY);
        }

        if(u1_t_bcty == (U1)TRUE){
            u1_t_sgnl    = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_BCTY, &u1_t_sgnl);
            u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_BCTY);
        }

        if(u1_t_lgcy == (U1)TRUE){
            u1_t_sgnl    = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_LGCY, &u1_t_sgnl);
            u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_LGCY);
        }

    }

    if(u1_t_hdcy_bdb == (U1)TRUE){
        if((u1_s_alert_b_tdoor_bdb1f01_sts & (U1)COM_NO_RX) == (U1)0U){
            u1_t_sgnl    = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_HDCY_BDB, &u1_t_sgnl);
            u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_HDCY);
        }
    }

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_tdoorPsdSgnl(const U1 u1_a_FACT)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_tdoorPsdSgnl(const U1 u1_a_FACT)
{
#if (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE)
    static const U2 u2_s_ALERT_B_TDOOR_TO_DRL1S03    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1              u1_t_fact_drl1s03;
#endif /* (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) */
#if (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)
    static const U2 u2_s_ALERT_B_TDOOR_TO_DRR1S03    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TDOOR_SGNL_LSB_RPSD = (U1)1U;
    U1              u1_t_fact_drr1s03;
#endif /* (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE) */
#if ((ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) || (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE))
    U1              u1_t_sgnl;
#endif /* ((ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) || (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)) */
    U1              u1_t_retval;

#if (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE)
    u1_t_fact_drl1s03  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DRL1S03_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                               u2_s_ALERT_B_TDOOR_TO_DRL1S03) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_fact_drl1s03 |= u1_a_FACT;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tdoor_drl1s03_sts, u1_t_fact_drl1s03);
#endif /* (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) */
#if (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)
    u1_t_fact_drr1s03  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DRR1S03_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                               u2_s_ALERT_B_TDOOR_TO_DRR1S03) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_fact_drr1s03 |= u1_a_FACT;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tdoor_drr1s03_sts, u1_t_fact_drr1s03);
#endif /* (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE) */

    u1_t_retval        = (U1)0U;

#if (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE)
    if((u1_s_alert_b_tdoor_drl1s03_sts & (U1)COM_NO_RX) == (U1)0U){
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_LPSDWARN, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
    }
#endif /* (ALERT_CFG_B_TDOOR_LPSDWARN == TRUE) */

#if (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE)
    if((u1_s_alert_b_tdoor_drr1s03_sts & (U1)COM_NO_RX) == (U1)0U){
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_RPSDWARN, &u1_t_sgnl);
        u1_t_retval |= (U1)(u1_t_sgnl << u1_s_ALERT_B_TDOOR_SGNL_LSB_RPSD);
    }
#endif /* (ALERT_CFG_B_TDOOR_RPSDWARN == TRUE) */

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_tdoorSlpSgnl(const U1 u1_a_FACT)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_tdoorSlpSgnl(const U1 u1_a_FACT)
{
#if (ALERT_CFG_B_TDOOR_SLP_POS == TRUE)
    static const U2 u2_s_ALERT_B_TDOOR_TO_SLP1S01 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TDOOR_SLP_MSK    = (U1)0x07U;
    static const U1 u1_sp_ALERT_B_TDOOR_SLP_TBL[ALERT_B_TDOOR_SLP_TBL_NUM] = {
        (U1)FALSE, (U1)TRUE, (U1)TRUE,  (U1)TRUE, (U1)TRUE,  (U1)TRUE, (U1)FALSE, (U1)FALSE
    };
    U1              u1_t_fact_slp1s01;
    U1              u1_t_sgnl;
#endif /* (ALERT_CFG_B_TDOOR_SLP_POS == TRUE) */
    U1              u1_t_retval;

#if (ALERT_CFG_B_TDOOR_SLP_POS == TRUE)
    u1_t_fact_slp1s01  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SLP1S01,
                                          (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                          u2_s_ALERT_B_TDOOR_TO_SLP1S01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_fact_slp1s01 |= u1_a_FACT;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tdoor_slp1s01_sts, u1_t_fact_slp1s01);
#endif /* (ALERT_CFG_B_TDOOR_SLP_POS == TRUE) */
    u1_t_retval        = (U1)0U;

#if (ALERT_CFG_B_TDOOR_SLP_POS == TRUE)
    if((u1_s_alert_b_tdoor_slp1s01_sts & (U1)COM_NO_RX) == (U1)0U){
        u1_t_sgnl   = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_SLP_POS, &u1_t_sgnl);
        u1_t_sgnl  &= u1_s_ALERT_B_TDOOR_SLP_MSK;
        u1_t_retval = u1_sp_ALERT_B_TDOOR_SLP_TBL[u1_t_sgnl];
    }
#endif /* (ALERT_CFG_B_TDOOR_SLP_POS == TRUE) */

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_tdoorIgOffDsp(const U1 u1_a_VOM, const U2 u2_a_DOOR_STS)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_tdoorIgOffDsp(const U1 u1_a_VOM, const U2 u2_a_DOOR_STS)
{
    static const U4 u4_s_ALERT_TDOOR_IGOFF_DSPTM  = ((U4)1200000U / (U4)ALERT_MAIN_TICK);
    static const U4 u4_s_ALERT_TDOOR_DSPCNT_RST   = (U4)1U;
    static const U4 u4_s_ALERT_TDOOR_BIT_IGOFFCNT = (U4)0x00000001U;
    U4              u4_t_retval;

    u4_t_retval = (U4)0U;
    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U) ||
       (u2_a_DOOR_STS                     == (U2)0U)){
        u4_s_alert_b_tdoor_igoff_dspcnt = (U4)0U;
    }
    else if(u2_a_DOOR_STS                 != u2_s_alert_b_tdoor_laststs){
        u4_s_alert_b_tdoor_igoff_dspcnt = u4_s_ALERT_TDOOR_DSPCNT_RST;
    }
    else if(u4_s_ALERT_TDOOR_IGOFF_DSPTM  <= u4_s_alert_b_tdoor_igoff_dspcnt){
        u4_s_alert_b_tdoor_igoff_dspcnt = u4_s_ALERT_TDOOR_IGOFF_DSPTM;
        u4_t_retval                     = u4_s_ALERT_TDOOR_BIT_IGOFFCNT;
    }
    else{
        u4_s_alert_b_tdoor_igoff_dspcnt++;
    }

    u2_s_alert_b_tdoor_laststs = u2_a_DOOR_STS;

    return(u4_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_tdoorRunSts(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_tdoorRunSts(void)
{
    static const U2 u2_s_ALERT_TDOOR_THRSH_RUN  = (U2)500U;
    static const U2 u2_s_ALERT_TDOOR_THRSH_STOP = (U2)400U;
    U2              u2_t_instspd;
    U1              u1_t_vehspd_sts;
    U1              u1_t_runsts;

    u2_t_instspd    = (U2)0U;
    u1_t_vehspd_sts = u1_g_AlertSpdKmphInst(&u2_t_instspd, (U1)TRUE);
    u1_t_runsts     = (U1)ALERT_B_TDOOR_STS_STOP;

    if(u1_t_vehspd_sts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_s_ALERT_TDOOR_THRSH_RUN        <= u2_t_instspd){
            u1_t_runsts = (U1)ALERT_B_TDOOR_STS_RUN;
        }
        else if((u2_s_ALERT_TDOOR_THRSH_STOP <  u2_t_instspd             ) &&
                (u1_s_alert_b_tdoor_runsts   == (U1)ALERT_B_TDOOR_STS_RUN)){
            u1_t_runsts = (U1)ALERT_B_TDOOR_STS_RUN;
        }
        else{
            /* Do Nothing */
        }
    }

    u1_s_alert_b_tdoor_runsts = u1_t_runsts;

    return(u1_s_alert_b_tdoor_runsts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     6/23/2021  RI       New.                                                                                               */
/*  5.0.1     8/ 5/2021  RI       Fix QAC Warning.                                                                                   */
/*  5.1.0     8/ 6/2021  MO       Change dlytimer thresh.                                                                            */
/*  5.1.1     1/19/2022  YN       Update for 840B #2 CV(Version update).                                                             */
/*  5.2.0     3/ 7/2023  MY       Change available signals to config.                                                                */
/*  5.3.0    10/24/2023  SH       Delete compile SW                                                                                  */
/*  5.4.0     4/12/2024  SH       Add calibration guard                                                                              */
/*  5.5.0     4/18/2023  TN       Add compile SW(RPSDWARN and LPSDWARN).                                                             */
/*  5.6.0     5/13/2023  SH       Add compile SW(SLP_POS).                                                                           */
/*  5.7.0     6/27/2024  TN       Delete Calibration Guard Process.                                                                  */
/*                                                                                                                                   */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
