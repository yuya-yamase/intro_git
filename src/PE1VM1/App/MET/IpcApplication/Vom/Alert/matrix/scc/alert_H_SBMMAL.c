/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_SBMMAL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_SBMMAL_C_MAJOR                   (5)
#define ALERT_H_SBMMAL_C_MINOR                   (1)
#define ALERT_H_SBMMAL_C_PATCH                   (0)

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
#if (ALERT_H_SBMMAL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_SBMMAL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_SBMMAL_NUM_DST                   (64U)

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
static U4      u4_s_AlertH_sbmmalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_sbmmalRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_SBMMAL_DST[ALERT_H_SBMMAL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 01 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 08 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 09 IMPSBLBU                                        */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 10 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 11 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 12 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 13 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 14 RW                                              */
    (U1)ALERT_REQ_H_SBMMAL_RW,                                                 /* 15 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 17 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 25 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 33 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 41 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 49 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_H_SBMMAL_IMPSBLBU,                                           /* 57 IMPSBLBU                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_SBMMAL_MTRX[1] = {
    {
        &u4_s_AlertH_sbmmalSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_sbmmalRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_SBMMAL_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_H_SBMMAL_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_sbmmalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_sbmmalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if (defined(OXCAN_PDU_RX_CAN_SBM1F01) && defined(ComConf_ComSignal_SBMFAILD)) || (defined(OXCAN_PDU_RX_CAN_SBM1S02) && defined(ComConf_ComSignal_SBMFAULT))
#if defined(OXCAN_PDU_RX_CAN_SBM1F01) /* _117D_CAN_ */
    static const U1 u1_s_ALERT_H_SBMMAL_LSB_SBM1F01  = (U1)5U;
#endif /* defined(OXCAN_PDU_RX_CAN_SBM1F01) */
#if defined(ComConf_ComSignal_SBMFAILD) /* _117D_CAN_ */
    static const U1 u1_s_ALERT_H_SBMMAL_LSB_SBMFAILD = (U1)3U;
#endif /* defined(ComConf_ComSignal_SBMFAILD) */
#if defined(OXCAN_PDU_RX_CAN_SBM1S02) /* _117D_CAN_ */
    static const U1 u1_s_ALERT_H_SBMMAL_LSB_SBM1S02  = (U1)2U;
#endif /* defined(OXCAN_PDU_RX_CAN_SBM1S02) */
    U4              u4_t_src_chk;
#if defined(OXCAN_PDU_RX_CAN_SBM1F01) || defined(OXCAN_PDU_RX_CAN_SBM1S02) /* _117D_CAN_ */
    U1              u1_t_msgsts;
#endif /* defined(OXCAN_PDU_RX_CAN_SBM1F01) || defined(OXCAN_PDU_RX_CAN_SBM1S02) */
    U1              u1_t_sgnl;

#if defined(OXCAN_PDU_RX_CAN_SBM1F01) /* _117D_CAN_ */
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBM1F01,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_SBMMAL_LSB_SBM1F01);
#else
    u4_t_src_chk  = (U4)0U;
#endif /* defined(OXCAN_PDU_RX_CAN_SBM1F01) */

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_SBMFAILD) /* _117D_CAN_ */
    (void)Com_ReceiveSignal(ComConf_ComSignal_SBMFAILD, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_H_SBMMAL_LSB_SBMFAILD);
#endif /* defined(ComConf_ComSignal_SBMFAILD) */

#if defined(OXCAN_PDU_RX_CAN_SBM1S02) /* _117D_CAN_ */
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBM1S02,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_SBMMAL_LSB_SBM1S02);
#endif /* defined(OXCAN_PDU_RX_CAN_SBM1S02) */

#if defined(ComConf_ComSignal_SBMFAULT) /* _117D_CAN_ */
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_SBMFAULT, &u1_t_sgnl);
#endif
    u4_t_src_chk |= (U4)u1_t_sgnl;
#endif /* defined(ComConf_ComSignal_SBMFAULT) */

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* (defined(OXCAN_PDU_RX_CAN_SBM1F01) && defined(ComConf_ComSignal_SBMFAILD)) || (defined(OXCAN_PDU_RX_CAN_SBM1S02) && defined(ComConf_ComSignal_SBMFAULT)) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_sbmmalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_sbmmalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if defined(ComConf_ComSignal_SBMW) /* _117D_CAN_ */
    static const U4 u4_s_ALERT_H_SBMMAL_RWTX_CRT = ((U4)((U4)1U << ALERT_REQ_H_SBMMAL_IMPSBLBU)
                                                  | (U4)((U4)1U << ALERT_REQ_H_SBMMAL_RW      ));
    static const U1 u1_s_ALERT_H_SBMMAL_RWTX_MSK = (U1)0x03U;
    U1              u1_t_sbmw;
    U4              u4_t_rw;

    u4_t_rw   = ((U4)1U << (u1_a_DST & u1_s_ALERT_H_SBMMAL_RWTX_MSK));
    u1_t_sbmw = (U1)ALERT_RW_SGNL_OFF;
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)         != (U1)0U) &&
       ((u4_t_rw  & u4_s_ALERT_H_SBMMAL_RWTX_CRT) != (U4)0U)){
        u1_t_sbmw = (U1)ALERT_RW_SGNL_ON;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SBMW, &u1_t_sbmw);    /* COM Tx STUB delete */
#endif
#endif /* defined(ComConf_ComSignal_SBMW) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     1/18/2022  RI       New.                                                                                               */
/*  5.0.1     3/16/2022  RI       Change RW Judge(Add CAN signal SBMFAILD).                                                          */
/*  5.1.0     2/05/2024  SW       Update for 19PFv3(change oXCAN I/F name).                                                          */
/*                                                                                                                                   */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
