/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_FRRADA                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_FRRADA_C_MAJOR                     (5)
#define ALERT_S_FRRADA_C_MINOR                     (1)
#define ALERT_S_FRRADA_C_PATCH                     (0)

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
#if (ALERT_S_FRRADA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_FRRADA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_FRRADA_BZ_CMP_NUM_DST            (64U)
#define ALERT_S_FRRADA_BZ_ERR_NUM_DST            (64U)

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
static U4      u4_s_AlertS_frradaBzCmpSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_frradaBzErrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_FRRADA_BZ_CMP_DST[ALERT_S_FRRADA_BZ_CMP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 01 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 02 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 03 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 04 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 05 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 06 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 07 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 08 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 09 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 10 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 11 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 12 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 13 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 14 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_CMP_CYCLE,                                       /* 15 CYCLE                                           */
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

static const U1  u1_sp_ALERT_S_FRRADA_BZ_ERR_DST[ALERT_S_FRRADA_BZ_ERR_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 01 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 02 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 03 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 04 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 05 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 06 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 07 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 08 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 09 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 10 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 11 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 12 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 13 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 14 CYCLE                                           */
    (U1)ALERT_REQ_S_FRRADA_BZ_ERR_CYCLE,                                       /* 15 CYCLE                                           */
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
const ST_ALERT_MTRX st_gp_ALERT_S_FRRADA_MTRX[2] = {
    {
        &u4_s_AlertS_frradaBzCmpSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_FRRADA_BZ_CMP_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_S_FRRADA_BZ_CMP_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_frradaBzErrSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_FRRADA_BZ_ERR_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_S_FRRADA_BZ_ERR_NUM_DST,                                     /* u2_num_srch                                        */
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
/*  static U4      u4_s_AlertS_frradaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_frradaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_FSR    = (U1)1U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSL    = (U1)2U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSR    = (U1)3U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    
    u1_t_msgsts  = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                    (U4)OXCAN_SYS_IGR,
                                    (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSL_PLRQ, &u1_t_sgnl);
    u4_t_src_chk = (U4)u1_t_sgnl;
    
    u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSR_PLRQ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_FSR;

    u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSL_PLRQ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSL;

    u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSR_PLRQ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSR;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS);

    return(u4_t_src_chk);
}
#endif /* BEVCDCFD-1483 */

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_frradaBzCmpSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_frradaBzCmpSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_CH_S_FRRADA_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_FSR    = (U1)1U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSL    = (U1)2U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSR    = (U1)3U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_CH_S_FRRADA_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSL_BZ_C, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSR_BZ_C, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_FSR;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSL_BZ_C, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSL;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSR_BZ_C, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSR;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_frradaBzErrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_frradaBzErrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_CH_S_FRRADA_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_FSR    = (U1)1U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSL    = (U1)2U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_RSR    = (U1)3U;
    static const U1 u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_CH_S_FRRADA_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSL_BZ_E, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FSR_BZ_E, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_FSR;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSL_BZ_E, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSL;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSR_BZ_E, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl << u1_s_ALERT_CH_S_FRRADA_LSB_RSR;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CH_S_FRRADA_LSB_MSGSTS);

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
/*  5.0.0     1/16/2024  PG       New.                                                                                               */
/*  5.1.0     6/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0,MET-S_ADTT-CSTD-0-02-A-C0)       */
/*                                                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
