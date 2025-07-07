/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_SYSMAL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_SYSMAL_C_MAJOR                   (5)
#define ALERT_H_SYSMAL_C_MINOR                   (7)
#define ALERT_H_SYSMAL_C_PATCH                   (0)

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
#if (ALERT_H_SYSMAL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_SYSMAL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_SYSMAL_BC_NUM_DST                (32U)
#define ALERT_H_SYSMAL_PD1_NUM_DST               (16U)
#define ALERT_H_SYSMAL_PD2_NUM_DST               (64U)
#define ALERT_H_SYSMAL_RW_NUM_DST                (32U)

#define ALERT_H_SYSMAL_PTSYS_NUM_TBL             (32U)
#define ALERT_H_SYSMAL_HVMALPAT_NUM_TBL          (8U)
#define ALERT_H_SYSMAL_HVIND_NUM_TBL             (16U)

#define ALERT_H_SYSMAL_PTSYS_OTHER               (0x00U)
#define ALERT_H_SYSMAL_PTSYS_HV                  (0x08U)
#define ALERT_H_SYSMAL_PTSYS_EV                  (0x10U)
#define ALERT_H_SYSMAL_HVMALPAT_RW_OFF           (0x00U)
#define ALERT_H_SYSMAL_HVMALPAT_RW_ON            (0x04U)
#define ALERT_H_SYSMAL_HVIND_RW_OFF              (0x00U)
#define ALERT_H_SYSMAL_HVIND_RW_PTN1             (0x01U)
#define ALERT_H_SYSMAL_HVIND_RW_PTN2             (0x02U)

#define ALERT_H_SYSMAL_RWSGNL_HVSW               (0U)
#define ALERT_H_SYSMAL_RWSGNL_HVSW2              (1U)
#define ALERT_H_SYSMAL_RWSGNL_EVSW               (2U)
#define ALERT_H_SYSMAL_RWSGNL_EVSW2              (3U)

#define ALERT_H_SYSMAL_NUM_RWSGNL                (4U)

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
static U4      u4_s_AlertH_sysmalBcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_sysmalPd1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_sysmalPd2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_sysmalRwSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_sysmalRwRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_SYSMAL_BC_DST[ALERT_H_SYSMAL_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SYSMAL_BC_SINGLE,                                          /* 01 SINGLE                                          */
    (U1)ALERT_REQ_H_SYSMAL_BC_ON,                                              /* 02 ON                                              */
    (U1)ALERT_REQ_H_SYSMAL_BC_CYCL1,                                           /* 03 CYCL1                                           */
    (U1)ALERT_REQ_H_SYSMAL_BC_CYCL2,                                           /* 04 CYCL2                                           */
    (U1)ALERT_REQ_H_SYSMAL_BC_CYCL3,                                           /* 05 CYCL3                                           */
    (U1)ALERT_REQ_H_SYSMAL_BC_CYCL4,                                           /* 06 CYCL4                                           */
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
static const U1  u1_sp_ALERT_H_SYSMAL_PD1_DST[ALERT_H_SYSMAL_PD1_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT4,                                        /* 01 MALPAT4                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT6,                                        /* 02 MALPAT6                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT1,                                        /* 03 MALPAT1                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT2,                                        /* 04 MALPAT2                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT5,                                        /* 05 MALPAT5                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT3,                                        /* 06 MALPAT3                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_SYSMAL_PD2_DST[ALERT_H_SYSMAL_PD2_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND1,                                           /* 01 IND1                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND2,                                           /* 02 IND2                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND3,                                           /* 03 IND3                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND7,                                           /* 04 IND7                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND8,                                           /* 05 IND8                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND9,                                           /* 06 IND9                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND10,                                          /* 07 IND10                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND11,                                          /* 08 IND11                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND12,                                          /* 09 IND12                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND13,                                          /* 10 IND13                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND4,                                           /* 11 IND4                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND5,                                           /* 12 IND5                                            */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND15,                                          /* 13 IND15                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND14,                                          /* 14 IND14                                           */
    (U1)ALERT_REQ_H_SYSMAL_PD2_IND6,                                           /* 15 IND6                                            */
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
static const U1  u1_sp_ALERT_H_SYSMAL_RW_DST[ALERT_H_SYSMAL_RW_NUM_DST] = {
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
    (U1)ALERT_REQ_H_SYSMAL_RW_HVSW,                                            /* 13 HVSW                                            */
    (U1)ALERT_REQ_H_SYSMAL_RW_HVSW2,                                           /* 14 HVSW2                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SYSMAL_RW_EVSW,                                            /* 17 EVSW                                            */
    (U1)ALERT_REQ_H_SYSMAL_RW_EVSW2,                                           /* 18 EVSW2                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SYSMAL_RW_EVSW,                                            /* 21 EVSW                                            */
    (U1)ALERT_REQ_H_SYSMAL_RW_EVSW2,                                           /* 22 EVSW2                                           */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_SYSMAL_MTRX[4] = {
    {
        &u4_s_AlertH_sysmalBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_SYSMAL_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_SYSMAL_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_sysmalPd1Srcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_SYSMAL_PD1_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_H_SYSMAL_PD1_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_sysmalPd2Srcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_SYSMAL_PD2_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_H_SYSMAL_PD2_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_sysmalRwSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_sysmalRwRwTx,                                             /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_SYSMAL_RW_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_SYSMAL_RW_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_sysmalBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_sysmalBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_SYSMALBC_LSB_EHV  = (U1)3U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0)
    static const U2 u2_s_ALERT_H_SYSMALBC_THRSH_TO = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0) */
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_H_SYSMALBC_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0) */
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_SYSMALBC_LSB_EHV);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_HVBUZZ
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVBUZZ, &u1_t_sgnl);
#endif /* ComConf_ComSignal_HVBUZZ */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_sysmalPd1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_sysmalPd1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_SYSMALPD1_LSB_EHV  = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0) */
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_SYSMALPD1_LSB_EHV);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_HVMALPAT
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVMALPAT, &u1_t_sgnl);
#endif /* ComConf_ComSignal_HVMALPAT */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_sysmalPd2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_sysmalPd2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_SYSMALPD2_LSB_EHV   = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0) */
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_SYSMALPD2_LSB_EHV);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_HVIND
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVIND, &u1_t_sgnl);
#endif /* ComConf_ComSignal_HVIND */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_sysmalRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_sysmalRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_sp_ALERT_H_SYSMALRW_PTSYS_JDG[ALERT_H_SYSMAL_PTSYS_NUM_TBL] = {
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_HV,
        (U1)ALERT_H_SYSMAL_PTSYS_HV,
        (U1)ALERT_H_SYSMAL_PTSYS_EV,
        (U1)ALERT_H_SYSMAL_PTSYS_HV,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_OTHER,
        (U1)ALERT_H_SYSMAL_PTSYS_HV
    };
    static const U1 u1_sp_ALERT_H_SYSMALRW_MLPT_JDG[ALERT_H_SYSMAL_HVMALPAT_NUM_TBL] = {
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_OFF,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_ON,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_ON,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_ON,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_ON,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_OFF,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_ON,
        (U1)ALERT_H_SYSMAL_HVMALPAT_RW_OFF
    };
    static const U1 u1_sp_ALERT_H_SYSMALRW_HVIND_JDG[ALERT_H_SYSMAL_HVIND_NUM_TBL] = {
        (U1)ALERT_H_SYSMAL_HVIND_RW_OFF,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN2,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN2,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN2,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN2,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1,
        (U1)ALERT_H_SYSMAL_HVIND_RW_PTN1
    };

    U4              u4_t_src_chk;
    U4              u4_t_ptsys_jdg;
    U4              u4_t_mlpt_jdg;
    U4              u4_t_hvind_jdg;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0)
    u1_t_msgsts    = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
                                      (U4)OXCAN_SYS_IGR,
                                      (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S26_CH0) */
    u1_t_sgnl      = (U1)0U;
#ifdef ComConf_ComSignal_HVMALPAT
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVMALPAT, &u1_t_sgnl);
#endif /* ComConf_ComSignal_HVMALPAT */
    if(u1_t_msgsts == (U1)COM_NO_RX){
        u4_t_mlpt_jdg  = (U4)ALERT_H_SYSMAL_HVMALPAT_RW_OFF;
    }
    else if(u1_t_sgnl >= (U1)ALERT_H_SYSMAL_HVMALPAT_NUM_TBL){
        u4_t_mlpt_jdg  = (U4)ALERT_H_SYSMAL_HVMALPAT_RW_OFF;
    }
    else{
        u4_t_mlpt_jdg  = (U4)u1_sp_ALERT_H_SYSMALRW_MLPT_JDG[u1_t_sgnl];
    }

    u1_t_sgnl      = (U1)0U;
#ifdef ComConf_ComSignal_HVIND
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVIND, &u1_t_sgnl);
#endif /* ComConf_ComSignal_HVIND */
    if((u1_t_msgsts == (U1)COM_NO_RX                   ) ||
       (u1_t_sgnl   >= (U1)ALERT_H_SYSMAL_HVIND_NUM_TBL)){
        u4_t_hvind_jdg = (U4)ALERT_H_SYSMAL_HVIND_RW_OFF;
    }
    else{
        u4_t_hvind_jdg = (U4)u1_sp_ALERT_H_SYSMALRW_HVIND_JDG[u1_t_sgnl];
    }

    u1_t_sgnl      = u1_g_AlertPtsys();
    if(u1_t_sgnl > (U1)ALERT_PTSYS_1F_NRX){
        u1_t_sgnl      = (U1)ALERT_PTSYS_0F_UNK;
    }
    u4_t_ptsys_jdg = (U4)u1_sp_ALERT_H_SYSMALRW_PTSYS_JDG[u1_t_sgnl];

    u4_t_src_chk   = (u4_t_ptsys_jdg | u4_t_mlpt_jdg | u4_t_hvind_jdg);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_sysmalRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_sysmalRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_sp_ALERT_H_SYSMALRWTX_VOM_CRT[ALERT_H_SYSMAL_NUM_RWSGNL] = {
        (U1)ALERT_VOM_IGN_ON,                                       /* HVSW     */
        (U1)ALERT_VOM_RWT_EN,                                       /* HVSW2    */
        (U1)ALERT_VOM_IGN_ON,                                       /* EVSW     */
        (U1)ALERT_VOM_RWT_EN                                        /* EVSW2    */
    };
    static const U1 u1_sp_ALERT_H_SYSMALRWTX_DST_CRT[ALERT_H_SYSMAL_NUM_RWSGNL] = {
        ((U1)1U << ALERT_REQ_H_SYSMAL_RW_HVSW),                     /* HVSW     */
        ((U1)1U << ALERT_REQ_H_SYSMAL_RW_HVSW2),                    /* HVSW2    */
        ((U1)1U << ALERT_REQ_H_SYSMAL_RW_EVSW),                     /* EVSW     */
        ((U1)1U << ALERT_REQ_H_SYSMAL_RW_EVSW2)                     /* EVSW2    */
    };
    static const U1 u1_s_ALERT_H_SYSMALRWTX_DST_MSK = (U1)0x03U;

    U1              u1_tp_sgnl[ALERT_H_SYSMAL_NUM_RWSGNL];
    U1              u1_t_rw;
    U4              u4_t_idx;

    u1_t_rw = (U1)0U;
    if(u1_a_DST != (U1)ALERT_REQ_UNKNOWN){
        u1_t_rw = ((U1)1U << (u1_a_DST & u1_s_ALERT_H_SYSMALRWTX_DST_MSK));
    }
    for(u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_H_SYSMAL_NUM_RWSGNL; u4_t_idx++){
        if(((u1_a_VOM & u1_sp_ALERT_H_SYSMALRWTX_VOM_CRT[u4_t_idx]) != (U1)0U) &&
           ((u1_t_rw  & u1_sp_ALERT_H_SYSMALRWTX_DST_CRT[u4_t_idx]) != (U1)0U)){
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_ON;
        }
        else{
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_OFF;
        }
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_HVSW, &u1_tp_sgnl[ALERT_H_SYSMAL_RWSGNL_HVSW]);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_HVSW2, &u1_tp_sgnl[ALERT_H_SYSMAL_RWSGNL_HVSW2]);    /* COM Tx STUB delete */
#endif
#if defined(ComConf_ComSignal_EVSW)
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_EVSW, &u1_tp_sgnl[ALERT_H_SYSMAL_RWSGNL_EVSW]);    /* COM Tx STUB delete */
#endif
#endif /* defined(ComConf_ComSignal_EVSW)  */
#if defined(ComConf_ComSignal_EVSW2)
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_EVSW2, &u1_tp_sgnl[ALERT_H_SYSMAL_RWSGNL_EVSW2]);    /* COM Tx STUB delete */
#endif
#endif /* defined(ComConf_ComSignal_EVSW2)  */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/27/2020  MY       New.                                                                                               */
/*  5.1.0     7/28/2020  ZS       Fix RW REQ Index table.                                                                            */
/*  5.2.0     9/10/2020  MY       Fix PTSYS initial value when no receive.                                                           */
/*  5.3.0     9/23/2020  MY       Fix receive logic when PTSYS is out of range.                                                      */
/*  5.4.0    12/ 7/2020  MO       Update for 800B 1A(HVMALPAT judg change).                                                          */
/*  5.5.0     4/15/2021  SO       Change remote warning logic.                                                                       */
/*  5.5.1     6/23/2021  TN       Update for 050D CV(Version update).                                                                */
/*  5.5.2    11/16/2021  TM       Fix QAC Warning.                                                                                   */
/*  5.6.0    01/12/2024  RO       Update for 19PFv3.                                                                                 */
/*  5.7.0    10/25/2024  RS       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
