/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_LDA                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_LDA_C_MAJOR                      (5)
#define ALERT_S_LDA_C_MINOR                      (5)
#define ALERT_S_LDA_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_LDA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_LDA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_LDA_TT_LDA_NUM_DST               (64U)
#define ALERT_S_LDA_BC_LDW_NUM_DST               (16U)
#define ALERT_S_LDA_BC_CSF_NUM_DST               (8U)
#define ALERT_S_LDA_PD_LDA_NUM_DST               (64U)

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
static U4      u4_s_AlertS_ldaTtLdaSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_ldaBcLdwSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_ldaBcCsfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_ldaPdLdaSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_LDA_TT_LDA_DST[ALERT_S_LDA_TT_LDA_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_W,                                           /* 01 ON_W                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_TT_LDA_FLASH_A,                                        /* 03 FLASH_A                                         */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 04 ON_A                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_R,                                           /* 06 ON_R                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_TT_LDA_LDAOFF_A,                                       /* 08 LDAOFF_A                                        */
    (U1)ALERT_REQ_S_LDA_TT_LDA_LDAOFF_W,                                       /* 09 LDAOFF_W                                        */
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
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 32 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 33 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 34 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 35 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 36 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 37 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 38 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 39 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 40 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 41 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 42 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 43 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 44 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 45 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 46 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 47 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 48 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 49 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 50 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 51 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 52 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 53 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 54 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 55 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 56 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 57 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 58 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 59 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 60 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 61 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,                                           /* 62 ON_A                                            */
    (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A                                            /* 63 ON_A                                            */
};
static const U1  u1_sp_ALERT_S_LDA_BC_LDW_DST[ALERT_S_LDA_BC_LDW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_BC_LDW_CYCL1,                                          /* 01 CYCL1                                           */
    (U1)ALERT_REQ_S_LDA_BC_LDW_CYCL2,                                          /* 02 CYCL2                                           */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_LDA_BC_CSF_DST[ALERT_S_LDA_BC_CSF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_BC_CSF_CYCL,                                           /* 01 CYCL                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_LDA_PD_LDA_DST[ALERT_S_LDA_PD_LDA_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_PD_LDA_UNAVLBL1,                                       /* 04 UNAVLBL1                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_PD_LDA_RESTRICT,                                       /* 09 RESTRICT                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_PD_LDA_LANEDEP,                                        /* 12 LANEDEP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_S_LDA_PD_LDA_LANEDEV,                                        /* 14 LANEDEV                                         */
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
const ST_ALERT_MTRX st_gp_ALERT_S_LDA_MTRX[4] = {
    {
        &u4_s_AlertS_ldaTtLdaSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_LDA_TT_LDA_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_LDA_TT_LDA_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_ldaBcLdwSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_LDA_BC_LDW_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_LDA_BC_LDW_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_ldaBcCsfSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_LDA_BC_CSF_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_LDA_BC_CSF_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_ldaPdLdaSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_LDA_PD_LDA_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_LDA_PD_LDA_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ldaTtLdaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ldaTtLdaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_LDA_TT_LDA_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_LDA_TT_LDA_LSB_STS = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DS12F03,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_LDA_TT_LDA_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDAINDI, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_LDA_TT_LDA_LSB_STS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ldaBcLdwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ldaBcLdwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_LDA_BC_LDW_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_LDA_BC_LDW_LSB_STS = (U1)2U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DS12F03,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_LDA_BC_LDW_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDWBUZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_LDA_BC_LDW_LSB_STS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ldaBcCsfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ldaBcCsfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_LDA_BC_CSF_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_LDA_BC_CSF_LSB_STS = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DS12F03,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_LDA_BC_CSF_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSFBUZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_LDA_BC_CSF_LSB_STS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_ldaPdLdaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_ldaPdLdaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_S_LDA_PD_LDA_TO_THRS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_LDA_PD_LDA_LSB_STS = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DS12F03,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_S_LDA_PD_LDA_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDAMSG, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_LDA_PD_LDA_LSB_STS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
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
/*  5.0.0     3/11/2020  MY       New.                                                                                               */
/*  5.1.0    12/ 8/2020  SO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/25/2021  SO       Update for 840B CV(Version update).                                                                */
/*  5.2.0    10/26/2021  KT       Update for 840B 1A(Version update).                                                                */
/*  5.3.0     1/ 5/2022  HU       Update for 840B 1A(Delete RW functions).                                                           */
/*  5.4.0     5/30/2022  KK       Add Req for u1_sp_ALERT_S_LDA_PD_LDA_DST.                                                          */
/*  5.5.0    11/10/2023  DR       Update for 19PFv3(delete LDOFINDI,SW)                                                              */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * DR   = Dyan Reyes, Denso Techno Philippines Inc.                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
