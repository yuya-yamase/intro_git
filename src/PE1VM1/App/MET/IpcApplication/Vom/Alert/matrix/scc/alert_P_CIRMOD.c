/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_CIRMOD                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_CIRMOD_C_MAJOR                   (5)
#define ALERT_P_CIRMOD_C_MINOR                   (1)
#define ALERT_P_CIRMOD_C_PATCH                   (0)

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
#if (ALERT_P_CIRMOD_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_CIRMOD.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_CIRMOD_TT_ALC_NUM_DST            (4U)
#define ALERT_P_CIRMOD_TT_CM_NUM_DST             (16U)
#define ALERT_P_CIRMOD_PD_CM_NUM_DST             (8U)
#define ALERT_P_CIRMOD_PD_FAN_NUM_DST            (4U)

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
static U4      u4_s_AlertP_cirmodTtAlcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_cirmodTtCmSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_cirmodPdCmSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_cirmodPdFanSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_CIRMOD_TT_ALC_DST[ALERT_P_CIRMOD_TT_ALC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_TT_ALC_ON,                                          /* 01 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_CIRMOD_TT_CM_DST[ALERT_P_CIRMOD_TT_CM_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 01 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 04 ON                                              */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 05 ON                                              */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 06 ON                                              */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 07 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,                                           /* 13 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_CIRMOD_PD_CM_DST[ALERT_P_CIRMOD_PD_CM_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_PD_CM_ON,                                           /* 01 ON                                              */
    (U1)ALERT_REQ_P_CIRMOD_PD_CM_OFF,                                          /* 02 OFF                                             */
    (U1)ALERT_REQ_P_CIRMOD_PD_CM_CANCEL,                                       /* 03 CANCEL                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_CIRMOD_PD_FAN_DST[ALERT_P_CIRMOD_PD_FAN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_CIRMOD_PD_FAN_CLING,                                       /* 01 CLING                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_CIRMOD_MTRX[4] = {
    {
        &u4_s_AlertP_cirmodTtAlcSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CIRMOD_TT_ALC_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_P_CIRMOD_TT_ALC_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_cirmodTtCmSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CIRMOD_TT_CM_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_P_CIRMOD_TT_CM_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_cirmodPdCmSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CIRMOD_PD_CM_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_P_CIRMOD_PD_CM_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_cirmodPdFanSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_CIRMOD_PD_FAN_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_P_CIRMOD_PD_FAN_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cirmodTtAlcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cirmodTtAlcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_P_CIRMOD_ALC_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S98,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_CIRMOD_ALC_LSB_MSG);

    u1_t_sgnl     = (U1)0U;

#if 0  /* For R2 Implementation */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ALCCM, &u1_t_sgnl);
#endif

    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cirmodTtCmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cirmodTtCmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_P_CIRMOD_SLCT_MSG = (U1)3U;
    static const U1 u1_s_ALERT_P_CIRMOD_SLCT     = (U1)2U;
    static const U1 u1_s_ALERT_P_CIRMOD_BXCM_MSG = (U1)1U;

    U4              u4_t_src_chk;
    U1              u1_t_msgsts_ect1s80;
    U1              u1_t_msgsts_eng1s99;
    U1              u1_t_sgnl;

    u1_t_msgsts_ect1s80 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1S80_RXCH0,
                                           (U2)OXCAN_RX_SYS_NRX_IGR,
                                           (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk = ((U4)u1_t_msgsts_ect1s80 << u1_s_ALERT_P_CIRMOD_SLCT_MSG);

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SLCT, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_P_CIRMOD_SLCT);

    u1_t_msgsts_eng1s99 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                           (U2)OXCAN_RX_SYS_NRX_IGR,
                                           (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  |= ((U4)u1_t_msgsts_eng1s99 << u1_s_ALERT_P_CIRMOD_BXCM_MSG);

    u1_t_sgnl = (U1)0U;
#if 0  /* For R2 Implementation */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_XCM, &u1_t_sgnl);
#endif
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cirmodPdCmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cirmodPdCmSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_P_CIRMOD_PDCM_LSB_MSG = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_CIRMOD_PDCM_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_SCM, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cirmodPdFanSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cirmodPdFanSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_P_CIRMOD_FAN_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_CIRMOD_FAN_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
#if 0  /* For R2 Implementation */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_FANCM, &u1_t_sgnl);
#endif
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
/*  5.0.0    12/02/2022  MY       New.                                                                                               */
/*  5.1.0    07/09/2024  JMH      Update for 19PFV3                                                                                  */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * JMH  = James Michael D. Hilarion, DTPH JM                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
