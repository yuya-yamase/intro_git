/* 5.1.1 */
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
#define ALERT_D_TMWRN_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_D_TMWRN_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_TMWRN.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_TMWRN_NUM_DST                    (27U)

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
static const U4  u4_sp_ALERT_D_TMWRN_CRIT[ALERT_D_TMWRN_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 SYSLMT_TMW1                                     */
    (U4)0x00000002U,                                                           /* 02 SYSMAL_TMW2                                     */
    (U4)0x00000003U,                                                           /* 03 SYSSTP_TMW3                                     */
    (U4)0x00000004U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x00000005U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000006U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00000007U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000008U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000010U,                                                           /* 09 UNKNOWN_TMW2                                    */
    (U4)0x00000011U,                                                           /* 10 SYSLMT_TMW2_1                                   */
    (U4)0x00000012U,                                                           /* 11 SYSMAL_TMW2                                     */
    (U4)0x00000013U,                                                           /* 12 SYSSTP_TMW2_3                                   */
    (U4)0x00000014U,                                                           /* 13 UNKNOWN_TMW2                                    */
    (U4)0x00000015U,                                                           /* 14 UNKNOWN_TMW2                                    */
    (U4)0x00000016U,                                                           /* 15 UNKNOWN_TMW2                                    */
    (U4)0x00000017U,                                                           /* 16 UNKNOWN_TMW2                                    */
    (U4)0x00000018U,                                                           /* 17 UNKNOWN_TMW2                                    */
    (U4)0x00000020U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000021U,                                                           /* 19 SYSLMT_TMW1                                     */
    (U4)0x00000022U,                                                           /* 20 SYSMAL_TMW2                                     */
    (U4)0x00000023U,                                                           /* 21 SYSSTP_TMW3                                     */
    (U4)0x00000024U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000025U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000026U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x00000027U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x00000028U                                                            /* 26 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_TMWRN_MASK[ALERT_D_TMWRN_NUM_DST] = {
    (U4)0x0000003FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 01 SYSLMT_TMW1                                     */
    (U4)0x0000003FU,                                                           /* 02 SYSMAL_TMW2                                     */
    (U4)0x0000003FU,                                                           /* 03 SYSSTP_TMW3                                     */
    (U4)0x0000003FU,                                                           /* 04 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000038U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 09 UNKNOWN_TMW2                                    */
    (U4)0x0000003FU,                                                           /* 10 SYSLMT_TMW2_1                                   */
    (U4)0x0000003FU,                                                           /* 11 SYSMAL_TMW2                                     */
    (U4)0x0000003FU,                                                           /* 12 SYSSTP_TMW2_3                                   */
    (U4)0x0000003FU,                                                           /* 13 UNKNOWN_TMW2                                    */
    (U4)0x0000003FU,                                                           /* 14 UNKNOWN_TMW2                                    */
    (U4)0x0000003FU,                                                           /* 15 UNKNOWN_TMW2                                    */
    (U4)0x0000003FU,                                                           /* 16 UNKNOWN_TMW2                                    */
    (U4)0x00000038U,                                                           /* 17 UNKNOWN_TMW2                                    */
    (U4)0x0000002FU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x0000002FU,                                                           /* 19 SYSLMT_TMW1                                     */
    (U4)0x0000002FU,                                                           /* 20 SYSMAL_TMW2                                     */
    (U4)0x0000002FU,                                                           /* 21 SYSSTP_TMW3                                     */
    (U4)0x0000002FU,                                                           /* 22 UNKNOWN                                         */
    (U4)0x0000002FU,                                                           /* 23 UNKNOWN                                         */
    (U4)0x0000002FU,                                                           /* 24 UNKNOWN                                         */
    (U4)0x0000002FU,                                                           /* 25 UNKNOWN                                         */
    (U4)0x00000028U                                                            /* 26 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_D_TMWRN_DST[ALERT_D_TMWRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_TMWRN_SYSLMT_TMW1,                                         /* 01 SYSLMT_TMW1                                     */
    (U1)ALERT_REQ_D_TMWRN_SYSMAL_TMW2,                                         /* 02 SYSMAL_TMW2                                     */
    (U1)ALERT_REQ_D_TMWRN_SYSSTP_TMW3,                                         /* 03 SYSSTP_TMW3                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 09 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_SYSLMT_TMW2_1,                                       /* 10 SYSLMT_TMW2_1                                   */
    (U1)ALERT_REQ_D_TMWRN_SYSMAL_TMW2,                                         /* 11 SYSMAL_TMW2                                     */
    (U1)ALERT_REQ_D_TMWRN_SYSSTP_TMW2_3,                                       /* 12 SYSSTP_TMW2_3                                   */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 13 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 14 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 15 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 16 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_D_TMWRN_UNKNOWN_TMW2,                                        /* 17 UNKNOWN_TMW2                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_D_TMWRN_SYSLMT_TMW1,                                         /* 19 SYSLMT_TMW1                                     */
    (U1)ALERT_REQ_D_TMWRN_SYSMAL_TMW2,                                         /* 20 SYSMAL_TMW2                                     */
    (U1)ALERT_REQ_D_TMWRN_SYSSTP_TMW3,                                         /* 21 SYSSTP_TMW3                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 26 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_TMWRN_MTRX[1] = {
    {
        &u4_s_AlertD_tmwrnSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_tmwrnRwTx,                                                /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_TMWRN_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_D_TMWRN_CRIT[0],                                          /* u4p_CRIT                                           */

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
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_D_TMWRN_LSB_MSGSTS  = (U1)3U;
    static const U1 u1_s_ALERT_TMSYS_WM_LSB_VALUE  = (U1)4U;
    static const U1 u1_s_ALERT_TMSYS_WM_LSB_MSGSTS = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMFL_IND, &u1_t_sgnl);
    
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_TMWRN_LSB_MSGSTS);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMSYS_WM, &u1_t_sgnl);

    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_TMSYS_WM_LSB_VALUE);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_TMSYS_WM_LSB_MSGSTS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_tmwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_tmwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_B_TMWRN_DST_CRT[ALERT_D_TMWRN_RWSGNL_NUM] = {
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSLMT_TMW1) | (U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSLMT_TMW2_1)), /* TMW1 */
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_UNKNOWN_TMW2)| (U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSLMT_TMW2_1)
                                                       | (U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSMAL_TMW2  )
                                                       | (U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSSTP_TMW2_3)), /* TMW2 */
        ((U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSSTP_TMW3) | (U1)((U1)1U << ALERT_REQ_D_TMWRN_SYSSTP_TMW2_3))  /* TMW3 */
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
 
    (void)Com_SendSignal(ComConf_ComSignal_TMW1, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW1]);
    (void)Com_SendSignal(ComConf_ComSignal_TMW2, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW2]);
    (void)Com_SendSignal(ComConf_ComSignal_TMW3, &u1_tp_sgnl[ALERT_D_TMWRN_RWSGNL_TMW3]);
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
/*  5.0.0     2/22/2024  SW       New.                                                                                               */
/*  5.1.0     4/04/2024  AA       Added remote warning (TMW1, TMW2, TMW3)                                                            */
/*  5.1.1     5/07/2024  JMH      Bug fix for D_TMWRN                                                                                */
/*                                                                                                                                   */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*  * JMH  = James Michael Hilarion, DTPH                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
