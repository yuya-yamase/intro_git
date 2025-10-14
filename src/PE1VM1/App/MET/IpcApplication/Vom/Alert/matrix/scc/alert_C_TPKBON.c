/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_TPKBON                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_TPKBON_C_MAJOR                   (5)
#define ALERT_C_TPKBON_C_MINOR                   (0)
#define ALERT_C_TPKBON_C_PATCH                   (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_TPKBON_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_TPKBON.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_TPKBON_NUM_DST                   (32U)

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
static U4      u4_s_AlertC_tpkbonSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_TPKBON_DST[ALERT_C_TPKBON_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 01 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 02 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 03 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 05 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 07 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 08 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 09 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 10 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 11 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 12 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 13 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 14 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 15 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 17 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 18 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 19 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 21 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 23 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 25 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 26 ON                                              */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 27 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON,                                                 /* 29 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_C_TPKBON_ON                                                  /* 31 ON                                              */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_TPKBON_MTRX[1] = {
    {
        &u4_s_AlertC_tpkbonSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_TPKBON_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_TPKBON_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_tpkbonSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_tpkbonSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_C_TPKBON_LSB_VSC1S95 = (U1)4U;
    static const U1 u1_s_ALERT_C_TPKBON_LSB_B_CPKB  = (U1)3U;
    static const U1 u1_s_ALERT_C_TPKBON_LSB_BDB1S01 = (U1)2U;
    static const U1 u1_s_ALERT_C_TPKBON_LSB_PKB_BDB = (U1)1U;
    static const U4 u4_s_ALERT_C_TPKBON_BIT_PKB_SW  = (U4)0x00000001U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_pkbsw_act;

    u4_t_src_chk  = (U4)0U;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S95,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_TPKBON_LSB_VSC1S95);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_B_CPKB
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_CPKB, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_CPKB */ /* 235D_CAN */
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_TPKBON_LSB_B_CPKB);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_TPKBON_LSB_BDB1S01);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PKB_BDB, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_TPKBON_LSB_PKB_BDB);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u1_t_pkbsw_act = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_C_TPKBON_PKB);
        if(u1_t_pkbsw_act == (U1)IOHW_DIFLT_SWITCH_ACT){
            u4_t_src_chk |= u4_s_ALERT_C_TPKBON_BIT_PKB_SW;
        }
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
/*  5.0.0    10/27/2021  HU       New.                                                                                               */
/*  5.0.1    11/11/2021  MO       Fix QAC Warning.                                                                                   */
/*  5.0.2    10/12/2022  SM       Update for 345D CV(Version update).                                                                */
/*  5.1.0    10/20/2023  GM       Update for 19PFv3(Version update).                                                                 */
/*                                                                                                                                   */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
