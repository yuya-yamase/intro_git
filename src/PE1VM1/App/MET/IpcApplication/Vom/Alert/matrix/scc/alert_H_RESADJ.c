/* 5.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_RESADJ                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_RESADJ_C_MAJOR                   (5)
#define ALERT_H_RESADJ_C_MINOR                   (2)
#define ALERT_H_RESADJ_C_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_RESADJ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_RESADJ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_RESADJ_NUM_DST                   (32U)

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
static U4      u4_s_AlertH_resadjSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_RESADJ_DST[ALERT_H_RESADJ_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_RESADJ_BLANK,                                              /* 01 BLANK                                           */
    (U1)ALERT_REQ_H_RESADJ_RES_1,                                              /* 02 RES_1                                           */
    (U1)ALERT_REQ_H_RESADJ_RES_2,                                              /* 03 RES_2                                           */
    (U1)ALERT_REQ_H_RESADJ_RES_3,                                              /* 04 RES_3                                           */
    (U1)ALERT_REQ_H_RESADJ_RESOLVER_1,                                         /* 05 RESOLVER_1                                      */
    (U1)ALERT_REQ_H_RESADJ_RESOLVER_2,                                         /* 06 RESOLVER_2                                      */
    (U1)ALERT_REQ_H_RESADJ_RESOLVER_R,                                         /* 07 RESOLVER_R                                      */
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_RESADJ_MTRX[1] = {
    {
        &u4_s_AlertH_resadjSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_RESADJ_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_H_RESADJ_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_resadjSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_resadjSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if defined(OXCAN_PDU_RX_CAN_MGC1S03)
    static const U2 u2_s_ALERT_H_RESADJ_TO_THRS = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_PDU_RX_CAN_MGC1S03) */ /* 840B_CAN */
    static const U1 u1_s_ALERT_H_RESADJ_LSB_STS = (U1)3U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#if defined(OXCAN_PDU_RX_CAN_MGC1S03)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_MGC1S03,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_H_RESADJ_TO_THRS) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_MGC1S03) */ /* 840B_CAN */

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_RESDISP
    (void)Com_ReceiveSignal(ComConf_ComSignal_RESDISP, &u1_t_sgnl);
#endif /* ComConf_ComSignal_RESDISP */ /* 840B_CAN */
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_RESADJ_LSB_STS);

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
/*  5.0.0     4/ 6/2020  TI       New.                                                                                               */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.2.0    10/25/2021  KT       Update for 840B 1A(Version update).                                                                */
/*  5.2.1    01/18/2022  TM       Fix QAC Warning.                                                                                   */
/*                                                                                                                                   */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
