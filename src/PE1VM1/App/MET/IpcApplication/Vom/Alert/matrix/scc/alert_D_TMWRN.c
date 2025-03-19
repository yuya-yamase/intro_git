/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_TMWRN                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_TMWRN_C_MAJOR                     (5)
#define ALERT_D_TMWRN_C_MINOR                     (1)
#define ALERT_D_TMWRN_C_PATCH                     (0)

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
#if (ALERT_D_TMWRN_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_TMWRN.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_TMWRN_NUM_DST                    (26U)

#define ALERT_D_TMWRN_RWSGNL_NUM                 (3U)
#define ALERT_D_TMWRN_RWSGNL_TMW1                (0U)
#define ALERT_D_TMWRN_RWSGNL_TMW2                (1U)
#define ALERT_D_TMWRN_RWSGNL_TMW3                (2U)

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
static U4      u4_s_AlertD_tmwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertD_tmwrnRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_D_TMWRN_DST[ALERT_D_TMWRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_TMWRN_TMSYSLIMIT,                                          /* 01 TMSYSLIMIT                                      */
    (U1)ALERT_REQ_D_TMWRN_TMSYSMAL,                                            /* 02 TMSYSMAL                                        */
    (U1)ALERT_REQ_D_TMWRN_TMSYSSTOP,                                           /* 03 TMSYSSTOP                                       */
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
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 16 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW1,                                        /* 17 UNKNOWN_TMW1                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 18 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW3,                                        /* 19 UNKNOWN_TMW3                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 20 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 21 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 22 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 23 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 24 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 25 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_TMWRN_MTRX[1] = {
    {
        &u4_s_AlertD_tmwrnSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_tmwrnRwTx,                                                /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_TMWRN_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_D_TMWRN_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_tmwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_tmwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_TMWRN_LSB_MSGSTS  = (U1)3U;
    static const U1 u1_s_ALERT_TMSYS_WM_LSB_VALUE  = (U1)4U;
    static const U1 u1_s_ALERT_TMSYS_WM_LSB_MSGSTS = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMFL_IND, &u1_t_sgnl);
    
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_TMWRN_LSB_MSGSTS);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMSYS_WM, &u1_t_sgnl);

    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_TMSYS_WM_LSB_VALUE);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_TMSYS_WM_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_tmwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_tmwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_B_TMWRN_DST_CRT[ALERT_D_TMWRN_RWSGNL_NUM] = {
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_TMSYSLIMIT) | (U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW1)), /* TMW1 */
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_TMSYSMAL  ) | (U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW1)
                                                      | (U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW2)
                                                      | (U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW3)), /* TMW2 */
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_TMSYSSTOP ) | (U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW3))  /* TMW3 */
    };

    static const U1 u1_s_ALERT_B_TMWRN_RWTX_MSK    = (U1)0x07U;
    static const U4 u4_s_ALERT_D_TMWRN_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_NUM];
    U4              u4_t_rw;
    U4              u4_t_idx;

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_B_TMWRN_RWTX_MSK));

    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_D_TMWRN_RWSGNL_NUM; u4_t_idx++) {
        if (((u1_a_VOM & (U1)ALERT_VOM_IGN_ON)                    != (U1)0U                        ) &&
            (u4_a_IGN_TM                                          >= u4_s_ALERT_D_TMWRN_TIM_RW_ENBL) &&
            ((u4_t_rw & (U4)u1_s_ALERT_B_TMWRN_DST_CRT[u4_t_idx]) != (U4)0U                        )) {
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_ON;
        }
        else {
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_OFF;
        }
    }
 
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_TMW1, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW1]);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_TMW2, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW2]);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_TMW3, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW3]);    /* COM Tx STUB delete */
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
/*  5.0.0     2/22/2024  SW       New.                                                                                               */
/*  5.1.0     4/04/2024  AA       Added remote warning (TMW1, TMW2, TMW3)                                                            */
/*                                                                                                                                   */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
