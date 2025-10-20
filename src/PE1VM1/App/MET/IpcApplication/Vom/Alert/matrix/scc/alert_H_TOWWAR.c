/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_TOWWAR                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_TOWWAR_C_MAJOR                   (5)
#define ALERT_H_TOWWAR_C_MINOR                   (3)
#define ALERT_H_TOWWAR_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_TOWWAR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_TOWWAR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_TOWWAR_NUM_DST                   (7U)

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
static U4      u4_s_AlertH_towwarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_towwarRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_H_TOWWAR_CRIT[ALERT_H_TOWWAR_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 MLFNC_HV2                                       */
    (U4)0x00000031U,                                                           /* 01 MLFNC_HV                                        */
    (U4)0x00000041U,                                                           /* 02 MLFNC_HV                                        */
    (U4)0x00000051U,                                                           /* 03 MLFNC_EV                                        */
    (U4)0x00000071U,                                                           /* 04 MLFNC_FCV                                       */
    (U4)0x000001F1U,                                                           /* 05 MLFNC_HV                                        */
    (U4)0x00000001U                                                            /* 06 MLFNC                                           */
};
static const U4  u4_sp_ALERT_H_TOWWAR_MASK[ALERT_H_TOWWAR_NUM_DST] = {
    (U4)0x000001FFU,                                                           /* 00 MLFNC_HV2                                       */
    (U4)0x000001FFU,                                                           /* 01 MLFNC_HV                                        */
    (U4)0x000001DFU,                                                           /* 02 MLFNC_HV                                        */
    (U4)0x000001FFU,                                                           /* 03 MLFNC_EV                                        */
    (U4)0x000001FFU,                                                           /* 04 MLFNC_FCV                                       */
    (U4)0x000001FFU,                                                           /* 05 MLFNC_HV                                        */
    (U4)0x0000000FU                                                            /* 06 MLFNC                                           */
};
static const U1  u1_sp_ALERT_H_TOWWAR_DST[ALERT_H_TOWWAR_NUM_DST] = {
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV2,                                          /* 00 MLFNC_HV2                                       */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV,                                           /* 01 MLFNC_HV                                        */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV,                                           /* 02 MLFNC_HV                                        */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_EV,                                           /* 03 MLFNC_EV                                        */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_FCV,                                          /* 04 MLFNC_FCV                                       */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV,                                           /* 05 MLFNC_HV                                        */
    (U1)ALERT_REQ_H_TOWWAR_MLFNC                                               /* 06 MLFNC                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_TOWWAR_MTRX[1] = {
    {
        &u4_s_AlertH_towwarSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_towwarRwTx,                                               /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_TOWWAR_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_H_TOWWAR_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_TOWWAR_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_H_TOWWAR_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_towwarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_towwarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
#if defined(OXCAN_PDU_RX_CAN_EHV1S94) && defined(ComConf_ComSignal_TOWW)
    static const U2 u2_s_ALERT_H_TOWWAR_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_TOWWAR_LSB_MSGSTS = (U1)2U;
    static const U1 u1_s_ALERT_H_TOWWAR_LSB_PTSYS  = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S94,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_H_TOWWAR_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TOWW, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_TOWWAR_LSB_MSGSTS);

    u1_t_sgnl     = u1_g_AlertPtsys();
    if(u1_t_sgnl > (U1)ALERT_PTSYS_1F_NRX){
        u1_t_sgnl = (U1)ALERT_PTSYS_0F_UNK;
    }

    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_H_TOWWAR_LSB_PTSYS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1S94) && defined(ComConf_ComSignal_TOWW) */
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_towwarRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_towwarRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U               ) &&
       (u1_a_DST                          != (U1)ALERT_REQ_UNKNOWN)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_PULW, &u1_t_sgnl);
#endif /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/23/2020  SK       New.                                                                                               */
/*  5.1.0     9/10/2020  MO       BC_CH and PD_CH were unified to H_TOWWAR_CH and failure judge processing was added.                */
/*  5.2.0     9/18/2020  MO       Processing reception PTSYS signal was fixed.                                                       */
/*  5.2.1     3/26/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.2.2     5/14/2021  TN       Fix 800B Bug.                                                                                      */
/*  5.2.3     6/30/2021  KT       Update for 050D CV(Version update).                                                                */
/*  5.3.0     5/13/2022  SAO      Fix 050D Bug(RW).                                                                                  */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
