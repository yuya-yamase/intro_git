/* 5.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_PERSET                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_PERSET_C_MAJOR                   (5)
#define ALERT_B_PERSET_C_MINOR                   (0)
#define ALERT_B_PERSET_C_PATCH                   (3)

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
#if (ALERT_B_PERSET_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_PERSET.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_PERSET_NUM_DST                   (64U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0) /* _840B_CAN_ */
static U1      u1_s_alert_b_perset_bdb1s28_sts;
#endif /* defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0)  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_persetSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_PERSET_DST[ALERT_B_PERSET_NUM_DST] = {
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
    (U1)ALERT_REQ_B_PERSET_ON,                                                 /* 33 ON                                              */
    (U1)ALERT_REQ_B_PERSET_SINGLE,                                             /* 34 SINGLE                                          */
    (U1)ALERT_REQ_B_PERSET_DOUBLE,                                             /* 35 DOUBLE                                          */
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
const ST_ALERT_MTRX st_gp_ALERT_B_PERSET_MTRX[1] = {
    {
        &u4_s_AlertB_persetSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_PERSET_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_B_PERSET_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_persetInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_persetInit(void)
{
#if defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0) /* _840B_CAN_ */
    u1_s_alert_b_perset_bdb1s28_sts = (U1)COM_NO_RX;
#endif /* defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0)  */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_persetSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_persetSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0) /* _840B_CAN_ */
    static const U2 u2_s_ALERT_B_PERSET_TRSH_BDB1S28 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_PERSET_LSB_BDB1S28  = (U1)3U;
    static const U4 u4_s_ALERT_B_PERSET_BIT_BAT_WT   = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S28_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                          u2_s_ALERT_B_PERSET_TRSH_BDB1S28) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_perset_bdb1s28_sts, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_b_perset_bdb1s28_sts << u1_s_ALERT_B_PERSET_LSB_BDB1S28);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PS_MBR, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_PERSET_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
#else /* defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0)  */
    return((U4)0U);
#endif /* defined(ComConf_ComSignal_PS_MBR) && defined(OXCAN_PDU_RX_CAN_BDB1S28_RXCH0)  */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    12/15/2020  RI       New.                                                                                               */
/*  5.0.1     7/14/2021  SO       Update for 032D 1A(Version update).                                                                */
/*  5.0.2     1/20/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*  5.0.3     8/05/2022  RN       Update for 840B #2 1A(Version update).                                                             */
/*                                                                                                                                   */
/*  * RI   = Ren Itou, NTTD MSE                                                                                                      */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
