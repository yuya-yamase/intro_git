/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_TBEAM12                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TBEAM12_C_MAJOR                  (5)
#define ALERT_B_TBEAM12_C_MINOR                  (1)
#define ALERT_B_TBEAM12_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_TBEAM12_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_TBEAM12.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_TBEAM12_NUM_DST                  (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH)
static U1      u1_s_alert_b_tbeam12_msgsts_bdb;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH) */
#if defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND)
static U1      u1_s_alert_b_tbeam12_msgsts_afs;
#endif /* defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_tbeam12Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_TBEAM12_DST[ALERT_B_TBEAM12_NUM_DST] = {
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
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 17 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 20 ON                                              */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 21 ON                                              */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 22 ON                                              */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 23 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 25 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_B_TBEAM12_ON,                                                /* 29 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_TBEAM12_MTRX[1] = {
    {
        &u4_s_AlertB_tbeam12Srcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_TBEAM12_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_B_TBEAM12_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_tbeam12Init(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_tbeam12Init(void)
{
#if defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH)
    u1_s_alert_b_tbeam12_msgsts_bdb = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH) */
#if defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND)
    u1_s_alert_b_tbeam12_msgsts_afs = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_tbeam12Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_tbeam12Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND)
    static const U2 u2_s_ALERT_B_TBEAM_THRSH_TO_AFS = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TBEAM_LSB_AFSSTS   = (U1)1U;
    U1              u1_t_sgnl_azb;
#endif /* defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND) */
#if defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH)
    static const U2 u2_s_ALERT_B_TBEAM_THRSH_TO_BDB = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_TBEAM_LSB_HEDH     = (U1)2U;
    static const U1 u1_s_ALERT_B_TBEAM_LSB_BDBSTS   = (U1)3U;
    U1              u1_t_sgnl_hedh;
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH) */
    static const U4 u4_s_ALERT_B_TBEAM_BIT_BAT_WT   = (U4)0x00000010U;
    U1              u1_t_trns_fact;
    U4              u4_t_src_chk;

#if defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND)
    u1_t_trns_fact = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_AFS1S01,
                                           (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                           u2_s_ALERT_B_TBEAM_THRSH_TO_AFS) & (U1)(COM_TIMEOUT | COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tbeam12_msgsts_afs, u1_t_trns_fact);

    u1_t_sgnl_azb  = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_AZB_HIND, &u1_t_sgnl_azb);

    u4_t_src_chk   = (U4)u1_t_sgnl_azb;
    u4_t_src_chk  |= (((U4)u1_s_alert_b_tbeam12_msgsts_afs & (U4)COM_NO_RX) << u1_s_ALERT_B_TBEAM_LSB_AFSSTS);
#else
    u4_t_src_chk   = (U4)0U;
#endif /* defined(OXCAN_PDU_RX_CAN_AFS1S01) && defined(ComConf_ComSignal_AZB_HIND) */

#if defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH)
    u1_t_trns_fact = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S03_RXCH0,
                                           (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                           u2_s_ALERT_B_TBEAM_THRSH_TO_BDB) & (U1)(COM_TIMEOUT | COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_tbeam12_msgsts_bdb, u1_t_trns_fact);

    u1_t_sgnl_hedh = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HEDH, &u1_t_sgnl_hedh);

    u4_t_src_chk  |= ((U4)u1_t_sgnl_hedh                                    << u1_s_ALERT_B_TBEAM_LSB_HEDH);
    u4_t_src_chk  |= (((U4)u1_s_alert_b_tbeam12_msgsts_bdb & (U4)COM_NO_RX) << u1_s_ALERT_B_TBEAM_LSB_BDBSTS);
#endif /* defined(OXCAN_PDU_RX_CAN_BDB1S03_RXCH0) && defined(ComConf_ComSignal_HEDH) */

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk   |= u4_s_ALERT_B_TBEAM_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/12/2020  MY       New.                                                                                               */
/*  5.1.0     8/31/2020  KH       Change AFS1S01/BDB1S03 THRSH time to 10000ms -> 5000ms.                                            */
/*                                                                                                                                   */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * KH   = Koji Hattori, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
