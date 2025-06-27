/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_BATCOO                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATCOO_C_MAJOR                   (5)
#define ALERT_H_BATCOO_C_MINOR                   (0)
#define ALERT_H_BATCOO_C_PATCH                   (0)

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
#if (ALERT_H_BATCOO_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_BATCOO.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATCOO_TT_PD_NUM_DST             (16U)
#define ALERT_H_BATCOO_BC_NUM_DST                (4U)

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
static U4      u4_s_AlertH_batcooTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_batcooBcSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_batcooTtPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_BATCOO_TT_PD_DST[ALERT_H_BATCOO_TT_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_TT,                                           /* 01 TT                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_TT,                                           /* 03 TT                                              */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_PD02,                                         /* 04 PD02                                            */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_TT_PD02,                                      /* 05 TT_PD02                                         */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_PD03,                                         /* 06 PD03                                            */
    (U1)ALERT_REQ_H_BATCOO_TT_PD_TT_PD03,                                      /* 07 TT_PD03                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_BATCOO_BC_DST[ALERT_H_BATCOO_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATCOO_BC_MALFUNC,                                         /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_BATCOO_MTRX[2] = {
    {
        &u4_s_AlertH_batcooTtPdSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_batcooTtPdRwTx,                                           /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATCOO_TT_PD_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_H_BATCOO_TT_PD_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_batcooBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATCOO_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_BATCOO_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_batcooTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_batcooTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_BATCOO_TTPD_LSB_STS = (U1)3U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSM)
    static const U1 u1_s_ALERT_H_BATCOO_LSB_HVBCSM   = (U1)1U;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSM) */
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) */

    u1_t_sgnl     = (U1)0U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_B_HVID1)
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_HVID1, &u1_t_sgnl);
#endif
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_B_HVID1) */
    u4_t_src_chk  = (U4)u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSM)
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVBCSM, &u1_t_sgnl);
#endif
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_H_BATCOO_LSB_HVBCSM);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSM) */
    
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_BATCOO_TTPD_LSB_STS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_batcooBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_batcooBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSMB)
    static const U1 u1_s_ALERT_H_BATCOO_BC_LSB_STS = (U1)1U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) */

    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVBCSMB, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_BATCOO_BC_LSB_STS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) && defined(ComConf_ComSignal_HVBCSMB) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_batcooTtPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_batcooTtPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U2 u2_s_ALERT_H_BATCOO_TTPD_RW_CRT = (U2)((U2)1U << ALERT_REQ_H_BATCOO_TT_PD_TT) 
                                                    | (U2)((U2)1U << ALERT_REQ_H_BATCOO_TT_PD_PD02)
                                                    | (U2)((U2)1U << ALERT_REQ_H_BATCOO_TT_PD_PD03)
                                                    | (U2)((U2)1U << ALERT_REQ_H_BATCOO_TT_PD_TT_PD02)
                                                    | (U2)((U2)1U << ALERT_REQ_H_BATCOO_TT_PD_TT_PD03);       /* HVBW                */
    static const U1 u1_s_ALERT_H_BATCOO_TTPD_RW_MSK = (U1)0x07U;
    
    U1              u1_t_sgnl;
    U2              u2_t_rw;

    u2_t_rw = ((U2)1U << (u1_a_DST & u1_s_ALERT_H_BATCOO_TTPD_RW_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)            != (U1)0U) &&
       ((u2_t_rw  & u2_s_ALERT_H_BATCOO_TTPD_RW_CRT) != (U2)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_HVBW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     4/ 8/2020  TI       New.                                                                                               */
/*                                                                                                                                   */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
