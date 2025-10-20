/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_DRS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_DRS_C_MAJOR                      (5)
#define ALERT_C_DRS_C_MINOR                      (0)
#define ALERT_C_DRS_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_DRS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_DRS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_DRS_NUM_DST                      (32U)

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
static U4      u4_s_AlertC_drsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_drsRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_DRS_DST[ALERT_C_DRS_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_DRS_TESTMODE,                                              /* 02 TESTMODE                                        */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 03 MALFUNC_RW                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_C_DRS_MALFUNC,                                               /* 05 MALFUNC                                         */
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
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 16 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 17 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 18 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 19 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 20 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 21 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 22 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 23 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 24 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 25 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 26 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 27 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 28 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 29 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW,                                            /* 30 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_DRS_MALFUNC_RW                                             /* 31 MALFUNC_RW                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_DRS_MTRX[1] = {
    {
        &u4_s_AlertC_drsSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_drsRwTx,                                                  /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_DRS_DST[0],                                             /* u1p_DST                                            */
        (U2)ALERT_C_DRS_NUM_DST,                                               /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_drsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_drsSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if defined(OXCAN_PDU_RX_CAN_ARS1S90) && defined(ComConf_ComSignal_ARS_METD) /* _840B_CAN_ */
    static const U1 u1_s_ALERT_C_DRS_LSB_MSGSTS = (U1)3U;
    static const U2 u2_s_ALERT_C_DRS_TO_THRESH  = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ARS1S90,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_C_DRS_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ARS_METD, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_DRS_LSB_MSGSTS);

    return(u4_t_src_chk);
#else /* defined(OXCAN_PDU_RX_CAN_ARS1S90) && defined(ComConf_ComSignal_ARS_METD) */
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_ARS1S90) && defined(ComConf_ComSignal_ARS_METD) */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_drsRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_drsRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    U1              u1_t_sgnl;
    U1              u1_t_esopt;

    u1_t_esopt = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_DRS_ARS1S90);
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                        ) &&
       (u1_t_esopt                        == (U1)TRUE                      ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_C_DRS_MALFUNC_RW)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if defined(ComConf_ComSignal_FWSW) /* _300D_CAN_ */
    (void)Com_SendSignal(ComConf_ComSignal_FWSW, &u1_t_sgnl);
#endif                              /* _300D_CAN_ */
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
/*  5.0.0     3/18/2021  MO       New.                                                                                               */
/*                                                                                                                                   */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
