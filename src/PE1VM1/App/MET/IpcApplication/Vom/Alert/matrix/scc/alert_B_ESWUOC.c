/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_ESWUOC                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_ESWUOC_C_MAJOR                   (5)
#define ALERT_B_ESWUOC_C_MINOR                   (5)
#define ALERT_B_ESWUOC_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_ESWUOC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_ESWUOC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_ESWUOC_BCB_NUM_DST               (16U)
#define ALERT_B_ESWUOC_BC_NUM_DST                (8U)
#define ALERT_B_ESWUOC_PD_NUM_DST                (16U)
#define ALERT_B_ESWUOC_PDB_NUM_DST               (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ)
static U1      u1_s_alert_b_eswuoc_bcb_msgsts;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ) */
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID)
static U1      u1_s_alert_b_eswuoc_pdb_msgsts;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_eswuocBcbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_eswuocBcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_eswuocPdSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_eswuocPdbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertB_eswuocPdbRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_ESWUOC_BCB_DST[ALERT_B_ESWUOC_BCB_NUM_DST] = {
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
    (U1)ALERT_REQ_B_ESWUOC_BCB_DOUBLE,                                         /* 11 DOUBLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_ESWUOC_BC_DST[ALERT_B_ESWUOC_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_B_ESWUOC_BC_DOUBLE,                                          /* 02 DOUBLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_ESWUOC_PD_DST[ALERT_B_ESWUOC_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_B_ESWUOC_PD_UNLTCHFL,                                        /* 03 UNLTCHFL                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_B_ESWUOC_PD_STPATUNLCK,                                      /* 05 STPATUNLCK                                      */
    (U1)ALERT_REQ_B_ESWUOC_PD_SPDATUNLCK,                                      /* 06 SPDATUNLCK                                      */
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
static const U1  u1_sp_ALERT_B_ESWUOC_PDB_DST[ALERT_B_ESWUOC_PDB_NUM_DST] = {
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
    (U1)ALERT_REQ_B_ESWUOC_PDB_SYSMLFNC,                                       /* 17 SYSMLFNC                                        */
    (U1)ALERT_REQ_B_ESWUOC_PDB_LHDSHOCK,                                       /* 18 LHDSHOCK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_B_ESWUOC_PDB_RHDSHOCK,                                       /* 23 RHDSHOCK                                        */
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
const ST_ALERT_MTRX st_gp_ALERT_B_ESWUOC_MTRX[4] = {
    {
        &u4_s_AlertB_eswuocBcbSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_ESWUOC_BCB_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_B_ESWUOC_BCB_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_eswuocBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_ESWUOC_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_B_ESWUOC_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_eswuocPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_ESWUOC_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_B_ESWUOC_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_eswuocPdbSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_eswuocPdbRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_ESWUOC_PDB_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_B_ESWUOC_PDB_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_eswuocInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_eswuocInit(void)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ)
    u1_s_alert_b_eswuoc_bcb_msgsts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ) */
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID)
    u1_s_alert_b_eswuoc_pdb_msgsts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_eswuocBcbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_eswuocBcbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ)
    static const U1 u1_s_ALERT_B_ESWUOC_BCB_LSB_MSG  = (U1)2U;
    static const U4 u4_s_ALERT_B_ESWUOC_BCB_BIT_BTWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_PBA,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_eswuoc_bcb_msgsts, u1_t_msgsts);

    u4_t_src_chk  = (((U4)u1_s_alert_b_eswuoc_bcb_msgsts & (U4)COM_NO_RX) << u1_s_ALERT_B_ESWUOC_BCB_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EL_BZ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_ESWUOC_BCB_BIT_BTWT;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_eswuocBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_eswuocBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ)
    static const U1 u1_s_ALERT_B_ESWUOC_BC_LSB_MSG = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EL_BZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_ESWUOC_BC_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_BZ) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_eswuocPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_eswuocPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID)
    static const U1 u1_s_ALERT_B_ESWUOC_PD_LSB_MSG = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EL_MID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_ESWUOC_PD_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_eswuocPdbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_eswuocPdbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID)
    static const U2 u2_s_ALERT_B_ESWUOC_PDB_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_ESWUOC_PDB_LSB_MSG  = (U1)3U;
    static const U4 u4_s_ALERT_B_ESWUOC_PDB_BIT_BTWT = (U4)0x00000010U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S05_RXCH0,
                                      (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                      u2_s_ALERT_B_ESWUOC_PDB_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_eswuoc_pdb_msgsts, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EL_MID, &u1_t_sgnl);
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= (((U4)u1_s_alert_b_eswuoc_pdb_msgsts & (U4)COM_NO_RX) << u1_s_ALERT_B_ESWUOC_PDB_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_ESWUOC_PDB_BIT_BTWT;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S05_RXCH0) && defined(ComConf_ComSignal_EL_MID) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_eswuocPdbRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_eswuocPdbRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                             ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_B_ESWUOC_PDB_SYSMLFNC)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ELSW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     2/21/2020  FN       New.                                                                                               */
/*  5.1.0     8/27/2020  TN       Modify index table for BC.                                                                         */
/*  5.2.0    12/ 7/2020  TN       PDB CH Add.                                                                                        */
/*  5.2.1    12/23/2020  TM       Add mask of communication status.                                                                  */
/*  5.3.0     2/ 3/2021  ZS       Add processing when communication fail for pdb.                                                    */
/*  5.4.0     6/23/2021  SO       Add CH for BCB, and Change matrix table for BC/PD/PDB, and Change RwTx logic.                      */
/*  5.5.0     0/19/2024  YR       Updated for 19PFv3                                                                                 */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
